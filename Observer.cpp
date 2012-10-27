#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stock;

class IInvestor {
public:
  virtual void Update(Stock* stock) = 0;
};

class Stock {
private:
  string symbol_;
  double price_;
  vector<IInvestor*> investors_;

public:
  Stock(string symbol, double price) 
    : symbol_(symbol)
    , price_(price)
  {}

  void Attach(IInvestor* investor) {
    investors_.push_back(investor);
  }

  void Detach(IInvestor* investor) {
    vector<IInvestor*>::iterator it = find(investors_.begin(), investors_.end(), investor);
    if(it != investors_.end())
      investors_.erase(it);
  }

  void Notify() {
    for_each(investors_.begin(), investors_.end(), 
	     [this](IInvestor* investor)->void{ investor->Update(this); });
    cout << endl;
  }

  double Price() {
    return price_;
  }

  void Price(double price) {
    if(price_ != price) {
      price_ = price;
      Notify();
    }
  }

  string Symbol() {
    return symbol_;
  }
};

class IBM : public Stock {
public:
  IBM(string symbol, double price) 
    : Stock(symbol, price)
  {}
};

class Investor : public IInvestor {
private:
  string name_;

public:
  Investor(string name) 
    : name_(name)
  {}

  virtual void Update(Stock* stock) {
    cout << "Notified " << name_ << " of " << stock->Symbol() << "'s cange to " << stock->Price() << endl;
  }
};

int main() {
  IBM* ibm = new IBM("IBM", 120.00);
  ibm->Attach(new Investor("Sorros"));
  ibm->Attach(new Investor("Berkshire"));

  ibm->Price(120.10);  
  ibm->Price(121.00);
  ibm->Price(120.50);
  ibm->Price(120.75);

  return 0;
}
