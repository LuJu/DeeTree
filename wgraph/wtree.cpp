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
#include "wtree.h"

WTree::WTree():
    _max_children_per_node(0),
    _next_id(0),
    _root(NULL),
    _number_of_level_outdated(true),
    _number_of_levels(0){
    
}

//! Deletes all the nodes inside the tree
/*!
    */
WTree::~WTree(){
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
void WTree::append(WNode *const&t){
    QList::append(t);
    if(_root==NULL) _root = t;
    t->set_id(_next_id++);
    _number_of_level_outdated=true;
}


quint16 WTree::addNode(void* t, int parentid){
    WNode* node = new WNode(t);
    WNode* parent=NULL;
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

WNode * WTree::get_node_by_id(quint16 id){
    WTree::iterator i;
    for (i=begin();i!=end();i++){
        if (((WNode*)*i)->get_id()==id) return *i;
    }
    return NULL;
}

quint16 WTree::get_number_of_levels(){
    if (_root){
        if (_number_of_level_outdated){
            _number_of_levels=_root->get_number_of_levels();
            _number_of_level_outdated=false;
        }
        return _number_of_levels;
    }
    else return 0;
}

void WTree::buildTest(){

    quint16 rootid=addNode(new QString("Root"));
    recursiveBuilding("/home/batman/Programmation/Windel/TEST",rootid);
//    recursiveBuilding("~",rootid);
    qDebug()<<"Building complete"<<endl;
}

void WTree::recursiveBuilding(QString folder, quint16 id){
    FILE *fp;
    int status;
    quint16 nodeid;
    char path[PATH_MAX];
    QString command = QString("ls -l "+folder);
    fp = popen(command.toStdString().c_str(), "r");
//    fp = popen("ls -lR | tail -n +2 | awk '{print $1"|"$9}'", "r");
    if (fp == NULL)
        qDebug()<<"problem opening file"<<endl;

//    while (fgets(path, PATH_MAX, fp) != NULL){
//        QString s(path);
//        if (s.at(0)!='t'){
//            FileType * file=new FileType(FileType::text);
//            QStringList list = s.split(" ",QString::SkipEmptyParts);
//            QString name = list[8];
//            int i;
//            for(i=9;i<list.size();i++){
//                name=name+" "+list[i];
//            }
//            name=name.remove("\n");

//            int size= list.at(4).toInt();
//            QString filepath= folder;


//            file->set_name(name);
//            file->set_size(size);
//            file->set_path(filepath);
//            if(s.at(0)=='d'){
//                file->set_type(FileType::folder);
//            } else {
//                file->set_type(FileType::text);
//            }
//            nodeid=addNode(new QString(name),id);
//            if(s.at(0)=='d')
//                recursiveBuilding(folder+"/"+name+"/",nodeid);
//        }
//    }
    status = pclose(fp);
    if (status == -1) {
        /* Error reported by pclose() */
   } else {
        /* Use macros described under wait() to inspect `status' in order
          to determine success/failure of command executed by popen() */
    }
}
