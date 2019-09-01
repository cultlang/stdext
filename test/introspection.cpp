#include "catch2/catch.hpp"

#include "stdext/introspection.hpp"

#include <vector>
#include <list>

TEST_CASE( "is_specialization tests", "[introspection]" ) {
    CHECK( stdext::is_specialization<int, std::list>::value == false );
    CHECK( stdext::is_specialization<std::vector<int>, std::list>::value == false );
    CHECK( stdext::is_specialization<std::vector<int>, std::vector>::value == true );
}

// see: https://stackoverflow.com/questions/50905808/getting-non-const-iterator-using-declval
template<typename T>
auto _wrapped_begin(T t)
{
  using std::begin;
  return begin(std::forward<T>(t));
}

template<typename T>
auto _wrapped_end(T t)
{
  using std::end;
  return end(std::forward<T>(t));
}

template <typename T>
using has_begin = decltype(_wrapped_begin<T>(std::declval<T>()));

template <typename T>
using has_end = decltype(_wrapped_end<T>(std::declval<T>()));

template <typename T, typename ...Ts>
using has_constructor = decltype(new T (std::declval<Ts>()...));

template <typename T, typename ...Ts>
using has_push_back = decltype(std::declval<T>().push_back(std::declval<Ts>()...));

TEST_CASE( "is_detected tests", "[introspection]" ) {
    CHECK( stdext::is_detected<has_begin, std::vector<int>>::value == true );
    CHECK( stdext::is_detected<has_end, std::vector<int>>::value == true );
    CHECK( stdext::is_detected<has_push_back, std::vector<int>, int>::value == true );
    
    CHECK( stdext::is_detected<has_begin, std::vector<int> const&>::value == true );
    CHECK( stdext::is_detected<has_end, std::vector<int> const&>::value == true );
    CHECK( stdext::is_detected<has_push_back, std::vector<int> const&, int>::value == false );
    
    CHECK( stdext::is_detected<has_constructor, std::vector<int>>::value == true );
    CHECK( stdext::is_detected<has_constructor, std::vector<int>, std::vector<int> const&>::value == true );
}
