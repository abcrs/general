/**
 * @file GUI.cc
 *
 * @copyright 2019 5801 Team24, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include <iostream>
#include "src/GUI.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GUI::GUI(
    int width, int height) :
    GraphicsApp(
        width + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        height,
        "Voting System"),
    vote_sys_(nullptr),
    velocity_vector_(),
    xOffset_(0),
    nanogui_intialized_(false)
{
      xOffset_ = GUI_MENU_WIDTH + GUI_MENU_GAP;
}


void GUI::InitNanoGUI() {
  gui = new nanogui::FormHelper(screen());
  
  window =
    gui->addWindow(
		   // Eigen::Vector2i(window_width()
		   // - GUI_MENU_WIDTH - GUI_MENU_GAP * 2, 0),
		   Eigen::Vector2i(0, 0),
		   "Menu");
  window->setFixedWidth(GUI_MENU_WIDTH);
  window->setLayout(new nanogui::GroupLayout());
  
  // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // assigned to either the window or the panel.
  
  nanogui::Widget *panel = new nanogui::Widget(window);
  panel->setLayout(new nanogui::BoxLayout(
					  nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 0));
  
  // *************** Add GUI ************************//
  
  panel = new nanogui::Widget(window);
  panel->setLayout(new nanogui::BoxLayout(
					  nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 0));
  // Lays out all the components with "15" units of inbetween spacing
   panel->setLayout(new nanogui::BoxLayout(
					   nanogui::Orientation::Vertical,nanogui::Alignment::Middle, 0, 15));
  
  new nanogui::Label(window, "File", "sans-bold");
  open_button_ = gui->addButton("Open", std::bind(&GUI::OnOpenButtonPressed, this));
  save_button_ = gui->addButton("Audit File - Save as", std::bind(&GUI::OnSaveButtonPressed, this));
  screen()->performLayout();
  
  new nanogui::Label(window, "Output", "sans-bold");
  analysis_button_ = gui->addButton("Analysis CSV file", std::bind(&GUI::OnAnalysisButtonPressed, this));
  display_button_ = gui->addButton("Display Winners", std::bind(&GUI::OnDisplayWinnersPressed, this));
  media_button_ = gui->addButton("Output Media File", std::bind(&GUI::OnOutputMediaPressed, this));
  audit_button_ = gui->addButton("Output Default Audit File", std::bind(&GUI::OnOutputAuditPressed, this));
  screen()->performLayout();
  
  nanogui_intialized_ = true;
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GUI::OnOpenButtonPressed() {
  std::string fname = nanogui::file_dialog({{"csv", "Comma-Separated Values"}}, false);
  if (fname != "") {
    // vote_sys_->get_file_data_()->LoadFile(fname);
    char tmp[fname.length() + 1];
    strcpy(tmp, fname.c_str());
    delete vote_sys_;
    vote_sys_ = new Voting_System(tmp);
    // vote_sys_->LoadFile(fname); NOT YET IMPLEMENTED
   // File_Data* data = vote_sys_->get_file_data_();
  }
}

void GUI::OnSaveButtonPressed() {
  if (vote_sys_) {
    std::string fname = nanogui::file_dialog({{"txt", "Text"}}, true);
    if (fname != "") {
      vote_sys_->Audit_File(fname);
    }
  } else {
    printf("Action cannot be completed without a loaded file.\nPlease load a file.\n");
  }
}

void GUI::OnAnalysisButtonPressed() {
  
 if (vote_sys_ == NULL) {
   return;
 }
 File_Data *data = vote_sys_ ->get_file_data_();
 data = vote_sys_ ->get_file_data_();

 int num_seats = data->get_num_seats_();
 int num_ballots = data->get_num_ballots_();
 int num_cands = data->get_num_candidates_();
 int num_parties = data->get_num_parties_();
 char * voting_type = data->get_voting_type_();

 std::string voting_type_s = voting_type;
 std::string party_s;
 std::string candidate_s;

 gui->addWindow(Eigen::Vector2i(10, 10), "CSV file Information");
 gui->addVariable("Voting type", voting_type_s);
 gui->addVariable("Total Seat Number", num_seats,false);
 gui->addVariable("Total number of ballots", num_ballots,false);
 gui->addVariable("Total number of candidates", num_cands,false);
 gui->addGroup(" ");

 if (voting_type_s == "OPL") {
  Candidate_Data * candidates = data->get_candidates_();
  for(int i = 0; i < num_cands;i++) {
    party_s = candidates[i].party_;
    gui->addVariable("Party name ", party_s,false);
    candidate_s = candidates[i].name_;
    gui->addVariable("Candidate name ", candidate_s,false);
    gui->addVariable("Votes ", candidates[i].votes_,false);
    gui->addGroup(" ");
  }
  } else {
  Party_Data * parties = data->get_party_list_();
  for(int i = 0; i < num_parties; i++) {
  party_s = parties[i].name_;
    gui->addVariable("Party name ", party_s,false);
    gui->addVariable("Votes ", parties[i].votes_,false);
    for (int k = 0 ; k < parties[i].num_candidates_ ; k++) {
    candidate_s = parties[i].candidates_[k].name_;
      gui->addVariable("Candidate name ", candidate_s,false);
    }
    gui->addGroup(" ");
  }
  
}

screen()->performLayout();
}

void GUI::OnDisplayWinnersPressed() {
  if(vote_sys_) {
    vote_sys_->Display_Winners();
  } else {
    printf("Action cannot be completed without a loaded file.\nPlease load a file.\n");
  }
}

void GUI::OnOutputMediaPressed() {
  if(vote_sys_) {
    vote_sys_->Media_File();
  } else {
    printf("Action cannot be completed without a loaded file.\nPlease load a file.\n");
  }
}

void GUI::OnOutputAuditPressed() {
  if(vote_sys_) { 
    vote_sys_->Audit_File();
  } else {
    printf("Action cannot be completed without a loaded file.\nPlease load a file.\n");
  }
}
 
void GUI::SetVotingSystem(Voting_System *vote_sys) {
  // vote_sys_ = vote_sys;
  if (nanogui_intialized_) {
    InitNanoGUI();
  }
}



/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
/*
void GUI::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  std::cout << "Bar\n";
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
}
*/
bool GUI::RunViewer() {
  std::cout << "Sanz\n";
  return Run();
}
