/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "window.h"

#include <QApplication>
#include "userclass.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <squarecomponent.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*Window window;
    window.show();

    Controler controler(window);
    controler.start();*/

    //UserClass userClass;
    //userClass.start();

    QWidget widget;
    widget.resize(500,500);
    //widget.setVisible(true);

    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *midleLayout = new QHBoxLayout;
    QHBoxLayout *downLayout = new QHBoxLayout;

    layout->addLayout(topLayout);
    layout->addLayout(midleLayout);
    layout->addLayout(downLayout);

    //Inserir em topLayout
    QLabel* label = new QLabel(&widget);
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
    SquareComponent* square = new SquareComponent(&widget);
    //square->setStyleSheet("background-color:black;");
    midleLayout->addWidget(square);


    //Inserir em downlayout
    QPushButton* pauseButton = new QPushButton(&widget);
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

    QPushButton* cancelButton = new QPushButton(&widget);
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

    widget.setLayout(layout);

    widget.setVisible(true);

    return app.exec();
}
