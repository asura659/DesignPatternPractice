#include <iostream>
#include <string>

using namespace std;

class Customer {
public:
  Customer(string name) 
    : name_(name) {}
  string Name() const { return name_; }
private:
  string name_;
};

class Loan {
public:
  bool HasNoBadLoans(const Customer* c) {
    cout << "Check loans for " << c->Name() << endl;
    return true;
  }
};

class Credit {
public:
  bool HasGoodCredit(const Customer* c) {
    cout << "Check credit for " << c->Name() << endl;
    return true;
  }
};

class Bank {
public:
  bool HasSufficientSavings(const Customer* c, int amount) {
    cout << "Check bank for " << c->Name() << endl;
    return true;
  }
};

class Mortgage {
public:
  Mortgage()
    : bank_(new Bank())
    , loan_(new Loan())
    , credit_(new Credit())
  {}

  ~Mortgage() {
    delete bank_;
    delete loan_;
    delete credit_;
  }

  bool IsEligible(const Customer *cust, int amount) {
    cout << cust->Name() << " applies for " << amount << " loan" << endl;
    bool eligible = true;

    if(!bank_->HasSufficientSavings(cust, amount)) {
      eligible = false;
    } else if(!loan_->HasNoBadLoans(cust)) {
      eligible = false;
    } else if(!credit_->HasGoodCredit(cust)) {
      eligible = false;
    }

    return eligible;
  }

private:
  Bank *bank_;
  Loan *loan_;
  Credit *credit_;
};

int main() {
  Mortgage* mortgage = new Mortgage();
  
  Customer* customer = new Customer("Ann McKinsey");
  bool eligible = mortgage->IsEligible(customer, 125000);

  cout << endl << customer->Name() << " has been " << (eligible ? "Approved" : "Rejected") << endl;
  delete mortgage;
  delete customer;

  return 0;
}
