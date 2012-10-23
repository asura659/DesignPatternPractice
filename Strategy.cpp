#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class SortStrategy {
public:
  virtual void Sort(vector<string> &vect) = 0;
};

class QuickSort : public SortStrategy {
public:
  virtual void Sort(vector<string> &vect) {
    sort(vect.begin(), vect.end());
    cout << "QuickSorted : " << endl;
  }
};

class ShellSort : public SortStrategy {
public:
  virtual void Sort(vector<string> &vect) {
    //ShellSort(vect.begin(), vect.end()); // not-implemented
    cout << "ShellSorted : " << endl;
  }
};

class MergeSort : public SortStrategy {
public:
  virtual void Sort(vector<string> &vect) {
    //MergeSort(vect.begin(), vect.end()); // not-implemented
    cout << "MergeSorted : " << endl;
  }
};

class SortedList {
private:
  vector<string> vect_;
  SortStrategy *sort_strategy_;

public:
  void SetSortStrategy(SortStrategy* sort_strategy) {
    sort_strategy_  = sort_strategy;
  }

  void Add(string name) {
    vect_.push_back(name);
  }

  void Sort() {
    sort_strategy_->Sort(vect_);

    for_each(vect_.begin(), vect_.end(), [](string name)->void {cout << name << endl;});
    cout << endl;
  }
    
};

int main() {
  SortedList student_records;
  student_records.Add("Samuel");
  student_records.Add("Jimmy");
  student_records.Add("Sandre");
  student_records.Add("Vivek");
  student_records.Add("Anna");

  student_records.SetSortStrategy(new QuickSort());
  student_records.Sort();

  student_records.SetSortStrategy(new ShellSort());
  student_records.Sort();

  student_records.SetSortStrategy(new MergeSort());
  student_records.Sort();

  return 0;
}
