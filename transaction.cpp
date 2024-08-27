#include "transaction.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Transaction::Transaction() {}

Transaction::Transaction(char tran_type, int acc_id, string last_name, string first_name, Status status) 
{
  trans_type_ = tran_type;
  acc_id_ = acc_id;
  last_name_ = last_name;
  first_name_ = first_name;
  status_ = status;
}

Transaction::Transaction(char tran_type, int acc_id, int fund_id, int amount, Status status) 
{
  trans_type_ = tran_type;
  acc_id_ = acc_id;
  fund_id_ = fund_id;
  amount_ = amount;
  status_ = status;
}

Transaction::Transaction(char tran_type, int acc_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, Status status) 
{
  trans_type_ = tran_type;
  acc_id_ = acc_id;
  fund_id_ = fund_id;
  transfer_acc_id_ = transfer_acc_id;
  transfer_fund_id_ = transfer_fund_id;
  amount_ = amount;
  status_ = status;
}

Transaction::Transaction(char tran_type, int acc_id, Status status) 
{
  trans_type_ = tran_type;
  acc_id_ = acc_id;
  status_ = status;
}

Transaction::Transaction(char tran_type, int account_id, int fund_id, Status status) 
{
  trans_type_ = tran_type;
  acc_id_ = account_id;
  fund_id_ = fund_id;
  status_ = status;
}

char Transaction::get_trans_type() const 
{ 
    return trans_type_; 
}

int Transaction::get_acc_id() const 
{ 
    return acc_id_; 
}

int Transaction::get_fund_id() const 
{ 
    return fund_id_; 
}

string Transaction::get_first_name() const
{ 
    return first_name_; 
}
string Transaction::get_last_name() const 
{ 
    return last_name_; 
}

int Transaction::get_transfer_account_id() const 
{ 
    return transfer_acc_id_; 
}

int Transaction::get_transfer_fund_id() const 
{ 
    return transfer_fund_id_; 
}

int Transaction::get_amount() const 
{ 
    return amount_; 
}

bool Transaction::CheckStatus() const { 
    return status_ == kSuccess; 
}

ostream &operator<<(ostream &o, const Transaction &other) {
    if (other.CheckStatus()) 
    {
        char trans_type = other.get_trans_type();
        if (trans_type == 'D' || trans_type == 'W') 
        {
            o << ' ' << trans_type << ' ' << other.get_acc_id() << ' ' << other.get_fund_id() << ' ' << other.get_amount();
        } 
        else if (trans_type == 'T') 
        {
            o << ' ' << trans_type << ' ' << other.get_acc_id() << ' ' << other.get_fund_id() << ' '
              << other.get_transfer_account_id() << ' ' << other.get_transfer_fund_id() << ' ' << other.get_amount();
        } 
        else if (trans_type == 'O') 
        {
            o << "Account opened for " << other.get_acc_id() << endl;
        } 
        else 
        {
            o << ' ' << trans_type << ": invalid transaction type";
        }
    } 
    else 
    {
        char trans_type = other.get_trans_type();
        if (trans_type == 'O') 
        {
            o << "The account " << other.get_acc_id() << " has already been created" << endl;
        } 
        else 
        {
            o << ' ' << trans_type << ' ' << other.get_acc_id() << ' ';
            if (trans_type == 'T')
            {
                o << other.get_fund_id() << ' ' << other.get_transfer_account_id() << ' ' << other.get_transfer_fund_id() << ' ';
            } else {
                o << other.get_fund_id() << ' ';
            }
            o << other.get_amount() << " (Failed)";
        }
    }
    return o << endl;
}
