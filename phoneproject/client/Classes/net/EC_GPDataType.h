/*
 * FILE: EC_GPDataType.h
 *
 * DESCRIPTION: Game protocol data type
 *
 * CREATED BY: CuiMing, Duyuxin, 2004/9/9
 *
 * HISTORY: 
 *
 * Copyright (c) 2004 Archosaur Studio, All Rights Reserved.
 */

#pragma once

#include "EC_RoleTypes.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Reference to External variables and functions
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Local Types and Variables and Global variables
//	
///////////////////////////////////////////////////////////////////////////

#pragma pack(1)

namespace S2C
{
	typedef unsigned char byte;

	//	��ȡѹ�����ݸ���ģ����
	template <typename T>
	bool Extract(T &ret, const byte *&pDataBuf, unsigned int &dwDataSize)
	{
		//	��ȡ������������
		if (dwDataSize >= sizeof(T))
		{
			ret = *(const T*)pDataBuf;
			pDataBuf += sizeof(T);
			dwDataSize -= sizeof(T);
			return true;
		}
		return false;
	}

	template <typename T>
	bool Extract(T *pRet, int count, const byte *&pDataBuf, unsigned int &dwDataSize)
	{
		//	��ȡ����
		if (count >=0)
		{
			unsigned int s = sizeof(T)*count;
			if (dwDataSize >= s)
			{
				::memcpy(pRet, pDataBuf, s);
				pDataBuf += s;
				dwDataSize -= s;
				return true;
			}
		}
		return false;
	}

	//	Data type ---------------------------
	struct info_player_1
	{
		int cid;
		A3DVECTOR3 pos;
		unsigned short crc_e;
		unsigned short crc_c;
		unsigned char dir;		//256�Ķ�������ʾ����
		unsigned char level2;
		int state;
		int state2;

		bool CheckValid(size_t buf_size, size_t& sz) const
		{
			if (buf_size < sizeof(*this))
				return false;

			return buf_size >= sz;
		}
	};

	struct info_player_2		//name ,customize data �����ı�
	{
		unsigned char size;
		char data[1];
	};

	struct info_player_3		//viewdata of equipments and special effect
	{
		unsigned char size;
		char  data[1];
	};

	struct info_player_4		//detail
	{
		unsigned short size;
		char	data[1];
	};

	//	Commands ----------------------------

	enum	//	Command ID
	{
		PROTOCOL_COMMAND = -1,	//	Reserved for protocol
		
		PLAYER_INFO_1 = 0,
		PLAYER_INFO_2,
		PLAYER_INFO_3,
		PLAYER_INFO_4,
	};

	struct cmd_header
	{
        unsigned short cmd;
	};

	//	object �뿪�ɼ�����
	struct cmd_leave_slice
	{
		int id;
	};

	//	player����λ��
	struct cmd_notify_hostpos
	{
		A3DVECTOR3 vPos;
		int tag;
	};

	struct cmd_change_curr_title_re
	{
		int roleid;
		unsigned short titleid;
	};
	struct cmd_modify_title_notify
	{
		unsigned short id;
		int expiretime;
		char flag;
	};
	struct cmd_refresh_signin
	{
		char	type; // ͬ��ԭ�� 0��ʼ1���ݲ�ͬ��2ǩ��3��ǩ4�콱
		int		monthcalendar;// ��ǰ��ǩ������
		int		curryearstate; // ��ǰ���·�ǩ��״̬
		int		lastyearstate; // ȥ���·�ǩ��״̬
		int		updatetime;  // ǩ���������һ�α��ʱ��  
		int		localtime;   // ��ǰ������ʱ��
	};
}

namespace C2S
{
	typedef unsigned char byte;

	//	Data type ---------------------------

	//	Commands ----------------------------
	enum
	{
		PLAYER_MOVE,		//	0
		LOGOUT,
	};

	struct cmd_header
	{
        unsigned short cmd;
	};

	struct cmd_player_move
	{
		A3DVECTOR3 vCurPos;
		A3DVECTOR3 vNextPos;
		unsigned short use_time;
		short sSpeed;				//	Move speed 8.8 fix-point
		unsigned char move_mode;	//	Walk run swim fly .... walk_back run_back
		unsigned short stamp;		//	move command stamp
	};

	struct cmd_stop_move
	{
		A3DVECTOR3 vCurPos;
		short sSpeed;				//	Moving speed in 8.8 fix-point
		unsigned char dir;			//	����ķ���
		unsigned char move_mode;	//	Walk run swim fly .... walk_back run_back
		unsigned short stamp;		//	move command stamp
		unsigned short use_time;
	};

	struct cmd_player_logout
	{
		int iOutType;
	};
}

#pragma pack()

