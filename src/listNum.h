// -- Class using the doubly linked node defined in node.h and node.cpp to create 
// -- a containter for very large numbers and allow the operations on that number 
// -- nessary for the Power 2 Prefix project
#ifndef _LISTNUM_H
#define _LISTNUM_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "node.h"
using namespace std;

class ListNum
{
   private:
      int numItems;
      Node* firstNode;
      Node* lastNode;
  
   public:
      // -- constructors and destructor
      ListNum() {numItems = 0; firstNode = NULL; lastNode = NULL;};
      ~ListNum();
      ListNum(const ListNum &listToCopy);   // copy constructor
      
      // -- operators
      ListNum& operator = (const ListNum &rightSide);
      
      //-- operations
      void insert(unsigned long long item, int pos);
      void remove(int pos);
      int lookup(unsigned long long item) const; 
      void doubleNum();
      void outputNum();
      bool comparePrefix(unsigned long long inputNum);
      int getPrefix(int strLen);
      
      // -- getters
      unsigned long long getData(int pos) const;
      unsigned long long getNumItems(void) {return numItems;};
      Node* getFirstNode() {return firstNode;};
      
      // -- setters
      void setFirstNode(Node* nwFrstNode, int newNumItems);
};

#endif
