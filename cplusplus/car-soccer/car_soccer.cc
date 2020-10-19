/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"
#include <stdlib.h>
#include <gfxmath.h>


CarSoccer::CarSoccer() : GraphicsApp(1024,768, "Car Soccer") {
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
}

CarSoccer::~CarSoccer() {
}


Vector2 CarSoccer::joystick_direction() {
    Vector2 dir;
    if (IsKeyDown(GLFW_KEY_LEFT))
        dir[0]--;
    if (IsKeyDown(GLFW_KEY_RIGHT))
        dir[0]++;
    if (IsKeyDown(GLFW_KEY_UP))
        dir[1]++;
    if (IsKeyDown(GLFW_KEY_DOWN))
        dir[1]--;
    return dir;
}


void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    if (key == GLFW_KEY_SPACE) {
      if (game_start_) {
        ball_.Reset();
        car_.Reset();
        game_start_ = false;
      } else {
        CarSoccer::LaunchBall();
        game_start_ = true;
      }
    }
    if (key == GLFW_KEY_ESCAPE) {
      exit(0);
    }
    if (key == GLFW_KEY_ENTER) {
      car_.set_velocity(Vector3());
      car_.set_speed(0.0f);
    }
    if (key == GLFW_KEY_RIGHT_CONTROL) {
      hand_brake_ = true;
    }
}

void CarSoccer::LaunchBall() {
  float init_velo_x = 1.0 * (rand() % 60 - 30);
  float init_velo_y = 1.0 * (rand() % 10 + 30);
  float init_velo_z = 1.0 * (rand() % 60 - 30);
  //std::cout << init_velo_x << " " << init_velo_y << " " << init_velo_z << std::endl;
  Vector3 v = Vector3(init_velo_x, init_velo_y, init_velo_z);
  //Vector3 v = Vector3(0,30,20);
  ball_.set_velocity(v);
}

void CarSoccer::UpdateSimulation(double timeStep) {
    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball as needed and checking for collisions.  Filling this routine
    // in is the main part of the assignment.
    if (game_start_) {
      CarSoccer::UpdateCar(timeStep);
      CarSoccer::UpdateBall(timeStep);
      CarSoccer::CheckBounce(timeStep);
    }
}

void CarSoccer::UpdateCar(double timeStep) {
  CarSoccer::UpdateCarVelocity(timeStep);
  CarSoccer::UpdateCarPosition(timeStep);
}

void CarSoccer::UpdateCarVelocity(double timeStep) {
  Vector2 car_velo_change = CarSoccer::joystick_direction();
  //Failed attempt at making car turn properly
  car_.set_angle(car_.angle() - car_velo_change[0]/100);
  car_.set_speed(car_.speed()-car_velo_change[1]/4);
  Vector3 direction = Vector3(-sin(car_.angle()), 0, -cos(car_.angle()));
  //std::cout << direction[0] << " " << direction[2] << std::endl;
  Vector3 magnitude = direction * car_.speed();
  Vector3 car_new_velo = Vector3((car_.velocity()[0]-magnitude[0])/2, 0, (car_.velocity()[2]-magnitude[2])/2);
  if (hand_brake_) {
    car_new_velo = car_new_velo * 0.1f;
    hand_brake_ = false;
  }
  if (abs(car_new_velo[0]) > max_car_velo) {
    if (car_new_velo[0] > 0) {
      car_new_velo[0] = max_car_velo;
    } else {
      car_new_velo[0] = -max_car_velo;
    }
  }
  if (abs(car_new_velo[2]) > max_car_velo) {
    if (car_new_velo[2] > 0) {
      car_new_velo[2] = max_car_velo;
    } else {
      car_new_velo[2] = -max_car_velo;
    }
  }
  car_.set_velocity(car_new_velo);
}

