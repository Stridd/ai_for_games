#include "Vector2D.h"

#include <cmath>

Vector2D Vector2D::operator+(const Vector2D& secondVector) const
{
	Vector2D resultVector{};
	resultVector.x = this->x + secondVector.x;
	resultVector.y = this->y + secondVector.x;

	return resultVector;
}

Vector2D Vector2D::operator-(const Vector2D& secondVector) const
{
	Vector2D resultVector{};
	resultVector.x = this->x - secondVector.x;
	resultVector.y = this->y - secondVector.y;

	return resultVector;
}

Vector2D Vector2D::operator*(const float& scalar) const
{
	Vector2D resultVector{};
	resultVector.x = this->x * scalar;
	resultVector.y = this->y * scalar;

	return resultVector;
}

Vector2D Vector2D::operator/(const float& scalar) const
{
	Vector2D resultVector{};
	resultVector.x = this->x / scalar;
	resultVector.y = this->y / scalar;

	return resultVector;
}

Vector2D& Vector2D::operator+=(const Vector2D& secondVector)
{
	x += secondVector.x;
	y += secondVector.y;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& secondVector)
{
	x -= secondVector.x;
	y -= secondVector.y;

	return *this;
}

Vector2D& Vector2D::operator*=(const float& scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

float Vector2D::getLength() const
{
	return sqrt(x * x + y * y);
}

void Vector2D::normalise()
{
	float length = getLength();
	x /= length;
	y /= length;
}

Vector2D operator*(const float& scalar, const Vector2D& vector)
{
	Vector2D result{};

	result.x = scalar * vector.x;
	result.y = scalar * vector.y;

	return result;
}