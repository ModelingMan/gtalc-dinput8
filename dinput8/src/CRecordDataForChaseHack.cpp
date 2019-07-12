// chase scene based on Silent's code
#include "CRecordDataForChaseHack.h"
#include <cmath>
#include "vcversion.h"
#include "Globals.h"
#include "SilentCall.h"
#include "ModelIndices.h"
#include "Offset.h"

CAutomobile *CRecordDataForChaseHack::pChaseCars[MAX_CHASE_CARS];
CCarStateEachFrame *CRecordDataForChaseHack::pBaseMemForCar[MAX_CHASE_CARS];
float CRecordDataForChaseHack::AnimTime;

static void(__cdecl *CallProcessControlCars)(void);

bool CRecordDataForChaseHack::initialise()
{
	InjectHook(0x004A4F39, &CRecordDataForChaseHack::Init); // CGame::Initialise
	ReadCall(0x004D75EE, CallProcessControlCars);
	InjectHook(0x004D75EE, &CRecordDataForChaseHack::ProcessControlCars); // CWorld::Process
	InjectHook(0x004D75F3, &CRecordDataForChaseHack::SaveOrRetrieveCarPositions); // CWorld::Process
	InjectHook(0x004D7B47, &CRecordDataForChaseHack::SaveOrRetrieveCarPositions); // CWorld::Process
	return true;
}

CAutomobile *CRecordDataForChaseHack::TurnChaseCarIntoScriptCar(int id)
{
	CAutomobile *vehicle = pChaseCars[id];
	pChaseCars[id] = 0;
	vehicle->status &= 7;
	vehicle->status |= 0x18;
	return vehicle;
}

void CRecordDataForChaseHack::RemoveCarFromChase(int id)
{
	if (pChaseCars[id]) {
		CWorld::Remove(pChaseCars[id]);
		delete pChaseCars[id];
		pChaseCars[id] = 0;
	}
}

void CRecordDataForChaseHack::CleanUpCarsForChaseScene(void)
{
	for (int i = 0; i < MAX_CHASE_CARS; i++) {
		if (pChaseCars[i]) {
			CWorld::Remove(pChaseCars[i]);
			delete pChaseCars[i];
			pChaseCars[i] = 0;
		}
	}
}

void CRecordDataForChaseHack::SetUpCarsForChaseScene(void)
{
	GiveUsACar(CAR_POLICE, { 273.5422 + OFFSETX, -1167.1907, 24.9906 + OFFSETZ }, 63.0, &pChaseCars[0], 2, 1);
	GiveUsACar(CAR_ENFORCER, { 231.1783 + OFFSETX, -1388.8322, 25.9782 + OFFSETZ }, 90.0, &pChaseCars[1], 2, 1);
	GiveUsACar(CAR_TAXI, { 184.3156 + OFFSETX, -1473.251, 25.9782 + OFFSETZ }, 0.0, &pChaseCars[4], 6, 6);
	GiveUsACar(CAR_CHEETAH, { 173.8868 + OFFSETX, -1377.6514, 25.9782 + OFFSETZ }, 0.0, &pChaseCars[6], 4, 5);
	GiveUsACar(CAR_STINGER, { 102.5946 + OFFSETX, -943.9363, 25.9781 + OFFSETZ }, 270.0, &pChaseCars[7], 53, 53);
	GiveUsACar(CAR_CHEETAH, { 177.7157 + OFFSETX, -862.1865, 25.9782 + OFFSETZ }, 155.0, &pChaseCars[10], 41, 1);
	GiveUsACar(CAR_STINGER, { 170.5698 + OFFSETX, -889.0236, 25.9782 + OFFSETZ }, 154.0, &pChaseCars[11], 10, 10);
	GiveUsACar(CAR_KURUMA, { 402.6081 + OFFSETX, -917.4963, 37.381 + OFFSETZ }, 90.0, &pChaseCars[14], 34, 1);
	GiveUsACar(CAR_TAXI, { -33.4962 + OFFSETX, -938.4563, 25.9781 + OFFSETZ }, 266.0, &pChaseCars[16], 6, 6);
	GiveUsACar(CAR_KURUMA, { 49.3631 + OFFSETX, -987.605, 25.9781 + OFFSETZ }, 0.0, &pChaseCars[18], 51, 1);
	GiveUsACar(CAR_TAXI, { 179.0049 + OFFSETX, -1154.6686, 25.9781 + OFFSETZ }, 0.0, &pChaseCars[19], 6, 76);
	GiveUsACar(CAR_RUMPO, { -28.9762 + OFFSETX, -1031.3367, 25.9781 + OFFSETZ }, 242.0, &pChaseCars[2], 1, 75);
	GiveUsACar(CAR_PATRIOT, { 114.1564 + OFFSETX, -796.6938, 24.9782 + OFFSETZ }, 180.0, &pChaseCars[3], 0, 0);
}

