
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*
 * Class Name: Number
 * Summary: This class holds a number, a pointer to the next number.
 */
class Number
{
   public:
      Number();
      void setNumber(int theNumber);
      void setNext(Number* nextNumber);
      int getNumber() {return number;}
      Number* getNext() {return next;}

   private:
      int number;
      Number* next;
};

Number* initilizeList(int listSize);
void applySieve(Number* headOfList);
int getInt (string desiredPrompt, string errorMsg);
