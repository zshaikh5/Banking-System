#include "fund.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Fund::Fund(){}

Fund::Fund(string name) 
{
  name_ = name;
}

string Fund::get_name() const 
{ 
  return name_; 
}

int Fund::get_balance() const 
{ 
  return balance_; 
}

vector<Transaction> Fund::get_tran() 
{ 
  return t_trans_; 
}

bool Fund::Deposit(int amount) 
{
  if(amount < 0)
  {
    return false;
  }

  balance_ += amount;
  return true;
}

bool Fund::Withdraw(int amount) 
{
  if (amount < 0 || amount > balance_) 
  {
    return false;
  }
  balance_ -= amount;
  return true;
}

bool Fund::FundTranHist(Transaction other) 
{
  t_trans_.push_back(other);
  return true;
}

void Fund::FundHistory() 
{
  for (const Transaction &tran : t_trans_)
   {
    cout << " " << tran;
  }
}

void Fund::FinalFundHist() 
{
  if (!t_trans_.empty()) 
  {
    cout << get_name() << ": $" << get_balance() << endl;
    for (const Transaction &transaction : t_trans_) 
    {
      cout << " " << transaction;
    }
  }
}

void Fund::set_fund_name(string name) {
    name_ = name;
}