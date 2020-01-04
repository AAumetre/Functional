#pragma once
#include <algorithm> 	// copy_if
#include <tuple> 	// tuple
#include <functional> // placeholders
#include <numeric> // iota

namespace pure{
    template< class CollectionType, class UnaryPredicate >
            const CollectionType filter(const CollectionType& input,
                            UnaryPredicate filter_function) {
                    CollectionType filtered;
                    std::copy_if(input.begin(), input.end(),
                                    std::back_inserter(filtered),
                                    filter_function);
                    return filtered;
            }

    /*template< typename T, template<class> class CollectionType>
            const T sum(const CollectionType<T>& input, const T& init = 0) {
                    return std::accumulate(input.begin(), input.end(), init);
            }*/

    template< typename T >
            bool ff_pair(T number) {
                    return (number%2 == 0);
            }

    const std::tuple< int, int > incrementBoth(const int& first,
            const int& second) {
            return std::make_tuple(first + 1, second + 1);
    }

    template< class F, class G>
    auto cmp( F f, G g){
        return [=](auto value){return f(g(value));};
    };

    // Applies std::transform to every element of "source", using the lambda
    template<typename Destination>
    auto transformAll = [](auto const& source, auto lambda){
        Destination result;
        result.reserve( source.size() );
        std::transform( source.begin(), source.end(), 
                std::back_inserter(result), lambda );
        return result;
    };

    // Creates a "range"
    // !!! was defined as a lambda in the example
    template< class T >
    std::vector<int> toRange( const T& collection ){
        std::vector<int> range( collection.size() );
        std::iota( begin(range), end(range), 0 );
        return range;
    }
    //template<const int n>
    std::vector<int> toRange( const int n ){
        std::vector<int> range( n );
        std::iota( begin(range), end(range), 0);
        return range;
    }

}

namespace ttt{
    using Line  = std::vector<char>;
    using Col   = std::vector<char>;
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





}
