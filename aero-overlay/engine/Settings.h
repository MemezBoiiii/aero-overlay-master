#include "Vector3.h"

#pragma once

namespace Settings
{
	static bool esp_players = true;
	static bool esp_players_ai = false;
	static bool esp_players_name = false;
	static bool esp_players_stance = false;
	static bool esp_players_distance = true;
	static bool esp_players_isdead = true;
	static bool esp_players_health = false;
	static bool esp_players_bones = false;
	static bool esp_players_box = true;
	static bool esp_players_team = false;
	static bool esp_players_snapline = false;

	namespace Colors
	{
		static uint32_t fildofview_cirle_r = 255;
		static uint32_t fildofview_cirle_g = 255;
		static uint32_t fildofview_cirle_b = 255;

		static uint32_t player_name_r = 255;
		static uint32_t player_name_g = 255;
		static uint32_t player_name_b = 255;

		static uint32_t player_box_r = 255;
		static uint32_t player_box_g = 255;
		static uint32_t player_box_b = 255;

		static uint32_t player_bone_r = 255;
		static uint32_t player_bone_g = 255;
		static uint32_t player_bone_b = 255;

		static uint32_t player_dead_r = 255;
		static uint32_t player_dead_g = 255;
		static uint32_t player_dead_b = 255;

		static uint32_t player_snapline_r = 255;
		static uint32_t player_snapline_g = 255;
		static uint32_t player_snapline_b = 255;

		static uint32_t player_stance_r = 255;
		static uint32_t player_stance_g = 255;
		static uint32_t player_stance_b = 255;

		///////////////////////////////////

		static uint32_t ai_name_r = 255;
		static uint32_t ai_name_g = 255;
		static uint32_t ai_name_b = 255;

		static uint32_t ai_box_r = 255;
		static uint32_t ai_box_g = 255;
		static uint32_t ai_box_b = 255;

		static uint32_t ai_bone_r = 255;
		static uint32_t ai_bone_g = 255;
		static uint32_t ai_bone_b = 255;

		static uint32_t ai_dead_r = 255;
		static uint32_t ai_dead_g = 255;
		static uint32_t ai_dead_b = 255;

		static uint32_t ai_snapline_r = 255;
		static uint32_t ai_snapline_g = 255;
		static uint32_t ai_snapline_b = 255;

		static uint32_t ai_stance_r = 255;
		static uint32_t ai_stance_g = 255;
		static uint32_t ai_stance_b = 255;

		///////////////////////////////////

		static uint32_t car_name_r = 255;
		static uint32_t car_name_g = 255;
		static uint32_t car_name_b = 255;

		static uint32_t car_box_r = 255;
		static uint32_t car_box_g = 255;
		static uint32_t car_box_b = 255;

		static uint32_t car_destroyed_r = 255;
		static uint32_t car_destroyed_g = 255;
		static uint32_t car_destroyed_b = 255;

		static uint32_t car_snapline_r = 255;
		static uint32_t car_snapline_g = 255;
		static uint32_t car_snapline_b = 255;

		///////////////////////////////////

		static uint32_t hellicopter_name_r = 255;
		static uint32_t hellicopter_name_g = 255;
		static uint32_t hellicopter_name_b = 255;

		static uint32_t hellicopter_box_r = 255;
		static uint32_t hellicopter_box_g = 255;
		static uint32_t hellicopter_box_b = 255;

		static uint32_t hellicopter_destroyed_r = 255;
		static uint32_t hellicopter_destroyed_g = 255;
		static uint32_t hellicopter_destroyed_b = 255;

		static uint32_t hellicopter_snapline_r = 255;
		static uint32_t hellicopter_snapline_g = 255;
		static uint32_t hellicopter_snapline_b = 255;

		///////////////////////////////////

		static uint32_t tank_name_r = 255;
		static uint32_t tank_name_g = 255;
		static uint32_t tank_name_b = 255;

		static uint32_t tank_box_r = 255;
		static uint32_t tank_box_g = 255;
		static uint32_t tank_box_b = 255;

		static uint32_t tank_destroyed_r = 255;
		static uint32_t tank_destroyed_g = 255;
		static uint32_t tank_destroyed_b = 255;

		static uint32_t tank_snapline_r = 255;
		static uint32_t tank_snapline_g = 255;
		static uint32_t tank_snapline_b = 255;

		///////////////////////////////////

		static uint32_t airplane_name_r = 255;
		static uint32_t airplane_name_g = 255;
		static uint32_t airplane_name_b = 255;

		static uint32_t airplane_box_r = 255;
		static uint32_t airplane_box_g = 255;
		static uint32_t airplane_box_b = 255;

