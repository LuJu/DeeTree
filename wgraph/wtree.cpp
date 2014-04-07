///*
//Copyright (c) 2013, Lucas Juliéron
//All rights reserved.

//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:

//1. Redistributions of source code must retain the above copyright notice, this
//list of conditions and the following disclaimer.

//2. Redistributions in binary form must reproduce the above copyright notice,
//this list of conditions and the following disclaimer in the documentation
//and/or other materials provided with the distribution.

//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
//TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
//BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.
//*/
//#include "wtree.h"

//WTree::WTree():
//    _max_children_per_node(0),
//    _next_id(0),
//    _root(NULL),
//    _number_of_level_outdated(true),
//    _number_of_levels(0){
    
//}

////! Deletes all the nodes inside the tree
///*!
//    */
//WTree::~WTree(){
//    for (int i=0; i<this->size(); i++){
//        delete this->value(i);
//    }
//}

////! Adds a new node to a tree
///*!
//        Adds the node in parameter to the list in the tree. Sets the id of the node to the next id available.
//        If the root of the tree is undefined, sets the node in parameter as root of the tree
//        \n Status  1 : not implemented
//        \param  t : The node to be added
//    */
//void WTree::append(WNode *const&t){
//    QList::append(t);
//    if(_root==NULL) _root = t;
//    t->set_id(_next_id++);
//    _number_of_level_outdated=true;
//}


//quint16 WTree::addNode(void* t, int parentid){
//    WNode* node = new WNode(t);
//    WNode* parent=NULL;
//    append(node);
//    if (parentid>=0){
//        parent=get_node_by_id(parentid);
//        node->set_parent(parent);
//        parent->addToChildren(node);
//        if (node->get_number_of_children() > _max_children_per_node)
//            _max_children_per_node = node->get_number_of_children();
//    }
//    return node->get_id();
//}

//WNode * WTree::get_node_by_id(quint16 id){
//    WTree::iterator i;
//    for (i=begin();i!=end();i++){
//        if (((WNode*)*i)->get_id()==id) return *i;
//    }
//    return NULL;
//}

//quint16 WTree::get_number_of_levels(){
//    if (_root){
//        if (_number_of_level_outdated){
//            _number_of_levels=_root->get_number_of_levels();
//            _number_of_level_outdated=false;
//        }
//        return _number_of_levels;
//    }
//    else return 0;
//}

