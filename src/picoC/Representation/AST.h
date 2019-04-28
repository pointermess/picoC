/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <vector>
#include <memory>

#include "LookupTable.h"

namespace PicoC
{
    namespace Representation
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
            std::string ElementType = "ASTBlockElement";

            std::vector<ASTElementPtr> Children;

            void AddChildren(ASTElementPtr item);

            void PrintDebug(int prependSpaces = 0);
        };

        class ASTProgram : public  ASTBlockElement
        {
        public:
            std::string ElementType = "ASTProgram";
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTProgram> ASTProgramPtr;


        class ASTExpression : public ASTElement
        {
        public:
            void PrintDebug(int prependSpaces = 0);
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

        enum ASTModifierType { mtNone, mtDereference, mtReference };
        class VariableCallExpression : public ASTElement
        {
        public:
            std::string ElementType = "ASTTypePointerExpression";
            ASTModifierType Modifier = mtNone;
            void PrintDebug(int prependSpaces = 0);
        };

        enum ASTPointerTyp { ptNone, ptPointer, ptReference };
        typedef std::shared_ptr<ASTPointerTyp> ASTPointerTypPtr;

        class ASTTypeElement : public ASTExpression {};
        typedef std::shared_ptr<ASTTypeElement> ASTTypeElementPtr;

        class ASTTypePointerExpression : public ASTTypeElement
        {
        public:
            std::string ElementType = "ASTTypePointerExpression";

            ASTPointerTyp Type = ptNone;
            ASTTypeElementPtr Element;

            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTTypePointerExpression> ASTTypePointerExpressionPtr;

        class ASTTypeExpression : public ASTTypeElement
        {
        public:
            std::string ElementType = "ASTTypeExpression";
            bool Signed = true;
            std::string DataType;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTTypeExpression> ASTTypeExpressionPtr;

        class ASTParenthesizedExpression : public ASTExpression
        {
        public:
            std::string ElementType = "ASTParenthesizedExpression";
            ASTExpressionPtr Expression;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTParenthesizedExpression> ASTParenthesizedExpressionPtr;

        class ASTNumericLiteralExperssion : public ASTExpression
        {
        public:
            std::string ElementType = "ASTNumericLiteralExperssion";
            int Number;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTNumericLiteralExperssion> ASTNumericLiteralExpressionPtr;

        class ASTBinaryExpression : public ASTExpression
        {
        public:
            std::string ElementType = "ASTBinaryExpression";
            ASTExpressionPtr Left;
            ASTExpressionPtr Right;
            std::string Operator;
            void PrintDebug(int prependSpaces = 0);
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
            std::string ElementType = "ASTIdentifierExpression";
            std::string Name;
            void PrintDebug(int prependSpaces = 0);
        };

        class ASTVariableDeclaration : public ASTExpression
        {
        public:
            std::string ElementType = "ASTVariableDeclaration";

            ASTTypeElementPtr Type;
            ASTIdentifierExpressionPtr Identifier;
            ASTExpressionPtr Initialization;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTVariableDeclaration> ASTVariableDeclarationPtr;



        class ASTFunctionDeclaration : public ASTExpression
        {
        public:
            std::string ElementType = "ASTFunctionDeclaration";

            ASTTypeElementPtr Type;
            ASTIdentifierExpressionPtr Identifier;
            std::vector<ASTVariableDeclarationPtr> Arguments;
            ASTBlockElementPtr Body;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTFunctionDeclaration> ASTFunctionDeclarationPtr;


        class ASTIfStatement : public ASTBlockElement
        {
        public:
            std::string ElementType = "ASTIfStatement";

            ASTExpressionPtr Condition;
            void PrintDebug(int prependSpaces = 0);
        };
        typedef std::shared_ptr<ASTIfStatement> ASTIfStatementPtr;

    }
}