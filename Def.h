#pragma once
#include <algorithm> 	// copy_if
#include <functional> // placeholders
#include <numeric> // iota


namespace ttt{
    using Line  = std::vector<char>;
    using Col   = std::vector<char>;
    using Board = std::vector<char>;
    const int board_size = 3;

    auto lineFilledWith = []( const auto& line, const auto token ){
        auto checkWithToken = [token](const auto& value){
            return value==token;
        };
        return std::all_of( line.begin(), line.end(), checkWithToken );
    };

    // Takes a line/column index and returns a vector with the corresponding
    // three board coordinates
    auto boardCoordinates = []( int group_index,
                                auto group_method ){
        const std::vector<int> range = pure::toRange(3);
        return pure::transformAll<std::vector<int>>( range, group_method );
    };

    auto getLine = [](const auto& board, const int line_index){
        // Defines the lambda to get board coordinates from line index
        auto L_line = [line_index]( int index ){
            return line_index*board_size + index;
        };
        std::vector<int> coord = boardCoordinates( line_index, L_line );
        // Return the corresponding symbols
        auto getter = [board](int a_coord){return board.at( a_coord );};
        return pure::transformAll<Col>(coord, getter);
    };
    
    auto getCol = [](const auto& board, const int col_index){
        // Defines the lambda to get board coordinates from col index
        auto L_col = [col_index]( int index ){
            return col_index + index*board_size;
        };
        std::vector<int> coord = boardCoordinates( col_index, L_col );
        // Return the corresponding symbols
        auto getter = [board](int a_coord){return board.at( a_coord );};
        return pure::transformAll<Col>(coord, getter);
    };

    // Diagonal getter, dia_index defined as follows:
    // 0: from top-left to bottom-right
    // 1: from top-right to bottom-left
    auto getDia = [](const auto& board, const int dia_index){
        // Defines the lambda to get board coordinates from diag index
        auto L_dia = [dia_index]( int index ){
            if (dia_index == 0 )
                return index*(board_size+1);
            else
                return board_size + index*(board_size-1) - 1;
        };
        std::vector<int> coord = boardCoordinates( dia_index, L_dia );
        // Return the corresponding symbols
        auto getter = [board](int a_coord){return board.at( a_coord );};
        return pure::transformAll<Col>(coord, getter);
    };

    auto getAllLines = []( const auto& board ){
        auto boundGetter = std::bind( getLine, board, std::placeholders::_1 );
        return pure::transformAll<std::vector<Line>>(
                pure::toRange( board_size ), boundGetter );
    };
    
    auto getAllCols = []( const auto& board ){
        auto boundGetter = std::bind( getCol, board, std::placeholders::_1 );
        return pure::transformAll<std::vector<Col>>(
                pure::toRange( board_size ), boundGetter );
    };
    
    auto getAllDias = []( const auto& board ){
        auto boundGetter = std::bind( getDia, board, std::placeholders::_1 );
        return pure::transformAll<std::vector<Line>>(
                pure::toRange( 2 ), boundGetter );
    };

    // Order is: lines, columns and diagonals, as a series of 3 elements
    auto getAllGroups = []( const auto& board ){
        auto all_groups = pure::concatenate(    getAllLines(board),
                                                getAllCols(board) );
        return pure::concatenate( all_groups, getAllDias(board) );
    };
    
    auto lineToString = [](const auto& line){
        return pure::transformAll<std::string>( line, 
                [](const auto tok)->char{ return tok; } );
    };

    auto boardToLineStrings = [](const auto& board)->std::vector<std::string>{
        return pure::transformAll<std::vector<std::string>>( board,
                lineToString );
    };

    auto boardToString = [](const auto board){
        auto lines_as_strings = boardToLineStrings( board );
        auto appendReturn = [](std::string current, std::string a_line){
            return current + a_line + "\n";
        };
        return pure::accumulateAll( lines_as_strings, appendReturn );
    };

    auto boardIsFull = []( const auto& board ){
        auto isBlank = [](const auto tok){return tok==' ';};
        // Problem here, anyOf(board,...) is a Line
        return !pure::anyOf( board, isBlank ); 
    };
}
