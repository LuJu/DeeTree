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
class WNode
{
public:
    enum SortingTypes{
        SIZE,
        SIZE_BACK,
        ID,
        TOTAL_SIZE,
        TOTAL_SIZE_BACK
    };
    WNode(void *data=NULL);
    ~WNode();
    void addToChildren(WNode* node);
    inline void* get_data()const{return _data;}
    inline void set_data(void* data){_data=data;}
    inline WNode * get_parent()const{return _parent;}
    inline void set_parent(WNode * parent){_parent=parent;}
    inline unsigned int get_id() const {return _id;}
    inline bool is_root() const {return _parent==NULL;}
    inline bool is_leaf() const {return _children.size()==0;}
    void * detach();
    //! Returns the numnber of children, recursively or not
    /*!
        Returns the number of children that the node has. \n
        If recursive is set to false, it returns only the direct children. If set to true, it returns all the descendants in the hierarchy
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


    friend bool operator<(const WNode &value1,const WNode &value2);
    static bool comparatorSizeLess(const WNode* s1, const WNode* s2);
    static bool comparatorSizeMore(const WNode* s1, const WNode* s2);
    static bool comparatorTotalSizeLess(const WNode* s1, const WNode* s2);
    static bool comparatorTotalSizeMore(const WNode* s1, const WNode* s2);
    static bool comparatorIDLess(const WNode* s1, const WNode* s2);
    static bool comparatorIDMore(const WNode* s1, const WNode* s2);
    quint16 get_number_of_levels();
    quint16 get_level();
    inline QList<WNode*>::const_iterator get_begin()const{return _children.begin();}
    inline QList<WNode*>::const_iterator get_end()const{return _children.end();}
    inline WNode * childAt(int index){ return _children.at(index);}
    int getK(int start=0);
private:
    void* _data;
    unsigned int _id;
    QList<WNode*> _children;
    WNode * _parent;
    bool _sorted;
};

#endif
