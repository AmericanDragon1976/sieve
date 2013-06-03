#include "listNum.h"
#include "node.h"


/************************************************************************
* Destructor for List class
************************************************************************/
ListNum::~ListNum()
{
   Node* nextNode = firstNode;
   
   while (nextNode != NULL)
   {
      nextNode = nextNode->getNext();
      delete firstNode;
      firstNode = nextNode;
   }
}

/************************************************************************
* Copy Constructor for List class
************************************************************************/
ListNum::ListNum(const ListNum &listToCopy)
{
   Node* currentNode = listToCopy.firstNode;
   Node* copyNode;
   Node* newNodePrev;
   
   numItems = listToCopy.numItems;
   if (numItems == 0)
   {
      firstNode = NULL;
      lastNode = NULL;
   }
   else 
   {
      firstNode = new Node(currentNode->getData());
      lastNode = firstNode;
      currentNode = currentNode->getNext();
      while (currentNode != NULL)
      {
         lastNode->setNext(new Node(currentNode->getData()));
         newNodePrev = lastNode;
         lastNode = lastNode->getNext();
         lastNode->setPrevious(newNodePrev);
         currentNode = currentNode->getNext();
      }
   }
}

/***********************************************************************
 * Overloaded assignment operator for list class.
 ***********************************************************************/
ListNum& ListNum::operator = (const ListNum &rightSide)
{ 
   if (this != &rightSide)
   {
   
      Node* tempPtr = firstNode;
      while (firstNode != NULL)
      { 
         tempPtr = firstNode->getNext();
         delete firstNode;
         firstNode = tempPtr;
      }
      tempPtr = rightSide.firstNode;
      if (tempPtr != NULL)
      { 
         firstNode = new Node(tempPtr->getData());
         tempPtr = tempPtr->getNext();
      }
      Node* prevThisList = firstNode;
      while (tempPtr != NULL)
      { 
         lastNode->setNext(new Node (tempPtr->getData())); 
         lastNode = lastNode->getNext();
         lastNode->setPrevious(prevThisList);
         prevThisList = lastNode;
         tempPtr = tempPtr->getNext();
      }
      numItems = rightSide.numItems;
   }
   return *this;
}

/***********************************************************************
 * Manipulator to add an integeter to the list of integers at a specific 
 * position. if the specified position is beyond the end of the list, the
 * item is inserted at the end of the list
 ***********************************************************************/
void ListNum::insert(unsigned long long item, int pos)
{ 
   Node* currentNode = firstNode;
   Node* nextNode;
   
   if ((pos <= 0) || (numItems == 0))
   {
      firstNode = new Node(item, firstNode);
      if (firstNode->getNext() != NULL)
         firstNode->getNext()->setPrevious(firstNode);
      else
         lastNode = firstNode;
   }
   else 
   {
      while ((currentNode->getNext() != NULL) && (--pos != 0))
         currentNode = currentNode->getNext();
      nextNode = currentNode->getNext();
      currentNode->setNext(new Node(item, nextNode, currentNode));
      currentNode = currentNode->getNext();
      if (nextNode != NULL)
         nextNode->setPrevious(currentNode);
      else 
         lastNode = currentNode;
      
   }
   numItems++;
}

/***********************************************************************
 * Manipulator to remove an integeter to the list of integers at a specific 
 * position. if the specified position is beyond the end of the list, then
 * nothing is removed.
 ***********************************************************************/
void ListNum::remove(int pos)
{ 
   if (firstNode != NULL)
   { 
      Node* tempPtr = firstNode;

      if (pos == 0)
      { 
         firstNode = tempPtr->getNext(); 
         delete tempPtr; 
         tempPtr = NULL; 
         if (firstNode != NULL)
            firstNode->setPrevious(tempPtr); 
         numItems--; 
      } else
      {         
         while ((tempPtr->getNext() != NULL) && (pos-- != 0))
            tempPtr = tempPtr->getNext();
            
         if (tempPtr->getNext() == NULL)
            lastNode = tempPtr->getPrevious();

         tempPtr->getPrevious()->setNext(tempPtr->getNext());
         if (tempPtr->getNext() != NULL)
            tempPtr->getNext()->setPrevious(tempPtr->getPrevious());
         delete tempPtr;
         numItems--; 
      }
   }
}

/***********************************************************************
 * finds item in the list and returns its position, if not found returns -1
 ***********************************************************************/
int ListNum::lookup(unsigned long long item) const
{
   int pos = 0;
   Node* current = firstNode;
   
   while (current != NULL)
   {
      if (current->getData() == item)
         return pos;
      pos++;
      current = current->getNext();
   }
   return -1;
}

/***********************************************************************
 * INPUT: the list makes up a number, first node has the low order digits,  
 * the second node has next lowest etc. 
 * OUTPUT: The number stored in the as been multiplied by two and stored back
 * in the same linked list.
 ***********************************************************************/
