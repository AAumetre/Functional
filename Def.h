#pragma once
#include <algorithm> 	// copy_if
#include <tuple> 	// tuple

namespace pure {
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

}
