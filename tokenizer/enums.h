#pragma once

#include <type_traits>
#include <util/string/builder.h>

namespace NTokenizer {
enum class ETokenType {
    UNKNOWN,
    WORD,
    PUNCT,
    SEPARATOR,
    NUMBER,
    WORDNUM,
    HIEROGLYPH,
};
enum class EGraphemTag {
    UNKNOWN = 0x0,
    // word tags
    CYRILLIC = 0x1,
    LATIN = 0x2,
    UPPER_CASE = 0x4,
    LOWER_CASE = 0x8,
    MIXED = 0x10,
    CAP_START = 0x20,
    // punct tags
    COMMA = 0x40,
    DOT = 0x80,
    COLON = 0x100,
    SEMICOLON = 0x200,
    QUESTION_MARK = 0x400,
    EXCLAMATION_MARK = 0x800,
    THREE_DOTS = 0x1000,
    QUOTE = 0x2000,
    DASH = 0x4000,
    PARENTHESIS_L = 0x8000,
    PARENTHESIS_R = 0x10000,
    LOWER_DASH = 0x20000,
    UNCOMMON_PUNCT = 0x40000,
    // number tags
    NORMAL = 0x80000,
    ROMAN = 0x100000,
    // separator tags
    SPACE = 0x200000,
    TAB = 0x400000,
    NEW_LINE = 0x800000,
    CR = 0x1000000,
    SINGLE_SEP = 0x2000000,
    MULTI_SEP = 0x4000000,
};

template<typename T>
inline T operator|(T left, T right) {
    static_assert(std::is_enum<T>::value, "Type of operator| must be enum");
    auto leftVal = static_cast<std::underlying_type_t<T>>(left);
    auto rightVal = static_cast<std::underlying_type_t<T>>(right);
    auto resVal = leftVal | rightVal;
    return static_cast<T>(resVal);
}
template<typename T>
inline T operator|=(T& left, T right) {
    static_assert(std::is_enum<T>::value, "Type of operator|= must be enum");
    auto leftVal = static_cast<std::underlying_type_t<T>>(left);
    auto rightVal = static_cast<std::underlying_type_t<T>>(right);
    auto resVal = leftVal | rightVal;
    return left = static_cast<T>(resVal);
}
template<typename T>
inline bool Intersect(T left, T right) {
    static_assert(std::is_enum<T>::value, "Type of Intersect must be enum");
    auto leftVal = static_cast<std::underlying_type_t<T>>(left);
    auto rightVal = static_cast<std::underlying_type_t<T>>(right);
    auto resVal = leftVal & rightVal;
    return static_cast<bool>(resVal);
}
template<typename T>
inline bool Contains(T left, T right) {
    static_assert(std::is_enum<T>::value, "Type of Contains must be enum");
    auto leftVal = static_cast<std::underlying_type_t<T>>(left);
    auto rightVal = static_cast<std::underlying_type_t<T>>(right);
    auto resVal = leftVal & rightVal;
    return resVal == rightVal;
}
template<typename T>
TVector<T> ToTagSet(T tag) {
    static_assert(std::is_enum<T>::value, "Type of ToTagSet must be enum");
    std::underlying_type_t<T> value = static_cast<std::underlying_type_t<T>>(tag);
    TVector<T> result;
    for (ui64 i = 1; i < 1ul << 63; i <<= 1) {
        if (value & i) {
            result.push_back(static_cast<T>(i));
        }
    }
    return result;
}

template<typename T>
TString ToTagStr(T tag) {
    TStringBuilder result;
    TVector<T> tagSet = ToTagSet(tag);
    for (auto tag : tagSet) {
        result << tag << ",";
    }
    if (result) {
        result.pop_back();
    }
    return result;
}
}
