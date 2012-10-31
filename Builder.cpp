#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Vehicle {
private:
  map<string, string> parts_;
  string vehicle_type_;
public:
  Vehicle(string vehicle_type) 
    : vehicle_type_(vehicle_type)
  {}

  string GetParts(string key) {
    return parts_[key];
  }

  void SetParts(string key, string value) {
    parts_[key] = value;
  }

  void Show() {
    cout << endl << " ---------- " << endl;
    cout << " Frame : " << parts_["frame"] << endl;
    cout << " Engine : " << parts_["engine"] << endl;
    cout << " #Wheels : " << parts_["wheels"] << endl;
    cout << " #Doors : " << parts_["doors"] << endl;
  }
};

class VehicleBuilder {
protected:
  Vehicle* vehicle_;
  
public:
  Vehicle* GetVehicle() {
    return vehicle_;
  }

  virtual void BuildFrame() = 0;
  virtual void BuildEngine() = 0;
  virtual void BuildWheels() = 0;
  virtual void BuildDoors() = 0;
};

class Shop {
public:
  void Construct(VehicleBuilder* vehicle_builder) {
    vehicle_builder->BuildFrame();
    vehicle_builder->BuildEngine();
    vehicle_builder->BuildWheels();
    vehicle_builder->BuildDoors();
  }
};

class MotorCycleBuilder : public VehicleBuilder {
public:
  MotorCycleBuilder() 
  {vehicle_ = new Vehicle("MotorCycle");}

  virtual void BuildFrame() {
    vehicle_->SetParts("frame", "MotorCycle Frame");
  }

  virtual void BuildEngine() {
    vehicle_->SetParts("engine", "500 cc");
  }

  virtual void BuildWheels() {
    vehicle_->SetParts("wheels", "2");
  }

  virtual void BuildDoors() {
    vehicle_->SetParts("doors", "0");
  }
};

class CarBuilder : public VehicleBuilder {
public:
  CarBuilder() 
  {
    vehicle_ = new Vehicle("Car");
  }

  virtual void BuildFrame() {
    vehicle_->SetParts("frame", "Car Frame");
  }

  virtual void BuildEngine() {
    vehicle_->SetParts("engine", "2500 cc");
  }

  virtual void BuildWheels() {
    vehicle_->SetParts("wheels", "4");
  }

  virtual void BuildDoors() {
    vehicle_->SetParts("doors", "4");
  }
};

class ScooterBuilder : public VehicleBuilder {
public:
  ScooterBuilder()
  {
    vehicle_ = new Vehicle("Scooter");
  }

  virtual void BuildFrame() {
    vehicle_->SetParts("frame", "Scooter Frame");
  }

  virtual void BuildEngine() {
    vehicle_->SetParts("engine", "50 cc");
  }

  virtual void BuildWheels() {
    vehicle_->SetParts("wheels", "2");
  }

  virtual void BuildDoors() {
    vehicle_->SetParts("doors", "0");
  }
};

int main() {
  VehicleBuilder *builder;
  Shop *shop = new Shop();

  builder = new ScooterBuilder();
  shop->Construct(builder);
  builder->GetVehicle()->Show();

  delete builder;

  builder = new CarBuilder();
  shop->Construct(builder);
  builder->GetVehicle()->Show();

  delete builder;

  builder = new MotorCycleBuilder();
  shop->Construct(builder);
  builder->GetVehicle()->Show();

  delete builder;

  return 0;
}
