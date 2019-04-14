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

    if (token[token.length() - 1] == ':')
        return ttLabel;
    else if (token == "byte" || token == "word" || token == "dword")
        return ttSize;
    else if (token == "section")
        return ttSectionKeyword;
    else if (token == ",")
        return ttOperandSplitter;
    else if (token == "-")
        return ttAddressSubtraction;
    else if (token == "+")
        return ttAddressAddition;
    else if (token == "]")
        return ttAddressCloser;
    else if (token == "[")
        return ttAddressOpener;
    else if (token[0] == '0' && token[1] == 'x')
        return ttConstHex;
    else if (token[0] == '@')
        return ttLabelAlias;
    else if (token[0] == '.')
        return ttDataAlias;
    else if (token[0] == '%')
        return ttCompilerCommand;
    else if (token[0] == 0x27 && token[token.length() - 1] == 0x27)
        return ttConstString;
    else if (is_number(token))
        return ttConstDec;

    return ttUnknown;
}