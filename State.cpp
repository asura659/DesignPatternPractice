#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account;

class State {
protected:
  Account* account_;
  double balance_;
  double interest_;
  double lower_limit_;
  double upper_limit_;

public:  
  Account* GetAccount() {
    return account_;
  }

  void SetAccount(Account* account) {
    account_ = account;
  }

  double Balance() {
    return balance_;
  }

  void Balance(double balance) {
    balance_ = balance;
  }

  virtual void Deposit(double amount) = 0;
  virtual void Withdraw(double amount) = 0;
  virtual void PayInterest() = 0;
  virtual string GetType() = 0;
};


class Account {
private:
  State* state_;
  string owner_;

public:
  Account(string owner);
 

  double Balance() {
    return state_->Balance();
  }

  State* GetState() {
    return state_;
  }

  void SetState(State* state) {
    state_ = state;
  }
  
  void Deposit(double amount) {
    state_->Deposit(amount);
    cout << "Deposited " << amount << " --- " << endl;
    cout << " Balance = " << Balance() << endl;
    cout << " Status = " << GetState()->GetType() << endl;
  }

  void Withdraw(double amount) {
    state_->Withdraw(amount);
    cout << "Withdraw " << amount << " --- " << endl;
    cout << " Balance = " << Balance() << endl;
    cout << " Status = " << GetState()->GetType() << endl;
  }
  
  void PayInterest() {
    state_->PayInterest();
    cout << "Interest Paid --- " << endl;
    cout << " Balance = " << Balance() << endl;
    cout << " Status = " << GetState()->GetType() << endl;
  }
};

class RedState : public State {
private:
  double service_fee_;

public:
  RedState(State* state) {
    balance_ = state->Balance();
    account_ = state->GetAccount();
    Initialize();
  }

  virtual string GetType() {
    return "RedState";
  }

private:
  void Initialize() {
    interest_ = 0.0;
    lower_limit_ = -1000.0;
    upper_limit_ = 0.0;
    service_fee_ = 15.00;
  }

public:
  virtual void Deposit(double amount) {
    balance_ += amount;
    StateChangeCheck();
  }

  virtual void Withdraw(double amount) {
    amount -= service_fee_;
    cout << "No funds available for withdrawal!" << endl;
  }

  virtual void PayInterest() {
    // No interest is paid
  }

private:
  void StateChangeCheck();
};

class SilverState : public State {
public:
  SilverState(double balance, Account* account) {
    balance_ = balance;
    account_ = account;
    Initialize();
  }

  SilverState(State* state) {
    Balance(state->Balance());
    SetAccount(state->GetAccount());
    Initialize();
  }

  virtual string GetType() {
    return "SilverState";
  }

private:
  void Initialize() {
    interest_ = 0.0;
    lower_limit_ = 0.0;
    upper_limit_ = 1000.0;
  }
  
public:
  virtual void Withdraw(double amount) {
    balance_ -= amount;
    StateChangeCheck();
  }

  virtual void PayInterest() {
    balance_ += interest_ * balance_;
    StateChangeCheck();
  }

  virtual void Deposit(double amount) {
    balance_ += amount;
    StateChangeCheck();
  }



private:
  void StateChangeCheck();
};

Account::Account(string owner)   
   : owner_(owner)
{
  state_ = new SilverState(0.0, this);
}

void RedState::StateChangeCheck() {
  if(balance_ > upper_limit_) {
    account_->SetState(new SilverState(this));
  }
}

class GoldState : public State {
public:
  GoldState(double balance, Account* account) {
    balance_ = balance;
    account_ = account;
    Initialize();
  }

  GoldState(State* state) {
    balance_ = state->Balance();
    SetAccount(state->GetAccount());
    Initialize();
  }

  virtual string GetType() {
    return "GoldState";
  }

private:
  void Initialize() {
    interest_ = 0.05;
    lower_limit_ = 1000.0;
    upper_limit_ = 10000000.0;
  }

public:
  virtual void Deposit(double amount) {
    balance_ += amount;
    StateChangeCheck();
  }

  virtual void Withdraw(double amount) {
    balance_ -= amount;
    StateChangeCheck();
  }

  virtual void PayInterest() {
    balance_ += interest_ * balance_;
    StateChangeCheck();
  }

private:
  void StateChangeCheck() {
    if(balance_ < 0.0) {
      account_->SetState(new RedState(this));
    } else if(balance_ < lower_limit_) {
      account_->SetState(new SilverState(this));
    }
  }
};

void SilverState::StateChangeCheck() {
  if(balance_ < lower_limit_) {
    account_->SetState(new RedState(this));
  } else if(balance_ > upper_limit_) {
    account_->SetState(new GoldState(this));
  }
}


int main() {
  Account *account = new Account("Jim Johnson");

  account->Deposit(500.0);
  account->Deposit(300.0);
  account->Deposit(550.0);
  account->PayInterest();
  account->Withdraw(2000.0);
  account->Withdraw(1100.0);

  return 0;
}
