#ifndef __SETTING_LAYER_H__
#define __SETTING_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class SettingLayer :public Layer {
public:
	static Layer* create(Node* character);
	virtual bool init(Node* character);
private:
	ui::Slider* _graSlider;
	ui::Slider* _camSlider;
	ui::Slider* _spdSlider;

	Size _graSliderSize;
	Size _camSliderSize;
	Size _spdSliderSize;

	Node* _graNode;
	Node* _camNode;
	Node* _spdNode;
	
	float y_pos;
	float distance;
	Size visibleSize;
	float scales;
	Node* _char;

	bool onCam();
};

#endif // !__SETTING_LAYER_H__
