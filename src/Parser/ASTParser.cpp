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

bool PicoC::Parser::ASTParser::_TryTypeExpression(TokenizerPtr tokenizer,  int & skipped)
{
    bool result = false;
    bool signedSet = false;

    Token token = tokenizer->GetNextToken(skipped++);

    if (token.Type == ttTypeUnsigned || token.Type == ttTypeSigned)
    {
        token = tokenizer->GetNextToken(skipped++);
        signedSet = true;
    }

    if ((token.Type >= ttTypeVoid && token.Type <= ttTypeInt) || (token.Type == ttIdentifier && signedSet == false))
        result = true;

    return result;
}

bool PicoC::Parser::ASTParser::_TryFunctionDeclaration(TokenizerPtr tokenizer,  int & skipped)
{
    bool result = false;

    if (_TryTypeExpression(tokenizer, skipped))
    {
        Token token = tokenizer->GetNextToken(skipped++);
        if (token.Type == ttIdentifier)
        {
            token = tokenizer->GetNextToken(skipped++);
            return (token.Type == ttSymbolLeftBracket);
        }
    }

    return result;
}

bool PicoC::Parser::ASTParser::_TryAndParseNextSection(TokenizerPtr tokenizer, ASTProgramPtr program)
{
    int skipped = 0;

    if (_TryFunctionDeclaration(tokenizer, skipped))
    {
        auto functionDeclaration = std::make_shared<ASTFunctionDeclaration>();
        ParseFunctionDeclaration(tokenizer, program, functionDeclaration);
        return true;
    }

    return false;
}

PicoC::Parser::ASTParser::ASTParser()
{
    State = std::make_shared<ASTParserState>();
}

bool ASTParser::ParseProgram(TokenizerPtr tokenizer, ASTProgramPtr program)
 {
    int skipped = 0;
    while (tokenizer->IsInRange())
    {
        skipped = 0;

        if (_TryFunctionDeclaration(tokenizer, skipped))
        {
            auto functionDeclaration = std::make_shared<ASTFunctionDeclaration>();
            ParseFunctionDeclaration(tokenizer, program, functionDeclaration);
        }
    }

    return false;
 }

bool PicoC::Parser::ASTParser::ParseFunctionDeclaration(TokenizerPtr tokenizer, ASTProgramPtr program, ASTFunctionDeclarationPtr expression)
{
    // prepare type expression object and assign to fuinction declaration expression;
    auto typeExpression = std::make_shared<ASTTypeExpression>();
    expression->Type = typeExpression;

    // parse type expression
    ParseTypeExpression(tokenizer, typeExpression);

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
                ASTVariableDeclarationPtr argument = std::make_shared<ASTVariableDeclaration>();
                if (ParseVariableDeclaration(tokenizer, argument))
                {
                    expression->Arguments.push_back(argument);
                    tokenizer->NextToken();
                }
                else
                {
                    // todo: log error
                    return false;
                }
            } while (token.Type == ttSymbolComma);
        }
    }
    else
    {
        // todo: log error
        return false;
    }

    if (token.Type == ttSymbolRightBracket)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
        if (token.Type == ttSymbolLeftCurlyBracket)
        {
            ParseBlock(tokenizer, expression->Body);
        }
    }
    return true;
}

bool PicoC::Parser::ASTParser::ParseBlock(TokenizerPtr tokenizer, ASTBlockElementPtr block)
{
    return false;
}

bool ASTParser::ParseExpression(TokenizerPtr tokenizer, ASTExpressionPtr expression)
{
    // generic experssion  parser method
    // single value

    // check if current expression might be a binary expression
    Token token = tokenizer->GetNextToken();
    if (token.Type == ttSymbolAnd)

    token = tokenizer->GetCurrentToken();
    if (token.Type == ttConstDec)
    {
        expression = std::make_shared<ASTNumericLiteralExperssion>();
        std::static_pointer_cast<ASTNumericLiteralExperssion>(expression)->Number = parse_number(token.Value);
    }
    else if (token.Type == ttSymbolLeftBracket)
    {
        expression = std::make_shared<ASTParenthesizedExpression>();
        ParseExpression(tokenizer, std::static_pointer_cast<ASTParenthesizedExpression>(expression)->Expression);
    }
    else
    {
        // todo: log error
        return false;
    }
}

bool PicoC::Parser::ASTParser::ParseTypeExpression(TokenizerPtr tokenizer, ASTTypeExpressionPtr expression)
{
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
    }
    else
    {
        // todo: log error
        return false;
    }

    tokenizer->NextToken();
    return true;
}

bool ASTParser::ParseBinaryExpression(TokenizerPtr tokenizer, ASTBinaryExpressionPtr expression)
{
    return false;
}

bool PicoC::Parser::ASTParser::ParseVariableDeclaration(TokenizerPtr tokenizer, ASTVariableDeclarationPtr expression)
{
    if (ParseTypeExpression(tokenizer, expression->Type))
    {
        Token token = tokenizer->GetCurrentToken();

        if (token.Type == ttIdentifier)
        {
            expression->Identifier = std::make_shared<ASTIdentifierExpression>();
            expression->Identifier->Name = token.Value;
        }
        else
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
}
