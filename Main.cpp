#include "Includes.h"
#include "obfuscate.h"
#include "Tools.h"
#include "fake_dlfcn.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "StrEnc.h"
#include "CN.h"
#include "Spoof.h"
#include "plthook.h"
#include "Items.h"
#include "json.hpp"
#include "KittyMemory/MemoryPatch.h"
using json = nlohmann::json;
//@MPR_MODS_VIP
#include "SDK.hpp"
#include "Color.h"
#include "Icon.h"
#include "Iconcpp.h"
#include "ImguiPP.h"
#include "Menu.h"
#include "Font.h"
#include "fontch.h"
#include "Vector2.hpp"
#include "Vector3.hpp"

using namespace SDK;

#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "base64/base64.h"


bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;

bool show_another_window2 = false;
static bool HideWindow = true;

float density = -1;

json mItemData;

char extra[32];

json items_data;
time_t expiredDate = 0;
std::string g_Token, g_Auth;
bool bValid = false;
bool Bypass = true;

#define ShortEvent_Offset 165 //////
// ======================================================================== //
float FOVSize = 500;
float FOVSizea = 370;
uintptr_t UE4;
uintptr_t anogs;

android_app *g_App = 0;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;

bool HIDEESP = true;

float Skill = 4;
float Sland = 15000;
float sinstanthit = 100000;
bool bypass = false;


static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;


time_t rng = 0;
static std::string ModName = "Welcome bro, Please Login";
static std::string EXP = "Key Expiry Working After Login Key";



#define IM_PI                   3.14159265358979323846f
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / IM_PI) )
#define DEG2RAD( x ) ( (float)(x) * (float)(IM_PI / 180.f) )
#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(localController, w, true, s)

//𝐉𝐎𝐈𝐍 𝐅𝐎𝐑 𝐁𝐆𝐌𝐢 𝟐. 𝟗 𝐒𝐑𝐂 - @Src_Leeakers
//𝐓𝐆 - @Src_Leeakers
// ======================================================================== //

enum EAimTarget {
    Head = 0,
    Chest = 1
};

enum EAimBy {
    FOV = 0,
    Distance = 1
};

enum EAimTrigger {
    None = 0,
    Shooting = 1,
    Scoping = 2,
    Both = 3,
    Any = 4
};
enum EAimMode {
    AimBullet = 0,
    Pbullet = 1,
    AimBot = 2
};

std::map<int, bool> Items;


struct sConfig {
	bool Bypass;
	float Line;
	float Skeleton;
    float Loot;
	bool V60FPS;
    struct sPlayerESP {
        bool Line;
        bool Box;
        bool Health;
        bool Skeleton;
        bool Name;
		bool Alert;
        bool Distance;
        bool TeamID;
        bool VehicleDist;
		bool VehicleFuel;
		bool Vehicle;
        bool NoBot;
        bool Grenade;
        bool LootBox;
		bool WideView;
		bool spawn;
		bool V60FPS;
		bool Awarnees;
		bool Armor;
		bool iterm;
		bool Offline;
		bool RadarMap;
		bool Antiban;
    };

    sPlayerESP PlayerESP{0};

    struct sAimMenu {
        bool Enable;
        bool AimBot;
		bool MagicBullet;
		EAimMode Mode;
       // EAimBy AimBy;
	    bool AimBy;
        EAimTarget Target;
        EAimTrigger Trigger;
		EAimTrigger targetsy;
        bool IgnoreKnocked;
		
        bool IgnoreBot;
        bool VisCheck;
		bool RecoilComparison;
		float Cross;
		bool FOV;
		float Meter;
		
		float Crosss;
		float Recc;
    };
    sAimMenu BulletTracking{0};
    sAimMenu AimBot{0};

    struct sHighRisk {
        bool Shake;
        bool Recoil;
        bool Instant;
        bool SmallCross;
        bool kill;
      		bool HitEffect;
    };
    sHighRisk HighRisk{0};

