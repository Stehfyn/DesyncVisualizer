#include "SceneLayer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/matrix_decompose.hpp>


SceneLayer::SceneLayer() : Walnut::Layer()
{
	m_FramebufferResolutionComboOptions = { {3840, 2160}, {1920, 1080}, {1768, 992}, {1600, 900}, {1366, 768}, {1280, 720}, {1176, 664}, {1152, 648}, {1024, 576} };
	m_FramebufferResolutionComboSelected = m_FramebufferResolutionComboOptions.at(0);
	m_Graphics = new Graphics();

	FramebufferSpecification fbSpec{ m_FramebufferResolutionComboSelected.x, m_FramebufferResolutionComboSelected.y };
	m_Framebuffer = new Framebuffer(fbSpec);

	m_Framebuffer->Construct();
	m_Graphics->Initialize(m_FramebufferResolutionComboSelected.x, m_FramebufferResolutionComboSelected.y);

	m_MouseWheel = ImGui::GetIO().MouseWheel;

	m_PlayerSpeed = 3.0f;

	m_PlayerSettings.rttPlayer = 200.0f;
	m_PlayerSettings.rttOther = 200.0f;

	m_PlayerSettings.processingDelayMin = 0.0f;
	m_PlayerSettings.processingDelayMax = 1.0f;
	m_PlayerSettings.queuingDelayMin = 0.1f;
	m_PlayerSettings.queuingDelayMax = 1.0f;
	m_PlayerSettings.transmissionDelayMin = 0.1f;
	m_PlayerSettings.transmissionDelayMax = 1.0f;
	m_PlayerSettings.propagationDelayMin = 0.1f;
	m_PlayerSettings.propagationDelayMax = 1.0f;
	m_PlayerSettings.numHopsToServer = 10;

	m_OtherSettings.rttPlayer = 200.0f;
	m_OtherSettings.rttOther = 200.0f;

	m_OtherSettings.processingDelayMin = 0.1f;
	m_OtherSettings.processingDelayMax = 1.0f;
	m_OtherSettings.queuingDelayMin = 0.1f;
	m_OtherSettings.queuingDelayMax = 1.0f;
	m_OtherSettings.transmissionDelayMin = 0.1f;
	m_OtherSettings.transmissionDelayMax = 1.0f;
	m_OtherSettings.propagationDelayMin = 0.1f;
	m_OtherSettings.propagationDelayMax = 1.0f;
	m_OtherSettings.numHopsToServer = 10;
}

