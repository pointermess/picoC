/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <algorithm>


#include "Token.h"
#include "Utilities.h"

using namespace PicoC;

FATokenType PicoC::Token::GetType(std::string TokenValue)
{
    std::string token = TokenValue;

    // set token to lowercase
    str_to_lower(token);

    if (token[0] == '#')
        return ttCompilerCommand;

    else if (token[0] == '"' && token[token.length() - 1] == '"')
        return ttConstString;
    else if (is_number(token))

        return ttConstDec;
    else if (token[0] == '0' && token[1] == 'x')
        return ttConstHex;

    else if (token == "if")
        return ttKeywordIf;
    else if (token == "while")
        return ttKeywordWhile;
    else if (token == "return")
        return ttKeywordReturn;

    else if (token == "signed")
        return ttTypeSigned;
    else if (token == "unsigned")
        return ttTypeUnsigned;
    else if (token == "void")
        return ttTypeVoid;
    else if (token == "char")
        return ttTypeChar;
    else if (token == "short")
        return ttTypeShort;
    else if (token == "int")
        return ttTypeInt;
    else if (token == "bool")
        return ttTypeBool;


    else if (token == "(")
        return ttSymbolLeftBracket;
    else if (token == ")")
        return ttSymbolRightBracket;
    else if (token == "[")
        return ttSymbolLeftSquareBracket;
    else if (token == "]")
        return ttSymbolRightSquareBracket;
    else if (token == "{")
        return ttSymbolLeftCurlyBracket;
    else if (token == "}")
        return ttSymbolRightCurlyBracket;
    else if (token == ",")
        return ttSymbolComma;
    else if (token == ";")
        return ttSymbolSemicolon;
    else if (token == "?")
        return ttSymbolQuestionMark;
    else if (token == ":")
        return ttSymbolColon;
    else if (token == "+")
        return ttSymbolPlus;
    else if (token == "-")
        return ttSymbolDash;
    else if (token == "*")
        return ttSymbolAsteriks;
    else if (token == "/")
        return ttSymbolForwardSlash;
    else if (token == "&")
        return ttSymbolCommercialAnd;
    else if (token == "&&")
        return ttSymbolAnd;
    else if (token == "||")
        return ttSymbolOr;
    else if (token == "!")
        return ttSymbolExclamationMark;
    else if (token == "=")
        return ttSymbolDefine;
    else if (token == "+=")
        return ttSymbolDefinePlus;
    else if (token == "-=")
        return ttSymbolDefineMinus;
    else if (token == "*=")
        return ttSymbolDefineTimes;
    else if (token == "==")
        return ttSymbolEquals;
    else if (token == "!=")
        return ttSymbolNotEquals;
    else if (token == "<=")
        return ttSymbolLowerEquals;
    else if (token == ">=")
        return ttSymbolGreaterEquals;
    else if (token == "<")
        return ttSymbolLower;
    else if (token == ">")
        return ttSymbolGreater;
    else if (token == "++")
        return ttSymbolIncrement;
    else if (token == "--")
        return ttSymbolDecrement;

    
    return ttIdentifier;
}