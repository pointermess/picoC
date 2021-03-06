/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <memory>
#include "ASTParser.h"
#include "../Exceptions.h"
#include "../Utilities.h"
using namespace PicoC;
using namespace PicoC::Parser;



PicoC::Parser::ASTParser::ASTParser(std::shared_ptr<CompilerState> compilerState)
{
    _CompilerState = compilerState;
}

bool ASTParser::ParseProgram(TokenizerPtr tokenizer, ASTProgramPtr& program)
{
    while (tokenizer->IsInRange())
    {
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

    
    //program->ParseFunctionLookupTable();
    return true;
 }

bool PicoC::Parser::ASTParser::ParseFunctionDeclaration(TokenizerPtr tokenizer, ASTProgramPtr program, ASTFunctionDeclarationPtr& expression)
{
    tokenizer->Remember();
    expression = std::make_shared<ASTFunctionDeclaration>();

    // prepare type expression object and assign to fuinction declaration expression;
    ASTTypeElementPtr typeExpression;

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

        // parse arguments if function doesnt end
        if (token.Type != ttSymbolRightBracket)
        {
            do
            {
                ASTVariableDeclarationPtr argument;
                if (ParseVariableDeclaration(tokenizer, argument))
                {
                    expression->Arguments.push_back(argument);
                    token = tokenizer->GetCurrentToken();
                }
                else
                {
                    // todo: log error
                    tokenizer->Reset();
                    return false;
                }
            } while (tokenizer->GetNextToken(-1).Type == ttSymbolComma);
        }
        else if (token.Type == ttSymbolRightBracket)
        {
            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();
        }
    }
    else
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }

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
        ASTIfStatementPtr ifStatement;
        ASTFunctionCallExpressionPtr functionCall;

        if (ParseVariableDeclaration(tokenizer, variableDeclaration))
        {
            block->Children.push_back(variableDeclaration);
        }
        else if (ParseIfStatement(tokenizer, ifStatement))
        {
            block->Children.push_back(ifStatement);
        }
        else if (ParseFunctionCallExpression(tokenizer, functionCall))
        {
            block->Children.push_back(functionCall);
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
    tokenizer->Remember();

    // check if current expression might be a binary expression
    Token token;

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
            tokenizer->Reset();
            return false;
        }
    }
    else if (token.Type == ttIdentifier)
    {
        expression = std::make_shared<ASTIdentifierExpression>();
        std::static_pointer_cast<ASTIdentifierExpression>(expression)->Name = token.Value;
    }
    else
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }

    // check if current expression might be a binary expression
    tokenizer->NextToken();
    try
    {
        token = tokenizer->GetCurrentToken();
    }
    catch (TokenizerOutOfRangeException& e)
    {
        return true;
    }

    std::set<FATokenType> binaryOperators = {
        ttSymbolPlus,
        ttSymbolDash,
        ttSymbolAsteriks,
        ttSymbolForwardSlash,
        ttSymbolAnd,
        ttSymbolOr,
        ttSymbolEquals,
        ttSymbolNotEquals,
        ttSymbolGreater,
        ttSymbolGreaterEquals,
        ttSymbolLower,
        ttSymbolLowerEquals
    };

    if (in_set<FATokenType>(binaryOperators, token.Type))
    {
        std::string binaryOperator = token.Value;
        tokenizer->NextToken();
        ASTExpressionPtr secondExpression;
        ParseExpression(tokenizer, secondExpression);

        ASTBinaryExpressionPtr binaryExpression = std::make_shared<ASTBinaryExpression>();
        binaryExpression->Left = expression;
        binaryExpression->Right = secondExpression;
        binaryExpression->Operator = binaryOperator;

        expression = binaryExpression;
    }

    return true;
}


