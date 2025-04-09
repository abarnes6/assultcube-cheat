#include "vecs.hpp"

#include <cstdint>
// Created with ReClass.NET 1.2 by KN4CK3R

class N0000004E
{
public:
	char pad_0000[156]; //0x0000
	Vector3 N00000076; //0x009C
	Vector3 N00000077; //0x00A8
	Vector3 N00000078; //0x00B4
	char pad_00C0[920]; //0x00C0
}; //Size: 0x0458

class game
{
public:
	class PLAYER* localplayer; //0x0000
	class PLAYER** otherplayers; //0x0004
	char pad_0008[4]; //0x0008
	uint32_t playerCount; //0x000C
	char pad_0010[44]; //0x0010
}; //Size: 0x003C

class playerlist
{
public:
	char pad_0000[4]; //0x0000
	class PLAYER* N00000D5A; //0x0004
	char pad_0008[1020]; //0x0008
}; //Size: 0x0404

class PLAYER
{
public:
	Vector3 headPos; //0x0004
	Vector3 pureVelocity; //0x0010
	Vector3 scaledVelocity; //0x001C
	Vector3 playerPos; //0x0028
	Vector2 viewAngle; //0x0034
	char pad_003C[176]; //0x003C
	uint32_t health; //0x00EC
	uint32_t armor; //0x00F0
	char pad_00F4[20]; //0x00F4
	uint32_t secondaryRes; //0x0108
	char pad_010C[16]; //0x010C
	uint32_t primaryRes; //0x011C
	char pad_0120[12]; //0x0120
	uint32_t secondaryAmmo; //0x012C
	char pad_0130[16]; //0x0130
	uint32_t primaryAmmo; //0x0140
	char pad_0144[193]; //0x0144
	char playerName[16]; //0x0205
	char pad_0215[335]; //0x0215
	class weapon* equippedWeapon; //0x0364
	char pad_0368[204]; //0x0368

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0434

class weapon
{
public:
	char pad_0000[1028]; //0x0000
}; //Size: 0x0404