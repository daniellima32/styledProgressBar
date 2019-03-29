#ifndef SQUARECOMPONENT_H
#define SQUARECOMPONENT_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QRect>
#include <cmath>

class SquareComponent: public QWidget
{
public:
    SquareComponent(QWidget* parent): QWidget(parent)
    {
        setMinimumSize(300,300);
    }

    bool hasHeightForWidth() const override
    {
        return true;
    }

    int heightForWidth(int w) const override
    {
        return w;
    }

    double percentage = 0.0;
    double diffX = 20;
    double diffY = 20;
    const double delta = 0.000005;

    void changePercentageValue(double value)
    {
        this->percentage = value;
    }

    void paintEvent(QPaintEvent *) override
    {
        QPen pen(Qt::lightGray);
        pen.setWidth(30);
        QBrush brush(Qt::lightGray);

        QPainter painter(this);
        painter.setPen(pen);
        painter.setBrush(brush);

        QRect rect(diffX, diffY, width()-2*diffX, height()-2*diffY);

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
        painter.drawEllipse(QPoint{width()/2, height()/2},(width()/2)-3*diffX,(height()/2)-3*diffY);

        /* Escrever textos que indicam percentual feito */
        pen.setColor(Qt::white);
        QFont font;
        font.setPointSize(width() > 100?40:20);
        painter.setPen(pen);
        painter.setFont(font);

        QRect rectPerc {(int)(0.30*width()),(double)(0.50*height()), 100, 100};
        int porcentageAsInteger = getPorcentageAsInteger(percentage);
        painter.drawText(rectPerc, QString::number(porcentageAsInteger));

        font.setPointSize(width() > 100?30:15);
        painter.setFont(font);
        rectPerc =  {(int)(0.60*width()), height()/2, 250, 250};

        int temp = getDecimalPartOfPercentage(percentage, porcentageAsInteger);
        painter.drawText(rectPerc, QString("0.")+QString::number(temp));

        rectPerc =  {width()/2, (int) (0.37*height()), 250, 250};
        painter.drawText(rectPerc, QString("%"));
    }

    int getAngleInDegreeBasedInPercentage(double percentage)
    {
        //Deve converter percent para um valor inteiro entre 0 e 360
        //100   ----   360
        //percent  ---- x
        //x = (percent*360)/100

        double valor = (percentage*360)/100;
        return valor;
    }

    int getPorcentageAsInteger(double entry)
    {
        double varFloor = floor(entry);
        double varCeil = ceil(entry); //Teto
        if (abs(varCeil - entry) < delta) return varCeil;
        else return varFloor;
    }

    int getDecimalPartOfPercentage(double entry, int integerPart)
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


};

#endif // SQUARECOMPONENT_H
