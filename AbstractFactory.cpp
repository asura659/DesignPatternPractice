#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Herbivore {
public:
  virtual string GetName() = 0;
};

class Carnivore {
public:
  virtual void Eat(Herbivore* h) = 0;
  virtual string GetName() = 0;
};

class ContinentFactory {
public:
  virtual Herbivore* CreateHerbivore() = 0;
  virtual Carnivore* CreateCarnivore() = 0;
};

class Lion : public Carnivore {
public:
  virtual void Eat(Herbivore* h) {
    cout << GetName() << " eats " << h->GetName() << endl;
  }

  virtual string GetName() {
    return "Lion";
  }
};

class Bison : public Herbivore {
  virtual string GetName() {
    return "Bison";
  }
};

class Wolf : public Carnivore {
public:
  virtual void Eat(Herbivore* h) {
    cout << GetName() << " eats " << h->GetName() << endl;
  }
  
  virtual string GetName() {
    return "Wolf";
  }
};

class Wildebeest : public Herbivore {
  virtual string GetName() {
    return "Wildebeest";
  }
};

class AfricaFactory : public ContinentFactory {
public:
  virtual Herbivore* CreateHerbivore() {
    return new Wildebeest();
  }

  virtual Carnivore* CreateCarnivore() {
    return new Lion();
  }
};

class AmericaFactory : public ContinentFactory {
public:
  virtual Herbivore* CreateHerbivore() {
    return new Bison();
  }

  virtual Carnivore* CreateCarnivore() {
    return new Wolf();
  }
};

class AnimalWorld {
private:
  Herbivore* herbivore_;
  Carnivore* carnivore_;

public:
  AnimalWorld(ContinentFactory* factory) {
    herbivore_ = factory->CreateHerbivore();
    carnivore_ = factory->CreateCarnivore();
  }

  void RunFoodChain() {
    carnivore_->Eat(herbivore_);
  }
};

int main() {
  ContinentFactory* africa = new AfricaFactory();
  AnimalWorld* world = new AnimalWorld(africa);
  world->RunFoodChain();

  delete world;
  
  ContinentFactory* america = new AmericaFactory();
  world = new AnimalWorld(america);
  world->RunFoodChain();

  return 0;
}
