// chase scene based on Silent's code
#pragma once

#include "vcclasses.h"

#define MAX_CHASE_CARS 20

template<typename T>
struct CPackedVector
{
	T x, y, z;
};

struct CCarStateEachFrame
{
	CPackedVector<short> velocity;
	CPackedVector<char>  right;
	CPackedVector<char>  up;
	char                 steerAngle;
	char                 gasPedal;
	char                 brakePedal;
	bool                 handbrakeUsed;
	CVector              position;
};

class CRecordDataForChaseHack : public CRecordDataForChase
{
public:
	static CAutomobile *pChaseCars[MAX_CHASE_CARS];
	static CCarStateEachFrame *pBaseMemForCar[MAX_CHASE_CARS];
	static float AnimTime;

	static bool initialise();
	static CAutomobile *TurnChaseCarIntoScriptCar(int);
	static void RemoveCarFromChase(int);
	static void CleanUpCarsForChaseScene(void);
	static void SetUpCarsForChaseScene(void);
	static void CleanUpChaseScene(void);
	static void StartChaseScene(float);
	static void GiveUsACar(int, CVector, float, CAutomobile **, unsigned char, unsigned char);
	static void ProcessControlCars(void);
	static void RestoreInfoForCar(CAutomobile *, CCarStateEachFrame *, bool);
	static void RestoreInfoForMatrix(CMatrix &, CCarStateEachFrame *);
	static void SaveOrRetrieveCarPositions(void);
	static void Init(void);
};
