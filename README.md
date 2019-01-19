# picoC

*This repository will contain a learning project and is currently only in planning phase.*

picoC is a very small and low-level language based on C which only contains minimal language features such as functions and variables. Its only target platform is my [FlexRTE](https://github.com/pointermess/FlexRTE-X).

The goal of this language is to provide an easy way to write FlexRTE applications without the need of writing only low-level [FlexASM](https://github.com/pointermess/FlexASM-Compiler). It should also be kept as simple as possible as a I'd like to write a more complex compiler in the future.

### Planned features
- Global & Local Variables:
    - const, pointers/references
    - uint8_t, uint16_t, uint32_t
    - int8_t, int16_t, int32_t
    - bool
    - Arrays / Strings
- Functions
    - Arguments
    - Return value
- Inline-Assembler
    - With support of picoC variables

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
