/** CSci-4611 Assignment 2:  Car Soccer
 */

#ifndef CAR_SOCCER_H_
#define CAR_SOCCER_H_

#include <mingfx.h>
using namespace mingfx;

#include "ball.h"
#include "car.h"


// The main class for the Car Soccer application
class CarSoccer : public GraphicsApp {
public:
    CarSoccer();
    virtual ~CarSoccer();

    /// This is called when special keys like SPACEBAR are pressed
    void OnSpecialKeyDown(int key, int scancode, int modifiers);
    void LaunchBall();

    /// This is called once each frame.  dt is "delta time", the time elapsed
    /// since the last call.
    void UpdateSimulation(double dt);
    void UpdateCar(double dt);
    void UpdateCarVelocity(double dt);
    void UpdateCarPosition(double dt);
    void UpdateBall(double dt);
    void StaticBounceBall(double dt, Vector3 n, int d, float f);
    void CheckBounce(double dt);

    /// This is called when it is time to initialize graphics objects, like
    /// texture files.
    void InitOpenGL();

    /// This is called once each frame, and you should draw the scene inside
    /// this function.
    void DrawUsingOpenGL();

    /// This is a little utility function that is helpful.  It treats the
    /// arrow keys like a joystick and returns the direction you are pressing
    /// as a 2D vector, taking into account the fact that you might be holding
    /// down more than one key at a time.
    Vector2 joystick_direction();

    // Feel free to add more functions here as needed.



private:

    // Simulation objects/parameters:

    // We suggest you start with the Car and Ball objects provided, adding new
    // member variables to those classes if you need to.  You'll probably want
    // to store some other data for the simulation here too, like some value
    // for gravity.
    Car car_;
    Ball ball_;
    Vector3 gravity_ = Vector3(0,-.15,0);
    float friction_ = .65;
    float max_car_velo = 75;

    int left_boundary_ = -40;
    int right_boundary_ = 38;
    int floor_ = 0;
    int ceiling_ = 35;
    int front_boundary_ = 48;
    int back_boundary_ = -50;

    bool game_start_;
    bool hand_brake_;


    // Support for drawing some simple shapes:
    QuickShapes quickShapes_;

    // Images to use as textures:
    Texture2D fieldTex_;
    Texture2D crowdTex_;

    // Control the computer graphics camera (we'll learn about this in a few weeks):
    Matrix4 modelMatrix_;
    Matrix4 viewMatrix_;
    Matrix4 projMatrix_;
    std::vector<Point3> goal_1_points;
    std::vector<Point3> goal_2_points;
    std::vector<Point3> boundary_points;

    // A list of paths to search for data files (images):
    std::vector<std::string> searchPath_;
};


#endif
