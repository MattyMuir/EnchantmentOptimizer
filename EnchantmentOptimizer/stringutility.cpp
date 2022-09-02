#include "stringutility.h"

#include <sstream>
#include <locale>
#include <ranges>

std::string FormatWithCommas(uint64_t value)
{
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << value;
    return ss.str();
}

std::vector<std::string> Split(std::string_view str, std::string_view delim)
{
    std::vector<std::string> split;
    for (const auto& token : std::views::split(str, delim))
        split.emplace_back(token.begin(), token.end());

    return split;
}