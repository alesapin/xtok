#include "rawtoken.h"

NTokenizer::TRawToken NTokenizer::FromToken(const NTokenizer::TToken& t) {
    TVector<TString> rawTags;
    for (auto tag : ToTagSet(t.GetGraphemTag())) {
        TStringStream ss;
        ss << tag;
        rawTags.push_back(ss.Str());
    }

    TStringStream ss1;
    ss1 << t.GetTypeTag();
    return TRawToken{
        .Data = t.GetUTF8Data(),
        .TokenType = ss1.Str(),
        .GraphemTags = rawTags,
    };
}

TVector<NTokenizer::TRawToken> NTokenizer::RawTokensFromText(const TString& text) {
    TVector<NTokenizer::TToken> tokens = FromUTF8Text(text);
    TVector<TRawToken> result;
    for (auto &token: tokens) {
        result.push_back(FromToken(token));
    }
    return result;
}
