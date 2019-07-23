#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QTime>
#include <QDebug>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QImage *img;

    int szer;
    int wys;
    int poczX;
    int poczY;

    int tryb_pracy;
    int powoli;
    int kolor_kreski_b, kolor_kreski_g, kolor_kreski_r;
    int kolor_tla_b, kolor_tla_g, kolor_tla_r;
    int kolor_wyp_b, kolor_wyp_g, kolor_wyp_r;
    int boki;

    int x0,y0,x1,y1;
    int x_pocz,y_pocz;



    int czysc();
    int czy_taki_kolor(int x0, int y0, int b, int g, int r);
    int wstaw_piksel(int x0, int y0, int b, int g, int r);
    int wstaw_4piksele(int x0, int y0, int x, int y, int b, int g, int r);
    int wstaw_8pikseli(int x0, int y0, int x, int y, int b, int g, int r);
    int rysuj_elipse(int x0, int y0, int x1, int y1, int b, int g, int r);
    int rysuj_okrag(int x0, int y0, int x1, int y1, int b, int g, int r);
    int flood_fill(int x0, int y0, int tlo_b, int tlo_g, int tlo_r, int wyp_b, int wyp_g, int wyp_r);
    int flood_fill_delay(int x0, int y0, int tlo_b, int tlo_g, int tlo_r, int wyp_b, int wyp_g, int wyp_r);
    int rysuj_odcinek(int x0, int y0, int x1, int y1, int b, int g, int r);
    int rysuj();
    void scanline();
    void delay(int n);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);



private slots:
    void on_checkBox_5_clicked();
    void on_radioButton_6_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_clicked();
    void on_exitButton_clicked();
    void on_cleanButton_clicked();
    void on_radioButton_4_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
