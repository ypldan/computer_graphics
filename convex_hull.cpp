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

void quickHull(QVector<QPoint> a, int n, QPoint p1, QPoint p2, int side, QSet<QPoint> &hull)
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
        hull.insert(p1);
        hull.insert(p2);
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
    int min_y = 0, max_y = 0;
    for (int i=1; i<n; i++)
    {
        if (points[i].x() < points[min_x].x() || (points[i].x() == points[min_x].x() && points[i].y() < points[min_x].y())) {
            min_x = i;
        }
        if (points[i].x() > points[max_x].x() || (points[i].x() == points[min_x].x() && points[i].y() < points[max_x].y())) {
            max_x = i;
        }
        if (points[i].y() < points[min_y].y()) {
            min_y = i;
        }
        if (points[i].y() > points[max_y].y()) {
            max_y = i;
        }
    }

    qInfo() << points[max_x] << " " << points[min_x];

    QSet<QPoint> up, down;

    // Recursively find convex hull points on
    // one side of line joining a[min_x] and
    // a[max_x]
    quickHull(points, n, points[min_x], points[max_x], 1, up);
    auto upList = up.toList();
    std::sort(upList.begin(), upList.end(), [&points, &max_y](const QPoint& a, const QPoint& b) {
        if (a.x() < b.x()) {
            return true;
        } else if (a.x() > b.x()) {
            return false;
        } else if (a.x() == b.x()) {
            if (a.x() <= points[max_y].x() && b.x() >= points[max_y].x()) {
                return true;
            } else if (a.x() >= points[max_y].x() && b.x() <= points[max_y].x()) {
                return false;
            } else if (a.x() >= points[max_y].x() && b.x() >= points[max_y].x()) {
                return a.y() > b.y();
            } else if (a.x() <= points[max_y].x() && b.x() <= points[max_y].x()) {
                return a.y() < b.y();
            }
        }
        qWarning() << "UNEXPECTED: " << a << " " << b;
        return true;
    });

    // Recursively find convex hull points on
    // other side of line joining a[min_x] and
    // a[max_x]
    quickHull(points, n, points[min_x], points[max_x], -1, down);
    auto downList = down.toList();
    std::sort(downList.begin(), downList.end(), [&points, &min_y](const QPoint& a, const QPoint& b) {
        if (a.x() > b.x()) {
            return true;
        } else if (a.x() < b.x()) {
            return false;
        } else if (a.x() == b.x()) {
            if (a.x() <= points[min_y].x() && b.x() >= points[min_y].x()) {
                return false;
            } else if (a.x() >= points[min_y].x() && b.x() <= points[min_y].x()) {
                return true;
            } else if (a.x() >= points[min_y].x() && b.x() >= points[min_y].x()) {
                return a.y() < b.y();
            } else if (a.x() <= points[min_y].x() && b.x() <= points[min_y].x()) {
                return a.y() > b.y();
            }
        }
        qWarning() << "UNEXPECTED: " << a << " " << b;
        return true;
    });
    QVector<QPoint> result;
    qInfo() << "up:";
    for (auto p: upList) {
        result.push_back(p);
        qInfo() << p;
    }
    qInfo() << "down:";
    for (auto p: downList) {
        result.push_back(p);
        qInfo() << p;
    }
//    for (auto p: result) {
//        qInfo() << p;
//    }
    return result;
}
