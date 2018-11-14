#include "main.h"

int GetAsset(ClientPlayer * LocalPlayer, Type uType)
{
	if (uType == Primary)
	{
		int Primary = (int)LocalPlayer + 0x1218;

		if (!Primary)
			return 0;

		return *(int*)Primary;
	}

	if (uType == Secondary)
	{
		int Secondary = (int)LocalPlayer + 0x1288;

		if (!Secondary)
			return 0;

		return *(int*)Secondary;
	}

	if (uType == Gadget1)
	{
		int Gadget1 = (int)LocalPlayer + 0x12f8;

		if (!Gadget1)
			return 0;

		return *(int*)Gadget1;
	}

	if (uType == Gadget2)
	{
		int Gadget2 = (int)LocalPlayer + 0x1448;

		if (!Gadget2)
			return 0;

		return *(int*)Gadget2;
	}

	if (uType == Grenade)
	{
		int Grenade = (int)LocalPlayer + 0x14b8;

		if (!Grenade)
			return 0;

		return *(int*)Grenade;
	}

	if (uType == Knife)
	{
		int Grenade = (int)LocalPlayer + 0x1528;

		if (!Grenade)
			return 0;

		return *(int*)Grenade;
	}

	return 0;
}

SoldierWeaponUnlockAsset* GetSoldierWeaponUnlockAsset(int debugID)
{
	ResourceManager* rManager = ResourceManager::GetInstance();

	for (int i = 0; i < 50; ++i)
	{
		ResourceManager::Compartment* pComp = rManager->m_compartments[i];

		if (!MmIsAddressValidPtr(pComp))
			continue;

		for (size_t x = 0; x < pComp->m_objects.size(); ++x)
		{
			std::string TypeName = pComp->m_objects[x]->GetType()->m_InfoData->m_Name;

			if (TypeName == "SoldierWeaponUnlockAsset")
			{
				SoldierWeaponUnlockAsset* Asset = (SoldierWeaponUnlockAsset*)pComp->m_objects[x];

				if (!MmIsAddressValidPtr(Asset))
					continue;

				if (Asset->debugID == debugID) return Asset;
			}
		}
	}
	return 0;
}

bool SetUnlockAsset(ClientPlayer * LocalPlayer, Type UType, SoldierWeaponUnlockAsset* UnlockAssetToSet)
{
	int VeniceCustomization = *(int*)((int)LocalPlayer + 0x700);

	if (!MmIsAddressValidPtr((void*)VeniceCustomization))
		return false;

	for (int vSize = 0; vSize < 820; vSize++)
	{
		if (*(int*)(VeniceCustomization + 0x4 * (int)vSize) == GetAsset(LocalPlayer, UType))
		{
			void* SetHere = (void*)(VeniceCustomization + 0x4 * (int)vSize);

			if (!MmIsAddressValidPtr(SetHere))
				return false;

			*(int*)SetHere = (int)UnlockAssetToSet;

			return true;
		}
	}
	return false;
}

void SetPrimary()
{
	SetWeapon(Primary, Gun[PrimaryArrayEnumarator]);
}

void SetSecondary()
{
	SetWeapon(Secondary, Gun[SecondaryArrayEnumarator]);
}

void SetGadet1()
{
	SetWeapon(Gadget1, Gun[Gadget1ArrayEnumarator]);
}

void SetGadget2()
{
	SetWeapon(Gadget2, Gun[Gadget2WeaponArrayEnumarator]);
}

void SetGrenade()
{
	SetWeapon(Grenade, Gun[GrenadeWeaponArrayEnumarator]);
}

void SetWeapon(Type WeaponType, int debugID)
{
	SoldierWeaponUnlockAsset* Asset = GetSoldierWeaponUnlockAsset(debugID);

	if (!MmIsAddressValidPtr(Asset))
		return;

	if (SetUnlockAsset(GetLocalPlayer(), WeaponType, Asset))
		GetFullAmmo();
}