void CarSoccer::UpdateCarPosition(double timeStep) {
  Point3 car_new_pos = car_.position() + car_.velocity() * timeStep * friction_;
  if (car_new_pos[0]-car_.collision_radius() < left_boundary_) {
    car_new_pos[0] = left_boundary_+car_.collision_radius();
    car_.set_velocity(Vector3(-0.1*car_.velocity()[0],0,car_.velocity()[2]));
  }
  if (car_new_pos[0] > right_boundary_) {
    car_new_pos[0] = right_boundary_;
    car_.set_velocity(Vector3(-0.1*car_.velocity()[0],0,car_.velocity()[2]));
  }
  if (car_new_pos[2]-car_.collision_radius() < back_boundary_) {
    car_new_pos[2] = back_boundary_+car_.collision_radius();
    car_.set_velocity(Vector3(car_.velocity()[0],0,-0.1*car_.velocity()[2]));
  }
  if (car_new_pos[2] > front_boundary_-1) {
    car_new_pos[2] = front_boundary_-1;
    car_.set_velocity(Vector3(car_.velocity()[0],0,-0.1*car_.velocity()[2]));
  }
  car_.set_position(car_new_pos);
}

void CarSoccer::UpdateBall(double timeStep) {
  ball_.set_velocity(ball_.velocity() + gravity_);
  Point3 new_position = ball_.position() + ball_.velocity() * timeStep;
  if (new_position[1]-ball_.radius() < floor_) {
    CarSoccer::StaticBounceBall(timeStep, Vector3(0,1,0), 1, floor_);
  } else if (new_position[1]-ball_.radius() > ceiling_) {
    CarSoccer::StaticBounceBall(timeStep, Vector3(0,-1,0), 1, ceiling_);
  } else if (new_position[0]-ball_.radius() < left_boundary_) {
    CarSoccer::StaticBounceBall(timeStep, Vector3(1,0,0), 0, left_boundary_);
  } else if (new_position[0]-ball_.radius() > right_boundary_-3) {
    CarSoccer::StaticBounceBall(timeStep, Vector3(-1,0,0), 0, right_boundary_-3);
  } else if (new_position[2]-ball_.radius() < back_boundary_) {
    if (new_position[0] > -10 && new_position[0] < 10 && new_position[1] < 10) {
      ball_.Reset();
      car_.Reset();
      game_start_ = false;
    } else {
      CarSoccer::StaticBounceBall(timeStep, Vector3(0,0,1), 2, back_boundary_);
    }
  } else if (new_position[2]-ball_.radius() > front_boundary_-3) {
    if (new_position[0] > -10 && new_position[0] < 10 && new_position[1] < 10) {
      ball_.Reset();
      car_.Reset();
      game_start_ = false;
    } else {
      CarSoccer::StaticBounceBall(timeStep, Vector3(0,0,-1), 2, front_boundary_-3);
    }
  } else {
    ball_.set_position(new_position);
  }
}

void CarSoccer::StaticBounceBall(double timeStep, Vector3 normal, int direction, float location) {
  Vector3 reflect_velo = (ball_.velocity() - 2 * (ball_.velocity().Dot(normal)) * normal) * .85;
  double time_to_hit = (location-(ball_.position()[direction]-ball_.radius())) / ball_.velocity()[direction];
  double time_left = timeStep - time_to_hit;

  ball_.set_position(ball_.position() + ball_.velocity() * time_to_hit);
  ball_.set_position(ball_.position() + reflect_velo * time_left);

  ball_.set_velocity(reflect_velo);
}

void CarSoccer::CheckBounce(double timeStep) {
  Vector3 vector_between = Vector3(car_.position()[0] - ball_.position()[0],
                                     car_.position()[1] - ball_.position()[1],
                                     car_.position()[2] - ball_.position()[2]);
  float distance_between = vector_between.Length();
  if (distance_between <= ball_.radius() + car_.collision_radius()) {
    Vector3 relative_velo = ball_.velocity() - car_.velocity();
    Vector3 normal_between = Vector3::Normalize(vector_between);
    relative_velo = (relative_velo - 2 * (relative_velo.Dot(normal_between)) * normal_between) * .85;
    ball_.set_velocity(car_.velocity() + relative_velo);
  }
}

