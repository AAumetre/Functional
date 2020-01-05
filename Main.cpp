#include <iostream>
#include <vector>
#include <functional> // for std::placeholders

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Pure.h"
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
                        initial_value ) );
};
TEST_CASE("Composition"){
    CHECK_EQ( fourIncr(6), 10 );
}

// ================================================================
// Starting to implement the TIC TAC TOE problem

const std::vector<char> board_x = { 'X', 'X', 'X',
                                    'X', 'X', 'X',
                                    'X', 'X', 'X'};


const std::vector<char> board = { 'X', ' ', 'O',
                                  'X', 'O', ' ',
                                  ' ', ' ', ' '};

auto isX = [](const char& elem){ return elem == 'X'; }; 
// Showcases  the use of std::all_of()
TEST_CASE("Is X?"){
    CHECK_EQ( std::all_of( board.begin(), board.end(), isX), false );
    CHECK_EQ( std::all_of( board_x.begin(), board_x.end(), isX), true );
}

auto lineFilledWithX = std::bind(
        ttt::lineFilledWith, std::placeholders::_1, 'X' );
auto lineFilledWithO = std::bind(
        ttt::lineFilledWith, std::placeholders::_1, 'O' );

// Tests the lineFilledWith method
TEST_CASE("Line filled with: token (X or O )"){
    const std::vector<char> all_x = {'X','X','X'};
    
    CHECK_EQ( ttt::lineFilledWith(all_x, 'X'), true );
    CHECK_EQ( lineFilledWithX(all_x), true );
    CHECK_EQ( lineFilledWithO(all_x), false );

    CHECK_EQ( ttt::getLine( board_x, 0), std::vector<char>{'X','X','X'} );
    CHECK_EQ( ttt::getLine( board, 1), std::vector<char>{'X','O',' '} );
}

// Testing the toRange function
TEST_CASE("Testing the toRange function"){
    CHECK_EQ( pure::toRange(board), std::vector<int>{0,1,2,3,4,5,6,7,8} );
    CHECK_EQ( pure::toRange(9), std::vector<int>{0,1,2,3,4,5,6,7,8} );
}

// Testing the getCol method
TEST_CASE("getCol method"){
    CHECK_EQ( ttt::getCol( board_x, 0), std::vector<char>{'X','X','X'} );
    CHECK_EQ( ttt::getCol( board,   1), std::vector<char>{' ','O',' '} );
}

// Testing the getDia method
TEST_CASE("getDia method"){
    CHECK_EQ( ttt::getDia( board_x, 0), std::vector<char>{'X','X','X'} );
    CHECK_EQ( ttt::getDia( board,   0), std::vector<char>{'X','O',' '} );
    CHECK_EQ( ttt::getDia( board,   1), std::vector<char>{'O','O',' '} );
}

TEST_CASE("toRange test"){
    CHECK_EQ( std::vector<int>{0,1,2,3,4}, pure::toRange(5) );
    CHECK_EQ( std::vector<int>{0,1,2,3,4,5,6,7,8}, pure::toRange(board) );
}


TEST_CASE("Concatenation test"){
    CHECK_EQ(   std::vector<int>{1,2,3,4},
                pure::concatenate(  std::vector<int>{1,2},
                                    std::vector<int>{3,4} ) );
}

// Testing all three
TEST_CASE("Retrieving lines, columns and diagonals"){
    SUBCASE( "Testing getAllLines"){
        std::vector< std::vector<char> > all_lines = ttt::getAllLines( board );
        for (int i=0 ; i<3 ; ++i ){
            CHECK_EQ( all_lines.at(i), ttt::getLine( board, i ) );
        }
    }
    SUBCASE( "Testing getAllCols"){
        std::vector< std::vector<char> > all_cols = ttt::getAllCols( board );
        for (int i=0 ; i<3 ; ++i ){
            CHECK_EQ( all_cols.at(i), ttt::getCol( board, i ) );
        }
    }
    SUBCASE( "Testing getAllDias"){
        std::vector< std::vector<char> > all_dias = ttt::getAllDias( board );
        for (int i=0 ; i<2 ; ++i ){
            CHECK_EQ( all_dias.at(i), ttt::getDia( board, i ) );
        }
    }
    SUBCASE( "Getting everything now" ){
        auto all_groups = ttt::getAllGroups( board );
        CHECK_EQ( all_groups,
                std::vector< std::vector<char> >{
                    {'X', ' ', 'O'},
                    {'X', 'O', ' '},
                    {' ', ' ', ' '},
                    {'X', 'X', ' '},
                    {' ', 'O', ' '},
                    {'O', ' ', ' '},
                    {'X', 'O', ' '},
                    {'O', 'O', ' '},
                });    
    }
}









