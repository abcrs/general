/**
 * @file my_web_server_session.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 **/
#include <map>
#include <string>

#include "my_web_server_session.h"  // NOLINT

#include "web_code/web/my_web_server_command.h"


void MyWebServerSession::receiveJSON(picojson::value& val) {
    std::string cmd = val.get<picojson::object>()["command"].get<std::string>();
    std::map<std::string, MyWebServerCommand*>::iterator it =
                                                       state.commands.find(cmd);
    if (it != state.commands.end()) {
        it->second->execute(this, val, &state);
    }
}
