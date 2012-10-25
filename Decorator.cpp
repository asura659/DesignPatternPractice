#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LibraryItem {
private:
  int num_copies_;

public:
  LibraryItem()
  {}

  LibraryItem(int num_copies)
    : num_copies_(num_copies)
  {}

  int NumCopies() const {
    return num_copies_;
  }
  
  void NumCopies(int num_copies) {
    num_copies_ = num_copies;
  }

  virtual void Display() = 0;
};

class Book : public LibraryItem {
private:
  string author_;
  string title_;

public:
  Book(string author, string title, int num_copies)
    : author_(author)
    , title_(title)
    , LibraryItem(num_copies)
  {
  }

  virtual void Display() {
    cout << endl << "Book ----- " << endl;
    cout << " Author: " << author_ << endl;
    cout << " Title: " << title_ << endl;
    cout << " # Copies: " << NumCopies() << endl;
  }
};

class Video : public LibraryItem {
private:
  string director_;
  string title_;
  int play_time_;

public:
  Video(string director, string title, int num_copies, int play_time) 
    : director_(director)
    , title_(title)
    , LibraryItem(num_copies)
    , play_time_(play_time)
  {
  }

  virtual void Display() {
    cout << endl << "Video ----- " << endl;
    cout << " Director: " << director_ << endl;
    cout << " Title: " << title_ << endl;
    cout << " # Copies: " << NumCopies() << endl;
    cout << " Playtime: " << play_time_ << endl;
  }
};

class Decorator : public LibraryItem {
protected:
  LibraryItem* library_item_;

public:
  Decorator(LibraryItem* library_item) 
    : library_item_(library_item)
  {}
  
  virtual void Display() {
    library_item_->Display();
  }
};

class Borrowable : public Decorator {
protected:
  vector<string> borrowers_;

public:
  Borrowable(LibraryItem* library_item) 
    : Decorator(library_item)
  {}

  void BorrowItem(string name) {
    borrowers_.push_back(name);
    library_item_->NumCopies(library_item_->NumCopies() - 1);
  }

  void ReturnItem(string name) {
    vector<string>::iterator it = find(borrowers_.begin(), borrowers_.end(), name);
    if(it != borrowers_.end())
      borrowers_.erase(it);
    library_item_->NumCopies(library_item_->NumCopies() + 1);
  }

  virtual void Display() {
    Decorator::Display();

    for_each(borrowers_.begin(), borrowers_.end(), 
	     [](string borrower)->void { cout << " borrower: " << borrower << endl;});
  }

};

int main() {
  Book* book = new Book("Worley", "Inside ASP.NET", 10);
  book->Display();

  Video* video = new Video("Spielberg", "Jaws", 23, 92);
  video->Display();

  cout << endl << "Making video borrowable:" << endl;

  Borrowable* borrow_video = new Borrowable(video);
  borrow_video->BorrowItem("Customer #1");
  borrow_video->BorrowItem("Customer #2");

  borrow_video->Display();

  return 0;
}
