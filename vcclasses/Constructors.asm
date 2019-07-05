.586
.MODEL FLAT
.STACK
.DATA
;=========================================================================
;= External function pointers
;=========================================================================
;#########################################################################
;# CMatrix
;#########################################################################
EXTERN ?g_CMatrix_Constructor_RwMatrix_bool@@3KA:DWORD	; CMatrix::CMatrix(RwMatrix *, bool)
EXTERN ?g_CMatrix_Copy_Constructor@@3KA:DWORD			; CMatrix::CMatrix(const CMatrix &)
EXTERN ?g_CMatrix_Destructor@@3KA:DWORD				; CMatrx::~CMatrix()

;#########################################################################
;# CEntity
;#########################################################################
EXTERN ?g_CEntity_Constructor@@3KA:DWORD	; CEntity::CEntity()
EXTERN ?g_CEntity_Destructor@@3KA:DWORD	; CEntity::~CEntity()

;#########################################################################
;# CPhysical
;#########################################################################
EXTERN ?g_CPhysical_Constructor@@3KA:DWORD	; CPhysical::CPhysical()
EXTERN ?g_CPhysical_Destructor@@3KA:DWORD	; CPhysical::~CPhysical()

;#########################################################################
;# CObject
;#########################################################################
EXTERN ?g_CObject_Constructor@@3KA:DWORD	; CObject::CObject()
EXTERN ?g_CObject_ConstructorWithIntBool@@3KA:DWORD ;CObject::CObject(int,bool)
EXTERN ?g_CObject_Destructor@@3KA:DWORD	; CObject::~CObject()

;#########################################################################
;# CCutsceneObject
;#########################################################################
EXTERN ?g_CCutsceneObject_Constructor@@3KA:DWORD	; CCutsceneObject::CCutsceneObject()
EXTERN ?g_CCutsceneObject_Destructor@@3KA:DWORD	; CCutsceneObject::~CCutsceneObject()

;#########################################################################
;# CAutomobile
;#########################################################################

EXTERN ?g_CAutomobile_Constructor@@3KA:DWORD
EXTERN ?g_CAutomobile_Destructor@@3KA:DWORD

;#########################################################################
;# CPlane
;#########################################################################

EXTERN ?g_CPlane_Constructor@@3KA:DWORD
EXTERN ?g_CPlane_Destructor@@3KA:DWORD

;#########################################################################
;# CBoat
;#########################################################################

EXTERN ?g_CBoat_Constructor@@3KA:DWORD
EXTERN ?g_CBoat_Destructor@@3KA:DWORD

;#########################################################################
;# CBike
;#########################################################################

EXTERN ?g_CBike_Constructor@@3KA:DWORD
EXTERN ?g_CBike_Destructor@@3KA:DWORD

;#########################################################################
;# CSprite2d
;#########################################################################
EXTERN ?g_CSprite2d_Constructor@@3KA:DWORD	; CSprite2d::CSprite2d()
EXTERN ?g_CSprite2d_Destructor@@3KA:DWORD	; CSprite2d::~CSprite2d()

.CODE

;#########################################################################
;# CMatrix
;#########################################################################

;*** CMatrix::CMatrix(RwMatrixTag *, bool)
??0CMatrix@@QAE@PAURwMatrixTag@@_N@Z PROC
	jmp ds:?g_CMatrix_Constructor_RwMatrix_bool@@3KA
??0CMatrix@@QAE@PAURwMatrixTag@@_N@Z ENDP

;*** CMatrix::CMatrix(RwMatrix *, bool)
??0CMatrix@@QAE@PAURwMatrix@@_N@Z PROC
	jmp ds:?g_CMatrix_Constructor_RwMatrix_bool@@3KA
??0CMatrix@@QAE@PAURwMatrix@@_N@Z ENDP

;*** CMatrix::CMatrix(const CMatrix &)
??0CMatrix@@QAE@ABV0@@Z PROC
	jmp ds:?g_CMatrix_Copy_Constructor@@3KA
??0CMatrix@@QAE@ABV0@@Z ENDP

;*** CMatrx::~CMatrix()
??1CMatrix@@QAE@XZ PROC
	jmp ds:?g_CMatrix_Destructor@@3KA
??1CMatrix@@QAE@XZ ENDP

;#########################################################################
;# CEntity
;#########################################################################

;*** CEntity::CEntity()
??0CEntity@@QAE@XZ PROC
	jmp ds:?g_CEntity_Constructor@@3KA 
