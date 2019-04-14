/*
 * Copyright (c) 2019-present by pointermess (Milos Stanojevic)
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <string>
#include <set>
#include <vector>

bool is_number(const std::string& s);

void str_to_lower(std::string & s);

std::string read_file(std::string fileName);

template <typename T>
bool in_set(std::set<T> & set, T value);


template<typename T>
inline bool in_set(std::set<T>& set, T value)
{
    return set.find(value) != set.end();
}

uint32_t parse_number(std::string number);