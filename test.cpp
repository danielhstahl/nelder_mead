#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "neldermead.h"
#include <chrono>

TEST_CASE("Test nedlermead", "[cppoptlib]"){
    auto result=neldermead::optimize([](std::vector<double>& val){
        return val[0]*val[0];
    }, std::vector<double>({1.0}));
    auto parameters=std::get<neldermead::optparms>(result);
    REQUIRE(parameters[0]==Approx(0.0));
}
TEST_CASE("Test nedlermead multiple params", "[cppoptlib]"){
    auto started = std::chrono::high_resolution_clock::now();
    auto result=neldermead::optimize([](std::vector<double>& val){
        return val[0]*val[0]+val[1]*val[1]+val[2]*val[2]+val[3]*val[3];
    }, std::vector<double>({1.0, 1.0, 1.0, 1.0}));
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << "Speed: "<<std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count()<<std::endl;
    auto parameters=std::get<neldermead::optparms>(result);
    auto fnVal=std::get<neldermead::fnval>(result);
    REQUIRE(fnVal==Approx(0.0));
    REQUIRE(parameters[0]==Approx(0.0));
    REQUIRE(parameters[1]==Approx(0.0));
}