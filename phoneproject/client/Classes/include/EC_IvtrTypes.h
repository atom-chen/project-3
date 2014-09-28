/*
 * FILE: EC_IvtrTypes.h
 *
 * DESCRIPTION: 
 *
 * CREATED BY: Duyuxin, 2004/11/19
 *
 * HISTORY: 
 *
 * Copyright (c) 2004 Archosaur Studio, All Rights Reserved.
 */

#pragma once

///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////

#ifndef NUM_MAGICCLASS
#define NUM_MAGICCLASS		5
#endif	//	NUM_MAGICCLASS

//	Equipment endurance scale
#define ENDURANCE_SCALE		100
//	Player item price scale
#define PLAYER_PRICE_SCALE	1.0f
//	Weapon endurance reduce speed
#define WEAPON_RUIN_SPEED	-2
//	Armor endurance reduce speed
#define ARMOR_RUIN_SPEED	-25

//	Inventory type
enum
{
	IVTRTYPE_PACK = 0,		//	Normal pack
	IVTRTYPE_EQUIPPACK,		//	Equipment
	IVTRTYPE_TASKPACK,		//	Task pack
	IVTRTYPE_TRASHBOX,		//	Trash box
	IVTRTYPE_TRASHBOX2,		//	Trash box - material box
	IVTRTYPE_TRASHBOX3,		//	Trash box - fashion box
	IVTRTYPE_ACCOUNT_BOX,	//  User account box
};

//	Index of item in equipment inventory
enum
{
	EQUIPIVTR_WEAPON = 0,
	EQUIPIVTR_HEAD,
	EQUIPIVTR_NECK,
	EQUIPIVTR_SHOULDER,
	EQUIPIVTR_BODY,
	EQUIPIVTR_WAIST,
	EQUIPIVTR_LEG,
	EQUIPIVTR_FOOT,
	EQUIPIVTR_WRIST,
	EQUIPIVTR_FINGER1,
	EQUIPIVTR_FINGER2,
	EQUIPIVTR_PROJECTILE,
	EQUIPIVTR_FLYSWORD,
	EQUIPIVTR_FASHION_BODY,
	EQUIPIVTR_FASHION_LEG,
	EQUIPIVTR_FASHION_FOOT,
	EQUIPIVTR_FASHION_WRIST,
	EQUIPIVTR_RUNE,
	EQUIPIVTR_BIBLE,
	EQUIPIVTR_SPEAKER,
	EQUIPIVTR_AUTOHP,
	EQUIPIVTR_AUTOMP,
	EQUIPIVTR_POCKET,
	EQUIPIVTR_GOBLIN,
	EQUIPIVTR_CERTIFICATE,
	EQUIPIVTR_FASHION_HEAD,
	EQUIPIVTR_FORCE_TOKEN,
	EQUIPIVTR_DYNSKILLEQUIP1,
	EQUIPIVTR_DYNSKILLEQUIP2,
	EQUIPIVTR_FASHION_WEAPON,
	SIZE_EQUIPIVTR,
};

//	Inventory size
enum
{
	IVTRSIZE_EQUIPPACK	= SIZE_EQUIPIVTR,	//	Equipment
	IVTRSIZE_TASKPACK	= 20,	//	Task pack
	IVTRSIZE_DEALPACK	= 24,	//	Deal pack
	IVTRSIZE_NPCPACK	= 32,	//	NPC pack
	IVTRSIZE_TRASHBOX	= 16,	//	Trash box
	IVTRSIZE_BUYPACK	= 12,	//	Buy pack
	IVTRSIZE_SELLPACK	= 12,	//	Sell pack
	IVTRSIZE_BOOTHSPACK	= 12,	//	Default booth pack for selling
	IVTRSIZE_BOOTHBPACK = 12,	//	Default booth pack for buying
	IVTRSIZE_BOOTHSPACK_MAX	= 20,	//	Max booth pack for selling (player may use certificate...)
	IVTRSIZE_BOOTHBPACK_MAX = 20,	//	Max booth pack for buying
	
	NUM_NPCIVTR			= 8,	//	NPC inventory number
};

