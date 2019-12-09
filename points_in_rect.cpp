#include "points_in_rect.h"

int INDENT = 200;

QVector<QPoint> generatePoints(QSize &size, int n) {
    QVector<QPoint> points(n);
    for (int i = 0; i < n; i++) {
        QPoint point(INDENT / 2 + qrand() % (size.width() - INDENT), INDENT / 2 + qrand() % (size.height() - INDENT));
        points[i] = point;
    }
    std::sort(points.begin(), points.end(),
          [](const QPoint& a, const QPoint& b) {
        if (a.x() == b.x()) {
            return a.y() <= b.y();
        } else {
            return a.x() < b.x();
        }
    });
    return points;
}

QVector<QLine> generateLines(QSize &size, int n) {
    QVector<QLine> lines(n);
    for (int i = 0; i < n; i++) {
        QPoint p1(INDENT / 2 + qrand() % (size.width() - INDENT), INDENT / 2 + qrand() % (size.height() - INDENT));
        QPoint p2(INDENT / 2 + qrand() % (size.width() - INDENT), INDENT / 2 + qrand() % (size.height() - INDENT));
        lines[i] = QLine(p1, p2);
    }
    return lines;
}

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

PointsCounter::PointsCounter(QVector<QPoint> &points) {
    QTextStream out(stdout);
    QSet<int> xSet, ySet;
    QSet<QPair<int,int>> pointsSet;
    for (QPoint p: points) {
        xSet.insert(p.x());
        ySet.insert(p.y());
        pointsSet.insert(QPair<int, int>(p.x(), p.y()));
    }
    int n = xSet.size() + 1;
    int m = ySet.size() + 1;

    unique = pointsSet.size();

    xvector = QVector<int> (n - 1);
    yvector = QVector<int> (m - 1);
    int ind = 0;
    for (int x: xSet) {
        xvector[ind++] = x;
    }
    ind = 0;
    for (int y: ySet) {
        yvector[ind++] = y;
    }
    table = QVector<QVector<int>>(n, QVector<int>(m, 0));
    for (int i = 1; i < n; i++) {
        for (int j = 1; i < m; i++) {
            table[i][j] = table[i-1][j]
                    + table[i][j-1]
                    - table[i-1][j-1]
                    + pointsSet.contains(QPair<int, int>(xvector[i-1], yvector[j-1]));
            out << table[i][j] << '\t';
        }
        out << '\n';
    }

}

PointsCounter::PointsCounter() {
    unique = 0;
    xvector = QVector<int> (0);
    yvector = QVector<int> (0);
    table = QVector<QVector<int>>(0, QVector<int>(0, 0));
}

PointsCounter::~PointsCounter() {
}

int PointsCounter::count(QPoint &leftTop, QPoint &rightBottom) {
    QPoint leftBottom(leftTop.rx(), rightBottom.y()), rightTop(rightBottom.x(), leftTop.y());
    return count(leftTop, rightTop, leftBottom, rightBottom);
}

int PointsCounter::count(QRect &rect) {
    return count(rect.topLeft(), rect.topRight(), rect.bottomLeft(), rect.bottomRight());
}

int PointsCounter::count(QPoint leftTop, QPoint rightTop, QPoint leftBottom, QPoint rightBottom) {
    return getQ(leftTop) + getQ(rightBottom) - getQ(leftBottom) - getQ(rightTop);
}

int PointsCounter::getQ(QPoint &p) {
    return table[xIndex(p.rx())][yIndex(p.ry())];
}

int PointsCounter::xIndex(int &x) {
    int i = std::distance(xvector.begin(), std::upper_bound(xvector.begin(), xvector.end(), x));
    return i;
}

int PointsCounter::yIndex(int &y) {
    int i = std::distance(yvector.begin(), std::upper_bound(yvector.begin(), yvector.end(), y));
    return i;
}

void PointsCounter::updatePoints(QVector<QPoint> &points) {
    QSet<int> xSet, ySet;
    QSet<int> pointsSet;
    for (QPoint p: points) {
        xSet.insert(p.x());
        ySet.insert(p.y());
        pointsSet.insert(p.x() * 10000 + p.y());
    }
    int n = xSet.size() + 1;
    int m = ySet.size() + 1;

    xvector = QVector<int> (n - 1);
    yvector = QVector<int> (m - 1);
    int ind = 0;
    for (int x: xSet) {
        xvector[ind++] = x;
    }
    ind = 0;
    for (int y: ySet) {
        yvector[ind++] = y;
    }
    std::sort(xvector.begin(), xvector.end());
    std::sort(yvector.begin(), yvector.end());
    table = QVector<QVector<int>>(n, QVector<int>(m, 0));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            table[i][j] = table[i-1][j]
                    + table[i][j-1]
                    - table[i-1][j-1]
                    + pointsSet.contains(xvector[i-1] * 10000 + yvector[j-1]);
        }
    }
    unique = pointsSet.size();
}

int PointsCounter::getUnique() {
    return unique;
}
