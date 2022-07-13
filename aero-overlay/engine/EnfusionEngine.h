/**
 * Copyright (c) 2019 exsightcore (by emey)
 * last up - 04.19.2019
 */


#include "Engine.h"
#include "EnfusionProcess.h"

struct Types
{
	static const uint16_t soldier = 28531;
	static const uint16_t hellicopter = 25960;
	static const uint16_t car = 24931;
	static const uint16_t tank = 24948;
	static const uint16_t airplane = 26977;
	static const uint16_t ship = 26739;
};

struct Stance
{
	static const uint64_t Standing = 0x3E94C0D6;
	static const uint64_t Sitting = 0x3DB40510;
	static const uint64_t Lying = 0x3D59BE6A;
};

struct Quality
{
	static const uint8_t Pristine = -1;
	static const uint8_t Worn = 1;
	static const uint8_t Damaged = 2;
	static const uint8_t BadlyDamaged = 3;
	static const uint8_t Ruined = 4;
};

struct DamageParts
{
	static const uint32_t soldier = 0x2C;
	static const uint32_t vehicle = 0x60;
};

struct DeletedObject
{
	uint64_t Entity;
	Vector3 Position;
};

uint64_t pCamera = 0;

vector<DeletedObject>ListDeletedObjects;
uint32_t CountDeletedObjects = 0;

class EnfusionEngine
{
public:
	static uint64_t GetWorld();
	static uint64_t GetNetworkManager();
	static uint64_t GetNetworkClient();
	static uint64_t GetNetworkClientScoreBoard();
	//static string GetNetworkClientServerName();
	static uint64_t GetCountOfPlayers();
	static uint64_t AIUnitInfo(uint64_t Entity);
	static string GetPlayerName(uint64_t Entity);
	//static string GetItemName(uint64_t Entity); // my own
	static uint64_t GetPlayerIdentityNetworkId(uint64_t Identity);
//	static string GetPlayerIdentityPlayerName(uint64_t Identity);
	static uint64_t GetIdentity(uint64_t networkId);
	static uint64_t SetUnitRecoilCoefficient(float value);
	static uint64_t NightVision();
	static uint64_t GetCamera();
	static uint64_t GetCameraEntry();
	static uint64_t InGameUI();
	static uint64_t StaticMapMain();
	static uint64_t GetCameraOn();
	static uint64_t GetLocalPlayer();
	static uint64_t GetLocalPlayerVisualState();
	static bool ForceRefuelVehicle();
	static bool ForceRepairVehicle();
	static bool HealYourself();
	static bool SetVelocity(uint64_t Entity, Vector3 velocity);
	static uint64_t GetInventory(uint64_t Entity);
	static uint64_t EnableStamina(float a);
	static string GetItemInHands(uint64_t Entity);
	static uint64_t GetEntity(uint64_t PlayerList, uint64_t SelectedPlayer);
	static uint64_t GetNetworkId(uint64_t Entity);
	static string GetEntityTypeName(uint64_t Entity);
	static string GetStance(uint64_t Entity);
	static string GetCleanName(uint64_t Entity);
	static uint8_t GetDamagePartObjectsCount(uint64_t Entity);
	static uint64_t GetType(uint64_t Entity);
	static uint64_t DisplayMainMap();
	static string GetTypeName(uint64_t Entity);
	static string GetModelName(uint64_t Entity);
	static Vector3 GetPosition(uint64_t Entity, bool islocal);
	static Vector3 GetCursorPosition();
	static Vector3 GetLastClickOnMapPosition();
	static Vector3 GetHeadPosition(uint64_t Entity);
	static bool DestoryTargetObject();
	static uint64_t GetTargetObjectOn();
	static	uint64_t GetLocalTargetObject();
	static	bool  DeleteTargetObject();
	static bool InvisibleMode(bool mode);
	static float GetDistanceToMe(Vector3 Entity);
	static float GetDistanceFromTo(Vector3 From, Vector3 To);
	static bool IsLocalPlayer(uint64_t playerId);
	static uint64_t GetItemTable();
	static uint64_t GetItemTableSize();
	static uint64_t NearEntityTable();
	static uint64_t NearEntityTableSize();
	static uint64_t FarEntityTable();
	static uint64_t FarEntityTableSize();
	static uint64_t BulletTable();
	static uint64_t BulletTableSize();
	static uint64_t GetVehicleOn();
	static uint64_t GetLocalPlayerVehicle();
	static bool SetTerrainGrid(float value);
	static bool IsMapOpen();
	static uint64_t GetDamagePart(uint64_t Entity);
	static bool SecuredGodMode(bool variable);
	static bool SecuredVehicleGodMode(bool variable);
	static void ForceVehicleUnlock(uint64_t Entity);
	static uint8_t  GetHealth(uint64_t Entity);
	static uint64_t GetRawTotalDamage(uint64_t Entity);
	static vector<uint64_t> GetAllItems();
	static vector<uint64_t> GetNearEntityes();
	static vector<uint64_t> GetFarEntityes();
	static vector<uint64_t> GetAllEntityes();
	static vector<uint64_t> GetAllBullets();
	static Vector3 WorldToScreen(Vector3 Position);
	static void SpeedHack(float Speed);
	//static void MovCameraUp();
	//static void MovCameraDown();
	//static void MovCameraRight();
	//static void MovCameraLeft();
    //static void MovCameraForward();
	//static void MovCameraBackward();
	//static void SetTerrainGrid(float value);
	//static float CameraSpeed;
	//static bool SetCameraMovSpeed(float Speed);
	static uint8_t GetQuality(uint64_t Entity);
	static bool SetPosition(uint64_t Entity, Vector3 to);
	static bool DefaultSilentAim(uint64_t Entity);
	static bool SmartSilentAim(uint64_t Entity);
	static bool IsDead(uint64_t Entity);
	static bool RemoveGravity();
	static Vector3 GetInvertedViewRight();
	static Vector3 GetInvertedViewUp();
	static Vector3 GetInvertedViewForward();
	static Vector3 GetViewportSize();
	static Vector3 GetInvertedViewTranslation();
	static Vector3 GetProjectionD1();
	static Vector3 GetProjectionD2();
	static string GetDirection();
	static float RadiansToDegrees(float value);

