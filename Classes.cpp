#include "main.h"

bool isLocalPlayerInVehicle()
{
	GameContext* GameContext = GameContext::GetInstance();

	if (!MmIsAddressValidPtr(GameContext))
		return false;

	ClientPlayerManager* PlayerManager = GameContext->m_PlayerManager;

	if (!MmIsAddressValidPtr(PlayerManager))
		return false;

	ClientPlayer* LocalPlayer = PlayerManager->m_LocalPlayer;

	if (!MmIsAddressValidPtr(LocalPlayer))
		return false;

	ClientVehicleEntity* pCVE = LocalPlayer->m_pAttachedControllable;

	if (!MmIsAddressValidPtr(pCVE))
		return false;

	void* HealthComp = pCVE->m_pHealthComp;

	if (!MmIsAddressValidPtr(HealthComp))
		return false;

	return (LocalPlayer->m_pAttachedControllable != NULL);
}

WeaponSway::Deviation* GetRecoil(WeaponSway* pGunSway)
{
	if (!MmIsAddressValid(pGunSway))
		return nullptr;
	return &pGunSway->m_currentRecoilDeviation;
}

WeaponSway::Deviation* GetSpread(WeaponSway* pGunSway)
{
	if (!MmIsAddressValid(pGunSway))
		return nullptr;

	WeaponSway::WeaponFiringUpdateContext m_context;

	unsigned int m_oldSeed = pGunSway->m_random.m_value;

	pGunSway->m_random.m_nextNormalIsValid = 0;

	if (MmIsAddressValid(GameContext::GetInstance()->m_pGameTime))
		m_context.ticks = GameContext::GetInstance()->m_pGameTime->m_ticks;

	pGunSway->primaryFireShotSpawnedCallback(0.0f, true, &m_context);
	pGunSway->m_random.m_value = m_oldSeed;

	return &pGunSway->m_CurrentDispersionDeviation;
}


bool isLocalPlayerAlive()
{
	GameContext* GameContext = GameContext::GetInstance();

	if (!MmIsAddressValidPtr(GameContext))
		return false;

	ClientPlayerManager* PlayerManager = GameContext->m_PlayerManager;

	if (!MmIsAddressValidPtr(PlayerManager))
		return false;

	ClientPlayer* LocalPlayer = PlayerManager->m_LocalPlayer;

	if (!MmIsAddressValidPtr(LocalPlayer))
		return false;

	ClientSoldierEntity* pCSE = LocalPlayer->m_pControlledControllable;

	if (!MmIsAddressValidPtr(pCSE))
		return false;

	if (!MmIsAddressValidPtr(pCSE->m_ClientSoliderPrediction))
		return false;

	if (!MmIsAddressValidPtr(pCSE->m_BoneCollisionComponentData))
		return false;

	if (!MmIsAddressValidPtr(pCSE->m_pClientSpottingComponent))
		return false;

	BFClientSoldierHealthComponent* Health = pCSE->m_pBFClientSoldierHealthComponent;

	if (!MmIsAddressValidPtr(Health))
		return false;

	if (!(Health->m_fhealth > 0.0f))
		return false;

	ClientSoliderWeaponComponent* pCSWC = pCSE->m_ClientSoliderWeaponComponent;

	if (!MmIsAddressValidPtr(pCSWC))
		return false;

	ClientSoliderWeaponComponent::WeaponHandler* pCAWH = pCSWC->pWeaponHandler;

	if (!MmIsAddressValidPtr(pCAWH))
		return false;

	ClientSoldierWeapon* pCSW = pCAWH->WeaponList[pCSWC->m_ActiveSlot];

	if (!MmIsAddressValidPtr(pCSW))
		return false;

	if (!MmIsAddressValid(pCSWC->GetActiveWeapon()))
		return false;

	if (!MmIsAddressValidPtr(pCSW->m_pReplicatedFiring))
		return false;

	if (!MmIsAddressValidPtr(pCSW->m_pCorrectedFiring))
		return false;

	if (!MmIsAddressValidPtr(pCSW->m_pClientSoldierAimingSimulation))
		return false;

	if (!MmIsAddressValidPtr(pCSW->m_pClientSoldierAimingSimulation->m_pFPSAimer))
		return false;

	ClientWeapon* pCW = pCSW->m_pWeapon;

	if (!MmIsAddressValidPtr(pCW))
		return false;

	if (!MmIsAddressValidPtr(pCW->m_pWeaponFiringData))
		return false;

	if (!MmIsAddressValidPtr(pCW->m_pWeaponFiringData->m_pShotConfigData))
		return false;

	if (!MmIsAddressValidPtr(pCSE->m_pClientVaultComponent))
		return false;

	return true;
}

bool isClientAlive(ClientPlayer* Target)
{
	if (!MmIsAddressValidPtr(Target))
		return false;

	if (!MmIsAddressValidPtr(Target->m_pControlledControllable))
		return false;

	if (Target->m_pAttachedControllable != 0)
		return false;

	if (!MmIsAddressValidPtr(Target->m_pControlledControllable->m_BoneCollisionComponentData))
		return false;

	if (!MmIsAddressValidPtr(Target->m_pControlledControllable->m_pBFClientSoldierPhysicsComponent))
		return false;

	if (!MmIsAddressValidPtr(Target->m_pControlledControllable->m_ClientSoliderPrediction))
		return false;

	return true;
}

ClientPlayer* GetLocalPlayer()
{
	GameContext* GameContext = GameContext::GetInstance();
	if (GameContext == 0)
		return NULL;

	ClientPlayerManager* PlayerManager = GameContext->m_PlayerManager;
	if (PlayerManager == 0)
		return NULL;

	return PlayerManager->m_LocalPlayer;
}

ClientPlayer* GetClientPlayer(unsigned int index)
{
	if (index > 24)
		return NULL;

	GameContext* GameContext = GameContext::GetInstance();

	if (!MmIsAddressValidPtr(GameContext))
		return NULL;

	ClientPlayerManager* PlayerManager = GameContext->m_PlayerManager;

	if (!MmIsAddressValidPtr(GameContext))
		return NULL;

	return PlayerManager->m_Players[index];
}