/* rand example: guess the number */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

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
