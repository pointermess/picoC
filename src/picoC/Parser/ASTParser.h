/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <vector>
#include <memory>


#include "../CompilerResult.h"
#include "../Representation/AST.h"
#include "Tokenizer.h"

using namespace PicoC::Representation;

namespace PicoC
{
    namespace Parser
    {

        //typedef std::shared_ptr<ASTParserState> ASTParserStatePtr;
        class CompilerState;
        class ASTParser
        {
        private:
            std::shared_ptr<CompilerState> _CompilerState;
        public:
            // This object holds the current state of the parser
            //ASTParserStatePtr State;

            ASTParser() {};
            ASTParser(std::shared_ptr<CompilerState> compilerState);


            bool ParseProgram(TokenizerPtr tokenizer, ASTProgramPtr& program);

            bool ParseFunctionDeclaration(TokenizerPtr tokenizer, ASTProgramPtr program, ASTFunctionDeclarationPtr& expression);

            bool ParseBlock(TokenizerPtr tokenizer, ASTBlockElementPtr& block);

            bool ParseExpression(TokenizerPtr tokenizer, ASTExpressionPtr& expression);
            bool ParseTypeExpression(TokenizerPtr tokenizer, ASTTypeElementPtr& expression);
            bool ParseBinaryExpression(TokenizerPtr tokenizer, ASTBinaryExpressionPtr& expression);
            bool ParseNumericLiteralExpression(TokenizerPtr tokenizer, ASTNumericLiteralExpressionPtr& expression);
            bool ParseVariableDeclaration(TokenizerPtr tokenizer, ASTVariableDeclarationPtr& expression);
            bool ParseFunctionCallExpression(TokenizerPtr tokenizer, ASTFunctionCallExpressionPtr& expression);
            bool ParseIfStatement(TokenizerPtr tokenizer, ASTIfStatementPtr& ifStatement);
        };
        typedef std::shared_ptr<ASTParser> ASTParserPtr;
    }
}