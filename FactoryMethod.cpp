#include <cxxabi.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

// memory leaks
char* demangle(const char *demangle) {
    int status;
    return abi::__cxa_demangle(demangle, 0, 0, &status);
}

class Page {
public:
  Page(){}
  virtual ~Page(){}
};

class SkillPage : public Page {
public:
  SkillPage(){}
  virtual ~SkillPage(){}
};

class EducationPage : public Page {
public:
  EducationPage(){}
  virtual ~EducationPage(){}
};

class ExperiencePage : public Page {
public:
  ExperiencePage(){}
  virtual ~ExperiencePage(){}
};

class IntroductionPage : public Page {
public:
  IntroductionPage(){}
  virtual ~IntroductionPage(){}
};

class ResultsPage : public Page {
public:
  ResultsPage(){}
  virtual ~ResultsPage(){}
};

class ConclusionPage : public Page {
public:
  ConclusionPage(){}
  virtual ~ConclusionPage(){}
};

class SummaryPage : public Page {
public:
  SummaryPage(){}
  virtual ~SummaryPage(){}
};

class BibliographyPage : public Page {
public:
  BibliographyPage(){}
  virtual ~BibliographyPage(){}
};

class Document {
protected:
  vector<Page*> pages_;

public:
  Document() {}

  vector<Page*> Pages() {
    return pages_;
  }

  virtual void CreatePages() = 0;
};

class Resume : public Document {
public:
  virtual void CreatePages() {
    pages_.push_back(new SkillPage());
    pages_.push_back(new EducationPage());
    pages_.push_back(new ExperiencePage());
  }
};

class Report : public Document {
public:
  virtual void CreatePages() {
    pages_.push_back(new IntroductionPage());
    pages_.push_back(new ResultsPage());
    pages_.push_back(new ConclusionPage());
    pages_.push_back(new SummaryPage());
    pages_.push_back(new BibliographyPage());
  }
};

int main() {
  vector<Document*> documents;
  Document* resume = new Resume();
  resume->CreatePages();
  documents.push_back(resume);

  Document* report = new Report();
  report->CreatePages();
  documents.push_back(report);

  for_each(documents.begin(), documents.end(),
	   [](Document* document)->void {
	     cout << endl << demangle(typeid(*document).name()) << " -- " << endl;
	     vector<Page*> pages = document->Pages();
	     for_each(pages.begin(), pages.end(),
		      [](Page* page)->void {
			cout << " " << demangle(typeid(*page).name()) << endl;
		      });
	   });
  return 0;
}
