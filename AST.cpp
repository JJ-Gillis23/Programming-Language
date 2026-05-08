#include "AST.h"

#include <iostream>
#include <string>
using namespace std;

//this part is the functions for creating the tree

void ASTNode::printDepth(int depth)
{
	for(int i=0;i<depth*2;i++)
	{
		cout <<" ";
	}
}

void ASTProgram::addProgramElement(ASTNode* theThing)
{
	nodes.push_back(theThing);
}

ASTFunction::ASTFunction()
{
	stmts=0;
}

void ASTFunction::setName(string name_in)
{
	name = name_in;
}

void ASTFunction::setParam(ASTParam * theParam)
{
	params = theParam;
}

void ASTFunction::setStatements(ASTNode* stmts)
{
	this->stmts = stmts;
}

void ASTFunction::setReturnType(string str)
{
	returnType = str;
}

void ASTParam::addParam(string type, string name)
{
	types.push_back(type);
	names.push_back(name);
}



void ASTTopLevel::setTopElement(ASTNode* node)
{
	topElement = node;
}

void ASTStatements::addStatement(ASTStatement* stmt)
{
	nodes.push_back(stmt);
}

bool ASTStatement::getIsBlock()
{
	return isBlock;
}
void ASTStatement::setStatement(ASTNode* stmt, bool isBlock)
{
	this->statement = stmt;
	this->isBlock = isBlock;
}

void ASTArgs::addArg(ASTNode* arg)
{
	args.push_back(arg);
}


ASTNode * ASTFunctionCall::getArgs()
{
	return args;
}

vector<ASTNode *> ASTArgs::getArgs()
{
	return args;
}


void ASTIf::setGuard(ASTNode* guard)
{
	this->guard = guard;
}
void ASTIf::setStatement(ASTStatement* statement)
{
	this->statement = statement;
}

void ASTAssign::setLeft(string s1, string s2)
{
	this->lhs1 = s1;
	this->lhs2 = s2;
}
void ASTAssign::setRight(ASTNode* right)
{
	this->right = right;
}

void ASTWhile::setGuard(ASTNode* guard)
{
	this->guard = guard;
}
void ASTWhile::setStatement(ASTStatement* statement)
{
	this->statement = statement;
}

void ASTFunctionCallStmt::setCall(ASTNode* param)
{
	this->call = param;
}

void ASTFunctionCall::setName(string name)
{
	this->name = name;
}
void ASTFunctionCall::setArg(ASTNode* param)
{
	args = param;
}

void ASTBlockStatement::setStatement(ASTNode* stmts)
{
	this->statement = stmts;
}

void ASTDeclaration::setType(string type)
{
	this->type = type;
}
void ASTDeclaration::setName(string name)
{
	this->name = name;
}
void ASTDeclaration::setStatement(ASTNode* stmt)
{
	this->statement = stmt;
}



void ASTBoolExprA::addItem(ASTNode* arg)
{
	stmts.push_back(arg);
}
void ASTBoolExprA::addOp(string op)
{
	operators.push_back(op);
}



void ASTBoolExprB::addItem(ASTNode* arg)
{
	stmts.push_back(arg);
}
void ASTBoolExprB::addOp(string op)
{
	operators.push_back(op);
}


void ASTTerm::addItem(ASTNode* arg)
{
	stmts.push_back(arg);
}
void ASTTerm::addOp(string op)
{
	operators.push_back(op);
}
void ASTFor::setGuard(ASTNode* guard)
{
	this->guard = guard;
}
void ASTFor::setStatement(ASTStatement* statement)
{
	this->statement = statement;
}
void ASTFor::setDeclaration(ASTDeclaration* declaration)
{
	this->declaration = declaration;
}
void ASTFor::setAssignment(ASTAssign* assignment)
{
	this->assignment = assignment;
}


void ASTExpr::addItem(ASTNode* arg)
{
	stmts.push_back(arg);
}
void ASTExpr::addOp(string op)
{
	operators.push_back(op);
}

void ASTFactor::setThing(ASTNode* arg, bool isElement)
{
	theThing = arg;
	this->isElement = isElement;
}



void ASTElement::addItem(string thing, string thing2, TokenType type)
{
	this->thing = thing;
	this->elementType = type;
	this->thing2 = thing2;
}



void ASTDefine::setName(string thing)
{
	this->thing = thing;
}
void ASTDefine::setValue(string value)
{
	this->value = value;
}
void ASTDefine::setType(TokenType value)
{
	this->type = value;
}

void ASTTexture::setName(string name)
{
	this->name = name;
}
void ASTTexture::setFName(string fname)
{
	this->fname = fname;
}



ASTReturn::ASTReturn()
{
	rhs = 0;
}

void ASTReturn::setRHS(ASTNode * node)
{
	rhs = node;
}



//this part is the functions for printing the tree

void ASTProgram::print(int depth)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->print(depth);
	}
}

void ASTTopLevel::print(int depth)
{
	topElement->print(depth);
}

ASTNode * ASTTopLevel::getNode()
{
	return topElement;
}

void ASTFunction::print(int depth)
{
	cout << returnType<<" "<<name << "(";
	params->print(depth);
	cout << ")\n";
	cout << "{\n";
	if(stmts != 0)
	{
		stmts->print(depth + 1);
	}
	cout << "}\n";
}

ASTParam* ASTFunction::getParams()
{
	return params;
}

string ASTFunction::getName()
{
	return name;
}

string ASTFunction::getReturnType()
{
	return returnType;
}

vector<string> ASTParam::getTypes()
{
	return types;
}

vector<string> ASTParam::getNames()
{
	return names;
}

void ASTParam::print(int depth)
{
	for (int i = 0; i < names.size(); i++)
	{
		cout << types[i] << " " << names[i];
		if (i != names.size() - 1)
		{
			cout << ", ";
		}
	}
}

void ASTStatements::print(int depth)
{
	for(int i=0;i<nodes.size();i++)
	{
		nodes[i]->print(depth);
	}
}
void ASTStatement::print(int depth)
{
	statement->print(depth);
}
void ASTFor::print(int depth)
{
	printDepth(depth);
	cout << "for(";
	declaration->print(0);
	guard->print(0);
	cout <<"; ";
	assignment->print(0);
	cout <<")\n";
	statement->print(statement->getIsBlock() ? depth : depth+1);	
}

