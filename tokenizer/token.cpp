#include "token.h"
namespace NTokenizer {
namespace {
    //ui64 CutWordNum(ui64 start, const TUtf16String &str) {
    //  ui64 i = start;
    //  while (i < str.length() && (IsAlphabetic(str[i]) || IsDigit(str[i]))) {
    //    ++i;
    //  }
    //  return i;
    //}
    //ui64 CutNumber(ui64 start, const TUtf16String &str) {
    //  ui64 i = start;
    //  while (i < str.length() && IsDigit(str[i])) {
    //    ++i;
    //  }
    //  //Если закончили не на пунктуации или
    //  //разделитель, значит это не цифра
    //  if (i < str.length() && !IsSpace(str[i]) && !IsPunct(str[i])) {
    //    return start;
    //  }
    //  return i;
    //}
    //
    //ui64 CutSeparator(ui64 start, const TUtf16String &str) {
    //  ui64 i = start;
    //  while (i < str.length() && (IsSpace(str[i]) || IsLineSep(str[i]) || IsParaSep(str[i]))) {
    //    i++;
    //  }
    //  return i;
    //}
    //ui64 CutPunct(ui64 start, const TUtf16String &str) {
    //  ui64 i = start;
    //  while (i < str.length() && IsPunct(str[i]) && str[i] == '.') {
    //    ++i;
    //  }
    //  if (i == start) {
    //    return i + 1;
    //  }
    //  return i;
    //}
    //uint CutWord(uint start, const TUtf16String &str) {
    //  uint i = start;
    //  while (i < str.length() && IsAlphabetic(str[i])) {
    //    i++;
    //  }
    //  if (i < str.length() && !IsSpace(str[i]) && !IsPunct(str[i])) {
    //    return start;
    //  }
    //  return i;
    //}
    //uint CutTrash(uint start, const TUtf16String &str) {
    //  uint i = start;
    //  while (i < str.length() && (IsIdeographic(str[i]) || IsCntrl(str[i]))) {
    //    i++;
    //  }
    //
    //  return i;
    //}

    //TToken ProcessWord(const TUtf16String& str) const {
    //    EGraphemTag t = GraphemTag::UNKNOWN;
    //    bool isUpperCase = true;
    //    bool isLowerCase = true;
    //    bool isLatin = true;
    //    bool isCyrrilic = true;
    //    bool capStart = IsUpper(str[0]);
    //    int capCounter = 0;
    //    for (const auto& chr : str) {
    //        if (!chr.isOneByte()) {
    //            isLatin = false;
    //        } else {
    //            isCyrrilic = false;
    //        }
    //        if (chr.islower()) {
    //            isUpperCase = false;
    //        } else {
    //            capCounter++;
    //            isLowerCase = false;
    //        }
    //    }
    //    if (isUpperCase) {
    //        t |= base::GraphemTag::UPPER_CASE;
    //    } else if (isLowerCase) {
    //        t |= base::GraphemTag::LOWER_CASE;
    //    } else if (capCounter == 1 && capStart) {
    //        t |= base::GraphemTag::CAP_START;
    //    } else {
    //        t |= base::GraphemTag::MIXED;
    //    }
    //    if (isLatin) {
    //        t |= base::GraphemTag::LATIN;
    //    } else if (isCyrrilic) {
    //        t |= base::GraphemTag::CYRILLIC;
    //    } else {
    //        t |= base::GraphemTag::MULTI_ENC;
    //    }
    //    base::Token* res = new base::Token(str, base::TokenTypeTag::WORD, t);
    //    return std::shared_ptr<base::Token>(res);
    //}
}

TUtf16String ToText(const TVector<TToken> &tokens) {
  TUtf16String result;
  for (auto &token : tokens) {
    result += token.GetData();
  }
  return result;
}
}
