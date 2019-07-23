#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>


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

    tryb_pracy = 1; //odcinek
    powoli = 0;  // powolne wypelnianie
    kolor_kreski_b = 255;
    kolor_kreski_g = 255;
    kolor_kreski_r = 255;
    kolor_tla_b = 0;
    kolor_tla_g = 0;
    kolor_tla_r = 0;
    kolor_wyp_b = 0;
    kolor_wyp_g = 255;
    kolor_wyp_r = 0;

    boki = 0;
    x_pocz=0;
    y_pocz=0;




}

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------
void MainWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowaæ na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy górny naro¿nik)
    p.drawImage(poczX,poczY,*img);
}

//---------------------------------------------------------------------------
void MainWindow::on_cleanButton_clicked()
{
    czysc();
    boki=0;
    update();

}
//---------------------------------------------------------------------------

void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
}
//---------------------------------------------------------------------------

void MainWindow::on_pushButton_clicked() //scanline button
{
    scanline();
    update();
}

//---------------------------------------------------------------------------
int MainWindow::czysc()
{
    // Wskaznik za pomoca, którego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wska¿nik do pierwszego piksela danych
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtów)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=kolor_tla_b; // Sk³adowa BLUE
            ptr[szer*4*i + 4*j + 1] = kolor_tla_g; // Sk³adowa GREEN
            ptr[szer*4*i + 4*j + 2] = kolor_tla_r; // Sk³adowa RED
        }
    }
    return(0);
}

//---------------------------------------------------------------------------
int MainWindow::wstaw_piksel(int x0, int y0, int b, int g, int r)
{
  unsigned char *wsk;


  if ((x0>=0)&&(y0>=0)&&(x0<szer)&&(y0<wys))
  {
        wsk = img->bits();
        wsk[szer*4*y0 + 4*x0] = b;
        wsk[szer*4*y0 + 4*x0+1] = g;
        wsk[szer*4*y0+ 4*x0+2] = r;
  }
  return(0);
}
//---------------------------------------------------------------------------
//Sprawdza czy piksel (x,y) ma kolor (r,g,b)
int MainWindow::czy_taki_kolor(int x0, int y0, int b, int g, int r)
{
  unsigned char *wsk;

  if ((x0>=0)&&(y0>=0)&&(x0<szer)&&(y0<wys))
  {
        wsk = img->bits();
        if ((wsk[szer*4*y0 + 4*x0] == b) && (wsk[szer*4*y0 + 4*x0+1] == g) && (wsk[szer*4*y0+ 4*x0+2] == r))
          return(1);
        else
          return(0);
  }
  else
    return(0);
}

//---------------------------------------------------------------------------
void MainWindow::on_radioButton_clicked()
{
    tryb_pracy = 1; //odcinek
    ui->checkBox_5->setEnabled(false);
}

void MainWindow::on_radioButton_2_clicked()
{
    tryb_pracy = 2; //okrag
    ui->checkBox_5->setEnabled(false);
}

void MainWindow::on_radioButton_3_clicked()
{
    tryb_pracy = 3; //elipsa
    ui->checkBox_5->setEnabled(false);
}

void MainWindow::on_radioButton_4_clicked()
{
    tryb_pracy = 4; //wielokat
    boki = 0;
    ui->checkBox_5->setEnabled(false);
}

void MainWindow::on_radioButton_6_clicked()
{
    tryb_pracy = 6; //flood-fill
    ui->checkBox_5->setEnabled(true);
}

void MainWindow::on_checkBox_5_clicked()
{
    if (powoli==0)
        {
            powoli=1;
        }
        else
        {
            powoli=0;
        }

}


//---------------------------------------------------------------------------
int MainWindow::rysuj_odcinek(int x0, int y0, int x1, int y1, int b, int g, int r)
//bresenham

