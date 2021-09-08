//
// Created by Robin Seo on 18 FEB 2020.
//
#include "skiplist.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>


using namespace std;
// To display all the elements of SkipList
ostream& operator<<(ostream& out, const SkipList& skipList) {
    for (int i = skipList.depth-1 ; i >= 0; i--) {
        SkipList::SNode* curr = skipList.frontGuards[i];
        out << "Level: " << i << " -- ";
        while (curr != nullptr) {
            out << curr->Data << ", ";
            curr = curr->Next;
        }
        out << endl;
    }
    return out;
}

// Constructor to set all the data, set all other ptr to nullptr
SkipList::SNode::SNode(int Data): Data(Data), Next(nullptr), Prev(nullptr),
                                  UpLevel(nullptr), DownLevel(nullptr){}

// Dynamically allocate frontGuards and rearGuards arrays and use SNode objects
// to tie all the SNode together (NSEW) directions
SkipList::SkipList(int depth): depth(depth){
    frontGuards = new SNode*[depth];
    rearGuards = new SNode*[depth];
    for (int i = 0; i < depth; i++) {
        frontGuards[i] = new SNode(INT_MIN);
        rearGuards[i] = new SNode(INT_MAX-1);
        frontGuards[i]->Next = rearGuards[i];
        rearGuards[i]->Prev = frontGuards[i];
        frontGuards[i]->Data = INT_MIN;
        rearGuards[i]->Data = INT_MAX;
        if (i >= 1) {
            frontGuards[i]->DownLevel  = frontGuards[i-1];
            rearGuards[i]->DownLevel = rearGuards[i-1];
            frontGuards[i-1]->UpLevel = frontGuards[i];
            rearGuards[i-1]->UpLevel = rearGuards[i];
        }
    }
}
// flip a coin (50% chance)
bool SkipList::alsoHigher() const {
    auto randNum = rand() % 2;
    return randNum == 1;
}

// return false if the given value is already in level-0
// else, insert node at the right place
// flip the coin to insert the node to the upper level
bool SkipList::add(int Data) {
    SNode* nextNode = frontGuards[0];
    auto* newNode = new SNode(Data);
    if (nextNode->Next == rearGuards[0]) {
        addBefore(newNode, nextNode->Next);
    } else {
        while (nextNode->Next != nullptr &&
               nextNode->Next->Data <= newNode->Data) {
            nextNode = nextNode->Next;
            if (nextNode->Data == Data){
                delete newNode;
                return false;
            }
        }
        addBefore(newNode, nextNode->Next);
    }

    int level = 1;
    while (alsoHigher() && level < depth){

        auto *newUpper = new SNode(Data);
        // connect newNode and newUpper (up-down)
        newNode->UpLevel = newUpper;
        newUpper->DownLevel = newNode;

        // starting from newNode, keep going back towards INT_MIN until you find
        // a node that has a valid up level link
        //nextNode = nextNode->Prev;
        while(nextNode->UpLevel == nullptr){
            nextNode = nextNode->Prev;
        }

        // go up one level
        nextNode = nextNode->UpLevel;
        level++;

        //go right towards INT_MAX
        addBefore(newUpper, nextNode->Next);
        newNode = newUpper;
    }
    return true;

}
// connects the newNode to nextNode
void SkipList::addBefore(SNode* newNode, SNode* nextNode) {
    assert(nextNode != nullptr && nextNode->Prev != nullptr);
    newNode->Prev = nextNode->Prev;
    newNode->Prev->Next = newNode;
    nextNode->Prev = newNode;
    newNode->Next = nextNode;
}


// need to delete individual nodes
SkipList::~SkipList() {
    for (int i = depth - 1; i >= 0; i--) {
        auto *curr = frontGuards[i]->Next;
        while (curr != nullptr){
            delete curr->Prev;
            curr = curr->Next;
        }
        delete rearGuards[i];
    }
    delete[] frontGuards;
    delete[] rearGuards;
}

// if data contains in SkipList then delete all the nodes that contains Data
bool SkipList::remove(int Data) {
    auto* curr = frontGuards[depth - 1];
    if (!contains(Data) || Data == INT_MAX || Data == INT_MIN) {
        return false;
    }
    while (curr != nullptr) {
        if (curr->Next->Data <= Data) {
            curr = curr->Next;
        }
        else {
            curr = curr->DownLevel;
        }
        // if we find a node then move down delete nodes.
        assert(curr != nullptr);
        if (curr->Data == Data) {
            while (curr->DownLevel != nullptr) {
                curr->Prev->Next = curr->Next;
                curr->Next->Prev = curr->Prev;
                curr = curr->DownLevel;
                delete curr->UpLevel;
                curr->UpLevel = nullptr;
            }
            if (curr->Data == Data && curr->DownLevel == nullptr) {
                curr->Prev->Next = curr->Next;
                curr->Next->Prev = curr->Prev;
                delete curr;
                curr = nullptr;
            }
        }
    }
    return true;
}

// check if we have data inside of SkipList.
// Started from top left and find a node
bool SkipList::contains(int Data) {
    auto *curr = frontGuards[depth-1];
    while (curr != nullptr ) {
        // move to next pointer
        if (curr->Next->Data <= Data) {
            curr = curr->Next;
        }

        if (curr->Data == Data) {
            return true;
        }
        // if Data < pointer->Next, move down
        if (curr->Next->Data > Data) {
            curr = curr->DownLevel;
        }
    }
    return false;
}

