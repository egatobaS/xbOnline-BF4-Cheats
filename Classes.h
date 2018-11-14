#pragma once

#define SOLDIER_HEIGHT 1.7f
#define SOLDIER_WIDTH 0.35f
#pragma warning( push )
#pragma warning( disable : 4172)

enum RayCastFlags
{
	NoCheck = 0x0,
	CheckDetailMesh = 0x1,
	IsAsyncRaycast = 0x2,
	DontCheckWater = 0x4,
	DontCheckTerrain = 0x8,
	DontCheckRagdoll = 0x10,
	DontCheckCharacter = 0x20,
	DontCheckGroup = 0x40,
	DontCheckPhantoms = 0x80,
	FORCE32BIT = 0x7FFFFFFF,
	AimbotFlags = (0x4 | 0x10 | 0x20 | 0x80)
};

enum CharacterPoseType
{
	CharacterPoseType_Stand,
	CharacterPoseType_Crouch,
	CharacterPoseType_Prone,
	CharacterPoseTypeCount,
};

enum BONES
{
	BONE_HEAD = 104,
	BONE_NECK = 142,
	BONE_SPINE2 = 7,
	BONE_SPINE1 = 6,
	BONE_SPINE = 5,
	BONE_LEFTSHOULDER = 9,
	BONE_RIGHTSHOULDER = 109,
	BONE_LEFTELBOWROLL = 11,
	BONE_RIGHTELBOWROLL = 111,
	BONE_LEFTHAND = 15,
	BONE_RIGHTHAND = 115,
	BONE_LEFTKNEEROLL = 188,
	BONE_RIGHTKNEEROLL = 197,
	BONE_LEFTFOOT = 184,
	BONE_RIGHTFOOT = 198
};

enum WeaponState
{
	None = 0,
	Idle = 3,
	Shooting = 9,
	Reloading = 11,
	FinishReload = 12
};

enum FireMode
{
	Auto = 0,
	Single = 1,
	Burst = 2
};

enum MaterialFlag
{
	MFSeeThrough = 0x1,
	MFClientDestructable = 0x40000000,
	MFPenetrable = 0x8
};

enum SpotType
{
	SpotType_None, //0x0000
	SpotType_Active, //0x0001
	SpotType_Passive, //0x0002
	SpotType_Radar, //0x0003
	SpotType_Unspottable, //0x0004
	SpotType_Auto, //0x0005
	SpotType_Count //0x0006
};

class ClientMovementComponent;
class OnlineManager;
class WeaponZeroingEntry;
class ZeroingModifier;
class QuatTransform;
class DynamicPhysicsEntity;
class ShotConfigData;
class WeaponFiring;
class UpdatePoseResultData;
class VaultComponentData;
class LevelData;
class ClientVaultComponent;
class Keyboard;
class KeyboardDevice;
class Mouse;
class MouseDevice;
class DifficultyData;
class ClientPlayerScore;
class DifficultyDatas;
class GameSettings;
class VersionData;
class ClientAnimatedSoldierWeaponHandler;
class ClientAntAnimatableComponent;
class ClientSoldierEntity;
class SomeScoreManagerClass;
class ClientPlayerScoreManager;
class ClientSoldierPrediction;
class TypeInfo;
class TypeInfoObject;
class ClientSoldierWeaponsComponent;
class ClientRagDollComponent;
class WeaponModifier;
class ClientControllableEntity;
class BreathControlHandler;
class SoldierAimingSimulation;
class ArrayTypeInfo;
class AntRef;
class JumpingClass;
class UnlockAssetBase;
class GameObject;
class ClientPeer;
class wf48;
class MaterialGridManager;
class SprintInputHandler;
class SkeletonCollisionData;
class ClientPlayerManager;
class MemberInfoData;
class ClientCharacterEntity;
class BoneCollisionComponent;
class BoneCollisionComponentData;
class SkeletonAsset;
struct BoneCollisionData;
struct PitchModifier;
class SoldierAimingSimulationData;
class BluePrintName;
class SomePickUpClass;
class ClientPickupEntity;
class TypeInfoObject;
class TypeInfo;
class MemberInfoData;
class WeaponInfo;
class MemberInfoFlags;
class ClientConnection;
class Message;
class ClientDamageStream;
class DamageData;
class PickupEntityData;
class ClientSpottingTargetComponent;
class WeaponSway;
class BorderInputNode;
class ClientPlayer;
class ShotStats;
class VehicleEntityData;
class Components;
class Temp;
class GameTime;
struct LinearTransform;
class BulletHitInfo;
class MeshAsset;
class WeaponComponentData;
class EntityData;
class WeaponEntityData;
class ClientSoldierWeapon;
class EntryComponent;
class ClientPlayerView;
class FiringFunctionData;
class FireLogicData;

class ResourceManager;
class ExplosiveData;
struct LinearTransform;
class Compartment;
template <typename T> class Array;
class DefibrillatorWeaponData;
class ClientParachuteComponent;
class SoldierEntityData;
class IPhysicsRayCaster;
class ClientWeaponComponent;
class TypeInfo;
class ClientExplosionPackEntity;
class Level;
class ClientGameWorld;
class PickupData;
class HavokPhysicsManager;
class GameWorld;
class IMouse;
class MouseInputBuffer;
class PhysicsEntityTransform;
class AxisAlignedBox;
struct TransformAABBStruct;
class HavokPhysicsData;
class LoadedData;
class PlayerEntryComponentData;
class ClientPlayerEntryComponent;
class ClientWeapon;

struct Vector2
{
	float x, y;
};
typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (Vector3 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	const Vector3& operator* (const float mul)
	{
		return Vector3(this->x *= mul, this->y *= mul, this->z *= mul);
	}

	const bool operator != (Vector3 const &Vector)
	{
		return (this->x != Vector.x && this->y != Vector.y && this->z != Vector.z);
	}
	const Vector3& operator+ (Vector3 const &Vector)
	{
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	const Vector3& operator- (Vector3 const &Vector)
	{
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}
	float Distance(Vector3 const &Vector)
	{
		return sqrt(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const &Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}

	Vector3 crossVector3D(const Vector3 &vec) const
	{
		return Vector3(y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x);
	}

	inline float Length(void) const { return (float)sqrtf(x*x + y * y + z * z); }

	inline Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}

	Vector3 GetForwardVector() const
	{
		return Vector3(2 * (x * z + 1 * y),
			2 * (y * x - 1 * x),
			1 - 2 * (x * x + y * y));
	}
	Vector3 GetUpVector() const
	{
		return Vector3(2 * (x * y - 1 * z),
			1 - 2 * (x * x + z * z),
			2 * (y * z + 1 * x));
	}

	Vector3 GetRightVector() const
	{
		return Vector3(1 - 2 * (y * y + z * z),
			2 * (x * y + 1 * z),
			2 * (x * z - 1 * y));
	}


} Vector3, *PVector3;

typedef struct Vector4
{
	float x, y, z, a;

	Vector4()
	{
		x = y = z = a = 0;
	}
	Vector4(float x, float y, float z, float a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}
	const bool operator== (Vector4 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z && this->a == Vector.z);
	}
	const bool operator != (Vector4 const &Vector)
	{
		return (this->x != Vector.x && this->y != Vector.y && this->z != Vector.z && this->a != Vector.a);
	}
	const Vector4& operator+ (Vector4 const &Vector)
	{
		return Vector4(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z, this->a + Vector.a);
	}
	const Vector4& operator- (Vector4 const &Vector)
	{
		return Vector4(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z, this->a - Vector.a);
	}
	float DotProduct(Vector4 const &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z) + (this->a * Vector.a);
	}

	inline float Length(void) const { return (float)sqrtf(x*x + y * y + z * z + a * a); }

} Vector4, *PVector4;

typedef struct
{
	float r, g, b, a;
} Color;

typedef struct
{
	float height, width, intensity;
} Dimensions;

template< class T > class WeakPtr
{
public:
	T * * m_ptr;

public:
	T * GetData()
	{
		if (!m_ptr)
			return NULL;

		if (!*m_ptr)
			return NULL;

		T* ptr = *m_ptr;

		return (T*)((intptr_t)ptr - 0x4);
	}
};