??0CEntity@@QAE@XZ ENDP

;*** CEntity::~CEntity()
??1CEntity@@UAE@XZ PROC
	jmp ds:?g_CEntity_Destructor@@3KA
??1CEntity@@UAE@XZ ENDP

;#########################################################################
;# CPhysical
;#########################################################################

;*** CPhysical::CPhysical()
??0CPhysical@@QAE@XZ PROC
	jmp ds:?g_CPhysical_Constructor@@3KA 
??0CPhysical@@QAE@XZ ENDP

;*** CPhysical::~CPhysical()
??1CPhysical@@UAE@XZ PROC
	jmp ds:?g_CPhysical_Destructor@@3KA
??1CPhysical@@UAE@XZ ENDP

;#########################################################################
;# CObject
;#########################################################################

;*** CObject::CObject()
??0CObject@@QAE@XZ PROC
	jmp ds:?g_CObject_Constructor@@3KA 
??0CObject@@QAE@XZ ENDP

;*** CObject::CObject(int,bool)
??0CObject@@QAE@H_N@Z PROC
	jmp ds:?g_CObject_ConstructorWithIntBool@@3KA
??0CObject@@QAE@H_N@Z ENDP

;*** CObject::~CObject()
??1CObject@@UAE@XZ PROC
	jmp ds:?g_CObject_Destructor@@3KA
??1CObject@@UAE@XZ ENDP

;#########################################################################
;# CCutsceneObject
;#########################################################################

;*** CCutsceneObject::CCutsceneObject()
??0CCutsceneObject@@QAE@XZ PROC
	jmp ds:?g_CCutsceneObject_Constructor@@3KA 
??0CCutsceneObject@@QAE@XZ ENDP

;*** CCutsceneObject::~CCutsceneObject()
??1CCutsceneObject@@UAE@XZ PROC
	jmp ds:?g_CCutsceneObject_Destructor@@3KA
??1CCutsceneObject@@UAE@XZ ENDP

;#########################################################################
;# CAutomobile
;#########################################################################

;*** CAutomobile::CAutomobile(int, unsigned char)
??0CAutomobile@@QAE@HE@Z PROC
	jmp ds:?g_CAutomobile_Constructor@@3KA 
??0CAutomobile@@QAE@HE@Z ENDP

;*** CAutomobile::~CAutomobile()
??1CAutomobile@@UAE@XZ PROC
	jmp ds:?g_CAutomobile_Destructor@@3KA
??1CAutomobile@@UAE@XZ ENDP

;#########################################################################
;# CPlane
;#########################################################################

;*** CPlane::CPlane()
??0CPlane@@QAE@HE@Z PROC
	jmp ds:?g_CPlane_Constructor@@3KA 
??0CPlane@@QAE@HE@Z ENDP

;*** CPlane::~CPlane()
??1CPlane@@UAE@XZ PROC
	jmp ds:?g_CPlane_Destructor@@3KA
??1CPlane@@UAE@XZ ENDP

;#########################################################################
;# CBoat
;#########################################################################

;*** CBoat::CBoat()
??0CBoat@@QAE@HE@Z PROC
	jmp ds:?g_CBoat_Constructor@@3KA 
??0CBoat@@QAE@HE@Z ENDP

;*** CBoat::~CBoat()
??1CBoat@@UAE@XZ PROC
	jmp ds:?g_CBoat_Destructor@@3KA
??1CBoat@@UAE@XZ ENDP

;#########################################################################
;# CBike
;#########################################################################

;*** CBike::CBike()
??0CBike@@QAE@HE@Z PROC
	jmp ds:?g_CBike_Constructor@@3KA 
??0CBike@@QAE@HE@Z ENDP

;*** CBike::~CBike()
??1CBike@@UAE@XZ PROC
	jmp ds:?g_CBike_Destructor@@3KA
??1CBike@@UAE@XZ ENDP

;#########################################################################
;# CSprite2d
;#########################################################################

;*** CSprite2d::CSprite2d()
??0CSprite2d@@QAE@XZ PROC
	jmp ds:?g_CSprite2d_Constructor@@3KA 
??0CSprite2d@@QAE@XZ ENDP

;*** CSprite2d::~CSprite2d()
??1CSprite2d@@QAE@XZ PROC
	jmp ds:?g_CSprite2d_Destructor@@3KA
??1CSprite2d@@QAE@XZ ENDP

END

