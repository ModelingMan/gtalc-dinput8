#include "CPacManPickupsHack.h"
#include "vcversion.h"
#include "SilentCall.h"
#include <math.h>
#include <fstream>
#include <string>

#define OFFSETX -335.0f
#define OFFSETZ 6.0f

int CPacManPickupsHack::PillsEatenInRace;
bool CPacManPickupsHack::bPMActive;
CPacManPickupHack CPacManPickupsHack::aPMPickups[MAX_PACMAN_PICKUP];
unsigned short scrambleModel;
unsigned short raceModel;

CVector aRacePoints1[MAX_PACMAN_PICKUP] =
{
	{ 913.6222f, -155.13692f, 4.969947f },
	{ 913.924f, -124.129425f, 4.969257f },
	{ 913.279f, -93.52423f, 7.432599f },
	{ 912.6085f, -63.15905f, 7.453359f },
	{ 934.22144f, -42.04912f, 7.451147f },
	{ 958.8809f, -23.863735f, 7.465234f },
	{ 978.5081f, -0.784588f, 5.13515f },
	{ 1009.4175f, -2.104122f, 2.446158f },
	{ 1040.6313f, -2.079383f, 2.293175f },
	{ 1070.7863f, -2.084095f, 2.278979f },
	{ 1100.5773f, -8.468729f, 5.324807f },
	{ 1119.9341f, -31.738031f, 7.191307f },
	{ 1122.1664f, -62.762737f, 7.470391f },
	{ 1122.814f, -93.650566f, 8.55775f },
	{ 1125.8253f, -124.26616f, 9.98033f },
	{ 1153.8727f, -135.4717f, 14.150617f },
	{ 1184.0831f, -135.82845f, 14.973998f },
	{ 1192.0432f, -164.57816f, 19.18627f },
	{ 1192.7761f, -194.28871f, 24.799675f },
	{ 1215.1527f, -215.0714f, 25.74975f },
	{ 1245.79f, -215.39304f, 28.70726f },
	{ 1276.2477f, -216.39485f, 33.71236f },
	{ 1306.5535f, -216.71007f, 39.71147f },
	{ 1335.0244f, -224.59329f, 46.47498f },
	{ 1355.4879f, -246.27664f, 49.93484f },
	{ 1362.6003f, -276.47064f, 49.96265f },
	{ 1363.027f, -307.30847f, 49.969173f },
	{ 1365.343f, -338.0861f, 49.96779f },
	{ 1367.5957f, -368.01105f, 50.092304f },
	{ 1368.2749f, -398.3805f, 50.061268f },
	{ 1366.9034f, -429.98483f, 50.057545f },
	{ 1356.8534f, -459.0926f, 50.035545f },
	{ 1335.5819f, -481.13544f, 47.217903f },
	{ 1306.7552f, -491.07443f, 40.20263f },
	{ 1275.5978f, -491.33194f, 33.969223f },
	{ 1244.702f, -491.4645f, 29.111021f },
	{ 1213.2222f, -491.8754f, 25.771168f },
	{ 1182.773f, -492.19995f, 24.749964f },
	{ 1152.6874f, -491.4222f, 21.70038f },
	{ 1121.5352f, -491.94604f, 20.075182f },
	{ 1090.7056f, -492.6375f, 17.585758f },
	{ 1059.6008f, -491.65762f, 14.848632f },
	{ 1029.113f, -489.6603f, 14.918498f },
	{ 998.2068f, -486.78107f, 14.945688f },
	{ 968.00555f, -484.91266f, 15.001229f },
	{ 937.7494f, -492.09015f, 14.958629f },
	{ 927.1735f, -520.97736f, 14.972308f },
	{ 929.2975f, -552.0864f, 14.978855f },
	{ 950.69525f, -574.4778f, 14.972788f },
	{ 974.02826f, -593.56024f, 14.966445f },
	{ 989.0478f, -620.12854f, 14.951016f },
	{ 1014.16394f, -637.3905f, 14.966736f },
	{ 1017.5961f, -667.3736f, 14.956415f },
	{ 1041.9735f, -685.9439f, 15.003841f },
	{ 1043.3064f, -716.113f, 14.974236f },
	{ 1043.5337f, -746.63855f, 14.96919f },
	{ 1044.142f, -776.93823f, 14.965424f },
	{ 1044.2657f, -807.29395f, 14.97171f },
	{ 1017.0797f, -820.1076f, 14.975431f },
	{ 986.23865f, -820.37103f, 14.972883f },
	{ 956.10065f, -820.2329f, 14.981133f },
	{ 925.86914f, -820.1905f, 14.976553f },
	{ 897.697f, -831.08734f, 14.962709f },
	{ 868.06586f, -835.9924f, 14.970685f },
	{ 836.93054f, -836.8439f, 14.965049f },
	{ 811.63586f, -853.7915f, 15.067576f },
	{ 811.46344f, -884.2737f, 12.247812f },
	{ 811.6065f, -914.7096f, 9.239375f },
	{ 811.10425f, -945.1627f, 5.817255f },
	{ 816.54584f, -975.6459f, 4.998558f },
	{ 828.2951f, -1003.3685f, 5.047117f },
	{ 852.2884f, -1021.59625f, 4.937103f },
	{ 882.5007f, -1025.4459f, 5.14077f },
	{ 912.8482f, -1026.7874f, 8.341545f },
	{ 943.68274f, -1026.6914f, 11.341879f },
	{ 974.4129f, -1027.3682f, 14.410345f },
	{ 1004.1079f, -1036.0778f, 14.92961f },
	{ 1030.1144f, -1051.1224f, 14.850387f },
	{ 1058.7585f, -1060.342f, 14.821624f },
	{ 1087.7797f, -1068.3263f, 14.800561f },
	{ 1099.8807f, -1095.656f, 11.877907f },
	{ 1130.0005f, -1101.994f, 11.853914f },
	{ 1160.3809f, -1101.6355f, 11.854824f },
	{ 1191.8524f, -1102.1577f, 11.853843f },
	{ 1223.3307f, -1102.7448f, 11.852233f },
	{ 1253.564f, -1098.1045f, 11.853944f },
	{ 1262.0203f, -1069.1785f, 14.8147f },
	{ 1290.9998f, -1059.1882f, 14.816016f },
	{ 1316.246f, -1041.0635f, 14.81109f },
	{ 1331.7539f, -1013.83496f, 14.81207f },
	{ 1334.0579f, -983.554f, 14.827253f },
	{ 1323.2429f, -954.23083f, 14.954678f },
	{ 1302.7495f, -932.21216f, 14.962917f },
	{ 1317.418f, -905.89325f, 14.967506f },
	{ 1337.9503f, -883.5025f, 14.969675f },
	{ 1352.6929f, -855.96954f, 14.967854f },
	{ 1357.2388f, -826.2697f, 14.97295f },
	{ 1384.8668f, -812.4769f, 12.907736f },
	{ 1410.8983f, -795.39056f, 12.052228f },
	{ 1433.901f, -775.5581f, 11.96265f },
	{ 1443.8615f, -746.9251f, 11.976114f },
	{ 1457.7015f, -720.00903f, 11.971177f },
	{ 1481.5685f, -701.30237f, 11.977908f },
	{ 1511.4004f, -696.83295f, 11.972709f },
	{ 1542.1796f, -695.61676f, 11.970441f },
	{ 1570.3301f, -684.6239f, 11.969202f },
	{ 0.0f, 0.0f, 0.0f }
};

