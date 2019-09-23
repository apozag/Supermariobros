#pragma once
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>

class Vector2D {
private:
	double x;
	double y;
public:
	Vector2D():x(0),y(0){}
	~Vector2D(){}
	Vector2D(double x, double y):x(x),y(y) {}
	Vector2D(const Vector2D* const v):x(v->x),y(v->y) {}
	Vector2D* clone() { return new Vector2D(this); }

	const double &getX() { return x; }
	const double &getY() { return y; }
	void setX(const double &x) { this->x = x; }
	void setY(const double &y) { this->y = y; }

	friend Vector2D operator + (const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator - (const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator *(const Vector2D &v, const double &i);
};



#endif