void ASTArgs::print(int depth)
{
	for(int i=0;i<args.size();i++)
	{
		args[i]->print(depth);
		if(i+1 != args.size())
			cout << ", ";
	}
}
void ASTIf::print(int depth)
{
	printDepth(depth);
	cout << "if(";
	guard->print(0);
	cout <<")\n";
	statement->print(statement->getIsBlock() ? depth : depth+1);	
}
void ASTAssign::print(int depth)
{
	printDepth(depth);
	cout << lhs1;
	if(lhs2 != "-1")
	{
		cout <<"."<<lhs2;
	}
	cout <<" = ";
	right->print(depth);
	cout <<";\n";
}
void ASTWhile::print(int depth)
{
	printDepth(depth);
	cout << "while(";
	guard->print(depth);
	cout <<")\n";
	statement->print(statement->getIsBlock() ? depth : depth+1);

}
void ASTFunctionCall::print(int depth)
{
	cout << name <<"(";

	args->print(depth);
	
	cout << ")";
}
void ASTFunctionCallStmt::print(int depth)
{
	printDepth(depth);
	call->print(depth);
	cout << ";\n";
}
void ASTBlockStatement::print(int depth)
{
	printDepth(depth);cout <<"{\n";
	
	statement->print(depth+1);
	
	printDepth(depth);cout <<"}\n";
}
void ASTDeclaration::print(int depth)
{
	printDepth(depth);
	cout << type<<" "<<name;
	if(statement != 0)
	{
		cout << " = ";
		statement->print(depth);
		
	}

	cout <<";\n";
	
}
void ASTBoolExprA::print(int depth)
{
	stmts[0]->print(depth);
	if(stmts.size() > 0)
	{
		for(int i=0;i<stmts.size()-1;i++)
		{
			cout <<" "<< operators[i] <<" ";
			stmts[i+1]->print(depth); 
		}
	}	
}
void ASTBoolExprB::print(int depth)
{
	stmts[0]->print(depth);
	if(stmts.size() > 0)
	{
		for(int i=0;i<stmts.size()-1;i++)
		{
			cout <<" "<< operators[i] <<" ";
			stmts[i+1]->print(depth); 
		}
	}
}
void ASTTerm::print(int depth)
{
	stmts[0]->print(depth);
	if(stmts.size() > 0)
	{
		for(int i=0;i<stmts.size()-1;i++)
		{
			cout <<" "<< operators[i] <<" ";
			stmts[i+1]->print(depth); 
		}
	}	
}
void ASTExpr::print(int depth)
{
	stmts[0]->print(depth);
	if(stmts.size() > 0)
	{
		for(int i=0;i<stmts.size()-1;i++)
		{
			cout <<" "<< operators[i] <<" ";
			stmts[i+1]->print(depth); 
		}
	}
}
void ASTFactor::print(int depth)
{
	if(isElement)
	{
		theThing->print(depth);
	}
	else
	{
		cout <<"(";
		theThing->print(depth);
		cout <<")";
	}
}
void ASTElement::print(int depth)
{
	if(thing2 != "-2")
	{
		cout << thing;
		if(thing2 != "-1" && thing2 != "-2")
		{
			cout << "."<<thing2;
		}
	}
	else
	{
		cout << "\""<<thing<<"\"";
	}
}
void ASTDefine::print(int depth)
{
	cout << "#def ";
	cout << thing<<" "<<value;
	cout << "\n";	
}
void ASTTexture::print(int depth)
{
	cout << "#text ";
	cout << name<<" \""<<fname;
	cout << "\"\n";
}

void ASTReturn::print(int depth)
{
	printDepth(depth);
	if(rhs == 0)
	{
		cout << "return;\n";
	}
	else
	{
		cout << "return ";
		rhs->print(0);
		cout <<";\n";
	}
}



void typeError(string code, int line, string message, bool& hasError)
{
	if (!hasError)
	{
		cout << code << " around line: " << line << " ;;; " << message << "\n";
		hasError = true;
	}
}

string typeToString(Type t)
{
	if (t == NULL_T)
		return "Null_Type";
	if (t == ERROR_T)
		return "Error_Type";
	if (t == FLOAT_T)
		return "Float_Type";
	if (t == INT_T)
		return "Int_Type";
	if (t == BOOL_T)
		return "Bool_Type";
	if (t == VOID_T)
		return "Void_Type";
	if (t == VECTOR3_T)
		return "Vector3_Type";
	if (t == STRING_T)
		return "String_Type";
	if (t == TEXTURE_T)
		return "Texture_type";
	return "Unknown type";
}

//checks if it is a keyword. isType is probably not the best name.
bool isType(string test)
{
	if(test == "int" || test == "float" || test == "vector3" || test == "if" || test == "while" || test == "return" || test == "bool" || test == "true" || test == "false")
		return true;
	return false;
}

//helper function to print the env.
void printEnv(TypeMap* map, FunctionParamMap* fmap)
{
	cout << "Variables:\n";
	for (auto it = map->begin(); it != map->end(); it++)
	{
		cout << it->first <<" "<<typeToString(it->second)<<endl;
	}
	cout << "functions:\n";
	for (auto it = fmap->begin(); it != fmap->end(); it++)
	{
		string temp = "";
		for(int i=0;i<it->second.size();i++)
		{
			temp+=typeToString(it->second[i])+" ";
		}
		
		cout << it->first <<" "<<temp<<endl;
	}
}


