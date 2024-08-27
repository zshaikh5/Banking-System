#include "bank.h"
#include <iostream>

int main(int argc, char *argv[]) 
{
  if(argc != 2)
  {
    cout << "Please enter 1 argument.";
    return -1;
  }

  Bank jolly_banker;
  jolly_banker.ReadTrans(argv[1]);
  jolly_banker.Transactions();
  jolly_banker.PrintTrans();
  
  return 0;
}