{
   int x,y, step,tmp,steep,d,d_x,d_y;

   if (abs(y1-y0) > abs(x1-x0))
     steep = 1;
   else
     steep = 0;

   if (steep == 1)
   {
     tmp = x0;
     x0  = y0;
     y0 = tmp;
     tmp = x1;
     x1 = y1;
     y1 = tmp;
   }

   if (x1 < x0)
    {
      tmp = x0;
      x0 = x1;
      x1 = tmp;
      tmp = y0;
      y0 = y1;
      y1 = tmp;
    }

    d_x = x1 - x0;
    d_y = abs(y1 - y0);
    d = 0;
    y = y0;
    if (y0 < y1)
      step = 1;
    else
      step = -1;

    for (x=x0; x<=x1; x++)
    {
      if (steep == 1)
        wstaw_piksel(y,x,b,g,r);
      else
        wstaw_piksel(x,y,b,g,r);
      d = d + d_y;
      if (2 * d >= d_x)
      {
        y = y + step;
        d = d - d_x;
      }
    }
    return(0);
}

//---------------------------------------------------------------------------
int MainWindow::wstaw_4piksele(int x0, int y0, int x, int y, int b, int g, int r)
{
  wstaw_piksel(x,y,b,g,r);
  wstaw_piksel(x,-y+2*y0,b,g,r);
  wstaw_piksel(-x+2*x0,y,b,g,r);
  wstaw_piksel(-x+2*x0,-y+2*y0,b,g,r);
  return(0);
}

//---------------------------------------------------------------------------
int MainWindow::wstaw_8pikseli(int x0, int y0, int x, int y, int b, int g, int r)
{
  wstaw_piksel(x,y,b,g,r);
  wstaw_piksel(x,-y+2*y0,b,g,r);
  wstaw_piksel(-x+2*x0,y,b,g,r);
  wstaw_piksel(-x+2*x0,-y+2*y0,b,g,r);
  wstaw_piksel(y-y0+x0,x-x0+y0,b,g,r);
  wstaw_piksel(-y+y0+x0,x-x0+y0,b,g,r);
  wstaw_piksel(y-y0+x0,-x+x0+y0,b,g,r);
  wstaw_piksel(-y+y0+x0,-x+x0+y0,b,g,r);
  return(0);
}

//---------------------------------------------------------------------------
// Bresenham
int MainWindow::rysuj_elipse(int x0, int y0, int x1, int y1, int bl, int g, int r)
{
    int a,b,a2,b2,d,x,y;
    double p1,p2;
    a = abs(x1-x0);
    b = abs(y1-y0);
    a2 = a * a;
    b2 = b * b;
    p1 = (double)a2/sqrt(a2+b2);
    p2 =  b * sqrt(1 - (double)a2/(a2+b2));


    y = b;
    x = 0;
    d = 4 * b2 - 4 * a2 * b + a2;
    wstaw_piksel(x1,y0,bl,g,r);
    wstaw_piksel(-x1+2*x0,y0,bl,g,r);
    wstaw_4piksele(x0,y0,x0+x,y0+y,bl,g,r);
    while (x < p1)
    {

      if (d >= 0)
      {
        d = d + 4 * b2 * (2*x + 3) - 4 * a2 * (2*y - 2);
        y = y - 1;
        x = x + 1;
      }
      else
      {
        d = d + 4 * b2 * (2*x + 3);
        x = x + 1;
      }
      wstaw_4piksele(x0,y0,x0+x,y0+y,bl,g,r);
    }

    y = 0;
    x = a;
    d = 4 * a2 - 4 * b2 * a + b2;
    while (y < p2)
    {
      if (d >= 0)
      {
        d = d + 4 * a2 * (2*y + 3) - 4 * b2 * (2*x - 2);
        x = x - 1;
        y = y + 1;
      }
      else
      {
        d = d + 4 * a2 * (2*y + 3);
        y = y + 1;
      }
      wstaw_4piksele(x0,y0,x0+x,y0+y,bl,g,r);
    }

    return(0);
}
//---------------------------------------------------------------------------
int MainWindow::rysuj_okrag(int x0, int y0, int x1, int y1, int b, int g, int r)
{
    int R,d,x,y;

    R = (int)floor(sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0))+0.5);

    y = R;
    x = 0;
    d = 1 - R;
    wstaw_8pikseli(x0,y0,x0+x,y0+y,b,g,r);
    while (x<y)
    {

      if (d >= 0)
      {
        d = d + 2 * (x - y) + 5;
        y = y - 1;
        x = x + 1;
      }
      else
      {
        d = d + 2 * x + 3;
        x = x + 1;
      }
      wstaw_8pikseli(x0,y0,x0+x,y0+y,b,g,r);
    }
    return(0);
}


