#include "styledprogressbar.h"

#include <QPen>
#include <QPainter>
#include <cmath>

StyledProgressBar::StyledProgressBar()
{
    resize(600,600);
    setFixedSize(this->size());
    setWindowTitle(tr("Basic Drawing"));
}

void StyledProgressBar::changeProgress(double percentage)
{
    if (percentage < 0.0) percentage = 0.0;
    else if (percentage > 100.0) percentage = 100.0;
    else
        this->percentage = percentage;

    //Triggers the redraw
    this->update();
}

void StyledProgressBar::paintEvent(QPaintEvent *)
{
    QPen pen(Qt::lightGray);
    pen.setWidth(30);
    QBrush brush(Qt::lightGray);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    double diffX = 50, diffY = 50;
    QRect rect(0+diffX, 0+diffY, 500, 500);

    /* Desenhar o fundo cinza em círculo */
    int startAngle = -90*16; //equivale a -90 (graus)
    int arcLength = 360*16; //equivale a 180 (graus)

    painter.drawArc(rect, startAngle, arcLength);

    int angle = getAngleInDegreeBasedInPercentage(percentage);

    if (angle > 360)
    {
        angle = 360;
        percentage = 100.0;
    }

    /* Desenhar a parte indicadora do processamento */
    if (angle < 90)
        pen.setColor(Qt::darkGray);
    else if (angle < 180)
        pen.setColor(Qt::darkBlue);
    else if (angle < 270)
        pen.setColor(Qt::darkCyan);
    else
        pen.setColor(Qt::darkGreen);

    painter.setPen(pen);

    startAngle = -90*16; //equivale a -90 (graus)
    arcLength = -angle*16; //equivale a 180 (graus)
    //aqui, valor começa de 0, de 10 em 10,até 360

    painter.drawArc(rect, startAngle, arcLength);

    /* Desenhar um círculo interno na cor cinza escuro */
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);
    painter.drawEllipse(QPoint{(int)diffX+250, (int)diffY+250},210,210);

    /* Escrever textos que indicam percentual feito */
    pen.setColor(Qt::white);
    QFont font;
    font.setPointSize(77);
    painter.setPen(pen);
    painter.setFont(font);

    QRect rectPerc {(int)diffX+250-110,(int)diffY+250+5, 250, 250};
    int porcentageAsInteger = getPorcentageAsInteger(percentage);
    painter.drawText(rectPerc, QString::number(porcentageAsInteger));

    font.setPointSize(40);
    painter.setFont(font);
    rectPerc =  {(int)diffX+250+100,(int)diffY+250, 250, 250};

    int temp = getDecimalPartOfPercentage(percentage, porcentageAsInteger);
    painter.drawText(rectPerc, QString("0.")+QString::number(temp));

    rectPerc =  {(int)diffX+250,(int)diffY+220, 250, 250};
    painter.drawText(rectPerc, QString("%"));
}

int StyledProgressBar::getAngleInDegreeBasedInPercentage(double percentage)
{
    //Deve converter percent para um valor inteiro entre 0 e 360
    //100   ----   360
    //percent  ---- x
    //x = (percent*360)/100

    double valor = (percentage*360)/100;
    return valor;
}

int StyledProgressBar::getPorcentageAsInteger(double entry)
{
    double varFloor = floor(entry);
    double varCeil = ceil(entry); //Teto
    if (abs(varCeil - entry) < delta) return varCeil;
    else return varFloor;
}

int StyledProgressBar::getDecimalPartOfPercentage(double entry, int integerPart)
{
    double varFloor = floor(entry);
    double difference = entry - varFloor;
    difference *= 10;
    double differenceCeil = ceil(difference);
    double differenceFloor = floor(difference);
    if (abs(differenceCeil - difference) < delta)
    {
        if (abs(10.0 - differenceCeil) < delta) return 0;
        else return differenceCeil;
    }
    else
    {
        return difference;
    }
}
