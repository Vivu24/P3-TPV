#ifndef VECTOR2D_H_
#define VECTOR2D_H_
#include <iostream>
template <class T>
class Vector2D {

private:
	T x;
	T y;
public:
	Vector2D() : x(), y() {};
	Vector2D(T x, T y) : x(x), y(y) {};

	T getX() const {
		return x;
	}

	T getY() const {
		return y;
	}

	void normalize() {
		double mag = sqrt(pow(x, 2) + pow(y, 2));
		if (mag > 0.0) {
			x = x / mag;
			y = y / mag;
		}
	}

	Vector2D<T> operator+(const Vector2D<T>& v) const {
		Vector2D<T> r;
		r.x = this->x + v.x;
		r.y = this->y + v.y;
		return r;
	}

	// Operador Resta Vectores
	Vector2D<T> operator-(const Vector2D<T>& v) const {
		Vector2D<T> r;
		r.x = this->x - v.x;
		r.y = this->y - v.y;
		return r;
	}

	// Operador Producto de Vector * Escalar
	Vector2D<T> operator*(T d) const {
		Vector2D r;
		r.x = x * d;
		r.y = y * d;
		return r;
	}

	// Operador Producto escalar
	T operator*(const Vector2D<T>& d) const {
		return d.x * x + d.y * y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2D<T>& v) {
		os << "(" << v.x << "," << v.y << ")";
		return os;
	}
};

template <class T>
using Point2D = Vector2D<T>;
#endif
