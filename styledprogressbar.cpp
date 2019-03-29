#include "styledprogressbar.h"

#include <QPen>
#include <QPainter>
#include <QPushButton>
#include <cmath>
#include <QGraphicsScene>

#include <QLabel>

#include <QVBoxLayout>

#include "squarecomponent.h"

StyledProgressBar::StyledProgressBar(QString title)
{
    /*resize(600,700);
    setFixedSize(this->size());
    setWindowTitle(title);

    //Inserir dois botões na interface
    pauseButton = new QPushButton(this);
    pauseButton->setText(tr("Pausar"));
    pauseButton->setGeometry(200,610,90,25);
    pauseButton->setFlat(true);
    pauseButton->setAttribute(Qt::WA_TranslucentBackground);
    pauseButton->setStyleSheet(
        "background-color: white;"
        "border: 1px solid black;"
        "border-radius: 15px;"
        //"font-size: 25px;"
        );
    QGraphicsScene scene;
    QGraphicsProxyWidget *pButtonProxyWidget = scene.addWidget(pauseButton);

    cancelButton = new QPushButton(this);
    cancelButton->setText(tr("Cancelar"));
    cancelButton->setGeometry(310,610,90,25);
    cancelButton->setFlat(true);
    cancelButton->setAttribute(Qt::WA_TranslucentBackground);
    cancelButton->setStyleSheet(
        "background-color: white;"
        "border: 1px solid black;"
        "border-radius: 15px;"
        //"font-size: 25px;"
        );

    QObject::connect(pauseButton, &QPushButton::clicked, [this]()
    {
        if (state == SPBState::Executing)
        {
            state = SPBState::Paused;
            this->pauseButton->setText(tr("Continuar"));
            label->setText("Pausada");
        }
        else if (state == SPBState::Paused)
        {
            state = SPBState::Executing;
            this->pauseButton->setText(tr("Pausar"));
            label->setText("Executando");
        }
    });

    QObject::connect(cancelButton, &QPushButton::clicked, [this]()
    {
        this->pauseButton->setEnabled(false);
        this->cancelButton->setEnabled(false);
        label->setText("Cancelada");

        this->state = SPBState::Canceled;
    });

    label = new QLabel(this);
    label->setText("Executando");
    label->setGeometry(520,10,70,25);
    label->setStyleSheet(
            "background-color: #7FFFD4;"
            "border: 1px solid black;"
            "border-radius: 15px;"
            //"font-size: 25px;"
            );
    label->setAlignment(Qt::AlignCenter);*/

    resize(500,500);

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
}

void StyledProgressBar::changeProgress(double percentage)
{
    if (state != SPBState::Executing) return;

    //if (percentage < 0.0) percentage = 0.0;
    if (percentage < 0.0) changePercentageValue(0.0);
    else if (percentage > 100.0)
    {
        //percentage = 100.0;
        changePercentageValue(100.0);
        reachedTheEnd();
    }
    else
        //this->percentage = percentage;
        changePercentageValue(percentage);

    if (abs(this->percentage - 100.0) < delta)
    {
        //reachedTheEnd();
        label->setText("Finalizada");
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
}

/*void StyledProgressBar::paintEvent(QPaintEvent *)
{
    QPen pen(Qt::lightGray);
    pen.setWidth(30);
    QBrush brush(Qt::lightGray);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    double diffX = 50, diffY = 50;
    QRect rect(0+diffX, 0+diffY, 500, 500);

    //Desenhar o fundo cinza em círculo
    int startAngle = -90*16; //equivale a -90 (graus)
    int arcLength = 360*16; //equivale a 180 (graus)

    painter.drawArc(rect, startAngle, arcLength);

    int angle = getAngleInDegreeBasedInPercentage(percentage);

    if (angle > 360)
    {
        angle = 360;
        percentage = 100.0;
    }

    // Desenhar a parte indicadora do processamento
    if (angle < 90)
        pen.setColor(Qt::darkGray);
    else if (angle < 180)
        pen.setColor(Qt::darkBlue);
    else if (angle < 270)
        pen.setColor(Qt::darkCyan);
    else
        pen.setColor(Qt::darkGreen);

    painter.setPen(pen);

    startAngle = -90*16; //equivale a -90 (graus)
    arcLength = -angle*16; //equivale a 180 (graus)
    //aqui, valor começa de 0, de 10 em 10,até 360

    painter.drawArc(rect, startAngle, arcLength);

    // Desenhar um círculo interno na cor cinza escuro
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);
    painter.drawEllipse(QPoint{(int)diffX+250, (int)diffY+250},210,210);

    // Escrever textos que indicam percentual feito
    pen.setColor(Qt::white);
    QFont font;
    font.setPointSize(77);
    painter.setPen(pen);
    painter.setFont(font);

    QRect rectPerc {(int)diffX+250-110,(int)diffY+250+5, 250, 250};
    int porcentageAsInteger = getPorcentageAsInteger(percentage);
    painter.drawText(rectPerc, QString::number(porcentageAsInteger));

    font.setPointSize(40);
    painter.setFont(font);
    rectPerc =  {(int)diffX+250+100,(int)diffY+250, 250, 250};

    int temp = getDecimalPartOfPercentage(percentage, porcentageAsInteger);
    painter.drawText(rectPerc, QString("0.")+QString::number(temp));

    rectPerc =  {(int)diffX+250,(int)diffY+220, 250, 250};
    painter.drawText(rectPerc, QString("%"));
}*/

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