bool CPacManPickupsHack::initialise()
{
	InjectHook(0x004A4ED8, &CPacManPickupsHack::Init); // CGame::Initialise
	InjectHook(0x004A4967, &CPacManPickupsHack::Init); // CGame::ReInitGameObjectVariables
	InjectHook(0x004A45D7, &CPacManPickupsHack::Update); // CGame::Process
	InjectHook(0x004A6547, &CPacManPickupsHack::Render); // RenderEffects
	return true;
}

void CPacManPickupsHack::Init(void)
{
	for (int i = 0; i < MAX_PACMAN_PICKUP; i++) {
		aPMPickups[i].state = 0;
		aPMPickups[i].object = 0;
	}
	bPMActive = false;
	PillsEatenInRace = 0;

	// get optional data for pickups
	// create pacman.dat and populate it with two custom models and up to 255 coordinate points
	scrambleModel = VCGlobals::MI_LIGHTBEAM;
	raceModel = VCGlobals::MI_LITTLEHA_POLICE;
	std::ifstream fileName("pacman.dat");
	if (fileName.is_open()) {
		std::string line;
		if (std::getline(fileName, line)) sscanf_s(line.c_str(), "%d", &scrambleModel);
		if (std::getline(fileName, line)) sscanf_s(line.c_str(), "%d", &raceModel);
		int i = 0;
		for (; std::getline(fileName, line) && i < MAX_PACMAN_PICKUP - 1; i++) {
			sscanf_s(line.c_str(), "%f %f %f", &aRacePoints1[i].x, &aRacePoints1[i].y, &aRacePoints1[i].z);
		}
		aRacePoints1[i].x = aRacePoints1[i].y = aRacePoints1[i].z = 0;
		fileName.close();
	}
}

void CPacManPickupsHack::Update(void)
{
	if (bPMActive) {
		for (int i = 0; i < MAX_PACMAN_PICKUP; i++) {
			if (aPMPickups[i].state) {
				aPMPickups[i].Update();
			}
		}
	}
}

