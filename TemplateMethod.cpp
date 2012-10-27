#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DataRow {
private:
  string str_;
public:
  DataRow(){}
  DataRow(string str) : str_(str) {}
  string ToString() {
    return str_;
  }
};

class DataTable {
public:
  DataTable(){
    rows_.push_back(new DataRow("abc"));
    rows_.push_back(new DataRow("bcd"));
    rows_.push_back(new DataRow("cde"));
    rows_.push_back(new DataRow("def"));
  }

  vector<DataRow*> rows_;
};

class DataSet {
public:
  DataTable* Tables(string str){return new DataTable();}
};

class DataAccessObject {
protected:
  string connection_string_;
  DataSet* data_set_;

public:
  virtual void Connect() {
    connection_string_ = "provider = Microsoft.JET.OLEDB.4.0; data source=..\\..\\..\\db1.mdb";
  }

  virtual void Select() = 0;
  virtual void Process() = 0;
  
  virtual void Disconnect() {
    connection_string_ = "";
  }

  void Run() {
    Connect();
    Select();
    Process();
    Disconnect();
  }
};
class OleDbDataAdapter {
public:
  OleDbDataAdapter(string sql, string connection) 
  {}

  void Fill(DataSet* data_set, string str)
  {}
};

class Categories : public DataAccessObject {
public:
  virtual void Select() {
    string sql = "select CategoryName from Categories";
    OleDbDataAdapter* data_adapter = new OleDbDataAdapter(sql, connection_string_);
    data_set_ = new DataSet();
    data_adapter->Fill(data_set_, "Categories");
  }

  virtual void Process() {
    cout << "Categories ---- " << endl;

    DataTable* data_table = data_set_->Tables("Categories");

    for_each(data_table->rows_.begin(), data_table->rows_.end(), 
	     [](DataRow* row)->void {cout << row->ToString() << endl;});
    cout << endl;
  }
};


class Products : public DataAccessObject {
public:
  virtual void Select() {
    string sql = "select ProductName from Products";
    OleDbDataAdapter* data_adapter = new OleDbDataAdapter(sql, connection_string_);
    data_set_ = new DataSet();
    data_adapter->Fill(data_set_, "Products");
  }

  virtual void Process() {
    cout << "Products ---- " << endl;
    DataTable* data_table = data_set_->Tables("Products");

    for_each(data_table->rows_.begin(), data_table->rows_.end(), 
	     [](DataRow* row)->void {cout << row->ToString() << endl;});
    cout << endl;
  }
};

int main() {
  DataAccessObject* dao_categories = new Categories();
  dao_categories->Run();

  DataAccessObject* dao_products = new Products();
  dao_products->Run();

  return 0;
}
