#include "vcversion.h"

static unsigned long g_RpAnimBlendClumpGetFirstAssociation = vcversion::AdjustOffset(0x00402E20);
static unsigned long g_RsMouseSetPos = vcversion::AdjustOffset(0x006030C0);

extern "C" __declspec(naked) unsigned long RpAnimBlendClumpGetFirstAssociation()
{
	__asm jmp g_RpAnimBlendClumpGetFirstAssociation;
}

extern "C" __declspec(naked) void RsMouseSetPos()
{
	__asm jmp g_RsMouseSetPos;
}

//########################################################################
//# Below added by ModelingMan 14/02/18
//########################################################################

static unsigned long g_RpAtomicClone = vcversion::AdjustOffset(0x00640FD0);
static unsigned long g_RpAtomicCreate = vcversion::AdjustOffset(0x00640DE0);
static unsigned long g_RpAtomicDestroy = vcversion::AdjustOffset(0x00640F50);
static unsigned long g_RpAtomicGetWorldBoundingSphere = vcversion::AdjustOffset(0x00640710);
static unsigned long g_RpAtomicRegisterPlugin = vcversion::AdjustOffset(0x006422D0);
static unsigned long g_RpAtomicRegisterPluginStream = vcversion::AdjustOffset(0x00642330);
static unsigned long g_RpAtomicSetDefaultPipeline = vcversion::AdjustOffset(0x006734A0);
static unsigned long g_RpAtomicSetFrame = vcversion::AdjustOffset(0x006423C0);
static unsigned long g_RpAtomicSetGeometry = vcversion::AdjustOffset(0x00640ED0);
static unsigned long g_RpAtomicSetStreamAlwaysCallBack = vcversion::AdjustOffset(0x00642360);
static unsigned long g_RpAtomicSetStreamRightsCallBack = vcversion::AdjustOffset(0x00642380);
static unsigned long g_RpClumpAddAtomic = vcversion::AdjustOffset(0x006415B0);
static unsigned long g_RpClumpClone = vcversion::AdjustOffset(0x006410E0);
static unsigned long g_RpClumpCreate = vcversion::AdjustOffset(0x006413C0);
static unsigned long g_RpClumpDestroy = vcversion::AdjustOffset(0x00641430);
static unsigned long g_RpClumpForAllAtomics = vcversion::AdjustOffset(0x00640D00);
static unsigned long g_RpClumpForAllCameras = vcversion::AdjustOffset(0x00640D40);
static unsigned long g_RpClumpForAllLights = vcversion::AdjustOffset(0x00640D90);
static unsigned long g_RpClumpGetNumAtomics = vcversion::AdjustOffset(0x00640C80);
static unsigned long g_RpClumpRegisterPlugin = vcversion::AdjustOffset(0x00642300);
static unsigned long g_RpClumpRemoveAtomic = vcversion::AdjustOffset(0x006415E0);
static unsigned long g_RpClumpRender = vcversion::AdjustOffset(0x00640CB0);
static unsigned long g_RpClumpStreamRead = vcversion::AdjustOffset(0x00641A10);
static unsigned long g_RpGeometryAddMorphTarget = vcversion::AdjustOffset(0x0064CBF0);
static unsigned long g_RpGeometryForAllMaterials = vcversion::AdjustOffset(0x0064CC90);
static unsigned long g_RpGeometryLock = vcversion::AdjustOffset(0x0064CCD0);
static unsigned long g_RpGeometryRegisterPlugin = vcversion::AdjustOffset(0x0064D080);
static unsigned long g_RpGeometryRegisterPluginStream = vcversion::AdjustOffset(0x0064D0B0);
static unsigned long g_RpGeometryTriangleSetMaterial = vcversion::AdjustOffset(0x0064CC30);
static unsigned long g_RpGeometryTriangleSetVertexIndices = vcversion::AdjustOffset(0x0064CC00);
static unsigned long g_RpHAnimAnimationCreate = vcversion::AdjustOffset(0x0064D970);
static unsigned long g_RtAnimAnimationCreate = vcversion::AdjustOffset(0x0064D970);
static unsigned long g_RpHAnimAnimationDestroy = vcversion::AdjustOffset(0x0064DA20);
static unsigned long g_RpHAnimHierarchyCreate = vcversion::AdjustOffset(0x00646280);
static unsigned long g_RpHAnimHierarchyGetMatrixArray = vcversion::AdjustOffset(0x00646370);
static unsigned long g_RpHAnimHierarchyUpdateMatrices = vcversion::AdjustOffset(0x006463C0);
static unsigned long g_RpHAnimIDGetIndex = vcversion::AdjustOffset(0x00646390);
static unsigned long g_RpHAnimInterpolatorSetCurrentAnim = vcversion::AdjustOffset(0x0064DAD0);
static unsigned long g_RtAnimInterpolatorSetCurrentAnim = vcversion::AdjustOffset(0x0064DAD0);
static unsigned long g_RpHAnimPluginAttach = vcversion::AdjustOffset(0x00645C80);
static unsigned long g_RpHAnimRegisterInterpolationScheme = vcversion::AdjustOffset(0x0064D8D0);
static unsigned long g_RpHAnimStdKeyFrameAdd = vcversion::AdjustOffset(0x0066B440);
static unsigned long g_RpHAnimStdKeyFrameBlend = vcversion::AdjustOffset(0x0066ADE0);
static unsigned long g_RpHAnimStdKeyFrameInterpolate = vcversion::AdjustOffset(0x0066A9C0);
static unsigned long g_RpHAnimStdKeyFrameMulRecip = vcversion::AdjustOffset(0x0066B2E0);
static unsigned long g_RpHAnimStdKeyFrameStreamGetSize = vcversion::AdjustOffset(0x0066B2D0);
static unsigned long g_RpHAnimStdKeyFrameStreamRead = vcversion::AdjustOffset(0x0066B1E0);
static unsigned long g_RpHAnimStdKeyFrameStreamWrite = vcversion::AdjustOffset(0x0066B260);
static unsigned long g_RpHAnimStdKeyFrameToMatrix = vcversion::AdjustOffset(0x0066A8A0);
static unsigned long g_RpLightCreate = vcversion::AdjustOffset(0x00660B20);
static unsigned long g_RpLightGetConeAngle = vcversion::AdjustOffset(0x006606D0);
static unsigned long g_RpLightSetColor = vcversion::AdjustOffset(0x00660680);
static unsigned long g_RpLightSetRadius = vcversion::AdjustOffset(0x00660660);
static unsigned long g_RpMatFXAtomicEnableEffects = vcversion::AdjustOffset(0x00657020);
static unsigned long g_RpMatFXMaterialGetEffects = vcversion::AdjustOffset(0x006572F0);
static unsigned long g_RpMatFXMaterialGetEnvMapCoefficient = vcversion::AdjustOffset(0x006575A0);
static unsigned long g_RpMatFXMaterialSetBumpMapTexture = vcversion::AdjustOffset(0x00657310);
static unsigned long g_RpMatFXMaterialSetDualBlendModes = vcversion::AdjustOffset(0x006575F0);
static unsigned long g_RpMatFXMaterialSetEffects = vcversion::AdjustOffset(0x00657050);
static unsigned long g_RpMatFXMaterialSetEnvMapCoefficient = vcversion::AdjustOffset(0x00657530);
static unsigned long g_RpMatFXMaterialSetEnvMapFrame = vcversion::AdjustOffset(0x006574D0);
static unsigned long g_RpMatFXMaterialSetupEnvMap = vcversion::AdjustOffset(0x00657180);
static unsigned long g_RpMatFXPluginAttach = vcversion::AdjustOffset(0x00655EB0);
static unsigned long g_RpMaterialCreate = vcversion::AdjustOffset(0x006557B0);
static unsigned long g_RpMaterialDestroy = vcversion::AdjustOffset(0x00655830);
static unsigned long g_RpMaterialRegisterPlugin = vcversion::AdjustOffset(0x006558C0);
static unsigned long g_RpMaterialRegisterPluginStream = vcversion::AdjustOffset(0x006558F0);
static unsigned long g_RpMaterialSetTexture = vcversion::AdjustOffset(0x00655890);
static unsigned long g_RpMorphTargetCalcBoundingSphere = vcversion::AdjustOffset(0x0064C920);
static unsigned long g_RpSkinAtomicGetHAnimHierarchy = vcversion::AdjustOffset(0x00649950);
static unsigned long g_RpSkinAtomicSetHAnimHierarchy = vcversion::AdjustOffset(0x00649930);
static unsigned long g_RpSkinGeometryGetSkin = vcversion::AdjustOffset(0x00649960);
static unsigned long g_RpSkinGeometrySetSkin = vcversion::AdjustOffset(0x00649970);
static unsigned long g_RpSkinGetVertexBoneWeights = vcversion::AdjustOffset(0x006499E0);
static unsigned long g_RpSkinPluginAttach = vcversion::AdjustOffset(0x00648C50);
static unsigned long g_RpWorldAddCamera = vcversion::AdjustOffset(0x00654460);
static unsigned long g_RpWorldAddClump = vcversion::AdjustOffset(0x00654500);
static unsigned long g_RpWorldAddLight = vcversion::AdjustOffset(0x00654680);
static unsigned long g_RpWorldCreate = vcversion::AdjustOffset(0x00654C90);
static unsigned long g_RpWorldDestroy = vcversion::AdjustOffset(0x00654950);
static unsigned long g_RpWorldPluginAttach = vcversion::AdjustOffset(0x00655070);
static unsigned long g_RpWorldRemoveCamera = vcversion::AdjustOffset(0x00654490);
static unsigned long g_RpWorldRemoveLight = vcversion::AdjustOffset(0x006546D0);
static unsigned long g_RpWorldSectorGetWorld = vcversion::AdjustOffset(0x006548C0);
static unsigned long g_RpWorldSetDefaultSectorPipeline = vcversion::AdjustOffset(0x00673470);
static unsigned long g_RtBMPImageRead = vcversion::AdjustOffset(0x00657870);
static unsigned long g_RwBBoxCalculate = vcversion::AdjustOffset(0x0066D8B0);
static unsigned long g_RwCameraBeginUpdate = vcversion::AdjustOffset(0x0064A820);
static unsigned long g_RwCameraClear = vcversion::AdjustOffset(0x0064A9D0);
static unsigned long g_RwCameraCreate = vcversion::AdjustOffset(0x0064AB50);
static unsigned long g_RwCameraDestroy = vcversion::AdjustOffset(0x0064AB10);
static unsigned long g_RwCameraEndUpdate = vcversion::AdjustOffset(0x0064A810);
static unsigned long g_RwCameraFrustumTestSphere = vcversion::AdjustOffset(0x0064A960);
static unsigned long g_RwCameraRegisterPlugin = vcversion::AdjustOffset(0x0064AAE0);
static unsigned long g_RwCameraSetFarClipPlane = vcversion::AdjustOffset(0x0064A930);
static unsigned long g_RwCameraSetNearClipPlane = vcversion::AdjustOffset(0x0064A860);
static unsigned long g_RwCameraSetProjection = vcversion::AdjustOffset(0x0064AA30);
static unsigned long g_RwCameraSetViewOffset = vcversion::AdjustOffset(0x0064A830);
static unsigned long g_RwCameraSetViewWindow = vcversion::AdjustOffset(0x0064AAA0);
static unsigned long g_RwCameraShowRaster = vcversion::AdjustOffset(0x0064AA00);
static unsigned long g_RwD3D8CameraAttachWindow = vcversion::AdjustOffset(0x0065DC30);
static unsigned long g_RwD3D8CameraIsBBoxFullyInsideFrustum = vcversion::AdjustOffset(0x00660010);
static unsigned long g_RwD3D8CameraIsSphereFullyInsideFrustum = vcversion::AdjustOffset(0x0065FFB0);
static unsigned long g_RwD3D8CreatePixelShader = vcversion::AdjustOffset(0x0065FE90);
static unsigned long g_RwD3D8DeletePixelShader = vcversion::AdjustOffset(0x0065FF00);
static unsigned long g_RwD3D8DeviceSupportsDXTTexture = vcversion::AdjustOffset(0x0065F1F0);
static unsigned long g_RwD3D8DrawIndexedPrimitive = vcversion::AdjustOffset(0x0065F410);
static unsigned long g_RwD3D8DrawPrimitive = vcversion::AdjustOffset(0x0065F4A0);
static unsigned long g_RwD3D8DynamicVertexBufferCreate = vcversion::AdjustOffset(0x0065FD70);
static unsigned long g_RwD3D8DynamicVertexBufferDestroy = vcversion::AdjustOffset(0x0065FE60);
static unsigned long g_RwD3D8DynamicVertexBufferLock = vcversion::AdjustOffset(0x006600A0);
static unsigned long g_RwD3D8DynamicVertexBufferUnlock = vcversion::AdjustOffset(0x00660220);
static unsigned long g_RwD3D8EnableLight = vcversion::AdjustOffset(0x0065FC10);
static unsigned long g_RwD3D8EngineSetRefreshRate = vcversion::AdjustOffset(0x0065DBC0);
static unsigned long g_RwD3D8GetRenderState = vcversion::AdjustOffset(0x006582F0);
static unsigned long g_RwD3D8GetTransform = vcversion::AdjustOffset(0x0065F670);
static unsigned long g_RwD3D8SetIndices = vcversion::AdjustOffset(0x0065F3C0);
static unsigned long g_RwD3D8SetLight = vcversion::AdjustOffset(0x0065FB20);
static unsigned long g_RwD3D8SetPixelShader = vcversion::AdjustOffset(0x0065F330);
static unsigned long g_RwD3D8SetPixelShaderConstant = vcversion::AdjustOffset(0x0065FF70);
static unsigned long g_RwD3D8SetRenderState = vcversion::AdjustOffset(0x006582A0);
static unsigned long g_RwD3D8SetStreamSource = vcversion::AdjustOffset(0x0065F370);
static unsigned long g_RwD3D8SetSurfaceProperties = vcversion::AdjustOffset(0x0065F7F0);
static unsigned long g_RwD3D8SetTexture = vcversion::AdjustOffset(0x00659850);
static unsigned long g_RwD3D8SetTextureStageState = vcversion::AdjustOffset(0x00658310);
static unsigned long g_RwD3D8SetTransform = vcversion::AdjustOffset(0x0065F530);
static unsigned long g_RwD3D8SetTransformWorld = vcversion::AdjustOffset(0x0065F6A0);
static unsigned long g_RwD3D8SetVertexShader = vcversion::AdjustOffset(0x0065F2F0);
static unsigned long g_RwEngineClose = vcversion::AdjustOffset(0x00642CE0);
static unsigned long g_RwEngineGetCurrentSubSystem = vcversion::AdjustOffset(0x00642AE0);
static unsigned long g_RwEngineGetCurrentVideoMode = vcversion::AdjustOffset(0x00642BA0);
static unsigned long g_RwEngineGetNumSubSystems = vcversion::AdjustOffset(0x00642A80);
static unsigned long g_RwEngineGetNumVideoModes = vcversion::AdjustOffset(0x00642B40);
static unsigned long g_RwEngineGetSubSystemInfo = vcversion::AdjustOffset(0x00642AB0);
static unsigned long g_RwEngineGetVideoModeInfo = vcversion::AdjustOffset(0x00642B70);
static unsigned long g_RwEngineInit = vcversion::AdjustOffset(0x00642F40);
static unsigned long g_RwEngineOpen = vcversion::AdjustOffset(0x00642D50);
static unsigned long g_RwEngineRegisterPlugin = vcversion::AdjustOffset(0x00642A30);
static unsigned long g_RwEngineSetSubSystem = vcversion::AdjustOffset(0x00642B10);
static unsigned long g_RwEngineSetVideoMode = vcversion::AdjustOffset(0x00642BD0);
static unsigned long g_RwEngineStart = vcversion::AdjustOffset(0x00642C50);
static unsigned long g_RwEngineStop = vcversion::AdjustOffset(0x00642C00);
static unsigned long g_RwEngineTerm = vcversion::AdjustOffset(0x00642F00);
static unsigned long g_RwErrorGet = vcversion::AdjustOffset(0x00669B40);
static unsigned long g_RwErrorSet = vcversion::AdjustOffset(0x00669AE0);
static unsigned long g_RwFrameAddChild = vcversion::AdjustOffset(0x00644DA0);
static unsigned long g_RwFrameCreate = vcversion::AdjustOffset(0x00644AA0);
static unsigned long g_RwFrameDestroy = vcversion::AdjustOffset(0x00644AD0);
static unsigned long g_RwFrameDestroyHierarchy = vcversion::AdjustOffset(0x00644C90);
static unsigned long g_RwFrameDirty = vcversion::AdjustOffset(0x006449D0);
static unsigned long g_RwFrameForAllChildren = vcversion::AdjustOffset(0x00645060);
static unsigned long g_RwFrameForAllObjects = vcversion::AdjustOffset(0x006453B0);
static unsigned long g_RwFrameGetLTM = vcversion::AdjustOffset(0x00644D80);
static unsigned long g_RwFrameOrthoNormalize = vcversion::AdjustOffset(0x00645320);
static unsigned long g_RwFrameRegisterPlugin = vcversion::AdjustOffset(0x006453F0);
static unsigned long g_RwFrameRegisterPluginStream_1 = vcversion::AdjustOffset(0x00650480);
static unsigned long g_RwFrameRegisterPluginStream_2 = vcversion::AdjustOffset(0x00655040);
static unsigned long g_RwFrameRegisterPluginStream_4 = vcversion::AdjustOffset(0x00660350);
static unsigned long g_RwFrameRegisterPluginStream_5 = vcversion::AdjustOffset(0x006736F0);
static unsigned long g_RwFrameRegisterPlugin_5 = vcversion::AdjustOffset(0x00655010);
static unsigned long g_RwFrameRegisterPlugin_8 = vcversion::AdjustOffset(0x00660910);
static unsigned long g_RwFrameRegisterPlugin_9 = vcversion::AdjustOffset(0x006736C0);
static unsigned long g_RwFrameRemoveChild = vcversion::AdjustOffset(0x00644F70);
static unsigned long g_RwFrameRotate = vcversion::AdjustOffset(0x00645280);
static unsigned long g_RwFrameScale = vcversion::AdjustOffset(0x00645140);
static unsigned long g_RwFrameTransform = vcversion::AdjustOffset(0x006451E0);
static unsigned long g_RwFrameTranslate = vcversion::AdjustOffset(0x006450A0);
static unsigned long g_RwFrameUpdateObjects = vcversion::AdjustOffset(0x00644D00);
static unsigned long g_RwFreeListCreate = vcversion::AdjustOffset(0x00665620);
static unsigned long g_RwFreeListDestroy = vcversion::AdjustOffset(0x00665630);
static unsigned long g_RwFreeListForAllUsed = vcversion::AdjustOffset(0x00665950);
static unsigned long g_RwFreeListPurgeAllFreeLists = vcversion::AdjustOffset(0x00665A50);
static unsigned long g_RwIm2DGetFarScreenZ = vcversion::AdjustOffset(0x00649B90);
static unsigned long g_RwIm2DGetNearScreenZ = vcversion::AdjustOffset(0x00649B80);
static unsigned long g_RwIm2DRenderIndexedPrimitive = vcversion::AdjustOffset(0x00649C20);
static unsigned long g_RwIm2DRenderLine = vcversion::AdjustOffset(0x00649C00);
static unsigned long g_RwIm2DRenderPrimitive = vcversion::AdjustOffset(0x00649C10);
static unsigned long g_RwIm3DEnd = vcversion::AdjustOffset(0x0065AF60);
static unsigned long g_RwIm3DRenderIndexedPrimitive = vcversion::AdjustOffset(0x0065AF90);
static unsigned long g_RwIm3DRenderLine = vcversion::AdjustOffset(0x0065B0F0);
static unsigned long g_RwIm3DSetRenderPipeline = vcversion::AdjustOffset(0x0065B210);
static unsigned long g_RwIm3DSetTransformPipeline = vcversion::AdjustOffset(0x0065B1C0);
static unsigned long g_RwIm3DTransform = vcversion::AdjustOffset(0x0065AE90);
static unsigned long g_RwImageAllocatePixels = vcversion::AdjustOffset(0x00651310);
static unsigned long g_RwImageApplyMask = vcversion::AdjustOffset(0x006514D0);
static unsigned long g_RwImageCopy = vcversion::AdjustOffset(0x00652080);
static unsigned long g_RwImageCreate = vcversion::AdjustOffset(0x00651250);
static unsigned long g_RwImageCreateResample = vcversion::AdjustOffset(0x00672490);
static unsigned long g_RwImageDestroy = vcversion::AdjustOffset(0x006512B0);
static unsigned long g_RwImageFindFileType = vcversion::AdjustOffset(0x00651C70);
static unsigned long g_RwImageFindRasterFormat = vcversion::AdjustOffset(0x006602E0);
static unsigned long g_RwImageFreePixels = vcversion::AdjustOffset(0x006513D0);
static unsigned long g_RwImageGammaCorrect = vcversion::AdjustOffset(0x00652260);
static unsigned long g_RwImageMakeMask = vcversion::AdjustOffset(0x00651400);
static unsigned long g_RwImageRead = vcversion::AdjustOffset(0x00651940);
static unsigned long g_RwImageReadMaskedImage = vcversion::AdjustOffset(0x00651D40);
static unsigned long g_RwImageResample = vcversion::AdjustOffset(0x00671D80);
static unsigned long g_RwImageSetFromRaster = vcversion::AdjustOffset(0x00660270);
static unsigned long g_RwImageSetGamma = vcversion::AdjustOffset(0x006523F0);
static unsigned long g_RwImageSetPath = vcversion::AdjustOffset(0x00651880);
static unsigned long g_RwMatrixCreate = vcversion::AdjustOffset(0x00644620);
static unsigned long g_RwMatrixDestroy = vcversion::AdjustOffset(0x006445F0);
static unsigned long g_RwMatrixInvert = vcversion::AdjustOffset(0x00643F40);
static unsigned long g_RwMatrixMultiply = vcversion::AdjustOffset(0x006437C0);
static unsigned long g_RwMatrixOptimize = vcversion::AdjustOffset(0x006436F0);
static unsigned long g_RwMatrixRotate = vcversion::AdjustOffset(0x00643EA0);
static unsigned long g_RwMatrixRotateOneMinusCosineSine = vcversion::AdjustOffset(0x00643C10);
static unsigned long g_RwMatrixScale = vcversion::AdjustOffset(0x00644190);
static unsigned long g_RwMatrixTransform = vcversion::AdjustOffset(0x00644470);
static unsigned long g_RwMatrixTranslate = vcversion::AdjustOffset(0x00644320);
static unsigned long g_RwMatrixUpdate = vcversion::AdjustOffset(0x006437B0);
static unsigned long g_RwMemLittleEndian32 = vcversion::AdjustOffset(0x0064FBC0);
static unsigned long g_RwOsGetFileInterface = vcversion::AdjustOffset(0x00663580);
static unsigned long g_RwRasterCreate = vcversion::AdjustOffset(0x00655490);
static unsigned long g_RwRasterDestroy = vcversion::AdjustOffset(0x006552E0);
static unsigned long g_RwRasterGetCurrentContext = vcversion::AdjustOffset(0x00655230);
static unsigned long g_RwRasterGetNumLevels = vcversion::AdjustOffset(0x00655420);
static unsigned long g_RwRasterLock = vcversion::AdjustOffset(0x00655530);
static unsigned long g_RwRasterLockPalette = vcversion::AdjustOffset(0x006553A0);
static unsigned long g_RwRasterPopContext = vcversion::AdjustOffset(0x006553D0);
static unsigned long g_RwRasterPushContext = vcversion::AdjustOffset(0x00655320);
static unsigned long g_RwRasterRegisterPlugin = vcversion::AdjustOffset(0x00655370);
static unsigned long g_RwRasterRenderFast = vcversion::AdjustOffset(0x00655270);
static unsigned long g_RwRasterSetFromImage = vcversion::AdjustOffset(0x006602B0);
static unsigned long g_RwRasterShowRaster = vcversion::AdjustOffset(0x00655460);
static unsigned long g_RwRasterUnlock = vcversion::AdjustOffset(0x00655250);
static unsigned long g_RwRasterUnlockPalette = vcversion::AdjustOffset(0x006552B0);
static unsigned long g_RwRenderStateGet = vcversion::AdjustOffset(0x00649BF0);
static unsigned long g_RwRenderStateSet = vcversion::AdjustOffset(0x00649BA0);
static unsigned long g_RwResourcesAllocateResEntry = vcversion::AdjustOffset(0x00669330);
static unsigned long g_RwResourcesEmptyArena = vcversion::AdjustOffset(0x00669520);
static unsigned long g_RwResourcesFreeResEntry = vcversion::AdjustOffset(0x00669240);
static unsigned long g_RwStreamClose = vcversion::AdjustOffset(0x006458F0);
static unsigned long g_RwStreamFindChunk = vcversion::AdjustOffset(0x0064FAC0);
static unsigned long g_RwStreamOpen = vcversion::AdjustOffset(0x006459C0);
static unsigned long g_RwStreamRead = vcversion::AdjustOffset(0x006454B0);
static unsigned long g_RwStreamReadInt32 = vcversion::AdjustOffset(0x0064FD50);
static unsigned long g_RwStreamReadReal = vcversion::AdjustOffset(0x0064FCE0);
static unsigned long g_RwStreamSkip = vcversion::AdjustOffset(0x006457D0);
static unsigned long g_RwStreamWrite = vcversion::AdjustOffset(0x00645610);
static unsigned long g_RwStreamWriteInt16 = vcversion::AdjustOffset(0x0064FCC0);
static unsigned long g_RwStreamWriteReal = vcversion::AdjustOffset(0x0064FC20);
static unsigned long g_RwTexDictionaryAddTexture = vcversion::AdjustOffset(0x0064E020);
static unsigned long g_RwTexDictionaryCreate = vcversion::AdjustOffset(0x0064DCF0);
static unsigned long g_RwTexDictionaryDestroy = vcversion::AdjustOffset(0x0064DD90);
static unsigned long g_RwTexDictionaryFindNamedTexture = vcversion::AdjustOffset(0x0064E060);
static unsigned long g_RwTexDictionaryForAllTextures = vcversion::AdjustOffset(0x0064DE20);
static unsigned long g_RwTexDictionaryGetCurrent = vcversion::AdjustOffset(0x0064E100);
static unsigned long g_RwTexDictionarySetCurrent = vcversion::AdjustOffset(0x0064E0E0);
static unsigned long g_RwTexDictionaryStreamRead = vcversion::AdjustOffset(0x0061E710);
static unsigned long g_RwTexDictionaryStreamWrite = vcversion::AdjustOffset(0x00650CD0);
static unsigned long g_RwTextureCreate = vcversion::AdjustOffset(0x0064DE60);
static unsigned long g_RwTextureDestroy = vcversion::AdjustOffset(0x0064DEC0);
static unsigned long g_RwTextureGetFindCallBack = vcversion::AdjustOffset(0x0064DC80);
static unsigned long g_RwTextureGetMipmapping = vcversion::AdjustOffset(0x0064DCB0);
static unsigned long g_RwTextureRasterGenerateMipmaps = vcversion::AdjustOffset(0x0064E340);
static unsigned long g_RwTextureRead = vcversion::AdjustOffset(0x0064E110);
static unsigned long g_RwTextureRegisterPlugin = vcversion::AdjustOffset(0x0064E310);
static unsigned long g_RwTextureSetFindCallBack = vcversion::AdjustOffset(0x0064DC60);
static unsigned long g_RwTextureSetMaskName = vcversion::AdjustOffset(0x0064DFB0);
static unsigned long g_RwTextureSetMipmapping = vcversion::AdjustOffset(0x0064DC90);
static unsigned long g_RwTextureSetName = vcversion::AdjustOffset(0x0064DF40);
static unsigned long g_RwTextureSetRaster = vcversion::AdjustOffset(0x0064DCC0);
static unsigned long g_RwTextureStreamGetSize = vcversion::AdjustOffset(0x006504B0);
static unsigned long g_RwTextureStreamRead = vcversion::AdjustOffset(0x006506F0);
static unsigned long g_RwTextureStreamWrite = vcversion::AdjustOffset(0x00650520);
static unsigned long g_RwV3dLength = vcversion::AdjustOffset(0x00647030);
static unsigned long g_RwV3dNormalize = vcversion::AdjustOffset(0x00646F20);
static unsigned long g_RwV3dTransformPoints = vcversion::AdjustOffset(0x00647160);
static unsigned long g_RwV3dTransformVectors = vcversion::AdjustOffset(0x00647170);
static unsigned long g_RxHeapAlloc = vcversion::AdjustOffset(0x00676B70);
static unsigned long g_RxHeapCreate = vcversion::AdjustOffset(0x00676EB0);
static unsigned long g_RxHeapDestroy = vcversion::AdjustOffset(0x00676E50);
static unsigned long g_RxHeapFree = vcversion::AdjustOffset(0x00676980);
static unsigned long g_RxLockedPipeAddFragment = vcversion::AdjustOffset(0x0067AE00);
static unsigned long g_RxLockedPipeUnlock = vcversion::AdjustOffset(0x0067A200);
static unsigned long g_RxPipelineCreate = vcversion::AdjustOffset(0x00668FC0);
static unsigned long g_RxPipelineExecute = vcversion::AdjustOffset(0x00668F20);
static unsigned long g_RxPipelineFindNodeByName = vcversion::AdjustOffset(0x0067AD70);
static unsigned long g__RwD3D8CurrentRasterTarget = vcversion::AdjustOffset(0x00786DC8);
static unsigned long g__RwD3D8RasterExtOffset = vcversion::AdjustOffset(0x00A0D8B0);
static unsigned long g__RwD3DAdapterIndex = vcversion::AdjustOffset(0x007897C8);
static unsigned long g__RwD3DAdapterType = vcversion::AdjustOffset(0x006DDE18);
static unsigned long g__RwD3DDevice = vcversion::AdjustOffset(0x007897A8);
static unsigned long g__RwDirect3DObject = vcversion::AdjustOffset(0x007897B4);
static unsigned long g__rpAtomicResyncInterpolatedSphere = vcversion::AdjustOffset(0x006405D0);
static unsigned long g__rpBuildMeshAddTriangle = vcversion::AdjustOffset(0x0066E140);
static unsigned long g__rpBuildMeshCreate = vcversion::AdjustOffset(0x0066DFE0);
static unsigned long g__rpBuildMeshDestroy = vcversion::AdjustOffset(0x0066E0C0);
static unsigned long g__rpClumpClose = vcversion::AdjustOffset(0x00640860);
static unsigned long g__rpClumpRegisterExtensions = vcversion::AdjustOffset(0x00640BD0);
static unsigned long g__rpCreatePlatformAtomicPipelines = vcversion::AdjustOffset(0x006742B0);
static unsigned long g__rpCreatePlatformWorldSectorPipelines = vcversion::AdjustOffset(0x00674200);
static unsigned long g__rpD3D8LightConstructor = vcversion::AdjustOffset(0x00679770);
static unsigned long g__rpD3D8LightCopy = vcversion::AdjustOffset(0x00679830);
static unsigned long g__rpD3D8LightPluginAttach = vcversion::AdjustOffset(0x00679740);
static unsigned long g__rpD3D8SkinGenericMatrixBlend1Matrix = vcversion::AdjustOffset(0x0066D2E0);
static unsigned long g__rpD3D8SkinGenericMatrixBlend1Weight = vcversion::AdjustOffset(0x0066D1F0);
static unsigned long g__rpDestroyPlatformAtomicPipelines = vcversion::AdjustOffset(0x00674330);
static unsigned long g__rpDestroyPlatformWorldSectorPipelines = vcversion::AdjustOffset(0x00674270);
static unsigned long g__rpGeometryAddRef = vcversion::AdjustOffset(0x0064CFD0);
static unsigned long g__rpGeometryNativeRead = vcversion::AdjustOffset(0x00673920);
static unsigned long g__rpGeometryOpen = vcversion::AdjustOffset(0x0064C8F0);
static unsigned long g__rpLightClose = vcversion::AdjustOffset(0x00660BC0);
static unsigned long g__rpLightTieDestroy = vcversion::AdjustOffset(0x00653530);
static unsigned long g__rpMatFXD3D8AtomicMatFXBumpMapRender = vcversion::AdjustOffset(0x006756F0);
static unsigned long g__rpMatFXD3D8AtomicMatFXDefaultRender = vcversion::AdjustOffset(0x00674380);
static unsigned long g__rpMatFXD3D8AtomicMatFXDualPassRender = vcversion::AdjustOffset(0x00674510);
static unsigned long g__rpMatFXD3D8AtomicMatFXEnvRender = vcversion::AdjustOffset(0x00674EE0);
static unsigned long g__rpMatFXD3D8AtomicMatFXRenderBlack = vcversion::AdjustOffset(0x00674450);
static unsigned long g__rpMatFXPipelineAtomicSetup = vcversion::AdjustOffset(0x00676930);
static unsigned long g__rpMatFXPipelinesCreate = vcversion::AdjustOffset(0x00676650);
static unsigned long g__rpMatFXPipelinesDestroy = vcversion::AdjustOffset(0x00676860);
static unsigned long g__rpMatFXTextureMaskCreate = vcversion::AdjustOffset(0x00655C40);
static unsigned long g__rpMaterialListAppendMaterial = vcversion::AdjustOffset(0x0066DA30);
static unsigned long g__rpMaterialListDeinitialize = vcversion::AdjustOffset(0x0066D9B0);
static unsigned long g__rpMaterialListFindMaterialIndex = vcversion::AdjustOffset(0x0066DAF0);
static unsigned long g__rpMaterialListGetMaterial = vcversion::AdjustOffset(0x0066DA20);
static unsigned long g__rpMaterialListInitialize = vcversion::AdjustOffset(0x0066DA10);
static unsigned long g__rpMaterialSetDefaultSurfaceProperties = vcversion::AdjustOffset(0x006556C0);
static unsigned long g__rpMeshClose = vcversion::AdjustOffset(0x0066DE90);
static unsigned long g__rpMeshDestroy = vcversion::AdjustOffset(0x0066E100);
static unsigned long g__rpMeshHeaderForAllMeshes = vcversion::AdjustOffset(0x0066E220);
static unsigned long g__rpMeshOptimise = vcversion::AdjustOffset(0x006700E0);
static unsigned long g__rpMeshRead = vcversion::AdjustOffset(0x0066E3B0);
static unsigned long g__rpMeshSize = vcversion::AdjustOffset(0x0066E580);
static unsigned long g__rpMeshWrite = vcversion::AdjustOffset(0x0066E260);
static unsigned long g__rpSkinD3D8CreatePlainPipe = vcversion::AdjustOffset(0x006796D0);
static unsigned long g__rpSkinGeometryNativeWrite = vcversion::AdjustOffset(0x0066D510);
static unsigned long g__rpSkinInitialize = vcversion::AdjustOffset(0x0066D410);
static unsigned long g__rpSkinIntelSSEMatrixBlend = vcversion::AdjustOffset(0x00678FD0);
static unsigned long g__rpSkinIntelSSEMatrixBlend1Matrix = vcversion::AdjustOffset(0x00678E40);
static unsigned long g__rpSkinIntelSSEMatrixBlend1Weight = vcversion::AdjustOffset(0x00678EF0);
static unsigned long g__rpSkinIntelSSEMatrixBlend2Weights = vcversion::AdjustOffset(0x006792C0);
static unsigned long g__rpSkinPipelinesCreate = vcversion::AdjustOffset(0x0066D650);
static unsigned long g__rpSkinPrepareAtomicMatrix = vcversion::AdjustOffset(0x00679500);
static unsigned long g__rpSkinSplitDataStreamGetSize = vcversion::AdjustOffset(0x0066D890);
static unsigned long g__rpSkinSplitDataStreamRead = vcversion::AdjustOffset(0x0066D730);
static unsigned long g__rpSkinSplitDataStreamWrite = vcversion::AdjustOffset(0x0066D6A0);
static unsigned long g__rpTieDestroy = vcversion::AdjustOffset(0x00653580);
static unsigned long g__rpTriListMeshGenerate = vcversion::AdjustOffset(0x0066FCC0);
static unsigned long g__rpWorldObjRegisterExtensions = vcversion::AdjustOffset(0x006535E0);
static unsigned long g__rpWorldSectorNativeRead = vcversion::AdjustOffset(0x00673E80);
static unsigned long g__rpWorldSectorNativeSize = vcversion::AdjustOffset(0x00674170);
static unsigned long g__rpWorldSectorNativeWrite = vcversion::AdjustOffset(0x00673C70);
static unsigned long g__rwCPUHave3DNow = vcversion::AdjustOffset(0x00677280);
static unsigned long g__rwCPUHaveMMX = vcversion::AdjustOffset(0x00677160);
static unsigned long g__rwCPUHaveSSE = vcversion::AdjustOffset(0x006771C0);
static unsigned long g__rwCPUHaveSSE2 = vcversion::AdjustOffset(0x00677220);
static unsigned long g__rwD3D8AtomicDefaultLightingCallback = vcversion::AdjustOffset(0x0067B6D0);
static unsigned long g__rwD3D8AtomicMatFXRenderCallback = vcversion::AdjustOffset(0x00676460);
static unsigned long g__rwD3D8CameraBeginUpdate = vcversion::AdjustOffset(0x0065DDA0);
static unsigned long g__rwD3D8CameraClear = vcversion::AdjustOffset(0x0065CA00);
static unsigned long g__rwD3D8CameraEndUpdate = vcversion::AdjustOffset(0x0065EA50);
static unsigned long g__rwD3D8CheckRasterSize = vcversion::AdjustOffset(0x00663990);
static unsigned long g__rwD3D8DecompressDXT1 = vcversion::AdjustOffset(0x006669E0);
static unsigned long g__rwD3D8DecompressDXT3 = vcversion::AdjustOffset(0x00666D30);
static unsigned long g__rwD3D8DecompressDXT5 = vcversion::AdjustOffset(0x00667080);
static unsigned long g__rwD3D8Im2DRenderClose = vcversion::AdjustOffset(0x00665DA0);
static unsigned long g__rwD3D8Im2DRenderIndexedPrimitive = vcversion::AdjustOffset(0x006664A0);
static unsigned long g__rwD3D8Im2DRenderLine = vcversion::AdjustOffset(0x00665DE0);
static unsigned long g__rwD3D8Im2DRenderOpen = vcversion::AdjustOffset(0x00665CE0);
static unsigned long g__rwD3D8Im2DRenderTriangle = vcversion::AdjustOffset(0x00665FE0);
static unsigned long g__rwD3D8Im3DRenderClose = vcversion::AdjustOffset(0x00677310);
static unsigned long g__rwD3D8Im3DRenderOpen = vcversion::AdjustOffset(0x00677330);
static unsigned long g__rwD3D8ImageFindRasterFormat = vcversion::AdjustOffset(0x00664460);
static unsigned long g__rwD3D8ImageGetFromRaster = vcversion::AdjustOffset(0x00663E80);
static unsigned long g__rwD3D8NativeTextureGetSize = vcversion::AdjustOffset(0x006400F0);
static unsigned long g__rwD3D8NativeTextureRead = vcversion::AdjustOffset(0x0063EFE0);
static unsigned long g__rwD3D8NativeTextureWrite = vcversion::AdjustOffset(0x0063FD60);
static unsigned long g__rwD3D8PixelToRGB = vcversion::AdjustOffset(0x00663C90);
static unsigned long g__rwD3D8RWGetRasterStage = vcversion::AdjustOffset(0x00659840);
static unsigned long g__rwD3D8RWGetRenderState = vcversion::AdjustOffset(0x00658F10);
static unsigned long g__rwD3D8RWSetRasterStage = vcversion::AdjustOffset(0x00659370);
static unsigned long g__rwD3D8RasterClear = vcversion::AdjustOffset(0x0063D860);
static unsigned long g__rwD3D8RasterClearRect = vcversion::AdjustOffset(0x0063D8A0);
static unsigned long g__rwD3D8RasterCreate = vcversion::AdjustOffset(0x0063C310);
static unsigned long g__rwD3D8RasterDestroy = vcversion::AdjustOffset(0x0063C0A0);
static unsigned long g__rwD3D8RasterGetMipLevels = vcversion::AdjustOffset(0x0063C030);
static unsigned long g__rwD3D8RasterLock = vcversion::AdjustOffset(0x0063EAB0);
static unsigned long g__rwD3D8RasterLockPalette = vcversion::AdjustOffset(0x0063E830);
static unsigned long g__rwD3D8RasterPluginAttach = vcversion::AdjustOffset(0x0063EF50);
static unsigned long g__rwD3D8RasterRender = vcversion::AdjustOffset(0x0063DF10);
static unsigned long g__rwD3D8RasterRenderFast = vcversion::AdjustOffset(0x0063DEF0);
static unsigned long g__rwD3D8RasterRenderScaled = vcversion::AdjustOffset(0x0063DED0);
static unsigned long g__rwD3D8RasterSetFromImage = vcversion::AdjustOffset(0x00664740);
static unsigned long g__rwD3D8RasterShowRaster = vcversion::AdjustOffset(0x0065EB50);
static unsigned long g__rwD3D8RasterSubRaster = vcversion::AdjustOffset(0x0063BFF0);
static unsigned long g__rwD3D8RasterUnlock = vcversion::AdjustOffset(0x0063E880);
static unsigned long g__rwD3D8RasterUnlockPalette = vcversion::AdjustOffset(0x0063E7C0);
static unsigned long g__rwD3D8RenderStateDestBlend = vcversion::AdjustOffset(0x00659320);
static unsigned long g__rwD3D8RenderStateFlushCache = vcversion::AdjustOffset(0x006581D0);
static unsigned long g__rwD3D8RenderStateIsVertexAlphaEnable = vcversion::AdjustOffset(0x00659F60);
static unsigned long g__rwD3D8RenderStateSrcBlend = vcversion::AdjustOffset(0x006592D0);
static unsigned long g__rwD3D8RenderStateTextureFilter = vcversion::AdjustOffset(0x00659170);
static unsigned long g__rwD3D8RenderStateVertexAlphaEnable = vcversion::AdjustOffset(0x00659CF0);
static unsigned long g__rwD3D8ResourceEntryInstanceDataDestroy = vcversion::AdjustOffset(0x00640190);
static unsigned long g__rwD3D8SetRasterContext = vcversion::AdjustOffset(0x0063D850);
static unsigned long g__rwD3D8SkinNeedsAManagedVertexBuffer = vcversion::AdjustOffset(0x0066D690);
static unsigned long g__rwD3D8TextureHasAlpha = vcversion::AdjustOffset(0x0063EE50);
static unsigned long g__rwD3D8TextureSetRaster = vcversion::AdjustOffset(0x0063C020);
static unsigned long g__rwD3D8CheckValidCameraTextureFormat = vcversion::AdjustOffset(0x0065FAC0);
static unsigned long g__rwD3D8CheckValidTextureFormat = vcversion::AdjustOffset(0x0065FA80);
static unsigned long g__rwD3D8CheckValidZBufferFormat = vcversion::AdjustOffset(0x0065FA20);
static unsigned long g__rwD3D8Im2DRenderPrimitive = vcversion::AdjustOffset(0x00666230);
static unsigned long g__rwD3D8ImageFindFormat = vcversion::AdjustOffset(0x00664550);
static unsigned long g__rwD3D8LightLocalEnable = vcversion::AdjustOffset(0x00679D50);
static unsigned long g__rwD3D8LightsEnable = vcversion::AdjustOffset(0x00679FC0);
static unsigned long g__rwD3D8LightsEqual = vcversion::AdjustOffset(0x0065FC70);
static unsigned long g__rwD3D8LightsGlobalEnable = vcversion::AdjustOffset(0x00679B60);
static unsigned long g__rwD3D8MatrixMultiplyTranspose = vcversion::AdjustOffset(0x0066BB10);
static unsigned long g__rwD3D8MeshGetNumVerticesMinIndex = vcversion::AdjustOffset(0x00678740);
static unsigned long g__rwD3D8RGBToPixel = vcversion::AdjustOffset(0x00663A40);
static unsigned long g__rwD3D8RenderStateStencilEnable = vcversion::AdjustOffset(0x00659F70);
static unsigned long g__rwD3D8RenderStateStencilFail = vcversion::AdjustOffset(0x00659FC0);
static unsigned long g__rwD3D8RenderStateStencilFunction = vcversion::AdjustOffset(0x0065A0B0);
static unsigned long g__rwD3D8RenderStateStencilFunctionMask = vcversion::AdjustOffset(0x0065A150);
static unsigned long g__rwD3D8RenderStateStencilFunctionRef = vcversion::AdjustOffset(0x0065A100);
static unsigned long g__rwD3D8RenderStateStencilFunctionWriteMask = vcversion::AdjustOffset(0x0065A1A0);
static unsigned long g__rwD3D8RenderStateStencilPass = vcversion::AdjustOffset(0x0065A060);
static unsigned long g__rwD3D8RenderStateStencilZFail = vcversion::AdjustOffset(0x0065A010);
static unsigned long g__rwDeviceRegisterPlugin = vcversion::AdjustOffset(0x0065B5C0);
static unsigned long g__rwDeviceSystemRequest = vcversion::AdjustOffset(0x00642940);
static unsigned long g__rwErrorOpen = vcversion::AdjustOffset(0x00669A90);
static unsigned long g__rwFrameCloneAndLinkClones = vcversion::AdjustOffset(0x00644730);
static unsigned long g__rwFrameListDeinitialize = vcversion::AdjustOffset(0x00660380);
static unsigned long g__rwFrameListStreamRead = vcversion::AdjustOffset(0x006603B0);
static unsigned long g__rwFramePurgeClone = vcversion::AdjustOffset(0x00644920);
static unsigned long g__rwFrameSyncDirty = vcversion::AdjustOffset(0x0066A540);
static unsigned long g__rwFrameSyncHierarchyLTM = vcversion::AdjustOffset(0x0066A7C0);
static unsigned long g__rwIm3DClose = vcversion::AdjustOffset(0x0065B4D0);
static unsigned long g__rwIm3DCreatePlatformRenderPipelines = vcversion::AdjustOffset(0x006770C0);
static unsigned long g__rwIm3DCreatePlatformTransformPipeline = vcversion::AdjustOffset(0x00676FC0);
static unsigned long g__rwIm3DDestroyPlatformRenderPipelines = vcversion::AdjustOffset(0x00677060);
static unsigned long g__rwIm3DDestroyPlatformTransformPipeline = vcversion::AdjustOffset(0x00677030);
static unsigned long g__rwIm3DOpen = vcversion::AdjustOffset(0x0065B510);
static unsigned long g__rwImageClose = vcversion::AdjustOffset(0x00651110);
static unsigned long g__rwInvSqrt = vcversion::AdjustOffset(0x00647100);
static unsigned long g__rwMatrixDeterminant = vcversion::AdjustOffset(0x006433E0);
static unsigned long g__rwMatrixIdentityError = vcversion::AdjustOffset(0x00643520);
static unsigned long g__rwMatrixNormalError = vcversion::AdjustOffset(0x00643490);
static unsigned long g__rwMatrixOrthogonalError = vcversion::AdjustOffset(0x00643430);
static unsigned long g__rwMatrixSetMultFn = vcversion::AdjustOffset(0x00643270);
static unsigned long g__rwMemoryClose = vcversion::AdjustOffset(0x00665BA0);
static unsigned long g__rwMemoryOpen = vcversion::AdjustOffset(0x00665A90);
static unsigned long g__rwObjectHasFrameReleaseFrame = vcversion::AdjustOffset(0x00660D10);
static unsigned long g__rwObjectHasFrameSetFrame = vcversion::AdjustOffset(0x00660CC0);
static unsigned long g__rwPalQuantAddImage = vcversion::AdjustOffset(0x00670140);
static unsigned long g__rwPalQuantInit = vcversion::AdjustOffset(0x00671C00);
static unsigned long g__rwPalQuantMatchImage = vcversion::AdjustOffset(0x006717C0);
static unsigned long g__rwPalQuantResolvePalette = vcversion::AdjustOffset(0x00670580);
static unsigned long g__rwPalQuantTerm = vcversion::AdjustOffset(0x00671CB0);
static unsigned long g__rwPluginRegistryAddPlgnStrmRightsCB = vcversion::AdjustOffset(0x00669C10);
static unsigned long g__rwPluginRegistryAddPlgnStrmlwysCB = vcversion::AdjustOffset(0x00669BE0);
static unsigned long g__rwPluginRegistryAddPlugin = vcversion::AdjustOffset(0x00669790);
static unsigned long g__rwPluginRegistryAddPluginStream = vcversion::AdjustOffset(0x00669BA0);
static unsigned long g__rwPluginRegistryClose = vcversion::AdjustOffset(0x00669650);
static unsigned long g__rwPluginRegistryCopyObject = vcversion::AdjustOffset(0x00669A50);
static unsigned long g__rwPluginRegistryDeInitObject = vcversion::AdjustOffset(0x00669A20);
static unsigned long g__rwPluginRegistryGetPluginOffset = vcversion::AdjustOffset(0x00669760);
static unsigned long g__rwPluginRegistryGetSize = vcversion::AdjustOffset(0x00669DC0);
static unsigned long g__rwPluginRegistryInitObject = vcversion::AdjustOffset(0x006699C0);
static unsigned long g__rwPluginRegistryInvokeRights = vcversion::AdjustOffset(0x00669D70);
static unsigned long g__rwPluginRegistrySkipDataChunks = vcversion::AdjustOffset(0x00669ED0);
static unsigned long g__rwPluginRegistryWriteDataChunks = vcversion::AdjustOffset(0x00669E00);
static unsigned long g__rwRasterClose = vcversion::AdjustOffset(0x00655570);
static unsigned long g__rwRasterOpen = vcversion::AdjustOffset(0x006555B0);
static unsigned long g__rwRenderPipelineClose = vcversion::AdjustOffset(0x006690C0);
static unsigned long g__rwRenderPipelineOpen = vcversion::AdjustOffset(0x006690A0);
static unsigned long g__rwResHeapAlloc = vcversion::AdjustOffset(0x00678650);
static unsigned long g__rwResHeapFree = vcversion::AdjustOffset(0x006785D0);
static unsigned long g__rwResHeapInit = vcversion::AdjustOffset(0x00678570);
static unsigned long g__rwResourcesClose = vcversion::AdjustOffset(0x006691E0);
static unsigned long g__rwResourcesOpen = vcversion::AdjustOffset(0x006690F0);
static unsigned long g__rwResourcesPurge = vcversion::AdjustOffset(0x006692B0);
static unsigned long g__rwSkinD3D8AtomicAllInOneNode = vcversion::AdjustOffset(0x0066BC50);
static unsigned long g__rwSqrt = vcversion::AdjustOffset(0x006470A0);
static unsigned long g__rwStreamModuleClose = vcversion::AdjustOffset(0x00645480);
static unsigned long g__rwStreamReadChunkHeader = vcversion::AdjustOffset(0x0064F990);
static unsigned long g__rwStreamWriteVersionedChunkHeader = vcversion::AdjustOffset(0x0064FA60);
static unsigned long g__rwStringOpen = vcversion::AdjustOffset(0x00663590);
static unsigned long g__rwStringOpen_0 = vcversion::AdjustOffset(0x0066A320);
static unsigned long g__rwTextureClose = vcversion::AdjustOffset(0x0064E370);
static unsigned long g__rwVectorClose = vcversion::AdjustOffset(0x00647180);
static unsigned long g__rwVectorOpen = vcversion::AdjustOffset(0x006471F0);
static unsigned long g__rwVectorSetMultFn = vcversion::AdjustOffset(0x00646D70);
static unsigned long g__rwerror = vcversion::AdjustOffset(0x00669B90);
static unsigned long g__rwpathisabsolute = vcversion::AdjustOffset(0x00672590);
static unsigned long g__rxChaseDependencies = vcversion::AdjustOffset(0x0067CBA0);
static unsigned long g__rxD3D8DefaultRenderCallback = vcversion::AdjustOffset(0x00678B30);
static unsigned long g__rxD3D8Reinstance = vcversion::AdjustOffset(0x00678AE0);
static unsigned long g__rxD3D8SkinAtomicCreateVertexBuffer = vcversion::AdjustOffset(0x0066C1A0);
static unsigned long g__rxD3D8SkinGeometryInstanceStaticInfo = vcversion::AdjustOffset(0x0066C2E0);
static unsigned long g__rxD3D8VertexBufferManagerClose = vcversion::AdjustOffset(0x00667660);
static unsigned long g__rxExecCtxGlobal = vcversion::AdjustOffset(0x009360F0);
static unsigned long g__rxHeapGlobal = vcversion::AdjustOffset(0x0078A054);
static unsigned long g__rxHeapReset = vcversion::AdjustOffset(0x00676DE0);
static unsigned long g__rxPacketDestroy = vcversion::AdjustOffset(0x00678510);
static unsigned long g__rxPipelineClose = vcversion::AdjustOffset(0x00668BB0);
static unsigned long g__rxPipelineDestroy = vcversion::AdjustOffset(0x00669030);
static unsigned long g__rxSkinD3D8AtomicAllInOnePipelineInit = vcversion::AdjustOffset(0x006796B0);
static unsigned long g__rx_rxRadixExchangeSort = vcversion::AdjustOffset(0x0067DAB0);
static unsigned long g_RwD3D8Image32GetFromRaster = vcversion::AdjustOffset(0x00664070);
static unsigned long g_RwD3D8Raster24_32LinearSetFromImage = vcversion::AdjustOffset(0x006651A0);
static unsigned long g_RwD3D8RasterCopyQuad = vcversion::AdjustOffset(0x0063DFD0);
static unsigned long g_RwD3D8RasterCtor = vcversion::AdjustOffset(0x0063EFB0);
static unsigned long g_RwD3D8RasterDtor = vcversion::AdjustOffset(0x0063EF80);
static unsigned long g_RwD3D8RasterPalletizedSetFromImage = vcversion::AdjustOffset(0x00664E50);
static unsigned long g_RwD3D8RasterRenderGeneric = vcversion::AdjustOffset(0x0063DF30);
static unsigned long g_RwD3D8RasterRenderQuad = vcversion::AdjustOffset(0x0063E1A0);
static unsigned long g_RwD3D8RenderStateBorderColor = vcversion::AdjustOffset(0x0065A970);
static unsigned long g_RwD3D8SelectConvertFn = vcversion::AdjustOffset(0x00664C40);
static unsigned long g_RwD3D8RenderStateCullMode = vcversion::AdjustOffset(0x0065A9D0);
static unsigned long g_RwD3D8RenderStateShadeMode = vcversion::AdjustOffset(0x0065A920);
static unsigned long g_RwD3D8RenderStateZTestEnable = vcversion::AdjustOffset(0x0065A820);
static unsigned long g_RwD3D8RenderStateZWriteEnable = vcversion::AdjustOffset(0x0065A720);
static unsigned long g_RwDestroyEntry = vcversion::AdjustOffset(0x00669720);
static unsigned long g_RwFrameCloneRecurse = vcversion::AdjustOffset(0x006447D0);
static unsigned long g_RwFrameDestroyRecurse = vcversion::AdjustOffset(0x00644C20);
static unsigned long g_RwFrameInternalInit = vcversion::AdjustOffset(0x006449F0);
static unsigned long g_RwFrameOpen = vcversion::AdjustOffset(0x00645420);
static unsigned long g_RwSetHierarchyRoot = vcversion::AdjustOffset(0x00644990);
static unsigned long g_Rwfexist = vcversion::AdjustOffset(0x00663650);
static unsigned long g_RxD3D8SubmitNode = vcversion::AdjustOffset(0x00677390);

