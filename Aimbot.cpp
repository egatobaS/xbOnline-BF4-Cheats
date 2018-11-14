#include "Main.h"

float fovSize_ID = 1000;
WeaponSway::Deviation* pRecoil = 0;
WeaponSway::Deviation *pSpread = 0;

bool AutoWall(Vector3& from, Vector3& to)
{
	bool(*RayCast)(int _this, const char *ident, int, Vector4 *start, Vector4 *end, RayCastHit *hit, int flags, int) = (bool(*)(int _this, const char *ident, int, Vector4 *start, Vector4 *end, RayCastHit *hit, int flags, int))0x88BD30A0;

	Vector4 final_from = Vector4(from.x, from.y, from.z, 0);
	Vector4 final_to = Vector4(to.x, to.y, to.z, 0);

	Vector3 direction(0, 0, 0);

	direction.x = to.x - from.x;
	direction.y = to.y - from.y;
	direction.z = to.z - from.z;

	direction.Normalize();
	direction.x /= 10.0f;
	direction.y /= 10.0f;
	direction.z /= 10.0f;

	//NoCheck = 0x0,
	//CheckDetailMesh = 0x1,
	//IsAsyncRaycast = 0x2,
	//DontCheckWater = 0x4,
	//DontCheckTerrain = 0x8,
	//DontCheckRagdoll = 0x10,
	//DontCheckCharacter = 0x20,
	//DontCheckGroup = 0x40,
	//DontCheckPhantoms = 0x80,
	//FORCE32BIT = 0x7FFFFFFF,
	//AimbotFlags = (0x4 | 0x10 | 0x20 | 0x80)

	int flags = DontCheckCharacter/* AimbotFlags /*| DontCheckTerrain | IsAsyncRaycast | DontCheckGroup*/;

	bool bReturn = false;

	int iterations = 20;

	RayCastHit* ray = new RayCastHit;

	while ((bReturn = RayCast(*(int*)0x89916E74, "OnGroundState::update", 0, &final_from, &final_to, ray, flags, 0)) && ((ray->m_Material.isSeeThrough() || ray->m_Material.isPenetrable()) && Vector3(ray->m_Position.x, ray->m_Position.y, ray->m_Position.z) == to))
	{
		if (!--iterations) return true;

		final_from.x = ray->m_Position.x + direction.x;
		final_from.y = ray->m_Position.y + direction.y;
		final_from.z = ray->m_Position.z + direction.z;
	}

	delete ray;

	return !bReturn;
}

bool IsPlayerInFOV(ClientSoldierEntity* player)
{
	Vector3 ScreenPos;
	Vector3 Position;

	if (!GetBone(player, &Position, BONE_NECK)) {
		Position = player->m_ClientSoliderPrediction->Position;

		Position.y += 1.8f;
	}

	if (WorldToScreen(Position, &ScreenPos))
	{
		if (ScreenPos.x > ((1280.0f / 2) - (fovSize_ID / 2)) &&
			ScreenPos.x < ((1280.0f / 2) + (fovSize_ID / 2)) &&
			ScreenPos.y >((720.0f / 2) - (fovSize_ID / 2)) &&
			ScreenPos.y < ((720.0f / 2) + (fovSize_ID / 2)))
		{
			return true;
		}
	}
	return false;
}

float RealDistanceToCrosshair(ClientSoldierEntity* player)
{
	//if (!MmIsAddressValid(GameRenderer::GetInstance()))
	//	return 0;
	//
	//if (!MmIsAddressValid(GameRenderer::GetInstance()->m_pRenderView))
	//	return 0;
	//
	//Vector3 Origin = Vector3(0, 0, 0);
	//Vector3 ShootSpace = Vector3(0, 0, 0);
	//
	//Origin = player->m_ClientSoliderPrediction->Position;
	//
	//Matrix mTmp = GameRenderer::GetInstance()->m_pRenderView->m_viewMatrixInverse;
	//
	//ShootSpace.x = Origin.x - mTmp.operator()(3, 1);
	//ShootSpace.y = Origin.y - mTmp.operator()(3, 2);
	//ShootSpace.z = Origin.z - mTmp.operator()(3, 3);
	//
	//ShootSpace.Normalize();
	//
	//Vector3 vLeft = Vector3(mTmp.operator()(1, 1), mTmp.operator()(1, 2), mTmp.operator()(1, 3));
	//float Yaw = -asin(vLeft.DotProduct(ShootSpace));
	//float YawDifference = GameRenderer::GetInstance()->m_pRenderView->m_FovY / 4 - Yaw;
	//
	//float RealDistance = abs(sin(YawDifference) * player->m_ClientSoliderPrediction->Position.Distance(GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderPrediction->Position));

	return 0;
}

