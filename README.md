# picoC Compiler

**Disclaimer:** This project is a learning project and useless for almost everyone who visits this repository. :)

picoC is a very small and low-level language based on C which only contains minimal language features such as functions and variables. Its only target platform is my [FlexRTE](https://github.com/pointermess/FlexRTE-X) platform.

The goal of this language is to provide an easy way to write FlexRTE applications without the need of writing only low-level [FlexASM](https://github.com/pointermess/FlexASM-Compiler) code. It should also be kept as simple as possible as a I'd like to write a more complex compiler in the future.

Most picoC code will not be compatible with the C standard.

### Planned features
- Global & Local Variables:
    - const, pointers/references
    - unsigned, signed
    - char, short, int
    - bool
    - Arrays / Strings
- Functions
    - Arguments
    - Return value
- Structs
    - Defining structs containing variables
- Inline-Assembler
    - With support of picoC variables
- Compiler directives
    - #include
    - #pragma once
    - #define
    - #ifdef #ifndef #else #endif

### Examples
#### Hello World
```cpp
int32_t main()
{
  uint8_t * helloWorldStr = "Hello World";
  println(helloWorldStr);
  
  return 0;
}

void println(uint8_t * str)
{
  asm
  {
    mov eax, 3    ; print until 0
    mov ebx, $str ; inline-assembler supports picoC variables
    int 0x40      ; console system call
  }
}
```

### Current progress
- Tokenizer :heavy_check_mark: **Done**
- Abstrac Syntax Tree **Current task**

The AST parser is able to parse following picoC code int an AST:

#### picoC
```cpp
int& main()
{
  char a = (32+(10*8)-13);
  unsigned int b;
  short* c;
}
int* d;
```

#### Abstract Syntax Tree
```
|- ASTProgram
    |- FunctionDeclaration
        |- ASTTypeExpression
           Signed: True
           Data Type: int
           Pointer Type: Reference
        |- ASTIdentifierExpression
           Name: main
        |- BlockElement
            |- ASTVariableDeclaration
                |- ASTTypeExpression
                   Signed: True
                   Data Type: char
                   Pointer Type: None
                |- ASTIdentifierExpression
                   Name: a
                |- ASTParenthesizedExpression
                    |- ASTBinaryExpression
                       Operator: +
                        |- ASTNumericLiteralExperssion
                           Number: 32
                        |- ASTBinaryExpression
                           Operator: -
                            |- ASTParenthesizedExpression
                                |- ASTBinaryExpression
                                   Operator: *
                                    |- ASTNumericLiteralExperssion
                                       Number: 10
                                    |- ASTNumericLiteralExperssion
                                       Number: 8
                            |- ASTNumericLiteralExperssion
                               Number: 13
            |- ASTVariableDeclaration
                |- ASTTypeExpression
                   Signed: False
                   Data Type: int
                   Pointer Type: None
                |- ASTIdentifierExpression
                   Name: b
            |- ASTVariableDeclaration
                |- ASTTypeExpression
                   Signed: True
                   Data Type: short
                   Pointer Type: Pointer
                |- ASTIdentifierExpression
                   Name: c
    |- ASTVariableDeclaration
        |- ASTTypeExpression
           Signed: True
           Data Type: int
           Pointer Type: Pointer
        |- ASTIdentifierExpression
           Name: d
```
