/** CSci-4611 Assignment 3:  Earthquake
 */

#include "quake_app.h"
#include "config.h"

#include <iostream>
#include <sstream>

// Number of seconds in 1 year (approx.)
const int PLAYBACK_WINDOW = 12 * 28 * 24 * 60 * 60;

using namespace std;

QuakeApp::QuakeApp() : GraphicsApp(1280,720, "Earthquake"),
    playback_scale_(15000000.0), debug_mode_(false)
{
    // Define a search path for finding data files (images and earthquake db)
    search_path_.push_back(".");
    search_path_.push_back("./data");
    search_path_.push_back(DATA_DIR_INSTALL);
    search_path_.push_back(DATA_DIR_BUILD);

    quake_db_ = EarthquakeDatabase(Platform::FindFile("earthquakes.txt", search_path_));
    current_time_ = quake_db_.earthquake(quake_db_.min_index()).date().ToSeconds();

    mag_range_ = quake_db_.max_magnitude() - quake_db_.min_magnitude();

    // Initializing values to handle morphing from globe to sphere and back
    sphere_ = false;
    morphing_ = false;
    morph_step_ = 0.0;

    // Initializing value for size intensity of earthquakes
    size_intensity_ = .02;

    // Rotational speed to spin the globe
    rotation_ = 45.0;
 }


QuakeApp::~QuakeApp() {
}


void QuakeApp::InitNanoGUI() {
    // Setup the GUI window
    nanogui::Window *window = new nanogui::Window(screen(), "Earthquake Controls");
    window->setPosition(Eigen::Vector2i(10, 10));
    window->setSize(Eigen::Vector2i(400,200));
    window->setLayout(new nanogui::GroupLayout());

    date_label_ = new nanogui::Label(window, "Current Date: MM/DD/YYYY", "sans-bold");

    globe_btn_ = new nanogui::Button(window, "Globe");
    globe_btn_->setCallback(std::bind(&QuakeApp::OnGlobeBtnPressed, this));
    globe_btn_->setTooltip("Toggle between map and globe.");

    new nanogui::Label(window, "Playback Speed", "sans-bold");

    nanogui::Widget *panel = new nanogui::Widget(window);
    panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                            nanogui::Alignment::Middle, 0, 20));

    nanogui::Slider *slider = new nanogui::Slider(panel);
    slider->setValue(0.5f);
    slider->setFixedWidth(120);

    speed_box_ = new nanogui::TextBox(panel);
    speed_box_->setFixedSize(Eigen::Vector2i(60, 25));
    speed_box_->setValue("50");
    speed_box_->setUnits("%");
    slider->setCallback(std::bind(&QuakeApp::OnSliderUpdate, this, std::placeholders::_1));
    speed_box_->setFixedSize(Eigen::Vector2i(60,25));
    speed_box_->setFontSize(20);
    speed_box_->setAlignment(nanogui::TextBox::Alignment::Right);

    nanogui::Button* debug_btn = new nanogui::Button(window, "Toggle Debug Mode");
    debug_btn->setCallback(std::bind(&QuakeApp::OnDebugBtnPressed, this));
    debug_btn->setTooltip("Toggle displaying mesh triangles and normals (can be slow)");

    screen()->performLayout();
}

void QuakeApp::OnSpecialKeyDown(int key, int scancode, int modifiers) {
  if (key == GLFW_KEY_ESCAPE) {
    exit(0);
  }
  if (key == GLFW_KEY_SPACE) {
    sphere_ = !sphere_;
    morphing_ = true;
  }
  if (key == GLFW_KEY_ENTER) {
    debug_mode_ = !debug_mode_;
  }
}

void QuakeApp::OnLeftMouseDrag(const Point2 &pos, const Vector2 &delta) {
    // Optional: In our demo, we adjust the tilt of the globe here when the
    // mouse is dragged up/down on the screen.
}


void QuakeApp::OnGlobeBtnPressed() {
  sphere_ = !sphere_;
  morphing_ = true;
}

void QuakeApp::OnDebugBtnPressed() {
    debug_mode_ = !debug_mode_;
}

void QuakeApp::OnSliderUpdate(float value) {
    speed_box_->setValue(std::to_string((int) (value * 100)));
    playback_scale_ = 30000000.0*value;
}


