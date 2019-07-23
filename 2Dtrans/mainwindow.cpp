#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    width = ui->drawFrame->width();
    height = ui->drawFrame->height();
    img_x0 = ui->drawFrame->x();
    img_y0 = ui->drawFrame->y();

    img = new QImage(width,height,QImage::Format_RGB32);
    img_org = new QImage(width,height,QImage::Format_RGB32);
    img_org->load(":/penguin.jpg");
    img->load(":/penguin.jpg");

    resetSettings();
    /*centerX=300;
    centerY=300;
    tX = 0;
    tY = 0;
    sX = 1.0;
    sY = 1.0;
    alpha = 0.0;

    resetMatrix(mainMatrix);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(img_x0, img_y0, *img);
}

void MainWindow::clean()
{
    unsigned char *ptr;

    ptr = img->bits();

    int i,j;
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            ptr[width*4*i + 4*j]=255; // Skladowa BLUE
            ptr[width*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[width*4*i + 4*j + 2] = 255; // Skladowa RED

        }
    }
}


void MainWindow::paint()
{
    double point[3];

    unsigned char *ptr, *ptr2;
        ptr = img->bits();
        ptr2 = img_org->bits();
        clean();


    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            point[0] = j-centerX-tX;
            point[1] = i-centerY-tY;
            point[2] = 1;
            multiplyMatrixVector(point);
            point[0] += (centerX+tX);
            point[1] += (centerY+tY);
            if (point[0]>=0 && point[0]<width && point[1]>=0 && point[1]<height)
            {
                ptr[width*4*i + 4*j] = ptr2[width*4*(int)point[1] + 4*(int)point[0]];
                ptr[width*4*i + 4*j + 1] = ptr2[width*4*(int)point[1] + 4*(int)point[0] + 1];
                ptr[width*4*i + 4*j + 2] = ptr2[width*4*(int)point[1] + 4*(int)point[0] + 2];
            }

        }
    }
}

void MainWindow::resetMatrix(double matrix[][3])
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            matrix[i][j] = 0.0;
        }
    }
    matrix[0][0] = 1.0;
    matrix[1][1] = 1.0;
    matrix[2][2] = 1.0;

}

void MainWindow::multiplyMatrix(double matrix[][3])
{
    double temp[3][3];

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            temp[i][j] = 0;
            for(int k=0; k<3; k++)
                temp[i][j] += (matrix[i][k]*mainMatrix[k][j]);

        }
    }
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            mainMatrix[i][j] = temp[i][j];

}

void MainWindow::createMatrix()
{
    resetMatrix(mainMatrix);
    multiplyMatrix(scaleXMatrix);
    multiplyMatrix(scaleYMatrix);
    multiplyMatrix(rotationMatrix);
    multiplyMatrix(shearXMatrix);
    multiplyMatrix(shearYMatrix);

    multiplyMatrix(translXMatrix);
    multiplyMatrix(translYMatrix);


}

void MainWindow::multiplyMatrixVector(double vec[])
{
    double temp[3];

    for(int i=0; i<3; i++)
    {
        temp[i] = 0;
        for(int k=0; k<3; k++)
            temp[i] += (mainMatrix[i][k]*vec[k]);
    }
    for(int i=0; i<3; i++)
        vec[i] = temp[i];

}


void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_resetButton_clicked()
{
    resetSettings();
}

void MainWindow::resetSettings()
{
    ui->transXSlider->setValue(0);
    ui->transYSlider->setValue(0);
    ui->rotationSlider->setValue(0);
    ui->scaleXSlider->setValue(50);
    ui->scaleYSlider->setValue(50);
    ui->shareXSlider->setValue(50);
    ui->shareYSlider->setValue(50);

    img->load(":/penguin.jpg");
    resetMatrix(mainMatrix);
    resetMatrix(translXMatrix);
    resetMatrix(translYMatrix);
    resetMatrix(rotationMatrix);
    resetMatrix(scaleXMatrix);
    resetMatrix(scaleYMatrix);
    resetMatrix(shearXMatrix);
    resetMatrix(shearYMatrix);
    centerX=300;
    centerY=300;
    tX = 0;
    tY = 0;
    sX = 1.0;
    sY = 1.0;
    shX = 0.0;
    shY = 0.0;
    alpha = 0.0;
}

void MainWindow::on_transXSlider_valueChanged(int value)
{
    translXMatrix[0][2] = -value;
    tX = value;
    createMatrix();
    paint();
    update();
}

void MainWindow::on_transYSlider_valueChanged(int value)
{
    translYMatrix[1][2] = -value;
    tY = value;
    createMatrix();
    paint();
    update();
}

void MainWindow::on_scaleXSlider_valueChanged(int value)
{

    if(value>=50.0)
       sX = 1 + (value-50.0)/25.0;
    else
       sX = 1 - (50.0-value)/50.0;
    scaleXMatrix[0][0] = 1.0/sX;
    createMatrix();
    paint();
    update();
}

void MainWindow::on_scaleYSlider_valueChanged(int value)
{
    if(value>=50.0)
       sY = 1 + (value-50.0)/25.0;
    else
       sY = 1 - (50.0-value)/50.0;
    scaleYMatrix[1][1] = 1.0/sY;
    createMatrix();
    paint();
    update();
}

void MainWindow::on_rotationSlider_valueChanged(int value)
{
    alpha = 3.14159/180.0*value;

    resetMatrix(rotationMatrix);
    rotationMatrix[0][0] = cos(alpha);
    rotationMatrix[0][1] = sin(alpha);
    rotationMatrix[1][0] = -sin(alpha);
    rotationMatrix[1][1] = cos(alpha);

    createMatrix();
    paint();
    update();

}

void MainWindow::on_shareXSlider_valueChanged(int value)
{
    if(value>=50.0)
        sX = (value-50.0)/25.0;
    else
        sX = -(50.0-value)/25.0;
    shearXMatrix[0][1] = -sX;
    createMatrix();
    paint();
    update();
}

void MainWindow::on_shareYSlider_valueChanged(int value)
{

    if(value>=50.0)
        sY = (value-50.0)/25.0;
    else
        sY = - (50.0-value)/25.0;
    shearYMatrix[1][0] = -sY;
    createMatrix();
    paint();
    update();

}
