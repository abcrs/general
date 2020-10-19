#include "animated_character.h"
#include "amc_util.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>


AnimatedCharacter::AnimatedCharacter(const std::string &asf_filename) :
    fps_(120.0), elapsed_since_last_frame_(0.0), current_frame_(0)
{
    LoadSkeleton(asf_filename);
}

AnimatedCharacter::AnimatedCharacter() :
    fps_(120.0), elapsed_since_last_frame_(0.0), current_frame_(0)
{
}

AnimatedCharacter::~AnimatedCharacter() {
}


void AnimatedCharacter::LoadSkeleton(const std::string &asf_filename) {
    skeleton_.LoadFromASF(asf_filename);
}


void AnimatedCharacter::Play(const MotionClip &motion_clip) {
    motion_queue_.clear();
    motion_queue_.push_back(motion_clip);
    current_frame_ = 0;
}


void AnimatedCharacter::Queue(const MotionClip &motion_clip) {
    if (motion_queue_.size() == 0) {
        Play(motion_clip);
    }
    else {
        motion_queue_.push_back(motion_clip);
    }
}


void AnimatedCharacter::ClearQueue() {
    motion_queue_.clear();
}


void AnimatedCharacter::OverlayClip(const MotionClip &clip, int num_transition_frames) {
    overlay_clip_ = clip;
    overlay_transition_frames_ = num_transition_frames;
    overlay_frame_ = 0;
}


void AnimatedCharacter::AdvanceAnimation(double dt) {
    if (motion_queue_.size() == 0) {
        pose_ = Pose();
    }
    else {
        elapsed_since_last_frame_ += dt;

        double frames_to_advance = fps_ * elapsed_since_last_frame_;
        double whole_frames;
        double frac = modf(frames_to_advance, &whole_frames);
        int nframes = (int)whole_frames;
        elapsed_since_last_frame_ = frac / fps_;

        for (int i=0; i<nframes; i++) {
            // advance the main motion track
            current_frame_++;
            // handle end case
            if (current_frame_ >= motion_queue_[0].size()) {
                // loop back to the first frame
                current_frame_ = 0;
                // if there are more motions in the queue then pop this one and goto the next
                if (motion_queue_.size() > 1) {
                    motion_queue_.erase(motion_queue_.begin());
                }
            }

            // advance the overlay clip if there is one
            if (overlay_clip_.size()) {
                overlay_frame_++;
                // handle end case
                if (overlay_frame_ >= overlay_clip_.size()) {
                    // done playing overlay, reset frame counter and clear the overlay clip
                    overlay_frame_ = 0;
                    overlay_clip_ = MotionClip();
                }
            }

            // update the pose based on new frames
            CalcCurrentPose();

            // add to the translation matrix for the case when relative root motion is used
            accum_translation_matrix_ = accum_translation_matrix_ * pose_.root_relative_translation();
        }
    }
}


void AnimatedCharacter::CalcCurrentPose() {
    if (!overlay_clip_.size()) {
        // no overaly track, motion is entirely from the base track (i.e., the motion queue)
        pose_ = motion_queue_[0][current_frame_];
    }
    else {
        // there is an active overlay track
        if (overlay_frame_ < overlay_transition_frames_) {
            // fade in the overlay
            float alpha = (float)overlay_frame_/(float)overlay_transition_frames_;
            pose_ = motion_queue_[0][current_frame_].Lerp(overlay_clip_[overlay_frame_], alpha);
        }
        else if (overlay_frame_ > overlay_clip_.size() - overlay_transition_frames_) {
            // fade out the overlay
            float alpha = (float)(overlay_clip_.size() - overlay_frame_)/(float)overlay_transition_frames_;
            pose_ = motion_queue_[0][current_frame_].Lerp(overlay_clip_[overlay_frame_], alpha);
        }
        else {
            // overlay is completely faded in, we don't see the base track at all
            pose_ = overlay_clip_[overlay_frame_];
        }
    }
}


Skeleton* AnimatedCharacter::skeleton_ptr() {
    return &skeleton_;
}


void AnimatedCharacter::set_fps(int fps) {
    fps_ = fps;
}


int AnimatedCharacter::fps() {
    return fps_;
}



