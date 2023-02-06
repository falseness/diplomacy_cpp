#include <tuple>

using std::forward; // You can change this if you like unreadable code or care hugely about namespace pollution.

template<size_t N>
struct ApplyMember
{
    template<typename C, typename F, typename T, typename... A>
    static inline auto apply(C&& c, F&& f, T&& t, A&&... a) ->
    decltype(ApplyMember<N-1>::apply(forward<C>(c), forward<F>(f), forward<T>(t), std::get<N-1>(forward<T>(t)), forward<A>(a)...))
    {
        return ApplyMember<N-1>::apply(forward<C>(c), forward<F>(f), forward<T>(t), std::get<N-1>(forward<T>(t)), forward<A>(a)...);
    }
};

template<>
struct ApplyMember<0>
{
    template<typename C, typename F, typename T, typename... A>
    static inline auto apply(C&& c, F&& f, T&&, A&&... a) ->
    decltype((forward<C>(c)->*forward<F>(f))(forward<A>(a)...))
    {
        return (forward<C>(c)->*forward<F>(f))(forward<A>(a)...);
    }
};

// C is the class, F is the member function, T is the tuple.
template<typename C, typename F, typename T>
inline auto apply(C&& c, F&& f, T&& t) ->
decltype(ApplyMember<std::tuple_size<typename std::decay<T>::type>::value>::apply(forward<C>(c), forward<F>(f), forward<T>(t)))
{
    return ApplyMember<std::tuple_size<typename std::decay<T>::type>::value>::apply(forward<C>(c), forward<F>(f), forward<T>(t));
}
