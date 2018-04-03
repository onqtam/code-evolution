#include "evaluator.h"

#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cassert>

using namespace std;

namespace evaluator
{
namespace
{
template <size_t N>
bool match(const char* str, const char (&key)[N]) {
    // no need to check for '\0' in str - it will be different from the key array anyway
    for(auto i = 0u; i < N - 1; ++i)
        if(str[i] != key[i])
            return false;
    return true;
}

bool match(const char* str, char c) { return *str == c; }

// advances the pointer if the string is matched
template <size_t N>
bool match_adv(const char*& str, const char (&key)[N]) {
    auto matches = match(str, key);
    if(matches)
        str += N - 1;
    return matches;
}

// advances the pointer if the character is matched
bool match_adv(const char*& str, char c) {
    auto matches = match(str, c);
    if(matches)
        ++str;
    return matches;
}

// skips all whitespace
void skip_whitespace(const char*& str) {
    while(isspace(*str))
        ++str;
}

enum class token_type
{
    oper,
    func,
    paren,
    number,
    var
};

enum class oper_token
{
    eq,
    add,
    sub,
    mul,
    div
};

enum class func_token
{
    neg,
    log,
    sin,
    cos
};

enum class paren_token
{
    open,
    close
};

struct var_tag
{
};

struct token
{
    token_type type;
    union
    {
        double      val;
        func_token  func;
        oper_token  oper;
        paren_token paren;
    };

    // clang-format off
	token(double in) : type(token_type::number), val(in) {}
	token(func_token in) : type(token_type::func), func(in) {}
	token(oper_token in) : type(token_type::oper), oper(in) {}
	token(paren_token in) : type(token_type::paren), paren(in) {}
	token(var_tag) : type(token_type::var) {}
    // clang-format on
};

// uses the shunting-yard algorithm to convert to reverse polish notation
// adapted from here: https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm#D
vector<token> infix_to_postfix(const vector<token>& tokens) {
    vector<token> out;
    vector<token> stack;

    auto precedence = [](oper_token op) {
        switch(op) {
            case oper_token::eq: return 0;
            case oper_token::add: return 1;
            case oper_token::sub: return 1;
            case oper_token::mul: return 2;
            case oper_token::div: return 2;
            default: assert(false); return 0;
        }
    };
    auto transfer_last = [](auto& src, auto& dst) {
        dst.push_back(src.back());
        src.pop_back();
    };

    for(auto& token : tokens) {
        if(token.type == token_type::func) {
            stack.push_back(token);
        } else if(token.type == token_type::oper) {
            while(!stack.empty() &&
                  ((stack.back().type == token_type::oper && precedence(stack.back().oper) >= precedence(token.oper)) ||
                   stack.back().type == token_type::func))
                transfer_last(stack, out);
            stack.push_back(token);
        } else if(token.type == token_type::paren && token.paren == paren_token::open) {
            stack.push_back(token);
        } else if(token.type == token_type::paren && token.paren == paren_token::close) {
            while(stack.back().type != token_type::paren || stack.back().paren != paren_token::open)
                transfer_last(stack, out);
            stack.pop_back();
        } else {
            out.push_back(token);
        }
    }

    while(!stack.empty())
        transfer_last(stack, out);

    return out;
}

double eval_postfix_expression(const vector<token>& tokens) {
    vector<double> data;
    for(auto& curr : tokens) {
        if(curr.type == token_type::oper) {
            assert(data.size() > 1);
            if(curr.oper == oper_token::add) {
                data[data.size() - 2] += data.back();
            } else if(curr.oper == oper_token::sub) {
                data[data.size() - 2] -= data.back();
            } else if(curr.oper == oper_token::mul) {
                data[data.size() - 2] *= data.back();
            } else {
                assert(curr.oper == oper_token::div);
                if(data.back() == 0)
                    throw runtime_error("Cannot divide by 0");
                data[data.size() - 2] /= data.back();
            }
            data.pop_back();
        } else if(curr.type == token_type::func) {
            assert(data.size() > 0);
            if(curr.func == func_token::neg) {
                data.back() = -data.back();
            } else if(curr.func == func_token::sin) {
                data.back() = sin(data.back());
            } else if(curr.func == func_token::cos) {
                data.back() = cos(data.back());
            } else {
                assert(curr.func == func_token::log);
                if(data.back() <= 0)
                    throw runtime_error("Argument to log should be greater than 0");
                data.back() = log10(data.back());
            }
        } else {
            assert(curr.type == token_type::number);
            data.push_back(curr.val);
        }
    }
    assert(data.size() == 1);
    return data.back();
}

// struct used to represent the 2 coefficients in expressions of the form "a * x + b" where b is the free coef
struct coef_pair
{
    double var_coef  = 0;
    double free_coef = 0;
};

double solve_postfix_equation(const vector<token>& tokens) {
    vector<coef_pair> st;
    for(auto& curr : tokens) {
        if(curr.type == token_type::oper) {
            auto popped = st.back();
            st.pop_back();
            auto& last = st.back();

            if(curr.oper == oper_token::mul) {
                // imagine we have (a*x + b) * (c*x + d):
                // there are 3 valid scenarios for a linear equation:
                // - a and c are 0
                // - a is non-zero and c is 0
                // - a is 0 and c is non-zero
                if(last.var_coef != 0 && popped.var_coef != 0)
                    throw runtime_error("Equation not linear");

                // multiply the right variable coef with the right free coef
                if(last.var_coef != 0)
                    last.var_coef *= popped.free_coef;
                else
                    popped.var_coef *= last.free_coef;
                // combine the result - one of them was 0 anyway
                last.var_coef += popped.var_coef;
                // the free coefs can be directly multiplied
                last.free_coef *= popped.free_coef;
            } else if(curr.oper == oper_token::add) {
                last.free_coef += popped.free_coef;
                last.var_coef += popped.var_coef;
            } else if(curr.oper == oper_token::sub || curr.oper == oper_token::eq) {
                // treat the equality operator as a subtraction - and the whole thing will be equal to 0 at the end
                last.free_coef -= popped.free_coef;
                last.var_coef -= popped.var_coef;
            } else {
                throw runtime_error("Unsupported operator in equation mode");
            }
        } else if(curr.type == token_type::var) {
            st.push_back({1, 0});
        } else if(curr.type == token_type::number) {
            st.push_back({0, curr.val});
        } else {
            assert(curr.type == token_type::func);
            if(curr.func == func_token::neg) {
                st.back().free_coef *= -1;
                st.back().var_coef *= -1;
            } else {
                throw runtime_error("Unsupported function in equation mode");
            }
        }
    }
    assert(st.size() == 1);
    // we should have arrived to a "a * x + b = 0" form so the answer is "-b/a"
    if(st.back().var_coef == 0)
        throw runtime_error("Equation has no answer");
    return -st.back().free_coef / st.back().var_coef;
}

// based on ideas from here: https://www.strchr.com/expression_evaluator
class ExprEval
{
    int         parens = 0;
    const char* begin  = nullptr;
    const char* expr   = nullptr;

