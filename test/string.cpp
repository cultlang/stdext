#include "catch2/catch.hpp"

#include "stdext/string.hpp"



TEST_CASE( "Can Trim Left", "ltrim" ) {
    REQUIRE( stdext::ltrim(std::string("   foo")) == std::string("foo"));
}


TEST_CASE( "Can Trim Right", "rtrim" ) {
    REQUIRE( stdext::rtrim(std::string("foo   ")) == std::string("foo"));
}

TEST_CASE( "Can Trim", "trim" ) {
    REQUIRE( stdext::trim(std::string("  foo   ")) == std::string("foo"));
}

TEST_CASE( "Can Split", "split" ) {
    std::vector<std::string> res;
    std::string cpp_src("1,2,3");
    std::string cpp_delim(",");

    auto c_src = "1,2,3";
    auto c_delim = ",";

    auto chr_delim = ',';

    SECTION( "String Source String delimiter") {
        stdext::split(cpp_src, cpp_delim, std::back_inserter(res));
        REQUIRE((
            res.size() == 3 &&
            res[0] == "1" && 
            res[1] == "2" &&
            res[2] == "3"
        ));
    }

    SECTION( "String Source CString delimiter") {
        stdext::split(cpp_src, c_delim, std::back_inserter(res));
        REQUIRE((
            res.size() == 3 &&
            res[0] == "1" && 
            res[1] == "2" &&
            res[2] == "3"
        ));
    }
}


TEST_CASE( "Can Join", "join" ) {
    std::vector<std::string> res {"1", "2", "3"};

    REQUIRE(stdext::join(std::string(","), res.begin(), res.end()) == "1,2,3");
}

TEST_CASE( "Can Starts With", "starts_with" ) {
    REQUIRE(stdext::starts_with(std::string("foobar"), std::string("foo")));
}

TEST_CASE( "Longest Common Prefix", "longest_common_prefix" ) {
    auto example = std::vector<std::string>{"JohnSmith", "JohnBrandt", "JohnFisher"};
    REQUIRE(stdext::longest_common_prefix(example.begin(), example.end()) == "John");
}