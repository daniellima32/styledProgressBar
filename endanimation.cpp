#include "endanimation.h"

#include "squarecomponent.h"

EndAnimation::EndAnimation(SquareComponent* squareComponent):
    squareComponent(squareComponent)
{

}

EndAnimation::~EndAnimation()
{
    this->terminate();
}

void EndAnimation::run()
{
    squareComponent->setInFinalAnimation();
    for(double exampleProgress = 100.0; exampleProgress >=0.0;exampleProgress -= 5)
    {
        squareComponent->changePercentageValue(exampleProgress);
        squareComponent->update();
        msleep(77);
    }
    while(1)
    {
        squareComponent->changePercentageValue(100);
        squareComponent->update();
        msleep(500);

        squareComponent->changePercentageValue(0);
        squareComponent->update();
        msleep(500);
    }
}
