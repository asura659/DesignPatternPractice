#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IMath {
public:
  virtual double Add(double x, double y) = 0;
  virtual double Sub(double x, double y) = 0;
  virtual double Mul(double x, double y) = 0;
  virtual double Div(double x, double y) = 0;
};

class Math : public IMath {
public:
  virtual double Add(double x, double y) { return x + y; }
  virtual double Sub(double x, double y) { return x - y; }
  virtual double Mul(double x, double y) { return x * y; }
  virtual double Div(double x, double y) { return x / y; }
};

class MathProxy : public IMath {
private:
  Math* math_;
  
public:
  MathProxy() 
    : math_(new Math())
  {}
  
  double Add(double x, double y) {
    return math_->Add(x, y);
  }

  double Sub(double x, double y) {
    return math_->Sub(x, y);
  }

  double Mul(double x, double y) {
    return math_->Mul(x, y);
  }

  double Div(double x, double y) {
    return math_->Div(x, y);
  }
};

int main() {
  MathProxy proxy;
  
  cout << "4 + 2 = " << proxy.Add(4, 2) << endl;
  cout << "4 - 2 = " << proxy.Sub(4, 2) << endl;
  cout << "4 * 2 = " << proxy.Mul(4, 2) << endl;
  cout << "4 / 2 = " << proxy.Div(4, 2) << endl;

  return 0;
}
