
#pragma once

#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <dwmapi.h> 
#include <iterator>

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <atlstr.h> 
#include <vector>
#include <assert.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <inttypes.h>

#include <d3d11.h>

#include <string>
#include <thread>
#include <chrono>
#include <mutex>

#include <winioctl.h>
#include <sys/types.h>
#include <algorithm>

#include <iomanip>  
#include <dxgiformat.h>
#include <stdarg.h> 
#include <memory>  
#include <psapi.h>

#include <vector>


#define COMPILE_SEED 7231369381

template <int X>
struct EnsureCompileTime
{
	enum : int
	{
		Value = X
	};
};

constexpr int LinearCongruentGenerator(int rounds)
{
	return 1013904223 + 1664525 * ((rounds > 0) ? LinearCongruentGenerator(rounds - 1) : COMPILE_SEED & 0xFFFFFFFF);
}

#define Random() EnsureCompileTime<LinearCongruentGenerator(10)>::Value
#define RandomNumber(Min, Max) (Min + (Random() % (Max - Min + 1)))

const BYTE g_xorKey = static_cast<BYTE>(RandomNumber(0, 0xFF));

template <int... Pack> struct IndexList {};

template <typename IndexList, int Right> struct Append;

template <int... Left, int Right> struct Append<IndexList<Left...>, Right>
{
	typedef IndexList<Left..., Right> Result;
};

template <int N> struct ConstructIndexList
{
	typedef typename Append<typename ConstructIndexList<N - 1>::Result, N - 1>::Result Result;
};

template <> struct ConstructIndexList<0>
{
	typedef IndexList<> Result;
};

constexpr char EncryptCharacter(const char character, int index)
{
	return character ^ (g_xorKey + index);
}

constexpr wchar_t EncryptWCharacter(const wchar_t character, int index)
{
	return character ^ (g_xorKey + index);
}

template <typename IndexList> class MetaString;

template <int... Index> class MetaString<IndexList<Index...> >
{
public:
	__forceinline constexpr MetaString(const char* const value)
		: m_value{ EncryptCharacter(value[Index], Index)... }
	{
	}

	char* Decrypt()
	{
		for (int t = 0; t < sizeof...(Index); t++)
		{
			m_value[t] = m_value[t] ^ (g_xorKey + t);
		}

		m_value[sizeof...(Index)] = '\0';

		return m_value;
	}

private:
	char m_value[sizeof...(Index) + 1];
};

template <typename IndexList> class MetaWString;

template <int... Index> class MetaWString<IndexList<Index...> >
{
public:
	__forceinline constexpr MetaWString(const wchar_t* const value)
		: m_value{ EncryptWCharacter(value[Index], Index)... }
	{
	}

	wchar_t* Decrypt()
	{
		for (int t = 0; t < sizeof...(Index); t++)
		{
			m_value[t] = m_value[t] ^ (g_xorKey + t);
		}

		m_value[sizeof...(Index)] = '\0';

		return m_value;
	}

private:
	wchar_t m_value[sizeof...(Index) + 1];
};

#define META_STRING(x) (MetaString<ConstructIndexList<sizeof(x) - 1>::Result>(x).Decrypt()) 
#define META_WSTRING(x) (MetaWString<ConstructIndexList<sizeof(x) - 1>::Result>(x).Decrypt()) 



#pragma warning (disable: 4996)

using namespace std;

//enfloyd.com /arma3/

#define off_world 0x2589140 //0xdd4ed0
#define off_networkmanager 0x2546CB0

#define off_networkmanager_networkclient 0x50

#define off_networkclient_scoreboard 0x10
#define off_networkclient_playeridentity_size 0x158
#define off_networkclient_servername 0x328

#define off_playeridentity_networkid 0x30
#define off_playeridentity_playername 0xf0

#define off_world_camera 0x828

#define off_camera_viewright 0x8
#define off_camera_viewup 0x14
#define off_camera_viewforward 0x20
#define off_camera_viewtranslation 0x2C
#define off_camera_viewportsize 0x58
#define off_camera_projection_d1 0xD0
#define off_camera_projection_d2 0xDC

#define off_world_nearanimaltable 0x1700//0xe78
#define off_world_faranimaltable 0x17c8//0xfc0
#define off_world_slowanimaltable 0x1f28
#define off_world_itemtable 0x1f90
#define off_world_bullettable 0x1630
#define off_world_setteraingrid 0x1124
#define off_world_ingameui 0x488
#define off_world_displaymainmap 0x1200
#define off_world_ismenuopen 0x27d3

#define off_ingameui_cursorposition 0x5C
#define off_displaymainmap_staticmapmain 0x190
#define off_staticmapmain_lastclickposition 0x9f8

#define off_world_cameraon 0x26f0
#define off_world_playeron 0x2720

#define off_world_terraingrid 0xb40 

#define off_sortedobject_entity 0x8

#define off_entity_cameraentry 0x2168
#define off_entity_futurevisualstate 0xd0
#define off_entity_renderervisualstate 0x190
#define off_entity_futureentitytype 0x38
#define off_entity_rendererentitytype 0x150
#define off_entity_sortobject 0x138
#define off_entity_baseentity 0xa8
#define off_entity_networkid 0x584
#define off_entity_inventory 0x4f8
#define off_entity_isdead 0x504
#define off_entity_fatigue 0x1090
#define off_entity_fatiguediff 0x1094
#define off_entity_recoilcoeff 0x1058

#define off_cameraentry_movupdown 0xa4
#define off_cameraentry_movforwardbackward 0xc4
#define off_cameraentry_movleftright 0xc8
#define off_cameraentry_movrotate 0xd8

#define off_inventory_iteminhands 0x200

#define off_entitytype_basetype 0x88
#define off_entitytype_typename 0x68
#define off_entitytype_modelname 0x80
#define off_entitytype_configname 0xd0
#define off_entitytype_cleanname 0x11d0

#define off_visualstate_position 0x2c
#define off_visualstate_headposition 0xf8

#define off_x 0x2c
#define off_y 0x30
#define off_z 0x34

#define off_text 0x10
#define off_length 0x8
