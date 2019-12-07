/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "picoC/Representation/LookupTable.h"
#include "./picoC/Parser/Tokenizer.h"
#include "./picoC/Parser/ASTParser.h"
#include "./picoC/Utilities.h"
#include "./picoC/Compiler.h"

#include <iostream>
#include <exception>
#include <math.h>
#include <memory>

using namespace PicoC;
using namespace PicoC::Parser;

int main()
{
    auto compiler = std::make_shared<Compiler>();
    compiler->Settings.InputFile = "C:\\Users\\Milos\\hello_world.pc";
    compiler->Settings.OutputFile = "C:\\Users\\Milos\\hello_world.fae";
    compiler->Compile();


}