void CPacManPickupsHack::GeneratePMPickUps(CVector center, float radius, short count)
{
	for (int i = 0; i < count && i < MAX_PACMAN_PICKUP; i++) {
		if (aPMPickups[i].state == 0) {
			CEntity entity;
			CEntity *pentity = &entity;
			CColPoint colpoint;
			CVector pos;
			bool t = false;
			int random;
			float randX, randY;
			int counter = 0;
			unsigned long *baseModelInfo = (unsigned long *)vcversion::AdjustOffset(0x0092D4C8);

			do {
				// prevents infinite loop in invalid areas
				if (counter++ * CTimer::ms_fTimeStep > 5000.0) {
					aPMPickups[i].position.x = 0;
					aPMPickups[i].position.y = 0;
					aPMPickups[i].position.z = 0;
					break;
				}
				random = VCGlobals::rand();
				randX = static_cast<float>((random & 255) - 128);
				randY = static_cast<float>(((random / 256) & 255) - 128);
				pos.x = center.x + randX * radius / 128;
				pos.y = center.y + randY * radius / 128;
				pos.z = 1000.0;
				t = CWorld::ProcessVerticalLine(pos, -1000.0, colpoint, pentity, true, false, false, false, true, false, 0);
			} while (!t || (pentity->status & 7) != 1 || !(*(unsigned short *)(baseModelInfo[pentity->modelIndex] + 0x42) & 4));

			aPMPickups[i].state = 1;
			aPMPickups[i].position.x = colpoint.point.x;
			aPMPickups[i].position.y = colpoint.point.y;
			aPMPickups[i].position.z = colpoint.point.z + 0.7f;

			auto allocateObject = (CObject *(__cdecl *)(unsigned int))vcversion::AdjustOffset(0x004E4070);
			CObject *object = allocateObject(0x194);
			if (object) {
				auto createObject = (CObject *(__thiscall *)(CObject *, int, bool))vcversion::AdjustOffset(0x004E41B0);
				object = createObject(object, scrambleModel, true);
			}
			if (object) {
				object->field_16C = 2;
				object->GetMatrix().SetRotate(0.0, 0.0, -1.5707964f);
				object->GetPos() = aPMPickups[i].position;
				object->GetMatrix().UpdateRW();
				object->UpdateRwFrame();
				object->field_11A &= 0xFD;
				object->field_052 = (object->field_052 & 0xFD) | 2;
				object->field_051 &= 0xFE;
				object->field_16D &= 0xFE;
				CWorld::Add(object);
				aPMPickups[i].object = object;
			}

		}
	}
	bPMActive = true;
}

void CPacManPickupsHack::GeneratePMPickUpsForRace(void)
{
	for (int i = 0; i < MAX_PACMAN_PICKUP; i++) {
		if (aRacePoints1[i].x == 0 &&
			aRacePoints1[i].y == 0 &&
			aRacePoints1[i].z == 0) {
			break;
		}
		if (aPMPickups[i].state == 0) {
			aPMPickups[i].state = 2;
			aPMPickups[i].position.x = aRacePoints1[i].x + OFFSETX;
			aPMPickups[i].position.y = aRacePoints1[i].y;
			aPMPickups[i].position.z = aRacePoints1[i].z + OFFSETZ;
			auto allocateObject = (CObject *(__cdecl *)(unsigned int))vcversion::AdjustOffset(0x004E4070);
			CObject *object = allocateObject(0x194);
			if (object) {
				auto createObject = (CObject *(__thiscall *)(CObject *, int, bool))vcversion::AdjustOffset(0x004E41B0);
				object = createObject(object, raceModel, true);
			}
			if (object) {
				object->field_16C = 2;
				object->GetMatrix().SetRotate(0.0, 0.0, -1.5707964f);
				object->GetPos() = aPMPickups[i].position;
				object->GetMatrix().UpdateRW();
				object->UpdateRwFrame();
				object->field_11A &= 0xFD;
				object->field_052 = (object->field_052 & 0xFD) | 2;
				object->field_051 &= 0xFE;
				object->field_16D &= 0xFE;
				CWorld::Add(object);
				aPMPickups[i].object = object;
			}
		}
	}
	bPMActive = true;
}

void CPacManPickupsHack::GenerateOnePMPickUp(CVector pos)
{
	bPMActive = true;
	aPMPickups[0].state = 2;
	aPMPickups[0].position.x = pos.x;
	aPMPickups[0].position.y = pos.y;
	aPMPickups[0].position.z = pos.z;
}

