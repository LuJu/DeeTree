/*
Copyright (c) 2013, Lucas Juliéron
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#include "graphicbuffer.h"
GraphicBuffer::GraphicBuffer() :
    QPainter()
{
    resetPen();
}


void GraphicBuffer::drawStandardCircle(QRect bounds, QString message, int type){
    drawStandardCircle(bounds.center().x(),bounds.center().y(),bounds.width()/2,message,type);
}

void GraphicBuffer::drawStandardCircle(int x, int y, int r, QString message, int type){
    reset();
    standardBrush(x,y,r);
    setBrush(_brush);
    setPen(_pen);

    if (type==0){
        drawEllipse(QPoint(x,y),r,r);
        QRect  textBounds(x-r/2,y-10,r,20);
        QFont f;
        f.setPointSize(8);
        setFont(f);
        setBrush(Qt::white);
        drawText(textBounds,Qt::AlignCenter | Qt::TextWordWrap | Qt::TextDontClip,message);
    }
    else if (type==1){
        _pen.setWidth(5);
        drawEllipse(QPoint(x,y),2,2);
    }
}

void GraphicBuffer::resetPen(){
    _pen.setColor(Qt::darkCyan);
    _pen.setWidth(1);
}

void GraphicBuffer::standardBrush(int x, int y, int r){
    QPoint r1(x,y);
    QPoint r2(x+r/2,y+r/2);
    QLinearGradient gradient2(r1,r2);
    gradient2.setColorAt(0, Qt::white);
    gradient2.setColorAt(1, Qt::cyan);

    _brush=QBrush(gradient2);
}

void GraphicBuffer::reset(){
    resetPen();
}
