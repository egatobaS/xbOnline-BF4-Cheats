#include "main.h"

UIRender Drawing;
Detour* DrawingDetour;

Detour* RayCastHookDetour;
pRayCastHook RayCastHookStub;

Detour* BulletHookDetour;
pBulletHook Bullet;

Vector4 Yellow = Vector4(1, 1, 0, 1);

ClientPlayer* AimTarget = { 0 };
int ClientCount = 0;

AddMoveStub AddMoveOriginal;
Detour* AddMoveHook;

Detour* XamInputGetStateDetour;
XamInputGetStateStub XamInputGetStateOriginal;

Detour* UNKDrawingCrash;

pUnkDrawingHook pUnkDrawingStub;

bool bTriggerBot = false;

bool setBitFlag = false;

bool bShoot = false;

int ShootCount = 0;

int filter(const char* cpp, const char* function, EXCEPTION_POINTERS *ExceptionInfo) {

	printf("%s has an exception in %s at address 0x%X\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);

	return EXCEPTION_EXECUTE_HANDLER;
}

void DrawingFix(int r3, int r4, int r5, int r6, int r7, int r8, int r9, int r10, int r11, int r12, int r13, int r14, int r15, int r16, int r17, int r18, int r19, int r20, int r21, int r22, int r23, int r24, int r25, int r26, int r27, int r28, int r29, int r30)
{
	__try
	{
		if (!MmIsAddressValid((PVOID)(*(int*)(r3 + 0x4))))
		{
			return pUnkDrawingStub(r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30);
		}
		else
		{
			return pUnkDrawingStub(r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30);
		}
	}
	__except (filter(__FILE__, __FUNCSIG__, GetExceptionInformation())) 
	{

	}

}

int RayCastHook(int r3, int r4, int r5, int r6, int r7, int r8, int r9, int r10)
{
	__try
	{
		if (isLocalPlayerAlive())
		{
			ClientPlayer* LocalPlayer = GameContext::GetInstance()->m_PlayerManager->m_LocalPlayer;

			*(int*)Addresses->_0x88C06B54 = bNoSpreadFake ? Addresses->_0x48000040 : Addresses->_0x419A0040;
			*(int*)Addresses->_0x89168184 = bNoSway ? Addresses->_0x60000000 : Addresses->_0x419A0020;
			*(int*)Addresses->_0x88B59AEC = bNoBBobbing ? Addresses->_0x39600000 : Addresses->_0x7C8B2378;
			*(int*)Addresses->_0x88C0D9F4 = bNoBBobbing ? Addresses->_0x60000000 : Addresses->_0x39200001;
			*(int*)Addresses->_0x88C0DA00 = bNoBBobbing ? Addresses->_0x60000000 : Addresses->_0x988B0000;

			if (bTeleCrosshair)
				TeleportToCrossHair(LocalPlayer);

			if (bTeleAir)
				TeleportInAir(LocalPlayer, fTeleHeight);

			if (bAimbot)
				Aimbot(LocalPlayer);

			if (bUnlimitedAmmo && (GetAsyncKeyState(XINPUT_GAMEPAD_X) && (LocalPlayer->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset->debugID != 0x7ECAA648 || 0x74E2BFBA)))
				GetFullAmmo();

#if defined(DEVKIT)
			setBitFlag = bFlyHack;

			if (bFlyHack)
				DoFlyHack(GetLocalPlayer());

#endif
		}
	}
	__except (filter(__FILE__, __FUNCSIG__, GetExceptionInformation()))
	{

	}

	return RayCastHookStub(r3, r4, r5, r6, r7, r8, r9, r10);
}

DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState)
{
	DWORD dwResult = XInputGetState(dwUserIndex, pState);

	if (dwUserIndex != 0 || dwResult != 0)
		return dwResult;

	__try
	{
		if (isLocalPlayerAlive())
		{
			if (MenuBase.isMenuOpened) {
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
			}

			if (bAutoShoot)
			{
				if (bTriggerBot)
					pState->Gamepad.bRightTrigger = (bShoot ? 255 : 0);

				if ((GetTickCount() - ShootCount) > GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pWeaponFiringData->m_pShotConfigData->m_RateOfFire / 60)
				{
					ShootCount = GetTickCount();
					bShoot = !bShoot;
				}
			}
		}
	}
	__except (filter(__FILE__, __FUNCSIG__, GetExceptionInformation()))
	{
		
	}

	return dwResult;
}