//	Equip mask
enum
{
	EQUIP_MASK_WEAPON       	= 0x00000001,
	EQUIP_MASK_HEAD         	= 0x00000002,
	EQUIP_MASK_NECK         	= 0x00000004,
	EQUIP_MASK_SHOULDER     	= 0x00000008,
	EQUIP_MASK_BODY         	= 0x00000010,
	EQUIP_MASK_WAIST        	= 0x00000020,
	EQUIP_MASK_LEG          	= 0x00000040,
	EQUIP_MASK_FOOT         	= 0x00000080,
	EQUIP_MASK_WRIST        	= 0x00000100,
	EQUIP_MASK_FINGER1      	= 0x00000200,
	EQUIP_MASK_FINGER2      	= 0x00000400,
	EQUIP_MASK_PROJECTILE   	= 0x00000800,
	EQUIP_MASK_FLYSWORD			= 0x00001000,
	EQUIP_MASK_FASHION_BODY		= 0x00002000,
	EQUIP_MASK_FASHION_LEG		= 0x00004000,
	EQUIP_MASK_FASHION_FOOT		= 0x00008000,
	EQUIP_MASK_FASHION_WRIST	= 0x00010000,
	EQUIP_MASK_RUNE				= 0x00020000,
	EQUIP_MASK_BIBLE			= 0x00040000,
	EQUIP_MASK_SPEAKER			= 0x00080000,
	EQUIP_MASK_AUTOHP			= 0x00100000,
	EQUIP_MASK_AUTOMP			= 0x00200000,
	EQUIP_MASK_POCKET			= 0x00400000,
	EQUIP_MASK_GOBLIN			= 0x00800000,
	EQUIP_MASK_CERTIFICATE		= 0x01000000,
	EQUIP_MASK_FASHION_HEAD		= 0x02000000,
	EQUIP_MASK_FORCE_TICKET		= 0x04000000,
	EQUIP_MASK_DYNSKILLEQUIP1	=	0x08000000,
	EQUIP_MASK_DYNSKILLEQUIP2	=	0x10000000,
	EQUIP_MASK_FASHION_WEAPON	=	0x20000000,
	EQUIP_MASK_ALL				= 0x0fffffff,
};

//	Weapon type
enum
{
    WEAPONTYPE_MELEE = 0,
    WEAPONTYPE_RANGE = 1,
};

//	Shortcut
enum
{
	NUM_HOSTSCSETS1 = 5,	// expanded from 3 to 5 (2009.05.27)
	NUM_HOSTSCSETS2 = 3,
	SIZE_HOSTSCSET1 = 9,	// expanded from 6 to 9 (2009.05.27)
	SIZE_HOSTSCSET2 = 8,

	SIZE_FASHIONSCSET = 240,
};

//	Pet food type
enum
{
	PET_FOOD_GRASS = 0,
	PET_FOOD_MEAT,
	PET_FOOD_VEGETABLE,
	PET_FOOD_FRUIT,
	PET_FOOD_WATER,
	MAX_PET_FOOD,
};

///////////////////////////////////////////////////////////////////////////
//	
//	Types and Global variables
//	
///////////////////////////////////////////////////////////////////////////

#pragma pack(1)

struct IVTR_ESSENCE_WEAPON
{
    short	weapon_type;
	short	weapon_dealy;
	int		weapon_class;
	int		weapon_level;
    int		require_projectile; 	//	��Ҫ��ҩ������
    int		damage_low;         	//	��������С��ֵ
    int 	damage_high;        	//	����������ֵ
    int 	magic_damage_low;		//	ħ������
    int 	magic_damage_high;		//	ħ������
//  int 	attack;					//	������
    int 	attack_speed;
    float	attack_range;
    float	attack_short_range;
};

struct IVTR_ESSENCE_ARROW
{
	unsigned int	dwBowMask;
	int		iDamage;
	int		iDamageScale;			//	Percent
	int		iWeaponReqLow;
	int		iWeaponReqHigh;
};

struct IVTR_ESSENCE_DECORATION
{
	int		damage;
	int		magic_damage;
	int		defense;
	int		armor;
	int		resistance[NUM_MAGICCLASS];
};

struct IVTR_ESSENCE_ARMOR
{
	int		defense;
	int		armor;
	int		mp_enhance;
	int		hp_enhance;
	int		resistance[NUM_MAGICCLASS];
};

