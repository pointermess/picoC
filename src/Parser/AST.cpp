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
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    for (ASTElementPtr& element : Children)
    {
        element->PrintDebug(prependSpaces + 4);
    }
}

void PicoC::Parser::ASTIdentifierExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*s  > Name: %s\n", prependSpaces, "", Name.c_str());
}

void PicoC::Parser::ASTFunctionDeclaration::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());

    printf("%*s  > Arguments:\n", prependSpaces, "");
    for (ASTVariableDeclarationPtr& element : Arguments)
    {
        element->PrintDebug(prependSpaces + 4);
    }

    printf("%*s  > Type:\n", prependSpaces, "");
    Type->PrintDebug(prependSpaces + 4);
    printf("%*s  > Identifier:\n", prependSpaces, "");
    Identifier->PrintDebug(prependSpaces + 4);
    printf("%*s  > Body:\n", prependSpaces, "");
    Body->PrintDebug(prependSpaces + 4);
}

void PicoC::Parser::ASTParenthesizedExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    Expression->PrintDebug(prependSpaces + 4);
}

void PicoC::Parser::ASTNumericLiteralExperssion::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*s  > Number: %u\n", prependSpaces, "", Number);
}

void PicoC::Parser::ASTVariableDeclaration::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*s  > Type:\n", prependSpaces, "");
    Type->PrintDebug(prependSpaces + 4);
    printf("%*s  > Identifier:\n", prependSpaces, "");
    Identifier->PrintDebug(prependSpaces + 4);
    if (Initialization != NULL)
    {
        printf("%*s  > Initialization:\n", prependSpaces, "");
        Initialization->PrintDebug(prependSpaces + 4);
    }
}

void PicoC::Parser::ASTTypeExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());


    printf("%*s  > Signed: ", prependSpaces, "");
    if (Signed)
        printf("True\n");
    else
        printf("False\n");

    printf("%*s  > Data Type: %s\n", prependSpaces, "", DataType.c_str());


    printf("%*s  > Pointer Type: ", prependSpaces, "");
    if (PointerType == ptNone)
        printf("None\n");
    else if (PointerType == ptPointer)
        printf("Pointer\n");
    else
        printf("Reference\n");
}

void PicoC::Parser::ASTProgram::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());

    printf("%*s  > Children:\n", prependSpaces, "");
    for (ASTElementPtr& element : Children)
    {
        element->PrintDebug(prependSpaces + 4);
    }
}

void PicoC::Parser::ASTBinaryExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*s  > Operator: %s\n", prependSpaces, "", Operator.c_str());

    printf("%*s  > Left:\n", prependSpaces, "");
    Left->PrintDebug(prependSpaces + 4);
    printf("%*s  > Right:\n", prependSpaces, "");
    Right->PrintDebug(prependSpaces + 4);
}

void PicoC::Parser::ASTExpression::PrintDebug(int prependSpaces)
{
}

void PicoC::Parser::ASTIfStatement::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());

    printf("%*s  > Condition:\n", prependSpaces, "");
    Condition->PrintDebug(prependSpaces + 4);

    printf("%*s  > Children:\n", prependSpaces, "");
    for (ASTElementPtr& element : Children)
    {
        element->PrintDebug(prependSpaces + 4);
    }
}
