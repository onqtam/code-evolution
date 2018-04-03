#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// a hacky extension to doctest - until this issue is resolved: https://github.com/onqtam/doctest/issues/97
#define CHECK_THROWS_WITH(expr, message)                                                                               \
    do {                                                                                                               \
        doctest::String _doctest_exception_string = "Didn't throw at all";                                             \
        try {                                                                                                          \
            expr;                                                                                                      \
        } catch(std::exception & e) { _doctest_exception_string = e.what(); } catch(...) {                             \
            _doctest_exception_string = "Unknown exception";                                                           \
        }                                                                                                              \
        DOCTEST_CHECK(_doctest_exception_string == doctest::String(message));                                          \
    } while((void)0, 0)

#include "evaluator.h"

using namespace evaluator;
using doctest::Approx;

const char* unexp_char       = "Unexpected character";
const char* open_paren       = "Unmatched opening parentheses";
const char* close_paren      = "Unmatched closing parentheses";
const char* div_zero         = "Cannot divide by 0";
const char* paren_after_func = "Expected parentheses after function";
const char* log_above_zero   = "Argument to log should be greater than 0";
const char* no_eq            = "Found variable but not an equation";
const char* no_var           = "Equation without a variable";
const char* more_eq          = "More than 1 equality operators found in equation";
const char* non_linear       = "Equation not linear";
const char* unsup_op         = "Unsupported operator in equation mode";
const char* unsup_func       = "Unsupported function in equation mode";
const char* no_answer        = "Equation has no answer";

TEST_CASE("expression evaluation") {
    // basics
    CHECK(eval("2 + 3") == 5);
    CHECK(eval("2 * 3") == 6);
    CHECK(eval("89") == 89);
    CHECK_THROWS_WITH(eval(""), unexp_char);

    // should handle spaces gracefully
    CHECK(eval("   12        -  8   ") == 4);
    CHECK(eval("142        -9   ") == 133);
    CHECK(eval("72+  15") == 87);
    CHECK(eval(" 12*  4") == 48);
    CHECK(eval(" 50/10") == 5);

    // should treat dot separated floating point numbers as a valid input
    CHECK(eval("2.5") == 2.5);
    CHECK(eval("4*2.5 + 8.5+1.5 / 3.0") == 19);
    CHECK(eval("5.0005 + 0.0095") == Approx(5.01));

    // should handle tight expressions
    CHECK(eval("67+2") == 69);
    CHECK(eval(" 2-7") == -5);
    CHECK(eval("5*7 ") == 35);
    CHECK(eval("8/4") == 2);

    // should calculate long additive expressions from left to right
    CHECK(eval("2 -4 +6 -1 -1") == 2);
    CHECK(eval("2 -4 +6 -1 -1- 0 +8") == 10);
    CHECK(eval("1 -1   + 2   - 2   +  4 - 4 +    6") == 6);

    // should calculate long multiplicative expressions from left to right
    CHECK(eval("2 -4 +6 -1 -1- 0 +8") == 10);
    CHECK(eval("1 -1   + 2   - 2   +  4 - 4 +    6") == 6);

    // should calculate long, mixed additive and multiplicative expressions from left to right
    CHECK(eval(" 2*3 - 4*5 + 6/3 ") == -12);
    CHECK(eval("2*3*4/8 -   5/2*4 +  6 + 0/3   ") == -1);

    // should return float pointing numbers when division result is not an integer
    CHECK(eval("10/4") == 2.5);
    CHECK(eval("5/3") == Approx(1.66666));
    CHECK(eval("3 + 8/5 -1 -2*5") == Approx(-6.4));

    // should raise an error on wrong token
    CHECK_THROWS_WITH(eval("  6 + c"), unexp_char);
    CHECK_THROWS_WITH(eval("  7 & 2"), unexp_char);
    CHECK_THROWS_WITH(eval("  %"), unexp_char);

    // should raise an error on syntax error
    CHECK_THROWS_WITH(eval(" 5 + + 6"), unexp_char);
    //CHECK_THROWS_WITH(eval(" --5 + 2"), unexp_char);

    // should return Infinity when attempt to divide by zero occurs
    CHECK_THROWS_WITH(eval("5/0"), div_zero);
    CHECK_THROWS_WITH(eval(" 2 - 1 + 14/(7 - 7)"), div_zero);

    // should compute 2 when given (2)
    CHECK(eval("(2)") == 2);

    // should compute complex expressions enclosed in parentheses
    CHECK(eval("(5 + 2*3 - 1 + 7 * 8)") == 66);
    CHECK(eval("(67 + 2 * 3 - 67 + 2/1 - 7)") == 1);

    // should compute expressions with many subexpressions enclosed in parentheses
    CHECK(eval("(2) + (17*2-30) * (5)+2 - (8/2)*4") == 8);
    CHECK_THROWS_WITH(eval("(5*7/5) + (23) - 5 * (98-4)/(6*7-42)"), div_zero);

    // should handle nested parentheses
    CHECK(eval("(((((5)))))") == 5);
    CHECK(eval("(( ((2)) + 4))*((5))") == 30);

    // should raise an error on unbalanced parentheses
    CHECK_THROWS_WITH(eval("2 + (5 * 2"), open_paren);
    CHECK_THROWS_WITH(eval("(((((4))))"), open_paren);
    CHECK_THROWS_WITH(eval("((2)) * ((3"), open_paren);
    CHECK_THROWS_WITH(eval("((9)) * ((1)"), open_paren);
    CHECK_THROWS_WITH(eval("((9)) * 1)"), close_paren);
    CHECK_THROWS_WITH(eval("2 * 1) + 5"), close_paren);

    // functions sin, cos and log should work
    CHECK(eval("sin(1.57079633)") == 1);
    CHECK(eval("sin(cos(0))") == Approx(0.8414709848));
    CHECK(eval("4 + sin(1) * 1 - 4") == Approx(0.8414709848));
    CHECK(eval("log(10)") == Approx(1));
    CHECK(eval("log   (10)") == Approx(1));
    CHECK(eval("5 + 8 * -log((-12 + log(100)) * -10) * log(1000)") == -43);
    CHECK_THROWS_WITH(eval("log 10"), paren_after_func);
    CHECK_THROWS_WITH(eval("log(6 - (3*2 ))"), log_above_zero);
    CHECK_THROWS_WITH(eval("log(-sin(1))"), log_above_zero);
}

