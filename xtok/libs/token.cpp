#include "token.h"

#include <util/charset/unidata.h>
#include <util/string/builder.h>
#include <util/string/join.h>

namespace NTokenizer {
    namespace {
        ui64 CutWordNum(ui64 start, const TUtf16String& str) {
            ui64 i = start;
            while (i < str.length() && (IsAlphabetic(str[i]) || IsDigit(str[i]))) {
                ++i;
            }
            return i;
        }
        ui64 CutNumber(ui64 start, const TUtf16String& str) {
            ui64 i = start;
            while (i < str.length() && IsDigit(str[i])) {
                ++i;
            }
            //Если закончили не на пунктуации или
            //разделитель, значит это не цифра
            if (i < str.length() && !IsSpace(str[i]) && !IsPunct(str[i])) {
                return start;
            }
            return i;
        }

        ui64 CutSeparator(ui64 start, const TUtf16String& str) {
            ui64 i = start;
            while (i < str.length() && (IsSpace(str[i]) || IsLineSep(str[i]) || IsParaSep(str[i]))) {
                i++;
            }
            return i;
        }
        ui64 CutPunct(ui64 start, const TUtf16String& str) {
            ui64 i = start;
            while (i < str.length() && IsPunct(str[i]) && str[i] == '.') {
                ++i;
            }
            if (i == start) {
                return i + 1;
            }
            return i;
        }
        ui64 CutWord(ui64 start, const TUtf16String& str) {
            ui64 i = start;
            while (i < str.length() && IsAlphabetic(str[i])) {
                i++;
            }
            if (i < str.length() && !IsSpace(str[i]) && !IsPunct(str[i])) {
                return start;
            }
            return i;
        }
        ui64 CutTrash(ui64 start, const TUtf16String& str) {
            ui64 i = start;
            while (i < str.length() &&
                   (IsIdeographic(str[i]) || IsHiragana(str[i]) || IsKatakana(str[i]))) {
                i++;
            }

            return i;
        }
        ui64 CutAscii(ui64 start, const TUtf16String& /*str*/) {
            return ++start;
        }

        TToken ProcessWord(const TUtf16String& str) {
            EGraphemTag t = EGraphemTag::UNKNOWN;
            bool isUpperCase = true;
            bool isLowerCase = true;
            bool isLatin = true;
            bool isCyrrilic = true;
            bool capStart = IsUpper(str[0]);
            int capCounter = 0;
            for (const auto& chr : str) {
                if (chr > 127) {
                    isLatin = false;
                } else {
                    isCyrrilic = false;
                }
                if (IsLower(chr)) {
                    isUpperCase = false;
                } else {
                    capCounter++;
                    isLowerCase = false;
                }
            }
            if (isUpperCase) {
                t |= EGraphemTag::UPPER_CASE;
            } else if (isLowerCase) {
                t |= EGraphemTag::LOWER_CASE;
            } else if (capCounter == 1 && capStart) {
                t |= EGraphemTag::CAP_START;
            } else {
                t |= EGraphemTag::MIXED;
            }
            if (isLatin) {
                t |= EGraphemTag::LATIN;
            } else if (isCyrrilic) {
                t |= EGraphemTag::CYRILLIC;
            }
            return TToken(str, ETokenType::WORD, t);
        }

