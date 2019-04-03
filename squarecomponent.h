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
    SquareComponent(QWidget* parent);

    ~SquareComponent(){}

    bool hasHeightForWidth() const override;

    int heightForWidth(int w) const override;

    double percentage = 0.0;
    double diffX = 20;
    double diffY = 20;
    const double delta = 0.000005;

    void changePercentageValue(double value);

    void paintEvent(QPaintEvent *) override;

    int getAngleInDegreeBasedInPercentage(double percentage);
};

#endif // SQUARECOMPONENT_H