extern "C" __declspec(naked) int RpAtomicClone()
{
	__asm jmp g_RpAtomicClone;
}

extern "C" __declspec(naked) int RpAtomicCreate()
{
	__asm jmp g_RpAtomicCreate;
}

extern "C" __declspec(naked) int RpAtomicDestroy()
{
	__asm jmp g_RpAtomicDestroy;
}

extern "C" __declspec(naked) int RpAtomicGetWorldBoundingSphere()
{
	__asm jmp g_RpAtomicGetWorldBoundingSphere;
}

extern "C" __declspec(naked) int RpAtomicRegisterPlugin()
{
	__asm jmp g_RpAtomicRegisterPlugin;
}

extern "C" __declspec(naked) int RpAtomicRegisterPluginStream()
{
	__asm jmp g_RpAtomicRegisterPluginStream;
}

extern "C" __declspec(naked) int RpAtomicSetDefaultPipeline()
{
	__asm jmp g_RpAtomicSetDefaultPipeline;
}

extern "C" __declspec(naked) int RpAtomicSetFrame()
{
	__asm jmp g_RpAtomicSetFrame;
}

extern "C" __declspec(naked) int RpAtomicSetGeometry()
{
	__asm jmp g_RpAtomicSetGeometry;
}

extern "C" __declspec(naked) int RpAtomicSetStreamAlwaysCallBack()
{
	__asm jmp g_RpAtomicSetStreamAlwaysCallBack;
}

