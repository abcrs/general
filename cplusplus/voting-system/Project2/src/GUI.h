/**
 * @file GUI.h
 *
 * @copyright 2019 5801 Team24, All rights reserved.
 */

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <MinGfx-1.0/mingfx.h>
#include <vector>

// #include "src/controller.h"
#include "src/Voting_System.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

// class Controller;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 *  @brief An application that uses the MinGfx library to open up a window that
 *  includes a few buttons for openning and saving election files
 *
 *  After constructing a new GUI, call Run to start and run the
 *  application. Run will not return until the application window is closed.
 *  Example:
 *
 *  ```
 *  int main(int argc, char **argv) {
 *      RobotViewer *app = new RobotViewer();
 *      app->Run();
 *      return 0;
 *  }
 *  ```
 *
 *  While the window is open UpdateSimulation will be called repeatedly,
 *  once per frame. Fill this in to update your simulation or perform any other
 *  processing that should happen over time as the simulation progresses.
 *
 *  Fill in the `On*()` methods as desired to respond to user input events.
 *
 *  Fill in the `Draw*()` methods to draw graphics on the screen using
 *  either the `nanovg` library or raw `OpenGL`.
 */
class GUI : public mingfx::GraphicsApp {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A arena_params passed down from main.cc for the
   * initialization of the VotingSystem.
   */
  explicit GUI(int width, int height);

  /**
   * @brief Destructor.
   *
   * `delete` the contained VotingSystem.
   */
  ~GUI() override {}

  /** Used to setup the 2D GUI. */
  void InitNanoGUI() override;

  /**
   * @brief Handle the user pressing the open button on the GUI.
   *
   * TODO: XXXX
   */
  void OnOpenButtonPressed();

  /**
   * @brief Handle the user pressing the save button on the GUI.
   *
   * TODO: XXXX
   */
  void OnSaveButtonPressed();

  /**
   * @brief Handle the user pressing the display winner button on the GUI.
   *
   * TODO: XXXX
   */

  void OnAnalysisButtonPressed();

  /**
   * @brief Handle the user pressing the analysis button on the GUI.
   *
   * TODO: XXXX
   */
  void OnDisplayWinnersPressed();

  /**
   * @brief Handle the user pressing the Output Media button on the GUI.
   *
   * TODO: XXXX
   */
  void OnOutputMediaPressed();

  /**
   * @brief Handle the user pressing the Output audit button on the GUI.
   *
   * TODO: XXXX
   */
  void OnOutputAuditPressed();

  /**
   * @brief Called each time the mouse moves on the screen within the GUI
   * window.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   * @param[in] delta How far the mouse has moved.
   */
  void OnMouseMove( const mingfx::Point2& pos,
                    const mingfx::Vector2& delta) override {};

  /**
   * @brief Called each time the left mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseDown( const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the left mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseUp( const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseDown( const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseUp( const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time a character key is pressed.
   *
   * @param[in] c Character representing a key that was pressed.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnKeyDown( const char *c,  int modifiers) override {};

  /**
   * @brief Called each time a character key is released.
   *
   * @param[in] c Character representing a key that was released.
   * @param[in] modifiers Any modifier keys that were held with the key.
   */
  void OnKeyUp( const char *c,  int modifiers) override { };

  /**
   * @brief Called each time a special (non-alphabetic) key is pressed.
   *
   * @param[in] key The key that was pressed.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnSpecialKeyDown( int key,  int scancode,
                         int modifiers) override {}

  /**
   * @brief Called each time a special (non-alphabetic) key is released.
   *
   * @param[in] key The key that was released.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnSpecialKeyUp( int key,  int scancode,
                       int modifiers) override {};

  /**
   * @brief Draw the Arena with all of its entities using `nanogui`.
   *
   * This is the primary driver for drawing all entities in the Arena. It is
   * called at each iteration of `nanogui::mainloop()`.
   *
   * @param[in] ctx Context for nanogui.
   */
  // void DrawUsingNanoVG(NVGcontext *ctx) override;

  /**
   * @brief Draw using `OpenGL`. This method is unimplemented, as currently
   * we are doing all drawing with `nanovg` in this application, so it is empty.
   */
  void DrawUsingOpenGL() override {}

  /**
   * @brief A method to receive a new voting system pointer from controller.
   *
   * Used at controller contstruction to pass active voting system
   */
  void SetVotingSystem(Voting_System *vote_sys);

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  GUI &operator=(const GUI &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  GUI(const GUI &other) = delete;

 private:

  bool RunViewer();

  // Controller *controller_;
  Voting_System *vote_sys_;
  bool paused_{true};

  std::vector<nanogui::TextBox*> velocity_vector_;

  // buttons
  nanogui::Button *open_button_{nullptr};
  nanogui::Button *save_button_{nullptr};
  nanogui::Button *analysis_button_{nullptr};
  nanogui::Button *display_button_{nullptr};
  nanogui::Button *media_button_{nullptr};
  nanogui::Button *audit_button_{nullptr};

  float xOffset_;
  bool nanogui_intialized_;
  nanogui::FormHelper* gui;
  nanogui::ref<nanogui::Window> window;
  
  nanogui::Window * DisplayCSVWindow;
};

#endif  // SRC_GUI_H_
