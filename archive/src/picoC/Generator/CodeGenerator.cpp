#include "CodeGenerator.h"
#include <stdio.h>

bool PicoC::Generator::CodeGenerator::_GenerateProgram(ASTProgramPtr program)
{
    Assembly->AppendLine("section .data");

    Assembly->AppendLine("section .text");
    _GenerateBlockElement(program);

    return true;
}

bool PicoC::Generator::CodeGenerator::_GenerateBlockElement(ASTBlockElementPtr block)
{
    for (ASTElementPtr children : block->Children)
    {
        if (typeid(*children) == typeid(ASTFunctionDeclaration))
        {
            if (!_GenerateASTFunctionDeclaration(std::static_pointer_cast<ASTFunctionDeclaration>(children)))
                return false;
        }
        else if (typeid(*children) == typeid(ASTIfStatement))
        {
            if (!_GenerateASTIfStatement(std::static_pointer_cast<ASTIfStatement>(children)))
                return false;
        }
        else if (typeid(*children) == typeid(ASTVariableDeclaration))
        {
            if (!_GenerateVariableDeclaration(std::static_pointer_cast<ASTVariableDeclaration>(children)))
                return false;
        }
    }

    return true;
}

bool PicoC::Generator::CodeGenerator::_GenerateASTFunctionDeclaration(ASTFunctionDeclarationPtr functionDeclaration)
{
    Assembly->AppendLine(functionDeclaration->GetCallingName() + ":");

    if (_GenerateBlockElement(functionDeclaration->Body))
    {
        return true;
    }

    return false;
}

bool PicoC::Generator::CodeGenerator::_GenerateASTIfStatement(ASTIfStatementPtr ifStatement)
{

    _GenerateResolveExpression(ifStatement->Condition, "", "eax");

    if (_GenerateBlockElement(ifStatement))
    {
        Assembly->AppendLine("after_if:");
        return true;
    }

    return false;
}

bool PicoC::Generator::CodeGenerator::_GenerateVariableDeclaration(ASTVariableDeclarationPtr variableDeclaration)
{
    _GenerateResolveExpression(variableDeclaration->Initialization, "", "eax");

    return true;
}

bool PicoC::Generator::CodeGenerator::_GenerateResolveExpression(ASTExpressionPtr expression, const std::string & from, const std::string & target)
{
    if (typeid(*expression) == typeid(ASTNumericLiteralExperssion))
    {
        _GenerateResolveNumericExpression(std::static_pointer_cast<ASTNumericLiteralExperssion>(expression), target);
        return true;
    }
    else if (typeid(*expression) == typeid(ASTBinaryExpression))
    {
        _GenerateResolveBinaryExpression(std::static_pointer_cast<ASTBinaryExpression>(expression), from, target);
        return true;
    }
    else if (typeid(*expression) == typeid(ASTParenthesizedExpression))
    {
        _GenerateResolveExpression(std::static_pointer_cast<ASTParenthesizedExpression>(expression)->Expression, from, target);
        return true;
    }

    return false;
}


bool PicoC::Generator::CodeGenerator::_GenerateResolveBinaryExpression(ASTBinaryExpressionPtr expression, const std::string & from, const std::string & target)
{
    std::vector<ASTExpressionPtr> expressions;

    bool reachedEnd = false;
    ASTExpressionPtr currentExpression = expression;
    while (!reachedEnd)
    {
        if (typeid(*currentExpression) == typeid(ASTBinaryExpression))
        {
            expressions.push_back(currentExpression);
            currentExpression = std::static_pointer_cast<ASTBinaryExpression>(currentExpression)->Right;
        }
        else
            reachedEnd = true;
    }
    

    ASTExpressionPtr nextExpression = expression;
    int currentExpressionIndex = 0;

    std::string result = "";
    while (currentExpressionIndex < expressions.size())
    {
        // set next expression index according to current index
        int nextExpressionIndex = currentExpressionIndex + 1;
        currentExpression = expressions[currentExpressionIndex];
        
        // loop though next expressions to look for point vor strikk yea
        reachedEnd = false;
        while (!reachedEnd)
        {
            if (nextExpressionIndex < expressions.size())
                nextExpression = expressions[nextExpressionIndex];
            else
                break;

            if (typeid(*nextExpression) == typeid(ASTBinaryExpression))
            {
                ASTBinaryExpressionPtr nextBinExpression = std::static_pointer_cast<ASTBinaryExpression>(nextExpression);

                if (nextBinExpression->Operator == "*")
                {
                    _GenerateResolveExpression(nextBinExpression->Left, "", "eax");
                    _GenerateResolveExpression(nextBinExpression->Right, "", "ebx");

                }
                else
                {
                    break;
                }
            }


            if (nextExpressionIndex >= expressions.size()) reachedEnd = true;
            ++nextExpressionIndex;
        }
        currentExpressionIndex = nextExpressionIndex;
    }

     return true;

}


bool PicoC::Generator::CodeGenerator::_GenerateResolveNumericExpression(ASTNumericLiteralExpressionPtr expression, const std::string & target)
{
    Assembly->AppendLine("mov", target, std::to_string(expression->Number));
    return true;
}

PicoC::Generator::CodeGenerator::CodeGenerator(std::shared_ptr<CompilerState> compilerResult)
{
    _CompilerState = compilerResult;

    Assembly = std::make_shared<ProgramAssembly>();
}

bool PicoC::Generator::CodeGenerator::Generate()
{
    _GenerateProgram(_CompilerState->Program);

    FILE * pFile;

    fopen_s(&pFile, "C:/Users/Milos/Desktop/FlexASM Compiler/Debug/pctest.txt", "w");
    for (AssemblyLine& line : Assembly->Lines)
    {
        fprintf(pFile, "%s\n", line.GetLine().c_str());
    }
    fclose(pFile);

    return 0;

    return true;
}
