#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include "../utils/integral_constant.hpp"

namespace ft {
	template <class T>
	struct is_integral : public ft::false_type {};

	template <class T>
	struct is_integral<const T> : public is_integral<T> {};
	template <class T>
	struct is_integral<volatile T> : public is_integral<T> {};
	template <class T>
	struct is_integral<const volatile T> : public is_integral<T> {};

	template <>
	struct is_integral<bool> : public ft::true_type {};
	template <>
	struct is_integral<char> : public ft::true_type {};
	template <>
	struct is_integral<signed char> : public ft::true_type {};
	template <>
	struct is_integral<unsigned char> : public ft::true_type {};
	template <>
	struct is_integral<wchar_t> : public ft::true_type {};
	// template <>
	// struct is_integral<char16_t> : public ft::true_type {};
	// template <>
	// struct is_integral<char32_t> : public ft::true_type {};
	template <>
	struct is_integral<short> : public ft::true_type {};
	template <>
	struct is_integral<unsigned short> : public ft::true_type {};
	template <>
	struct is_integral<int> : public ft::true_type {};
	template <>
	struct is_integral<unsigned int> : public ft::true_type {};
	template <>
	struct is_integral<long> : public ft::true_type {};
	template <>
	struct is_integral<unsigned long> : public ft::true_type {};
	// template <>
	// struct is_integral<long long> : public ft::true_type {};
	// template <>
	// struct is_integral<unsigned long long> : public ft::true_type {};
}

#endif
