#pragma once

enum Type : int
{
	Primary,
	Secondary,
	Gadget1,
	Gadget2,
	Grenade,
	Knife
};

SoldierWeaponUnlockAsset* GetSoldierWeaponUnlockAsset(int debugID);

void SetPrimary();

void SetSecondary();

void SetGadet1();

void SetGadget2();

void SetGrenade();

void SetWeapon(Type WeaponType, int debugID);
