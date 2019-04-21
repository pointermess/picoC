/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <string>
namespace PicoC
{

    enum FATokenType
    {
        ttUnknown,

        ttCompilerCommand,

        ttConstString,
        ttConstDec,
        ttConstHex,

        ttKeywordIf,
        ttKeywordWhile,
        ttKeywordReturn,

        ttTypeSigned,
        ttTypeUnsigned,
        ttTypeVoid,
        ttTypeChar,
        ttTypeShort,
        ttTypeInt,

        ttSymbolLeftBracket,
        ttSymbolRightBracket,
        ttSymbolLeftSquareBracket,
        ttSymbolRightSquareBracket,
        ttSymbolLeftCurlyBracket,
        ttSymbolRightCurlyBracket,
        ttSymbolComma,
        ttSymbolSemicolon,
        ttSymbolColon,
        ttSymbolQuestionMark,
        ttSymbolPlus,
        ttSymbolDash,
        ttSymbolAsteriks,
        ttSymbolForwardSlash,
        ttSymbolCommercialAnd,
        ttSymbolAnd,
        ttSymbolOr,
        ttSymbolExclamationMark,
        ttSymbolDefine,
        ttSymbolDefinePlus,
        ttSymbolDefineMinus,
        ttSymbolDefineTimes,
        ttSymbolEquals,
        ttSymbolNotEquals,
        ttSymbolIncrement,
        ttSymbolDecrement,


        ttIdentifier
    };

    struct Token
    {
    public:
        std::string Value;
        unsigned int Position;
        unsigned int Line;
        FATokenType Type;

        static FATokenType GetType(std::string TokenValue);
    };

}