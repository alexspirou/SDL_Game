#ifndef __MATH_h_
#define __MATH_h_
#ifdef __MATH_EXPORTS
#define __MATH_API __declspec(dllexport)
#else __MATH_API
#define __MATH_API __declspec(dllexport)
#endif
#include "../Collision/ColliderBox.h"

__MATH_API inline double calculateLength(ColliderBox& gameObject1, ColliderBox& gameObject2)
{

	return sqrt(((gameObject1.x - gameObject2.x) * (gameObject1.x - gameObject2.x)) + ((gameObject1.y - gameObject2.y) * (gameObject1.y - gameObject2.y)));
}

#endif
