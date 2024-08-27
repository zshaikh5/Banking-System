#include "bank.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

Bank::Bank() {}

bool Bank::ReadTrans(const string& file) {
  ifstream file_name(file);
  if (!file_name.is_open()) 
  {
    cerr << "The file cannot be opened: " << file << endl;
    return false;
  }

  string line;
  while (getline(file_name, line)) 
  {
    if (line.empty()) 
    {
      break;  
    }
    istringstream read(line);

    char trans_type;
    read >> trans_type;

    ReadMainTrans(trans_type, read); 

  }
  return true;
}

void Bank::ReadMainTrans(char trans_type, istringstream &read) 
{
  if (trans_type == 'O') 
  {
    int account_id;
    string last_name;
    string first_name;

    read >> account_id >> last_name >> first_name;

    Transaction t(trans_type, account_id, last_name, first_name, Transaction::kSuccess);
    queue_trans_.push(t);
  } 
  else if (trans_type == 'D' || trans_type == 'W') 
  {
    int amount;
    int account_id;
    int fund_id;

    read >> account_id >> fund_id >> amount;

    Transaction new_tran(trans_type, account_id, fund_id, amount, Transaction::kSuccess);
    queue_trans_.push(new_tran);
    
  } 
  else if (trans_type == 'T') 
  {
    int transfer_acc_id;
    int transfer_fund_id;
    int account_id;
    int fund_id;
    int amount;

    read >> account_id >> fund_id >> transfer_acc_id >> transfer_fund_id >> amount;
    Transaction new_tran(trans_type, account_id, fund_id, transfer_acc_id, transfer_fund_id, amount, Transaction::kSuccess);
    queue_trans_.push(new_tran);

  } 
  else if (trans_type == 'H') 
  {
    int account_id;
    read >> account_id;
    Transaction new_tran(trans_type, account_id, Transaction::kSuccess);
    queue_trans_.push(new_tran);
  } 
  else if (trans_type == 'F') 
  {
    int account_id;
    int fund_id;
    read >> account_id >> fund_id;
    Transaction new_tran(trans_type, account_id, fund_id, Transaction::kSuccess);
    queue_trans_.push(new_tran);
  } 
  else 
  {
    cerr << "ERROR: Invalid transaction type: " << trans_type << endl;
  }
}

void Bank::Transactions() 
{
  while (!queue_trans_.empty()) 
  {
    Transaction tran = queue_trans_.front();
    int account_id = tran.get_acc_id();
    char trans_type = tran.get_trans_type();

    queue_trans_.pop();

    if (trans_type == 'W')
    {
      Withdrawal(tran, account_id); 
    } 
    else if (trans_type == 'D') 
    {
      Deposit(tran, account_id); 
    } 
    else if (trans_type == 'T') 
    {
      Transfer(tran, account_id); 
    } 
    else if (trans_type == 'O') 
    {
      OpenAcc(tran, account_id); 
    } 
    else if (trans_type == 'H') 
    {
      ExeAccHistory(tran, account_id); 
    } 
    else if (trans_type == 'F') 
    {
      ExeFundHistory(tran, account_id); 
    } 
    else 
    {
      cerr << "ERROR: Invalid transaction type: " << trans_type << endl;
    }
  }
}

void Bank::Transfer(const Transaction& new_tran, int account_id) 
{
  if (new_tran.CheckStatus()) 
  {
    int transfer_acc_id = new_tran.get_transfer_account_id();
    int fund_id = new_tran.get_fund_id();
    int amount = new_tran.get_amount();
    int transfer_fund_id = new_tran.get_transfer_fund_id();

    Account *from;
    Account *to;

    if ((tree_accounts_.Retrieve(account_id, from)) && (tree_accounts_.Retrieve(transfer_acc_id, to))) 
    {
      if (from->AccWithdraw(fund_id, amount, new_tran.get_trans_type(), account_id, transfer_acc_id, transfer_fund_id)) 
      {
        to->Deposit(transfer_fund_id, amount, new_tran.get_trans_type(), transfer_acc_id, account_id, fund_id);
      }
    } 
    else 
    {
      cerr << "ERROR: Account " << (tree_accounts_.Retrieve(account_id, from) ? transfer_acc_id : account_id) << " not found. Transfer not allowed " << endl;
    }
  }
}

void Bank::Withdrawal(const Transaction& new_tran, int account_id) 
{
  int fund_id = new_tran.get_fund_id();
  int amount = new_tran.get_amount();

  Account *new_acc;

  if (tree_accounts_.Retrieve(account_id, new_acc)) 
  {
    new_acc->AccWithdraw(fund_id, amount, new_tran.get_trans_type(), account_id, 0, 0);
  }
  else 
  {
    cerr << "ERROR: Account " << account_id << " not found. Withdraw not allowed" << endl;
  }
}

void Bank::Deposit(const Transaction& new_tran, int account_id) 
{
  int fund_id = new_tran.get_fund_id();
  int amount = new_tran.get_amount();

  Account *new_acc;

  if (tree_accounts_.Retrieve(account_id, new_acc)) 
  {
    new_acc->Deposit(fund_id, amount, new_tran.get_trans_type(), account_id, 0, 0);
  } 
  else 
  {
    cerr << "ERROR: Account " << account_id << " not found. Deposit not allowed" << endl;
  }
}

void Bank::OpenAcc(const Transaction& new_tran, int account_id) 
{
  Account *new_acc;
  if (tree_accounts_.Retrieve(account_id, new_acc)) 
  {
    cerr << "ERROR: Account " << account_id << " is already open. No Transaction" << endl;
  } else 
  {
    Account *t_account = new Account(new_tran.get_acc_id(), new_tran.get_first_name(), new_tran.get_last_name());
    tree_accounts_.Insert(t_account);
  }
}

void Bank::ExeFundHistory(const Transaction& new_tran, int account_id) 
{
  int fund_id = new_tran.get_fund_id();
  Account *acc;
  if (tree_accounts_.Retrieve(account_id, acc)) 
  {
    acc->AccountFundHistory(fund_id);
  } 
  else 
  {
    cerr << "ERROR: Invalid Account ID " << new_tran.get_acc_id() << ". History by fund cannot be displayed." << endl;
  }
}

void Bank::PrintTrans() 
{
  cout << endl << "Account Balance:" << endl;
  tree_accounts_.Display();
}

void Bank::ExeAccHistory(const Transaction& new_tran, int account_id) 
{
  Account *new_acc;
  if (tree_accounts_.Retrieve(account_id, new_acc)) 
  {
    new_acc->AccountHistory();
  } 
  else 
  {
    if (new_tran.get_acc_id() <= 0) 
    {
      cerr << "ERROR: Invalid Account ID: " << new_tran.get_acc_id() << endl;
    } 
    else 
    {
      cerr << "ERROR: Account " << new_tran.get_acc_id() << " not found. Account History cannot be outputted." << endl;
    }
  }
}
