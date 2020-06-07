#include <han/maybe.hh>
#include <boost/ut.hpp>

template <typename T>
auto helper(bool present, T&& value) -> han::maybe<T> {
    if (present) return han::maybe{std::forward<T>(value)};
    else return std::nullopt;
}

class mocker {
    std::string expected;
    std::string copies;

    mocker(std::string expected_): expected(std::move(expected_)) {}

public:
    struct mocked {
        mocker& log;
        char x = 'z';

        mocked(mocker& log_, char x_): log(log_), x(x_) {}
        mocked(const mocked& o): log(o.log), x(o.x) { log.copy(x); }
        mocked(mocked&& o): log(o.log) { std::swap(x, o.x); }
    };

    ~mocker() {
        boost::ut::expect(boost::ut::that % expected == copies);
    }

    static inline auto expect_copies(std::string what) {
        return mocker(std::move(what));
    }

    auto mock(char x) { return mocked{*this, x}; }

private:
    auto copy(char x) -> void { copies += x; }
};

auto main() -> int {
    using namespace boost::ut;
    using namespace std::literals;

    "[copies in or_else()]"_test = [] {
        "lvalue a, lvalue b"_test = [] {
            "value present, copy a"_test = [] {
                auto m = mocker::expect_copies("a");
                auto a = helper(true, m.mock('a'));
                auto b = m.mock('b');
                expect(that % a.or_else(b).x == 'a');
            };
            "value missing, copy b"_test = [] {
                auto m = mocker::expect_copies("b");
                auto a = helper(false, m.mock('a'));
                auto b = m.mock('b');
                expect(that % a.or_else(b).x == 'b');
            };
        };
        "lvalue a, rvalue b"_test = [] {
            "value present, copy a"_test = [] {
                auto m = mocker::expect_copies("a");
                auto a = helper(true, m.mock('a'));
                auto b = m.mock('b');
                expect(that % a.or_else(std::move(b)).x == 'a');
            };
            "value missing, no copies"_test = [] {
                auto m = mocker::expect_copies("");
                auto a = helper(false, m.mock('a'));
                auto b = m.mock('b');
                expect(that % a.or_else(std::move(b)).x == 'b');
            };
        };
        "rvalue a, lvalue b"_test = [] {
            "value present, no copies"_test = [] {
                auto m = mocker::expect_copies("");
                auto a = helper(true, m.mock('a'));
                auto b = m.mock('b');
                expect(that % std::move(a).or_else(b).x == 'a');
            };
            "value missing, copy b"_test = [] {
                auto m = mocker::expect_copies("b");
                auto a = helper(false, m.mock('a'));
                auto b = m.mock('b');
                expect(that % std::move(a).or_else(b).x == 'b');
            };
        };
        "rvalue a, rvalue b"_test = [] {
            "value present, no copies"_test = [] {
                auto m = mocker::expect_copies("");
                auto a = helper(true, m.mock('a'));
                auto b = m.mock('b');
                expect(that % std::move(a).or_else(std::move(b)).x == 'a');
            };
            "value missing, no copies"_test = [] {
                auto m = mocker::expect_copies("");
                auto a = helper(false, m.mock('a'));
                auto b = m.mock('b');
                expect(that % std::move(a).or_else(std::move(b)).x == 'b');
            };
        };
    };

    return 0;
}
