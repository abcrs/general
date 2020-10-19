// Author: Philip Siedlecki, University of Minnesota
// Copyright 2018

#include "mia/command_line_processor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <list>

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

namespace image_tools {

void CommandLineProcessor::ProcessCommandLine(int num, char **cmd) {
  // Create a list of commands
  ExtractCommands(num, cmd);
  // take each command in the list and check that the individual
  if (CheckCommands()) {  // All commands are valid
    ExecuteCommands();
  }
}

bool CommandLineProcessor::IsFile(const char * buf) {
  const char * probe = buf;  // point to the start
  while (*probe != '\0') {
    probe++;
  }  // probe is now at the end of our input string
  // Check that the string is longer than 4 chars.
  if ((probe - buf) / sizeof(char) < 4) {
    return false;
  }
  probe -= 4;  // garbage.png_ -> garbage_.png (probe == _)
  return strcmp(probe, ".png") == 0;
}

bool CommandLineProcessor::IsFloat(const char * buf) {
  // all characters should be 0, 1, .. 9 or .
  // ascii range to check 48 = '0' -> 57 = '9', 46 = '.'
  const char * probe = buf;
  while (*probe != '\0') {  // check whole string
    if (*probe < 46 || *probe > 57 || *probe == 47) {
      return false;
    }
      probe++;
  }
  return true;
}

bool CommandLineProcessor::FileExists(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f != NULL) {
    fclose(f);
    return true;
  } else {
    return false;
  }
}

void CommandLineProcessor::ExtractCommands(int num, char **cmd) {
  int i = 1;
  int input_num = 0;  // num input values per command
  Command command;

  while (i < num) {
    if (cmd[i][0] == '-' || IsFile(cmd[i])) {
      // fresh command -command or _____.png
      if (i > 1) {  // push the previous command to the list
        command.num_args = input_num;
        command_list_.push_back(command);
      }
      snprintf(command.name, sizeof(char) * 255, "%s", cmd[i]);
      input_num = 0;
    } else if (IsFloat(cmd[i])) {
      // safe to convert to floating point value
      command.input[input_num] = strtof(cmd[i], NULL);
      input_num++;
    } else {
      std::cout << RED << "Unexpected input: " << RESET << cmd[i] << std::endl;
    }
    i++;
  }
  // push the last Commands
  command.num_args = input_num;
  command_list_.push_back(command);
}

void CommandLineProcessor::PrintCommands() {
  for (std::list<Command>::iterator it = command_list_.begin();
       it != command_list_.end(); it++) {
    std::cout << it->name << " ";
    for (int i = 0; i < it->num_args; i++) {
      printf("%.2f ", it->input[i]);
    }
  }
}

void CommandLineProcessor::PrintHelp() {
  printf("usage: mia infile.png [image processing commands...] ");
  printf("outfile.png\n\n");
  printf("infile.png:          input image in png format\n");
  printf("outfile.png:         filename to use for saving the result\n\n");
  printf("image processing commands:\n\n");
  printf("-blur r:             apply a gaussian blur of radius r\n");
  printf("-edgedetect:         apply an edge detection filter\n");
  printf("-sharpen r:          apply a sharpening filter of radius r\n");
  printf("-red s:              scale the red channel by a factor s\n");
  printf("-green s:            scale the green channel by a factor s\n");
  printf("-blue s:             scale the blue channel by a factor s\n");
  printf("-quantize n:         quantize each color channel into n bins\n");
  printf("-saturate s:         saturate colors by scale factor s\n");
  printf("-threshold c:        threshold using cutoff value c\n");
  printf("-motionblur-n-s r:   north-south motion blur with kernel radius r\n");
  printf("-motionblur-e-w r:   east-west motion blur with kernel radius r\n");
  printf("-motionblur-ne-sw r: ne-sw motion blur with kernel radius r\n");
  printf("-motionblur-nw-se r: nw-se motion blur with kernel radius r\n\n");
}

