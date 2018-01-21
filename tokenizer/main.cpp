#include <util/generic/vector.h>
#include <util/generic/string.h>
#include <util/stream/output.h>
#include <util/charset/unidata.h>
#include <util/charset/wide.h>

int main() {
    TVector<TString> XX;
    TUtf16String str = TUtf16String::FromUtf8("Пы!@ 3,z");
    Cerr << WideToUTF8(str) << Endl;
    for (ui64 i = 0; i < str.size() ; ++i ) {
        Cerr << str[i] << "\n";
        Cerr << "IsPunct:" << IsPunct(str[i]) << Endl;
        Cerr << "Is Alphabetical:" << IsAlphabetic(str[i]) << Endl;
        Cerr << "Is space:" << IsSpace(str[i]) << Endl;
        Cerr << "Is Digit:" << IsDigit(str[i]) << Endl;
        Cerr << "Is Upper:" << IsUpper(str[i]) << Endl;
        Cerr << "Is Lower:" << IsLower(str[i]) << Endl;
    }
    Cerr << '\n';
    return 0;
}
