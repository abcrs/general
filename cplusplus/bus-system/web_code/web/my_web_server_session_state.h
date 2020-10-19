/**
 * @file my_web_server_session_state.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 **/
#ifndef WEB_MY_WEB_SERVER_SESSION_STATE_H_
#define WEB_MY_WEB_SERVER_SESSION_STATE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <map>

class MyWebServerCommand;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct MyWebServerSessionState {
    MyWebServerSessionState() :
                      commands(std::map<std::string, MyWebServerCommand*>()) {}
    std::map<std::string, MyWebServerCommand*> commands;
};

#endif  // WEB_MY_WEB_SERVER_SESSION_STATE_H_
