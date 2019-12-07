#include "ProgramAssembly.h"


void PicoC::Generator::ProgramAssembly::InsertLine(std::string instruction, std::string argument1, std::string argument2)
{
    Lines.insert(Lines.begin() + 1, { instruction, argument1, argument2 });
    ++InsertIndex;
}

void PicoC::Generator::ProgramAssembly::AppendLine(std::string instruction, std::string argument1, std::string argument2)
{
    Lines.push_back({ instruction, argument1, argument2 });

    if (KeepInsertIndexAtEnd)
        InsertIndex = Lines.size();
}

std::string PicoC::Generator::AssemblyLine::GetLine()
{
    std::string result = Instruction;

    if (!Argument1.empty())
        result += " " + Argument1;

    if (!Argument2.empty())
        result += ", " + Argument2;

    return result;
}
