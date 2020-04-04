#pragma once
#include <algorithm> 	// copy_if
#include <tuple> 	// tuple
#include <functional> // placeholders
#include <numeric> // iota
#include <optional> // nullopt & optional

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

    // Concatenation of vector of the same type
    auto concatenate = []( const auto& first, const auto& second ){
        auto result( first );
        result.insert(  result.end(), // add at the end
                        make_move_iterator( second.begin() ),
                        make_move_iterator( second.end() ) );
        return result;
    };

    // Applies std::any_of to an entire collection
    auto anyOf = []( const auto& collection, const auto& fn ){
        return std::any_of(collection.begin(), collection.end(), fn);
    };

    // Split a list into a list of size-sized lists
    /*template< typename T>
    auto split = []( T list, int size ){
        T<T> result;
        transformAll< T<T> >( list, 
        return result;
    };*/

    auto accumulateAll = [](auto source, auto lambda){
        return std::accumulate( source.begin(), source.end(),
                typename decltype(source)::value_type(),
                lambda );
    };

    auto findIf = [](const auto& coll, const auto& fn){
        auto result = std::find_if(coll.begin(), coll.end(), fn );
        return (result==coll.end()) ? std::nullopt : std::optional(*result);
    };

    auto noneOf = [](const auto& coll, auto& lambda){
        return std::none_of( coll.begin(), coll.end(), lambda );
    };
}
