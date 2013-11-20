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
    shake_protocol::Command command;
    command.set_cmd(cmd.cmd);
    {
      shake_protocol::Command::User* user = command.add_users();
      user->set_id(cmd.add_user_.id_);
      user->set_name(cmd.add_user_.name_);
      user->set_color(cmd.add_user_.color_);
      user->set_ready(cmd.add_user_.ready_);
    }
    std::string msg;
    command.SerializeToString(&msg);
    return msg;
  }
};
int main() {
  obj::PlayerAdd p;
  p.add_user_ = obj::User(0, "Nick", 2, 1);
  std::string str = Protocol::Serialize(p);
  for (size_t i = 0; i < str.size(); ++i) {
    std::cout << (int)str[i];
    if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z')
      std::cout << "[" <<str[i] << "] ";
    else
      std::cout << " ";

  }
  return 0;
}
