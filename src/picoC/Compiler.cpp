#include "Compiler.h"

using namespace PicoC::Representation;
using namespace PicoC::Generator;
PicoC::Compiler::Compiler()
{
    _State = std::make_shared<CompilerState>();
}

void PicoC::Compiler::Compile()
{
    // read in input file
    const std::string source = read_file(Settings.InputFile);
    


    TokenizerPtr tokenizer = std::make_shared<Tokenizer>();
    tokenizer->Tokenize(source);

    ASTParserPtr astParser = std::make_shared<ASTParser>();


    ASTProgramPtr program = std::make_shared<ASTProgram>();
    _State->Program = program;

    if (astParser->ParseProgram(tokenizer, program))
    {
        //program->ParseFunctionLookupTable();
        CodeGeneratorPtr generator = std::make_shared<CodeGenerator>(this->_State);
        generator->Generate();
    }

    program->PrintDebug(0);
}

void PicoC::CompilerState::AddHint(CompilerHintType type, const std::string & message)
{
    Hints.push_back({ type, 0, 0, message });
}
