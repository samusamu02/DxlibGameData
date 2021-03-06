#pragma once
// ev[g
template <class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x_;
	T y_;

	// γόZq
	Vector2Template& operator=(const Vector2Template& vec);

	// Y¦Zq
	int& operator[](int i);

	// PZq
	Vector2Template& operator+=(const Vector2Template& vec);
	Vector2Template& operator-=(const Vector2Template& vec);
	Vector2Template& operator*=(const Vector2Template& vec);
	Vector2Template& operator/=(const Vector2Template& vec);
	Vector2Template& operator%=(const Vector2Template& vec);
	Vector2Template operator+()const;
	Vector2Template operator-()const;

	// ρZq
	Vector2Template operator+(Vector2Template vec);		// operatorΜ+ΙΞ΅Δα€p³ΜNX
	Vector2Template operator-(Vector2Template vec);
	Vector2Template operator*(Vector2Template vec);
	Vector2Template operator/(Vector2Template vec);
	Vector2Template operator%(Vector2Template vec);

	// δrZq
	bool operator==(const Vector2Template& vec) const;
	bool operator!=(const Vector2Template& vec) const;
	bool operator<(const Vector2Template& vec) const;
	bool operator<=(const Vector2Template& vec) const;
	bool operator>(const Vector2Template& vec) const;
	bool operator>=(const Vector2Template& vec) const;
	
private:
};

// Vector2ΖintΜ|―Z
template <class T>
Vector2Template<T> operator*(const class Vector2Template<T>& u, T k);
template <class T>
Vector2Template<T> operator*(T k, const class Vector2Template<T>& u);

using Vector2 = Vector2Template<int>;
using Vector2Float = Vector2Template<float>;
using Vector2Double = Vector2Template<double>;

#include"../detail/Vector2.h"