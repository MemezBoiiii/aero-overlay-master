#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>

#include <render/Device3D9.hpp>
#include <render/Surface3D9.hpp>

#include "../engine/EnfusionProcess.h"
#include "../engine/EnfusionEngine.h"

#include "../engine/Settings.h"

#define RGBA_TO_FLOAT(r,g,b,a) (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f

int realToIntegerPeterShirley(const double value) {
	return int(255.99 * value);
}

#define F2B(f) ((f) >= 1.0 ? 255 : (int)((f)*256.0))
int realToIntegerInkredibl(const double value) {
	return F2B(value);
}

const int realToIntegerMarkByers(const double value) {
	return std::floor(value >= 1.0 ? 255 : value * 256.0);
}

int realToIntegerToolmakerSteve(const double value) {
	return std::round(value * 255.0);
}

int realToIntegerErichKitzmueller(const double value) {
	return value * 255.999;
}

int realToInteger(const float value) {
	return realToIntegerInkredibl(value);
}

using namespace render;

//bool show_demo_window = true;
//bool show_another_window = false;
//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int windowstate = 0;
bool enabled = false;

//Overlay FPS
float flCurTick, flOldTick;
int iTempFPS, iRenderFPS;

int overlay_fps = 0;

void iGetFPS(int * fps) {

	flCurTick = clock() * 0.001f;
	iTempFPS++;
	if ((flCurTick - flOldTick) > 1.0f) {
		iRenderFPS = iTempFPS;

		iTempFPS = 0;
		flOldTick = flCurTick;
	}

	*(int *)fps = iRenderFPS;
}

void CustomImGUIStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(10, 10);
	style.FramePadding = ImVec2(1, 1);
	style.ItemSpacing = ImVec2(7, 7);
	style.ColumnsMinSpacing = 2.0f;
	style.ItemInnerSpacing = ImVec2(7, 7);
	style.WindowRounding = 0;
	style.FrameRounding = 0;
	style.TabRounding = 0;


	ImVec4* colors = style.Colors;
	colors[ImGuiCol_FrameBg] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.90f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(26 / 255.0f, 111 / 255.0f, 125 / 255.0f, 0.90f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.90f);

	colors[ImGuiCol_TitleBgActive] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.90f);
	colors[ImGuiCol_TitleBg] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.90f);

	colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 230 / 255.0f, 230 / 255.0f, 1.0f);

	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.26f, 0.26f, 0.50f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.50f);

	colors[ImGuiCol_Button] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.90f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(26 / 255.0f, 111 / 255.0f, 125 / 255.0f, 0.90f);
	colors[ImGuiCol_ButtonActive] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.90f);

	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.26f, 0.26f, 0.50f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.26f, 0.26f, 0.50f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.50f);

	colors[ImGuiCol_SeparatorHovered] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.70f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.70f);

	colors[ImGuiCol_ResizeGrip] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.95f);

	colors[ImGuiCol_Tab] = ImVec4(23 / 255.0f, 125 / 255.0f, 142 / 255.0f, 0.90f);
	colors[ImGuiCol_TabHovered] = ImVec4(26 / 255.0f, 111 / 255.0f, 125 / 255.0f, 0.90f);
	colors[ImGuiCol_TabActive] = ImVec4(23 / 255.0f, 140 / 255.0f, 142 / 255.0f, 0.25f);

	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);

	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.26f, 0.26f, 0.50f);
}

void ChangeClickability(bool canclick, HWND ownd)
{
	long style = GetWindowLong(
		ownd, GWL_EXSTYLE);
	if (canclick) {
		style &= ~WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		SetForegroundWindow(ownd);
		windowstate = 1;
	}
	else {
		style |= WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		windowstate = 0;
	}
}

Device3D9::~Device3D9()
{
    /// Call to a virtual function inside a destructor will be statically resolved
    DTOR_EXECUTE_VIRTUAL( shutdown );
}

bool Device3D9::create( const std::string& target_window_title )
{
    if( !Overlay::create( target_window_title ) ) {
        return false;
    }
    if( FAILED( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_Direct3D9Ex ) ) ) {
        return false;
    }
    
    D3DPRESENT_PARAMETERS params;
    ZeroMemory( &params, sizeof( D3DPRESENT_PARAMETERS ) );

    params.Windowed               = TRUE;
    params.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    params.BackBufferFormat       = D3DFMT_A8R8G8B8;
    params.EnableAutoDepthStencil = TRUE;
    params.AutoDepthStencilFormat = D3DFMT_D16;
    params.MultiSampleType        = D3DMULTISAMPLE_NONE;
    params.PresentationInterval   = 0x80000000L;

    DWORD mulit_sample_quality = 0;
    if( SUCCEEDED( this->m_Direct3D9Ex->CheckDeviceMultiSampleType(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        D3DFMT_A8R8G8B8,
        true,
        D3DMULTISAMPLE_NONMASKABLE,
        &mulit_sample_quality ) ) ) {
        params.MultiSampleType    = D3DMULTISAMPLE_NONMASKABLE;
        params.MultiSampleQuality = mulit_sample_quality - 1;
    }
    if( FAILED( m_Direct3D9Ex->CreateDeviceEx(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        m_WndOverlay,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &params,
        nullptr,
        &m_Direct3D9Device ) ) ) {
        return false;
    }

	D3DXCreateLine(m_Direct3D9Device, &m_Direct3D9Line);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	CustomImGUIStyle();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(m_WndOverlay);
	ImGui_ImplDX9_Init(m_Direct3D9Device);

    if( FAILED( D3DXCreateSprite( m_Direct3D9Device, &m_Direct3DXSprite ) ) ) {
        return false;
    }

    m_Surface = std::make_unique<Surface3D9>( m_Direct3DXSprite );
    return m_Surface->initialize( m_Direct3D9Device );
}

void UpdateUnits()
{
	while (true)
	{
		
		if (Settings::mem_speedhack)
		{
			if (GetAsyncKeyState(VK_LSHIFT)) {
				EnfusionEngine::SpeedHack(Settings::mem_speedhack_stephope);
				EnfusionEngine::RemoveGravity();
			}
		}

		if (GetAsyncKeyState(VK_MBUTTON)) {
			if(Settings::mem_delete_target_object){
				EnfusionEngine::DeleteTargetObject();
			}
		
			//EnfusionEngine::DestoryTargetObject();
		}


		if (Settings::tp_teleport_by_mapclick)
		{
			if (EnfusionEngine::IsMapOpen()) {
				if (GetAsyncKeyState(VK_RBUTTON)) {
					EnfusionEngine::SetPosition(EnfusionEngine::GetLocalPlayer(), EnfusionEngine::GetLastClickOnMapPosition());
					Settings::tp_teleport_on_coordinates_lastTpPosition = EnfusionEngine::GetLastClickOnMapPosition();
				}
			}
		}

		if (Settings::tp_teleport_by_cursor)
		{
			if (GetAsyncKeyState(VK_LCONTROL)) {
				EnfusionEngine::SetPosition(EnfusionEngine::GetLocalPlayer(), EnfusionEngine::GetCursorPosition());
			}
		}

		

		if (Settings::mem_without_fatigue)
		{
			EnfusionEngine::EnableStamina(FALSE);
		}

		if (Settings::mem_without_recoil)
		{
			EnfusionEngine::SetUnitRecoilCoefficient(0.0f);
		}
		else {
			EnfusionEngine::SetUnitRecoilCoefficient(1.0f);
		}

		if (Settings::mem_godmode)
		{
			EnfusionEngine::SecuredGodMode(TRUE);
		}
		else {
			EnfusionEngine::SecuredGodMode(FALSE);
		}

		if (Settings::mem_vehicle_godmode)
		{
			EnfusionEngine::SecuredVehicleGodMode(TRUE);
		}
		else {
			EnfusionEngine::SecuredVehicleGodMode(FALSE);
		}

		if (Settings::mem_player_invisible)
		{
			EnfusionEngine::InvisibleMode(TRUE);
		}
		else {
			EnfusionEngine::InvisibleMode(FALSE);
		}

		if (Settings::mem_without_gravity)
		{
			EnfusionEngine::RemoveGravity();
		}
		

		Sleep(1);
	}
}

