#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowaæ na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy górny naro¿nik)
    p.drawImage(poczX,poczY,*img);
}


void MainWindow::on_pushButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    R = value;
    rysuj_red(value);
    update();
}

void MainWindow::on_verticalSlider_sliderPressed()
{
    rysuj_red(R);
    update();
}


void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    G = value;
    rysuj_green(value);
    update();
}

void MainWindow::on_verticalSlider_2_sliderPressed()
{
    rysuj_green(G);
    update();
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    B = value;
    rysuj_blue(value);
    update();
}

void MainWindow::on_verticalSlider_3_sliderPressed()
{
    rysuj_blue(B);
    update();
}

void MainWindow::on_verticalSlider_4_valueChanged(int value)
{
    H = value;
    rysuj_hue(value);
    update();
}

void MainWindow::on_verticalSlider_4_sliderPressed()
{
    rysuj_hue(H);
    update();
}

void MainWindow::on_verticalSlider_6_valueChanged(int value)
{
    S = value;
    rysuj_saturation(value);
    update();
}

void MainWindow::on_verticalSlider_6_sliderPressed()
{
    rysuj_saturation(S);
    update();
}

void MainWindow::on_verticalSlider_5_valueChanged(int value)
{
    V = value;
    rysuj_value(value);
    update();
}

void MainWindow::on_verticalSlider_5_sliderPressed()
{
    rysuj_value(V);
    update();
}

void MainWindow::rysuj_red(int czerwony)
{

    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255-i/2; // Sk³adowa BLUE
            ptr[szer*4*i + 4*j + 1] = j/2; // Sk³adowa GREEN
            ptr[szer*4*i + 4*j + 2] = czerwony; // Sk³adowa RED
        }
    }
}

void MainWindow::rysuj_green(int zielony)
{

    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255-i/2; // Sk³adowa BLUE
            ptr[szer*4*i + 4*j + 1] = zielony; // Sk³adowa GREEN
            ptr[szer*4*i + 4*j + 2] = j/2; // Sk³adowa RED
        }
    }
}

void MainWindow::rysuj_blue(int niebieski)
{

    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=niebieski; // Sk³adowa BLUE
            ptr[szer*4*i + 4*j + 1] = j/2; // Sk³adowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255-i/2; // Sk³adowa RED
        }
    }
}

void MainWindow::rysuj_hue(int hue)
{

    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    double r,g,b;

    for(i=0; i<wys; i++) // saturacja
    {
        for(j=0; j<szer; j++) //jasnosc
        {
            hsv2rgb(hue,1.0-1.0*i/wys,1.0*j/szer,&r,&g,&b);
            ptr[szer*4*i + 4*j]=(int)(255*b); // Sk³adowa BLUE
            ptr[szer*4*i + 4*j + 1] = (int)(255*g); // Sk³adowa GREEN
            ptr[szer*4*i + 4*j + 2] = (int)(255*r); // Sk³adowa RED
        }
    }
}

void MainWindow::rysuj_saturation(int saturation)
{

    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    double r,g,b;

    for(i=0; i<wys; i++) // jasnosc
    {
        for(j=0; j<szer; j++) //kolor
        {
            hsv2rgb(360-1.0*j/szer*360, saturation/100.0, 1.0-1.0*i/wys,&r,&g,&b);
            ptr[szer*4*i + 4*j]=(int)(255*b); // Sk³adowa BLUE
            ptr[szer*4*i + 4*j + 1] = (int)(255*g); // Sk³adowa GREEN
            ptr[szer*4*i + 4*j + 2] = (int)(255*r); // Sk³adowa RED
        }
    }
}

void MainWindow::rysuj_value(int value)
{

    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    double r,g,b;

    for(i=0; i<wys; i++) // saturacja
    {
        for(j=0; j<szer; j++) //kolor
        {
            hsv2rgb(360-1.0*j/szer*360, 1.0-1.0*i/wys,value/100.0,&r,&g,&b);
            ptr[szer*4*i + 4*j]=(int)(255*b); // Sk³adowa BLUE
            ptr[szer*4*i + 4*j + 1] = (int)(255*g); // Sk³adowa GREEN
            ptr[szer*4*i + 4*j + 2] = (int)(255*r); // Sk³adowa RED
        }
    }
}

void MainWindow::hsv2rgb(double h, double s, double v, double *r, double *g, double *b)
{
  int h_i;
  double h_f,p,q,t;

  h_i = (int)floor(h/60.0);
  if(h_i==6) h_i = 0;
  h_f = h/60.0 - h_i;

  p = v * (1 - s);
  q = v * (1 - h_f * s);
  t = v * (1 - (1 - h_f) * s);

  switch (h_i)
  {
    case 0:
      *r = v;
      *g = t;
      *b = p;
      break;
    case 1:
      *r = q;
      *g = v;
      *b = p;
      break;
    case 2:
      *r = p;
      *g = v;
      *b = t;
      break;
    case 3:
      *r = p;
      *g = q;
      *b = v;
      break;
    case 4:
      *r = t;
      *g = p;
      *b = v;
      break;
    case 5:
      *r = v;
      *g = p;
      *b = q;
      break;
  }
}




















