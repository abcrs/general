/**
 * @file my_web_server_command.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 **/

#ifndef WEB_MY_WEB_SERVER_COMMAND_H_
#define WEB_MY_WEB_SERVER_COMMAND_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

#include "src/config_manager.h"
#include "src/data_structs.h"
#include "web_code/web/visualization_simulator.h"
#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server_session_state.h"
#include "web_code/web/my_web_server.h"

class MyWebServerSession;
class MyWebServerSessionState;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Web Server Commands
 *
 * Virtual class to establish different commands for the webserver
 **/
class MyWebServerCommand {
 public:
	/**
	 * @brief Virtual Destructor
	 *
	 * Destructor for webservercommand objects
	 **/
    virtual ~MyWebServerCommand() {}

	/**
	 * @brief Virtual command
	 *
	 * Virtual class to establish parameters needed for a command
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    virtual void execute(MyWebServerSession* session, picojson::value& command,  // NOLINT
                         MyWebServerSessionState* state) = 0;
};


///***** * * * * * COMMANDS * * * * * ******///

/**
 * @brief Command to get routes
 *
 * Gets routes as needed for web server
 **/
class GetRoutesCommand : public MyWebServerCommand {
 public:
	/**
	 * @brief GetRoutesCommand constructor
	 *
	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
	 **/
    explicit GetRoutesCommand(MyWebServer* ws);

	/**
	 * @brief Gets routes as needed for web server
	 *
	 * Interacts with webserver and route information to execute the command
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    MyWebServer* myWS;
};

/**
 * @brief Command to get buses
 *
 * Gets buses as needed for web server
 **/
class GetBussesCommand : public MyWebServerCommand {
 public:
	 /**
 	 * @brief GetBussesCommand constructor
 	 *
 	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
 	 **/
    explicit GetBussesCommand(MyWebServer* ws);

	/**
	 * @brief Gets buses as needed for web server
	 *
	 * Interacts with webserver and bus information to execute the command
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    MyWebServer* myWS;
};

/**
 * @brief Command to start webserver
 *
 * Starts webserver
 **/
class StartCommand : public MyWebServerCommand {
 public:
	 /**
 	 * @brief StartCommand constructor
 	 *
 	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
 	 **/
    explicit StartCommand(VisualizationSimulator* sim);

	/**
	 * @brief Starts VisSim object
	 *
	 * Starts the visualization simulator to get everything going
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    VisualizationSimulator* mySim;
    std::vector<int> timeBetweenBusses;
    int numTimeSteps;
};

/**
 * @brief Command to pause webserver
 *
 * Pauses webserver
 **/
class PauseCommand : public MyWebServerCommand {
 public:
	 /**
 	 * @brief PauseCommand constructor
 	 *
 	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
 	 **/
    explicit PauseCommand(VisualizationSimulator* sim);

	/**
	 * @brief Pauses VisSim actions
	 *
	 * Interacts with webserver to pause the VisSim object
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    VisualizationSimulator* mySim;
};

/**
 * @brief Command to update the VisualizationSimulator
 *
 * Updates VisualizationSimulator
 **/
class UpdateCommand : public MyWebServerCommand {
 public:
	 /**
 	 * @brief UpdateCommand constructor
 	 *
 	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
 	 **/
    explicit UpdateCommand(VisualizationSimulator* sim);

	/**
	 * @brief Updates the VisSim object
	 *
	 * Updates the VisSim object to update all relevant data
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    VisualizationSimulator* mySim;
};

/**
 * @brief Command to add observer to a bus
 *
 * Add an observer to a bus
 **/
class AddBusListenerCommand: public MyWebServerCommand {
 public:
	 /**
 	 * @brief AddListenerCommand constructor
 	 *
 	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
 	 **/
    explicit AddBusListenerCommand(VisualizationSimulator* sim);

	/**
	 * @brief Adds an observer to a bus
	 *
	 * Interacts with webserver and creates observer as needed
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    VisualizationSimulator* mySim;
};

/**
 * @brief Command to add observer to a stop
 *
 * Add an observer to a stop
 **/
class AddStopListenerCommand: public MyWebServerCommand {
 public:
	 /**
 	 * @brief AddStopListenerCommand constructor
 	 *
 	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
 	 **/
    explicit AddStopListenerCommand(VisualizationSimulator* sim);

	/**
	 * @brief Adds an observer to a stop
	 *
	 * Interacts with webserver and creates observer as needed
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    VisualizationSimulator* mySim;
};

/**
 * @brief Command initialize the routes
 *
 * Initializes the routes
 **/
class InitRoutesCommand : public MyWebServerCommand {
 public:
	 /**
 	 * @brief InitRoutesCommand constructor
 	 *
 	 * Actually constructs a VisSim object with the parameter
 	 *
 	 * @param[in] ws MyWebServer object to construct a VisSim object
 	 **/
    explicit InitRoutesCommand(ConfigManager* cm);

	/**
	 * @brief Start routes for webserver
	 *
	 * Interacts with webserver and route information to execute the command
	 *
	 * @param[in] session the webserversession that is being interacted with
	 * @param[in] command Javascript something
	 * @param[in] state webserversession state, not used, why here?
	 **/
    void execute(MyWebServerSession* session, picojson::value& command,
                 MyWebServerSessionState* state) override;

 private:
    ConfigManager* cm;
};

#endif  // WEB_MY_WEB_SERVER_COMMAND_H_