extern "C" __declspec(naked) int RpAtomicSetStreamRightsCallBack()
{
	__asm jmp g_RpAtomicSetStreamRightsCallBack;
}

extern "C" __declspec(naked) int RpClumpAddAtomic()
{
	__asm jmp g_RpClumpAddAtomic;
}

extern "C" __declspec(naked) int RpClumpClone()
{
	__asm jmp g_RpClumpClone;
}

extern "C" __declspec(naked) int RpClumpCreate()
{
	__asm jmp g_RpClumpCreate;
}

extern "C" __declspec(naked) int RpClumpDestroy()
{
	__asm jmp g_RpClumpDestroy;
}

extern "C" __declspec(naked) int RpClumpForAllAtomics()
{
	__asm jmp g_RpClumpForAllAtomics;
}

extern "C" __declspec(naked) int RpClumpForAllCameras()
{
	__asm jmp g_RpClumpForAllCameras;
}

extern "C" __declspec(naked) int RpClumpForAllLights()
{
	__asm jmp g_RpClumpForAllLights;
}

extern "C" __declspec(naked) int RpClumpGetNumAtomics()
{
	__asm jmp g_RpClumpGetNumAtomics;
}

extern "C" __declspec(naked) int RpClumpRegisterPlugin()
{
	__asm jmp g_RpClumpRegisterPlugin;
}

