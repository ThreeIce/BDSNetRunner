#pragma once
#include "BDS.hpp"

enum EventType : UINT16 {
	Nothing = 0,
	onServerCmd = 1,
	onServerCmdOutput = 2,
	onFormSelect = 3,
	onUseItem = 4,
	onPlacedBlock = 5,
	onDestroyBlock = 6,
	onStartOpenChest = 7,
	onStartOpenBarrel = 8,
	onStopOpenChest = 9,
	onStopOpenBarrel = 10,
	onSetSlot = 11,
	onChangeDimension = 12,
	onMobDie = 13,
	onMobHurt = 14,
	onRespawn = 15,
	onChat = 16,
	onInputText = 17,
	onCommandBlockUpdate = 18,
	onInputCommand = 19,
	onBlockCmd = 20,
	onNpcCmd = 21,
	onLoadName = 22,
	onPlayerLeft = 23,
	onMove = 24,
	onAttack = 25,
	onLevelExplode = 26
};

// ����ģʽ
static enum ActMode : UINT16
{
	BEFORE = 0,
	AFTER = 1
};

// ���йؼ���
struct ACTEVENT {
	const std::string ONSERVERCMD = u8"onServerCmd";
	const std::string ONSERVERCMDOUTPUT = u8"onServerCmdOutput";
	const std::string ONFORMSELECT = u8"onFormSelect";
	const std::string ONUSEITEM = u8"onUseItem";
	const std::string ONMOVE = u8"onMove";
	const std::string ONATTACK = u8"onAttack";
	const std::string ONPLACEDBLOCK = u8"onPlacedBlock";
	const std::string ONDESTROYBLOCK = u8"onDestroyBlock";
	const std::string ONSTARTOPENCHEST = u8"onStartOpenChest";
	const std::string ONSTARTOPENBARREL = u8"onStartOpenBarrel";
	const std::string ONCHANGEDIMENSION = u8"onChangeDimension";
	const std::string ONLOADNAME = u8"onLoadName";
	const std::string ONPLAYERLEFT = u8"onPlayerLeft";
	const std::string ONSTOPOPENCHEST = u8"onStopOpenChest";
	const std::string ONSTOPOPENBARREL = u8"onStopOpenBarrel";
	const std::string ONSETSLOT = u8"onSetSlot";
	const std::string ONMOBDIE = u8"onMobDie";
	const std::string ONRESPAWN = u8"onRespawn";
	const std::string ONCHAT = u8"onChat";
	const std::string ONINPUTTEXT = u8"onInputText";
	const std::string ONINPUTCOMMAND = u8"onInputCommand";
	const std::string ONLEVELEXPLODE = u8"onLevelExplode";
};

struct Events {
	EventType type;	// �¼�����
	ActMode mode;	// ����ģʽ
	int result;		// �¼������ע��After�¼�ʱ����ֵ��Ч��
	void* data;		// ԭʼ����ָ��
};

