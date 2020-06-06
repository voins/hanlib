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
                  typename R = std::result_of_t<C(T)>,
                  typename = std::enable_if_t<!std::is_void_v<R>>>
        constexpr auto then_do(C&& code) const -> maybe<R> {
            if (data) return maybe<R>{std::invoke(std::forward<C>(code), *data)};
            else return maybe<R>{std::nullopt};
        }

        template <typename C,
                  typename R = std::result_of_t<C(T)>,
                  typename = std::enable_if_t<std::is_void_v<R>>>
        constexpr auto then_do(C&& code) const -> maybe<T> {
            if (data) std::invoke(std::forward<C>(code), *data);
            return *this;
        }

        template <typename C,
                  typename R = std::result_of_t<C()>,
                  typename = std::enable_if_t<!std::is_void_v<R>>,
                  typename = std::enable_if_t<std::is_same_v<R, T>>>
        constexpr auto or_else_do(C&& code) const -> maybe<T> {
            if (!data) return maybe<T>{std::invoke(std::forward<C>(code))};
            else return *this;
        }

        template <typename C,
                  typename R = std::result_of_t<C()>,
                  typename = std::enable_if_t<std::is_void_v<R>>>
        constexpr auto or_else_do(C&& code) const -> maybe<T> {
            if (!data) std::invoke(std::forward<C>(code));
            return *this;
        }
    };

    template <typename T> maybe(T) -> maybe<T>;
}

#endif
