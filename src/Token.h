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
        ttInstruction,
        ttConstString,
        ttConstDec,
        ttConstHex,
        ttRegister,
        ttAddressOpener,
        ttAddressCloser,
        ttAddressAddition,
        ttAddressSubtraction,
        ttOperandSplitter,
        ttSize,
        ttLabel,
        ttLabelAlias,
        ttSectionKeyword,
        ttDataAlias,
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