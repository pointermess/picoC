#pragma once
#include <string>
#include <vector>
#include <memory>
namespace PicoC
{
    namespace Generator
    {
        struct AssemblyLine
        {
        private:

        public:

            std::string Instruction;
            std::string Argument1;
            std::string Argument2;
            std::string GetLine();
        };

        class ProgramAssembly
        {
        public:
            std::vector<AssemblyLine> Lines;
            bool KeepInsertIndexAtEnd = true;
            int InsertIndex = 0;
            
            void InsertLine(std::string instruction, std::string argument1 = "", std::string argument2 = "");
            void AppendLine(std::string instruction, std::string argument1 = "", std::string argument2 = "");

            
        };

        typedef std::shared_ptr<ProgramAssembly> ProgramAssemblyPtr;

    }
}
