#include "token.h"
#include <util/charset/wide.h>
using namespace NTokenizer;
int main() {
    //TVector<TString> XX;
    //TUtf16String str = TUtf16String::FromUtf8("Пы!@ 3,z");
    //Cerr << WideToUTF8(str) << Endl;
    //for (ui64 i = 0; i < str.size() ; ++i ) {
    //    Cerr << str[i] << "\n";
    //    Cerr << "IsPunct:" << IsPunct(str[i]) << Endl;
    //    Cerr << "Is Alphabetical:" << IsAlphabetic(str[i]) << Endl;
    //    Cerr << "Is space:" << IsSpace(str[i]) << Endl;
    //    Cerr << "Is Digit:" << IsDigit(str[i]) << Endl;
    //    Cerr << "Is Upper:" << IsUpper(str[i]) << Endl;
    //    Cerr << "Is Lower:" << IsLower(str[i]) << Endl;
    //}
    //Cerr << '\n';

    //Cerr << UTF8ToWide("»")[0] << Endl;
    //Cerr << UTF8ToWide("«")[0] << Endl;
    //Cerr << UTF8ToWide("—")[0] << Endl;

    TUtf16String someText = UTF8ToWide("Привет мир светит солнце!");
    TVector<TToken> tokens = FromText(someText);

    for (auto& token : tokens) {
        Cerr << "{ \"text\":\"" << token.GetData() << "\", \"type\":"<< token.GetTypeTag()  << ", \"info\":" << ToTagStr(token.GetGraphemTag()) << "}\n";
    }

    return 0;
}
