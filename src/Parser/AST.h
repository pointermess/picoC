/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <vector>
#include <memory>

namespace PicoC
{
    namespace Parser
    {
        class AST
        {
        private:
        public:
            
        };
        class ASTElement;
        typedef std::shared_ptr<ASTElement> ASTElementPtr;
        class ASTBlockElement;
        typedef std::shared_ptr<ASTBlockElement> ASTBlockElementPtr;
        class ASTElement : public std::enable_shared_from_this<ASTElement>
        {
        private:
            ASTElement* _parent;
        public:
            std::string ElementType = "UNDEFINED";
            
            unsigned int Line;
            unsigned int Position;

            unsigned int Begin;
            unsigned int End;

            void SetParent(ASTElement* parent) { _parent = parent;  }
            ASTElement* GetParent() { return _parent; };

            virtual void PrintDebug(int prependSpaces = 0) = 0;
        };

        class ASTBlockElement : public ASTElement
        {
        public:
            std::string ElementType = "BlockElement";

            std::vector<ASTElementPtr> Children;

            void AddChildren(ASTElementPtr item);

            void PrintDebug(int prependSpaces = 0);
        };

        class ASTProgram : public  ASTBlockElement
        {

        };
        typedef std::shared_ptr<ASTProgram> ASTProgramPtr;


        class ASTExpression : public ASTElement
        {

        };
        typedef std::shared_ptr<ASTExpression> ASTExpressionPtr;

        // Expression forward declarations
        class ASTIdentifierExpression;
        typedef std::shared_ptr<ASTIdentifierExpression> ASTIdentifierExpressionPtr;

        class ASTFunctionCallExpression : public ASTElement
        {
        public:
            ASTIdentifierExpressionPtr Identifier;
            std::vector<ASTExpressionPtr> Arguments;
        };

        class ASTTypeExpression
        {
        public:
            bool Signed = true;
            std::string DataType;
        };
        typedef std::shared_ptr<ASTTypeExpression> ASTTypeExpressionPtr;

        class ASTParenthesizedExpression : public ASTExpression
        {
        public:
            ASTExpressionPtr Expression;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTParenthesizedExpression> ASTParenthesizedExpressionPtr;

        class ASTNumericLiteralExperssion : public ASTExpression
        {
        public:
            int Number;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTNumericLiteralExperssion> ASTNumericLiteralExpressionPtr;

        class ASTBinaryExpression : public ASTExpression
        {
        public:
            ASTExpressionPtr Left;
            ASTExpressionPtr Right;
        };
        typedef std::shared_ptr<ASTBinaryExpression> ASTBinaryExpressionPtr;

        class ASTStringLiteralExpression : public ASTExpression
        {
        public:
            std::string EscapedContent;
        };
        typedef std::shared_ptr<ASTStringLiteralExpression> ASTStringLiteralExpressionPtr;

        class ASTIdentifierExpression : public ASTExpression
        {
        public:
            std::string Name;
            void PrintDebug(int prependSpaces = 0);
        };

        class ASTVariableDeclaration : public ASTExpression
        {
        public:
            ASTTypeExpressionPtr Type;
            ASTIdentifierExpressionPtr Identifier;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTVariableDeclaration> ASTVariableDeclarationPtr;

        class ASTFunctionDeclaration : public ASTExpression
        {
        public:
            ASTTypeExpressionPtr Type;
            ASTIdentifierExpressionPtr Identifier;
            std::vector<ASTVariableDeclarationPtr> Arguments;
            ASTBlockElementPtr Body;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTFunctionDeclaration> ASTFunctionDeclarationPtr;
    }
}