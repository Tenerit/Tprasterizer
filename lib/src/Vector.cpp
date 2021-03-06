#include "Vector.h"
#include <string>

Vector3::Vector3() : Vector3(0, 0, 0) {}

Vector3::Vector3(const double &x, const double &y, const double &z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(const Matrix &A) {
    assert(A.getRows()==3);
    assert(A.getCols()==1);

    this->x = A(0, 0);
    this->y = A(1, 0);
    this->z = A(2, 0);
}

double Vector3::getLength() const {
    return length(*this);
}

Vector3 Vector3::getNormalized() const {
    return normalize(*this);
}

Matrix Vector3::getTransposition() const {
    Matrix result(1, 3);

    result(0, 0) = this->x;
    result(0, 1) = this->y;
    result(0, 2) = this->z;

    return result;
}

bool Vector3::operator!=(const Vector3 &rhs) const {
    return (length(*this - rhs)>0.0001);
}

Vector3 & Vector3::operator+=(const Vector3 &rhs) {
    this->x +=rhs.x;
    this->y +=rhs.y;
    this->z +=rhs.z;

    return *this;
}

Vector3 & Vector3::operator-=(const Vector3 &rhs) {
    this->x -=rhs.x;
    this->y -=rhs.y;
    this->z -=rhs.z;

    return *this;
}

Vector3 Vector3::operator+(const Vector3 &rhs) const {
    return Vector3(
        this->x + rhs.x,
        this->y + rhs.y,
        this->z + rhs.z
    );
}

Vector3 Vector3::operator-(const Vector3 &rhs) const {
    return Vector3(
        this->x - rhs.x,
        this->y - rhs.y,
        this->z - rhs.z
    );
}

Matrix Vector3::operator*(const Matrix &rhs) const {
    return this->getTransposition().getTransposition()*rhs;
}

double Vector3::operator*(const Vector3 &rhs) const {
    return this->x*rhs.x + this->y*rhs.y + this->z*rhs.z;
}

Vector3 Vector3::operator^(const Vector3 &rhs) const {
    return Vector3(
        this->y*rhs.z - this->z*rhs.y,
        -(this->x*rhs.z - this->z*rhs.x),
        this->x*rhs.y - this->y*rhs.x
    );
}

Vector3 Vector3::operator*(const double &rhs) const {
    return Vector3(
        this->x * rhs,
        this->y * rhs,
        this->z * rhs
    );
}

Vector3 Vector3::operator/(const double &rhs) const {
    return (*this)*(1/rhs);
}

Vector3 Vector3::UnitX() {
    return  Vector3(1, 0, 0);
}

Vector3 Vector3::UnitY() {
    return  Vector3(0, 1, 0);
}

Vector3 Vector3::UnitZ() {
    return  Vector3(0, 0, 1);
}

Vector3 operator*(const double &lhs, const Vector3 &rhs) {
    return rhs*lhs;
}

Vector3 operator*(const Matrix &lhs, const Vector3 &rhs) {
    return Vector3(lhs*(rhs.getTransposition().getTransposition()));
}

double length(const Vector3 &vec) {
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2) + std::pow(vec.z, 2));
}

Vector3 normalize(const Vector3 &v) {
    double len = length(v);

    if(len==0)
        return v;

    return (v/len);
}

Vector3 rotate(const Vector3 &axis, const Vector3 &v, const double &theta) {
    Vector3 k = normalize(axis);

    double c = std::cos(theta);
    double s = std::sin(theta);

    //Rodrigues' rotation formula
    return (c*v + s*(k^v) + (k*v)*(1.f-c)*k);
}

std::ostream & operator<<(std::ostream &lhs, const Vector3 &rhs) {
    lhs << "[";
    lhs << rhs.x << ", ";
    lhs << rhs.y << ", ";
    lhs << rhs.z;
    lhs << "]";
    return lhs;
}