	static bool RestoreAllDeletedObjects();

private:
	static string ReadArmaString(uint64_t address);
};

uint64_t EnfusionEngine::GetWorld() {
	return EnfusionProcess::ReadData<uint64_t>(
		ModuleBase + off_world);
}

uint64_t EnfusionEngine::GetNetworkManager() {
	return EnfusionProcess::ReadData<uint64_t>(
		ModuleBase + off_networkmanager);
}

uint64_t EnfusionEngine::GetNetworkClient() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkManager() + off_networkmanager_networkclient);
}

uint64_t  EnfusionEngine::GetNetworkClientScoreBoard() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkClient() + off_networkclient_scoreboard);
}

/*
string EnfusionEngine::GetNetworkClientServerName() {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkClient() + off_networkclient_servername)).c_str();
}
*/

uint64_t EnfusionEngine::GetCountOfPlayers() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkClientScoreBoard() + off_sortedobject_entity);
}

/*
string EnfusionEngine::GetPlayerName(uint64_t Entity) {

	return GetPlayerIdentityPlayerName(
		EnfusionEngine::GetNetworkId(Entity)).c_str();
}
*/

/*
string EnfusionEngine::GetItemName(uint64_t Entity) {

	return GetItemName(
		EnfusionEngine::GetNetworkId(Entity)).c_str();
}
*/

bool EnfusionEngine::InvisibleMode(bool mode)
{
	if (mode) { EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x14C, 3); }
	else { EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x14C, 2); }
	return true;
}

uint64_t EnfusionEngine::GetPlayerIdentityNetworkId(uint64_t Identity) {
	return EnfusionProcess::ReadData<uint64_t>(Identity + off_playeridentity_networkid);
}

/*
string EnfusionEngine::GetPlayerIdentityPlayerName(uint64_t Identity) {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(Identity + off_playeridentity_playername));
}
*/

