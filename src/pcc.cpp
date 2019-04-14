/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "Tokenizer.h"
#include <iostream>
#include <memory>
using namespace PicoC;
int main()
{
    std::cout << "Hello World!\n"; 

    auto tokenizer = std::make_shared<Tokenizer>();
    tokenizer->Tokenize("int32_t main(){uint8_t * helloWorldStr=\"Hello World\"; println(helloWorldStr); return 0;}void println(uint8_t * str){asm{mov eax, 3 mov ebx, $str int 0x40}}");

    while (tokenizer->IsInRange())
    {
        std::cout <<  tokenizer->GetCurrentToken().Value << std::endl;
        tokenizer->NextToken();
    }
}