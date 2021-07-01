#pragma once

#include <memory>

#ifdef LIA_PLATFORM_WINDOWS
	
#else
	#error Liatris only support Windows!
#endif // LIA_PLATFORM_WINDOWS

#ifdef LIA_DEBUG
	#define LIA_ENABLE_ASSERTS
#endif // LIA_DEBUG


#ifdef LIA_ENABLE_ASSERTS
	#define LIA_ASSERT(x, ...) {if(!(x)) {LIA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define LIA_CORE_ASSERT(x, ...) {if(!(x)) {LIA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define LIA_ASSERT(x, ...)
	#define LIA_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LIA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Liatris
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}