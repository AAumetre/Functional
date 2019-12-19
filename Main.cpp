#include <iostream>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Def.h"

TEST_CASE("Increment a value"){
    CHECK_EQ(2, 2);
}

auto incr = [](const int value){
    return value + 1;
};

auto multDec = [](const int first){
    return [=](const int second){return first*second;};
};

TEST_CASE("Multiply and increment"){
    auto incMult = [](int first, int second){
        return pure::cmp(incr, multDec(first))(second);
    };

    CHECK_EQ(incMult(3,4), 13);
}

auto fourIncr = [](const int initial_value){
    return pure::cmp( incr, incr )(
            pure::cmp( incr, incr)(
                initial_value
                )
            );
};
TEST_CASE("Composition"){
    CHECK_EQ( fourIncr(6), 10 );
}
/*for (int i=0 ; i<10 ; ++i){
    
}*/