void SceneLayer::DoSceneEditBar()
{
	ImGui::PushItemWidth(120);
	
	//ImVec2 pos = ImGui::GetCursorPos();
	//ImVec2 avail = ImGui::GetWindowSize();
	//ImVec2 button_size = ImGui::CalcItemSize(ImVec2{ 150, 0 }, 0.0f, 0.0f);
	//ImVec2 centre_position_for_button{
	//	// we have two buttons, so twice the size - and we need to account for the spacing in the middle
	//	(avail.x - button_size.x * 2 - ImGui::GetStyle().ItemSpacing.x) / 2,
	//	pos.y
	//};
	//ImGui::SetCursorPos(centre_position_for_button);

	static int item_current_idx = 0;
	std::string combo_preview = ImVec2ToString(m_FramebufferResolutionComboSelected);
	if (ImGui::BeginCombo(" ", combo_preview.c_str(), 0))
	{
		for (int n = 0; n < m_FramebufferResolutionComboOptions.size(); n++)
		{
			const bool is_selected = (item_current_idx == n);
			std::string option = ImVec2ToString(m_FramebufferResolutionComboOptions.at(n));
			if (ImGui::Selectable(option.c_str(), is_selected))
			{
				item_current_idx = n;
				m_FramebufferResolutionComboSelected = m_FramebufferResolutionComboOptions.at(n);
			}
			if (is_selected) ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}
	ImGui::SameLine();
	ImGui::SliderFloat("Scale", &m_ScaleSlider, 0.0f, 5.0f, "%.3f", 0);

	ImGui::SameLine();
	ImGui::Checkbox("Maintain Aspect Ratio", &m_MaintainAspectRatio);

	ImGui::SameLine();
	ImGui::Checkbox("Fixed Cam", &m_FixedCam);

	ImGui::SameLine();
	ImGui::SliderFloat("Player Speed", &m_PlayerSpeed, 1.0f, 10.0f, "%.3f", 0);
}

void SceneLayer::DoNetworkInputWindow()
{
	std::pair<float, float> rtts = DoCalculateNetworkLatency();

	ImGui::Begin("Network Input (Player)");
	ImGui::PushItemWidth(120);
	//ImGui::SliderFloat("Server Tickrate (hz)", &m_NetworkSettings.tickrate, 1.0f, 30, "%.3f", 0);
	ImGui::Text("Player to Server");
	ImGui::Separator();
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 1.0f, 0.0f, .5f));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(.25, .25, .25, 1.0f));
	ImGui::Text("Processing Delay (ms)"); DoToolTip("In a packet switching-based network, the time it takes routers to process the packet header.");
	ImGui::SliderFloat("Min##1", &m_PlayerSettings.processingDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##1", &m_PlayerSettings.processingDelayMax, 0.1f, 1.0f);

	ImGui::Text("Queuing Delay (ms)"); DoToolTip("The time it takes a router to begin procesing a packet.");
	ImGui::SliderFloat("Min##2", &m_PlayerSettings.queuingDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##2", &m_PlayerSettings.queuingDelayMax, 0.1f, 1.0f);

	ImGui::Text("Transmission Delay (ms)");  DoToolTip("In a packet switching-based network, the amount of time required to push all bits of a packet onto the wire.");
	ImGui::SliderFloat("Min##3", &m_PlayerSettings.transmissionDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##3", &m_PlayerSettings.transmissionDelayMax, 0.1f, 1.0f);

	ImGui::Text("Propagation Delay (ms)"); DoToolTip("The time it takes for the head of a signal to travel and reach the receiver.");
	ImGui::SliderFloat("Min##4", &m_PlayerSettings.propagationDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##4", &m_PlayerSettings.propagationDelayMax, 0.1f, 1.0f);

	ImGui::Text("Number of Hops"); DoToolTip("The number of times a packet is switched on its' way to a destination.");
	ImGui::SliderInt("Hops##1", &m_PlayerSettings.numHopsToServer, 1, 100);

	ImGui::Text("RTT: %.3fms", rtts.first);
	ImGui::Text("Ping to Server: %.3fms", rtts.first / 2.0f);
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::End();

	ImGui::Begin("Network Input (Other)");

	ImGui::Text("Server to Other");
	ImGui::Separator();
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 1.0f, .5f));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(.25, .25, .25, 1.0f));
	ImGui::Text("Processing Delay (ms)"); DoToolTip("In a packet switching-based network, the time it takes routers to process the packet header.");
	ImGui::SliderFloat("Min##5", &m_OtherSettings.processingDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##5", &m_OtherSettings.processingDelayMax, 0.1f, 1.0f);

	ImGui::Text("Queuing Delay (ms)"); DoToolTip("The time it takes a router to begin procesing a packet.");
	ImGui::SliderFloat("Min##6", &m_OtherSettings.queuingDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##6", &m_OtherSettings.queuingDelayMax, 0.1f, 1.0f);

	ImGui::Text("Transmission Delay (ms)");  DoToolTip("In a packet switching-based network, the amount of time required to push all bits of a packet onto the wire.");
	ImGui::SliderFloat("Min##7", &m_OtherSettings.transmissionDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##7", &m_OtherSettings.transmissionDelayMax, 0.1f, 1.0f);

	ImGui::Text("Propagation Delay (ms)"); DoToolTip("The time it takes for the head of a signal to travel and reach the receiver.");
	ImGui::SliderFloat("Min##8", &m_OtherSettings.propagationDelayMin, 0.1f, 1.0f);
	ImGui::SliderFloat("Max##8", &m_OtherSettings.propagationDelayMax, 0.1f, 1.0f);

	ImGui::Text("Number of Hops"); DoToolTip("The number of times a packet is switched on its' way to a destination.");
	ImGui::SliderInt("Hops##2", &m_OtherSettings.numHopsToServer, 1, 100);

	ImGui::Text("RTT: %.3f ms", rtts.second);
	ImGui::Text("Ping to Server: %.3f ms", rtts.second/ 2.0f);
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::End();
}

void SceneLayer::DoControlsWindow()
{
	ImGui::Begin("Controls");
	ImGui::Text("Move Player: Arrow Keys");
	ImGui::Text("Zoom In: MouseWheel Up");
	ImGui::Text("Zoom Out: MouseWheel Down");
	ImGui::Text("Look (Free cam): Left Mouse Click + Mouse Drag");
	ImGui::Text("Move (Free cam): WASD");
	ImGui::End();
}

void SceneLayer::DoKeyWindow()
{
	ImGui::Begin("Simulation Key");
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	static float sz = 12.0f;
	static ImVec4 colP = ImVec4(1.0f, .0f, 0.0f, 1.0f);
	const ImU32 ucolP = ImColor(colP);
	static ImVec4 colS = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	const ImU32 ucolS = ImColor(colS);
	static ImVec4 colO = ImVec4(0.0f, .0f, 1.0f, 1.0f);
	const ImU32 ucolO = ImColor(colO);

	const ImDrawFlags corners_tl_br = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomRight;
	const float rounding = sz / 5.0f;
	const float spacing = 10.0f;
	ImVec2 p = ImGui::GetCursorScreenPos();
	float x = p.x + 4.0f;
	float y = p.y + 4.0f;
	draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), ucolP, 0.0f, ImDrawFlags_None, 3.0f);          x += sz + spacing;
	ImGui::Text("         Player"); DoToolTip("The player right now.");
	p = ImGui::GetCursorScreenPos();
	x = p.x + 4.0f;
	y = p.y + 4.0f;
	draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), ucolS, 0.0f, ImDrawFlags_None, 3.0f);		    x += sz + spacing;
	ImGui::Text("         Server"); DoToolTip("How the server sees the player right now.");
	p = ImGui::GetCursorScreenPos();
	x = p.x + 4.0f;
	y = p.y + 4.0f;
	draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), ucolO, 0.0f, ImDrawFlags_None, 3.0f);          x += sz + spacing;
	ImGui::Text("         Other"); DoToolTip("How some other client sees the player right now.");
	p = ImGui::GetCursorScreenPos();
	x = p.x + 4.0f;
	y = p.y + 4.0f;
	ImGui::End();
}

