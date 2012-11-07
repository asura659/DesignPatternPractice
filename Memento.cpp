#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Memento {
private:
  string name_;
  string phone_;
  double budget_;

public:
  Memento(string name, string phone, double budget)
    : name_(name)
    , phone_(phone)
    , budget_(budget)
  {}

  string Name() {
    return name_;
  }

  void Name(string name) {
    name_ = name;
  }

  string Phone() {
    return phone_;
  }

  void Phone(string phone) {
    phone_ = phone;
  }
  
  double Budget() {
    return budget_;
  }

  void Budget(double budget) {
    budget_ = budget;
  }
};

class SalesProspect {
private:
  string name_;
  string phone_;
  double budget_;

public:
  string Name() {
    return name_;
  }

  void Name(string name) {
    name_ = name;
    cout << "Name: " << name_ << endl;
  }

  string Phone() {
    return phone_;
  }

  void Phone(string phone) {
    phone_ = phone;
    cout << "Phone: " << phone_ << endl;
  }

  double Budget() {
    return budget_;
  }

  void Budget(double budget) {
    budget_ = budget;
    cout << "Budget: " << budget_ << endl;
  }

  Memento* SaveMemento() {
    cout << endl << "Saving state -- " << endl;
    return new Memento(name_, phone_, budget_);
  }

  void RestoreMemento(Memento* memento) {
    cout << endl << "Restoring state -- " << endl;
    Name(memento->Name());
    Phone(memento->Phone());
    Budget(memento->Budget());
  }
};

class ProspectMemory {
private:
  Memento* memento_;

public:
  Memento* GetMemento() {
    return memento_;
  }

  void SetMemento(Memento* memento) {
    memento_ = memento;
  }
};

int main() {
  SalesProspect* s = new SalesProspect();
  s->Name("Noel van Halen");
  s->Phone("(412) 256-0990");
  s->Budget(25000.0);

  ProspectMemory* m = new ProspectMemory();
  m->SetMemento(s->SaveMemento());

  s->Name("Leo Welch");
  s->Phone("(310) 209-7111");
  s->Budget(1000000.0);

  s->RestoreMemento(m->GetMemento());
  
  return 0;
}
