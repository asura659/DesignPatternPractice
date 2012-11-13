#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
private:
  string name_;
  
public:
  Item(string name)
    : name_(name)
  {}

  string Name() {
    return name_;
  }
};

class IAbstractIterator {
public:
  virtual Item* First() = 0;
  virtual Item* Next() = 0;
  virtual bool IsDone() = 0;
  virtual Item* CurrentItem() = 0;
};


class IAbstractCollection {
public:
  virtual IAbstractIterator* CreateIterator() = 0;
};

class Collection : public IAbstractCollection {
private:
  vector<Item*> items_;

public:
  virtual IAbstractIterator* CreateIterator();
 

  int Count() {
    return items_.size();
  }

  Item* GetAt(int i) {
    return items_.at(i);
  }

  void PushBack(Item* item) {
    items_.push_back(item);
  }
};

class Iterator : public IAbstractIterator {
private: 
  Collection* collection_;
  int current_;
  int step_;

public:
  Iterator(Collection* collection) 
    : current_(0)
    , step_(1)
    , collection_(collection)
  {}

  virtual Item* First() {
    current_ = 0;
    return collection_->GetAt(current_);
  }

  virtual Item* Next() {
    current_ += step_;
    if(!IsDone()) {
      return collection_->GetAt(current_);
    } else {
      return 0;
    }
  }

  int Step() {
    return step_;
  }

  void Step(int step) {
    step_ = step;
  }

  virtual Item* CurrentItem() {
    return collection_->GetAt(current_);
  }

  virtual bool IsDone() {
    return current_ >= collection_->Count();
  }
};

IAbstractIterator* Collection::CreateIterator() {
    return new Iterator(this);
}

int main() {
  Collection collection;
  collection.PushBack(new Item("Item 0"));
  collection.PushBack(new Item("Item 1"));
  collection.PushBack(new Item("Item 2"));
  collection.PushBack(new Item("Item 3"));
  collection.PushBack(new Item("Item 4"));
  collection.PushBack(new Item("Item 5"));
  collection.PushBack(new Item("Item 6"));
  collection.PushBack(new Item("Item 7"));
  collection.PushBack(new Item("Item 8"));

  Iterator iterator(&collection); 
  iterator.Step(2);
  
  for(Item* item = iterator.First(); !iterator.IsDone(); item = iterator.Next()) {
    cout << item->Name() << endl;
  }

  return 0;
}