int ClosestClient(ClientPlayer* LocalPlayer)
{
	int Nearest = -1;

	float nearestDistance = 99999;

	for (int i = 0; i < 24; i++)
	{
		ClientPlayer* Target = GetClientPlayer(i);

		if (!MmIsAddressValidPtr(Target))
			continue;

		if (!isClientAlive(Target))
			continue;

		if (LocalPlayer == Target)
			continue;

		Vector3 Position, PositionL;

		Target->m_pControlledControllable->EngineChamsBehingBigWalls = 0x9F;

		if (!GetBone(Target->m_pControlledControllable, &Position, BONE_NECK) || !GetBone(LocalPlayer->m_pControlledControllable, &PositionL, BONE_HEAD) || !GetBone(LocalPlayer->m_pControlledControllable, &PositionL, BONE_LEFTHAND) || !GetBone(LocalPlayer->m_pControlledControllable, &PositionL, BONE_RIGHTHAND)) {
			PositionL = GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderPrediction->Position;

			PositionL.y += 1.8f;

			Position = Target->m_pControlledControllable->m_ClientSoliderPrediction->Position;

			Position.y += 1.8f;
		}

		isClientWallable[i] = AutoWall(PositionL, Position);

		float distance = GetDistance(Position, PositionL);

		if (Target->m_TeamID != LocalPlayer->m_TeamID)
		{
			if ((bVisibility && (isClientWallable[i])) || !bVisibility)
			{
				if ((distance < nearestDistance))
				{
					nearestDistance = distance;
					Nearest = i;
				}
			}
		}
	}
	return Nearest;
}

float solveQuadratic(float a, float b, float c)
{
	return (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
}

bool custom_isnan(double var)
{
	volatile double d = var;
	return d != d;
}

void CorrectRecoil(Vector2* pAngles, WeaponSway::Deviation* pRecoil)
{
	WeaponFiring* pFiring = GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring;
	if (MmIsAddressValid(pFiring) && MmIsAddressValid(pRecoil))
	{
		if (custom_isnan(asin(pRecoil->m_Yaw)) || custom_isnan(asin(pRecoil->m_Pitch)))
			return;


		pAngles->x += asin(pRecoil->m_Yaw);
		pAngles->y += asin(pRecoil->m_Pitch);
	}
}

void CorrectSpread(Vector2* pAngles, WeaponSway::Deviation* pSpread)
{
	WeaponFiring* pFiring = GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring;
	if (MmIsAddressValid(pFiring) && MmIsAddressValid(pSpread))
	{
		if (custom_isnan(asin(pSpread->m_Yaw)) || custom_isnan(asin(pSpread->m_Pitch)))
			return;

		pAngles->x += pSpread->m_Yaw;
		pAngles->y += pSpread->m_Pitch;
	}
}

void AimCorrection(Vector3 * inVec, Vector3 enemyVelo, Vector3 myVelo, float Distance, float BulletSpeed, float Gravity)
{
	ClientSoliderWeaponComponent *pWeapComp = GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent;
	if (pWeapComp == 0)
		return;

	WeaponFiringData *pFireData = pWeapComp->GetActiveWeapon()->m_pWeapon->m_pWeaponFiringData;
	if (pFireData == 0)
		return;

	ShotConfigData* ShotConfig = pFireData->m_pShotConfigData;
	BulletEntityData *pProjData = ShotConfig->m_pBulletEntityData;
	if (pProjData == 0)
		return;

	inVec->y -= atan2(ShotConfig->m_initialSpeed.y, ShotConfig->m_initialSpeed.z);

	float m_time = Distance / fabsf(BulletSpeed);
	float m_grav = fabsf(Gravity);
	*inVec = *inVec + (enemyVelo * m_time);
	inVec->y += 0.2f * m_grav * m_time * m_time;

	float holdover = solveQuadratic(Gravity / (2 * (BulletSpeed*BulletSpeed)), 1 + (Gravity*inVec->y) / (BulletSpeed*BulletSpeed), (Distance)*Gravity / (2 * (BulletSpeed*BulletSpeed)));
	inVec->y += holdover;
}

void DoAimCorrection(ClientSoldierEntity * mySoldier, ClientSoldierEntity * enemySoldier, Vector3 & enemyVec)
{
	ClientSoliderWeaponComponent *pWeapComp = mySoldier->m_ClientSoliderWeaponComponent;
	if (pWeapComp == 0)
		return;

	WeaponFiringData *pFireData = pWeapComp->GetActiveWeapon()->m_pWeapon->m_pWeaponFiringData;
	if (pFireData == 0)
		return;

	ShotConfigData* ShotConfig = pFireData->m_pShotConfigData;
	BulletEntityData *pProjData = ShotConfig->m_pBulletEntityData;
	if (pProjData == 0)
		return;

	float Gravity = pProjData->m_gravity;
	float Bulletspeed = ShotConfig->m_initialSpeed.z;

	AimCorrection(&enemyVec, enemySoldier->m_ClientSoliderPrediction->Velocity, mySoldier->m_ClientSoliderPrediction->Velocity, mySoldier->m_ClientSoliderPrediction->Position.Distance(enemySoldier->m_ClientSoliderPrediction->Position), Bulletspeed, Gravity);
}

Vector3 *Vec3Normalize(Vector3 *pOut, const Vector3 *pV)
{
	float length = (pV->x * pV->x +
		pV->z * pV->z +
		pV->y * pV->y);

	if (length > 0.0f) {
		length = sqrtf(length);
		pOut->x = pV->x / length;
		pOut->y = pV->y / length;
		pOut->z = pV->z / length;
		return pOut;
	}
	else
	{
		return pOut;
	}
}

bool IsInFOV(Vector3 forward, Vector3 EnemyPos, Vector3 LocalPos, float fov)
{
	Vector3 vec1 = Vector3(0, 0, 0), vec2 = Vector3(0, 0, 0);
	Vec3Normalize(&vec1, &forward);
	Vec3Normalize(&vec2, &(EnemyPos - LocalPos));
	float angle = acos(vec1.DotProduct(vec2));
	angle = D3DXToDegree(angle);

	if (angle > (fov / 2))
		return false;

	return true;
}

bool GetAimPos(ClientPlayer* _EnemyPlayer, Vector2* Angles, Vector3* LocalOrigin, Vector3* Origin)
{
	Vector3 Space;

	if (_EnemyPlayer->m_pControlledControllable != 0)
	{
		if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, BONE_NECK) || !GetBone(GetLocalPlayer()->m_pControlledControllable, LocalOrigin, BONE_HEAD)) {
			*LocalOrigin = GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderPrediction->Position;

			*Origin = _EnemyPlayer->m_pControlledControllable->m_ClientSoliderPrediction->Position;
		}

		if (GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset->debugID != 0xA6784811)
			DoAimCorrection(GetLocalPlayer()->m_pControlledControllable, _EnemyPlayer->m_pControlledControllable, *Origin);

		Space.x = Origin->x - LocalOrigin->x;
		Space.y = Origin->y - LocalOrigin->y;
		Space.z = Origin->z - LocalOrigin->z;

		Angles->x = -atan2(Space.x, Space.z);
		Angles->y = atan2(Space.y, VectorLength2D(&Space));

		return true;
	}
	return false;
}

