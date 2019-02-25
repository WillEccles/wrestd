#ifndef WRESTD_MATH_H
#define WRESTD_MATH_H

namespace wrestd {
	namespace math {
		namespace compiletime {
			// compile-time factorial "function."
			// this is done with template metaprogramming.
			// usage: factorial<12>::value would be the factorial of 12
			template<unsigned int x>
			struct factorial {
				enum { value = x * wrestd::math::factorial<x-1>::value };
			};
			template<>
			struct factorial<1> {
				enum { value = 1 };
			};
		};

#if __cplusplus >= 201103L
		// constexpr factorial function (C++11 or higher)
		constexpr unsigned int constfactorial(unsigned int x) {
			return x <= 1 ? 1 : x * constfactorial(x-1);
		};
#endif

		// non-constexpr factorial function
		inline unsigned int factorial(unsigned int x) {
			return x <= 1 ? 1 : x * factorial(x-1);
		};

		// clamp a value between a minimum and maximum (inclusive of each)
		template <typename T>
		inline T clamp(T val, T min, T max)
		{
			if (val > max)
				return max;
			if (val < min)
				return min;
			return val;
		};

		// confirm that a value is less than or equal to a max value
		template <typename T>
		inline T clamp_upper(T val, T max)
		{
			return (val > max ? max : val);
		};

		// confirm that a value is greater than or equal to a minimum value
		template <typename T>
		inline T clamp_lower(T val, T min)
		{
			return (val < min ? min : val);
		};
	};
};

#endif // include guard