uint64_t EnfusionEngine::GetIdentity(uint64_t networkId) {
	for (uint64_t i = 0; i < EnfusionEngine::GetCountOfPlayers(); i++) {
		uint64_t tempIdentity = EnfusionEngine::GetPlayerIdentityNetworkId(
			EnfusionProcess::ReadData<uint64_t>(
				EnfusionEngine::GetNetworkClientScoreBoard() + i * off_networkclient_playeridentity_size));

		if (tempIdentity == networkId)
			return  tempIdentity;
	}
}

uint64_t EnfusionEngine::GetCameraOn() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_cameraon);
}

uint64_t EnfusionEngine::GetVehicleOn() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + 0x26e8);
}

uint64_t EnfusionEngine::GetTargetObjectOn() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::InGameUI() + 0x20);
}

uint64_t EnfusionEngine::GetCamera() {
	if (pCamera == 0)
	{
		pCamera = EnfusionProcess::ReadData<uint64_t>(
			EnfusionEngine::GetWorld() + off_world_camera);

		return EnfusionProcess::ReadData<uint64_t>(
			EnfusionEngine::GetWorld() + off_world_camera);
	}
	else
	{
		return pCamera;
	}
}

uint64_t EnfusionEngine::GetCameraEntry() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetLocalPlayer() + off_entity_cameraentry);
}

bool EnfusionEngine::IsDead(uint64_t Entity)
{
	if (EnfusionProcess::ReadData<uint8_t>(Entity + off_entity_isdead))
	{
		return true;
	} 
	else
	{ return false; }
}

bool EnfusionEngine::SetTerrainGrid(float value)
{
	EnfusionProcess::WriteFloat(EnfusionEngine::GetWorld() + off_world_setteraingrid, value);
	return true;
}

string EnfusionEngine::GetStance(uint64_t Entity)
{
	uint32_t _tempstance = EnfusionProcess::ReadData<uint32_t>(
		EnfusionProcess::ReadData<uint64_t>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + 0x78) + 0x38) + 0x34);

	if (_tempstance == Stance::Standing)
		return META_STRING("Standing");
	else if (_tempstance == Stance::Sitting)
		return META_STRING("Sitting");
	else if (_tempstance == Stance::Lying)
		return META_STRING("Lying");
	else
		return META_STRING("Unknown");
}

uint8_t EnfusionEngine::GetQuality(uint64_t Entity)
{
	return EnfusionProcess::ReadData<uint8_t>(Entity + 0xF4);
}

uint64_t EnfusionEngine::GetRawTotalDamage(uint64_t Entity)
{
	return EnfusionProcess::ReadData<uint64_t>(Entity + 0xF0);
}


uint8_t EnfusionEngine::GetHealth(uint64_t Entity)
{
	uint8_t _tempHealth = (uint8_t)abs(
		EnfusionProcess::ReadData<float>(
			EnfusionEngine::GetRawTotalDamage(
				Entity) + 0x0) * 100 - 100);

	if (!EnfusionEngine::GetRawTotalDamage(Entity)) {
		return 100;
	}

	if (_tempHealth > 100) {
		return 100;
	}

	if (_tempHealth < 0) {
		return 100;
	}

	return _tempHealth;
}

bool EnfusionEngine::SetVelocity(uint64_t Entity, Vector3 velocity)
{	
	EnfusionProcess::WriteFloat(EnfusionEngine::GetLocalPlayerVisualState() + 0x54, velocity.x);
	EnfusionProcess::WriteFloat(EnfusionEngine::GetLocalPlayerVisualState() + 0x58, velocity.y);
	EnfusionProcess::WriteFloat(EnfusionEngine::GetLocalPlayerVisualState() + 0x5C, velocity.z);
	return true;
}

bool EnfusionEngine::RemoveGravity()
{
	EnfusionEngine::SetVelocity(EnfusionEngine::GetLocalPlayer(), Vector3(0.001f, 0.001f, 0.001f));
	return true;
}

