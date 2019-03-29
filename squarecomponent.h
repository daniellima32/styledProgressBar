#ifndef SQUARECOMPONENT_H
#define SQUARECOMPONENT_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QRect>

class SquareComponent: public QWidget
{
public:
    SquareComponent(QWidget* parent): QWidget(parent)
    {
        setMinimumSize(200,200);
    }

    bool hasHeightForWidth() const override
    {
        return true;
    }

    int heightForWidth(int w) const override
    {
        return w;
    }

    /*bool hasWidthForHeight() const override
    {
        return true;
    }

    int widthForHeight(int h) const override
    {
        return h;
    }*/

    double percentage = 0.25;
    double diffX = 20;
    double diffY = 20;

    void paintEvent(QPaintEvent *) override
    {
        QPen pen(Qt::lightGray);
        pen.setWidth(30);
        QBrush brush(Qt::lightGray);

        QPainter painter(this);
        painter.setPen(pen);
        painter.setBrush(brush);

        //double diffX = 50, diffY = 50;
        //QRect rect(0, 0, width(), height());
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
        /*pen.setColor(Qt::lightGray);
        painter.setPen(pen);
        painter.drawEllipse(QPoint{(int)diffX+250, (int)diffY+250},210,210);*/

        /* Escrever textos que indicam percentual feito */
        /*pen.setColor(Qt::white);
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
        painter.drawText(rectPerc, QString("%"));*/
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

};

#endif // SQUARECOMPONENT_H