    struct sOTHER {
        bool EXP;
        bool BLOCK_SPECTATE;
        bool FPS;
        bool HIDEESP;
        bool Bypass; 
        bool HiTLERYT;
       bool spawn;
    };
    sOTHER OTHER{0};
	
	struct sColorsESP {
        float *Line;
        float *Box;
        float *Name;
        float *Distance;
		float *Fov;
        float *Skeleton;
        float *SkeletonVisible;
		float *Vehicle;
        
    };
    sColorsESP ColorsESP{0};
};
sConfig Config{0};

#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};
//𝐉𝐎𝐈𝐍 𝐅𝐎𝐑 𝐁𝐆𝐌𝐢 𝟐. 𝟗 𝐒𝐑𝐂 - @Src_Leeakers
//𝐓𝐆 - @Src_Leeakers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
#define GEngine_Offset 0xc5bde40
#define GNames_Offset 0x70e285c
#define GUObject_Offset 0xc3c7270
#define GNativeAndroidApp_Offset 0xbf2cfc8

#define Actors_Offset 0xA0
//#define ShortEvent_Offset 165
#define GetActorArray 0x8abf258
#define CanvasMap_Offsets 0xc005658

static UEngine *GEngine = 0;
UWorld *GetWorld() {
    while (!GEngine) {
        GEngine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1"); // Auto 
        sleep(1);
    }
    if (GEngine) {
        auto ViewPort = GEngine->GameViewport;

        if (ViewPort) {
   //return {};
            return ViewPort->World;
        }
    }
    return 0;
}


TNameEntryArray *GetGNames() {
    return ((TNameEntryArray *(*)()) (UE4 + GNames_Offset))();
}

std::vector<AActor *> getActors() {
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();

    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
        return std::vector<AActor *>();

    auto Actors = *(TArray<AActor *> *)((uintptr_t) PersistentLevel + Actors_Offset);

    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.Num(); i++) {
        auto Actor = Actors[i];
        if (Actor) {
            actors.push_back(Actor);
        }
    }
    return actors;
}
struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

bool isObjectInvalid(UObject *obj) {
    if (!Tools::IsPtrValid(obj)) {
        return true;
    }

    if (!Tools::IsPtrValid(obj->ClassPrivate)) {
        return true;
    }

    if (obj->InternalIndex <= 0) {
        return true;
    }

    if (obj->NamePrivate.ComparisonIndex <= 0) {
        return true;
    }

    if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4) {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end; }) ||
        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj->ClassPrivate) >= region.start && ((uintptr_t) obj->ClassPrivate) <= region.end; })) {
        return true;
    }

    return false;
}
std::string getObjectPath(UObject *Object) {
    std::string s;
    for (auto super = Object->ClassPrivate; super; super = (UClass *) super->SuperStruct) {
        if (!s.empty())
            s += ".";
        s += super->NamePrivate.GetName();
    }
    return s;
}
int32_t ToColor(float *col) {
    return ImGui::ColorConvertFloat4ToU32(*(ImVec4 *) (col));
}

FRotator ToRotator(FVector local, FVector target) {
    FVector rotation = UKismetMathLibrary::Subtract_VectorVector(local, target);

    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;

    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;

    return newViewAngle;
}
static uintptr_t gameoverlay_return_address = 0;



void VectorAnglesRadar(Vector3 & forward, FVector & angles) {
 if (forward.X == 0.f && forward.Y == 0.f) {
  angles.X = forward.Z > 0.f ? -90.f : 90.f;
  angles.Y = 0.f;
 } else {
  angles.X = RAD2DEG(atan2(-forward.Z, forward.Magnitude(forward)));
  angles.Y = RAD2DEG(atan2(forward.Y, forward.X));
 }
 angles.Z = 0.f;
}

