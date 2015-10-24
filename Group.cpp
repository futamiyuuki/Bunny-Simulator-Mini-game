//
//  Group.cpp
//  PA4
//
//  Created by Hubert Hsiung on 11/13/14.
//  Copyright (c) 2014 Hubert Hsiung. All rights reserved.
//

#include "Group.h"

Group::Group() {}

void Group::addChild(Node* c) {
    child.push_back(c);
}

void Group::removeChild(Node* c) {
    child.remove(c);
}

void Group::draw(Matrix4& c) {
    for(list<Node*>::const_iterator iter = child.begin(); iter != child.end(); ++iter) {
        (*(*iter)).draw(c);
    }
}

void Group::removeAll() {
    for(list<Node*>::const_iterator iter = child.begin(); iter != child.end(); ++iter) {
        removeChild(*iter);
    }
}

void Group::update() {}

Group::~Group() {
    for(list<Node*>::const_iterator iter = child.begin(); iter != child.end(); ++iter) {
        delete *iter;
    }
}