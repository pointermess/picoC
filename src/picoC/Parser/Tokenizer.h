/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <vector>
#include <memory>
#include <string>
#include <set>

#include "Token.h"

namespace PicoC
{
    class Tokenizer
    {
    private:
        int _RememberIndex = 0;

        int FCurrentTokenIndex;
        std::set<char> _KeepTogetherChars;

        void _InitializeKeepTogetherChars();
    public:
        Tokenizer();
        ~Tokenizer();

        char EscapeChar;
        std::set<char> StringChars;
        std::set<char> StopChars;
        std::set<char> IgnoreChars;
        std::set<std::string> KeepTogether;


        std::vector<Token> Tokens;

        Token GetCurrentToken();
        Token GetNextToken(int add = 1);

        int GetTokenIndex();
        void SetTokenIndex(int index);

        bool NextToken();
        bool NextToken(Token& refreshToken);

        bool PreviousToken();
        bool PreviousToken(Token& refreshToken);
        bool IsInRange();

        void Tokenize(std::string str);

        void Remember();
        void Reset();
    };
    typedef std::shared_ptr<Tokenizer> TokenizerPtr;


}
