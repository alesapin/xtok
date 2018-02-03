#include <xtok/libs/token.h>
#include <library/unittest/registar.h>

using namespace NTokenizer;

SIMPLE_UNIT_TEST_SUITE(TTokenizeTest) {
    SIMPLE_UNIT_TEST(TestWord) {
        TUtf16String hi = UTF8ToWide("Привет");
        EGraphemTag t = EGraphemTag::CAP_START;
        t |= EGraphemTag::CYRILLIC; //= EGraphemTag::CAP_START | EGraphemTag::CYRILLIC;
        TVector<TToken> result = FromWideText(hi);
        UNIT_ASSERT_EQUAL(result.size(), 1);
        UNIT_ASSERT_EQUAL(result[0].GetTypeTag(), ETokenType::WORD);
        UNIT_ASSERT_EQUAL(result[0].GetWideData(), hi);
        UNIT_ASSERT_EQUAL(result[0].GetGraphemTag(), t);

        TUtf16String ohi = UTF8ToWide("ПрИвЕт");
        TVector<TToken> r = FromWideText(ohi);
        UNIT_ASSERT_EQUAL(r.size(), 1);
        EGraphemTag ot = EGraphemTag::MIXED;
        ot |= EGraphemTag::CYRILLIC;
        UNIT_ASSERT_EQUAL(r[0].GetTypeTag(), ETokenType::WORD);
        UNIT_ASSERT_EQUAL(r[0].GetWideData(), ohi);
        UNIT_ASSERT_EQUAL(r[0].GetGraphemTag(), ot);

        TUtf16String hi1 = UTF8ToWide("ПРИВЕТ");
        TVector<TToken> r1 = FromWideText(hi1);
        UNIT_ASSERT_EQUAL(r1.size(), 1);
        UNIT_ASSERT_EQUAL(r1[0].GetTypeTag(), ETokenType::WORD);
        EGraphemTag t1 = EGraphemTag::UPPER_CASE;
        t1 |= EGraphemTag::CYRILLIC;
        UNIT_ASSERT_EQUAL(r1[0].GetWideData(), hi1);
        UNIT_ASSERT_EQUAL(r1[0].GetGraphemTag(), t1);

        TUtf16String hi2 = UTF8ToWide("HeLLo");
        TVector<TToken> r2 = FromWideText(hi2);
        UNIT_ASSERT_EQUAL(r2.size(), 1);
        UNIT_ASSERT_EQUAL(r2[0].GetTypeTag(), ETokenType::WORD);
        EGraphemTag t2 = EGraphemTag::MIXED;
        t2 |= EGraphemTag::LATIN;
        UNIT_ASSERT_EQUAL(r2[0].GetWideData(), hi2);
        UNIT_ASSERT_EQUAL(r2[0].GetGraphemTag(), t2);

        TUtf16String hi3 = UTF8ToWide("приllo");
        TVector<TToken> r3 = FromWideText(hi3);
        UNIT_ASSERT_EQUAL(r3.size(), 1);
        UNIT_ASSERT_EQUAL(r3[0].GetTypeTag(), ETokenType::WORD);
        EGraphemTag t3 = EGraphemTag::LOWER_CASE;
        UNIT_ASSERT_EQUAL(r3[0].GetWideData(), hi3);
        UNIT_ASSERT_EQUAL(r3[0].GetGraphemTag(), t3);

        TUtf16String hi4 = UTF8ToWide("при123");
        TVector<TToken> r4 = FromWideText(hi4);
        UNIT_ASSERT_EQUAL(r4.size(), 1);
        UNIT_ASSERT_EQUAL(r4[0].GetTypeTag(), ETokenType::WORDNUM);
        UNIT_ASSERT_EQUAL(r4[0].GetWideData(), hi4);
        UNIT_ASSERT_EQUAL(r4[0].GetGraphemTag(), EGraphemTag::UNKNOWN);
    }

    SIMPLE_UNIT_TEST(TestNumber) {
        TUtf16String n = UTF8ToWide("1234");
        EGraphemTag t = EGraphemTag::NORMAL;
        TVector<TToken> r = FromWideText(n);
        UNIT_ASSERT_EQUAL(r.size(), 1);
        UNIT_ASSERT_EQUAL(r[0].GetWideData(), n);
        UNIT_ASSERT_EQUAL(r[0].GetGraphemTag(), t);

        //TUtf16String roman = UTF8ToWide("MMMCMXCIX"); TODO(bug, can't detect roman)
        //EGraphemTag romantag = EGraphemTag::ROMAN;
        //TVector<TToken> romans = FromWideText(roman);
        //Cerr << ToTagStr(romantag) << Endl;
        //Cerr << ToTagStr(romans[0].GetGraphemTag()) << Endl;
        //UNIT_ASSERT_EQUAL(romans.size(), 1);
        //UNIT_ASSERT_EQUAL(romans[0].GetWideData(), roman);
        //UNIT_ASSERT_EQUAL(romans[0].GetGraphemTag(), romantag);
    }
    SIMPLE_UNIT_TEST(TestPunct) {
        TUtf16String p = UTF8ToWide(",");
        EGraphemTag t = EGraphemTag::COMMA;
        TVector<TToken> r = FromWideText(p);
        UNIT_ASSERT_EQUAL(r.size(), 1);
        UNIT_ASSERT_EQUAL(r[0].GetWideData(), p);
        UNIT_ASSERT_EQUAL(r[0].GetGraphemTag(), t);

        TUtf16String p1 = UTF8ToWide("...");
        EGraphemTag t1 = EGraphemTag::THREE_DOTS;
        TVector<TToken> r1 = FromWideText(p1);
        UNIT_ASSERT_EQUAL(r1.size(), 1);
        UNIT_ASSERT_EQUAL(r1[0].GetWideData(), p1);
        UNIT_ASSERT_EQUAL(r1[0].GetGraphemTag(), t1);

        TUtf16String p3 = UTF8ToWide("?!");
        EGraphemTag t3 = EGraphemTag::QUESTION_MARK;
        TVector<TToken> r3 = FromWideText(p3);
        UNIT_ASSERT_EQUAL(r3.size(), 2);
        UNIT_ASSERT_EQUAL(r3[0].GetWideData(), UTF8ToWide("?"));
        UNIT_ASSERT_EQUAL(r3[0].GetGraphemTag(), t3);

        TUtf16String p4 = UTF8ToWide("----");
        EGraphemTag t4 = EGraphemTag::DASH;
        TVector<TToken> r4 = FromWideText(p4);
        UNIT_ASSERT_EQUAL(r4.size(), 4);
        UNIT_ASSERT_EQUAL(r4[0].GetWideData(), UTF8ToWide("-"));
        UNIT_ASSERT_EQUAL(r4[0].GetGraphemTag(), t4);
    }

    SIMPLE_UNIT_TEST(TestSeparator) {
        TUtf16String s = UTF8ToWide(" ");
        EGraphemTag t = EGraphemTag::SPACE;
        t |= EGraphemTag::SINGLE_SEP;
        TVector<TToken> r = FromWideText(s);
        UNIT_ASSERT_EQUAL(r.size(), 1);
        UNIT_ASSERT_EQUAL(r[0].GetWideData(), s);
        UNIT_ASSERT_EQUAL(r[0].GetGraphemTag(), t);

        TUtf16String s1 = UTF8ToWide("    ");
        EGraphemTag t1 = EGraphemTag::MULTI_SEP;
        TVector<TToken> r1 = FromWideText(s1);
        UNIT_ASSERT_EQUAL(r1.size(), 1);
        UNIT_ASSERT_EQUAL(r1[0].GetWideData(), s1);
        UNIT_ASSERT_EQUAL(r1[0].GetGraphemTag(), t1);

        TUtf16String s2 = UTF8ToWide(" \n");
        EGraphemTag t2 = EGraphemTag::MULTI_SEP;
        TVector<TToken> r2 = FromWideText(s2);
        UNIT_ASSERT_EQUAL(r2.size(), 1);
        UNIT_ASSERT_EQUAL(r2[0].GetWideData(), s2);
        UNIT_ASSERT_EQUAL(r2[0].GetGraphemTag(), t2);
    }
    SIMPLE_UNIT_TEST(TestSerious) {
        TUtf16String s = UTF8ToWide("Здарова МИХА 228. Я,было11 good... ツ\n");

        TVector<TToken> r = FromWideText(s);
        UNIT_ASSERT_EQUAL(r.size(), 16);

        TUtf16String fWord = UTF8ToWide("Здарова");
        UNIT_ASSERT_EQUAL(r[0].GetWideData(), fWord);
        UNIT_ASSERT_EQUAL(r[0].GetGraphemTag(), (EGraphemTag::CAP_START | EGraphemTag::CYRILLIC));

        TUtf16String sps = UTF8ToWide(" ");
        UNIT_ASSERT_EQUAL(r[1].GetWideData(), sps);
        UNIT_ASSERT_EQUAL(r[1].GetGraphemTag(), (EGraphemTag::SPACE | EGraphemTag::SINGLE_SEP));

        TUtf16String mih = UTF8ToWide("МИХА");
        UNIT_ASSERT_EQUAL(r[2].GetWideData(), mih);
        UNIT_ASSERT_EQUAL(r[2].GetGraphemTag(), (EGraphemTag::UPPER_CASE | EGraphemTag::CYRILLIC));

        TUtf16String tte = UTF8ToWide("228");
        UNIT_ASSERT_EQUAL(r[4].GetWideData(), tte);
        UNIT_ASSERT_EQUAL(r[4].GetGraphemTag(), EGraphemTag::NORMAL);

        TUtf16String dt = UTF8ToWide(".");
        UNIT_ASSERT_EQUAL(r[5].GetWideData(), dt);
        UNIT_ASSERT_EQUAL(r[5].GetGraphemTag(), EGraphemTag::DOT);

        TUtf16String w = UTF8ToWide("Я");
        UNIT_ASSERT_EQUAL(r[7].GetWideData(), w);
        UNIT_ASSERT_EQUAL(r[7].GetGraphemTag(), (EGraphemTag::UPPER_CASE | EGraphemTag::CYRILLIC));

        TUtf16String com = UTF8ToWide(",");
        UNIT_ASSERT_EQUAL(r[8].GetWideData(), com);
        UNIT_ASSERT_EQUAL(r[8].GetGraphemTag(), EGraphemTag::COMMA);

        TUtf16String bs = UTF8ToWide("было11");
        UNIT_ASSERT_EQUAL(r[9].GetWideData(), bs);
        UNIT_ASSERT_EQUAL(r[9].GetTypeTag(), ETokenType::WORDNUM);
        UNIT_ASSERT_EQUAL(r[9].GetGraphemTag(), EGraphemTag::UNKNOWN);

        TUtf16String g = UTF8ToWide("good");
        UNIT_ASSERT_EQUAL(r[11].GetWideData(), g);
        UNIT_ASSERT_EQUAL(r[11].GetGraphemTag(), (EGraphemTag::LOWER_CASE | EGraphemTag::LATIN));

        TUtf16String ddd = UTF8ToWide("...");
        UNIT_ASSERT_EQUAL(r[12].GetWideData(), ddd);
        UNIT_ASSERT_EQUAL(r[12].GetGraphemTag(), EGraphemTag::THREE_DOTS);

        TUtf16String hir = UTF8ToWide("ツ");
        UNIT_ASSERT_EQUAL(r[14].GetWideData(), hir);
        UNIT_ASSERT_EQUAL(r[14].GetTypeTag(), ETokenType::HIEROGLYPH);
        UNIT_ASSERT_EQUAL(r[14].GetGraphemTag(), EGraphemTag::UNKNOWN);

        TUtf16String last = UTF8ToWide("\n");
        UNIT_ASSERT_EQUAL(r[15].GetWideData(), last);
        UNIT_ASSERT_EQUAL(r[15].GetGraphemTag(), (EGraphemTag::NEW_LINE | EGraphemTag::SINGLE_SEP));

        TUtf16String p4 = UTF8ToWide("«Если тебе повезло, и ты в молодости жил в Париже, то, где бы ты ни был потом, он до конца дней твоих останется с тобой….» («Праздник, который всегда с тобой», 1960). Платонова раздражает, с моральной точки зрения, описание первой встречи лейтенанта Генри с медсестрой Кетрин Баркли — «циничный, грубоватый лаконизм изложения, «мужественное» пренебрежение первой пощёчиной, «многоопытная» уверенность в близком поцелуе» и т.д");
        TVector<TToken> r2 = FromWideText(p4);
        ui64 counter = 0;
        for (ui64 i = 0; i < r2.size(); ++i) {
            if (Contains(r2[i].GetTypeTag(), ETokenType::PUNCT)) {
                TToken pnct = r2[i];
                if (Contains(pnct.GetGraphemTag(), EGraphemTag::DOT)) {
                    counter++;
                }
            }
        }
        UNIT_ASSERT_EQUAL(counter, 3);
    }
    SIMPLE_UNIT_TEST(TestStrange) {
        TUtf16String s = UTF8ToWide(" = input.ReadLine()");
        TVector<TToken> r = FromWideText(s);
        UNIT_ASSERT_EQUAL(r.size(), 8);

        TUtf16String s1 = UTF8ToWide("GottaBeMobile.com");
        TVector<TToken> r1 = FromWideText(s1);
        UNIT_ASSERT_EQUAL(r1.size(), 3);
        UNIT_ASSERT_EQUAL(r1[2].GetTypeTag(), ETokenType::WORD);
    }
    SIMPLE_UNIT_TEST(TestMultiWord) {
        TUtf16String s = UTF8ToWide("салтыков-щедрин");
        TVector<TToken> r = FromWideText(s);
        UNIT_ASSERT_EQUAL(r.size(), 1);
        UNIT_ASSERT_EQUAL(r[0].GetWideData(), s);
        UNIT_ASSERT(Contains(r[0].GetGraphemTag(), EGraphemTag::MULTI_WORD));

        TUtf16String s1 = UTF8ToWide("-");
        TVector<TToken> r1 = FromWideText(s1);
        UNIT_ASSERT_EQUAL(r1.size(), 1);
        UNIT_ASSERT_EQUAL(r1[0].GetTypeTag(), ETokenType::PUNCT);

        TUtf16String s2 = UTF8ToWide("-x-y");
        TVector<TToken> r2 = FromWideText(s2);
        UNIT_ASSERT_EQUAL(r2.size(), 2);
        UNIT_ASSERT_EQUAL(r2[0].GetTypeTag(), ETokenType::PUNCT);
        UNIT_ASSERT_EQUAL(r2[1].GetWideData(), UTF8ToWide("x-y"));
        UNIT_ASSERT(Contains(r2[1].GetGraphemTag(), EGraphemTag::MULTI_WORD));

        TUtf16String s3 = UTF8ToWide("x-y-");
        TVector<TToken> r3 = FromWideText(s3);
        UNIT_ASSERT_EQUAL(r3.size(), 2);
        UNIT_ASSERT_EQUAL(r3[0].GetWideData(), UTF8ToWide("x-y"));
        UNIT_ASSERT(Contains(r[0].GetGraphemTag(), EGraphemTag::MULTI_WORD));
        UNIT_ASSERT_EQUAL(r3[1].GetTypeTag(), ETokenType::PUNCT);

        TUtf16String s4 = UTF8ToWide("Ростов-на-Дону");
        TVector<TToken> r4 = FromWideText(s4);
        UNIT_ASSERT_EQUAL(r4.size(), 1);
    }


}
