#include <xtok/libs/token.h>
#include <util/charset/wide.h>
#include <library/getopt/small/last_getopt.h>
#include <util/stream/input.h>
#include <util/stream/output.h>
#include <util/stream/file.h>
#include <library/json/json_writer.h>

using namespace NTokenizer;
using namespace NLastGetopt;
using namespace NJson;

int main(int argc, char** argv) {
    TOpts opts = TOpts::Default();
    TString inputFile, outputFile;
    opts.AddLongOption("input", "program input file")
        .StoreResult(&inputFile);
    opts.AddLongOption("output", "program output file").StoreResult(&outputFile);
    opts.AddLongOption("wonly", "print only words with separators").NoArgument();
    opts.AddLongOption("remove-trash", "remove hieroglyphs from text").NoArgument();
    opts.AddLongOption("json", "print output in json format").NoArgument();
    opts.AddLongOption("pretty", "pretty json output").NoArgument();

    TOptsParseResult res(&opts, argc, argv);

    THolder<IInputStream> input = &Cin;
    THolder<IOutputStream> output = &Cout;

    if (inputFile) {
        input = MakeHolder<TFileInput>(inputFile);
    }

    if (outputFile) {
        output = MakeHolder<TFileOutput>(outputFile);
    }

    if (res.Has("json")) {
        bool pretty = res.Has("pretty");
        TJsonWriter writer(output.Get(), pretty);
        writer.OpenMap();
        writer.OpenArray("tokens");
        TString line;
        while (input->ReadLine(line)) {
            TVector<TToken> tokens = FromUTF8Text(line);
            for (auto& token : tokens) {
                if (res.Has("remove-trash") && token.GetTypeTag() == ETokenType::HIEROGLYPH) {
                    continue;
                } else if (res.Has("wonly") && token.GetTypeTag() != ETokenType::WORD) {
                    continue;
                }
                TokenToJson(writer, token);
            }
        }
        writer.CloseArray();
        writer.CloseMap();
        writer.Flush();
    } else {
        TString line;
        while (input->ReadLine(line)) {
            TVector<TToken> tokens = FromUTF8Text(line);
            for (auto& token : tokens) {
                if (res.Has("remove-trash") && token.GetTypeTag() == ETokenType::HIEROGLYPH) {
                    continue;
                } else if (res.Has("wonly") && token.GetTypeTag() != ETokenType::WORD) {
                    continue;
                }
                output->Write(token.GetUTF8Data() + STRINGBUF("\n"));
                output->Flush();
            }
        }
        if (output != &Cout) {
            output->Finish();
        }
    }


    return 0;
}
