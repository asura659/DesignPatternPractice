#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DrawingElement {
protected:
  string name_;

public:
  DrawingElement(string name) 
    : name_(name)
  {}

  virtual void Add(DrawingElement *d) = 0;
  virtual void Remove(DrawingElement *d) = 0;
  virtual void Display(int indent) = 0;
};

class PrimitiveElement : public DrawingElement {
public:
  PrimitiveElement(string name)
    : DrawingElement(name)
  {}

  virtual void Add(DrawingElement *c) {
    cout << "Cannot add to PrimitiveElement" << endl;
  }

  virtual void Remove(DrawingElement *c) {
    cout << "Cannot remove from a PrimitiveElement" << endl;
  }

  virtual void Display(int indent) {
    
    cout << string(indent, '-') << " " << name_ << endl;
  }
};

class CompositeElement : public DrawingElement {
private:
  vector<DrawingElement*> elements_;

public:
  CompositeElement(string name) 
    : DrawingElement(name)
  {}

  virtual void Add(DrawingElement *d) {
    elements_.push_back(d);
  }

  virtual void Remove(DrawingElement *d) {
    vector<DrawingElement*>::iterator it = 
      find(elements_.begin(), elements_.end(), d);
    if(it != elements_.end())
      elements_.erase(it);
  }

  virtual void Display(int indent) {
    cout << string(indent, '-') << "+ " << name_ << endl;

    for_each(elements_.begin(), elements_.end(), [indent](DrawingElement* d)->void
	     { 
	       d->Display(indent + 2);
	     });
  }
};

int main() {
  CompositeElement* root = new CompositeElement("Picture");

  root->Add(new PrimitiveElement("Red Line"));
  root->Add(new PrimitiveElement("Blue Circle"));
  root->Add(new PrimitiveElement("Green Box"));

  CompositeElement* comp = new CompositeElement("Two Circles");
  
  comp->Add(new PrimitiveElement("Black Circle"));
  comp->Add(new PrimitiveElement("White Circle"));
  root->Add(comp);

  PrimitiveElement* pe = new PrimitiveElement("Yellow Line");
  root->Add(pe);
  root->Remove(pe);

  root->Display(1);

  return 0;
}
