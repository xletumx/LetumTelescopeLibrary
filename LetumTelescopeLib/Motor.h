#pragma once
#ifndef MOTOR_H_
#define MOTOR_H_

enum EMotorState
{
	Off = 0,
	Idle = 1,
	Running = 2,
	HighEnd = 3,
	LowEnd = 4,
	ErrorRange = 5
};

class Motor
{
private:
	//float speed;
	int Stepping;
	int stepSize;
	float homePosition;
	float Position;
	float servoPosition;
	float highEnd;
	float lowEnd;

	EMotorState State;

public:
	Motor(int sizeofstep, float high, float low, float home, int steps);
	virtual ~Motor(void);

	virtual void reset(void);
	virtual void startMotor(void);
	virtual void pauseMotor(void);

	int getMotorState(void);
	int getStepping(void);
	float getServoPosition(void);
	float getHomePosition(void);
	float getPosition(void);

	void setStepping(int steps);
	void setServoPosition(float pos);
	void setServoPositionToPosition(void);
	void setHomePosition(float home);
	void setHomePositionToPositon(void);

	virtual int Step(void);
};

#endif