/*

bool EnfusionEngine::SetCameraMovSpeed(float Speed) {
	EnfusionEngine::CameraSpeed = Speed;
	return true;
}

float EnfusionEngine::CameraSpeed = 1.0f;

void EnfusionEngine::MovCameraUp() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown, updown + EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraDown() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown, updown - EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraRight() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright, updown + EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraLeft() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright, updown - EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraForward() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward, updown - EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraBackward() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward, updown + EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::SetTerrainGrid(float value) {
	EnfusionProcess::WriteData<float>(EnfusionEngine::GetWorld() + off_world_terraingrid, value); //0 - remove 12 - set
}
*/

uint64_t EnfusionEngine::GetLocalPlayer() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetCameraOn() + off_sortedobject_entity);
}

uint64_t EnfusionEngine::GetLocalPlayerVehicle() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetVehicleOn() + off_sortedobject_entity);
}


uint64_t EnfusionEngine::GetLocalTargetObject() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetTargetObjectOn() + off_sortedobject_entity);
}

bool EnfusionEngine::RestoreAllDeletedObjects()
{
	for (DeletedObject Object : ListDeletedObjects) {
		EnfusionEngine::SetPosition(Object.Entity, Object.Position);
	} 
	ListDeletedObjects.clear();
	return true;
}

bool EnfusionEngine::HealYourself()
{
	for (int objectParts = 0; objectParts < EnfusionEngine::GetDamagePartObjectsCount(
		EnfusionEngine::GetLocalPlayer()); objectParts++)
	{
		float _tempDamageObjectPart = EnfusionProcess::ReadData<float>(
			EnfusionEngine::GetDamagePart(
				EnfusionEngine::GetLocalPlayer()) + (objectParts * 0x4));

		if (_tempDamageObjectPart != 0.0f) {
			EnfusionProcess::WriteFloat(
				EnfusionEngine::GetDamagePart(
					EnfusionEngine::GetLocalPlayer()) + (objectParts * 0x4), 0.0f);
		}
	}
	return true;
}



bool EnfusionEngine::DestoryTargetObject()
{/*

	for (int objectParts = 0; objectParts < EnfusionEngine::GetDamagePartObjectsCount(
		EnfusionEngine::GetLocalTargetObject()); objectParts++)
	{
		float _tempDamageObjectPart = EnfusionProcess::ReadData<float>(
			EnfusionEngine::GetDamagePart(
				EnfusionEngine::GetLocalTargetObject()) + (objectParts * 0x4));

		if (_tempDamageObjectPart != 0.0f) {
			EnfusionProcess::WriteFloat(
				EnfusionEngine::GetDamagePart(
					EnfusionEngine::GetLocalTargetObject()) + (objectParts * 0x4), 1.0f);
		}
	}
	*/
	return true;
}

bool EnfusionEngine::DeleteTargetObject()
{
	DeletedObject _tempDeletedObject;
	_tempDeletedObject.Entity = GetLocalTargetObject();
	_tempDeletedObject.Position = EnfusionEngine::GetPosition(GetLocalTargetObject(), TRUE);

	if (EnfusionEngine::GetPosition(GetLocalTargetObject(), TRUE) != Vector3(-9999.0f, -9999.0f, -9999.0f)) {
		ListDeletedObjects.push_back(_tempDeletedObject);
	}

	EnfusionEngine::SetPosition(GetLocalTargetObject(), Vector3(-9999.0f, -9999.0f, -9999.0f));
	return true;
}

uint64_t EnfusionEngine::GetLocalPlayerVisualState() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetLocalPlayer() + off_entity_futurevisualstate);
}

uint64_t EnfusionEngine::GetEntity(uint64_t PlayerList, uint64_t SelectedPlayer) {
	return EnfusionProcess::ReadData<uint64_t>(PlayerList + SelectedPlayer * off_sortedobject_entity);
}

uint64_t EnfusionEngine::GetNetworkId(uint64_t Entity) {
	return EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_networkid);
}

uint64_t EnfusionEngine::GetInventory(uint64_t Entity) {
	return EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_inventory);
}


