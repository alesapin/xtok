#pragma once

#include "enums.h"
#include <util/generic/vector.h>
#include <util/charset/unidata.h>
#include <util/generic/string.h>
#include <util/string/builder.h>
#include <util/string/join.h>

namespace NTokenizer {
class TToken {
protected:
  TUtf16String Data;
  ETokenType TokenType;
  EGraphemTag GraphemTag;

public:
    TToken(const TUtf16String &data, ETokenType tokenType = ETokenType::UNKNOWN,
           EGraphemTag graphemTag = EGraphemTag::UNKNOWN)
        : Data(data), TokenType(tokenType), GraphemTag(graphemTag) {}

    TToken() = default;

    ETokenType GetTypeTag() const { return TokenType; }
    EGraphemTag GetGraphemTag() const { return GraphemTag; }
    TUtf16String GetData() const { return Data; }

    void SetTypeTag(ETokenType tokenType) { TokenType = tokenType; }
    void SetGraphemTag(EGraphemTag graphemTag) { GraphemTag = graphemTag; }
    void SetData(const TUtf16String &data) { Data = data; }
};
TUtf16String ToText(const TVector<TToken> &tokens);
TVector<TToken> FromText(const TUtf16String &text);
}
