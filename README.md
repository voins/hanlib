Why
===
I don't like `std::optional`. I mean it's cool at solving one problem: turning
an undefined behavior of dereferencing a `nullptr` into defined behavior of
dereferencing `std::optional`. Effectively converting `SIGSEGV` into an
exception. But it doesn't help me make my code cleaner. I still need to check if
that thing contains some value and if I fail to remember, I have a bug.

How
===
The pattern could be found in other languages. But the general idea is that it
should be impossible to access the value without the check.

API
===
```C++
template <typename T> class maybe;
```

```C++
auto maybe<T>::then_do([](T&&) -> void { ... }) -> maybe<T>;
```

```C++
template <typename R>
auto maybe<T>::then_do([](T&&) -> R { ... }) -> maybe<R>;
```

```C++
template <typename R>
auto maybe<T>::then_maybe([](T&&) -> maybe<R> { ... }) -> maybe<R>;
```

```C++
auto maybe<T>::or_else(T) -> T
```

```C++
auto maybe<T>::or_else_do([]{ ... }) -> maybe<T>;
```

```C++
auto maybe<T>::or_else_do([]() -> T { ... }) -> maybe<T>;
```

```C++
auto maybe<T>::or_maybe([]() -> maybe<T> { ... }) -> maybe<T>;
```