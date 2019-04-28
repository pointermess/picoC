/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "./picoC/Parser/Tokenizer.h"
#include "./picoC/Parser/ASTParser.h"
#include "./picoC/Utilities.h"
#include "picoC/Representation/LookupTable.h"

#include <iostream>
#include <exception>
#include <math.h>
#include <memory>

using namespace PicoC;
using namespace PicoC::Parser;
int main()
{
    auto test = std::make_shared<LookupTable<int>>();
    test->Add("test", 1);
    int a = 0;
    bool found = test->Find("test", a);

    std::cout << "Hello World!\n"; 

    auto tokenizer = std::make_shared<Tokenizer>();
    auto source = read_file("C:\\Users\\Milos\\hello_world.pc");
    tokenizer->Tokenize(source);

    auto astParser = std::make_shared<ASTParser>();
    auto astProgram = std::make_shared<ASTProgram>();


    astParser->ParseProgram(tokenizer, astProgram);
    astProgram->PrintDebug();
}