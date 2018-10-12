/*
 * Q 19.10 Write a method to generate a random number between 1 and 7,
 * given a method that generates a random number between 1 and 5(i.e.,implement rand7()using rand5()).
 */

#include <iostream>
using namespace std;

int Rand5(){
  int x = ~(1<<31); // max int
  while(x > 5)
      x = Rand7();
  return x;
}
int main()
{
    return 0;
}
