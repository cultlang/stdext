#include "catch2/catch.hpp"

#include "stdext/to_hex_string.hpp"

#include <iostream>

TEST_CASE( "Can Build HexString", "[to_hex_string]" ) {
    uint8_t data[4] = {0, 1, 2, 3};
    REQUIRE( stdext::to_hex_string(data, 4) == "00010203");
}
