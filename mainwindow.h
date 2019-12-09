#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPainter>
#include <QValidator>
#include "points_in_rect.h"
#include "convex_hull.h"
#include "segments.h"
#include "cabinet.h"
#include "bezier.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_xSlider_sliderMoved(int position);

    void on_ySlider_sliderMoved(int position);

    void on_zSlider_sliderMoved(int position);

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene grahicsScene;
    PointsCounter counter;
    QPoint press;
    QVector<QPoint> points;
    QVector<QPoint> hull;
    QVector<QLine> segments;
    QVector<QPointF> curve;
    int state;
};
#endif // MAINWINDOW_H
