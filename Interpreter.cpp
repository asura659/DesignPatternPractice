#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Context {
private:
  string input_;
  int output_;

public:
  Context(string input) 
    : input_(input)
    , output_(0)
  {}

  string Input() {
    return input_;
  }

  void Input(string input) {
    input_ = input;
  }

  int Output() {
    return output_;
  }

  void Output(int output) {
    output_ = output;
  }
};

class Expression {
public:
  void Interpret(Context* context) {
    if(context->Input().empty())
      return;

    if(context->Input().find(Nine()) == 0) {
      context->Output(context->Output() + 9 * Multiplier());
      context->Input(context->Input().substr(2));
    } else if(context->Input().find(Four()) == 0) {
      context->Output(context->Output() + 4 * Multiplier());
      context->Input(context->Input().substr(2));
    } else if(context->Input().find(Five()) == 0) {
      context->Output(context->Output() + 5 * Multiplier());
      context->Input(context->Input().substr(1));
    }

    while(context->Input().find(One()) == 0) {
      context->Output(context->Output() + 1 * Multiplier());
      context->Input(context->Input().substr(1));
    }
  }

  virtual string One() = 0;
  virtual string Four() = 0;
  virtual string Five() = 0;
  virtual string Nine() = 0;
  virtual int Multiplier() = 0;
};

class ThousandExpression : public Expression {
public:
  virtual string One() { return "M"; }
  virtual string Four() { return " "; }
  virtual string Five() { return " "; }
  virtual string Nine() { return " "; }
  virtual int Multiplier() { return 1000; }
};

class HundredExpression : public Expression {
public:
  virtual string One() { return "C"; }
  virtual string Four() { return "CD"; }
  virtual string Five() { return "D"; }
  virtual string Nine() { return "CM"; }
  virtual int Multiplier() { return 100; }
};

class TenExpression : public Expression {
public:
  virtual string One() { return "X"; }
  virtual string Four() { return "XL"; }
  virtual string Five() { return "L"; }
  virtual string Nine() { return "XC"; }
  virtual int Multiplier() { return 10; }
};

class OneExpression : public Expression {
public:
  virtual string One() { return "I"; }
  virtual string Four() { return "IV"; }
  virtual string Five() { return "V"; }
  virtual string Nine() { return "IX"; }
  virtual int Multiplier() { return 1; }
};

int main() {
  string roman = "MCMXXVIII";
  Context context(roman);

  vector<Expression*> tree;
  tree.push_back(new ThousandExpression());
  tree.push_back(new HundredExpression());
  tree.push_back(new TenExpression());
  tree.push_back(new OneExpression());

  for_each(tree.begin(), tree.end(),
	   [&context](Expression* exp)->void {
	     exp->Interpret(&context);
	   });

  cout << roman << " = " << context.Output() << endl;

  return 0;
}
