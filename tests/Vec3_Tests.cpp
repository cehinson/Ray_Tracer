#include "catch2/catch.hpp"
#include "Vec3.h"

TEST_CASE("Vec3 operators work", "[Vec3]")
{
    using namespace ch;

    auto v1 = Vec3<>{1, 2, 3};
    auto v2 = Vec3<>{4, 5, 6};

    SECTION("[] operator")
    {
        REQUIRE(v1[0] == 1);
        REQUIRE(v1[1] == 2);
        REQUIRE(v1[2] == 3);
    }
}

