#ifndef SCANNER

#define SCANNER



#include <iostream>
#include <fstream>
using namespace std;

//this specifies the types of tokens
enum TokenType{ERROR, ENDOFFILE, LBRACE, RBRACE, EQUALASSIGN, EE, NE, SEMI, MOD, RPAREN, LPAREN, GRE, GR, LT, LTE, MULTIPLY, DIVIDE, PLUS, MINUS, COMMA, AND, OR, NOT, DOT, QUOTED,INT, FLOAT,STRING,TEXTURE, DEFINE, NONE /*this is for if the file is empty*/};

class Scanner
{
public:
	Scanner(string filename);

	//these functions get the current and 
	TokenType currentTokenType();
	TokenType nextTokenType();
	string currentTokenString();
	string nextTokenString();

	//this function advances the scanner to the next thing.
	void advance();

	//this function takes a Token and converts it to the string that represents it.
	string toString(TokenType t);

	//returns the current line of the token
	int getLine();
private:
	ifstream filestream;
	string currents;
	string nexts;
	TokenType currenttt;
	TokenType nexttt;

	//this function should be called if you know an error character is currently in the buffer
	void dealWithError(string buffer);

	int linenext;
	int linecurrent;
};

#endif // !