Type ASTProgram::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	fmap = new FunctionParamMap();

	//predefined functions
	vector<Type> absf;
	absf.push_back(FLOAT_T);
	fmap->operator[]("abs$param") = absf;
	fmap->operator[]("abs$return") = absf;

	vector<Type> sqrt;
	sqrt.push_back(FLOAT_T);
	fmap->operator[]("sqrt$param") = sqrt;
	fmap->operator[]("sqrt$return") = sqrt;

	vector<Type> pow;
	pow.push_back(FLOAT_T);
	pow.push_back(FLOAT_T);	
	vector<Type> powr;
	powr.push_back(FLOAT_T);
	fmap->operator[]("pow$param") = pow;
	fmap->operator[]("pow$return") = powr;
	
	vector<Type> print;
	print.push_back(STRING_T);
	print.push_back(FLOAT_T);	
	vector<Type> printr;
	printr.push_back(VOID_T);
	fmap->operator[]("print$param") = print;
	fmap->operator[]("print$return") = printr;
	
	vector<Type> vector3;
	vector3.push_back(FLOAT_T);
	vector3.push_back(FLOAT_T);
	vector3.push_back(FLOAT_T);	
	vector<Type> vector3r;
	vector3r.push_back(VECTOR3_T);
	fmap->operator[]("vector3$param") = vector3;
	fmap->operator[]("vector3$return") = vector3r;
	
	vector<Type> getTextColor;
	getTextColor.push_back(STRING_T);
	getTextColor.push_back(FLOAT_T);
	getTextColor.push_back(FLOAT_T);	
	vector<Type> getTextColorr;
	getTextColorr.push_back(VECTOR3_T);
	fmap->operator[]("getTextureColor$param") = getTextColor;
	fmap->operator[]("getTextureColor$return") = getTextColorr;
	
	
	

	TypeMap * m = new TypeMap();
	
	//predefined constant vars
	m->operator[]("MOUSE_Y") = FLOAT_T;
	m->operator[]("MOUSE_X") = FLOAT_T;
	m->operator[]("CENTER_X") = FLOAT_T;
	m->operator[]("CENTER_Y") = FLOAT_T;
	m->operator[]("MIN_Y") = FLOAT_T;
	m->operator[]("MIN_X") = FLOAT_T;
	m->operator[]("MAX_X") = FLOAT_T;
	m->operator[]("MAX_X") = FLOAT_T;
	m->operator[]("true") = BOOL_T;
	m->operator[]("false") = BOOL_T;
	
	//call typecheck on the textures and defs
	for (int i = 0; i < nodes.size(); i++)
	{
		ASTTopLevel* tl = (ASTTopLevel*)nodes[i];
		
		if(dynamic_cast<ASTTexture*>(tl->getNode()))
		{
			tl->getNode()->typeCheck(m,fmap,hadError);
		}
		if(dynamic_cast<ASTDefine*>(tl->getNode()))
		{
			tl->getNode()->typeCheck(m,fmap,hadError);
		}
	}
	

	
	for (int i = 0; i < nodes.size(); i++)
	{
		ASTTopLevel* tl = (ASTTopLevel*)nodes[i];
		
		if(dynamic_cast<ASTFunction*>(tl->getNode()))
		{
			ASTFunction* function = (ASTFunction*)(tl->getNode());
			

			ASTParam* params = function->getParams();

			vector<Type> functionParamTypes;

			//check param types and then add the types into the map.
			for (int j = 0; j < params->getNames().size(); j++)
			{
				vector<string> names = params->getNames();
				vector<string> types = params->getTypes();

				if (types[j] == "float")
				{
					string name = names[j];
					if (isType(name))
					{
						bool hadErrorB = false;
						typeError("T_function06", function->getLine(), "\"" + name + "\" keyword cannot be used as a function parameter name", hadErrorB);
						hadError = hadError || hadErrorB;
					}
					//please note the weird syntax here, calling the [] operator as if it is the function.
					else if (m->operator[](names[j]) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
					{
						//we good since it is not prev defined!
						//m->operator[](names[j]) = FLOAT_T;
						functionParamTypes.push_back(FLOAT_T);
					}
					else
					{
						//already defined...
						typeError("T_Function01", getLine(), "Variable \"" + names[j] + "\" is already defined", hadError);
					}
				}
				else if (types[j] == "bool")
				{
					string name = names[j];
					if (isType(name))
					{
						bool hadErrorB = false;
						typeError("T_function07", function->getLine(), "\"" + name + "\" keyword cannot be used as a function parameter name", hadErrorB);
						hadError = hadError || hadErrorB;
					}
					//please note the weird syntax here, calling the [] operator as if it is the function.
					else if (m->operator[](names[j]) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
					{
						//we good since it is not prev defined!
						//m->operator[](names[j]) = BOOL_T;
						functionParamTypes.push_back(BOOL_T);
					}
					else
					{
						//already defined...
						typeError("T_Function02", getLine(), "Variable \"" + names[j] + "\" is already defined", hadError);
					}
				}
				else if (types[j] == "vector3")
				{
					string name = names[j];
					if (isType(name))
					{
						bool hadErrorB = false;
						typeError("T_function001", function->getLine(), "\"" + name + "\" keyword cannot be used as a function parameter name", hadErrorB);
						hadError = hadError || hadErrorB;
					}
					//please note the weird syntax here, calling the [] operator as if it is the function.
					else if (m->operator[](names[j]) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
					{
						//we good since it is not prev defined!
						//m->operator[](names[j]) = BOOL_T;
						functionParamTypes.push_back(VECTOR3_T);
					}
					else
					{
						//already defined...
						typeError("T_Function002", getLine(), "Variable \"" + names[j] + "\" is already defined", hadError);
					}
				}
				else if (types[j] == "int")
				{
					string name = names[j];
					if (isType(name))
					{
						bool hadErrorB = false;
						typeError("T_function003", function->getLine(), "\"" + name + "\" keyword cannot be used as a function parameter name", hadErrorB);
						hadError = hadError || hadErrorB;
					}
					//please note the weird syntax here, calling the [] operator as if it is the function.
					else if (m->operator[](names[j]) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
					{
						//we good since it is not prev defined!
						//m->operator[](names[j]) = BOOL_T;
						functionParamTypes.push_back(INT_T);
					}
					else
					{
						//already defined...
						typeError("T_Function04", getLine(), "Variable \"" + names[j] + "\" is already defined", hadError);
					}
				}
				else
				{
					typeError("T_Function03", getLine(), "Type \"" + types[j] + "\" undefined", hadError);
				}
			}

			string name = function->getName();

			//see if function already exists
			if (fmap->find(function->getName()+"$return") != fmap->end())
			{
				bool hadErrorB = false;
				typeError("T_function05", function->getLine(), "\"" + name + "\" already defined", hadErrorB);
				hadError = hadError || hadErrorB;
			}
			else if (isType(name))
			{
				bool hadErrorB=false;
				typeError("T_function04", function->getLine(), "\"" + name + "\" keyword cannot be used as a function name", hadErrorB);
				hadError = hadError || hadErrorB;
			}
			else
			{
				//add a paramters / return to a function. Note how they are saved.
				fmap->operator[](function->getName()+"$param") = functionParamTypes;
				
				vector<Type> functionReturnType;
				if(function->getReturnType() == "int")
				{
					functionReturnType.push_back(INT_T);
					fmap->operator[](function->getName()+"$return") = functionReturnType;
				}
				else if(function->getReturnType() == "float")
				{
					functionReturnType.push_back(FLOAT_T);
					fmap->operator[](function->getName()+"$return") = functionReturnType;
				}
				else if(function->getReturnType() == "vector3")
				{
					functionReturnType.push_back(VECTOR3_T);
					fmap->operator[](function->getName()+"$return") = functionReturnType;
				}
				else if(function->getReturnType() == "bool")
				{
					functionReturnType.push_back(BOOL_T);
					fmap->operator[](function->getName()+"$return") = functionReturnType;
				}
				else if(function->getReturnType() == "void")
				{
					functionReturnType.push_back(VOID_T);
					fmap->operator[](function->getName()+"$return") = functionReturnType;
				}
				else
				{
					bool hadErrorB=false;
					typeError("T_function09", function->getLine(), "\"" + function->getReturnType() + "\" not a valid return type", hadErrorB);
					hadError = hadError || hadErrorB;
				}
			}

		}		
	}

	bool mainFound = false;
	bool rightReturnType = false;
	bool rightParamType=false;

	//call typecheck on each of the functions
	for (int i = 0; i < nodes.size(); i++)
	{
		ASTTopLevel* tl = (ASTTopLevel*)nodes[i];
		
		if(dynamic_cast<ASTFunction*>(tl->getNode()))
		{
			ASTFunction* function = (ASTFunction*)(tl->getNode());
			
			//each function gets its own typemap copy
			TypeMap* tm = new TypeMap();

			for (auto it = m->begin(); it != m->end(); it++)
			{
				tm->operator[](it->first) = it->second;
			}
			
			(*fmap)["$$current"] = (*fmap)[function->getName()+"$return"];
			
			function->typeCheck(tm,fmap,hadError);
			
			//main checking
			if (function->getName() == "cellCode")
			{
				mainFound = true;
				if(function->getReturnType() == "vector3")
				{
					rightReturnType=true;
				}
				if((*fmap)["cellCode$param"].size() == 0)
				{
					rightParamType = true;
				}
			}
		}	
	}
	
	
	//verify a couple different thigns in the main.
	if (!mainFound)
	{
		bool hadErrorB=false;
		typeError("T_missingmain", getLine(), "cellCode function not found", hadErrorB);
		hadError = hadError || hadErrorB;
	}
	else if(!rightReturnType)
	{
		bool hadErrorB=false;
		typeError("T_wrong_main_return", getLine(), "cellCode must return vector3", hadErrorB);
		hadError = hadError || hadErrorB;		
	}
	else if(!rightParamType)
	{
		bool hadErrorB=false;
		typeError("T_wrong_main_param", getLine(), "cellCode must have no parameters", hadErrorB);
		hadError = hadError || hadErrorB;		
	}
	
	
	return Type::NULL_T;
}

Type ASTDefine::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	//check if the name alreday exists as a def / text
	if (map->find(thing) != map->end())
	{
		typeError( "T3",getLine(), thing+ " already defined", hadError);
	}
	else
	{
		//certain names cannot be used
		if(isType(thing))
		{
			typeError( "T4",getLine(), thing+ " cannot be used as define name as it is a type", hadError);			
		}
		else
		{
			//if not used then create it as a def
			if(type == FLOAT)
				map->operator[](thing) = FLOAT_T;
			else
				map->operator[](thing) = INT_T;
			
			map->operator[](thing+"$def") = DEF_T; //to indicate it exists as a def
		}
	}
	
	return Type::NULL_T;
}
Type ASTTexture::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	if (map->find(name) != map->end())
	{
		typeError( "T1",getLine(), name+ " already defined", hadError);
	}
	else
	{
		if(isType(name))
		{
			typeError( "T2",getLine(), name+ " cannot be used as texture name as it is a type", hadError);			
		}
		else
		{
			map->operator[](name) = TEXTURE_T;
			
		}
	}
	
	
	
	return Type::NULL_T;
}



Type ASTFunction::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	ASTParam* params = getParams();

	vector<string> names = params->getNames();
	vector<string> types = params->getTypes();
		

	// add the param vars into the map.
	for (int j = 0; j < params->getNames().size(); j++)
	{
		string vname = names[j];
		string vtype = types[j];
		
		Type t = NULL_T;
		
		//verify good type
		if(vtype == "int")
		{
			t = INT_T;
		}
		else if(vtype == "float")
		{
			t = FLOAT_T;
		}
		else if(vtype == "vector3")
		{
			t = VECTOR3_T;
		}
		else if(vtype == "bool")
		{
			t = BOOL_T;
		}
		else
		{
			bool hadErrorB=false;
			typeError("T_functiondec01", getLine(), "\"" + vtype + "\" not a valid param type", hadErrorB);
			hadError = hadError || hadErrorB;			
		}
			
		
		//verify not keyword
		if(isType(vname))
		{
			bool hadErrorB=false;
			typeError("T_functiondec03", getLine(), "\"" + vname + "\" cannot be used as var name", hadErrorB);
			hadError = hadError || hadErrorB;				
		}
		//verify good name
		else if (map->operator[](vname) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
		{
			map->operator[](vname) = t;
			
		}
		else
		{
			bool hadErrorB=false;
			typeError("T_functiondec02", getLine(), "\"" + vname + "\" already defined", hadErrorB);
			hadError = hadError || hadErrorB;				
		}
	}
	
	
	
	
	stmts->typeCheck(map,fmap,hadError);

	return Type::NULL_T;
}

//this is to handle functioncalls. you don't have to modify it at all.
Type ASTFunctionCall::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	//printEnv(map,fmap);
	
	//checking it exists
	if (fmap->find(name+"$param") == fmap->end())
	{
		bool hadErrorB = false;
		typeError("t_functioncall01", getLine(), "Function \""+name+"\" does not exist", hadErrorB);
		hadError = hadErrorB || hadError;
	}

	vector<Type> paramTypes;

	//getting the types of the arguments.
	for (int i = 0; i < ((ASTArgs*)this->args)->getArgs().size(); i++)
	{
		bool hadErrorB = false;
		paramTypes.push_back(((ASTArgs*)this->args)->getArgs()[i]->typeCheck(map,fmap, hadErrorB));
		hadError = hadErrorB || hadError;
	}

	bool paramerror = false;

	//comparing to arguments that were passed in and the actual types in the function definition
	if (fmap->find(name+"$param") != fmap->end())
	{
		vector<Type> actualTypes = fmap->operator[](name+"$param");

		bool error = false;

		if (paramTypes.size()!= actualTypes.size())
		{
			error = true;
		}
		else
		{
			for (int i = 0; i < paramTypes.size(); i++)
			{
				if (paramTypes[i] != actualTypes[i] && !(actualTypes[i] == FLOAT_T && paramTypes[i] == INT_T  ))
				{
					error = true;

				}
				if (paramTypes[i] == ERROR_T)
				{
					paramerror = true;
				}
			}
		}

		//code to generate the error message
		if(error && !paramerror)
		{
			bool hadErrorB = false;

			string wanted = "";
			string actual = "";

			for (int i = 0; i < paramTypes.size(); i++)
			{
				wanted += typeToString(paramTypes[i]);
				if (i != paramTypes.size() - 1)
					wanted += ", ";
			}

			for (int i = 0; i < actualTypes.size(); i++)
			{
				actual += typeToString(actualTypes[i]);
				if (i != actualTypes.size() - 1)
					actual += ", ";
			}

			typeError("t_functioncall02", getLine(), "Function \"" + name + "\" recieved arguments \""+ wanted +"\" but wanted \""+actual+"\"", hadErrorB);
			hadError = hadErrorB || hadError;
		}
	}

	return fmap->operator[](name+"$return")[0];
}

