#ifndef BANK_H_
#define BANK_H_

#include "account.h"
#include "bst.h"
#include "transaction.h"

#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Bank {
public:
  //constructors
  Bank();

  //functions
  bool ReadTrans(const string& file_name); 
  void ReadMainTrans(char transaction_type, istringstream& parseLine); 
  void Transactions(); 
  void Deposit(const Transaction& process, int account_id); 
  void OpenAcc(const Transaction& process, int account_id); 
  void Transfer(const Transaction& process, int account_id); 
  void ExeAccHistory(const Transaction& process, int account_id); 
  void Withdrawal(const Transaction& process, int account_id); 
  void ExeFundHistory(const Transaction& process, int account_id); 
  void PrintTrans(); 

private:
  //data members
  BSTree tree_accounts_;
  queue<Transaction> queue_trans_;
};

#endif