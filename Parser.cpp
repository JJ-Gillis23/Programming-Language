#include "Parser.h"
#include "AST.h"


void Parser::printError(string code, string message, int line)
{
   if(!errorDetected)
      cout << "Error: "<< code << " on line: " << line << " " << message << ". Recieved " << scan->toString(scan->currentTokenType()) << " \"" << scan->currentTokenString() << "\"." << endl;
   errorDetected = true;
}

Parser::Parser(string fname)
{
   scan = new Scanner(fname);
   errorDetected = false;
   program = 0;
}

bool Parser::getErrorDetected()
{
   return errorDetected;
}

ASTProgram* Parser::parse()
{
   program = rdpProgram();
   return program;
}

// <program> := {<topLevel>}
ASTProgram* Parser::rdpProgram()
{
   ASTProgram* theProg = new ASTProgram();

   while (scan->currentTokenType() == STRING || scan->currentTokenType() == DEFINE || scan->currentTokenType() == TEXTURE)
   {
      theProg->addProgramElement(rdpTopLevel());
   }

   if (scan->currentTokenType() != NONE && scan->currentTokenType() != ENDOFFILE)
   {
      printError("ASTProgram01","Expected String or EOF recieved "+scan->toString(scan->currentTokenType()),scan->getLine());
   }
   return theProg;
}

ASTTopLevel* Parser::rdpTopLevel()
{
   ASTTopLevel* top = new ASTTopLevel();
   if(scan->currentTokenType() == DEFINE)
   {
      //top->setTopElement(rdpDefine());
   }
   else if(scan->currentTokenType() == TEXTURE)
   {
      //top->setTopElement(rdpTexture());
   }
   else if(scan->currentTokenType() == STRING)
   {
      top->setTopElement(rdpFunction());
   }
   else
   {
      printError("ASTTopLevel01", "Expected DEFINE, STRING, or TEXTURE", scan->getLine());
      scan->advance();
   }
   return top;
}

ASTFunction* Parser::rdpFunction()
{
   ASTFunction* theFunction = new ASTFunction();

   if (scan->currentTokenType() == STRING)
   {
      theFunction->setReturnType(scan->currentTokenString());
      scan->advance();
   }
   else
   {
      printError("ASTFunction00", "Expected String for function return type", scan->getLine());
      scan->advance();
   }

   string name;
   if (scan->currentTokenType() == STRING)
   {
      name = scan->currentTokenString();
      theFunction->setName(name);
      scan->advance();
   }
   else
   {
      printError("ASTFunction01", "Expected String for function name", scan->getLine());
      scan->advance();
   }

   if (scan->currentTokenType() == LPAREN)
   {
      scan->advance();
   }
   else
   {
      printError("ASTFunction02", "Expected LPAREN for function name", scan->getLine());
      scan->advance();
   }

   theFunction->setParam(rdpParam());

   if (scan->currentTokenType() == RPAREN)
   {
      scan->advance();
   }
   else
   {
      printError("ASTFunction03", "Expected RPAREN for function name", scan->getLine());
      scan->advance();
   }

   if (scan->currentTokenType() == LBRACE)
   {
      scan->advance();
   }
   else
   {
      printError("ASTFunction04", "Expected LBRACE for function name", scan->getLine());
      scan->advance();
   }

   theFunction->setStatements(rdpStatements());

   if (scan->currentTokenType() == RBRACE)
   {
      scan->advance();
   }
   else
   {
      printError("ASTFunction05", "Expected RBRACE for function name", scan->getLine());
      scan->advance();
   }

   return theFunction;
}

ASTParam* Parser::rdpParam()
{
   ASTParam* params = new ASTParam();

   while (scan->currentTokenType() == STRING)
   {
      string type = scan->currentTokenString();
      scan->advance();
      string name;
      if (scan->currentTokenType() == STRING)
      {
         name = scan->currentTokenString();
         scan->advance();
      }
      else
      {
         printError("ASTParams01", "Expected String for for param name", scan->getLine());
         scan->advance();
      }

      params->addParam(type, name);

      if (scan->currentTokenType() == COMMA)
      {
         scan->advance();
      }
      else if (scan->currentTokenType() == RPAREN)
      {
         //handled by astfunction
      }
      else
      {
         printError("ASTParams02", "Expected COMMA or RPAREN", scan->getLine());
         scan->advance();
      }
   }

   return params;
}

ASTStatements* Parser::rdpStatements()
{
   ASTStatements* node = new ASTStatements();

   while(scan->currentTokenType() == STRING || scan->currentTokenType() == LBRACE)
   {
      node->addStatement(rdpStatement());
   }

   return node;
}