void RotateTriangle(std::array<Vector3, 3> & points, float rotation) {
 const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
 for (auto & point : points) {
  point = point - points_center;
  const auto temp_x = point.X;
  const auto temp_y = point.Y;
  const auto theta = DEG2RAD(rotation);
  const auto c = cosf(theta);
  const auto s = sinf(theta);
  point.X = temp_x * c - temp_y * s;
  point.Y = temp_x * s + temp_y * c;
  point = point + points_center;
 }
}

int isOutsideSafezone(FVector2D pos, FVector2D screen) {
	FVector2D mSafezoneTopLeft(screen.X * 0.04f, screen.Y * 0.04f);
	FVector2D mSafezoneBottomRight(screen.X * 0.96f, screen.Y * 0.96f);
	int result = 0;
	if (pos.Y < mSafezoneTopLeft.Y) {
		result |= 1;
	}
	if (pos.X > mSafezoneBottomRight.X) {
		result |= 2;
	}
	if (pos.Y > mSafezoneBottomRight.Y) {
		result |= 4;
	}
	if (pos.X < mSafezoneTopLeft.X) {
		result |= 8;
	}
	return result;
}

 bool flag = false;
 

bool isInsideFOVs(int x, int y) {
    if (!FOVSize)
        return true;

    int circle_x = glWidth / 2;
    int circle_y = glHeight / 2;
    int rad = FOVSizea;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

auto GetTargetForAimBot() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();

    auto GWorld = GetWorld();
    if (GWorld) {
        ULevel *PersistentLevel = GWorld->PersistentLevel;
        if (PersistentLevel) {
            TArray<AActor *> Actors = *(TArray<AActor *> *) ((uintptr_t) PersistentLevel +
                                                             Actors_Offset);

            auto localPlayer = g_LocalPlayer;
            auto localController = g_LocalController;

            if (localPlayer) {
                for (int i = 0; i < Actors.Num(); i++) {
                    auto Actor = Actors[i];
                    if (isObjectInvalid(Actor))
                        continue;

                    if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                        auto Player = (ASTExtraPlayerCharacter *) Actor;

                        if (Player->PlayerKey == localPlayer->PlayerKey)
                            continue;

                        if (Player->TeamID == localPlayer->TeamID)
                            continue;

                        if (Player->bDead)
                            continue;

                        if (Config.AimBot.IgnoreKnocked) {
                            if (Player->Health == 0.0f)
                                continue;
                        }

                        if (Config.AimBot.VisCheck) {
                            if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                                continue;
                        }

                        if (Config.AimBot.IgnoreBot) {
                            if (Player->bIsAI)
                                continue;
                        }

                        auto Root = Player->GetBonePos("Root", {});
                        auto Head = Player->GetBonePos("Head", {});

                        FVector2D RootSc, HeadSc;
                        if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                            float height = abs(HeadSc.Y - RootSc.Y);
                            float width = height * 0.65f;

                            FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2),
                                                   0};
                            if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) &&
                                (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                                FVector2D v2Middle = FVector2D((float) (glWidth / 2),
                                                               (float) (glHeight / 2));
                                FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                                float dist = FVector2D::Distance(v2Middle, v2Loc);

                                if (dist < max) {
                                    max = dist;
                                    result = Player;
                                }
                            }
                        }
                    }
                }
            }

            return result;
        }
    }
}