void CRecordDataForChaseHack::CleanUpChaseScene(void)
{
	if (Status == 2 || Status == 3) {
		Status = 0;
		CleanUpCarsForChaseScene();
		for (int i = 0; i < MAX_CHASE_CARS; i++) {
			if (pBaseMemForCar[i]) {
				delete[] pBaseMemForCar[i];
				pBaseMemForCar[i] = 0;
			}
		}
	}
}

void CRecordDataForChaseHack::StartChaseScene(float)
{
	SetUpCarsForChaseScene();
	Status = 2;
	CFileMgr::SetDir("data\\paths");
	for (int i = 0; i < MAX_CHASE_CARS; i++) {
		if (pChaseCars[i]) {
			char fileName[16];
			VCGlobals::sprintf(fileName, "chase%d.dat", i);
			if (int chaseFile = CFileMgr::OpenFile(fileName, "rb")) {
				pBaseMemForCar[i] = new CCarStateEachFrame[MAX_CHASE_FRAMES * sizeof(CCarStateEachFrame)];
				CCarStateEachFrame *state = &pBaseMemForCar[i][0];
				for (int j = 0; j < MAX_CHASE_FRAMES; j++, state++) {
					CFileMgr::Read(chaseFile, (char *)state, sizeof(CCarStateEachFrame));
					CFileMgr::Seek(chaseFile, sizeof(CCarStateEachFrame), 1);
				}
				CFileMgr::CloseFile(chaseFile);
			} else {
				pBaseMemForCar[i] = 0;
			}
		} else {
			pBaseMemForCar[i] = 0;
		}
	}
	CFileMgr::SetDir("");
	AnimTime = 0.0;
}

void CRecordDataForChaseHack::GiveUsACar(int model, CVector pos, float heading, CAutomobile **outVehicle, unsigned char firstColour, unsigned char secondColour)
{
	// work around issues with vehicles with van animation
	bool store = CCutsceneMgr::ms_cutsceneProcessing;
	CCutsceneMgr::ms_cutsceneProcessing = false;
	CStreaming::RequestModel(model, 4);
	CStreaming::LoadAllRequestedModels(false);
	CCutsceneMgr::ms_cutsceneProcessing = store;
	if (*(unsigned char *)(vcversion::AdjustOffset(0x0094DDD8) + model * 0x14) == 1) {
		CAutomobile *vehicle = new CAutomobile(model, 2);
		vehicle->GetPos() = pos;
		vehicle->status &= 7;
		vehicle->status |= 8;
		vehicle->GetMatrix().SetRotateZOnly(heading * 0.017453292f);
		vehicle->driver = 0;
		vehicle->firstColour = firstColour;
		vehicle->secondColour = secondColour;
		CWorld::Add(vehicle);
		*outVehicle = vehicle;
	}
}

void CRecordDataForChaseHack::ProcessControlCars(void)
{
	if (Status == 3) {
		for (int i = 0; i < MAX_CHASE_CARS; i++) {
			if (pChaseCars[i]) {
				pChaseCars[i]->ProcessControl();
			}
		}
	}
	CallProcessControlCars();
}

void CRecordDataForChaseHack::RestoreInfoForCar(CAutomobile *vehicle, CCarStateEachFrame *state, bool stationary)
{
	CVector oldPos = { vehicle->GetX(), vehicle->GetY(), vehicle->GetZ() };
	RestoreInfoForMatrix(vehicle->GetMatrix(), state);
	vehicle->moveSpeed = {
		static_cast<float>(state->velocity.x) / 16383.5f,
		static_cast<float>(state->velocity.y) / 16383.5f,
		static_cast<float>(state->velocity.z) / 16383.5f };
	vehicle->turnSpeed = { 0.0, 0.0, 0.0 };
	vehicle->steerAngle = static_cast<float>(state->steerAngle) / 20.0f;
	vehicle->gasPedal = static_cast<float>(state->gasPedal) / 100.0f;
	vehicle->brakePedal = static_cast<float>(state->brakePedal) / 100.0f;
	vehicle->field_1F9 &= 0xDF;
	if (state->handbrakeUsed) {
		vehicle->field_1F9 |= 0x20;
	}
	float distance = sqrt(
		pow(oldPos.x - vehicle->GetX(), 2) +
		pow(oldPos.y - vehicle->GetY(), 2) +
		pow(oldPos.z - vehicle->GetZ(), 2));
	if (distance > 15.0) {
		if (pChaseCars[14] == vehicle) {
			vehicle->firstColour = 58;
			vehicle->secondColour = 1;
		} else {
			((CVehicleModelInfo *)(CModelInfo::ms_modelInfoPtrs[vehicle->modelIndex]))->ChooseVehicleColour(vehicle->firstColour, vehicle->secondColour);
		}
	}
	if (vehicle->health < 500.0) {
		vehicle->health = 500.0;
	}
	if (stationary) {
		vehicle->gasPedal = 0.0;
		vehicle->brakePedal = 0.0;
		vehicle->moveSpeed = { 0.0, 0.0, 0.0 };
		vehicle->field_1F9 &= 0xDF;
	}
}

