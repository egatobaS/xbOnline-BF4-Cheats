#pragma once

extern float fovSize_ID;

extern WeaponSway::Deviation* pRecoil;
extern WeaponSway::Deviation *pSpread;

bool AutoWall(Vector3 & from, Vector3 & to);

int ClosestClient(ClientPlayer * LocalPlayer);

float solveQuadratic(float a, float b, float c);

void CorrectRecoil(Vector2 * pAngles, WeaponSway::Deviation* pRecoil);

void CorrectSpread(Vector2 * pAngles, WeaponSway::Deviation* pSpread);

void AimCorrection(Vector3 * inVec, Vector3 enemyVelo, Vector3 myVelo, float Distance, float BulletSpeed, float Gravity);

void DoAimCorrection(ClientSoldierEntity * mySoldier, ClientSoldierEntity * enemySoldier, Vector3 & enemyVec);

bool GetAimPos(ClientPlayer * _EnemyPlayer, Vector2 * Angles, Vector3 * LocalOrigin, Vector3 * Origin);

void Aimbot(ClientPlayer * LocalEntity);
