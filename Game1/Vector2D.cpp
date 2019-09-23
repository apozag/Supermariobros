#include "Vector2D.h"

Vector2D operator +(const Vector2D &v1, const Vector2D &v2) {
	return Vector2D(v1.x+v2.x, v1.y+v2.y);
}
Vector2D operator -(const Vector2D &v1, const Vector2D &v2) {
	return Vector2D(v1.x - v2.x, v1.y - v2.y);
}
Vector2D operator *(const Vector2D &v, const double &i) {
	return Vector2D(v.x*i, v.y*i);
}
