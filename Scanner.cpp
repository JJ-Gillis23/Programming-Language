#include "Scanner.h"

#include <string>
using namespace std;

//this function returns a string representation of the TokenType
string Scanner::toString(TokenType t)
{
   if (t == NONE)
      return "NONE";
   if (t == EQUALASSIGN)
      return "EQL";
   if (t == LBRACE)
      return "LBRACE";
   if (t == RBRACE)
      return "RBRACE";
   if (t == EE)
      return "EE";
   if(t == NE)
      return "NE";
   if (t == STRING)
      return "STRING";
   if(t == SEMI)
      return "SEMI";
   if(t == LPAREN)
      return "LPAREN";  
   if(t == RPAREN)
      return "RPAREN"; 
   if(t == GRE)
      return "GRE";   
   if(t == GRE)
      return "GRE";
   if(t == GR)
      return "GR";
   if(t == LT)
      return "LT";
   if(t == LTE)
      return "LTE";
   if(t == COMMA)
      return "COMMA";
   if(t == AND)
      return "AND";
   if(t == OR)
      return "OR";  
   if(t == NOT)
      return "NOT";
   if(t == DOT)
      return "DOT";  
   if(t == QUOTED)
      return "QUOTED";    
   if(t == MOD)
      return "MOD"; 
   if(t == MULTIPLY)
      return "MULTIPLY";    
   if(t == DIVIDE)
      return "DIVIDE";  
   if(t == PLUS)
      return "PLUS";   
   if(t == MINUS)
      return "MINUS";
   if(t == INT)
      return "INT";
   if(t == FLOAT)
      return "FLOAT";    
   if(t == TEXTURE)
      return "TEXTURE"; 
   if(t == DEFINE)
      return "DEFINE"; 
   if (t == ERROR)
      return "error: ";
   return "ERROR in tostring";
}

string Scanner::currentTokenString()
{
   return currents;
}

string Scanner::nextTokenString()
{
   return nexts;
}

TokenType Scanner::currentTokenType()
{
   return currenttt;
}

TokenType Scanner::nextTokenType()
{
   return nexttt;
}


//constructor for the scanner. Right now it also iterates over everything in the scanner.
Scanner::Scanner(string fname)
{
   filestream.open(fname);

   linenext = 1;

	

   if (!filestream.good())
   {
      cout << "Could not open file: "<< fname<<"\n";
      return;
   }

	
   advance(); //fill up first slot
   advance(); //fill up second slot

}


//this function takes the next thing in the stream and adds it to the buffer
void addToBuffer(string & buf, ifstream & stream)
{
   int next = stream.get();

   if (next == -1)
   {
      buf = buf + (char)0; //null signifies eof for today!
   }
   else
   {
      buf = buf + (char)next;
   }

}


//this function removes the end of the buffer and sticks it back in the stream so it can be read again)
void removeFromBuffer(string & buf, ifstream & stream)
{
   char last = buf.back();
   stream.putback(last);
   buf = buf.substr(0, buf.size() - 1);
}


//returns true if the character is a number
bool isNum(char test)
{
   return (test == '0' || test == '1' || test == '2' || test == '3' || test == '4' || test == '5' || test == '6' || test == '7' || test == '8' || test == '9');
}

//returns true if lowercase character (and _)
bool isLowerCharacter(char test)
{
   return (test == 'a' || test == 'b' || test == 'c' || test == 'd' ||
      test == 'e' || test == 'f' || test == 'g' || test == 'h' ||
      test == 'i' || test == 'j' || test == 'k' || test == 'l' ||
      test == 'm' || test == 'n' || test == 'o' || test == 'p' ||
      test == 'q' || test == 'r' || test == 's' || test == 't' ||
      test == 'u' || test == 'v' || test == 'w' || test == 'x' || test == 'y' || test == 'z' || test == '_');
}

//returns true if uppercase case character
bool isUpperCharacter(char test)
{
   return (test == 'A' || test == 'B' || test == 'C' || test == 'D' ||
      test == 'E' || test == 'F' || test == 'G' || test == 'H' ||
      test == 'I' || test == 'J' || test == 'K' || test == 'L' ||
      test == 'M' || test == 'N' || test == 'O' || test == 'P' ||
      test == 'Q' || test == 'R' || test == 'S' || test == 'T' ||
      test == 'U' || test == 'V' || test == 'W' || test == 'X' || test == 'Y' || test == 'Z');
}