void CPacManPickupsHack::Render(void)
{
	if (bPMActive) {
		RwRenderStateSet(8, 0);
		RwRenderStateSet(12, 1);
		RwRenderStateSet(10, 2);
		RwRenderStateSet(11, 2);
		RwRenderStateSet(1, (int)**(void ***)vcversion::AdjustOffset(0x00695550));
		for (int i = 0; i < MAX_PACMAN_PICKUP; i++) {
			if (aPMPickups[i].state) {
				RwV3d pickup;
				pickup.x = aPMPickups[i].position.x;
				pickup.y = aPMPickups[i].position.y;
				pickup.z = aPMPickups[i].position.z;
				RwV3d pos;
				float width;
				float height;
				if (CSprite::CalcScreenCoors(pickup, &pos, &width, &height, true) && pos.z < 100.0) {
					float time = ((float)CTimer::m_snTimeInMilliseconds) * 6.1359233e-3f;
					if (aPMPickups[i].object) {
						CMatrix *matrix = &aPMPickups[i].object->GetMatrix();
						matrix->SetRotateZOnly(time);
						matrix->UpdateRW();
						aPMPickups[i].object->UpdateRwFrame();
					}
					CSprite::RenderOneXLUSprite(pos.x, pos.y, pos.z, width * 0.8f * sin(time), height * 0.8f, 100, 50, 5, 255, 1.0f / pos.z, 255);
				}
			}
		}
		//RwRenderStateSet(10, 5);
		//RwRenderStateSet(11, 6);
		//RwRenderStateSet(8, 1);
		//RwRenderStateSet(12, 0);
	}
}

void CPacManPickupHack::Update(void)
{
	CVehicle *vehicle = VCGlobals::FindPlayerVehicle();
	if (!vehicle ||
		(pow(vehicle->GetY() - position.y, 2) + pow(vehicle->GetX() - position.x, 2) > 100.0) ||
		!vehicle->IsSphereTouchingVehicle(position.x, position.y, position.z, 1.5)) {
		return;
	}
	if (state == 1) {
		vehicle->powerPillsCarried++;
		vehicle->forceX *= 0.65f;
		vehicle->forceY *= 0.65f;
		vehicle->forceZ *= 0.65f;
		float multiplier = (250.0f + vehicle->mass) / vehicle->mass;
		vehicle->mass *= multiplier;
		vehicle->turnResistance *= multiplier;
		vehicle->accelerationResistance *= multiplier;
		VCGlobals::FindPlayerPed()->wanted->counter += 10;
		VCGlobals::FindPlayerPed()->wanted->UpdateWantedLevel();
	} else if (state == 2) {
		CPacManPickupsHack::PillsEatenInRace++;
	}
	VCGlobals::DMAudio.cDMAudio::PlayFrontEndSound(0x54, 0);
	state = 0;
	if (object) {
		CWorld::Remove(object);
		auto Destroy = (void(__thiscall *)(CObject *, int))*(unsigned long *)(object->vtbl + 8);
		Destroy(object, 1);
		object = 0;
	}
}

void CPacManPickupsHack::StartPacManRace(int)
{
	GeneratePMPickUpsForRace();
	PillsEatenInRace = 0;
}

int CPacManPickupsHack::QueryPowerPillsEatenInRace(void)
{
	return PillsEatenInRace;
}

void CPacManPickupsHack::ResetPowerPillsEatenInRace(void)
{
	PillsEatenInRace = 0;
}

void CPacManPickupsHack::CleanUpPacManStuff(void)
{
	bPMActive = 0;
	for (int i = 0; i < MAX_PACMAN_PICKUP; i++) {
		if (aPMPickups[i].state && aPMPickups[i].object) {
			CWorld::Remove(aPMPickups[i].object);
			auto Destroy = (void(__thiscall *)(CObject *, int))*(unsigned long *)(aPMPickups[i].object->vtbl + 8);
			Destroy(aPMPickups[i].object, 1);
			aPMPickups[i].object = 0;
		}
		aPMPickups[i].state = 0;
	}
}

void CPacManPickupsHack::StartPacManScramble(CVector center, float radius, short count)
{
	GeneratePMPickUps(center, radius, count);
}

int CPacManPickupsHack::QueryPowerPillsCarriedByPlayer(void)
{
	if (CVehicle *vehicle = VCGlobals::FindPlayerVehicle()) {
		return vehicle->powerPillsCarried;
	}
	return 0;
}

void CPacManPickupsHack::ResetPowerPillsCarriedByPlayer(void)
{
	if (CVehicle *vehicle = VCGlobals::FindPlayerVehicle()) {
		vehicle->powerPillsCarried = 0;
		vehicle->mass /= vehicle->accelerationResistance;
		vehicle->turnResistance /= vehicle->accelerationResistance;
		vehicle->accelerationResistance = 1.0;
	}
}
