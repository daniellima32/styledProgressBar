#include "styledprogressbar.h"

#include <QPen>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "squarecomponent.h"

StyledProgressBar::StyledProgressBar
(
        QString title,
        StyledProgressBarType type,
        bool useOpacity,
        double opacity
):
    type (type)
{
    resize(320,370);
    setWindowTitle(title);

    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *midleLayout = new QHBoxLayout;
    QHBoxLayout *downLayout = new QHBoxLayout;

    layout->addLayout(topLayout);
    layout->addLayout(midleLayout);
    layout->addLayout(downLayout);

    //Inserir em topLayout
    label = new QLabel(this);
    label->setText("Executando");
    label->setGeometry(520,10,70,25);
    label->setStyleSheet(
            "background-color: #7FFFD4;"
            "border: 1px solid black;"
            "border-radius: 15px;"
            //"font-size: 25px;"
            );
    label->setAlignment(Qt::AlignCenter);

    topLayout->addStretch();
    topLayout->addWidget(label);

    //Inserir em midleLayout
    square = new SquareComponent(this);
    midleLayout->addWidget(square);

    //Inserir em downlayout
    pauseButton = new QPushButton(this);
    pauseButton->setText("Pausar");
    pauseButton->setGeometry(200,610,90,25);
    pauseButton->setFlat(true);
    pauseButton->setAttribute(Qt::WA_TranslucentBackground);
    pauseButton->setStyleSheet(
        "background-color: white;"
        "border: 1px solid black;"
        "border-radius: 15px;"
        //"font-size: 25px;"
        );

    cancelButton = new QPushButton(this);
    cancelButton->setText("Cancelar");
    cancelButton->setGeometry(310,610,90,25);
    cancelButton->setFlat(true);
    cancelButton->setAttribute(Qt::WA_TranslucentBackground);
    cancelButton->setStyleSheet(
        "background-color: white;"
        "border: 1px solid black;"
        "border-radius: 15px;"
        //"font-size: 25px;"
        );

    downLayout->addStretch();
    downLayout->addWidget(pauseButton);
    downLayout->addWidget(cancelButton);
    downLayout->addStretch();

    //fim de down
    setLayout(layout);

    //Conectando eventos
    QObject::connect(pauseButton, &QPushButton::clicked, [this]()
    {
        if (state == SPBState::Executing)
        {
            state = SPBState::Paused;
            this->pauseButton->setText(tr("Continuar"));
            this->label->setText("Pausada");
        }
        else if (state == SPBState::Paused)
        {
            state = SPBState::Executing;
            this->pauseButton->setText(tr("Pausar"));
            this->label->setText("Executando");
        }
    });

    QObject::connect(cancelButton, &QPushButton::clicked, [this]()
    {
        this->pauseButton->setEnabled(false);
        this->cancelButton->setEnabled(false);
        this->label->setText("Cancelada");

        this->state = SPBState::Canceled;
    });

    setVisible(true);

    if (useOpacity) setWindowOpacity(opacity);
}

StyledProgressBar::~StyledProgressBar()
{
    if (pauseButton != nullptr) delete pauseButton;
    if (cancelButton != nullptr) delete cancelButton;
    if (label != nullptr) delete label;
    if (square != nullptr) delete square;
}

double getValueInRange(double percentage)
{
    if (percentage < 0.0) return 0.0;
    else if (percentage > 100.0) return 100.0;
    else return percentage;
}

void StyledProgressBar::changeProgress(double actual, double total)
{
    //total ----- 100
    //actual ------ x
    //x = (actual*100)/total

    changeProgress((actual*100.)/total);
}

void StyledProgressBar::changeProgress(double percentage)
{
    if (state != SPBState::Executing) return;

    percentage = getValueInRange(percentage);
    changePercentageValue(percentage);

    if (abs(percentage - 100.0) < delta)
    {
        reachedTheEnd();
    }

    //Triggers the redraw
    this->update();
}

void StyledProgressBar::reachedTheEnd()
{
    pauseButton->setEnabled(false);
    cancelButton->setEnabled(false);
    label->setText("Finalizada");

    this->close();

    state = SPBState::End;
}

SPBState StyledProgressBar::getState()
{
    return state;
}

void StyledProgressBar::changePercentageValue(double value)
{
    square->changePercentageValue(value);
}

void StyledProgressBar::resizeEvent(QResizeEvent * event)
{
    if (type==StyledProgressBarType::SPECIFIC)
    {
        int side = qMin(width(), height());
        QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side,
                             side, QRegion::Ellipse);
        QPoint pos1 = pauseButton->pos();
        QPoint pos2 = cancelButton->pos();
        int dx=5, dy=5;
        QRegion regB1 (pos1.rx()-dx, pos1.ry()-dy, pauseButton->width()+2*dx, pauseButton->height()+2*dy);
        QRegion regB2 (pos2.rx()-dx, pos2.ry()-dy, cancelButton->width()+2*dx, cancelButton->height()+2*dy);
        setMask(maskedRegion.united(regB1.united(regB2)));
    }
    else
        QWidget::resizeEvent(event);
}
