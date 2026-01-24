#pragma once

#include <memory>

#ifdef GE_PLATFORM_WINDOWS
	#if GE_DYNAMIC_LINK
		#ifdef GE_BUILD_DLL
			#define GAMEENGINE_API __declspec(dllexport)
		#else
			#define GAMEENGINE_API __declspec(dllimport)
		#endif
	#else
		#define GAMEENGINE_API
	#endif
#else
		#error GameEngine only supports Windows!
#endif

#ifdef GE_DEBUG
	#define GE_ENABLE_ASSERTS
#endif

#ifdef GE_ENABLE_ASSERTS
	// the x is the condition to be evaluated, the {0} is the message to be printed if the assertion fails
	// the __VA_ARGS__ is a special macro that allows us to pass a variable number of arguments to the macro
	// we use __debugbreak() to break into the debugger if the assertion fails
	#define GE_CORE_ASSERT(x, ...)\
		{ if(!(x)) {\
			GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);\
			__debugbreak();}\
		}
	#define GE_ASSERT(x, ...)\
		{ if(!(x)) {\
			GE_ERROR("Assertion Failed: {0}", __VA_ARGS__);\
			__debugbreak();}\
		}
#else
	#define GE_CORE_ASSERT(x, ...)
	#define GE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace GameEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}