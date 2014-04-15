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

//! This class represents a tree containing nodes. A tree is a non-cyclic graph
//! where each node can have zero or more children
template <class T>
class WTree : public QList<WNode<T> *>
{
public:

    WTree();
    ~WTree();
    inline int get_next_id(){return _next_id;}
    //! Returns the number of levels of the tree
    /*!
        \n Status  1 : not implemented
        \return The number of levels
    */
    int get_number_of_levels() const;
    virtual void append(WNode<T> *const&t);
    //! Add the type t in the tree
    /*!
        \n Status  1 : not implemented
        \param  t : an object of the class of the tree
        \param  parentid : the id of the node parent of the object given in parameter
        \return the id of the newly created node
    */
    int addNode(T* t=NULL, int parentid=-1);
    //! Returns the root of the tree
    /*!
        The root of the tree is the first node and does not have parent.
        \n Status  1 : not implemented
        \return The root or NULL if the tree has no root yet
    */
    inline WNode<T> * get_root()const{ return _root; }

    WNode<T> *get_node_by_id(int id);
    
    //! Returns the maximum number of children a node has in the tree
    int get_max_children_per_node() const {return _max_children_per_node;}

private:
    unsigned int _next_id;
    WNode<T> * _root;

    mutable bool _number_of_level_outdated;
    mutable int _number_of_levels;
    
    int _max_children_per_node;
};

template<class T>
WTree<T>::WTree():
    _max_children_per_node(0),
    _next_id(0),
    _root(NULL),
    _number_of_level_outdated(true),
    _number_of_levels(0){

}

//! Deletes all the nodes inside the tree
/*!
    */
template<class T>
WTree<T>::~WTree(){
    for (int i=0; i<this->size(); i++){
        delete this->value(i);
    }
}

//! Adds a new node to a tree
/*!
        Adds the node in parameter to the list in the tree. Sets the id of the node to the next id available.
        If the root of the tree is undefined, sets the node in parameter as root of the tree
        \n Status  1 : not implemented
        \param  t : The node to be added
    */
template<class T>
void WTree<T>::append(WNode<T> *const&t){
    QList<WNode<T>*>::append(t);
    if(_root==NULL) _root = t;
    t->set_id(_next_id++);
    _number_of_level_outdated=true;
}

template<class T>
int WTree<T>::addNode(T *t, int parentid){
    WNode<T>* node = new WNode<T>(t);
    WNode<T>* parent=NULL;
    append(node);
    if (parentid>=0){
        parent=get_node_by_id(parentid);
        node->set_parent(parent);
        parent->addToChildren(node);
        if (node->get_number_of_children() > _max_children_per_node)
            _max_children_per_node = node->get_number_of_children();
    }
    return node->get_id();
}

template<class T>
WNode<T> * WTree<T>::get_node_by_id(int id){
    typename WTree<T>::iterator i;
    for (i=this->begin();i!=this->end();i++){
        if (((WNode<T>*)*i)->get_id()==id) return *i;
    }
    return NULL;
}

template<class T>
int WTree<T>::get_number_of_levels() const{
    if (_root){
        if (_number_of_level_outdated){
            _number_of_levels=_root->get_number_of_levels();
            _number_of_level_outdated=false;
        }
        return _number_of_levels;
    }
    else return 0;
}





#endif // WTREE_H
