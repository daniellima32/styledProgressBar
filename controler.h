#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include <QThread>
#include "window.h"

class Controler : public QThread
//! [1] //! [2]
{
private:
    Window &window;

public:
    Controler(Window &window, QObject *parent = NULL) : QThread(parent), window(window)
    {
    }

    void run() override
    {
        for(double counter = 0; counter <=100.0;counter += 0.1)
        {
            window.animation();
            msleep(50);
            //msleep(200);
        }
    }
};

#endif // CONTROLER_H
