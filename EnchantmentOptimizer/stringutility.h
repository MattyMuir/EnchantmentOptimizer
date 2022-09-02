#pragma once
#include <string>
#include <vector>

std::string FormatWithCommas(uint64_t value);
std::vector<std::string> Split(std::string_view str, std::string_view delim);