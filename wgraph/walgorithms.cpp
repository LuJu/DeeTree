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
#include "walgorithms.h"

//QPointF WAlgorithms::getRelativePosition(int index, int total){
//    double theta=0.0;
//    double r=0.5;
//    double newr=0.0;
//    QPointF center(0.5,0.5);
//    QPointF position;
////    r=qMin(bounds.width(),bounds.height());
//    newr=r*4/5;
//    theta = (2*3.14 / (double)total)*index;
//    position.setY(qSin(theta) * newr);
//    position.setX(qCos(theta) * newr);
//    position=position+center;
//    return position;
//}
QPointF WAlgorithms::getRelativePosition(int index, int n, int k, qreal R, qreal r2){
    double theta=0.0;
    double pi=3.141592;
    double r;
    if(R*2+r2==0.5) r=R+r2;
    else r=r2;
    r=0.5;
    r=R+r2;
    double newr=0.0;
//    QPointF center(0.0,0.0);
    QPointF center(0.5,0.5);
    QPointF position;
//    r=qMin(bounds.width(),bounds.height());
    newr=r;
    theta = (2*pi / (double)k)*index;
    position.setY(qSin(theta) * newr);
    position.setX(qCos(theta) * newr);
    position=position+center;
    return position;


}

QPointF WAlgorithms::getSize(int index, int n, int k){
    double pi=3.141592;
    qreal R=0.5;
    qreal r =0.0;
    qreal r2 = 0.0;
    qreal fn=((1-qSin(pi/n))*(1-qSin(pi/n)))/((1+qSin(pi/n))*(1+qSin(pi/n)));
//    qreal fn=((1-qSin(pi/n))*(1-qSin(pi/n)))/((1+qSin(pi/n))*(1+qSin(pi/n)));
    r =  R * (1 - qSqrt(fn))/2;
    r2 = R * qSqrt(fn);
//    r=r/(qreal)(index/8+1);
    qreal total = r*2+r2;
    if (total!=0.5) qDebug()<<"index : "<<index<<" R : "<<total;
//    if (total!=0.5) return QPoint(0.3,0.1);
    return QPointF(r,r2);
}

//QPointF WAlgorithms::getPosition(int index, int total, QRect bounds){
//    double theta=0.0;
//    double r=0.5;
//    double newr=0.0;
//    QPointF center(0.5,0.5);
//    QPointF position;
////    r=qMin(bounds.width(),bounds.height());
//    newr=r*4/5;
//    theta = (2*3.14 / (double)total)*index;
//    position.setY(qSin(theta) * newr);
//    position.setX(qCos(theta) * newr);
//    position=position+center;
//    return position;
//}
