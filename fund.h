#ifndef FUND_H_
#define FUND_H_

#include "transaction.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Fund {
public:
  //constructor
  Fund();
  Fund(string name);

  //getter-setters
  string get_name() const;
  int get_balance() const;
  void set_fund_name(string name); 
  vector<Transaction> get_tran(); 
  
  bool Deposit(int amount);
  bool Withdraw(int amount);
  bool FundTranHist(Transaction other); 
  void FundHistory();
  void FinalFundHist(); 

private:
  //data members
  string name_;
  int balance_ = 0;
  vector<Transaction> t_trans_;
};
#endif
