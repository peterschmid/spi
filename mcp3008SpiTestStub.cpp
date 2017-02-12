#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

/**
 * Main program to generate random numbers between 0 and 1023
 */
int main ()
{
  auto number = 0;

  /* initialize random seed: */
  srand (time(NULL));

  /* generate secret number between 1 and 10: */
  number = rand() % 1023;

  std::cout << number << std::endl;

  return 0;
}
