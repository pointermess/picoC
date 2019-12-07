#pragma once

#include "LookupTable.h"

#include <memory>
#include <vector>

#include "AST.h"
#include "../Types.h"

namespace PicoC
{
    namespace Representation
    {
        class ProgramScope; 
        class ProgramObjectBase
        {
        public:
            std::shared_ptr<ProgramScope> Parent;
        };

        class VariableDeclaration : public ProgramObjectBase
        {
        private:
            ASTVariableDeclarationPtr ASTObject;

            MemorySize GetMemorySize();
        };
        typedef std::shared_ptr<VariableDeclaration> VariableDeclarationPtr;
        typedef LookupTable<VariableDeclarationPtr> VariableDeclarationLookupTable;


        class ProgramScope : public ProgramObjectBase
        {
        public:
            VariableDeclarationLookupTable Variables;
            std::vector<std::shared_ptr<ProgramScope>> Children; 
        };

        class ProgramFunction : public ProgramScope
        {
        public:
            ASTFunctionDeclarationPtr ASTObject;
        };
        typedef std::shared_ptr<ProgramFunction> ProgramFunctionPtr;
        typedef LookupTable<ProgramFunctionPtr> ProgramFunctionLookupTable;

        class ProgramStruct : public ProgramScope
        {
        public:
            ProgramFunctionLookupTable Functions;
            ASTProgramPtr ASTObject;
        };
        typedef std::shared_ptr<ProgramStruct> ProgramStructPtr;
    }
}