Type ASTStatements::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	for(int i=0;i<nodes.size();i++)
	{
		nodes[i]->typeCheck(map,fmap,hadError);
	}
	return Type::NULL_T;
}
Type ASTStatement::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	statement->typeCheck(map,fmap,hadError);
	
	return Type::NULL_T;
}

Type ASTDeclaration::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{

	Type t = NULL_T;
	
	string vtype = type;
	string vname = name;
	
	//verify type
	if(vtype == "int")
	{
		t = INT_T;
	}
	else if(vtype == "float")
	{
		t = FLOAT_T;
	}
	else if(vtype == "vector3")
	{
		t = VECTOR3_T;
	}
	else if(vtype == "bool")
	{
		t = BOOL_T;
	}
	else
	{
		bool hadErrorB=false;
		typeError("T_dec01", getLine(), "\"" + vtype + "\" not a valid type", hadErrorB);
		hadError = hadError || hadErrorB;			
	}
	
	if(statement != 0)
	{
		//get rhs type
		Type rhs = statement->typeCheck(map,fmap,hadError);
		
		//verify type and rhs type are the same (or compatible)
		if((rhs == t) || (rhs == INT_T && t == FLOAT_T))
		{
			
		}
		else
		{
			if(rhs != ERROR_T)
			{
				bool hadErrorB=false;
				typeError("T_dec04", getLine(), "Left and right sides of declaration do not agree. Left is \"" + typeToString(t) + "\". Right is \""+ typeToString(rhs)+"\"", hadErrorB);
				hadError = hadError || hadErrorB;
			}			

		}
		
		
		
	}

	//verify name. Note we do this last so that the varname cannot be used in the expression of the declartion.
	if(isType(vname))
	{
		bool hadErrorB=false;
		typeError("T_functiondec03", getLine(), "\"" + vname + "\" cannot be used as var name", hadErrorB);
		hadError = hadError || hadErrorB;				
	}
	//verify good name
	else if (map->operator[](vname) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
	{
		map->operator[](name) = t;
		
	}
	else
	{
		bool hadErrorB=false;
		typeError("T_functiondec02", getLine(), "\"" + vname + "\" already defined", hadErrorB);
		hadError = hadError || hadErrorB;				
	}

	
	return Type::NULL_T;
}

Type ASTFactor::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	return theThing->typeCheck(map,fmap,hadError);
}
Type ASTElement::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	//scafolding here. NOTE: the functionCall is handeled not in this note.
	
	/*
	if(elementType == INT)
	{
		
	}
	else if(elementType == FLOAT)
	{
		
	}
	else if(thing2 != "-1" && thing2 != "-2") //so it is var DOT (r | g | b)
	{
		
	}
	else if(thing2 == "-2") // so a literal string
	{
		
	}
	else //varname or true or false
	{
		
	}
	*/
	
	if(elementType == INT)
	{
		return Type::INT_T;
	}
	else if(elementType == FLOAT)
	{
		return Type::FLOAT_T;
	}
	else if(thing2 != "-1" && thing2 != "-2") //so it is var DOT (r | g | b)
	{
		//handle dot LHS
		if (map->operator[](thing) == VECTOR3_T) //in this case null_t is 0 so that is what will be returned if it is empty.
		{

		}
		else
		{
			bool hadErrorB=false;
			typeError("T_element03", getLine(), "Left had side of Dot must be vector3, \"" + thing + "\" is of "+typeToString(map->operator[](thing)), hadErrorB);
			hadError = hadError || hadErrorB;	
		}
		
		//hanlde dot RHS
		if(thing2 != "r" && thing2 != "g" && thing2 != "b")
		{
			bool hadErrorB=false;
			typeError("T_element02", getLine(), "Right side of dot must be r,g, or b.  \"" + thing2 + "\" is of "+typeToString(map->operator[](thing)), hadErrorB);
			hadError = hadError || hadErrorB;	
		}
		
		return Type::FLOAT_T;
	}
	else if (thing2 == "-2") // so a literal string
	{
		return Type::STRING_T;
	}
	else
	{
		if(thing == "true" || thing == "false")
			return Type::BOOL_T;
		
		//handle variable
		if (map->operator[](thing) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
		{
			bool hadErrorB=false;
			typeError("T_element01", getLine(), "Variable \"" + thing + "\" is not defined", hadErrorB);
			hadError = hadError || hadErrorB;	
			
			return Type::ERROR_T;
		}
		else
		{
			return map->operator[](thing);
		}
	}
	
	
}


