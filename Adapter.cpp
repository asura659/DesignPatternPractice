#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>
using namespace std;

class ChemicalDatabank {
public:
  float GetCriticalPoint(string compound, string point) {
    transform(compound.begin(), compound.end(), compound.begin(), ::tolower);
    if(point == "M") {
      if(compound == "water") return 0.0f;
      if(compound == "benzene") return 5.5f;
      if(compound == "ethanol") return -114.1f;
      return 0;
    } else {
      if(compound == "water") return 100.0f;
      if(compound == "benzene") return 80.1f;
      if(compound == "ethanol") return 78.3f;
      return 0;
    }
  }

  string GetMolecularStructure(string compound) {
    transform(compound.begin(), compound.end(), compound.begin(), ::tolower);
    if(compound == "water") return "H2O";
    if(compound == "benzene") return "C6H6";
    if(compound == "ethanol") return "C2H5OH";
    return "";
  }

  double GetMolecularWeight(string compound) {
    transform(compound.begin(), compound.end(), compound.begin(), ::tolower);
    if(compound == "water") return 18.015;
    if(compound == "benzene") return 78.1134;
    if(compound == "ethanol") return 46.0688;
    return 0;
  }
};

class Compound {
protected:
  string chemical_;
  float boiling_point_;
  float melting_point_;
  double molecular_weight_;
  string molecular_formula_;

public:
  Compound(string chemical) 
    : chemical_(chemical)
  {}

  virtual void Display() {
    cout << endl << "Compound : " << chemical_ << " ------- ";
  }
};

class RitchCompound : public Compound {
private:
  ChemicalDatabank *bank_;
  
public:
  RitchCompound(string name)
    : Compound(name)
  {}

  virtual void Display() {
    bank_ = new ChemicalDatabank();

    boiling_point_ = bank_->GetCriticalPoint(chemical_, "B");
    melting_point_ = bank_->GetCriticalPoint(chemical_, "M");
    molecular_weight_ = bank_->GetMolecularWeight(chemical_);
    molecular_formula_ = bank_->GetMolecularStructure(chemical_);

    Compound::Display();
    cout << " Formula : " << molecular_formula_;
    cout << " Weight : " << molecular_weight_;
    cout << " Melting Pt : " << melting_point_;
    cout << " Boiling Pt : " << boiling_point_;

    delete bank_;
  }
};

int main() {
  Compound *unknown = new Compound("Unknown");
  unknown->Display();

  Compound *water = new RitchCompound("Water");
  water->Display();
  
  Compound *benzene = new RitchCompound("Benzene");
  benzene->Display();

  Compound *ethanol = new RitchCompound("Ethanol");
  ethanol->Display();
  
  return 0;
}
