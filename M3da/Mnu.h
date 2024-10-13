// Meshing Menu Class
// for handling meshing commands
#include "stdafx.h"
#include "DBase.h"
#include <stdlib.h>

//root menu


class zMnu
{ 
protected:
  int iCKill;
  int RetVal;
  int iResumePos;
  int iCancelPos;
  zMnu* pNext;
  int iStat;
  int initCnt;
  int S_initCnt;
  int iT;
public:
	DBase* cDBase;
	virtual void DoNext(CString *CInMsg,CPoint Pt);
	virtual void Init(DBase* TheDBase,int iType);
	virtual int DoMenu(CString CInMsg,CPoint Pt);
	virtual int ExtractPt(CString mCInMsg, C3dVector *ReturnPt);
	BOOL isNULL();
};

class zELTYPE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zLMEAS_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zAMEAS_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNDCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zWPMODE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zORTHO_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zKEY_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};



class zLNX_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zLNANG_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELCR_Mnu: public zMnu
{
public:
E_Object* pE;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
}; 

class zELINSSPG_Mnu : public zMnu
{
public:
	E_Object* pE;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
}; 


class zCVCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCVFIT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSUREX_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSURCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSURSWEEP_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zSURBOUND_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

//SOLID SECTION
class zSDSEC_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

//Curve modify line weight thin
class zCVMOLWT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

//Curve modify line weight medium
class zCVMOLWM_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