bool PicoC::Parser::ASTParser::ParseTypeExpression(TokenizerPtr tokenizer, ASTTypeElementPtr& expression)
{
    tokenizer->Remember();
    ASTTypeExpressionPtr typeExpression = std::make_shared<ASTTypeExpression>();

    bool signedSet = false;

    Token token = tokenizer->GetCurrentToken();

    if (token.Type == ttTypeUnsigned || token.Type == ttTypeSigned)
    {
        signedSet = true;
        if (token.Type == ttTypeUnsigned)
            typeExpression->Signed = false;

        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }

    if ((token.Type >= ttTypeVoid && token.Type <= ttTypeBool) || (token.Type == ttIdentifier && signedSet == false))
    {
        typeExpression->DataType = token.Value;
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }
    else
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }

    if (token.Type == ttSymbolAsteriks || token.Type == ttSymbolCommercialAnd)
    {
        // todo: loop to get unlimited pointers

        ASTTypePointerExpressionPtr typePtrExpression;
        ASTTypeElementPtr typeElementTemp = typeExpression;

        while (token.Type == ttSymbolAsteriks || token.Type == ttSymbolCommercialAnd)
        {
            typePtrExpression = std::make_shared<ASTTypePointerExpression>();

            if (token.Type == ttSymbolAsteriks)
            {
                typePtrExpression->Type = ptPointer;
            }
            else if (token.Type == ttSymbolCommercialAnd)
            {
                typePtrExpression->Type = ptReference;
            }


            typePtrExpression->Element = typeElementTemp;
            typeElementTemp = typePtrExpression;

            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();

        }


        expression = typeElementTemp;

    }
    else
    {
        expression = typeExpression;
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

        ASTExpressionPtr initExpression;
        if (ParseExpression(tokenizer, initExpression))
        {
            expression->Initialization = initExpression;
            token = tokenizer->GetCurrentToken();
        }
    }

    if (token.Type != ttSymbolSemicolon && token.Type != ttSymbolComma && token.Type != ttSymbolRightBracket)
    {
        // todo: log error
        tokenizer->Reset();
        return false;
    }

    tokenizer->NextToken();
    return true;
}

bool PicoC::Parser::ASTParser::ParseFunctionCallExpression(TokenizerPtr tokenizer, ASTFunctionCallExpressionPtr & expression)
{
    tokenizer->Remember();
    expression = std::make_shared< ASTFunctionCallExpression>();

    Token token = tokenizer->GetCurrentToken();

    if (token.Type == ttIdentifier)
    {
        expression->Identifier = std::make_shared<ASTIdentifierExpression>();
        expression->Identifier->Name = token.Value;

        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();

        if (token.Type == ttSymbolLeftBracket)
        {
            if (tokenizer->GetNextToken().Type != ttSymbolRightBracket)
            {
                do
                {
                    tokenizer->NextToken();
                    token = tokenizer->GetCurrentToken();

                    ASTExpressionPtr argumentExpression;
                    if (ParseExpression(tokenizer, argumentExpression))
                    {
                        expression->Arguments.push_back(argumentExpression);
                        token = tokenizer->GetCurrentToken();
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
        if (token.Type == ttSymbolSemicolon)
        {
            tokenizer->NextToken();
            return true;
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
}

bool PicoC::Parser::ASTParser::ParseIfStatement(TokenizerPtr tokenizer, ASTIfStatementPtr & ifStatement)
{
    ifStatement = std::make_shared< ASTIfStatement>();
    tokenizer->Remember();
    Token token = tokenizer->GetCurrentToken();

    if (token.Type == ttKeywordIf)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();

        if (token.Type == ttSymbolLeftBracket)
        {
            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();

            ASTExpressionPtr expression;
            if (ParseExpression(tokenizer, expression))
            {
                ifStatement->Condition = expression;

                token = tokenizer->GetCurrentToken();
                if (token.Type != ttSymbolRightBracket)
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

    tokenizer->NextToken();
    token = tokenizer->GetCurrentToken();

    if (token.Type == ttSymbolLeftCurlyBracket)
    {
        tokenizer->NextToken();
        ASTBlockElementPtr block;
        if (ParseBlock(tokenizer, block))
        {
            ifStatement->Children = block->Children;
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

    return true;
}
