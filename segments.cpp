#include "segments.h"

bool rangeTest(int m, int c, double &tmin, double &tmax) {
    if (m < 0) {
        double r = 1. * c / m;
        if (r > tmax) {
            return false;
        } else if (r > tmin) {
            tmin = r;
        }
    } else if (m > 0) {
        double r = 1. * c / m;
        if (r < tmin) {
            return false;
        } else if (r < tmax) {
            tmax = r;
        }
    } else if (c < 0) {
        return false;
    }
    return true;
}

bool instersects(QLine &line, QRect &rect) {
    double tmin = 0, tmax = 1;
    int dx = line.x2() - line.x1();
    int xmin = rect.x(), ymin = rect.y();
    int xmax = xmin + rect.width(), ymax = ymin + rect.height();
//    qInfo() << xmin << " " << ymin << " " << xmax << " " << ymax;
    if (rangeTest(-dx, line.x1() - xmin, tmin, tmax)) {
        if (rangeTest(dx, xmax - line.x1(), tmin, tmax)) {
            int dy = line.y2() - line.y1();
            if (rangeTest(-dy, line.y1() - ymin, tmin, tmax)) {
                if (rangeTest(dy, ymax - line.y1(), tmin, tmax)) {
                    if (tmax < 1) {
                        line.setP2(QPoint((int)(line.x1() + tmax*dx), (int)(line.y1() + tmax*dy)));
                    }
                    if (tmin > 0) {
                        line.setP1(QPoint((int)(line.x1() + tmin*dx), (int)(line.y1() + tmin*dy)));
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
