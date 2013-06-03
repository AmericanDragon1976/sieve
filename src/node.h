// -- Node for a doubly linked list of int.s all functions inliine
#ifndef _NODE_H
#define _NODE_H

#include <cstdlib>
using namespace std;

class Node
{
   private:
     unsigned long long data;                 // -- data in each node
     Node* next;               // -- pointer to next node
     Node* previous;           // -- pointer to the previous node

   public:
     Node(unsigned long long nData = 0, Node* nxtPtr = NULL, Node* prePtr = NULL); // --- Creates New node
     Node* getNext(){return next;};         // -- returns next pointer of a node
     Node* getPrevious(){return previous;};// -- returns previous pointer of node
     unsigned long long getData(){return data;};                   // -- returns data of a node
     void setData(unsigned long long item){data = item;};  // -- stores item in data member node
     void setNext(Node* node) {next = node;};            // -- sets next to node
     void setPrevious (Node* node) {previous = node;}; // -- sets previouse node
};

#endif
