#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>

#include "imgui.h"
#include "imgui_internal.h"

#include "Walnut/engine/graphics.h"
#include "Walnut/editor/SceneLayer.h"

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Desync Visualizer";
	Walnut::Application* app = new Walnut::Application(spec);

	app->PushLayer<SceneLayer>();

	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}