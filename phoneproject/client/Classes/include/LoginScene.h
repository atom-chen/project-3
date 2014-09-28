#ifndef __LOGINSCENE_H__
#define __LOGINSCENE_H__

#include "cocos2d.h"
#include "CocoGUILIB/BaseClasses/UIWidget.h"
#include "CocoGUILIB/UIWidgets/UINodeContainer.h"
#include "CocoGUILIB/System/UILayer.h"
#include "CocoGUILIB/System/UIHelper.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "network/HttpClient.h"
#include "ActionStubs.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class LoginScene : public CCLayerColor
{
	bool _init();

public:
	virtual bool init();

	virtual void onExit();

	static CCScene* scene();

	CREATE_FUNC(LoginScene);

	void Update(float dt);

	void IOSelect(float dt);

	void StartPatching();

	void PatchingUpdate(float dt);

	void OnBtnLogin(CCObject* sender);					// "��½" ��ť
	void OnBtnGenRandName(CCObject* sender);	// "���" ��ť
	void OnBtnOK(CCObject* sender);						// ������ɫ���� "ȷ��" ��ť
	void OnBtnCancel(CCObject* sender);				// ������ɫ���� "ȡ��" ��ť

	void OnBtnReConnect(CCObject* sender);			// ��������

	void SendLoginCmd();			// ���͵�½��������

	void JumpToCreateRolePage();
	void JumpToLoginPage();

	// just for test
	void OnBtnDanjiMode(CCObject* sender);

	void onHttpRequestGetUpdateInfo(CCHttpClient *sender, CCHttpResponse *response);

	void OnBtnNoticeClose(CCObject* sender);

	UIWidget* m_pLoginWidget;
	UIWidget* m_pCreateRoleWidget;
	UIWidget* m_pNoticeWidget;					// ���¹���
	UIWidget* m_pLostConnectWidget;			// �޷����ӷ�����������

	cocos2d::extension::CCEditBox* m_pInputNameEditBox;

	UIHelper m_uiSystem;

	UILayer* m_pUILayer;

	aeditor::ActionTemplateTable* m_actionRunner;

	// data from config.xml
	std::string m_strIP;
	int m_nPort;
	std::string m_strUpdateInfoUrl;
	std::string m_strPatchUrl;
};

#endif
