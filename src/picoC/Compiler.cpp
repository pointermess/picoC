#include "Compiler.h"
#include "Utilities.h"

PicoC::Compiler::Compiler()
{
    Options = std::make_shared<CompilerOptions>();
    Options->SetDefaults();

    Result = std::make_shared<CompilerResult>();
    Result->AddHint({ Warning, 0, 0, "test" }); 
}

PicoC::Compiler::~Compiler()
{
    
}

bool PicoC::Compiler::Compile()
{
    // initiate tokenizer and read input file
    _tokenizer = std::make_shared<Tokenizer>();
    const std::string source = read_file(Options->InputFilePath);
    _tokenizer->Tokenize(source);

    for (auto token : _tokenizer->Tokens)
    {
        printf("%s\n", token.Value.c_str());
    }

    return false;
}
