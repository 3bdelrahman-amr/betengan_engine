#include "MeshRenderer.h"
#include"../common/mesh/mesh-utils.hpp"
#include"../common/imgui-utils/utils.hpp"

MeshRenderer::MeshRenderer()
{
	mesh = nullptr; 
	shader = nullptr;
	trans = nullptr;
	CameraPtr = nullptr;
}

void MeshRenderer::init(Camera* c)
{
	mesh = new Mesh;
	shader = new ShaderProgram;
	trans = new vector<Transform>;
	/////////////////////////////////////////////////////////////////////

	shader->create();
	shader->attach("../assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
	shader->attach("../assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
	//shader->attach("../assets/shaders/3Dheart.txt", GL_FRAGMENT_SHADER);
	shader->link();

	our::mesh_utils::Sphere(*mesh);
	// translation for every object rendered of the mesh in the space
	//trans->push_back({ {0,10,0}, {0,0,0}, {7,2,7} });
	//trans->push_back({ {-2,1,-2}, {0,0,0}, {2,2,2} });
	//trans->push_back({ {2,1,-2}, {0,0,0}, {2,2,2} });
	//trans->push_back({ {-2,1,2}, {0,0,0}, {2,2,2} });
	trans->push_back({ {2,1,2}, {0,0,0}, {2,2,2} });
	
	CameraPtr = c;


}

void MeshRenderer::Draw()
{
	if (enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
	glDepthFunc(depth_function);

	glClearDepth(clear_depth);

	glDepthMask(depth_mask);
	glColorMask(color_mask.r, color_mask.g, color_mask.b, color_mask.a);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(*shader);

	shader->set("tint", glm::vec4(1, 1, 1, 1));

	for (const auto& object : *trans)
	{
		shader->set("transform", CameraPtr->getVPMatrix() * object.to_mat4());
		mesh->draw();
	}

	//NOTE: Remember to reset the color mask such that ImGUI can draw
	glColorMask(true, true, true, true);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void MeshRenderer::ImGui()
{
	ImGui::Begin("Objects");

	our::ReorderableList(trans->begin(), trans->end(),
		[](size_t index, Transform& transform) {
			ImGui::DragFloat3("Translation", glm::value_ptr(transform.translation), 1.0f);
			ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
			ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
		}, [this](size_t index) {
			trans->insert(trans->begin() + index, Transform());
		}, [this](size_t index) {
			trans->erase(trans->begin() + index);
		});

	ImGui::End();

	ImGui::Begin("Controls");

	ImGui::Text("Depth Testing");

	ImGui::Checkbox("Enable Depth Testing", &enable_depth_test);
	our::OptionMapCombo("Comparison Function", depth_function, our::gl_enum_options::comparison_functions);

	ImGui::Separator();

	ImGui::Text("Extras");

	ImGui::DragFloat("Clear Depth Value", &clear_depth, 0.01f, 0.0f, 1.0f);
	ImGui::Checkbox("Depth Mask", &depth_mask);
	ImGui::Checkbox("Color Mask (Red)", &color_mask.r);
	ImGui::Checkbox("Color Mask (Green)", &color_mask.g);
	ImGui::Checkbox("Color Mask (Blue)", &color_mask.b);
	ImGui::Checkbox("Color Mask (Alpha)", &color_mask.a);

	ImGui::End();
}

auto MeshRenderer::get_pointer_To_trans_vector()
{
	return trans;
}

auto MeshRenderer::get_begin_it()
{
	return trans->begin();
}

auto MeshRenderer::get_end_it()
{
	return trans->end();
}


MeshRenderer::~MeshRenderer()
{
	delete mesh, delete shader, delete trans;
	
}
