#pragma once
#include "Walnut/Layer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include "imgui.h"
#include "imgui_internal.h"

#include "Walnut/Graphics/Framebuffer.h"
#include "Walnut/engine/graphics.h"

#include "Walnut/editor/SceneHelpers.h"

#include <string>
#include <sstream>
#include <utility>


class SceneLayer : public Walnut::Layer
{
public:
	SceneLayer();
	virtual void OnUpdate(float ts);
	virtual void OnUIRender() override;

private:
	void DoSceneEditBar();
	void DoNetworkInputWindow();
	void DoControlsWindow();
	void DoKeyWindow();
	std::pair<float, float> DoCalculateNetworkLatency();
	void DoToolTip(const char* tip);
	bool ImVec2IsInRect(ImVec2& vec, std::pair<ImVec2, ImVec2>& rect);
	std::string ImVec2ToString(ImVec2& vec);
	std::pair<ImVec2, ImVec2> GetScreenFill();
	std::pair<ImVec2, ImVec2> GetScreenMaintainAspectRatio();
private:
	
	Graphics* m_Graphics;
	Framebuffer* m_Framebuffer;

	float m_ScaleSlider = 1.0f;
	bool m_MaintainAspectRatio = true;
	bool m_FixedCam = true;

	ImVec2 m_FramebufferResolutionComboSelected;
	std::vector<ImVec2> m_FramebufferResolutionComboOptions;

	float m_PlayerSpeed;
	NetworkSettings m_PlayerSettings;
	NetworkSettings m_OtherSettings;

	float m_LastX;
	float m_LastY;
	int m_MouseWheel;
	bool m_IsSceneFocusedAndMouseInScene = false;
};