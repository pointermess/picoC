#pragma once

#include "../Representation/AST.h"
#include "../Compiler.h"

#include "./ProgramAssembly.h"

#include <memory>
#include <string>

namespace PicoC
{
    class CompilerState;
    namespace Generator
    {
        class CodeGenerator
        {
        private:
            std::shared_ptr<CompilerState> _CompilerState;


            bool _GenerateASTBinaryExpression(ASTBinaryExpressionPtr binaryExpression, std::vector<std::string> output);
            bool _GenerateASTExpressionExpression(std::vector<std::string> output);

            bool _GenerateProgram(ASTProgramPtr program);

            bool _GenerateBlockElement(ASTBlockElementPtr block);

            bool _GenerateASTFunctionDeclaration(ASTFunctionDeclarationPtr functionDeclaration);
            bool _GenerateASTIfStatement(ASTIfStatementPtr ifStatement);
            bool _GenerateVariableDeclaration(ASTVariableDeclarationPtr variableDeclaration);
            bool _GenerateGlobalVariableDeclaration(ASTVariableDeclarationPtr variableDeclaration);


            bool _GenerateResolveExpression(ASTExpressionPtr expression, const std::string & from, const std::string& target);

            bool _GenerateResolveNumericExpression(ASTNumericLiteralExpressionPtr expression, const std::string& target);


            bool _GenerateResolveBinaryExpression(ASTBinaryExpressionPtr expression, const std::string& from, const std::string& target);
        public:

            CodeGenerator(std::shared_ptr<CompilerState> compilerResult);

            ProgramAssemblyPtr Assembly;
            

            bool Generate();
        };
        typedef std::shared_ptr< CodeGenerator> CodeGeneratorPtr;
    }
}