#include "userclass.h"

#include "styledprogressbar.h"

UserClass::UserClass(StyledProgressBar * styledProgressBar): styledProgressBar(styledProgressBar)
{

}

UserClass::~UserClass()
{
    /*if (styledProgressBar != nullptr)
    {
        styledProgressBar->setVisible(false);
        styledProgressBar->close();
        delete styledProgressBar;
    }*/
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
                 styledProgressBar->getState() == SPBState::End)
        {
            //styledProgressBar->close();
            //break;
        }
        //msleep(50);
        msleep(10);
    }

    /*if (styledProgressBar != nullptr)
    {
        styledProgressBar->setVisible(false);
        styledProgressBar->close();
        delete styledProgressBar;
    }*/

    //styledProgressBar->close();
}