int BulletHook(int r3, int r4, int r5, int r6, int r7)
{
	__try
	{
		if (isLocalPlayerAlive())
		{
			if (bHealSelf && GetAsyncKeyState(0x6666) && GetLocalPlayer()->m_pControlledControllable->m_pBFClientSoldierHealthComponent->m_fhealth <= 50)
				SendDamageMessage(GetLocalPlayer(), GetLocalPlayer(), -100, 0, 0);

			if (bTeamHeal)
				TeamHealing(GetLocalPlayer());

			if (isClientAlive(AimTarget))
			{
				if (bUnfairAimbot)
				{
					if (!MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()) && !MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon) && !MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier) && !MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset))
						return Bullet(r3, r4, r5, r6, r7);

					SendDamageMessage(AimTarget, GetLocalPlayer(), 9000, !bSpoofKills ? GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset : GetSoldierWeaponUnlockAsset(Spoof[SpoofArrayEnumarator]), bHeadshots ? 1 : 0);
				}
				else
				{
					if (!MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()) && !MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon) && !MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier) && !MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset))
						return Bullet(r3, r4, r5, r6, r7);

					SendDamageMessage(AimTarget, GetLocalPlayer(), GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring->m_pPrimaryFire->m_pShotConfigData->m_pBulletEntityData->m_DamageMaX, GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset, 0);
				}
			}
		}
	}
	__except (filter(__FILE__, __FUNCSIG__, GetExceptionInformation()))
	{

	}

	return Bullet(r3, r4, r5, r6, r7);
}

#if defined(DEVKIT)
void DoFlyHack(ClientPlayer* GetLocalPlayer)
{
	if (GetAsyncKeyState(0x0100))
	{
		MatrixD* Mat = (MatrixD*)&GameRenderer::GetInstance()->m_pRenderView->m_viewMatrixInverse;

		Vector3 vOrigin = Mat->Translation();
		Vector3 vForward = Mat->Forward();
		vForward.Normalize();
		vForward = Vector3(vForward.x * 10, vForward.y * 10, vForward.z * 10);
		Vector3 vRayEnd = vOrigin + vForward;
		Vector3 vDiff = vRayEnd - vOrigin;
		vDiff.Normalize();
		float factor = FlySpeed / sqrt(vDiff.x*vDiff.x + vDiff.y*vDiff.y + vDiff.z*vDiff.z);
		vDiff = Vector3(vDiff.x * factor, vDiff.y * factor, vDiff.z * factor);

		memcpy(&GetLocalPlayer->m_ExtEntryInputState->m_VaultVelocity, &vDiff, 0xC);
		GetLocalPlayer->m_ExtEntryInputState->m_CustomBitFlags = 4474631;
	}
	else
	{
		Vector3 Hax = Vector3(0, 0, 0);
		memcpy(&GetLocalPlayer->m_ExtEntryInputState->m_VaultVelocity, &Hax, 0xC);
		GetLocalPlayer->m_ExtEntryInputState->m_CustomBitFlags = 4474631;
	}
}
#endif

void FixMovement(EntryInputState* pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove)
{
	float deltaView = CurAngle - OldAngle;

	if (CurAngle < OldAngle)
		deltaView = abs(CurAngle - OldAngle);
	else
		deltaView = 6.28319f - abs(OldAngle - CurAngle);

	if (CurAngle > XM_PI)
		deltaView = XM_2PI - deltaView;

	pCmd->m_AnalogInput[3] = cosf(deltaView)*fOldForward + cosf((deltaView)+XM_PIDIV2)*fOldSidemove;
	pCmd->m_AnalogInput[0] = sinf(deltaView)*fOldForward + sinf((deltaView)+XM_PIDIV2)*fOldSidemove;

}

