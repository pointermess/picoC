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
    printf("%*s", prependSpaces, ElementType.c_str());

    for (ASTElementPtr& element : Children)
    {

    }
}

void PicoC::Parser::ASTIdentifierExpression::PrintDebug(int prependSpaces)
{
}

void PicoC::Parser::ASTFunctionDeclaration::PrintDebug(int prependSpaces)
{
}

void PicoC::Parser::ASTParenthesizedExpression::PrintDebug(int prependSpaces)
{
}

void PicoC::Parser::ASTNumericLiteralExperssion::PrintDebug(int prependSpaces)
{
}

void PicoC::Parser::ASTVariableDeclaration::PrintDebug(int prependSpaces)
{
}
