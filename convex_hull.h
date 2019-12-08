#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <QPoint>
#include <QSet>
#include <QVector>
#include <algorithm>
#include <QDebug>

inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

// Returns the side of point p with respect to line
// joining points p1 and p2.
int findSide(QPoint p1, QPoint p2, QPoint p);

// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int lineDist(QPoint p1, QPoint p2, QPoint p);

// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(QVector<QPoint> a, int n, QPoint p1, QPoint p2, int side, QSet<QPoint> &hull);

QVector<QPoint> getHull(QVector<QPoint> points);

#endif // CONVEX_HULL_H
