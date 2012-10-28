#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Random;
class Object;

class LoadBalancer {
private:
  static LoadBalancer* instance_;
  vector<string> servers_;

protected:
  LoadBalancer() {
    servers_.push_back("ServerI");
    servers_.push_back("ServerII");
    servers_.push_back("ServerIII");
    servers_.push_back("ServerIV");
    servers_.push_back("ServerV");
  }

public:
  static LoadBalancer* GetLoadBalancer() {
    if(instance_ == 0) {
      instance_ = new LoadBalancer();
    }
    return instance_;
  }

  string Server() {
    int r = rand() % servers_.size();
    return servers_.at(r);
  }
};

LoadBalancer* LoadBalancer::instance_ = 0;

int main() {
  LoadBalancer* b1 = LoadBalancer::GetLoadBalancer();
  LoadBalancer* b2 = LoadBalancer::GetLoadBalancer();
  LoadBalancer* b3 = LoadBalancer::GetLoadBalancer();
  LoadBalancer* b4 = LoadBalancer::GetLoadBalancer();

  if(b1 == b2 && b2 == b3 && b3 == b4)
    cout << "Same instance" << endl;

  LoadBalancer* balancer = LoadBalancer::GetLoadBalancer();
  for(int i = 0; i < 15; ++i) {
    string server = balancer->Server();
    cout << "Dispatch Request to: " + server << endl;
  }

  return 0;
}
