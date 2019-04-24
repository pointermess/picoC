/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <memory>
#include "ASTParser.h"
#include "../Utilities.h"
using namespace PicoC;
using namespace PicoC::Parser;



PicoC::Parser::ASTParser::ASTParser()
{
    State = std::make_shared<ASTParserState>();
}

bool ASTParser::ParseProgram(TokenizerPtr tokenizer, ASTProgramPtr& program)
{
    int skipped = 0;
    while (tokenizer->IsInRange())
    {
        skipped = 0;


        ASTElementPtr element;
        ASTFunctionDeclarationPtr functionDeclaration;
        ASTVariableDeclarationPtr variableDeclaration;

        if (ParseFunctionDeclaration(tokenizer, program, functionDeclaration))
        {
            program->Children.push_back(functionDeclaration);
        }
        else if (ParseVariableDeclaration(tokenizer, variableDeclaration))
        {
            program->Children.push_back(variableDeclaration);
        }
        else
        {
            break;
        }
    }

    return true;
 }

bool PicoC::Parser::ASTParser::ParseFunctionDeclaration(TokenizerPtr tokenizer, ASTProgramPtr program, ASTFunctionDeclarationPtr& expression)
{
    tokenizer->Remember();
    expression = std::make_shared<ASTFunctionDeclaration>();

    // prepare type expression object and assign to fuinction declaration expression;
    ASTTypeExpressionPtr typeExpression;

    // parse type expression
    ParseTypeExpression(tokenizer, typeExpression);
    expression->Type = typeExpression;

    // parse function name
    Token token = tokenizer->GetCurrentToken();
    if (token.Type == ttIdentifier)
    {
        expression->Identifier = std::make_shared<ASTIdentifierExpression>();
        expression->Identifier->Name = token.Value;
    }
    else
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }


    // parse arguments
    tokenizer->NextToken();
    token = tokenizer->GetCurrentToken();

    // parse arguments
    if (token.Type == ttSymbolLeftBracket)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();

        // skip arguments if function already ends
        if (token.Type != ttSymbolRightBracket)
        {
            do
            {
                ASTVariableDeclarationPtr argument;
                if (ParseVariableDeclaration(tokenizer, argument))
                {
                    expression->Arguments.push_back(argument);
                    tokenizer->NextToken();
                }
                else
                {
                    // todo: log error
                    tokenizer->Reset();
                    return false;
                }
            } while (token.Type == ttSymbolComma);
        }
    }
    else
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }

    if (token.Type == ttSymbolRightBracket)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
        if (token.Type == ttSymbolLeftCurlyBracket)
        {
            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();
            if (ParseBlock(tokenizer, expression->Body))
            {
                token = tokenizer->GetCurrentToken();
                if (token.Type != ttSymbolRightCurlyBracket)
                {
                    // todo: log error
                    tokenizer->Reset();
                    return false;
                }
            }
            else
            {
                // todo: log error
                tokenizer->Reset();
                return false;
            }
        }
    }
    tokenizer->NextToken();
    return true;
}

bool PicoC::Parser::ASTParser::ParseBlock(TokenizerPtr tokenizer, ASTBlockElementPtr& block)
{
    block = std::make_shared<ASTBlockElement>();

    Token token = tokenizer->GetCurrentToken();

    do
    {
        ASTElementPtr element;
        ASTVariableDeclarationPtr variableDeclaration;

        if (ParseVariableDeclaration(tokenizer, variableDeclaration))
        {
            block->Children.push_back(variableDeclaration);
        }
        else
        {
            break;
        }

        token = tokenizer->GetCurrentToken();
    } while (token.Type != ttSymbolRightCurlyBracket);

    return true;
}

