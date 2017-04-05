// chase scene based on Silent's code
#pragma once

#include "vcclasses.h"

#define MAX_CHASE_CARS 20
#define MAX_CHASE_FRAMES 1200

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
	static CAutomobile *pChaseCars[MAX_CHASE_CARS];                           // CRecordDataForChase::pChaseCars
	static CCarStateEachFrame *pBaseMemForCar[MAX_CHASE_CARS];                // CRecordDataForChase::pBaseMemForCar
	static float AnimTime;                                                    // CRecordDataForChase::AnimTime

	static bool initialise();
	static CAutomobile *TurnChaseCarIntoScriptCar(int);                       // CRecordDataForChase::TurnChaseCarIntoScriptCar
	static void RemoveCarFromChase(int);                                      // CRecordDataForChase::RemoveCarFromChase
	static void CleanUpCarsForChaseScene(void);                               // CRecordDataForChase::CleanUpCarsForChaseScene
	static void SetUpCarsForChaseScene(void);                                 // CRecordDataForChase::SetUpCarsForChaseScene
	static void CleanUpChaseScene(void);                                      // CRecordDataForChase::CleanUpChaseScene
	static void StartChaseScene(float);                                       // CRecordDataForChase::StartChaseScene
	static void GiveUsACar(int, CVector, float, CAutomobile **, unsigned char, unsigned char); // CRecordDataForChase::GiveUsACar
	static void ProcessControlCars(void);                                     // CRecordDataForChase::ProcessControlCars
	static void RestoreInfoForCar(CAutomobile *, CCarStateEachFrame *, bool); // CRecordDataForChase::RestoreInfoForCar
	static void RestoreInfoForMatrix(CMatrix &, CCarStateEachFrame *);        // CRecordDataForChase::RestoreInfoForMatrix
	static void SaveOrRetrieveCarPositions(void);                             // CRecordDataForChase::SaveOrRetrieveCarPositions
	static void Init(void);                                                   // CRecordDataForChase::Init
};
