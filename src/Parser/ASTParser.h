/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <vector>
#include <memory>


#include "AST.h"
#include "../Tokenizer.h"


namespace PicoC
{
    namespace Parser
    {
        enum ASTParserHintType { Comment, Warning, Error};
        struct ASTParserHint
        {
        public:
            unsigned int Line = 0;
            unsigned int Position = 0;
            std::string Text = "UNDEFINED";
        };


        // Waiting = Not running yet
        // Running = Currently running / Paused
        // Failed = Fatal or syntax error detected
        // Successful = Parsing process completed
        enum ASTParserResultType { Waiting, Running, Failed, Successful };
        class ASTParserState
        {
        public:
            ASTParserResultType Result = Failed;
            std::vector<ASTParserHint> Hints;
        };
        typedef std::shared_ptr<ASTParserState> ASTParserStatePtr;

        class ASTParser
        {
        private:

        public:
            // This object holds the current state of the parser
            ASTParserStatePtr State;

            ASTParser();


            bool ParseProgram(TokenizerPtr tokenizer, ASTProgramPtr& program);

            bool ParseFunctionDeclaration(TokenizerPtr tokenizer, ASTProgramPtr program, ASTFunctionDeclarationPtr& expression);

            bool ParseBlock(TokenizerPtr tokenizer, ASTBlockElementPtr& block);

            bool ParseExpression(TokenizerPtr tokenizer, ASTExpressionPtr& expression);
            bool ParseTypeExpression(TokenizerPtr tokenizer, ASTTypeExpressionPtr& expression);
            bool ParseBinaryExpression(TokenizerPtr tokenizer, ASTBinaryExpressionPtr& expression);
            bool ParseNumericLiteralExpression(TokenizerPtr tokenizer, ASTNumericLiteralExpressionPtr& expression);
            bool ParseVariableDeclaration(TokenizerPtr tokenizer, ASTVariableDeclarationPtr& expression);
            bool ParseIfStatement(TokenizerPtr tokenizer, ASTIfStatementPtr& ifStatement);
        };
        typedef std::shared_ptr<ASTParser> ASTParserPtr;
    }
}