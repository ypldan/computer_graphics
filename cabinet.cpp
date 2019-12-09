#include "cabinet.h"

QPointF project(QVector3D point3d, double angle) {
    return QPointF(point3d.x() + point3d.z() * cos(angle) / 2,
                   point3d.y() + point3d.z() * sin(angle) / 2);
}

QVector<QLineF> projectCube(QVector3D start, float a, double angle, QMatrix3x3 matrix) {
    QVector<QLineF> projection;
    QPointF vector000 = project(start + turn(QVector3D(-a/2, -a/2, -a/2), matrix), angle),
            vector001 = project(start + turn(QVector3D(-a/2, -a/2, a/2), matrix), angle),
            vector010 = project(start + turn(QVector3D(-a/2, a/2, -a/2), matrix), angle),
            vector011 = project(start + turn(QVector3D(-a/2, a/2, a/2), matrix), angle),
            vector100 = project(start + turn(QVector3D(a/2, -a/2, -a/2), matrix), angle),
            vector101 = project(start + turn(QVector3D(a/2, -a/2, a/2), matrix), angle),
            vector110 = project(start + turn(QVector3D(a/2, a/2, -a/2), matrix), angle),
            vector111 = project(start + turn(QVector3D(a/2, a/2, a/2), matrix), angle);
    projection.push_back(QLineF(vector000, vector001));
    projection.push_back(QLineF(vector000, vector010));
    projection.push_back(QLineF(vector000, vector100));
    projection.push_back(QLineF(vector001, vector011));
    projection.push_back(QLineF(vector001, vector101));
    projection.push_back(QLineF(vector010, vector011));
    projection.push_back(QLineF(vector010, vector110));
    projection.push_back(QLineF(vector100, vector101));
    projection.push_back(QLineF(vector100, vector110));
    projection.push_back(QLineF(vector111, vector011));
    projection.push_back(QLineF(vector111, vector101));
    projection.push_back(QLineF(vector111, vector110));
    return projection;
}

QMatrix3x3 xMatrix(double angle) {
    double a = angle / 360 * 2 * 3.1416;
    float arr[] = {
        1, 0, 0,
        0, (float) cos(a), (float) -sin(a),
        0, (float) sin(a), (float) cos(a)
    };
    return QMatrix3x3(arr);
}

QMatrix3x3 yMatrix(double angle) {
    double a = angle / 360 * 2 * 3.1416;
    float arr[] = {
        (float) cos(a), 0, (float) sin(a),
        0, 1, 0,
        (float) -sin(a), 0, (float) cos(a)
    };
    return QMatrix3x3(arr);
}

QMatrix3x3 zMatrix(double angle) {
    double a = angle / 360 * 2 * 3.1416;
    float arr[] = {
        (float) cos(a), (float) -sin(a), 0,
        (float) sin(a), (float) cos(a), 0,
        0, 0, 1
    };
    return QMatrix3x3(arr);
}

QMatrix3x3 getMatrix(double x, double y, double z) {
    return xMatrix(x) * yMatrix(y) * zMatrix(z);
}

QVector3D turn(QVector3D vector, QMatrix3x3 matrix) {
    QGenericMatrix<1,3,float> v;

    for (int i = 0; i < 3; i++) {
        v(i, 0) = vector[i];
    }
    QGenericMatrix<1,3,float> r = matrix * v;
    QVector3D result;
    for (int i = 0; i < 3; i++) {
        result[i] = r(i, 0);
    }
    return result;
}
