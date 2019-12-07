#ifndef SEGEMENTS_H
#define SEGEMENTS_H

#include <QLine>
#include <QRect>
#include <cmath>
#include <QDebug>

bool instersects(QLine &line, QRect &rect);

bool rangeTest(int m, int c, double &tmin, double &tmax);

#endif // SEGEMENTS_H
