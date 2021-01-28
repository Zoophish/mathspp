**Some C++ header only mathematical type templates and utilities I use in personal projects.**

To use, just `#include <mathspp/maths.hpp>`.


**Template Types**

|  Type     |                   Description                  |
|-----------|:----------------------------------------------:|
|  vec3<>   | 3D Vector                                      |
|  vec2<>   | 2D Vector                                      |
| affine3<> | 3x3 affine transformation matrix & translation |
| bounds<>  | 3D axis-aligned bounding box                   |

** Generic Types **

|  Type     |   Description    |
|-----------|:----------------:|
|   Real    | `float`          |
|   Vec3    | `vec3<Real>`     |
|   Vec2    | `vec2<Real>`     |
|  Affine3  | `affine3<Real>`  |
|  Bounds   | `bounds<Real>`   |


**Utility functions**

|                   Function                        |
|---------------------------------------------------|
|  Clamp(*x, min, max*)                             |
|  Lerp(*a, b, ratio*)                              |
|  BarycentricInterpolation(*p0, p1, p2, u, v*)     |
|  Fract(*v*)                                       |
|  FindInterval(*size, predicate*)                  |
|  Dot(*v1, v2*)                                    |
|  Cross(*v1, v2)                                   |
|  DistSq(*v1, v2*)                                 |
|  Rotate(*v, axis, theta*)                         |
|  SphericalDirection(*sin_theta, cos_theta, phi*)  |
|  SphericalTheta(*v*)                              |
|  SphericalPhi(*v*)                                |
|  WorldToLocal(*v, n, b, t*)                       |
|  LocalToWorld(*v, n, b, t*)                       |
|  Union(*b1, b2*)                                  |