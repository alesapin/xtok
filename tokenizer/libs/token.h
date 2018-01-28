#pragma once

#include "enums.h"
#include <util/charset/wide.h>
#include <util/generic/vector.h>
#include <util/generic/string.h>

namespace NTokenizer {
    class TToken {
    protected:
        TUtf16String Data;
        ETokenType TokenType;
        EGraphemTag GraphemTag;

    public:
        TToken(const TUtf16String& data, ETokenType tokenType = ETokenType::UNKNOWN,
               EGraphemTag graphemTag = EGraphemTag::UNKNOWN)
            : Data(data)
            , TokenType(tokenType)
            , GraphemTag(graphemTag)
        {
        }

        TToken() = default;

        ETokenType GetTypeTag() const {
            return TokenType;
        }
        EGraphemTag GetGraphemTag() const {
            return GraphemTag;
        }
        TUtf16String GetWideData() const {
            return Data;
        }
        TString GetUTF8Data() const {
            return WideToUTF8(Data);
        }

        void SetTypeTag(ETokenType tokenType) {
            TokenType = tokenType;
        }
        void SetGraphemTag(EGraphemTag graphemTag) {
            GraphemTag = graphemTag;
        }
        void SetWideData(const TUtf16String& data) {
            Data = data;
        }
        void SetUTF8Data(const TString& data) {
            Data = UTF8ToWide(data);
        }
    };

    TUtf16String ToWideText(const TVector<TToken>& tokens);
    TString ToUTF8Text(const TVector<TToken>& tokens);
    TVector<TToken> FromWideText(const TUtf16String& text);
    TVector<TToken> FromUTF8Text(const TString& text);
    TString TokenToJson(const TToken& token, bool pretty = false);
}