int AddMove(int* streammanagermoveclient, EntryInputState* pMove)
{
	__try
	{
#if defined(DEVKIT)
		if (setBitFlag)
			pMove->m_CustomBitFlags = 4474631;
#endif
		if (isLocalPlayerAlive())
		{
			if (bSilentAimbot)
			{
				if (bTriggerBot)
				{
					ClientSoldierEntity* pCSE = GameContext::GetInstance()->m_PlayerManager->m_LocalPlayer->m_pControlledControllable;
					if (!pCSE->m_IsSprinting)
					{
						float OldAngle = pMove->m_ViewAngles.x;

						pMove->m_ViewAngles.x = (pSilent.x);
						pMove->m_ViewAngles.y = (pSilent.y);

						FixMovement(pMove, pMove->m_ViewAngles.x, OldAngle, pMove->m_AnalogInput[3], pMove->m_AnalogInput[0]);
					}
				}
			}

			if (pAim && NearestPlayer != -1 && isClientAlive(AimTarget))
			{
				if (MmIsAddressValid(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring) && MmIsAddressValid(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring->m_pSway))
				{
					pSpread = &GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring->m_pSway->m_CurrentDispersionDeviation;
					pRecoil = &GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring->m_pSway->m_currentRecoilDeviation;

					if (MmIsAddressValidPtr(pSpread) && MmIsAddressValidPtr(pRecoil))
					{
						CorrectSpread(&pMove->m_ViewAngles, pSpread);
						CorrectRecoil(&pMove->m_ViewAngles, pRecoil);
					}
				}
			}

#if defined(DEVKIT)
			if (ServerCrash)
			{
				pMove->m_ViewAngles.x = 0x7ffffffff;
				pMove->m_ViewAngles.y = 0x7ffffffff;

				ServerCrash = false;
			}
#endif			
		}
	}
	__except (filter(__FILE__, __FUNCSIG__, GetExceptionInformation()))
	{

	}

	return AddMoveOriginal((int)streammanagermoveclient, (int)pMove);
}

bool DrawTargetInfo(int r3)
{
	if (!MmIsAddressValid(GetLocalPlayer()))
		return false;

	if (!MmIsAddressValid(GetLocalPlayer()->m_pControlledControllable))
		return false;

	if (!MmIsAddressValid(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderPrediction))
		return false;

	if (MmIsAddressValid(GetLocalPlayer()->m_pAttachedControllable))
		return false;

	Vector4 ClientInfo = Vector4(20, 0, 505, 345);

	if (!isClientAlive(AimTarget))
		return false;

	if (!MmIsAddressValid(AimTarget->Name))
		return false;

	if (!MmIsAddressValid(AimTarget->m_pControlledControllable))
		return false;


	if (!MmIsAddressValid(AimTarget->m_pControlledControllable->m_ClientSoliderPrediction))
		return false;

	if (!MmIsAddressValid(AimTarget->m_pControlledControllable->m_pBFClientSoldierHealthComponent))
		return false;

	ClientSoliderWeaponComponent* b = AimTarget->m_pControlledControllable->m_ClientSoliderWeaponComponent;

	if (!MmIsAddressValid(b))
		return false;

	ClientSoldierWeapon* ActiveWP = b->GetActiveWeapon();

	if (!MmIsAddressValid(ActiveWP))
		return false;

	if (!MmIsAddressValid(ActiveWP->m_pWeapon))
		return false;

	if (!MmIsAddressValid(ActiveWP->m_pWeapon->m_pModifier))
		return false;

	if (!MmIsAddressValid(ActiveWP->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset))
		return false;

	if (!MmIsAddressValid(ActiveWP->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset->m_Name))
		return false;

	ClientVenicePersistenceManager* pCVPM = ClientVenicePersistenceManager::GetInstance();

	if (!MmIsAddressValid(pCVPM))
		return false;

	ClientPlayerScoreManager* pCPSM = pCVPM->m_pScoreManager;

	if (!MmIsAddressValid(pCPSM))
		return false;

	ClientPlayerScore* pCPS = pCPSM->getScore(AimTarget);

	if (!MmIsAddressValid(pCPS))
		return false;

	char Buffer[0x2000];

	g_snprintf(Buffer, sizeof(Buffer),
		"Client Name: %s\nClient Health: %0.0f\nKills: %i\nDeath: %i\nClient Weapon: %s\nDistance: %f\n%sPosition: %0.2f %0.2f %0.2f\nVelocity: %0.2f",
		AimTarget->Name,
		AimTarget->m_pControlledControllable->m_pBFClientSoldierHealthComponent->m_fhealth,
		pCPS->m_Kills,
		pCPS->m_Deaths,
		AimTarget->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset->m_Name,
		AimTarget->m_pControlledControllable->m_ClientSoliderPrediction->Position.Distance(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderPrediction->Position),
		isClientWallable[ClientCount] ? "Is Client Visible : TRUE\n" : "Is Client Visible : FALSE\n",
		AimTarget->m_pControlledControllable->m_ClientSoliderPrediction->Position.x,
		AimTarget->m_pControlledControllable->m_ClientSoliderPrediction->Position.y,
		AimTarget->m_pControlledControllable->m_ClientSoliderPrediction->Position.z,
		AimTarget->m_pControlledControllable->m_ClientSoliderPrediction->Velocity.Length());

	Drawing.DrawText(Buffer, 15, &ClientInfo, &Vector4(1, 1, 1, 1), &Vector4(0, 0.94901960784, 1, 1), 80.0f);

	return true;
}

