#pragma once

#include "token.h"

namespace NTokenizer {
    struct TRawToken {
        TString Data;
        TString TokenType;
        TVector<TString> GraphemTags;
    };

    TRawToken FromToken(const TToken& token);
    TVector<TRawToken> RawTokensFromText(const TString& text);
}
