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
unsigned int main()
{
  char a = (32+(10*8)-13);
  unsigned int& b;
  short* c;
  bool d = a >= 50;
  
  if (d && a > 66)
  {
    bool e = a + (d - 420);
  }
}
char& e;
```

#### Abstract Syntax Tree
```
+ ASTProgram
  > Children:
    + ASTFunctionDeclaration
      > Type:
        + ASTTypeExpression
          > Signed: False
          > Data Type: int
          > Pointer Type: None
      > Identifier:
        + ASTIdentifierExpression
          > Name: main
      > Body:
        + BlockElement
            + ASTVariableDeclaration
              > Type:
                + ASTTypeExpression
                  > Signed: True
                  > Data Type: char
                  > Pointer Type: None
              > Identifier:
                + ASTIdentifierExpression
                  > Name: a
              > Initialization:
                + ASTParenthesizedExpression
                    + ASTBinaryExpression
                      > Operator: +
                      > Left:
                        + ASTNumericLiteralExperssion
                          > Number: 32
                      > Right:
                        + ASTBinaryExpression
                          > Operator: -
                          > Left:
                            + ASTParenthesizedExpression
                                + ASTBinaryExpression
                                  > Operator: *
                                  > Left:
                                    + ASTNumericLiteralExperssion
                                      > Number: 10
                                  > Right:
                                    + ASTNumericLiteralExperssion
                                      > Number: 8
                          > Right:
                            + ASTNumericLiteralExperssion
                              > Number: 13
            + ASTVariableDeclaration
              > Type:
                + ASTTypeExpression
                  > Signed: False
                  > Data Type: int
                  > Pointer Type: Reference
              > Identifier:
                + ASTIdentifierExpression
                  > Name: b
            + ASTVariableDeclaration
              > Type:
                + ASTTypeExpression
                  > Signed: True
                  > Data Type: short
                  > Pointer Type: Pointer
              > Identifier:
                + ASTIdentifierExpression
                  > Name: c
            + ASTVariableDeclaration
              > Type:
                + ASTTypeExpression
                  > Signed: True
                  > Data Type: bool
                  > Pointer Type: None
              > Identifier:
                + ASTIdentifierExpression
                  > Name: d
              > Initialization:
                + ASTBinaryExpression
                  > Operator: >=
                  > Left:
                    + ASTIdentifierExpression
                      > Name: a
                  > Right:
                    + ASTNumericLiteralExperssion
                      > Number: 50
            + ASTIfStatement
              > Condition:
                + ASTBinaryExpression
                  > Operator: &&
                  > Left:
                    + ASTIdentifierExpression
                      > Name: d
                  > Right:
                    + ASTBinaryExpression
                      > Operator: >
                      > Left:
                        + ASTIdentifierExpression
                          > Name: a
                      > Right:
                        + ASTNumericLiteralExperssion
                          > Number: 66
              > Children:
                + ASTVariableDeclaration
                  > Type:
                    + ASTTypeExpression
                      > Signed: True
                      > Data Type: bool
                      > Pointer Type: None
                  > Identifier:
                    + ASTIdentifierExpression
                      > Name: e
                  > Initialization:
                    + ASTBinaryExpression
                      > Operator: +
                      > Left:
                        + ASTIdentifierExpression
                          > Name: a
                      > Right:
                        + ASTParenthesizedExpression
                            + ASTBinaryExpression
                              > Operator: -
                              > Left:
                                + ASTIdentifierExpression
                                  > Name: d
                              > Right:
                                + ASTNumericLiteralExperssion
                                  > Number: 420
    + ASTVariableDeclaration
      > Type:
        + ASTTypeExpression
          > Signed: True
          > Data Type: char
          > Pointer Type: Reference
      > Identifier:
        + ASTIdentifierExpression
          > Name: e
```