ASTStatement* Parser::rdpStatement()
{
   ASTStatement* node = new ASTStatement();

   if(scan->currentTokenString() == "return")
   {
      node->setStatement(rdpReturn(), false);
   }
   else if(scan->currentTokenString() == "if")
   {
      node->setStatement(rdpIf(), false);
   }
   else if(scan->currentTokenString() == "while")
   {
      node->setStatement(rdpWhile(), false);
   }
   else if(scan->currentTokenString() == "for")
   {
      node->setStatement(rdpFor(), false);
   }
   else if(scan->currentTokenString() == "{")
   {
      node->setStatement(rdpBlockStatement(), true);
   }
   else if(scan->currentTokenType() == STRING && scan->nextTokenType() == STRING) //declaration
   {
      node->setStatement(rdpDeclaration(), false);
   }
   else if((scan->currentTokenType() == STRING && scan->nextTokenType() == EQUALASSIGN) || (scan->currentTokenType() == STRING && scan->nextTokenType() == DOT))
   {
      node->setStatement(rdpAssign(), false);
   }
   else if(scan->currentTokenType() == STRING && scan->nextTokenType() == LPAREN) //functionCall
   {
      node->setStatement(rdpFunctionCallStmt(), false);
   }
   else
   {
      printError("rdpstatement01", "Expected return, if, while, {, or declaration, functioncall, or assign", scan->getLine());
      scan->advance();
   }
   return node;
}

ASTReturn* Parser::rdpReturn()
{
   ASTReturn* node = new ASTReturn();

   if(scan->currentTokenString() == "return")
   {
      scan->advance();
   }
   else
   {
      printError("rdpreturn01", "Expected return", scan->getLine());
      scan->advance();
   }

   if(scan->currentTokenString() != ";")
   {
      node->setRHS(rdpElement());
   }

   if(scan->currentTokenString() == ";")
   {
      scan->advance();
   }
   else
   {
      printError("rdpreturn02", "Expected ;", scan->getLine());
      scan->advance();
   }

   return node;
}

ASTNode* Parser::rdpElement()
{
   ASTElement* node = new ASTElement();
   if(scan->currentTokenType() == STRING && scan->nextTokenType() == DOT)
   {
      string s1 = scan->currentTokenString();
      scan->advance();
      scan->advance();
      if(scan->currentTokenType() == STRING)
      {
         string s2 = scan->currentTokenString();
         scan->advance();
         node->addItem(s1, s2, STRING);
      }
      else
      {
         printError("rdpelement02", "element", scan->getLine());
         scan->advance();
      }
   }
   else if(scan->currentTokenType() == STRING && scan->nextTokenType() == LPAREN)
   {
      return rdpFunctionCall();
   }
   else if(scan->currentTokenType() == FLOAT)
   {
      node->addItem(scan->currentTokenString(), "-1", FLOAT);
      scan->advance();
   }
   else if(scan->currentTokenType() == INT)
   {
      node->addItem(scan->currentTokenString(), "-1", INT);
      scan->advance();
   }
   else if(scan->currentTokenType() == QUOTED)
   {
      scan->advance();
      if(scan->currentTokenType() == STRING && scan->nextTokenType() == QUOTED)
      {
         node->addItem(scan->currentTokenString(), "-2", STRING);
         scan->advance();
         scan->advance();
      }
      else
      {
         printError("rdpelement03", "expecting lit string", scan->getLine());
         scan->advance();
      }
   }
   else if(scan->currentTokenType() == STRING)
   {
      node->addItem(scan->currentTokenString(), "-1", STRING);
      scan->advance();
   }
   else
   {
      printError("rdpelement01", "element", scan->getLine());
      scan->advance();
   }
   return node;
}

ASTBoolExprA* Parser::rdpBoolExprA()
{
   ASTBoolExprA* node = new ASTBoolExprA();
   node->addItem(rdpBoolExprB());  // was addBoolExprB
   

   if(scan->currentTokenType() == OR)
   {
      node->addOp("||");           // was addOperator, now addOp
      scan->advance();
      node->addItem(rdpBoolExprB());
   }
   else if(scan->currentTokenType() == AND)
   {
      node->addOp("&&");           // was addOperator, now addOp
      scan->advance();
      node->addItem(rdpBoolExprB());
   }
   return node;
}

