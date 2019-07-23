#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();

    void on_resetButton_clicked();

    void paintEvent(QPaintEvent*);



    void on_transXSlider_valueChanged(int value);

    void on_transYSlider_valueChanged(int value);

    void on_scaleXSlider_valueChanged(int value);

    void on_scaleYSlider_valueChanged(int value);

    void on_rotationSlider_valueChanged(int value);

    void on_shareXSlider_valueChanged(int value);

    void on_shareYSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    int width;
    int height;
    int img_x0;
    int img_y0;

    int tX,tY;
    double sX, sY;
    double shX, shY;
    int centerX, centerY;
    double alpha;

    QImage *img_org;
    QImage *img;

    double mainMatrix[3][3];
    double translXMatrix[3][3];
    double translYMatrix[3][3];
    double rotationMatrix[3][3];
    double scaleXMatrix[3][3];
    double shearXMatrix[3][3];
    double scaleYMatrix[3][3];
    double shearYMatrix[3][3];

    void paint();
    void clean();
    void resetMatrix(double matrix[][3]);
    void createMatrix();
    void multiplyMatrix(double matrix[][3]);
    void multiplyMatrixVector(double vec[]);
    void resetSettings();
};

#endif // MAINWINDOW_H
