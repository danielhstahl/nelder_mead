#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "neldermeadsolver.h"
#include "neldermead2.h"
TEST_CASE("Test getItemAt", "[cppoptlib]"){
    std::vector<std::vector<double> > myTestV(4, std::vector<double>(3, 0));
    myTestV[0][0]=1;
    myTestV[1][0]=2;
    myTestV[2][0]=3;
    myTestV[3][0]=4;
    myTestV[0][1]=11;
    myTestV[1][1]=12;
    myTestV[2][1]=13;
    myTestV[3][1]=14;
    myTestV[0][2]=21;
    myTestV[1][2]=22;
    myTestV[2][2]=23;
    myTestV[3][2]=24;
    std::vector<double> myV(12, 0);
    myV[0]=1;
    myV[1]=2;
    myV[2]=3;
    myV[3]=4;
    myV[4]=11;
    myV[5]=12;
    myV[6]=13;
    myV[7]=14;
    myV[8]=21;
    myV[9]=22;
    myV[10]=23;
    myV[11]=24;
    for(int i=0; i<4;++i){
        for(int j=0; j<3; ++j){
            REQUIRE(myTestV[i][j]==Approx(cppoptlib::getItemAt(i, j, 4, myV)));
        }
    }
}
TEST_CASE("Test getRowAsVector", "[cppoptlib]"){
    std::vector<double> myTestV1(4, 0.0);
    myTestV1[0]=1;
    myTestV1[1]=2;
    myTestV1[2]=3;
    myTestV1[3]=4;
    std::vector<double> myTestV2(4, 0.0);
    myTestV2[0]=11;
    myTestV2[1]=12;
    myTestV2[2]=13;
    myTestV2[3]=14;

    std::vector<double> myV(12, 0);
    myV[0]=1;
    myV[1]=2;
    myV[2]=3;
    myV[3]=4;
    myV[4]=11;
    myV[5]=12;
    myV[6]=13;
    myV[7]=14;
    myV[8]=21;
    myV[9]=22;
    myV[10]=23;
    myV[11]=24;

    auto myRow=cppoptlib::getColumnAsVector(myV, 0, 4);
    for(int i=0; i<4; ++i){
        REQUIRE(myTestV1[i]==Approx(myRow[i]));
    }
    myRow=cppoptlib::getColumnAsVector(myV, 1, 4);
    for(int i=0; i<4; ++i){
        REQUIRE(myTestV2[i]==Approx(myRow[i]));
    }
    

}
TEST_CASE("Test setItemAt", "[cppoptlib]"){
    std::vector<double> testV({1, 2, 3});
    testV=cppoptlib::setItemAt(1, 1, 1, 4.0, std::move(testV));
    REQUIRE(testV[2]==Approx(4.0));
}
TEST_CASE("Test makeInitialSimplex", "[cppoptlib]"){
    std::vector<double> testV({1, 2, 3});
    auto result=cppoptlib::makeInitialSimplex(testV);
    for(auto& v:result){
        std::cout<<"v: "<<v<<std::endl;
    }
}
TEST_CASE("Test getMaxCoefOfDiff", "[cppoptlib]"){
    std::vector<double> col1({1, 3, 2});
    std::vector<double> col2({2, 6, 4});
    auto maxDiff=cppoptlib::getMaxCoefOfDiff(std::move(col1), std::move(col2));
    REQUIRE(maxDiff==Approx(3.0));
}

TEST_CASE("Test nedlermead2", "[cppoptlib]"){
    auto result=BT::Simplex([](std::vector<double>& val){
        return val[0]*val[0];
    }, std::vector<double>({1.0}));
    REQUIRE(result[0]==Approx(0.0));
}
TEST_CASE("Test nedlermead2 multiple params", "[cppoptlib]"){
    auto result=BT::Simplex([](std::vector<double>& val){
        return val[0]*val[0]+val[1]*val[1];
    }, std::vector<double>({1.0, 1.0}));
    REQUIRE(result[0]==Approx(0.0));
    REQUIRE(result[1]==Approx(0.0));
}