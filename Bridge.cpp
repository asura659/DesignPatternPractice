#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class DataObject {
public:
  DataObject(){}
  virtual ~DataObject(){}
  virtual void NextRecord() = 0;
  virtual void PriorRecord() = 0;
  virtual void AddRecord(string name) = 0;
  virtual void DeleteRecord(string name) = 0;
  virtual void ShowRecord() = 0;
  virtual void ShowAllRecords() = 0;
};

class CustomerBase {
private:
  DataObject* data_object_;
  
protected:
  string group_;
  
public:
  CustomerBase(string group)
    : group_(group)
  {}

  void Data(DataObject* data) {
    data_object_ = data;
  }
  
  DataObject* Data() {
    return data_object_;
  }

  virtual void Next() {
    data_object_->NextRecord();
  }

  virtual void Prior() {
    data_object_->PriorRecord();
  }

  virtual void Add(string customer) {
    data_object_->AddRecord(customer);
  }

  virtual void Delete(string customer) {
    data_object_->DeleteRecord(customer);
  }

  virtual void Show() {
    data_object_->ShowRecord();
  }

  virtual void ShowAll() {
    cout << "Customer Group: " << group_ << endl;
    data_object_->ShowAllRecords();
  }
};

class Customers : public CustomerBase {
public:
  Customers(string group)
    : CustomerBase(group)
  {}

  virtual void ShowAll() {
    cout << endl << "--------------------" << endl;
    CustomerBase::ShowAll();
    cout << "--------------------" << endl;
  }
};

class CustomerData : public DataObject {
private:
  vector<string> customers_;
  int current_;
public:
  CustomerData() 
    : current_(0)
  {
    customers_.push_back("Jim Jones");
    customers_.push_back("Samual Jackson");
    customers_.push_back("Allen Good");
    customers_.push_back("Ann Stills");
    customers_.push_back("Lisa Giolani");
  }
  
  virtual void NextRecord() {
    if(current_ < customers_.size() - 1) {
      ++current_;
    }
  }

  virtual void PriorRecord() {
    if(current_ > 0) {
      --current_;
    }
  }

  virtual void AddRecord(string customer) {
    customers_.push_back(customer);
  }

  virtual void DeleteRecord(string custom) {
    vector<string>::iterator it = find(customers_.begin(), customers_.end(), custom);
    if(it != customers_.end())
      customers_.erase(it);
  }

  virtual void ShowRecord() {
    cout << customers_.at(current_) << endl;
  }

  virtual void ShowAllRecords() {
    for_each(customers_.begin(), customers_.end(), 
	     [](string customer)->void {cout << " " << customer << endl;});
  }
};

int main() {
  Customers *customers = new Customers("Chicago");
  customers->Data(new CustomerData());

  customers->Show();
  customers->Next();
  customers->Show();
  customers->Next();
  customers->Show();
  customers->Add("Henry Valasquez");
  
  customers->ShowAll();

  delete customers->Data();
  delete customers;
  return 0;
}
