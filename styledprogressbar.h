#ifndef STYLEDPROGRESSBAR_H
#define STYLEDPROGRESSBAR_H

#include <QWidget>
#include <QString>

#include "spbstate.h"

class QPushButton;
class QLabel;
class SquareComponent;

enum class StyledProgressBarType
{
    GENERAL, SPECIFIC
};

class StyledProgressBar : public QWidget
{
    Q_OBJECT

public:
    StyledProgressBar
    (
            QString title = "Progress Bar",
            StyledProgressBarType type = StyledProgressBarType::GENERAL,
            bool useOpacity = false,
            double opacity = 1.0
    );
    ~StyledProgressBar();

    void changeProgress(double percentage);

    SPBState getState();

    void resizeEvent(QResizeEvent *);
private:
    void changePercentageValue(double value);
    void reachedTheEnd();

    const double delta = 0.000005;
    StyledProgressBarType type;
    SPBState state = SPBState::Executing;
    QPushButton *pauseButton = nullptr;
    QPushButton *cancelButton = nullptr;
    QLabel *label = nullptr;
    SquareComponent* square = nullptr;
};

#endif // STYLEDPROGRESSBAR_H
