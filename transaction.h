#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction{
public:
    enum Status {kExecuted, kSuccess, kFailed};
    
    //constructors 
    Transaction();
    Transaction(char tran_type, int acc_id, string last_name, string first_name, Status status);
    Transaction(char tran_type, int acc_id, int fund_id, int amount, Status status);
    Transaction(char tran_type, int acc_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, Status status);
    Transaction(char tran_type, int acc_id, Status status);
    Transaction(char tran_type, int acc_id, int fund_id, Status status);

    //getters
    char get_trans_type() const;
    int get_acc_id() const;
    int get_fund_id() const;

    string get_first_name() const;
    string get_last_name() const;
    string get_full_name() const; 

    int get_transfer_account_id() const;
    int get_transfer_fund_id() const;
    int get_amount() const;

    bool CheckStatus() const;

    //operator 
    friend ostream& operator<<(ostream& stream, const Transaction& other);

private:
    //data members
    char trans_type_;
    int amount_;
    string last_name_;
    string first_name_;
    int acc_id_;
    int fund_id_;
    int transfer_acc_id_;
    int transfer_fund_id_;
    Status status_; 
};
#endif