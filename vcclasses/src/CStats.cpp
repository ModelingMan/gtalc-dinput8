#include "vcclasses.h"
#include "vcversion.h"

float *CStats::FavoriteRadioStationList = reinterpret_cast<float *>(vcversion::AdjustOffset(0x00862460));
int &CStats::TyresPopped = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0094DB58));
int *CStats::PedsKilledOfThisType = reinterpret_cast<int *>(vcversion::AdjustOffset(0x0094DB64));
int &CStats::BoatsExploded = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974B04));
float &CStats::ShootingRank = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974B08));
float &CStats::TotalProgressInGame = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974B0C));
int &CStats::BestStuntJump = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974B30));
int &CStats::LongestStoppie = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974B3C));
int &CStats::NumberOfUniqueJumpsFound = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974B48));
int *CStats::FastestTimes = reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974B80));
int &CStats::TotalNumberMissions = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974BF0));
float &CStats::GarbagePickups = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974C00));
float &CStats::DistanceTravelledByGolfCart = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974C04));
int &CStats::NumberKillFrenziesPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974C08));
int &CStats::TotalNumberKillFrenzies = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974C0C));
float &CStats::LoanSharks = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974C28));
int &CStats::HelisDestroyed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009751F0));
int &CStats::IndustrialPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009751F4));
int &CStats::LongestWheelie = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0097530C));
int &CStats::HighestLevelFireMission = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00975310));
int &CStats::TimesDied = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00975320));
int &CStats::RoundsFiredByPlayer = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0097532C));
int &CStats::TimesArrested = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00975330));
float &CStats::IceCreamSold = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00975390));
int &CStats::PeopleKilledByOthers = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009753AC));
int &CStats::PropertyDestroyed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00975404));
int &CStats::TotalNumberOfUniqueJumps = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00978530));
int &CStats::FlightTime = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0097854C));
int &CStats::SeagullsKilled = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0097869C));
float &CStats::LongestWheelieDist = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009786C0));
float &CStats::PizzasDelivered = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00978780));
int &CStats::PeopleKilledByPlayer = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00978794));
int &CStats::KgsOfExplosivesUsed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009787A8));
int &CStats::CriminalsCaught = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009787B4));
int &CStats::MaximumJumpFlips = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009787DC));
int &CStats::SuburbanPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00978A0C));
int &CStats::MaximumJumpSpins = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00978D14));
int &CStats::HighestLevelAmbulanceMission = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00978DB8));
float &CStats::HighestChaseValue = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00978E0C));
int &CStats::DaysPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0097F1F4));
float &CStats::MaximumJumpDistance = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0097F210));
float &CStats::StoresKnockedOff = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0097F898));
int &CStats::CommercialPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B489C));
int &CStats::TimesDrowned = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B48B4));
float &CStats::Longest2WheelDist = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009B48D0));
int &CStats::LivesSavedWithAmbulance = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B5EA8));
int &CStats::WantedStarsAttained = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B5EB8));
int &CStats::WantedStarsEvaded = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B5F30));
float &CStats::LongestStoppieDist = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009B5F44));
float &CStats::DistanceTravelledByHelicopter = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009B6A48));
float &CStats::DistanceTravelledByPlane = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009B6A78));
int &CStats::FiresExtinguished = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B6A84));
int &CStats::BulletsThatHit = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B6CD4));
float &CStats::ProgressMade = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009B6CDC));
int *CStats::HighestScores = reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B6E20));
int &CStats::HeadsPopped = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B6E38));
float &CStats::MaximumJumpHeight = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0CFD8));
int &CStats::PassengersDroppedOffWithTaxi = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D1DC));
int &CStats::SafeHouseVisits = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D228));
float &CStats::DistanceTravelledByBike = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0D2D8));
int &CStats::BloodRingTime = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D2E0));
float &CStats::DistanceTravelledByBoat = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0D384));
int &CStats::CarsExploded = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D388));
float &CStats::TopShootingRangeScore = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0D8A4));
float &CStats::DistanceTravelledOnFoot = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0D9B4));
int &CStats::MoneyMadeWithTaxi = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D9C8));
float &CStats::MovieStunts = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0FC8C));
int &CStats::Sprayings = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0FC94));
int &CStats::NoMoreHurricanes = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0FCAC));
int &CStats::Longest2Wheel = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0FCF8));
float &CStats::DistanceTravelledByCar = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0FCFC));
int &CStats::MissionsGiven = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A1023C));
float &CStats::AutoPaintingBudget = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A10298));
float &CStats::Assassinations = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A10918));

static unsigned long g_BuildStatLine = vcversion::AdjustOffset(0x004CAE8F);
static unsigned long g_AnotherKillFrenzyPassed = vcversion::AdjustOffset(0x004CDBA7);
static unsigned long g_FindChaseString = vcversion::AdjustOffset(0x004CDBAE);

__declspec(naked) void CStats::BuildStatLine(char *, void *, int, void *, int)
{
	__asm jmp g_BuildStatLine;
}

__declspec(naked) void CStats::AnotherKillFrenzyPassed(void)
{
	__asm jmp g_AnotherKillFrenzyPassed;
}

__declspec(naked) wchar_t *CStats::FindChaseString(float)
{
	__asm jmp g_FindChaseString;
}
