/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <iostream>
#include <set>
#include "Utilities.h"

#include "Tokenizer.h"


void PicoC::Tokenizer::_InitializeKeepTogetherChars()
{
    for (const std::string currrentStr : KeepTogether)
    {
        for (const char currentChar : currrentStr)
        {
            if (!in_set(_KeepTogetherChars, currentChar))
                _KeepTogetherChars.insert(currentChar);
        }
    }
}

PicoC::Tokenizer::Tokenizer()
{
    // Initialize private variables
    FCurrentTokenIndex = 0;

    EscapeChar = '\\';

    // specifying string char
    StringChars = { '"', 0x27 };

    // specifying stop chars
    StopChars = { ' ', '.', ',', '<', '>', '(', ')', '{', '}', ':', '=', '&', '|', '+', '-', '/', '*', ';', '"', '\'', '!',  10, 13, '"', 0x27 };

    // specifying ignore chars
    IgnoreChars = { ' ', 10, 13, '"', 0x27 };

    // specifying and initializing keep together strings
    KeepTogether = { ">=", "<=", "++", "--", "&&", "||", "->", "::", "==", "+=", "-=", "*=" };
    _InitializeKeepTogetherChars();
}


PicoC::Tokenizer::~Tokenizer()
{
}

PicoC::Token PicoC::Tokenizer::GetCurrentToken()
{
    try
    {
        Token result = Tokens.at(FCurrentTokenIndex);
        return result;
    }
    catch (std::out_of_range e)
    {
       // throw TokenizerEndOfFileException();
    }
}

PicoC::Token PicoC::Tokenizer::GetNextToken(int add)
{
    try
    {
        Token result = Tokens.at(FCurrentTokenIndex + add);
        return result;
    }
    catch (std::out_of_range e)
    {
     //   throw TokenizerEndOfFileException();
    }
}

int PicoC::Tokenizer::GetTokenIndex()
{
    return FCurrentTokenIndex;
}

void PicoC::Tokenizer::SetTokenIndex(int index)
{
    FCurrentTokenIndex = index;
}

void PicoC::Tokenizer::NextToken()
{
    ++FCurrentTokenIndex;
}

void PicoC::Tokenizer::PreviousToken()
{
    --FCurrentTokenIndex;
}

bool PicoC::Tokenizer::IsInRange()
{
    return FCurrentTokenIndex < Tokens.size();
}

void PicoC::Tokenizer::Tokenize(std::string str)
{
    unsigned int position = 0;
    unsigned int line = 0;

    unsigned int keepTogether = 0;

    bool inString = false;
    bool escapedChar = false;

    std::string buffer = "";
    char currentStringChar = ' ';

    // loop through provided string
    int currentCharIndex = -1;
    for (char& currentChar : str)
    {
        currentCharIndex += 1;

        // skip any chars from keeptogether
        if (keepTogether > 0)
        {
            keepTogether -= 1;
            continue;
        }


        bool isCurrentCharInStringChars = in_set<char>(StringChars, currentChar);

        // check if in string
        if (inString)
        {

            if (currentChar != currentStringChar || escapedChar) // check if string continues
            {
                buffer += currentChar;
                escapedChar = false;
            }
            else
            {
                // stringchars
                buffer = currentChar + buffer + currentChar;

                Tokens.push_back({ buffer, position, line, Token::GetType(buffer) });

                buffer = "";
                inString = false;
            }

            if (currentChar == EscapeChar)
            {
                escapedChar = true;
            }
            continue;
        }

        position += 1;

        if (currentChar == 0xA)
        {
            position = 0;
            line += 1;
        }

        bool isCurrentCharInStopChars = in_set<char>(StopChars, currentChar);
        bool isCurrentCharInIgnoreChars = in_set<char>(IgnoreChars, currentChar);
        bool isCurrentCharInKeepTogetherSet = in_set<char>(_KeepTogetherChars, currentChar);

        // if current char is in StopChars set
        if (!isCurrentCharInStopChars)
        {
            buffer += currentChar;
        }

        // if current char is in stop chars OR reached file end and buffer isnt empty
        if (((isCurrentCharInStopChars) ||
            (currentCharIndex == str.length() - 1)) &&
            (buffer != ""))
        {
            Tokens.push_back({ buffer, position, line, Token::GetType(buffer) });
            buffer = "";
        }

        if (isCurrentCharInStringChars)
        {
            currentStringChar = currentChar;
            inString = true;
        }

        if (isCurrentCharInStopChars && !isCurrentCharInIgnoreChars)
        {
            // handle keep together stuff
            if (isCurrentCharInKeepTogetherSet)
            {
                for (const std::string keepTogetherString : KeepTogether)
                {
                    std::string keepBuffer = str.substr(currentCharIndex, keepTogetherString.length());

                    if (keepBuffer == keepTogetherString)
                    {
                        Tokens.push_back({ keepTogetherString, position, line, Token::GetType(std::string(1, currentChar)) });
                        keepTogether = keepTogetherString.length() - 1;
                    }
                }
            }



            if (keepTogether == 0)
            {
                Tokens.push_back({ std::string(1, currentChar), position, line, Token::GetType(std::string(1, currentChar)) });
            }
        }
    }
}
