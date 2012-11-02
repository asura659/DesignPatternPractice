#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Element;

class IVisitor {
public:
  virtual void Visit(Element* element) = 0;
};

class Element {
public:
  virtual void Accept(IVisitor* visitor) = 0;
};

class Employee : public Element {
private:
  string name_;
  double income_;
  int vacation_days_;

public:
  Employee(string name, double income, int vacation_days)
    : name_(name),
      income_(income),
      vacation_days_(vacation_days)
  {}

  virtual string GetType() {
    return "Employee";
  }

  string Name() {
    return name_;
  }
  
  void Name(string name) {
    name_ = name;
  }

  double Income() {
    return income_;
  }

  void Income(double income) {
    income_ = income;
  }

  int VacationDays() {
    return vacation_days_;
  }

  void VacationDays(int vacation_days) {
    vacation_days_ = vacation_days;
  }

  virtual void Accept(IVisitor* visitor) {
    visitor->Visit(this);
  }
};

class IncomeVisitor : public IVisitor {
public:
  virtual void Visit(Element* element) {
    Employee* employee = dynamic_cast<Employee*>(element);
    employee->Income(employee->Income() * 1.10);
    cout << employee->GetType() << " " << employee->Name() << "'s new Income: " << employee->Income() << endl;
  }
};

class VacationVisitor : public IVisitor {
public:
  virtual void Visit(Element* element) {
    Employee* employee = dynamic_cast<Employee*>(element);
    
    cout << employee->GetType() << " " << employee->Name() << "'s new vacation days: " << employee->VacationDays() << endl;
  }
};

class Employees {
private:
  vector<Employee*> employees_;

public:
  void Attach(Employee* employee) {
    employees_.push_back(employee);
  }

  void Accept(IVisitor* visitor) {
    for_each(employees_.begin(), employees_.end(), 
	     [visitor](Employee* e) -> void { 
	       e->Accept(visitor);
	     });
    cout << endl;
  }
};

class Clerk : public Employee {
public:
  Clerk()
    : Employee("Hank", 25000.0, 14)
  {}

  virtual string GetType() {
    return "Clerk";
  }
};

class Director : public Employee {
public:
  Director()
    : Employee("Elly", 35000.0, 16)
  {}

  virtual string GetType() {
    return "Director";
  }
};

class President : public Employee {
public:
  President()
    : Employee("Dick", 45000.0, 21)
  {}
  
  virtual string GetType() {
    return "President";
  }
};

int main() {
  Employees e;

  e.Attach(new Clerk());
  e.Attach(new Director());
  e.Attach(new President());

  e.Accept(new IncomeVisitor());
  e.Accept(new VacationVisitor());

  return 0;
}
  