string EnfusionEngine::GetItemInHands(uint64_t Entity) {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(EnfusionProcess::ReadData<uint64_t>(
			EnfusionEngine::GetInventory(Entity) + off_inventory_iteminhands)
			+ off_entity_rendererentitytype) + off_entitytype_cleanname)).c_str();
}

string EnfusionEngine::GetEntityTypeName(uint64_t Entity) {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(
			Entity + off_entity_rendererentitytype)
		+ off_entitytype_configname)).c_str();
}

uint64_t EnfusionEngine::GetType(uint64_t Entity) {
	return EnfusionProcess::ReadData<uint16_t>(
		EnfusionProcess::ReadData<uint64_t>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + off_entity_rendererentitytype)
			+ off_entitytype_configname) + 0x10);
}

Vector3 EnfusionEngine::GetInvertedViewRight() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewright));
}

Vector3 EnfusionEngine::GetInvertedViewUp() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewup));
}

Vector3 EnfusionEngine::GetInvertedViewForward() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewforward));
}

Vector3 EnfusionEngine::GetViewportSize() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewportsize));
}

Vector3 EnfusionEngine::GetInvertedViewTranslation() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewtranslation));
}

Vector3 EnfusionEngine::GetProjectionD1() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_projection_d1));
}

Vector3 EnfusionEngine::GetProjectionD2() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_projection_d2));
}

Vector3 EnfusionEngine::WorldToScreen(Vector3 Position)
{
	//convert world cords to screen cords :)

	if (!EnfusionEngine::GetCamera())
		return Vector3();

	Vector3 temp = Position - EnfusionEngine::GetInvertedViewTranslation();

	float x = temp.Dot(EnfusionEngine::GetInvertedViewRight());
	float y = temp.Dot(EnfusionEngine::GetInvertedViewUp());
	float z = temp.Dot(EnfusionEngine::GetInvertedViewForward());

		return Vector3(
			EnfusionEngine::GetViewportSize().x * (1 + (x / EnfusionEngine::GetProjectionD1().x / z)),
			EnfusionEngine::GetViewportSize().y * (1 - (y / EnfusionEngine::GetProjectionD2().y / z)),
			z);
}

float EnfusionEngine::RadiansToDegrees(float radians) {
	float degrees;
	degrees = ((radians * 180) / 3.14159265358979323846);
	return degrees;
}

string EnfusionEngine::GetDirection()
{
	//get ur direction view

	Vector3 viewAnglesRadians, viewAngle;
	viewAnglesRadians.x = atan2(
		EnfusionEngine::GetInvertedViewRight().z, EnfusionEngine::GetInvertedViewRight().x);
	viewAngle.x = EnfusionEngine::RadiansToDegrees(viewAnglesRadians.x);
	viewAnglesRadians.y = atan2(
		EnfusionEngine::GetInvertedViewForward().y, EnfusionEngine::GetInvertedViewUp().y);
	viewAngle.y = EnfusionEngine::RadiansToDegrees(viewAnglesRadians.y);

	if (viewAngle.x >= 0 && viewAngle.x <= 90) {
		return META_STRING("NW");
	}
	else if (viewAngle.x <= 0 && viewAngle.x >= -90) {
		return META_STRING("NE");
	}
	else if (viewAngle.x >= 90 && viewAngle.x <= 180) {
		return META_STRING("SW");
	}
	else if (viewAngle.x <= -90 && viewAngle.x >= -180) {
		return META_STRING("SE");
	}
}

uint64_t EnfusionEngine::SetUnitRecoilCoefficient(float value)
{
	if (!EnfusionEngine::GetLocalPlayer())
		return 0;

	EnfusionProcess::WriteFloat(
		EnfusionEngine::GetLocalPlayer() + off_entity_recoilcoeff, value);
	return 0;
}