void ListNum::doubleNum()
{
   Node* current = firstNode;
//   Node* nlPtr = NULL; 
   unsigned long long carry = 0;
   unsigned long long dbldNum;
   
   while (current != NULL)
   {
      dbldNum = ((current->getData() * 2) + carry) % 1000000000;
      carry = ((current->getData() * 2) + carry) / 1000000000; 
      current->setData(dbldNum);
      if ((current->getNext() == NULL) && (carry > 0))
      { 
         current->setNext(new Node(carry, NULL, current));
         current->getNext()->setPrevious(current);
         current = current->getNext();
         lastNode = current; 
         numItems++;
      }
      current = current->getNext(); 
   }
}

/***********************************************************************
 * INPUT: the list makes up a number, first node has the low order digits,  
 * the second node has next lowest etc. 
 * OUTPUT: print the number to screen high order digits first. the lastNode
 * does not have leading zeros output to the screen, all others do. 
 ***********************************************************************/
void ListNum::outputNum()
{
   Node* tempPtr = lastNode;
   
   while (tempPtr != NULL)
   {
      if (tempPtr->getNext() == NULL)
         cout << setfill(' ') << setw(1) << tempPtr->getData();
      else
         cout << setfill('0') << setw(9) << tempPtr->getData();
      tempPtr = tempPtr->getPrevious();
   }
}

/***********************************************************************
 * INPUT: the list makes up a number, first node has the low order digits,  
 * the second node has next lowest etc. an unsigned long long that will bc
 * compared with the number to see if it is a sufix of the number.
 * OUTPUT: print the number to screen high order digits first. the lastNode
 * does not have leading zeros output to the screen, all others do. 
 ***********************************************************************/
bool ListNum::comparePrefix(unsigned long long inputNum)
{
   string inputDigits;
   string powerDigits;
   stringstream strm;
   stringstream strmTwo;
   bool match = true;
   
   strm << inputNum;
   inputDigits = strm.str(); 
   strmTwo << lastNode->getData();
   powerDigits = strmTwo.str(); 
   if (firstNode != lastNode)
   {
      strmTwo.str("");
      strmTwo << lastNode->getPrevious()->getData();
      
      for (int count = strmTwo.str().length(); count < 9; count++)
         powerDigits = powerDigits + "0";
      for (int i = 0; i < strmTwo.str().length(); i++)
         powerDigits = powerDigits + strmTwo.str()[i];
   }
   
   for (int i = 0; i < inputDigits.length(); i++)
   { 
      if (inputDigits.length() > powerDigits.length())
      {
         match = false;
         break;
      }
      if (inputDigits[i] != powerDigits[i])
      { 
         match = false;
         break;
      }
   } 
   return match;
}

/***********************************************************************
 * returns the first strLen digits of the number as a string, if the number 
 * doesn't have strLen digits the entire number is returned as a string. 
 ***********************************************************************/
int ListNum::getPrefix(int strLen)
{
   string powerDigits;
   int intPowerDigits = 0;
   stringstream strm;
   
   strm << lastNode->getData();
   powerDigits = strm.str();
   
   if (firstNode != lastNode)
   {
      strm.str("");
      strm << lastNode->getPrevious()->getData();
      
      for (int count = strm.str().length(); count < 9; count++)
         powerDigits = powerDigits + "0";
      for (int i = 0; i < strm.str().length(); i++)
         powerDigits = powerDigits + strm.str()[i];
   }
   
   if (strLen < powerDigits.length())
      powerDigits.erase(strLen);
   
   for (int i = 0; i < powerDigits.length(); i++)
   {
      intPowerDigits = intPowerDigits * 10;
      switch (powerDigits[i])
      {
         case '0':
            intPowerDigits += 0;
            break;
         case '1':
            intPowerDigits += 1;
            break;
         case '2':
            intPowerDigits += 2;
            break;
         case '3':
            intPowerDigits += 3;
            break;
         case '4':
            intPowerDigits += 4;
            break;
         case '5':
            intPowerDigits += 5;
            break;
         case '6':
            intPowerDigits += 6;
            break;
         case '7':
            intPowerDigits += 7;
            break;
         case '8':
            intPowerDigits += 8;
            break;
         case '9':
            intPowerDigits += 9;
            break;
         default:
            cout << "Error not a number" ;
            exit(1);
            break;
      }
   }
   
   return intPowerDigits;
}

/***********************************************************************
 * finds a specific position in the list and returns the data at that position
 * if the position is beyond the end of the list it returns garbage. 
 ***********************************************************************/
unsigned long long ListNum::getData(int pos) const
{
   unsigned long long dataItem;
   Node* current = firstNode;
   int position = 0;
   
   while ((current != NULL) && (position != pos))
   {
      current = current->getNext(); 
      if (current != NULL)
         position++; 
   }
   if (position == pos)
      dataItem = current->getData();
   return dataItem;
}

/***********************************************************************
 * sets the first node pointer, used to swap entire lists
 ***********************************************************************/
void ListNum::setFirstNode(Node* nwFrstNode, int numIte)
{
   Node* current = nwFrstNode;
   firstNode = nwFrstNode;
   
   numItems = numIte;
}
