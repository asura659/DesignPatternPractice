#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Command {
public:
  virtual void Execute() = 0;
  virtual void UnExecute() = 0;
};

class Calculator {
private:
  int current_;

public:
  Calculator()
    : current_(0)
  {}

  void Operation(char op, int operand) {
    switch(op) {
    case '+': current_ += operand; break;
    case '-': current_ -= operand; break;
    case '*': current_ *= operand; break;
    case '/': current_ /= operand; break;
    }

    cout << "Current value = " << current_ << " (following " << op << " " << operand << ")" << endl;
  }
};

class CalculatorCommand : public Command {
private:
  char operator_;
  int operand_;
  Calculator* calculator_;
  
public:
  CalculatorCommand(Calculator* calculator, char op, int operand)
    : calculator_(calculator)
    , operator_(op)
    , operand_(operand)
  {}

  void SetOperator(char op) {
    operator_ = op;
  }

  void SetOperand(int operand) {
    operand_ = operand;
  }

  virtual void Execute() {
    calculator_->Operation(operator_, operand_);
  }

  virtual void UnExecute() {
    calculator_->Operation(Undo(operator_), operand_);
  }

private:
  char Undo(char op) {
    switch(op) {
    case '+': return '-';
    case '-': return '+';
    case '*': return '/';
    case '/': return '*';
    }
  }
};

class User {
private:
  Calculator* calculator_;
  vector<Command*> commands_;
  int current_;

public:
  User()
    : calculator_(new Calculator())
    , current_(0)
  {}

  void Redo(int levels) {
    cout << endl << "---- Redo " << levels << " levels " << endl;
    for(int i = 0; i < levels; ++i) {
      if(current_ < commands_.size() - 1) {
	Command *command = commands_.at(current_++);
	command->Execute();
      }
    }
  }

  void Undo(int levels) {
    cout << endl << "---- Undo " << levels << " levels " << endl;
    for(int i = 0; i < levels; ++i) {
      if(current_ > 0) {
	Command *command = commands_.at(--current_);
	command->UnExecute();
      }
    }
  }

  void Compute(char op, int operand) {
    Command *command = new CalculatorCommand(
					     calculator_, op, operand);
    command->Execute();
    commands_.push_back(command);
    ++current_;
  }
};

int main() {
  User user;
  user.Compute('+', 100);
  user.Compute('-', 50);
  user.Compute('*', 10);
  user.Compute('/', 2);

  user.Undo(4);
  user.Redo(3);

  return 0;
}
