#include "catch2/catch.hpp"

#include "stdext/platform_windows.h"

#include <iostream>

#ifdef _WIN32
TEST_CASE( "No Error is Empty", "[platform_windows]" ) {
    auto err = stdext::platform::windows::GetLastErrorAsString();
    
    REQUIRE( err == "");
}

TEST_CASE( "Windows Errors Produce Strings", "[platform_windows]" ) {
    auto notADll = LoadLibraryA("sdjlfksldkfjsdlfkjsdf.dll");

    auto err = stdext::platform::windows::GetLastErrorAsString();
    REQUIRE( err.size() != 0);
}

#endif
