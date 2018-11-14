#include "main.h"

bool hasVaulted = false;
int TickClientCount = 0;

void TeleportInAir(ClientPlayer* LocalPlayer, float Height)
{
	if ((GetAsyncKeyState(XINPUT_GAMEPAD_RIGHT_THUMB) && GetAsyncKeyState(XINPUT_GAMEPAD_LEFT_THUMB)) && !GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_LEFT) && !MenuBase.isMenuOpened)
	{
		SuperJumpPatchON();

		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_vaultCoords = Vector3(LocalPlayer->m_pControlledControllable->m_ClientSoliderPrediction->Position.x, LocalPlayer->m_pControlledControllable->m_ClientSoliderPrediction->Position.y + Height, LocalPlayer->m_pControlledControllable->m_ClientSoliderPrediction->Position.z);

		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_Unk1 = 0;
		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_Unk2 = 0;
		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_Unk3 = 0;
		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_VaultHeight = 0;
		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_VaultState = 2;

		if (!hasVaulted) {
			TickClientCount = GetTickCount();
			hasVaulted = true;
		}
	}

	if (hasVaulted && (GetTickCount() - TickClientCount) >= 500)
	{
		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_VaultState = 0;

		SuperJumpPatchOff();

		TickClientCount = 0;

		hasVaulted = false;
	}
}

void TeleportToCrossHair(ClientPlayer* LocalPlayer)
{
	Vector3 w2stest = Vector3(0, 0, 0);

	if (GetAsyncKeyState(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		SuperJumpPatchON();

		LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->pWeaponHandler->WeaponList[LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->m_ActiveSlot]->m_pClientSoldierAimingSimulation->m_pSoldierAimingSimulationData->m_AimingRange = 9999.0f;

		if (WorldToScreen(LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->pWeaponHandler->WeaponList[LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->m_ActiveSlot]->m_pClientSoldierAimingSimulation->CrossHair, &w2stest))
		{
			if (LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->pWeaponHandler->WeaponList[LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->m_ActiveSlot]->m_pClientSoldierAimingSimulation->CrossHair != Vector3(0, 0, 0))
				LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_vaultCoords = LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->pWeaponHandler->WeaponList[LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->m_ActiveSlot]->m_pClientSoldierAimingSimulation->CrossHair;

			LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_Unk1 = 0;
			LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_Unk2 = 0;
			LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_Unk3 = 0;
			LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_VaultHeight = 0;
			LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_VaultState = 2;

			if (!hasVaulted) {
				TickClientCount = GetTickCount();
				hasVaulted = true;
			}
		}
	}

	if (hasVaulted && (GetTickCount() - TickClientCount) >= 500)
	{
		LocalPlayer->m_pControlledControllable->m_pClientVaultComponent->m_VaultState = 0;

		SuperJumpPatchOff();

		TickClientCount = 0;

		hasVaulted = false;
	}
}