//free of charge
Type ASTFunctionCallStmt::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	call->typeCheck(map, fmap, hadError);
	return Type::NULL_T;
}

Type ASTBlockStatement::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	TypeMap* tm = new TypeMap();

	for (auto it = map->begin(); it != map->end(); it++)
	{
		tm->operator[](it->first) = it->second;
	}

	statement->typeCheck(tm, fmap, hadError);
	return Type::NULL_T;
}


// for part 2

//these will have to be modified

Type ASTBoolExprA::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type left = stmts[0]->typeCheck(map, fmap, hadError);
	if (operators.size() == 0)
        return left;  // no operators, just pass through
	if(left != BOOL_T && left != ERROR_T)
	{
		bool hadErrorB=false;
		typeError("T_boolexpr01", getLine(), "Left hand side of boolean expression must be bool. Left hand side is of type \"" + typeToString(left) + "\"", hadErrorB);
		hadError = hadError || hadErrorB;	
	}
	for(int i = 0; i < operators.size(); i++)
    {
        Type right = stmts[i+1]->typeCheck(map, fmap, hadError);

        if(right != BOOL_T && right != ERROR_T)
        {
            bool hadErrorB = false;
            typeError("T_boolA02", getLine(),
                "Right side of && or || must be bool, found " + typeToString(right),
                hadErrorB);
            hadError = hadError || hadErrorB;
        }
    }

    return Type::BOOL_T;
}
Type ASTBoolExprB::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type left = stmts[0]->typeCheck(map, fmap, hadError);
	if (operators.size() == 0)
        return left;  // no operators, just pass through
	for(int i = 0; i < operators.size(); i++)
	{
		Type right = stmts[i+1]->typeCheck(map, fmap, hadError);
		string op = operators[i];

		if(op == "==" || op == "!=")
		{
			if(left != right && left != ERROR_T && right != ERROR_T && !(left == FLOAT_T && right == INT_T) && !(left == INT_T && right == FLOAT_T))
			{
				bool hadErrorB = false;
				typeError("T_boolB01", getLine(),
					"Both sides of == and != must be the same type or INTs and FLOATS. Left is " + typeToString(left) + " and right is " + typeToString(right),
					hadErrorB);
				hadError = hadError || hadErrorB;
			}
		}
		else
		{
			if((left != FLOAT_T && left != INT_T) || (right != FLOAT_T && right != INT_T))
			{
				bool hadErrorB = false;
				typeError("T_boolB02", getLine(),
					"Both sides of <, >, <=, and >= must be INTs or FLOATs. Left is " + typeToString(left) + " and right is " + typeToString(right),
					hadErrorB);
				hadError = hadError || hadErrorB;
			}

		}

		left = right;  // move forward for chaining
	}
	return Type::BOOL_T;
}