//---------------------------------------------------------------------------
//wypelnia wielokat kolorem - kol_wyp, metoda flood-fill, zaczynajac od punktu (x0,y0)
int MainWindow::flood_fill(int x0, int y0, int tlo_b, int tlo_g, int tlo_r, int wyp_b, int wyp_g, int wyp_r)
{
  int *x, *y;
  int x_akt,y_akt,i;
  x_akt = x0;
  y_akt = y0;
  x = new int[szer*wys*sizeof(int)];
  y = new int[szer*wys*sizeof(int)];

  if (czy_taki_kolor(x_akt,y_akt,wyp_b,wyp_g,wyp_r)==1)
    return(0);

  i = 0;
  x[i] = x_akt;
  y[i] = y_akt;

  while (i >= 0)
  {
    x_akt = x[i];
    y_akt = y[i];
    i = i - 1;

    if(x_akt > 1)
      if (czy_taki_kolor(x_akt-1,y_akt,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt - 1;
        y[i] = y_akt;
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);

      }
    if(x_akt < szer-1)
      if (czy_taki_kolor(x_akt+1,y_akt,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt + 1;
        y[i] = y_akt;
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);

      }
    if(y_akt > 1)
      if (czy_taki_kolor(x_akt,y_akt-1,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt;
        y[i] = y_akt - 1;
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);

      }
    if(y_akt < wys-1)
      if (czy_taki_kolor(x_akt,y_akt+1,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt;
        y[i] = y_akt+1;
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);

      }

  }
  delete[] x;
  delete[] y;
  return(0);
}

//---------------------------------------------------------------------------
//wypelnia wielokat kolorem - kol_wyp, metoda flood-fill, zaczynajac od punktu (x0,y0)
int MainWindow::flood_fill_delay(int x0, int y0, int tlo_b, int tlo_g, int tlo_r, int wyp_b, int wyp_g, int wyp_r)
{
  int *x, *y;
  int x_akt,y_akt,i;
  int opoz = 1;
  x_akt = x0;
  y_akt = y0;
  x = new int[szer*wys*sizeof(int)];
  y = new int[szer*wys*sizeof(int)];

  if (czy_taki_kolor(x_akt,y_akt,wyp_b,wyp_g,wyp_r)==1)
    return(0);

  i = 0;
  x[i] = x_akt;
  y[i] = y_akt;

  while (i >= 0)
  {
    x_akt = x[i];
    y_akt = y[i];
    i = i - 1;

    if(x_akt > 1)
      if (czy_taki_kolor(x_akt-1,y_akt,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt - 1;
        y[i] = y_akt;
        delay(opoz);
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);
        update();

      }
    if(x_akt < szer-1)
      if (czy_taki_kolor(x_akt+1,y_akt,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt + 1;
        y[i] = y_akt;
        delay(opoz);
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);
        update();

      }
    if(y_akt > 1)
      if (czy_taki_kolor(x_akt,y_akt-1,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt;
        y[i] = y_akt - 1;
        delay(opoz);
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);
        update();

      }
    if(y_akt < wys-1)
      if (czy_taki_kolor(x_akt,y_akt+1,tlo_b,tlo_g,tlo_r)==1)
      {
        i = i + 1;
        x[i] = x_akt;
        y[i] = y_akt+1;
        delay(opoz);
        wstaw_piksel(x[i],y[i],wyp_b,wyp_g,wyp_r);
        update();

      }

  }
  delete[] x;
  delete[] y;
  return(0);
}


