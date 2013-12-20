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
#include "wnode.h"


WNode::WNode(void *data){
    _data=data;_id=0;
    _parent=NULL;
    _sorted=false;
}

WNode::~WNode(){
    if(_data!=NULL){
        qWarning()<<"Data not empty for node "<<_id<<" ";
    }
}

void * WNode::detach(){
    void * ret = _data;
   _data=NULL;
    return ret;
}

void WNode::addToChildren(WNode* node){
    _children.append(node);
    node->set_parent(this);
    _sorted=false;
}

bool operator<(const WNode &value1,const WNode &value2){
    return value1.get_number_of_children()<value2.get_number_of_children();
}

int WNode::get_number_of_children(bool recursive) const{
    QList<WNode*>::const_iterator i;
    int number=0;
    if (!recursive){
        return _children.size();
    } else {
        for(i=_children.begin();i!=_children.end();i++){
            number+=((WNode)*i).get_number_of_children(true);
        }
        return number;
    }
}

int WNode::getK(int start){
    if (!is_leaf()){
        double pi=3.141592;
        int k = 1;
        double n=get_number_of_children()-start;
        double fn=((1-qSin(pi/n))*(1-qSin(pi/n)))/((1+qSin(pi/n))*(1+qSin(pi/n)));
        if (!_sorted) sort(SIZE_BACK);
        int total_grand_children=0;
        int k_grand_children=0;
        for(int i=start;i<get_number_of_children();i++){
            total_grand_children+=_children[i]->get_number_of_children();
        }
        if (total_grand_children>0){
            while(k_grand_children/total_grand_children<=fn){
                for(int j=start;j<k+start;j++){
                    k_grand_children+=_children[j]->get_number_of_children();
                }
                k++;
            }
            return k;
        }
        else return n;
    }
    return 0.0;
}

void WNode::sort(SortingTypes type){
    switch (type){
    case SIZE:
        qSort(_children.begin(),_children.end(),comparatorSizeLess);
        break;
    case SIZE_BACK:
        qSort(_children.begin(),_children.end(),comparatorSizeMore);
        break;
    case ID:
         qSort(_children.begin(),_children.end(),comparatorIDLess);
        break;
    case TOTAL_SIZE:
        qSort(_children.begin(),_children.end(),comparatorTotalSizeLess);
        break;
    case TOTAL_SIZE_BACK:
        qSort(_children.begin(),_children.end(),comparatorTotalSizeMore);
        break;
    default:
        _sorted=false;
        break;
    }
    _sorted=true;
}

bool WNode::comparatorSizeLess(const WNode* s1, const WNode* s2)
{
    return (*s1)<(*s2);
}

bool WNode::comparatorSizeMore(const WNode* s1, const WNode* s2)
{
    return (*s2)<(*s1);
}

bool WNode::comparatorTotalSizeLess(const WNode* s1, const WNode* s2)
{
    return (s1->get_number_of_children(true)<s2->get_number_of_children(true));
}

bool WNode::comparatorTotalSizeMore(const WNode* s1, const WNode* s2)
{
    return (s2->get_number_of_children(true)<s1->get_number_of_children(true));
}

bool WNode::comparatorIDLess(const WNode* s1, const WNode* s2)
{
    return s1->get_id()<s2->get_id();
}

bool WNode::comparatorIDMore(const WNode* s1, const WNode* s2)
{
    return s2->get_id()<s1->get_id();
}

quint16 WNode::get_level(){
    if(_parent!=NULL){
        return _parent->get_level()+1;
    } else return 1;
}

quint16 WNode::get_number_of_levels(){
    quint16 levels=0;
    quint16 max=0;
    quint16 current=0;
    if (is_leaf()) levels=1;
    else {
        QList<WNode*>::const_iterator i;
        for (i=_children.begin();i!=_children.end();i++){
            current = ((WNode)*i).get_number_of_levels();
            if(max<current) max=current;
        }
        levels = 1+max;
    }
    return levels;
}

