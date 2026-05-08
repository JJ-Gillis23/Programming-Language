#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Scanner.h"
#include "Type.h"
using namespace std;


class	ASTProgram;
class	ASTTopLevel;
class 	ASTFunction;
class	ASTParam;
class	ASTStatements;
class	ASTStatement;
class	ASTArgs;
class	ASTIf;
class ASTFor;
class	ASTAssign;
class	ASTWhile;
class	ASTFunctionCall;
class	ASTFunctionCallStmt;
class	ASTBlockStatement;
class	ASTDeclaration;
class	ASTBoolExprA;
class	ASTBoolExprB;
class	ASTTerm;
class	ASTExpr;
class	ASTFactor;
class	ASTElement;
class 	ASTDefine;
class 	ASTTexture;



//parent of all the nodes in the tree
class ASTNode
{
public:
	virtual void print(int depth) = 0;
	virtual Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError) = 0;
	virtual void generateCode(ofstream& out, int& tempCount, int& labelCount) = 0;
	// returns the register name holding the result — default returns "" for non-expression nodes
	virtual string generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest = "")
	{
		return "";
	}
	void setLine(int l) { line = l; }
	int getLine() { return line; }
protected:
	void printDepth(int depth);

private:
	int line;
};

//this is the node for the program rule
class ASTProgram : public ASTNode
{
public:
	void addProgramElement(ASTNode * theFunction);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	vector<ASTNode*> nodes;

};

//this is the node for the function rule
class ASTFunction : public ASTNode
{
public:
	ASTFunction();
	void setParam(ASTParam* params_in);
	void setName(string name);
	void setReturnType(string type);
	void print(int depth);
	void setStatements(ASTNode* stmts);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);

	ASTParam* getParams();
	string getName();
	string getReturnType();
private:
	ASTParam* params;
	string name;
	string returnType;
	ASTNode* stmts;

};

//this is the node for the param rule. Note that the ith type corresponds to the ith name
class ASTParam : public ASTNode
{
public:
	void addParam(string type, string name);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	vector<string> getNames();
	vector<string> getTypes();
private:
	vector<string> types;
	vector<string> names;

};

class ASTTopLevel : public ASTNode
{
public:
	void setTopElement(ASTNode* node);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);

	ASTNode * getNode();
private:
	ASTNode * topElement;
};

class ASTStatements : public ASTNode
{
public:
	void addStatement(ASTStatement* stmt);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	vector<ASTStatement *> nodes;
};

class ASTStatement : public ASTNode
{
public:
	void setStatement(ASTNode* stmt,bool isBlock);
	bool getIsBlock();
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * statement;
	bool isBlock;
};


class ASTArgs : public ASTNode
{
public:
	void addArg(ASTNode* arg);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	vector<ASTNode *> getArgs();

private:
	vector<ASTNode *> args;
};

class ASTReturn : public ASTNode
{
public:
	ASTReturn();
	void setRHS(ASTNode* stmt);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * rhs;
};

class ASTIf : public ASTNode
{
public:
	void setGuard(ASTNode* guard);
	void setStatement(ASTStatement* statement);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * guard;
	ASTStatement * statement;
};

class ASTAssign : public ASTNode
{
public:
	void setLeft(string s1, string s2);
	void setRight(ASTNode* right);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	string lhs1, lhs2;
	ASTNode * right;
};

class ASTWhile : public ASTNode
{
public:
	void setGuard(ASTNode* guard);
	void setStatement(ASTStatement* statement);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * guard;
	ASTStatement * statement;
};

class ASTFunctionCallStmt : public ASTNode
{
public:
	void setCall(ASTNode* param);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * call;
};

class ASTFunctionCall : public ASTNode
{
public:
	void setName(string name);
	void setArg(ASTNode* param);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	// helper used by code generator to emit args into IR without the callfunction wrapper
	void generateArgs(ofstream& out, int& tempCount, int& labelCount);
	ASTNode * getArgs();
private:
	string name;
	ASTNode * args;
};

class ASTBlockStatement: public ASTNode
{
public:
	void setStatement(ASTNode* stmts);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * statement;
};

class ASTDeclaration: public ASTNode
{
public:
	void setStatement(ASTNode* stmt);
	void setType(string type);
	void setName(string name);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * statement;
	string type;
	string name;
};

class ASTBoolExprA : public ASTNode
{
public:
	void addItem(ASTNode* arg);
	void addOp(string op);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	// returns the name of the register holding the result
	string generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest = "");
private:
	vector<ASTNode *> stmts;
	vector<string> operators;
};

class ASTBoolExprB : public ASTNode
{
public:
	void addItem(ASTNode* arg);
	void addOp(string op);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	string generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest = "");
private:
	vector<ASTNode *> stmts;
	vector<string> operators;
};

class ASTTerm : public ASTNode
{
public:
	void addItem(ASTNode* arg);
	void addOp(string op);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	string generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest = "");
private:
	vector<ASTNode *> stmts;
	vector<string> operators;
};

class ASTExpr : public ASTNode
{
public:
	void addItem(ASTNode* arg);
	void addOp(string op);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	string generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest = "");
private:
	vector<ASTNode *> stmts;
	vector<string> operators;
};

class ASTFactor : public ASTNode
{
public:
	void setThing(ASTNode* arg, bool isElement);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	string generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest = "");
private:
	ASTNode * theThing;
	bool isElement;
};

class ASTElement : public ASTNode
{
public:
	void addItem(string thing, string thing2, TokenType type);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
	// returns the token string for this element (varname, literal, or var.component)
	string generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest = "");

private:
	string thing;
	string thing2;
	TokenType elementType;
};

class ASTFor : public ASTNode
{
public:
	void setGuard(ASTNode* guard);
	void setDeclaration(ASTDeclaration* declaration);
	void setAssignment(ASTAssign* assignment);
	void setStatement(ASTStatement* statement);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);
private:
	ASTNode * guard;
	ASTStatement * statement;
	ASTDeclaration * declaration;
	ASTAssign * assignment;
};

class ASTDefine : public ASTNode
{
public:
	void setName(string thing);
	void setValue(string value);
	void setType(TokenType type);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);

private:
	string thing;
	string value;
	TokenType type;
};

class ASTTexture : public ASTNode
{
public:
	void setName(string name);
	void setFName(string fname);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	void generateCode(ofstream& out, int& tempCount, int& labelCount);

private:
	string name;
	string fname;
};