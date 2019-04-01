#ifndef ENDANIMATION_H
#define ENDANIMATION_H

#include <QThread>

class SquareComponent;

class EndAnimation : public QThread
{
public:
    EndAnimation(SquareComponent* squareComponent);
    ~EndAnimation();

    void run() override;

private:
    SquareComponent* squareComponent = nullptr;
};

#endif // ENDANIMATION_H