void EnfusionEngine::SpeedHack(float Speed)
{	
	Vector3 curPos = EnfusionEngine::GetPosition(EnfusionEngine::GetLocalPlayer(), TRUE);

	Vector3 newPos = Vector3(
		curPos.x + Speed * EnfusionEngine::GetInvertedViewForward().x,		
		curPos.y + Speed * EnfusionEngine::GetInvertedViewForward().y,
		curPos.z + Speed * EnfusionEngine::GetInvertedViewForward().z);

	SetPosition(EnfusionEngine::GetLocalPlayer(), newPos);
}

void EnfusionEngine::ForceVehicleUnlock(uint64_t Entity)
{
	EnfusionProcess::WriteInt(Entity + 0xDBC, 0);
}

uint64_t EnfusionEngine::AIUnitInfo(uint64_t Entity)
{
	return EnfusionProcess::ReadData<uint64_t>(Entity + 0xA90);
}

string EnfusionEngine::GetPlayerName(uint64_t Entity)
{
	if (!EnfusionEngine::AIUnitInfo(Entity))
		return META_STRING("AI (BOT)");

	return EnfusionEngine::ReadArmaString(EnfusionEngine::AIUnitInfo(Entity));
}

uint64_t EnfusionEngine::EnableStamina(float a)
{
	if (!a)
	{
		if (!EnfusionEngine::GetLocalPlayer())
			return 0;
		
			EnfusionProcess::WriteFloat(EnfusionEngine::GetLocalPlayer() + off_entity_fatigue, 0.0f);
			EnfusionProcess::WriteFloat(EnfusionEngine::GetLocalPlayer() + off_entity_fatiguediff, 1.0f);	
	}

	return 0;
}

uint64_t EnfusionEngine::NightVision()
{
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + 0x1038);
}

uint64_t EnfusionEngine::InGameUI()
{
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_ingameui);
}

uint64_t EnfusionEngine::DisplayMainMap()
{
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_displaymainmap);
}

uint64_t EnfusionEngine::StaticMapMain()
{
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::DisplayMainMap() + off_displaymainmap_staticmapmain);
}

bool EnfusionEngine::IsMapOpen()
{
	return EnfusionProcess::ReadData<uint8_t>(
		EnfusionEngine::GetWorld() + off_world_ismenuopen);
}

bool EnfusionEngine::SecuredGodMode(bool variable)
{
		if (variable) {
			if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayer() + 0x1d0) != 91) {
				EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d0, 91);
			}

			if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayer() + 0x1d4) != 28) {
				EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d4, 28);
			}

			if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayer() + 0x1d5) != -33) {
				EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d5, -33);
			}

			if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayer() + 0x1d6) != 68) {
				EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d6, 68);
			}

			if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayer() + 0x1d7) != 33) {
				EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d7, 33);
			}
		}

		if (!variable) {
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d0, 92);
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d4, -65);
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d5, 74);
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d6, 32);
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayer() + 0x1d7, -65);
		}

		return true;
}

bool EnfusionEngine::SecuredVehicleGodMode(bool variable)
{
	if (variable) {
		if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d0) != 91) {
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d0, 91);
		}

		if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d4) != 28) {
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d4, 28);
		}

		if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d5) != -33) {
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d5, -33);
		}

		if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d6) != 68) {
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d6, 68);
		}

		if (EnfusionProcess::ReadData<INT8>(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d7) != 33) {
			EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d7, 33);
		}
	}

	if (!variable) {
		EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d0, 92);
		EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d4, -65);
		EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d5, 74);
		EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d6, 32);
		EnfusionProcess::WriteInt(EnfusionEngine::GetLocalPlayerVehicle() + 0x1d7, -65);
	}

	return true;
}

uint64_t EnfusionEngine::GetDamagePart(uint64_t Entity)
{
	return EnfusionProcess::ReadData<uint64_t>(Entity + 0x270);
}

uint8_t EnfusionEngine::GetDamagePartObjectsCount(uint64_t Entity)
{
	return EnfusionProcess::ReadData<uint8_t>(Entity + 0x278);
}

