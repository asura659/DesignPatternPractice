#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class ColorPrototype {
public:
  virtual ColorPrototype* Clone() = 0;
};

class Color : public ColorPrototype {
private:
  int red_;
  int green_;
  int blue_;

public:
  Color(int red, int green, int blue) 
    : red_(red)
    , green_(green)
    , blue_(blue)
  {}

  virtual ColorPrototype* Clone() {
    cout << "Cloning color RGB: " << red_ << ", " << green_ << ", " << blue_ << endl;
    ColorPrototype* clone(this);
    return clone;
  }
};

class ColorManager {
private: 
  map<string, ColorPrototype*> colors_;
  
public:
  ColorPrototype* GetColor(string key) {
    return colors_[key];
  }

  void SetColor(string key, ColorPrototype* value) {
    colors_[key] = value;
  }
};

int main() {
  ColorManager colormanager;
  colormanager.SetColor("red", new Color(255, 0, 0));
  colormanager.SetColor("green", new Color(0, 255, 0));
  colormanager.SetColor("blue", new Color(0, 0, 255));

  colormanager.SetColor("angry", new Color(255, 54, 0));
  colormanager.SetColor("peace", new Color(128, 211, 128));
  colormanager.SetColor("flame", new Color(211, 34, 20));

  Color* color1 = dynamic_cast<Color*>(colormanager.GetColor("red")->Clone());
  Color* color2 = dynamic_cast<Color*>(colormanager.GetColor("peace")->Clone());
  Color* color3 = dynamic_cast<Color*>(colormanager.GetColor("flame")->Clone());

  return 0;
}
