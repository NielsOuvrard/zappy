/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-kenan.blasius
** File description:
** raytracer
*/

#pragma once

#include <iostream>
#include <cassert>
#include <cmath>

// INFO: Classe template pour les vecteurs
template <size_t DIM, typename T>
class vec
{
    public:
        vec() {
            for (size_t i = DIM; i--; data_[i] = T());
        }

        T &operator[](const size_t i) {
            assert(i < DIM);
            return data_[i];
        }
        const T &operator[](const size_t i) const {
            assert(i < DIM);
            return data_[i];
        }

    private:
        T data_[DIM];
};

// INFO: Typedefs pour les vecteurs
typedef vec<2, float> Vec2f;
typedef vec<3, float> Vec3f;
typedef vec<3, int> Vec3i;
typedef vec<4, float> Vec4f;

// INFO: Classe Vec2
template <typename T>
class vec<2, T>
{
    public:
        vec() : x(T()), y(T()) {}
        vec(T X, T Y) : x(X), y(Y) {}
        template <class U>
        vec(const vec<2, U> &v);

        T &operator[](const size_t i) {
            assert(i < 2);
            return i <= 0 ? x : y;
        }
        const T &operator[](const size_t i) const {
            assert(i < 2);
            return i <= 0 ? x : y;
        }

        T x, y;
};

// INFO: Classe Vec3
template <typename T>
class vec<3, T>
{
    public:
        vec() : x(T()), y(T()), z(T()) {}
        vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

        T &operator[](const size_t i) {
            assert(i < 3);
            return i <= 0 ? x : (1 == i ? y : z);
        }
        const T &operator[](const size_t i) const {
            assert(i < 3);
            return i <= 0 ? x : (1 == i ? y : z);
        }

        float norm() { return std::sqrt(x * x + y * y + z * z); }
        vec<3, T> &normalize(T l = 1) {
            *this = (*this) * (l / norm());
            return *this;
        }

        T x, y, z;
};

// INFO: Classe Vec4
template <typename T>
class vec<4, T>
{
    public:
        vec() : x(T()), y(T()), z(T()), w(T()) {}
        vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}

        T &operator[](const size_t i) {
            assert(i < 4);
            return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w));
        }
        const T &operator[](const size_t i) const {
            assert(i < 4);
            return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w));
        }

        T x, y, z, w;
};

// INFO: Surcharge des opérateurs (* + - / <<) pour les vecteurs et cross pour les vecteurs 3D
// permet de calculer le produit scalaire de deux vecteurs (dot product)
template <size_t DIM, typename T>
T operator*(const vec<DIM, T> &lhs, const vec<DIM, T> &rhs)
{
    T ret = T();
    for (size_t i = DIM; i--; ret += lhs[i] * rhs[i]);
    return ret;
}

template <size_t DIM, typename T>
vec<DIM, T> operator+(vec<DIM, T> lhs, const vec<DIM, T> &rhs)
{
    for (size_t i = DIM; i--; lhs[i] += rhs[i]);
    return lhs;
}

template <size_t DIM, typename T>
vec<DIM, T> operator-(vec<DIM, T> lhs, const vec<DIM, T> &rhs)
{
    for (size_t i = DIM; i--; lhs[i] -= rhs[i]);
    return lhs;
}

template <size_t DIM, typename T, typename U>
vec<DIM, T> operator*(const vec<DIM, T> &lhs, const U &rhs)
{
    vec<DIM, T> ret;
    for (size_t i = DIM; i--; ret[i] = lhs[i] * rhs);
    return ret;
}

template <size_t DIM, typename T, typename U>
vec<DIM, T> operator/(const vec<DIM, T> &lhs, const U &rhs)
{
    vec<DIM, T> ret;
    for (size_t i = DIM; i--; ret[i] = lhs[i] / rhs);
    return ret;
}

template <size_t DIM, typename T>
vec<DIM, T> operator-(const vec<DIM, T> &lhs)
{
    return lhs * T(-1);
}

// permet de calculer le produit vectoriel de deux vecteurs 3D (produit vectoriel)
// le produit vectoriel est un vecteur perpendiculaire aux deux vecteurs d'origine
// ce qui permet de calculer la normale d'un plan
template <typename T>
vec<3, T> cross(vec<3, T> v1, vec<3, T> v2)
{
    return vec<3, T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <size_t DIM, typename T>
std::ostream &operator<<(std::ostream &out, const vec<DIM, T> &v)
{
    for (unsigned int i = 0; i < DIM; i++) {
        out << v[i] << " ";
    }
    return out;
}
