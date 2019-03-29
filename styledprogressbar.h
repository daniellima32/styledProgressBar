#ifndef STYLEDPROGRESSBAR_H
#define STYLEDPROGRESSBAR_H

#include <QWidget>
#include <QString>

#include "spbstate.h"

class QPushButton;
class QLabel;
class SquareComponent;

class StyledProgressBar : public QWidget
{
    Q_OBJECT

public:
    StyledProgressBar(QString title = "Progress Bar");

    void changeProgress(double percentage);

    //void paintEvent(QPaintEvent * /* event */);

    SPBState getState();

private:
    void changePercentageValue(double value);
    int getPorcentageAsInteger(double entry);
    int getDecimalPartOfPercentage(double entry, int integerPart);

    int getAngleInDegreeBasedInPercentage(double percentage);

    const double delta = 0.000005;

    double percentage; //The percentage informed by the user

    SPBState state = SPBState::Executing;

    QPushButton *pauseButton = nullptr;
    QPushButton *cancelButton = nullptr;
    QLabel *label = nullptr;
    SquareComponent* square = nullptr;
    void reachedTheEnd();
};

#endif // STYLEDPROGRESSBAR_H
