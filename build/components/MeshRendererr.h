#pragma once

class MeshRendererr
{
public:
  //unique_ptr<Mesh> mesh;
  Mesh mesh;
	//unique_ptr<ShaderProg> shader;
	ShaderProg shader;
	///////////////////////////////////////////////////////////
	bool enable_depth_test = false;
	GLenum depth_function = GL_LEQUAL;
	float clear_depth = 1.0f;
	bool depth_mask = true;
	glm::bvec4 color_mask = { true, true, true, true };
};