void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    viewMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));

    // Set a background color for the screen
    glClearColor(0.8,0.8,0.8, 1);

    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));

    // Boolean value that will start game and allow for resets
    game_start_ = false;

    // Boolean value to slow down the car
    hand_brake_ = false;

    // Create set of points for first goal drawing
    goal_1_points.push_back(Point3(-10,0,50));
    goal_1_points.push_back(Point3(-10,10,50));
    goal_1_points.push_back(Point3(10,10,50));
    goal_1_points.push_back(Point3(10,0,50));

    // Create set of points for second goal drawing
    goal_2_points.push_back(Point3(-10,0,-50));
    goal_2_points.push_back(Point3(-10,10,-50));
    goal_2_points.push_back(Point3(10,10,-50));
    goal_2_points.push_back(Point3(10,0,-50));

    // Create set of points for boundary drawing
    boundary_points.push_back(Point3(-40,35,-50));
    boundary_points.push_back(Point3(40,35,-50));
    boundary_points.push_back(Point3(40,35,50));
    boundary_points.push_back(Point3(-40,35,50));
    boundary_points.push_back(Point3(-40,35,-50));
    boundary_points.push_back(Point3(-40,0,-50));
    boundary_points.push_back(Point3(40,0,-50));
    boundary_points.push_back(Point3(40,0,50));
    boundary_points.push_back(Point3(-40,0,50));
    boundary_points.push_back(Point3(-40,0,-50));
}


void CarSoccer::DrawUsingOpenGL() {
    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);

    // Draw the field with the field texture on it.
    Color col(16.0/255.0, 46.0/255.0, 9.0/255.0);
    Matrix4 M = Matrix4::Translation(Vector3(0,-0.201,0)) * Matrix4::Scale(Vector3(50, 1, 60));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0,-0.2,0)) * Matrix4::Scale(Vector3(40, 1, 50));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, Color(1,1,1), fieldTex_);

    // Draw the car
    Color carcol(0.8, 0.2, 0.2);
    Matrix4 Mcar =
        Matrix4::Translation(car_.position() - Point3(0,0,0)) *
        Matrix4::RotationY(car_.angle()) *
        Matrix4::Scale(car_.size()) *
        Matrix4::Scale(Vector3(0.5,0.5,0.5));
    quickShapes_.DrawCube(modelMatrix_ * Mcar, viewMatrix_, projMatrix_, carcol);


    // Draw the ball
    Color ballcol(1,1,1);
    Matrix4 Mball =
        Matrix4::Translation(ball_.position() - Point3(0,0,0)) *
        Matrix4::Scale(Vector3(ball_.radius(), ball_.radius(), ball_.radius()));
    quickShapes_.DrawSphere(modelMatrix_ * Mball, viewMatrix_, projMatrix_, ballcol);


    // Draw the ball's shadow -- this is a bit of a hack, scaling Y by zero
    // flattens the sphere into a pancake, which we then draw just a bit
    // above the ground plane.
    Color shadowcol(0.2,0.4,0.15);
    Matrix4 Mshadow =
        Matrix4::Translation(Vector3(ball_.position()[0], -0.1, ball_.position()[2])) *
        Matrix4::Scale(Vector3(ball_.radius(), 0, ball_.radius())) *
        Matrix4::RotationX(90);
    quickShapes_.DrawSphere(modelMatrix_ * Mshadow, viewMatrix_, projMatrix_, shadowcol);


    // You should add drawing the goals and the boundary of the playing area
    // using quickShapes_.DrawLines()
    Color goal1col(1.0,1.0,0.0);
    Color goal2col(1.0,165.0/255.0,0.0);
    Color boundarycol(1.0,1.0,1.0,0.75);
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, goal1col, goal_1_points, QuickShapes::LinesType::LINE_STRIP, .25);
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, goal2col, goal_2_points, QuickShapes::LinesType::LINE_STRIP, .25);
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, boundarycol, boundary_points, QuickShapes::LinesType::LINE_STRIP, .05);
}
