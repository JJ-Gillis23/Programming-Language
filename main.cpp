#include "Scanner.h"
#include "Parser.h"
#include "AST.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
   if (argc < 2)
   {
      cout << "Usage: <executable name> <filename>";
   }

   Parser p(argv[1]);
      cout << "Starting parse\n";
      ASTProgram* prog = p.parse();
      cout << "Parse done\n";
      if (!p.getErrorDetected())
      {
         cout << "Starting typecheck\n";
         bool hadError = false;
         prog->typeCheck(0, 0, hadError);
         cout << "Typecheck done\n";

      if(!hadError)
      {
         cout << "Starting code generation\n";
         ofstream out("input.txt");
         int tempCount = 0;
         int labelCount = 0;
         prog->generateCode(out, tempCount, labelCount);
         out.close();
         cout << "Code generation complete. Output written to input.txt\n";
      }
    }
}