bool tab_misc_character = true;
bool tab_misc_godmode = false;
bool tab_misc_speedhack = false;
bool tab_misc_objects = false;
bool tab_misc_vehpart = false;
bool tab_misc_other = false;

bool tab_visual_players = true;
bool tab_visual_ai = false;
bool tab_visual_cars = false;
bool tab_visual_air = false;
bool tab_visual_heli = false;
bool tab_visual_tanks = false;
bool tab_visual_ships = false;
bool tab_visual_items = false;
bool tab_visual_other = false;

bool tab_visual_color_players = true;
bool tab_visual_color_ai = false;
bool tab_visual_color_cars = false;
bool tab_visual_color_air = false;
bool tab_visual_color_heli = false;
bool tab_visual_color_tanks = false;
bool tab_visual_color_ships = false;
bool tab_visual_color_items = false;
bool tab_visual_color_other = false;

float _temp_tp_x = 0.0f;
float _temp_tp_y = 0.0f;
float _temp_tp_z = 0.0f;


bool Device3D9::render()
{
    /// handle window messages
    if( !Overlay::render() ) {
        return false;
    }

    if( FAILED( m_Direct3D9Device->Clear(
        0,
        nullptr,
        D3DCLEAR_TARGET,
        0x00000000,
        1.f,
        0 )
    ) ) {
        return false;        
    }
    /// start the surface scene only when the target window
    /// is in foreground
	if ( /*in_foreground()*/true) {


		if (GetAsyncKeyState(VK_INSERT) & 1) enabled = !enabled;

		if (enabled)
		{
			// Start the Dear ImGui frame
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGuiIO& io = ImGui::GetIO();
			io.IniFilename = "";

			if (windowstate != 1) //You might need to remove this check and call it every time to get keyboard input working. Mouse input works anyway.
			{
				ChangeClickability(true, m_WndOverlay);
			}

			ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

			ImGui::Begin(META_STRING("test menu"), &enabled, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

			/*fovcirle*/ 
				static ImVec4 color_fildofview = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::fildofview_cirle_r,
					Settings::Colors::fildofview_cirle_g,
					Settings::Colors::fildofview_cirle_b,
					255));
			

			/*player's*/ 
				static ImVec4 color_player_name = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::player_name_r,
					Settings::Colors::player_name_g,
					Settings::Colors::player_name_b,
					255));

				static ImVec4 color_player_box = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::player_box_r,
					Settings::Colors::player_box_g,
					Settings::Colors::player_box_b,
					255));

				static ImVec4 color_player_bone = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::player_bone_r,
					Settings::Colors::player_bone_g,
					Settings::Colors::player_bone_b,
					255));

				static ImVec4 color_player_dead = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::player_dead_r,
					Settings::Colors::player_dead_g,
					Settings::Colors::player_dead_b,
					255));

				static ImVec4 color_player_snapline = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::player_snapline_r,
					Settings::Colors::player_snapline_g,
					Settings::Colors::player_snapline_b,
					255));

				static ImVec4 color_player_stance = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::player_stance_r,
					Settings::Colors::player_stance_g,
					Settings::Colors::player_stance_b,
					255));
			

			/*npc's*/ 
				static ImVec4 color_ai_name = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ai_name_r,
					Settings::Colors::ai_name_g,
					Settings::Colors::ai_name_b,
					255));

				static ImVec4 color_ai_box = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ai_box_r,
					Settings::Colors::ai_box_g,
					Settings::Colors::ai_box_b,
					255));

				static ImVec4 color_ai_bone = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ai_bone_r,
					Settings::Colors::ai_bone_g,
					Settings::Colors::ai_bone_b,
					255));

				static ImVec4 color_ai_dead = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ai_dead_r,
					Settings::Colors::ai_dead_g,
					Settings::Colors::ai_dead_b,
					255));

				static ImVec4 color_ai_snapline = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ai_snapline_r,
					Settings::Colors::ai_snapline_g,
					Settings::Colors::ai_snapline_b,
					255));

				static ImVec4 color_ai_stance = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ai_stance_r,
					Settings::Colors::ai_stance_g,
					Settings::Colors::ai_stance_b,
					255));
			

			/*car's*/ 
				static ImVec4 color_car_name = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::car_name_r,
					Settings::Colors::car_name_g,
					Settings::Colors::car_name_b,
					255));

				static ImVec4 color_car_box = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::car_box_r,
					Settings::Colors::car_box_g,
					Settings::Colors::car_box_b,
					255));

				static ImVec4 color_car_destroyed = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::car_destroyed_r,
					Settings::Colors::car_destroyed_g,
					Settings::Colors::car_destroyed_b,
					255));

				static ImVec4 color_car_snapline = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::car_snapline_r,
					Settings::Colors::car_snapline_g,
					Settings::Colors::car_snapline_b,
					255));
			
			
			/*hellicopter's*/ 
				static ImVec4 color_hellicopter_name = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::hellicopter_name_r,
					Settings::Colors::hellicopter_name_g,
					Settings::Colors::hellicopter_name_b,
					255));

				static ImVec4 color_hellicopter_box = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::hellicopter_box_r,
					Settings::Colors::hellicopter_box_g,
					Settings::Colors::hellicopter_box_b,
					255));

				static ImVec4 color_hellicopter_destroyed = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::hellicopter_destroyed_r,
					Settings::Colors::hellicopter_destroyed_g,
					Settings::Colors::hellicopter_destroyed_b,
					255));

				static ImVec4 color_hellicopter_snapline = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::hellicopter_snapline_r,
					Settings::Colors::hellicopter_snapline_g,
					Settings::Colors::hellicopter_snapline_b,
					255));
			

			/*airplane's*/ 
				static ImVec4 color_airplane_name = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::airplane_name_r,
					Settings::Colors::airplane_name_g,
					Settings::Colors::airplane_name_b,
					255));

				static ImVec4 color_airplane_box = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::airplane_box_r,
					Settings::Colors::airplane_box_g,
					Settings::Colors::airplane_box_b,
					255));

				static ImVec4 color_airplane_destroyed = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::airplane_destroyed_r,
					Settings::Colors::airplane_destroyed_g,
					Settings::Colors::airplane_destroyed_b,
					255));

				static ImVec4 color_airplane_snapline = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::airplane_snapline_r,
					Settings::Colors::airplane_snapline_g,
					Settings::Colors::airplane_snapline_b,
					255));
			

			/*tank's*/ 
				static ImVec4 color_tank_name = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::tank_name_r,
					Settings::Colors::tank_name_g,
					Settings::Colors::tank_name_b,
					255));

				static ImVec4 color_tank_box = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::tank_box_r,
					Settings::Colors::tank_box_g,
					Settings::Colors::tank_box_b,
					255));

				static ImVec4 color_tank_destroyed = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::tank_destroyed_r,
					Settings::Colors::tank_destroyed_g,
					Settings::Colors::tank_destroyed_b,
					255));

				static ImVec4 color_tank_snapline = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::tank_snapline_r,
					Settings::Colors::tank_snapline_g,
					Settings::Colors::tank_snapline_b,
					255));
			

			/*ship's*/ 
				static ImVec4 color_ship_name = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ship_name_r,
					Settings::Colors::ship_name_g,
					Settings::Colors::ship_name_b,
					255));

				static ImVec4 color_ship_box = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ship_box_r,
					Settings::Colors::ship_box_g,
					Settings::Colors::ship_box_b,
					255));

				static ImVec4 color_ship_destroyed = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ship_destroyed_r,
					Settings::Colors::ship_destroyed_g,
					Settings::Colors::ship_destroyed_b,
					255));

				static ImVec4 color_ship_snapline = ImColor(RGBA_TO_FLOAT(
					Settings::Colors::ship_snapline_r,
					Settings::Colors::ship_snapline_g,
					Settings::Colors::ship_snapline_b,
					255));
			

			ImGui::BeginTabBar(META_STRING("Unitx for uc_uc_uc_uc"), ImGuiTabBarFlags_None);

			if (ImGui::BeginTabItem(META_STRING("visual"))) {

			
				ImGui::Columns(2, META_STRING("v_list"), true);
				ImGui::SetColumnWidth(0, 62.0f);

				if (ImGui::Button(META_STRING("players"))) {
					tab_visual_ai = false;
					tab_visual_cars = false;
					tab_visual_air = false;
					tab_visual_heli = false;
					tab_visual_tanks = false;
					tab_visual_ships = false;
					tab_visual_items = false;
					tab_visual_other = false;
					tab_visual_players = true;
				}

				if (ImGui::Button(META_STRING("  npc  "))) {
					tab_visual_players = false;
					tab_visual_cars = false;
					tab_visual_air = false;
					tab_visual_heli = false;
					tab_visual_tanks = false;
					tab_visual_ships = false;
					tab_visual_items = false;
					tab_visual_other = false;
					tab_visual_ai = true;
				}

				if (ImGui::Button(META_STRING(" cars  "))) {
					tab_visual_players = false;
					tab_visual_ai = false;
					tab_visual_air = false;
					tab_visual_heli = false;
					tab_visual_tanks = false;
					tab_visual_ships = false;
					tab_visual_items = false;
					tab_visual_other = false;

					tab_visual_cars = true;
				}

				if (ImGui::Button(META_STRING(" helli "))) {
					tab_visual_players = false;
					tab_visual_ai = false;
					tab_visual_cars = false;
					tab_visual_air = false;
					tab_visual_tanks = false;
					tab_visual_ships = false;
					tab_visual_items = false;
					tab_visual_other = false;

					tab_visual_heli = true;
				}

				if (ImGui::Button(META_STRING("airplan"))) {
					tab_visual_players = false;
					tab_visual_cars = false;
					tab_visual_ai = false;
					tab_visual_heli = false;
					tab_visual_tanks = false;
					tab_visual_ships = false;
					tab_visual_items = false;
					tab_visual_other = false;

					tab_visual_air = true;
				}

				if (ImGui::Button(META_STRING(" tanks "))) {
					tab_visual_players = false;
					tab_visual_ai = false;
					tab_visual_cars = false;
					tab_visual_air = false;
					tab_visual_heli = false;
					tab_visual_ships = false;
					tab_visual_items = false;
					tab_visual_other = false;

					tab_visual_tanks = true;
				}

				if (ImGui::Button(META_STRING(" ships "))) {
					tab_visual_players = false;
					tab_visual_ai = false;
					tab_visual_cars = false;
					tab_visual_air = false;
					tab_visual_heli = false;
					tab_visual_tanks = false;
					tab_visual_items = false;
					tab_visual_other = false;

					tab_visual_ships = true;
				}

				if (ImGui::Button(META_STRING(" items "))) {
					tab_visual_players = false;
					tab_visual_ai = false;
					tab_visual_cars = false;
					tab_visual_air = false;
					tab_visual_heli = false;
					tab_visual_tanks = false;
					tab_visual_ships = false;
					tab_visual_other = false;

					tab_visual_items = true;
				}

				if (ImGui::Button(META_STRING(" other "))) {
					tab_visual_players = false;
					tab_visual_ai = false;
					tab_visual_cars = false;
					tab_visual_air = false;
					tab_visual_heli = false;
					tab_visual_tanks = false;
					tab_visual_ships = false;
					tab_visual_items = false;

					tab_visual_other = true;
				}

				ImGui::NextColumn();

				if(tab_visual_players) {
					ImGui::Checkbox(META_STRING("Enable"), &Settings::esp_players);
					ImGui::Checkbox(META_STRING("box"), &Settings::esp_players_box);
					ImGui::Checkbox(META_STRING("name"), &Settings::esp_players_name);
					ImGui::Checkbox(META_STRING("health"), &Settings::esp_players_health);
					ImGui::Checkbox(META_STRING("dead"), &Settings::esp_players_isdead);
					ImGui::Checkbox(META_STRING("stance"), &Settings::esp_players_stance);
					ImGui::Checkbox(META_STRING("distance"), &Settings::esp_players_distance);
					ImGui::Checkbox(META_STRING("team"), &Settings::esp_players_team);
					ImGui::Checkbox(META_STRING("snapline"), &Settings::esp_players_snapline);
				}

				if (tab_visual_ai) {
					ImGui::Checkbox(META_STRING("box"), &Settings::esp_ai_box);
					ImGui::Checkbox(META_STRING("name"), &Settings::esp_ai_name);
					ImGui::Checkbox(META_STRING("health"), &Settings::esp_ai_health);
					ImGui::Checkbox(META_STRING("dead"), &Settings::esp_ai_isdead);
					ImGui::Checkbox(META_STRING("distance"), &Settings::esp_ai_distance);
					ImGui::Checkbox(META_STRING("team"), &Settings::esp_ai_team);
					ImGui::Checkbox(META_STRING("snapline"), &Settings::esp_ai_snapline);
				}

				if (tab_visual_cars) {
					ImGui::Checkbox(META_STRING("Enable"), &Settings::esp_vehicles);
					ImGui::Checkbox(META_STRING("box"), &Settings::esp_vehicles_box);
					ImGui::Checkbox(META_STRING("name"), &Settings::esp_vehicles_name);
					ImGui::Checkbox(META_STRING("health"), &Settings::esp_vehicles_health);
					ImGui::Checkbox(META_STRING("destroyed"), &Settings::esp_vehicles_isdestroyed);
					ImGui::Checkbox(META_STRING("distance"), &Settings::esp_vehicles_distance);
					ImGui::Checkbox(META_STRING("snapline"), &Settings::esp_vehicles_snapline);
				}

				if (tab_visual_heli) {
					ImGui::Checkbox(META_STRING("Enable"), &Settings::esp_hellicopters);
					ImGui::Checkbox(META_STRING("box"), &Settings::esp_hellicopters_box);
					ImGui::Checkbox(META_STRING("name"), &Settings::esp_hellicopters_name);
					ImGui::Checkbox(META_STRING("health"), &Settings::esp_hellicopters_health);
					ImGui::Checkbox(META_STRING("destroyed"), &Settings::esp_hellicopters_isdestroyed);
					ImGui::Checkbox(META_STRING("distance"), &Settings::esp_hellicopters_distance);
					ImGui::Checkbox(META_STRING("snapline"), &Settings::esp_hellicopters_snapline);
				}

				if (tab_visual_air) {
					ImGui::Checkbox(META_STRING("Enable"), &Settings::esp_airplanes);
					ImGui::Checkbox(META_STRING("box"), &Settings::esp_airplanes_box);
					ImGui::Checkbox(META_STRING("name"), &Settings::esp_airplanes_name);
					ImGui::Checkbox(META_STRING("health"), &Settings::esp_airplanes_health);
					ImGui::Checkbox(META_STRING("destroyed"), &Settings::esp_airplanes_isdestroyed);
					ImGui::Checkbox(META_STRING("distance"), &Settings::esp_airplanes_distance);
					ImGui::Checkbox(META_STRING("snapline"), &Settings::esp_airplanes_snapline);
				}

				if (tab_visual_tanks) {
					ImGui::Checkbox(META_STRING("Enable"), &Settings::esp_tanks);
					ImGui::Checkbox(META_STRING("box"), &Settings::esp_tanks_box);
					ImGui::Checkbox(META_STRING("name"), &Settings::esp_tanks_name);
					ImGui::Checkbox(META_STRING("health"), &Settings::esp_tanks_health);
					ImGui::Checkbox(META_STRING("destroyed"), &Settings::esp_tanks_isdestroyed);
					ImGui::Checkbox(META_STRING("distance"), &Settings::esp_tanks_distance);
					ImGui::Checkbox(META_STRING("snapline"), &Settings::esp_tanks_snapline);
				}


				if (tab_visual_ships) {
					ImGui::Checkbox(META_STRING("Enable"), &Settings::esp_ships);
					ImGui::Checkbox(META_STRING("box"), &Settings::esp_ships_box);
					ImGui::Checkbox(META_STRING("name"), &Settings::esp_ships_name);
					ImGui::Checkbox(META_STRING("health"), &Settings::esp_ships_health);
					ImGui::Checkbox(META_STRING("destroyed"), &Settings::esp_ships_isdestroyed);
					ImGui::Checkbox(META_STRING("distance"), &Settings::esp_ships_distance);
					ImGui::Checkbox(META_STRING("snapline"), &Settings::esp_ships_snapline);
				}
			
				ImGui::Columns(1);				
				ImGui::EndTabItem();
			}

			
			if (ImGui::BeginTabItem(META_STRING("almb0t"))) {
			
					ImGui::Columns(2, META_STRING("m_silent"), true);
					ImGui::SetColumnWidth(0, 62.0f);
					ImGui::Button(META_STRING("silent "));

					ImGui::NextColumn();
					ImGui::Checkbox(META_STRING("Enable"), &Settings::slim_silentaim);
					ImGui::Checkbox(META_STRING("field of view "), &Settings::slim_visual_fov);
					ImGui::SliderFloat(META_STRING("visual radius"), &Settings::slim_option_fov, 0.0f, 180.0f, META_STRING("%.0001f"));
					ImGui::Columns(1);
					ImGui::EndTabItem();
				
			}
			
			if (ImGui::BeginTabItem(META_STRING("teleport"))) {

				ImGui::Columns(2, META_STRING("m_teleport"), true);
				ImGui::SetColumnWidth(0, 62.0f);
				ImGui::Button(META_STRING("  tp   "));
				ImGui::NextColumn();

				ImGui::Checkbox(META_STRING("teleport to cursor"), &Settings::tp_teleport_by_cursor);
				ImGui::Checkbox(META_STRING("teleport to target"), &Settings::tp_teleport_to_target);
				ImGui::Checkbox(META_STRING("teleport on Map(click)"), &Settings::tp_teleport_by_mapclick);

					ImGui::InputFloat(META_STRING("x"), &_temp_tp_x);
					ImGui::InputFloat(META_STRING("y"), &_temp_tp_y);
					ImGui::InputFloat(META_STRING("z"), &_temp_tp_z);

					if (ImGui::Button(META_STRING("teleport character"))) {
						EnfusionEngine::SetPosition(EnfusionEngine::GetLocalPlayer(), Vector3(_temp_tp_x, _temp_tp_z, _temp_tp_y));
						Settings::tp_teleport_on_coordinates_lastTpPosition = Vector3(_temp_tp_x, _temp_tp_z, _temp_tp_y);
					} 
					
					ImGui::SameLine(); 

					if (ImGui::Button(META_STRING("teleport vehicle"))) {
						EnfusionEngine::SetPosition(EnfusionEngine::GetLocalPlayerVehicle(), Vector3(_temp_tp_x, _temp_tp_z, _temp_tp_y));
						Settings::tp_teleport_on_coordinates_lastTpPosition = Vector3(_temp_tp_x, _temp_tp_z, _temp_tp_y);
					}

					Vector3 LocalPlayerPosition = EnfusionEngine::GetPosition(EnfusionEngine::GetLocalPlayer(), TRUE);

					ImGui::Text(META_STRING("your current position (%0.1f,%0.1f,%0.1f)"),
						LocalPlayerPosition.x, 
						LocalPlayerPosition.z, 
						LocalPlayerPosition.y);

					ImGui::Text(META_STRING("last teleport position (%0.1f,%0.1f,%0.1f)"),
						Settings::tp_teleport_on_coordinates_lastTpPosition.x, 
						Settings::tp_teleport_on_coordinates_lastTpPosition.z,
						Settings::tp_teleport_on_coordinates_lastTpPosition.y);
				

				ImGui::Columns(1);
				ImGui::EndTabItem();
			}
			
			if (ImGui::BeginTabItem(META_STRING("misc"))) {

				ImGui::Columns(2, META_STRING("m_list"), true);
				ImGui::SetColumnWidth(0, 62.0f);

				if (ImGui::Button(META_STRING("charact"))) {
					tab_misc_godmode = false;
					tab_misc_speedhack = false;
					tab_misc_objects = false;
					tab_misc_vehpart = false;
					tab_misc_other = false;

					tab_misc_character = true;
				}

				if (ImGui::Button(META_STRING("g0dmode"))) {
					tab_misc_character = false;
					tab_misc_speedhack = false;
					tab_misc_objects = false;
					tab_misc_vehpart = false;
					tab_misc_other = false;

					tab_misc_godmode = true;
				}

				if (ImGui::Button(META_STRING("n0clip "))) {
					tab_misc_character = false;
					tab_misc_godmode = false;
					tab_misc_objects = false;
					tab_misc_vehpart = false;
					tab_misc_other = false;

					tab_misc_speedhack = true;
				}

				if (ImGui::Button(META_STRING("objects"))) {
					tab_misc_character = false;
					tab_misc_godmode = false;
					tab_misc_speedhack = false;
					tab_misc_vehpart = false;
					tab_misc_other = false;

					tab_misc_objects = true;
				}

				if (ImGui::Button(META_STRING("vehicle"))) {
					tab_misc_character = false;
					tab_misc_godmode = false;
					tab_misc_speedhack = false;
					tab_misc_objects = false;
					tab_misc_other = false;

					tab_misc_vehpart = true;
				}

				if (ImGui::Button(META_STRING(" other "))) {
					tab_misc_character = false;
					tab_misc_godmode = false;
					tab_misc_speedhack = false;
					tab_misc_objects = false;
					tab_misc_vehpart = false;

					tab_misc_other = true;
				}

				ImGui::NextColumn();

				if (tab_misc_character) {
					ImGui::Checkbox(META_STRING("no fatigue"), &Settings::mem_without_fatigue);
					ImGui::Checkbox(META_STRING("no recoil"), &Settings::mem_without_recoil);
					ImGui::Checkbox(META_STRING("no gravity"), &Settings::mem_without_gravity);
					ImGui::Checkbox(META_STRING("invisible"), &Settings::mem_player_invisible);
					if (ImGui::Button(META_STRING("heal character"))) {
						EnfusionEngine::HealYourself();
					}		
				}

				if (tab_misc_godmode) {
					ImGui::Checkbox(META_STRING("character g0dmode"), &Settings::mem_godmode);
					ImGui::Checkbox(META_STRING("vehicle g0dmode"), &Settings::mem_vehicle_godmode);
				}

				if (tab_misc_speedhack) {
					ImGui::Checkbox(META_STRING("n0clip"), &Settings::mem_speedhack);
					ImGui::SliderFloat(META_STRING("stephop"), &Settings::mem_speedhack_stephope, 0.0f, 5.0f, META_STRING("%.01f"));
					if (Settings::mem_speedhack)
					{
						ImGui::TextColored(ImVec4(0.0f, 230 / 255.0f, 230 / 255.0f, 1.0f), "Do not forget about godmode\nif you are going to fly :)");
					}
				}

				if (tab_misc_objects) {

					const char* items[] = { 
						"Mouse Midle",
						"Mouse 3", 
						"Mouse 4",
						"Mouse 5",
						"Mouse 6" 
					};

					static int item_current = 0;
	
					ImGui::Checkbox(META_STRING("delete target objects"), &Settings::mem_delete_target_object);
					ImGui::Checkbox(META_STRING("destroy target objects"), &Settings::mem_flyhack);
					ImGui::Combo(META_STRING("select key"), &item_current, items, IM_ARRAYSIZE(items));
					if (ImGui::Button(META_STRING("restore all deleted objects"))) {
						EnfusionEngine::RestoreAllDeletedObjects();
					}
				}

				if(tab_misc_vehpart) {

					ImGui::Checkbox(META_STRING("auto unlock near vehicle"), &Settings::mem_vehicle_autounlock);

					if (ImGui::Button(META_STRING("refuel vehicle"))) {
						EnfusionEngine::ForceRefuelVehicle();
					}
					if (ImGui::Button(META_STRING("repair vehicle"))) {
						EnfusionEngine::ForceRepairVehicle();
					}

				}

				ImGui::Columns(1);
				ImGui::EndTabItem();
			}
			

			if (ImGui::BeginTabItem(META_STRING("colors"))) {

				ImGui::Columns(2, META_STRING("v_color_list"), true);
				ImGui::SetColumnWidth(0, 62.0f);

				if (ImGui::Button(META_STRING("players "))) {
					tab_visual_color_ai = false;
					tab_visual_color_cars = false;
					tab_visual_color_air = false;
					tab_visual_color_heli = false;
					tab_visual_color_tanks = false;
					tab_visual_color_ships = false;
					tab_visual_color_items = false;
					tab_visual_color_other = false;

					tab_visual_color_players = true;
				}

				if (ImGui::Button(META_STRING("  npc   "))) {
					tab_visual_color_players = false;
					tab_visual_color_cars = false;
					tab_visual_color_air = false;
					tab_visual_color_heli = false;
					tab_visual_color_tanks = false;
					tab_visual_color_ships = false;
					tab_visual_color_items = false;
					tab_visual_color_other = false;

					tab_visual_color_ai = true;
				}

				if (ImGui::Button(META_STRING("	 cars  "))) {
					tab_visual_color_players = false;
					tab_visual_color_ai = false;
					tab_visual_color_air = false;
					tab_visual_color_heli = false;
					tab_visual_color_tanks = false;
					tab_visual_color_ships = false;
					tab_visual_color_items = false;
					tab_visual_color_other = false;

					tab_visual_color_cars = true;
				}

				if (ImGui::Button(META_STRING("hellicop"))) {
					tab_visual_color_players = false;
					tab_visual_color_cars = false;
					tab_visual_color_air = false;
					tab_visual_color_tanks = false;
					tab_visual_color_ships = false;
					tab_visual_color_items = false;
					tab_visual_color_other = false;

					tab_visual_color_heli = true;
				}

				if (ImGui::Button(META_STRING("airplane"))) {
					tab_visual_color_players = false;
					tab_visual_color_cars = false;
					tab_visual_color_heli = false;
					tab_visual_color_tanks = false;
					tab_visual_color_ships = false;
					tab_visual_color_items = false;
					tab_visual_color_other = false;

					tab_visual_color_air = true;
				}

				if (ImGui::Button(META_STRING(" tanks  "))) {
					tab_visual_color_players = false;
					tab_visual_color_ai = false;
					tab_visual_color_cars = false;
					tab_visual_color_air = false;
					tab_visual_color_heli = false;
					tab_visual_color_ships = false;
					tab_visual_color_items = false;
					tab_visual_color_other = false;

					tab_visual_color_tanks = true;
				}

				if (ImGui::Button(META_STRING(" ships  "))) {
					tab_visual_color_players = false;
					tab_visual_color_ai = false;
					tab_visual_color_cars = false;
					tab_visual_color_air = false;
					tab_visual_color_heli = false;
					tab_visual_color_tanks = false;
					tab_visual_color_items = false;
					tab_visual_color_other = false;

					tab_visual_color_ships = true;
				}

				if (ImGui::Button(META_STRING(" items  "))) {
					tab_visual_color_players = false;
					tab_visual_color_ai = false;
					tab_visual_color_cars = false;
					tab_visual_color_air = false;
					tab_visual_color_heli = false;
					tab_visual_color_tanks = false;
					tab_visual_color_ships = false;
					tab_visual_color_other = false;

					tab_visual_color_items = true;
				}

				if (ImGui::Button(META_STRING(" other  "))) {
					tab_visual_color_players = false;
					tab_visual_color_ai = false;
					tab_visual_color_cars = false;
					tab_visual_color_air = false;
					tab_visual_color_heli = false;
					tab_visual_color_tanks = false;
					tab_visual_color_ships = false;
					tab_visual_color_items = false;

					tab_visual_color_other = true;
				}

				ImGui::NextColumn();

				if (tab_visual_color_players) {

					ImGui::Text(META_STRING("name")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("player name"), (float*)&color_player_name, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::player_name_r = realToInteger(color_player_name.x);
					Settings::Colors::player_name_g = realToInteger(color_player_name.y);
					Settings::Colors::player_name_b = realToInteger(color_player_name.z);

					ImGui::Text(META_STRING("box")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("player box"), (float*)&color_player_box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::player_box_r = realToInteger(color_player_box.x);
					Settings::Colors::player_box_g = realToInteger(color_player_box.y);
					Settings::Colors::player_box_b = realToInteger(color_player_box.z);

					ImGui::Text(META_STRING("bones")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("player bones"), (float*)&color_player_bone, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::player_bone_r = realToInteger(color_player_bone.x);
					Settings::Colors::player_bone_g = realToInteger(color_player_bone.y);
					Settings::Colors::player_bone_b = realToInteger(color_player_bone.z);

					ImGui::Text(META_STRING("dead")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("player dead"), (float*)&color_player_dead, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::player_dead_r = realToInteger(color_player_dead.x);
					Settings::Colors::player_dead_g = realToInteger(color_player_dead.y);
					Settings::Colors::player_dead_b = realToInteger(color_player_dead.z);

					ImGui::Text(META_STRING("stance")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("player stance"), (float*)&color_player_stance, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::player_stance_r = realToInteger(color_player_stance.x);
					Settings::Colors::player_stance_g = realToInteger(color_player_stance.y);
					Settings::Colors::player_stance_b = realToInteger(color_player_stance.z);

					ImGui::Text(META_STRING("snapline")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("player snapline"), (float*)&color_player_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::player_snapline_r = realToInteger(color_player_snapline.x);
					Settings::Colors::player_snapline_g = realToInteger(color_player_snapline.y);
					Settings::Colors::player_snapline_b = realToInteger(color_player_snapline.z);

				}

				if (tab_visual_color_ai) {
					ImGui::Text(META_STRING("name")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("npc name"), (float*)&color_ai_name, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ai_name_r = realToInteger(color_ai_name.x);
					Settings::Colors::ai_name_g = realToInteger(color_ai_name.y);
					Settings::Colors::ai_name_b = realToInteger(color_ai_name.z);

					ImGui::Text(META_STRING("box")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("npc box"), (float*)&color_ai_box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ai_box_r = realToInteger(color_ai_box.x);
					Settings::Colors::ai_box_g = realToInteger(color_ai_box.y);
					Settings::Colors::ai_box_b = realToInteger(color_ai_box.z);

					ImGui::Text(META_STRING("bones")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("npc bones"), (float*)&color_ai_bone, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ai_bone_r = realToInteger(color_ai_bone.x);
					Settings::Colors::ai_bone_g = realToInteger(color_ai_bone.y);
					Settings::Colors::ai_bone_b = realToInteger(color_ai_bone.z);

					ImGui::Text(META_STRING("dead")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("npc dead"), (float*)&color_ai_dead, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ai_dead_r = realToInteger(color_ai_dead.x);
					Settings::Colors::ai_dead_g = realToInteger(color_ai_dead.y);
					Settings::Colors::ai_dead_b = realToInteger(color_ai_dead.z);

					ImGui::Text(META_STRING("stance")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("npc stance"), (float*)&color_ai_stance, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ai_stance_r = realToInteger(color_ai_stance.x);
					Settings::Colors::ai_stance_g = realToInteger(color_ai_stance.y);
					Settings::Colors::ai_stance_b = realToInteger(color_ai_stance.z);

					ImGui::Text(META_STRING("snapline")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("npc snapline"), (float*)&color_ai_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ai_snapline_r = realToInteger(color_ai_snapline.x);
					Settings::Colors::ai_snapline_g = realToInteger(color_ai_snapline.y);
					Settings::Colors::ai_snapline_b = realToInteger(color_ai_snapline.z);

				}

				if (tab_visual_color_cars) {
					ImGui::Text(META_STRING("name")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("cars name"), (float*)&color_car_name, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::car_name_r = realToInteger(color_car_name.x);
					Settings::Colors::car_name_g = realToInteger(color_car_name.y);
					Settings::Colors::car_name_b = realToInteger(color_car_name.z);

					ImGui::Text(META_STRING("box")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("cars box"), (float*)&color_car_box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::car_box_r = realToInteger(color_car_box.x);
					Settings::Colors::car_box_g = realToInteger(color_car_box.y);
					Settings::Colors::car_box_b = realToInteger(color_car_box.z);

					ImGui::Text(META_STRING("destroyed")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("cars destroyed"), (float*)&color_car_destroyed, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::car_destroyed_r = realToInteger(color_car_destroyed.x);
					Settings::Colors::car_destroyed_g = realToInteger(color_car_destroyed.y);
					Settings::Colors::car_destroyed_b = realToInteger(color_car_destroyed.z);

					ImGui::Text(META_STRING("snapline")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("cars snapline"), (float*)&color_car_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::car_snapline_r = realToInteger(color_car_snapline.x);
					Settings::Colors::car_snapline_g = realToInteger(color_car_snapline.y);
					Settings::Colors::car_snapline_b = realToInteger(color_car_snapline.z);
				}

				if (tab_visual_color_heli) {
					ImGui::Text(META_STRING("name")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("hellicopter name"), (float*)&color_hellicopter_name, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::hellicopter_name_r = realToInteger(color_hellicopter_name.x);
					Settings::Colors::hellicopter_name_g = realToInteger(color_hellicopter_name.y);
					Settings::Colors::hellicopter_name_b = realToInteger(color_hellicopter_name.z);

					ImGui::Text(META_STRING("box")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("hellicopter box"), (float*)&color_hellicopter_box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::hellicopter_box_r = realToInteger(color_hellicopter_box.x);
					Settings::Colors::hellicopter_box_g = realToInteger(color_hellicopter_box.y);
					Settings::Colors::hellicopter_box_b = realToInteger(color_hellicopter_box.z);

					ImGui::Text(META_STRING("destroyed")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("hellicopter destroyed"), (float*)&color_hellicopter_destroyed, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::hellicopter_destroyed_r = realToInteger(color_hellicopter_destroyed.x);
					Settings::Colors::hellicopter_destroyed_g = realToInteger(color_hellicopter_destroyed.y);
					Settings::Colors::hellicopter_destroyed_b = realToInteger(color_hellicopter_destroyed.z);

					ImGui::Text(META_STRING("snapline")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("hellicopter snapline"), (float*)&color_hellicopter_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::hellicopter_snapline_r = realToInteger(color_hellicopter_snapline.x);
					Settings::Colors::hellicopter_snapline_g = realToInteger(color_hellicopter_snapline.y);
					Settings::Colors::hellicopter_snapline_b = realToInteger(color_hellicopter_snapline.z);
				}

				if (tab_visual_color_air) {
					ImGui::Text(META_STRING("name")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("airplane name"), (float*)&color_airplane_name, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::airplane_name_r = realToInteger(color_airplane_name.x);
					Settings::Colors::airplane_name_g = realToInteger(color_airplane_name.y);
					Settings::Colors::airplane_name_b = realToInteger(color_airplane_name.z);

					ImGui::Text(META_STRING("box")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("airplane box"), (float*)&color_airplane_box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::airplane_box_r = realToInteger(color_airplane_box.x);
					Settings::Colors::airplane_box_g = realToInteger(color_airplane_box.y);
					Settings::Colors::airplane_box_b = realToInteger(color_airplane_box.z);

					ImGui::Text(META_STRING("destroyed")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("airplane destroyed"), (float*)&color_airplane_destroyed, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::airplane_destroyed_r = realToInteger(color_airplane_destroyed.x);
					Settings::Colors::airplane_destroyed_g = realToInteger(color_airplane_destroyed.y);
					Settings::Colors::airplane_destroyed_b = realToInteger(color_airplane_destroyed.z);

					ImGui::Text(META_STRING("snapline")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("airplane snapline"), (float*)&color_airplane_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::airplane_snapline_r = realToInteger(color_airplane_snapline.x);
					Settings::Colors::airplane_snapline_g = realToInteger(color_airplane_snapline.y);
					Settings::Colors::airplane_snapline_b = realToInteger(color_airplane_snapline.z);
				}

				if (tab_visual_color_tanks) {
					ImGui::Text(META_STRING("name")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("tank name"), (float*)&color_tank_name, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::tank_name_r = realToInteger(color_tank_name.x);
					Settings::Colors::tank_name_g = realToInteger(color_tank_name.y);
					Settings::Colors::tank_name_b = realToInteger(color_tank_name.z);

					ImGui::Text(META_STRING("box")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("tank box"), (float*)&color_tank_box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::tank_box_r = realToInteger(color_tank_box.x);
					Settings::Colors::tank_box_g = realToInteger(color_tank_box.y);
					Settings::Colors::tank_box_b = realToInteger(color_tank_box.z);

					ImGui::Text(META_STRING("destroyed")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("tank destroyed"), (float*)&color_tank_destroyed, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::tank_destroyed_r = realToInteger(color_tank_destroyed.x);
					Settings::Colors::tank_destroyed_g = realToInteger(color_tank_destroyed.y);
					Settings::Colors::tank_destroyed_b = realToInteger(color_tank_destroyed.z);

					ImGui::Text(META_STRING("snapline")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("tank snapline"), (float*)&color_tank_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::tank_snapline_r = realToInteger(color_tank_snapline.x);
					Settings::Colors::tank_snapline_g = realToInteger(color_tank_snapline.y);
					Settings::Colors::tank_snapline_b = realToInteger(color_tank_snapline.z);
				}


				if (tab_visual_color_ships) {
					ImGui::Text(META_STRING("name")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("ship name"), (float*)&color_ship_name, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ship_name_r = realToInteger(color_ship_name.x);
					Settings::Colors::ship_name_g = realToInteger(color_ship_name.y);
					Settings::Colors::ship_name_b = realToInteger(color_ship_name.z);

					ImGui::Text(META_STRING("box")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("ship box"), (float*)&color_ship_box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ship_box_r = realToInteger(color_ship_box.x);
					Settings::Colors::ship_box_g = realToInteger(color_ship_box.y);
					Settings::Colors::ship_box_b = realToInteger(color_ship_box.z);

					ImGui::Text(META_STRING("destroyed")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("ship destroyed"), (float*)&color_ship_destroyed, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ship_destroyed_r = realToInteger(color_ship_destroyed.x);
					Settings::Colors::ship_destroyed_g = realToInteger(color_ship_destroyed.y);
					Settings::Colors::ship_destroyed_b = realToInteger(color_ship_destroyed.z);

					ImGui::Text(META_STRING("snapline")); ImGui::SameLine(); ImGui::ColorEdit4(META_STRING("ship snapline"), (float*)&color_ship_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
					Settings::Colors::ship_snapline_r = realToInteger(color_ship_snapline.x);
					Settings::Colors::ship_snapline_g = realToInteger(color_ship_snapline.y);
					Settings::Colors::ship_snapline_b = realToInteger(color_ship_snapline.z);
				}

				ImGui::Columns(1);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(META_STRING("crosshair"))) {
				//fuck off
				ImGui::EndTabItem();
			}
			
			ImGui::EndTabBar();		
			ImGui::End();
			ImGui::EndFrame();
		}
		else
		{
			if (windowstate != 0)
			{
				ChangeClickability(false, m_WndOverlay);
			}
		}

        /// if the surface has successfully started a new scene
		if (m_Surface->begin_scene()) {
			///-------------------------------------------------------------------------------------------------
			/// begin the rendering here
			///-------------------------------------------------------------------------------------------------

			//iGetFPS(&overlay_fps);

			

			m_Surface->text(17, 100, META_STRING("default"), 0xFF00FF00, string(META_STRING("test for enigma by enfloyd")));


			if (!processId)
				EnfusionProcess::SetHook();

			uint32_t color = 0xFFFF0000;

			float centerX = m_Width / 2.0f;
			float centerY = m_Height / 2.0f;

			for (uint64_t Entity : EnfusionEngine::GetAllEntityes())
			{
				uint16_t EntityType = EnfusionEngine::GetType(Entity);
				Vector3 worldPosition = EnfusionEngine::GetPosition(Entity);
				Vector3 screenPosition = EnfusionEngine::WorldToScreen(worldPosition);

				uint32_t distance = static_cast<uint32_t>(EnfusionEngine::GetDistanceToMe(worldPosition));

				if (screenPosition.z >= 1.5f && distance < 1000)
				{
					if (Settings::esp_players && EntityType == Types::soldier)
					{
						float corrector = 20.0f;

						if (!EnfusionEngine::IsDead(Entity))
						{
							string text_player = META_STRING("Soldier");

							if (Settings::esp_players_name) {
								text_player = EnfusionEngine::GetPlayerName(Entity);
							}

							if (Settings::esp_players_box) {
								Vector3 head = EnfusionEngine::WorldToScreen(
									EnfusionEngine::GetHeadPosition(Entity));
								float width = (head.y - screenPosition.y) / 4.5f;
								m_Surface->box(screenPosition, head, width,
									D3DCOLOR_ARGB(255,
										Settings::Colors::player_box_r,
										Settings::Colors::player_box_g,
										Settings::Colors::player_box_b),
									m_Direct3D9Line);
								
							}

							Vector3 headscreen = EnfusionEngine::WorldToScreen(
								EnfusionEngine::GetHeadPosition(Entity));

							m_Surface->DrawBar(headscreen, screenPosition, EnfusionEngine::GetHealth(Entity), m_Direct3D9Line);
								
							

							headscreen.y -= 15.0f;

							m_Surface->text_outlined(
								headscreen.x - corrector, headscreen.y, META_STRING("default"),
								D3DCOLOR_ARGB(255,
									Settings::Colors::player_name_r,
									Settings::Colors::player_name_g,
									Settings::Colors::player_name_b), text_player);

							m_Surface->text_outlined(
								screenPosition.x - 10.0f, screenPosition.y, META_STRING("default"),
								D3DCOLOR_ARGB(255,
									Settings::Colors::player_name_r,
									Settings::Colors::player_name_g,
									Settings::Colors::player_name_b), to_string(distance) + META_STRING("m"));
						}
						else
						{
							if (Settings::esp_players_isdead) {
								m_Surface->text_outlined(
									screenPosition.x - corrector, screenPosition.y, META_STRING("default"),
									D3DCOLOR_ARGB(255,
										Settings::Colors::player_dead_r,
										Settings::Colors::player_dead_g,
										Settings::Colors::player_dead_b), META_STRING("Corpse"));
							}
						}
					}

					if (Settings::esp_vehicles && EntityType == Types::car)
					{
						float corrector = 20.0f;

						if (!EnfusionEngine::IsDead(Entity))
						{
							if (Settings::mem_vehicle_autounlock) {
								EnfusionEngine::ForceVehicleUnlock(Entity);
							}

							string text_player = META_STRING("");

							if (Settings::esp_vehicles_name) {
								text_player = EnfusionEngine::GetTypeName(Entity);
							}

							if (Settings::esp_vehicles_distance) {
								corrector = 25.0f;
								text_player += string(META_STRING(" ")) + to_string(distance) + string(META_STRING("m"));
							}

							if (Settings::esp_vehicles_health) {
								text_player += string(META_STRING("\nHP (")) + to_string(EnfusionEngine::GetHealth(Entity)) + string(META_STRING(")"));
							}

							if (Settings::esp_vehicles_box) {
								float width = 5.0f;
								Vector3 htanks = Vector3(screenPosition.x, screenPosition.y - 15, screenPosition.z);
								m_Surface->box(screenPosition, htanks, width, D3DCOLOR_ARGB(255,
									Settings::Colors::car_box_r,
									Settings::Colors::car_box_g,
									Settings::Colors::car_box_b), m_Direct3D9Line);

							}

							m_Surface->text_outlined(
								screenPosition.x - 10.0f, screenPosition.y, META_STRING("default"),
								D3DCOLOR_ARGB(255,
									Settings::Colors::car_name_r,
									Settings::Colors::car_name_g,
									Settings::Colors::car_name_b), text_player);
						}
						else
						{
							if (Settings::esp_vehicles_isdestroyed) {
								m_Surface->text_outlined(
									screenPosition.x - corrector, screenPosition.y, META_STRING("default"),
									D3DCOLOR_ARGB(255,
										Settings::Colors::car_destroyed_r,
										Settings::Colors::car_destroyed_g,
										Settings::Colors::car_destroyed_b), META_STRING("Destroyed"));
							}
						}
					}

					if (Settings::esp_hellicopters && EntityType == Types::hellicopter)
					{
						float corrector = 20.0f;

						if (!EnfusionEngine::IsDead(Entity))
						{
							string text_player = META_STRING("");

							if (Settings::esp_hellicopters_name) {
								text_player = EnfusionEngine::GetTypeName(Entity);
							}

							if (Settings::esp_hellicopters_distance) {
								corrector = 25.0f;
								text_player += string(META_STRING(" ")) + to_string(distance) + string(META_STRING("m"));
							}

							if (Settings::esp_hellicopters_health) {
								text_player += string(META_STRING("\nHP (")) + to_string(EnfusionEngine::GetHealth(Entity)) + string(META_STRING(")"));
							}

							if (Settings::esp_hellicopters_box) {
								float width = 5.0f;
								Vector3 htanks = Vector3(screenPosition.x, screenPosition.y - 15, screenPosition.z);
								m_Surface->box(screenPosition, htanks, width, D3DCOLOR_ARGB(255,
									Settings::Colors::hellicopter_box_r,
									Settings::Colors::hellicopter_box_g,
									Settings::Colors::hellicopter_box_b), m_Direct3D9Line);

							}

							m_Surface->text_outlined(
								screenPosition.x - 10.0f, screenPosition.y, META_STRING("default"),
								D3DCOLOR_ARGB(255,
									Settings::Colors::hellicopter_name_r,
									Settings::Colors::hellicopter_name_g,
									Settings::Colors::hellicopter_name_b), text_player);
						}
						else
						{
							if (Settings::esp_tanks_isdestroyed) {
								m_Surface->text_outlined(
									screenPosition.x - corrector, screenPosition.y, META_STRING("default"),
									D3DCOLOR_ARGB(255,
										Settings::Colors::hellicopter_destroyed_r,
										Settings::Colors::hellicopter_destroyed_g,
										Settings::Colors::hellicopter_destroyed_b), META_STRING("Destroyed"));
							}
						}
					}

					if (Settings::esp_airplanes && EntityType == Types::airplane)
					{
						float corrector = 20.0f;

						if (!EnfusionEngine::IsDead(Entity))
						{
							string text_player = META_STRING("");

							if (Settings::esp_airplanes_name) {
								text_player = EnfusionEngine::GetTypeName(Entity);
							}

							if (Settings::esp_airplanes_distance) {
								corrector = 25.0f;
								text_player += string(META_STRING(" ")) + to_string(distance) + string(META_STRING("m"));
							}

							if (Settings::esp_airplanes_health) {
								text_player += string(META_STRING("\nHP (")) + to_string(EnfusionEngine::GetHealth(Entity)) + string(META_STRING(")"));
							}

							if (Settings::esp_airplanes_box) {
								float width = 5.0f;
								Vector3 htanks = Vector3(screenPosition.x, screenPosition.y + 15, screenPosition.z);
								m_Surface->box(screenPosition, htanks, width, D3DCOLOR_ARGB(255,
									Settings::Colors::airplane_box_r,
									Settings::Colors::airplane_box_g,
									Settings::Colors::airplane_box_b), m_Direct3D9Line);

							}

							m_Surface->text_outlined(
								screenPosition.x - 10.0f, screenPosition.y, META_STRING("default"),
								D3DCOLOR_ARGB(255,
									Settings::Colors::airplane_name_r,
									Settings::Colors::airplane_name_g,
									Settings::Colors::airplane_name_b), text_player);
						}
						else
						{
							if (Settings::esp_airplanes_isdestroyed) {
								m_Surface->text_outlined(
									screenPosition.x - corrector, screenPosition.y, META_STRING("default"),
									D3DCOLOR_ARGB(255,
										Settings::Colors::airplane_destroyed_r,
										Settings::Colors::airplane_destroyed_g,
										Settings::Colors::airplane_destroyed_b), META_STRING("Destroyed"));
							}
						}
					}

					if (Settings::esp_tanks && EntityType == Types::tank)
					{
						float corrector = 20.0f;

						if (!EnfusionEngine::IsDead(Entity))
						{
							string text_player = META_STRING("");

							if (Settings::esp_tanks_name) {
								text_player = EnfusionEngine::GetTypeName(Entity);
							}

							if (Settings::esp_tanks_distance) {
								corrector = 25.0f;
								text_player += string(META_STRING(" ")) + to_string(distance) + string(META_STRING("m"));
							}

							if (Settings::esp_tanks_health) {
								text_player += string(META_STRING("\nHP (")) + to_string(EnfusionEngine::GetHealth(Entity)) + string(META_STRING(")"));
							}

							if (Settings::esp_tanks_box) {
								float width = 5.0f;
								Vector3 htanks = Vector3(screenPosition.x, screenPosition.y + 15, screenPosition.z);
								m_Surface->box(screenPosition, htanks, width, D3DCOLOR_ARGB(255,
									Settings::Colors::tank_box_r,
									Settings::Colors::tank_box_g,
									Settings::Colors::tank_box_b), m_Direct3D9Line);

							}

							m_Surface->text_outlined(
								screenPosition.x - 10.0f, screenPosition.y, META_STRING("default"),
								D3DCOLOR_ARGB(255,
									Settings::Colors::tank_name_r,
									Settings::Colors::tank_name_g,
									Settings::Colors::tank_name_b), text_player);
						}
						else
						{
							if (Settings::esp_tanks_isdestroyed) {
								m_Surface->text_outlined(
									screenPosition.x - corrector, screenPosition.y, META_STRING("default"),
									D3DCOLOR_ARGB(255,
										Settings::Colors::tank_destroyed_r,
										Settings::Colors::tank_destroyed_g,
										Settings::Colors::tank_destroyed_b), META_STRING("Destroyed"));
							}
						}
					}

					if (Settings::esp_ships && EntityType == Types::ship)
					{
						float corrector = 20.0f;

						if (!EnfusionEngine::IsDead(Entity))
						{
							string text_player = META_STRING("");

							if (Settings::esp_ships_name) {
								text_player = EnfusionEngine::GetTypeName(Entity);
							}

							if (Settings::esp_ships_distance) {
								corrector = 25.0f;
								text_player += string(META_STRING(" ")) + to_string(distance) + string(META_STRING("m"));
							}

							if (Settings::esp_ships_health) {
								text_player += string(META_STRING("\nHP (")) + to_string(EnfusionEngine::GetHealth(Entity)) + string(META_STRING(")"));
							}

							if (Settings::esp_ships_box) {
								float width = 5.0f;
								Vector3 htanks = Vector3(screenPosition.x, screenPosition.y + 15, screenPosition.z);
								m_Surface->box(screenPosition, htanks, width, D3DCOLOR_ARGB(255,
									Settings::Colors::ship_box_r,
									Settings::Colors::ship_box_g,
									Settings::Colors::ship_box_b), m_Direct3D9Line);

							}

							m_Surface->text_outlined(
								screenPosition.x - 10.0f, screenPosition.y, META_STRING("default"),
								D3DCOLOR_ARGB(255,
									Settings::Colors::ship_name_r,
									Settings::Colors::ship_name_g,
									Settings::Colors::ship_name_b), text_player);
						}
						else
						{
							if (Settings::esp_ships_isdestroyed) {
								m_Surface->text_outlined(
									screenPosition.x - corrector, screenPosition.y, META_STRING("default"),
									D3DCOLOR_ARGB(255,
										Settings::Colors::ship_destroyed_r,
										Settings::Colors::ship_destroyed_g,
										Settings::Colors::ship_destroyed_b), META_STRING("Destroyed"));
							}
						}
					}
					
					if (Settings::slim_silentaim)
					{
						if (GetAsyncKeyState(VK_LCONTROL)) {

							if (screenPosition.x - centerX < Settings::slim_option_fov &&
								centerX - screenPosition.x < Settings::slim_option_fov &&
								centerY - screenPosition.y < Settings::slim_option_fov &&
								screenPosition.y - centerY < Settings::slim_option_fov) {

								color = 0xFF00FF00;
								EnfusionEngine::DefaultSilentAim(Entity);
							}
						}
					}

					if (Settings::tp_teleport_to_target)
					{
						if (GetAsyncKeyState(VK_LCONTROL)) {

							if (screenPosition.x - centerX < Settings::slim_option_fov &&
								centerX - screenPosition.x < Settings::slim_option_fov &&
								centerY - screenPosition.y < Settings::slim_option_fov &&
								screenPosition.y - centerY < Settings::slim_option_fov) {

								EnfusionEngine::SetPosition(EnfusionEngine::GetLocalPlayer(), worldPosition);
							}
						}
					}
				}

			//	if (Settings::slim_visual_fov) {
					//m_Surface->circle(centerX, centerY, Settings::slim_option_fov, 30,
					//	D3DCOLOR_ARGB(255,
					//	Settings::Colors::fildofview_cirle_r,
					//	Settings::Colors::fildofview_cirle_g,
					//	Settings::Colors::fildofview_cirle_b), m_Direct3D9Line);
				//}
			}

			if (enabled)
			{
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			}

            execute_callbacks();
            ///-------------------------------------------------------------------------------------------------
            /// stop the rendering here
            ///-------------------------------------------------------------------------------------------------
            m_Surface->end_scene();
        }
    }

    m_Direct3D9Device->EndScene();
    m_Direct3D9Device->PresentEx(
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0
    );

    return true;
}

void Device3D9::shutdown()
{
    Overlay::shutdown();
    safe_release( &m_Direct3D9Ex );
    safe_release( &m_Direct3D9Device );
    safe_release( &m_Direct3DXSprite );

    if( m_Surface ) {
        m_Surface->shutdown();
    }
}