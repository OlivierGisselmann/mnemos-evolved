#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <math/vector.hpp>

#include <cstring>

const double PI = 3.14159265;

namespace mnm::math
{
    template <typename T>
    struct Mat4
    {
    public:
        // Ctors & Dtor
        Mat4()
        {
            memset(mValues, static_cast<T>(0), sizeof(mValues));
            mValues[0] = mValues[5] = mValues[10] = mValues[15] = static_cast<T>(1.0);
        }

        Mat4(T diagonal)
        {
            memset(mValues, static_cast<T>(0), sizeof(mValues));
            mValues[0] = mValues[5] = mValues[10] = mValues[15] = static_cast<T>(diagonal);
        }

        Mat4(const Mat4<T>& mat)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    (*this)(col, row) = mat(col, row);
                }
            }
        }

        Mat4& operator=(const Mat4<T>& mat)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    (*this)(col, row) = mat(col, row);
                }
            }

            return *this;
        }

        // Value access
        inline T& operator()(int row, int col)
        {
            return mValues[col * 4 + row];
        }

        inline const T& operator()(int row, int col) const
        {
            return mValues[col * 4 + row];
        }

        // Data pointer access
        inline const T* Data() const
        {
            return mValues;
        }

        inline T* Data()
        {
            return mValues;
        }

        // Matrix operations
        [[nodiscard]] inline Mat4<T> operator+(const Mat4<T>& rhs) const
        {
            Mat4<T> res;

            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    res(row, col) = (*this)(row, col) + rhs(row, col);
                }
            }

            return res;
        }

        [[nodiscard]] inline Mat4<T> operator-(const Mat4<T>& rhs) const
        {
            Mat4<T> res;

            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    res(row, col) = (*this)(row, col) - rhs(row, col);
                }
            }

            return res;
        }

        [[nodiscard]] inline Mat4<T> operator*(const Mat4<T>& rhs) const
        {
            Mat4<T> res;

            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    for(i8 k = 0; k < 4; ++k)
                    {
                        res(row, col) += (*this)(row, k) * rhs(k, col);
                    }
                }
            }

            return res;
        }

        inline Mat4<T>& operator+=(const Mat4<T>& rhs)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    (*this)(row, col) += rhs(row, col);
                }
            }

            return (*this);
        }

        inline Mat4<T>& operator-=(const Mat4<T>& rhs)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    (*this)(row, col) -= rhs(row, col);
                }
            }

            return (*this);
        }

        inline Mat4<T>& operator*=(const Mat4<T>& rhs)
        {
            Mat4<T> res(0);

            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    for(i8 k = 0; k < 4; ++k)
                    {
                        res(row, col) += (*this)(row, k) * rhs(k, col);
                    }
                }
            }

            return *this = res;
        }

    private:
        T mValues[16]; // 4 * 4
    };

    typedef Mat4<f32> Mat4f;

    template<typename T>
    [[nodiscard]] inline T Radians(T degrees)
    {
        return degrees * (static_cast<T>(PI) / static_cast<T>(180));
    }

    template<typename T>
    [[nodiscard]] inline Mat4<T> Translate(const Mat4<T>& m, const Vec3<T>& t)
    {
        Mat4<T> res(m);

        res(0, 3) = t.x;
        res(1, 3) = t.y;
        res(2, 3) = t.z;

        return res;
    }

    template<typename T>
    [[nodiscard]] inline Mat4<T> Scale(const Mat4<T>& m, const Vec3<T>& s)
    {
        Mat4<T> res(m);

        res(0, 0) = s.x;
        res(1, 1) = s.y;
        res(2, 2) = s.z;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline Mat4<T> Rotate(const Mat4<T>& m, T angle, const Vec3<T>& v)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

		Vec3<T> axis = Normalize(v);

        Mat4<T> res(m);

		res(0, 0) = c + (static_cast<T>(1) - c)      * axis.x     * axis.x;
		res(0, 1) = (static_cast<T>(1) - c) * axis.x * axis.y + s * axis.z;
		res(0, 2) = (static_cast<T>(1) - c) * axis.x * axis.z - s * axis.y;
		res(0, 3) = static_cast<T>(0);

		res(1, 0) = (static_cast<T>(1) - c) * axis.y * axis.x - s * axis.z;
		res(1, 1) = c + (static_cast<T>(1) - c) * axis.y * axis.y;
		res(1, 2) = (static_cast<T>(1) - c) * axis.y * axis.z + s * axis.x;
		res(1, 3) = static_cast<T>(0);

		res(2, 0) = (static_cast<T>(1) - c) * axis.z * axis.x + s * axis.y;
		res(2, 1) = (static_cast<T>(1) - c) * axis.z * axis.y - s * axis.x;
		res(2, 2) = c + (static_cast<T>(1) - c) * axis.z * axis.z;
		res(2, 3) = static_cast<T>(0);

		res(3, 0) = 0;
		res(3, 1) = 0;
		res(3, 2) = 0;
		res(3, 3) = 1;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline Mat4<T> RotateX(const Mat4<T>& m, T angle)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

        Mat4<T> res(m);

        res(1, 1) = c;
        res(1, 2) = -s;
        res(2, 1) = s;
        res(2, 2) = c;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline Mat4<T> RotateY(const Mat4<T>& m, T angle)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

        Mat4<T> res(m);

        res(0, 0) = c;
        res(0, 2) = s;
        res(2, 0) = -s;
        res(2, 2) = c;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline Mat4<T> RotateZ(const Mat4<T>& m, T angle)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

        Mat4<T> res(m);

        res(0, 0) = c;
        res(0, 1) = -s;
        res(1, 0) = s;
        res(1, 1) = c;
        
        return res;
    }

    template<typename T>
    [[nodiscard]] inline Mat4<T> Perspective(T fov, T aspect, T near, T far)
    {
        const T range = std::tan(Radians(fov) / static_cast<T>(2));

        Mat4<T> res(0);

        res(0, 0) = static_cast<T>(1) / (aspect * range);
        res(1, 1) = static_cast<T>(1) / (range);
        res(2, 2) = -(far + near) / (far - near);
        res(2, 3) = -(static_cast<T>(2) * far * near) / (far - near);
        res(3, 2) = -static_cast<T>(1);

        return res;
    }

    template <typename T>
    [[nodiscard]] inline Mat4<T> LookAt(const Vec3<T>& eye, const Vec3<T>& center, const Vec3<T>& up)
    {
        Mat4<T> res;

        Vec3<T> f = Normalize(eye - center);
        Vec3<T> s = Normalize(Cross(Normalize(up), f));
        Vec3<T> u = Normalize(Cross(f, s));

        Vec3<T> t(0);
        t.x = Dot(s, eye);
        t.y = Dot(u, eye);
        t.z = Dot(f, eye);

        res(0, 0) = s.x;
        res(0, 1) = s.y;
        res(0, 2) = s.z;

        res(1, 0) = u.x;
        res(1, 1) = u.y;
        res(1, 2) = u.z;

        res(2, 0) = f.x;
        res(2, 1) = f.y;
        res(2, 2) = f.z;

        res(0, 3) = t.x;
        res(1, 3) = t.y;
        res(2, 3) = t.z;

        return res;
    }
}

#endif
