#pragma once

#include "../Representation/AST.h"

namespace PicoC
{
    namespace Generator
    {
        class CodeOptimizerBase
        {
            virtual void Optimize(void* Object) = 0;
        };

        class CodeOptimizerAST : public CodeOptimizerBase
        {
        public:

        };

    }
}