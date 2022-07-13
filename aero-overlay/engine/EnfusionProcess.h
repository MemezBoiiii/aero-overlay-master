/*
	by unitx 12.22.2018
*/

#pragma once

static uint32_t processId;
static uint64_t ModuleBase;

#include "Engine.h"
#include "kInterface.hpp"

void UpdateUnits();

class EnfusionProcess
{
public:
	static const char* GameName;

	static void SetHook()
	{
			KeInterface::_KeInterface(META_STRING("\\\\.\\suns"));
			processId = KeInterface::GetTargetPid();		//
			ModuleBase = KeInterface::get_modulebase();
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UpdateUnits, 0, 0, 0);
	}

	template <typename T>
	static T ReadData(uint64_t address)
	{
		return KeInterface::ReadVirtualMemory<T>(processId, address, sizeof(T));
	};

	static bool WriteFloat(uint64_t address, float data)
	{
		return KeInterface::WriteFloatVirtualMemory(processId, address, data, sizeof(float));
	};

	static bool WriteInt(uint64_t address, int data)
	{
		return KeInterface::WriteIntVirtualMemory(processId, address, data, sizeof(INT8));
	};

	static bool WriteInt64(uint64_t address, INT64 data)
	{
		return KeInterface::WriteInt64VirtualMemory(processId, address, data, sizeof(INT64));
	};

	template <typename T>
	static T ReadString(uint64_t address, uint64_t size)
	{
		return KeInterface::ReadVirtualMemory<T>(processId, address, size);
	};

};



