#pragma once

// see: http://stackoverflow.com/a/13182321
// see: http://gcc.gnu.org/ml/gcc-help/2007-10/msg00328.html

/*
template<typename T, typename U> constexpr size_t offsetof_impl(U T::*member)
{
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}
*/

/*
template <typename T, typename U>
constexpr size_t offsetof_impl(T const* t, U T::* a)
{
	return (uintptr_t)t - (uintptr_t)&(t->*a) >= 0 ?
		(uintptr_t)t - (uintptr_t)&(t->*a) :
		(uintptr_t)&(t->*a) - (uintptr_t)t;
}
*/

#include <type_traits>

namespace stdext
{
    //
    // other
    //
    
    template <class... _> constexpr std::false_type always_false { };
    
	//
	// callables
	//

	// http://stackoverflow.com/a/22851790
	template <typename M>
	struct memptr
    {
	private:
		template <typename C, typename T>
		static T get_value_type(T C::*v);
		template <typename C, typename T>
		static C get_object_type(T C::*v);
	public:
		typedef decltype(get_value_type(static_cast<M>(nullptr))) type;
		typedef decltype(get_object_type(static_cast<M>(nullptr))) class_type;
	};

	//
	// templates
	//

	template <class T, template <class...> class Template>
	struct is_specialization : std::false_type { };

	template <template <class...> class Template, class... Args>
	struct is_specialization<Template<Args...>, Template> : std::true_type { };

	template <class T, template <class...> class Template>
    inline constexpr bool is_specialization_v = is_specialization<T, Template>::value;
    
	//
	// parameter packs
	//

	template <class T1, class ...T>
	struct parampack_first
	{
		typedef T1 type;
	};

	template <class T1, class ...T>
	struct parampack_last
	{
		typedef typename parampack_last<T...>::type type;
	};

	template <class T1>
	struct parampack_last<T1>
	{
		typedef T1 type;
	};

	//
	// detection
	//
    
    // https://blog.tartanllama.xyz/detection-idiom/
    
    namespace detail
    {
        template <template <class...> class Trait, class Enabler, class... Args>
        struct is_detected : std::false_type{};

        template <template <class...> class Trait, class... Args>
        struct is_detected<Trait, std::void_t<Trait<Args...>>, Args...> : std::true_type{};
    }

    template <template <typename...> typename Trait, typename... Args>
    using is_detected = typename detail::is_detected<Trait, void, Args...>::type;
    
    template <template <typename...> typename Trait, typename... Args>
    inline constexpr bool is_detected_v = is_detected<Trait, Args...>::value;
}
