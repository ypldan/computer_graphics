#include "bezier.h"

QPointF f(QPointF a, QPointF b, double t) {
    a * (1 - t);
    return a * (1 - t) + b * t;
}

QPointF deCasteljau(double t, int n, int m, QVector<QPointF> &points) {
    if (n == 0) {
        return points[m];
    }
    return f(deCasteljau(t, n-1, m, points), deCasteljau(t, n-1, m+1, points), t);
}

QVector<QPointF> getCurve(QVector<QPointF> points) {
    QVector<QPointF> result;
    for (double i = 0; i <= 1; i += 0.001) {
        result.push_back(deCasteljau(i, points.size() - 1, 0, points));
    }
    return result;
}
