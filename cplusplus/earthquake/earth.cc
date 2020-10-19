/** CSci-4611 Assignment 3:  Earthquake
 */

#include "earth.h"
#include "config.h"

#include <vector>

// for M_PI constant
#define _USE_MATH_DEFINES
#include <math.h>


Earth::Earth() {
}

Earth::~Earth() {
}

void Earth::Init(const std::vector<std::string> &search_path) {
    // init shader program
    shader_.Init();

    // init texture: you can change to a lower-res texture here if needed
    earth_tex_.InitFromFile(Platform::FindFile("earth-2k.png", search_path));

    // init geometry
    const int nslices = 25;
    const int nstacks = 25;

    std::vector<unsigned int> indices;
    std::vector<Point2> texcoords;

    int i = 0;  // i acts as index tracker for index array assignment
    // Saving stacks and slices as doubles, for assigning vertices
    double nsl_doub = (double)nslices;
    double nst_doub = (double)nstacks;

    for (int y = 0; y <= nstacks; y++) {  // Outer loop iterates through stacks
      for (int x = 0; x <= nslices; x++) {  // Inner loop iterates through slices
        // Vertex array coordinates start at -pi, -pi/2, 0 and go to pi, pi/2, 0
        // Each step increases by (max - min) / total steps
        // Each dimension has its own step determined by slices (x) and stacks (y)
        // Create vertex array for both flat and spherical earth
        flat_vertices_.push_back(Point3(-M_PI + x * 2.0*M_PI/nsl_doub, -M_PI/2.0 + y * M_PI/nst_doub, 0));
        Point3 sphere_point = LatLongToSphere(-90 + y * 180.0/nst_doub, -180.0 + x * 360.0/nsl_doub);
        sphere_vertices_.push_back(sphere_point);
        // Fill with nothing to hold for later
        morphing_vertices_.push_back(Point3());

        // Texture Coordinates exist on the x,y plane
        // Range from 0 to 1 in both x and y dimensions
        // Start from "top right" (0,1) and step across to (1,1)
        // Then with each iteration of the loop step down in the y dimension
        // And repeat across, from (0,1-ystep) to (1,1-ystep)
        // Steps in each dimension determined by slices (x) and stacks (y)
        texcoords.push_back(Point2(x/nsl_doub, 1.0 - y/nst_doub));

        // Normals assigned for each form
        // flat surface normal points straight out
        flat_normals_.push_back(Vector3(0,0,1));
        // sphere normal points from origin to point on sphere
        sphere_normals_.push_back((sphere_point - Point3(0,0,0)).ToUnit());
        // Fill with nothing to hold for later
        morphing_normals_.push_back(Vector3());

        // Skip pushing vertices to the index array on last iteration
        // of inner loop and entire last iteration of outer loop
        if (x != nslices && y != nstacks) {
          // Numbers are pushed to the index array before they are assigned
          // But this is not a problem, because the mesh isn't updated until
          // all verices are made
          indices.push_back(i);
          indices.push_back(i+nslices+2);
          indices.push_back(i+nslices+1);

          indices.push_back(i);
          indices.push_back(i+1);
          indices.push_back(i+nslices+2);
        }
        i++;
      }
    }

    earth_mesh_.SetVertices(flat_vertices_);
    earth_mesh_.SetIndices(indices);
    earth_mesh_.SetTexCoords(0, texcoords);
    earth_mesh_.SetNormals(flat_normals_);
    earth_mesh_.UpdateGPUMemory();
}

void Earth::Draw(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix, bool morphing, double alpha_step) {
    // Define a really bright white light.  Lighting is a property of the "shader"
    DefaultShader::LightProperties light;
    light.position = Point3(10,10,10);
    light.ambient_intensity = Color(1,1,1);
    light.diffuse_intensity = Color(1,1,1);
    light.specular_intensity = Color(1,1,1);
    shader_.SetLight(0, light);

    // Adust the material properties, material is a property of the thing
    // (e.g., a mesh) that we draw with the shader.  The reflectance properties
    // affect the lighting.  The surface texture is the key for getting the
    // image of the earth to show up.
    DefaultShader::MaterialProperties mat;
    mat.ambient_reflectance = Color(0.5, 0.5, 0.5);
    mat.diffuse_reflectance = Color(0.75, 0.75, 0.75);
    mat.specular_reflectance = Color(0.75, 0.75, 0.75);
    mat.surface_texture = earth_tex_;

    // If morphing, move from one Vertex/Normal array set to the other
    // alpha_step tells which direction the morph should happen in
    // Otherwise, don't update the mesh and save time
    if (morphing) {
      for(int i = 0; i < morphing_vertices_.size(); i++) {
        morphing_vertices_.at(i) = Point3::Lerp(flat_vertices_.at(i), sphere_vertices_.at(i), alpha_step);
        morphing_normals_.at(i) = Vector3::Lerp(flat_normals_.at(i), sphere_normals_.at(i), alpha_step);
      }
      earth_mesh_.SetVertices(morphing_vertices_);
      earth_mesh_.SetNormals(morphing_normals_);
      earth_mesh_.UpdateGPUMemory();
    }

    // Draw the earth mesh using these settings
    if (earth_mesh_.num_triangles() > 0) {
        shader_.Draw(model_matrix, view_matrix, proj_matrix, &earth_mesh_, mat);
    }
}


Point3 Earth::LatLongToSphere(double latitude, double longitude) const {
    double lat = GfxMath::ToRadians(latitude);
    double lon = GfxMath::ToRadians(longitude);
    double x = cos(lat) * sin(lon);
    double y = sin(lat);
    double z = cos(lat) * cos(lon);
    return Point3(x, y, z);
}

Point3 Earth::LatLongToPlane(double latitude, double longitude) const {
    double lat = GfxMath::ToRadians(latitude);
    double lon = GfxMath::ToRadians(longitude);
    double x = cos(lon);
    double y = sin(lat);
    return Point3(x * M_PI, y * M_PI/2, 0);
}



void Earth::DrawDebugInfo(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // This draws a cylinder for each line segment on each edge of each triangle in your mesh.
    // So it will be very slow if you have a large mesh, but it's quite useful when you are
    // debugging your mesh code, especially if you start with a small mesh.
    for (int t=0; t<earth_mesh_.num_triangles(); t++) {
        std::vector<unsigned int> indices = earth_mesh_.triangle_vertices(t);
        std::vector<Point3> loop;
        loop.push_back(earth_mesh_.vertex(indices[0]));
        loop.push_back(earth_mesh_.vertex(indices[1]));
        loop.push_back(earth_mesh_.vertex(indices[2]));
        quick_shapes_.DrawLines(model_matrix, view_matrix, proj_matrix,
            Color(1,1,0), loop, QuickShapes::LinesType::LINE_LOOP, 0.005);
    }
}
