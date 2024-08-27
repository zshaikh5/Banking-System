#include "account.h"
#include "bst.h"
#include "transaction.h"

#include <string>
#include <vector>

using namespace std;
Account::Account() {}

Account::Account(int account_id, string first_name, string last_name) 
{
  
  first_name_ = first_name;
  last_name_ = last_name;
  account_id_ = account_id;

  Transaction open_account('O', account_id, last_name, first_name, Transaction::kSuccess);
  total_history_.push_back(open_account);

  fund_names_[0] = "Money Market"; 
  fund_names_[1] = "Prime Money Market"; 
  fund_names_[2] = "Long-Term Bond"; 
  fund_names_[3] = "Short-Term Bond"; 
  fund_names_[4] = "500 Index Fund"; 
  fund_names_[5] = "Capital Value Fund"; 
  fund_names_[6] = "Growth Equity Fund"; 
  fund_names_[7] = "Growth Index Fund"; 
  fund_names_[8] = "International Fund"; 

  for (int i = 0; i < 9; i++) 
  {
    fund_[i].set_fund_name(fund_names_[i]);
  }

  fund_[0].Deposit(200);
  Transaction deposit_transaction('D', account_id, 0, 200, Transaction::kSuccess);
} 

string Account::get_first_name() const 
{ 
  return first_name_; 
}

string Account::get_last_name() const 
{ 
  return last_name_; 
}

int Account::new_acc_id() const 
{ 
  return account_id_; 
}

string Account::FundNameList(int id) const 
{ 
  return fund_names_[id]; 
} 

bool Account::Deposit(int fund_id, int val, char tran_type, int acc_id, int transfer_acc_id, int transfer_fund_id) 
{
  if(fund_id >= 9 || fund_id < 0)
  {
    cerr << "ERROR: Invalid Fund ID " << fund_id << " for Account " << acc_id << ". Deposit/Transfer failed." << endl;
    return false; 
  }

  if(tran_type == 'D')
    {
      return MakeDeposit(fund_id, val); 
    }
    else if (tran_type == 'T')
    {
      return MakeTransfer(fund_id, transfer_acc_id, transfer_fund_id, val);
    }
    else
    {
      cerr << "ERROR: Invalid transaction type " << tran_type << " deposit/transfer failed." << endl;
      return false;
    }
} 

bool Account::MakeDeposit(int fund_id, int val) 
{
  if (val < 0) {
    cerr << "ERROR: Cannot deposit a negative amount to " << FundNameList(fund_id) << " for " << first_name_ << " " << last_name_ << endl;
    return false;
  }

  fund_[fund_id].Deposit(val);
  Transaction deposit_transaction('D', account_id_, fund_id, val, Transaction::kSuccess);
  fund_[fund_id].FundTranHist(deposit_transaction);
  total_history_.push_back(deposit_transaction);
  return true;
} 

bool Account::MakeTransfer(int fund_id, int transfer_account_id, int transfer_fund_id, int val) 
{
  if(transfer_fund_id >= 9 || transfer_fund_id < 0)
  {
    cerr << "ERROR: Invalid transfer Fund ID " << transfer_fund_id << " for Account " << transfer_account_id << ". Transfer failed." << endl;
    return false; 
  }

  if (val < 0) 
  {
    cerr << "ERROR: Cannot transfer a negative amount from "  << FundNameList(fund_id)[fund_id] << " to " << FundNameList(transfer_fund_id)[transfer_fund_id] << " for Account " << account_id_ << endl;
    return false;
  }

  fund_[fund_id].Deposit(val);
  Transaction transfer_transaction('T', transfer_account_id, transfer_fund_id, account_id_, fund_id, val, Transaction::kSuccess);
  fund_[fund_id].FundTranHist(transfer_transaction);
  total_history_.push_back(transfer_transaction);
  return true;
} 