std::pair<float, float>SceneLayer::DoCalculateNetworkLatency()
{
	float rttPlayer_ = 0.0f;
	float rttOther_ = 0.0f;

	for (size_t i = 0; i < m_PlayerSettings.numHopsToServer; i++)
	{
		float processDelay = glm::linearRand(m_PlayerSettings.processingDelayMin, m_PlayerSettings.processingDelayMax);
		float queuingDelay = glm::linearRand(m_PlayerSettings.queuingDelayMin, m_PlayerSettings.queuingDelayMax);
		float transmissionDelay = glm::linearRand(m_PlayerSettings.transmissionDelayMin, m_PlayerSettings.transmissionDelayMax);
		float propagationDelay = glm::linearRand(m_PlayerSettings.propagationDelayMin, m_PlayerSettings.propagationDelayMax);

		float sum = processDelay + queuingDelay + transmissionDelay + propagationDelay;
		rttPlayer_ += sum;
	}
	for (size_t i = 0; i < m_OtherSettings.numHopsToServer; i++)
	{
		float processDelay = glm::linearRand(m_OtherSettings.processingDelayMin, m_OtherSettings.processingDelayMax);
		float queuingDelay = glm::linearRand(m_OtherSettings.queuingDelayMin, m_OtherSettings.queuingDelayMax);
		float transmissionDelay = glm::linearRand(m_OtherSettings.transmissionDelayMin, m_OtherSettings.transmissionDelayMax);
		float propagationDelay = glm::linearRand(m_OtherSettings.propagationDelayMin, m_OtherSettings.propagationDelayMax);

		float sum = processDelay + queuingDelay + transmissionDelay + propagationDelay;
		rttOther_ += sum;
	}
	rttPlayer_ *= 2;
	rttOther_ *= 2;
	m_PlayerSettings.rttPlayer = rttPlayer_;
	m_OtherSettings.rttOther = rttOther_;
	return {rttPlayer_, rttOther_};
}

