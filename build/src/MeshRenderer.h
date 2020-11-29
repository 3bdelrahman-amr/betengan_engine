#pragma once
#include"../common/mesh/mesh.hpp"
#include"../common/shader.hpp"
#include"transform.h"
#include"../common/camera/camera.hpp"
#include<vector>
using namespace our;
using namespace std;
class MeshRenderer
{
private:
	Camera* CameraPtr;
	vector<Transform>* trans;
/////////////////////
  Mesh *mesh;
  ShaderProgram *shader;
 
  ///////////////////////////////////////////////////////////
  bool enable_depth_test = false;
  GLenum depth_function = GL_LEQUAL;
  float clear_depth = 1.0f;
  bool depth_mask = true;
  glm::bvec4 color_mask = { true, true, true, true };
  ///////////////////////////////////////////////////////////////////
public:
	MeshRenderer();
	void init(Camera*);
	void Draw();
	void ImGui();
	auto get_pointer_To_trans_vector();
	auto get_begin_it();
	auto get_end_it();
	
	
	
	~MeshRenderer();


};