void DrawBullets(ClientPlayer* LocalEntity, int USP)
{
	GameContext*  pGContext = GameContext::GetInstance();
	if (!MmIsAddressValid(pGContext))
		return;
	ClientLevel* pLevel = pGContext->m_PlayerLevel;
	if (!MmIsAddressValid(pLevel))
		return;
	void* pWorld = (void*)pLevel->m_pGameWorld;
	if (!MmIsAddressValid(pWorld))
		return;

	EntityIterator<ClientSoldierEntity> flags(pWorld, (void*)0x899D94C0, 0x5c);
	if (flags.front())
	{
		do
		{
			ClientSoldierEntity *pResupplySphere = flags.front()->getObject(Addresses->_0x20);

			if (!MmIsAddressValid(pResupplySphere))
				continue;

			Matrix trans;
			Vector3 Pos;

			ClientVehicleEntity* pEnt = (ClientVehicleEntity*)pResupplySphere;

			pEnt->GetTransform(&trans);
			Pos = Vector3(trans.operator()(3, 0), trans.operator()(3, 1), trans.operator()(3, 2));
			Vector3 ScreenPos = Vector3(0, 0, 0);

			TransformDrawAABB((ClientVehicleEntity*)pResupplySphere, Vector4(1, 0, 0, 1), 1);
		} while (flags.next());
	}
}

int DrawingHook(int r3, int r4, int r5, int r6) //ed 0x91F94DC4 0x4e800020 Egato's black magic
{
	__try
	{
		Drawing.SetSolidTextStyle(r3);

		Vector4 ScoreCoords = Vector4(90, 0, 9000, 700);

		if (isLocalPlayerAlive() || isLocalPlayerInVehicle())
		{
			DrawMenu();

			ClientPlayer* LocalPlayer = GameContext::GetInstance()->m_PlayerManager->m_LocalPlayer;

			*(int*)0x88BE3500 = bOHK ? 0xED8701F2 : 0xED870232;
			*(int*)0x88BE3524 = bOHK ? 0x60000000 : 0x4098000C;
			*(int*)0x886E71D4 = bUAV ? 0x39600001 : 0x39600000;

			if (isLocalPlayerAlive() && !isLocalPlayerInVehicle())
				LocalPlayer->m_pControlledControllable->m_pClientSoldierParachuteComponent->Tweak(bAntiParachute);

			if (bTargetInfo && !MenuBase.isMenuOpened)
				DrawTargetInfo(r3);

			//DrawBullets(GetLocalPlayer(), r3);

			DoEntityDrawings(r3);

		}
	}
	__except (filter(__FILE__, __FUNCSIG__, GetExceptionInformation()))
	{

	}

	return 0;
}



