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
#ifndef WNODE_H
#define WNODE_H

#include <iostream>
#include <iterator>
#include <QList>
#include <QDebug>
#include <qmath.h>

//! This class represents a node in a tree. It provides several methods to
//! manipulate and get information on it
template <class T> class WNode
{
public:
    enum SortingTypes{
        SIZE,
        SIZE_BACK,
        ID,
        TOTAL_SIZE,
        TOTAL_SIZE_BACK
    };
    WNode(const T* data);
    ~WNode();
    void addToChildren(WNode* node);
    inline T* get_data()const{return _data;}
    inline void set_data(T* data){_data=data;}
    inline WNode * get_parent()const{return _parent;}
    inline void set_parent(WNode * parent){_parent=parent;}
    inline unsigned int get_id() const {return _id;}
    inline bool is_root() const {return _parent==NULL;}
    inline bool is_leaf() const {return _children.size()==0;}
    void * detach();
    //! Returns the numnber of children, recursively or not
    /*!
        Returns the number of children that the node has. \n
        If recursive is set to false, it returns only the direct children.
        If set to true, it returns all the descendants in the hierarchy
        \n Status  1 : not implemented
        \param  recursive : Whether it counts all the descendants or not
        \return The number of children
    */
    int get_number_of_children(bool recursive = false) const;
    inline void set_id(quint16 id){_id=id;}

    //! Sorts the children of this node
    /*!
        This function modifies the list of children and sorts them according to the SortingTypes selected
        \param  the sorting type chosen
    */
    void sort(SortingTypes type=SIZE);


//    bool operator<(const WNode<T> &value1,const WNode<T> &value2);
    static bool comparatorSizeLess(const WNode* s1, const WNode* s2);
    static bool comparatorSizeMore(const WNode* s1, const WNode* s2);
    static bool comparatorTotalSizeLess(const WNode* s1, const WNode* s2);
    static bool comparatorTotalSizeMore(const WNode* s1, const WNode* s2);
    static bool comparatorIDLess(const WNode* s1, const WNode* s2);
    static bool comparatorIDMore(const WNode* s1, const WNode* s2);
    int get_number_of_levels();
    int get_level();
    typename QList<WNode<T>* >::const_iterator get_begin()const{return _children.begin();}
    typename QList<WNode<T>* >::const_iterator get_end()const{return _children.end();}
    inline WNode * childAt(int index){ return _children.at(index);}
    int getK(int start=0);
private:
    T* _data;
    unsigned int _id;
    QList<WNode*> _children;
    WNode * _parent;
    bool _sorted;
};

template<class T>
WNode<T>::WNode(const T *data){
    _data=data;_id=0;
    _parent=NULL;
    _sorted=false;
}

template<class T>
WNode<T>::~WNode(){
}

template<class T>
void * WNode<T>::detach(){
    T * ret = _data;
   _data=NULL;
    return ret;
}

template<class T>
void WNode<T>::addToChildren(WNode<T>* node){
    _children.append(node);
    node->set_parent(this);
    _sorted=false;
}

template<class T>
bool operator<(const WNode<T> &value1,const WNode<T> &value2){
    return value1.get_number_of_children()<value2.get_number_of_children();
}
template<class T>
int WNode<T>::get_number_of_children(bool recursive) const{
    typename QList<WNode<T> *>::const_iterator i;
    int number=0;
    if (!recursive){
        return _children.size();
    } else {
        for(i=_children.begin();i!=_children.end();i++){
            number+=((WNode<T>)*i).get_number_of_children(true);
        }
        return number;
    }
}

template<class T>
int WNode<T>::getK(int start){
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

template<class T>
void WNode<T>::sort(SortingTypes type){
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

template<class T>
bool WNode<T>::comparatorSizeLess(const WNode<T>* s1, const WNode<T>* s2)
{
    return (*s1)<(*s2);
}
template<class T>
bool WNode<T>::comparatorSizeMore(const WNode<T>* s1, const WNode<T>* s2)
{
    return (*s2)<(*s1);
}
template<class T>
bool WNode<T>::comparatorTotalSizeLess(const WNode<T>* s1, const WNode<T>* s2)
{
    return (s1->get_number_of_children(true)<s2->get_number_of_children(true));
}
template<class T>
bool WNode<T>::comparatorTotalSizeMore(const WNode<T>* s1, const WNode<T>* s2)
{
    return (s2->get_number_of_children(true)<s1->get_number_of_children(true));
}
template<class T>
bool WNode<T>::comparatorIDLess(const WNode<T>* s1, const WNode<T>* s2)
{
    return s1->get_id()<s2->get_id();
}
template<class T>
bool WNode<T>::comparatorIDMore(const WNode<T>* s1, const WNode<T>* s2)
{
    return s2->get_id()<s1->get_id();
}
template<class T>
int WNode<T>::get_level(){
    if(_parent!=NULL){
        return _parent->get_level()+1;
    } else return 1;
}
template<class T>
int WNode<T>::get_number_of_levels(){
    int levels=0;
    int max=0;
    int current=0;
    if (is_leaf()) levels=1;
    else {
        typename QList<WNode<T>*>::const_iterator i;
        for (i=_children.begin();i!=_children.end();i++){
            current = ((WNode<T>)*i).get_number_of_levels();
            if(max<current) max=current;
        }
        levels = 1+max;
    }
    return levels;
}




#endif
