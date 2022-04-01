#pragma once

namespace ft {
	// is_integral //
	template<typename _Tp, _Tp _v>
	struct integral_constant {
		typedef integral_constant<_Tp, _v>	type;
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template<typename>
	struct is_integral_h : public false_type {};
	template<>
	struct is_integral_h<bool> : public true_type {};
	template<>
	struct is_integral_h<char> : public true_type {};
	template<>
	struct is_integral_h<signed char> : public true_type {};
	template<>
	struct is_integral_h<unsigned char> : public true_type {};
	template<>
	struct is_integral_h<wchar_t> : public true_type {};
	template<>
	struct is_integral_h<short> : public true_type {};
	template<>
	struct is_integral_h<unsigned short> : public true_type {};
	template<>
	struct is_integral_h<int> : public true_type {};
	template<>
	struct is_integral_h<unsigned int> : public true_type {};
	template<>
	struct is_integral_h<long> : public true_type {};
	template<>
	struct is_integral_h<unsigned long> : public true_type {};
	template<>
	struct is_integral_h<long long> : public true_type {};
	template<>
	struct is_integral_h<unsigned long long> : public true_type {};

	template<typename _Tp>
	struct is_integral : public is_integral_h<_Tp>::type {};

	// enable_if //
	template<bool, typename _Tp = void>
    struct enable_if {};

	template<class _Tp>
    struct enable_if<true, _Tp> { typedef _Tp type; };
}
