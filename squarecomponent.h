#ifndef SQUARECOMPONENT_H
#define SQUARECOMPONENT_H

#include <QWidget>

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

    bool hasWidthForHeight() const override
    {
        return true;
    }

    int widthForHeight(int h) const override
    {
        return h;
    }

};

#endif // SQUARECOMPONENT_H