auto GetTargetForBT() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();

    auto GWorld = GetWorld();
    if (GWorld) {
        ULevel *PersistentLevel = GWorld->PersistentLevel;
        if (PersistentLevel) {
            TArray<AActor *> Actors = *(TArray<AActor *> *) ((uintptr_t) PersistentLevel +
                                                             Actors_Offset);


            auto localPlayer = g_LocalPlayer;
            auto localController = g_LocalController;

            if (localPlayer) {
                for (int i = 0; i < Actors.Num(); i++) {
                    auto Actor = Actors[i];
                    if (isObjectInvalid(Actor))
                        continue;

                    if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                        auto Player = (ASTExtraPlayerCharacter *) Actor;

                        if (Player->PlayerKey == localPlayer->PlayerKey)
                            continue;

                        if (Player->TeamID == localPlayer->TeamID)
                            continue;

                        if (Player->bDead)
                            continue;

                        if (Config.BulletTracking.IgnoreKnocked) {
                            if (Player->Health == 0.0f)
                                continue;
                        }

                        if (Config.BulletTracking.VisCheck) {
                            if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                                continue;
                        }

                        if (Config.BulletTracking.IgnoreBot) {
                            if (Player->bEnsure)
                                continue;
                        }

                        auto Root = Player->GetBonePos("Root", {});
                        auto Head = Player->GetBonePos("Head", {});

                        FVector2D RootSc, HeadSc;
                        if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                            float height = abs(HeadSc.Y - RootSc.Y);
                            float width = height * 0.65f;

                            FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2),
                                                   0};
                            if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) &&
                                (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                                FVector2D v2Middle = FVector2D((float) (glWidth / 2),
                                                               (float) (glHeight / 2));
                                FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                                float dist = FVector2D::Distance(v2Middle, v2Loc);

                                if (dist < max) {
                                    max = dist;
                                    result = Player;
                                }
                            }
                        }
                    }
                }
            }

            return result;
        }
    }
}


auto GetTargetByPussy() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
     auto Actors = getActors();
     
    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;
    FVector ViewPosY{0, 0, 0};
    if (localPlayer) {                   
       ViewPosY = localPlayer->GetBonePos("Head", {});
       ViewPosY.Z += 10.f;
    }  
    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                auto Player = (ASTExtraPlayerCharacter *) Actor;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

               if (Config.BulletTracking.IgnoreKnocked) {
                    if (Player->Health == 0.0f)
                        continue;
                }
                  
                 
                    if (!localController->LineOfSightTo(Player, ViewPosY, true))
                              continue;
      
                        float dist = g_LocalPlayer->GetDistanceTo(Player);
                             if (dist < max) {
                                 max = dist;
                              result = Player;
                        }
                    }
                }
            }
            
    return result;
}


auto GetTargetByCrossDist() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();

    auto GWorld = GetWorld();
    if (GWorld) {
        ULevel *PersistentLevel = GWorld->PersistentLevel;
        if (PersistentLevel) {
            TArray<AActor *> Actors = *(TArray<AActor *> *) ((uintptr_t) PersistentLevel + Actors_Offset);

            auto localPlayer = g_LocalPlayer;
            auto localController = g_LocalController;

            if (localPlayer) {
                for (int i = 0; i < Actors.Num(); i++) {
                    auto Actor = Actors[i];
                    if (isObjectInvalid(Actor))
                        continue;

                    if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                        auto Player = (ASTExtraPlayerCharacter *) Actor;

                        if (Player->PlayerKey == localPlayer->PlayerKey)
                            continue;


                        if (Player->bDead)
                            continue;


                        if (Config.BulletTracking.VisCheck) {
                            if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                                continue;
                        }

                        auto Root = Player->GetBonePos("Root", {});
                        auto Head = Player->GetBonePos("Head", {});

                        FVector2D RootSc, HeadSc;
                        if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                            float height = abs(HeadSc.Y - RootSc.Y);
                            float width = height * 0.65f;

                            FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                            if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                                FVector2D v2Middle = FVector2D((float) (glWidth / 2), (float) (glHeight / 2));
                                FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                                float dist = FVector2D::Distance(v2Middle, v2Loc);

                                if (dist < max) {
                                    max = dist;
                                    result = Player;
                                }
                            }   
						
                        }
                    }
                }
            }
        }
    }

    return result;
}




const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) {
    switch (Vehicle->VehicleShapeType) {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return ICON_FA_BICYCLE"BAJAJ PLATINA";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleSh
