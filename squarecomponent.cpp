#include "squarecomponent.h"

SquareComponent::SquareComponent(QWidget* parent): QWidget(parent)
{
    setMinimumSize(300,300);
}

bool SquareComponent::hasHeightForWidth() const
{
    return true;
}

int SquareComponent::heightForWidth(int w) const
{
    return w;
}

int SquareComponent::getAngleInDegreeBasedInPercentage(double percentage)
{
    //Deve converter percent para um valor inteiro entre 0 e 360
    //100   ----   360
    //percent  ---- x
    //x = (percent*360)/100

    double valor = (percentage*360)/100;
    return valor;
}

void SquareComponent::paintEvent(QPaintEvent *)
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
        pen.setColor(Qt::darkYellow);
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
    painter.drawText(rectPerc, QString::number(percentage, 'f', 1));

    font.setPointSize(width() > 100?30:15);
    painter.setFont(font);
    rectPerc =  {(int)(0.60*width()), height()/2, 250, 250};

    rectPerc =  {width()/2, (int) (0.37*height()), 250, 250};
    painter.drawText(rectPerc, QString("%"));
}

void SquareComponent::changePercentageValue(double value)
{
    this->percentage = value;
}
