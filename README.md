# A Custom Shader Programming Language

As part of a programming languages class that I took, I built a A fully implemented programming language designed for shader programming, built from scratch in C++ and Java. The project includes a **Scanner**, **Parser**, **AST**, **Type Checker**, **Code Generator**, and **Interpreter** — a complete compiler pipeline from source code to execution.

The language is designed around a `cellCode` function that returns a `vector3` color value, making it suitable for pixel shaders and cellular automaton-style graphics programs.

---

## Grammar

```
<program>          := <toplevel> { <toplevel> }
<toplevel>         := <function> | <define> | <texture>
<define>           := DEFINE STRING INT | DEFINE STRING FLOAT
<texture>          := TEXTURE STRING QUOTED STRING QUOTED
<function>         := STRING STRING LPAREN [<param>] RPAREN LBRACE <statements> RBRACE
<param>            := STRING STRING { COMMA STRING STRING }
<statements>       := { <statement> }
<statement>        := <if> | <while> | <for> | <declaration> | <assign> 
                    | <blockstatement> | <functioncallstmt> | <return>
<if>               := if LPAREN <booleanExprA> RPAREN <statement>
<while>            := while LPAREN <booleanExprA> RPAREN <statement>
<for>              := for LPAREN <declaration> <booleanExprA> SEMI <assign> RPAREN <statement>
<return>           := return [<booleanExprA>] SEMI
<assign>           := STRING EQUALASSIGN <booleanExprA> SEMI
                    | STRING DOT STRING EQUALASSIGN <booleanExprA> SEMI
<declaration>      := STRING STRING [EQUALASSIGN <booleanExprA>] SEMI
<functioncallstmt> := <functioncall> SEMI
<functioncall>     := STRING LPAREN [<args>] RPAREN
<args>             := <booleanExprA> { COMMA <booleanExprA> }
<blockstatement>   := LBRACE <statements> RBRACE
<booleanExprA>     := <booleanExprB> { (AND | OR) <booleanExprB> }
<booleanExprB>     := <term> { (NE | EE | GR | GRE | LT | LTE) <term> }
<term>             := <expr> { (PLUS | MINUS) <expr> }
<expr>             := <factor> { (MULTIPLY | DIVIDE | MOD) <factor> }
<factor>           := <element> | LPAREN <booleanExprA> RPAREN
<element>          := STRING | STRING DOT STRING | FLOAT | INT 
                    | QUOTED STRING QUOTED | <functioncall>
```

---

## Types

| Type | Description |
|---|---|
| `float` | Floating point number |
| `int` | Integer number |
| `bool` | Boolean value (`true` or `false`) |
| `string` | String literal |
| `vector3` | RGB vector with `.r`, `.g`, `.b` components |

---

## Built-in Functions

| Function | Parameters | Returns | Description |
|---|---|---|---|
| `print` | `string, float` | `void` | Prints a value to stdout |
| `abs` | `float` | `float` | Absolute value |
| `sqrt` | `float` | `float` | Square root |
| `pow` | `float, float` | `float` | Power function |
| `vector3` | `float, float, float` | `vector3` | Creates a vector3 from r, g, b components |
| `getTextureColor` | `string, float, float` | `vector3` | Samples a texture at given coordinates |

---

## Built-in Constants

| Constant | Type | Description |
|---|---|---|
| `MOUSE_X` | `float` | Current mouse X position |
| `MOUSE_Y` | `float` | Current mouse Y position |
| `CENTER_X` | `float` | Center X of the canvas |
| `CENTER_Y` | `float` | Center Y of the canvas |
| `MIN_X` | `float` | Minimum X of the canvas |
| `MIN_Y` | `float` | Minimum Y of the canvas |
| `MAX_X` | `float` | Maximum X of the canvas |
| `true` | `bool` | Boolean true |
| `false` | `bool` | Boolean false |

---

## Example Program

```
vector3 cellCode()
{
    float x = MOUSE_X + 1.0;
    float y = MOUSE_Y + 1.0;
    vector3 color = vector3(0.0, 0.0, 0.0);

    for(float i = 0.0; i < 10.0; i = i + 1.0)
    {
        color.r = color.r + x;
        color.g = color.g + y;
    }

    return vector3(color.r, color.g, color.b);
}
```

---

## Project Structure

```
.
├── Scanner.h / Scanner.cpp       # Tokenizer — converts source text into tokens
├── Parser.h / Parser.cpp         # Recursive descent parser — builds the AST
├── AST.h / AST.cpp               # AST node definitions, typechecker, and code generator
├── Type.h                        # Type enum used by the typechecker
├── Interpreter.java              # Java-based interpreter that executes the IR
├── Register.java                 # Register class used by the interpreter
└── README.md
```

---

## Pipeline

```
Source File (.txt)
      ↓
   Scanner          tokenizes the source into a stream of tokens
      ↓
   Parser           recursive descent parser builds an AST
      ↓
  Typechecker       walks the AST and verifies type correctness
      ↓
 Code Generator     walks the AST and emits a flat token-stream IR to input.txt
      ↓
  Interpreter       Java program reads input.txt and executes the IR
```

---

## How to Build and Run

### Compile the C++ compiler
```bash
g++ -o mycompiler main.cpp Parser.cpp AST.cpp Scanner.cpp -std=c++17
```

### Run the compiler on a source file
```bash
./mycompiler yourprogram.txt
```

This will produce `input.txt` containing the IR.

### Compile and run the interpreter
```bash
javac Interpreter.java
java Interpreter
```

---

## Entry Point

Every program must define a `cellCode` function with no parameters that returns a `vector3`. This is the shader entry point — it is called once per pixel and its return value is the color of that pixel.

```
vector3 cellCode()
{
    return vector3(1.0, 0.0, 0.0);  // returns red
}
```

---

## Language Features

- **Arithmetic** — `+`, `-`, `*`, `/`, `%`
- **Comparisons** — `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Boolean logic** — `&&`, `||`, `!`
- **Control flow** — `if`, `while`, `for`
- **Functions** — user-defined functions with typed parameters and return values
- **Vector3** — built-in RGB vector type with component access via `.r`, `.g`, `.b`
- **Textures** — load textures with `#text` and sample them with `getTextureColor`
- **Defines** — compile-time constants with `#def`
- **Type checking** — full static type checking with helpful error messages