void QuakeApp::UpdateSimulation(double dt)  {
    // Advance the current time and loop back to the start if time is past the last earthquake
    current_time_ += playback_scale_ * dt;
    if (current_time_ > quake_db_.earthquake(quake_db_.max_index()).date().ToSeconds()) {
        current_time_ = quake_db_.earthquake(quake_db_.min_index()).date().ToSeconds();
    }
    if (current_time_ < quake_db_.earthquake(quake_db_.min_index()).date().ToSeconds()) {
        current_time_ = quake_db_.earthquake(quake_db_.max_index()).date().ToSeconds();
    }

    Date d(current_time_);
    stringstream s;
    s << "Current date: " << d.month()
        << "/" << d.day()
        << "/" << d.year();
    date_label_->setCaption(s.str());

    // If morphing from one shape to the other
    // If a sphere already, move towards flat
    // If flat, move towards a sphere
    // Alpha for the Lerp function determined by morph steps
    // When the max steps are hit, stop morphing
    if (morphing_) {
      if (sphere_) {
        morph_step_+=dt;
      } else {
        morph_step_-=dt;
      }
      morph_step_ = GfxMath::Clamp(morph_step_, 0.0, 1.0);
      if (morph_step_ == 1.0 || morph_step_ == 0.0) {
        morphing_ = !morphing_;
        rotation_speed_ = 0.0;
      }
    }

    // After morph into sphere is finished, begin rotation
    if (sphere_ && !morphing_) {
      rotation_speed_ = rotation_speed_ + dt*rotation_;
    }
}


void QuakeApp::InitOpenGL() {
    // Set up the camera in a good position to see the entire earth in either mode
    proj_matrix_ = Matrix4::Perspective(60, aspect_ratio(), 0.1, 50);
    view_matrix_ = Matrix4::LookAt(Point3(0,0,3.5), Point3(0,0,0), Vector3(0,1,0));
    glClearColor(0.0, 0.0, 0.0, 1);

    // Initialize the earth object
    earth_.Init(search_path_);

    // Initialize the texture used for the background image
    stars_tex_.InitFromFile(Platform::FindFile("iss006e40544.png", search_path_));
}


void QuakeApp::DrawUsingOpenGL() {
    quick_shapes_.DrawFullscreenTexture(Color(1,1,1), stars_tex_);

    // You can leave this as the identity matrix and we will have a fine view of
    // the earth.  If you want to add any rotation or other animation of the
    // earth, the model_matrix is where you would apply that.
    Matrix4 model_matrix;
    Matrix4 Mrotate;
    if (sphere_ && !morphing_) {
      Mrotate = Matrix4::Rotation(Point3(0,0,0),Vector3(0,1,0),GfxMath::ToRadians(rotation_speed_));
    }

    // Draw the earth
    earth_.Draw(model_matrix * Mrotate, view_matrix_, proj_matrix_, morphing_, morph_step_);
    if (debug_mode_) {
        earth_.DrawDebugInfo(model_matrix, view_matrix_, proj_matrix_);
    }

    if (quake_db_.earthquake(quake_index_).date().SecondsUntil(Date(current_time_)) < 100) {
      visible_quakes_.push_back(quake_db_.earthquake(quake_index_));
      quake_index_++;
      //cout << quake_index_ << endl;
    }
    if ((Date(current_time_).ToSeconds() - visible_quakes_.front().date().ToSeconds()) > PLAYBACK_WINDOW) {
      visible_quakes_.erase(visible_quakes_.begin()+0);
    }
    for (Earthquake &quake : visible_quakes_) {
      // Determine location for earthquake
      // Lerp between flat and spherical locations if necessary
      Point3 location;
      if (!morphing_ && sphere_) {
        location = earth_.LatLongToSphere(quake.latitude(), quake.longitude() +  rotation_speed_);
        //location[0] = location[0] + GfxMath::ToRadians(rotation_speed_);
      } else if (!morphing_) {
        location = earth_.LatLongToPlane(quake.latitude(), quake.longitude());
      } else {
        Point3 location_sphere = earth_.LatLongToSphere(quake.latitude(), quake.longitude());
        Point3 location_flat = earth_.LatLongToPlane(quake.latitude(), quake.longitude());
        location = Point3::Lerp(location_flat, location_sphere, morph_step_);
      }

      // Determine scale (for color and size) of earthquake
      float scale = (quake.magnitude()-quake_db_.min_magnitude())/mag_range_;

      // Use scale to determine size and color of the sphere
      double size = size_intensity_+2*(scale/(1.0/size_intensity_));
      double green_color = GfxMath::Clamp(1.0-1.5*scale,0.0,1.0);
      // Draw the sphere
      Matrix4 Mquake = Matrix4::Translation(location - Point3(0,0,0)) * Matrix4::Scale(Vector3(size, size, size));
      quick_shapes_.DrawSphere(model_matrix * Mquake, view_matrix_, proj_matrix_, Color(1.0,green_color,0.0));
    }
}