Type ASTTerm::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
    Type left = stmts[0]->typeCheck(map, fmap, hadError);
    for (int i = 0; i < operators.size(); i++)
    {
        Type right = stmts[i+1]->typeCheck(map, fmap, hadError);

        if (left != ERROR_T && right != ERROR_T)
        {
            if ((left != FLOAT_T && left != INT_T) || (right != FLOAT_T && right != INT_T))
            {
                bool hadErrorB = false;
                typeError("T_term01", getLine(),
                    "Both sides of * and / must be INTs or FLOATs. Left is "
                    + typeToString(left) + " and right is " + typeToString(right),
                    hadErrorB);
                hadError = hadError || hadErrorB;
                left = ERROR_T;
            }
            else if (left == FLOAT_T || right == FLOAT_T)
            {
                left = FLOAT_T;
            }
            else
            {
                left = INT_T;
            }
        }
    }
    return left;
}
Type ASTExpr::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
    Type left = stmts[0]->typeCheck(map, fmap, hadError);
    for (int i = 0; i < operators.size(); i++)
    {
        Type right = stmts[i+1]->typeCheck(map, fmap, hadError);

        if (left != ERROR_T && right != ERROR_T)
        {
            if ((left != FLOAT_T && left != INT_T) || (right != FLOAT_T && right != INT_T))
            {
                bool hadErrorB = false;
                typeError("T_expr01", getLine(),
                    "Both sides of + and - must be INTs or FLOATs. Left is "
                    + typeToString(left) + " and right is " + typeToString(right),
                    hadErrorB);
                hadError = hadError || hadErrorB;
                left = ERROR_T;
            }
            else if (left == FLOAT_T || right == FLOAT_T)
            {
                left = FLOAT_T;
            }
            else
            {
                left = INT_T;
            }
        }
    }
    return left;
}


