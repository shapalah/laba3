#include "Cipher.cpp"
#include "cipher.h"
#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <locale>
#include <string>

SUITE(KeyTest)
{
    TEST(ValidKey)
    {
        cipher c(3);
        CHECK_EQUAL(c.encrypt("RYBAKOV"), "BOYKRAV");
    }
    TEST(InvalidKey) { CHECK_THROW(cipher c(-10), cipher_error); }
    TEST(FloatKey) { CHECK_THROW(cipher c(-36.6), cipher_error); }
    TEST(BigKey)
    {
        cipher c(50);
        CHECK_EQUAL(c.encrypt("RYBAKOV"), "VOKABYR");
    }

    TEST(KeyIsOne)
    {
        cipher c(1);
        CHECK_EQUAL("RYBAKOV", c.encrypt("RYBAKOV"));
    }
}
SUITE(EncryptTest)
{

    TEST(UpString)
    {
        cipher c(5);
        CHECK_EQUAL("TKARRTO", c.encrypt("TRAKTOR"));
    }
    TEST(LowString)
    {
        cipher c(5);
        CHECK_EQUAL("traktor", c.encrypt("TKARRTO"));
    }

    TEST(EmptyString)
    {
        cipher c(5);
        CHECK_THROW(c.encrypt(""), cipher_error);
    }

    TEST(DigestText)
    {
        cipher c(5);
        CHECK_EQUAL("GAADLO", c.encrypt("TRAKTOR2005"));
    }
    TEST(PunctuationUndSpaceText)
    {
        cipher c(5);
        CHECK_EQUAL("TKARRTO", c.encrypt("tra12k3t or"));
    }

    TEST(SpaceTextBeginEnd)
    {
        cipher c(5);
        CHECK_EQUAL("TKARRTO", c.encrypt(" TRAKTOR   "));
    }
}

SUITE(DecryptTest)
{
    TEST(UpString)
    {
        cipher c(5);
        CHECK_EQUAL("TRAKTOR", c.decrypt("TKARRTO"));
    }
    TEST(LowString)
    {
        cipher c(5);
        CHECK_EQUAL("tkarrto", c.decrypt("TRAKTOR"));
    }

    TEST(EmptyString)
    {
        cipher c(5);
        CHECK_THROW(c.decrypt(""), cipher_error);
    }
    TEST(DigestText)
    {
        cipher c(5);
        CHECK_EQUAL("TKARRTO2005", c.decrypt("TRAKTOR"));
    }
    TEST(PunctuationUndSpaceText)
    {
        cipher c(5);
        CHECK_EQUAL("T K A R R T, O", c.decrypt("TRAKTOR"));
    }

    TEST(NonAsciiDecrypt)
    {
        cipher c(5);
        CHECK_EQUAL("TRAKTOR", c.decrypt("TKARRTOпрвет"));
    }
    TEST(SpaceTextBeginEndDecrypt)
    {
        cipher c(5);
        CHECK_EQUAL("TRAKTOR", c.decrypt("  TKARRTO  "));
    }
}

int main() { return UnitTest::RunAllTests(); }