template <class T> class EntityIterator
{
public:
	class Element
	{
	public:

		Element * m_pFlink;
		Element* m_pBlink;
		__int32  m_Unk1;
		__int32  m_Unk2;

		T* getObject(int size)
		{
			intptr_t pObject = reinterpret_cast<intptr_t>(this);
			pObject -= size;

			return reinterpret_cast<T*>(pObject);
		}
	};

	Element* m_pFirst;
	Element* m_pCurrent;

	EntityIterator(void* pGameWorld, void* pClassInfo, int objectsize)
	{
		// objSize = objectsize;
		int(*GetEntityList)(void* pClassInfo, void* pThis) = (int(*)(void* pClassInfo, void* pThis))0x88A23E30;

		this->m_pFirst = (Element*)GetEntityList(pClassInfo, pGameWorld);
		this->m_pCurrent = this->m_pFirst;
	}

	bool hasNext()
	{
		if (m_pCurrent && m_pCurrent->m_pFlink)
			return true;

		return false;
	}

	Element* first() { return m_pFirst; }
	Element* front() { return m_pCurrent; }
	Element* next()
	{
		if (!m_pFirst)
			return nullptr;

		m_pCurrent = m_pCurrent->m_pFlink;

		return m_pCurrent;
	}
};

class GameTime
{
public:
	uint32_t m_ticks; //0x0000
	uint32_t m_tickFrequency; //0x0004
	uint32_t m_tickIndexInFrame; //0x0008
	uint32_t m_lastTickIndexInFrame; //0x000C
	uint32_t m_tickCountInFrame; //0x0010
	char pad_0014[4]; //0x0014
	float m_deltaTime; //0x0018
	float m_passedDeltaTimeInFrame; //0x001C
}; //Size: 0x0044

class TypeInfo
{
public:
	class MemberInfoData
	{
	public:
		class MemberInfoFlags
		{
		public:
			int m_FlagBits; //0x0000 

		};//Size=0x0040
		char* m_Name; //0x0000 
		MemberInfoFlags m_Flags; //0x0008 

	};//Size=0x0048
	MemberInfoData* m_InfoData; //0x0000 
	TypeInfo* m_Next; //0x0008 
	int m_RuntimeId; //0x0010 
	int m_Flags; //0x0012 
	void* super;
	void* default_instance;
	unsigned int class_id;
	unsigned int last_sub_class_Id;
	void* first_derived_class;
	void* next_silbling_class;
	void* field_infos;
	int total_field_count;
};

class Message
{
public:
	//virtual TypeInfo* GetType();//0

	int m_Vtable;
	DWORD m_Category;//4
	DWORD m_Type;//8
};

enum ChatChannelType
{
	CctSayAll,                     // constant 0x0
	CctTeam,                     // constant 0x1
	CctSquad,                     // constant 0x2
	CctSquadLeader,                     // constant 0x3
	CctAdmin,                     // constant 0x4
	CctGame,                     // constant 0x5
}; // fb::ChatChannelType

class TypeInfoObject
{
public:
	virtual TypeInfo* GetType();
};

class SupplySphereEntityData
{
public:
	char pad01[0x13c];
	char* m_Name;
};

class BluePrintName
{
public:
	char pad[0x8];
	char *shortName;  //U_WEAPONNAME
};

class SomePickUpClass
{
public:
	BluePrintName * m_nameData;
};

class PickupEntityData
{
public:
	char _0x0000[0xD0];
	SomePickUpClass *m_pickup;//0xD0
};
class PickupName
{
public:
	char pad_0000[8]; //0x0000
	char* m_weaponassetname; //0x0008
	char pad_000C[4]; //0x000C
	char* m_name; //0x0010
	char pad_0014[24]; //0x0014
	char* m_bpb_name1; //0x002C
	char* m_bpb_name2; //0x0030
};//Size=0x04C0
class PositionData
{
public:
	char pad_0x0000[0x40]; //0x0000
	Vector3  m_Position; //0x0040
};//Size=0x0440
class ClientPickupEntity
{
public:
	virtual void* GetType();
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void GetAABB();
	virtual void GetTransform();
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27();
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void* GetPhysiscsEntity(); //physics
	virtual Vector3 * GetVelocity(); //velocity
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //

	char pad_0004[20]; //0x0004
	class PickupEntityData* m_data; //0x0018
	class PositionData* m_PositionData; //0x001C
	char pad_0020[376]; //0x0020
	class PickupName* m_PickupName; //0x0198
};

class ClientSupplySpherePre
{
public:
	char pad[0x18];
	class SupplySphereEntityData*   m_SupplySphereEntityData; //0x18
	char pad_1ac[0x190];
	class SoldierWeaponUnlockAsset*  m_SoldierWeaponUnlockAsset; //0x1ac
	char pad_230[0x80];
	class RigidMeshAsset*  m_RigidMeshAsset; //0x230
	char pad_2f0[0xbc];
	class ClientSupplySphereEntity*  m_ClientSupplySphereEntity; //0x2f0
};

class SoldierWeaponUnlockAsset
{
public:
	char pad[0x10];
	char * m_Name;
	int debugID;
};

class ResourceManager
{
public:
	class Compartment
	{
	public:
		BYTE padding00[0x94];
		std::vector<TypeInfoObject*> m_objects;
	};

public:
	volatile unsigned int m_bundleLoadInProgress;
	Compartment* m_compartments[50];

public:
	static ResourceManager* GetInstance()
	{
		return *(ResourceManager**)(0x89904630);
	}
};

class ClientPlayerScore
{
public:
	char pad_0x0000[0x2A8]; //0x0000 32 bit
	int m_Rank; //0x0x2A8
	int m_Kills; //0x02FC
	int m_Deaths; //0x0300
	int m_ScoreMultiplier; //0x0304
	int m_Score; //0x0308
	int m_GlobalScoreOriginal; //0x030C
	int m_GlobalScoreUpdated; //0x0310
	float m_Time; //0x0314
};//Size=0x0440

class ClientPlayerScoreManager
{
public:
	ClientPlayerScore * getScore(ClientPlayer *player)
	{
		typedef ClientPlayerScore* (__thiscall *tgetPlayerScore)(ClientPlayerScoreManager*, ClientPlayer *player);
		tgetPlayerScore getPlayerScore = (tgetPlayerScore)0x88583598;
		return getPlayerScore(this, player);
	}
};//Size=0x0080

class ClientVenicePersistenceManager
{
public:
	char pad_0000[12]; //0x0000
	class ClientPlayerScoreManager* m_pScoreManager; //0x000C

	static ClientVenicePersistenceManager* GetInstance()
	{
		return *(ClientVenicePersistenceManager**)(0x89854560);
	}
};//Size=0x0440

