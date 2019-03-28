#ifndef USERCLASS_H
#define USERCLASS_H

#include <QThread>

class StyledProgressBar;

class UserClass : public QThread
{
private:
    StyledProgressBar* styledProgressBar = nullptr;

public:
    UserClass();
    ~UserClass();

    void run() override;
};

#endif // USERCLASS_H
