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

	return sqrt(((gameObject1.colliderBox.x - gameObject2.colliderBox.x) * (gameObject1.colliderBox.x - gameObject2.colliderBox.x)) + ((gameObject1.colliderBox.y - gameObject2.colliderBox.y) * (gameObject1.colliderBox.y - gameObject2.colliderBox.y)));
}

#endif
