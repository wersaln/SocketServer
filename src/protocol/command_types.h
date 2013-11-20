#include <string>
#include <vector>
namespace obj {
  enum {
    // Client commands.
    CMD_CREATE_GROUP    = 1,
    CMD_GET_GROUP       = 2,
    CMD_READY           = 3,
    CMD_SHAKE           = 4,
    CMD_GET_PLAYERS     = 5,
    CMD_GET_MY_ID       = 6,
    // Server commands.
    CMD_YOUR_ID         = 65,
    CMD_USER_READY      = 66,
    CMD_USER_ADD        = 67,
    CMD_USER_EXIT       = 68,
    CMD_GROUP_USERS     = 69,
    CMD_START           = 70,
    CMD_USERS_POSITIONS = 71
  };

  struct User {
    User() {}
    User(int id, std::string name, int color, bool ready)
      : id_(id),
        name_(name),
        color_(color),
        ready_(ready)
    {}
    int id_;
    std::string name_;
    int color_;
    bool ready_;
  }; // do not send

  struct UserPosition {
    int id;
    int count;
    bool finished;
  }; // do not send

  // base
  struct Command {
    Command() {}
    Command(const int command) { cmd = command; }

    int cmd;
  };
  // server only

  struct Players : Command {
    Players() { cmd = CMD_GROUP_USERS; }
    std::vector<User> users_;
  };
  struct Positions :Command {
    Positions() { cmd = CMD_USERS_POSITIONS; }
    std::vector<UserPosition> users_;
  };
  struct PlayerAdd :Command {
    PlayerAdd() { cmd = CMD_USER_ADD; }
    User add_user_;
  };
  struct Player : Command {
    int id_;
  }; // do not send
  struct Ready : Player {
    Ready() { cmd = CMD_USER_READY; }
  };
  struct PlayerExit : Player {
    PlayerExit() { cmd = CMD_USER_EXIT; }
  };
  struct YourID : Player {
    YourID() { cmd = CMD_YOUR_ID; }
  };


  // client only
  struct NewGame : Command {
    std::string name;
  }; // do not send
  struct CreateGroup :NewGame {
    CreateGroup() { cmd = CMD_CREATE_GROUP; }
  };
  struct GetGroup : NewGame {
    GetGroup() { cmd = CMD_GET_GROUP; }
  };
} //namespace obj
