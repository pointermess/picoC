/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "AST.h"

void PicoC::Representation::ASTBlockElement::AddChildren(ASTElementPtr item)
{
    item->SetParent(this);
    Children.push_back(item);
}

void PicoC::Representation::ASTBlockElement::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    for (ASTElementPtr& element : Children)
    {
        element->PrintDebug(prependSpaces + 4);
    }
}

void PicoC::Representation::ASTIdentifierExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*s  > Name: %s\n", prependSpaces, "", Name.c_str());
}

std::string PicoC::Representation::ASTFunctionDeclaration::GetCallingName()
{
    std::string name = GetFunctionName() + "(";


    for (ASTVariableDeclarationPtr& arg : Arguments)
    {
        name += "_" + arg->Type->GetTypeName();
    }

    return name + ")";
}

std::string PicoC::Representation::ASTFunctionDeclaration::GetFunctionName()
{
    return Identifier->Name;
}

void PicoC::Representation::ASTFunctionDeclaration::PrintDebug(int prependSpaces)
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

void PicoC::Representation::ASTParenthesizedExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    Expression->PrintDebug(prependSpaces + 4);
}

void PicoC::Representation::ASTNumericLiteralExperssion::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*s  > Number: %u\n", prependSpaces, "", Number);
}

void PicoC::Representation::ASTVariableDeclaration::PrintDebug(int prependSpaces)
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

std::string PicoC::Representation::ASTTypeExpression::GetTypeName()
{
    return DataType;
}

void PicoC::Representation::ASTTypeExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());


    printf("%*s  > Signed: ", prependSpaces, "");
    if (Signed)
        printf("True\n");
    else
        printf("False\n");

    printf("%*s  > Data Type: %s\n", prependSpaces, "", DataType.c_str());



}



void PicoC::Representation::ASTProgram::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());

    printf("%*s  > Children:\n", prependSpaces, "");
    for (ASTElementPtr& element : Children)
    {
        element->PrintDebug(prependSpaces + 4);
    }
}

void PicoC::Representation::ASTBinaryExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());
    printf("%*s  > Operator: %s\n", prependSpaces, "", Operator.c_str());

    printf("%*s  > Left:\n", prependSpaces, "");
    Left->PrintDebug(prependSpaces + 4);
    printf("%*s  > Right:\n", prependSpaces, "");
    Right->PrintDebug(prependSpaces + 4);
}

void PicoC::Representation::ASTExpression::PrintDebug(int prependSpaces)
{
}

void PicoC::Representation::ASTIfStatement::PrintDebug(int prependSpaces)
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

std::string PicoC::Representation::ASTTypePointerExpression::GetTypeName()
{
    return Element->GetTypeName() + "*";
}

void PicoC::Representation::ASTTypePointerExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());

    printf("%*s  > Signed: ", prependSpaces, "");
    if (Type == ptReference)
        printf("Reference\n");
    else if (Type == ptPointer)
        printf("Pointer\n");
    else
        printf("None\n");

    printf("%*s  > Element:\n", prependSpaces, "");
    Element->PrintDebug(prependSpaces + 4);
}

void PicoC::Representation::ASTFunctionCallExpression::PrintDebug(int prependSpaces)
{
    printf("%*s+ %s\n", prependSpaces, "", ElementType.c_str());

    printf("%*s  > Identifier:\n", prependSpaces, "");
    Identifier->PrintDebug(prependSpaces + 4);

    printf("%*s  > Arguments:\n", prependSpaces, "");
    for (ASTExpressionPtr& argument : Arguments)
    {
        argument->PrintDebug(prependSpaces + 4);
    }
}
