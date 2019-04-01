#include "userclass.h"

#include "styledprogressbar.h"

UserClass::UserClass()
{
    styledProgressBar = new StyledProgressBar(tr("Simulação do eixo norte"),
                                              //StyledProgressBarType::SPECIFIC);
                                              StyledProgressBarType::GENERAL);
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

void UserClass::run()
{
    for(double exampleProgress = 0; exampleProgress <=100.0;)
    {
        if (styledProgressBar->getState() == SPBState::Executing)
        {
            styledProgressBar->changeProgress(exampleProgress);
            exampleProgress += 0.1;
        }

        msleep(10);
    }
}