		static uint32_t airplane_destroyed_r = 255;
		static uint32_t airplane_destroyed_g = 255;
		static uint32_t airplane_destroyed_b = 255;

		static uint32_t airplane_snapline_r = 255;
		static uint32_t airplane_snapline_g = 255;
		static uint32_t airplane_snapline_b = 255;

		///////////////////////////////////

		static uint32_t ship_name_r = 255;
		static uint32_t ship_name_g = 255;
		static uint32_t ship_name_b = 255;

		static uint32_t ship_box_r = 255;
		static uint32_t ship_box_g = 255;
		static uint32_t ship_box_b = 255;

		static uint32_t ship_destroyed_r = 255;
		static uint32_t ship_destroyed_g = 255;
		static uint32_t ship_destroyed_b = 255;

		static uint32_t ship_snapline_r = 255;
		static uint32_t ship_snapline_g = 255;
		static uint32_t ship_snapline_b = 255;

		///////////////////////////////////

		static uint32_t item_name_r = 255;
		static uint32_t item_name_g = 255;
		static uint32_t item_name_b = 255;

		static uint32_t item_box_r = 255;
		static uint32_t item_box_g = 255;
		static uint32_t item_box_b = 255;

		static uint32_t item_destroyed_r = 255;
		static uint32_t item_destroyed_g = 255;
		static uint32_t item_destroyed_b = 255;

		static uint32_t item_snapline_r = 255;
		static uint32_t item_snapline_g = 255;
		static uint32_t item_snapline_b = 255;
	}

	static bool esp_ai = false;
	static bool esp_ai_name = false;
	static bool esp_ai_distance = false;
	static bool esp_ai_health = false;
	static bool esp_ai_isdead = false;
	static bool esp_ai_box = false;
	static bool esp_ai_team = false;
	static bool esp_ai_snapline = false;
	static uint32_t esp_ai_color = 0xFFFFFFFF;

	static bool esp_vehicles = true;
	static bool esp_vehicles_name = false;
	static bool esp_vehicles_distance = true;
	static bool esp_vehicles_health = false;
	static bool esp_vehicles_isdestroyed = false;
	static bool esp_vehicles_box = false;
	static bool esp_vehicles_snapline = false;
	static uint32_t esp_vehicles_color = 0xFFFFFFFF;

	static bool esp_hellicopters = true;
	static bool esp_hellicopters_name = false;
	static bool esp_hellicopters_distance = false;
	static bool esp_hellicopters_health = false;
	static bool esp_hellicopters_isdestroyed = false;
	static bool esp_hellicopters_box = false;
	static bool esp_hellicopters_snapline = false;
	static uint32_t esp_hellicopters_color = 0xFFFFFFFF;

	static bool esp_tanks = true;
	static bool esp_tanks_name = false;
	static bool esp_tanks_distance = true;
	static bool esp_tanks_health = false;
	static bool esp_tanks_isdestroyed = false;
	static bool esp_tanks_box = false;
	static bool esp_tanks_snapline = false;
	static uint32_t tanks = 0xFFFFFFFF;

	static bool esp_airplanes = true;
	static bool esp_airplanes_name = false;
	static bool esp_airplanes_distance = false;
	static bool esp_airplanes_health = false;
	static bool esp_airplanes_isdestroyed = false;
	static bool esp_airplanes_box = false;
	static bool esp_airplanes_snapline = false;
	static uint32_t esp_airplanes_color = 0xFFFFFFFF;

	static bool esp_ships = true;
	static bool esp_ships_name = false;
	static bool esp_ships_distance = false;
	static bool esp_ships_health = false;
	static bool esp_ships_isdestroyed = false;
	static bool esp_ships_box = false;
	static bool esp_ships_snapline = false;
	static uint32_t esp_ships_color = 0xFFFFFFFF;

	static bool tp_teleport_by_cursor = false;
	static bool tp_teleport_by_mapclick = true;
	static bool tp_teleport_to_target = false;

	static bool tp_teleport_on_coordinates = false;
	static Vector3 tp_teleport_on_coordinates_lastTpPosition;

	static bool slim_silentaim = true;
	static bool slim_visual_fov = true;
	static float slim_option_fov = 30.0f;

	static bool mem_without_fatigue = false;
	static bool mem_without_recoil = false;
	static bool mem_without_grass = false;
	static bool mem_godmode = false;
	static bool mem_vehicle_godmode = false;
	static bool mem_vehicle_autounlock = false;
	static bool mem_player_invisible = false;
	static bool mem_without_gravity = false;

	static bool mem_delete_target_object = false;

	static bool mem_speedhack = false;
	static float mem_speedhack_stephope = 0;

	static bool mem_flyhack = false;
}