        TToken ProcessPunct(const TUtf16String& str) {
            EGraphemTag t = EGraphemTag::UNKNOWN;
            if (str.length() > 1) {
                bool isThreeDots = true;
                for (const auto& t : str) {
                    if (t != '.') {
                        isThreeDots = false;
                    }
                }
                if (isThreeDots) {
                    t |= EGraphemTag::THREE_DOTS;
                }
            } else {
                wchar16 sym = str[0];
                if (sym == ',') {
                    t |= EGraphemTag::COMMA;
                } else if (sym == '.') {
                    t |= EGraphemTag::DOT;
                } else if (sym == ':') {
                    t |= EGraphemTag::COLON;
                } else if (sym == ';') {
                    t |= EGraphemTag::SEMICOLON;
                } else if (sym == '?') {
                    t |= EGraphemTag::QUESTION_MARK;
                } else if (sym == '!') {
                    t |= EGraphemTag::EXCLAMATION_MARK;
                } else if (sym == '\\' || sym == 187 || sym == 171) { // » and «
                    t |= EGraphemTag::QUOTE;
                } else if (sym == '_') {
                    t |= EGraphemTag::LOWER_DASH;
                } else if (sym == '-' || sym == 8212) { // longer —
                    t |= EGraphemTag::DASH;
                } else if (sym == '(') {
                    t |= EGraphemTag::PARENTHESIS_L;
                } else if (sym == ')') {
                    t |= EGraphemTag::PARENTHESIS_R;
                } else {
                    t |= EGraphemTag::UNCOMMON_PUNCT;
                }
            }
            return TToken(str, ETokenType::PUNCT, t);
        }
        TToken ProcessNumber(const TUtf16String& number) {
            bool isRoman = true;
            for (const wchar16& chr : number) {
                if (!IsRomanDigit(chr)) {
                    isRoman = false;
                    break;
                }
            }
            EGraphemTag t = EGraphemTag::UNKNOWN;
            if (isRoman) {
                t |= EGraphemTag::ROMAN;
            } else {
                t |= EGraphemTag::NORMAL;
            }
            return TToken(number, ETokenType::NUMBER, t);
        }
        TToken ProcessSeparator(const TUtf16String& sep) {
            EGraphemTag t = EGraphemTag::UNKNOWN;
            if (sep.length() > 1) {
                t = EGraphemTag::MULTI_SEP;
            } else {
                t = EGraphemTag::SINGLE_SEP;
                wchar16 sym = sep[0];
                if (sym == ' ') {
                    t |= EGraphemTag::SPACE;
                } else if (sym == '\t') {
                    t |= EGraphemTag::TAB;
                } else if (sym == '\n') {
                    t |= EGraphemTag::NEW_LINE;
                } else if (sym == '\r') {
                    t |= EGraphemTag::CR;
                }
            }
            return TToken(sep, ETokenType::SEPARATOR, t);
        }
        TToken ProcessWordNum(const TUtf16String& wn) {
            EGraphemTag t = EGraphemTag::UNKNOWN;
            bool stop = false;
            for (ui64 i = wn.length() - 1; i > 0; --i) {
                if ((wn[i] < 128) && !stop) {
                    stop = true;
                } else if (!(wn[i] < 128) && stop) {
                    stop = false;
                    break;
                }
            }
            if (stop) {
                t |= EGraphemTag::CYRILLIC;
            }
            return TToken(wn, ETokenType::WORDNUM, t);
        }
        TToken ProcessHieroglyph(const TUtf16String& hir) {
            return TToken(hir, ETokenType::HIEROGLYPH);
        }
        TToken ProcessAscii(const TUtf16String& ascii) {
            return TToken(ascii, ETokenType::ASCII);
        }
    }
    TUtf16String ToWideText(const TVector<TToken>& tokens) {
        TUtf16String result;
        for (auto& token : tokens) {
            result += token.GetWideData();
        }
        return result;
    }

    TString ToUTF8Text(const TVector<TToken>& tokens) {
        TStringBuilder builder;
        for (auto& token : tokens) {
            builder << token.GetUTF8Data();
        }
        return builder;
    }

    TVector<TToken> FromWideText(const TUtf16String& text) {
        TVector<TToken> result;
        for (ui64 i = 0; i < text.length();) {
            TToken r;
            ui64 nextI = i;
            if (IsAlphabetic(text[i])) {
                nextI = CutWord(i, text);
                bool notAword = false;
                if (nextI == i) { //Не продвинулись --> не слово
                    nextI = CutWordNum(i, text);
                    notAword = true;
                }
                TUtf16String word = text.substr(i, nextI - i);
                if (notAword) {
                    r = ProcessWordNum(word);
                } else {
                    r = ProcessWord(word);
                }
            } else if (IsPunct(text[i])) {
                nextI = CutPunct(i, text);
                TUtf16String punct = text.substr(i, nextI - i);
                r = ProcessPunct(punct);
            } else if (IsDigit(text[i])) {
                nextI = CutNumber(i, text);
                bool notAnumber = false;
                if (nextI == i) { //Не продвинулись --> не цифра
                    nextI = CutWordNum(i, text);
                    notAnumber = true;
                }
                TUtf16String num = text.substr(i, nextI - i);
                if (notAnumber) {
                    r = ProcessWordNum(num);
                } else {
                    r = ProcessNumber(num);
                }
            } else if (IsSpace(text[i])) {
                nextI = CutSeparator(i, text);
                TUtf16String sep = text.substr(i, nextI - i);
                r = ProcessSeparator(sep);
            } else if (IsIdeographic(text[i]) || IsCntrl(text[i]) || IsHiragana(text[i]) || IsKatakana(text[i])) {
                nextI = CutTrash(i, text);
                TUtf16String trash = text.substr(i, nextI - i);
                r = ProcessHieroglyph(trash);
            } else {
                nextI = CutAscii(i, text);
                TUtf16String ascii = text.substr(i, nextI - i);
                r = ProcessAscii(ascii);
            }
            i = nextI;
            result.push_back(r);
        }
        return result;
    }

    void TokenToJson(NJson::TJsonWriter& writer, const TToken& token) {
        writer.OpenMap();
        writer.Write("data", token.GetUTF8Data());
        writer.Write("token_type", ToString(token.GetTypeTag()));
        writer.OpenArray("info");
        for(auto tag : ToTagSet(token.GetGraphemTag())) {
            writer.Write(ToString(tag));
        }
        writer.CloseArray();
        writer.CloseMap();
    }

    TVector<TToken> FromUTF8Text(const TString& text) {
        TUtf16String wideStr = UTF8ToWide(text);
        return FromWideText(wideStr);
    }
}
