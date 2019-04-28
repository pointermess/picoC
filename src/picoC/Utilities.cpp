/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <algorithm>
#include <fstream>
#include <streambuf>

#include "Utilities.h"

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void str_to_lower(std::string & s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

std::string read_file(std::string fileName)
{
    std::ifstream t(fileName);
    std::string result((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return result;
}

unsigned stou(std::string const & str, size_t * idx = 0, int base = 10) {
    unsigned long result = std::stoul(str, idx, base);
    if (result > std::numeric_limits<unsigned>::max()) {
        throw std::out_of_range("stou");
    }
    return result;
}

uint32_t parse_number(std::string number)
{
    if (number.length() > 2)
    {
        std::string prefix;
        std::string value;
        prefix.assign(number, 0, 2);
        value.assign(number, 2, number.length() - 2);

        if (prefix == "0x")
            return stou(value, nullptr, 16);
        if (prefix == "0o")
            return stou(value, nullptr, 8);
        if (prefix == "0b")
            return stou(value, nullptr, 2);
    }
    return std::stoi(number);
}