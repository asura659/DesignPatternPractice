#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Participant;
class AbstractChatroom {
public:
  virtual void Register(Participant* participant) = 0;
  virtual void Send(string from, string to, string message) = 0;
};

class Participant {
private:
  AbstractChatroom* chatroom_;
  string name_;

public:
  Participant(string name) 
    : name_(name)
  {}

  string Name() {
    return name_;
  }

  AbstractChatroom* GetChatroom() {
    return chatroom_;
  }

  void SetChatroom(AbstractChatroom* chatroom) {
    chatroom_ = chatroom;
  }

  void Send(string to, string message) {
    chatroom_->Send(name_, to, message);
  }

  virtual void Receive(string from, string message) {
    cout << from << " to " << Name() << ": '" << message << "'" << endl;
  }
};

class Chatroom : public AbstractChatroom {
private:
  map<string, Participant*> participants_;

public:
  virtual void Register(Participant* participant) {
    map<string, Participant*>::iterator it 
      = find_if(participants_.begin(), participants_.end(),
		[participant](pair<string, Participant*> p)->bool {
		  return p.second == participant;
		});
    if(it == participants_.end()) {
      participants_[participant->Name()] = participant;
    }
    participant->SetChatroom(this);
  }
  
  virtual void Send(string from, string to, string message) {
    Participant* participant = participants_[to];
    if(participant != 0)
      participant->Receive(from, message);
  }
};

class Beatle : public Participant {
public:
  Beatle(string name)
    : Participant(name)
  {}

  virtual void Receive(string from, string message) {
    cout << "To a Beatle: " << endl;
    Participant::Receive(from, message);
  }
};

class NonBeatle : public Participant {
public:
  NonBeatle(string name) 
    : Participant(name)
  {}

  virtual void Receive(string from, string message) {
    cout << "To a non-Beatle: " << endl;
    Participant::Receive(from, message);
  }
};

int main() {
  
  Chatroom *chatroom = new Chatroom();
  
  Participant	*George = new Beatle("George");
  Participant	*Paul	= new Beatle("Paul");
  Participant	*Ringo	= new Beatle("Ringo");
  Participant	*John	= new Beatle("John");
  Participant	*Yoko	= new NonBeatle("Yoko");

  chatroom->Register(George);
  chatroom->Register(Paul);
  chatroom->Register(Ringo);
  chatroom->Register(John);
  chatroom->Register(Yoko);
  
  Yoko->Send("John", "Hi John!");
  Paul->Send("Ringo", "All you need is love");
  Ringo->Send("George", "My sweet Lord");
  Paul->Send("John", "Can't buy me love");
  John->Send("Yoko", "My sweet love");

  return 0;
}
