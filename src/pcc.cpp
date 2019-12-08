#include <iostream>
#include <memory>
#include "picoC/Compiler.h"
int main()
{
    auto compiler = std::make_shared<PicoC::Compiler>();
    compiler->Compile();
}