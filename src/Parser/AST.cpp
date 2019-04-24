/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "AST.h"

void PicoC::Parser::ASTBlockElement::AddChildren(ASTElementPtr item)
{
    item->SetParent(this);
    Children.push_back(item);
}

void PicoC::Parser::ASTBlockElement::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());
    for (ASTElementPtr& element : Children)
    {
        element->PrintDebug(prependSpaces + 4);
    }
}

void PicoC::Parser::ASTIdentifierExpression::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*sName: %s\n", prependSpaces + 3, "", Name.c_str());
}

void PicoC::Parser::ASTFunctionDeclaration::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());

    Type->PrintDebug(prependSpaces + 4);
    Identifier->PrintDebug(prependSpaces + 4);
    Body->PrintDebug(prependSpaces + 4);
}

void PicoC::Parser::ASTParenthesizedExpression::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());
    Expression->PrintDebug(prependSpaces + 4);
}

void PicoC::Parser::ASTNumericLiteralExperssion::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*sNumber: %u", prependSpaces + 3, "", Number);
}

void PicoC::Parser::ASTVariableDeclaration::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());
    Type->PrintDebug(prependSpaces + 4);
    Identifier->PrintDebug(prependSpaces + 4);
}

void PicoC::Parser::ASTTypeExpression::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());


    printf("%*sSigned: ", prependSpaces + 3, "");
    if (Signed)
        printf("True\n");
    else
        printf("False\n");

    printf("%*sData Type: %s\n", prependSpaces + 3, "", DataType.c_str());


    printf("%*sPointer Type: ", prependSpaces + 3, "");
    if (PointerType == ptNone)
        printf("None\n");
    else if (PointerType == ptPointer)
        printf("Pointer\n");
    else
        printf("Reference\n");
}

void PicoC::Parser::ASTProgram::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());
    for (ASTElementPtr& element : Children)
    {
        element->PrintDebug(prependSpaces + 4);
    }
}

void PicoC::Parser::ASTBinaryExpression::PrintDebug(int prependSpaces)
{
    printf("%*s|- %s\n", prependSpaces, "", ElementType.c_str());
    Left->PrintDebug(prependSpaces + 4);
    Right->PrintDebug(prependSpaces + 4);
}

void PicoC::Parser::ASTExpression::PrintDebug(int prependSpaces)
{
}
