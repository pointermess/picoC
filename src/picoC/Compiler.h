#pragma once
#include <memory>
#include <string>
#include <vector>

#include "CompilerResult.h"
#include "compileoptions.h"
#include "Parser/Tokenizer.h"
#include "Parser/Token.h"

using namespace PicoC::Representation;

namespace PicoC
{
    class Compiler
    {
    private:
        TokenizerPtr _tokenizer;
    public:
        Compiler();
        ~Compiler();


        CompilerOptionsPtr Options;
        CompilerResultPtr Result;
        bool Compile();

    };
}