bool ASTParser::ParseExpression(TokenizerPtr tokenizer, ASTExpressionPtr& expression)
{
    // generic experssion  parser method
    // single value

    ASTExpressionPtr tempExpression;

    // check if current expression might be a binary expression
    Token token = tokenizer->GetNextToken();

    token = tokenizer->GetCurrentToken();
    if (token.Type == ttConstDec)
    {
        expression = std::make_shared<ASTNumericLiteralExperssion>();
        std::static_pointer_cast<ASTNumericLiteralExperssion>(expression)->Number = parse_number(token.Value);
    }
    else if (token.Type == ttSymbolLeftBracket)
    {
        tokenizer->NextToken();

        expression = std::make_shared<ASTParenthesizedExpression>();
        ParseExpression(tokenizer, std::static_pointer_cast<ASTParenthesizedExpression>(expression)->Expression);

        token = tokenizer->GetCurrentToken();
        if (token.Type != ttSymbolRightBracket)
        {
            // todo: log error
            return false;
        }
    }
    else
    {
        // todo: log error
        return false;
    }

    // check if current expression might be a binary expression
    tokenizer->NextToken();

    if (tokenizer->IsInRange())
    {
        token = tokenizer->GetCurrentToken();

        std::set<FATokenType> binaryOperators = {
            ttSymbolPlus,
            ttSymbolDash,
            ttSymbolAsteriks,
            ttSymbolForwardSlash,
            ttSymbolAnd,
            ttSymbolOr,
            ttSymbolEquals,
            ttSymbolNotEquals
        };

        if (in_set<FATokenType>(binaryOperators, token.Type))
        {
            ASTExpressionPtr secondExpression;
            ParseExpression(tokenizer, secondExpression);

            ASTBinaryExpressionPtr binaryExpression = std::make_shared<ASTBinaryExpression>();
            binaryExpression->Left = expression;
            binaryExpression->Right = secondExpression;


            expression = binaryExpression;
        }
    }
}


bool PicoC::Parser::ASTParser::ParseTypeExpression(TokenizerPtr tokenizer, ASTTypeExpressionPtr& expression)
{
    tokenizer->Remember();
    expression = std::make_shared< ASTTypeExpression>();

    bool signedSet = false;

    Token token = tokenizer->GetCurrentToken();

    if (token.Type == ttTypeUnsigned || token.Type == ttTypeSigned)
    {
        signedSet = true;
        if (token.Type == ttTypeUnsigned)
            expression->Signed = false;

        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }

    if ((token.Type >= ttTypeVoid && token.Type <= ttTypeInt) || (token.Type == ttIdentifier && signedSet == false))
    {
        expression->DataType = token.Value;
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }
    else
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }

    if (token.Type == ttSymbolAsteriks)
    {
        expression->PointerType = ptPointer;
        tokenizer->NextToken();
    }
    else if (token.Type == ttSymbolCommercialAnd)
    {
        expression->PointerType = ptReference;
        tokenizer->NextToken();
    }

    return true;
}

bool ASTParser::ParseBinaryExpression(TokenizerPtr tokenizer, ASTBinaryExpressionPtr& expression)
{
    return false;
}

bool PicoC::Parser::ASTParser::ParseVariableDeclaration(TokenizerPtr tokenizer, ASTVariableDeclarationPtr& expression)
{
    tokenizer->Remember();
    expression = std::make_shared< ASTVariableDeclaration>();

    Token token;

    if (ParseTypeExpression(tokenizer, expression->Type))
    {
        token = tokenizer->GetCurrentToken();

        if (token.Type == ttIdentifier)
        {
            expression->Identifier = std::make_shared<ASTIdentifierExpression>();
            expression->Identifier->Name = token.Value;

            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();
        }
        else
        {
            // todo: log error
            tokenizer->Reset();
            return false;
        }
    }
    else
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }


    if (token.Type == ttSymbolDefine || token.Type == ttSymbolDefinePlus || token.Type == ttSymbolDefineMinus)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }

    if (token.Type != ttSymbolSemicolon)
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }

    tokenizer->NextToken();
    return true;
}
