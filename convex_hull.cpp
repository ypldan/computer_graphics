#include "convex_hull.h"

int findSide(QPoint p1, QPoint p2, QPoint p) {
    int val = (p.y() - p1.y()) * (p2.x() - p1.x()) -
              (p2.y() - p1.y()) * (p.x() - p1.x());

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int lineDist(QPoint p1, QPoint p2, QPoint p) {
    return abs ((p.y() - p1.y()) * (p2.x() - p1.x()) -
               (p2.y() - p1.y()) * (p.x() - p1.x()));
}

void quickHull(QVector<QPoint> a, int n, QPoint p1, QPoint p2, int side, QVector<QPoint> &hull)
{
    int ind = -1;
    int max_dist = 0;

    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<n; i++)
    {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        hull.push_back(p1);
        hull.push_back(p2);
        return;
    }

    // Recur for the two parts divided by a[ind]
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2), hull);
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1), hull);
}

QVector<QPoint> getHull(QVector<QPoint> points)
{
    // a[i].y() -> y-coordinate of the ith point

    // Finding the point with minimum and
    // maximum x-coordinate
    int n = points.size();
    int min_x = 0, max_x = 0;
    for (int i=1; i<n; i++)
    {
        if (points[i].x() < points[min_x].x())
            min_x = i;
        if (points[i].x() > points[max_x].x())
            max_x = i;
    }

    QVector<QPoint> up, down;

    // Recursively find convex hull points on
    // one side of line joining a[min_x] and
    // a[max_x]
    quickHull(points, n, points[min_x], points[max_x], 1, up);
    std::sort(up.begin(), up.end(), [](const QPoint& a, const QPoint& b) {
        return a.x() < b.x();
    });

    // Recursively find convex hull points on
    // other side of line joining a[min_x] and
    // a[max_x]
    quickHull(points, n, points[min_x], points[max_x], -1, down);
    std::sort(down.begin(), down.end(), [](const QPoint& a, const QPoint& b) {
        return a.x() > b.x();
    });
    QVector<QPoint> result;
    for (auto p: up) {
        result.push_back(p);
    }
    for (auto p: down) {
        result.push_back(p);
    }
    return result;
}
