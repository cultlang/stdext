#include "catch2/catch.hpp"

#include "stdext/bindmem.hpp"


class Foo {

public:
    int doFoo() {return 0;}
};

TEST_CASE( "Can Bind Mem", "[bindmem]" ) {
    auto foo = new Foo();

    auto bound = stdext::bindmem(foo, &Foo::doFoo);

    REQUIRE( bound() == foo->doFoo());
}