Type ASTIf::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type guardExpr = guard->typeCheck(map, fmap, hadError);
	if (guardExpr != BOOL_T && guardExpr != ERROR_T)
	{
		bool hadErrorB = false;
		typeError("T_if01", getLine(),
			"Guard of if statement must be a boolean. Received " + typeToString(guardExpr),
			hadErrorB);
		hadError = hadError || hadErrorB;
	}
	TypeMap* tm = new TypeMap(*map);
	statement->typeCheck(tm, fmap, hadError);
	

	return Type::NULL_T;
}
Type ASTAssign::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	
	//make sure not define
	//remember that the def will have a second thing in the map with its name ending with $def if it is a def. So, a def for X will have X and X$def in the map.
	
	//First check if define
	if(map->find(lhs1+"$def") != map->end())
	{
		bool hadErrorB=false;
		typeError("T_assign01", getLine(), "Cannot assign to \"" + lhs1 + "\" because it is a defined constant", hadErrorB);
		hadError = hadError || hadErrorB;	
		return Type::ERROR_T;
	}
	if(lhs2 == "-1")
	{
		Type left = map->operator[](lhs1); //get the type of the variable we are assigning to. Note if it is not defined it will return null_t which is 0.
		Type rightType = right->typeCheck(map, fmap, hadError);
		if(left == NULL_T)
		{
			bool hadErrorB=false;
			typeError("T_assign02", getLine(), "Variable \"" + lhs1 + "\" is not defined", hadErrorB);
			hadError = hadError || hadErrorB;	
		}
		else if(rightType != left && rightType != ERROR_T && !(left == FLOAT_T && rightType == INT_T))
		{
			bool hadErrorB=false;
			typeError("T_assign03", getLine(), "Type of right hand side does not match type of left hand side. Left hand side is \"" + typeToString(left) + "\" and right hand side is \"" + typeToString(rightType) + "\"", hadErrorB);
			hadError = hadError || hadErrorB;	
		}
	}
	else
	{
		Type left = map->operator[](lhs1); //get the type of the variable we are assigning to. Note if it is not defined it will return null_t which is 0.
		if(left != VECTOR3_T)
		{
			bool hadErrorB=false;
			typeError("T_assign04", getLine(), "Left hand side of dot assignment must be vector3. \"" + lhs1 + "\" is of type "+typeToString(map->operator[](lhs1)), hadErrorB);
			hadError = hadError || hadErrorB;	
		}
		if(lhs2 != "r" && lhs2 != "g" && lhs2 != "b")
		{
			bool hadErrorB=false;
			typeError("T_assign05", getLine(), "Right hand side of dot assignment must be r, g, or b. \"" + lhs2 + "\" is not valid", hadErrorB);
			hadError = hadError || hadErrorB;	
		}
		Type rightType = right->typeCheck(map, fmap, hadError);
		if(rightType != FLOAT_T && rightType != INT_T && rightType != ERROR_T)
		{
			bool hadErrorB=false;
			typeError("T_assign06", getLine(), "Right hand side of dot assignment must be int or float. It is of type \"" + typeToString(rightType) + "\"", hadErrorB);
			hadError = hadError || hadErrorB;	
		}
	}
	//handle vector too :) lhs1 is the normal var name. if lhs2 is not -1, then it is a VAR DOT VAR. remember the second var can only be 'r', 'g', or 'b'.

	return Type::NULL_T;
}



Type ASTWhile::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type guardExpr = guard->typeCheck(map, fmap, hadError);
	if (guardExpr != BOOL_T && guardExpr != ERROR_T)
	{
		bool hadErrorB = false;
		typeError("T_while01", getLine(),
			"Guard of while statement must be a boolean. Received " + typeToString(guardExpr),
			hadErrorB);
		hadError = hadError || hadErrorB;
	}
	TypeMap* tm = new TypeMap(*map);

	/*
	Typemap* tm = new TypeMap();
	for (auto it = map->begin(); it != map->end(); it++)
	{
		tm->operator[](it->first) = it->second;
	} */
	statement->typeCheck(tm, fmap, hadError);
	

	return Type::NULL_T;	
}

Type ASTFor::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
		TypeMap* tm = new TypeMap(*map);
		declaration->typeCheck(tm,fmap,hadError);
		Type guardExpr = guard->typeCheck(tm, fmap, hadError);
		if (guardExpr != BOOL_T && guardExpr != ERROR_T)
		{
			bool hadErrorB = false;
			typeError("T_for01", getLine(),
				"Guard of for statement must be a boolean. Received " + typeToString(guardExpr),
				hadErrorB);
			hadError = hadError || hadErrorB;
		}
		assignment->typeCheck(tm,fmap,hadError);
		statement->typeCheck(tm, fmap, hadError);

		return Type::NULL_T;

}




Type ASTReturn::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	//you need to verify the return type is correct as well as verify the type of the 
	//the one thing we aren't verfiying (we probably should) is that the function has a return of the proper type at the end. But who wants to do that????
	
	//this statement will get the current function's return type list. Recall it will be a vector of size 1 - the 0th index being the thing you need.
	vector<Type> currenReturnType = (*fmap)["$$current"];
	if(rhs == 0) // so void return
	{
		if(currenReturnType[0] != VOID_T)
		{
			bool hadErrorB = false;
			typeError("T_return02", getLine(),
				"Return statement is a void return but the function's declared return type is not void. Function return type is " + typeToString(currenReturnType[0]),
				hadErrorB);
			hadError = hadError || hadErrorB;
		}
	}
	else
	{
		Type returnExprType = rhs->typeCheck(map, fmap, hadError);
		if(returnExprType != currenReturnType[0] && returnExprType != ERROR_T && !(currenReturnType[0] == FLOAT_T && returnExprType == INT_T))
		{
			bool hadErrorB = false;
			typeError("T_return01", getLine(),
				"Return type does not match the function's declared return type. Function return type is " + typeToString(currenReturnType[0]) + " and return statement is returning " + typeToString(returnExprType),
				hadErrorB);
			hadError = hadError || hadErrorB;
		}
	}

	


	return Type::NULL_T;
}




//not implemented
Type ASTTopLevel::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	return Type::NULL_T;
}
//not implmeneted
Type ASTParam::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	return Type::NULL_T;
}

//not implemented. handle in ASTFunctionCall
Type ASTArgs::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	return Type::NULL_T;
}

// ============================================================
//  CODE GENERATOR
// ============================================================

static string newTemp(string type, ofstream& out, int& tempCount)
{
    return "t" + to_string(tempCount++);
}


static string newLabel(int& labelCount)
{
	return "t" + to_string(labelCount++);
}

void ASTProgram::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	for(int i = 0; i < nodes.size(); i++)
		nodes[i]->generateCode(out, tempCount, labelCount);
}

void ASTTopLevel::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	if(topElement != 0)
		topElement->generateCode(out, tempCount, labelCount);
}

void ASTFunction::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	out << "function\n";
	out << name << "\n";
	out << returnType << "\n";
	if(params != 0)
		params->generateCode(out, tempCount, labelCount);
	if(stmts != 0)
		stmts->generateCode(out, tempCount, labelCount);
	out << "endfunction\n";
}

void ASTParam::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	for(int i = 0; i < names.size(); i++)
	{
		out << types[i] << "\n";
		out << names[i] << "\n";
	}
}

void ASTStatements::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	for(int i = 0; i < nodes.size(); i++)
		nodes[i]->generateCode(out, tempCount, labelCount);
}

void ASTStatement::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	if(statement != 0)
		statement->generateCode(out, tempCount, labelCount);
}

void ASTBlockStatement::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	if(statement != 0)
		statement->generateCode(out, tempCount, labelCount);
}

void ASTReturn::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
    if(rhs != 0)
        rhs->generateCode(out, tempCount, labelCount);
}



