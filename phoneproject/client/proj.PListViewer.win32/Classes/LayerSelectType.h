#pragma once

#include <cocos2d.h>
#include <string>

USING_NS_CC;

// ����ѡ��������֡�������������Ӷ���
class LayerSelectType : public CCLayer {
public:
	virtual bool init();

	static CCScene* scene();

	void onBtnAnimationView(CCObject* pSender);

	void onBtnParticleView(CCObject* pSender);

	CREATE_FUNC(LayerSelectType);
};