ASTBoolExprB* Parser::rdpBoolExprB()
{
   ASTBoolExprB* node = new ASTBoolExprB();
   node->addItem(rdpTerm());
   if(scan->currentTokenType() == NE)
   {
      node->addOp("!=");  
      scan->advance();
      node->addItem(rdpTerm());
   }
   else if(scan->currentTokenType() == EE)
   {
      node->addOp("==");
      scan->advance();
      node->addItem(rdpTerm());
   }
   else if(scan->currentTokenType() == GRE)
   {
      node->addOp(">=");
      scan->advance();
      node->addItem(rdpTerm());
   }
   else if(scan->currentTokenType() == GR)
   {
      node->addOp(">");
      scan->advance();
      node->addItem(rdpTerm());
   }
   else if(scan->currentTokenType() == LT)
   {
      node->addOp("<");
      scan->advance();
      node->addItem(rdpTerm());
   }
   else if(scan->currentTokenType() == LTE)
   {
      node->addOp("<=");
      scan->advance();
      node->addItem(rdpTerm());
   }
   return node;
}

ASTTerm* Parser::rdpTerm()
{
   ASTTerm* node = new ASTTerm();
   node->addItem(rdpExpr());
   while(scan->currentTokenType() == PLUS || scan->currentTokenType() == MINUS)
   {
      node->addOp(scan->currentTokenString());   // was addOperator, now addOp
      scan->advance();
      node->addItem(rdpExpr());
   }
   return node;
}

ASTExpr* Parser::rdpExpr()
{
   ASTExpr* node = new ASTExpr();
   node->addItem(rdpFactor());
   while(scan->currentTokenType() == MULTIPLY || scan->currentTokenType() == DIVIDE || scan->currentTokenType() == MOD)
   {
      node->addOp(scan->currentTokenString());   // was addOperator, now addOp
      scan->advance();
      node->addItem(rdpFactor());
   }
   return node;
}
ASTFor* Parser::rdpFor()
{
   ASTFor* node = new ASTFor();

   if(scan->currentTokenString() == "for")
      scan->advance();
   else
   {
      printError("rdpfor01", "Expected for", scan->getLine());
      scan->advance();
   }

   if(scan->currentTokenType() == LPAREN)
      scan->advance();
   else
   {
      printError("rdpfor02", "Expected LPAREN", scan->getLine());
      scan->advance();
   }
   //Set Declaration
   if(scan->currentTokenType() == STRING && scan->nextTokenType() == STRING)
   {
      node->setDeclaration(rdpDeclaration());
   }
   else if(scan->currentTokenType() == SEMI)
   {
      scan->advance(); // empty init
   }
   else
   {
      printError("rdpfor03", "Expected ; after declaration", scan->getLine());
      scan->advance();
   }

   // guard
   node->setGuard(rdpBoolExprA());

   if(scan->currentTokenType() == SEMI)
      scan->advance();
   else
   {
      printError("rdpfor04", "Expected ; after for guard", scan->getLine());
      scan->advance();
   }

   // increment — only an assign or empty
   if((scan->currentTokenType() == STRING && scan->nextTokenType() == EQUALASSIGN) ||
      (scan->currentTokenType() == STRING && scan->nextTokenType() == DOT))
   {
      node->setAssignment(rdpAssign());
   }

   if(scan->currentTokenType() == RPAREN)
      scan->advance();
   else
   {
      printError("rdpfor05", "Expected RPAREN after for header", scan->getLine());
      scan->advance();
   }

   node->setStatement(rdpStatement());
   return node;
}

ASTFactor* Parser::rdpFactor()
{
   ASTFactor* node = new ASTFactor();
   if(scan->currentTokenType() == LPAREN)
   {
      scan->advance();
      node->setThing(rdpBoolExprA(), false);     // was addItemBoolExprA, now setThing(..., false)
      if(scan->currentTokenType() == RPAREN)
      {
         scan->advance();
      }
      else
      {
         printError("rdpfactor02", "Expected RPAREN after BoolExprA", scan->getLine());
         scan->advance();
      }
   }
   else
   {
      node->setThing(rdpElement(), true);        // was addItemElement, now setThing(..., true)
   }
   return node;
}

ASTFunctionCallStmt* Parser::rdpFunctionCallStmt()
{
   ASTFunctionCallStmt* node = new ASTFunctionCallStmt();
   node->setCall(rdpFunctionCall());             // was addItem, now setCall
   if(scan->currentTokenType() == SEMI)
      scan->advance();
   else
   {
      printError("rdpfunctioncallStmt01", "Expected SEMI after FunctionCall", scan->getLine());
      scan->advance();
   }
   return node;
}

ASTFunctionCall* Parser::rdpFunctionCall()
{
   ASTFunctionCall* node = new ASTFunctionCall();
   node->setName(scan->currentTokenString());
   scan->advance();
   if(scan->currentTokenType() != LPAREN)
   {
      printError("rdpFunctionCall02", "Expected LPAREN after function name", scan->getLine());
      scan->advance();
   }
   scan->advance();
   node->setArg(rdpArgs());                      // was addItem, now setArg
   if(scan->currentTokenType() != RPAREN)
   {
      printError("rdpFunctionCall03", "Expected RPAREN after args", scan->getLine());
      scan->advance();
   }
   scan->advance();
   return node;
}

