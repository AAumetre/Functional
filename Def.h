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
    // using Coordinates = std::pair<int,int>;
    using Line  = std::vector<char>;
    using Col   = std::vector<char>;
    const int board_size = 3;

    auto lineFilledWith = []( const auto& line, const auto token ){
        auto checkWithToken = [token](const auto& value){return value==token;};
        return std::all_of( line.begin(), line.end(), checkWithToken );
    };

    auto boardAt = []( const auto& board, std::pair<int,int> coord ){
        return board.at( coord.first + board_size*coord.second );
    };

    auto proCoordinates = []( const auto& board, const auto& coord ){
        auto boardElem = std::bind( boardAt, board, std::placeholders::_1 );
        return pure::transformAll<Line>( coord, boardElem );
    };

    // Takes a line index and returns a vector with the corresponding
    // three board coordinates
    auto lineCoordinates = []( const auto& board, auto line_index ){
        const std::vector<int> range = pure::toRange(3);
        return pure::transformAll<std::vector<int>>( range,
            [line_index](auto index){
                return index + line_index*board_size;
            });
    };
    
    // Takes a column index and returns a vector with the corresponding
    // three board coordinates
    auto colCoordinates = []( const auto& board, auto col_index ){
        const std::vector<int> range = {0, 1, 2};
        // Return the correct vector index
        auto getter = [col_index](auto index){
            return col_index + index*board_size;
        };
        // Apply a transformation
        return pure::transformAll<std::vector<int>>( range, getter );
    };

    auto getLine = [](const auto& board, const int line_index){
        // Get indexes corresponding to that line
        std::vector<int> coord = lineCoordinates( board, line_index );
        // Return the corresponding symbols
        auto getter = [board](int a_coord){return board.at( a_coord );};
        return pure::transformAll<Line>(coord, getter);
    };
    
    auto getCol = [](const auto& board, const int col_index){
        // Get indexes corresponding to that column
        std::vector<int> coord = colCoordinates( board, col_index );
        // Return the corresponding symbols
        auto getter = [board](int a_coord){return board.at( a_coord );};
        return pure::transformAll<Col>(coord, getter);
    };
}
