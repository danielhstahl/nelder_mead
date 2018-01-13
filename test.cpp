#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "neldermead.h"

TEST_CASE("Test nedlermead", "[cppoptlib]"){
    auto result=neldermead::Simplex([](std::vector<double>& val){
        return val[0]*val[0];
    }, std::vector<double>({1.0}));
    REQUIRE(result[0]==Approx(0.0));
}
TEST_CASE("Test nedlermead multiple params", "[cppoptlib]"){
    auto result=neldermead::Simplex([](std::vector<double>& val){
        return val[0]*val[0]+val[1]*val[1];
    }, std::vector<double>({1.0, 1.0}));
    REQUIRE(result[0]==Approx(0.0));
    REQUIRE(result[1]==Approx(0.0));
}