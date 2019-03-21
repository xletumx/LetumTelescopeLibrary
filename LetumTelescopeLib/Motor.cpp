#include "Motor.h"
#include "math.h"



Motor::Motor(int sizeofstep = 200, float high = 360.0f, float low = 0.0f, float home = 0.0f, int steps = 1)
	: stepSize(sizeofstep), highEnd(high), lowEnd(low), homePosition(home), Stepping(steps), State(EMotorState::Off)
{
	this->servoPosition = 0.0f;
}


Motor::~Motor(void)
{
	this->reset();
	this->State = EMotorState::Off;
}

void Motor::reset(void)
{
	this->Position = 0.0f;
	//this->homePosition = 0.0f;
	//this->Stepping = 1;

	if (this->servoPosition < this->highEnd && this->servoPosition > this->lowEnd)
	{
		this->State = EMotorState::Idle;
	}
	else
	{
		this->State = EMotorState::ErrorRange;
	}

	//this->servoPosition = 0.0f;
};

void Motor::startMotor(void)
{
	if (this->servoPosition < this->highEnd && this->servoPosition > this->lowEnd)
	{
		this->State = EMotorState::Running;
	}
};
void Motor::pauseMotor(void)
{
	if (this->servoPosition < this->highEnd && this->servoPosition > this->lowEnd)
	{
		this->State = EMotorState::Idle;
	}
};

int Motor::getMotorState(void) { return this->State; };
int Motor::getStepping(void) { return this->Stepping; };
float Motor::getServoPosition(void) { return this->servoPosition; };
float Motor::getHomePosition(void) { return this->homePosition; };
float Motor::getPosition(void) { return this->Position; };

void Motor::setStepping(int steps) { this->Stepping = steps; };
void Motor::setServoPosition(float pos) { this->servoPosition = pos; };
void Motor::setServoPositionToPosition(void) { this->servoPosition = this->Position; };
void Motor::setHomePosition(float home) { this->homePosition = home; };
void Motor::setHomePositionToPositon(void) { this->homePosition = this->Position; };

int Motor::Step(void)
{
	if (this->State != ErrorRange)
	{
		if (this->State == EMotorState::Running)
		{
			float newpos = this->Position + ((360 / this->stepSize) / this->Stepping);

			if (newpos > 360)
			{
				this->Position = 0.0f;
			}
			else
			{
				this->Position = newpos;
			}

			newpos = this->servoPosition + ((360 / this->stepSize) / this->Stepping);

			if (this->servoPosition < this->highEnd)
			{
				if ((this->servoPosition + newpos) <= this->highEnd)
				{
					this->servoPosition = newpos;
				}
				else
				{
					this->servoPosition = this->highEnd;
					this->State = HighEnd;
				}
			}
		}

		if (this->servoPosition > this->highEnd || this->servoPosition < this->lowEnd) // if servo upper or lower limit is passed, set motor state to error out of range
		{
			this->State = EMotorState::ErrorRange;
		}
	}

	return this->State;
};