void CRecordDataForChaseHack::RestoreInfoForMatrix(CMatrix &matrix, CCarStateEachFrame *state)
{
	matrix.right.x = static_cast<float>(state->right.x) / 127.0f;
	matrix.right.y = static_cast<float>(state->right.y) / 127.0f;
	matrix.right.z = static_cast<float>(state->right.z) / 127.0f;
	matrix.up.x = static_cast<float>(state->up.x) / 127.0f;
	matrix.up.y = static_cast<float>(state->up.y) / 127.0f;
	matrix.up.z = static_cast<float>(state->up.z) / 127.0f;
	VCGlobals::CrossProduct(&matrix.at, matrix.right, matrix.up);
	matrix.pos.x = state->position.x + OFFSETX;
	matrix.pos.y = state->position.y;
	matrix.pos.z = state->position.z + OFFSETZ;
}

void CRecordDataForChaseHack::SaveOrRetrieveCarPositions(void)
{
	if (Status == 2) {
		Status = 3;
	} else if (Status == 3)	{
		AnimTime += CTimer::ms_fTimeStepNonClipped * 0.02f;
		if (AnimTime > 80.0) {
			AnimTime = 80.0;
		}
		float time = AnimTime * 15.0f;
		for (int i = 0; i < MAX_CHASE_CARS; i++) {
			if (pBaseMemForCar[i] && pChaseCars[i]) {
				if (time < static_cast<float>(MAX_CHASE_FRAMES - 1)) {
					RestoreInfoForCar(pChaseCars[i], &pBaseMemForCar[i][static_cast<int>(time)], false);
					CMatrix matrix;
					RestoreInfoForMatrix(matrix, &pBaseMemForCar[i][static_cast<int>(time) + 1]);

					float timeDifference = time - static_cast<int>(time);

					pChaseCars[i]->GetMatrix().right.x += (matrix.right.x - pChaseCars[i]->GetMatrix().right.x) * timeDifference;
					pChaseCars[i]->GetMatrix().up.x += (matrix.up.x - pChaseCars[i]->GetMatrix().up.x) * timeDifference;
					pChaseCars[i]->GetMatrix().at.x += (matrix.at.x - pChaseCars[i]->GetMatrix().at.x) * timeDifference;

					pChaseCars[i]->GetMatrix().right.y += (matrix.right.y - pChaseCars[i]->GetMatrix().right.y) * timeDifference;
					pChaseCars[i]->GetMatrix().up.y += (matrix.up.y - pChaseCars[i]->GetMatrix().up.y) * timeDifference;
					pChaseCars[i]->GetMatrix().at.y += (matrix.at.y - pChaseCars[i]->GetMatrix().at.y) * timeDifference;

					pChaseCars[i]->GetMatrix().right.z += (matrix.right.z - pChaseCars[i]->GetMatrix().right.z) * timeDifference;
					pChaseCars[i]->GetMatrix().up.z += (matrix.up.z - pChaseCars[i]->GetMatrix().up.z) * timeDifference;
					pChaseCars[i]->GetMatrix().at.z += (matrix.at.z - pChaseCars[i]->GetMatrix().at.z) * timeDifference;

					pChaseCars[i]->GetMatrix().pos.x += (matrix.pos.x - pChaseCars[i]->GetMatrix().pos.x) * timeDifference;
					pChaseCars[i]->GetMatrix().pos.y += (matrix.pos.y - pChaseCars[i]->GetMatrix().pos.y) * timeDifference;
					pChaseCars[i]->GetMatrix().pos.z += (matrix.pos.z - pChaseCars[i]->GetMatrix().pos.z) * timeDifference;

				} else {
					RestoreInfoForCar(pChaseCars[i], &pBaseMemForCar[i][MAX_CHASE_FRAMES - 1], true);
					if (!i) {
						pChaseCars[i]->GetZ() += 0.2;
					}
				}
				pChaseCars[i]->GetMatrix().UpdateRW();
				pChaseCars[i]->UpdateRwFrame();
				pChaseCars[i]->RemoveAndAdd();
			}
		}
	}
}

void CRecordDataForChaseHack::Init(void)
{
	Status = 0;
	for (int i = 0; i < MAX_CHASE_CARS; i++) {
		pChaseCars[i] = 0;
	}
}