bool Account::AccWithdraw(int fund_id, int val, char transaction_type, int account_id, int transfer_account_id, int transfer_fund_id) 
{
  if (transaction_type != 'W' && transaction_type != 'T') 
  {
    cerr << "ERROR: Invalid transaction type: " << transaction_type << endl;
    return false;
  }
  if(fund_id >= 9 || fund_id < 0)
  {
     cerr << "ERROR: Cannot withdraw/transfer " << val << " from account: " << account_id << " fund: " << fund_id << endl;
    return false; 
  }
  if (transaction_type == 'W') 
  {
    if ((val >= 0) && (val <= fund_[fund_id].get_balance())) 
    {
      Transaction withdraw_transaction('W', account_id_, fund_id, val, Transaction::kSuccess);
      fund_[fund_id].Withdraw(val);
      fund_[fund_id].FundTranHist(withdraw_transaction);
      total_history_.push_back(withdraw_transaction);
      return true;
    }

    else if (CheckLink(fund_id) && (val >= 0) && (val <= ConnectBalance(fund_id))) 
    {
      return TransFunds(fund_id, FundConnect(fund_id), val);
    }
    else 
    {
      if(val < 0)
      {
        cerr << "ERROR: NOT ALLOWED - negative withdraw of $ " << val << " from " << first_name_ << " " << last_name_ << " " << FundNameList(fund_id) << endl;   
      }
      else
      {
        cerr << "ERROR: Not enough funds to withdraw " << val << " from " << first_name_ << " " << last_name_ << " " << FundNameList(fund_id) << endl;
      }

      Transaction withdraw_transaction('W', account_id_, fund_id, val, Transaction::kFailed);
      fund_[fund_id].FundTranHist(withdraw_transaction);
      total_history_.push_back(withdraw_transaction);
      return false;
    }
  }
  else 
  {
    if (transfer_fund_id >= 9 || transfer_fund_id < 0) 
    {
      cerr << "ERROR: Transfer failed - Invalid transfer fund ID: " << transfer_fund_id << endl;
      return false;
    }
    if (transaction_type == 'T') 
    {
        if ((val >= 0) && (val <= fund_[fund_id].get_balance())) 
        {
        Transaction transfer_transaction('T', account_id_, fund_id, transfer_account_id, transfer_fund_id, val, Transaction::kSuccess);
        fund_[fund_id].Withdraw(val);
        fund_[fund_id].FundTranHist(transfer_transaction);
        total_history_.push_back(transfer_transaction);
        return true;
        }

      else if (CheckLink(fund_id) && (val >= 0) && (val <= ConnectBalance(fund_id))) 
      {
        return TransFunds(fund_id, FundConnect(fund_id), val);
      }
      else 
      {
        cerr << "ERROR: Unable to transfer " << val << " from Account: " << account_id_ << " " << FundNameList(fund_id) << " to Account: " << transfer_account_id << " " << FundNameList(transfer_fund_id) << endl;
        Transaction transfer_transaction('T', account_id_, fund_id, transfer_account_id, transfer_fund_id, val, Transaction::kFailed);
        fund_[fund_id].FundTranHist(transfer_transaction);
        total_history_.push_back(transfer_transaction);
        return false;
      }
    }
  } 
  return false; 
}

bool Account::CheckLink(int fund_id) const 
{
  return (fund_id == kMoneyMarket_ && FundConnect(fund_id) == kPrimeMoneyMarket_) || 
        (fund_id == kPrimeMoneyMarket_ && FundConnect(fund_id) == kMoneyMarket_) ||
         (fund_id == kLongTermBond_ && FundConnect(fund_id) == kShortTermBond_) || 
         (fund_id == kShortTermBond_ && FundConnect(fund_id) == kLongTermBond_);
}

int Account::FundConnect(int fund_id) const 
{
  if (fund_id == kMoneyMarket_) 
  {
    return kPrimeMoneyMarket_;
  } else if (fund_id == kPrimeMoneyMarket_) 
  {
    return kMoneyMarket_;
  } else if (fund_id == kLongTermBond_) 
  {
    return kShortTermBond_;
  } else if (fund_id == kShortTermBond_) 
  {
    return kLongTermBond_;
  } else 
  {
    return -1;
  }
}
 
int Account::ConnectBalance(int fund_id) const 
{
  return fund_[fund_id].get_balance() + fund_[FundConnect(fund_id)].get_balance();
} 

bool Account::TransFunds(int primary, int secondary, int val) 
{
  int primary_balance = fund_[primary].get_balance();

  Transaction withdraw_transaction1('W', account_id_, primary, min(val, primary_balance), Transaction::kSuccess);
  total_history_.push_back(withdraw_transaction1);
  fund_[primary].Withdraw(min(val, primary_balance));
  fund_[primary].FundTranHist(withdraw_transaction1);

  if (val > primary_balance) 
  {
    int remaining_amount = val - primary_balance;

    Transaction withdraw_transaction2('W', account_id_, secondary, remaining_amount, Transaction::kSuccess);
    total_history_.push_back(withdraw_transaction2);
    fund_[secondary].Withdraw(remaining_amount);
    fund_[secondary].FundTranHist(withdraw_transaction2);
  }
  return true;
}

void Account::AccountHistory() 
{
cout << "\nTransaction History for Account: " << account_id_  << ", Holder " << first_name_ << " " << last_name_  <<  " by fund." << endl;

  for (int i = 0; i < 9; i++) 
  {
    fund_[i].FinalFundHist();
  }

}

void Account::AccountFundHistory(int fund_id) 
{
  if(fund_id >= 9 || fund_id < 0)
  {
    cerr << "ERROR: Cannot Print Transactions by fund. Fund ID cannot be " << fund_id << endl;

  } 
  else 
  {
    cout << "\nTransaction History for " << first_name_ << " " << last_name_ << " " << fund_[fund_id].get_name() << ": $" << fund_[fund_id].get_balance() << endl;
    for (Transaction transaction : fund_[fund_id].get_tran()) 
    {
      cout << " " << transaction;
    }
  }
}

ostream &operator<<(ostream &o, const Account &other) 
{
  cout << other.get_first_name() << " " << other.get_last_name() << " Account ID: " << other.new_acc_id() << endl;

  for (int i = 0; i < 9; i++) 
  {
    cout << "    " << other.fund_[i].get_name() << ": " << "$" << other.fund_[i].get_balance() << endl;
  }
  
  return cout;
}