void Aimbot(ClientPlayer* LocalEntity)
{
	Vector2 Angles = { 0 };
	Vector2 TempAng = { 0 };

	NearestPlayer = ClosestClient(LocalEntity);

	if (NearestPlayer == -1)
	{
		bTriggerBot = false;
		return;
	}

	AimTarget = GetClientPlayer(NearestPlayer);
	ClientCount = NearestPlayer;

	Vector3 LocalOrigin, Origin;

	if (!GetAimPos(AimTarget, &Angles, &LocalOrigin, &Origin))
		return;

	ClientSoliderWeaponComponent* pCSWC = LocalEntity->m_pControlledControllable->m_ClientSoliderWeaponComponent;

	if (!MmIsAddressValidPtr(pCSWC))
		return;

	ClientSoliderWeaponComponent::WeaponHandler* pCAWH = pCSWC->pWeaponHandler;

	if (!MmIsAddressValidPtr(pCAWH))
		return;

	ClientSoldierWeapon* pCSW = pCAWH->WeaponList[pCSWC->m_ActiveSlot];

	if (!MmIsAddressValidPtr(pCSW))
		return;

	if (pCSW->m_pCorrectedFiring->m_FireMode == Reloading)
		return;

	Angles.x -= pCSW->m_pClientSoldierAimingSimulation->m_Sway.x;
	Angles.y -= pCSW->m_pClientSoldierAimingSimulation->m_Sway.y;

	TempAng = Angles;

	if ((bFOVCheck && IsPlayerInFOV(AimTarget->m_pControlledControllable)) || !bFOVCheck)
	{
		if (bAimingRequired)
		{
			if (GetAsyncKeyState(0x5555))
			{
				bTriggerBot = true;

				if (bSilentAimbot)
					pSilent = Angles;
				else
				{
					pCSW->m_pClientSoldierAimingSimulation->m_pFPSAimer->m_AuthoratativeViewAngles = Angles;

					pRecoil = &GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring->m_pSway->m_currentRecoilDeviation;

					//if (MmIsAddressValidPtr(pRecoil))
					//	CorrectRecoil(&pCSW->m_pClientSoldierAimingSimulation->m_pFPSAimer->m_AuthoratativeViewAngles, pRecoil);
				}
			}
			else
				bTriggerBot = false;
		}
		else
		{
			bTriggerBot = true;

			if (bSilentAimbot)
				pSilent = TempAng;
			else
			{
				pCSW->m_pClientSoldierAimingSimulation->m_pFPSAimer->m_AuthoratativeViewAngles = Angles;
				pRecoil = &GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pPrimaryFiring->m_pSway->m_currentRecoilDeviation;

				//if ( MmIsAddressValidPtr(pRecoil))
				//	CorrectRecoil(&pCSW->m_pClientSoldierAimingSimulation->m_pFPSAimer->m_AuthoratativeViewAngles, pRecoil);
			}
		}
	}
}