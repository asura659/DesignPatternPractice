#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Character {
protected:
  char symbol_;
  int width_;
  int height_;
  int ascent_;
  int descent_;
  int point_size_;

public:
  virtual void Display(int point_size) = 0;
};

class CharacterA : public Character {
public:
  CharacterA() {
    symbol_ = 'A';
    height_ = 100;
    width_ = 120;
    ascent_ = 70;
    descent_ = 0;
  }

  virtual void Display(int point_size) {
    point_size_ = point_size;
    cout << symbol_ << " (pointsize " << point_size_ << ")" << endl;
  }
};

class CharacterB : public Character {
public:
  CharacterB() {
    symbol_ = 'B';
    height_ = 100;
    width_ = 140;
    ascent_ = 72;
    descent_ = 0;
  }

  virtual void Display(int point_size) {
    point_size_ = point_size;
    cout << symbol_ << " (pointsize " << point_size_ << ")" << endl;
  }
};

class CharacterZ : public Character {
public:
  CharacterZ() {
    symbol_ = 'Z';
    height_ = 100;
    width_ = 100;
    ascent_ = 68;
    descent_ = 0;
  }

  virtual void Display(int point_size) {
    point_size_ = point_size;
    cout << symbol_ << " (pointsize " << point_size_ << ")" << endl;
  }
};

class CharacterFactory {
private:
  map<char, Character*> characters_;

public:
  Character* GetCharacter(char key) {
    Character* character = characters_[key];
    if(character == 0) {
      switch(key) {
      case 'A': character = new CharacterA(); break;
      case 'B': character = new CharacterB(); break;
      case 'Z': character = new CharacterZ(); break;
      }
      characters_[key] = character;
    }
    return character;
  }
};

int main() {
  string document = "AAZZBBZB";
  // char *chars = document.c_str();

  CharacterFactory factory;
  
  int point_size = 10;

  for_each(document.begin(), document.end(), 
	   [&point_size, &factory](char c)->void {
	     ++point_size;
	     Character* character = factory.GetCharacter(c);
	     character->Display(point_size);
	   });
  return 0;
}
