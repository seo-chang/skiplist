//
// Created by <Name> on <Date>.
//

#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream& operator<<(ostream& out, const SkipList& skipList) { return out; }

SkipList::SNode::SNode(int data) {}

SkipList::SkipList(int depth) {}

bool SkipList::alsoHigher() const { return false; }

bool SkipList::add(int data) { return true; }

void SkipList::addBefore(SNode* newNode, SNode* nextNode) {}

SkipList::~SkipList() {
    // need to delete individual nodes
}

bool SkipList::remove(int data) { return false; }

bool SkipList::contains(int data) { return false; }