float rand_FloatRange(float a, float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

bool EnfusionEngine::ForceRepairVehicle()
{
	for (int objectParts = 0; objectParts < EnfusionEngine::GetDamagePartObjectsCount(EnfusionEngine::GetLocalPlayerVehicle()); objectParts++)
	{
		float _tempDamageObjectPart = EnfusionProcess::ReadData<float>(
			EnfusionEngine::GetDamagePart(
				EnfusionEngine::GetLocalPlayerVehicle()) + (objectParts * 0x4));

		if (_tempDamageObjectPart != 0.0f) {
			EnfusionProcess::WriteFloat(
				EnfusionEngine::GetDamagePart(
					EnfusionEngine::GetLocalPlayerVehicle()) + (objectParts * 0x4), rand_FloatRange(0.009f, 0.125f));
		}
	}
	return true;
}

bool EnfusionEngine::ForceRefuelVehicle()
{
	EnfusionProcess::WriteFloat(
		EnfusionProcess::ReadData<uint64_t>(
			EnfusionEngine::GetLocalPlayerVehicle() + off_entity_futurevisualstate) + 0xC8, 16.0f);
	return true;
}

Vector3 EnfusionEngine::GetLastClickOnMapPosition()
{
	return EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::StaticMapMain() + off_staticmapmain_lastclickposition);
}

Vector3 EnfusionEngine::GetCursorPosition()
{
	return EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::InGameUI() + off_ingameui_cursorposition);
}

Vector3 EnfusionEngine::GetPosition(uint64_t Entity, bool islocal = false)
{
	if(islocal)
		return  Vector3(EnfusionProcess::ReadData<Vector3>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + off_entity_futurevisualstate) + off_visualstate_position));
	if (!islocal)
		return  Vector3(EnfusionProcess::ReadData<Vector3>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + off_entity_renderervisualstate) + off_visualstate_position));
	
}

Vector3 EnfusionEngine::GetHeadPosition(uint64_t Entity)
{
	return  Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionProcess::ReadData<uint64_t>(
			Entity + off_entity_renderervisualstate) + 0x168));

}

float EnfusionEngine::GetDistanceToMe(Vector3 Entity)
{
	return Entity.Distance(
		EnfusionEngine::GetPosition(EnfusionEngine::GetLocalPlayer(), TRUE));
}

float EnfusionEngine::GetDistanceFromTo(Vector3 From, Vector3 To)
{
	return From.Distance(To);
}


string EnfusionEngine::GetTypeName(uint64_t Entity) {

	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_rendererentitytype) + off_entitytype_typename)).c_str();
}



string EnfusionEngine::GetModelName(uint64_t Entity) {

	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_rendererentitytype) + off_entitytype_modelname)).c_str();
}

string EnfusionEngine::GetCleanName(uint64_t Entity) {

	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_rendererentitytype) + off_entitytype_cleanname)).c_str();
}


uint64_t EnfusionEngine::BulletTable() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_bullettable);
}

uint64_t EnfusionEngine::BulletTableSize() {
	return sizeof(EnfusionEngine::BulletTable());
}

uint64_t EnfusionEngine::GetItemTable()
{
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_itemtable);
}

uint64_t EnfusionEngine::GetItemTableSize() {
	return sizeof(EnfusionEngine::GetItemTable()) * 3;
}


uint64_t EnfusionEngine::NearEntityTable() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_nearanimaltable);
}

uint64_t EnfusionEngine::NearEntityTableSize() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_nearanimaltable + off_sortedobject_entity);
}

uint64_t EnfusionEngine::FarEntityTable() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_faranimaltable);
}

uint64_t EnfusionEngine::FarEntityTableSize() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_faranimaltable + off_sortedobject_entity);
}

vector<uint64_t> EnfusionEngine::GetAllItems()
{
	vector<uint64_t> arrayList;

	for (uint64_t ItemId = NULL; ItemId < EnfusionEngine::GetItemTableSize(); ++ItemId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::GetItemTable(), ItemId));
	}

	return arrayList;
}

vector<uint64_t> EnfusionEngine::GetNearEntityes() // get entityes from 0 - 100m
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::NearEntityTableSize(); ++playerId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::NearEntityTable(), playerId));
	}
	return arrayList;
}

