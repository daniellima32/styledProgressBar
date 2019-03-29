#include "styledprogressbar.h"

#include <QPen>
#include <QPainter>
#include <QPushButton>
#include <cmath>
#include <QGraphicsScene>

#include <QLabel>

#include <QVBoxLayout>

#include "squarecomponent.h"

#include "endanimation.h"

StyledProgressBar::StyledProgressBar(QString title, StyledProgressBarType type):
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
    //square->setStyleSheet("background-color:black;");
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


    //new
    /*setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setParent(0); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up*/

    //setStyleSheet("QWidget { background: transparent; }"); //makes the header transparent
    //setAttribute(Qt::WA_TranslucentBackground);

    setWindowOpacity(0.9);


    //layout->setStyleSheet("background-color: transparent;");
}

StyledProgressBar::~StyledProgressBar()
{
    int a = 10;
}

void StyledProgressBar::changeProgress(double percentage)
{
    if (state != SPBState::Executing) return;

    if (percentage < 0.0) changePercentageValue(0.0);
    else if (percentage > 100.0)
    {
        //percentage = 100.0;
        changePercentageValue(100.0);
        reachedTheEnd();
    }
    else
        changePercentageValue(percentage);

    //if (abs(this->percentage - 100.0) < delta)
    if (abs(percentage - 100.0) < delta)
    {
        //label->setText("Finalizada");
        //reachedTheEnd();

        EndAnimation* anim = new EndAnimation(square);
        anim->start();
    }

    //Triggers the redraw
    this->update();
}

void StyledProgressBar::reachedTheEnd()
{
    pauseButton->setEnabled(false);
    cancelButton->setEnabled(false);
    label->setText("Finalizada");

    state = SPBState::Finished;

    //Animation
    EndAnimation endAnimation(square);
    endAnimation.start();
}

SPBState StyledProgressBar::getState()
{
    return state;
}

void StyledProgressBar::changePercentageValue(double value)
{
    square->changePercentageValue(value);
}

int StyledProgressBar::getAngleInDegreeBasedInPercentage(double percentage)
{
    //Deve converter percent para um valor inteiro entre 0 e 360
    //100   ----   360
    //percent  ---- x
    //x = (percent*360)/100

    double valor = (percentage*360)/100;
    return valor;
}

int StyledProgressBar::getPorcentageAsInteger(double entry)
{
    double varFloor = floor(entry);
    double varCeil = ceil(entry); //Teto
    if (abs(varCeil - entry) < delta) return varCeil;
    else return varFloor;
}

int StyledProgressBar::getDecimalPartOfPercentage(double entry, int integerPart)
{
    double varFloor = floor(entry);
    double difference = entry - varFloor;
    difference *= 10;
    double differenceCeil = ceil(difference);
    double differenceFloor = floor(difference);
    if (abs(differenceCeil - difference) < delta)
    {
        if (abs(10.0 - differenceCeil) < delta) return 0;
        else return differenceCeil;
    }
    else
    {
        return difference;
    }
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
        //QRegion regB1 (pos.rx(), pos.ry(), pauseButton->width(), pauseButton->height());
        QRegion regB1 (pos1.rx()-dx, pos1.ry()-dy, pauseButton->width()+2*dx, pauseButton->height()+2*dy);
        QRegion regB2 (pos2.rx()-dx, pos2.ry()-dy, cancelButton->width()+2*dx, cancelButton->height()+2*dy);
        //setMask(maskedRegion.united(regB1));
        setMask(maskedRegion.united(regB1.united(regB2)));
    }
    else
        QWidget::resizeEvent(event);
}
