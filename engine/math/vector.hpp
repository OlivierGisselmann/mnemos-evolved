#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

namespace mnm::math
{
    template <typename T>
    struct Vec2
    {
        T x, y;

        Vec2(T _x, T _y) : x(_x), y(_y) {}
        Vec2(T value) : x(value), y(value) {}
        Vec2(const Vec2& v) : x(v.x), y(v.y) {}
        Vec2& operator=(const Vec2& v)
        {
            this->x = v.x;
            this->y = v.y;
        }
        ~Vec2() {}

        // Arithmetic functions
        inline Vec2<T>& operator+=(const Vec2<T>& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        inline Vec2<T>& operator-=(const Vec2<T>& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        inline Vec2<T>& operator *=(T value)
        {
            x *= value;
            y *= value;
            return *this;
        }

        [[nodiscard]] inline Vec2<T> operator+(const Vec2<T>& v)
        {
            return {x + v.x, y + v.y};
        }

        [[nodiscard]] inline Vec2<T> operator-(const Vec2<T>& v)
        {
            return {x - v.x, y - v.y};
        }

        [[nodiscard]] inline Vec2<T> operator*(T value)
        {
            return {x * value, y * value};
        }
    };

    typedef Vec2<f32> Vec2f;
    typedef Vec2<i32> Vec2i;
    typedef Vec2<u32> Vec2u;

    template <typename T>
    struct Vec3
    {
        T x, y, z;

        Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        Vec3(T value) : x(value), y(value), z(value) {}
        Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
        Vec3& operator=(const Vec3& v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }
        ~Vec3() {}

        // Arithmetic functions
        inline Vec3<T>& operator+=(const Vec3<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        inline Vec3<T>& operator-=(const Vec3<T>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        inline Vec3<T>& operator*=(T value)
        {
            x *= value;
            y *= value;
            z *= value;
            return *this;
        }

        [[nodiscard]] inline Vec3<T> operator+(const Vec3<T>& v)
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        [[nodiscard]] inline Vec3<T> operator-(const Vec3<T>& v)
        {
            return {x - v.x, y - v.y, z - v.z};
        }

        [[nodiscard]] inline Vec3<T> operator*(T value)
        {
            return {x * value, y * value, z * value};
        }
    };

    typedef Vec3<f32> Vec3f;
    typedef Vec3<i32> Vec3i;
    typedef Vec3<u32> Vec3u;

    template <typename T>
    [[nodiscard]] inline T Length(const Vec3<T>& v)
    {
        return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    }

    template <typename T>
    [[nodiscard]] inline Vec3<T> Normalize(const Vec3<T>& v)
    {
        return v / Length(v);
    }

    template <typename T>
    [[nodiscard]] inline T Dot(const Vec3<T>& v1, const Vec3<T> v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    }

    template <typename T>
    [[nodiscard]] inline Vec3<T> Cross(const Vec3<T>& v1, const Vec3<T> v2)
    {
        return
        {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }
}

#endif
