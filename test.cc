#include <han/maybe.hh>
#include <boost/ut.hpp>

template <typename T>
auto helper(bool present, T&& value) -> han::maybe<T> {
    if (present) return han::maybe{std::forward<T>(value)};
    else return std::nullopt;
}

auto main() -> int {
    using namespace boost::ut;

    "[maybe::or_else()]"_test = [] {
        "value present"_test = [] {
            expect(that % helper(true, 5).or_else(10) == 5);
        };
        "value missing"_test = [] {
            expect(that % helper(false, 5).or_else(10) == 10);
        };
    };

    return 0;
}
