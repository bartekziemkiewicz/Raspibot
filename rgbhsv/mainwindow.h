#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <cmath>

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
    void on_pushButton_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_3_valueChanged(int value);

    void on_verticalSlider_sliderPressed();

    void on_verticalSlider_2_sliderPressed();

    void on_verticalSlider_3_sliderPressed();

    void on_verticalSlider_4_valueChanged(int value);

    void on_verticalSlider_4_sliderPressed();

    void on_verticalSlider_6_valueChanged(int value);

    void on_verticalSlider_6_sliderPressed();

    void on_verticalSlider_5_valueChanged(int value);

    void on_verticalSlider_5_sliderPressed();

private:
    Ui::MainWindow *ui;

    QImage *img;

        int szer;
        int wys;
        int poczX;
        int poczY;
        int R,G,B;
        int H,S,V;

        void rysuj_red(int value);
        void rysuj_green(int value);
        void rysuj_blue(int value);
        void rysuj_hue(int value);
        void hsv2rgb(double h, double s, double v, double *r, double *g, double *b);
        void rysuj_saturation(int value);
        void rysuj_value(int value);

        void paintEvent(QPaintEvent*);



};

#endif // MAINWINDOW_H
