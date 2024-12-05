/**
 * @file macros.h
 * @brief Provides helper macros for compile-time optimizations.
 * 
 * This header defines a set of macros and functions that aid in compile-time
 * optimizations by expanding templates, counting variadic arguments, and 
 * detecting if variadic arguments are present or empty.
 */

#ifndef MACROS_H
#define MACROS_H

/**
 * @brief Expands a macro argument.
 * 
 * This macro ensures that the provided argument is fully expanded 
 * during macro substitution.
 * 
 * @param x The macro argument to expand.
 */
#define _EXPAND(x) x

/**
 * @brief Counts the number of arguments in a variadic template pack.
 * 
 * This constexpr function returns the number of arguments in a given
 * variadic template pack at compile time.
 * 
 * @tparam ...T A variadic template pack.
 * @param ... Parameters whose count is to be determined.
 * @return The number of parameters in the variadic pack.
 */
template<typename... T>
constexpr size_t _ARG_COUNT_(T...) { 
    return sizeof...(T); 
}

/**
 * @brief Detects if a variadic argument pack is empty.
 * 
 * This macro evaluates to `true` if the given `__VA_ARGS__` pack is empty.
 * 
 * @param ... The variadic arguments to check.
 * @return A boolean value indicating if the pack is empty.
 */
#define _VA_EMPTY_(...) (_ARG_COUNT_(__VA_ARGS__) == 0)

/**
 * @brief Detects if a variadic argument pack contains arguments.
 * 
 * This macro evaluates to `true` if the given `__VA_ARGS__` pack contains 
 * at least one argument.
 * 
 * @param ... The variadic arguments to check.
 * @return A boolean value indicating if the pack has arguments.
 */
#define _VA_HAS_ARGS(...) (_ARG_COUNT_(__VA_ARGS__) != 0)

#endif // MACROS_H