void AnimatedCharacter::Draw(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix,
                             bool use_absolute_position)
{
    Matrix4 character_root_transform;
    if (use_absolute_position) {
        // set root position based on the absolute position in the mocap data
        character_root_transform = model_matrix * pose_.RootTransform();
    }
    else {
        // set root position based on the relative updates accumulated each frame
        character_root_transform = model_matrix * accum_translation_matrix_ * pose_.root_rotation();
    }

    for (int i=0; i<skeleton_.num_root_bones(); i++) {
        DrawBoneRecursive(skeleton_.root_bone(i), character_root_transform, view_matrix, proj_matrix);
    }
}


void AnimatedCharacter::DrawBoneRecursive(const std::string &bone_name, const Matrix4 &parent_transform,
                                          const Matrix4 &view_matrix, const Matrix4 &proj_matrix)
{
    // Here is a good way to check your work -- draw the coordinate axes for each
    // bone.  To start, this will just draw the axes for the root node of the
    // character, but once you add the recursive call to draw the children, this
    // will draw the axes for each bone.
    // Matrix4 S = Matrix4::Scale(Vector3(0.15,0.15,0.15));
    // quick_shapes_.DrawAxes(ctm * S, view_matrix, proj_matrix);
    // std::cout << bone_name << " - Bone direction and length: " << skeleton_.BoneDirectionAndLength(bone_name) << "\n";

    /**
    // Previous version of model used line segments
    // This portion of code is used to set values used to draw them
    Color c = Color(0, 0, 0);

    Point3 bone_end = Point3(skeleton_.BoneDirectionAndLength(bone_name)[0],
                            skeleton_.BoneDirectionAndLength(bone_name)[1],
                            skeleton_.BoneDirectionAndLength(bone_name)[2]);
    Point3 bone_start = Point3(0,0,0);

    float r = .0025;
    **/

    // Step 1:  Draw this bone
    Matrix4 ctm = parent_transform *
                  skeleton_.RotAxesSpaceToBoneSpace(bone_name) *
                  pose_.JointRotation(bone_name) *
                  skeleton_.BoneSpaceToRotAxesSpace(bone_name);

    // Set colors used in creating the clown
    Color yellow_color = Color(0.8, 0.7, 0.1);
    Color red_color = Color(0.9, 0.1, 0.1);
    Color white_color = Color(0.9, 0.9, 0.9);

    // Party time colors
    if (party_) {
      yellow_color = Color(1.0 - yellow_color[0], 1.0 - yellow_color[1], 1.0 - yellow_color[2]);
      red_color = Color(1.0 - red_color[0], 1.0 - red_color[1], 1.0 - red_color[2]);
      white_color = Color(1.0 - white_color[0], 1.0 - white_color[1], 1.0 - white_color[2]);
    }

    // Because the base model does not use as many bones and joints as this
    // skeleton, some of the bones/joints are not drawn. They are left in
    // should another model wish to be used, and to illustrate the lines if
    // desired. Also, because some of the left and right joints exist in
    // different real-world coordinates, they need to be split to be adjusted
    // separately.

    if (bone_name == "lhipjoint" || bone_name == "rhipjoint") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
    }
    if (bone_name == "lfemur") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 lfemur_scale = Matrix4::Scale(Vector3(0.075, 0.2, 0.075));
      Matrix4 lfemur_pos = Matrix4::Translation(Vector3(0, -0.18, 0));
      Matrix4 lfemur_rot = Matrix4::RotationZ(GfxMath::ToRadians(20.0));

      quick_shapes_.DrawSphere(ctm * lfemur_rot * lfemur_pos * lfemur_scale, view_matrix, proj_matrix, yellow_color);
    }
    if(bone_name == "rfemur") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 rfemur_scale = Matrix4::Scale(Vector3(0.075, 0.2, 0.075));
      Matrix4 rfemur_pos = Matrix4::Translation(Vector3(0, -0.18, 0));
      Matrix4 rfemur_rot = Matrix4::RotationZ(GfxMath::ToRadians(-20.0));

      quick_shapes_.DrawSphere(ctm * rfemur_rot * rfemur_pos * rfemur_scale, view_matrix, proj_matrix, yellow_color);
    }
    if (bone_name == "ltibia") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 ltibia_scale = Matrix4::Scale(Vector3(0.06, 0.18, 0.06));
      Matrix4 ltibia_pos = Matrix4::Translation(Vector3(0, -0.18, 0));
      Matrix4 ltibia_rot = Matrix4::RotationZ(GfxMath::ToRadians(20.0));

      quick_shapes_.DrawSphere(ctm * ltibia_rot * ltibia_pos * ltibia_scale, view_matrix, proj_matrix, yellow_color);
    }
    if(bone_name == "rtibia") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 rtibia_scale = Matrix4::Scale(Vector3(0.06, 0.18, 0.06));
      Matrix4 rtibia_pos = Matrix4::Translation(Vector3(0, -0.18, 0));
      Matrix4 rtibia_rot = Matrix4::RotationZ(GfxMath::ToRadians(-20.0));

      quick_shapes_.DrawSphere(ctm * rtibia_rot * rtibia_pos * rtibia_scale, view_matrix, proj_matrix, yellow_color);

    }
    if (bone_name == "lfoot" || bone_name == "rfoot") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 foot_scale = Matrix4::Scale(Vector3(0.06, 0.06, 0.08));

      Matrix4 heel_scale = Matrix4::Scale(Vector3(0.06, 0.06, 0.06));
      Matrix4 heel_pos = Matrix4::Translation(Vector3(0, 0.03, -0.12));

      quick_shapes_.DrawSphere(ctm * foot_scale, view_matrix, proj_matrix, red_color);
      quick_shapes_.DrawSphere(ctm * heel_pos * heel_scale, view_matrix, proj_matrix, red_color);
    }
    if (bone_name == "ltoes" || bone_name == "rtoes") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 toe_scale = Matrix4::Scale(Vector3(0.08, 0.08, 0.08));
      Matrix4 toe_pos = Matrix4::Translation(Vector3(0, 0.12, 0.075));

      quick_shapes_.DrawSphere(ctm * toe_scale, view_matrix, proj_matrix, red_color);
    }
    if (bone_name == "lowerback") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 belly_scale = Matrix4::Scale(Vector3(0.15, 0.2, 0.15));
      Matrix4 belly_pos = Matrix4::Translation(Vector3(0, 0.05, 0));

      Matrix4 belly_button_scale = Matrix4::Scale(Vector3(0.035, 0.035, 0.035));
      Matrix4 belly_button_pos = Matrix4::Translation(Vector3(0, 0.05, .18));

      quick_shapes_.DrawSphere(ctm * belly_pos * belly_scale, view_matrix, proj_matrix, yellow_color);
      quick_shapes_.DrawSphere(ctm * belly_button_pos * belly_button_scale, view_matrix, proj_matrix, red_color);
    }
    if (bone_name == "upperback") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
    }
    if (bone_name == "thorax") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 chest_scale = Matrix4::Scale(Vector3(0.12, 0.12, 0.12));
      Matrix4 chest_pos = Matrix4::Translation(Vector3(0, 0.08, 0));

      Matrix4 chest_button_scale = Matrix4::Scale(Vector3(0.035, 0.035, 0.035));
      Matrix4 chest_button_pos = Matrix4::Translation(Vector3(0, 0.08, 0.155));

      quick_shapes_.DrawSphere(ctm * chest_pos * chest_scale, view_matrix, proj_matrix, yellow_color);
      quick_shapes_.DrawSphere(ctm * chest_button_pos * chest_button_scale, view_matrix, proj_matrix, red_color);
    }
    if (bone_name == "lowerneck" || bone_name == "upperneck") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
    }
    if (bone_name == "head") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 head_scale = Matrix4::Scale(Vector3(0.1, 0.1, 0.1));

      // Set the values for the hat
      Matrix4 hat1_scale = Matrix4::Scale(Vector3(0.04, 0.04, 0.04));
      Matrix4 hat1_pos = Matrix4::Translation(Vector3(-0.02, 0.13, -0.025));

      Matrix4 hat2_scale = Matrix4::Scale(Vector3(0.02, 0.02, 0.02));
      Matrix4 hat2_pos = Matrix4::Translation(Vector3(-0.005, 0.165, -0.02));

      // Set the values for the nose
      Matrix4 nose_scale = Matrix4::Scale(Vector3(0.04, 0.04, 0.04));
      Matrix4 nose_pos = Matrix4::Translation(Vector3(0, 0, 0.1));

      // Draw the head, eyes, and mouth
      quick_shapes_.DrawSphere(ctm * head_scale, view_matrix, proj_matrix, white_color);
      quick_shapes_.DrawSphere(ctm * hat1_pos * hat1_scale, view_matrix, proj_matrix, red_color);
      quick_shapes_.DrawSphere(ctm * hat2_pos * hat2_scale, view_matrix, proj_matrix, white_color);
      quick_shapes_.DrawSphere(ctm * nose_pos * nose_scale, view_matrix, proj_matrix, red_color);

    }
    if (bone_name == "lclavicle") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 lclav_scale = Matrix4::Scale(Vector3(0.06, 0.06, 0.06));
      Matrix4 lclav_pos = Matrix4::Translation(Vector3(0.11, 0.05, 0));

      quick_shapes_.DrawSphere(ctm * lclav_pos * lclav_scale, view_matrix, proj_matrix, yellow_color);
    }
    if(bone_name == "rclavicle") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 rclav_scale = Matrix4::Scale(Vector3(0.06, 0.06, 0.06));
      Matrix4 rclav_pos = Matrix4::Translation(Vector3(-0.11, 0.05, 0));

      quick_shapes_.DrawSphere(ctm * rclav_pos * rclav_scale, view_matrix, proj_matrix, yellow_color);
    }
    if (bone_name == "lhumerus") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 lhumer_scale = Matrix4::Scale(Vector3(0.13, 0.065, 0.065));
      Matrix4 lhumer_pos = Matrix4::Translation(Vector3(0.11, 0, 0));

      quick_shapes_.DrawSphere(ctm * lhumer_pos * lhumer_scale, view_matrix, proj_matrix, yellow_color);
    }
    if(bone_name == "rhumerus") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 rhumer_scale = Matrix4::Scale(Vector3(0.13, 0.065, 0.065));
      Matrix4 rhumer_pos = Matrix4::Translation(Vector3(-0.11, 0, 0));

      quick_shapes_.DrawSphere(ctm * rhumer_pos * rhumer_scale, view_matrix, proj_matrix, yellow_color);
    }
    if(bone_name == "lradius") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 lradius_scale = Matrix4::Scale(Vector3(0.13, 0.065, 0.065));
      Matrix4 lradius_pos = Matrix4::Translation(Vector3(0.07, 0, 0));

      quick_shapes_.DrawSphere(ctm * lradius_pos * lradius_scale, view_matrix, proj_matrix, red_color);
    }
    if(bone_name == "rradius") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 rradius_scale = Matrix4::Scale(Vector3(0.13, 0.065, 0.065));
      Matrix4 rradius_pos = Matrix4::Translation(Vector3(-0.07, 0, 0));

      quick_shapes_.DrawSphere(ctm * rradius_pos * rradius_scale, view_matrix, proj_matrix, red_color);
    }
    if (bone_name == "lwrist" || bone_name == "rwrist") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
    }
    if (bone_name == "lhand") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 lhand_scale = Matrix4::Scale(Vector3(0.07, 0.07, 0.07));
      Matrix4 lhand_pos = Matrix4::Translation(Vector3(-0.01, 0, 0));

      quick_shapes_.DrawSphere(ctm * lhand_pos * lhand_scale, view_matrix, proj_matrix, white_color);
    }
    if(bone_name == "rhand") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
      Matrix4 rhand_scale = Matrix4::Scale(Vector3(0.07, 0.07, 0.07));
      Matrix4 rhand_pos = Matrix4::Translation(Vector3(0.01, 0, 0));

      quick_shapes_.DrawSphere(ctm * rhand_pos * rhand_scale, view_matrix, proj_matrix, white_color);
    }
    if(bone_name == "lthumb" || bone_name == "rthumb" || bone_name == "rfingers" || bone_name == "lfingers") {
      // quick_shapes_.DrawLineSegment(ctm, view_matrix, proj_matrix, c, bone_end, bone_start, r);
    }


    // Step 2: Draw the bone's children
    // The child_root_transform is the ctm matrix transformed by the matrix from
    // the BoneSpaceToChildrenSpace() function. Then, iteratively call this
    // function with each child of the current bone.
    Matrix4 child_root_transform = ctm * skeleton_.BoneSpaceToChildrenSpace(bone_name);
    for (int i=0; i<skeleton_.num_children(bone_name); i++) {
        DrawBoneRecursive(skeleton_.child_bone(bone_name, i), child_root_transform, view_matrix, proj_matrix);
    }
}
