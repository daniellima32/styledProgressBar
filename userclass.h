#ifndef USERCLASS_H
#define USERCLASS_H

#include <QThread>

class StyledProgressBar;

#include "spbstate.h"

class UserClass : public QThread
{
private:
    StyledProgressBar* styledProgressBar = nullptr;

public:
    UserClass();
    ~UserClass();

    void run() override;
    SPBState getStateOfOwnedObject();
};

#endif // USERCLASS_H
