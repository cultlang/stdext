#include "catch2/catch.hpp"

#include "stdext/to_hex_string.hpp"

#include <iostream>

TEST_CASE( "Can Build HexString", "[to_hex_string]" ) {
    uint32_t number = 0x00B1C2D3;
    CHECK( stdext::to_hex_string(number, false, true) == "00b1c2d3");
    CHECK( stdext::to_hex_string(number, false, false) == "d3c2b100");
    CHECK( stdext::to_hex_string(number, true, true) == "00B1C2D3");
    CHECK( stdext::to_hex_string(number, true, false) == "D3C2B100");
}
