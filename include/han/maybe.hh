#ifndef HAN_MAYBE_HH
#define HAN_MAYBE_HH
#include <optional>
#include <functional>

namespace han {
    template <typename T>
    class maybe {
        std::optional<T> data;

    public:
        constexpr maybe() noexcept = default;
        constexpr maybe(std::nullopt_t) noexcept {}
        constexpr explicit maybe(T value): data(std::move(value)) {}
        constexpr maybe(const maybe&) = default;
        constexpr maybe(maybe&&) = default;

        constexpr auto or_else(T alt) const -> T {
            if (data) return *data;
            else return alt;
        }

        template <typename C,
                  typename R = std::result_of_t<C(T)>>
        constexpr auto then_do(C&& code) const -> maybe<R> {
            if (data) return maybe<R>{std::invoke(std::forward<C>(code), *data)};
            else return maybe<R>{std::nullopt};
        }
    };

    template <typename T> maybe(T) -> maybe<T>;
}

#endif
