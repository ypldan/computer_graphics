#ifndef CABINET_H
#define CABINET_H

#include <QPointF>
#include <QVector3D>
#include <QtMath>
#include <QVector>
#include <QLineF>
#include <QVector4D>
#include <QMatrix3x3>
#include <QGenericMatrix>

QPointF project(QVector3D point3d, double angle);

QVector<QLineF> projectCube(QVector3D start, float a, double angle, QMatrix3x3 matrix);

QMatrix3x3 xMatrix(double angle);

QMatrix3x3 yMatrix(double angle);

QMatrix3x3 zMatrix(double angle);

QMatrix3x3 getMatrix(double x, double y, double z);

QVector3D turn(QVector3D vector, QMatrix3x3 matrix);

#endif // CABINET_H
