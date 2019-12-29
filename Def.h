#pragma once
#include <algorithm> 	// copy_if
#include <tuple> 	// tuple
#include <functional> // placeholders

namespace pure{
    template< class CollectionType, class UnaryPredicate >
            const CollectionType filter(const CollectionType& input,
                            UnaryPredicate filter_function) {
                    CollectionType filtered;
                    std::copy_if(input.begin(), input.end(),
                                    std::back_inserter(filtered), filter_function);
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

    const std::tuple< int, int > incrementBoth(const int& first, const int& second) {
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
                std::back_insert(result), lambda );
        return result;
    };
}

namespace ttt{
    using Coordinates = std::pair<int,int>;
    using Line = std::vector<char>;

    auto lineFilledWith = [](const auto& line, const auto token){
        auto checkWithToken = [token](const auto& value){return value==token;};
        return std::all_of( line.begin(), line.end(), checkWithToken );
    };

    auto boardAt = [](const auto& board, std::pair<int,int> coord){
        const int board_size = 3;
        return board.at( coord.first + board_size*coord.second );
    };

    auto proCoordinates = [](const auto& board, const auto& coord){
        auto boardElem = std::bind( boardAt, board, std::placeholders _1 );
        return pure::transformAll<Line>( coord, boardElem );
    };

    /*auto line = []( const auto& board, int line_index ){
        return proCoordinates( board, 
    };
    auto name = [](){

    };
    auto name = [](){

    };
    auto name = [](){

    };

    auto getLine = [](const auto& board, const int line_index){
        
        
        return pure::transformAll<Line>(board, );
    };*/
}