struct IVTR_ESSENCE_FASHION
{
	int require_level;
	unsigned short color;
	unsigned short gender;
};

struct IVTR_ESSENCE_FLYSWORD
{
	int		cur_time;
	int		max_time;
	short	require_level;
    short	level;
	int		profession;
	size_t	time_per_element;
	float	speed_increase;
	float	speed_increase2;		//	���ٷ����ٶ�
};

struct IVTR_ESSENCE_WING
{
	int		require_level;
	size_t	mp_launch;
	size_t	mp_per_second;
	float	speed_increase;
};

struct IVTR_ESSENCE_AUTOHP
{
	int		hp_left;
	float	trigger;
};

struct IVTR_ESSENCE_AUTOMP
{
	int		mp_left;
	float	trigger;
};

struct IVTR_ESSENCE_PETEGG
{
	int		req_level;          //	������Ҽ���
	int		req_class;          //	�������ְҵ
	int		honor_point;        //	�øж�
	int		pet_tid;            //	�����ģ��ID
	int		pet_vis_tid;        //	����Ŀɼ�ID�����Ϊ0�����ʾ������ɼ�ID��
	int		pet_egg_tid;        //	���ﵰ��ID
	int		pet_class;          //	�������� ս�裬��裬���ͳ�
	short	level;				//	���Ｖ��
	unsigned short	color;			//	������ɫ�����λΪ1��ʾ��Ч��Ŀǰ���������Ч
	int		exp;                //	���ﵱǰ����
	int		skill_point;        //	ʣ�༼�ܵ�
	unsigned short name_len;	//	���ֳ��� 
	unsigned short skill_count;	//	��������		
	wchar_t	name[8];			//	��������
	//	������漼�ܱ�
	/*
	struct
	{	
		int skill
		int level;

	} skills[]
	 */
};

struct IVTR_ESSENCE_DESTROYING
{
	int tid;
};

struct IVTR_ESSENCE_GOBLIN
{
	struct _GOBLIN_DATA
	{
		unsigned int exp;			//	��ǰ����ֵ
		short	level;				//	��ǰ�ȼ�
		
		short	total_attribute;	//	�������������Ե�������������װ�����ӵļ������Գ�ʼֵ
		short	strength;			//	����, �ɼ����Ե������������ֵ��������װ�����ӵļ������Գ�ʼֵ
		short	agility;			//	����
		short	vitality;			//	����
		short	energy;				//	����

		short	total_genius;		//	�����������츳��������������װ�����ӵ�
		short	genius[5];			//	��ľˮ����0-4 //�ɼ��츳����������츳ֵ��������װ�����ӵ�
		
		short	refine_level;		//	�����ȼ�
		int		stamina; 			//	����
		int		status_value;		//	0: ��ȫ״̬��>0��ת��״̬��-1:�ɽ���״̬ 
	};

	_GOBLIN_DATA	data;

	int equip_cnt;					//	װ������
//	unsigned int equipid[];			//	װ��id
	int skill_cnt;					//	��ѧ��ļ����� 
/*	struct
	{	
		unsigned short skill
		short level;

	} skills[]; */
};

struct IVTR_ESSENCE_WEDDING_BOOKCARD 
{
	int	year;
	int	month;
	int	day;
};

struct IVTR_ESSENCE_WEDDING_INVITECARD 
{
	int	start_time;	//	����ʼʱ��
	int	end_time;	//	�������ʱ��
	int	groom;		//	���ɽ�ɫ ID
	int	bride;		//	�����ɫ ID
	int	scene;		//	���������������������ƺ;���λ��
	int	invitee;	//	�������� ID
};

struct IVTR_ESSENCE_FORCE_TOKEN
{
	int require_force;	// ��Ʒʹ��������������
	int repu_total;		// �洢�Ķ������������ܶ�
	int repu_inc_ratio; // ÿ�λ������ʱ�������ӵ�����ϵ����1~100��Ӧ0%~100%
};

#pragma pack()

///////////////////////////////////////////////////////////////////////////
//	
//	Declare of Global functions
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Inline functions
//	
///////////////////////////////////////////////////////////////////////////



