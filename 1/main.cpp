#include "modAlphaCipher.cpp"
#include "modAlphaCipher.h"
#include <UnitTest++/UnitTest++.h>
#include <locale>
using namespace std;
SUITE(KeyTest)
{
    TEST(ValidKey)
    {
        wstring q1 = L"ХЮПРПСР";
        wstring q2 = modAlphaCipher(L"ЕГОР").encrypt(L"РЫБАКОВ");
        if(q1 == q2) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST(LongKey)
    {
        wstring q3 = L"ХЮПР";
        wstring q4 = modAlphaCipher(L"РЫБАКОВ").encrypt(L"ЕГОР");
        if(q3 == q4) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST(LowCaseKey)
    {
        wstring q5 = L"ХЮПРПСР";
        wstring q6 = modAlphaCipher(L"ЕГОР").encrypt(L"рыбаков");
        if(q5 == q6) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST(DigitsInKey) { CHECK_THROW(modAlphaCipher cp(L"А1"), cipher_error); }
    TEST(PunctuationInKey) { CHECK_THROW(modAlphaCipher cp(L"Е,Г"), cipher_error); }
    TEST(WhitespaceInKey) { CHECK_THROW(modAlphaCipher cp(L"Е Г"), cipher_error); }
    TEST(EmptyKey) { CHECK_THROW(modAlphaCipher cp(L""), cipher_error); }
    TEST(WeakKey) { CHECK_THROW(modAlphaCipher cp(L"ААА"), cipher_error); }
}
struct KeyB_fixture {
    modAlphaCipher* p;
    KeyB_fixture() { p = new modAlphaCipher(L"СЕССИЯ"); }
    ~KeyB_fixture() { delete p; }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString)
    {
        wstring q7 = L"УЦЦЮШПЪЖЦДЁСАДЮСЪСЦХГЬИЮЯЕГДЩНЦТЪРЩДТДДСШНХФЪГАЗЬНБВСБЦЧЕВИТВЕТЕХАСССЖЧФ";
        wstring q8 = p->encrypt(L"ВСЕМПРИВЕТЭТОЯМАСТЕРСКАЯНАСТРОЕНИЯРЕБЯТАПОДПИСЧИКИПРИВЕТУРАУРАБУМБАМАХОХ");
        if(q7 == q8) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString)
    {
        wstring q9 = L"УЦЦЮШПЪЖЦДЁСАДЮСЪСЦХГЬИЮЯЕГДЩНЦТЪРЩДТДДСШНХФЪГАЗЬНБВСБЦЧЕВИТВЕТЕХАСССЖЧФ";
        wstring q10 = p->encrypt(L"всемприветэтоямастерскаянастроенияребятаподписчикиприветураурабумбамахох");
        if(q9 == q10) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct)
    {
        wstring q11 = L"УЦЦЮШПЪЖЦДЁСАДЮСЪСЦХГЬИЮЯЕГДЩНЦТЪРЩДТДДСШНХФЪГАЗЬНБВСБЦЧЕВИТВЕТЕХАСССЖЧФ";
        wstring q12 = p->encrypt(
            L"ВСЕМ ПРИВЕТ, ЭТО Я - МАСТЕРСКАЯ НАСТРОЕНИЯ, РЕБЯТА ПОДПИСЧИКИ ПРИВЕТ УРА, УРА. БУМ .БАМ АХ ОХ");
        if(q11 == q12) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers)
    {
        wstring q13 = L"ЦЗАВ";
        wstring q14 = p->encrypt(L"Егор52");
        if(q13 == q14) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) { CHECK_THROW(p->encrypt(L""), cipher_error); }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) { CHECK_THROW(p->encrypt(L"7777"), cipher_error); }
    TEST(MaxShiftKey)
    {
        wstring q15 = L"БРДЛОПЗБДСЬСНЮЛЯРСДПРЙЯЮМЯРСПНДМЗЮПДАЮСЯОНГОЗРЦЗЙЗОПЗБДСТПЯТПЯАТЛАЯЛЯФНФ";
        wstring q16 = modAlphaCipher(L"Я").encrypt(
            L"ВСЕМПРИВЕТЭТОЯМАСТЕРСКАЯНАСТРОЕНИЯРЕБЯТАПОДПИСЧИКИПРИВЕТУРАУРАБУМБАМАХОХ");
        if(q15 == q16) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString)
    {
        wstring q17 = L"ВСЕМПРИВЕТЭТОЯМАСТЕРСКАЯНАСТРОЕНИЯРЕБЯТАПОДПИСЧИКИПРИВЕТУРАУРАБУМБАМАХОХ";
        wstring q18 = p->decrypt(L"УЦЦЮШПЪЖЦДЁСАДЮСЪСЦХГЬИЮЯЕГДЩНЦТЪРЩДТДДСШНХФЪГАЗЬНБВСБЦЧЕВИТВЕТЕХАСССЖЧФ");
        if(q17 == q18) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) { CHECK_THROW(p->decrypt(L"приветмедвед"), cipher_error); }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString)
    {
        CHECK_THROW(p->decrypt(L"привет, медвед"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString)
    {
        CHECK_THROW(p->decrypt(L"ПРИВЕТМЕДВЕД12345"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) { CHECK_THROW(p->decrypt(L":?!№;"), cipher_error); }
    TEST_FIXTURE(KeyB_fixture, EmptyString) { CHECK_THROW(p->decrypt(L""), cipher_error); }
    TEST(MaxShiftKey)
    {
        wstring q19 = L"ВСЕМПРИВЕТЭТОЯМАСТЕРСКАЯНАСТРОЕНИЯРЕБЯТАПОДПИСЧИКИПРИВЕТУРАУРАБУМБАМАХОХ";
        wstring q20 = modAlphaCipher(L"Я").decrypt(
            L"БРДЛОПЗБДСЬСНЮЛЯРСДПРЙЯЮМЯРСПНДМЗЮПДАЮСЯОНГОЗРЦЗЙЗОПЗБДСТПЯТПЯАТЛАЯЛЯФНФ");
        if(q19 == q20) {
            CHECK(true);
        } else {
            CHECK(false);
        }
    }
}
int main(int argc, char** argv)
{
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    return UnitTest::RunAllTests();
}