bool CommandLineProcessor::CheckCommands() {
  bool files_open = false;  // Is a file open
  bool cmd_edit;            // Is the command trying to edit an image?
  int exp_num_args;         // expected number of args a command takes
  bool ret = true;  // store return value, so we can print all usage mistakes

  for (std::list<Command>::iterator it = command_list_.begin();
       it != command_list_.end(); it++) {
    cmd_edit = false;
    exp_num_args = 1;
    if (strcmp(it->name, "-h") == 0) {
      PrintHelp();
      return false;  // Don't execute commands if the user asks for help
    } else if (strcmp(it->name, "-blur") == 0) {
      if (it->input[0] < 1 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -blur [1.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-edgedetect") == 0) {
      cmd_edit = true;
      exp_num_args = 0;
    } else if (strcmp(it->name, "-sharpen") == 0) {
      if (it->input[0] < 1 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -sharpen [1.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-red") == 0) {
      if (it->input[0] < 0 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -red [0.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-green") == 0) {
      if (it->input[0] < 0 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -green [0.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-blue") == 0) {
      if (it->input[0] < 0 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -blue [0.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-quantize") == 0) {
      if (it->input[0] < 1 || it->input[0] > 256) {
        printf(RED "ERROR:" RESET " -quantize [1 -> 256]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-saturate") == 0) {
      if (it->input[0] < 0 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -saturate [0.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-threshold") == 0) {
      if (it->input[0] < 0 || it->input[0] > 1) {
        printf(RED "ERROR:" RESET " -threshold [0.0 -> 1.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-motionblur-n-s") == 0) {
      if (it->input[0] < 1 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -motionblur [1.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-motionblur-e-w") == 0) {
      if (it->input[0] < 1 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -motionblur [1.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-motionblur-ne-sw") == 0) {
      if (it->input[0] < 1 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -motionblur [1.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-motionblur-nw-se") == 0) {
      if (it->input[0] < 1 || it->input[0] > 10) {
        printf(RED "ERROR:" RESET " -motionblur [1.0 -> 10.0]\n");
        return false;
      }
      cmd_edit = true;
    } else if (strcmp(it->name, "-Tool") == 0) {
      exp_num_args = 0;
    } else if (IsFile(it->name)) {
      exp_num_args = 0;
      // first file, need to check that it exists
      if (!files_open && !FileExists(it->name)) {
        // File does not exist
        printf(RED "ERROR:" RESET " %s does not exist\n", it->name);
        return false;
      }
      files_open = !files_open;
    } else {
      printf(RED "Invalid Command:" RESET " %s\n", it->name);
      exp_num_args = 0;
      ret = false;
    }
    if (!files_open && cmd_edit) {  // file is not open, can't edit image
      printf(RED "ERROR:" RESET " %s called without loading an image!\n",
             it->name);
      ret = false;
    }
    if (exp_num_args != it->num_args) {
      char temp[2];
      temp[1] = '\0';
      temp[0] = (exp_num_args == 1) ? '\0' : 's';
      printf(RED "Invalid Call:" RESET " %s takes %d argument%s!\n",
             it->name, exp_num_args, temp);
      ret = false;
    }
  }
  if (files_open) {
    printf(RED "ERROR:" RESET " Save image to a file!\n");
    return false;
  }
  return ret;
}

void CommandLineProcessor::ExecuteCommands() {
  bool files_open = false;  // Is a file open
  ImageEditor *image_editor = new ImageEditor();

  for (std::list<Command>::iterator it = command_list_.begin();
       it != command_list_.end(); it++) {
    if (strcmp(it->name, "-blur") == 0) {
      BlurFilterCommand blur_cmd = BlurFilterCommand(image_editor,
                                                     it->input[0]);
      blur_cmd.Execute();
    } else if (strcmp(it->name, "-edgedetect") == 0) {
      EdgeFilterCommand edge_cmd = EdgeFilterCommand(image_editor);
      edge_cmd.Execute();
    } else if (strcmp(it->name, "-sharpen") == 0) {
      SharpenFilterCommand sharpen_cmd =
        SharpenFilterCommand(image_editor, it->input[0]);
      sharpen_cmd.Execute();
    } else if (strcmp(it->name, "-red") == 0) {
      ChannelsFilterCommand channels_cmd =
        ChannelsFilterCommand(image_editor, it->input[0], 1.0, 1.0);
      channels_cmd.Execute();
    } else if (strcmp(it->name, "-green") == 0) {
      ChannelsFilterCommand channels_cmd =
        ChannelsFilterCommand(image_editor, 1.0, it->input[0], 1.0);
      channels_cmd.Execute();
    } else if (strcmp(it->name, "-blue") == 0) {
      ChannelsFilterCommand channels_cmd =
        ChannelsFilterCommand(image_editor, 1.0, 1.0, it->input[0]);
      channels_cmd.Execute();
    } else if (strcmp(it->name, "-quantize") == 0) {
      QuantizeFilterCommand quantize_cmd =
        QuantizeFilterCommand(image_editor, it->input[0]);
      quantize_cmd.Execute();
    } else if (strcmp(it->name, "-saturate") == 0) {
      SaturateFilterCommand saturate_cmd =
        SaturateFilterCommand(image_editor, it->input[0]);
      saturate_cmd.Execute();
    } else if (strcmp(it->name, "-threshold") == 0) {
      ThresholdFilterCommand threshold_cmd =
        ThresholdFilterCommand(image_editor, it->input[0]);
      threshold_cmd.Execute();
    } else if (strcmp(it->name, "-motionblur-n-s") == 0) {
      MotionBlurFilterCommand mblur_cmd =
        MotionBlurFilterCommand(image_editor, it->input[0],
                                ImageEditor::MBlurDir::MBLUR_DIR_N_S);
      mblur_cmd.Execute();
    } else if (strcmp(it->name, "-motionblur-e-w") == 0) {
      MotionBlurFilterCommand mblur_cmd =
        MotionBlurFilterCommand(image_editor, it->input[0],
                                ImageEditor::MBlurDir::MBLUR_DIR_E_W);
      mblur_cmd.Execute();
    } else if (strcmp(it->name, "-motionblur-ne-sw") == 0) {
      MotionBlurFilterCommand mblur_cmd =
        MotionBlurFilterCommand(image_editor, it->input[0],
                                ImageEditor::MBlurDir::MBLUR_DIR_NE_SW);
      mblur_cmd.Execute();
    } else if (strcmp(it->name, "-motionblur-nw-se") == 0) {
      MotionBlurFilterCommand mblur_cmd =
        MotionBlurFilterCommand(image_editor, it->input[0],
                                ImageEditor::MBlurDir::MBLUR_DIR_NW_SE);
      mblur_cmd.Execute();
    } else if (IsFile(it->name)) {
      std::string filename(it->name);  // convert char * -> string
      if (files_open) {  // Save the buffer to a file
        SaveCommand save_cmd = SaveCommand(image_editor, filename);
        save_cmd.Execute();
      } else {           // Load the buffer from a file
        LoadCommand load_cmd = LoadCommand(image_editor, filename);
        load_cmd.Execute();
      }
      files_open = !files_open;
    } else {  // The list should have already been checked
      printf("Invalid Command: %s\n", it->name);
      printf("Invalid use of ExecuteCommands(): \n");
      printf("validate commands prior to use\n");
      return;
    }
  }
  return;
}

}  // namespace image_tools