TEST_CASE("equation solving") {
    // check invalid equations
    CHECK_THROWS_WITH(eval("x + 5 * 4 - (x - 4) * 2 - 0"), no_eq);
    CHECK_THROWS_WITH(eval("5 * 4 - (4) = - 4 * 2 - 0"), no_var);
    CHECK_THROWS_WITH(eval("5 * x - (4) = - 4 * 2 - 3 = 0"), more_eq);

    // detect non-linear equations
    CHECK_THROWS_WITH(eval("x * 5 * (4 * (x - 2)) - (x - 4) * 2 - 0 = 0"), non_linear);
    CHECK_THROWS_WITH(eval("(x  + 6) * 5 * (4 * (x - 2)) = x"), non_linear);

    // invalid uses of operators/functions
    CHECK_THROWS_WITH(eval("x + (2 / (1 - 5)) = 0"), unsup_op);
    CHECK_THROWS_WITH(eval("x + sin(2) = 0"), unsup_func);
    CHECK_THROWS_WITH(eval("x + cos(2) = 0"), unsup_func);
    CHECK_THROWS_WITH(eval("x + log(2) = 0"), unsup_func);

    // equations with no possible solutions
    CHECK_THROWS_WITH(eval("x = x + 2"), no_answer);
    CHECK_THROWS_WITH(eval("2 * x = (1 + 1) * x + 0.1"), no_answer);

    // equations where 0 is the only possibility
    CHECK(eval("0 = x") == 0);
    CHECK(eval("(5 - (10 - 5)) = (((2))) * x") == 0);

    // actual legit equations
    CHECK(eval("(3 + x) * (2 * (1 - 5)) = x - 6") == -2);
    CHECK(eval("x * 2 + (5 * 2 + 5 * (3 - 4) * x) * 2 = -7") == 3.375);
    CHECK(eval("(((2 + x) * 2 + 1) * (3 - 1 * 2) - 5) * 2 - 1 = x * (5 + 2)") == Approx(-0.3333333333));
}
