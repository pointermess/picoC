/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Tokenizer.h"
#include "./Parser/ASTParser.h"
#include "Utilities.h"
#include <iostream>
#include <math.h>
#include <memory>
using namespace PicoC;
using namespace PicoC::Parser;
int main()
{
    abs(-1);
    std::cout << "Hello World!\n"; 

    auto tokenizer = std::make_shared<Tokenizer>();
    auto source = read_file("C:\\Users\\Milos\\hello_world.pc");
    tokenizer->Tokenize(source);

    auto astParser = std::make_shared<ASTParser>();
    auto astProgram = std::make_shared<ASTProgram>();
    astParser->ParseProgram(tokenizer, astProgram);


}