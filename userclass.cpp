#include "userclass.h"

#include "styledprogressbar.h"

UserClass::UserClass()
{
    styledProgressBar = new StyledProgressBar(tr("Simulação do eixo norte"));
    styledProgressBar->show();
}

UserClass::~UserClass()
{
    if (styledProgressBar != nullptr)
    {
        this->terminate();
        delete styledProgressBar;
    }
}

void UserClass::run()
{
    for(double exampleProgress = 0; exampleProgress <=100.0;exampleProgress += 0.1)
    {
        styledProgressBar->changeProgress(exampleProgress);
        msleep(50);
    }
}
