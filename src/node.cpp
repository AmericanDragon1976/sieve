#include "node.h"

/************************************************************************
* Constructors for Node class
************************************************************************/
Node::Node(unsigned long long nData, Node* nxtPtr, Node* prePtr)
{
   data = nData; 
   next = nxtPtr;
   previous = prePtr;
}