struct ServerCmdEvent {
	char* cmd;	// ָ������
public:
	ServerCmdEvent() {
		memset(this, 0, sizeof(ServerCmdEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
	}
};

struct ServerCmdOutputEvent {
	char* output;	// �����Ϣ
public:
	ServerCmdOutputEvent() {
		memset(this, 0, sizeof(ServerCmdOutputEvent));
	}
	void releaseAll() {
		if (output) {
			delete output;
			output = NULL;
		}
	}
};

struct PlayerEvent {
	char* playername;	// �������
	char* dimension;	// �������ά��
	Vec3 XYZ;			// �������λ��
	int dimensionid;	// �������ά��ID
	bool isstand;		// ����Ƿ������ڷ���/����
public:
	PlayerEvent() {
		memset(this, 0, sizeof(PlayerEvent));
	}
	void releaseAll() {
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
	}
};

struct FormSelectEvent : PlayerEvent {
	char* uuid;			// ���uuid��Ϣ
	char* selected;		// �����ش���ѡ������Ϣ
	int formid;			// ����ID
public:
	FormSelectEvent() {
		memset(this, 0, sizeof(FormSelectEvent));
	}
	void releaseAll() {
		if (uuid) {
			delete uuid;
			uuid = NULL;
		}
		if (selected) {
			delete selected;
			selected = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct UseItemEvent : PlayerEvent {
	char* itemname;		// ��Ʒ����
	BPos3 position;		// ������������λ��
	short itemid;		// ��ƷID
	short itemaux;		// ��Ʒ����ֵ
public:
	UseItemEvent() {
		memset(this, 0, sizeof(UseItemEvent));
	}
	void releaseAll() {
		if (itemname) {
			delete itemname;
			itemname = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct BlockEvent : PlayerEvent {
	char* blockname;	// ��������
	BPos3 position;		// ������������λ��
	short blockid;		// ����ID
public:
	BlockEvent() {
		memset(this, 0, sizeof(BlockEvent));
	}
	void releaseAll() {
		if (blockname) {
			delete blockname;
			blockname = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct PlacedBlockEvent : BlockEvent {
};

struct DestroyBlockEvent : BlockEvent {
};

struct StartOpenChestEvent : BlockEvent {
};

struct StartOpenBarrelEvent : BlockEvent {
};

struct StopOpenChestEvent : BlockEvent {
};

struct StopOpenBarrelEvent : BlockEvent {
};

struct SetSlotEvent : PlayerEvent {
	char* itemname;		// ��Ʒ����
	char* blockname;	// ��������
	BPos3 position;		// ������������λ��
	int itemcount;		// ��Ʒ����
	int slot;			// ��������λ��
	short itemaux;		// ��Ʒ����ֵ
	short blockid;		// ����ID
	short itemid;		// ��ƷID
	
public:
	SetSlotEvent() {
		memset(this, 0, sizeof(SetSlotEvent));
	}
	void releaseAll() {
		if (itemname) {
			delete itemname;
			itemname = NULL;
		}
		if (blockname) {
			delete blockname;
			blockname = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};


struct ChangeDimensionEvent : PlayerEvent {
};

struct MobDieEvent {
	char* mobname;		// ��������
	char* playername;	// ������֣���Ϊ������������Ӵ���Ϣ��
	char* dimension;	// �������ά�ȣ�������Ϣ��
	char* mobtype;		// ��������
	char* srcname;		// �˺�Դ����
	char* srctype;		// �˺�Դ����
	Vec3 XYZ;			// ��������λ��
	int dimensionid;	// ��������ά��ID
	int dmcase;			// �˺�����ԭ��ID
	bool isstand;		// ����Ƿ������ڷ���/���գ�������Ϣ��
public:
	MobDieEvent() {
		memset(this, 0, sizeof(MobDieEvent));
	}
	void releaseAll() {
		if (mobname) {
			delete mobname;
			mobname = NULL;
		}
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
		if (mobtype) {
			delete mobtype;
			mobtype = NULL;
		}
		if (srcname) {
			delete srcname;
			srcname = NULL;
		}
		if (srctype) {
			delete srctype;
			srctype = NULL;
		}
	}
};

struct MobHurtEvent : MobDieEvent {
	char* dmtype;	// ������������
	float health;	// ����Ѫ��
	int dmcount;	// �������˾���ֵ
public:
	MobHurtEvent() {
		memset(this, 0, sizeof(MobHurtEvent));
	}
	void releaseAll() {
		if (dmtype) {
			delete dmtype;
			dmtype = NULL;
		}
		((MobDieEvent*)this)->releaseAll();
	}
};

struct RespawnEvent : PlayerEvent {
};

struct ChatEvent {
	char* playername;	// ���������֣�����Ϊ������������鷢�ԣ�
	char* target;		// ����������
	char* msg;			// ���յ�����Ϣ
	char* chatstyle;	// ��������
public:
	ChatEvent() {
		memset(this, 0, sizeof(ChatEvent));
	}
	void releaseAll() {
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (target) {
			delete target;
			target = NULL;
		}
		if (msg) {
			delete msg;
			msg = NULL;
		}
		if (chatstyle) {
			delete chatstyle;
			chatstyle = NULL;
		}
	}
};

struct InputTextEvent : PlayerEvent {
	char* msg;	// ������ı�
public:
	InputTextEvent() {
		memset(this, 0, sizeof(InputTextEvent));
	}
	void releaseAll() {
		if (msg) {
			delete msg;
			msg = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct CommandBlockUpdateEvent : PlayerEvent {
	char* cmd;		// �������µ���ָ��
	char* actortype;// ʵ�����ͣ��������µ��ǷǷ��飬���Ӵ���Ϣ��
	BPos3 position;	// ���������λ��
	bool isblock;	// �Ƿ��Ƿ���
public:
	CommandBlockUpdateEvent() {
		memset(this, 0, sizeof(CommandBlockUpdateEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
		if (actortype) {
			delete actortype;
			actortype = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct InputCommandEvent : PlayerEvent {
	char* cmd;	// ��������ָ��
public:
	InputCommandEvent() {
		memset(this, 0, sizeof(InputCommandEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct BlockCmdEvent {
	char* cmd;		// ����ִ�е�ָ��
	char* name;		// ִ�����Զ�������
	char* dimension;// ���������ά��
	BPos3 position;	// ִ��������λ��
	int dimensionid;// ���������ά��ID
	int tickdelay;	// �����趨�ļ��ʱ��
	int type;		// ִ��������
public:
	BlockCmdEvent() {
		memset(this, 0, sizeof(BlockCmdEvent));
	}
	void releaseAll() {
		if (cmd) {
			delete cmd;
			cmd = NULL;
		}
		if (name) {
			delete name;
			name = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
	}
};

struct NpcCmdEvent {
	char* npcname;		// NPC����
	char* entity;		// NPCʵ���ʶ��
	char* dimension;	// NPC����ά��
	char* actions;		// ָ���б�
	Vec3 position;		// NPC����λ��
	int actionid;		// ѡ����
	int entityid;		// NPCʵ���ʶID
	int dimensionid;	// NPC����ά��ID
public:
	NpcCmdEvent() {
		memset(this, 0, sizeof(NpcCmdEvent));
	}
	void releaseAll() {
		if (npcname) {
			delete npcname;
			npcname = NULL;
		}
		if (entity) {
			delete entity;
			entity = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
		if (actions) {
			delete actions;
			actions = NULL;
		}
	}
};

struct LoadNameEvent {
	char* playername;	// �������
	char* uuid;			// ���uuid�ַ���
	char* xuid;			// ���xuid�ַ���
	char* ability;		// �������ֵ�б�����ѡ����ҵ����ã�
public:
	LoadNameEvent() {
		memset(this, 0, sizeof(LoadNameEvent));
	}
	void releaseAll() {
		if (playername) {
			delete playername;
			playername = NULL;
		}
		if (uuid) {
			delete uuid;
			uuid = NULL;
		}
		if (xuid) {
			delete xuid;
			xuid = NULL;
		}
		if (ability) {
			delete ability;
			ability = NULL;
		}
	}
};

struct PlayerLeftEvent : LoadNameEvent {
};

struct MoveEvent : PlayerEvent {
};

struct AttackEvent : PlayerEvent
{
	char* actorname;	// ������ʵ������
	char* actortype;	// ������ʵ������
	Vec3 actorpos;		// ������ʵ������λ��
public:
	AttackEvent() {
		memset(this, 0, sizeof(AttackEvent));
	}
	void releaseAll() {
		if (actorname) {
			delete actorname;
			actorname = NULL;
		}
		if (actortype) {
			delete actortype;
			actortype = NULL;
		}
		((PlayerEvent*)this)->releaseAll();
	}
};

struct LevelExplodeEvent {
	char* entity;		// ��ը��ʵ���ʶ��������Ϊ�գ�
	char* blockname;	// ��ը������������Ϊ�գ�
	char* dimension;	// ��ը������ά��
	Vec3 position;		// ��ը������λ��
	int entityid;		// ��ը��ʵ���ʶID
	int dimensionid;	// ��ը������ά��ID
	float explodepower;	// ��ըǿ��
	short blockid;		// ��ը����ID
public:
	LevelExplodeEvent() {
		memset(this, 0, sizeof(LevelExplodeEvent));
	}
	void releaseAll() {
		if (entity) {
			delete entity;
			entity = NULL;
		}
		if (dimension) {
			delete dimension;
			dimension = NULL;
		}
	}
};