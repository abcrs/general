/**
 * @file my_web_server_session.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 **/
#ifndef WEB_MY_WEB_SERVER_SESSION_H_
#define WEB_MY_WEB_SERVER_SESSION_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "WebServer.h"
#include "web_code/web/my_web_server_session_state.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class to allow interaction between C++ and the server
 *
 * A class that extends a JS class for use with the server
 */
class MyWebServerSession : public JSONSession {
 public:
    /**
     * @brief Constructor
     *
     * Takes a server session state
     */
    explicit MyWebServerSession(MyWebServerSessionState s) : state(s) {}
    /**
     * @brief Destructor
     */
    ~MyWebServerSession() {}
    /**
     * @brief receives information from the Wserver
     *
     * Receives information from the webserver
     * Uses this to interact with the C++ code to exhibit changes in the sim
     *
     * @param[in] val javascript thing
     */
    void receiveJSON(picojson::value& val) override;
    /**
     * @brief Unused update
     */
    void update() override {}

 private:
    MyWebServerSessionState state;
};


#endif  // WEB_MY_WEB_SERVER_SESSION_H_