extern "C" __declspec(naked) int RpClumpRemoveAtomic()
{
	__asm jmp g_RpClumpRemoveAtomic;
}

extern "C" __declspec(naked) int RpClumpRender()
{
	__asm jmp g_RpClumpRender;
}

extern "C" __declspec(naked) int RpClumpStreamRead()
{
	__asm jmp g_RpClumpStreamRead;
}

extern "C" __declspec(naked) int RpGeometryAddMorphTarget()
{
	__asm jmp g_RpGeometryAddMorphTarget;
}

extern "C" __declspec(naked) int RpGeometryForAllMaterials()
{
	__asm jmp g_RpGeometryForAllMaterials;
}

extern "C" __declspec(naked) int RpGeometryLock()
{
	__asm jmp g_RpGeometryLock;
}

extern "C" __declspec(naked) int RpGeometryRegisterPlugin()
{
	__asm jmp g_RpGeometryRegisterPlugin;
}

extern "C" __declspec(naked) int RpGeometryRegisterPluginStream()
{
	__asm jmp g_RpGeometryRegisterPluginStream;
}

extern "C" __declspec(naked) int RpGeometryTriangleSetMaterial()
{
	__asm jmp g_RpGeometryTriangleSetMaterial;
}

extern "C" __declspec(naked) int RpGeometryTriangleSetVertexIndices()
{
	__asm jmp g_RpGeometryTriangleSetVertexIndices;
}

extern "C" __declspec(naked) int RpHAnimAnimationCreate()
{
	__asm jmp g_RpHAnimAnimationCreate;
}

extern "C" __declspec(naked) int RtAnimAnimationCreate()
{
	__asm jmp g_RtAnimAnimationCreate;
}

extern "C" __declspec(naked) int RpHAnimAnimationDestroy()
{
	__asm jmp g_RpHAnimAnimationDestroy;
}

extern "C" __declspec(naked) int RpHAnimHierarchyCreate()
{
	__asm jmp g_RpHAnimHierarchyCreate;
}

extern "C" __declspec(naked) int RpHAnimHierarchyGetMatrixArray()
{
	__asm jmp g_RpHAnimHierarchyGetMatrixArray;
}

extern "C" __declspec(naked) int RpHAnimHierarchyUpdateMatrices()
{
	__asm jmp g_RpHAnimHierarchyUpdateMatrices;
}

extern "C" __declspec(naked) int RpHAnimIDGetIndex()
{
	__asm jmp g_RpHAnimIDGetIndex;
}

extern "C" __declspec(naked) int RpHAnimInterpolatorSetCurrentAnim()
{
	__asm jmp g_RpHAnimInterpolatorSetCurrentAnim;
}

extern "C" __declspec(naked) int RtAnimInterpolatorSetCurrentAnim()
{
	__asm jmp g_RtAnimInterpolatorSetCurrentAnim;
}

extern "C" __declspec(naked) int RpHAnimPluginAttach()
{
	__asm jmp g_RpHAnimPluginAttach;
}

