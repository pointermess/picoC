#pragma once
#include <string>
#include <memory>

enum CompileOptimizationLevel
{
    O1,
    O2,
    O3,
    O4,
    O0
};

namespace PicoC
{

    class CompilerOptions
    {
    public:
        std::string OutputPath;
        std::string OutputBinaryFileName;

        std::string InputFilePath;

        CompileOptimizationLevel OptimizationLevel;

        void SetDefaults()
        {
            OptimizationLevel = O0;

            InputFilePath = "C:\\test\\input.pc";

            OutputPath = "C:\\test\\";
            OutputBinaryFileName = "%projectname%.fae";
        }
    };

    typedef std::shared_ptr<CompilerOptions> CompilerOptionsPtr;
}