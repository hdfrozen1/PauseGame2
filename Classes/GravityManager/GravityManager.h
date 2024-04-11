#ifndef __GRAVITY_MANAGER_H__
#define __GRAVITY_MANAGER_H__



class GravityManager
{
public:
	static GravityManager* getInstance();

	void setGravityValue(float newVolume);
private:
	static GravityManager* _instance;

	float _gravityvalue;
};

#endif // !__GRAVITY_MANAGER_H__