#ifndef STYLEDPROGRESSBAR_H
#define STYLEDPROGRESSBAR_H

#include <QWidget>
#include <QString>

class StyledProgressBar : public QWidget
{
    Q_OBJECT

public:
    StyledProgressBar(QString title = "Progress Bar");

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
