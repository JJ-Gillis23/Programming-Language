#pragma once

#include <iostream>
#include <string>
#include "Scanner.h"
#include "AST.h"
using namespace std;


class Parser
{
public:
	Parser(string fname);
	ASTProgram* parse();

	void printError(string code, string message, int line);

	ASTProgram* rdpProgram();
	ASTTopLevel* rdpTopLevel();
	ASTFunction* rdpFunction();
	ASTParam* rdpParam();
	ASTStatements* rdpStatements();
	ASTStatement* rdpStatement();
	ASTNode* rdpElement();
	ASTReturn* rdpReturn();
	ASTIf* rdpIf();
	ASTWhile* rdpWhile();
	ASTFor* rdpFor();
	ASTDeclaration* rdpDeclaration();
	ASTAssign* rdpAssign();
	ASTFunctionCallStmt* rdpFunctionCallStmt();
	ASTBlockStatement* rdpBlockStatement();
	ASTBoolExprA* rdpBoolExprA();
	ASTBoolExprB* rdpBoolExprB();
	ASTTerm* rdpTerm();
	ASTExpr* rdpExpr();
	ASTFactor* rdpFactor();
	ASTFunctionCall* rdpFunctionCall();
	ASTArgs* rdpArgs();
	ASTDefine* rdpDefine();
	ASTTexture* rdpTexture();
	bool getErrorDetected();
private:
	bool errorDetected;
	Scanner* scan;
	ASTProgram* program;
};
