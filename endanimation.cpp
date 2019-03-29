#include "endanimation.h"

#include "squarecomponent.h"

EndAnimation::EndAnimation(SquareComponent* squareComponent):
    squareComponent(squareComponent)
{

}

EndAnimation::~EndAnimation()
{

}

void EndAnimation::run()
{
    for(double exampleProgress = 0; exampleProgress <=100.0;exampleProgress -= 0.1)
    {
        squareComponent->changePercentageValue(exampleProgress);
        squareComponent->update();
        msleep(5);
    }
}
