#include "userclass.h"

#include "styledprogressbar.h"

UserClass::UserClass()
{
    styledProgressBar = new StyledProgressBar(tr("Simulação do eixo norte"),
                                              StyledProgressBarType::SPECIFIC);
                                              //StyledProgressBarType::GENERAL);
    styledProgressBar->show();
}

UserClass::~UserClass()
{
    if (styledProgressBar != nullptr)
    {
        styledProgressBar->close();
        this->terminate();
        //delete styledProgressBar;
    }
}

SPBState UserClass::getStateOfOwnedObject()
{
    return styledProgressBar->getState();
}

void UserClass::run()
{
    for(double exampleProgress = 0; exampleProgress <=100.0;)
    {
        if (styledProgressBar->getState() == SPBState::Executing)
        {
            styledProgressBar->changeProgress(exampleProgress);
            exampleProgress += 0.1;
        }
        else if (styledProgressBar->getState() == SPBState::Canceled ||
                 styledProgressBar->getState() == SPBState::CloseWindow)
        {
            this->terminate();
            styledProgressBar->close();
            break;
        }

        msleep(10);
    }
}