vector<uint64_t> EnfusionEngine::GetFarEntityes() // get entityes from 100 - 1000 & 1635m
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::FarEntityTableSize(); ++playerId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::FarEntityTable(), playerId));
	}
	return arrayList;
}

bool EnfusionEngine::SetPosition(uint64_t Entity, Vector3 TargetPosition)
{
	uint64_t _temppos = EnfusionProcess::ReadData<uint64_t>(
		Entity + off_entity_futurevisualstate);

		EnfusionProcess::WriteFloat(_temppos + 0x2c, TargetPosition.x); //x
		EnfusionProcess::WriteFloat(_temppos + 0x30, TargetPosition.y); //z
		EnfusionProcess::WriteFloat(_temppos + 0x34, TargetPosition.z); //y
	
	return true;
}

bool EnfusionEngine::DefaultSilentAim(uint64_t Entity)
{
	for (uint64_t pBulletId = NULL; pBulletId < EnfusionEngine::BulletTableSize(); ++pBulletId) {

		EnfusionEngine::SetPosition(EnfusionEngine::GetEntity(EnfusionEngine::BulletTable(), pBulletId), EnfusionEngine::GetHeadPosition(Entity));
		
	}
	return true;
}

bool EnfusionEngine::SmartSilentAim(uint64_t Entity)
{
	for (uint64_t pBulletId = NULL; pBulletId < EnfusionEngine::BulletTableSize(); ++pBulletId) {

		uint64_t _tempUnitInfo = EnfusionEngine::AIUnitInfo(Entity);
		uint64_t _tempBulletEntity = EnfusionEngine::GetEntity(EnfusionEngine::BulletTable(), pBulletId);

		EnfusionProcess::WriteInt64(_tempBulletEntity + 0xA90, _tempUnitInfo);

		EnfusionEngine::SetPosition(_tempBulletEntity, EnfusionEngine::GetHeadPosition(Entity));

	}
	return true;
}

vector<uint64_t> EnfusionEngine::GetAllBullets()
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::BulletTableSize(); ++playerId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::BulletTable(), playerId));
	}

	return arrayList; 
}

bool EnfusionEngine::IsLocalPlayer(uint64_t playerId)
{
	if (playerId == 0) {
		return true;
	} else { return false; }
}

vector<uint64_t> EnfusionEngine::GetAllEntityes()
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::NearEntityTableSize(); ++playerId) {
		if (playerId != 0) { // check if entity != localplayer
			uint64_t targetentity = EnfusionEngine::GetEntity(EnfusionEngine::NearEntityTable(), playerId);
			uint64_t currenttype = EnfusionEngine::GetType(targetentity);

			if (currenttype == Types::soldier |
				currenttype == Types::hellicopter |
				currenttype == Types::car |
				currenttype == Types::airplane |
				currenttype == Types::ship |
				currenttype == Types::tank)
			{
				arrayList.push_back(targetentity);
			}
		}
	}

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::FarEntityTableSize(); ++playerId) {
		uint64_t targetentity = EnfusionEngine::GetEntity(EnfusionEngine::FarEntityTable(), playerId);
		uint64_t currenttype = EnfusionEngine::GetType(targetentity);

		if (currenttype == Types::soldier |
			currenttype == Types::hellicopter |
			currenttype == Types::car |
			currenttype == Types::airplane |
			currenttype == Types::ship |
			currenttype == Types::tank)
		{
			arrayList.push_back(targetentity);
		}
	}

	return arrayList;
}


std::string EnfusionEngine::ReadArmaString(uint64_t address)
{
	int length = EnfusionProcess::ReadData<uint64_t>(address + off_length); 
	char* p = KeInterface::ReadVirtualMemory<char*>(processId, address + off_text, sizeof(p));
	const char* add = reinterpret_cast<const char*>(&p);
	std::string str = add;
	string s2 = str.substr(0, 8);

	return s2;
//	std::cout << std::dec << i << ":" << nameString << std::endl;
}





















