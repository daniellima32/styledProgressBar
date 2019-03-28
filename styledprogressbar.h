#ifndef STYLEDPROGRESSBAR_H
#define STYLEDPROGRESSBAR_H

#include <QWidget>

class StyledProgressBar : public QWidget
{
    Q_OBJECT

public:
    StyledProgressBar();

    void changeProgress(double percentage);

    void paintEvent(QPaintEvent * /* event */);

private:
    int getPorcentageAsInteger(double entry);
    int getDecimalPartOfPercentage(double entry, int integerPart);

    int getAngleInDegreeBasedInPercentage(double percentage);

    const double delta = 0.000005;

    double percentage; //The percentage informed by the user
};

#endif // STYLEDPROGRESSBAR_H
