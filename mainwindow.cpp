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
    painter.setPen(Qt::black);
    if (state == 0 || state == 1) {
        for (auto point: points) {
            painter.drawPoint(point);
        }
    }
    if (state == 1) {
        state = 0;
        painter.setPen(Qt::red);
        painter.drawPolygon(QPolygon(hull));
    }
    if (state == 2) {
        for (auto segment: segments) {
            painter.drawLine(segment);
        }
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