extern "C" __declspec(naked) int RpHAnimRegisterInterpolationScheme()
{
	__asm jmp g_RpHAnimRegisterInterpolationScheme;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameAdd()
{
	__asm jmp g_RpHAnimStdKeyFrameAdd;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameBlend()
{
	__asm jmp g_RpHAnimStdKeyFrameBlend;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameInterpolate()
{
	__asm jmp g_RpHAnimStdKeyFrameInterpolate;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameMulRecip()
{
	__asm jmp g_RpHAnimStdKeyFrameMulRecip;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameStreamGetSize()
{
	__asm jmp g_RpHAnimStdKeyFrameStreamGetSize;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameStreamRead()
{
	__asm jmp g_RpHAnimStdKeyFrameStreamRead;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameStreamWrite()
{
	__asm jmp g_RpHAnimStdKeyFrameStreamWrite;
}

extern "C" __declspec(naked) int RpHAnimStdKeyFrameToMatrix()
{
	__asm jmp g_RpHAnimStdKeyFrameToMatrix;
}

extern "C" __declspec(naked) int RpLightCreate()
{
	__asm jmp g_RpLightCreate;
}

extern "C" __declspec(naked) int RpLightGetConeAngle()
{
	__asm jmp g_RpLightGetConeAngle;
}

extern "C" __declspec(naked) int RpLightSetColor()
{
	__asm jmp g_RpLightSetColor;
}

extern "C" __declspec(naked) int RpLightSetRadius()
{
	__asm jmp g_RpLightSetRadius;
}

extern "C" __declspec(naked) int RpMatFXAtomicEnableEffects()
{
	__asm jmp g_RpMatFXAtomicEnableEffects;
}

extern "C" __declspec(naked) int RpMatFXMaterialGetEffects()
{
	__asm jmp g_RpMatFXMaterialGetEffects;
}

extern "C" __declspec(naked) int RpMatFXMaterialGetEnvMapCoefficient()
{
	__asm jmp g_RpMatFXMaterialGetEnvMapCoefficient;
}

extern "C" __declspec(naked) int RpMatFXMaterialSetBumpMapTexture()
{
	__asm jmp g_RpMatFXMaterialSetBumpMapTexture;
}

extern "C" __declspec(naked) int RpMatFXMaterialSetDualBlendModes()
{
	__asm jmp g_RpMatFXMaterialSetDualBlendModes;
}

extern "C" __declspec(naked) int RpMatFXMaterialSetEffects()
{
	__asm jmp g_RpMatFXMaterialSetEffects;
}

extern "C" __declspec(naked) int RpMatFXMaterialSetEnvMapCoefficient()
{
	__asm jmp g_RpMatFXMaterialSetEnvMapCoefficient;
}

extern "C" __declspec(naked) int RpMatFXMaterialSetEnvMapFrame()
{
	__asm jmp g_RpMatFXMaterialSetEnvMapFrame;
}

extern "C" __declspec(naked) int RpMatFXMaterialSetupEnvMap()
{
	__asm jmp g_RpMatFXMaterialSetupEnvMap;
}

extern "C" __declspec(naked) int RpMatFXPluginAttach()
{
	__asm jmp g_RpMatFXPluginAttach;
}

extern "C" __declspec(naked) int RpMaterialCreate()
{
	__asm jmp g_RpMaterialCreate;
}

extern "C" __declspec(naked) int RpMaterialDestroy()
{
	__asm jmp g_RpMaterialDestroy;
}

extern "C" __declspec(naked) int RpMaterialRegisterPlugin()
{
	__asm jmp g_RpMaterialRegisterPlugin;
}

extern "C" __declspec(naked) int RpMaterialRegisterPluginStream()
{
	__asm jmp g_RpMaterialRegisterPluginStream;
}

extern "C" __declspec(naked) int RpMaterialSetTexture()
{
	__asm jmp g_RpMaterialSetTexture;
}

extern "C" __declspec(naked) int RpMorphTargetCalcBoundingSphere()
{
	__asm jmp g_RpMorphTargetCalcBoundingSphere;
}

extern "C" __declspec(naked) int RpSkinAtomicGetHAnimHierarchy()
{
	__asm jmp g_RpSkinAtomicGetHAnimHierarchy;
}

extern "C" __declspec(naked) int RpSkinAtomicSetHAnimHierarchy()
{
	__asm jmp g_RpSkinAtomicSetHAnimHierarchy;
}

extern "C" __declspec(naked) int RpSkinGeometryGetSkin()
{
	__asm jmp g_RpSkinGeometryGetSkin;
}

extern "C" __declspec(naked) int RpSkinGeometrySetSkin()
{
	__asm jmp g_RpSkinGeometrySetSkin;
}

extern "C" __declspec(naked) int RpSkinGetVertexBoneWeights()
{
	__asm jmp g_RpSkinGetVertexBoneWeights;
}

extern "C" __declspec(naked) int RpSkinPluginAttach()
{
	__asm jmp g_RpSkinPluginAttach;
}

extern "C" __declspec(naked) int RpWorldAddCamera()
{
	__asm jmp g_RpWorldAddCamera;
}

extern "C" __declspec(naked) int RpWorldAddClump()
{
	__asm jmp g_RpWorldAddClump;
}

extern "C" __declspec(naked) int RpWorldAddLight()
{
	__asm jmp g_RpWorldAddLight;
}

extern "C" __declspec(naked) int RpWorldCreate()
{
	__asm jmp g_RpWorldCreate;
}

extern "C" __declspec(naked) int RpWorldDestroy()
{
	__asm jmp g_RpWorldDestroy;
}

extern "C" __declspec(naked) int RpWorldPluginAttach()
{
	__asm jmp g_RpWorldPluginAttach;
}

extern "C" __declspec(naked) int RpWorldRemoveCamera()
{
	__asm jmp g_RpWorldRemoveCamera;
}

extern "C" __declspec(naked) int RpWorldRemoveLight()
{
	__asm jmp g_RpWorldRemoveLight;
}

extern "C" __declspec(naked) int RpWorldSectorGetWorld()
{
	__asm jmp g_RpWorldSectorGetWorld;
}

extern "C" __declspec(naked) int RpWorldSetDefaultSectorPipeline()
{
	__asm jmp g_RpWorldSetDefaultSectorPipeline;
}

extern "C" __declspec(naked) int RtBMPImageRead()
{
	__asm jmp g_RtBMPImageRead;
}

extern "C" __declspec(naked) int RwBBoxCalculate()
{
	__asm jmp g_RwBBoxCalculate;
}

extern "C" __declspec(naked) int RwCameraBeginUpdate()
{
	__asm jmp g_RwCameraBeginUpdate;
}

extern "C" __declspec(naked) int RwCameraClear()
{
	__asm jmp g_RwCameraClear;
}

extern "C" __declspec(naked) int RwCameraCreate()
{
	__asm jmp g_RwCameraCreate;
}

extern "C" __declspec(naked) int RwCameraDestroy()
{
	__asm jmp g_RwCameraDestroy;
}

extern "C" __declspec(naked) int RwCameraEndUpdate()
{
	__asm jmp g_RwCameraEndUpdate;
}

extern "C" __declspec(naked) int RwCameraFrustumTestSphere()
{
	__asm jmp g_RwCameraFrustumTestSphere;
}

extern "C" __declspec(naked) int RwCameraRegisterPlugin()
{
	__asm jmp g_RwCameraRegisterPlugin;
}

extern "C" __declspec(naked) int RwCameraSetFarClipPlane()
{
	__asm jmp g_RwCameraSetFarClipPlane;
}

extern "C" __declspec(naked) int RwCameraSetNearClipPlane()
{
	__asm jmp g_RwCameraSetNearClipPlane;
}

extern "C" __declspec(naked) int RwCameraSetProjection()
{
	__asm jmp g_RwCameraSetProjection;
}

extern "C" __declspec(naked) int RwCameraSetViewOffset()
{
	__asm jmp g_RwCameraSetViewOffset;
}

extern "C" __declspec(naked) int RwCameraSetViewWindow()
{
	__asm jmp g_RwCameraSetViewWindow;
}

extern "C" __declspec(naked) int RwCameraShowRaster()
{
	__asm jmp g_RwCameraShowRaster;
}

extern "C" __declspec(naked) int RwD3D8CameraAttachWindow()
{
	__asm jmp g_RwD3D8CameraAttachWindow;
}

extern "C" __declspec(naked) int RwD3D8CameraIsBBoxFullyInsideFrustum()
{
	__asm jmp g_RwD3D8CameraIsBBoxFullyInsideFrustum;
}

extern "C" __declspec(naked) int RwD3D8CameraIsSphereFullyInsideFrustum()
{
	__asm jmp g_RwD3D8CameraIsSphereFullyInsideFrustum;
}

extern "C" __declspec(naked) int RwD3D8CreatePixelShader()
{
	__asm jmp g_RwD3D8CreatePixelShader;
}

extern "C" __declspec(naked) int RwD3D8DeletePixelShader()
{
	__asm jmp g_RwD3D8DeletePixelShader;
}

extern "C" __declspec(naked) int RwD3D8DeviceSupportsDXTTexture()
{
	__asm jmp g_RwD3D8DeviceSupportsDXTTexture;
}

extern "C" __declspec(naked) int RwD3D8DrawIndexedPrimitive()
{
	__asm jmp g_RwD3D8DrawIndexedPrimitive;
}

extern "C" __declspec(naked) int RwD3D8DrawPrimitive()
{
	__asm jmp g_RwD3D8DrawPrimitive;
}

extern "C" __declspec(naked) int RwD3D8DynamicVertexBufferCreate()
{
	__asm jmp g_RwD3D8DynamicVertexBufferCreate;
}

extern "C" __declspec(naked) int RwD3D8DynamicVertexBufferDestroy()
{
	__asm jmp g_RwD3D8DynamicVertexBufferDestroy;
}

extern "C" __declspec(naked) int RwD3D8DynamicVertexBufferLock()
{
	__asm jmp g_RwD3D8DynamicVertexBufferLock;
}

extern "C" __declspec(naked) int RwD3D8DynamicVertexBufferUnlock()
{
	__asm jmp g_RwD3D8DynamicVertexBufferUnlock;
}

extern "C" __declspec(naked) int RwD3D8EnableLight()
{
	__asm jmp g_RwD3D8EnableLight;
}

extern "C" __declspec(naked) int RwD3D8EngineSetRefreshRate()
{
	__asm jmp g_RwD3D8EngineSetRefreshRate;
}

extern "C" __declspec(naked) int RwD3D8GetRenderState()
{
	__asm jmp g_RwD3D8GetRenderState;
}

extern "C" __declspec(naked) int RwD3D8GetTransform()
{
	__asm jmp g_RwD3D8GetTransform;
}

extern "C" __declspec(naked) int RwD3D8SetIndices()
{
	__asm jmp g_RwD3D8SetIndices;
}

extern "C" __declspec(naked) int RwD3D8SetLight()
{
	__asm jmp g_RwD3D8SetLight;
}

extern "C" __declspec(naked) int RwD3D8SetPixelShader()
{
	__asm jmp g_RwD3D8SetPixelShader;
}

extern "C" __declspec(naked) int RwD3D8SetPixelShaderConstant()
{
	__asm jmp g_RwD3D8SetPixelShaderConstant;
}

extern "C" __declspec(naked) int RwD3D8SetRenderState()
{
	__asm jmp g_RwD3D8SetRenderState;
}

extern "C" __declspec(naked) int RwD3D8SetStreamSource()
{
	__asm jmp g_RwD3D8SetStreamSource;
}

extern "C" __declspec(naked) int RwD3D8SetSurfaceProperties()
{
	__asm jmp g_RwD3D8SetSurfaceProperties;
}

extern "C" __declspec(naked) int RwD3D8SetTexture()
{
	__asm jmp g_RwD3D8SetTexture;
}

extern "C" __declspec(naked) int RwD3D8SetTextureStageState()
{
	__asm jmp g_RwD3D8SetTextureStageState;
}

extern "C" __declspec(naked) int RwD3D8SetTransform()
{
	__asm jmp g_RwD3D8SetTransform;
}

extern "C" __declspec(naked) int RwD3D8SetTransformWorld()
{
	__asm jmp g_RwD3D8SetTransformWorld;
}

extern "C" __declspec(naked) int RwD3D8SetVertexShader()
{
	__asm jmp g_RwD3D8SetVertexShader;
}

extern "C" __declspec(naked) int RwEngineClose()
{
	__asm jmp g_RwEngineClose;
}

extern "C" __declspec(naked) int RwEngineGetCurrentSubSystem()
{
	__asm jmp g_RwEngineGetCurrentSubSystem;
}

extern "C" __declspec(naked) int RwEngineGetCurrentVideoMode()
{
	__asm jmp g_RwEngineGetCurrentVideoMode;
}

extern "C" __declspec(naked) int RwEngineGetNumSubSystems()
{
	__asm jmp g_RwEngineGetNumSubSystems;
}

extern "C" __declspec(naked) int RwEngineGetNumVideoModes()
{
	__asm jmp g_RwEngineGetNumVideoModes;
}

extern "C" __declspec(naked) int RwEngineGetSubSystemInfo()
{
	__asm jmp g_RwEngineGetSubSystemInfo;
}

extern "C" __declspec(naked) int RwEngineGetVideoModeInfo()
{
	__asm jmp g_RwEngineGetVideoModeInfo;
}

extern "C" __declspec(naked) int RwEngineInit()
{
	__asm jmp g_RwEngineInit;
}

extern "C" __declspec(naked) int RwEngineOpen()
{
	__asm jmp g_RwEngineOpen;
}

extern "C" __declspec(naked) int RwEngineRegisterPlugin()
{
	__asm jmp g_RwEngineRegisterPlugin;
}

extern "C" __declspec(naked) int RwEngineSetSubSystem()
{
	__asm jmp g_RwEngineSetSubSystem;
}

extern "C" __declspec(naked) int RwEngineSetVideoMode()
{
	__asm jmp g_RwEngineSetVideoMode;
}

extern "C" __declspec(naked) int RwEngineStart()
{
	__asm jmp g_RwEngineStart;
}

extern "C" __declspec(naked) int RwEngineStop()
{
	__asm jmp g_RwEngineStop;
}

extern "C" __declspec(naked) int RwEngineTerm()
{
	__asm jmp g_RwEngineTerm;
}

extern "C" __declspec(naked) int RwErrorGet()
{
	__asm jmp g_RwErrorGet;
}

extern "C" __declspec(naked) int RwErrorSet()
{
	__asm jmp g_RwErrorSet;
}

extern "C" __declspec(naked) int RwFrameAddChild()
{
	__asm jmp g_RwFrameAddChild;
}

extern "C" __declspec(naked) int RwFrameCreate()
{
	__asm jmp g_RwFrameCreate;
}

extern "C" __declspec(naked) int RwFrameDestroy()
{
	__asm jmp g_RwFrameDestroy;
}

extern "C" __declspec(naked) int RwFrameDestroyHierarchy()
{
	__asm jmp g_RwFrameDestroyHierarchy;
}

extern "C" __declspec(naked) int RwFrameDirty()
{
	__asm jmp g_RwFrameDirty;
}

extern "C" __declspec(naked) int RwFrameForAllChildren()
{
	__asm jmp g_RwFrameForAllChildren;
}

extern "C" __declspec(naked) int RwFrameForAllObjects()
{
	__asm jmp g_RwFrameForAllObjects;
}

extern "C" __declspec(naked) int RwFrameGetLTM()
{
	__asm jmp g_RwFrameGetLTM;
}

extern "C" __declspec(naked) int RwFrameOrthoNormalize()
{
	__asm jmp g_RwFrameOrthoNormalize;
}

extern "C" __declspec(naked) int RwFrameRegisterPlugin()
{
	__asm jmp g_RwFrameRegisterPlugin;
}

extern "C" __declspec(naked) int RwFrameRegisterPluginStream_1()
{
	__asm jmp g_RwFrameRegisterPluginStream_1;
}

extern "C" __declspec(naked) int RwFrameRegisterPluginStream_2()
{
	__asm jmp g_RwFrameRegisterPluginStream_2;
}

extern "C" __declspec(naked) int RwFrameRegisterPluginStream_4()
{
	__asm jmp g_RwFrameRegisterPluginStream_4;
}

extern "C" __declspec(naked) int RwFrameRegisterPluginStream_5()
{
	__asm jmp g_RwFrameRegisterPluginStream_5;
}

extern "C" __declspec(naked) int RwFrameRegisterPlugin_5()
{
	__asm jmp g_RwFrameRegisterPlugin_5;
}

extern "C" __declspec(naked) int RwFrameRegisterPlugin_8()
{
	__asm jmp g_RwFrameRegisterPlugin_8;
}

extern "C" __declspec(naked) int RwFrameRegisterPlugin_9()
{
	__asm jmp g_RwFrameRegisterPlugin_9;
}

extern "C" __declspec(naked) int RwFrameRemoveChild()
{
	__asm jmp g_RwFrameRemoveChild;
}

extern "C" __declspec(naked) int RwFrameRotate()
{
	__asm jmp g_RwFrameRotate;
}

extern "C" __declspec(naked) int RwFrameScale()
{
	__asm jmp g_RwFrameScale;
}

extern "C" __declspec(naked) int RwFrameTransform()
{
	__asm jmp g_RwFrameTransform;
}

extern "C" __declspec(naked) int RwFrameTranslate()
{
	__asm jmp g_RwFrameTranslate;
}

extern "C" __declspec(naked) int RwFrameUpdateObjects()
{
	__asm jmp g_RwFrameUpdateObjects;
}

extern "C" __declspec(naked) int RwFreeListCreate()
{
	__asm jmp g_RwFreeListCreate;
}

extern "C" __declspec(naked) int RwFreeListDestroy()
{
	__asm jmp g_RwFreeListDestroy;
}

extern "C" __declspec(naked) int RwFreeListForAllUsed()
{
	__asm jmp g_RwFreeListForAllUsed;
}

extern "C" __declspec(naked) int RwFreeListPurgeAllFreeLists()
{
	__asm jmp g_RwFreeListPurgeAllFreeLists;
}

extern "C" __declspec(naked) int RwIm2DGetFarScreenZ()
{
	__asm jmp g_RwIm2DGetFarScreenZ;
}

extern "C" __declspec(naked) int RwIm2DGetNearScreenZ()
{
	__asm jmp g_RwIm2DGetNearScreenZ;
}

extern "C" __declspec(naked) int RwIm2DRenderIndexedPrimitive()
{
	__asm jmp g_RwIm2DRenderIndexedPrimitive;
}

extern "C" __declspec(naked) int RwIm2DRenderLine()
{
	__asm jmp g_RwIm2DRenderLine;
}

extern "C" __declspec(naked) int RwIm2DRenderPrimitive()
{
	__asm jmp g_RwIm2DRenderPrimitive;
}

extern "C" __declspec(naked) int RwIm3DEnd()
{
	__asm jmp g_RwIm3DEnd;
}

extern "C" __declspec(naked) int RwIm3DRenderIndexedPrimitive()
{
	__asm jmp g_RwIm3DRenderIndexedPrimitive;
}

extern "C" __declspec(naked) int RwIm3DRenderLine()
{
	__asm jmp g_RwIm3DRenderLine;
}

extern "C" __declspec(naked) int RwIm3DSetRenderPipeline()
{
	__asm jmp g_RwIm3DSetRenderPipeline;
}

extern "C" __declspec(naked) int RwIm3DSetTransformPipeline()
{
	__asm jmp g_RwIm3DSetTransformPipeline;
}

extern "C" __declspec(naked) int RwIm3DTransform()
{
	__asm jmp g_RwIm3DTransform;
}

extern "C" __declspec(naked) int RwImageAllocatePixels()
{
	__asm jmp g_RwImageAllocatePixels;
}

extern "C" __declspec(naked) int RwImageApplyMask()
{
	__asm jmp g_RwImageApplyMask;
}

extern "C" __declspec(naked) int RwImageCopy()
{
	__asm jmp g_RwImageCopy;
}

extern "C" __declspec(naked) int RwImageCreate()
{
	__asm jmp g_RwImageCreate;
}

extern "C" __declspec(naked) int RwImageCreateResample()
{
	__asm jmp g_RwImageCreateResample;
}

extern "C" __declspec(naked) int RwImageDestroy()
{
	__asm jmp g_RwImageDestroy;
}

extern "C" __declspec(naked) int RwImageFindFileType()
{
	__asm jmp g_RwImageFindFileType;
}

extern "C" __declspec(naked) int RwImageFindRasterFormat()
{
	__asm jmp g_RwImageFindRasterFormat;
}

extern "C" __declspec(naked) int RwImageFreePixels()
{
	__asm jmp g_RwImageFreePixels;
}

extern "C" __declspec(naked) int RwImageGammaCorrect()
{
	__asm jmp g_RwImageGammaCorrect;
}

extern "C" __declspec(naked) int RwImageMakeMask()
{
	__asm jmp g_RwImageMakeMask;
}

extern "C" __declspec(naked) int RwImageRead()
{
	__asm jmp g_RwImageRead;
}

extern "C" __declspec(naked) int RwImageReadMaskedImage()
{
	__asm jmp g_RwImageReadMaskedImage;
}

extern "C" __declspec(naked) int RwImageResample()
{
	__asm jmp g_RwImageResample;
}

extern "C" __declspec(naked) int RwImageSetFromRaster()
{
	__asm jmp g_RwImageSetFromRaster;
}

extern "C" __declspec(naked) int RwImageSetGamma()
{
	__asm jmp g_RwImageSetGamma;
}

extern "C" __declspec(naked) int RwImageSetPath()
{
	__asm jmp g_RwImageSetPath;
}

extern "C" __declspec(naked) int RwMatrixCreate()
{
	__asm jmp g_RwMatrixCreate;
}

extern "C" __declspec(naked) int RwMatrixDestroy()
{
	__asm jmp g_RwMatrixDestroy;
}

extern "C" __declspec(naked) int RwMatrixInvert()
{
	__asm jmp g_RwMatrixInvert;
}

extern "C" __declspec(naked) int RwMatrixMultiply()
{
	__asm jmp g_RwMatrixMultiply;
}

extern "C" __declspec(naked) int RwMatrixOptimize()
{
	__asm jmp g_RwMatrixOptimize;
}

extern "C" __declspec(naked) int RwMatrixRotate()
{
	__asm jmp g_RwMatrixRotate;
}

extern "C" __declspec(naked) int RwMatrixRotateOneMinusCosineSine()
{
	__asm jmp g_RwMatrixRotateOneMinusCosineSine;
}

extern "C" __declspec(naked) int RwMatrixScale()
{
	__asm jmp g_RwMatrixScale;
}

extern "C" __declspec(naked) int RwMatrixTransform()
{
	__asm jmp g_RwMatrixTransform;
}

extern "C" __declspec(naked) int RwMatrixTranslate()
{
	__asm jmp g_RwMatrixTranslate;
}

extern "C" __declspec(naked) int RwMatrixUpdate()
{
	__asm jmp g_RwMatrixUpdate;
}

extern "C" __declspec(naked) int RwMemLittleEndian32()
{
	__asm jmp g_RwMemLittleEndian32;
}

extern "C" __declspec(naked) int RwOsGetFileInterface()
{
	__asm jmp g_RwOsGetFileInterface;
}

extern "C" __declspec(naked) int RwRasterCreate()
{
	__asm jmp g_RwRasterCreate;
}

extern "C" __declspec(naked) int RwRasterDestroy()
{
	__asm jmp g_RwRasterDestroy;
}

extern "C" __declspec(naked) int RwRasterGetCurrentContext()
{
	__asm jmp g_RwRasterGetCurrentContext;
}

extern "C" __declspec(naked) int RwRasterGetNumLevels()
{
	__asm jmp g_RwRasterGetNumLevels;
}

extern "C" __declspec(naked) int RwRasterLock()
{
	__asm jmp g_RwRasterLock;
}

extern "C" __declspec(naked) int RwRasterLockPalette()
{
	__asm jmp g_RwRasterLockPalette;
}

extern "C" __declspec(naked) int RwRasterPopContext()
{
	__asm jmp g_RwRasterPopContext;
}

extern "C" __declspec(naked) int RwRasterPushContext()
{
	__asm jmp g_RwRasterPushContext;
}

extern "C" __declspec(naked) int RwRasterRegisterPlugin()
{
	__asm jmp g_RwRasterRegisterPlugin;
}

extern "C" __declspec(naked) int RwRasterRenderFast()
{
	__asm jmp g_RwRasterRenderFast;
}

extern "C" __declspec(naked) int RwRasterSetFromImage()
{
	__asm jmp g_RwRasterSetFromImage;
}

extern "C" __declspec(naked) int RwRasterShowRaster()
{
	__asm jmp g_RwRasterShowRaster;
}

extern "C" __declspec(naked) int RwRasterUnlock()
{
	__asm jmp g_RwRasterUnlock;
}

extern "C" __declspec(naked) int RwRasterUnlockPalette()
{
	__asm jmp g_RwRasterUnlockPalette;
}

extern "C" __declspec(naked) int RwRenderStateGet()
{
	__asm jmp g_RwRenderStateGet;
}

extern "C" __declspec(naked) int RwRenderStateSet()
{
	__asm jmp g_RwRenderStateSet;
}

extern "C" __declspec(naked) int RwResourcesAllocateResEntry()
{
	__asm jmp g_RwResourcesAllocateResEntry;
}

extern "C" __declspec(naked) int RwResourcesEmptyArena()
{
	__asm jmp g_RwResourcesEmptyArena;
}

extern "C" __declspec(naked) int RwResourcesFreeResEntry()
{
	__asm jmp g_RwResourcesFreeResEntry;
}

extern "C" __declspec(naked) int RwStreamClose()
{
	__asm jmp g_RwStreamClose;
}

extern "C" __declspec(naked) int RwStreamFindChunk()
{
	__asm jmp g_RwStreamFindChunk;
}

extern "C" __declspec(naked) int RwStreamOpen()
{
	__asm jmp g_RwStreamOpen;
}

extern "C" __declspec(naked) int RwStreamRead()
{
	__asm jmp g_RwStreamRead;
}

extern "C" __declspec(naked) int RwStreamReadInt32()
{
	__asm jmp g_RwStreamReadInt32;
}

extern "C" __declspec(naked) int RwStreamReadReal()
{
	__asm jmp g_RwStreamReadReal;
}

extern "C" __declspec(naked) int RwStreamSkip()
{
	__asm jmp g_RwStreamSkip;
}

extern "C" __declspec(naked) int RwStreamWrite()
{
	__asm jmp g_RwStreamWrite;
}

extern "C" __declspec(naked) int RwStreamWriteInt16()
{
	__asm jmp g_RwStreamWriteInt16;
}

extern "C" __declspec(naked) int RwStreamWriteReal()
{
	__asm jmp g_RwStreamWriteReal;
}

extern "C" __declspec(naked) int RwTexDictionaryAddTexture()
{
	__asm jmp g_RwTexDictionaryAddTexture;
}

extern "C" __declspec(naked) int RwTexDictionaryCreate()
{
	__asm jmp g_RwTexDictionaryCreate;
}

extern "C" __declspec(naked) int RwTexDictionaryDestroy()
{
	__asm jmp g_RwTexDictionaryDestroy;
}

extern "C" __declspec(naked) int RwTexDictionaryFindNamedTexture()
{
	__asm jmp g_RwTexDictionaryFindNamedTexture;
}

extern "C" __declspec(naked) int RwTexDictionaryForAllTextures()
{
	__asm jmp g_RwTexDictionaryForAllTextures;
}

extern "C" __declspec(naked) int RwTexDictionaryGetCurrent()
{
	__asm jmp g_RwTexDictionaryGetCurrent;
}

extern "C" __declspec(naked) int RwTexDictionarySetCurrent()
{
	__asm jmp g_RwTexDictionarySetCurrent;
}

extern "C" __declspec(naked) int RwTexDictionaryStreamRead()
{
	__asm jmp g_RwTexDictionaryStreamRead;
}

extern "C" __declspec(naked) int RwTexDictionaryStreamWrite()
{
	__asm jmp g_RwTexDictionaryStreamWrite;
}

extern "C" __declspec(naked) int RwTextureCreate()
{
	__asm jmp g_RwTextureCreate;
}

extern "C" __declspec(naked) int RwTextureDestroy()
{
	__asm jmp g_RwTextureDestroy;
}

extern "C" __declspec(naked) int RwTextureGetFindCallBack()
{
	__asm jmp g_RwTextureGetFindCallBack;
}

extern "C" __declspec(naked) int RwTextureGetMipmapping()
{
	__asm jmp g_RwTextureGetMipmapping;
}

extern "C" __declspec(naked) int RwTextureRasterGenerateMipmaps()
{
	__asm jmp g_RwTextureRasterGenerateMipmaps;
}

extern "C" __declspec(naked) int RwTextureRead()
{
	__asm jmp g_RwTextureRead;
}

extern "C" __declspec(naked) int RwTextureRegisterPlugin()
{
	__asm jmp g_RwTextureRegisterPlugin;
}

extern "C" __declspec(naked) int RwTextureSetFindCallBack()
{
	__asm jmp g_RwTextureSetFindCallBack;
}

extern "C" __declspec(naked) int RwTextureSetMaskName()
{
	__asm jmp g_RwTextureSetMaskName;
}

extern "C" __declspec(naked) int RwTextureSetMipmapping()
{
	__asm jmp g_RwTextureSetMipmapping;
}

extern "C" __declspec(naked) int RwTextureSetName()
{
	__asm jmp g_RwTextureSetName;
}

extern "C" __declspec(naked) int RwTextureSetRaster()
{
	__asm jmp g_RwTextureSetRaster;
}

extern "C" __declspec(naked) int RwTextureStreamGetSize()
{
	__asm jmp g_RwTextureStreamGetSize;
}

extern "C" __declspec(naked) int RwTextureStreamRead()
{
	__asm jmp g_RwTextureStreamRead;
}

extern "C" __declspec(naked) int RwTextureStreamWrite()
{
	__asm jmp g_RwTextureStreamWrite;
}

extern "C" __declspec(naked) int RwV3dLength()
{
	__asm jmp g_RwV3dLength;
}

extern "C" __declspec(naked) int RwV3dNormalize()
{
	__asm jmp g_RwV3dNormalize;
}

extern "C" __declspec(naked) int RwV3dTransformPoints()
{
	__asm jmp g_RwV3dTransformPoints;
}

extern "C" __declspec(naked) int RwV3dTransformVectors()
{
	__asm jmp g_RwV3dTransformVectors;
}

extern "C" __declspec(naked) int RxHeapAlloc()
{
	__asm jmp g_RxHeapAlloc;
}

extern "C" __declspec(naked) int RxHeapCreate()
{
	__asm jmp g_RxHeapCreate;
}

extern "C" __declspec(naked) int RxHeapDestroy()
{
	__asm jmp g_RxHeapDestroy;
}

extern "C" __declspec(naked) int RxHeapFree()
{
	__asm jmp g_RxHeapFree;
}

extern "C" __declspec(naked) int RxLockedPipeAddFragment()
{
	__asm jmp g_RxLockedPipeAddFragment;
}

extern "C" __declspec(naked) int RxLockedPipeUnlock()
{
	__asm jmp g_RxLockedPipeUnlock;
}

extern "C" __declspec(naked) int RxPipelineCreate()
{
	__asm jmp g_RxPipelineCreate;
}

extern "C" __declspec(naked) int RxPipelineExecute()
{
	__asm jmp g_RxPipelineExecute;
}

extern "C" __declspec(naked) int RxPipelineFindNodeByName()
{
	__asm jmp g_RxPipelineFindNodeByName;
}

extern "C" __declspec(naked) int _RwD3D8CurrentRasterTarget()
{
	__asm jmp g__RwD3D8CurrentRasterTarget;
}

extern "C" __declspec(naked) int _RwD3D8RasterExtOffset()
{
	__asm jmp g__RwD3D8RasterExtOffset;
}

extern "C" __declspec(naked) int _RwD3DAdapterIndex()
{
	__asm jmp g__RwD3DAdapterIndex;
}

extern "C" __declspec(naked) int _RwD3DAdapterType()
{
	__asm jmp g__RwD3DAdapterType;
}

extern "C" __declspec(naked) int _RwD3DDevice()
{
	__asm jmp g__RwD3DDevice;
}

extern "C" __declspec(naked) int _RwDirect3DObject()
{
	__asm jmp g__RwDirect3DObject;
}

extern "C" __declspec(naked) int _rpAtomicResyncInterpolatedSphere()
{
	__asm jmp g__rpAtomicResyncInterpolatedSphere;
}

extern "C" __declspec(naked) int _rpBuildMeshAddTriangle()
{
	__asm jmp g__rpBuildMeshAddTriangle;
}

extern "C" __declspec(naked) int _rpBuildMeshCreate()
{
	__asm jmp g__rpBuildMeshCreate;
}

extern "C" __declspec(naked) int _rpBuildMeshDestroy()
{
	__asm jmp g__rpBuildMeshDestroy;
}

extern "C" __declspec(naked) int _rpClumpClose()
{
	__asm jmp g__rpClumpClose;
}

extern "C" __declspec(naked) int _rpClumpRegisterExtensions()
{
	__asm jmp g__rpClumpRegisterExtensions;
}

extern "C" __declspec(naked) int _rpCreatePlatformAtomicPipelines()
{
	__asm jmp g__rpCreatePlatformAtomicPipelines;
}

extern "C" __declspec(naked) int _rpCreatePlatformWorldSectorPipelines()
{
	__asm jmp g__rpCreatePlatformWorldSectorPipelines;
}

extern "C" __declspec(naked) int _rpD3D8LightConstructor()
{
	__asm jmp g__rpD3D8LightConstructor;
}

extern "C" __declspec(naked) int _rpD3D8LightCopy()
{
	__asm jmp g__rpD3D8LightCopy;
}

extern "C" __declspec(naked) int _rpD3D8LightPluginAttach()
{
	__asm jmp g__rpD3D8LightPluginAttach;
}

extern "C" __declspec(naked) int _rpD3D8SkinGenericMatrixBlend1Matrix()
{
	__asm jmp g__rpD3D8SkinGenericMatrixBlend1Matrix;
}

extern "C" __declspec(naked) int _rpD3D8SkinGenericMatrixBlend1Weight()
{
	__asm jmp g__rpD3D8SkinGenericMatrixBlend1Weight;
}

extern "C" __declspec(naked) int _rpDestroyPlatformAtomicPipelines()
{
	__asm jmp g__rpDestroyPlatformAtomicPipelines;
}

extern "C" __declspec(naked) int _rpDestroyPlatformWorldSectorPipelines()
{
	__asm jmp g__rpDestroyPlatformWorldSectorPipelines;
}

extern "C" __declspec(naked) int _rpGeometryAddRef()
{
	__asm jmp g__rpGeometryAddRef;
}

extern "C" __declspec(naked) int _rpGeometryNativeRead()
{
	__asm jmp g__rpGeometryNativeRead;
}

extern "C" __declspec(naked) int _rpGeometryOpen()
{
	__asm jmp g__rpGeometryOpen;
}

extern "C" __declspec(naked) int _rpLightClose()
{
	__asm jmp g__rpLightClose;
}

extern "C" __declspec(naked) int _rpLightTieDestroy()
{
	__asm jmp g__rpLightTieDestroy;
}

extern "C" __declspec(naked) int _rpMatFXD3D8AtomicMatFXBumpMapRender()
{
	__asm jmp g__rpMatFXD3D8AtomicMatFXBumpMapRender;
}

extern "C" __declspec(naked) int _rpMatFXD3D8AtomicMatFXDefaultRender()
{
	__asm jmp g__rpMatFXD3D8AtomicMatFXDefaultRender;
}

extern "C" __declspec(naked) int _rpMatFXD3D8AtomicMatFXDualPassRender()
{
	__asm jmp g__rpMatFXD3D8AtomicMatFXDualPassRender;
}

extern "C" __declspec(naked) int _rpMatFXD3D8AtomicMatFXEnvRender()
{
	__asm jmp g__rpMatFXD3D8AtomicMatFXEnvRender;
}

extern "C" __declspec(naked) int _rpMatFXD3D8AtomicMatFXRenderBlack()
{
	__asm jmp g__rpMatFXD3D8AtomicMatFXRenderBlack;
}

extern "C" __declspec(naked) int _rpMatFXPipelineAtomicSetup()
{
	__asm jmp g__rpMatFXPipelineAtomicSetup;
}

extern "C" __declspec(naked) int _rpMatFXPipelinesCreate()
{
	__asm jmp g__rpMatFXPipelinesCreate;
}

extern "C" __declspec(naked) int _rpMatFXPipelinesDestroy()
{
	__asm jmp g__rpMatFXPipelinesDestroy;
}

extern "C" __declspec(naked) int _rpMatFXTextureMaskCreate()
{
	__asm jmp g__rpMatFXTextureMaskCreate;
}

extern "C" __declspec(naked) int _rpMaterialListAppendMaterial()
{
	__asm jmp g__rpMaterialListAppendMaterial;
}

extern "C" __declspec(naked) int _rpMaterialListDeinitialize()
{
	__asm jmp g__rpMaterialListDeinitialize;
}

extern "C" __declspec(naked) int _rpMaterialListFindMaterialIndex()
{
	__asm jmp g__rpMaterialListFindMaterialIndex;
}

extern "C" __declspec(naked) int _rpMaterialListGetMaterial()
{
	__asm jmp g__rpMaterialListGetMaterial;
}

extern "C" __declspec(naked) int _rpMaterialListInitialize()
{
	__asm jmp g__rpMaterialListInitialize;
}

extern "C" __declspec(naked) int _rpMaterialSetDefaultSurfaceProperties()
{
	__asm jmp g__rpMaterialSetDefaultSurfaceProperties;
}

extern "C" __declspec(naked) int _rpMeshClose()
{
	__asm jmp g__rpMeshClose;
}

extern "C" __declspec(naked) int _rpMeshDestroy()
{
	__asm jmp g__rpMeshDestroy;
}

extern "C" __declspec(naked) int _rpMeshHeaderForAllMeshes()
{
	__asm jmp g__rpMeshHeaderForAllMeshes;
}

extern "C" __declspec(naked) int _rpMeshOptimise()
{
	__asm jmp g__rpMeshOptimise;
}

extern "C" __declspec(naked) int _rpMeshRead()
{
	__asm jmp g__rpMeshRead;
}

extern "C" __declspec(naked) int _rpMeshSize()
{
	__asm jmp g__rpMeshSize;
}

extern "C" __declspec(naked) int _rpMeshWrite()
{
	__asm jmp g__rpMeshWrite;
}

extern "C" __declspec(naked) int _rpSkinD3D8CreatePlainPipe()
{
	__asm jmp g__rpSkinD3D8CreatePlainPipe;
}

extern "C" __declspec(naked) int _rpSkinGeometryNativeWrite()
{
	__asm jmp g__rpSkinGeometryNativeWrite;
}

extern "C" __declspec(naked) int _rpSkinInitialize()
{
	__asm jmp g__rpSkinInitialize;
}

extern "C" __declspec(naked) int _rpSkinIntelSSEMatrixBlend()
{
	__asm jmp g__rpSkinIntelSSEMatrixBlend;
}

extern "C" __declspec(naked) int _rpSkinIntelSSEMatrixBlend1Matrix()
{
	__asm jmp g__rpSkinIntelSSEMatrixBlend1Matrix;
}

extern "C" __declspec(naked) int _rpSkinIntelSSEMatrixBlend1Weight()
{
	__asm jmp g__rpSkinIntelSSEMatrixBlend1Weight;
}

extern "C" __declspec(naked) int _rpSkinIntelSSEMatrixBlend2Weights()
{
	__asm jmp g__rpSkinIntelSSEMatrixBlend2Weights;
}

extern "C" __declspec(naked) int _rpSkinPipelinesCreate()
{
	__asm jmp g__rpSkinPipelinesCreate;
}

extern "C" __declspec(naked) int _rpSkinPrepareAtomicMatrix()
{
	__asm jmp g__rpSkinPrepareAtomicMatrix;
}

extern "C" __declspec(naked) int _rpSkinSplitDataStreamGetSize()
{
	__asm jmp g__rpSkinSplitDataStreamGetSize;
}

extern "C" __declspec(naked) int _rpSkinSplitDataStreamRead()
{
	__asm jmp g__rpSkinSplitDataStreamRead;
}

extern "C" __declspec(naked) int _rpSkinSplitDataStreamWrite()
{
	__asm jmp g__rpSkinSplitDataStreamWrite;
}

extern "C" __declspec(naked) int _rpTieDestroy()
{
	__asm jmp g__rpTieDestroy;
}

extern "C" __declspec(naked) int _rpTriListMeshGenerate()
{
	__asm jmp g__rpTriListMeshGenerate;
}

extern "C" __declspec(naked) int _rpWorldObjRegisterExtensions()
{
	__asm jmp g__rpWorldObjRegisterExtensions;
}

extern "C" __declspec(naked) int _rpWorldSectorNativeRead()
{
	__asm jmp g__rpWorldSectorNativeRead;
}

extern "C" __declspec(naked) int _rpWorldSectorNativeSize()
{
	__asm jmp g__rpWorldSectorNativeSize;
}

extern "C" __declspec(naked) int _rpWorldSectorNativeWrite()
{
	__asm jmp g__rpWorldSectorNativeWrite;
}

extern "C" __declspec(naked) int _rwCPUHave3DNow()
{
	__asm jmp g__rwCPUHave3DNow;
}

extern "C" __declspec(naked) int _rwCPUHaveMMX()
{
	__asm jmp g__rwCPUHaveMMX;
}

extern "C" __declspec(naked) int _rwCPUHaveSSE()
{
	__asm jmp g__rwCPUHaveSSE;
}

extern "C" __declspec(naked) int _rwCPUHaveSSE2()
{
	__asm jmp g__rwCPUHaveSSE2;
}

extern "C" __declspec(naked) int _rwD3D8AtomicDefaultLightingCallback()
{
	__asm jmp g__rwD3D8AtomicDefaultLightingCallback;
}

extern "C" __declspec(naked) int _rwD3D8AtomicMatFXRenderCallback()
{
	__asm jmp g__rwD3D8AtomicMatFXRenderCallback;
}

extern "C" __declspec(naked) int _rwD3D8CameraBeginUpdate()
{
	__asm jmp g__rwD3D8CameraBeginUpdate;
}

extern "C" __declspec(naked) int _rwD3D8CameraClear()
{
	__asm jmp g__rwD3D8CameraClear;
}

extern "C" __declspec(naked) int _rwD3D8CameraEndUpdate()
{
	__asm jmp g__rwD3D8CameraEndUpdate;
}

extern "C" __declspec(naked) int _rwD3D8CheckRasterSize()
{
	__asm jmp g__rwD3D8CheckRasterSize;
}

extern "C" __declspec(naked) int _rwD3D8DecompressDXT1()
{
	__asm jmp g__rwD3D8DecompressDXT1;
}

extern "C" __declspec(naked) int _rwD3D8DecompressDXT3()
{
	__asm jmp g__rwD3D8DecompressDXT3;
}

extern "C" __declspec(naked) int _rwD3D8DecompressDXT5()
{
	__asm jmp g__rwD3D8DecompressDXT5;
}

extern "C" __declspec(naked) int _rwD3D8Im2DRenderClose()
{
	__asm jmp g__rwD3D8Im2DRenderClose;
}

extern "C" __declspec(naked) int _rwD3D8Im2DRenderIndexedPrimitive()
{
	__asm jmp g__rwD3D8Im2DRenderIndexedPrimitive;
}

extern "C" __declspec(naked) int _rwD3D8Im2DRenderLine()
{
	__asm jmp g__rwD3D8Im2DRenderLine;
}

extern "C" __declspec(naked) int _rwD3D8Im2DRenderOpen()
{
	__asm jmp g__rwD3D8Im2DRenderOpen;
}

extern "C" __declspec(naked) int _rwD3D8Im2DRenderTriangle()
{
	__asm jmp g__rwD3D8Im2DRenderTriangle;
}

extern "C" __declspec(naked) int _rwD3D8Im3DRenderClose()
{
	__asm jmp g__rwD3D8Im3DRenderClose;
}

extern "C" __declspec(naked) int _rwD3D8Im3DRenderOpen()
{
	__asm jmp g__rwD3D8Im3DRenderOpen;
}

extern "C" __declspec(naked) int _rwD3D8ImageFindRasterFormat()
{
	__asm jmp g__rwD3D8ImageFindRasterFormat;
}

extern "C" __declspec(naked) int _rwD3D8ImageGetFromRaster()
{
	__asm jmp g__rwD3D8ImageGetFromRaster;
}

extern "C" __declspec(naked) int _rwD3D8NativeTextureGetSize()
{
	__asm jmp g__rwD3D8NativeTextureGetSize;
}

extern "C" __declspec(naked) int _rwD3D8NativeTextureRead()
{
	__asm jmp g__rwD3D8NativeTextureRead;
}

extern "C" __declspec(naked) int _rwD3D8NativeTextureWrite()
{
	__asm jmp g__rwD3D8NativeTextureWrite;
}

extern "C" __declspec(naked) int _rwD3D8PixelToRGB()
{
	__asm jmp g__rwD3D8PixelToRGB;
}

extern "C" __declspec(naked) int _rwD3D8RWGetRasterStage()
{
	__asm jmp g__rwD3D8RWGetRasterStage;
}

extern "C" __declspec(naked) int _rwD3D8RWGetRenderState()
{
	__asm jmp g__rwD3D8RWGetRenderState;
}

extern "C" __declspec(naked) int _rwD3D8RWSetRasterStage()
{
	__asm jmp g__rwD3D8RWSetRasterStage;
}

extern "C" __declspec(naked) int _rwD3D8RasterClear()
{
	__asm jmp g__rwD3D8RasterClear;
}

extern "C" __declspec(naked) int _rwD3D8RasterClearRect()
{
	__asm jmp g__rwD3D8RasterClearRect;
}

extern "C" __declspec(naked) int _rwD3D8RasterCreate()
{
	__asm jmp g__rwD3D8RasterCreate;
}

extern "C" __declspec(naked) int _rwD3D8RasterDestroy()
{
	__asm jmp g__rwD3D8RasterDestroy;
}

extern "C" __declspec(naked) int _rwD3D8RasterGetMipLevels()
{
	__asm jmp g__rwD3D8RasterGetMipLevels;
}

extern "C" __declspec(naked) int _rwD3D8RasterLock()
{
	__asm jmp g__rwD3D8RasterLock;
}

extern "C" __declspec(naked) int _rwD3D8RasterLockPalette()
{
	__asm jmp g__rwD3D8RasterLockPalette;
}

extern "C" __declspec(naked) int _rwD3D8RasterPluginAttach()
{
	__asm jmp g__rwD3D8RasterPluginAttach;
}

extern "C" __declspec(naked) int _rwD3D8RasterRender()
{
	__asm jmp g__rwD3D8RasterRender;
}

extern "C" __declspec(naked) int _rwD3D8RasterRenderFast()
{
	__asm jmp g__rwD3D8RasterRenderFast;
}

extern "C" __declspec(naked) int _rwD3D8RasterRenderScaled()
{
	__asm jmp g__rwD3D8RasterRenderScaled;
}

extern "C" __declspec(naked) int _rwD3D8RasterSetFromImage()
{
	__asm jmp g__rwD3D8RasterSetFromImage;
}

extern "C" __declspec(naked) int _rwD3D8RasterShowRaster()
{
	__asm jmp g__rwD3D8RasterShowRaster;
}

extern "C" __declspec(naked) int _rwD3D8RasterSubRaster()
{
	__asm jmp g__rwD3D8RasterSubRaster;
}

extern "C" __declspec(naked) int _rwD3D8RasterUnlock()
{
	__asm jmp g__rwD3D8RasterUnlock;
}

extern "C" __declspec(naked) int _rwD3D8RasterUnlockPalette()
{
	__asm jmp g__rwD3D8RasterUnlockPalette;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateDestBlend()
{
	__asm jmp g__rwD3D8RenderStateDestBlend;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateFlushCache()
{
	__asm jmp g__rwD3D8RenderStateFlushCache;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateIsVertexAlphaEnable()
{
	__asm jmp g__rwD3D8RenderStateIsVertexAlphaEnable;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateSrcBlend()
{
	__asm jmp g__rwD3D8RenderStateSrcBlend;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateTextureFilter()
{
	__asm jmp g__rwD3D8RenderStateTextureFilter;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateVertexAlphaEnable()
{
	__asm jmp g__rwD3D8RenderStateVertexAlphaEnable;
}

extern "C" __declspec(naked) int _rwD3D8ResourceEntryInstanceDataDestroy()
{
	__asm jmp g__rwD3D8ResourceEntryInstanceDataDestroy;
}

extern "C" __declspec(naked) int _rwD3D8SetRasterContext()
{
	__asm jmp g__rwD3D8SetRasterContext;
}

extern "C" __declspec(naked) int _rwD3D8SkinNeedsAManagedVertexBuffer()
{
	__asm jmp g__rwD3D8SkinNeedsAManagedVertexBuffer;
}

extern "C" __declspec(naked) int _rwD3D8TextureHasAlpha()
{
	__asm jmp g__rwD3D8TextureHasAlpha;
}

extern "C" __declspec(naked) int _rwD3D8TextureSetRaster()
{
	__asm jmp g__rwD3D8TextureSetRaster;
}

extern "C" __declspec(naked) int _rwD3D8CheckValidCameraTextureFormat()
{
	__asm jmp g__rwD3D8CheckValidCameraTextureFormat;
}

extern "C" __declspec(naked) int _rwD3D8CheckValidTextureFormat()
{
	__asm jmp g__rwD3D8CheckValidTextureFormat;
}

extern "C" __declspec(naked) int _rwD3D8CheckValidZBufferFormat()
{
	__asm jmp g__rwD3D8CheckValidZBufferFormat;
}

extern "C" __declspec(naked) int _rwD3D8Im2DRenderPrimitive()
{
	__asm jmp g__rwD3D8Im2DRenderPrimitive;
}

extern "C" __declspec(naked) int _rwD3D8ImageFindFormat()
{
	__asm jmp g__rwD3D8ImageFindFormat;
}

extern "C" __declspec(naked) int _rwD3D8LightLocalEnable()
{
	__asm jmp g__rwD3D8LightLocalEnable;
}

extern "C" __declspec(naked) int _rwD3D8LightsEnable()
{
	__asm jmp g__rwD3D8LightsEnable;
}

extern "C" __declspec(naked) int _rwD3D8LightsEqual()
{
	__asm jmp g__rwD3D8LightsEqual;
}

extern "C" __declspec(naked) int _rwD3D8LightsGlobalEnable()
{
	__asm jmp g__rwD3D8LightsGlobalEnable;
}

extern "C" __declspec(naked) int _rwD3D8MatrixMultiplyTranspose()
{
	__asm jmp g__rwD3D8MatrixMultiplyTranspose;
}

extern "C" __declspec(naked) int _rwD3D8MeshGetNumVerticesMinIndex()
{
	__asm jmp g__rwD3D8MeshGetNumVerticesMinIndex;
}

extern "C" __declspec(naked) int _rwD3D8RGBToPixel()
{
	__asm jmp g__rwD3D8RGBToPixel;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilEnable()
{
	__asm jmp g__rwD3D8RenderStateStencilEnable;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilFail()
{
	__asm jmp g__rwD3D8RenderStateStencilFail;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilFunction()
{
	__asm jmp g__rwD3D8RenderStateStencilFunction;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilFunctionMask()
{
	__asm jmp g__rwD3D8RenderStateStencilFunctionMask;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilFunctionRef()
{
	__asm jmp g__rwD3D8RenderStateStencilFunctionRef;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilFunctionWriteMask()
{
	__asm jmp g__rwD3D8RenderStateStencilFunctionWriteMask;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilPass()
{
	__asm jmp g__rwD3D8RenderStateStencilPass;
}

extern "C" __declspec(naked) int _rwD3D8RenderStateStencilZFail()
{
	__asm jmp g__rwD3D8RenderStateStencilZFail;
}

extern "C" __declspec(naked) int _rwDeviceRegisterPlugin()
{
	__asm jmp g__rwDeviceRegisterPlugin;
}

extern "C" __declspec(naked) int _rwDeviceSystemRequest()
{
	__asm jmp g__rwDeviceSystemRequest;
}

extern "C" __declspec(naked) int _rwErrorOpen()
{
	__asm jmp g__rwErrorOpen;
}

extern "C" __declspec(naked) int _rwFrameCloneAndLinkClones()
{
	__asm jmp g__rwFrameCloneAndLinkClones;
}

extern "C" __declspec(naked) int _rwFrameListDeinitialize()
{
	__asm jmp g__rwFrameListDeinitialize;
}

extern "C" __declspec(naked) int _rwFrameListStreamRead()
{
	__asm jmp g__rwFrameListStreamRead;
}

extern "C" __declspec(naked) int _rwFramePurgeClone()
{
	__asm jmp g__rwFramePurgeClone;
}

extern "C" __declspec(naked) int _rwFrameSyncDirty()
{
	__asm jmp g__rwFrameSyncDirty;
}

extern "C" __declspec(naked) int _rwFrameSyncHierarchyLTM()
{
	__asm jmp g__rwFrameSyncHierarchyLTM;
}

extern "C" __declspec(naked) int _rwIm3DClose()
{
	__asm jmp g__rwIm3DClose;
}

extern "C" __declspec(naked) int _rwIm3DCreatePlatformRenderPipelines()
{
	__asm jmp g__rwIm3DCreatePlatformRenderPipelines;
}

extern "C" __declspec(naked) int _rwIm3DCreatePlatformTransformPipeline()
{
	__asm jmp g__rwIm3DCreatePlatformTransformPipeline;
}

extern "C" __declspec(naked) int _rwIm3DDestroyPlatformRenderPipelines()
{
	__asm jmp g__rwIm3DDestroyPlatformRenderPipelines;
}

extern "C" __declspec(naked) int _rwIm3DDestroyPlatformTransformPipeline()
{
	__asm jmp g__rwIm3DDestroyPlatformTransformPipeline;
}

extern "C" __declspec(naked) int _rwIm3DOpen()
{
	__asm jmp g__rwIm3DOpen;
}

extern "C" __declspec(naked) int _rwImageClose()
{
	__asm jmp g__rwImageClose;
}

extern "C" __declspec(naked) int _rwInvSqrt()
{
	__asm jmp g__rwInvSqrt;
}

extern "C" __declspec(naked) int _rwMatrixDeterminant()
{
	__asm jmp g__rwMatrixDeterminant;
}

extern "C" __declspec(naked) int _rwMatrixIdentityError()
{
	__asm jmp g__rwMatrixIdentityError;
}

extern "C" __declspec(naked) int _rwMatrixNormalError()
{
	__asm jmp g__rwMatrixNormalError;
}

extern "C" __declspec(naked) int _rwMatrixOrthogonalError()
{
	__asm jmp g__rwMatrixOrthogonalError;
}

extern "C" __declspec(naked) int _rwMatrixSetMultFn()
{
	__asm jmp g__rwMatrixSetMultFn;
}

extern "C" __declspec(naked) int _rwMemoryClose()
{
	__asm jmp g__rwMemoryClose;
}

extern "C" __declspec(naked) int _rwMemoryOpen()
{
	__asm jmp g__rwMemoryOpen;
}

extern "C" __declspec(naked) int _rwObjectHasFrameReleaseFrame()
{
	__asm jmp g__rwObjectHasFrameReleaseFrame;
}

extern "C" __declspec(naked) int _rwObjectHasFrameSetFrame()
{
	__asm jmp g__rwObjectHasFrameSetFrame;
}

extern "C" __declspec(naked) int _rwPalQuantAddImage()
{
	__asm jmp g__rwPalQuantAddImage;
}

extern "C" __declspec(naked) int _rwPalQuantInit()
{
	__asm jmp g__rwPalQuantInit;
}

extern "C" __declspec(naked) int _rwPalQuantMatchImage()
{
	__asm jmp g__rwPalQuantMatchImage;
}

extern "C" __declspec(naked) int _rwPalQuantResolvePalette()
{
	__asm jmp g__rwPalQuantResolvePalette;
}

extern "C" __declspec(naked) int _rwPalQuantTerm()
{
	__asm jmp g__rwPalQuantTerm;
}

extern "C" __declspec(naked) int _rwPluginRegistryAddPlgnStrmRightsCB()
{
	__asm jmp g__rwPluginRegistryAddPlgnStrmRightsCB;
}

extern "C" __declspec(naked) int _rwPluginRegistryAddPlgnStrmlwysCB()
{
	__asm jmp g__rwPluginRegistryAddPlgnStrmlwysCB;
}

extern "C" __declspec(naked) int _rwPluginRegistryAddPlugin()
{
	__asm jmp g__rwPluginRegistryAddPlugin;
}

extern "C" __declspec(naked) int _rwPluginRegistryAddPluginStream()
{
	__asm jmp g__rwPluginRegistryAddPluginStream;
}

extern "C" __declspec(naked) int _rwPluginRegistryClose()
{
	__asm jmp g__rwPluginRegistryClose;
}

extern "C" __declspec(naked) int _rwPluginRegistryCopyObject()
{
	__asm jmp g__rwPluginRegistryCopyObject;
}

extern "C" __declspec(naked) int _rwPluginRegistryDeInitObject()
{
	__asm jmp g__rwPluginRegistryDeInitObject;
}

extern "C" __declspec(naked) int _rwPluginRegistryGetPluginOffset()
{
	__asm jmp g__rwPluginRegistryGetPluginOffset;
}

extern "C" __declspec(naked) int _rwPluginRegistryGetSize()
{
	__asm jmp g__rwPluginRegistryGetSize;
}

extern "C" __declspec(naked) int _rwPluginRegistryInitObject()
{
	__asm jmp g__rwPluginRegistryInitObject;
}

extern "C" __declspec(naked) int _rwPluginRegistryInvokeRights()
{
	__asm jmp g__rwPluginRegistryInvokeRights;
}

extern "C" __declspec(naked) int _rwPluginRegistrySkipDataChunks()
{
	__asm jmp g__rwPluginRegistrySkipDataChunks;
}

extern "C" __declspec(naked) int _rwPluginRegistryWriteDataChunks()
{
	__asm jmp g__rwPluginRegistryWriteDataChunks;
}

extern "C" __declspec(naked) int _rwRasterClose()
{
	__asm jmp g__rwRasterClose;
}

extern "C" __declspec(naked) int _rwRasterOpen()
{
	__asm jmp g__rwRasterOpen;
}

extern "C" __declspec(naked) int _rwRenderPipelineClose()
{
	__asm jmp g__rwRenderPipelineClose;
}

extern "C" __declspec(naked) int _rwRenderPipelineOpen()
{
	__asm jmp g__rwRenderPipelineOpen;
}

extern "C" __declspec(naked) int _rwResHeapAlloc()
{
	__asm jmp g__rwResHeapAlloc;
}

extern "C" __declspec(naked) int _rwResHeapFree()
{
	__asm jmp g__rwResHeapFree;
}

extern "C" __declspec(naked) int _rwResHeapInit()
{
	__asm jmp g__rwResHeapInit;
}

extern "C" __declspec(naked) int _rwResourcesClose()
{
	__asm jmp g__rwResourcesClose;
}

extern "C" __declspec(naked) int _rwResourcesOpen()
{
	__asm jmp g__rwResourcesOpen;
}

extern "C" __declspec(naked) int _rwResourcesPurge()
{
	__asm jmp g__rwResourcesPurge;
}

extern "C" __declspec(naked) int _rwSkinD3D8AtomicAllInOneNode()
{
	__asm jmp g__rwSkinD3D8AtomicAllInOneNode;
}

extern "C" __declspec(naked) int _rwSqrt()
{
	__asm jmp g__rwSqrt;
}

extern "C" __declspec(naked) int _rwStreamModuleClose()
{
	__asm jmp g__rwStreamModuleClose;
}

extern "C" __declspec(naked) int _rwStreamReadChunkHeader()
{
	__asm jmp g__rwStreamReadChunkHeader;
}

extern "C" __declspec(naked) int _rwStreamWriteVersionedChunkHeader()
{
	__asm jmp g__rwStreamWriteVersionedChunkHeader;
}

extern "C" __declspec(naked) int _rwStringOpen()
{
	__asm jmp g__rwStringOpen;
}

extern "C" __declspec(naked) int _rwStringOpen_0()
{
	__asm jmp g__rwStringOpen_0;
}

extern "C" __declspec(naked) int _rwTextureClose()
{
	__asm jmp g__rwTextureClose;
}

extern "C" __declspec(naked) int _rwVectorClose()
{
	__asm jmp g__rwVectorClose;
}

extern "C" __declspec(naked) int _rwVectorOpen()
{
	__asm jmp g__rwVectorOpen;
}

extern "C" __declspec(naked) int _rwVectorSetMultFn()
{
	__asm jmp g__rwVectorSetMultFn;
}

extern "C" __declspec(naked) int _rwerror()
{
	__asm jmp g__rwerror;
}

extern "C" __declspec(naked) int _rwpathisabsolute()
{
	__asm jmp g__rwpathisabsolute;
}

extern "C" __declspec(naked) int _rxChaseDependencies()
{
	__asm jmp g__rxChaseDependencies;
}

extern "C" __declspec(naked) int _rxD3D8DefaultRenderCallback()
{
	__asm jmp g__rxD3D8DefaultRenderCallback;
}

extern "C" __declspec(naked) int _rxD3D8Reinstance()
{
	__asm jmp g__rxD3D8Reinstance;
}

extern "C" __declspec(naked) int _rxD3D8SkinAtomicCreateVertexBuffer()
{
	__asm jmp g__rxD3D8SkinAtomicCreateVertexBuffer;
}

extern "C" __declspec(naked) int _rxD3D8SkinGeometryInstanceStaticInfo()
{
	__asm jmp g__rxD3D8SkinGeometryInstanceStaticInfo;
}

extern "C" __declspec(naked) int _rxD3D8VertexBufferManagerClose()
{
	__asm jmp g__rxD3D8VertexBufferManagerClose;
}

extern "C" __declspec(naked) int _rxExecCtxGlobal()
{
	__asm jmp g__rxExecCtxGlobal;
}

extern "C" __declspec(naked) int _rxHeapGlobal()
{
	__asm jmp g__rxHeapGlobal;
}

extern "C" __declspec(naked) int _rxHeapReset()
{
	__asm jmp g__rxHeapReset;
}

extern "C" __declspec(naked) int _rxPacketDestroy()
{
	__asm jmp g__rxPacketDestroy;
}

extern "C" __declspec(naked) int _rxPipelineClose()
{
	__asm jmp g__rxPipelineClose;
}

extern "C" __declspec(naked) int _rxPipelineDestroy()
{
	__asm jmp g__rxPipelineDestroy;
}

extern "C" __declspec(naked) int _rxSkinD3D8AtomicAllInOnePipelineInit()
{
	__asm jmp g__rxSkinD3D8AtomicAllInOnePipelineInit;
}

extern "C" __declspec(naked) int _rx_rxRadixExchangeSort()
{
	__asm jmp g__rx_rxRadixExchangeSort;
}

extern "C" __declspec(naked) int RwD3D8Image32GetFromRaster()
{
	__asm jmp g_RwD3D8Image32GetFromRaster;
}

extern "C" __declspec(naked) int RwD3D8Raster24_32LinearSetFromImage()
{
	__asm jmp g_RwD3D8Raster24_32LinearSetFromImage;
}

extern "C" __declspec(naked) int RwD3D8RasterCopyQuad()
{
	__asm jmp g_RwD3D8RasterCopyQuad;
}

extern "C" __declspec(naked) int RwD3D8RasterCtor()
{
	__asm jmp g_RwD3D8RasterCtor;
}

extern "C" __declspec(naked) int RwD3D8RasterDtor()
{
	__asm jmp g_RwD3D8RasterDtor;
}

extern "C" __declspec(naked) int RwD3D8RasterPalletizedSetFromImage()
{
	__asm jmp g_RwD3D8RasterPalletizedSetFromImage;
}

extern "C" __declspec(naked) int RwD3D8RasterRenderGeneric()
{
	__asm jmp g_RwD3D8RasterRenderGeneric;
}

extern "C" __declspec(naked) int RwD3D8RasterRenderQuad()
{
	__asm jmp g_RwD3D8RasterRenderQuad;
}

extern "C" __declspec(naked) int RwD3D8RenderStateBorderColor()
{
	__asm jmp g_RwD3D8RenderStateBorderColor;
}

extern "C" __declspec(naked) int RwD3D8SelectConvertFn()
{
	__asm jmp g_RwD3D8SelectConvertFn;
}

extern "C" __declspec(naked) int RwD3D8RenderStateCullMode()
{
	__asm jmp g_RwD3D8RenderStateCullMode;
}

extern "C" __declspec(naked) int RwD3D8RenderStateShadeMode()
{
	__asm jmp g_RwD3D8RenderStateShadeMode;
}

extern "C" __declspec(naked) int RwD3D8RenderStateZTestEnable()
{
	__asm jmp g_RwD3D8RenderStateZTestEnable;
}

extern "C" __declspec(naked) int RwD3D8RenderStateZWriteEnable()
{
	__asm jmp g_RwD3D8RenderStateZWriteEnable;
}

extern "C" __declspec(naked) int RwDestroyEntry()
{
	__asm jmp g_RwDestroyEntry;
}

extern "C" __declspec(naked) int RwFrameCloneRecurse()
{
	__asm jmp g_RwFrameCloneRecurse;
}

extern "C" __declspec(naked) int RwFrameDestroyRecurse()
{
	__asm jmp g_RwFrameDestroyRecurse;
}

extern "C" __declspec(naked) int RwFrameInternalInit()
{
	__asm jmp g_RwFrameInternalInit;
}

extern "C" __declspec(naked) int RwFrameOpen()
{
	__asm jmp g_RwFrameOpen;
}

extern "C" __declspec(naked) int RwSetHierarchyRoot()
{
	__asm jmp g_RwSetHierarchyRoot;
}

extern "C" __declspec(naked) int Rwfexist()
{
	__asm jmp g_Rwfexist;
}

extern "C" __declspec(naked) int RxD3D8SubmitNode()
{
	__asm jmp g_RxD3D8SubmitNode;
}