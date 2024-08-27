#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "fund.h"
#include "transaction.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
 public:
 //constructors
  Account();
  Account(int acc_id, string first_name, string last_name);

  //getters-setters
  string get_first_name() const;
  string get_last_name() const;
  int new_acc_id() const;
  string FundNameList(int id) const;

  bool Deposit(int fund_id, int val, char tran_type, int acc_id, int transfer_acc_id, int transfer_fund_id); 
  bool MakeDeposit(int fund_id, int val); 
  bool MakeTransfer(int fund_id, int transfer_account_id, int transfer_fund_id, int val); 
  bool AccWithdraw(int fund_id, int val, char transaction_type, int account_id, int transfer_account_id, int transfer_fund_id); 

  bool CheckLink(int fund_id) const; 
  int FundConnect(int fund_id) const; 
  int ConnectBalance(int fund_id) const; 

  bool TransFunds(int primary, int secondary, int val); 
  void AccountHistory();
  void AccountFundHistory(int fund_id);

  //operators 
  friend ostream &operator<<(ostream &o, const Account &other);
  
private:
  //data members
  string last_name_;
  string first_name_;
  int account_id_ = 0;
  Fund fund_[9];
  vector<Transaction> total_history_;
  string fund_names_[9];

const int kMoneyMarket_ = 0;
const int kPrimeMoneyMarket_ = 1;
const int kLongTermBond_ = 2;
const int kShortTermBond_ = 3;

};
#endif