void SceneLayer::DoToolTip(const char* tip)
{
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip(tip);
	}
}
void SceneLayer::OnUpdate(float ts)
{
	//m_SceneView->OnUpdate(ts);
	float playerSpeed = m_PlayerSpeed * ts;
	float camSpeed = 3.0f * ts;
	float camSensitivity = 45.0f * ts;

	auto* cam = m_Graphics->getCamera();
	auto* player = m_Graphics->getPlayer();
	auto input = ImGui::GetIO();

	//translation
	if (!m_FixedCam)
	{
		if (input.KeysDown[ImGuiKey_W])
			cam->pos += camSpeed * cam->forward;
		if (input.KeysDown[ImGuiKey_S])
			cam->pos -= camSpeed * cam->forward;
		if (input.KeysDown[ImGuiKey_A])
			cam->pos -= glm::normalize(glm::cross(cam->forward, cam->up)) * camSpeed;
		if (input.KeysDown[ImGuiKey_D])
			cam->pos += glm::normalize(glm::cross(cam->forward, cam->up)) * camSpeed;

		static bool init = true;
		if (m_IsSceneFocusedAndMouseInScene && input.MouseDown[0])
		{
			float x, y;
			x = input.MousePos.x;
			y = input.MousePos.y;

			if (init)
			{
				m_LastX = x;
				m_LastY = y;
				init = false;
			}

			ImVec2 delta(x - m_LastX, m_LastY - y);

			cam->yaw += delta.x * camSensitivity;
			cam->pitch += delta.y * camSensitivity;

			if (cam->pitch > 89.0f) cam->pitch = 89.0f;
			if (cam->pitch < -89.0f) cam->pitch = -89.0f;

			m_LastX = x;
			m_LastY = y;
		}
		else init = true;
	}
	else
	{
		//rotation
		static glm::mat4 cameraBasis = cam->GetView();
		glm::mat4 transformation;
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		cam->SetView(cameraBasis);
		glm::decompose(player->model, scale, rotation, translation, skew, perspective);
		cam->pos = translation;
		cam->pos += glm::vec3(0.0f, 5.0f, 0.0f);
		cam->yaw = -90.0f;
		cam->pitch = -89.0f;
	}

	//zoom
	if (m_MouseWheel);
	{
		cam->fov -= m_MouseWheel * 10;
		if (cam->fov >= 120.0f) cam->fov = 120.0f;
		if (cam->fov <= 10.0f) cam->fov = 10.0f;
	}

	

	if (input.KeysDown[ImGuiKey_LeftArrow])
		player->translation = glm::translate(player->translation, glm::vec3(-playerSpeed, 0.0f, 0.0f));
	if (input.KeysDown[ImGuiKey_RightArrow])
		player->translation = glm::translate(player->translation, glm::vec3(playerSpeed, 0.0f, 0.0f));
	if (input.KeysDown[ImGuiKey_UpArrow])
		player->translation = glm::translate(player->translation, glm::vec3(0.0f, 0.0f, -playerSpeed));
	if (input.KeysDown[ImGuiKey_DownArrow])
		player->translation = glm::translate(player->translation, glm::vec3(0.0f, 0.0f, playerSpeed));

	cam->Update(ts);
	m_Graphics->Update(ts,m_PlayerSettings.rttPlayer, m_OtherSettings.rttOther);
	//m_Graphics->Update2(ts, m_NetworkSettings);
}
void SceneLayer::OnUIRender()
{
	ImGuiWindowClass window_class;
	//window_class.DockingAllowUnclassed = true;
	window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverOther | ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
	ImGui::SetNextWindowClass(&window_class);

	ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav);
	{

		m_IsSceneFocusedAndMouseInScene = ImGui::IsWindowFocused(); //assume, then check
		
		//io mousehweel updates inside of imgui frame, and our layer update happens before imgui frame so we gotta cap input here
		m_MouseWheel = ImGui::GetIO().MouseWheel;
		ImVec2 mousePos = ImGui::GetIO().MousePos;

		DoSceneEditBar();
		DoNetworkInputWindow();
		DoControlsWindow();
		DoKeyWindow();
		ImVec2 avail = ImGui::GetContentRegionAvail();
		if (avail.x >= 0.0f && avail.y >= 0.0f)
		{
			
			m_Framebuffer->Destruct(); //for right now still storing rendered texture on gpu, so can only invalidate and destroy the fbo after imgui uses it (start of the next frame)
			m_Framebuffer->Construct();
			m_Framebuffer->Bind();

			m_Framebuffer->Resize(m_FramebufferResolutionComboSelected.x, m_FramebufferResolutionComboSelected.y);
			//don't like doing this here but works for now
			m_Framebuffer->Rescale(m_ScaleSlider);

			m_Graphics->Render();
			m_Framebuffer->Unbind();

			std::pair<ImVec2, ImVec2> window_coordinates;
			window_coordinates = (m_MaintainAspectRatio) ? GetScreenMaintainAspectRatio() : GetScreenFill();
			m_IsSceneFocusedAndMouseInScene = ImVec2IsInRect(mousePos, window_coordinates);

			//ImGui::GetWindowDrawList()->AddImage((void*)m_SceneView->GetFramebufferRendererID(), window_coordinates.first, window_coordinates.second, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::GetWindowDrawList()->AddImage((void*)m_Framebuffer->GetRendererID(), window_coordinates.first, window_coordinates.second, ImVec2(0, 1), ImVec2(1, 0));
		}
	}
	ImGui::End();
}
bool SceneLayer::ImVec2IsInRect(ImVec2& vec, std::pair<ImVec2, ImVec2>& rect)
{
	if (vec.x >= rect.first.x && vec.x <= rect.second.x)
		if (vec.y >= rect.first.y && vec.y <= rect.second.y)
			return true;
	return false;
}
std::string SceneLayer::ImVec2ToString(ImVec2& vec)
{
	std::stringstream conversion;
	conversion << vec.x << ", " << vec.y;
	return conversion.str();
}
std::pair<ImVec2, ImVec2> SceneLayer::GetScreenFill()
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 avail = ImGui::GetContentRegionAvail();

	ImVec2 filled;
	filled.x = pos.x + avail.x;
	filled.y = pos.y + avail.y;

	return { pos, filled };
}
std::pair<ImVec2, ImVec2> SceneLayer::GetScreenMaintainAspectRatio()
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 avail = ImGui::GetContentRegionAvail();

	ImVec2 aspected = avail;
	float aspect_ratio = m_FramebufferResolutionComboSelected.x / m_FramebufferResolutionComboSelected.y; //not asking actual framebuffer with a validated state, deffo refactor this guy
	aspected.y = aspected.x / aspect_ratio;
	float yOff = (avail.y - aspected.y) / 2;
	if (yOff >= 0.0f)
	{
		pos.y += yOff;
	}
	else
	{
		aspected = avail;
		aspected.x = aspected.y * aspect_ratio;
		float xOff = (avail.x - aspected.x) / 2;
		if (xOff >= 0.0f)
		{
			pos.x += xOff;
		}
	}
	aspected.x += pos.x;
	aspected.y += pos.y;

	return { pos, aspected };
}