ASTArgs* Parser::rdpArgs()
{
   ASTArgs* node = new ASTArgs();
   if(scan->currentTokenType() == RPAREN)
      return node;
   node->addArg(rdpBoolExprA());                 // was addItem, now addArg
   while(scan->currentTokenType() == COMMA)
   {
      scan->advance();
      node->addArg(rdpBoolExprA());              // was addItem, now addArg
   }
   return node;
}

ASTAssign* Parser::rdpAssign()
{
   ASTAssign* node = new ASTAssign();
   if(scan->nextTokenType() == DOT)
   {
      string thing1 = scan->currentTokenString();
      scan->advance();                           // eat var name
      scan->advance();                           // eat DOT
      string thing2 = scan->currentTokenString();
      scan->advance();                           // eat component name
      scan->advance();                           // eat EQUALASSIGN
      node->setLeft(thing1, thing2);             // was addItem, now setLeft/setRight
      node->setRight(rdpBoolExprA());
   }
   else
   {
      string thing1 = scan->currentTokenString();
      scan->advance();                           // eat var name
      scan->advance();                           // eat EQUALASSIGN
      node->setLeft(thing1, "-1");                 // was addItem, now setLeft/setRight
      node->setRight(rdpBoolExprA());
   }
   if(scan->currentTokenType() == SEMI)
      scan->advance();
   else
   {
      printError("rdpAssign01", "Expected SEMI after assign", scan->getLine());
      scan->advance();
   }
   return node;
}

ASTBlockStatement* Parser::rdpBlockStatement()
{
   ASTBlockStatement* node = new ASTBlockStatement();
   scan->advance();                              // eat LBRACE
   node->setStatement(rdpStatements());          // was addItem, now setStatement
   if(scan->currentTokenType() == RBRACE)
   {
      scan->advance();                           // eat RBRACE
   }
   else
   {
      printError("rdpBlockStatement01", "Expected RBRACE after statements", scan->getLine());
      scan->advance();
   }
   return node;
}

ASTDeclaration* Parser::rdpDeclaration()
{
   ASTDeclaration* node = new ASTDeclaration();
   string thing1 = scan->currentTokenString();
   scan->advance();
   string thing2 = scan->currentTokenString();
   scan->advance();
   node->setType(thing1);                        // was addItem, now setType/setName/setStatement
   node->setName(thing2);;
   if(scan->currentTokenType() == SEMI)
   {
      scan->advance();
      return node;                               // empty declaration, no initializer
   }
   else if(scan->currentTokenType() == EQUALASSIGN)
   {
      scan->advance();
      node->setStatement(rdpBoolExprA());
      if(scan->currentTokenType() == SEMI)
      {
         scan->advance();
      }
      else
      {
         printError("rdpDeclaration02", "Expected SEMI after declaration", scan->getLine());
         scan->advance();
      }
   }
   else
   {
      printError("rdpDeclaration01", "Expected SEMI or EQUALASSIGN after var name", scan->getLine());
      scan->advance();
   }
   return node;
}


ASTIf* Parser::rdpIf()
{
   ASTIf* node = new ASTIf();

   if(scan->currentTokenString() == "if")
      scan->advance();
   else
   {
      printError("rdpIf01", "Expected if", scan->getLine());
      scan->advance();
   }

   if(scan->currentTokenType() == LPAREN)
      scan->advance();
   else
   {
      printError("rdpIf02", "Expected LPAREN after if", scan->getLine());
      scan->advance();
   }

   node->setGuard(rdpBoolExprA());

   if(scan->currentTokenType() == RPAREN)
      scan->advance();
   else
   {
      printError("rdpIf03", "Expected RPAREN after condition", scan->getLine());
      scan->advance();
   }

   node->setStatement(rdpStatement());

   return node;
}

ASTWhile* Parser::rdpWhile()
{
   ASTWhile* node = new ASTWhile();
   scan->advance(); // eat while
   if(scan->currentTokenType() == LPAREN)
      scan->advance();
   else
   {
      printError("rdpWhile02", "Expected LPAREN after while", scan->getLine());
      scan->advance();
   }
   node->setGuard(rdpBoolExprA());

   if(scan->currentTokenType() == RPAREN)
      scan->advance();
   else
   {
      printError("rdpWhile03", "Expected RPAREN after condition", scan->getLine());
      scan->advance();
   }


   node->setStatement(rdpStatement());

   return node;
}
