#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

enum TokenType
{
	tokenType_none,
	tokenType_number,
	tokenType_identifier,

	//
	tokenType_semicolon, // ;
	tokenType_assign, // =
	tokenType_plus, // +
	tokenType_minus, // -
	tokenType_asterisk, // *
	tokenType_slash, // /
	tokenType_lparen, // (
	tokenType_rparen, // )
};


struct Token
{
	Token() = default;
	explicit Token(TokenType type) : 
		type(type)
	{}

	TokenType type = tokenType_none;
	float numberData;
	std::string strData;
};

bool isSign(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

struct Lexer
{
	Lexer(const char* const code) :
		m_code(code),
		m_ptr(code)
	{}

	void skipSpacesAhead()
	{
		while(isspace(*m_ptr))
			m_ptr++;
	}

	Token getNextToken()
	{
		skipSpacesAhead();

		if(*m_ptr == '\0')
		{
			// No more tokes to process, this should be it!
			Token token;
			return token;
		}
		else if(isalpha(*m_ptr) || *m_ptr == '_')
		{
			Token token;

			// This should be an indentifier.
			token.type = tokenType_identifier;
			while(isalpha(*m_ptr) || *m_ptr == '_'|| isdigit(*m_ptr))
			{
				token.strData.push_back(*m_ptr);
				m_ptr++;
			}

			return token;
		}
		else if(*m_ptr == ';') {
			m_ptr++;
			return Token(tokenType_semicolon);
		}
		else if(*m_ptr == '=') {
			m_ptr++;
			return Token(tokenType_assign);
		}
		else if(*m_ptr == '*') {
			m_ptr++;
			return Token(tokenType_asterisk);
		}
		else if(*m_ptr == '/') {
			m_ptr++;
			return Token(tokenType_slash);
		}
		else if(*m_ptr == '+') {
			m_ptr++;
			return Token(tokenType_plus);
		}
		else if(*m_ptr == '-') {
			m_ptr++;
			return Token(tokenType_minus);
		}
		else if(*m_ptr == '(') {
			m_ptr++;
			return Token(tokenType_lparen);
		}
		else if(*m_ptr == ')') {
			m_ptr++;
			return Token(tokenType_rparen);
		}
		else if(isdigit(*m_ptr))
		{
			// This should be a number.
			// TODO: Floating point numbers.
			float numberAccum = 0;
			while(isdigit(*m_ptr)){
				int digit = *m_ptr - '0';
				numberAccum = numberAccum*10.f + (float)digit;
				m_ptr++;
			}

			Token token;
			token.type = tokenType_number;
			token.numberData = numberAccum;

			return token;
		}

		// Should never happen.
		assert(false);
		return Token();
	}

	const char* m_code = nullptr;
	const char* m_ptr = nullptr;
};

enum AstNodeType
{
	astNodeType_invalid,
	astNodeType_number,
	astNodeType_identifier,
	astNodeType_binop,
	astNodeType_unop,
	astNodeType_assign,
};

struct AstNode
{
	AstNode(AstNodeType const type = astNodeType_invalid) :
		type(type)
	{}
	virtual ~AstNode() = default;

	AstNodeType type;
};

struct AstNumber : public AstNode
{
	AstNumber(float const value = NAN) 
		: AstNode(astNodeType_number)
		, value(value)
	{}

	float value = NAN;
};

struct AstIdentifier : public AstNode
{
	AstIdentifier(std::string identifier) 
		: AstNode(astNodeType_identifier)
		, identifier(identifier)
	{}

	std::string identifier;
};

struct AstBinOp : public AstNode
{
	AstBinOp(char op, AstNode* left, AstNode* right) 
		: AstNode(astNodeType_binop)
		, op(op)
		, left(left)
		, right(right)
	{}

	AstNode* left;
	AstNode* right;
	char op; // + - * /
};

struct AstUnOp : public AstNode
{
	AstUnOp(char op, AstNode* left) 
		: AstNode(astNodeType_unop)
		, op(op)
		, left(left)
	{}

	AstNode* left;
	char op; // + -
};

struct AstAssign : public AstNode
{
	
	AstAssign(AstNode* left, AstNode* right) 
		: AstNode(astNodeType_assign)
		, left(left)
		, right(right)
	{}

	AstNode* left;
	AstNode* right;
};

struct Parser
{

	AstNode* root = nullptr;
	const Token* m_token = nullptr;

	void parse()
	{
		root = parse_expression();
	}

	AstNode* parse_expression()
	{
		return parse_expression4();
	}

	AstNode* parse_exporession0()
	{
		if(m_token->type == tokenType_number)
		{
			AstNode* const result =  new AstNumber(m_token->numberData);
			matchAny();
			return result;
		}
		else if(m_token->type == tokenType_identifier)
		{
			AstNode* const result =  new AstIdentifier(m_token->strData);
			matchAny();
			return result;
		}
		else if(m_token->type == tokenType_lparen)
		{
			matchAny();
			AstNode* const result =  parse_expression();
			match(tokenType_rparen);
			return result;
		}

		assert(false);
		return nullptr;
	}

	AstNode* parse_expression1()
	{
		AstNode* left = parse_exporession0();

		if(m_token->type == tokenType_asterisk)
		{
			matchAny();
			AstNode* retval = new AstBinOp('*', left, parse_expression());
			return retval;
		}
		else if(m_token->type == tokenType_slash)
		{
			matchAny();
			AstNode* retval = new AstBinOp('/', left, parse_expression());
			return retval;
		}

		return left;
	}

	AstNode* parse_expression2()
	{
		AstNode* left = parse_expression1();

		if(m_token->type == tokenType_plus)
		{
			matchAny();
			AstNode* retval = new AstBinOp('+', left, parse_expression());
			return retval;
		}
		else if(m_token->type == tokenType_minus)
		{
			matchAny();
			AstNode* retval = new AstBinOp('-', left, parse_expression());
			return retval;
		}

		return left;
	}

	AstNode* parse_expression3()
	{
		if(m_token->type == tokenType_minus)
		{
			matchAny();
			AstUnOp* const result =  new AstUnOp('-', parse_expression());
			return result;
		}
		else if(m_token->type == tokenType_plus)
		{
			matchAny();
			AstUnOp* const result =  new AstUnOp('+', parse_expression());
			return result;
		}
		
		return parse_expression2();
	}

	AstNode* parse_expression4()
	{
		AstNode* left = parse_expression3();

		if(m_token->type == tokenType_assign)
		{
			matchAny();
			AstAssign* assign = new AstAssign(left, parse_expression());
			return assign;
		}

		return left;
	}

	void matchAny()
	{
		++m_token;
	}

	void match(TokenType const type)
	{
		if(m_token->type != type)
		{
			// A compilation error here!
			assert(false);
			return;
		}
		++m_token;
	}
};

void printNode(const AstNode* const n, const int tab)
{
	auto const ident = [](int cnt) {
		while(cnt) {
			printf("  ");
			cnt--;
		}
	};

	ident(tab);

	if(n->type == astNodeType_identifier)
	{
		const AstIdentifier* ident = (AstIdentifier*)n;
		printf("ident(%s)", ident->identifier.c_str());
	}
	else if(n->type == astNodeType_number)
	{
		const AstNumber* num = (AstNumber*)n;
		printf("num(%f)", num->value);
	}
	else if(n->type == astNodeType_binop)
	{
		const AstBinOp* op = (AstBinOp*)n;
		printf(" (%c ", op->op);
		printNode(op->left, tab);
		printf(" ");
		printNode(op->right, tab);
		printf(") ");
	}
	else if(n->type == astNodeType_assign)
	{
		const AstAssign* assign = (AstAssign*)n;
		printNode(assign->left, tab);
		printf(" = ");
		printNode(assign->right, tab);
	}
	else if(n->type == astNodeType_unop)
	{
		const AstUnOp* op = (AstUnOp*)n;
		printf("u%c", op->op);
		printNode(op->left, tab);
	}
	else
	{
		printf("???\n");
	}
}

int main2()
{
	const char* const testCode = R"(
x = y+77/2*(321+1/1 = 2) = -0-+1*(2+-y*-(a+b))
)";

	Lexer lexer(testCode);

	std ::vector<Token> tokens;

	while(true)
	{
		const Token tok = lexer.getNextToken();
		tokens.push_back(tok);
	
		if(tok.type == tokenType_number) printf("%f ", tok.numberData);
		if(tok.type == tokenType_identifier) printf("IDENT(%s) ", tok.strData.c_str());
		if(tok.type == tokenType_semicolon) printf("; \n");
		if(tok.type == tokenType_assign) printf("= ");
		if(tok.type == tokenType_plus) printf("+ ");
		if(tok.type == tokenType_minus) printf("- ");
		if(tok.type == tokenType_asterisk) printf("* ");
		if(tok.type == tokenType_slash) printf("/ ");
		if(tok.type == tokenType_lparen) printf("(");
		if(tok.type == tokenType_rparen) printf(") ");
		if(tok.type == tokenType_none) { printf("\nNONE;\n "); break; }
	}

	Parser p;
	p.m_token = tokens.data();

	p.parse();
	AstNode* root = p.root;

	printNode(root, 0);

	return 0;
}