    std::vector<token> tokens;

	// helper that computes the position of the error in the original input
    void parse_error(const char* msg) { throw ParseException(msg, expr - begin); }

    // parse a number, identifier or an expression in parentheses
    void parse_atom() {
        skip_whitespace(expr);

        // handle the sign before parentheses, numbers, functions or identifiers - as a function
        if(match_adv(expr, '-'))
            tokens.push_back(token(func_token::neg));

        // handle functions
        bool is_func = false;
        if(match_adv(expr, "log")) {
            tokens.push_back(token(func_token::log));
            is_func = true;
        } else if(match_adv(expr, "sin")) {
            tokens.push_back(token(func_token::sin));
            is_func = true;
        } else if(match_adv(expr, "cos")) {
            tokens.push_back(token(func_token::cos));
            is_func = true;
        }

        skip_whitespace(expr);

        // check if there is parentheses
        if(match_adv(expr, '(')) {
            ++parens;
            tokens.push_back(paren_token::open);

            parse_summands();

            if(!match_adv(expr, ')'))
                parse_error("Unmatched opening parentheses");

            --parens;
            tokens.push_back(paren_token::close);

            return;
        } else {
            if(is_func)
                parse_error("Expected parentheses after function");
        }

        // try to match the 'x' identifier for equations
        if(match_adv(expr, 'x')) {
            tokens.push_back(var_tag());
            return;
        }

        // it should be a number - convert to double
        char*  end_ptr;
        double res = strtod(expr, &end_ptr);
        if(end_ptr == expr)
            parse_error("Unexpected character");
        // advance the pointer and add the token
        expr = end_ptr;
        tokens.push_back(res);
    }

    // parse multiplication and division
    void parse_factors() {
        parse_atom();
        for(;;) {
            skip_whitespace(expr);

            if(match_adv(expr, '/')) {
                tokens.push_back(oper_token::div);
            } else if(match_adv(expr, '*')) {
                tokens.push_back(oper_token::mul);
            } else {
                return;
            }
            parse_atom();
        }
    }

    // parse addition, subtraction and equality
    void parse_summands() {
        parse_factors();
        for(;;) {
            skip_whitespace(expr);

            if(match_adv(expr, '-')) {
                tokens.push_back(oper_token::sub);
            } else if(match_adv(expr, '+')) {
                tokens.push_back(oper_token::add);
            } else if(match_adv(expr, '=')) {
                tokens.push_back(oper_token::eq);
            } else {
                return;
            }
            parse_factors();
        }
    }

    void parse(const char* in) {
        parens = 0;
        expr   = in;
        begin  = in;
        tokens.clear();

        parse_summands();

        // now, expr should point to '\0', and parens should be zero
        if(parens != 0 || *expr == ')')
            parse_error("Unmatched closing parentheses");
        if(*expr != '\0')
            parse_error("Unexpected character");

        tokens = infix_to_postfix(tokens);
    }

public:
    double eval(const char* in) {
        parse(in);

        auto is_eq = [](const auto& in) { return in.type == token_type::oper && in.oper == oper_token::eq; };

        auto var_it = find_if(tokens.begin(), tokens.end(), [](const auto& in) { return in.type == token_type::var; });
        auto eq_it  = find_if(tokens.begin(), tokens.end(), is_eq);

        // equations have both a variable and the equals operator in them
        if(var_it != tokens.end() && eq_it == tokens.end())
            throw runtime_error("Found variable but not an equation");
        if(var_it == tokens.end() && eq_it != tokens.end())
            throw runtime_error("Equation without a variable");

        if(var_it == tokens.end()) {
            return eval_postfix_expression(tokens);
        } else {
            if(count_if(tokens.begin(), tokens.end(), is_eq) > 1)
                throw runtime_error("More than 1 equality operators found in equation");
            return solve_postfix_equation(tokens);
        }
    }
};
} // namespace

double eval(const char* in) {
    ExprEval e;
    return e.eval(in);
}

} // namespace evaluator
