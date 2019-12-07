#ifndef POINTS_IN_RECT_H
#define POINTS_IN_RECT_H

#include <QtAlgorithms>
#include <QMap>
#include <QSet>
#include <QHash>
#include <QDateTime>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QVector>
#include <QVector2D>
#include <random>
#include <QDebug>
#include <QLine>

QVector<QPoint> generatePoints(QSize &size, int n);

QVector<QLine> generateLines(QSize &size, int n);

class PointsCounter {
private:
    QVector<QVector<int>> table;
    QVector<int> xvector, yvector;
    int unique;
public:
    PointsCounter();
    PointsCounter(QVector<QPoint> &points);
    ~PointsCounter();
    int xIndex(int &x);
    int yIndex(int &y);
    int getQ(QPoint &p);
    int getUnique();
    int count(QRect &rect);
    int count(QPoint &leftTop, QPoint &rightBottom);
    int count(QPoint leftTop, QPoint rightTop, QPoint leftBottom, QPoint rightBottom);
    void updatePoints(QVector<QPoint> &points);
};

#endif // POINTS_IN_RECT_H
