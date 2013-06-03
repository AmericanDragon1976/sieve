/**************************************************************************
* Program:
*    Sieve of Eratosthenes
*    Private project, version 1.0
* Author:
*    Edward Moroni Goodson
* Summary:
*    This program uses the sieve of eratosthenes to create a linked list of
*   prime numbers. The program creates a linked list of numbers and then checks
*   each number aginst all primes already found by the sieve, up to the first
*   prime whoes square is larger than the number being checked. As a number is
*   eliminated from the list another is added to the end of the list, in the end
*   x primes will have been found where x is a preset number of primes. In this
*   version x will be set as a constant. (another version will take each prime
*   number through the list in order. As numbers are eliminated by the sieve
*   new numbers are added to the end of the list. Each new number is checked
*   against each know prime up to the largest whoes square does not exceed the n
*   new number only adding numbers not eliminated in the process. As each prime
*   reaches the end of the list the next number not eliminated by the sieve is
*   designated prime and the process starts again. I wish to know which is more
*   efficent.
****************************************************************************/
#include "sieve.h"

Number::Number()
{
   next = NULL;
}

void Number::setNumber(int theNumber)
{
   number = theNumber;
}

void Number::setNext(Number* nextNumber)
{
   next = nextNumber;
}

/*
 * Uses the Sieve of Eratosthenes to create a list of the first x prime numbers where x is a number entered by the user.
 */
int main ()
{
   Number* header = initilizeList (getInt("How many primes do you want? ", "Must enter an integer. Please try again."));
   Number* temp = header;

   applySieve(header);

   while (header != NULL)
   {
      cout << header->getNumber() << ", ";
      temp = header;
      header = header->getNext();
      delete temp;
   }

   return 0;
}

/*
 * Creates the starting list of numbers. Starting with 2
 */
Number* initilizeList(int listSize)
{
   Number* head = new Number;
   Number* current = head;
   int num = 2;

   current->setNumber(num++);
   current->setNext(new Number);
   current = current->getNext();

   for(int i = 2; i < listSize; i++)
   {
      current->setNumber(num);
      num += 2;
      current->setNext(new Number);
      current = current->getNext();
   }

   current->setNumber(num);

   return (head);
}

/*****************************************************************************
 * applys the sieve of eratosthenes to turn the list into a list of the first
 * 100 prime numbers.
 *****************************************************************************/
void applySieve(Number* headOfList)
{
   if (headOfList != NULL)
   {
      Number* listTail = headOfList;
      Number* currentNumber = headOfList->getNext();
      Number* previousNumber = headOfList;
      Number* currentPrime = headOfList;

      while (listTail->getNext() != NULL)
         listTail = listTail->getNext();

      while (currentNumber != NULL)
      {
         if ((currentNumber->getNumber() % currentPrime->getNumber()) == 0)
         {
            // point the end of the list at the current number
            listTail->setNext(currentNumber);
            // set number to 1 higher than current highest number
            currentNumber->setNumber(listTail->getNumber() + 1);
            // if we are not already at the end of the list
            // make the previous number point one further up the list removing
            // the node from this point in the list.
            if (listTail != previousNumber->getNext())
               previousNumber->setNext(currentNumber->getNext());
            // advance listTail to the new node at the list end
            listTail = listTail->getNext();
            // ensure the list terminates with a null pointer
            listTail->setNext(NULL);
            currentNumber = previousNumber->getNext();
            //reset current prime to beginning of known primes
            currentPrime = headOfList;
         } else
         {
            if ((currentPrime->getNumber() * currentPrime->getNumber()) > currentNumber->getNumber())
            {
               previousNumber = currentNumber;
               currentNumber = currentNumber->getNext();
               currentPrime = headOfList;
            } else
            {
               currentPrime = currentPrime->getNext();
            }
            }
         }
   } else
   {
      cout << "ERROR: NULL list passed into applySieve";
   }
}


int getInt (string prompt, string errorMsg);

/*********************************************************************
* Input: A string to promt the user for input
*        A string to be used as an error message if invalid data entered
* Output: An int entered by the user.
*********************************************************************/
int getInt (string desiredPrompt, string errorMsg)
{
   int tempInt;
   bool intObtained = false;

   cout << desiredPrompt;
   do
   {
      cin >> tempInt;
      if (cin.fail ())
      {
         cin.clear ();
         cin.ignore (1000, '\n');
         cout << errorMsg;
      }
      else
      {
         intObtained = true;
      }
   } while (intObtained == false);
   cin.ignore(80,'\n');
   return (tempInt);
}
