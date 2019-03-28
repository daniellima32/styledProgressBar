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
#include <QtWidgets>
#include <QPushButton>
#include <cmath>

void Window::animation()
{
    //Forma 3
    if(this->percentagem<=100.0)
    {
        //this->percentagem += progress;
        this->percentagem = progress;
        this->changeProgress(this->percentagem);

        progress+=0.1;
    }
}

Window::Window()
{
    resize(600,600);
    setFixedSize(this->size());
    setWindowTitle(tr("Basic Drawing"));

    QPushButton *b = new QPushButton("clique", this);

    connect(b, &QPushButton::clicked, [this](bool)
    {       
        //Forma 2
        this->percentagem += 5;
        this->changeProgress(percentagem);

        //Forma 1
        /*this->valor += 10;
        this->update();*/
    });
}

void Window::paintEvent(QPaintEvent * /* event */)
{
    QPen pen(Qt::lightGray);
    pen.setWidth(30);
    QBrush brush(Qt::lightGray);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    double diffX = 50, diffY = 50;
    QRect rect(0+diffX, 0+diffY, 500, 500);

    /* Desenhar o fundo cinza em círculo */
    int startAngle = -90*16; //equivale a -90 (graus)
    int arcLength = 360*16; //equivale a 180 (graus)

    painter.drawArc(rect, startAngle, arcLength);

    if (valor > 360)
    {
        valor = 360;
        percentagem = 100;
    }

    /* Desenhar a parte indicadora do processamento */
    if (valor < 90)
        pen.setColor(Qt::darkGray);
    else if (valor < 180)
        pen.setColor(Qt::darkBlue);
    else if (valor < 270)
        pen.setColor(Qt::darkCyan);
    else
        pen.setColor(Qt::darkGreen);

    painter.setPen(pen);

    startAngle = -90*16; //equivale a -90 (graus)
    arcLength = -valor*16; //equivale a 180 (graus)
    //aqui, valor começa de 0, de 10 em 10,até 360

    painter.drawArc(rect, startAngle, arcLength);

    /* Desenhar um círculo interno na cor cinza escuro */
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);
    painter.drawEllipse(QPoint{(int)diffX+250, (int)diffY+250},210,210);

    /* Escrever textos que indicam percentual feito */
    pen.setColor(Qt::white);
    QFont font;
    font.setPointSize(77);
    painter.setPen(pen);
    painter.setFont(font);
    /*painter.drawText(QPoint{(int)diffX+250-110,(int)diffY+250+5},
                     QString::number(percentagem));*/
    QRect rectPerc {(int)diffX+250-110,(int)diffY+250+5, 250, 250};
    //painter.drawText(rectPerc, QString::number(percentagem));
    //painter.drawText(rectPerc, QString::number((int)percentagem));
    //painter.drawText(rectPerc, QString::number(ceil(percentagem)));
    painter.drawText(rectPerc, QString::number(floor(percentagem)));

    font.setPointSize(40);
    painter.setFont(font);
    rectPerc =  {(int)diffX+250+100,(int)diffY+250, 250, 250};
    //painter.drawText(rectPerc, QString::number(percentagem - (int)percentagem));
    subtr = percentagem - floor(percentagem);
    int res = subtr * 10;
    expression = subtr <= 0.9 && subtr >= 0.1;
    painter.drawText(rectPerc, QString("0.")+QString::number(res));
    //painter.drawText(rectPerc, QString::number(1.0 - (ceil(percentagem) - percentagem)));

    rectPerc =  {(int)diffX+250,(int)diffY+220, 250, 250};
    painter.drawText(rectPerc, QString("%"));
}

/*!
 * \brief Window::changeProgress: must receve a value between 0.0 and 100.0
 * \param percent
 */
void Window::changeProgress(double percent)
{
    //Deve converter percent para um valor inteiro entre 0 e 360
    //100   ----   360
    //percent  ---- x
    //x = (percent*360)/100

    valor = (percent*360)/100;

    //está faltando o uso de percent para alterar as outras informações

    this->update();
}