//returns if it is a white space character
bool isWhiteSpace(char test)
{
   return (test == ' ' || test == '\t' || test == '\n');
}




//advance places whatever is in the "next" variables into the "current" variables and then finds what the next variables are supposed to be. Next variables are things we are looking ahead at.
void Scanner::advance()
{
   currents = nexts;
   currenttt = nexttt;
   linecurrent = linenext;


	//set that the scanner has not picked something yet. We will use this later on.
   nexttt = NONE;

	//holds what is currently read in but not yet processed
   string buffer;

   bool start = true;
   while (start)
   {
      start = false;
   
      buffer = "";
   
   	//add the first thing to the buffer
      addToBuffer(buffer, filestream);
   
   	
   	//if the first thing is a {, then say we have an LBrace and set the string representation of it to "{"
      if (buffer[0] == '{')
      {
         nexttt = LBRACE;
         nexts = "{";
      }
      else if (buffer[0] == '}')
      {
         nexttt = RBRACE;
         nexts = "}";
      }
      else if (buffer[0] == '(')
      {
         nexttt = LPAREN;
         nexts = "(";
      }      
      else if (buffer[0] == ')')
      {
         nexttt = RPAREN;
         nexts = ")";
      }
      else if (buffer[0] == '>')
      {
      
         addToBuffer(buffer, filestream);
         if (buffer[1] == '=') 
         {
         	//if yes then you know you have an >=
            nexttt = GRE;
            nexts = ">=";
         }
         else //otherwise remove the "bad" character from the buffer and just use =
         {
            removeFromBuffer(buffer, filestream);
            nexttt = GR;
            nexts = ">";
         }
      }   
      else if(buffer[0] == '!')
      {
         addToBuffer(buffer, filestream);
         if (buffer[1] == '=') 
         {
         	//if yes then you know you have an !=
            nexttt = NE;
            nexts = "!=";
         }
         else //otherwise remove the "bad" character from the buffer and just use !
         {
            removeFromBuffer(buffer, filestream);
            nexttt = NOT;
            nexts = "!";
         }
      }
      else if (buffer[0] == '<')
      {
      
         addToBuffer(buffer, filestream);
         if (buffer[1] == '=')
         {
         	//if yes then you know you have an <=
            nexttt = LTE;
            nexts = "<=";
         }
         else //otherwise remove the "bad" character from the buffer and just use =
         {
            removeFromBuffer(buffer, filestream);
            nexttt = LT;
            nexts = "<";
         }
      }   
      
      else if(buffer[0] == '*')
      {
         nexttt = MULTIPLY;
         nexts = "*";
      }           
      else if(buffer[0] == '/')
      {
         nexttt = DIVIDE;
         nexts = "/";
      }     
      else if(buffer[0] == '+')
      {
         nexttt = PLUS;
         nexts = "+";
      }      
      else if(buffer[0] == '-')
      {
         addToBuffer(buffer,filestream);
         if(isNum(buffer[1]))
         {
            addToBuffer(buffer,filestream);
            while(isNum(buffer[buffer.size()-1]))
            {
               addToBuffer(buffer,filestream);
            }
            if(buffer[buffer.size()-1] == '.')
            {
               addToBuffer(buffer,filestream);
               if(isNum(buffer[buffer.size()-1]))
               {
                  while(isNum(buffer[buffer.size()-1]))
                  {
                     addToBuffer(buffer,filestream);
                  }
                  removeFromBuffer(buffer,filestream);
                  nexttt = FLOAT;
                  nexts = buffer;
               }
               else
               {
                  removeFromBuffer(buffer,filestream);
                  dealWithError(buffer);
               }
            }
            else
            {
               removeFromBuffer(buffer,filestream);
               nexttt = INT;
               nexts = buffer;
            }
            
         }
         
         else
         {
            removeFromBuffer(buffer, filestream);
            nexttt = MINUS;
            nexts = "-";
         }
      
      }
      else if(isNum(buffer[0]))
      {
         addToBuffer(buffer,filestream);
         while(isNum(buffer[buffer.size()-1]))
         {
            addToBuffer(buffer,filestream);
         }
         {
            addToBuffer(buffer,filestream);
         }
            if(buffer[buffer.size()-1] == '.')
            {
               addToBuffer(buffer,filestream);
               if(isNum(buffer[buffer.size()-1]))
               {
                  while(isNum(buffer[buffer.size()-1]))
                  {
                     addToBuffer(buffer,filestream);
                  }
                  removeFromBuffer(buffer,filestream);
                  nexttt = FLOAT;
                  nexts = buffer;
               }
               else
               {
                  removeFromBuffer(buffer,filestream);
                  dealWithError(buffer);
               }
            }
            else
            {
               nexttt = INT;
               nexts = buffer;
            }
      
      }         
      else if (buffer[0] == ',')
      {
         nexttt = COMMA;
         nexts = ",";
      }      
      else if (buffer[0] == '&')
      {
         nexttt = AND;
         nexts = "&";
      }      
      else if (buffer[0] == '|')
      {
         nexttt = OR;
         nexts = "|";
      }      
      else if (buffer[0] == '!')
      {
         nexttt = NOT;
         nexts = "!";
      }  
      else if (buffer[0] == '.')
      {
         nexttt = DOT;
         nexts = ".";
      }    
      else if (buffer[0] == '"')
      {
         nexttt = QUOTED;
         nexts = "\"";
      }
      else if (buffer[0] == '#')
      {
         addToBuffer(buffer,filestream);
         if(isLowerCharacter(buffer[1]))
         {
            if(buffer[1] == 't')
            {
               nexttt = TEXTURE;
               nexts = "#text";
            }
            
            else if(buffer[1] == 'd')
            {
               nexttt = DEFINE;
               nexts = "#def";
            }
         }
         
         else
         {
            removeFromBuffer(buffer,filestream);
            dealWithError(buffer);
         }
      }
      else if (buffer[0] == '"')
      {
         nexttt = QUOTED;
         nexts = "\"";
      }      
      else if (buffer[0] == '=')
      {
      	//this one is harder because you have to determine if you have an = or if you have ==
      
         addToBuffer(buffer, filestream);
         if (buffer[1] == '=') //check if both are =
         {
         	//if yes then you know you have an ==
            nexttt = EE;
            nexts = "==";
         }
         else //otherwise remove the "bad" character from the buffer and just use =
         {
            removeFromBuffer(buffer, filestream);
            nexttt = EQUALASSIGN;
            nexts = "=";
         }
      }
      else if (buffer[0] == 0) //add buffer puts a null char if the file is empty
      {
         nexttt = ENDOFFILE;
         nexts = "eof";
      }//here is for a string. It requres to start with a lowercase or uppercase (_ is marked as a lowercase letter) then the remainder can be lower/upper/ or nums
      else if (isLowerCharacter(buffer[0]) || isUpperCharacter(buffer[0]))
      {
         addToBuffer(buffer, filestream);
         while (isLowerCharacter(buffer[buffer.size() - 1]) || isUpperCharacter(buffer[buffer.size() - 1]) || isNum(buffer[buffer.size() - 1]))
         {
            addToBuffer(buffer, filestream);
         }
         removeFromBuffer(buffer, filestream);
      
         nexttt = STRING;
         nexts = buffer;
      	
      }
      
      else if (buffer[0] == ';')
      {
         nexttt = SEMI;
         nexts = ";";
      }
      
      else
      {
      
      	
         
      
      
      
      	//nothing matched so far //// white space and error checking
         if(nexttt == NONE)
         {
         
         	//white space
            if (isWhiteSpace(buffer[0]))
            {
               while (isWhiteSpace(buffer[buffer.size() - 1]))
               {
               	
                  if (buffer[buffer.size() - 1] == '\n')
                  {
                     linenext++;
                  }
                  addToBuffer(buffer, filestream);
               }
               removeFromBuffer(buffer, filestream);
               start = true;
            }
            else
            {
            	//or is an error character.
               dealWithError(buffer);
            }
         }
      }
   }
	/*cout << "***"<<endl;
	cout << linecurrent << " " << currentTokenString()<<endl;
	cout << linenext << " " << nextTokenString() << endl;
	cout << "***" << endl;*/
}

//this function should be called if you know an error character is currently in the buffer
void Scanner::dealWithError(string buffer)
{
   while (!isWhiteSpace(buffer[buffer.size() - 1]) && buffer[buffer.size() - 1] != 0)
   {
      addToBuffer(buffer, filestream);
   }
   removeFromBuffer(buffer, filestream);
   nexttt = ERROR;
   nexts = "IT2: Invalid Token detected on line: " + to_string(linenext) + " [ " + buffer + " ]";
}


//returns the current line number
int Scanner::getLine()
{
   return linecurrent;
}