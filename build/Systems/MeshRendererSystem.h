#ifndef RENDER_SYS
#define RENDER_SYS
#include"CameraSystem.h"
#endif // !RENDER_SYS


//#include"../src/Manager.h"
#include"../src/System.h"
#include"ComponentsDef.h"
#include"MeshSystem.h"
#include"ShaderSystem.h"

#include"../Systems/mesh-utils.hpp"
//extern class CameraSystem;
class MeshRendererSystem:public System
{
	
	Manager* mngr;
	ShaderSystem* ShdSys = nullptr;
	MeshSystem* MshSys = nullptr;
	CameraSystem* CmSys = nullptr;
public:
	///////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	MeshRendererSystem() {
		ShdSys =new ShaderSystem();
		MshSys = new MeshSystem();
		CmSys = new CameraSystem();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	void Set_Mngr_ptr(Manager*m) {
		mngr = m;
		CmSys->SetManger(m);
		MshSys->SetManger(m);
		//ShdSys->se

	}
	CameraSystem* get_cam_ptr() {
		return CmSys;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	void init(Entity e)
	{
		auto MeshRend = mngr->GetComponent<MeshRendererr>(e);
		/////////////////////////////////////////////////////////////////////

		ShdSys->create(e,mngr);
		ShdSys->attach("../assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER,e);
		ShdSys->attach("../assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER,e);
		//shader->attach("../assets/shaders/3Dheart.txt", GL_FRAGMENT_SHADER);
		ShdSys->link(e);

		Betengan::mesh_utils::Sphere( e,MshSys,MeshRend->mesh );
		//mngr->AddComponent(e, vector<Transform>);
		auto Trans = mngr->GetComponent<vector<Transform>>(e);
		// translation for every object rendered of the mesh in the space
		//trans->push_back({ {0,10,0}, {0,0,0}, {7,2,7} });
		//trans->push_back({ {-2,1,-2}, {0,0,0}, {2,2,2} });
		//trans->push_back({ {2,1,-2}, {0,0,0}, {2,2,2} });
		//trans->push_back({ {-2,1,2}, {0,0,0}, {2,2,2} });
		
		Trans->push_back({ {2,1,2}, {0,0,0}, {2,2,2} });
		//mngr->AddComponent(e, Trans);
		//CameraPtr = c;


	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	void Draw(double delta,Entity CameraEntity)
	{
		CmSys->update(delta,CameraEntity);
		auto CameraComp = mngr->GetComponent<Camera>(CameraEntity);
		
		for (const auto ent : Entities)
		{
			if (ent == 1)
				goto a1;
			auto MeshRend = mngr->GetComponent<MeshRendererr>(ent);
		
		if (MeshRend->enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
		glDepthFunc(MeshRend->depth_function);

		glClearDepth(MeshRend->clear_depth);

		glDepthMask(MeshRend->depth_mask);
		glColorMask(MeshRend->color_mask.r, MeshRend->color_mask.g, MeshRend->color_mask.b, MeshRend->color_mask.a);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(MeshRend->shader.program);

		ShdSys->set("tint", glm::vec4(1, 1, 1, 1), ent);                  //("tint", glm::vec4(1, 1, 1, 1));

		
			auto objects = mngr->GetComponent<vector<Transform>>(ent);
			for (auto object : *objects) {
				//auto cameracomp= mngr->GetComponent<vector<Transform>>(CameraEntity);
				ShdSys->set("transform", CmSys->getVPMatrix(CameraEntity) * object.to_mat4(), ent);
				MshSys->draw(ent);
				//ShdSys->link(ent);
			}
		}

		//NOTE: Remember to reset the color mask such that ImGUI can draw
		a1:glColorMask(true, true, true, true);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////
	void ImGui()
	{
		/*ImGui::Begin("Objects");

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

		ImGui::End();*/
	}



	
	


	/*~MeshRendererSystem()
	{
		delete mesh, delete shader, delete trans;

	}*/

};

