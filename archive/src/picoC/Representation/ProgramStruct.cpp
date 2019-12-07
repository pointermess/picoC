#include "ProgramStruct.h"

using namespace PicoC;

MemorySize PicoC::Representation::VariableDeclaration::GetMemorySize()
{
    if (typeid(*ASTObject->Type) == typeid(ASTTypePointerExpression))
    {
        return msDWord;
    }
    else if (typeid(*ASTObject->Type) == typeid(ASTTypeExpression))
    {
        ASTTypeExpressionPtr type = std::static_pointer_cast<ASTTypeExpression>(ASTObject->Type);

        if (type->DataType == "int") return msDWord;
        else if (type->DataType == "short") return msWord;
        else if (type->DataType == "char") return msByte;
    }
    
    return msUnknown;
}