//Curve modify line weight large
class zCVMOLWL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCVMOSOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCVMODOT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCVMOCTR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCVMODASH_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zFIL_Mnu: public zMnu
{
CPoint PNear1;
CPoint PNear2;
C3dVector vR;
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCORNER_Mnu: public zMnu
{
CPoint PNear1;
CPoint PNear2;
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTRIM_Mnu : public zMnu
{
	CPoint PNear1;
	CPoint PNear2;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zINT_Mnu: public zMnu
{
public:
CPoint PNear1;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPROJ_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
}; 

class zKNOTINS_Mnu : public zMnu
{
  NCurve* pC=NULL;
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCVSPLIT_Mnu : public zMnu
{
	NCurve* pC = NULL;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zKNOTMOD_Mnu : public zMnu
{
  CString sKnot;
  NCurve* pC = NULL;
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zSURRV_Mnu: public zMnu
{
public:
C3dVector p1;
double dAng;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCVONSUR_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zSURTRIM_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSURFUNTRIM_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zMMESHQ_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMESHQND_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMESHINT_Mnu : public zMnu
{
public:
	int iCnt;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMESHINTWP_Mnu : public zMnu
{
public:
	int iCnt;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zMMESHT_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMMESHAF_Mnu : public zMnu
{
public:
	int iCnt;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zEXTRACT_Mnu : public zMnu
{
public:
	int iCnt;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMMESHSZ_Mnu : public zMnu
{
public:
	int iCnt;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMMESHBZ_Mnu : public zMnu
{
public:
	int iCnt;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zFMESHT_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};



class zSURTRIMLOOP_Mnu: public zMnu
{
public:
int iCnt;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};



class zNDBET_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNDCO_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zBUPVEC_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zBOFF_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zBDOFA_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zBDOFB_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zSOFF_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zBOFFY_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zBOFFZ_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zFILET_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zQANGSIZE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zQSIZE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPTSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zEDSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zFCSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zNDSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zTXTSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zBMSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zWPSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zELSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLMSIZE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMOVE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMOVETO_Mnu: public zMnu
{
public:
C3dVector   vF;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCOPY_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCOPYTO_Mnu: public zMnu
{
public:
C3dVector   vF;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELSWEEP_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELSWEEPNDS_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zELSWEEPNDB_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zELSWEEPB_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zOFFSET_Mnu: public zMnu
{
public:
C3dVector dDist;
G_Object* pO;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zWPONCV_Mnu: public zMnu
{
public:
NCurve* pC;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zWPONSURF_Mnu: public zMnu
{
public:

NSurf* pS;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zWPCENT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNDMOVE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNODEX_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zNODEY_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zNODEZ_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zFCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zACR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGRAV_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zRACR_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zTCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTEMPD_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zTBCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zFLUXCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMATEDIT_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPREDIT_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zOEDIT_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};



class zPCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMMESHTET_Mnu: public zMnu
{
public:
double dT;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zFFACE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMSHELL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCHK2D_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zFEDGE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zQMORPH_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zELMASS_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCELM_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zSNORM_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMQUADTOTRI_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zRCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCNODES_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zQWNODES_Mnu: public zMnu
{
public:
double dTol;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMERNODES_Mnu: public zMnu
{
public:
double dTol;
BOOL bUp;
BOOL bDel;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNDEQLAB_Mnu : public zMnu
{
public:
	double dTol;
	BOOL bUp;
	BOOL bDel;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCHKSHELLASP_Mnu : public zMnu
{
public:
  double dT;
  BOOL bList;
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zCHKTETCOL_Mnu : public zMnu
{
public:
  double dT;
  BOOL bList;
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCHKCOUNT_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLABENT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELMOPID_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELRBENODE_Mnu : public zMnu
{
public:
virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zNDMOOSYS_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELMOSHELLMCYS_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zSPGMOSYS_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNDMOLAB_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};



class zELMOLAB_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNDMOLAB2_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELMOLAB2_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELREV_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCHKCIRCUMSPH_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zNDMORSYS_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zWPLSIZE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zCIRCR_Mnu: public zMnu
{
public:
C3dVector vR;
double dRad;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTEXTCR_Mnu : public zMnu
{
	C3dVector p1;
	CString sText;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCIRCPT_Mnu: public zMnu
{
C3dVector p1;
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCIRCR2_Mnu : public zMnu
{
	C3dVector p1;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLNTANCIR_Mnu : public zMnu
{
	CPoint PNear1;
	C3dVector p1;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLNTAN2CIR_Mnu : public zMnu
{
	CPoint PNear1;
	CPoint PNear2;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLN_Mnu: public zMnu
{
C3dVector p1;
C3dVector p2;
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zDIMA_Mnu : public zMnu
{
	C3dVector p1;
	C3dVector p2;
	C3dVector p3;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIMANG_Mnu : public zMnu
{
	C3dVector p1;
	C3dVector p2;
	C3dVector p3;
	C3dVector pIns;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIMH_Mnu : public zMnu
{
	C3dVector p1;
	C3dVector p2;
	C3dVector p3;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIMV_Mnu : public zMnu
{
	C3dVector p1;
	C3dVector p2;
	C3dVector p3;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIML_Mnu : public zMnu
{
	CString sText;
	C3dVector p1;
	C3dVector p2;
	C3dVector p3;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIMR_Mnu : public zMnu
{
C3dVector p2;
NCircle* pC = nullptr;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIMCL_Mnu : public zMnu
{
	C3dVector p2;
	NCircle* pC = nullptr;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIMDRAG_Mnu : public zMnu
{
	C3dVector p1;
	DIM* pD = nullptr;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDIMD_Mnu : public zMnu
{
	C3dVector p2;
	NCircle* pC = nullptr;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zLNC_Mnu : public zMnu
{
BOOL bF;
C3dVector pLast;
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCIR3PT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zARC3PT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRECT_Mnu: public zMnu
{
C3dVector p1;
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zLNY_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zLNZ_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPTCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zFINDNODE_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zBET_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTVEC_Mnu: public zMnu
{
C3dVector p1;
C3dVector p2;
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zWPALIGN_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zALIGN_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zREFLECT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zREFLECT2D_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zROTANG_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zROTABOUT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCOPYROT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCOPYROT2D_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSCALE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zINSCAT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCOORDCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zNDSONCV_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPTSONCIR_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zTEST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zDSPLAM_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCVMOW_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zCVPTON_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zWPGLOB_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSOLVE_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDEL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zTRAN_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPTRAN_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zONSCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zLSETCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zBSETCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTSETCR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zLSETLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMSHLIST_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMSHCR_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMSHACT_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLABGAP_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLABGAPMP_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zMSHVIS_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMSHDEL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zLSETACT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSOLACT_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zSTEPACT_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zBSETLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zBSETACT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTSETLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTSETACT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESCOLSETBAR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESREVCOLBAR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPBYPID_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zCOLPID_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCOLINC_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zCHKJAC_Mnu : public zMnu
{
public:
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDSPGP_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};



class zDSPALL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSHOWALL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zHIDE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zDSPSEL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zDES_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};
class zGPBYMID_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPBYTYPE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zSELBYPID_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELBYMID_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMATLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSOLLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSOLCR_Mnu: public zMnu
{
public:
int iSol;
CString sT;
double dT;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSTEPCR_Mnu: public zMnu
{
public:
int iSol;
int iLC;
int iBC;
int iTC;
BOOL bRS;
CString sT;

virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRLISTALL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMATLISTALL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRELTO_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zPRBROD_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
int iMID;
double dR;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRROD_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
int iMID;
double dA;
double dJ;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRBAR2_Mnu : public zMnu
{
public:
	int  iNLab;
	int iPID;
	int iMID;
	double dA;
	double dI1;
	double dI2;
	double dJ;
	CString sTit;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPRBBAR_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
int iMID;
double dW;
double dH;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRCMAT_Mnu: public zMnu
{
public:

int iPID;
int iMID1;
int iMID2;
CString sTit;

virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRSHELL_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
int iMID;
double dT;
double dNSM;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRPCOMP_Mnu : public zMnu
{
public:
	int  iNLab;
	int iPID;
	int iNoLay = 0;
	CString sLay[50];
	double dNSM;
	CString sTit;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPRSPGT_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
double dkx;
double dky;
double dkz;
double dkt;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRBUSH_Mnu : public zMnu
{
public:
	int  iNLab;
	int iPID;
	double dk1;
	double dk2;
	double dk3;
	double dk4;
	double dk5;
	double dk6;
	CString sTit;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPRMASS_Mnu : public zMnu
{
public:
  int  iNLab;
  int iPID;
  double dM;
  CString sTit;
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPRSPGR_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
double dkx;
double dky;
double dkz;
double dkt;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRSOLID_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
int iMID;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};



class zPRBTUBE_Mnu: public zMnu
{
public:
int  iNLab;
int iPID;
int iMID;
double dR;
double dr;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};



class zPRBBOX_Mnu: public zMnu
{
public:
int iNLab;
int iPID;
int iMID;
double dW;
double dH;
double dWT;
double dHT;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zPRBL_Mnu : public zMnu
{
public:
	int iNLab;
	int iPID;
	int iMID;
	double dW;
	double dH;
	double dWT;
	double dHT;
	CString sTit;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPRBT2_Mnu : public zMnu
{
public:
	int iNLab;
	int iPID;
	int iMID;
	double dW;
	double dH;
	double dWT;
	double dHT;
	CString sTit;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPRBCHAN2_Mnu : public zMnu
{
public:
	int iNLab;
	int iPID;
	int iMID;
	double dW;
	double dH;
	double dWT;
	double dHT;
	CString sTit;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zPRBI2_Mnu : public zMnu
{
public:
	int iNLab;
	int iPID;
	int iMID;
	double d1;
	double d2;
	double d3;
	double d4;
	double d5;
	double d6;
	CString sTit;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMMAT1_Mnu: public zMnu
{
public:
int iNLab;
int iMID;
double dE;
double dV;
double dDen;
double dA;
double dk;
CString sTit;
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zMMAT8_Mnu : public zMnu
{
public:
  int iNLab;
  int iMID;
  double dE1;
  double dE2;
  double dNU12;
  double dG12;
  double dG1Z;
  double dG2Z;
  double dRHO;
  double dA1;
  double dA2;
  double dk;
  CString sTit;
  virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zCOLINE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zELAT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELBYCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELBYTYPE_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELALL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELINV_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELNODESBYCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELSURFCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELPTSCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zSELCURCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
}; 

class zSELCURLAY_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zGPBYCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPNDBYCOL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPNDBYOSYS_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPNDBYDSYS_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPSET_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPDEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zLSETDEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zBSETDEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zTSETDEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zDELAY_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zHLIMIT_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zECHO_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESDELAY_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESLSTRESP_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESGRAPHRESP_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESLABRESP_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESLSTRESPFULL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESFRAMES_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zGPNEXT_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPPREV_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESSETLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESVECLIST_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESDEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESSETFULLLIST_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESLISTEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESLISTND_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESSEL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESENVMAX_Mnu : public zMnu
{

public:
	int iNo = 0;
	CString sSeq[50];
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESDIVINTO_Mnu : public zMnu
{

public:
	CString sSeq;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESSCALE_Mnu : public zMnu
{

public:
	int iNo = 0;
	CString sSeq;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESENVMIN_Mnu : public zMnu
{

public:
	int iNo = 0;
	CString sSeq[50];
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESVEC_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESVECDEL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zRESSELDEF_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zRESSETDEFSCL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zDIMSCL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zRESSETVECSCL_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

//int zRESDISPOFF_Mnu::DoMenu(CString CInMsg, CPoint Pt)
class zRESDISPOFF_Mnu : public zMnu
{
public:
	Node* pN;
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};


class zLAB_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zSETFIL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPDSP_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zFILALL_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zFILCLR_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPADDGP_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPREMGP_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zGPADD_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};


class zGPREM_Mnu: public zMnu
{
public:
virtual	int DoMenu(CString CInMsg,CPoint Pt);
};

class zEXPINC_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zGPBYINC_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMODINCNO_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};

class zMODLAYNO_Mnu : public zMnu
{
public:
	virtual	int DoMenu(CString CInMsg, CPoint Pt);
};