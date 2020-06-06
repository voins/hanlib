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

    "[maybe::or_else()]"_test = [] {
        "value present"_test = [] {
            expect(that % helper(true, 5).or_else(10) == 5);
        };
        "value missing"_test = [] {
            expect(that % helper(false, 5).or_else(10) == 10);
        };
    };

    "[maybe::then_do()]"_test = [] {
        "value present"_test = [] {
            auto value = helper(true, 5).then_do([](auto&& x) { return x * 3; });
            expect(that % value.or_else(10) == 15);
        };

        "value missing"_test = [] {
            auto value = helper(false, 5).then_do([](auto&& x) { return x * 3; });
            expect(that % value.or_else(10) == 10);
        };
    };

    "[maybe::then_do() changes type]"_test = [] {
        "value present"_test = [] {
            auto value = helper(true, 5).then_do([](auto&&) { return "aaa"s; });
            expect(that % value.or_else("bbb"s) == "aaa"s);
        };

        "value missing"_test = [] {
            auto value = helper(false, 5).then_do([](auto&&) { return "aaa"s; });
            expect(that % value.or_else("bbb"s) == "bbb"s);
        };
    };

    return 0;
}
