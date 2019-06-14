#include "catch2/catch.hpp"

#include "stdext/exception.h"

TEST_CASE( "Can Throw Exception", "[exception]" ) {
    try
    {
        throw stdext::exception("Throwing");
    }
    catch(stdext::exception e)
    {
        REQUIRE( true );
    }
}

TEST_CASE( "Can Format Exception", "[exception]" ) {
    try
    {
        throw stdext::exception("Throwing {}", 0);
    }
    catch(stdext::exception e)
    {
        REQUIRE( std::string(e.what()) == "Throwing 0" );
    }
}