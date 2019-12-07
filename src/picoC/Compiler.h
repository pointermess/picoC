#pragma once

#include <string>

#include "CompilerResult.h"
#include "./Utilities.h"
#include "./Parser/Tokenizer.h"
#include "./Parser/ASTParser.h"
#include "./Generator/CodeGenerator.h"
#include "./Representation/AST.h"
#include "./Representation/ProgramStruct.h"

using namespace PicoC::Representation;
using namespace PicoC::Parser;

namespace PicoC
{
    struct CompilerSettings
    {
    public:
        enum OptimizerLevel { O0, O1, O2, O3, O4 };

        OptimizerLevel OptimizerLevel = O4;
        std::string InputFile;
        std::string OutputFile;
    };

    enum CompilerStateType { Waiting, Running, Failed, Successful };
    class CompilerState
    {
    private:
    public:
        CompilerStateType Type;

        ASTProgramPtr Program;

        ProgramStructPtr ProgramStruct;
        std::vector<std::string> Output;

        std::vector<CompilerHint> Hints;
        void AddHint(CompilerHintType type, const std::string& message);
    };

    class Compiler
    {
    private:
        std::shared_ptr<CompilerState> _State;
    public:
        CompilerSettings Settings;

        Compiler();

        void Compile();
    };
}

