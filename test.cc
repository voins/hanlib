#include <boost/ut.hpp>

auto main() -> int {
    using namespace boost::ut;

    "hello"_test = [] {
        expect(true);
    };

    return 0;
}
