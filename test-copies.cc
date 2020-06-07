#include <han/maybe.hh>
#include <boost/ut.hpp>

template <typename T>
auto helper(bool present, T&& value) -> han::maybe<T> {
    if (present) return han::maybe{std::forward<T>(value)};
    else return std::nullopt;
}

auto main() -> int {
    using namespace boost::ut;
    using namespace std::literals;


    return 0;
}
