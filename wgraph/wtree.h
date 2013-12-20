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
#ifndef WTREE_H
#define WTREE_H

//#include <iostream>
#include <QStringList>
#include "wnode.h"

class WTree : public QList<WNode*>
{
public:

    WTree();
    ~WTree();
    inline quint16 get_next_id(){return _next_id;}
    //! Returns the number of levels of the tree
    /*!
        \n Status  1 : not implemented
        \return The number of levels
    */
    quint16 get_number_of_levels();
    virtual void append(WNode *const&t);
    //! Add the type t in the tree
    /*!
            \n Status  1 : not implemented
            \param  t : an object of the class of the tree
            \param  parentid : the id of the node parent of the object given in parameter
            \return the id of the newly created node
        */
    quint16 addNode(void* t=NULL, int parentid=-1);
    inline WNode * get_root()const{
        return _root;
    }
    void buildTest();

    WNode *get_node_by_id(quint16 id);
    
    //! Returns the maximum number of children a node has in the tree
    int get_max_children_per_node() const {return _max_children_per_node;}

private:
    void recursiveBuilding(QString folder, quint16 id);
    quint16 _next_id;
    WNode * _root;

    bool _number_of_level_outdated;
    quint16 _number_of_levels;
    
    int _max_children_per_node;
};

#endif // WTREE_H
