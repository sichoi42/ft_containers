#ifndef INTEGRAL_CONSTANT_HPP
# define INTEGRAL_CONSTANT_HPP

namespace ft {
	template <class T, T v>
	struct integral_constant {
		typedef T												value_type;
		typedef integral_constant				type;

		static const T value = v;

		operator value_type() const {
			return value;
		}

		value_type operator()() const {
			return value;
		}
	};

	typedef ft::integral_constant<bool, true> true_type;
	typedef ft::integral_constant<bool, false> false_type;
}

#endif
