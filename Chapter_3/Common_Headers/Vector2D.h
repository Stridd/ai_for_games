#pragma once
struct Vector2D
{
	float x;
	float y;

	Vector2D operator+(const Vector2D& secondVector) const;
	Vector2D operator-(const Vector2D& secondVector) const;

	Vector2D operator*(const float& scalar) const;
	Vector2D operator/(const float& scalar) const;

	Vector2D& operator+=(const Vector2D& secondVector);
	Vector2D& operator-=(const Vector2D& secondVector);
	Vector2D& operator*=(const float& scalar);
	Vector2D& operator/=(const float& scalar);

	float getLength() const;
	void normalise();

};

Vector2D operator*(const float& scalar, const Vector2D& vector);