void ASTDeclaration::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
    out << type << " ";
    out << name << "\n";
    if(statement != 0)
    {
        statement->generateCodeExpr(out, tempCount, labelCount, name);
    }
}

void ASTAssign::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
    string dest = lhs1;
    if(lhs2 != "" && lhs2 != "-1")
        dest = lhs1 + "." + lhs2;

    right->generateCodeExpr(out, tempCount, labelCount, dest);
}

void ASTIf::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
    string guardResult = guard->generateCodeExpr(out, tempCount, labelCount, "");
    string bodyLabel = newLabel(labelCount);
    string endLabel = newLabel(labelCount);
    out << "jumpif " << bodyLabel << " " << guardResult << "\n";
    out << "jump " << endLabel << "\n";
    out << "label " << bodyLabel << "\n";
    statement->generateCode(out, tempCount, labelCount);
    out << "label " << endLabel << "\n";
}

void ASTWhile::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	string startlabel = newLabel(labelCount);
	string endlabel = newLabel(labelCount);
	out << "label " << startlabel << "\n";
	string guardResult = guard->generateCodeExpr(out, tempCount, labelCount, "b");
	out << "jumpif" << " ";
	out << guardResult << " ";
	out << endlabel << "\n";
	statement->generateCode(out,tempCount,labelCount);
	out << "jump " << startlabel << "\n";
	out << "label " << endlabel << "\n";
}

void ASTFor::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	declaration->generateCode(out, tempCount, labelCount);
	string startlabel = newLabel(labelCount);
	out << "label " << startlabel << "\n";
	string guardResult = guard->generateCodeExpr(out, tempCount, labelCount, "b");
	out << "jumpif" << " ";
	out << guardResult << " ";
	string bodylabel = newLabel(labelCount);
	out << bodylabel << "\n";
	string endlabel = newLabel(labelCount);
	out << "jump " << endlabel << "\n";
	out << "label " << bodylabel << "\n";
	statement->generateCode(out,tempCount,labelCount);
	assignment->generateCode(out,tempCount,labelCount);
	out << "jump " << startlabel << "\n";
	out << "label " << endlabel << "\n";

}

void ASTFunctionCallStmt::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	if(call != 0)
		call->generateCode(out, tempCount, labelCount);
}

void ASTFunctionCall::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	out << "callfunction" << "\n";
	out << name << "\n";
	out << "void\n";
	out << "args\n";
	if(args != 0)
		args->generateCode(out, tempCount, labelCount);
	out << "endargs\n";
}

void ASTFunctionCall::generateArgs(ofstream& out, int& tempCount, int& labelCount)
{
	args->generateCode(out, tempCount, labelCount);
}

void ASTArgs::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	for(int i = 0; i < args.size(); i++)
    {
        // evaluate the argument expression and get the register it landed in
        string result = args[i]->generateCodeExpr(out, tempCount, labelCount, "");
        // emit that register name so the interpreter can find it
        out << result << "\n";
    }
}

void ASTBoolExprA::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	generateCodeExpr(out, tempCount, labelCount);
}

string ASTBoolExprA::generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest)
{
    if(operators.size() == 0)
        return stmts[0]->generateCodeExpr(out, tempCount, labelCount, dest);
    string result = stmts[0]->generateCodeExpr(out, tempCount, labelCount);
    for(int i = 0; i < operators.size(); i++)
    {
        string rhs = stmts[i+1]->generateCodeExpr(out, tempCount, labelCount);
        out << operators[i] << " ";
        out << dest << " ";
        out << result << " ";
        out << rhs << "\n";
        result = dest;
    }
    return result;
}

void ASTBoolExprB::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	generateCodeExpr(out, tempCount, labelCount);
}

string ASTBoolExprB::generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest)
{
    if(operators.size() == 0)
        return stmts[0]->generateCodeExpr(out, tempCount, labelCount, dest);
    string result = stmts[0]->generateCodeExpr(out, tempCount, labelCount);
    for(int i = 0; i < operators.size(); i++)
    {
        string rhs = stmts[i+1]->generateCodeExpr(out, tempCount, labelCount);
        string target = (dest != "") ? dest : result;
        out << operators[i] << " ";
        out << target << " ";
        out << result << " ";
        out << rhs << "\n";
        result = target;
    }
    return result;
}
void ASTTerm::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	generateCodeExpr(out, tempCount, labelCount);
}

string ASTTerm::generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest)
{
    if(operators.size() == 0)
        return stmts[0]->generateCodeExpr(out, tempCount, labelCount, dest);
    string result = stmts[0]->generateCodeExpr(out, tempCount, labelCount);
    for(int i = 0; i < operators.size(); i++)
    {
        string rhs = stmts[i+1]->generateCodeExpr(out, tempCount, labelCount);
        out << operators[i] << " ";
        out << dest << " ";
        out << result << " ";
        out << rhs << "\n";
        result = dest;
    }
    return result;
}

void ASTExpr::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	generateCodeExpr(out, tempCount, labelCount);
}

string ASTExpr::generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest)
{
    string result = stmts[0]->generateCodeExpr(out, tempCount, labelCount);
    for(int i = 0; i < operators.size(); i++)
    {
        string rhs = stmts[i+1]->generateCodeExpr(out, tempCount, labelCount);
        out << operators[i] << " ";
        out << dest << " ";
        out << result << " ";
        out << rhs << "\n";
        result = dest;
    }
    return result;
}
void ASTFactor::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	generateCodeExpr(out, tempCount, labelCount);
}

string ASTFactor::generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest)
{
	if(isElement)
		return theThing->generateCodeExpr(out, tempCount, labelCount, dest);
	else
		return theThing->generateCodeExpr(out, tempCount, labelCount, dest);
}

void ASTElement::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	generateCodeExpr(out, tempCount, labelCount);
}

string ASTElement::generateCodeExpr(ofstream& out, int& tempCount, int& labelCount, string dest)
{
	if(thing2 == "-2")
		return "\"" + thing + "\"";
	if(thing2 != "-1")
		return thing + "." + thing2;
	return thing;
}

void ASTDefine::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	// nothing to emit
}

void ASTTexture::generateCode(ofstream& out, int& tempCount, int& labelCount)
{
	// nothing to emit
}