int MainWindow::rysuj()
{
    switch (tryb_pracy)
    {
       case 1:
         x1=1;
    };

    update();
    return(0);

}
//---------------------------------------------------------------------------
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    switch (tryb_pracy)
    {
        case 1:
           x0 = event->x() - poczX;
           y0 = event->y() - poczY;
           break;
        case 2:
           x0 = event->x() - poczX;
           y0 = event->y() - poczY;
           break;
        case 3:
           x0 = event->x() - poczX;
           y0 = event->y() - poczY;
           break;
        case 6:
           x0 = event->x() - poczX;
           y0 = event->y() - poczY;
           if(!powoli)
                flood_fill(x0,y0,kolor_tla_b,kolor_tla_g,kolor_tla_r, kolor_wyp_b,kolor_wyp_g,kolor_wyp_r);
           else
               flood_fill_delay(x0,y0,kolor_tla_b,kolor_tla_g,kolor_tla_r, kolor_wyp_b,kolor_wyp_g,kolor_wyp_r);
           break;
    }
}

//---------------------------------------------------------------------------
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    switch (tryb_pracy)
    {
        case 1:
           x1 = event->x() - poczX;
           y1 = event->y() - poczY;
           rysuj_odcinek(x0,y0,x1,y1,kolor_kreski_b,kolor_kreski_g,kolor_kreski_r);
           break;
        case 2:
           x1 = event->x() - poczX;
           y1 = event->y() - poczY;
           rysuj_okrag(x0,y0,x1,y1,kolor_kreski_b,kolor_kreski_g,kolor_kreski_r);
           break;
        case 3:
           x1 = event->x() - poczX;
           y1 = event->y() - poczY;
           rysuj_elipse(x0,y0,x1,y1,kolor_kreski_b,kolor_kreski_g,kolor_kreski_r);
           break;
        case 4:

           if (boki==0)
           {
               x1 = event->x() - poczX;
               y1 = event->y() - poczY;
               boki++;
               x_pocz=x1;
               y_pocz=y1;
           }
           else
           {
               x0 = x1;
               y0 = y1;
               x1 = event->x() - poczX;
               y1 = event->y() - poczY;
              // qDebug()<<x_pocz<<" "<<y_pocz<<" "<<x1<<" "<<y1<<endl;
               if(abs(x1-x_pocz)<10 && abs(y1-y_pocz)<10)
               {
                  // qDebug()<<"trafilem"<<endl;
                   rysuj_odcinek(x_pocz,y_pocz,x0,y0,kolor_kreski_b,kolor_kreski_g,kolor_kreski_r);
                   boki=0;
               }
               else
                    rysuj_odcinek(x0,y0,x1,y1,kolor_kreski_b,kolor_kreski_g,kolor_kreski_r);
           }
           break;

    }
    update();
}
//---------------------------------------------------------------------------

void MainWindow::delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//---------------------------------------------------------------------------

void MainWindow::scanline()
{

   // unsigned char *ptr;
   // ptr = img->bits();

    int i,j;
    int pocz=0, kon=0;

    for(i=0; i<wys; i++)
    {
        j = 0;
        while(j<szer)
        {
            if(czy_taki_kolor(j, i, 255, 255, 255) == 1)
            {
                pocz = j;
                kon = j+1;
                while (czy_taki_kolor(kon,i,255,255,255) == 1 && kon<szer) kon++;
                while (czy_taki_kolor(kon,i,255,255,255) != 1 && kon<szer)
                {
                    kon++;
                }

                j = kon+1;
                if(kon==szer) kon=pocz;
                for(int k=pocz; k<=kon; k++)
                    wstaw_piksel(k,i,kolor_wyp_b,kolor_wyp_g,kolor_wyp_r);
            }
            else
                j++;

        }
    }
}