struct MatrixD : public XMFLOAT4X4
{
	MatrixD() : XMFLOAT4X4(1.f, 0, 0, 0,
		0, 1.f, 0, 0,
		0, 0, 1.f, 0,
		0, 0, 0, 1.f) {}
	MatrixD(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) : XMFLOAT4X4(m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33) {}
	explicit MatrixD(const Vector3& r0, const Vector3& r1, const Vector3& r2) : XMFLOAT4X4(r0.x, r0.y, r0.z, 0,
		r1.x, r1.y, r1.z, 0,
		r2.x, r2.y, r2.z, 0,
		0, 0, 0, 1.f) {}
	explicit MatrixD(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3) : XMFLOAT4X4(r0.x, r0.y, r0.z, r0.a,
		r1.x, r1.y, r1.z, r1.a,
		r2.x, r2.y, r2.z, r2.a,
		r3.x, r3.y, r3.z, r3.a) {}
	MatrixD(const XMFLOAT4X4& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); }
	MatrixD(const XMFLOAT3X3& M);
	MatrixD(const XMFLOAT4X3& M);

	operator XMMATRIX() const { return XMLoadFloat4x4(this); }

	// Comparison operators
	bool operator == (const MatrixD& M) const;
	bool operator != (const MatrixD& M) const;

	// Assignment operators
	MatrixD& operator= (const MatrixD& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(float) * 16); return *this; }
	MatrixD& operator= (const XMFLOAT4X4& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); return *this; }
	MatrixD& operator= (const XMFLOAT3X3& M);
	MatrixD& operator= (const XMFLOAT4X3& M);
	MatrixD& operator+= (const MatrixD& M);
	MatrixD& operator-= (const MatrixD& M);
	MatrixD& operator*= (const MatrixD& M);
	MatrixD& operator*= (float S);
	MatrixD& operator/= (float S);

	MatrixD& operator/= (const MatrixD& M);
	// Element-wise divide

	// Unary operators
	MatrixD operator+ () const { return *this; }
	MatrixD operator- () const;

	// Properties
	Vector3 Up() const { return Vector3(_21, _22, _23); }
	void Up(const Vector3& v) { _21 = v.x; _22 = v.y; _23 = v.z; }

	Vector3 Down() const { return Vector3(-_21, -_22, -_23); }
	void Down(const Vector3& v) { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

	Vector3 Right() const { return Vector3(_11, _12, _13); }
	void Right(const Vector3& v) { _11 = v.x; _12 = v.y; _13 = v.z; }

	Vector3 Left() const { return Vector3(-_11, -_12, -_13); }
	void Left(const Vector3& v) { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

	Vector3 Forward() const { return Vector3(-_31, -_32, -_33); }
	void Forward(const Vector3& v) { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

	Vector3 Backward() const { return Vector3(_31, _32, _33); }
	void Backward(const Vector3& v) { _31 = v.x; _32 = v.y; _33 = v.z; }

	Vector3 Translation() const { return Vector3(_41, _42, _43); }
	void Translation(const Vector3& v) { _41 = v.x; _42 = v.y; _43 = v.z; }
};

class Matrix
{
public:
	float m[4][4];

	Matrix()
	{
		m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
	}

	float operator() (const int r, const int c)
	{
		return m[r][c];
	}
};

class NetworkableMessage : public Message
{
public:
	char _0x0010[0x34 - sizeof(Message)];//0xC
};

class Material
{
public:
	UINT32 m_flagsAndIndex;
	
	__forceinline int isPenetrable()
	{
		return (int)(m_flagsAndIndex & MFPenetrable);
	};
	__forceinline int isSeeThrough()
	{
		return (int)(m_flagsAndIndex & MFSeeThrough);
	};
};

class RayCastHit
{
public:
	Vector4 m_Position;  // 0x00
	Vector4 m_Normal;  // 0x10
	void*  m_RigidBody; // 0x20
	Material m_Material;  // 0x28
	int  m_Part;   // 0x30
	float  m_Lambda;  // 0x34
	char  _pad[200];  // 0x38
}; //Size = 0x0070

class GameContext
{
public:
	char pad_0000[4]; //0x0000
	class MessageManager* m_pMessageManager; //0x0004
	char pad_0008[8]; //0x0008
	class GameTime* m_pGameTime; //0x0010
	class ClientLevel* m_PlayerLevel; //0x0014
	char pad_0018[24]; //0x0018
	class ClientPlayerManager* m_PlayerManager; //0x0030
	class OnlineManager* m_pOnlineManager; //0x0034
	class ClientGameView* m_pGameView; //0x0038
	void* m_pInterpolationManager; //0x003C

	static GameContext* GetInstance()
	{
		return *(GameContext**)0x89916E78;
	}
};//Size=0x0040

class ClientPlayerManager
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

	char _0x0004[372];
	ClientPlayer* m_LocalPlayer; //0x0178
	ClientPlayer** m_Players; //0x017C
	char _0x0180[832];
};//Size=0x04C0

class EntryComponentData
{
public:

};

class EntryComponent {
public:
	class WeaponInfo {
	public:
		virtual void WorldTransfrom(Matrix&);
		virtual void GetState(int&);
		virtual void AddWeaponFiringCallbacks(void*);
		virtual void RemoveWeaponFiringCallbacks(void*);
		virtual WeaponFiring* GetWeaponFiring();
		virtual ClientWeapon* GetWeapon();
		virtual bool ActiveInStance(int);
		virtual void* GetWeaponComponent();

		ClientSoldierWeapon *m_pWeaponComponent; //0x0008
	};

	class FiringCallbacks
	{
	public:
		virtual void Function0();
		char __0x0004[0x4];
		WeaponInfo* weapon_info;
	};

	virtual int GetActiveStance();
	virtual bool isCharacterControlEntry();
	virtual void animTree();
	virtual void onPrimaryStartedFiring(WeaponInfo *);
	virtual void onPrimaryFire(WeaponInfo *);
	virtual void onPrimaryFireRelease(WeaponInfo *);
	virtual void onPrimaryFireShotSpawned(WeaponInfo *, float);
	virtual void onPrimaryFireAutomaticBegin(WeaponInfo *);
	virtual void onPrimaryFireAutomaticEnd(WeaponInfo *);
	virtual void onPrimaryStoppedFiring(WeaponInfo *);
	virtual void onReload(WeaponInfo *);
	virtual DWORD_PTR entryData();
	virtual void onSwitchStance();
	virtual bool isStanceAvailable(int);
	std::vector<FiringCallbacks*> weapons;
};

class ExtEntryInputState
{
public:
	char _0x0000[256];
	float m_AnalogInput[11]; //0x0100
	float m_DownTimes[70]; //0x0128
	char _0x0248[32];
	long long m_DigitalBitFlags; //0x0268
	int m_CustomBitFlags; //0x0270
	float m_DeltaTime; //0x0274
	float m_TimeBehind; //0x0278
	Vector2 m_ViewAngles; //0x027C
	Vector2 m_ViewAngles2; //0x0284
	float m_AuthoritiveMovementPenalty; //0x028C
	Vector4 m_CollisionDirection; //0x0290
	char _0x02A0[16];
	Vector4 m_VaultDestination; //0x02B0
	Vector4 m_VaultVelocity; //0x02C0
	char _0x02D0[16];
	unsigned int m_Ticks; //0x02E0
	char _0x02E4[12];
	int m_VaultFlags; //0x02F0
};

class EntryInputState
{
public:
	char _0x0000[256];
	char _unk[0x10];
	float m_AnalogInput[11]; //0x0100
	float m_DownTimes[70]; //0x0128
	char _0x0248[32];
	long long m_DigitalBitFlags; //0x0268
	int m_CustomBitFlags; //0x0270
	float m_DeltaTime; //0x0274
	float m_TimeBehind; //0x0278
	Vector2 m_ViewAngles; //0x027C
	Vector2 m_ViewAngles2; //0x0284
	float m_AuthoritiveMovementPenalty; //0x028C
	Vector4 m_CollisionDirection; //0x0290
	char _0x02A0[16];
	Vector4 m_VaultDestination; //0x02B0
	Vector4 m_VaultVelocity; //0x02C0
	char _0x02D0[16];
	unsigned int m_Ticks; //0x02E0
	char _0x02E4[12];
	int m_VaultFlags; //0x02F0
};

class DamageData
{
public:
	char pad_0x0000[0x84];
	int m_VictimPlayerId;
	int m_VictimInstanceId;
	int m_InflictorPlayerId;
	int m_HitType;
	int m_pWeaponUnlockAsset;
	Vector4  m_Direction;
	float m_Damage;
	unsigned char m_ClientAIKilled;
};

class ClientDamageStream
{
public:
	char pad[0x8];
	DamageData* m_damagedata;
};

class ClientPlayer
{
public:
	virtual ~ClientPlayer();
	virtual int* GetCharacterEntity(); // ClientSoldierEntity + 188
	virtual DWORD_PTR GetCharacterUserData(); // PlayerCharacterUserData
	virtual EntryComponent* GetEntryComponent();
	virtual bool InVehicle();//1dc5 bf1
	virtual unsigned int getId();//1d74 bf1
	virtual bool hasUnlockAsset(LPVOID, bool);
	virtual void getUnlockAssets(int *);
	virtual bool isUnlocked(LPVOID);
	virtual void Function9(); //

	char pad_0x0000[0x24];
	char Name[16]; //0x28
	char pad_0x0038[0x6C8];
	class VeniceSoldierCustomizationAsset* Customize; //0x700
	char pad_0x0704[0x750];
	int m_TeamID;//0xe54
	char _0xE58[0x84];
	class ClientSoldierEntity* m_Corpse; //0x0EDC
	WeakPtr<ClientSoldierEntity> m_Soldier; //0x0EE0
	WeakPtr<ClientPlayer> m_Player; //0x0EE4
	class ClientVehicleEntity* m_pAttachedControllable;
	int m_attachedEntryId;
	class ClientSoldierEntity* m_pControlledControllable; //0xef0
	char pad_0x0EF4[0x8];
	class ExtEntryInputState* m_ExtEntryInputState;

	/*		char pad_0004[4]; //0x0004
	class PlayerData* m_pPlayerData; //0x0008
	char pad_000C[4]; //0x000C
	char* m_Name; //0x0010
	char pad_0014[20]; //0x0014
	char szName[20]; //0x0028
	char pad_003C[1732]; //0x003C
	class VeniceSoldierCustomizationAsset* m_pSelectedCustomizationAsset; //0x0700
	char pad_0704[4]; //0x0704
	int32_t m_pSelectedActiveUnlocks; //0x0708
	char pad_070C[1860]; //0x070C
	int8_t m_isAIPlayer; //0x0E50
	int8_t m_IsSpectator; //0x0E51
	char pad_0E52[2]; //0x0E52
	uint32_t m_TeamId; //0x0E54
	char pad_0E58[132]; //0x0E58
	WeakPtr<ClientSoldierEntity> m_Corpse; //0x0EDC
	WeakPtr<ClientSoldierEntity> m_Soldier; //0x0EE0
	WeakPtr<ClientPlayer> m_Player; //0x0EE4
	class ClientVehicleEntity* m_pAttachedControllable; //0x0EE8
	uint32_t m_AttachedEntryId; //0x0EEC
	class ClientSoldierEntity* m_pControlledControllable; //0x0EF0
	int32_t m_ControlledEntryId; //0x0EF4
	class EntryInputState* m_pInputState; //0x0EF8
	class EntryInputState* m_pExternalInputState; //0x0EFC
	char pad_0F00[4]; //0x0F00
	int32_t m_Id; //0x0F04
	char pad_0F08[16]; //0x0F08
	class ClientPlayerManager* m_pClientPlayerManager; //0x0F18
	class ClientPlayerView* m_pOwnPlayerView; //0x0F1C
	class ClientPlayerView* m_pPlayerView; //0x0F20
	char pad_0F24[16]; //0x0F24
	class InputConfigurationAsset* m_pInputConfigurationAsset; //0x0F34
	char pad_0F38[52]; //0x0F38
	uint32_t N00002C6A; //0x0F6C
	char pad_0F70[36]; //0x0F70
	uint32_t m_SquadId; //0x0F94
	int8_t m_IsSquadLeader; //0x0F98
	int8_t m_SquadClosed; //0x0F99
	int8_t m_isAllowedToSpawnOn; //0x0F9A
	int8_t m_reviveAllowed; //0x0F9B
	int8_t m_isPendingFriendJoin; //0x0F9C
	int8_t m_isCommander; //0x0F9D
	int8_t m_isHighValueTarget; //0x0F9E
	int8_t m_isAdmin; //0x0F9F
	float m_blinkNametagTimer; //0x0FA0
	float m_antiSpamBlockedTime; //0x0FA4
	float m_antiSpamBlockedMaxTime; //0x0FA8
	char pad_0FAC[92]; //0x0FAC
	class ValueUnlockAsset* m_pFieldUpgradeUnlock; //0x1008
	char pad_100C[128]; //0x100C
	class UnlockAssetBase* m_pParachuteCamo; //0x108C
	char pad_1090[16]; //0x1090
	char m_FakeName[25]; //0x10A0
	char pad_10B9[180]; //0x10B9
	char m_ClanName[4]; //0x116D
	char pad_1171[1]; //0x1171
	char m_FullName[25]; //0x1172*/
};//Size=0x1040

class WeaponZeroingEntry
{
public:
	float m_ZeroDistance; //0x0000
	float m_Angle; //0x0004

	WeaponZeroingEntry(float Dist, float Angle)
	{
		m_ZeroDistance = Dist;
		m_Angle = Angle;
	}
};//Size=0x0008
class ZeroingModifier
{
public:
	char _0x0000[24];
	WeaponZeroingEntry* m_ppZeroLevels;
	float m_DefaultZeroingDistance; //0x0020

	WeaponZeroingEntry GetZeroLevelAt(int index)
	{
		if (index > -1)
			return m_ppZeroLevels[index];
		else
			return WeaponZeroingEntry(m_DefaultZeroingDistance, 0.0f);
	}
};//Size=0x0038

class OnlineManager
{
public:
	char _0x0000[24];
	ClientPeer* m_ClientPeer; //0x0018
	ClientConnection* m_ClientConnection; //0x001C
	char _0x0020[32];
};//Size=0x0040

class ClientPeer
{
public:
	char pad_0000[13892]; //0x0000
	int32_t m_ChatManager; //0x3644
};//Size=0x0040

class ClientConnection
{
public:
	class EntryInputStateNetworkMove
	{
	public:
		char pad[0xc];
		EntryInputState* m_EntryInputState;
	};

	char _0x0[0x6A4];
	EntryInputStateNetworkMove m_EntryInputStateNetworkMove;
	char _0x6A8[0x15A4];
	ClientDamageStream* m_pDamageStream;
	//char pad_0x0000[0x1c4c];
	//ClientDamageStream* m_pDamageStream;
};

class N01F84DCC
{
public:
	char _0x0000[132];
};//Size=0x0084

class PlayerData
{
public:
	char _0x0000[64];
};//Size=0x0040

class WCSE
{
public:
	char _0x0000[64];
};//Size=0x0040

class IPhysicsRayCaster
{
public:
	virtual bool PhysicsRayQuery(const char* identifier, Vector4 * from, Vector4 * to, RayCastHit* hit, int flag, int PhysicsEntityList);
	virtual void* asyncPhysicsRayQuery(char* text, Vector4  *from, Vector4  *to, int flag, void* Physics);
};

class GameWorld
{
public:
	char pad00[0x18];    // 0x00
	IPhysicsRayCaster* m_RayCaster;  // 0x0018
};

class HavokPhysicsManager
{
public:
	char _0x0[0x40];
	class IPhysicsRayCaster* m_pRayCaster; //0x40
};

class ClientLevel
{
public:
	char pad_0000[36]; //0x0000
	class LevelData* m_pLevelData; //0x0024
	class TeamEntityData** m_ppTeamEntityData; //0x0028
	char* m_LevelName; //0x002C
	int m_pGameMode; //0x0030
	char pad_0034[100]; //0x0034
	class HavokPhysicsManager* m_pHavokPhysicsManager; //0x0098
	char pad_009C[4]; //0x009C
	GameWorld* m_pGameWorld; //0x00A0
};//Size=0x0040

class VeniceSoldierCustomizationAsset
{
public:
	char _0x0000[64];
};//Size=0x0040

class SoldierEntityData
{
public:
};

class BFClientSoldierHealthComponent
{
public:
	char _0x0000[0x10];
	float m_fhealth;
	float m_MaxHealth;
};

class ClientSoliderPrediction
{
public:
	char _0x00[0x20];
	Vector3 Position;
	char _0x2C[0x14];
	Vector3 Velocity;
	char _0x4C[0x14];
	int inAir;
	int GroundType;
	char _0x68[0x4];
	int Stance1;
	int Stance2;
};

class SoldierWeaponData
{
public:
	char pad_0x0000[0xf0]; //0x0000
	PCHAR m_name; //0x0130
};//Size=0x0004

class BulletEntityData
{
public:
	char pad_0000[172]; //0x0000
	char* m_ProjectileName; //0x00AC
	char pad_00B0[72]; //0x00B0
	float m_gravity; //0x00F8
	float m_impactImpulse; //0x00FC
	float m_detonationTimeVariation; //0x0100
	float m_vehicleDetonationRadius; //0x0104
	float m_vehicleDrtonationActivationDelay; //0x0108
	float m_flyBySoundRadius; //0x010C
	float m_flyBySoundSpeed; //0x0110
	float m_firstFraneTravelDistance; //0x0114
	float m_distributeDamageOverTime; //0x0118
	float m_DamageMaX; //0x011C
	float m_DamageMin; //0x0120
	float m_DamageFallOff; //0x0124
	float m_DamageFallOffEndDistance; //0x0128
	float m_TimeToArmExplosion; //0x012C
	char pad_0130[4]; //0x0130
	int8_t m_bHasVehicleDetination; //0x0134
	uint8_t m_bInstantHit; //0x0135
	uint8_t m_bStopTrail; //0x0136
	uint8_t m_bUnk; //0x0137
	float m_RocketGravity; //0x0138
};

class ShotConfigData
{
public:

	char pad_0000[80]; //0x0000
	Vector4 m_PositionOffset; //0x0050
	Vector4 m_Direction; //0x0060
	Vector4 m_initialSpeed; //0x0070
	char pad_0080[16]; //0x0080
	class BulletEntityData* m_pBulletEntityData; //0x0090
	char pad_0094[16]; //0x0094
	uint32_t m_numberOfBulletsPerShell; //0x00A8
	uint32_t m_numberOfBulletsPerShot; //0x00AC
	uint32_t m_numberOfBulletsPerBurst; //0x00B0
	int8_t m_relativeTargetAiming; //0x00B4
	int8_t m_forceSpawnToCamera; //0x00B5
	uint8_t m_activeForceSpawnToCamera; //0x00B6
	int8_t m_SpawnVisualAtBone; //0x00B7
	char pad_00B8[212]; //0x00B8
	float m_TriggerPullWeight; //0x0188
	float m_RateOfFire; //0x018C
	float m_RateOfFireForBurst; //0x0190
	char pad_0194[4]; //0x0194
	float m_ClientFireRateMultiplier; //0x0198
	char pad_019C[4]; //0x019C
	float m_ReloadTime; //0x01A0
};

class WeaponFiringData
{
public:
	char pad_0000[8]; //0x0000
	class ShotConfigData* m_pShotConfigData; //0x0008
};

class WeaponModifier
{
public:
	struct WeaponMiscModifierSettings
	{
		bool m_EnableBreathControl; //0x0000
		bool m_CanBeInSupportedShooting; //0x0001
		bool m_UnZoomOnBoltAction; //0x0002
		bool m_HoldBoltActionUntilZoomRelease; //0x0003
		bool m_IsSilenced; //0x0004
	};//Size=0x0005
	char pad_0000[36]; //0x0000
	SoldierWeaponUnlockAsset* m_pWeaponUnlockAsset; //0x0024
	WeaponMiscModifierSettings m_WeaponMiscModifierSettings; //0x0028
};//Size=0x0044

class ClientWeapon
{
public:
	char pad_0x0000[0x4];
	int m_pWeaponData;
	char pad_0x0008[0x4];
	WeaponFiringData* m_pWeaponFiringData;
	WeaponModifier* m_pModifier;
	char pad_0x0014[0xC];
	Vector4 m_moveSpeed;
	MatrixD m_shootSpace;
	MatrixD m_shootSpaceIdentity;
	char pad_0x00B0[0x118];
	float m_cameraFov;
	float m_weaponFov;
	float m_fovScaleFactor;
	char pad_0x01D4[0x8];
	int m_zoomLevel;
	int m_zoomMaxLevel;
	char pad_0x1c0[0x30];
	bool inAim;
	char pad_0x1f4[0x10];
	ClientSoldierEntity* m_controllableFinder;
};

class SoldierAimingSimulationData
{
public:
	char pad_0x0000[0x68];
	float m_AimingRange;
};

class FPSAimer
{
public:
	char pad_0x0000[0xc];
	Vector2 m_AuthoratativeViewAngles;
};

class ClientSoliderAimingSimulation
{
public:
	SoldierAimingSimulationData * m_pSoldierAimingSimulationData; //0x00
	int unk; //0x04
	FPSAimer* m_pFPSAimer; //0x08
	float m_Yaw; //0x0c
	float m_Pitch; //0x10
	float m_AimYawTimer; //0x14
	float m_AimPitchTimer; //0x18
	Vector2 m_Sway; //0x1c
	char pad_0x24[0x12c];
	Vector3 CrossHair; //0x150
};

class ClientExplosionPackEntity
{
public:
	virtual int* GetType();
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void GetAABB(TransformAABBStruct& pAABB);
	virtual void GetTransform(Matrix& mTransform);
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27();
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void* GetPhysiscsEntity(); //physics
	virtual Vector3* GetVelocity(); //velocity
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //

	char pad_0x000[0x2dc];
	int m_TeamID;
};

class WeaponSway
{
public:
	struct Random
	{
		unsigned int m_value;
		unsigned int m_tableIndex;
		float m_nextNormal;
		bool m_nextNormalIsValid;
	};
	class GunSwayLagData
	{
	public:
		float m_MoveStrafeModifier; //+0x0
		float m_MoveForwardModifier; //+0x4
		float m_RotateYawModifier; //+0x8
		float m_RotatePitchModifier; //+0xC
		float m_ReleaseModifier;//+0x10
	};
	class GunSwayRecoilData
	{
	public:
		float m_RecoilAmplitudeMax;//+0x0
		float m_RecoilAmplitudeIncPerShot; //+0x4
		float m_HorizontalRecoilAmplitudeIncPerShotMin; //+0x8
		float m_HorizontalRecoilAmplitudeIncPerShotMax; //+0xC
		float m_HorizontalRecoilAmplitudeMax;//+0x10
		float m_RecoilAmplitudeDecreaseFactor; //+0x14
	};
	class CameraRecoilData
	{
	public:
		char pad[0x8];
		float m_SpringConstant; //+0x10
		float m_SpringDamping;//+0x14
		float m_SpringMinThresholdAngle; //+0x18
	};
	class GunSwayDispersionData
	{
	public:
		float m_MinAngle; //+0x0
		float m_MaxAngle; //+0x4
		float m_IncreasePerShot;//+0x8
		float m_DecreasePerSecond;//+0xC
		float m_NoFireDecreasePerSecond;//+0x10
		float m_NoFireTimeThreshold; //+0x14
	};
	class GunSwayBaseMoveJumpData
	{
	public:
		GunSwayDispersionData m_BaseValue; //+0x0
		GunSwayDispersionData m_Moving; //+0x18
		GunSwayDispersionData m_Jumping; //+0x30
		GunSwayDispersionData m_Sprinting; //+0x48
		GunSwayDispersionData m_VaultingSmallObject; //+0x60
		GunSwayDispersionData m_VaultingMediumObject; //+0x78
		GunSwayRecoilData m_Recoil; //+0x90
		GunSwayLagData m_GunSwayLag; //+0xA8
	};

	class GunSwayStandData
	{
	public:
		GunSwayBaseMoveJumpData m_NoZoom; //+0x0
		GunSwayBaseMoveJumpData m_Zoom; //+0xBC
	};
	class GunSwayBaseMoveData
	{
	public:
		GunSwayDispersionData m_BaseValue; //+0x0
		GunSwayDispersionData m_Moving; //+0x18
		GunSwayRecoilData m_Recoil;//+0x30
		GunSwayLagData m_GunSwayLag; //+0x48
	};
	class GunSwayCrouchProneData
	{
	public:
		GunSwayBaseMoveData m_NoZoom;//+0x0
		GunSwayBaseMoveData m_Zoom; //+0x5C
	};
	class GunSwayStanceTransition
	{
	public:
		GunSwayDispersionData m_MaxPenaltyValue; //+0x0
		float m_CoolDown; //+0x18
	};
	class GunSwayDispersionModData
	{
	public:
		float m_MinAngleModifier; //+0x0
		float m_MaxAngleModifier; //+0x4
		float m_IncreasePerShotModifier; //+0x8
		float m_DecreasePerSecondModifier; //+0xC
	};

	class GunSwayStanceZoomModifierData
	{
	public:
		GunSwayDispersionModData m_DispersionMod; //+0x0
		GunSwayDispersionModData m_MovingDispersionMod; //+0x10
		GunSwayDispersionModData m_SprintingDispersionMod; //+0x20
		float m_RecoilMagnitudeMod;//+0x30
		float m_RecoilAngleMod; //+0x34
		float m_FirstShotRecoilMod;//+0x38
		float m_LagYawMod; //+0x3C
		float m_LagPitchMod; //+0x40
	};

	class GunSwayData
	{
	public:
		char pad[0x8];
		GunSwayStandData m_Stand; //+0x10
		GunSwayCrouchProneData m_Crouch; //+
		GunSwayCrouchProneData m_Prone; //+
		GunSwayStanceTransition m_ProneToCrouch; //+
		GunSwayStanceTransition m_ProneToStand; //+
		GunSwayStanceTransition m_CrouchToProne; //+
		GunSwayStanceTransition m_CrouchToStand; //+
		GunSwayStanceTransition m_StandToProne; //+
		GunSwayStanceTransition m_StandToCrouch; //+
		GunSwayStanceZoomModifierData m_SuppressionModifierUnzoomed;//+
		GunSwayStanceZoomModifierData m_SuppressionModifierZoomed; //+
		void* m_ModifierUnlocks; //+

		float m_DeviationScaleFactorZoom; //+
		float m_GameplayDeviationScaleFactorZoom; //+
		float m_DeviationScaleFactorNoZoom;//+
		float m_GameplayDeviationScaleFactorNoZoom;//+

		float m_ShootingRecoilDecreaseScale; //+
		float m_FirstShotRecoilMultiplier; //+0x438 
		CameraRecoilData m_CameraRecoil;//+
	};
	class Deviation
	{
	public:
		float m_Pitch; //0x0000
		float m_Yaw; //0x0004
		float m_Roll; //0x0008
		float m_TransY; //0x000C
	};//Size=0x0010
	class GunSwayModifierData
	{
	public:
		char pad[0x10];
		GunSwayStanceZoomModifierData m_StandZoomModifier; //+0x18
		GunSwayStanceZoomModifierData m_StandNoZoomModifier;//+0x5C
		GunSwayStanceZoomModifierData m_CrouchZoomModifier; //+0xA0
		GunSwayStanceZoomModifierData m_CrouchNoZoomModifier; //+0xE4
		GunSwayStanceZoomModifierData m_ProneZoomModifier; //+0x128
		GunSwayStanceZoomModifierData m_ProneNoZoomModifier; //+0x16C
		bool m_OnlyInSupportedShooting;//+0x1B0
		bool m_OnlyOnWeaponLightEnabled;//+0x1B1
	};
	struct WeaponFiringUpdateContext
	{
		union Flags
		{
			struct
			{
				unsigned primaryFireTrigger : 1;
				unsigned orderTrigger : 1;
				unsigned reloadTrigger : 1;
			};

			unsigned int data;
		};

		Vector4 targetPos; //0x0000
		WeakPtr<ClientSoldierEntity> target; //0x0010
		WeaponSway* weaponSway; //0x0014
		float deltaTime; //0x0018
		float reloadTimeMultiplier; //0x001C
		float damageMultiplier; //0x0020
		float explosiveMultiplier; // 0x0024
		float overheatMultiplier; // 0x0028
		void* characterMelee; //0x002C
		unsigned int ticks; //0x0030
							// unfinished //
	};
	virtual void primaryStartedFiringCallback(); //1 byte weaponsway+0x214 (m_IsFiring) and zero word weaponsway+0x210 (m_InitialFireShot)
	virtual void subprimaryFireCallback(); // inc DWORD weaponsway+0x210 (m_InitialFireShot)
	virtual void nullsub_1_fc2();
	virtual void primaryFireShotSpawnedCallback(float, bool, WeaponSway::WeaponFiringUpdateContext*); // ?
	virtual void nullsub_1_fc4();
	virtual void nullsub_1_fc5();
	virtual void nullsub_1_fc6();
	virtual void primaryStoppedFiringCallback(); //zero byte weaponsway+0x214 (m_IsFiring) and zero word weaponsway+0x210 (m_InitialFireShot)
	virtual void nullsub_1_fc8();
	virtual void nullsub_1_fc9();
	virtual void nullsub_1_fc10();
	virtual void nullsub_1_fc11();
	virtual void nullsub_1_fc12();
	virtual void nullsub_1_fc13();
	virtual void nullsub_1_fc14();
	virtual void nullsub_1_fc15();
	virtual void nullsub_1_fc16();
	virtual void nullsub_1_fc17();
	virtual void nullsub_1_fc18();
	virtual void nullsub_1_fc19();
	virtual void nullsub_1_fc20();
	virtual void nullsub_1_fc21();
	virtual void nullsub_1_fc22();
	virtual void sub_140B21E70(); //xor eax,eax...
	virtual void unlockModifiers(WeaponModifier *);
	virtual void update(float deltatime, intptr_t &);//fb::WeaponSway::SoldierAttributesCallback &);
	virtual intptr_t getDispersion(LinearTransform &, bool scaleTransform); //(GetDispersion, 26); ReuNion(tm)
	virtual intptr_t getRecoil(LinearTransform &, bool scaleTransform);//(GetRecoil, 27); ReuNion(tm)
	virtual void getCameraRecoil(LinearTransform &);
	virtual intptr_t getLag(LinearTransform &, bool scaleTransform);
	virtual void nullsub_1_fc30();
	virtual float getDispersionFactor(); //0x1AC
	virtual float getDispersionAngle(); //0x1A0
	virtual float getMinDispersionAngle(); //0x1A4
	virtual void getcrossHairDispersionFactor(); //0x1A8
	virtual void getSuppresionMinDispersionAngleFactor(); //0x1C8
	virtual float getRecoilPitch(); //m_deviationPitch
	virtual float getRecoilYaw(); //m_deviationYaw
	virtual void sub_14019CEA0();

	class GunSwayData* m_data; //0x0004
	char pad_0008[192]; //0x0008
	Deviation m_currentRecoilDeviation; //0x00C8
	float m_TimeSinceLastShot; //0x00D8
	int32_t m_cameraRecoilDeviation; //0x00DC
	Matrix m_cameraRecoilTransform; //0x00E0
	Deviation m_CurrentLagDeviation; //0x0120
	float m_dispersionAngle; //0x0130
	float m_minDispersionAngle; //0x0134
	float m_CrossHairDispersionFactor; //0x0138
	float m_DispersionFactor; //0x013C
	Deviation m_CurrentDispersionDeviation; //0x0140
	float m_CurrentGameplayDeviationScaleFactor; //0x0150
	float m_CurrentVisualDeviationScaleFactor; //0x0154
	float m_SuppressionMinDispersionAngleFactor; //0x0158
	Random m_random; //0x015C
	uint32_t m_Seed; //0x016C
	float m_RandomAngle; //0x0170
	float m_RandomRadius; //0x0174
	char pad_0178[4]; //0x0178
	float m_TimeSinceLastShot2; //0x017C
	int8_t m_ShotsFired; //0x0180
	char pad_0181[3]; //0x0181
	int8_t m_IsFiring; //0x0184
};//Size=0x0C44


class WeaponFiring
{
public:
	char pad_0000[36]; //0x0000
	class wf24* m_p24; //0x0024
	char pad_0028[20]; //0x0028
	class WeaponSway* m_pSway; //0x003C
	char pad_0040[84]; //0x0040
	class WeaponFiringData* m_pPrimaryFire; //0x0094
	char pad_0098[12]; //0x0098
	WeaponState m_weaponState; //0x00A4
	WeaponState m_lastWeaponState; //0x00A8
	WeaponState m_nextWeaponState; //0x00AC
	char pad_00B0[8]; //0x00B0
	float m_timeToWait; //0x00B8
	float m_reloadTimer; //0x00BC
	float m_holdReleaseMinDelay; //0x00C0
	float m_recoilTimer; //0x00C4
	float m_recoilAngleX; //0x00C8
	float m_recoilAngleY; //0x00CC
	float m_recoilAngleZ; //0x00D0
	float m_recoilFovAngle; //0x00D4
	float m_recoilTimeMultiplier; //0x00D8
	float m_overheatDropMultiplier; //0x00DC
	uint32_t m_primaryAmmoToFill; //0x00E0
	int32_t m_reloadStage; //0x00E4
	char pad_00E8[4]; //0x00E8
	int32_t m_externalPrimaryMagazineCapacity; //0x00EC
	uint32_t m_ammoInClip; //0x00F0
	uint32_t m_ammoInReserve; //0x00F4
	char pad_00F8[4]; //0x00F8
	int8_t m_hasStoppedFiring; //0x00FC
	uint8_t m_primaryFireTriggeredLastFrame; //0x00FD
	uint8_t m_isOverheated; //0x00FE
	float m_Heat; //0x00FF
	float m_OverHeatTimer; //0x0103
	uint32_t m_Ticks; //0x0107
	char pad_010B[1]; //0x010B
	FireMode m_FireMode; //0x010C
};

class ClientSoldierWeapon
{
public:
	char pad_0000[24]; //0x0000
	class SoldierWeaponData* m_pSoldierWeaponData; //0x0018
	char pad_001C[9380]; //0x001C
	class ZoomLevelData* m_pZoomLevelData; //0x24C0
	char pad_24C4[16]; //0x24C4
	class ClientSoliderAimingSimulation* m_pClientSoldierAimingSimulation; //0x24D4
	char pad_24D8[12]; //0x24D8
	class ClientWeapon* m_pWeapon; //0x24E4
	class ClientWeaponFiringReplication* m_pReplicatedFiring; //0x24E8
	char pad_24EC[4]; //0x24EC
	class WeaponFiring* m_pPrimaryFiring; //0x24F0
	class WeaponFiring* m_pCorrectedFiring; //0x24F4
};

class ClientSoliderWeaponComponent
{
public:
	class WeaponHandler
	{
	public:
		ClientSoldierWeapon * WeaponList[7];
	};

	enum WeaponList
	{
		PRIMARY = 0,
		Secondary = 1,
		GADGET = 2,
		GRENADE = 6,
		KNIFE = 7,
	};
	char _0x000[0x510];
	WeaponHandler* pWeaponHandler;
	char _0x514[0x100];
	int m_ActiveSlot;
	char pad_0x0614[0x60]; //0x0620
	int m_currentZoomLevel; //0x0674

	ClientSoldierWeapon* GetActiveWeapon()
	{
		return pWeaponHandler->WeaponList[m_ActiveSlot];
	}
};

class UpdatePoseResultData
{
public:

	class QuatTransform
	{
	public:
		Vector3 m_transandScale;
		char pad_0x000c[0x4];
		Vector3 m_rotation;
		int m_pad;
	};

	QuatTransform* m_LocalTransform; //0x0
	QuatTransform* m_WorldTransform; //0x4
	QuatTransform* unk1; //0x8
	QuatTransform* unk2; //0xc
	QuatTransform* unk3; //0x10
	QuatTransform* m_ActiveWorldTransform;
	QuatTransform* m_ActiveLocalTransform;
	char pad_0x001c[0x8];
	bool m_ValidTransforms;
	bool m_PoseUpdateEnabled;
	bool m_PoseNeeded;
};

class RagdollComponentData
{
public:
	char pad[0x60];
	SkeletonAsset*   m_SkeletonAsset; //0x60 
	class RagdollAsset*  m_RagdollAsset; //0x64
	SkeletonCollisionData*  m_SkeletonCollisionData; //0x68
};

class ClientRagDollComponent
{
public:
	char pad[0x8];
	RagdollComponentData* m_RagdollComponentData; //0x8 	
	char pad_0x000[0x40];
	UpdatePoseResultData m_ragdollTransform;
};

class SpottingComponentData
{
public:
	char pad_0x000[0xb0];
	int unk;
};

class ClientSpottingComponent
{
public:
	char pad_0x000[0x8];
	SpottingComponentData* m_SpottingComponentData; //0x8
	char pad_0x00c[0x18];
	SpotType m_spottype;
};

class ClientSpottingTargetComponent
{
public:
};

class VaultComponentData
{
public:
	char     _0x0000[0x54];
	float    m_StartHeightMax; //0x54
	float    m_StartHeightMin; //0x58
};

typedef struct
{
	int vfptr; //0x00
	char padding00[0x88];
	char unk1;
	char padding01[0x7];
	int unk2;
	char padding02[0x8];
	int ClientPlayerPtr;
	int UnlockAsset;
	char buffer[0x300];
}damagemsg_t;

class VaultComponent
{
public:
	char                   _0x0000[0xC0];
	VaultComponentData*    m_pVaultData; //0xC0
	char                   _0x00C4[0x10C];
	float                  m_VaultHeight; //0x1C0
	float                  m_Unk1; //0x1C4
	float                  m_Unk2; //0x1C8
	float                  m_Unk3; //0x1CC
	Vector3                m_vaultCoords;//0x1D0
	char                   _0x01DC[0x4];
	int                    m_VaultState; //0x1E0
};

class ClientMovementComponent
{
public:
	int unk1; //0x0024
	int unk2; //0x0028
	int unk3; //0x002C
	char _0x0030[32];
	Vector3 Velocity; //0x0050
	char _0x005C[36];
}; //Size: 0x00A0

class AxisAlignedBox
{
public:
	Vector4  m_Min;
	Vector4  m_Max;

	Vector3 GetCenter() const {
		return Vector3(
			(m_Max.x + m_Min.x) * 0.5f,
			(m_Max.y + m_Min.y) * 0.5f,
			(m_Max.z + m_Min.z) * 0.5f);
	}
};

struct LinearTransform
{
	Vector3 m_right; //0x0000
	Vector3 m_up; //0x0010
	Vector3 m_forward; //0x0020
	Vector3 m_trans; //0x0030
};

struct TransformAABBStruct
{
	Matrix Transform;
	AxisAlignedBox AABB;
	Matrix  pad;

	TransformAABBStruct()
	{

	}
};

class ClientExplosionPackEntityPre
{
public:
	char pad[0x18];
	class ExplosionPackEntityData*   m_ExplosionPackEntityData; //0x18
	char pad_1a0[0x184];
	class CamoUnlockAsset*  m_CamoUnlockAsset; //0x1a0
	char pad_1ac[0x8];
	SoldierWeaponUnlockAsset*  m_SoldierWeaponUnlockAsset; //0x1ac
	char pad_230[0x80];
	class RigidMeshAsset*  m_RigidMeshAsset; //0x230
	char pad_2f0[0xbc];
	ClientExplosionPackEntity*  m_ClientExplosionPackEntity; //0x2f0
};

class ClientSoldierEntity
{
public:

	class BoneTransform
	{
	public:
		Vector3      m_position; //0x0
		char      _0x000C[0x34];
	};

	virtual TypeInfo* GetType();
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void GetAABB(TransformAABBStruct& pAABB);
	virtual void GetTransform(Matrix& mTransform);
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27();
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void* GetPhysiscsEntity(); //physics
	virtual Vector3* GetVelocity(); //velocity
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //

	char _0x0004[0x9];
	unsigned char EngineChamsBehingBigWalls;
	char _padding[0x7];
	class SoldierEntityData* m_pSoldierEntityData; //0x0018
	char _0x001C[156];
	class BFClientSoldierHealthComponent* m_pBFClientSoldierHealthComponent; //0x00B8
	int* m_pBFClientSoldierPhysicsComponent; //0x00BC
	char _0x00C0[84];
	class ClientPlayer* m_ClientPlayer; //0x0118
	int* m_pAnimatable; //0x011C
	int* m_pAnimatable2; //0x0120
	int* m_CSCC; //0x0124
	char _0x0128[0x12C];
	int* m_BoneCollisionComponentData; //0x0240
	char _0x0244[212];
	class ClientSoliderPrediction* m_ClientSoliderPrediction; //0x0318
	char _0x031C[60];
	int m_PoseType; //0x0358
	char m_EngineChams; //0x035C
	char _0x0360[91];
	class ClientSoliderWeaponComponent* m_ClientSoliderWeaponComponent; //0x03B8
	int* m_pBodyComponent; //0x03BC
	class ClientRagDollComponent* m_pClientRagdollComponent; //0x03C0
	char pad_0x03c4[0x18]; //0x03c4
	unsigned char m_IsSprinting;
	unsigned char m_occluded;//0x3dd
	char pad_03EE[37]; //0x03EE
	int8_t m_jumping; //0x0413
	char pad_0414[728]; //0x0414
	class ClientParachuteComponent* m_pClientSoldierParachuteComponent; //0x06EC
	char pad_06F0[60]; //0x06F0
	intptr_t pClientPlayerEntryComponent; //0x072C
	char pad_0730[12]; //0x0730
	class ClientSpottingComponent* m_pClientSpottingComponent; //0x073C
	char pad_0740[12]; //0x0740
	class ClientSpottingTargetComponent* m_pClientSpottingTargetComponent; //0x074C
	char _0x0740[140];
	class VaultComponent* m_pClientVaultComponent; //0x07CC
	char _0x07D0[0x1C];
	class ClientMovementComponent* m_pClientMovementComponent; //0x7DC
	char _0x07E0[0x8C0];
	BoneTransform m_Transforms[25]; //0x10B0
};//Size=0x0900

class NetworkDefibrillatorReviveMessage : public NetworkableMessage
{
public:
	char pad[0x4];
	WeakPtr<ClientSoldierEntity> m_SoldierToRevive;
	int m_pSoldierToReviveId;//0x3C //ClientSoldierEntity + 0x39
	Vector4 m_Position;//0x40
	float m_Health;//0x50 //0.033-2.00

};

class DynamicPhysicsEntity
{
public:
	virtual int* GetType();
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void GetAABB(TransformAABBStruct& pAABB);
	virtual void GetTransform(Matrix& mTransform);
};

class ClientInteractionPRE
{
public:
	char pad[0x94];
	class GameInteractionEntityData*   m_GameInteractionEntityData; //0x94
	char pad_170[0xd8];
	class DynamicPhysicsEntity*  m_DynamicPhysicsEntity; //0x170
	char pad_194[0x20];
	class BoatFloatPhysicsData*  m_BoatFloatPhysicsData; //0x194
	char pad_25c[0xc4];
	class PropertyDebugEntityData*  m_PropertyDebugEntityData; //0x25c
};

class ClientParachuteComponent
{
public:

	class AimingConstraints
	{
	public:
		float m_MinYaw; //0x0000
		float m_MaxYaw; //0x0004
		float m_MinPitch; //0x0008
		float m_MaxPitch; //0x000C
		float m_PitchOffset; //0x0010
		float m_YawOffset; //0x0014
		float m_MinYawDefault; //0x0018
		float m_MaxYawDefault; //0x001C
	};

	class ParachuteComponentData
	{
	public:
		char pad_0000[212]; //0x0000
		float m_UndeployTime; //0x00D4
		float m_AutoDeployInitialDelay; //0x00D8
		float m_AutoDeployGroundDistance; //0x00DC
		float m_AutoDeployMinGroundDistance; //0x00E0
		uint8_t m_AutoDeployEnabled; //0x00E4
		uint8_t m_AutoDeployOnceOnSpawnOnly; //0x00E5
	};

	char pad_0000[8]; //0x0000
	class ParachuteComponentData* m_pData; //0x0008
	char pad_000C[4]; //0x000C
	class ClientPlayerEntryComponent* m_pEntry; //0x0010
	char pad_0014[152]; //0x0014
	class ClientAntAnimatableComponent* m_pAnimatable; //0x00AC
	class CharacterPhysicsEntity* m_pPhysicsEntity; //0x00B0
	class AimingConstraints* m_pAimingContraints; //0x00B4
	char pad_00B8[72]; //0x00B8
	uint32_t m_State; //0x0100
	Vector2 m_View; //0x0104
	Vector2 m_DeltaView; //0x010C
	Vector2 m_AuthoratativeView; //0x0114
	uint8_t m_SoldierInParachute; //0x011C

	void Tweak(bool IsActive)
	{
		if ((this->m_pAimingContraints))
		{
			this->m_pAimingContraints->m_MinYaw = IsActive == true ? -180.f : -45.f;
			this->m_pAimingContraints->m_MaxYaw = IsActive == true ? 180.f : 45.f;
			this->m_pAimingContraints->m_MinPitch = IsActive == true ? -180.f : -85.f;
			this->m_pAimingContraints->m_MaxPitch = IsActive == true ? 180.f : 70.f;
			this->m_pAimingContraints->m_MinYawDefault = IsActive == true ? -180.f : -45.f;
			this->m_pAimingContraints->m_MaxYawDefault = IsActive == true ? 180.f : 45.f;
		}

		if ((this->m_pData))
			this->m_pData->m_UndeployTime = IsActive == true ? 0.f : 1.0f;
	}
}; //Size = 0x0150

class ClientControllable
{
public:
	char _0x0000[64];
};//Size=0x0040

class ClientGrenadeEntity
{
public:
	virtual int* GetType();
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void GetAABB(TransformAABBStruct& pAABB);
	virtual void GetTransform(Matrix& mTransform);
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27();
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void* GetPhysiscsEntity(); //physics
	virtual Vector3* GetVelocity(); //velocity
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //

	char pad_1[0x4];
};

class ClientGrenadePre
{
public:
	char pad[0x18];
	class GrenadeEntityData*   m_GrenadeEntityData; //0x18
	char pad_1ac[0x190];
	class SoldierWeaponUnlockAsset*  m_SoldierWeaponUnlockAsset; //0x1ac
	char pad_230[0x80];
	class RigidMeshAsset*  m_RigidMeshAsset; //0x230
	char pad_300[0xcc];
	class ClientGrenadeEntity*  m_ClientGrenadeEntity; //0x300
};

class RenderView
{
public:
	char _0x0000[180];
	float m_FovY; //0x00B4
	float defualtFovY; //0x00B8
	float nearPlane; //0x00BC
	float farPlane; //0x00C0
	float m_Aspect; //0x00C4
	float orthoWidth; //0x00C8
	float orthoHeight; //0x00CC
	char _0x00D0[384];
	float m_FovX; //0x0250
	float depthHeightRatio; //0x0254
	float fovScale; //0x0258
	float fovScaleSqr; //0x025C
	Matrix m_viewMatrix; //0x0260
	Matrix m_viewMatrixTranspose; //0x02A0
	MatrixD m_viewMatrixInverse; //0x02E0
	Matrix m_ProjectionMatrix; //0x0320
	Matrix m_viewMatrixAtOrigin; //0x0360
	Matrix m_ProjectionTranspose; //0x03A0
	Matrix m_ProjectionInverse; //0x03E0
	Matrix m_ViewProj; //0x0420
	Matrix m_ViewProjTranspose; //0x0460
	Matrix m_ViewProjInverse; //0x04A0
	Matrix m_UnknMatrix; //0x04E0
	MatrixD m_Transform2; //0x0520
	Matrix m_UnknMatrix2; //0x0560
	char _0x05A0[64];

	float GetYaw()
	{
		return atan2(m_viewMatrix.operator()(3, 1), m_viewMatrix.operator()(3, 3));
	}
};//Size=0x05E0

class GameRenderer
{
public:
	char pad_0x0000[0x24]; //0x0000
	int m_GameRenderSettings; //0x0024  not sure
	char pad_0x0028[0x8]; //0x0028
	RenderView* m_pRenderView; //0x0030
	char pad_0x0034[0x10C]; //0x0034

	static GameRenderer* GetInstance()
	{
		return *(GameRenderer**)(0x8991B790);
	}
};//Size=0x0140

class ClientVehicleEntity
{
public:
	virtual int* GetType();
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void GetAABB(TransformAABBStruct& pAABB);
	virtual void GetTransform(Matrix* mTransform);
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27();
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void* GetPhysiscsEntity(); //physics
	virtual Vector3 * GetVelocity(); //velocity
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //

	char pad_0004[16]; //0x0004
	class Components* m_pComponents; //0x0014
	class VehicleEntityData* m_data; //0x0018
	char pad_001C[104]; //0x001C
	int32_t m_TeamId; //0x0084
	int32_t m_PlayerIn;
	char pad_0088[44]; //0x0088
	class ClientVehicleHealthComponent* m_pHealthComp; //0x00B8
	class ClientVehiclePhysicsComponent* m_pClientVehiclePhysicsComponent; //0x00BC
	char pad_00C0[188]; //0x00C0
	class DynamicPhysicsEntity* m_pDynamicPhysicsEntity; //0x017C
	float m_waterLevel; //0x0180
	float m_terrainLevel; //0x0184
	float m_waterLevelUpdateTimer; //0x0188
	float m_terrainLevelUpdateTime; //0x018C
	AxisAlignedBox m_childrenAABB; //0x0190
	char pad_01B0[16]; //0x01B0
	Vector3 m_vehicleSpeed; //0x01C0
	char pad_01CC[4]; //0x01CC
	Vector3 m_prevVelocity; //0x01D0
	char pad_01DC[168]; //0x01DC
	WeakPtr<ClientPlayer> m_GadgetOwner; //0x0284
	char pad_0288[203]; //0x0288
	uint8_t m_EngineChams; //0x0353
};//Size=0x0284

#pragma warning( pop )

bool isLocalPlayerInVehicle();

WeaponSway::Deviation * GetRecoil(WeaponSway * pGunSway);

WeaponSway::Deviation * GetSpread(WeaponSway * pGunSway);

bool isLocalPlayerAlive();

ClientPlayer * GetLocalPlayer();

ClientPlayer * GetClientPlayer(unsigned int index);

bool isClientAlive(ClientPlayer * Target);
