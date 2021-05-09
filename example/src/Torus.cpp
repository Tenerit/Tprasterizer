#include "Torus.h"

Torus::Torus() {
    this->majorRadius = 2;
    this->minorRadius = 1;
}

Torus::Torus(const Vector3 &center, const double &majorRadius, const double &minorRadius) {
    this->transform.translate(center);

    this->majorRadius = majorRadius;
    this->minorRadius = minorRadius;

    this->material = Material(rand()%255, rand()%255, rand()%255);  //random color
}

Torus::Torus(const Vector3 &center, const double &majorRadius, const double &minorRadius, const Material &material) : Torus(center, majorRadius, minorRadius) {
    this->material = material;
}

sf::Color Torus::getPixel() const {
    return this->material.getColor();
}

Vector3 Torus::getNormal(const Vector3 &point) const {
    const double alpha = (this->majorRadius*this->majorRadius)/std::sqrt(point.x*point.x + point.y*point.y);

    return normalize(point - alpha*Vector3(point.x, point.y, 0));
}




CollisionData Torus::distance(const Vector3 &point) const {
    CollisionData data;             // construct fills struct with correct fields
    const double R = this->majorRadius;
    const double r = this->minorRadius;
    const Vector3 center = this->transform.getTranslation();

    Vector3 t = point - center;

    data.distance = length(Vector3(length(Vector3(t.x, t.y, 0)) - R, 0, t.z)) - r;  // set distance from surface to point (with sign)
    data.point = point;                                                             // set point, where calculations are
    data.normal = this->getNormal(data.point-center);                               // set normal in the nearest point
    data.color = this->material.getColor();                                         // set color in the nearest point
    data.material = this->material;                                                 // set material of the objects
    data.exist = (data.distance<EPSILON);                                           // set true if point is near enough

    return data;    // return collision data
}
