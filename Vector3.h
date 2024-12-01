#pragma once
#include <cmath>
struct Vector3 {
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Add two vectors
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Subtract two vectors
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Scale a vector by a scalar
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Normalize a vector
    Vector3 normalize() const {
        float length = sqrt(x * x + y * y + z * z);
        if (length > 0) {
            return Vector3(x / length, y / length, z / length);
        }
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    // Cross product
    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
	bool operator==(const Vector3& other) const {
		return x == other.x && y == other.y && z == other.z;
	}
	bool operator!=(const Vector3& other) const {
		return x != other.x || y != other.y || z != other.z;
	}
};
