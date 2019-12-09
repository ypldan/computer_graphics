#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , counter()
    , press(0, 0)
    , points()
    , hull()
    , segments()
    , state(0)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator( new QIntValidator(0, 10000000, this) );
    ui->lineEdit2->setValidator( new QIntValidator(0, 1000000, this) );
    ui->lineEdit3->setValidator( new QIntValidator(1, 180, this) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    int xmin = std::min(press.x(), event->x());
    int ymin = std::min(press.y(), event->y());
    int xmax = std::max(press.x(), event->x());
    int ymax = std::max(press.y(), event->y());
    QRect rect(QPoint(xmin, ymin), QPoint(xmax, ymax));
    if (state == 1 || state == 0) {
        ui->label2->setNum(counter.count(rect));
    } else if (state == 2) {
        QVector<QLine> newVector;
        for (auto l: segments) {
            if (instersects(l, rect)) {
                newVector.push_back(l);
            }
        }
        segments = newVector;
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    if (state == 0 || state == 1) {
        for (auto point: points) {
            painter.drawPoint(point);
        }
    }
    if (state == 1) {
        state = 0;
        QPen redPen(Qt::red, 2);
        painter.setPen(redPen);
        auto polygon = QPolygon(hull);
        painter.drawPolygon(polygon);
        QPen bluePen(Qt::blue, 5);
        painter.setPen(bluePen);
        painter.drawPoints(polygon);
    }
    if (state == 2) {
        for (auto segment: segments) {
            painter.drawLine(segment);
        }
    }
    if (state == 3) {
        painter.setPen(Qt::black);
        double angle = ui->lineEdit3->text().toDouble() / 180 * 3.14;
        double x = ui->xSlider->value();
        double y = ui->ySlider->value();
        double z = ui->zSlider->value();
        auto m = getMatrix(x, y, z);
        painter.drawLines(projectCube(QVector3D(250,250,250), 200, angle, m));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    press = event->pos();
}

void MainWindow::on_pushButton_clicked()
{
    QSize size = ui->centralwidget->size();
    points = generatePoints(size, ui->lineEdit->text().toInt());
    counter.updatePoints(points);
    hull.clear();
    ui->lineEdit->setText(QString::number(counter.getUnique()));
    ui->label2->setText("");
    state = 0;
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    hull = getHull(points);
    state = 1;
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSize size = ui->centralwidget->size();
    segments = generateLines(size, ui->lineEdit2->text().toInt());
    state = 2;
    ui->label2->clear();
    update();
}

void MainWindow::on_pushButton_4_clicked()
{
    state = 3;
    update();
}

void MainWindow::on_xSlider_sliderMoved(int position)
{
    update();
}

void MainWindow::on_ySlider_sliderMoved(int position)
{
    update();
}

void MainWindow::on_zSlider_sliderMoved(int position)
{
    update();
}
