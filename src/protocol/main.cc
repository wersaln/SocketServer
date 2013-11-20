#include <string>
#include <iostream>

#include "shake_protocol.pb.h"
#include "command_types.h"
class Protocol {
public:
  static std::string Serialize(const obj::Command &cmd){

  }
  static std::string Serialize(const obj::PlayerAdd &cmd){
    std::cout << "PlayerAdd\n";
  }
};
int main() {
  obj::PlayerAdd p;
  p.add_user = obj::User(0, "Nick", 2, 1);
  Protocol::Serialize(p);
  return 0;
}
