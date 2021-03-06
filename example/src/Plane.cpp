#include "Plane.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal) {
    Vector3 norm = normalize(normal);
    A = norm.x;
    B = norm.y;
    C = norm.z;
    D = -A*point.x - B*point.y - C*point.z;

    this->material.setAmbient(0);
    this->material.setDiffuse(1);
    this->material.setSpecular(0);
    this->material.setShininess(1);
    this->material.setReflection(0);
}

Plane::Plane(const Vector3 &point, const Vector3 &normal, const Material &material) : Plane(point, normal) {
    this->material = material;
    this->material.setAmbient(0);
    this->material.setDiffuse(1);
    this->material.setSpecular(0);
    this->material.setShininess(1);
    this->material.setReflection(0.5);
}

sf::Color Plane::getPixel(const Vector3 &point3D) const {
    //only special case
    sf::Vector2f point2D(point3D.x, point3D.y);

    return this->material.getColorAt(point3D.x, point3D.y);
}

Vector3 Plane::getNormal() const {
    return Vector3(this->A, this->B, this->C);
}

/*  CollisionData CustomObject::intersect(const Ray &) const

    method parameter is Ray struct, 
    if user objects collide with that ray, should return correct CollisionData struct
    if not, should return not changed CollisionData struct  */

CollisionData Plane::intersect(const Ray &ray) const {
    CollisionData data;     // construct fills struct with correct fields

    const double dot = this->getNormal()*ray.direction;
    if(dot<EPSILON && dot>-EPSILON)
        return data;        // return not changed if ray parallel to plane

    Vector3 p0 = Vector3(0, 0, -D/C);
    Vector3 p1 = Vector3(1, 0, -(D + A)/C);
    Vector3 p2 = Vector3(1, 1, -(D + A + B)/C);

    Vector3 p01 = p1 - p0;
    Vector3 p02 = p2 - p0;

    double t = -(((p01^p02)*(ray.origin - p0))/(ray.direction*(p01^p02)));

    data.point = ray.origin + t*ray.direction;          // set collision point

    if((ray.direction*(data.point - ray.origin))<EPSILON)
        return data;        // return not changed if result point of collision is behind ray origin

    // if ray collide with object fill data fields in correct way
    data.normal = this->getNormal();                    // set surface notrmal vector in collision point
    data.color = this->getPixel(data.point);            // set color of the object in collision point
    data.material = this->material;                     // set material of the objects
    data.distance = length(data.point - ray.origin);    // set distance from ray origin to collision point
    data.exist = true;                                  // collision occured? set to true
    return data;        // return collision data
}

/*  CollisionData CustomObject::distance(const Vector3 &) const

    method parameter is Vector3 class, 
    method should return infromations about object int the nearest point */

CollisionData Plane::distance(const Vector3 &point) const {
    CollisionData data;         // construct fills struct with correct fields

    const Vector3 P(0, 0, -this->D/this->C);
    const Vector3 N = this->getNormal();
    const Vector3 V = point - P;

    data.distance = std::abs(V*N);                          // set distance from surface to point (with sign)
    data.point = point;                                     // set point, where calculations are
    data.normal = N;                                        // set normal in the nearest point
    data.material = this->material;                         // set material of the objects
    data.color = this->getPixel(point + N*data.distance);   // set color in the nearest point
    data.exist = (data.distance<EPSILON);                   // set true if point is near enough

    return data;    // return collision data
}
