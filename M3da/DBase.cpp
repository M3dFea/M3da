#include "DBase.h"
#include <cmath>
#include "gl\gl.h"
#include "gl\glu.h"
#include "M3Da.h"
#include "SymTable.h"
#include "GLOBAL_VARS.h"
#include <fstream>  // Include the necessary header file
#include <string>
#include <atlstr.h>

#pragma warning(disable:4477)
BOOL gORTHO;
BOOL gDSP_CPTS = FALSE;
BOOL gDSP_CIRS = TRUE;
BOOL gDSP_BACK = TRUE;
const double dTol = 0.00000001;  //unsed for Surface tolerance
const double Pi = 3.1415926535;
#define D2R  0.01745329251994
#define R2D  57.2957795130931



float CPal[12][3] ={{0.00f, 0.00f, 1.00f},    //151 Blue
{0.00f, 0.33f, 1.00f},    //152 Grey Blue
{0.00f, 0.66f, 1.00f},    //153 Light Blue
{0.00f, 1.00f, 1.00f},    //154 Cyan
{0.00f, 0.33f, 0.00f},    //155 Dark Olive
{0.00f, 0.66f, 0.00f},    //156 Dark Green
{0.00f, 1.00f, 0.00f},    //157 Green
{1.00f, 1.00f, 0.00f},    //158 Yellow
{1.00f, 0.66f, 0.00f},    //159 Golden Orange
{1.00f, 0.33f, 0.00f},    //160 Orangr
{1.00f, 0.00f, 0.00f},    //161 Red
{1.00f, 0.00f, 1.00f}};    //162 Magenta
//{1.00f, 0.33f, 1.00f},    //163 Light Magenta
//{1.00f, 0.66f, 1.00f},    //164 Pink
//{1.00f, 1.00f, 1.00f},    //165 White
//{0.6f, 0.6f, 0.6f}};      //166Grey

//************************************************************************************
// Pre  : FName string to search
//        sC character to search for (String*1)
// Post : Returns the last occurance of sC in FName or -1
//************************************************************************************
int GetLastChar(CString FName,char sC)
{
int irc=-1;
int i;

for (i=0;i<FName.GetLength();i++)
{
  if (FName[i] == sC) 
    irc = i;
}
return(irc);
}

//************************************************************************************
// Pre  : File name
// Post : Returns the path without the file name or "NULL"
//************************************************************************************
CString getPath(CString FName)
{
CString src="NULL";

int iP;
iP = FName.Find(":");
if (iP > 0 )
{
  src = FName.Left (GetLastChar(FName, '\\'));
}
return (src);
};

//************************************************************************************
// Pre  : File name
// Post : Returns the drive prefix or "NULL" if none valid
//************************************************************************************
CString getDrive(CString FName)
{
CString src="NULL";
int iP;
iP = FName.Find(":");
if (iP > 0)
  src = FName.Mid(iP - 1, 2);

return (src);
}

CString getName(CString FName)
{
CString src = "NULL";
int iP;

iP = FName.Find (":");
if (iP > 0) 
  src = FName.Right(FName.GetLength() - GetLastChar(FName, '\\')-1);

return (src);
}

//*****************************************************
//Pre   : sIn nastran line from file
//Post  : Return True if first 7 chars form "include" or
//        "INCLUDE"
//*****************************************************
BOOL IsInclude(CString sIN)
{
BOOL brc  = FALSE;
CString St;
St = sIN.Left( 7);
if ((St.Find("include")>-1) || (St.Find("INCLUDE")>-1))
  brc = TRUE;

return(brc);
}

//*****************************************************
//Pre   : sIn nastran line from file
//Post  : Return the include string between ' ' or "NULL"
//*****************************************************
CString GetIncName(CString sIN)
{
CString S;
int iP;

iP = sIN.Find("'");
if (iP == -1) 
{
  S = "NULL";
}
else
{
  S = sIN.Right(sIN.GetLength() - iP-1);
  iP = S.Find("'");
  if (iP == 0)
    S = "NULL";
  else
    S = S.Left(iP);
} 
return (S);
}


unsigned char threeto8[8] = 
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char twoto8[4] = 
{
	0, 0x55, 0xaa, 0xff
};

unsigned char oneto8[2] = 
{
	0, 255
};

static int defaultOverride[13] = 
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

static PALETTEENTRY defaultPalEntry[20] = 
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

double ae(CString sIn)
{

int iIsM;
int iIsP;
int iPos=-1;
int iDPos=-1;

double dRet=DBL_MAX;
CString sRet=sIn;
CString sNew=sIn;
//Check for +/- to see if exponetial format
iIsM=sIn.ReverseFind('-');
iIsP=sIn.ReverseFind('+');
iDPos=sIn.Find('.');
 if (iIsM>-1)
 {
   iPos=iIsM;
 }
 else if (iIsP>-1)
 {
   iPos=iIsP;
 }
if ((iPos>-1) && (iPos>iDPos))
{
// Now need to see if e is present
  if ((sIn.Find('e')==-1) && (sIn.Find('E')==-1))
  {

     sNew=sIn.Left(iPos);
     sNew+='E';
     sNew+=sIn.Right(sIn.GetLength()-iPos);
     sRet=sNew;
  }
  dRet=atof(sRet);
}
else
{
  dRet=atof(sIn);
}
return(dRet);
}

double aeB(CString sIn)
{

int iIsM;
int iIsP;
int iPos;

double dRet=DBL_MAX;
CString sRet=sIn;
CString sNew=sIn;
//Check for +/- to see if exponetial format
iIsM=sIn.Find('-',1);
iIsP=sIn.Find('+',1);
if ((sIn=="        ") ||
    (sIn=="       ") ||
    (sIn=="      ") ||
    (sIn=="     ") ||
    (sIn=="    ") ||
    (sIn=="   ") ||
    (sIn=="  ") ||
    (sIn==" ") ||
   (sIn==""))
{
dRet=DBL_MAX;
}
else if ((iIsM>-1) || (iIsP>-1)) 
{
// Now need to see if e is present
  if ((sIn.Find('e')==-1) && (sIn.Find('E')==-1))
  {
     if (iIsM>-1)
     {
       iPos=iIsM;
     }
     else
     {
       iPos=iIsP;
     }
     sNew=sIn.Left(iPos);
     sNew+='E';
     sNew+=sIn.Right(sIn.GetLength()-iPos);
     sRet=sNew;
  }
  dRet=atof(sRet);
}
else
{
  dRet=atof(sIn);
}
return(dRet);
}

IMPLEMENT_DYNAMIC(DBase, CCmdTarget)


DBase::DBase()
{
	EnableAutomation();
    pWorldBMP=NULL;
	bIsDrag = FALSE;
	iHLimit = -1;
	G_Object* pDragObj = nullptr;
}

DBase::~DBase()
{
	int i;
	S_Count = 0;
	for (i = 0; i < DB_ObjectCount; i++)
	{
		delete(DB_Obj[i]);
		DB_Obj[i] = NULL;
	}
	DB_ObjectCount = 0;
	if (pDragObj != nullptr)
	   delete (pDragObj);
}


void DBase::LabGaps(int iGap)
{
	if (pCurrentMesh != NULL)
		pCurrentMesh->LabGaps(iGap);
}
//***************************************************************************
// PRE: TRUE
// POST: ALL DELETED
//***************************************************************************

void DBase::DeleteAll()
{
	int i;
	S_Count = 0;
	DelAll_Group();
	for (i = 1; i < DB_ObjectCount; i++)
	{
		delete(DB_Obj[i]);
		DB_Obj[i] = NULL;
	}
	DB_ObjectCount = 1;
	PropsT->DeleteAll();
	MatT->DeleteAll();
}

void DBase::PrintTime(CString cS)
{
	int Hour;
	int Min;
	int Sec;
	char s1[80];
	COleDateTime timeStart;
	timeStart = COleDateTime::GetCurrentTime();
	Hour = timeStart.GetHour();
	Min = timeStart.GetMinute();
	Sec = timeStart.GetSecond();
	sprintf_s(s1, "%s %i:%i:%i\n", cS, Hour, Min, Sec);
	outtext1(s1);
}

void DBase::ExporttoNAS(int iFileNo)
{
	outtext1("EXPORTING NASTRAN DECK");
	FILE* pFile;
	CFileDialog FDia(FALSE, "dat", "*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		pFile = fopen(sPath, "w");
		if (pFile != NULL)
		{
			ExportMeshNAS(pFile, iFileNo);
			fclose(pFile);
		}
	}
}



int DBase::GetFileByNo(CString sF)
{
	int irc=-1;
	int i;
	for (i = 0; i < iFileNo; i++)
	{
		if (sFiles[i] == sF)
		{
			irc = i;
			break;
		}

	}
	return(irc);
}

void DBase::DragUpdate(CPoint inPt)
{
	C3dVector vG;
	vG = PickPointToGlobal2(inPt);
	C3dMatrix mTran;
	WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
	mTran = pWPlane->mWPTransform;
	if (pDragObj != nullptr)
		pDragObj->DragUpdate(vG, mTran);
}

void DBase::SetLineStart(CPoint pS)
{
	vLS = PickPointToGlobal2(pS);
}

void DBase::SetLineEnd(CPoint pE)
{
	vLE = PickPointToGlobal2(pE);
}



void DBase::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

DBase::DBase(double WPS)
{
EnableAutomation();
bIsDrag = FALSE;
TmpOGLCnt=0;
DB_ObjectCount = 0;
DB_ActiveBuff = 1;
DB_BuffCount = 0;
iDspLstCount = 0;
S_Count = 0;
Pen = NULL;
CreateWP(WPS);
iMeshCnt = 0;
DB_Obj[DB_ObjectCount] =CreateMesh("WORK");
pCurrentMesh=(ME_Object*) DB_Obj[DB_ObjectCount];
DB_ObjectCount++;
pCurrentPart = NULL;
Dsp_All();
WPSize = WPS;
DB_DrawState = 0;
iFastView=1;
iOGLList = -1;
int iOGL_Start=-1;
int iOGL_NoOff=-1;
iOGLInit=-1;
bNoList = FALSE;
MeshCat=NULL;
gDim=2;
pSecs=NULL;
iSH=6;
iSW=4;
gdSize=0.005;
gdASize=10;
FILTER.SetAll();
//FILTER.SetFilter(4);
iSMode=1;  //0 Gen on mid plain 1 outer
iCurElemType=94;
iNoGPs = 0;
iCurGp = -1;
iMeshCnt = 1;
OTemp = new ObjList();
OTemp2 = new ObjList();
PropsT=new PropTable();
MatT= new MatTable();
bPICK=TRUE;
bDispAll=TRUE;
iEdges=1;
DspFlags=DSP_ALL;
dMFullScl=1;
bRevColBar=FALSE;
iPtLabCnt=1;
iTxtLabCnt = 1;
iCVLabCnt=1;
iSFLabCnt=1;
iPartLabCnt = 1;
iNoSymbols=0;
LoadSymbolsInternal();  //Load the Acad char set
pWorldBMP = NULL;
ResFrameDelay = 200;
NoResFrame = 5;
iHLimit =-1;
G_Object* pDragObj = nullptr;
}

//********************************************************
//                    MESH MANAGEMENT
//********************************************************
void DBase::MeshListALl()
{
	int i;
	char S1[200];
	CString sVis;
	ME_Object* ME;
	outtext1("All Available Meshes:-");
	for (i = 0; i < DB_ObjectCount; i++)
	{
		if (DB_Obj[i]->iObjType == 4)
		{
			ME = (ME_Object*)DB_Obj[i];
			if (ME->Visable == 1)
				sVis = "Vis ON ";
			else
				sVis = "Vis OFF";
			sprintf_s(S1, "%i : %s : %s", ME->iLabel, ME->sName, sVis);
			outtext1(S1);
		}
	}
	if (pCurrentMesh->Visable == 1)
		sVis = "Vis ON ";
	else
		sVis = "Vis OFF";
	outtext1("Currently Active Mesh:-");
	sprintf_s(S1, "%i : %s : %s", pCurrentMesh->iLabel, pCurrentMesh->sName, sVis);
	outtext1(S1);
}

void DBase::SetActiveMesh(int ID)
{
	int i;
	char S1[200];
	ME_Object* ME;
	for (i = 0; i < DB_ObjectCount; i++)
	{
		if ((DB_Obj[i]->iObjType == 4) && (DB_Obj[i]->iLabel == ID))
		{
			ME = (ME_Object*)DB_Obj[i];
			pCurrentMesh = ME;
			sprintf_s(S1, "%i : %s", ME->iLabel, ME->sName);
			outtext1(S1);
			break;
		}
	}
}

void DBase::TogVisableMesh(int ID)
{
	int i;
	char S1[200];
	ME_Object* ME;
	for (i = 0; i < DB_ObjectCount; i++)
	{
		if ((DB_Obj[i]->iObjType == 4) && (DB_Obj[i]->iLabel == ID))
		{
			ME = (ME_Object*)DB_Obj[i];
			if (ME->Visable == 0)
			{
				ME->Visable = 1;
				Dsp_Add(ME);
				InvalidateOGL();
				ReDraw();
			}
			else
			{
				ME->Visable = 0;
				Dsp_Rem(ME);
				InvalidateOGL();
				ReDraw();
			}
			sprintf_s(S1, "%i : %s", ME->iLabel, ME->sName);
			outtext1(S1);
			break;
		}
	}
}

void DBase::DeleteMesh(int ID)
{
	int i;
	ME_Object* ME;
	for (i = 0; i < DB_ObjectCount; i++)
	{
		if ((DB_Obj[i]->iObjType == 4) && (DB_Obj[i]->iLabel == ID))
		{
			ME = (ME_Object*)DB_Obj[i];
			if (ME != pCurrentMesh)
			{
				//Dsp_Rem(ME);
				//Dsp_RemGP(ME);
				//RemObj(ME);
				//sprintf_s(S1, "%i : %s", ME->iLabel, ME->Name);
				//outtext1(S1);
				//break;
			}
			else
			{
				outtext1("ERROR: Cannot Delete the Currently Active Mesh");
			}

		}
	}
}

void DBase::CreateNewMesh(CString sName)
{
	ME_Object* ME;
	ME=CreateMesh(sName);
	if (ME != NULL)
		AddObj(ME);
}



void DBase::SetCurLC(int iSet)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->SetCurLC(iSet);
  InvalidateOGL();
  ReDraw();
}
}

void DBase::SetCurBC(int iSet)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->SetCurBC(iSet);
  InvalidateOGL();
  ReDraw();
}
}

void DBase::SetCurTSET(int iSet)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->SetCurTSET(iSet);
  InvalidateOGL();
  ReDraw();
}
}

void DBase::ListLC()
{
if (pCurrentMesh!=NULL)
  pCurrentMesh->ListLC();
}

void DBase::ListBC()
{
if (pCurrentMesh!=NULL)
  pCurrentMesh->ListBC();
}

void DBase::ListTSET()
{
if (pCurrentMesh!=NULL)
  pCurrentMesh->ListTSET();
}

void DBase::DeleteLC(int iSet)
{
  pCurrentMesh->DeleteLC(iSet);
}

void DBase::DeleteBC(int iSet)
{
  pCurrentMesh->DeleteBC(iSet);
}

void DBase::DeleteTSET(int iSet)
{
  pCurrentMesh->DeleteTSET(iSet);
}


void DBase::AnalysisLoadsets()
{
  int i;
  CSETSDialog Dlg;
  char OutT[80];
  Dlg.sTitle="Load Sets";
  Dlg.AttachSets(&pCurrentMesh->iNoLCs,&pCurrentMesh->iCurLC);
  Dlg.sSET="LSETCR";
  Dlg.sDEL="LSETDEL";
  Dlg.sACT="LSETACT";
  Dlg.sLIST="LSETLIST";
  if (pCurrentMesh!=NULL)
  {
    for (i=0;i<pCurrentMesh->iNoLCs;i++)
    {
      sprintf_s(OutT,"%i : %s",pCurrentMesh->LCS[i]->iLabel,pCurrentMesh->LCS[i]->sTitle);
      Dlg.AddSet(i,OutT);
    }
    Dlg.DoModal();
  }
  else 
  {outtext1("ERROR: No Mesh Active.");}

}

void DBase::AnalysisBCsets()
{
  int i;
  CSETSDialog Dlg;
  char OutT[80];
  Dlg.sTitle="Boundary Condition Sets";
  Dlg.AttachSets(&pCurrentMesh->iNoBCs,&pCurrentMesh->iCurBC);
  Dlg.sSET="BSETCR";
  Dlg.sDEL="BSETDEL";
  Dlg.sACT="BSETACT";
  Dlg.sLIST="BSETLIST";
  if (pCurrentMesh!=NULL)
  {
    for (i=0;i<pCurrentMesh->iNoBCs;i++)
    {
      sprintf_s(OutT,"%i : %s",pCurrentMesh->BCS[i]->iLabel,pCurrentMesh->BCS[i]->sTitle);
      Dlg.AddSet(i,OutT);
    }
    Dlg.DoModal();
  }
  else 
  {outtext1("ERROR: No Mesh Active.");}
}

void DBase::AnalysisTEMPsets()
{
  int i;
  CSETSDialog Dlg;
  char OutT[80];
  Dlg.sTitle="Temperature Sets";
  Dlg.AttachSets(&pCurrentMesh->iNoTSets,&pCurrentMesh->iCurTSet);
  Dlg.sSET="TSETCR";
  Dlg.sDEL="TSETDEL";
  Dlg.sACT="TSETACT";
  Dlg.sLIST="TSETLIST";
  if (pCurrentMesh!=NULL)
  {
    for (i=0;i<pCurrentMesh->iNoTSets;i++)
    {
      sprintf_s(OutT,"%i : %s",pCurrentMesh->TSETS[i]->iLabel,pCurrentMesh->TSETS[i]->sTitle);
      Dlg.AddSet(i,OutT);
    }
    Dlg.DoModal();
  }
  else 
  {outtext1("ERROR: No Mesh Active.");}
}


void DBase::CreateLC(int ID, CString sTit)
{
  int iRC=-1;
  if (pCurrentMesh!=NULL)
  {
    if (ID<1)
    {
      outtext1("ERROR: Set ID Must be Greater than 0.");
    }
    else if (isValidLCid(ID)==TRUE)
    {
      outtext1("ERROR: Set ID Allready in Use.");
    }
    else
    {
      iRC=pCurrentMesh->CreateLC(ID,sTit);
      outtext1("1 Load Set Created.");
    }
  }
  else
    outtext1("ERROR: No Mesh Active.");
  if (iRC==-1)
    outtext1("ERROR: Load Set Not Created.");
}

void DBase::CreateBC(int ID, CString sTit)
{
  int iRC=-1;
  if (pCurrentMesh!=NULL)
  {
    if (ID<1)
    {
      outtext1("ERROR: Set ID Must be Greater than 0.");
    }
    else if (isValidBCid(ID)==TRUE)
    {
      outtext1("ERROR: Set ID Allready in Use.");
    }
    else
    {
      iRC=pCurrentMesh->CreateBC(ID,sTit);
      outtext1("1 Boundary Set Created.");
    }
  }
  else
    outtext1("ERROR: No Mesh Active.");
  if (iRC==-1)
    outtext1("ERROR: Boundary Set Not Created.");
}

void DBase::CreateTSET(int ID, CString sTit)
{
  int iRC=-1;
  if (pCurrentMesh!=NULL)
  {
    if (ID<1)
    {
      outtext1("ERROR: Set ID Must be Greater than 0.");
    }
    else if (isValidTCid(ID)==TRUE)
    {
      outtext1("ERROR: Set ID Allready in Use.");
    }
    else
    {
      iRC=pCurrentMesh->CreateTSET(ID,sTit);
      outtext1("1 Temperatue Set Created.");
    }
  }
  else
    outtext1("ERROR: No Mesh Active.");
  if (iRC==-1)
    outtext1("ERROR: Temperature Set Not Created.");
}

void DBase::AnalysisSolution()
{
  CSOLDialog Dlg;
  Dlg.sTitle="Solutions.";
  if (pCurrentMesh!=NULL)
  {
    Dlg.pSOL=pCurrentMesh->pSOLS;
    Dlg.DoModal();
  }
  else 
  {
    outtext1("ERROR: No Mesh Active.");
  }

}

void DBase::SetActSol(int iD)
{
  BOOL bret;
  if (pCurrentMesh != NULL)
  {
    if (pCurrentMesh->pSOLS != NULL)
    {
      bret = pCurrentMesh->pSOLS->SetCurSol(iD);
      if (!bret)
        outtext1("ERROR: Invalid Solution ID.");
      else
      {
        CString sT = pCurrentMesh->pSOLS->GetTitleString(iD);
        outtext1(_T(sT));
      }
    }
  }
}

void DBase::SetActStep(int iD)
{
  BOOL bret;
  if (pCurrentMesh != NULL)
  {
    if (pCurrentMesh->pSOLS != NULL)
    {
      bret = pCurrentMesh->pSOLS->SetCurStep(iD);
      if (!bret)
        outtext1("ERROR: Invalid Step ID.");
      else
      {
        Solution* pS = pCurrentMesh->pSOLS->GetCurSolution();
        pS->SetCurStep(iD);
        CString sT = pS->GetStepTitleString(iD);
        outtext1(_T(sT));
      }
    }
  }
}

void DBase::AnalysisLoadStep()
{
  int i;
  CSTEPSDialog Dlg;
  char OutT[80];
  Dlg.sTitle="Solution Steps.";


  //Dlg.AttachSets(&pCurrentMesh->iNoLCs,&pCurrentMesh->iCurLC);
 // Dlg.sSET="LSETCR";
  //Dlg.sDEL="LSETDEL";
  //Dlg.sACT="LSETACT";
  //Dlg.sLIST="LSETLIST";
  if (pCurrentMesh!=NULL)
  {
    Dlg.pSOL=pCurrentMesh->pSOLS;
    for (i=0;i<pCurrentMesh->iNoLCs;i++)
    {
      sprintf_s(OutT,"%i : %s",pCurrentMesh->LCS[i]->iLabel,pCurrentMesh->LCS[i]->sTitle);
      Dlg.AddSet(pCurrentMesh->LCS[i]->iLabel,OutT,0);
    }
    for (i=0;i<pCurrentMesh->iNoBCs;i++)
    {
      sprintf_s(OutT,"%i : %s",pCurrentMesh->BCS[i]->iLabel,pCurrentMesh->BCS[i]->sTitle);
      Dlg.AddSet(pCurrentMesh->BCS[i]->iLabel,OutT,1);
    }
    for (i=0;i<pCurrentMesh->iNoTSets;i++)
    {
      sprintf_s(OutT,"%i : %s",pCurrentMesh->TSETS[i]->iLabel,pCurrentMesh->TSETS[i]->sTitle);
      Dlg.AddSet(pCurrentMesh->TSETS[i]->iLabel,OutT,2);
    }
    Dlg.DoModal();
  }
  else 
  {outtext1("ERROR: No Mesh Active.");}

}

//*********************************
//********************************************
//DELAY IN SECONDS
//********************************************
void DBase::DELAY(int iDelay)
{	
char buff[80];

	if (iDelay>0)
	{
       int iDelayMilli=iDelay*1000; //Delay in milli seconds
	   sprintf_s(buff, "%s %i %s","Waiting",iDelay,"Second(s)");
	   outtext1(buff);
	   Sleep(iDelayMilli);          //sleep for iDelay
	   outtext1("Resume.");
	}
}

void DBase::HLimit(int iHlim)
{
	char buff[80];
	if (iHlim > 0)
	{
		iHLimit = iHlim;
		sprintf_s(buff, "%s %i", "Highlight Limit = ", iHLimit);
		outtext1(buff);
	}
	else
	{
		iHLimit = -1;
		sprintf_s(buff, "%s", "Highlight Limit = ALL");
		outtext1(buff);
	}
}

//*************************************************************
//  LIST RESPONSE DATA FOR FREQUENCY ANALYSIS
//  List repose for loadcase LC
//  and for node or element iEnt
//*************************************************************
void DBase::ResListRespData(int iEnt)
{
	if (pCurrentMesh != NULL)
		pCurrentMesh->ResListRespData(iEnt);

}

//RESGRAPHRESP
void DBase::ResGraphRespData(int iEnt)
{
	//if (pCurrentMesh != NULL)
	//	pCurrentMesh->ResListRespData(iEnt);
	CGraphDialog* Dlg = new CGraphDialog();
	Dlg->pME = pCurrentMesh;
	Dlg->DoModal();
	if (Dlg != NULL)
		delete Dlg;
	InvalidateOGL();
	ReGen();
}

//RESLABRESP
void DBase::LabelRespItems()
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->ResLabRespItems();
		InvalidateOGL();
		ReDraw();
	}

}

//*************************************************************
//  LIST RESPONSE DATA FOR FREQUENCY ANALYSIS
//  List reponse for loadcase LC
//  and for node or element iEnt
//*************************************************************
void DBase::ResListRespDataFull(int iEnt)
{
	if (pCurrentMesh != NULL)
		pCurrentMesh->ResListRespDataFull(iEnt);

}



//********************************************
//RESULTS FRAME DELAY IN MIL SECONDS
//********************************************
void DBase::ResDelay(int iDelay)
{
	char S1[80];
	ResFrameDelay = iDelay;
	sprintf_s(S1, "%s %i ms", "Animation Delay : ", iDelay);
	outtext1(S1);
	
}




void DBase::ResFrames(int iNoF)
{
	char S1[80];
	if ((iNoF > 0) && (iNoF < 21))
		NoResFrame = iNoF;
	else
	outtext1("Frames Out of Range (1 to 20)");
	sprintf_s(S1, "%s %i", "No Off Animation Frames : ", NoResFrame);
	outtext1(S1);
}

void DBase::LoadProps(CString sFile)
{
  ME_Object* Mesh = ImportNASTRAN2(sFile,FALSE);
  if (Mesh!=NULL)
  {
	Mesh->sName="Properties";
    pCurrentMesh=Mesh;
    DB_Obj[DB_ObjectCount] =Mesh;
    DB_ObjectCount++;
    Dsp_Add(Mesh);
  }
}

void DBase::LoadSecT(FILE* pFileA)
{

int iStop =0;
char s1[1000];
char s2[20];
char s3[20]; 
char s4[20]; 
char s5[20]; 
char s6[20];
char s7[20]; 
char s8[20];
char s9[20];
char s10[20];
char s11[20];
char s12[20];
char s13[20];
char s14[20];
char s15[20];
char s16[20];
char s17[20];
char s18[20];
char s19[20];

char sT[20];

  if (pSecs!=NULL)
  {
	delete(pSecs);
	pSecs=NULL;
  }
  pSecs=new SecTable(); 
  outtext1("Loading Sections:-");
int iWR;
int iWG;
double dTHK;
double dW;
double dH;
int iCOL;
int iPID;
int iPID2;
int iSecNo;
int iOpt;
BOOL inF;
double dr;
int iM1;
int iM2;
double dTHK2;
 double dLFR;
 double dNSMS;
 double dNSMB;
 int iP1;
 int iP2;
 int iP3;
 int iP4;
 int iP5;
 int iP6;
  do
  {
    if (fgets(s1,1000,pFileA)!=NULL)
    {
      if ((s1[0]=='S') &&
		      (s1[1]=='E') &&
		      (s1[2]=='C') &&
          (s1[3]==' '))
	    {
         outtext1(s1);
         sscanf(s1,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			   sT,s2 ,s3 ,s4 ,s5 ,s6 ,s7 ,s8 ,s9,s10,s11,s12,s13,s14); 

        iWR=atoi(s2);
        iWG=atoi(s3);
        dTHK=atof(s4);
        dW=atof(s5);
        dH=atof(s6);
        iCOL=atoi(s7);
        iPID=atoi(s8);
        iPID2=atoi(s9);
        iSecNo=atoi(s10);
        iOpt=atoi(s11);
        inF=FALSE;
        dr=0;
        iM1=atoi(s12);
        iM2=-1;
        dTHK2=0;
        dLFR=0;
        dNSMS=atof(s13);
        dNSMB=atof(s14);
        iP1=-1;
        iP2=-1;
        iP3=-1;
        iP4=-1;
        iP5=-1;
        iP6=-1;
        pSecs->add(iWR,iWG,dTHK,dW,dH,iCOL,iPID,iPID2,iSecNo,iOpt,inF,dr,iM1,iM2,dTHK2,dLFR,dNSMS,dNSMB,
                   iP1,iP2,iP3,iP4,iP5,iP6);
	    }
      else if ((s1[0]=='S') &&
		      (s1[1]=='E') &&
		      (s1[2]=='C') &&
          (s1[3]=='F'))
	    {
         outtext1(s1);
         sscanf(s1,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
         sT,s2 ,s3 ,s4 ,s5 ,s6 ,s7 ,s8 ,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19); 
        iWR=atoi(s2);
        iWG=atoi(s3);
        dTHK=atof(s4);
        dW=atof(s6);
        dH=atof(s7);
        iCOL=atoi(s10);
        iPID=-1;
        iPID2=-1;
        iSecNo=-1;
        iOpt=atoi(s13);
        inF=TRUE;
        dr=atof(s9);
        iM1=atoi(s11);
        iM2=atoi(s12);;
        dTHK2=atof(s5);
        dLFR=atof(s8);
        dNSMS=-1;
        dNSMB=-1;
        iP1=atoi(s14);
        iP2=atoi(s15);
        iP3=atoi(s16);
        iP4=atoi(s17);
        iP5=atoi(s18);
        iP6=atoi(s19);
         pSecs->add(iWR,iWG,dTHK,dW,dH,iCOL,iPID,iPID2,iSecNo,iOpt,inF,dr,iM1,iM2,dTHK2,dLFR,dNSMS,dNSMB,
                iP1,iP2,iP3,iP4,iP5,iP6);
	    }
    }
    if (feof(pFileA))
     {
     //printf("\nEND OF FILE\n");
     iStop = 1;     
     }
  }
  while (iStop == 0);

}


void DBase::Serialize(CArchive& ar)
{
	int iCurMesh=-1;
	int iCurPart=-1;
	ME_Object* pM;
	WG_Def* pD;
	int i;
	int iType;
	int iSecondaryType;
	if (ar.IsStoring())
	{
	  // TODO: add storing code here
		ar<<VERSION_NO;
		ar << pModelMat.m_00;
		ar << pModelMat.m_01;
		ar << pModelMat.m_02;
		ar << pModelMat.m_03;
		ar << pModelMat.m_10;
		ar << pModelMat.m_11;
		ar << pModelMat.m_12;
		ar << pModelMat.m_13;
		ar << pModelMat.m_20;
		ar << pModelMat.m_21;
		ar << pModelMat.m_22;
		ar << pModelMat.m_23;
		ar << pModelMat.m_30;
		ar << pModelMat.m_31;
		ar << pModelMat.m_32;
		ar << pModelMat.m_33;
		//global vars
		ar << WPSize;
		ar << gPT_SIZE;
		ar << gND_SIZE;
		ar << gLM_SIZE;
		ar << gEL_SIZE;
		ar << gED_SIZE;
		ar << gFC_SIZE;
		ar << gWP_SIZE;
		ar << gBM_SIZE;
		ar << gTXT_SIZE;
		ar << gDIM_FILSZ;
		ar << gDIM_OFFSZ;
		ar << gTXT_HEIGHT;
		ar << gDIM_RADSZ;
		ar << gDIM_SIZE;
		ar << gDRILL_KS;
		ar << gRIGID_MULTIPLIER;
		ar << gVSTIFF_KS;
		ar << gDEF_E;
		ar << gDEF_V;
		ar << gSTIFF_BDIA;
		ar << gDEF_CTE;
		ar << gDEF_THERM_LNK;
		ar << gDEF_SOL_TOL;
		ar << gDIM_PREC;

		PropsT->Serialize(ar,VERSION_NO);
		MatT->Serialize(ar,VERSION_NO);
		ar<<DB_ObjectCount;
		ar<<iMeshCnt;
		ar<<iCurGp;
		ar<<iPtLabCnt; 
		ar<<iTxtLabCnt;
		ar<<iCVLabCnt;
		ar<<iSFLabCnt;
		ar<<iPartLabCnt;
		ar << pCurrentMesh->iLabel;
		if (pCurrentPart!=NULL)
			ar << pCurrentPart->iLabel;
		else
			ar << -1;
		//Workplane 
		DB_Obj[0]->Serialize(ar, iVER);
		for (i=1;i<DB_ObjectCount;i++)
		{
			ar << DB_Obj[i]->iObjType;
			ar << DB_Obj[i]->iType;
			DB_Obj[i]->Serialize(ar,iVER);       //all 
		}
		SaveGps(ar);
	}
	else
	{
		ar>>iVER;
		if (iVER <= -66)
		{
			C3dMatrix mT;
			ar >> mT.m_00;
			ar >> mT.m_01;
			ar >> mT.m_02;
			ar >> mT.m_03;
			ar >> mT.m_10;
			ar >> mT.m_11;
			ar >> mT.m_12;
			ar >> mT.m_13;
			ar >> mT.m_20;
			ar >> mT.m_21;
			ar >> mT.m_22;
			ar >> mT.m_23;
			ar >> mT.m_30;
			ar >> mT.m_31;
			ar >> mT.m_32;
			ar >> mT.m_33;
			tOrient.PushMat(mT);
			pModelMat = mT;
		}

		if (iVER <= -65)
		{
			ar >> WPSize;
			ar >> gPT_SIZE;
			ar >> gND_SIZE;
			ar >> gLM_SIZE;
			ar >> gEL_SIZE;
			ar >> gED_SIZE;
			ar >> gFC_SIZE;
			ar >> gWP_SIZE;
			ar >> gBM_SIZE;
			ar >> gTXT_SIZE;
		}
		if (iVER <= -67)
		{
			ar >> gDIM_FILSZ;
			ar >> gDIM_OFFSZ;
			ar >> gTXT_HEIGHT;
			ar >> gDIM_RADSZ;
		}
		if (iVER <= -70)
		{
			ar >> gDIM_SIZE;
		}
		if (iVER <= -72)
		{
			ar >> gDRILL_KS;
			ar >> gRIGID_MULTIPLIER;
			ar >> gVSTIFF_KS;
			ar >> gDEF_E;
			ar >> gDEF_V;
			ar >> gSTIFF_BDIA;
			ar >> gDEF_CTE;
			ar >> gDEF_THERM_LNK;
		}
		if (iVER <= -73)
		{
			ar >> gDEF_SOL_TOL;
		}
		if (iVER <= -74)
		{
			ar >> gDIM_PREC;
		}
		PropsT->Serialize(ar,iVER);
		MatT->Serialize(ar,iVER);
		ar>>DB_ObjectCount; //Change here
		ar>>iMeshCnt;
		ar>>iCurGp;
		ar>>iPtLabCnt;
		if (iVER <= -55)
			ar >> iTxtLabCnt;
		if (iVER <= -51)
			ar >> iCVLabCnt;
		ar>>iSFLabCnt;
		if (iVER <= -50)
			ar >> iPartLabCnt;
		if (iVER <= -51)
		{
			ar >> iCurMesh;
			ar >> iCurPart;
		}
		//Workplane 
		if (iVER <= -65)
		{
			WP_Object* pWP = (WP_Object*)DB_Obj[0];
			pWP->Serialize(ar, iVER);
			pWP->ReSize(WPSize);
		}
		for (i=1;i<DB_ObjectCount;i++)
		{
			ar>>iType;
			if (iVER < -52)
				ar >> iSecondaryType;
			else
				iSecondaryType = -1;
			switch(iType) 
			{
			case 0:
				DB_Obj[i] = new CvPt_Object;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 1:
				DB_Obj[i] = new Node;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 2 :
				DB_Obj[i] = new Line_Object;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 3 :
				DB_Obj[i] = new ContrPolyW;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 4 :
				DB_Obj[i] = new ME_Object;
				DB_Obj[i]->Serialize(ar, iVER);
				pM = (ME_Object*)DB_Obj[i];
				pM->UpdatePropRef(PropsT);
					//pM->Visable = TRUE;
				break;
			case 5 :
				DB_Obj[i] = new Symbol();
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 6:
				DB_Obj[i] = new Text();
				DB_Obj[i]->Serialize(ar, iVER);
				break;
			case 7 :
				if (iSecondaryType == 3)
					DB_Obj[i] = new NCircle;
				else if (iSecondaryType == 2)
					DB_Obj[i] = new NLine;
				else 
					DB_Obj[i] = new NCurve;
				DB_Obj[i]->Serialize(ar,iVER);
				//
				DB_Obj[i]->iObjType = iType;
				DB_Obj[i]->iType = iSecondaryType;
				break;
			case 8 :
				DB_Obj[i] = new NCircle;
				DB_Obj[i]->Serialize(ar,iVER);
				//Update for old file format can be removed latter
				DB_Obj[i]->iObjType = 7;
				DB_Obj[i]->iType = 3;
				break;
			case 9 :
				DB_Obj[i] = new NLine;
				DB_Obj[i]->Serialize(ar,iVER);
				//Update for old file format can be removed latter
				DB_Obj[i]->iObjType = 7;
				DB_Obj[i]->iType = 2;
				break;
			case 10:
				if (iSecondaryType == 0)
					DB_Obj[i] = new DIM();
				else if (iSecondaryType == 1)
					DB_Obj[i] = new DIMA();
				else if (iSecondaryType == 2)
					DB_Obj[i] = new DIMH();
				else if (iSecondaryType == 3)
					DB_Obj[i] = new DIMV();
				else if (iSecondaryType == 4)
					DB_Obj[i] = new DIMR();
				else if (iSecondaryType == 5)
					DB_Obj[i] = new DIMD();
				else if (iSecondaryType == 6)
					DB_Obj[i] = new DIMANG();
				else if (iSecondaryType == 7)
					DB_Obj[i] = new DIML();
				DB_Obj[i]->Serialize(ar, iVER);
				DB_Obj[i]->iObjType = iType;
				DB_Obj[i]->iType = iSecondaryType;
				DB_Obj[i]->Build();
				break;
			case 11 :
				DB_Obj[i] = new Surf_R;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 15 :
				if (iSecondaryType == 3)
					DB_Obj[i] = new NSurfR;
				else if (iSecondaryType == 2)
					DB_Obj[i] = new NSurfE;
				else
					DB_Obj[i] = new NSurf;
				DB_Obj[i]->Serialize(ar,iVER);
				//Update for old file format can be removed latter
				DB_Obj[i]->iObjType = iType;
				DB_Obj[i]->iType = iSecondaryType;
				break;
			case 16 :
				DB_Obj[i] = new NSurfR;
				DB_Obj[i]->Serialize(ar,iVER);
				DB_Obj[i]->iObjType = 15;
				DB_Obj[i]->iType = 3;
				break;	  
			case 17 :
				DB_Obj[i] = new NSurfE;
				DB_Obj[i]->Serialize(ar,iVER);
				DB_Obj[i]->iObjType = 15;
				DB_Obj[i]->iType = 2;
				break;
			case 20 :
				DB_Obj[i] = new Part();
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 200 :
				DB_Obj[i] = new Section;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 603 :
				DB_Obj[i] = new Sweep;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 604 :
				DB_Obj[i] = new SweepB;
				DB_Obj[i]->Serialize(ar,iVER);
				break;
			case 999:
				DB_Obj[i] = new BackGround(WPSize);
				DB_Obj[i]->Serialize(ar, iVER);
				break;
			case 500 :
				DB_Obj[i] = new WG_Def;
				DB_Obj[i]->Serialize(ar,iVER);
				pD = (WG_Def*) DB_Obj[i];
				pD->UpdatePropRef(PropsT);
				break;
			}
		}
		SaveGps(ar);
		pCurrentMesh=(ME_Object*) DB_Obj[1];
		outtext1("Searching for Mesh.");
		char S1[200];
		if (iCurMesh != -1)
		{
			for (i = 1; i < DB_ObjectCount; i++)
			{
				if ((DB_Obj[i]->iObjType == 4) && (DB_Obj[i]->iLabel == iCurMesh))
				{
					pCurrentMesh = (ME_Object*)DB_Obj[i];
					break;
				}
			}
		}
		sprintf_s(S1,"%s%s%s","Name : ",pCurrentMesh->sName," Active");
		outtext1(S1);

		pCurrentPart = NULL;
		outtext1("Searching for Part.");
		pCurrentPart = NULL;
		if (iCurPart != -1)
		{
			for (i = 1; i < DB_ObjectCount; i++)
			{
				if ((DB_Obj[i]->iObjType == 20) && (DB_Obj[i]->iLabel == iCurPart))
				{
					pCurrentPart = (Part*) DB_Obj[i];
					break;
				}
			}
		}
		if (pCurrentPart != NULL)
		{
			sprintf_s(S1, "%s%s%s", "Name : ", pCurrentPart->sName, " Active");
			outtext1(S1);
		}
		else
		{
			outtext1("ERROR: no active Part found.");
		}

		//iPtLabCnt=GetMaxPtLabCnt();
		sprintf_s(S1,"%s%i","Maximum Point Label  : ",iPtLabCnt);
		outtext1(S1);
		//iCVLabCnt=GetMaxCVLabCnt();	
		sprintf_s(S1,"%s%i","Maximum Curve Label  : ",iCVLabCnt);
		outtext1(S1);
		//iSFLabCnt=GetMaxSFLabCnt();
		sprintf_s(S1,"%s%i","Maximum Surface Label: ",iSFLabCnt);
		outtext1(S1);
		sprintf_s(S1, "%s%i", "Maximum Part Label: ", iPartLabCnt);
		outtext1(S1);
	}
}

int DBase::GetMaxPtLabCnt()
{
int i;
int irc=0;
for (i=1;i<DB_ObjectCount;i++)
{
  if (DB_Obj[i]->iObjType==0)
  {
    if (DB_Obj[i]->iLabel > irc)
      irc=DB_Obj[i]->iLabel;
  }
}
irc++;
return(irc);
}

int DBase::GetMaxTxtLabCnt()
{
	int i;
	int irc = 0;
	for (i = 1; i < DB_ObjectCount; i++)
	{
		if (DB_Obj[i]->iObjType == 6)
		{
			if (DB_Obj[i]->iLabel > irc)
				irc = DB_Obj[i]->iLabel;
		}
	}
	irc++;
	return(irc);
}

int DBase::GetMaxCVLabCnt()
{
int i;
int irc=1;
for (i=1;i<DB_ObjectCount;i++)
{
  if (DB_Obj[i]->iObjType==7)
  {
    if (DB_Obj[i]->iLabel > irc)
      irc=DB_Obj[i]->iLabel;
  }
}
irc++;
return(irc);
}

int DBase::GetMaxSFLabCnt()
{
int i;
int irc=1;
for (i=1;i<DB_ObjectCount;i++)
{
  if (DB_Obj[i]->iObjType==15)
  {
    if (DB_Obj[i]->iLabel > irc)
      irc=DB_Obj[i]->iLabel;
  }
}
irc++;
return(irc);
}


void DBase::SaveGps(CArchive& ar)
{
int i;
int iType[10];
int iLab[10];
int j;
int k;
int iNo;

G_Object* ptr;
int iLevs;

if (ar.IsStoring())
{
 ar<<iNoGPs;
 for (i=0;i<iNoGPs;i++)
 {
   ar<<Groups[i]->Title;
   iNo = Groups[i]->iNo;
   ar<<iNo;
   for (j=0;j<iNo;j++)
   {
		iLevs=0;
		ptr = Groups[i]->Objs[j];
		do
		{
			iLevs++;        //Count the levels of heiarachy
			ptr=ptr->pParent;
		}
		while (ptr!=NULL);
		ptr = Groups[i]->Objs[j];
		ar<<iLevs;
		for (k=0;k<iLevs;k++)
		{
			ar<<ptr->iObjType;
			ar<<ptr->iLabel;
			ptr=ptr->pParent;
		}
   }
 }
}
else
{
  ar>>iNoGPs;
  for (i=0;i<iNoGPs;i++)
  {
    Groups[i] = new ObjGp;
    ar>>Groups[i]->Title;
    ar>>iNo;
	for (j=0;j<iNo;j++)
	{
    ar>>iLevs;
	  for (k=0;k<iLevs;k++)
	  {
         ar>>iType[iLevs-k-1];
         ar>>iLab[iLevs-k-1];
	  }
	  ptr = GetObj(iType[0],iLab[0]); //Top level object
    if (ptr != NULL)
    {
      for (k = 1; k < iLevs; k++)
      {
        ptr = ptr->GetObj(iType[k], iLab[k]);
      }
    }
    if (ptr!=NULL) 
	  {
         Groups[i]->Add(ptr);
	  }
	}
    
  }
}
}



void DBase::Dsp_Add(G_Object* pDspObject)
{
  {
	  pDspObject->SetToScr(&pModelMat,&pScrMat);
    Dsp_List[iDspLstCount]=pDspObject;
    iDspLstCount++;
  }
}



void DBase::Dsp_All()
{
iDspLstCount = 0;
bDispAll=TRUE;
int iCO;
for (iCO=0;iCO<DB_ObjectCount;iCO++)
  {
	if (DB_Obj[iCO]->Visable==1)
       Dsp_Add(DB_Obj[iCO]);  
  }
InvalidateOGL();

}

void DBase::Dsp_ShowAll()
{

	int iCO;
	for (iCO = 0; iCO < DB_ObjectCount; iCO++)
	{
		DB_Obj[iCO]->Visable = 1;
	}
	Dsp_All();
	ReDraw();
}

void DBase::Dsp_Hide()
{
	int iCO;
	if (S_Count > 0)
	{
		for (iCO = 0; iCO < S_Count; iCO++)
		{
			S_Buff[iCO]->Visable = 0;
		}
	}
	S_Des();
	Dsp_All();
	ReDraw();
}

void DBase::Info()
{
int iCO;
for (iCO=0;iCO<S_Count;iCO++)
{
  S_Buff[iCO]->Info();
}
}



      //pointer to current mesh
void DBase::SetCurMesh()
{

if (S_Count>0)
{
  if (S_Buff[S_Count-1]->iObjType == 4)
  {
    pCurrentMesh = 	(ME_Object*) S_Buff[S_Count-1];
	outtext1("Mesh Set as Active.");
  }
  else
  {
    outtext1("ERROR: Invalid Selection.");
  }
}
else
{
  outtext1("ERROR: Invalid Selection.");
}
}


void DBase::Dsp_CurMesh()
{

if (pCurrentMesh!=NULL)
{
  iDspLstCount = 0;
  Dsp_Add(pCurrentMesh);
  InvalidateOGL();
  ReDraw();
}
}


void DBase::Dsp_Selected()
{

bDispAll=FALSE;
int iCO;
iDspLstCount = 0;
Dsp_Add(DB_Obj[0]);
if (S_Count>0)
{
  for (iCO=0;iCO<S_Count;iCO++)
  {
	Dsp_Add(S_Buff[iCO]);
  }
}
InvalidateOGL();
ReDraw();
}


void DBase::Dsp_Rem(G_Object* gIn)
{
int i;
for (i=0;i<iDspLstCount;i++)
{
  if (Dsp_List[i]==gIn)
  {
    Dsp_List[i]=Dsp_List[iDspLstCount-1];
    iDspLstCount--;
    break;
  }
}
if (gIn!=NULL)
  RemTempGraphics(gIn);
}


void DBase::Dsp_Cat()
{
iDspLstCount = 0;
if (MeshCat!=NULL)
{
  Dsp_Add(MeshCat);
}	  
InvalidateOGL();
ReDraw();
}

void DBase::Dsp_Next()
{
if (MeshCat!=NULL)
{
  MeshCat->Next();
}
InvalidateOGL();
ReDraw();
}

void DBase::Dsp_Prev()
{
if (MeshCat!=NULL)
{
  MeshCat->Previous();
}
InvalidateOGL();
ReDraw();
}


void DBase::WPMode()
{
  WP_Object* pWPlane =(WP_Object*) DB_Obj[iWP];
  if (pWPlane->iWPMode==0) 
  {
    pWPlane->iWPMode=1;
    outtext1("Workplain Mode Cylindrical.");
  }
  else
  {
    pWPlane->iWPMode=0;
    outtext1("Workplain Mode Rectangular.");
  }
InvalidateOGL();
ReDraw();
}

void DBase::Ortho()
{
	
	if (gORTHO)
	{
		gORTHO = TRUE;
		outtext1("Orthogonal Drawing Mode ON.");
	}
	else
	{
		gORTHO = FALSE;
		outtext1("Orthogonal Drawing Mode OFF.");
	}
}


void DBase::CreateWP(double dWPSize)
{
WP_Object* TheWP= new WP_Object;
TheWP->Create(dWPSize);
iWP = DB_ObjectCount;
DB_Obj[DB_ObjectCount] =TheWP ;
DB_ObjectCount++;
}


ME_Object* DBase::CreateMesh(CString inName)
{
pCurrentMesh = new ME_Object;
pCurrentMesh->Create(inName,NULL,iMeshCnt);
iMeshCnt++;
return (pCurrentMesh);
}

void DBase::SetWPSize(double dSize)
{
WPSize = dSize;
WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
pWPlane->ReSize(dSize);
ReCalcScreenMat();
InvalidateOGL();
ReGen();
}

void DBase::SetWPMode(int iMode)
{
WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];

if (iMode == 0)
  {
  pWPlane->iWPMode = 0;
  }
else
  {
  pWPlane->iWPMode = 1;
  }
}



C3dVector DBase::CylToCart(C3dVector InPt)
{
double Pi = 3.1415926535;

C3dVector vCart;
vCart.x = InPt.x * cos(InPt.y * (2 * Pi)/360);
vCart.y = InPt.x * sin(InPt.y * (2 * Pi)/360);
vCart.z = InPt.z;
return (vCart);
}

C3dVector DBase::CartToCyl(C3dVector InPt)
{

C3dVector vCyl;
if ((InPt.x==0) &&
    (InPt.x==0) &&
    (InPt.x==0))
{
  vCyl.x =0;
  vCyl.y =0;
  vCyl.z =0;
}
else
{
  vCyl.x = pow(InPt.x * InPt.x + InPt.y * InPt.y,0.5);
  vCyl.y = atan2(InPt.y,InPt.x)*180/Pi;
  vCyl.z = InPt.z;
}
return (vCyl);
}



void DBase::AddNode(C3dVector InPt, int iLab,int i2,int i3, int iC,int iDef,int iOut)
{

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
Node* cAddedNode;
if (iLab == -1)
{
  iLab=pCurrentMesh->iNodeLab;
}
cAddedNode = pCurrentMesh->AddNode(InPt,iLab,i2,i3,iC,iDef,iOut);
pCurrentMesh->iNodeLab++;
AddTempGraphics(cAddedNode);
Dsp_Add(cAddedNode);
ReDraw();
}

C3dMatrix DBase::GetNodalSys(Node* pN)
{
C3dMatrix mRC;

ME_Object* ME=(ME_Object*) pN->pParent;
if (ME!=NULL)
{
  mRC=ME->GetNodalSys(pN);
}
return (mRC);
}



void DBase::AddFluxQ(ObjList* Nodes,double T)
{
int i;
if (pCurrentMesh->iCurLC!=-1)
{
  for (i=0;i<Nodes->iNo;i++)
  { 
   if (Nodes->Objs[i]->iObjType==1)
   {
     Node* pN = (Node*) Nodes->Objs[i];
     ME_Object* ME= (ME_Object*) pN->pParent;
     G_Object* cAddedT;
     cAddedT = ME->AddFluxQ((Node*) pN, T,-1);
     if (cAddedT!=NULL)
     {
        Dsp_Add(cAddedT);
        AddTempGraphics(cAddedT);
	 }
   }
  }
  ReDraw();
}
else
{
  outtext1("ERROR: No Load Set is Active.");
}
}

void DBase::AddTemperatureBC(ObjList* Nodes,double T)
{
int i;
int iSet;
if (pCurrentMesh->iCurBC!=-1)
{
  for (i=0;i<Nodes->iNo;i++)
  { 
   if (Nodes->Objs[i]->iObjType==1)
   {
     Node* pN = (Node*) Nodes->Objs[i];
     ME_Object* ME= (ME_Object*) pN->pParent;
     G_Object* cAddedT;
	 iSet = ME->GetTSETID(ME->iCurTSet);
     cAddedT = ME->AddTemperatureBC((Node*) pN, T,-iSet);
     if (cAddedT!=NULL)
     {
        Dsp_Add(cAddedT);
        AddTempGraphics(cAddedT);
	 }
   }
  }
  ReDraw();
}
else
{
  outtext1("ERROR: No Boundary Set is Active.");
}
}

void DBase::AddTemperature(ObjList* Nodes,double T)
{
int i;
if (pCurrentMesh->iCurTSet!=-1)
{
  for (i=0;i< Nodes->iNo;i++)
  { 
   if (Nodes->Objs[i]->iObjType==1)
   {
     Node* pN = (Node*)Nodes->Objs[i];
     ME_Object* ME= (ME_Object*) pN->pParent;
     G_Object* cAddedT;
     cAddedT = ME->AddTemperature((Node*) pN, T,-1);
     if (cAddedT!=nullptr)
     {
        Dsp_Add(cAddedT);
        AddTempGraphics(cAddedT);
	 }
   }
  }
  ReDraw();
}
else
{
  outtext1("ERROR: No Temperature Set is Active.");
}
}

void DBase::AddTEMPD(double T)
{
	int i;
	int iSID = -1;
	double dT;
	BOOL bIsTempD = FALSE;
	cLinkedList* pS = nullptr;
	if (pCurrentMesh->iCurTSet != -1)
	{
		iSID = pCurrentMesh->GetTSETID(pCurrentMesh->iCurTSet);
		pS = pCurrentMesh->GetTSET(iSID);
		bIsTempD = pCurrentMesh->TSEThasTEMPD(pS, dT);
		if (bIsTempD)
			outtext1("ERROR: TEMPD card already exists.");
		else
		   G_Object* pT = pCurrentMesh->AddTempD(T, iSID);
	}
	else
	{
		outtext1("ERROR: No Temperature Set is Active.");
	}
}

void DBase::AddGrav(double dScl, C3dVector Vec)
{
	int i;
	int iSID = -1;
	double dT;
	GRAV* pGrav = nullptr;
	cLinkedList* pS = nullptr;
	if (pCurrentMesh->iCurLC != -1)
	{
		iSID = pCurrentMesh->GetLCID(pCurrentMesh->iCurLC);
		pS = pCurrentMesh->GetLC(iSID);
		pGrav = pCurrentMesh->LSEThasGRAV(pS);
		if (pGrav!=nullptr)
			outtext1("ERROR: GRAV card already exists in this Load Set.");
		else
		    G_Object* pT = pCurrentMesh->AddGRAV(iSID, 0, dScl, Vec);
	}
	else
	{
		outtext1("ERROR: No Load Set is Active.");
	}
}



void DBase::AddRotAccel(ObjList* Elements, double dw, C3dVector vAP1, C3dVector vAP2)
{
  int i;
  C3dVector vAxisD;
  C3dVector vAxisC;
  vAxisC = vAP1;
  vAxisD = vAP2;
  vAxisD -= vAP1;
  vAxisD.Normalize();
  if (pCurrentMesh->iCurLC != -1)
  {
    for (i = 0; i<Elements->iNo; i++)
    {
      if (Elements->Objs[i]->iObjType == 3)
      {
        E_Object* pE = (E_Object*)Elements->Objs[i];
        ME_Object* ME = (ME_Object*)pE->pParent;
        G_Object* cAddedA;
        cAddedA = ME->AddRotAccel((E_Object*)pE, vAxisD, vAxisC, dw, -1);
        if (cAddedA != NULL)
        {
          Dsp_Add(cAddedA);
          AddTempGraphics(cAddedA);
        }
      }
    }
    ReDraw();
  }
  else
  {
    outtext1("ERROR: No Load Set is Active.");
  }
}

void DBase::AddAccel(ObjList* Elements,C3dVector vA)
{
int i;
if (pCurrentMesh->iCurLC!=-1)
{
  for (i=0;i<Elements->iNo;i++)
  { 
   if (Elements->Objs[i]->iObjType==3)
   {
     E_Object* pE = (E_Object*) Elements->Objs[i];
     ME_Object* ME= (ME_Object*) pE->pParent;
     G_Object* cAddedA;
     cAddedA = ME->AddAccel((E_Object*) pE, vA,-1);
     if (cAddedA!=NULL)
     {
        Dsp_Add(cAddedA);
        AddTempGraphics(cAddedA);
	 }
   }
  }
  ReDraw();
}
else
{
  outtext1("ERROR: No Load Set is Active.");
}
}


void DBase::AddForce(ObjList* Nodes,C3dVector F)
{
int i;
int iSet;
C3dMatrix TMat;
TMat.MakeUnit();
if (pCurrentMesh->iCurLC!=-1)
{
for (i=0;i<Nodes->iNo;i++)
{ 
 if (Nodes->Objs[i]->iObjType==1)
 {
   Node* pN = (Node*) Nodes->Objs[i];
   if (pN->pParent!=NULL)
   {
    if (pN->pParent->iObjType==4)
	  {
      if (pN->OutSys!=0)
      {
        TMat=GetNodalSys(pN);
      }
	    ME_Object* ME= (ME_Object*) pN->pParent;
        G_Object* cAddedF;
		iSet = ME->GetLCID(ME->iCurLC);
        cAddedF = ME->AddForce((Node*) pN, TMat*F, iSet);
		if (cAddedF!=NULL)
		{
          Dsp_Add(cAddedF);
          AddTempGraphics(cAddedF);
		}
	  }
   }
 }
}
ReDraw();
}
else
{
  outtext1("ERROR: No Load Set is Active.");
}
}


void DBase::AddMoment(ObjList* Nodes,C3dVector F)
{
int i;
int iSet;
C3dMatrix TMat;
TMat.MakeUnit();
if (pCurrentMesh->iCurLC!=-1)
{
for (i=0;i<Nodes->iNo;i++)
{ 
 if (Nodes->Objs[i]->iObjType==1)
 {
   Node* pN = (Node*) Nodes->Objs[i];

   if (pN->pParent!=NULL)
   {
    if (pN->pParent->iObjType==4)
	  {
      if (pN->OutSys!=0)
      {
        TMat=GetNodalSys(pN);
      }
        ME_Object* ME= (ME_Object*) pN->pParent;
        G_Object* cAddedF;
		iSet = ME->GetLCID(ME->iCurLC);
        cAddedF = ME->AddMoment((Node*) pN, TMat*F,iSet);
		if (cAddedF!=NULL)
		{
          Dsp_Add(cAddedF);
          AddTempGraphics(cAddedF);
		}
	  }
   }
 }
}
ReDraw();
}
else
{
  outtext1("ERROR: No Load Set is Active.");
}
}


//***************************************************************************
//                     SOLID ELEMENT SHELL COAT
//***************************************************************************

void DBase::ShellSolids(ObjList* Els,int iCol)
{
int i;
E_Object* pRet;
FreeFaceDsp(Els);
Node* pENodes[100];
eFace* pNext;
pNext=pCurrentMesh->FcList->Head;
while (pNext!=NULL)
{
  for (i=0;i<pNext->NoVert;i++)
  {
    pENodes[i]=pNext->pVertex[i];
  }
  if (pNext->NoVert==4)
  {
    pRet = pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,iCol,94,-1,-1,4,1,1,1,FALSE,-1,0); 
  }
  else
  {
    pRet = pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,iCol,91,-1,-1,3,1,1,1,FALSE,-1,0); 
  }
  pRet->Reverse();
  pCurrentMesh->iElementLab++;
  pNext=(eFace*) pNext->next;
}

InvalidateOGL();
ReDraw();
}

//***************************************************************************
//                    SPLIT QUAD ELEMENT INTO TRI'S
//no check for quality yet TODO
//***************************************************************************
void DBase::QuadToTri(ObjList* Els)
{
E_Object* pRet;
Node* pENodes[100];
int i;
ObjList* Els2  = new ObjList();
for (i=0;i<Els->iNo;i++)
{ 
  if ((Els->Objs[i]->iObjType==3) && (Els->Objs[i]->pParent==this->pCurrentMesh))
  {
     E_Object* pE = (E_Object*) Els->Objs[i];
	 if (pE->iType==94)
	 { 
        Els2->Add(pE);
	 }
  }
}
//Create new tri elements
for (i=0;i<Els2->iNo;i++)
{
  //Check best diagonal to split along
  //if corner 013 angle greater than 012
  C3dVector v0; C3dVector v1; C3dVector v2; C3dVector v3;
  C3dVector vA; C3dVector vB;
  double dA1; double dA2;
  E_Object4* pE = (E_Object4*) Els2->Objs[i];
  v0=pE->pVertex[0]->Get_Centroid();
  v1=pE->pVertex[1]->Get_Centroid();
  v2=pE->pVertex[2]->Get_Centroid();
  v3=pE->pVertex[3]->Get_Centroid();
vA=v1; vA-=v0; vA.Normalize();
vB=v3; vB-=v0; vB.Normalize();
dA1=acos(vA.Dot(vB));
vA=v0; vA-=v1; vA.Normalize();
vB=v2; vB-=v1; vB.Normalize();
dA2=acos(vA.Dot(vB));
  if (dA1>dA2)
  {
    pENodes[0]=pE->pVertex[0];
    pENodes[1]=pE->pVertex[1];
    pENodes[2]=pE->pVertex[2];
    pRet = pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,pE->iColour,91,pE->PID,pE->iMatID,3,1,1,1,FALSE,pE->iMCys,pE->MAng); 
    pCurrentMesh->iElementLab++;
    Dsp_Add(pRet);
    pENodes[0]=pE->pVertex[0];
    pENodes[1]=pE->pVertex[2];
    pENodes[2]=pE->pVertex[3];
    pRet = pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,pE->iColour,91,pE->PID,pE->iMatID,3,1,1,1,FALSE,pE->iMCys,pE->MAng); 
    pCurrentMesh->iElementLab++;
    Dsp_Add(pRet);
  }
  else
  {
    pENodes[0]=pE->pVertex[0];
    pENodes[1]=pE->pVertex[1];
    pENodes[2]=pE->pVertex[3];
    pRet = pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,pE->iColour,91,pE->PID,pE->iMatID,3,1,1,1,FALSE,pE->iMCys,pE->MAng); 
    pCurrentMesh->iElementLab++;
    Dsp_Add(pRet);
    pENodes[0]=pE->pVertex[1];
    pENodes[1]=pE->pVertex[2];
    pENodes[2]=pE->pVertex[3];
    pRet = pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,pE->iColour,91,pE->PID,pE->iMatID,3,1,1,1,FALSE,pE->iMCys,pE->MAng); 
    pCurrentMesh->iElementLab++;
    Dsp_Add(pRet);

  }
}
//Delete quad elements
for (i=0;i<Els2->iNo;i++)
{
  E_Object4* pE = (E_Object4*) Els2->Objs[i];
  //RemObj(pE);
  Dsp_Rem(pE);
  Dsp_RemGP(pE);
  pCurrentMesh->DeleteEl(pE);
  Els2->Objs[i]=NULL;
}
Els->Clear();
delete(Els2);
InvalidateOGL();
ReDraw();
}

E_Object* DBase::GetElRelEdge(ObjList* pFrom, Node* N1, Node* N2)
{
  E_Object* pE = NULL;
  E_Object* pRet = NULL;
  int i;
  for (i = 0; i<pFrom->iNo; i++)
  {
    pE = (E_Object*)pFrom->Objs[i];
    if ((pE->NodeInEl(N1)) && (pE->NodeInEl(N2)))
    {
      pRet = pE;
      break;
    }
  }
  return (pRet);
}

//***************************************************************************
//                    SPLIT QUAD ELEMENT INTO TRI'S
//no check for quality yet TODO
//***************************************************************************

void DBase::ShellNormConsistancy(ObjList* Els)
{
int i;
ObjList* Els2  = new ObjList();
for (i=0;i<Els->iNo;i++)
{ 
  if ((Els->Objs[i]->iObjType==3) && (Els->Objs[i]->pParent==this->pCurrentMesh))
  {
     E_Object* pE = (E_Object*) Els->Objs[i];
	 if ((pE->iType==91) || (pE->iType==94))
	 { 
        Els2->Add(pE);
	 }
  }
}
int iN;
int iDir;
eEdge* pLk;
if (Els2->iNo>0)
{
  E_Object* pE = (E_Object*) Els2->Objs[0];
  Els2->Remove(pE);
  eEdgeList* LkList = new eEdgeList();
  eEdge* Lk[200];
  iN = pE->GetLinkList(Lk);
  LkList->AddGp(iN,Lk);
  int ii;
  do
  {
    pLk = LkList->pCur;
    if (pLk == NULL)
      break;
    pE = GetElRelEdge(Els2, pLk->pVertex[0], pLk->pVertex[1]);
    if (pE == NULL)
    {
      LkList->Remove(pLk);
    }
    else
    {
      ii = pE->iLabel;
      Els2->Remove(pE);
      iN = pE->GetLinkList(Lk);
      for (i = 0; i < iN; i++)
      {
        iDir = pLk->isSameWithDir(Lk[i]);
        if (iDir != 0)
          break;
      }
      if (iDir == 1) //The same direction we must reverse the element
      {
        pE->Reverse();
        iN = pE->GetLinkList(Lk);
      }
      LkList->AddGp(iN, Lk);
      //LkList->Remove(pLk);
    }

  } 
  while (LkList->iNo>0);

  delete (LkList);
}
else
{
  outtext1("ERROR: No Valid Elements Selected.");
}
delete(Els2);
InvalidateOGL();
ReDraw();
}

//***************************************************************************
// PRE: Elements to check are in 2d XY plain
// POST: Group of valid elements returned else NULL
//***************************************************************************
CONST double dNd2dTol = 0.0000001;
ObjList* DBase::is2D(ObjList* Els, double &dxMin, double &dyMin, double &dxMax, double &dyMax)
{
	char S1[200];
	BOOL brc = TRUE;
	BOOL bShellFail = FALSE;
	int i;
	int j;
	E_Object* pE;
	Node* pN;
	ObjList* Els2 = new ObjList();
	for (i = 0; i < Els->iNo; i++)
	{
		if (Els->Objs[i]->iObjType == 3) 
		{
			E_Object* pE = (E_Object*)Els->Objs[i];
			if ((pE->iType == 91) || (pE->iType == 94))
			{
				Els2->Add(pE);
			}
			else
			{
				bShellFail = TRUE;
				brc = FALSE;
			}
		}
	}
	for (i = 0; i < Els2->iNo; i++)
	{
		pE = (E_Object*) Els2->Objs[i];
		for (j = 0; j < pE->iNoNodes; j++)
		{
			pN = (Node*) pE->GetNode(j);
			if ((pN->Pt_Point->z > -dNd2dTol) && (pN->Pt_Point->z < dNd2dTol))
			{
				if (pN->Pt_Point->x > dxMax)
					dxMax = pN->Pt_Point->x;
				if (pN->Pt_Point->x < dxMin)
					dxMin = pN->Pt_Point->x;
				if (pN->Pt_Point->y > dyMax)
					dyMax = pN->Pt_Point->y;
				if (pN->Pt_Point->y < dyMin)
					dyMin = pN->Pt_Point->y;
			}
			else
			{
				sprintf_s(S1, "ERROR: Element %i Fails Planality Check.", pE->iLabel);
				outtext1(S1);
				brc = FALSE;
				break;
			}
		}
	}



	if (bShellFail)
		outtext1("WARNING: Only 2d Shell Elements are Considered.");
	
	if (!brc)
	{
	   delete(Els2);
	   Els2 = NULL;
	}
	return (Els2);
}


//***************************************************************************
// PRE: Elements to calculate section propertiess; A,Ixx,Iyy,Izz,Xbar,YBar
// POST: Properties listed to list window
//***************************************************************************
void DBase::SectionProps(ObjList* Els)
{
	NLine* lx;
	NLine* ly;
	double dxs, dys;
	char S1[200];
	int i;
	double dA; //Area
	double dATot = 0;
	double dIx = 0; //First Moment of Area About X-X;
	double dIy = 0; //First Moment of Area About Y-Y;
	double dIxx = 0; //Second Moment of Area About X-X;
	double dIyy = 0; //Second Moment of Area About Y-Y;
	double dIzz = 0; //Polor Second Moment of Area;
	double xbar;
	double ybar;
	E_Object* pE;
	E_Object3* pE3;
	E_Object4* pE4;
	C3dVector vC;
	ObjList* Els2;
	double dxMin, dyMin, dxMax, dyMax;
	dxMin = 1e36; dxMax = -1e36;
	dyMin = 1e36; dyMax = -1e36;
	Els2 = is2D(Els, dxMin, dyMin, dxMax, dyMax);
	dxs = 0.6*(dxMax - dxMin);
	dys = 0.6*(dyMax - dyMin);
	if (Els2 == NULL)
	{
		outtext1("ERROR: Property Check Failed");
	}
	else
	{   //First Moment of Area Calculation about X-X & Y-Y
		for (i = 0; i < Els2->iNo; i++)
		{
			pE = (E_Object*)Els2->Objs[i];
			if (pE->iType == 91)
			{
				pE3 = (E_Object3*) pE;
				dA = pE3->GetArea2d();
			}
			else if (pE->iType == 94)
			{
				pE4 = (E_Object4*) pE;
				dA = pE4->GetArea2d();
			}
			dATot += dA;
			//First Moment of Area about X-X & Y-Y
			vC = pE->Get_Centroid();
			dIx += dA * vC.y;
			dIy += dA * vC.x;
			//Line  in X
		}
		xbar = dIy / dATot;
		ybar = dIx / dATot;
		//Second Moment of Area Calculation about Centriod xbar,ybar
		for (i = 0; i < Els2->iNo; i++)
		{
			pE = (E_Object*)Els2->Objs[i];
			if (pE->iType == 91)
			{
				pE3 = (E_Object3*)pE;
				dA = pE3->GetArea2d();
			}
			else if (pE->iType == 94)
			{
				pE4 = (E_Object4*)pE;
				dA = pE4->GetArea2d();
			}
			//Second Moment of Area about Centroid
			vC = pE->Get_Centroid();
			dIxx += dA * (vC.y-ybar)*(vC.y - ybar);
			dIyy += dA * (vC.x-xbar)*(vC.x - xbar);
		}
		dIzz = dIxx + dIyy;
		sprintf_s(S1, "2d Section Properties in X-Y Plane");
		outtext1(S1);
		sprintf_s(S1, "Total Area A: %g", dATot);
		outtext1(S1);
		sprintf_s(S1, "Centroid X: %g", xbar);
		outtext1(S1);
		sprintf_s(S1, "Centroid Y: %g", ybar);
		outtext1(S1);
		sprintf_s(S1, "Second Moments of Area about Centroid");
		outtext1(S1);
		sprintf_s(S1, "Ixx: %g", dIxx);
		outtext1(S1);
		sprintf_s(S1, "Iyy: %g", dIyy);
		outtext1(S1);
		sprintf_s(S1, "Izz: %g", dIzz);
		outtext1(S1);
		lx= AddLNbyXYZ(xbar-dxs, ybar, 0, xbar + dxs, ybar, 0,151);
		ly= AddLNbyXYZ(xbar, ybar-dys, 0, xbar, ybar + dys, 0,151);
		lx->iLnThk = 5;
		ly->iLnThk = 5;
	}

	//Dsp_Add(pCurrentMesh->LkList);
	//InvalidateOGL();
	//ReDraw();
	if (Els2!=NULL)
		delete(Els2);

}

//***************************************************************************
//                     FREE FACE AND EDGE DISPLAYS
//***************************************************************************
void DBase::FreeEdgeDsp(ObjList* Els)
{
int i;
eEdgeList* LkList=NULL;
ObjList* Els2  = new ObjList();
for (i=0;i<Els->iNo;i++)
{ 
  if ((Els->Objs[i]->iObjType==3) && (Els->Objs[i]->pParent==this->pCurrentMesh))
  {
     E_Object* pE = (E_Object*) Els->Objs[i];
	 if ((pE->iType==11) || (pE->iType==21) || (pE->iType==122) ||
		 (pE->iType==91) || (pE->iType==94))
	 { 
        Els2->Add(pE);
	 }
  }
}
if (Els2->iNo > 0)
{
	LkList = FindEdges(Els2);
}
else
{
	outtext1("ERROR: No Valid Elements Selected.");
}
if (pCurrentMesh->LkList!=NULL)
{
	Dsp_Rem(pCurrentMesh->LkList);
	RemTempGraphics(pCurrentMesh->LkList);
    delete(pCurrentMesh->LkList);
    pCurrentMesh->LkList=NULL;
}
if ((pCurrentMesh->LkList == NULL) && (LkList != NULL))
{
	pCurrentMesh->LkList = LkList;
	//Dsp_Add(pCurrentMesh->LkList);
	eEdge* pNext = LkList->Head;
	while (pNext != NULL)
	{
		Dsp_Add(pNext);
		pNext = (eEdge*)pNext->next;
	}
	InvalidateOGL();
	ReDraw();
}
delete(Els2);
}

//Find element free edges
eEdgeList* DBase::FindEdges(ObjList* Els)
{
	eEdge* Lk[200];
	int iN;
	int i;
	int j;
	eEdgeList* LkList = new eEdgeList();
	for (i = 0; i < Els->iNo; i++)
	{
		E_Object* pE = (E_Object*)Els->Objs[i];
		iN = pE->GetLinkList(Lk);
		for (j = 0; j < iN; j++)
		{
			Lk[j]->iColour = 0;
			LkList->AddIncOnly(Lk[j]);
		}
	}
	LkList->Purge();
	return (LkList);
}

void DBase::FreeFaceDsp(ObjList* Els)
{
int i;
ObjList* Els2  = new ObjList();
for (i=0;i<Els->iNo;i++)
{ 
  if ((Els->Objs[i]->iObjType==3) && (Els->Objs[i]->pParent==this->pCurrentMesh))
  {
     E_Object* pE = (E_Object*) Els->Objs[i];
	 if ((pE->iType==111) || (pE->iType==112) || (pE->iType==115))
	 { 
        Els2->Add(pE);
	 }
  }
}
if (pCurrentMesh->FcList!=NULL)
{
   delete(pCurrentMesh->FcList);
   pCurrentMesh->FcList=NULL;
}
if (pCurrentMesh->FcList==NULL)
  pCurrentMesh->FcList=new eFaceList();
eFace* Fc[8];
int iN;
int j;
for(i=0;i<Els2->iNo;i++)
{
  E_Object* pE = (E_Object*) Els2->Objs[i];
  iN = pE->GetfaceList(Fc);
  for (j=0;j<iN;j++)
  {
    pCurrentMesh->FcList->Add(Fc[j]);
  }
}
delete(Els2);


//Dsp_Add(pCurrentMesh->LkList);
eFace* pNext = pCurrentMesh->FcList->Head;
while (pNext != NULL)
{
	Dsp_Add(pNext);
	pNext = (eFace*)pNext->next;
}
InvalidateOGL();
ReDraw();
}


//***************************************************************************
//                     MASS CHECK
//***************************************************************************
void DBase::ElMass(ObjList* Els)
{
  char S1[200] = "";
  int i;
  int j;
  Mat mm;
  double dM=0;
  C3dVector vC;
  double mx = 0;
  double my = 0;
  double mz = 0;
  //monents of inertia about origin in basic cys
  double Ixx = 0;
  double Iyy = 0;
  double Izz = 0;
  double Ixy = 0;
  double Ixz = 0;
  double Iyz = 0;

  for (i = 0; i<Els->iNo; i++)
  {
    E_Object* pE = (E_Object*)Els->Objs[i];
    mm=pE->GetElNodalMass(PropsT, MatT);
	
    for(j=0;j<pE->iNoNodes;j++)
    {
	  vC = pE->GetNode(j)->Get_Centroid();
	  vC = GlobaltoWP(vC);
	  mx += *mm.mn(j + 1, 1) * vC.x;
	  my += *mm.mn(j + 1, 1) * vC.y;
	  mz += *mm.mn(j + 1, 1) * vC.z;
      dM+= *mm.mn(j+1, 1);
	  //Mass Inertia Matrix Calculation
	  Ixx += *mm.mn(j + 1, 1) * (vC.y * vC.y + vC.z * vC.z);
	  Iyy += *mm.mn(j + 1, 1) * (vC.x * vC.x + vC.z * vC.z);
	  Izz += *mm.mn(j + 1, 1) * (vC.x * vC.x + vC.y * vC.y);
	  Ixy -= *mm.mn(j + 1, 1) * vC.x * vC.y;
	  Ixz -= *mm.mn(j + 1, 1) * vC.x * vC.z;;
	  Iyz -= *mm.mn(j + 1, 1) * vC.y * vC.z;;
    }
    mm.clear();
  }
  outtext1("ELEMENT MASS SUMATION IN WP COORDINATES");
  sprintf_s(S1, "Number off Elements summed: %i", Els->iNo);
  sprintf_s(S1, "CofG X,Y,Z : %g,%g,%g", mx/dM, my / dM, mz / dM);
  outtext1(S1);
  outtext1("Mass Moment of Inertia");
  sprintf_s(S1, "Ixx : %g", Ixx);
  outtext1(S1);
  sprintf_s(S1, "Iyy : %g", Iyy);
  outtext1(S1);
  sprintf_s(S1, "Izz : %g", Izz);
  outtext1(S1);
  sprintf_s(S1, "Ixy : %g", Ixy);
  outtext1(S1);
  sprintf_s(S1, "Ixz : %g", Ixz);
  outtext1(S1);
  sprintf_s(S1, "Iyz : %g", Iyz);
  outtext1(S1);
  sprintf_s(S1, "Mass Total: %g", dM);
  outtext1(S1);
}

//***************************************************************************
//           AUTO TET MESH FROM SHELL ELEMENT BOUNDARY
//***************************************************************************
void DBase::MeshTET(ObjList* Els,double G)
{
//Els is initial closed boundary all normal pointing into domain
//Basic checks pn front to be done here
int i;
int j;

BOOL bGo=TRUE;
cLinkedList* pNodes = new cLinkedList();
cLinkedList* Els2  = new cLinkedList();
for (i=0;i<Els->iNo;i++)
{ 
  if (Els->Objs[i]->iObjType==3) 
  {
     E_Object* pE = (E_Object*) Els->Objs[i];
	 if (pE->iType!=91)
	 {
		outtext1("ERROR: Only Tri Elements Allowed.");
		bGo=FALSE;
		break;
	 }
	 else if (pE->pParent!=this->pCurrentMesh)
	 {
     outtext1("ERROR: All Tri Elements Must be From the Same Mesh.");
	   bGo=FALSE;
	   break;
	 }
	 else
	 {
		E_Object3* pE3 = (E_Object3*) pE;//pE->Copy(pCurrentMesh);
		Els2->Add(pE3);
		 for (j=0;j<3;j++)
           pNodes->AddEx(pE3->pVertex[j]);
	 }
  }
}
if (bGo)
{
	Els->Clear();
	this->Dsp_All();
	this->ReDraw();
	AdvancingTet(Els2, pNodes, G);
}
// dont delete delete(Els) as will get deleted in the menu command
delete(pNodes);
delete(Els2);
}

//*********************************************************************************
//*********************************************************************************
//       A D V A N C I N G   F R O N T   M E S H   G E N E R A T O R
//*********************************************************************************
//*********************************************************************************
void DBase::AdvancingTet(cLinkedList* fEls, cLinkedList* fNodes, double dG)
{
	double dMinAng = 25;  //Minimum internal angle for acceptance
	char S1[200] = "";
	E_Object3* pE = NULL;
	int i;
	int iTT = 0;
	int ii = 0;
	int isc = 0;
	int itry;
	double dC;
	double dTgt = GetTargetElSize(fEls);
	double dMaxAng;
	int iNoElsGen = 0;
	Node* nNode;
	Node* nNodeTry;
	C3dVector vC;
	C3dVector vCF;
	C3dVector vN;
	C3dVector vB;
	C3dVector vT;
	BOOL bV;
	BOOL bExit = FALSE;
	BOOL bReTry = FALSE;
	BOOL bIsTet = FALSE;
	double dAdjAng = 0;
	E_Object3* pAdjEl = NULL;
	//Clear what been selected for bebud purposes at moment
	this->S_Des();
	OTemp->Clear();
	OTemp2->Clear();
	ObjList* pCandidateNodes = new ObjList();
	ObjList* pFrontNodes = new ObjList();
	ObjList* pCandidateFaces = new ObjList();
	ObjList* pAdjFaces = new ObjList();
	E_Object34* eTET = new E_Object34();
	outtext1("**** I N   T E T   G E N E R A T O R ****");
	E_Object3* pIntFace;
	//fEls->MinSizeSort();
	bExit = FALSE;
	ZeroRemeshFlg(fEls);
	//****************************************************************************
	do
	{
		if (iTT == 703)
			iTT = iTT;
		bReTry = FALSE;
		pIntFace = NULL;
		dMaxAng = 0;
		bIsTet = FALSE;
		pE = (E_Object3*)fEls->Head;
		dMinAng = 35;
		if (pE->iNoRemesh > 0)
			dMinAng = 15;
		else if (pE->iNoRemesh > 1)
			bExit = TRUE;
		pE->iNoRemesh++;
		vC = pE->Get_Centroid();
		vB = vC;
		vN = pE->Get_Normal();
		dC = pE->GetCharSize();
		dC *= 0.5;
		dC = dC + dG * (dTgt - dC);

		vN *= dC;
		vC += vN;  //Or Ideal Node Position
		
		// get other candate nodes from boundary with a certain distance from ideal position
		// in order of distance.
	    //GetCandiates(fNodes, vC, 2*dC, pCandidateNodes);
		//GetCandiateFaces(pE,fEls, vC, 2.0*dC, pCandidateFaces);
		GetCandiates(fEls, vC,1.5*dC, pCandidateFaces);
		pFrontNodes->Clear();
		//Build list of possible face nodes that may create a TET
		for (i = 0; i < pCandidateFaces->iNo; i++)
		{
			E_Object3* pEl2;
			pEl2 = (E_Object3*) pCandidateFaces->Objs[i];
			if (pEl2 != NULL)
			{
				pFrontNodes->AddEx(pEl2->pVertex[0]);
				pFrontNodes->AddEx(pEl2->pVertex[1]);
				pFrontNodes->AddEx(pEl2->pVertex[2]);
			}
		}
		pCandidateNodes->Clear();
		GetCandiatesNode(pE, pFrontNodes, vC, 1.0*dC, pCandidateNodes);
		GetAdjFaces(pCandidateFaces, pE, pAdjFaces, &dAdjAng, pAdjEl);
		if (pAdjFaces->iNo > 0)	  //070122 SEEMS TO WORK BETTER WITH OUT THIS
		{
			if (dAdjAng < 45)
			{
				nNodeTry = GetOtherNode(pAdjEl, pE);
				CreateTET(eTET, pE, nNodeTry);
				bV = IsValidTET2(pCandidateFaces, pCandidateNodes, eTET, dC, pE);
				pIntFace = DoesTETPenetrateBoundary(pCandidateFaces, eTET, pE);
				if ((pIntFace == NULL) && (bV))
				{
					nNode = nNodeTry;
					bIsTet = TRUE;
				}
			}
		}

		if (!bIsTet)
		{
			dMaxAng = 0;
			for (itry = 0; itry < pCandidateNodes->iNo; itry++)
			{
			    vT = pCandidateNodes->Objs[itry]->Get_Centroid();
				nNodeTry = (Node*)pCandidateNodes->Objs[itry];
				CreateTET(eTET, pE, nNodeTry);
				double dH = eTET->GetTETHeight(vB);
				double aaaa = MinInternalAngTET(eTET);
				double dss = eTET->GetCharSize();
				if ((aaaa > dMaxAng) && (aaaa > dMinAng))
				{
					bV = IsValidTET2(pCandidateFaces, pCandidateNodes, eTET, dC, pE);
					pIntFace = DoesTETPenetrateBoundary(pCandidateFaces, eTET, pE);
					if ((pIntFace == NULL) && (bV))
					{
						nNode = nNodeTry;
						dMaxAng = aaaa;
						bIsTet = TRUE;
					}
				}
			}
		}
		//NO EASY NEARBY NODE SO LETS CREATE A NEW ONE
		if (!bIsTet)
		{
			//outtext1("Failed to find existing node creating new one"); 
			nNode = pCurrentMesh->AddNode(vC, pCurrentMesh->iNodeLab, 0, 0, 50, 0, 0);
			pCurrentMesh->iNodeLab++;
			//Dsp_Add(nNode);
		}
		CreateTET(eTET, pE, nNode);
		bV = IsValidTET2(pCandidateFaces, pCandidateNodes, eTET, dC, pE);
		pIntFace = DoesTETPenetrateBoundary(pCandidateFaces, eTET, pE);
		if ((pIntFace == NULL) && (bV))
		{
			fNodes->Add(nNode);
			bIsTet = TRUE;
		}
		if ((!bIsTet) && (pIntFace != NULL))  //STILL NO TET AND BOUNDARY PENETRATION
		{
			int jc;
			E_Object3* pIntFaceTmp;
			for (jc = 0; jc < 3; jc++)
			{
				if (!pE->NodeInEl(pIntFace->pVertex[jc]))
				{
					CreateTET(eTET, pE, pIntFace->pVertex[jc]);
					bV = IsValidTET2(pCandidateFaces, pCandidateNodes, eTET, dC, pE);
					pIntFaceTmp = DoesTETPenetrateBoundary(pCandidateFaces, eTET, pE);
					if ((bV) && (pIntFaceTmp == NULL))
					{
						bIsTet = TRUE;
						break;
					}
				}
			}
		}
		//if still no TET lets try and delete the TET on the FACE.
		if ((!bIsTet) && (pIntFace != NULL))  //STILL NO TET AND BOUNDARY PENETRATION
		{
			E_Object34* pEDel = GetTETRelFace(pIntFace);
			if (pEDel != NULL)
			{
				sprintf_s(S1, "BOUNDARY VIOLATION DELETEING TET: %i CNT: %i", pEDel->iLabel, iTT);
				outtext1(S1);
				DeleteTET(fEls, fNodes, pCandidateFaces, pEDel);
				bReTry = TRUE;	   //Should be TRUE
				//bExit = TRUE;
			}
		}

		if (bIsTet)
		{
			CommitTET(fEls, pCandidateFaces, eTET);
			iNoElsGen++;
		}
		else if (bReTry)
		{
			bExit = FALSE;
		}
		else
		{
			  outtext1(S1);
			  outtext1("SWAPING");
			  //bExit=TRUE;
			  G_Object* pp = fEls->Head;
			  fEls->RemNoDelete(pp);
			  fEls->Add(pp);
			  ii++;
		}
		iTT++;
		if (fEls->Head == NULL)
			bExit = TRUE;
		if (iTT % 200 == 0)
		{
			InvalidateOGL();
			ReDraw();
		}
	} while ((iTT < 10000) && (bExit == FALSE)); //(fEls->iNo>0);

	InvalidateOGL();
	ReDraw();
	if (eTET != NULL)
		delete(eTET);
	sprintf_s(S1, "Number off Tet Elements Generated: %i", iNoElsGen);
	outtext1(S1);
	outtext1("** E N D   OF   T E T   G E N E R A T I O N **");


}


double DBase::GetTargetElSize(cLinkedList* fEls)
{
double drc=0;
E_Object3* pE;
G_Object* pNext;
pNext = fEls->Head;
while (pNext != NULL)
{
  pE=(E_Object3*) pNext;
  drc+=pE->GetCharSize();
  pNext = pNext->next;
}
drc=drc/fEls->iCnt;
return(drc);
}

E_Object34* DBase::GetTETRelFace(E_Object3* pF)
{
int i;

E_Object34* pRet=NULL;

for (i=0;i<pCurrentMesh->iElNo;i++)
{
   if ((pCurrentMesh->pElems[i]->NodeInEl(pF->pVertex[0])) &&
       (pCurrentMesh->pElems[i]->NodeInEl(pF->pVertex[1])) &&
       (pCurrentMesh->pElems[i]->NodeInEl(pF->pVertex[2])))
   {
      if (pCurrentMesh->pElems[i]->iType==111)
	  {
         pRet=(E_Object34*) pCurrentMesh->pElems[i];
         break;
	  }
   }

}
return (pRet);
}

E_Object3*  DBase::DoesTETPenetrateBoundary(ObjList* pCandidateFaces,E_Object34* pTET,E_Object3* notThisFace)
{
E_Object3* pIF;
int i;
E_Object3* pF;
pIF=NULL;
for (i=0;i<pCandidateFaces->iNo;i++)
{
   pF=(E_Object3*) pCandidateFaces->Objs[i];
   if (DoesTETPenetrateFace(pTET,pF,0.0)==TRUE)
   {
	  pIF=pF;
	  break;
   }
}
return (pIF);
}

// **********************************************************************
//CHECK INTERSECTION NOT NEAR BASE NODE
//vIntPt the calculated intersection point
//VFN1,VFN2,VFN3 the base node vertex locations
// **********************************************************************
BOOL DBase::IsBaseIntersect(C3dVector vIntPt, C3dVector vFN1, C3dVector vFN2, C3dVector vFN3, double dTol)
{
  BOOL brc = FALSE;
  vFN1 -= vIntPt;
  vFN2 -= vIntPt;
  vFN3 -= vIntPt;
  double d1;
  double d2;
  double d3;
  d1 = vFN1.Mag();
  d2 = vFN2.Mag();
  d3 = vFN3.Mag();
  if (vFN1.Mag() < dTol)
    brc = TRUE;
  else if (vFN2.Mag() < dTol)
    brc = TRUE;
  else if (vFN3.Mag() < dTol)
    brc = TRUE;
  
  return (brc);
}




// **********************************************************************
//TET PENTRATION TEST 
//Check all faces of tet with all faces in pCandidateFaces
// **********************************************************************
BOOL DBase::DoesTETPenetrateFace(E_Object34* pTET,E_Object3* pFace,double dTol)
{
BOOL bI=FALSE; 
BOOL brc = FALSE;
C3dVector p0;
C3dVector p1;
C3dVector vInt;
C3dVector vFN1;
C3dVector vFN2;
C3dVector vFN3;
C3dVector vFN4;
E_Object3* pTFace=new E_Object3();
double dS;  //Parametric ordinates of intersection a seg with triange
double dT;  //Parametric ordinates of intersection a seg with triange
if ((pTET->pVertex[3] == pFace->pVertex[0]) ||
    (pTET->pVertex[3] == pFace->pVertex[1]) ||
    (pTET->pVertex[3] == pFace->pVertex[2]))
{
  brc = FALSE;
}
else
{
  //BOOL DBase::LineIntTRI(C3dVector p0,C3dVector p1,E_Object3* pFace, C3dVector& vRes,double& dS,double& dT)
  //
  // Need to check all interections are not with elements connected to base
  // Try if the intersection is near a base node ignore

  //
  //Extra check added check base face centroid to node 3 for intersection with test face
  pTFace->pVertex[0] = pTET->pVertex[0];
  pTFace->pVertex[1] = pTET->pVertex[1];
  pTFace->pVertex[2] = pTET->pVertex[2];
  vFN1 = pTET->pVertex[0]->Get_Centroid();
  vFN2 = pTET->pVertex[1]->Get_Centroid();
  vFN3 = pTET->pVertex[2]->Get_Centroid();

  C3dVector vBaseCent = pTFace->Get_Centroid();
  p0 = vBaseCent;
  p1 = pTET->pVertex[3]->Get_Centroid();
  brc = LineIntTRI(p0, p1, pFace, vInt, dS, dT, dTol);
  if ((brc) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3,0.0001)))
  {
  //pPt=AddPt(vInt, 111);
  brc = TRUE;
  goto Fail;
  }
  // All edges of tet to face
  //First edge 0-3
  p0 = pTET->pVertex[0]->Get_Centroid();
  p1 = pTET->pVertex[3]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  //Second edge 1-3
  p0 = pTET->pVertex[1]->Get_Centroid();
  p1 = pTET->pVertex[3]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  //First edge 2-3
  p0 = pTET->pVertex[2]->Get_Centroid();
  p1 = pTET->pVertex[3]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  // all edges of face with TET faces (not base face)
  // First face of TET
  pTFace->pVertex[0] = pTET->pVertex[0];
  pTFace->pVertex[1] = pTET->pVertex[1];
  pTFace->pVertex[2] = pTET->pVertex[3];

  p0 = pFace->pVertex[0]->Get_Centroid();
  p1 = pFace->pVertex[1]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);

  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  p0 = pFace->pVertex[1]->Get_Centroid();
  p1 = pFace->pVertex[2]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  p0 = pFace->pVertex[2]->Get_Centroid();
  p1 = pFace->pVertex[0]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  //Second face of TET
  pTFace->pVertex[0] = pTET->pVertex[1];
  pTFace->pVertex[1] = pTET->pVertex[2];
  pTFace->pVertex[2] = pTET->pVertex[3];

  p0 = pFace->pVertex[0]->Get_Centroid();
  p1 = pFace->pVertex[1]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);

  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  p0 = pFace->pVertex[1]->Get_Centroid();
  p1 = pFace->pVertex[2]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  p0 = pFace->pVertex[2]->Get_Centroid();
  p1 = pFace->pVertex[0]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  // Third face of TET
  pTFace->pVertex[0] = pTET->pVertex[2];
  pTFace->pVertex[1] = pTET->pVertex[0];
  pTFace->pVertex[2] = pTET->pVertex[3];

  p0 = pFace->pVertex[0]->Get_Centroid();
  p1 = pFace->pVertex[1]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);

  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  p0 = pFace->pVertex[1]->Get_Centroid();
  p1 = pFace->pVertex[2]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
  p0 = pFace->pVertex[2]->Get_Centroid();
  p1 = pFace->pVertex[0]->Get_Centroid();
  bI = LineIntTRI(p0, p1, pTFace, vInt, dS, dT, dTol);
  if ((bI) && (!IsBaseIntersect(vInt, vFN1, vFN2, vFN3, 0.0001)))
  {
    //pPt=AddPt(vInt, 111);
    brc = TRUE;
    goto Fail;
  }
}
Fail:
if (pTFace!=NULL)
  delete (pTFace);

return (brc);
}

//p0 start of line seg, p1 end of line seg
//pFace the face defining plane to intersect
//vRes intersetion point

int DBase::LineIntPlane(C3dVector p0,C3dVector p1,E_Object3* pFace, C3dVector& vRes,double& dR)
{
int iRC=-1;
C3dVector vN;   //Face nornal
C3dVector v0;   //Face Origin
C3dVector vT;
vN=pFace->Get_Normal();
v0=pFace->Get_Centroid();
double db;
double dt;
double dpp;

vT=v0-p0;
dt=vN.Dot(vT);
vT=p1-p0;
db=vN.Dot(vT);
if ((db>-0.00000001) && (db<0.00000001)) // line // with plane
{
  iRC=-1;
}
else
{

  dpp=dt/db;
  dR=dpp;
  // a ray (considering direction) intersects only if dpp>0 ret 0
  // a seg intersects if dpp 0<=dpp<=1                      ret 1
  if (dpp>=0)
  {
    vRes.x=p0.x+dpp*vT.x;
    vRes.y=p0.y+dpp*vT.y;
    vRes.z=p0.z+dpp*vT.z;
    iRC=0;
  }
  if ((dpp>0) && (dpp<1.0))	  //was dpp<1.1
  {
    iRC=1;
  }
  
}
return (iRC);
}

//*****************************************************************************
//p0 start of line seg, p1 end of line seg
//pFace the face defining plane to intersect
//vRes intersetion point
// DOES A LINE SEG / RAY INETERSECT A TRAINGLE IF SO WHERE
//*****************************************************************************
BOOL DBase::LineIntTRI(C3dVector p0,C3dVector p1,E_Object3* pFace, C3dVector& vRes,double& dS,double& dT,double dTol)
{
int iRC=0;
BOOL brc=FALSE;
C3dVector PI;
C3dVector V0;
C3dVector V1;
C3dVector V2;
C3dVector W;
C3dVector U;
C3dVector V;
double dd;
double tp;
double t;
double s;
double dR;
iRC=LineIntPlane(p0,p1,pFace,PI,dR);
vRes=PI;
// if iRC==-1 then there is no intersection we are fininshed.
if (iRC==1)   //else is the point pI in the triangle?
{
  V0=pFace->pVertex[0]->Get_Centroid();
  V1=pFace->pVertex[1]->Get_Centroid();
  V2=pFace->pVertex[2]->Get_Centroid();
  W=PI-V0;
  U=V1-V0;
  V=V2-V0;
  tp=U.Dot(V);
  
  dd=(tp*tp)-(U.Dot(U)*V.Dot(V)); //common denominator
  s= U.Dot(V)*W.Dot(V) - V.Dot(V)*W.Dot(U);
  t= U.Dot(V)*W.Dot(U) - U.Dot(U)*W.Dot(V);
  s/=dd;
  t/=dd;
  brc=TRUE;
  if ((s<=dTol) || (s>=1-dTol))
  {brc=FALSE;}
  if ((t<=dTol) || ((s+t)>=1-dTol))
  {brc=FALSE;}
  dS=s;
  dT=t;
  
}

return (brc);
}

//Assumes 2d
//check to see if point is in triangle
double DBase::sign(C3dVector p1, C3dVector p2, C3dVector p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}


BOOL DBase::PointIn2dTriangle(C3dVector vt1,C3dVector vt2,C3dVector vt3,C3dVector vPt)
{
    BOOL b1, b2, b3;

    b1 = sign(vPt, vt1, vt2) < 0.0;
    b2 = sign(vPt, vt2, vt3) < 0.0;
    b3 = sign(vPt, vt3, vt1) < 0.0;

    return ((b1 == b2) && (b2 == b3));
}

E_Object3* DBase::DoesFaceOverLap(E_Object3* pF1, ObjList* pCandidateFaces, double dTol)
{

#ifdef _DEBUG
	CMemoryState oldMemState, newMemState, diffMemState;
	oldMemState.Checkpoint();
#endif 
	double dTD = 10;
	double dAng;
	C3dVector vBll;
	C3dVector vBur;
	C3dVector vTll;
	C3dVector vTur;
	C3dMatrix mTram;
	C3dVector vTran;
	C3dVector I0;
	C3dVector I1;
	C3dVector vN1;
	C3dVector vN2;
	E_Object3* pRet = NULL;
	E_Object3* pF2 = NULL;
	int i;
	E_Object3* pFB = new E_Object3();   //Base face
	E_Object3* pFT = new E_Object3();   //test face
	pFB->pParent = NULL;
	pFB->pVertex[0] = (Node *)pF1->pVertex[0]->Copy(NULL);
	pFB->pVertex[1] = (Node *)pF1->pVertex[1]->Copy(NULL);
	pFB->pVertex[2] = (Node *)pF1->pVertex[2]->Copy(NULL);
	pFT->pParent = NULL;
	pFT->pVertex[0] = (Node *)pF1->pVertex[0]->Copy(NULL);
	pFT->pVertex[1] = (Node *)pF1->pVertex[1]->Copy(NULL);
	pFT->pVertex[2] = (Node *)pF1->pVertex[2]->Copy(NULL);
	mTram = pFB->GetElSys();
	pFB->TransformAVF(mTram);
	vTran = pFB->pVertex[0]->Get_Centroid();
	vTran *= -1;
	pFB->TranslateAVF(vTran);
	pFB->GetBoundingBox(vBll, vBur);
	for (i = 0; i < pCandidateFaces->iNo; i++)
	{
		pF2 = (E_Object3*)pCandidateFaces->Objs[i];
		if (pF2 != pF1)
		{
			vN1 = pF1->Get_Normal();
			vN2 = pF2->Get_Normal();
			dAng = vN1.Dot(vN2);
			//dAng=AngleBetweenFaces(pF1,pF2);
			if (abs(dAng) > 0.985)  //if no significant ahgle between faces
			{
				pFT->pVertex[0]->Pt_Point->x = pF2->pVertex[0]->Pt_Point->x;
				pFT->pVertex[0]->Pt_Point->y = pF2->pVertex[0]->Pt_Point->y;
				pFT->pVertex[0]->Pt_Point->z = pF2->pVertex[0]->Pt_Point->z;

				pFT->pVertex[1]->Pt_Point->x = pF2->pVertex[1]->Pt_Point->x;
				pFT->pVertex[1]->Pt_Point->y = pF2->pVertex[1]->Pt_Point->y;
				pFT->pVertex[1]->Pt_Point->z = pF2->pVertex[1]->Pt_Point->z;

				pFT->pVertex[2]->Pt_Point->x = pF2->pVertex[2]->Pt_Point->x;
				pFT->pVertex[2]->Pt_Point->y = pF2->pVertex[2]->Pt_Point->y;
				pFT->pVertex[2]->Pt_Point->z = pF2->pVertex[2]->Pt_Point->z;

				pFT->TransformAVF(mTram);
				pFT->TranslateAVF(vTran);
				//**********************************************************************************
				if ((abs(pFT->pVertex[0]->Pt_Point->z) < dTol) ||
					(abs(pFT->pVertex[1]->Pt_Point->z) < dTol) ||
					(abs(pFT->pVertex[2]->Pt_Point->z) < dTol))
				{

					pFT->GetBoundingBox(vTll, vTur);
					if ((vTur.x > vBll.x) &&
						(vTur.y > vBll.y) &&
						(vTll.x < vBur.x) &&
						(vTll.y < vBur.y))
					{
						//pRet=pF2;
						//Chech none of the nodes lie entirly in face
			  //          if (PointIn2dTriangle(*pFT->pVertex[0]->Pt_Point, *pFT->pVertex[1]->Pt_Point,
			  //			                    *pFT->pVertex[2]->Pt_Point, *pFB->pVertex[0]->Pt_Point))
			  //		    {pRet=pF2; break;}
			  //		  if (PointIn2dTriangle(*pFT->pVertex[0]->Pt_Point, *pFT->pVertex[1]->Pt_Point,
			  //			                    *pFT->pVertex[2]->Pt_Point, *pFB->pVertex[1]->Pt_Point))
			  //		    {pRet=pF2; break;}
			  //	 	  if (PointIn2dTriangle(*pFT->pVertex[0]->Pt_Point, *pFT->pVertex[1]->Pt_Point,
			  //			                    *pFT->pVertex[2]->Pt_Point, *pFB->pVertex[2]->Pt_Point))
			  //		    {pRet=pF2; break;}
			  ////
			  //		  if (PointIn2dTriangle(*pFB->pVertex[0]->Pt_Point, *pFB->pVertex[1]->Pt_Point,
			  //			                    *pFB->pVertex[2]->Pt_Point, *pFT->pVertex[0]->Pt_Point))
			  //		    {pRet=pF2; break;}
			  //		  if (PointIn2dTriangle(*pFB->pVertex[0]->Pt_Point, *pFB->pVertex[1]->Pt_Point,
			  //			                    *pFB->pVertex[2]->Pt_Point, *pFT->pVertex[1]->Pt_Point))
			  //		    {pRet=pF2; break;}
			  //	 	  if (PointIn2dTriangle(*pFB->pVertex[0]->Pt_Point, *pFB->pVertex[1]->Pt_Point,
			  //			                    *pFB->pVertex[2]->Pt_Point, *pFT->pVertex[2]->Pt_Point))
			  //		    {pRet=pF2; break;}
			  //  		  //*************************EDGE 1 INTERSECTIONS*************************
						if (intersect2D_2Segments(*pFB->pVertex[0]->Pt_Point, *pFB->pVertex[1]->Pt_Point,
							*pFT->pVertex[0]->Pt_Point, *pFT->pVertex[1]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						if (intersect2D_2Segments(*pFB->pVertex[0]->Pt_Point, *pFB->pVertex[1]->Pt_Point,
							*pFT->pVertex[1]->Pt_Point, *pFT->pVertex[2]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						if (intersect2D_2Segments(*pFB->pVertex[0]->Pt_Point, *pFB->pVertex[1]->Pt_Point,
							*pFT->pVertex[2]->Pt_Point, *pFT->pVertex[0]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						//*************************EDGE 2 INTERSECTIONS*************************
						if (intersect2D_2Segments(*pFB->pVertex[1]->Pt_Point, *pFB->pVertex[2]->Pt_Point,
							*pFT->pVertex[0]->Pt_Point, *pFT->pVertex[1]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						if (intersect2D_2Segments(*pFB->pVertex[1]->Pt_Point, *pFB->pVertex[2]->Pt_Point,
							*pFT->pVertex[1]->Pt_Point, *pFT->pVertex[2]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						if (intersect2D_2Segments(*pFB->pVertex[1]->Pt_Point, *pFB->pVertex[2]->Pt_Point,
							*pFT->pVertex[2]->Pt_Point, *pFT->pVertex[0]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						//*************************EDGE 3 INTERSECTIONS*************************
						if (intersect2D_2Segments(*pFB->pVertex[2]->Pt_Point, *pFB->pVertex[0]->Pt_Point,
							*pFT->pVertex[0]->Pt_Point, *pFT->pVertex[1]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						if (intersect2D_2Segments(*pFB->pVertex[2]->Pt_Point, *pFB->pVertex[0]->Pt_Point,
							*pFT->pVertex[1]->Pt_Point, *pFT->pVertex[2]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}
						if (intersect2D_2Segments(*pFB->pVertex[2]->Pt_Point, *pFB->pVertex[0]->Pt_Point,
							*pFT->pVertex[2]->Pt_Point, *pFT->pVertex[0]->Pt_Point,
							&I0, &I1) == 1)
						{
							pRet = pF2; break;
						}



					}
				}
			}
		}
	}
	//**********************************************************************************
	//Delete the test elements
	delete(pFB->pVertex[0]);
	delete(pFB->pVertex[1]);
	delete(pFB->pVertex[2]);
	delete(pFB);
	delete(pFT->pVertex[0]);
	delete(pFT->pVertex[1]);
	delete(pFT->pVertex[2]);
	delete(pFT);



#ifdef _DEBUG
	newMemState.Checkpoint();


	if (diffMemState.Difference(oldMemState, newMemState))
	{
		TRACE("Memory leaked in Face Over Check!\n");
		diffMemState.DumpStatistics();
	}
#endif

	return (pRet);
}

#define SMALL_NUM   0.0000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
double DBase::dot2D(C3dVector u,C3dVector v)   
{
return (u.x * v.x + u.y * v.y + u.z * v.z);
}

// perp product  (2D)
double DBase::perp2D(C3dVector u,C3dVector v)  
{
return (u.x * v.y - u.y * v.x);  
}

// http://geomalgorithms.com/a05-_intersect-1.html
//USED FOR "D PARAMETRIC SURFACE MESHING
int DBase::intersect2DUV_2Segments(C2dVector S1a, C2dVector S1b,
	                               C2dVector S2a, C2dVector S2b,
	                               C2dVector* I0, C2dVector* I1)
{

	C2dVector u; u = S1b; u -= S1a;
	C2dVector v; v = S2b; v -= S2a;
	C2dVector w; w = S1a; w -= S2a;
	double D = u.Cross(v);

	// test if  they are parallel (includes either being a point)
	if (fabs(D) < SMALL_NUM)
	{
		return (0); //S1 and S2 are parallel ignore for now
	}

	// the segments are skew and may intersect in a point
	// get the intersect parameter for S1
	double sI = v.Cross(w) / D;
	if (sI < 0 - SMALL_NUM || sI > 1 + SMALL_NUM)                // no intersect with S1
		return 0;
	// get the intersect parameter for S2
	double tI = u.Cross(w) / D;
	if (tI < 0 - SMALL_NUM || tI > 1 + SMALL_NUM)                // no intersect with S2
		return 0;
	// compute S1 intersect point         
	I0->x = S1a.x + sI * u.x;
	I0->y = S1a.y + sI * u.y;
	return 1;

}

// intersect2D_2Segments(): find the 2D intersection of 2 finite segments
//    Input:  two finite segments S1 and S2
//    Output: *I0 = intersect point (when it exists)
//            *I1 =  endpoint of intersect segment [I0,I1] (when it exists)
//    Return: 0=disjoint (no intersect)
//            1=intersect  in unique point I0
//            2=overlap  in segment from I0 to I1
// http://geomalgorithms.com/a05-_intersect-1.html
int DBase::intersect2D_2Segments(C3dVector S1a, C3dVector S1b,
								 C3dVector S2a, C3dVector S2b,
								 C3dVector* I0, C3dVector* I1)
{

    C3dVector u; u=S1b; u-=S1a;
    C3dVector v; v=S2b; v-=S2a;
    C3dVector w; w=S1a; w-=S2a;
    double D = perp2D(u,v);

    // test if  they are parallel (includes either being a point)
if (fabs(D) < SMALL_NUM)
{
  return (0); //S1 and S2 are parallel ignore for now
}

// the segments are skew and may intersect in a point
// get the intersect parameter for S1
double sI = perp2D(v,w) / D;
if (sI < 0+SMALL_NUM || sI > 1-SMALL_NUM)                // no intersect with S1
   return 0;
// get the intersect parameter for S2
double tI = perp2D(u,w) / D;
if (tI < 0+SMALL_NUM || tI > 1-SMALL_NUM)                // no intersect with S2
   return 0;
// compute S1 intersect point         
I0->x=S1a.x+sI*u.x;
I0->y=S1a.y+sI*u.y;
I0->z=S1a.z+sI*u.z;
return 1;

    //if (fabs(D) < SMALL_NUM) {           // S1 and S2 are parallel
    //    if (perp(u,w) != 0 || perp(v,w) != 0)  {
    //        return 0;                    // they are NOT collinear
    //    }
    //    // they are collinear or degenerate
    //    // check if they are degenerate  points
    //    float du = dot(u,u);
    //    float dv = dot(v,v);
    //    if (du==0 && dv==0) {            // both segments are points
    //        if (S1.P0 !=  S2.P0)         // they are distinct  points
    //             return 0;
    //        *I0 = S1.P0;                 // they are the same point
    //        return 1;
    //    }
    //    if (du==0) {                     // S1 is a single point
    //        if  (inSegment(S1.P0, S2) == 0)  // but is not in S2
    //             return 0;
    //        *I0 = S1.P0;
    //        return 1;
    //    }
    //    if (dv==0) {                     // S2 a single point
    //        if  (inSegment(S2.P0, S1) == 0)  // but is not in S1
    //             return 0;
    //        *I0 = S2.P0;
    //        return 1;
    //    }
    //    // they are collinear segments - get  overlap (or not)
    //    float t0, t1;                    // endpoints of S1 in eqn for S2
    //    Vector w2 = S1.P1 - S2.P0;
    //    if (v.x != 0) {
    //             t0 = w.x / v.x;
    //             t1 = w2.x / v.x;
    //    }
    //    else {
    //             t0 = w.y / v.y;
    //             t1 = w2.y / v.y;
    //    }
    //    if (t0 > t1) {                   // must have t0 smaller than t1
    //             float t=t0; t0=t1; t1=t;    // swap if not
    //    }
    //    if (t0 > 1 || t1 < 0) {
    //        return 0;      // NO overlap
    //    }
    //    t0 = t0<0? 0 : t0;               // clip to min 0
    //    t1 = t1>1? 1 : t1;               // clip to max 1
    //    if (t0 == t1) {                  // intersect is a point
    //        *I0 = S2.P0 +  t0 * v;
    //        return 1;
    //    }

    //    // they overlap in a valid subsegment
    //    *I0 = S2.P0 + t0 * v;
    //    *I1 = S2.P0 + t1 * v;
    //    return 2;
    //}

    //// the segments are skew and may intersect in a point
    //// get the intersect parameter for S1
    //float     sI = perp(v,w) / D;
    //if (sI < 0 || sI > 1)                // no intersect with S1
    //    return 0;

    //// get the intersect parameter for S2
    //float     tI = perp(u,w) / D;
    //if (tI < 0 || tI > 1)                // no intersect with S2
    //    return 0;

    //*I0 = S1.P0 + sI * u;                // compute S1 intersect point
}


BOOL DBase::IsValidTET(ObjList* pCandidateFaces,E_Object34* eTET, double dCD,E_Object3* pBaseF)
{
  BOOL bV=TRUE;    //Its good until we prove not
  if (eTET==NULL)
  {
    return(FALSE);
  }
  E_Object3* pCF = new E_Object3();
  E_Object3* pAF;
  C3dVector vFN;   //Test face normal vector
  C3dVector vFC;   //Test face centroid
  C3dVector vCC;   //Candidate face centroid
  double dDot;
  double dAng;
  double dTD;
  //dTD=-1*dCD/10;   //test distance for distinctness
  dTD=10;  //10 degree angle beteen faces min
  //First Tet Face to Check
  //pTEST=DoesFaceOverLap((E_Object3*) fEls->Objs[0],fEls,0.1);
  pCF->pVertex[0]=eTET->pVertex[0];
  pCF->pVertex[1]=eTET->pVertex[1];
  pCF->pVertex[2]=eTET->pVertex[3];
  //Get any adjacent faces if NULL then no further check
  pAF=GetAdjFace(pCandidateFaces,pCF->pVertex[0],pCF->pVertex[1],pCF->pVertex[2],pBaseF);
  if ((pAF!=NULL) && (bV==TRUE))// need to check face is distinct and non intersecting
  {
    dAng=AngleBetweenFaces(pCF,pAF);
	if ((dAng<dTD) || (dAng>360-dTD))
	{
	  bV=FALSE;
	}
	//dAng=AngleBetweenFaces(pCF,pAF);
  }
 
  //Second Tet Face to Check
  pCF->pVertex[0]=eTET->pVertex[1];
  pCF->pVertex[1]=eTET->pVertex[2];
  pCF->pVertex[2]=eTET->pVertex[3];
  //Get any adjacent faces if NULL then no further check
  pAF=GetAdjFace(pCandidateFaces,eTET->pVertex[1],eTET->pVertex[2],eTET->pVertex[3],pBaseF);
  if ((pAF!=NULL) && (bV==TRUE))// need to check face is distinct and non intersecting
  {
	dAng=AngleBetweenFaces(pCF,pAF);
	if ((dAng<dTD) || (dAng>360-dTD))
	{
	  bV=FALSE;
	}
  }

  //Third Tet Face to Check
  pCF->pVertex[0]=eTET->pVertex[2];
  pCF->pVertex[1]=eTET->pVertex[0];
  pCF->pVertex[2]=eTET->pVertex[3];
  //Get any adjacent faces if NULL then no further check
  pAF=GetAdjFace(pCandidateFaces,pCF->pVertex[0],pCF->pVertex[1],pCF->pVertex[2],pBaseF);
  if ((pAF!=NULL) && (bV==TRUE))// need to check face is distinct and non intersecting
  {
	dAng=AngleBetweenFaces(pCF,pAF);
    dDot=vFN.Dot(vCC); //dDot must be negative to be distinct and by a certain distance
	if ((dAng<dTD) || (dAng>360-dTD)) 
	{
	  bV=FALSE;
	}
  }
 
  delete (pCF);
  return(bV);
}

BOOL DBase::isNodeInTET(ObjList* pChkNodes,E_Object34* eTET)
{
int i;
BOOL brc=TRUE;
if (pChkNodes->iNo==0)
  brc=FALSE;
E_Object3* pCF = new E_Object3();
C3dVector vFN;
C3dVector vFC;
C3dVector vNC;
C3dVector vNN;
for (i=0;i<pChkNodes->iNo;i++)
{
  vNC=pChkNodes->Objs[i]->Get_Centroid();

  //FACE 1
  pCF->pVertex[0]=eTET->pVertex[0];
  pCF->pVertex[1]=eTET->pVertex[2];
  pCF->pVertex[2]=eTET->pVertex[1];
  vFC=pCF->Get_Centroid();
  vFN=pCF->Get_Normal();
  vNN=vNC;vNN-=vFC;vNN.Normalize();
  if (vNN.Dot(vFN)<0)
    return(FALSE);
  //FACE 2
  pCF->pVertex[0]=eTET->pVertex[0];
  pCF->pVertex[1]=eTET->pVertex[1];
  pCF->pVertex[2]=eTET->pVertex[3];
  vFC=pCF->Get_Centroid();
  vFN=pCF->Get_Normal();
  vNN=vNC;vNN-=vFC;vNN.Normalize();
  if (vNN.Dot(vFN)<0)
    return(FALSE);
  //FACE 3
  pCF->pVertex[0]=eTET->pVertex[1];
  pCF->pVertex[1]=eTET->pVertex[2];
  pCF->pVertex[2]=eTET->pVertex[3];
  vFC=pCF->Get_Centroid();
  vFN=pCF->Get_Normal();
  vNN=vNC;vNN-=vFC;vNN.Normalize();
  if (vNN.Dot(vFN)<0)
    return(FALSE);
 //FACE 4
  pCF->pVertex[0]=eTET->pVertex[2];
  pCF->pVertex[1]=eTET->pVertex[0];
  pCF->pVertex[2]=eTET->pVertex[3];
  vFC=pCF->Get_Centroid();
  vFN=pCF->Get_Normal();
  vNN=vNC;vNN-=vFC;vNN.Normalize();
  if (vNN.Dot(vFN)<0)
    return(FALSE);
}
delete(pCF);
return (brc);
}


BOOL DBase::IsValidTET2(ObjList* pCandidateFaces,ObjList* pChkNodes,E_Object34* eTET, double dCD,E_Object3* pBaseF)
{
  BOOL bV=TRUE;    //Its good until we prove not
  if (eTET==NULL)
    return(FALSE);
  if (isNodeInTET(pChkNodes,eTET))
    return(FALSE);
  E_Object3* pCF = new E_Object3();
  E_Object3* pTEST;
  E_Object3* pAF;

  //Check Node is forward of base
  C3dVector vN;
  C3dVector vA;
  C3dVector vB;
  C3dVector vC;
vA=eTET->pVertex[0]->Get_Centroid();
vB=eTET->pVertex[1]->Get_Centroid();
vC=eTET->pVertex[2]->Get_Centroid();
vB-=vA;vB.Normalize();
vC-=vA;;vC.Normalize();
vN=vB.Cross(vC);vN.Normalize();
vA-=eTET->pVertex[3]->Get_Centroid();
vA.Normalize();
if (vA.Dot(vN)>0.1)
  return(FALSE);


  pCF->pVertex[0]=eTET->pVertex[0];
  pCF->pVertex[1]=eTET->pVertex[1];
  pCF->pVertex[2]=eTET->pVertex[3];
  pAF=GetFace(pCandidateFaces,pCF->pVertex[0],pCF->pVertex[1],pCF->pVertex[2]);
  if ((pAF==NULL) && (bV==TRUE))// need to check face is distinct and non intersecting
  {
    pTEST=DoesFaceOverLap(pCF,pCandidateFaces,dCD/10.0);
	if (pTEST!=NULL) 
	{
	  bV=FALSE;
	}
  }
 
  //Second Tet Face to Check
  pCF->pVertex[0]=eTET->pVertex[1];
  pCF->pVertex[1]=eTET->pVertex[2];
  pCF->pVertex[2]=eTET->pVertex[3];
  pAF=GetFace(pCandidateFaces,pCF->pVertex[0],pCF->pVertex[1],pCF->pVertex[2]);
  if ((pAF==NULL) && (bV==TRUE))// need to check face is distinct and non intersecting
  {
    pTEST=DoesFaceOverLap(pCF,pCandidateFaces,dCD/10.0);
	if (pTEST!=NULL) 
	{
	  bV=FALSE;
	}
  }

  //Third Tet Face to Check
  pCF->pVertex[0]=eTET->pVertex[2];
  pCF->pVertex[1]=eTET->pVertex[0];
  pCF->pVertex[2]=eTET->pVertex[3];
  pAF=GetFace(pCandidateFaces,pCF->pVertex[0],pCF->pVertex[1],pCF->pVertex[2]);
  if ((pAF==NULL) && (bV==TRUE))// need to check face is distinct and non intersecting
  {
    pTEST=DoesFaceOverLap(pCF,pCandidateFaces,dCD/10.0);
	if (pTEST!=NULL) 
	{
	  bV=FALSE;
	}
  }
 
  delete (pCF);
  return(bV);
}



void DBase::DeleteTET(cLinkedList* fEls, cLinkedList* fNodes,ObjList* pCandidateFaces,E_Object34* eTET)
{
E_Object3* pFF;
//Removes faces of tet that exist in front and add those that don't


    pFF=GetFace(pCandidateFaces,eTET->pVertex[0],eTET->pVertex[1],eTET->pVertex[2]);
	if (pFF!=NULL)
		RemoveFace(fEls,pCandidateFaces,pFF);
	else
	  fEls->Add(CreateFace(eTET->pVertex[0],eTET->pVertex[1],eTET->pVertex[2]));
	pFF=GetFace(pCandidateFaces,eTET->pVertex[0],eTET->pVertex[1],eTET->pVertex[3]);
	if (pFF!=NULL)
       RemoveFace(fEls,pCandidateFaces,pFF);
	else
		fEls->Add(CreateFace(eTET->pVertex[0],eTET->pVertex[3],eTET->pVertex[1]));
	pFF=GetFace(pCandidateFaces,eTET->pVertex[1],eTET->pVertex[2],eTET->pVertex[3]);
	if (pFF!=NULL)
       RemoveFace(fEls,pCandidateFaces,pFF);
	else
	   fEls->Add(CreateFace(eTET->pVertex[1],eTET->pVertex[3],eTET->pVertex[2]));
	pFF=GetFace(pCandidateFaces,eTET->pVertex[2],eTET->pVertex[0],eTET->pVertex[3]);
	if (pFF!=NULL)
        RemoveFace(fEls,pCandidateFaces,pFF);
 	else
		fEls->Add(CreateFace(eTET->pVertex[2],eTET->pVertex[3],eTET->pVertex[0]));

//RemObj(eTET);
//Dsp_Rem(eTET);
//Dsp_RemGP(eTET);
// need to remove any free nodes left
int i;
E_Object3* pE;
BOOL bRem;
for (i=0;i<4;i++)
{
  bRem=TRUE;
  pE = (E_Object3*) fEls->Head;
  while (pE!=NULL)
  {
     if (pE->NodeInEl(eTET->pVertex[i]))
	 {
       bRem=FALSE;
	   break;
	 }
	 pE = (E_Object3*) pE->next;
  }
  if (bRem==TRUE)
  {
	//Dsp_Rem(eTET->pVertex[i]);
    fNodes->RemNoDelete(eTET->pVertex[i]);
  }
}
//InvalidateOGL();
pCurrentMesh->DeleteEl(eTET);
}



BOOL DBase::CommitTET(cLinkedList* fEls,ObjList* pCandidateFaces,E_Object34* eTET)
{
  BOOL bRet=FALSE;
  E_Object34* pRet;
  E_Object3* pFF;
  Node* pENodes[100];
  pENodes[0]=eTET->pVertex[0];
  pENodes[1]=eTET->pVertex[1];
  pENodes[2]=eTET->pVertex[2];
  pENodes[3]=eTET->pVertex[3];;
  //Properties and material need sorting out
  pRet = (E_Object34*) pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,50,111,-1,-1,4,1,1,1,FALSE,-1,0); 
  eTET->iLabel=pCurrentMesh->iElementLab;
  pCurrentMesh->iElementLab++;
  //this->Dsp_Add(pRet);
  //AddTempGraphics(pRet);
  //ReDraw();
  //pRet->SetToScr(&pModelMat,&pScrMat);
  if (pRet!=NULL)
    bRet=TRUE;
  if (bRet==TRUE)
  {
    pFF=GetFace(pCandidateFaces,eTET->pVertex[0],eTET->pVertex[1],eTET->pVertex[2]);
	if (pFF!=NULL)
		RemoveFace(fEls,pCandidateFaces,pFF);
	else
	  fEls->Add(CreateFace(eTET->pVertex[0],eTET->pVertex[1],eTET->pVertex[2]));
	pFF=GetFace(pCandidateFaces,eTET->pVertex[0],eTET->pVertex[1],eTET->pVertex[3]);
	if (pFF!=NULL)
       RemoveFace(fEls,pCandidateFaces,pFF);
	else
		fEls->Add(CreateFace(eTET->pVertex[0],eTET->pVertex[1],eTET->pVertex[3]));
	pFF=GetFace(pCandidateFaces,eTET->pVertex[1],eTET->pVertex[2],eTET->pVertex[3]);
	if (pFF!=NULL)
       RemoveFace(fEls,pCandidateFaces,pFF);
	else
	   fEls->Add(CreateFace(eTET->pVertex[1],eTET->pVertex[2],eTET->pVertex[3]));
	pFF=GetFace(pCandidateFaces,eTET->pVertex[2],eTET->pVertex[0],eTET->pVertex[3]);
	if (pFF!=NULL)
        RemoveFace(fEls,pCandidateFaces,pFF);
 	else
		fEls->Add(CreateFace(eTET->pVertex[2],eTET->pVertex[0],eTET->pVertex[3]));
  }
  return(bRet);
}

E_Object3* DBase::GetFace(ObjList* pAdjFaces,Node* N1,Node* N2,Node* N3)
{
int i;
E_Object3* pRet=NULL;
E_Object3* pE;
for (i=0;i<pAdjFaces->iNo;i++)
{   
  pE=(E_Object3*) pAdjFaces->Objs[i];
  if ((pE->NodeInEl(N1)) && (pE->NodeInEl(N2)) && (pE->NodeInEl(N3)))
  {
    pRet=pE;
	break;
  }
}
return (pRet);
}

void DBase::RemoveFaces(cLinkedList* fEls,ObjList* pAdjFaces,E_Object3* pE)
{
  int i;
  //these probably want deleting before nest advance
  fEls->Remove(pE);
  for (i=0;i<pAdjFaces->iNo;i++)
  {
    fEls->Remove(pAdjFaces->Objs[i]);
  }
}

void DBase::RemoveFace(cLinkedList* fEls,ObjList* pCandidateFaces,E_Object3* pFF)
{
fEls->RemNoDelete(pFF);
pCandidateFaces->Remove(pFF);
pCurrentMesh->DeleteEl(pFF);
}


E_Object3* DBase::CreateFace(Node* N1,Node* N2,Node* N3)
{

  E_Object3* pRet=NULL;
  Node* pENodes[100];
  pENodes[0]=N1;
  pENodes[1]=N2;
  pENodes[2]=N3;
  //Properties and material need sorting out
  pRet = (E_Object3*) pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,20,91,-1,-1,3,1,1,1,FALSE,-1,0); 
  pCurrentMesh->iElementLab++;
  //pRet->SetToScr(&pModelMat,&pScrMat);
  //this->Dsp_Add(pRet);
  return (pRet);
}

BOOL DBase::NodeNotInTET(E_Object34* eTET,ObjList* pCandidateNodes)
{
BOOL brc=TRUE;

C3dVector vN0;
C3dVector vN1;
C3dVector vN2;
C3dVector vN3;
C3dVector A;
C3dVector B;

vN0=eTET->pVertex[0]->Get_Centroid();
vN1=eTET->pVertex[1]->Get_Centroid();
vN2=eTET->pVertex[2]->Get_Centroid();
vN3=eTET->pVertex[3]->Get_Centroid();

A=vN3; A-=vN0; A.Normalize();
B=vN3; B-=vN1; B.Normalize();

return (brc);
}

double DBase::TETFaceInternalAng(C3dVector vN0,C3dVector vN1,C3dVector vN2,C3dVector vN3)
{
double dRet=0;
C3dVector A;
C3dVector B;
C3dVector C;
C3dVector vNrm1;
C3dVector vNrm2;
A=vN1; A-=vN0; A.Normalize();
B=vN2; B-=vN0; B.Normalize();
C=vN3; C-=vN0; C.Normalize();


vNrm1=A.Cross(B);
vNrm2=C.Cross(A);
vNrm1.Normalize();
vNrm2.Normalize();
dRet=vNrm1.Dot(vNrm2);
dRet=acos(dRet);
dRet*=57.29577951;
dRet=180.0-dRet;

return (dRet);
}

double DBase::MinInternalAngTET(E_Object34* eTET)
{
double drc=360;
double dAng;
C3dVector vN0;
C3dVector vN1;
C3dVector vN2;
C3dVector vN3;
C3dVector A;
C3dVector B;

vN0=eTET->pVertex[0]->Get_Centroid();
vN1=eTET->pVertex[1]->Get_Centroid();
vN2=eTET->pVertex[2]->Get_Centroid();
vN3=eTET->pVertex[3]->Get_Centroid();

A=vN3; A-=vN0; A.Normalize();
B=vN3; B-=vN1; B.Normalize();
dAng=A.Dot(B);
dAng=acos(dAng);
dAng*=57.29577951;
if (dAng<drc)
  drc=dAng;

A=vN3; A-=vN1; A.Normalize();
B=vN3; B-=vN2; B.Normalize();
dAng=A.Dot(B);
dAng=acos(dAng);
dAng*=57.29577951;
if (dAng<drc)
  drc=dAng;

A=vN3; A-=vN2; A.Normalize();
B=vN3; B-=vN0; B.Normalize();
dAng=A.Dot(B);
dAng=acos(dAng);
dAng*=57.29577951;
if (dAng<drc)
  drc=dAng;
//Angles betwen base faces - shared edge and two indepenedant nodes on each face
dAng=TETFaceInternalAng(vN0,vN1,vN2,vN3);
if (dAng<drc)
  drc=dAng;

dAng=TETFaceInternalAng(vN1,vN2,vN0,vN3);
if (dAng<drc)
  drc=dAng;

dAng=TETFaceInternalAng(vN2,vN0,vN3,vN1);
if (dAng<drc)
  drc=dAng;

dAng=TETFaceInternalAng(vN0,vN3,vN1,vN2);
if (dAng<drc)
  drc=dAng;

dAng=TETFaceInternalAng(vN1,vN3,vN0,vN2);
if (dAng<drc)
  drc=dAng;

dAng=TETFaceInternalAng(vN2,vN3,vN0,vN1);
if (dAng<drc)
  drc=dAng;

return (drc);
}




void DBase::CreateTET(E_Object34* eRet,E_Object3* pE,Node* nNode)
{


  eRet->pVertex[0]=pE->pVertex[0];
  eRet->pVertex[1]=pE->pVertex[1];
  eRet->pVertex[2]=pE->pVertex[2];
  eRet->pVertex[3]=nNode;
}

Node* DBase::GetBestNode(ObjList* pFrom, E_Object3* pFace)
{
ObjList* pCand = new ObjList();
Node* pN;
E_Object3* pF;

int i;
Node* pRet=NULL;
pCand->Clear();
if (pFace->iLabel==48)
  i=0;
for (i=0;i<pFrom->iNo;i++)
{
  pF= (E_Object3*) pFrom->Objs[i];
  pN=GetOtherNode(pF,pFace);
  if (pN!=NULL)
  {
     pCand->AddEx(pN);
  }
}
//find the node whcih give the most face seperation
//for each existing face edge form the face to the
//other posisble nodes and check they are distinct from
//the current one and not co-planar
 Node* n1;
 Node* n2;
 int j;
 C3dVector vFN;
 C3dVector vFC;
 C3dVector vC;
 E_Object3 pTE;
 double dA;
 dA=pFace->GetCharSize();
 dA*=0.1;
pRet=(Node*) pCand->Objs[0];
if (pCand->iNo>0)
{  
 for (i=0;i<pFrom->iNo;i++)
 {
    pF= (E_Object3*) pFrom->Objs[i];
    pN=GetOtherNode(pF,pFace);
	vFN=pF->Get_Normal();
	vFC=pF->Get_Centroid();
	//edge nodes n1,n2
	if ((pF->pVertex[0]!=pN) && (pF->pVertex[1]!=pN))
	  {n1=pF->pVertex[0];n2=pF->pVertex[1];}
	else if ((pF->pVertex[1]!=pN) && (pF->pVertex[2]!=pN))
	  {n1=pF->pVertex[1];n2=pF->pVertex[2];}
	else
      {n1=pF->pVertex[2];n2=pF->pVertex[0];}
	for (j=0;j<pCand->iNo;j++)   //For each possible node available
	{
      if (pCand->Objs[j]!=pN)
	  {
         pTE.pVertex[0]=(Node*) n1;
		 pTE.pVertex[1]=(Node*) n2;
		 pTE.pVertex[2]=(Node*) pCand->Objs[j];
         vC=pTE.Get_Centroid();
         vC-=vFC;
		 double dd=vC.Dot(vFN);
		 if (vC.Dot(vFN)>dA)
		 {
           pRet=(Node*) pCand->Objs[j];
		   break;
		 }
	  }
	}
 }
}
//Report diagnostics
//char S1[200]="";
//sprintf_s(S1,"No off conflicting nodes: %i %i",pCand->iNo,pFace->iLabel);
//outtext1(S1); 

delete (pCand);
return(pRet);
}

//Get node in pFrom thats not in pFace
Node* DBase::GetOtherNode(E_Object3* pFrom, E_Object3* pFace)
{
Node* pRet=NULL;
if (pFace->NodeInEl(pFrom->pVertex[0])==FALSE)
{pRet=pFrom->pVertex[0];}
else if (pFace->NodeInEl(pFrom->pVertex[1])==FALSE)
{pRet=pFrom->pVertex[1];}
else if (pFace->NodeInEl(pFrom->pVertex[2])==FALSE)
{pRet=pFrom->pVertex[2];}
else
{}

return(pRet);
}

//Find the other face conected to N1 & N2 nut not N3
//Note if the face is the existing face NULL will be returned
E_Object3* DBase::GetAdjFace(ObjList* pFrom,Node* N1,Node* N2,Node* N3,E_Object3* pExclude)
{
  E_Object3* pFace=NULL;
  E_Object3* pE=NULL;
  int i;
  for (i=0;i<pFrom->iNo;i++)
  {
    pE = (E_Object3*) pFrom->Objs[i];
	if (pE!=pExclude)
	{
      if ((pE->NodeInEl(N1)) && (pE->NodeInEl(N2)))
	  {
        if (pE->NodeInEl(N3)==FALSE) 
	    {
          pFace=pE; 
		  break;
	    }
	  }
	}
  }
return (pFace);
}




double DBase::AngleBetweenFaces(E_Object3* pFace1,E_Object3* pFace2)
{
double dAng=0;
double dS;
C3dVector N1=pFace1->Get_Normal();
C3dVector N2=pFace2->Get_Normal();
C3dVector C1=pFace1->Get_Centroid();
C3dVector C2=pFace2->Get_Centroid();
C2-=C1;
//C2.Normalize();
dS=C2.Dot(N1);
dAng=N1.Dot(N2);
dAng=acos(dAng);
dAng*=57.29577951;
if (dS>0)
  dAng=180.0-dAng;
else
  dAng=180+dAng;

return (dAng);
}

void DBase::GetAdjFaces(ObjList* pFrom,E_Object3* pFace, ObjList* pRes,double* dAngO,E_Object3*& pEl)
{
int i;
pRes->Clear();
E_Object3* pE;
C3dVector v1;
C3dVector v2;
C3dVector vN;
C3dVector vFN;
C3dVector vFD;
C3dVector vFC;
C3dVector vD;
C3dVector E0;
C3dVector E1;
double MinAng=360;

bool bE;
int iCnt=0;
double dAng;
vFN=pFace->Get_Normal();
vFC=pFace->Get_Centroid();
pEl=NULL;
  for (i=0;i<pFrom->iNo;i++)
  {
    pE = (E_Object3*) pFrom->Objs[i];
	if (pE!=pFace)
	{
		bE=FALSE;
	    if ((pE->NodeInEl(pFace->pVertex[0])) && (pE->NodeInEl(pFace->pVertex[1])))
		{
           E0=pFace->pVertex[0]->Get_Centroid();
           E1=pFace->pVertex[1]->Get_Centroid();
           bE=TRUE;
		   goto lDone;
		}
		if ((pE->NodeInEl(pFace->pVertex[1])) && (pE->NodeInEl(pFace->pVertex[2])))
		{
           E0=pFace->pVertex[1]->Get_Centroid();
           E1=pFace->pVertex[2]->Get_Centroid();
           bE=TRUE;
		   goto lDone;
		}
		if ((pE->NodeInEl(pFace->pVertex[2])) && (pE->NodeInEl(pFace->pVertex[0])))
		{
           E0=pFace->pVertex[2]->Get_Centroid();
           E1=pFace->pVertex[0]->Get_Centroid();
		   bE=TRUE;
		}
lDone:
        if (bE)  //Then Common edge
		{
		  E1-=E0;                  //The base edge vector
		  E1.Normalize();

          v1=pE->Get_Centroid();
	      v1-=vFC;
	      v1.Normalize();
	      vN=pE->Get_Normal();

          C3dVector vNN;
		  double dND;
          vNN=vFN.Cross(vN);
          dND=vNN.Dot(E1);

          dAng = AngleBetweenFaces(pFace,pE);
	      if ((dAng<100) && (dND<0))
		  {
			if (dAng<MinAng)
			{
               *dAngO=dAng;
               MinAng=dAng;
               pEl=pE;
			}
	        pRes->Add(pE);
			iCnt++;
			if (iCnt>2)
				break;
		  }
	  }
    }
  }
  pRes->Remove(pFace);
}

void DBase::GetCandiatesNode(E_Object3* pFace, ObjList* pFrom, C3dVector vC, double dCD, ObjList* pRes)
{
	int i;
	C3dVector vT;
	C3dVector vFC;
	C3dVector vFN;

	G_Object* pO;
	double dDot;
	double dDist;
	vFC = pFace->Get_Centroid();
	vFN = pFace->Get_Normal();
	for (i = 0; i < pFrom->iNo; i++)
	{
		pO = pFrom->Objs[i];
		vT = pO->Get_Centroid();
		dDist = vT.Dist(vC);
		vT -= vFC;
		vT.Normalize();

		dDot = vT.Dot(vFN);
		if ((dDist < dCD) && (dDot >= 0.1))      // if node is smaller than critical distance it a posible
			pRes->Add(pO);
	}
}

//**************************************************************
//Pre: pFrom linked list to search
//     vC search point
//     dCD critcal distance
//     pRes results list
//Post: For aall items in pFrom centroid distance to vC that are within dCD
//      returned in pRes
//**************************************************************
void DBase::GetCandiates(cLinkedList* pFrom,C3dVector vC, double dCD, ObjList* pRes)
{
  C3dVector vT;
  pRes->Clear();
  double dDist;
  G_Object* pNext;
  pNext = pFrom->Head;
  while (pNext != NULL)
  {
    vT= pNext->Get_Centroid();
    dDist=vT.Dist(vC);
    if (dDist<dCD)         // if distacnce is smaller than critical distance it a posible
	  pRes->Add(pNext);
	pNext = (G_Object*)pNext->next;
  }
}

void DBase::ZeroRemeshFlg(cLinkedList* pFrom)
{

	E_Object3* pNext;
	pNext =(E_Object3*) pFrom->Head;
	while (pNext != NULL)
	{
		pNext->iNoRemesh = 0;
		pNext = (E_Object3*) pNext->next;
	}
}

void DBase::GetCandiateFaces(E_Object3* pBF,ObjList* pFrom,C3dVector vC, double dCD, ObjList* pRes)
{
  int i;
  C3dVector vT;
  C3dVector vTN;
  C3dVector vTC;
  C3dVector vBC;
  C3dVector vA;
  pRes->Clear();
  E_Object3* pO;
  double dDist;
  double dDot;
  vBC=pBF->Get_Centroid();

  for (i=0;i<pFrom->iNo;i++)
  {
    pO =  (E_Object3*) pFrom->Objs[i];
    vTN=pO->Get_Normal();
    vTC=pO->Get_Centroid();
    vA=vBC;vA-=vTC;vA.Normalize();
    
    dDot=vA.Dot(vTN);
	if (dDot>0)
	{
      vT=pO->Get_Centroid();
      dDist=vT.Dist(vC);
      if (dDist<dCD)         // if node is smaller than critical distance it a posible
	    pRes->Add(pO);
	  }
  }
}



void DBase::AddPressure(ObjList* Els,C3dVector F)
{
int i;
int iSet;
if (pCurrentMesh->iCurLC!=-1)
{
for (i=0;i<Els->iNo;i++)
{ 
 if (Els->Objs[i]->iObjType==3) 
 {
   E_Object* pE = (E_Object*) Els->Objs[i];
   if ((pE->pParent!=NULL) && ((pE->iType==91) || (pE->iType==94)))
   {
    if (pE->pParent->iObjType==4)
	  {
		ME_Object* ME= (ME_Object*) pE->pParent;
		G_Object* cAddedM;
		iSet = ME->GetLCID(ME->iCurLC);
		cAddedM = ME->AddPressure((E_Object*) pE, F,iSet);
		Dsp_Add(cAddedM);
		AddTempGraphics(cAddedM);
	  }
   }
 }
}
ReDraw();
}
else
{
  outtext1("ERROR: No Load Set is Active.");
}
}

void DBase::RESLISTEL(ObjList* Els)
{
int i;
char S1[80];
float fRes;
if (pCurrentMesh!=NULL)
{  
if (pCurrentMesh->CResSet!=NULL)
{
    outtext1(pCurrentMesh->CResSet->sName);
	outtext1("TITLE:-" + pCurrentMesh->CResSet->sTitle);
	outtext1("SUBTITLE:-" + pCurrentMesh->CResSet->sSubTitle);
	if (pCurrentMesh->iCVar!=-1)
	   outtext1(pCurrentMesh->CResSet->lab[pCurrentMesh->iCVar]);
	for (i=0;i<Els->iNo;i++)
	{ 
	 if (Els->Objs[i]->iObjType==3) 
	 {
	   E_Object* pE = (E_Object*) Els->Objs[i];
       if (pE->pResV!=NULL)
	   {
	     fRes=(*pE->pResV->GetAddress(pCurrentMesh->iCVar));
         sprintf_s(S1,"LAB: %i VAL: %g ",pE->iLabel,fRes);
         outtext1(S1); 
	   }
	 }
	}
}
else
{
  outtext1("ERROR: No Results."); 
}
}
else
{

}
}

void DBase::RESLISTND(ObjList* Nds)
{
	int i;
	char S1[80];
	float fRes;
	if (pCurrentMesh != NULL)
	{
		if (pCurrentMesh->CResSet != NULL)
		{
			outtext1(pCurrentMesh->CResSet->sName);
			outtext1("TITLE:-" + pCurrentMesh->CResSet->sTitle);
			outtext1("SUBTITLE:-" + pCurrentMesh->CResSet->sSubTitle);
			if (pCurrentMesh->iCVar != -1)
				outtext1(pCurrentMesh->CResSet->lab[pCurrentMesh->iCVar]);
			for (i = 0; i < Nds->iNo; i++)
			{
				if (Nds->Objs[i]->iObjType == 1)
				{
					Node* pN = (Node*) Nds->Objs[i];
					if (pN->pResV != NULL)
					{
						fRes = (*pN->pResV->GetAddress(pCurrentMesh->iCVar));
						sprintf_s(S1, "LAB: %i VAL: %g ", pN->iLabel, fRes);
						outtext1(S1);
					}
				}
			}
		}
		else
		{
			outtext1("ERROR: No Results.");
		}
	}
	else
	{

	}
}

void DBase::AddRestraint(ObjList* Nodes,C3dVector TDofSet,C3dVector RDofSet)
{
int i;
int iSet = -1;
BOOL xon,yon,zon,rxon,ryon,rzon;
xon = FALSE;
yon = FALSE;
zon = FALSE;
rxon = FALSE;
ryon = FALSE;
rzon = FALSE;
if (pCurrentMesh->iCurBC!=-1)
{
if (TDofSet.x==1) xon=TRUE;
if (TDofSet.y==1) yon=TRUE;
if (TDofSet.z==1) zon=TRUE;
if (RDofSet.x==1) rxon=TRUE;
if (RDofSet.y==1) ryon=TRUE;
if (RDofSet.z==1) rzon=TRUE;

for (i=0;i<Nodes->iNo;i++)
{     
 if (Nodes->Objs[i]->iObjType==1)
 {
   Node* pN = (Node*) Nodes->Objs[i];
   if (pN->pParent!=NULL)
   {
      if (pN->pParent->iObjType==4)
	  {
		ME_Object* ME= (ME_Object*) pN->pParent;
        G_Object* cAddedR;
		iSet = ME->GetBCID(ME->iCurBC);
        cAddedR = ME->AddRestraint((Node*) pN, xon,yon,zon,rxon,ryon,rzon, iSet);
		if (cAddedR!=NULL)
          Dsp_Add(cAddedR);
	  }
   }
 }
}
InvalidateOGL();
ReDraw();
}
else
{
  outtext1 ("ERROR: No Boundary Set Active.");
}
}

void DBase::CoincidentNodes(ObjList* Nodes,ObjList* CNodes,double dTol)
{
  int i=0;
  int j=0;
  C3dVector v1;
  C3dVector v2;
  double dDist;
  while (i<Nodes->iNo-1)
  {
    if (Nodes->Objs[i]->iObjType==1)
    {
      v1=Nodes->Objs[i]->Get_Centroid();
      for (j=i+1;j<Nodes->iNo;j++)
      {
        if (Nodes->Objs[j]->iObjType==1)
        {
          v2=Nodes->Objs[j]->Get_Centroid();
          dDist=v1.Dist(v2);
          if (dDist<dTol)
          {
             CNodes->AddEx(Nodes->Objs[i]);
             CNodes->AddEx(Nodes->Objs[j]);
          }
        }
      }
    }
    i++;
  }

}


void DBase::CoincidentElements (ObjList* Chkls)
{
  ObjList* CElm;
  ObjList* CAllElm;
  CElm=new(ObjList);
  CAllElm = new(ObjList);
  
  CAllElm->Clear();
  double dTol=0.0000001;
  int i = 0;
  int j = 0;
  C3dVector v1;
  C3dVector v2;
  double dDist;
  while (i<Chkls->iNo - 1)
  {
    if (Chkls->Objs[i]->iObjType == 3)
    {
      CElm->Clear();
      CElm->Add(Chkls->Objs[i]);     //Add first elem which is being checked
      v1 = Chkls->Objs[i]->Get_Centroid();
      for (j = i + 1; j<Chkls->iNo; j++)
      {
        if (Chkls->Objs[j]->iObjType == 3)
        {
          v2 = Chkls->Objs[j]->Get_Centroid();
          dDist = v1.Dist(v2);
          if (dDist<dTol)
          {
            CElm->Add(Chkls->Objs[i]);
            //before adding here all nodes must be checked
            //to do
            CAllElm->Add(Chkls->Objs[i]);
          }
        }
      }
    }
    i++;
  }

  int iGP;
  CString sTit;
  sTit = "Coincident Elements";
  iGP = AddGp(sTit);
  for(i=0;i<CAllElm->iNo;i++)
    Groups[iGP]->Add(CAllElm->Objs[i]);
  CElm->Clear();
  CAllElm->Clear();
  delete(CElm);
  delete(CAllElm);
}

void DBase::FindNode(C3dVector vP)
{
	char s1[80];
	Node* cNode;
	double dMinDist = 1e36;
	sprintf_s(s1, "Closest Node To: %g,%g,%g",vP.x,vP.y,vP.z);
	outtext1(s1);
	if (pCurrentMesh != NULL)
	{
		cNode = pCurrentMesh->GetClosestNode2(vP, dMinDist);
		if (cNode != NULL)
		{
			sprintf_s(s1, "NID: %i DISTANCE: %g", cNode->iLabel, dMinDist);
			outtext1(s1);
			S_Buff[S_Count] = cNode;
			S_Count++;
		}
		else
		{
			outtext1("ERROR: No Node Found.");
		}
	}
	else
	{
		outtext1("WARNING: No Active Mesh.");
	}


}

CvPt_Object* DBase::AddPt(C3dVector InPt, int iLab,BOOL bRedraw)
{

CvPt_Object* pThePt = new CvPt_Object;
pThePt->Create(InPt,1,iPtLabCnt,0,0,11,NULL);
iPtLabCnt++;
AddObj(pThePt);
if (bRedraw)
  ReDraw();
return (pThePt);
}


void DBase::AddPt2(double x,double y,double z, int iLab)
{

C3dVector InPt(x,y,z);
CvPt_Object* pThePt = new CvPt_Object;
pThePt->Create(InPt,1,iPtLabCnt,0,0,11,NULL);
iPtLabCnt++;
AddObj(pThePt);
ReDraw();
}

C3dVector DBase::WPtoGlobal(C3dVector InPt)
{
C3dVector vTrans;
C3dVector vCart;

WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
vCart = InPt;
if (pWPlane->iWPMode == 1)
  {
  vCart = CylToCart(InPt);
  }
vTrans = (pWPlane->mWPTransform) * vCart;
return (vTrans);
}




C3dVector DBase::WPtoGlobal2(C3dVector InPt)
{
C3dVector vTrans;
C3dVector vCart;

WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
vCart = InPt;
vTrans = (pWPlane->mWPTransform) * vCart;
return (vTrans);
}




C3dMatrix DBase::GetWPmat()
{
  C3dMatrix mrc;
  mrc.MakeUnit();
  if (DB_Obj[iWP] != NULL)
  {
    WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
    mrc = pWPlane->mWPTransform;
  }
  return (mrc);
}

//Convert global to workplane  coordintes

C3dVector DBase::GlobaltoWP(C3dVector InPt)
{
C3dVector v1moved;
C3dVector v2Glob;
C3dMatrix mTran;
C3dMatrix mInv;


WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
mTran = pWPlane->mWPTransform;
v1moved = InPt;
v1moved.x = v1moved.x-mTran.m_30;
v1moved.y = v1moved.y-mTran.m_31;
v1moved.z = v1moved.z-mTran.m_32;
mTran.m_30=0;
mTran.m_31=0;
mTran.m_32=0;
mInv = mTran.Inv();
v2Glob = mInv*v1moved;

if (pWPlane->iWPMode == 1)
  {
  v2Glob = CartToCyl(v2Glob);
  }

return (v2Glob);
}

C3dVector DBase::GlobaltoWP3(C3dVector InPt)
{

C3dVector v2Glob;
C3dMatrix mTran;
WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
mTran = pWPlane->mWPTransform;
mTran.Translate2(0,0,0);
v2Glob = mTran*InPt;
return (v2Glob);
}


//Convert global to workplane CARTESIAN coordintes

C3dVector DBase::GlobaltoWP2(C3dVector InPt)
{
C3dVector v1moved;
C3dVector v2Glob;
C3dMatrix mTran;
C3dMatrix mInv;


WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
mTran = pWPlane->mWPTransform;
v1moved = InPt;
v1moved.x = v1moved.x-mTran.m_30;
v1moved.y = v1moved.y-mTran.m_31;
v1moved.z = v1moved.z-mTran.m_32;
mTran.m_30=0;
mTran.m_31=0;
mTran.m_32=0;
mInv = mTran.Inv();
v2Glob = mInv*v1moved;

return (v2Glob);
}

void DBase::ModNodeX(ObjList* Nodes, double dX)
{
  int i;
  C3dVector vTrans;
  C3dVector vCart;
  WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
  Node* pT;
  C3dVector vNewNode;
  for (i = 0; i<Nodes->iNo; i++)
  {
    pT = (Node*)Nodes->Objs[i];
    vNewNode.x = pT->Pt_Point->x;
    vNewNode.y = pT->Pt_Point->y;
    vNewNode.z = pT->Pt_Point->z;
    vNewNode = GlobaltoWP(vNewNode);
    vNewNode.x=dX;
    vNewNode = WPtoGlobal(vNewNode);
    pT->SetTo(vNewNode);
  }
  InvalidateOGL();
  ReDraw();
}


void DBase::ModNodeY(ObjList* Nodes, double dY)
{
  int i;
  C3dVector vTrans;
  C3dVector vCart;
  WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
  Node* pT;
  C3dVector vNewNode;
  for (i = 0; i<Nodes->iNo; i++)
  {
    pT = (Node*)Nodes->Objs[i];
    vNewNode.x = pT->Pt_Point->x;
    vNewNode.y = pT->Pt_Point->y;
    vNewNode.z = pT->Pt_Point->z;
    vNewNode = GlobaltoWP(vNewNode);
    vNewNode.y = dY;
    vNewNode = WPtoGlobal(vNewNode);
    pT->SetTo(vNewNode);
  }
  InvalidateOGL();
  ReDraw();
}

void DBase::ModNodeZ(ObjList* Nodes, double dZ)
{
  int i;
  C3dVector vTrans;
  C3dVector vCart;
  WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
  Node* pT;
  C3dVector vNewNode;
  for (i = 0; i<Nodes->iNo; i++)
  {
    pT = (Node*)Nodes->Objs[i];
    vNewNode.x = pT->Pt_Point->x;
    vNewNode.y = pT->Pt_Point->y;
    vNewNode.z = pT->Pt_Point->z;
    vNewNode = GlobaltoWP(vNewNode);
    vNewNode.z = dZ;
    vNewNode = WPtoGlobal(vNewNode);
    pT->SetTo(vNewNode);
  }
  InvalidateOGL();
  ReDraw(); 
}



void DBase::CpNodes(ObjList* Nodes,C3dVector vTrVect,int iNoOfTimes)
{
int i;
int j;

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
C3dVector vTrans;
C3dVector vCart;
WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
Node* cAddedNode;
Node* pT;
C3dVector vNewNode;

   for (i=0;i<Nodes->iNo;i++)
   {     
	   for (j=1;j<=iNoOfTimes;j++)
	   {   
		 pT = (Node*) Nodes->Objs[i];
	   vNewNode.x = pT->Pt_Point->x;
     vNewNode.y = pT->Pt_Point->y;
     vNewNode.z = pT->Pt_Point->z;
		 vNewNode=GlobaltoWP(vNewNode);
		 vNewNode+=vTrVect*j;
     vNewNode=WPtoGlobal(vNewNode);
     cAddedNode=pCurrentMesh->AddNode(vNewNode, pCurrentMesh->iNodeLab,0,0,pT->iColour,0,0);
		 pCurrentMesh->iNodeLab++;
     Dsp_Add(cAddedNode);
     AddTempGraphics(cAddedNode);
	   }
   }
InvalidateOGL();
ReDraw();
}

void DBase::RotateAbout(ObjList* Objs,C3dVector p1,C3dVector p2,double dAng)
{
int i;
C3dVector vX;
C3dVector vZ;
C3dVector vYP;
C3dVector vUp;
C3dMatrix mRot;
C3dMatrix mTform;
C3dMatrix Forward;
C3dMatrix Back;
vZ=p2;
vZ-=p1;
vZ.Normalize();
//Generate an outof plain vector
mRot.MakeUnit();
mRot.Rotate(45,45,45);

vUp=vZ.GenerateUp();
vX=vZ.Cross(vUp);
vYP=vZ.Cross(vX);
vZ.Normalize();
vYP.Normalize();
vX.Normalize();

Back.SetColVec(1,vX);
Back.SetColVec(2,vYP);
Back.SetColVec(3,vZ);
Forward=Back;
Back.Transpose();
mRot.MakeUnit();
mRot.Rotate(0,0,dAng);

mTform.MakeUnit();
mTform*=Forward;
mTform*=mRot;
mTform*=Back;
for (i=0;i<Objs->iNo;i++)
{     
    Objs->Objs[i]->Translate(-p1);
    Objs->Objs[i]->Transform(mTform);
    //Objs->Objs[i]->Transform(mRot);
    //Objs->Objs[i]->Transform(Forward);
    Objs->Objs[i]->Translate(p1);
    //Objs->Objs[i]->SetToScr(&pModelMat,&pScrMat);
}
InvalidateOGL();
ReDraw();
}


void DBase::RotateAbout2(G_Object* Obj,C3dVector p1,C3dVector p2,double dAng)
{
C3dVector vX;
C3dVector vZ;
C3dVector vYP;
C3dVector vUp;
C3dMatrix mRot;
C3dMatrix mTform;
C3dMatrix Forward;
C3dMatrix Back;
vZ=p2;
vZ-=p1;
vZ.Normalize();
//Generate an outof plain vector
mRot.MakeUnit();
mRot.Rotate(45,45,45);

vUp=vZ.GenerateUp();
vX=vZ.Cross(vUp);
vYP=vZ.Cross(vX);
vZ.Normalize();
vYP.Normalize();
vX.Normalize();

Back.SetColVec(1,vX);
Back.SetColVec(2,vYP);
Back.SetColVec(3,vZ);
Forward=Back;
Back.Transpose();
mRot.MakeUnit();
mRot.Rotate(0,0,dAng);

mTform.MakeUnit();
mTform*=Forward;
mTform*=mRot;
mTform*=Back;
if (Obj != NULL)
{     
    Obj->Translate(-p1);
    Obj->Transform(mTform);
    Obj->Translate(p1);
}
}

void DBase::Scale(ObjList* Objs,C3dVector p1,double dScale)
{
int i;
for (i=0;i<Objs->iNo;i++)
{     
  Scale2(Objs->Objs[i],p1,dScale);
}
InvalidateOGL();
ReDraw();
}

void DBase::Scale2(G_Object* Obj,C3dVector p1,double dScale)
{

C3dMatrix mScale;
mScale.Scale(dScale,dScale,dScale);
if (Obj != NULL)
{     
    Obj->Translate(-p1);
    Obj->Transform(mScale);
    Obj->Translate(p1);
}
}

void DBase::RotateAngs(ObjList* Objs,C3dVector pCent,C3dVector pRot)
{
int i;
C3dMatrix mRot;
mRot.Rotate(pRot.x,pRot.y,pRot.z);

for (i=0;i<Objs->iNo;i++)
{     
  Objs->Objs[i]->Translate(-pCent);
  Objs->Objs[i]->Transform(mRot);
  Objs->Objs[i]->Translate(pCent);
  //Objs->Objs[i]->SetToScr(&pModelMat,&pScrMat);
}
InvalidateOGL();
ReDraw();
}

void DBase::Reflect(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3)
{
int i;
int k;
int iNewNd=-1;
NEList* newNds = new NEList();
G_Object* pO;
G_Object* pOC;
C3dVector vA;
Node* pInVertex[MaxSelNodes];
Node* Nd;
Node* NdNew;
E_Object* El;
E_Object* ENew;

C3dVector vX;
C3dVector vZ;
C3dVector vYP;
C3dMatrix ZRef;
C3dMatrix Back;
C3dMatrix Forward;
vX=p2;
vX-=p1;
vX.Normalize();
vYP=p3;
vYP-=p1;
vYP.Normalize();
ZRef.MakeUnit();
ZRef.m_22=-1;
C3dMatrix tForm;

if ((vX.Mag()!=0) && (vYP.Mag()!=0))
{
  if ((abs(vX.Dot(vYP))!=1))
  {
    vZ=vX.Cross(vYP);
    vYP=vZ.Cross(vX);
    vZ.Normalize();
    vYP.Normalize();
    vX.Normalize();
    Back.SetColVec(1,vX);
    Back.SetColVec(2,vYP);
    Back.SetColVec(3,vZ);
    Forward=Back;
    Back.Transpose();

    tForm.MakeUnit();
    tForm*=Forward;
    tForm*=ZRef;
    tForm*=Back;
    //for (i=0;i<Objs->iNo;i++)
    //{     
    //  Objs->Objs[i]->Translate(-p1);
    //  Objs->Objs[i]->Transform(tForm);
   //   Objs->Objs[i]->Translate(p1);
    //}
  }
}
pCurrentMesh->MaxLab();
if (Objs->iNo>0)
{
//pCurrentMesh->iElementLab++;
//pCurrentMesh->iNodeLab++;

  newNds->iNo=0;
  for (i=0;i<Objs->iNo;i++)
  {
    if (Objs->Objs[i]->iObjType==3)
    {
      El= (E_Object*) Objs->Objs[i];
      for (k=0;k<El->iNoNodes;k++)
      {
        Nd=(Node*) El->GetNode(k);
        iNewNd=newNds->Get(Nd->iLabel);
        if (iNewNd!=-1)
        {
          pInVertex[k]=(Node*) pCurrentMesh->GetNode(iNewNd);
        }
        else
        {
          pInVertex[k]=(Node*) El->GetNode(k)->Copy(pCurrentMesh);
          pInVertex[k]->iLabel=pCurrentMesh->iNodeLab;
          newNds->Add(Nd->iLabel,pCurrentMesh->iNodeLab);
          pCurrentMesh->iNodeLab++;
          pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=pInVertex[k];
          pCurrentMesh->iNdNo++;
          pInVertex[k]->Translate(-p1);
          pInVertex[k]->Transform(tForm);
          pInVertex[k]->Translate(p1);
          Dsp_Add(pInVertex[k]);
        }
      }
      ENew=(E_Object*) El->Copy2(pCurrentMesh,pInVertex,El->PID,El->iMatID,El->PIDunv);
      pCurrentMesh->pElems[pCurrentMesh->iElNo]=ENew;
      pCurrentMesh->iElNo++    ;             
      ENew->iLabel=pCurrentMesh->iElementLab;
      Dsp_Add(ENew);
      pCurrentMesh->iElementLab++;
    }
}

for (i=0;i<Objs->iNo;i++)
{
  if ((Objs->Objs[i]->iObjType==1) || (Objs->Objs[i]->iObjType==3) || (Objs->Objs[i]->iObjType==13))
  {
    if (Objs->Objs[i]->iObjType==1)
    {
      Nd= (Node*) Objs->Objs[i];
      NdNew=(Node*) Nd->Copy(pCurrentMesh);
      NdNew->iLabel=pCurrentMesh->iNodeLab;
      newNds->Add(Nd->iLabel,pCurrentMesh->iNodeLab);
      pCurrentMesh->iNodeLab++;
      pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=NdNew;
      //Dsp_Add(NdNew);
      NdNew->Translate(-p1);
      NdNew->Transform(tForm);
      NdNew->Translate(p1);
      Dsp_Add(NdNew);
      pCurrentMesh->iNdNo++;
    }   
  }
  else
  {
     pOC=Objs->Objs[i];
     pO=NULL;
	if (pOC->iObjType==0)             //POINTS
	{ 
		pO = Objs->Objs[i]->Copy(NULL);
		pO->iLabel=iPtLabCnt;
		iPtLabCnt++;
    }
	else if (pOC->iObjType == 6)
	{
		pO = Objs->Objs[i]->Copy(NULL);
		pO->iLabel = iTxtLabCnt;
		iTxtLabCnt++;
	}
    else if (pOC->iObjType==7) 
    {
		pO = Objs->Objs[i]->Copy(NULL);
		pO->iLabel=iCVLabCnt;
		iCVLabCnt++;
     }
     else if (pOC->iObjType==15)
     {
		pO = Objs->Objs[i]->Copy(NULL);
		pO->iLabel=iSFLabCnt;
		iSFLabCnt++;
     }
     if (pO!=NULL)
     {
		pO->pParent=NULL;
		pO->Translate(-p1);
		pO->Transform(tForm);
		pO->Translate(p1);
		AddObj(pO);
     }
  }
}
delete (newNds);
InvalidateOGL();
ReDraw();
}
}

void DBase::Reflect2(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3)
{
int i;
C3dVector vX;
C3dVector vZ;
C3dVector vYP;
C3dMatrix ZRef;
C3dMatrix Back;
C3dMatrix Forward;
vX=p2;
vX-=p1;
vX.Normalize();
vYP=p3;
vYP-=p1;
vYP.Normalize();
ZRef.MakeUnit();
ZRef.m_22=-1;


if ((vX.Mag()!=0) && (vYP.Mag()!=0))
{
  if ((abs(vX.Dot(vYP))!=1))
  {
    vZ=vX.Cross(vYP);
    vYP=vZ.Cross(vX);
    vZ.Normalize();
    vYP.Normalize();
    vX.Normalize();
    Back.SetColVec(1,vX);
    Back.SetColVec(2,vYP);
    Back.SetColVec(3,vZ);
    Forward=Back;
    Back.Transpose();
    C3dMatrix tForm;
    tForm.MakeUnit();
    tForm*=Forward;
    tForm*=ZRef;
    tForm*=Back;
    for (i=0;i<Objs->iNo;i++)
    {     
      Objs->Objs[i]->Translate(-p1);
      Objs->Objs[i]->Transform(tForm);
      Objs->Objs[i]->Translate(p1);
    }
  }
}
InvalidateOGL();
ReDraw();
}

void DBase::Reflect2d(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3)
{
int i;
C3dVector vX;
C3dVector vZ;
C3dVector vYP;
C3dMatrix ZRef;
C3dMatrix Back;
C3dMatrix Forward;
vX=p2;
vX-=p1;
vX.Normalize();
vYP=p3;
vYP-=p1;
vYP.Normalize();
ZRef.MakeUnit();
ZRef.m_22=-1;
G_Object* pO;

if ((vX.Mag()!=0) && (vYP.Mag()!=0))
{
  if ((abs(vX.Dot(vYP))!=1))
  {
    vZ=vX.Cross(vYP);
    vYP=vZ.Cross(vX);
    vZ.Normalize();
    vYP.Normalize();
    vX.Normalize();
    Back.SetColVec(1,vX);
    Back.SetColVec(2,vYP);
    Back.SetColVec(3,vZ);
    Forward=Back;
    Back.Transpose();
    C3dMatrix tForm;
    tForm.MakeUnit();
    tForm*=Forward;
    tForm*=ZRef;
    tForm*=Back;
    for (i=0;i<Objs->iNo;i++)
    {     
	  if ((Objs->Objs[i]->iObjType==0) ||
          (Objs->Objs[i]->iObjType==7) ||
		  (Objs->Objs[i]->iObjType==15)) 
	  {
	    pO=Objs->Objs[i]->Copy(NULL);
		if (pO->iObjType==0)
		{  //Point
          pO->iLabel=iPtLabCnt;
	      iPtLabCnt++;
		}
		else if (pO->iObjType==7)
		{//curve
          pO->iLabel=iCVLabCnt;
		  iCVLabCnt++;
		}
		else if (pO->iObjType==15) 
		{//surface
          pO->iLabel=iSFLabCnt;
	      iSFLabCnt++;
		}
        pO->Translate(-p1);
        pO->Transform(tForm);
        pO->Translate(p1);
		AddObj(pO);
	  }
    }
  }
}
InvalidateOGL();
ReDraw();
}


void DBase::Align(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3,
                                C3dVector p4,C3dVector p5,C3dVector p6)
{
int i;
C3dVector vX;
C3dVector vZ;
C3dVector vYP;
C3dVector vX2;
C3dVector vZ2;
C3dVector vYP2;
C3dMatrix Back;
C3dMatrix Forward;
vX=p2;
vX-=p1;
vX.Normalize();
vYP=p3;
vYP-=p1;
vYP.Normalize();

vX2=p5;
vX2-=p4;
vX2.Normalize();
vYP2=p6;
vYP2-=p4;
vYP2.Normalize();


if ((vX.Mag()!=0) && (vYP.Mag()!=0) && (vX2.Mag()!=0) && (vYP2.Mag()!=0))
{
  if ((abs(vX.Dot(vYP))!=1) && (abs(vX2.Dot(vYP2))!=1))
  {
    vZ=vX.Cross(vYP);
    vYP=vZ.Cross(vX);
    vZ.Normalize();
    vYP.Normalize();
    vX.Normalize();
    vZ2=vX2.Cross(vYP2);
    vYP2=vZ2.Cross(vX2);
    vZ2.Normalize();
    vYP2.Normalize();
    vX2.Normalize();
    Back.SetColVec(1,vX);
    Back.SetColVec(2,vYP);
    Back.SetColVec(3,vZ);
    Back.Transpose();
    Forward.SetColVec(1,vX2);
    Forward.SetColVec(2,vYP2);
    Forward.SetColVec(3,vZ2);
    for (i=0;i<Objs->iNo;i++)
    {     
      Objs->Objs[i]->Translate(-p1);
      Objs->Objs[i]->Transform(Back);
      Objs->Objs[i]->Transform(Forward);
      Objs->Objs[i]->Translate(p4);
      //Objs->Objs[i]->SetToScr(&pModelMat,&pScrMat);
    }
  }
}
InvalidateOGL();
ReDraw();
}

void DBase::Move(ObjList* Nodes,C3dVector vTrVect)
{
int i;
for (i=0;i<Nodes->iNo;i++)
{     
  Nodes->Objs[i]->Move(vTrVect);
  Nodes->Objs[i]->SetToScr(&pModelMat,&pScrMat);
}
InvalidateOGL();
ReDraw();
}

void DBase::BetNodes(ObjList* Nodes,ObjList* Nodes2,int iNoOfTimes)
{
int i;
int j;

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
C3dVector vTrans;
C3dVector vCart;
WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
int bWPMode = pWPlane->iWPMode;
Node* cAddedNode;
Node* pT;
C3dVector vNewNode;
C3dVector vN1;
C3dVector vN2;
C3dVector vDiff;
double ds;
if ((Nodes->iNo>0) && (Nodes2->iNo>0))
{
if (Nodes->iNo == Nodes2->iNo)
{
   for (i=0;i<Nodes->iNo;i++)
   { 
	  pT = (Node*) Nodes->Objs[i];
	  vN1.x = pT->Pt_Point->x;
      vN1.y = pT->Pt_Point->y;
      vN1.z = pT->Pt_Point->z;
	  pT = (Node*) Nodes2->Objs[i];
	  vN2.x = pT->Pt_Point->x;
      vN2.y = pT->Pt_Point->y;
      vN2.z = pT->Pt_Point->z;
	  vN1=GlobaltoWP(vN1);
      vN2=GlobaltoWP(vN2);
	  if (bWPMode == 1) // polar coords
	  {
		  if (vN2.y < vN1.y)
			  vN2.y += 360.0;
	  }
	  vDiff=vN2;
      vDiff-=vN1;
	  for (j=1;j<=iNoOfTimes;j++)
		{   
		  ds=j;
		  ds = ds	/(iNoOfTimes+1);
          vNewNode=vN1;
		  vNewNode.x=vNewNode.x+vDiff.x*ds;
		  vNewNode.y=vNewNode.y+vDiff.y*ds;
		  vNewNode.z=vNewNode.z+vDiff.z*ds;
          vNewNode=WPtoGlobal(vNewNode);
          cAddedNode=pCurrentMesh->AddNode(vNewNode, pCurrentMesh->iNodeLab,0,0,11,0,0);
		  pCurrentMesh->iNodeLab++;
          AddTempGraphics(cAddedNode);
		  Dsp_Add(cAddedNode);
	  }
     }
}
else if ((Nodes->iNo == 1) && (Nodes2->iNo>0))
{
   for (i=0;i<Nodes2->iNo;i++)
   { 
	  pT = (Node*) Nodes->Objs[0];
	  vN1.x = pT->Pt_Point->x;
      vN1.y = pT->Pt_Point->y;
      vN1.z = pT->Pt_Point->z;
	  pT = (Node*) Nodes2->Objs[i];
	  vN2.x = pT->Pt_Point->x;
      vN2.y = pT->Pt_Point->y;
      vN2.z = pT->Pt_Point->z;
	  vN1=GlobaltoWP(vN1);
      vN2=GlobaltoWP(vN2);
	  if (bWPMode == 1) // polar coords
	  {
		  if (vN2.y < vN1.y)
			  vN2.y += 360.0;
	  }
	  vDiff=vN2;
      vDiff-=vN1;
	  for (j=1;j<=iNoOfTimes;j++)
	  {   
		ds=j;
		ds = ds	/(iNoOfTimes+1);
        vNewNode=vN1;
		vNewNode.x=vNewNode.x+vDiff.x*ds;
		vNewNode.y=vNewNode.y+vDiff.y*ds;
		vNewNode.z=vNewNode.z+vDiff.z*ds;
        vNewNode=WPtoGlobal(vNewNode);
        cAddedNode=pCurrentMesh->AddNode(vNewNode, pCurrentMesh->iNodeLab,0,0,11,0,0);
		pCurrentMesh->iNodeLab++;
        AddTempGraphics(cAddedNode);
		Dsp_Add(cAddedNode);
	  }
     }
}
else if ((Nodes->iNo > 0) && (Nodes2->iNo==1))
{
   for (i=0;i<Nodes->iNo;i++)
   { 
	  pT = (Node*) Nodes->Objs[i];
	  vN1.x = pT->Pt_Point->x;
      vN1.y = pT->Pt_Point->y;
      vN1.z = pT->Pt_Point->z;
	  pT = (Node*) Nodes2->Objs[0];
	  vN2.x = pT->Pt_Point->x;
      vN2.y = pT->Pt_Point->y;
      vN2.z = pT->Pt_Point->z;
	  vN1=GlobaltoWP(vN1);
      vN2=GlobaltoWP(vN2);
	  if (bWPMode == 1) // polar coords
	  {
		  if (vN2.y < vN1.y)
			  vN2.y += 360.0;
	  }
	  vDiff=vN2;
      vDiff-=vN1;
	  for (j=1;j<=iNoOfTimes;j++)
	  {   
		ds=j;
		ds = ds	/(iNoOfTimes+1);
        vNewNode=vN1;
		vNewNode.x=vNewNode.x+vDiff.x*ds;
		vNewNode.y=vNewNode.y+vDiff.y*ds;
		vNewNode.z=vNewNode.z+vDiff.z*ds;
        vNewNode=WPtoGlobal(vNewNode);
        cAddedNode=pCurrentMesh->AddNode(vNewNode, pCurrentMesh->iNodeLab,0,0,11,0,0);
		pCurrentMesh->iNodeLab++;
		Dsp_Add(cAddedNode);
        AddTempGraphics(cAddedNode);
	  }
     }
}
}
ReDraw();
}

//Intersect one set of TRI element with another set
void DBase::IntersectEls(ObjList* Els1)
{
	int i;
	int j;
	int iCol = -1;
	BOOL bI;
	CvPt_Object* pThePt = NULL;
	C3dVector p0;
	C3dVector p1;
	C3dVector p2;
	C3dVector vInt;
	double dS= 0;		//Parametric ordinates of intersection a seg with triange;
	double dT = 0;		//Parametric ordinates of intersection a seg with triange
	double dTol = 0.0001;
	int iNoInts = 0;
	E_Object* pE = NULL;
	E_Object3* pEInt = NULL;
	E_Object3* pETarget = NULL;
	for (i = 0; i < Els1->iNo; i++)
	{
		if ((Els1->Objs[i]->iObjType == 3) && (Els1->Objs[i]->iType == 91))
		{
			//Element to intersect
			pEInt = (E_Object3*)Els1->Objs[i];
			p0 = pEInt->pVertex[0]->Get_Centroid();
			p1 = pEInt->pVertex[1]->Get_Centroid();
			p2 = pEInt->pVertex[2]->Get_Centroid();
			//Target elements
			for (j = 0; j < Els1->iNo; j++)
			{
					if ((pEInt!= Els1->Objs[j]) && (Els1->Objs[j]->iObjType == 3) && (Els1->Objs[j]->iType == 91))
					{
						pETarget = (E_Object3*)Els1->Objs[j];
						bI = LineIntTRI(p0, p1, pETarget, vInt, dS, dT, dTol);
						if (bI)
						{
							pThePt = new CvPt_Object;
							pThePt->Create(vInt, 1, iPtLabCnt, 0, 0, 11, NULL);
							iPtLabCnt++;
							AddObj(pThePt);
							iNoInts++;
						}
						bI = LineIntTRI(p1, p2, pETarget, vInt, dS, dT, dTol);
						if (bI)
						{
							pThePt = new CvPt_Object;
							pThePt->Create(vInt, 1, iPtLabCnt, 0, 0, 11, NULL);
							iPtLabCnt++;
							AddObj(pThePt);
							iNoInts++;
						}
						bI = LineIntTRI(p2, p0, pETarget, vInt, dS, dT, dTol);
						if (bI)
						{
							pThePt = new CvPt_Object;
							pThePt->Create(vInt, 1, iPtLabCnt, 0, 0, 11, NULL);
							iPtLabCnt++;
							AddObj(pThePt);
							iNoInts++;
						}

					}
			}
		}

	}
	char s1[200];
	sprintf_s(s1, "No of Intersection Points Generated: %i", iNoInts);
	outtext1(s1);
	ReDraw();

}


//Intersect one set of TRI element with the WP
void DBase::IntersectElsWP(ObjList* Els1)
{
	int i;
	int j;
	int iCol = -1;
	BOOL bI;
	CvPt_Object* pThePt = NULL;
	C3dVector p0;
	C3dVector p1;
	C3dVector p2;
	C3dVector vInt;
	double dS = 0;		//Parametric ordinates of intersection a seg with triange;
	double dT = 0;		//Parametric ordinates of intersection a seg with triange
	double dTol = 0.0001;
	int iNoInts = 0;
	E_Object* pE = NULL;
	E_Object3* pEInt = NULL;
	E_Object3* pETarget = NULL;
	ObjList* WP = new ObjList();
	//Create 2 Tri element that are the size of the WP
	WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
	E_Object3* WP1 = new E_Object3();
	E_Object3* WP2 = new E_Object3();
	C3dMatrix TMAT = pWPlane->mWPTransform;
	C3dVector vPt;

	Node* N1 = new Node();
	vPt.Set(pWPlane->Pt_Point[0]->x, pWPlane->Pt_Point[0]->y, pWPlane->Pt_Point[0]->z );
	vPt = TMAT * vPt;
	N1->Pt_Point = new C3dVector(vPt.x, vPt.y, vPt.z);
	Node* N2 = new Node();
	vPt.Set(pWPlane->Pt_Point[1]->x, pWPlane->Pt_Point[1]->y, pWPlane->Pt_Point[1]->z);
	vPt = TMAT * vPt;
	N2->Pt_Point = new C3dVector(vPt.x, vPt.y, vPt.z);
	Node* N3 = new Node();
	vPt.Set(pWPlane->Pt_Point[2]->x, pWPlane->Pt_Point[2]->y, pWPlane->Pt_Point[2]->z);
	vPt = TMAT * vPt;
	N3->Pt_Point = new C3dVector(vPt.x, vPt.y, vPt.z);
	Node* N4 = new Node();
	vPt.Set(pWPlane->Pt_Point[3]->x, pWPlane->Pt_Point[3]->y, pWPlane->Pt_Point[3]->z);
	vPt = TMAT * vPt;
	N4->Pt_Point = new C3dVector(vPt.x, vPt.y, vPt.z);
	WP1->pVertex[0] = N1;
	WP1->pVertex[1] = N2;
	WP1->pVertex[2] = N3;
	WP->Add(WP1);
	WP2->pVertex[0] = N1;
	WP2->pVertex[1] = N3;
	WP2->pVertex[2] = N4;
	WP->Add(WP2);
	for (i = 0; i < Els1->iNo; i++)
	{

			//Element to intersect
			pEInt = (E_Object3*)Els1->Objs[i];
			p0 = pEInt->pVertex[0]->Get_Centroid();
			p1 = pEInt->pVertex[1]->Get_Centroid();
			p2 = pEInt->pVertex[2]->Get_Centroid();
			//Target elements
			for (j = 0; j < WP->iNo; j++)
			{
					pETarget = (E_Object3*)WP->Objs[j];
					bI = LineIntTRI(p0, p1, pETarget, vInt, dS, dT, dTol);
					if (bI)
					{
						pThePt = new CvPt_Object;
						pThePt->Create(vInt, 1, iPtLabCnt, 0, 0, 11, NULL);
						iPtLabCnt++;
						AddObj(pThePt);
						iNoInts++;
					}
					bI = LineIntTRI(p1, p2, pETarget, vInt, dS, dT, dTol);
					if (bI)
					{
						pThePt = new CvPt_Object;
						pThePt->Create(vInt, 1, iPtLabCnt, 0, 0, 11, NULL);
						iPtLabCnt++;
						AddObj(pThePt);
						iNoInts++;
					}
					bI = LineIntTRI(p2, p0, pETarget, vInt, dS, dT, dTol);
					if (bI)
					{
						pThePt = new CvPt_Object;
						pThePt->Create(vInt, 1, iPtLabCnt, 0, 0, 11, NULL);
						iPtLabCnt++;
						AddObj(pThePt);
						iNoInts++;
					}
			}

	}
	char s1[200];
	sprintf_s(s1, "No of Intersection Points Generated: %i", iNoInts);
	outtext1(s1);
	ReDraw();

}


void DBase::ElsBetNodes(ObjList* Nodes,ObjList* Nodes2,int iNoOfTimes)
{
int i;
int j;

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
C3dVector vTrans;
C3dVector vCart;
WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
Node* cAddedNode;
Node* pT;
C3dVector vNewNode;
C3dVector vN1;
C3dVector vN2;
C3dVector vDiff;
double ds;
Matrix<Node*> Nds(Nodes->iNo,iNoOfTimes+2) ;

if ((Nodes->iNo>0) && (Nodes2->iNo>0) && (iNoOfTimes>=0))
{
  if (Nodes->iNo == Nodes2->iNo)
  {
	 for (i=0;i<Nodes->iNo;i++)
     { 
	   Nds(i,0)=(Node*) Nodes->Objs[i];
       Nds(i,iNoOfTimes+1)=(Node*) Nodes2->Objs[i];
	 }
     for (i=0;i<Nodes->iNo;i++)
     { 
	   pT = (Node*) Nodes->Objs[i];
	   vN1.x = pT->Pt_Point->x;
       vN1.y = pT->Pt_Point->y;
       vN1.z = pT->Pt_Point->z;
	   pT = (Node*) Nodes2->Objs[i];
	   vN2.x = pT->Pt_Point->x;
       vN2.y = pT->Pt_Point->y;
       vN2.z = pT->Pt_Point->z;
	   vN1=GlobaltoWP(vN1);
       vN2=GlobaltoWP(vN2);
	   vDiff=vN2;
       vDiff-=vN1;
	   for (j=1;j<=iNoOfTimes;j++)
	   {   
		  ds=j;
		  ds = ds	/(iNoOfTimes+1);
          vNewNode=vN1;
		  vNewNode.x=vNewNode.x+vDiff.x*ds;
		  vNewNode.y=vNewNode.y+vDiff.y*ds;
		  vNewNode.z=vNewNode.z+vDiff.z*ds;
          vNewNode=WPtoGlobal(vNewNode);
          cAddedNode=pCurrentMesh->AddNode(vNewNode, pCurrentMesh->iNodeLab,0,0,11,0,0);
		  Nds(i,j)=cAddedNode;
		  pCurrentMesh->iNodeLab++;
          AddTempGraphics(cAddedNode);
		  Dsp_Add(cAddedNode);
	  }
    }
	Node* iNlabs[MaxSelNodes]; 
    E_Object* pEl;
    for (i=0;i<Nodes->iNo-1;i++)
    {
      for (j=0;j<=iNoOfTimes;j++)
      {
        iNlabs[0]=Nds(i,j);
	    iNlabs[1]=Nds(i,j+1);
	    iNlabs[2]=Nds(i+1,j+1);
	    iNlabs[3]=Nds(i+1,j);
        pEl=pCurrentMesh->AddEl(iNlabs,pCurrentMesh->iElementLab,4,94,1,1,4,0,0,0,0,0,0);
        pCurrentMesh->iElementLab++;
        AddTempGraphics(pEl);
		Dsp_Add(pEl);
     }
    }
  }
  else 
  {
    outtext1("ERROR: Unequal Number of Nodes.");
  }

}
ReDraw();
Nds.DeleteAll();
}

NLine* DBase::AddLNbyXYZ(double x1, double y1, double z1, double x2, double y2, double z2,int iCol)
{
	C3dVector v1;
	C3dVector v2;
	v1.Set(x1, y1, z1);
	v2.Set(x2, y2, z2);
	NLine* LnIn = new NLine();
	LnIn->Create(v1, v2, iCVLabCnt, NULL);
	LnIn->iColour = iCol;
	iCVLabCnt++;
	AddObj(LnIn);
	ReDraw();
	return (LnIn);
}

void DBase::AddDragLN(C3dVector v1)
{
	NLine* LnIn = new NLine();
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	LnIn->Create(v1, v1, -1, NULL);
	pDragObj = (NLine*)LnIn;
}

void DBase::AddDragDIMA(C3dVector v1, C3dVector v2)
{
	C3dVector vN, vDir, vO;
	vO.Set(0, 0, 0);
	vN.Set(0, 0, 1);
	vDir.Set(1, 0, 0);  //Text direction assume workplane X
	vO = WPtoGlobal2(vO);
	vN = WPtoGlobal2(vN);
	vDir = WPtoGlobal2(vDir);
	vN -= vO;
	vDir -= vO;

	DIM* pDIM = new DIMA(v1,v2,v2,vO,vN,vDir,gDIM_SIZE,-1);
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*) pDIM;
}

void DBase::AddDragDIMANG(C3dVector vVert, C3dVector v1, C3dVector v2)
{
	C3dVector vN, vDir, vO;
	vO.Set(0, 0, 0);
	vN.Set(0, 0, 1);
	vDir.Set(1, 0, 0);  //Text direction assume workplane X
	vO = WPtoGlobal2(vO);
	vN = WPtoGlobal2(vN);
	vDir = WPtoGlobal2(vDir);
	vN -= vO;
	vDir -= vO;

	DIM* pDIM = new DIMANG(vVert,v1, v2, v2, vO, vN, vDir, gDIM_SIZE, -1);
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*)pDIM;
}

void DBase::AddDragDIMH(C3dVector v1, C3dVector v2)
{
	C3dVector vN, vDir, vO;
	vO.Set(0, 0, 0);
	vN.Set(0, 0, 1);
	vDir.Set(1, 0, 0);  //Text direction assume workplane X
	vO = WPtoGlobal2(vO);
	vN = WPtoGlobal2(vN);
	vDir = WPtoGlobal2(vDir);
	vN -= vO;
	vDir -= vO;

	DIM* pDIM = new DIMH(v1, v2, v2, vO, vN, vDir, gDIM_SIZE, -1);
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*)pDIM;
}

void DBase::AddDragDIMV(C3dVector v1, C3dVector v2)
{
	C3dVector vN, vDir, vO;
	vO.Set(0, 0, 0);
	vN.Set(0, 0, 1);
	vDir.Set(1, 0, 0);  //Text direction assume workplane X
	vO = WPtoGlobal2(vO);
	vN = WPtoGlobal2(vN);
	vDir = WPtoGlobal2(vDir);
	vN -= vO;
	vDir -= vO;

	DIM* pDIM = new DIMV(v1, v2, v2, vO, vN, vDir, gDIM_SIZE, -1);
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*)pDIM;
}


void DBase::AddDragDIML(CString sText, C3dVector v1)
{
	C3dVector vN, vDir, vO;
	vO.Set(0, 0, 0);
	vN.Set(0, 0, 1);
	vDir.Set(1, 0, 0);  //Text direction assume workplane X
	vO = WPtoGlobal2(vO);
	vN = WPtoGlobal2(vN);
	vDir = WPtoGlobal2(vDir);
	vN -= vO;
	vDir -= vO;

	DIM* pDIM = new DIML(sText,v1, v1, v1, vO, vN, vDir, gDIM_SIZE, -1);
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*)pDIM;
}

void DBase::AddDragDIMR(NCircle* pC, C3dVector v1)
{
	C3dVector vN, vDir, vO;
	vO.Set(0, 0, 0);
	vN.Set(0, 0, 1);
	vDir.Set(1, 0, 0);  //Text direction assume workplane X
	vO = WPtoGlobal2(vO);
	vN = WPtoGlobal2(vN);
	vDir = WPtoGlobal2(vDir);
	vN -= vO;
	vDir -= vO;
	C3dVector vC;
	vC = pC->Get_Centroid();
	DIM* pDIM = new DIMR(pC->dRadius, vC, vC, vC, vO, vN, vDir, gDIM_SIZE, -1);
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*)pDIM;
}

void DBase::AddCirCL(NCircle* pC)
{
	int iC = 12;
	NLine* pCL = nullptr;
	C3dVector vDirX, vDirY, vO, vCent, p1X, p1Y, p2X, p2Y;
	double dR = 1;
	dR = pC->dRadius;
	vO.Set(0, 0, 0);  //Origin
	vDirX.Set(1, 0, 0);  //X Dir
	vDirY.Set(0, 1, 0);  //Y Dir
	vCent = pC->Get_Centroid();
	vO = WPtoGlobal2(vO);
	vDirX = WPtoGlobal2(vDirX);
	vDirY = WPtoGlobal2(vDirY);
	vDirX -= vO; 
	vDirY -= vO; 
	p1X = vDirX;
	p1Y = vDirY;
	//Centre of matker
	p1X *= 0.25 * dR;
	p1Y *= 0.25 * dR;
    //Add Circle Centre Lines
	pCL = new NLine();
	pCL->Create(vCent - p1X, vCent + p1X, -1, nullptr);
	pCL->iColour = iC;
	pCL->iLnThk = 2;
	AddObj(pCL);
	pCL = new NLine();
	pCL->Create(vCent - p1Y, vCent + p1Y, -1, nullptr);
	pCL->iColour = iC;
	pCL->iLnThk = 2;
	AddObj(pCL);

	//X 
	p1X = vDirX;
	p2X = vDirX;
	p1X *= 0.5 * dR;
	p2X *= 1.25 * dR;
	pCL = new NLine();
	pCL->Create(vCent - p1X, vCent - p2X, -1, nullptr);
	pCL->iColour = iC;
	pCL->iLnThk = 2;
	AddObj(pCL);
	pCL = new NLine();
	pCL->Create(vCent + p1X, vCent + p2X, -1, nullptr);
	pCL->iColour = iC;
	pCL->iLnThk = 2;
	AddObj(pCL);
	//Y
	p1Y = vDirY;
	p2Y = vDirY;
	p1Y *= 0.5 * dR;
	p2Y *= 1.25 * dR;
	pCL = new NLine();
	pCL->Create(vCent - p1Y, vCent - p2Y, -1, nullptr);
	pCL->iColour = iC;
	pCL->iLnThk = 2;
	AddObj(pCL);
	pCL = new NLine();
	pCL->Create(vCent + p1Y, vCent + p2Y, -1, nullptr);
	pCL->iColour = iC;
	pCL->iLnThk = 2;
	AddObj(pCL);

}

void DBase::AddDimForDrag(DIM* pD)
{
	Dsp_Rem(pD);
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*) pD;
	InvalidateOGL();
	ReDraw();
}

void DBase::AddDragDIMD(NCircle* pC, C3dVector v1)
{
	C3dVector vN, vDir, vO;
	vO.Set(0, 0, 0);
	vN.Set(0, 0, 1);
	vDir.Set(1, 0, 0);  //Text direction assume workplane X
	vO = WPtoGlobal2(vO);
	vN = WPtoGlobal2(vN);
	vDir = WPtoGlobal2(vDir);
	vN -= vO;
	vDir -= vO;
	C3dVector vC;
	vC = pC->Get_Centroid();
	DIM* pDIM = new DIMD(pC->dRadius, vC, vC, vC, vO, vN, vDir, gDIM_SIZE, -1);
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pDragObj = (DIM*)pDIM;
}


NLine* DBase::AddLNfromDrag(C3dVector v2)
{

	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	NLine* LnIn = nullptr;
	C3dMatrix mTran;
	C3dVector vn1, vn2;
	WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
	mTran = pWPlane->mWPTransform;
	if (pDragObj != nullptr)
	{
		pDragObj->DragUpdate(v2, mTran);
		NLine* pL = (NLine*)pDragObj;
		vn1 = pL->cPts[0]->Pt_Point;
		vn2 = pL->cPts[1]->Pt_Point;
		LnIn = new NLine();
		LnIn->Create(vn1, vn2, iCVLabCnt, NULL);
		iCVLabCnt++;
		AddObj(LnIn);
		ReDraw();
	}
	return (LnIn);
}

DIM* DBase::AddDIMfromDrag(C3dVector v3)
{
	DIM* pD = nullptr;
	C3dMatrix mTran;
	C3dVector vn1, vn2;
	WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
	mTran = pWPlane->mWPTransform;
	if (pDragObj != nullptr)
	{
		pDragObj->DragUpdate(v3, mTran);
		pD = (DIM*) pDragObj;
		pDragObj = nullptr;

		//iDIMLabCnt++;  NEW DIM COUNT
		AddObj(pD);
		ReDraw();
	}
	return (pD);
}




NLine* DBase::AddLN(C3dVector v1,C3dVector v2, int ilab,BOOL bRedraw)
{

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 

NLine* LnIn = new NLine();

LnIn->Create(v1, v2, iCVLabCnt, NULL);
iCVLabCnt++;
AddObj(LnIn);
if (bRedraw)
  ReDraw();
return (LnIn);
}




void DBase::AddRect(C3dVector v1,C3dVector v2, int ilab)
{

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat();
WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
C3dMatrix mSc,invMsc;     
mSc=pWPlane->mWPTransform;

invMsc=mSc.Inv();
v1=invMsc.Mult(v1);
v2=invMsc.Mult(v2);
C3dVector a,b;
a.Set(v1.x,v1.y,v1.z);
b.Set(v2.x,v1.y,v1.z);
a=mSc.MultBack(a);
b=mSc.MultBack(b);

NLine* LnIn = new NLine();
LnIn->Create(a,b,iCVLabCnt,NULL);
iCVLabCnt++;
AddObj(LnIn);
a.Set(v1.x,v2.y,v1.z);
b.Set(v2.x,v2.y,v1.z);
a=mSc.MultBack(a);
b=mSc.MultBack(b);
LnIn = new NLine();
LnIn->Create(a,b,iCVLabCnt,NULL);
iCVLabCnt++;
AddObj(LnIn);
a.Set(v1.x,v2.y,v1.z);
b.Set(v1.x,v1.y,v1.z);
a=mSc.MultBack(a);
b=mSc.MultBack(b);
LnIn = new NLine();
LnIn->Create(a,b,iCVLabCnt,NULL);
iCVLabCnt++;
AddObj(LnIn);
a.Set(v2.x,v2.y,v1.z);
b.Set(v2.x,v1.y,v1.z);
a=mSc.MultBack(a);
b=mSc.MultBack(b);
LnIn = new NLine();
LnIn->Create(a,b,iCVLabCnt,NULL);
iCVLabCnt++;
AddObj(LnIn);
ReDraw();

}



NSurf* DBase::AddPlainSurf(C3dVector vC,C3dVector vN,C3dVector vR, int ilab,BOOL bRedraw)
{

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
C3dVector v1,v2;
v1.Set(vC.x-10,vC.y-10,0);
v2.Set(vC.x-10,vC.y+10,0);
NLine* LnIn1 = new NLine();
LnIn1->Create(v1,v2,iCVLabCnt,NULL);
iSFLabCnt++;
v1.Set(vC.x+10,vC.y-10,0);
v2.Set(vC.x+10,vC.y+10,0);
NLine* LnIn2 = new NLine();
LnIn2->Create(v1,v2, iCVLabCnt,NULL);
iSFLabCnt++;
BOOL bErr;
NSurf* pS = new NSurf();
pS->Create(iSFLabCnt,NULL);
iSFLabCnt++;
pS->AddCV((NCurve*) LnIn1);
pS->AddCV((NCurve*) LnIn2);
bErr=pS->Generate(1,0,1);



if (bErr==FALSE)
{
  C3dMatrix RMat;
  RMat.MakeUnit();
  C3dVector vX;
  C3dVector vY;
  C3dVector vZ;
  vZ=vN;
  vX=vR;
  vZ.Normalize();
  vX.Normalize();
  vY=vZ.Cross(vX);
  RMat.SetColVec(1,vX);
  RMat.SetColVec(2,vY);
  RMat.SetColVec(3,vZ);
  C3dMatrix TMat;
  pS->Transform(RMat);
  TMat.Translate(vC.x,vC.y,vC.z);
  pS->Transform(TMat);
  AddObj(pS);
}
else
{
  delete(pS);
}
delete(LnIn1);
delete(LnIn2);
if (bRedraw)
  ReDraw();
return (pS);
}


NSurf* DBase::AddPlainSurf2(C3dMatrix TMat,double XMax,double YMax,double XMin,double YMin,BOOL bRedraw)
{

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
C3dVector v1,v2;
double dCX, dCY, dXSP, dYSP,dS;
dXSP = (XMax - XMin);
dYSP = (YMax - YMin);
dCX = XMin + 0.5*dXSP;
dCY = YMin + 0.5*dYSP;
if (dXSP > dYSP)
  dS = dXSP;
else
  dS = dYSP;
XMax = dCX + 0.5*dS;
XMin = dCX - 0.5*dS;
YMax = dCY + 0.5*dS;
YMin = dCY - 0.5*dS;
v1.Set(XMin-1,YMin-1,0);
v2.Set(XMax+1,YMin-1,0);
v1=TMat*v1;
v2=TMat*v2;
NLine* LnIn1 = new NLine();
LnIn1->Create(v1,v2,0,NULL);
v1.Set(XMin-1,YMax+1,0);
v2.Set(XMax+1,YMax+1,0);
v1=TMat*v1;
v2=TMat*v2;
NLine* LnIn2 = new NLine();
LnIn2->Create(v1,v2,0,NULL);

BOOL bErr;
NSurf* pS = new NSurf();
pS->Create(iSFLabCnt,NULL);
iSFLabCnt++;
pS->AddCV((NCurve*) LnIn1);
pS->AddCV((NCurve*) LnIn2);
bErr=pS->Generate(1,0,1);
if (bErr==FALSE)
{
  AddObj(pS);
}
else
{
  delete(pS);
  pS=NULL;
}
delete(LnIn1);
delete(LnIn2);
if (bRedraw)
  ReDraw();
return (pS);
}

void DBase::TestSYS()
{

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
C3dMatrix RMat;
C3dVector Org;
RMat.MakeUnit();
RMat.Rotate(0,0,45);



CoordSys* Sys = new CoordSys();
Sys->Create(Org,RMat,0,1,1,11,NULL);
DB_Obj[DB_ObjectCount]=Sys;
DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
Dsp_Add(Sys);

DB_ObjectCount++;
AddTempGraphics(Sys);
OglDraw(DspFlags);

}





Line_Object* DBase::AddLN2(double x1,double y1,double z1,double x2,double y2,double z2, int ilab)
{
CDC* pDC = pTheView->GetDC();
SetPen(pDC,3);
//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
C3dVector v1(x1,y1,z1);
C3dVector v2(x2,y2,z2);
Line_Object* LnIn = new Line_Object();
LnIn->Create(&v1,&v2,0,NULL);
DB_Obj[DB_ObjectCount]=LnIn;
DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
DB_Obj[DB_ObjectCount]->Draw(pDC,4);
Dsp_Add(LnIn);
Dsp_Add(LnIn->pVertex1);
Dsp_Add(LnIn->pVertex2);

DB_ObjectCount++;
RestorePen(pDC);
pTheView->ReleaseDC(pDC);
return(LnIn);
}



CString DBase::GetObjName(int index)
{
CString SRC;
SRC="INDEX OUT OF BOUNDS";
if (index<DB_ObjectCount)
{
  if (DB_Obj[index]->iObjType==500)
  {
    WG_Def* W = (WG_Def*) DB_Obj[index];
    SRC=W->Name;
  }
  else
  {
    SRC="PRIVATE OBJECT";
  }
}
return (SRC);
}

G_Object* DBase::GetObj(int iType,int iLab)
{
G_Object* pRet;
pRet = NULL;
int iCO;

for (iCO=0;iCO<DB_ObjectCount;iCO++)
{

  if ((DB_Obj[iCO]->iObjType == iType) && 
	  (DB_Obj[iCO]->iLabel == iLab))  
  {
     pRet =  DB_Obj[iCO];
	 pRet->pParent = NULL;
	 break;
  }
}

return (pRet);
}


G_Object* DBase::LabSel(int iType,int iLab1,int iLab2)
{
int i;
G_Object* pRet;
G_Object* pMsh;

int iNo=0;
if (iLab2<iLab1)
{
  iLab2=iLab1;
}
if (pCurrentPart != NULL)
{
	if ((iType == 0) || (iType == 7) || (iType == 8) ||
		(iType == 9) || (iType == 15) || (iType == 16) ||
		(iType == 17) || (iType == 19))
	{
		for (i = iLab1; i <= iLab2; i++)
		{
			pRet = pCurrentPart->GetObj(iType, i);
			if (pRet != NULL)
			{
				if (iNo < MAX_SIZE)
				{
					S_Buff[S_Count] = pRet;
					S_Count++;
				}
			}
		}
	}
}

if ((iType==1) || (iType==3) || (iType==12))
{
  pMsh = GetObj(4,pCurrentMesh->iLabel);
  for (i=iLab1;i<=iLab2;i++)
  {
    pRet = pMsh->GetObj(iType,i);
	if (pRet!=NULL)
	{
	  if (iNo< MAX_SIZE)
	  {
        S_Buff[S_Count]=pRet;
        S_Count++;
	  }
	}
  }
}
else
{
  for (i=iLab1;i<=iLab2;i++)
  {
    pRet = GetObj(iType,i);
	if (pRet!=NULL)
	{
		if (iNo< MAX_SIZE)
		{
			S_Buff[S_Count]=pRet;
			S_Count++;
		}
	}
  }
}
ReDraw();
return (pRet);
}



void DBase::TrimLn()
{
	CvPt_Object* mPt;
	double MinDist = 10000000;
	double dDist = 0;
	double dU, dTU;
	C3dVector vP;
	CDC* pDC = pTheView->GetDC();
	int iCnt1;

	// Check if the last two objects in S_Buff are both of type 2 (Line_Object)
	if ((S_Buff[S_Count - 1]->iObjType == 2) && (S_Buff[S_Count - 2]->iObjType == 2))
	{
		Line_Object* L2 = (Line_Object*)S_Buff[S_Count - 1];
		Line_Object* L1 = (Line_Object*)S_Buff[S_Count - 2];

		// Iterate through a range of values for parameter dU
		for (iCnt1 = 1; iCnt1 < 1000; iCnt1++)
		{
			dU = iCnt1 * 0.001;
			vP = L2->GetPt(dU);
			dDist = L1->MinDist(vP);

			// Update MinDist and dTU if a smaller distance is found
			if (dDist < MinDist)
			{
				MinDist = dDist;
				dTU = dU;
			}
		}

		// If the minimum distance is less than 0.1
		if (MinDist < 0.1)
		{
			// Set a thicker pen for drawing
			SetPen(pDC, 5);
			L2->SetToScr(&pModelMat, &pScrMat);
			L2->Draw(pDC, 4);
			RestorePen(pDC);

			// Move an endpoint of L2 to the calculated position
			mPt = L2->GetTEnd();
			vP = L2->GetPt(dTU);
			mPt->SetTo(vP);

			// Set a thinner pen for drawing
			SetPen(pDC, 3);
			L2->SetToScr(&pModelMat, &pScrMat);
			L2->Draw(pDC, 4);
			RestorePen(pDC);
		}

		MinDist = 10000000;
		L2 = (Line_Object*)S_Buff[S_Count - 2];
		L1 = (Line_Object*)S_Buff[S_Count - 1];

		// Iterate through a range of values for parameter dU again
		for (iCnt1 = 1; iCnt1 < 1000; iCnt1++)
		{
			dU = iCnt1 * 0.001;
			vP = L2->GetPt(dU);
			dDist = L1->MinDist(vP);

			// Update MinDist and dTU if a smaller distance is found
			if (dDist < MinDist)
			{
				MinDist = dDist;
				dTU = dU;
			}
		}

		// If the minimum distance is less than 0.1
		if (MinDist < 0.1)
		{
			// Set a thicker pen for drawing
			SetPen(pDC, 5);
			L2->SetToScr(&pModelMat, &pScrMat);
			L2->Draw(pDC, 4);
			RestorePen(pDC);

			// Move an endpoint of L2 to the calculated position
			mPt = L2->GetTEnd();
			vP = L2->GetPt(dTU);
			mPt->SetTo(vP);

			// Set a thinner pen for drawing
			SetPen(pDC, 3);
			L2->SetToScr(&pModelMat, &pScrMat);
			L2->Draw(pDC, 4);
			RestorePen(pDC);
		}
	}

	// Release the device context
	pTheView->ReleaseDC(pDC);
}




//Caluclate the aparent intersection of two lines in 3d
//lines defined as points
BOOL DBase::LnIntByPoints(C3dVector p11, C3dVector p12, C3dVector p21,
	               C3dVector p22, C3dVector& pInt)
{
	C3dVector v1, v2;
	NLine* Ln1;
	NLine* Ln2;
	v1 = p11; v1 -= p12; v1.Normalize();
	v2 = p21; v2 -= p22; v2.Normalize();
	//Check for parrellel lines
	if (abs(v1.Dot(v2)) > 1.0)
		return (FALSE);
	Ln1 = new NLine();
	Ln1->Create(p11, p12, -1, NULL);
	Ln2 = new NLine();
	Ln2->Create(p21, p22, -1, NULL);
	pInt = NLnInt(Ln1, Ln2, &v1);

	delete(Ln1);
	delete(Ln2);
	return (TRUE);
}

C3dVector DBase::LnInt(Line_Object* L1,G_Object* L2)
{
int i=0;
double MinDist = 10000000;
double dDist = 0;
double dDistB = 0;
double dM;
const double dTol = 0.0001;
C3dVector P1;
C3dVector P2;

P1.Set(L1->pVertex1->Pt_Point->x,
       L1->pVertex1->Pt_Point->y,
       L1->pVertex1->Pt_Point->z);
P2=L2->MinPt(P1);
P1=L1->MinPt(P2);
dDist=P2.Dist(P1);
do
{
  dDistB=dDist;
  P2=L2->MinPt(P1);
  P1=L1->MinPt(P2);
  dDist=P2.Dist(P1);
  dM=pow(dDistB-dDist*dDistB-dDist,0.5);
  i++;
}
while (dM>dTol);
return (P2);
}

C3dVector DBase::NLnInt(NCurve* L1,NCurve* L2, C3dVector* pNear)
{
int i=0;
double MinDist = 10000000;
double dDist = 0;
double dDistB = 0;
const double dTol = 0.00001;
C3dVector P1;
C3dVector P2;
int iMaxIt=0;
P1=L1->GetPt(0);

do
{
  P2=L2->MinPt(P1);
  P1=L1->MinPt(P2);
  dDist=P2.Dist(P1);
  iMaxIt++;
}
while ((dDist>dTol) && (iMaxIt<100));
return (P2);
}

//RBLows 23042023
//This version finds intersection near pNear
//this should probably superceed NLnInt above
//THIS VERSION FAILS TO BE ACCURATE WHEN CURVES ARW PARALE//

C3dVector DBase::NLnInt2(NCurve* L1, NCurve* L2, C3dVector* pNear)
{
	int i = 0;
	double MinDist = 10000000;
	double dDist = 0;
	double dDistB = 0;
	const double dTol = 0.0000001;
	C3dVector P1;
	C3dVector P2;
	P1.Set(pNear->x,pNear->y,pNear->z);
	P2.Set(pNear->x, pNear->y, pNear->z);
	int iMaxIt = 0;
	//P1 = L1->GetPt(0);

	do
	{
		P2 = L2->MinPt(P1);
		P1 = L1->MinPt(P2);
		dDist = P2.Dist(P1);
		iMaxIt++;
	} while ((dDist > dTol) && (iMaxIt<10000));
	char S1[200];
	CString OutT;
	sprintf_s(S1, "ITERATIONS: %i TOL: %f", iMaxIt, dDist);
	outtext1(S1);

	return (P1);
}

C3dVector DBase::NLnInt3(NCurve* L1, NCurve* L2, C3dVector* pNear)
{
	int i = 0;
	double MinDist = 10000000;
	double w;
	double dw=0.01;
	double dDist = 0;
	double dDistF = 0;
	double dDistB = 0;
	const double dTol = 0.0000001;
	C3dVector P1;
	C3dVector P2;
	BOOL isClosed = FALSE;
	P1.Set(pNear->x, pNear->y, pNear->z);
	P2.Set(pNear->x, pNear->y, pNear->z);
	int iMaxIt = 0;
	isClosed = L1->IsClosed();
	w = L1->MinWPt(P1);
	dDist = 1;
	
	do
	{
		P1 = L1->GetPt(w+dw);
		P2 = L2->MinPt(P1);
		dDistF = P2.Dist(P1);
		if (dDistF < dDist)
		{
			w = w + dw;
			dDist = dDistF;
			if (w > 1)
				w = 1;
		}
		else
		{
			double dAA;
			dAA = (w - dw);
			if (dAA < 0)
			  dAA = 0;
			P1 = L1->GetPt(dAA);
			P2 = L2->MinPt(P1);
			dDistB = P2.Dist(P1);
			if (dDistB < dDist)
			{
				w = w - dw;
				if (w < 0)
					w = 0;
				dDist = dDistB;
			}
			else
			{
				dw = 0.5 * dw;
			}
		}
		iMaxIt++;
	} while ((dDist > dTol) && (iMaxIt < 1000));
	char S1[200];
	CString OutT;
	sprintf_s(S1, "ITERATIONS: %i TOL: %g", iMaxIt, dDist);
	outtext1(S1);
	return (P1);
}


BOOL DBase::IsIntersection(C3dVector C1S, C3dVector C1E, C3dVector C2S, C3dVector C2E)
{
	C3dVector vD1,v1,v2,vN1, vN2;
	double dd1, dd2;
	//Test 1
	vD1 = C1E - C1S;
	v1 = C2S - C1S;
	v2 = C2E - C1S;
	vD1.Normalize(); v1.Normalize(); v2.Normalize();
	vN1 = vD1.Cross(v1);
	vN2 = vD1.Cross(v2);
	dd1 = vN1.Dot(vN2);
	//Test 2
	vD1 = C2E - C2S;
	v1 = C1S - C2S;
	v2 = C1E - C2S;
	vD1.Normalize(); v1.Normalize(); v2.Normalize();
	vN1 = vD1.Cross(v1);
	vN2 = vD1.Cross(v2);
	dd2 = vN1.Dot(vN2);

	if ((dd1<=0.0) && (dd2<=0.0))
	  return TRUE;
	else
	  return FALSE;
}


//Find possible approximate multiple intersection between two curves
//First draft of proc
int DBase::TentativeInt(NCurve* C1, NCurve* C2, C3dVector vInts[10],double uInts[10])
{
	int iDiv = 100;
	int i;
	int j;
	int iRet = 0;
	double dU1=0;
	double dU2 = 0;
	BOOL bErr;
	C3dVector vInt;
	C3dVector vP1,vP2, vP3, vP4, PC3,vN,vD1,vD2,vt1,vt2;

	for (i = 0; i <= iDiv-1; i++)
	{
		dU1 = i*0.01;
		vP1 = C1->GetPt(i * 0.01);
		vP2 = C1->GetPt((i + 1) * 0.01);
		for (j = 0; j <= iDiv; j++)
		{
			vP3 = C2->GetPt(j * 0.01);
			vP4 = C2->GetPt((j + 1) * 0.01);
			bErr = IsIntersection(vP1, vP2, vP3, vP4);
			if (bErr)
			{
				//C3dVector vRet = NLnInt2(C1, C2, &vP1);
				if (iRet < 10)
				{
					vInts[iRet] = vP1;
					uInts[iRet] = i * 0.01;
					iRet++;
				}
				//AddPt(vRet, -1, TRUE);
			}
			  //outtext1("Inter");
		}
	}

	return (iRet);
}



//find span u lies between
int DBase::FindNearest(int iNo,double uInts[10], double u)
{
	int iRC = -1;
	int i;
	if (iNo == 1)
	{
		iRC = 0;
	}
	else
	{
		//if (u < uInts[0])
		//	iRC = 0;
		//else if (u > uInts[iNo - 1])
		//	iRC = iNo - 1;
		//else
		{
			double ddist = 0;
			ddist = abs(u - uInts[0]);
			iRC = 0;
			for (i = 0; i < iNo; i++)
			{
				if (abs(u - uInts[i]) < ddist)
				{
					ddist = abs(u - uInts[i]);
					iRC = i;
				}
				//if ((u >= uInts[i]) && (u < uInts[i + 1]))
				//{

				//}
			}
		}
	}
	return (iRC);
}

C3dVector DBase::LnInt2(Line_Object* L1,G_Object* L2)
{
int i=0;
double MinDist = 10000000;
double dDist = 0;
double dDistB = 0;
double dM;
const double dTol = 0.0001;
C3dVector P1;
C3dVector P2;

P1.Set(L1->pVertex2->Pt_Point->x,
       L1->pVertex2->Pt_Point->y,
       L1->pVertex2->Pt_Point->z);
P2=L2->MinPt(P1);
P1=L1->MinPt(P2);
dDist=P2.Dist(P1);
do
{
  dDistB=dDist;
  P2=L2->MinPt(P1);
  P1=L1->MinPt(P2);
  dDist=P2.Dist(P1);
  dM=pow(dDistB-dDist*dDistB-dDist,0.5);
  i++;
}
while (dM>dTol);
return (P2);
}

NCircle* DBase::AddCirCR(C3dVector vNorm, C3dVector vCent, double dR, int ilab)
{
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	C3dVector vRDir, vX;
	C3dMatrix mTran;
	WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
	mTran = pWPlane->mWPTransform;
	vX.Set(mTran.m_00, mTran.m_10, mTran.m_20);

	NCircle* cCir = new NCircle();
	cCir->Create2(vNorm, vCent, vX, dR, iCVLabCnt, NULL);
	iCVLabCnt++;
	AddObj(cCir);
	ReDraw();
	return cCir;
}

void DBase::AddDragCIR(C3dVector vN,C3dVector v1)
{
	NCircle* pCir = new NCircle();
	//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
	if (pDragObj != nullptr)
		delete(pDragObj);
	pCir->Create(vN, v1, 0, -1,NULL);
	pDragObj = (NCircle*) pCir;
}

int calculateTangents(double Cx, double Cy, double r, double Px, double Py, C3dVector &t1, C3dVector &t2)
{
	int irc=0;
	double dx = Px - Cx;
	double dy = Py - Cy;
	double dxr = -dy;
	double dyr = dx;
	double d = std::sqrt(dx * dx + dy * dy);

	if (d >= r) {
		double rho = r / d;
		double ad = rho * rho;
		double bd = rho * std::sqrt(1 - rho * rho);
		double T1x = Cx + ad * dx + bd * dxr;
		double T1y = Cy + ad * dy + bd * dyr;
		double T2x = Cx + ad * dx - bd * dxr;
		double T2y = Cy + ad * dy - bd * dyr;
		t1.Set(T1x, T1y, 0);
		t2.Set(T2x, T2y, 0);
		irc = 1; //ok
	}

	return (irc);
}

//Create a line from a point tangent to a circle
NLine* DBase::AddCirTanPt(C3dVector vNorm, C3dVector vPt, CPoint PNear1)
{
	//https://math.stackexchange.com/questions/543496/how-to-find-the-equation-of-a-line-tangent-to-a-circle-that-passes-through-a-g

	int iErr;
	C3dVector vC;
	NCircle* pC;
	C3dVector pN1;
	C3dVector t1;
	C3dVector t2;
	C3dVector vD;
	double d1, d2;

	pN1 = PickPointToGlobal(PNear1);
	pN1 = GlobaltoWP(pN1);
	if (S_Count > 0)
	{
		// Check to see is item is circle
		if ((S_Buff[S_Count - 1]->iObjType == 7) &&
			(S_Buff[S_Count - 1]->iType == 3))
		{
			pC = (NCircle*) S_Buff[S_Count - 1];
			S_Des();
			double Cx, Cy;
			vC = pC->vCent;
			vC = GlobaltoWP(vC);
			Cx = vC.x;
			Cy = vC.y;
			double r = 5;
			r = pC->dRadius;
			double Px , Py;
			vPt = GlobaltoWP(vPt);
			Px = vPt.x;
			Py = vPt.y;
			iErr = calculateTangents(Cx, Cy, r, Px, Py, t1, t2);
			if (iErr == 1)
			{
				vD = pN1 - t1;
				d1 = vD.Mag();
				vD = pN1 - t2;
				d2 = vD.Mag();
				vPt = WPtoGlobal(vPt);
				if (d1 < d2)
				{
					t1 = WPtoGlobal(t1);
					AddLN(vPt, t1, -1, TRUE);
				}
				else
				{
					t2 = WPtoGlobal(t2);
					AddLN(vPt, t2, -1, TRUE);
				}
			}
			else
			{
				outtext1("ERROR: Calculating tangents.");
			}
		}
		else
		{
			outtext1("ERROR: No Circle Selected.");
		}
	}

	return(nullptr);
}

int CalcTan2Circles(C3dVector vC1, double dR1, C3dVector vNr1,
	                C3dVector vC2, double dR2, C3dVector vNr2,
	                C3dVector& t1, C3dVector& t2)
{
	//https://math.stackexchange.com/questions/719758/inner-tangent-between-two-circles-formula#:~:text=Treating%20the%20bigger%20circle%20as,us%20calculate%20the%20two%20outer
	int irc = 0;
	double dDot;
	double dT;
	double dR3;
	double dPhi;
	C3dMatrix mT;
	C3dVector vCC;
	C3dVector vTT;
	double dDist;
	C3dVector vP1, vP2;
	//Error circles are concentric
	if (vC1 == vC2)
	{
		return (1);
	}
	vP1 = vNr1 - vC1;
	vP1.Normalize();
	vP2 = vNr2 - vC2;
	vP2.Normalize();
	dDot = vP1.Dot(vP2);
	if (dDot > 0)
	{
		outtext1("INFO: External Tangent.");
		if (dR1 > dR2)
		{
			dR3 = dR1 - dR2;
			vTT = vC2 - vC1;
		}
		else
		{
			dR3 = dR2 - dR1;
			vTT = vC1 - vC2;
		}
		
		dDist = vTT.Mag();
		vTT.Normalize();
		vCC = vTT;
		dPhi = std::acos(dR3 / dDist);
		mT.MakeUnit();
		mT.Rotate(0, 0, dPhi*R2D);
		vTT = mT*vTT; 
		vTT.Normalize();
		if (vTT.Dot(vP1) < 0) //change offset dir
		{
			mT.MakeUnit();
			mT.Rotate(0, 0, -dPhi * R2D);
			vTT = vCC;
			vTT = mT * vTT;
			vTT.Normalize();
		}
		t1 = vTT; t1 *= dR1; dT = t1.Mag(); t1 += vC1;
		vTT.Normalize();
		t2 = vTT; t2 *= dR2; dT = t2.Mag(); t2 += vC2;
	}
	else
	{
		outtext1("INFO: Internal Tangent.");
        dR3 = dR1 + dR2;
		vTT = vC2 - vC1;
		dDist = vTT.Mag();
		if (dDist <= dR1 + dR2)
			return (2);
		vTT.Normalize();
		vCC = vTT;
		//Case 1
		dPhi = std::asin(dR3 / dDist) - Pi/2;
		mT.MakeUnit();
		mT.Rotate(0, 0, dPhi * R2D);
		vTT = mT * vCC;
		vTT.Normalize();
		if (vTT.Dot(vP1) < 0) //change offset dir
		{
			mT.MakeUnit();
			mT.Rotate(0, 0, -dPhi * R2D);
			vTT = mT * vCC;
			t1 = vTT; t1 *= dR1; dT = t1.Mag(); t1 += vC1;
			mT.Rotate(0, 0, -180);
			vTT = mT * vCC;
			t2 = vTT; t2 *= dR2; dT = t2.Mag(); t2 += vC2;
		}
		else
		{
			t1 = vTT; t1 *= dR1; dT = t1.Mag(); t1 += vC1;
			mT.Rotate(0, 0, -180);
			vTT = mT * vCC;
			t2 = vTT; t2 *= dR2; dT = t2.Mag(); t2 += vC2;
		}
	}

	return (irc);
}

NLine* DBase::AddLinTan2Cir(CPoint PNear1, CPoint PNear2)
{
	int iErr = 0;
	C3dVector vNr1, vNr2;
	C3dVector vC1, vC2;
	C3dVector vt1, vt2;
	double dR1, dR2;
	NCircle* pC1 = nullptr;
	NCircle* pC2 = nullptr;
	//Pick near points in WP coords
	vNr1 = PickPointToGlobal(PNear1);
	vNr1 = GlobaltoWP(vNr1);
	vNr2 = PickPointToGlobal(PNear2);
	vNr2 = GlobaltoWP(vNr2);

	if (S_Count > 1) //We have two objects is buffer
	{
		// Check to see is item is circle
		if ((S_Buff[S_Count - 2]->iObjType == 7) &&
			(S_Buff[S_Count - 2]->iType == 3) &&
			(S_Buff[S_Count - 1]->iObjType == 7) &&
			(S_Buff[S_Count - 1]->iType == 3))
		{
			pC1 = (NCircle*)S_Buff[S_Count - 2];
			pC2 = (NCircle*)S_Buff[S_Count - 1];
			//All circle centres to workplaing
			vC1 = pC1->vCent;
			vC1 = GlobaltoWP(vC1);
			dR1 = pC1->dRadius;
			vC2 = pC2->vCent;
			vC2 = GlobaltoWP(vC2);
			dR2 = pC2->dRadius;
			iErr = CalcTan2Circles(vC1, dR1, vNr1,
				                   vC2, dR2, vNr2,
				                   vt1, vt2);
			if (iErr == 1)
			{
				outtext1("ERROR: Circles are Concentric.");
			}
			else if (iErr == 2)
			{
				outtext1("ERROR: Circles Must be Distinct for Internal Tangent.");
			}
			else
			{
				vt1 = WPtoGlobal(vt1);
				vt2 = WPtoGlobal(vt2);
				AddLN(vt1, vt2, -1, TRUE);
			}
		}
		else
		{
			outtext1("ERROR: No Circles Selected.");
		}
	}
	S_Des();
	return (nullptr);
}

NCircle* DBase::AddCirCentPt(C3dVector vNorm,C3dVector vCent,C3dVector vR)
{

C3dVector vRDir,vX;
C3dMatrix mTran;
vR-=vCent;

double dR = vR.Mag();
WP_Object* pWPlane = (WP_Object*)DB_Obj[iWP];
mTran = pWPlane->mWPTransform;
vX.Set(mTran.m_00, mTran.m_10, mTran.m_20);
NCircle* cCir = new NCircle();

cCir->Create2(vNorm,vCent, vX,vR.Mag(),iCVLabCnt,NULL);
iCVLabCnt++;
AddObj(cCir);
ReDraw();
return (cCir);
}


C3dVector DBase::PickPointToGlobal(CPoint Pt)
{

WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
C3dVector p1,p2,p3;
C3dMatrix mSc,mScInv;
p1.Set((double) Pt.x,(double) Pt.y,0.0);
p1.x=((p1.x-pScrInvMat.m_30)*pScrInvMat.m_00);
p1.y=-((p1.y-pScrInvMat.m_31)*pScrInvMat.m_00);      
mSc=pModelMat;
mSc=mSc.Inv();
p2=mSc.MultBack(p1);
p3=pModelMat*p2;
mSc=pWPlane->mWPTransform;
mScInv=mSc.Inv();
p2=mScInv.MultBack(p2);
p2.z=0;
p2=mSc.Mult(p2);

return (p2);
}

//***************************************************************************
//Gets a point picked on the work plane 
//Noye as the Z ordinate is lost some
//work hass to be done to get it back
//***************************************************************************
C3dVector DBase::PickPointToGlobal2(CPoint Pt)
{
	//REALLY DONT LIKE THIS CODE 
	// USE BI-LIN INTERPOLATION FOR BETTER SOLUTION
	//JUST GLAD IT WORKS FOR NOW 09/04/2020
	WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
	C3dVector P0, PX, PY;
	C3dVector D0, DX, DY;
	C3dVector VPT,VDO, VDX, VDY;
	double LWP;
	double DOTX,DOTY;
	double LDX, LDY;
	double FDX, FDY;
	C3dVector V;
	C3dVector R;
	C3dVector M;
	VPT.x = Pt.x; VPT.y = Pt.y; VPT.z = 0;
	P0= pWPlane->Pt_Point[0];


	D0 = pWPlane->DSP_Point[0];
	PX = pWPlane->Pt_Point[1];

	DX = pWPlane->DSP_Point[1];
	PY = pWPlane->Pt_Point[3];
	DY = pWPlane->DSP_Point[3];
	LWP = (PX - P0).Mag();
	VDO = VPT - D0;
	VDX = DX - D0; VDX.z = 0;
	VDY = DY - D0; VDY.z = 0;
	LDX = VDX.Mag();
	LDY = VDY.Mag();
	VDX.Normalize();
	VDY.Normalize();
	DOTX = VDO.Dot(VDX);
	DOTY = VDO.Dot(VDY);
	FDX = DOTX / LDX * LWP + P0.x;
	FDY = DOTY / LDY * LWP + P0.y;
	P0.Set(FDX, FDY, 0);

	//Error Check
	double dErr;
	int iErrCnt = 0;
	C3dMatrix WPM = pWPlane->mWPTransform;
	C3dMatrix AA;
	AA = pModelMat;
	do
	{
		P0 = this->WPtoGlobal2(P0); //was WPtoGlobal1
		M = P0;
		V.x = AA.m_00 * M.x + AA.m_01 * M.y + AA.m_02 * M.z + AA.m_30;
		V.y = AA.m_10 * M.x + AA.m_11 * M.y + AA.m_12 * M.z + AA.m_31;
		V.z = AA.m_20 * M.x + AA.m_21 * M.y + AA.m_22 * M.z + AA.m_32;
		R.x = pScrMat.m_00 * V.x + pScrMat.m_01 * V.y + pScrMat.m_02 * V.z + pScrMat.m_30;
		R.y = pScrMat.m_10 * V.x + pScrMat.m_11 * V.y + pScrMat.m_12 * V.z + pScrMat.m_31;
		R.z = pScrMat.m_20 * V.x + pScrMat.m_21 * V.y + pScrMat.m_22 * V.z + pScrMat.m_32;
		R.z = 0;
		VDO = VPT - R; //Vector error
		dErr = VDO.Mag();
		DOTX = VDO.Dot(VDX);
		DOTY = VDO.Dot(VDY);
		FDX = DOTX / LDX * LWP;
		FDY = DOTY / LDY * LWP;
		P0 = this->GlobaltoWP(P0);
		P0.x += FDX;
		P0.y += FDY;
		P0.z = 0;
		iErrCnt++;
	} 
	while ((dErr > 5) && (iErrCnt<100));
	  P0 = this->WPtoGlobal(P0);
	//sprintf_s(s1, "Error %g cnt %i", dErr, iErrCnt);
	//outtext1(s1);
	return (P0);
}

G_Object* DBase::AddRHDCyl(C3dVector vNorm,C3dVector vCent,C3dVector vRef,double dR,int ilab,BOOL bRedraw)
{

//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
NCircle* cCir = new NCircle();
cCir->Create2(vNorm,vCent,vRef,dR,iCVLabCnt,NULL);
iCVLabCnt++;
vNorm*=-0.1;
cCir->Translate(vNorm);
AddObj(cCir);
NSurfE* pS = new NSurfE();
NCurve* pC2=(NCurve*) cCir->Copy(pS);
pC2->iLabel = iCVLabCnt;
iCVLabCnt++;
vNorm*=-2;
pC2->Translate(vNorm);
pS->Create((NCurve*) cCir,pC2,vNorm, iSFLabCnt,NULL);
iSFLabCnt++;
BOOL bErr;
bErr=pS->Generate(1,0,1);
AddObj(pS);   
if (bRedraw)
  ReDraw();
return(pS);
}


void DBase::AddCurveFit(int p)
{
int iCnt;
C3dVector(pT);
//C3dMatrix cTransformMat = DB_pGrpWnd->Get3DMat(); 
if (DB_NoInBuff() > 2)
{
  Vec<C4dVector> P;
  Vec<double> U;
  NCurve* cPolyW = new NCurve();
  cPolyW->Create(iCVLabCnt,NULL);
  iCVLabCnt++;
  for (iCnt = 0; iCnt < DB_NoInBuff(); iCnt++)
  {
	  pT = DB_GetBuffbyInd(iCnt);
	  cPolyW->AddVert(pT, 1);
  }
  cPolyW->globalInterp(p,P,U);
  cPolyW->GenerateExp(p,P,U); 
  DB_Obj[DB_ObjectCount]=cPolyW;
  DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
  Dsp_Add(cPolyW); 
  DB_ObjectCount++;
  AddTempGraphics(cPolyW);
  ReDraw();
  P.DeleteAll();
  U.DeleteAll();
}
else
{
	outtext1("ERROR: Insufficient Point.");
}
}

void DBase::AddCoordSys(C3dVector p1,C3dVector p2,C3dVector p3,int Lab,int Typ,int iRID)
{
C3dVector vO;
C3dVector vX;
C3dVector vY;
C3dVector vZ;
C3dMatrix rMat;
vO=p1;
vX=p2-vO;
vX.Normalize();
vY=p3-vO;
vY.Normalize();
vZ=vX.Cross(vY);
vY = vZ.Cross(vX);
vY.Normalize();
rMat.MakeUnit();
rMat.m_00 = vX.x;
rMat.m_10 = vX.y;
rMat.m_20 = vX.z;
rMat.m_01 = vY.x;
rMat.m_11 = vY.y;
rMat.m_21 = vY.z;
rMat.m_02 = vZ.x;
rMat.m_12 = vZ.y;
rMat.m_22 = vZ.z;
if (Typ==0) Typ=1;
CoordSys* pRet = pCurrentMesh->AddSys(vO,rMat,iRID,Typ,Lab,55);
Dsp_Add(pRet); 
AddTempGraphics(pRet);
ReDraw();
}

void DBase::AddContPolyW(double dWght, double deg)
{
	int iCnt;
	C3dVector pT;
	if (DB_NoInBuff() >2)
	{
		NCurve* cPolyW = new NCurve();
		cPolyW->Create(iCVLabCnt,NULL);
		iCVLabCnt++;
		for (iCnt=0;iCnt< DB_NoInBuff();iCnt++)
		{
			pT = DB_GetBuffbyInd(iCnt);
			cPolyW->AddVert(pT,dWght);
		}
		cPolyW->Generate(deg);
		C3dVector a = cPolyW->GetPt(0.5);
		DB_Obj[DB_ObjectCount]=cPolyW;
		DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
		Dsp_Add(cPolyW); 
		DB_ObjectCount++;
		AddTempGraphics(cPolyW);
		ReDraw();
	}
	else
	{
		outtext1("ERROR: Insufficient Point.");
	}
}

void DBase::AddSurfR(C3dVector vB, C3dVector vD,double dAng)
{

BOOL bErr;
C3dVector vN(0,1,0);
C3dVector vC(0,0,0);
C3dMatrix mG;
WP_Object* TWP = (WP_Object*) DB_Obj[0];
mG = TWP->mWPTransform;
NSurfR* pS;
double we;
we=dAng/360;
if (we>1){we=1;}
if (we<0){we=0;}

int i;
NCurve* pC = NULL;

vN = vD - vB;
vN.Normalize();
vC = vB;
  for (i=0;i<S_Count;i++)
  {
    if (S_Buff[i]->iObjType == 7) 
    {
	  pS = new NSurfR();
      pS->Create((NCurve*) S_Buff[i],vN,vC,-1,NULL,0);
      bErr=pS->Generate(2,0,we);
      if (bErr==TRUE)
      {
        delete(pS);
        outtext1("ERROR: Cannot Build Surface.");
        outtext1("Check Order and Number Off Points.");
      }
      else
      {
        DB_Obj[DB_ObjectCount]=pS;
        DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
        Dsp_Add(pS);
        pS->iLabel=iSFLabCnt;
        iSFLabCnt++;
        DB_ObjectCount++;
        AddTempGraphics(pS);
      }
    }
  }
  ReDraw();

}



void DBase::AddSurfE(C3dVector vTr)
{

BOOL bErr;
C3dVector vN;
C3dVector vC;

NSurfE* pS;
NCurve* pC2;

int i;
if (vTr.Mag()!=0)
{
for (i=0;i<S_Count;i++)
{
  if (S_Buff[i]->iObjType == 7)
  {
	pS = new NSurfE();
	pC2=(NCurve*) S_Buff[i]->Copy(pS);
	MoveObj(pC2,vTr);
    pS->Create((NCurve*) S_Buff[i],(NCurve*) pC2,vTr,-1,NULL);
    
    bErr=pS->Generate(1,0,1);
    if (bErr==TRUE)
    {
      delete(pS);
      outtext1("ERROR: Cannot Build Surface.");
      outtext1("Check Order and Number Off Points.");
    }
    else
    {
      DB_Obj[DB_ObjectCount]=pS;
      DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
      Dsp_Add(pS);
      pS->iLabel=iSFLabCnt;
      iSFLabCnt++;
      DB_ObjectCount++;
      AddTempGraphics(pS);
    }
  }
}
}
else
{
  outtext1("ERROR: Zero Length Vector.");
}
ReDraw();
}


//**************************************************************
//Pre: List of curves
//Post: TRUE if curve loop in 2D is clockwise
// This relise on find two curves which must for the convex hull
// for the cross product to work
//**************************************************************
BOOL DBase::isClockWise(ObjList* Curves)
{
	CONST int MAX_VERTS = 500;
	bool brc=FALSE;
	C3dVector vPt;
	C2dVector vVerts[MAX_VERTS];
	NCurveOnSurf* c1;
	int iNo = 0;
	int i;

	if (Curves->iNo > 2)
	{
		c1 = (NCurveOnSurf*)Curves->Objs[0];
		vVerts[iNo].x = c1->cPts[0]->Pt_Point->x;
		vVerts[iNo].y = c1->cPts[0]->Pt_Point->y;
		iNo++;
		for (i = 0; i < Curves->iNo; i++)
		{
			c1 = (NCurveOnSurf*)Curves->Objs[i];
			if (iNo < MAX_VERTS)
			{
				vVerts[iNo].x = c1->cPts[c1->iNoCPts - 1]->Pt_Point->x;
				vVerts[iNo].y = c1->cPts[c1->iNoCPts - 1]->Pt_Point->y;
				iNo++;
			}
			else
			{
				break;
			}
		}
		
		//p1 = c1->cPts[c1->iNoCPts - 1]->Pt_Point;
	}
	else
	{
		c1 = (NCurveOnSurf*)Curves->Objs[0];
		vPt = c1->GetParaPt(c1->ws);
	    vVerts[iNo].x = vPt.x;
		vVerts[iNo].y = vPt.y;
		iNo++;
		vPt = c1->GetParaPt((c1->ws+c1->we)*0.33);
		vVerts[iNo].x = vPt.x;
		vVerts[iNo].y = vPt.y;
		iNo++;
		vPt = c1->GetParaPt((c1->ws + c1->we)*0.66);
		vVerts[iNo].x = vPt.x;
		vVerts[iNo].y = vPt.y;
		iNo++;
	}
	
	double area = 0;
	int j;
	for (i=0;i<iNo;i++) 
	{
		j = (i + 1) % iNo;
		area += vVerts[i].x * vVerts[j].y;
		area -= vVerts[j].x * vVerts[i].y;
	}

	//for (i = 0; i < iNo; i++)
	//{

	//	sprintf_s(s1, "%s %g %s %g ", "U:", vVerts[i].x, "V:", vVerts[i].y);
	//	outtext1(s1);
	//}
	//sprintf_s(s1, "Area %g", area);
	//outtext1(s1);
	//outtext1("*************");
	if (area > 0)
		brc = TRUE;
	else
		brc = FALSE;
	return(brc);
}

//**************************************************************
//Pre: List of curves
//Post: List of curves sorted into loop else bool=TRUE
//**************************************************************
BOOL DBase::ChainNormal(ObjList* Curves,C3dVector &vN)
{
int i;

BOOL bErr=TRUE;
C3dVector p1;
C3dVector p2;
C3dVector p0;
C3dVector v1;
C3dVector v2;

NCurve* c1;
c1=(NCurve*)  Curves->Objs[0];
p0=c1->cPts[0]->Pt_Point;
double ddot;
double dMin;
dMin=1;
if (Curves->iNo>1)
{
  p1=c1->cPts[c1->iNoCPts-1]->Pt_Point;
  v1=p1-p0;
  v1.Normalize();
  //for (i=1;i<Curves->iNo;i++)
  i=1;
  {
    c1=(NCurve*)  Curves->Objs[i];
	p1=c1->cPts[0]->Pt_Point;
    p2=c1->cPts[c1->iNoCPts-1]->Pt_Point;
    v2=p2-p1;
    v2.Normalize();
    ddot=v1.Dot(v2);
    //if (abs(ddot) < dMin)
    //{
      vN=v1.Cross(v2);
      vN.Normalize();
      bErr=FALSE;
	  dMin=abs(ddot);
    //  break;
    //}
  }
}
else
{
    p1=c1->GetPt(0.25);
    p2=c1->GetPt(0.5);
    v1=p1-p0;
    v2=p2-p0;
    vN=v1.Cross(v2);
}
return (bErr);
}

//**************************************************************
//Pre: List of curves
//Post: List of curves sorted into loop else bool=TRUE
//**************************************************************
BOOL DBase::ChainNormal2(NSurf* pS,ObjList* Curves,C3dVector &vN)
{
int i;

BOOL bRev=FALSE;
C3dVector p1;
C3dVector p2;
C3dVector p0;


double dTol=0.1;
C3dVector v1;
C3dVector v2;
C3dVector vSN;
NCurveOnSurf* c1;
double ddot;
double dMin;
dMin=1;
if (Curves->iNo>1)
{
  for (i=0;i<Curves->iNo-2;i++)
  {
    c1=(NCurveOnSurf*)  Curves->Objs[i];
	  p0=c1->GetParaPt(1);
    vSN=pS->Get_Normal(p0.x,p0.y);
	  vSN.Normalize();
    p1=c1->GetParaPt(1-dTol);
    c1=(NCurveOnSurf*)  Curves->Objs[i+1];
    p2=c1->GetParaPt(dTol);
    p0=pS->GetPt(p0.x,p0.y);
    p1=pS->GetPt(p1.x,p1.y);
    p2=pS->GetPt(p2.x,p2.y);
    v1=p1-p0;
	  v2=p2-p0;
	  v1.Normalize();
	  v2.Normalize();
    vN=v1.Cross(v2);
	  vN.Normalize();
    ddot=vSN.Dot(vN);
    if (ddot > 0.5)
      {
      bRev=TRUE;
      }
  }
}
return (bRev);
}

BOOL DBase::ChainRef(ObjList* Curves,C3dVector &vR,C3dVector &vC)
{

BOOL bErr=FALSE;
C3dVector p1;
C3dVector p2;
C3dVector p0;

NCurve* c1;
c1=(NCurve*)  Curves->Objs[0];
if (Curves->iNo>1)
{
  p0=c1->cPts[0]->Pt_Point;
  p1=c1->cPts[c1->iNoCPts-1]->Pt_Point;
}
else
{
  p0=c1->cPts[0]->Pt_Point;
  p1=c1->GetPt(0.5);
}
vR=p0-p1;
vC=p0;
vR.Normalize();
return (bErr);
}


BOOL DBase::Extents(ObjList* Curves,C3dMatrix TMat,C3dVector vO
                       ,double &dXMax,double &dYMax
                       ,double &dXMin,double &dYMin)
{

BOOL bErr=FALSE;
C3dVector p1;

int i;
int j;
NCurve* c1;

c1=(NCurve*)  Curves->Objs[0];
p1=c1->cPts[0]->GetCoords();
p1-=vO;
p1=TMat*p1;
dXMax=p1.x;
dYMax=p1.y;
dXMin=p1.x;
dYMin=p1.y;
for (i=0;i<Curves->iNo;i++)
{
   c1=(NCurve*)  Curves->Objs[i];
   for (j=0;j<c1->iNoCPts;j++)
   {
     p1=c1->cPts[j]->GetCoords();
     p1-=vO;
     p1=TMat*p1;
     if (p1.x>dXMax)
     {
       dXMax=p1.x;
     }
     if (p1.y>dYMax)
     {
       dYMax=p1.y;
     }
     if (p1.x<dXMin)
     {
       dXMin=p1.x;
     }
     if (p1.y<dYMin)
     {
       dYMin=p1.y;
     }
   }
}

return (bErr);
}


//**************************************************************
//Pre: List of curves
//Post: List of curves sorted into loop else bool=TRUE
//**************************************************************
BOOL DBase::ChainReverse(ObjList* Curves)
{
int j;
ObjList* tmp = new(ObjList);
NCurve* pC;
tmp->Clear();
for (j=0;j<Curves->iNo;j++)
{
  tmp->Objs[j]=Curves->Objs[Curves->iNo-j-1];
  pC=(NCurve*) tmp->Objs[j];
  pC->Reverse();
}
for (j=0;j<Curves->iNo;j++)
{
  Curves->Objs[j]=tmp->Objs[j];
}
delete(tmp);
return(TRUE);
}

//**************************************************************
//Pre: List of curves
//Post: List of curves sorted into loop else bool=TRUE
//**************************************************************
BOOL DBase::ChainCurves(ObjList* Curves)
{
int i;
int j;
int ind;
C3dVector v1;
C3dVector v2;
double dist;
double MinDist;
NCurve* c1;
NCurve* c2;
NCurve* cCand=NULL;
BOOL bRev=TRUE;
BOOL bErr = FALSE;
ObjList* tmp = new(ObjList);
tmp->Clear();
if (Curves->iNo==0)
{
  bErr = TRUE;
  delete(tmp);
  return(bErr);
}
else if (Curves->iNo==1)
{

}
else
{
  tmp->Add(Curves->Objs[0]);  //start with first curve
  Curves->Objs[0]=NULL;
  for (j=1;j<Curves->iNo;j++)
  {
  c1=(NCurve*)  tmp->Objs[j-1];
  v1=c1->cPts[c1->iNoCPts-1]->Pt_Point;
  MinDist=1e36;
  cCand=NULL;
  for (i=1;i<Curves->iNo;i++)
  {
    if (Curves->Objs[i]!=NULL)
    {     
       c2=(NCurve*)  Curves->Objs[i];
       v2=c2->cPts[0]->Pt_Point;
       v2=v2-v1;
       dist=v2.Mag();
       if (dist<MinDist)
       {
          MinDist=dist;
          cCand=c2;
          bRev=FALSE;
          ind=i;
       }
       v2=c2->cPts[c2->iNoCPts-1]->Pt_Point;
       v2=v2-v1;
       dist=v2.Mag();
       if (dist<MinDist)
       {
          MinDist=dist;
          cCand=c2;
          bRev=TRUE;
          ind=i;
       }
    }
  }
  if (cCand!=NULL)
  {
    if (bRev==TRUE)
    {
       cCand->Reverse();
    }
    Curves->Objs[ind]=NULL;
    tmp->Add(cCand);
  }
  }
}


for (j=0;j<tmp->iNo;j++)
{
  Curves->Objs[j]=tmp->Objs[j];
}

//ensure all intersecsiona are exact


c1=(NCurve*)  Curves->Objs[0];
c2=(NCurve*)  Curves->Objs[Curves->iNo-1];
v1=c1->cPts[0]->Pt_Point;
v2=c2->cPts[c2->iNoCPts-1]->Pt_Point;
v1=v1-v2;
dist=v1.Mag();
if (dist>0.001)
{
   bErr=TRUE;
   outtext1("ERROR: Boundary Not Closed.");
}
else
{
  for (j=0;j<Curves->iNo-1;j++)
  {
    c1=(NCurve*)  Curves->Objs[j];
    c2=(NCurve*)  Curves->Objs[j+1];
    v1=c1->cPts[c1->iNoCPts-1]->Pt_Point;
    c2->cPts[0]->Pt_Point->Set(v1.x,v1.y,v1.z);
  }
  c1=(NCurve*)  Curves->Objs[0];
  c2=(NCurve*)  Curves->Objs[Curves->iNo-1];
  v1=c1->cPts[0]->Pt_Point;
  c2->cPts[c2->iNoCPts-1]->Pt_Point->Set(v1.x,v1.y,v1.z);
}
delete(tmp);
return(bErr);
}


//**************************************************************
//Pre: List of curves
//Post: List of curves sorted into loop else bool=TRUE
//**************************************************************
BOOL DBase::ChainPath(ObjList* Curves)
{
int i;
int j;
int ind;
C3dVector v1;
C3dVector v2;
double dist;
double MinDist;
NCurve* c1;
NCurve* c2;
NCurve* cCand=NULL;
BOOL bRev=TRUE;
BOOL bErr = FALSE;
ObjList* tmp = new(ObjList);
tmp->Clear();
if (Curves->iNo==0)
{
  bErr = TRUE;
  delete(tmp);
  return(bErr);
}
else if (Curves->iNo==1)
{

}
else
{
  tmp->Add(Curves->Objs[0]);  //start with first curve
  Curves->Objs[0]=NULL;
  for (j=1;j<Curves->iNo;j++)
  {
  c1=(NCurve*)  tmp->Objs[j-1];
  v1=c1->GetPt(c1->we);
  MinDist=1e36;
  cCand=NULL;
  for (i=1;i<Curves->iNo;i++)
  {
    if (Curves->Objs[i]!=NULL)
    {     
       c2=(NCurve*)  Curves->Objs[i];
       v2=c2->GetPt(c2->ws);
       v2=v2-v1;
       dist=v2.Mag();
       if (dist<MinDist)
       {
          MinDist=dist;
          cCand=c2;
          bRev=FALSE;
          ind=i;
       }
       v2=c2->GetPt(c2->we);
       v2=v2-v1;
       dist=v2.Mag();
       if (dist<MinDist)
       {
          MinDist=dist;
          cCand=c2;
          bRev=TRUE;
          ind=i;
       }
    }
  }
  if (cCand!=NULL)
  {
    if (bRev==TRUE)
    {
       cCand->Reverse();
    }
    Curves->Objs[ind]=NULL;
    tmp->Add(cCand);
  }
  }
}


for (j=0;j<tmp->iNo;j++)
{
  Curves->Objs[j]=tmp->Objs[j];
}



delete(tmp);
return(bErr);
}

//*******************************************************************************
// THIS IS THE PARAMETRIC CURVE VERSION
// Internal Trim Loops
//*******************************************************************************
void DBase::AddSurfBoundTrimLoopIGES(G_Object* pS,ObjList* pCur) 
{
int i,j;
double dU;
double dV;
C3dVector p1;
C3dVector p2;
BOOL bErr=FALSE;
ObjList* pCurOnS= new ObjList();
NCurveOnSurf* pTC;
if (pS!=NULL)
{
if (pS->iObjType == 15)   //NSURF General surface not revolve
{
   
   NSurf* pFS = (NSurf*) pS;
   NCurve* pC;
   p1=pFS->GetPt(0,0); 
   p2=pFS->GetPt(1,0);

   dU=p1.Dist(p2);
   p2=pFS->GetPt(0,1);
   dV=p1.Dist(p2);


   for (i=0;i<pCur->iNo;i++)
   {
     if (pCur->Objs[i]==NULL)
       bErr=TRUE;
   }
   if (bErr==FALSE)
   {
	 
     for (i=0;i<pCur->iNo;i++)
     {
       pC=(NCurve*) pCur->Objs[i];
       pTC=pC->GetSurfaceCV2(pFS);
       pCurOnS->Add(pTC);
       //Now we have the curve on the surface need to
       //normalise the ordinates to UV
       for (j=0;j<pTC->iNoCPts;j++)
       {
         //double par1=(pTC->cPts[j]->Pt_Point->x-pFS->dUs)/dU;
         //double par2=(pTC->cPts[j]->Pt_Point->y-pFS->dVs)/dV;
		 double par1 = (pTC->cPts[j]->Pt_Point->x - pFS->dUs) / pFS->dUspan;
		 double par2 = (pTC->cPts[j]->Pt_Point->y - pFS->dVs) / pFS->dVspan;
         if (par1<0)
           par1=0;
         if (par2<0)
           par2=0;
         if (par1>1)
           par1=1;
         if (par2>1)
           par2=1;
         pTC->cPts[j]->Pt_Point->x=par1;
         pTC->cPts[j]->Pt_Point->y=par2;
       }
         pFS->AddTrimCurveExp(pTC);
     }
	 //bErr = ChainCurves(pCurOnS);
	 bErr = isClockWise(pCurOnS);
	 if (bErr)
	 {
		bErr = ChainReverse(pCurOnS);
	 }
     pFS->InternalTrim(pCurOnS);
   }
}
}

}

//*******************************************************************************
// THIS IS THE PARAMETRIC CURVE VERSION
// External boundary curves trim loop
//*******************************************************************************
void DBase::AddSurfBoundIGES(G_Object* pS,ObjList* pCur)
{
int i,j;
double dU;
double dV;
C3dVector p1;
C3dVector p2;
C3dVector vN;
C3dVector vSN;

BOOL bErr=FALSE;
ObjList* pCurOnS= new ObjList();
NCurveOnSurf* pTC;
if (pS!=NULL)
{
if (pS->iLabel == 3741) 
{
  pS=pS;
}
{   
  NSurf* pFS = (NSurf*) pS;
  NCurve* pC;

  if (pS->iObjType == 16)
  {
    dV=2*Pi;
    dU=1;
  }
  for (i=0;i<pCur->iNo;i++)
  {
    if (pCur->Objs[i]==NULL)
      bErr=TRUE;
  }
  if (bErr==FALSE)
  {
     bErr=ChainCurves(pCur);
	 for (i=0;i<pCur->iNo;i++)
     {
       pC=(NCurve*) pCur->Objs[i];
       pTC=pC->GetSurfaceCV2(pFS);
       pCurOnS->Add(pTC);
       //Now we have the curve on the surface need to
       //normalise the ordinates to UV
       for (j=0;j<pTC->iNoCPts;j++)
       {
         double par1=(pTC->cPts[j]->Pt_Point->x-pFS->dUs)/pFS->dUspan;
         double par2=(pTC->cPts[j]->Pt_Point->y-pFS->dVs)/pFS->dVspan;
         if (par1<0) par1=0;
         if (par1>1) par1=1;
         if (par2<0) par2=0;
         if (par2>1) par2=1;
         pTC->cPts[j]->Pt_Point->x=par1; 
         pTC->cPts[j]->Pt_Point->y=par2;
       }
       pFS->AddTrimCurveExp(pTC);
     }
     vSN=pFS->Get_Normal(0.5,0.5);
     vSN.Normalize();
     //bErr=ChainNormal2(pFS,pCurOnS,vN);
	 bErr = isClockWise(pCurOnS);
     if (!bErr)
     {
       bErr=ChainReverse(pCurOnS);
     }
     pFS->UserTrim(pCurOnS);
   }
}
}
delete(pCurOnS);
}

//*******************************************************************************
// THIS IS THE NON PARAMETRIC CURVE VERSION - IDES TYPE 141
// External boundary curves trim loop
// pS the surface to trim allready created and in database
// pCur ptr to the curves forminf the boundary
// these can either be in model or paremtric coods were restrictic to model
// Need to check it could be an External or Internal trim loop
// Model coordinate curves need to be converted to curves on surface 
//*******************************************************************************
void DBase::AddSurfBoundIGES2(G_Object* pS, ObjList* pCur)
{
	int i;
	NSurf* pSurf;
	pSurf = (NSurf*) pS;
	C3dVector vN;
	C3dVector vCDir;
	C3dVector vO;
	C3dVector v1;
	C3dVector v2;
	for (i = 0; i < pCur->iNo; i++)
	{
		//Convert all curves to curves on surface.
		pCur->Objs[i] = pSurf->AddTrimCurve((NCurve*)pCur->Objs[i]);
	}

	//Need to determine if its an external or internal trim loop
	//cross product with curve dir and surface normal.

	C3dVector vSN = pSurf->Get_Normal(0.5, 0.5);
	vSN.Normalize();
	//BOOL bErr = ChainNormal(pCur, vN); Chain normal fails
	BOOL bCLk = isClockWise(pCur);

	if (bCLk)
		pSurf->UserTrim(pCur);
	else
		pSurf->InternalTrim(pCur);
	

}

void DBase::CurveModType(int iW)
{
int i;
NCurve* pC;
for (i=0;i<S_Count;i++)
{
  if ((S_Buff[i]->iObjType == 7) ||
      (S_Buff[i]->iObjType == 13))
  {
    pC=(NCurve*) S_Buff[i];
	  pC->iLnType=iW;
  }
}
InvalidateOGL();
ReDraw();
}

void DBase::CurveModLWT(int iW)
{
int i;
NCurve* pC;
for (i=0;i<S_Count;i++)
{
  if ((S_Buff[i]->iObjType == 7) ||
	  (S_Buff[i]->iObjType == 13))
  {
      pC=(NCurve*) S_Buff[i];
	  pC->iLnThk=iW;
  }
}
InvalidateOGL();
ReDraw();
}

void DBase::AddSolidSection()
{

}

void DBase::AddSurfBound()
{

BOOL bErr;

C3dVector pt;
NSurf* pS;

ObjList* Curves = new ObjList();
Curves->Clear();
int i;
int j;
double dInc;
for (i=0;i<S_Count;i++)
{
	if ((S_Buff[i]->iObjType == 7) && (S_Buff[i]->iType == 1))
	{
		//NEEDS UPDATING TO CURVE SPLIT FOR WS & WE <> 0 & 1
		//Curves->Add(S_Buff[i]->Copy(NULL));
		NCurve* pC = (NCurve*)S_Buff[i];
		if ((pC->we == 1.0) && (pC->ws == 0.0))
		{
			Curves->Add(S_Buff[i]->Copy(NULL));
		}
		else
		{
			dInc = (pC->we - pC->ws) / 36;
			NCurve* pPC = new NCurve();
			for (j = 0; j <= 36; j++)
			{
				pt = pC->GetPt(pC->ws + j * dInc);
				pPC->AddVert(pt, 1);
			}
			pPC->Generate(1);
			Curves->Add(pPC);
		}
	}
	else if ((S_Buff[i]->iObjType == 7) && (S_Buff[i]->iType == 2))
	{
		C3dVector p1, p2;
		NCurve* C1 = (NCurve*)S_Buff[i];
		p1 = C1->GetPt(C1->ws);
		p2 = C1->GetPt(C1->we);
		NLine* oL = new NLine();
		oL->Create(p1, p2, -1, NULL);
		Curves->Add(oL);
		// Curves->Add(S_Buff[i]->Copy(NULL));
	}
  else if (S_Buff[i]->iObjType == 13)
  {  
     NCurveOnSurf* pSS;
     pSS=(NCurveOnSurf*) S_Buff[i];
     Curves->Add(pSS->GetSurfaceCVG(pSS->pParent));
  }
  else if ((S_Buff[i]->iObjType == 7) && (S_Buff[i]->iType == 3))
  {
  //Need to deal with incomplete circles until we have 
  //the arbitaru arc
    NCircle* pC = (NCircle*) S_Buff[i];
    if ((pC->we==1.0) && (pC->ws==0.0))
    {
      Curves->Add(S_Buff[i]->Copy(NULL));
    }
    else
    {
       dInc=(pC->we-pC->ws)/36;
       NCurve* pPC=new NCurve();
       for (j=0;j<=36;j++)
       {
         pt=pC->GetPt(pC->ws+j*dInc);
         pPC->AddVert(pt,1);
       }
       pPC->Generate(1);
       Curves->Add(pPC);
    }
  }
}
C3dVector vR;
C3dVector vY;
C3dVector vN;
C3dVector vO;
C3dMatrix TMat;
C3dMatrix TMatInv;
double XMax;
double YMax;
double XMin;
double YMin;
if (Curves->iNo>0)
  {
  bErr=ChainCurves(Curves);
  bErr=ChainNormal(Curves,vN);
  bErr=ChainRef(Curves,vR,vO);
  vR.Normalize();
  vN.Normalize();
  vY=vN.Cross(vR);
  TMat.SetColVec(1,vR);
  TMat.SetColVec(2,vY);
  TMat.SetColVec(3,vN);
  TMat.ClearTranslations();
  TMatInv=TMat;
  TMatInv.Transpose();
  //TMat.Translate(-vO.x,-vO.y,-vO.z);
  TMat.Translate2(vO.x,vO.y,vO.z);
  bErr=Extents(Curves,TMatInv,vO,XMax,YMax,XMin,YMin);
  pS=AddPlainSurf2(TMat,XMax,YMax,XMin,YMin,TRUE);
  for (i=0;i<Curves->iNo;i++)
  {
    Curves->Objs[i] = pS->AddTrimCurve((NCurve*) Curves->Objs[i]);
  }
  pS->UserTrim(Curves);
  //pS->DefualtTrim();
}

delete (Curves);
ReDraw();
}


void DBase::SurfaceTrimLoop(ObjList* Sur,ObjList* Curves2)
{

BOOL bErr;
NSurf* pS;
pS=(NSurf*) Sur->Objs[0];
C3dVector vR;
C3dVector vN;
C3dVector vSN;
C3dVector vO;
C3dMatrix TMat;
C3dVector pt;
int i;
int j;
double dInc;
if ((Sur->iNo>0) && (Curves2->iNo>0))
{
  ObjList* Curves = new ObjList();
  Curves->Clear();

  G_Object* pG;
  for (i=0;i<Curves2->iNo;i++)
  {
    pG=(G_Object*) Curves2->Objs[i];
    if ((pG->iType == 1) ||
        (pG->iType == 2))
    {
       Curves->Add(pG);
    }
    else if (pG->iType == 3)
    {
    //Need to deal with incomplete circles until we have 
    //the arbitaru arc
      NCircle* pC = (NCircle*) pG;
      if ((pC->we==1.0) && (pC->ws==0.0))
      {
        Curves->Add(pC);
      }
      else
      {
         dInc=(pC->we-pC->ws)/36;
         NCurve* pPC=new NCurve();
         for (j=0;j<=36;j++)
         {
           pt=pC->GetPt(pC->ws+j*dInc);
           pPC->AddVert(pt,1);
         }
         pPC->Generate(1);
         Curves->Add(pPC);
      }
    }
  }

  vO.Set(0,0,0);
  vSN=pS->Get_Normal(0.5,0.5);
  bErr=ChainCurves(Curves);
  bErr=ChainNormal(Curves,vN);
  if (vN.Dot(vSN)>0)
  {
    bErr=ChainReverse(Curves);
  }

  for (i=0;i<Curves->iNo;i++)
  {
    
    Curves->Objs[i] = pS->AddTrimCurve((NCurve*) Curves->Objs[i]);
  }
  pS->InternalTrim(Curves);
  delete(Curves);
  InvalidateOGL();
  ReDraw();
  }
}

void DBase::OffSet(G_Object* pOff,C3dVector vDir,double Dist)
{
G_Object* pO;
C3dVector vN;

WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
C3dMatrix mSc,mScInv;     
vN.Set(0,0,1);
mSc=pWPlane->mWPTransform;
mScInv=mSc;//.Inv();
mScInv.m_30=0;
mScInv.m_31=0;
mScInv.m_32=0;
vN=mScInv.MultBack(vN);
if (pOff!=NULL)
{
  if (pOff->iObjType==7) 
  {
    pO = pOff->OffSet(vN,vDir,Dist);
    if (pO!=NULL)
	{
       pO->iLabel=iCVLabCnt;
	   iCVLabCnt++;
	   AddObj(pO);
       ReDraw();
	}
  }
}
}

void DBase::BeamUpVecs(ObjList* Items,C3dVector tVec)
{
int iCO;
char s1[200];
CString OutT;
BOOL bReGen=FALSE;
tVec.Normalize();
for (iCO=0;iCO<Items->iNo;iCO++)
{
  if (Items->Objs[iCO]->iObjType == 3)
  {
    E_Object* pE = (E_Object*) Items->Objs[iCO];
    if (pE->iType==21)
    {
      E_Object2B* pB=(E_Object2B*) pE;
      C3dVector vDir;
      vDir=pB->GetDir();
      if (abs(tVec.Dot(vDir) < 0.99))
      {
         pB->vUp=tVec;
         pB->iONID=-1;
         bReGen=TRUE;
         sprintf_s(s1,"%s%i","Up vector changed for El: ",pE->iLabel);
         OutT=s1;
         outtext1(OutT);
      }
      else
      {
         sprintf_s(s1,"%s%i","Up vector or colinear for El: ",pE->iLabel);
         OutT=s1;
         outtext1(OutT);
      }
    }
  }
}
if (bReGen==TRUE)
{
  InvalidateOGL();
  ReDraw();
}
}

void DBase::BeamOffsets(ObjList* Items,C3dVector tVec)
{
int iCO;

CString OutT;
BOOL bReGen=FALSE;
for (iCO=0;iCO<Items->iNo;iCO++)
{
  if (Items->Objs[iCO]->iObjType == 3)
  {
    E_Object* pE = (E_Object*) Items->Objs[iCO];
    if (pE->iType==21)
    {
      E_Object2B* pB=(E_Object2B*) pE;
      pB->OffA=tVec;
      pB->OffB=tVec;
      bReGen=TRUE;
    }
  }
}
if (bReGen==TRUE)
{
  InvalidateOGL();
  ReDraw();
}
}

void DBase::BeamOffsetY(ObjList* Items, double dy)
{
	int iCO;
	C3dVector tVec;
	C3dVector tVecR;
	tVec.Set(0, dy, 0);
	C3dMatrix EMat;
	CString OutT;
	BOOL bReGen = FALSE;
	for (iCO = 0; iCO < Items->iNo; iCO++)
	{
		if (Items->Objs[iCO]->iObjType == 3)
		{
			E_Object* pE = (E_Object*)Items->Objs[iCO];
			if (pE->iType == 21)
			{

				E_Object2B* pB = (E_Object2B*)pE;
				EMat = pB->GetElSys();
				EMat.Transpose();
				tVecR = EMat*tVec;
				pB->OffA = tVecR;
				pB->OffB = tVecR;
				bReGen = TRUE;
			}
		}
	}
	if (bReGen == TRUE)
	{
		InvalidateOGL();
		ReDraw();
	}
}

void DBase::BeamOffsetZ(ObjList* Items, double dz)
{
	int iCO;
	C3dVector tVec;
	C3dVector tVecR;
	tVec.Set(0, 0, dz);
	C3dMatrix EMat;
	CString OutT;
	BOOL bReGen = FALSE;
	for (iCO = 0; iCO < Items->iNo; iCO++)
	{
		if (Items->Objs[iCO]->iObjType == 3)
		{
			E_Object* pE = (E_Object*)Items->Objs[iCO];
			if (pE->iType == 21)
			{

				E_Object2B* pB = (E_Object2B*)pE;
				EMat = pB->GetElSys();
				EMat.Transpose();
				tVecR = EMat*tVec;
				pB->OffA = tVecR;
				pB->OffB = tVecR;
				bReGen = TRUE;
			}
		}
	}
	if (bReGen == TRUE)
	{
		InvalidateOGL();
		ReDraw();
	}
}

void DBase::SetDOFStringA(ObjList* Items, CString sDOF)
{
	int iCO;
	CString OutT;
	for (iCO = 0; iCO < Items->iNo; iCO++)
	{
		if (Items->Objs[iCO]->iObjType == 3)
		{
			E_Object* pE = (E_Object*)Items->Objs[iCO];
			if (pE->iType == 21)
			{
				E_Object2B* pB = (E_Object2B*)pE;
				pB->SetDOFStringA(sDOF);
			}
		}
	}
}

void DBase::SetDOFStringB(ObjList* Items, CString sDOF)
{
	int iCO;
	CString OutT;
	for (iCO = 0; iCO < Items->iNo; iCO++)
	{
		if (Items->Objs[iCO]->iObjType == 3)
		{
			E_Object* pE = (E_Object*)Items->Objs[iCO];
			if (pE->iType == 21)
			{
				E_Object2B* pB = (E_Object2B*)pE;
				pB->SetDOFStringB(sDOF);
			}
		}
	}
}

void DBase::ShellOffsets(ObjList* Items,double dOff)
{
int iCO=0;
int iNoC=0;
char s1[200];

CString OutT;
BOOL bReGen=FALSE;
for (iCO=0;iCO<Items->iNo;iCO++)
{
  if (Items->Objs[iCO]->iObjType == 3)
  {
    E_Object* pE = (E_Object*) Items->Objs[iCO];
    if (pE->iType==91) 
    {
      E_Object3* pB=(E_Object3*) pE;
      pB->dZOFFS=dOff;
      bReGen=TRUE;
	  iNoC++;
    }
    else if (pE->iType==94) 
    {
      E_Object4* pB=(E_Object4*) pE;
      pB->dZOFFS=dOff;
      bReGen=TRUE;
	  iNoC++;
    }
  }
}
sprintf_s(s1, "%s%i", "Number of Elements Modified : ", iNoC);
outtext1(_T(s1));
if (bReGen==TRUE)
{
  InvalidateOGL();
  ReDraw();
}
}


void DBase::Copy(ObjList* Items,C3dVector tVec,int iNoOff)
{
int i;
int j;
int k;
int iNewNd=-1;
NEList* newNds = new NEList();
G_Object* pO;
C3dVector vA;
Node* pInVertex[MaxSelNodes];
Node* Nd;
Node* NdNew;
E_Object* El;
E_Object* ENew;


if (Items->iNo>0)
{
pCurrentMesh->MaxLab();
//pCurrentMesh->iElementLab++;
//pCurrentMesh->iNodeLab++;
vA = tVec;
for (j=0;j<iNoOff;j++)
{
  newNds->iNo=0;
  for (i=0;i<Items->iNo;i++)
  {
    if (Items->Objs[i]->iObjType==3)
    {
      El= (E_Object*) Items->Objs[i];
      for (k=0;k<El->iNoNodes;k++)
      {
        Nd=(Node*) El->GetNode(k);
        iNewNd=newNds->Get(Nd->iLabel);
        if (iNewNd!=-1)
        {
          pInVertex[k]=(Node*) pCurrentMesh->GetNode(iNewNd);
        }
        else
        {
          pInVertex[k]=(Node*) El->GetNode(k)->Copy(pCurrentMesh);
          pInVertex[k]->iLabel=pCurrentMesh->iNodeLab;
          newNds->Add(Nd->iLabel,pCurrentMesh->iNodeLab);
          pCurrentMesh->iNodeLab++;
          pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=pInVertex[k];
          pCurrentMesh->iNdNo++;
          MoveObj(pInVertex[k],vA);
          Dsp_Add(pInVertex[k]);
        }
      }
      ENew=(E_Object*) El->Copy2(pCurrentMesh,pInVertex,El->PID,El->iMatID,El->PIDunv);
      Dsp_Add(ENew);
      pCurrentMesh->pElems[pCurrentMesh->iElNo]=ENew;
      pCurrentMesh->iElNo++    ;             
      ENew->iLabel=pCurrentMesh->iElementLab++;
      pCurrentMesh->iElementLab++;
    }
  } 
  vA+=tVec;
}

  for (i=0;i<Items->iNo;i++)
  {
    if ((Items->Objs[i]->iObjType==1) || (Items->Objs[i]->iObjType==3) || (Items->Objs[i]->iObjType==13))
    {
      if (Items->Objs[i]->iObjType==1)
      {
        Nd= (Node*) Items->Objs[i];
        vA = tVec;
	      for (j=0;j<iNoOff;j++)
        {
          	NdNew=(Node*) Nd->Copy(pCurrentMesh);
            NdNew->iLabel=pCurrentMesh->iNodeLab;
            newNds->Add(Nd->iLabel,pCurrentMesh->iNodeLab);
            pCurrentMesh->iNodeLab++;
            pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=NdNew;
            Dsp_Add(NdNew);
            pCurrentMesh->iNdNo++;
            MoveObj(NdNew,vA);
            vA+=tVec;
        }   
      }   
    }
    else
    {
	    vA = tVec;
	    for (j=0;j<iNoOff;j++)
        {
	      pO = Items->Objs[i]->Copy(NULL);
		  if (pO->iObjType==0)
		  {  //Point
             pO->iLabel=iPtLabCnt;
			 iPtLabCnt++;
		  }
		  else if (pO->iObjType == 4)
		  {  //MESH
			  pO->iLabel = iMeshCnt;
			  iMeshCnt++;
		  }
		  else if (pO->iObjType == 6)
		  {  //Text
			  pO->iLabel = iTxtLabCnt;
			  iTxtLabCnt++;
		  }
		  else if (pO->iObjType==7)
		  {  //curve
             pO->iLabel=iCVLabCnt;
			 iCVLabCnt++;
		  }
		  else if (pO->iObjType==15)
		  {  //surface
             pO->iLabel=iSFLabCnt;
			 iSFLabCnt++;
		  }
		  else if (pO->iObjType == 12)
		  {  //Coordinate System
			  pO->iLabel = pCurrentMesh->iCYSLab;
			  pCurrentMesh->iCYSLab++;
		  }
          pO->pParent=NULL;
		  MoveObj(pO,vA);
	      AddObj(pO);
          Dsp_Add(pO);
		  vA+=tVec;
	    }
    }
  }
delete (newNds);
InvalidateOGL();
ReDraw();
}
}


void DBase::CopyRot(ObjList* Items,C3dVector p1,C3dVector p2,double dAng,int iNoOff)
{
int i;
int j;
int k;
int iNewNd;
G_Object* pO;
double dA;
NEList* newNds = new NEList();
Node* pInVertex[MaxSelNodes];
Node* Nd;
Node* NdNew;
E_Object* El;
E_Object* ENew;


if (Items->iNo>0)
{
  pCurrentMesh->MaxLab();
  pCurrentMesh->iElementLab++;
  pCurrentMesh->iNodeLab++;

dA = dAng;
for (j=0;j<iNoOff;j++)
{
  newNds->iNo=0;
  for (i=0;i<Items->iNo;i++)
  {
    if (Items->Objs[i]->iObjType==3)
    {
      El= (E_Object*) Items->Objs[i];
      for (k=0;k<El->iNoNodes;k++)
      {
        Nd=(Node*) El->GetNode(k);
        iNewNd=newNds->Get(Nd->iLabel);
        if (iNewNd!=-1)
        {
          pInVertex[k]=(Node*) pCurrentMesh->GetNode(iNewNd);
        }
        else
        {
          pInVertex[k]=(Node*) El->GetNode(k)->Copy(pCurrentMesh);
          pInVertex[k]->iLabel=pCurrentMesh->iNodeLab;
          newNds->Add(Nd->iLabel,pCurrentMesh->iNodeLab);
          pCurrentMesh->iNodeLab++;
          pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=pInVertex[k];
          pCurrentMesh->iNdNo++;
          RotateAbout2(pInVertex[k],p1,p2,dA);
        }
      }
      ENew=(E_Object*) El->Copy2(pCurrentMesh,pInVertex,El->PID,El->iMatID,El->PIDunv);
      pCurrentMesh->pElems[pCurrentMesh->iElNo]=ENew;
      pCurrentMesh->iElNo++    ;             
      ENew->iLabel=pCurrentMesh->iElementLab++;
      pCurrentMesh->iElementLab++;
      Dsp_Add(ENew);
    }
  } 
  dA+=dAng;
}

  for (i=0;i<Items->iNo;i++)
  {
    if ((Items->Objs[i]->iObjType==1) || (Items->Objs[i]->iObjType==3) || (Items->Objs[i]->iObjType==13))
    {
      if (Items->Objs[i]->iObjType==1)
      {
        Nd= (Node*) Items->Objs[i];
        dA = dAng;
	      for (j=0;j<iNoOff;j++)
        {
          	NdNew=(Node*) Nd->Copy(pCurrentMesh);
            NdNew->iLabel=pCurrentMesh->iNodeLab;
            pCurrentMesh->iNodeLab++;
            pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=NdNew;
            pCurrentMesh->iNdNo++;
            RotateAbout2(NdNew,p1,p2,dA);
            dA+=dAng;
            Dsp_Add(NdNew);
        }   
      }   
    }
    else
    {
	    dA = dAng;
	    for (j=0;j<iNoOff;j++)
      {
	    pO = Items->Objs[i]->Copy(NULL);
		  if (pO->iObjType==0)
		  {		//Point
				pO->iLabel=iPtLabCnt;
				iPtLabCnt++;
		  }
		  else if (pO->iObjType == 6)
		  {		//Text
				pO->iLabel = iTxtLabCnt;
				iTxtLabCnt++;
		  }
		  else if (pO->iObjType==7) 
		  {		//curve
				pO->iLabel=iCVLabCnt;
				iCVLabCnt++;
		  }
		  else if (pO->iObjType==15)
		  {		//surface
				pO->iLabel=iSFLabCnt;
				iSFLabCnt++;
		  }
          RotateAbout2(pO,p1,p2,dA);
	      AddObj(pO);
		  dA+=dAng;
	    }
    }
  }
InvalidateOGL();
ReDraw();
}
}

void DBase::ElSweep(ObjList* Items,C3dVector tVec,int iNoOff)
{
int i;
int j;
int k;
double dd = iNoOff;
eFace* eF = NULL;
eEdge* eE = NULL;
//change to how sweep is done now tVec is the totatl vector
//to move in iNoOff increments
if (iNoOff > 0)
{
	tVec.x /= dd;
	tVec.y /= dd;
	tVec.z /= dd;
}
Node* iNlabs[MaxSelNodes]; 
C3dVector vA;
Node* NdNew = NULL;
E_Object* El = NULL;
E_Object* ENew = NULL;
ObjList* ELF=new ObjList;
ObjList* NDF=new ObjList;;
ObjList* NDF1=new ObjList;;
ObjList* NDF2=new ObjList;;
NDF->Clear();
NDF1->Clear();
NDF2->Clear();
ELF->Clear();
BOOL bFirst = TRUE;
if (Items->iNo>0)
{
  pCurrentMesh->MaxLab();
  pCurrentMesh->iElementLab++;
  pCurrentMesh->iNodeLab++;
  for (i=0;i<Items->iNo;i++)
  {
    if (Items->Objs[i]->iObjType==3) 
    {
	    El = (E_Object*) Items->Objs[i];
        if ((El->iType == 91) || (El->iType == 94) || (El->iType == 21))
        {
		  ELF->Add(El);
          for (j=0;j<El->iNoNodes;j++)
		  {
            NDF->AddEx(El->GetNode(j)); 
		  }
        }
	}
	else if (Items->Objs[i]->iObjType == 9) //eFace
	{
		eF = (eFace*) Items->Objs[i];
		if (eF->NoVert == 4)	 //Used as a marker to tell what type of element it is
		{
			E_Object4* El4 = new E_Object4();
			El4->iType = 94;
			ELF->Add(El4);
			for (j = 0; j < eF->NoVert; j++)
			{
				El4->pVertex[j] = eF->pVertex[j];
				NDF->AddEx(eF->pVertex[j]);
			}
		}
		else if (eF->NoVert == 3)
		{
			E_Object3* EL3 = new E_Object3();
			EL3->iType = 91;
			ELF->Add(EL3);
			for (j = 0; j < eF->NoVert; j++)
			{
				EL3->pVertex[j] = eF->pVertex[j];
				NDF->AddEx(eF->pVertex[j]);
			}
		}
		
	}
	else if (Items->Objs[i]->iObjType == 8) //eEdge
	{
		eE = (eEdge*)Items->Objs[i];
		E_Object2* El2 = new E_Object2B();
		El2->iType = 21;
		ELF->Add(El2);
		for (j = 0; j < 2; j++)
		{
			El2->pVertex[j] = eE->pVertex[j];
			NDF->AddEx(eE->pVertex[j]);
		}
	}
  }

for (i=0;i<iNoOff+1;i++)
{
  if (bFirst==TRUE)
  {
    //vA = tVec;
    vA.Set(0,0,0);
    for (j=0;j<NDF->iNo;j++)
    {
      NdNew=(Node*) NDF->Objs[j]->Copy(pCurrentMesh);
      NdNew->iLabel=pCurrentMesh->iNodeLab;
      pCurrentMesh->iNodeLab++;
      pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=NdNew;
	  NDF1->Add(NdNew);
      pCurrentMesh->iNdNo++;
      MoveObj(NdNew,vA);
    }
    bFirst=FALSE;
  }
  else
  {
    vA = tVec;
    for (j=0;j<NDF->iNo;j++)
    {
      NdNew=(Node*) NDF1->Objs[j]->Copy(pCurrentMesh);
      NdNew->iLabel=pCurrentMesh->iNodeLab;
      pCurrentMesh->iNodeLab++;
      pCurrentMesh->pNodes[pCurrentMesh->iNdNo]=NdNew;
	  NDF2->Objs[j] = NdNew;
      pCurrentMesh->iNdNo++;
      MoveObj(NdNew,vA);
    }
	for (k=0;k<ELF->iNo;k++)
	{
      El = (E_Object*) ELF->Objs[k];
      if (El->iType==94)
	  {
        iNlabs[0]=(Node*) NDF1->Objs[NDF->IsIn2(El->GetNode(0))];
	    iNlabs[1]=(Node*) NDF1->Objs[NDF->IsIn2(El->GetNode(1))];
	    iNlabs[2]=(Node*) NDF1->Objs[NDF->IsIn2(El->GetNode(2))];
	    iNlabs[3]=(Node*) NDF1->Objs[NDF->IsIn2(El->GetNode(3))];
        iNlabs[4]=(Node*) NDF2->Objs[NDF->IsIn2(El->GetNode(0))];
	    iNlabs[5]=(Node*) NDF2->Objs[NDF->IsIn2(El->GetNode(1))];
	    iNlabs[6]=(Node*) NDF2->Objs[NDF->IsIn2(El->GetNode(2))];
	    iNlabs[7]=(Node*) NDF2->Objs[NDF->IsIn2(El->GetNode(3))];
		ENew=pCurrentMesh->AddEl(iNlabs,pCurrentMesh->iElementLab,9,115,-1,1,8,0,0,0,0,0,0);
		pCurrentMesh->iElementLab++;
	  }
	  else if (El->iType==91)
	  {
        iNlabs[0]=(Node*) NDF1->Objs[NDF->IsIn2(El->GetNode(0))];
	    iNlabs[1]=(Node*) NDF1->Objs[NDF->IsIn2(El->GetNode(1))];
	    iNlabs[2]=(Node*) NDF1->Objs[NDF->IsIn2(El->GetNode(2))];
        iNlabs[3]=(Node*) NDF2->Objs[NDF->IsIn2(El->GetNode(0))];
	    iNlabs[4]=(Node*) NDF2->Objs[NDF->IsIn2(El->GetNode(1))];
	    iNlabs[5]=(Node*) NDF2->Objs[NDF->IsIn2(El->GetNode(2))];
		ENew=pCurrentMesh->AddEl(iNlabs,pCurrentMesh->iElementLab,9,112,-1,1,6,0,0,0,0,0,0);
		pCurrentMesh->iElementLab++;
	  }
	  else if (El->iType == 21)
	  {
		  iNlabs[0] = (Node*)NDF1->Objs[NDF->IsIn2(El->GetNode(0))];
		  iNlabs[1] = (Node*)NDF2->Objs[NDF->IsIn2(El->GetNode(0))];
		  iNlabs[2] = (Node*)NDF2->Objs[NDF->IsIn2(El->GetNode(1))];
		  iNlabs[3] = (Node*)NDF1->Objs[NDF->IsIn2(El->GetNode(1))];
		  ENew = pCurrentMesh->AddEl(iNlabs, pCurrentMesh->iElementLab, 74, 94, -1, 1, 4, 0, 0, 0, 0, -1, 0);
		  pCurrentMesh->iElementLab++;
	  }

	}
    for (j=0;j<NDF->iNo;j++)
    {
	  NDF1->Objs[j] = NDF2->Objs[j];
    }
  } 
}
InvalidateOGL();
ReDraw();
}
delete(ELF);
delete(NDF);
delete(NDF1);
delete(NDF2);
}

//******************************************************************
//Sweep an ordered list of nodes into shell elements along tvec
void DBase::NDSweepToShell(ObjList* Items, C3dVector tVec, int iNoOff)
{
	int i;
	int j;
	int k;
	double dd = iNoOff;
	//change to how sweep is done now tVec is the totatl vector
	//to move in iNoOff increments
	if (iNoOff > 0)
	{
		tVec.x /= dd;
		tVec.y /= dd;
		tVec.z /= dd;
	}
	Node* iNlabs[MaxSelNodes];
	C3dVector vA;
	Node* NdNew = NULL;
	E_Object* El = NULL;
	E_Object* ENew = NULL;
	ObjList* ELF = new ObjList;
	ObjList* NDF = new ObjList;;
	ObjList* NDF1 = new ObjList;;
	ObjList* NDF2 = new ObjList;;
	NDF->Clear();
	NDF1->Clear();
	NDF2->Clear();
	ELF->Clear();
	BOOL bFirst = TRUE;
	if (Items->iNo > 0)
	{
		pCurrentMesh->MaxLab();
		pCurrentMesh->iElementLab++;
		pCurrentMesh->iNodeLab++;
		for (i = 0; i < Items->iNo; i++)
		{
			if (Items->Objs[i]->iObjType == 1)
			{
						NDF->AddEx(Items->Objs[i]);
			}	
		}
		for (i = 0; i < iNoOff + 1; i++)
		{
			if (bFirst == TRUE)
			{
				//vA = tVec;
				vA.Set(0, 0, 0);
				for (j = 0; j < NDF->iNo; j++)
				{
					//NdNew = (Pt_Object*)NDF->Objs[j]->Copy(pCurrentMesh);
					//NdNew->iLabel = pCurrentMesh->iNodeLab;
					//pCurrentMesh->iNodeLab++;
					//pCurrentMesh->pNodes[pCurrentMesh->iNdNo] = NdNew;
					NDF1->Add(NDF->Objs[j]);
					//pCurrentMesh->iNdNo++;
					//MoveObj(NdNew, vA);
				}
				bFirst = FALSE;
			}
			else
			{
				vA = tVec;
				for (j = 0; j < NDF->iNo; j++)
				{
					NdNew = (Node*)NDF1->Objs[j]->Copy(pCurrentMesh);
					NdNew->iLabel = pCurrentMesh->iNodeLab;
					pCurrentMesh->iNodeLab++;
					pCurrentMesh->pNodes[pCurrentMesh->iNdNo] = NdNew;
					NDF2->Objs[j] = NdNew;
					pCurrentMesh->iNdNo++;
					MoveObj(NdNew, vA);
				}
				for (k = 0; k < NDF1->iNo-1; k++)
				{
						iNlabs[0] = (Node*) NDF1->Objs[k];
						iNlabs[1] = (Node*) NDF2->Objs[k];
						iNlabs[2] = (Node*) NDF2->Objs[k+1]; 
						iNlabs[3] = (Node*) NDF1->Objs[k+1];
						ENew = pCurrentMesh->AddEl(iNlabs, pCurrentMesh->iElementLab, 74, 94, -1, 1, 4, 0, 0, 0, 0, -1, 0);
						pCurrentMesh->iElementLab++;
				}
				for (j = 0; j < NDF->iNo; j++)
				{
					NDF1->Objs[j] = NDF2->Objs[j];
				}
			}
		}
		InvalidateOGL();
		ReDraw();
	}
	delete(ELF);
	delete(NDF);
	delete(NDF1);
	delete(NDF2);
}

//******************************************************************
//Sweep an ordered list of nodes into beam elements along tvec
void DBase::NDSweepToBeam(ObjList* Items, C3dVector tVec, int iNoOff)
{
	int i;
	int j;
	int k;
	double dd = iNoOff;
	//change to how sweep is done now tVec is the totatl vector
	//to move in iNoOff increments
	if (iNoOff > 0)
	{
		tVec.x /= dd;
		tVec.y /= dd;
		tVec.z /= dd;
	}
	Node* iNlabs[MaxSelNodes];
	C3dVector vA;
	Node* NdNew = NULL;
	E_Object* El = NULL;
	E_Object* ENew = NULL;
	ObjList* ELF = new ObjList;
	ObjList* NDF = new ObjList;;
	ObjList* NDF1 = new ObjList;;
	ObjList* NDF2 = new ObjList;;
	NDF->Clear();
	NDF1->Clear();
	NDF2->Clear();
	ELF->Clear();
	BOOL bFirst = TRUE;
	if (Items->iNo > 0)
	{
		pCurrentMesh->MaxLab();
		pCurrentMesh->iElementLab++;
		pCurrentMesh->iNodeLab++;
		for (i = 0; i < Items->iNo; i++)
		{
			if (Items->Objs[i]->iObjType == 1)
			{
				NDF->AddEx(Items->Objs[i]);
			}
		}
		for (i = 0; i < iNoOff + 1; i++)
		{
			if (bFirst == TRUE)
			{
				//vA = tVec;
				vA.Set(0, 0, 0);
				for (j = 0; j < NDF->iNo; j++)
				{
					//NdNew = (Pt_Object*)NDF->Objs[j]->Copy(pCurrentMesh);
					//NdNew->iLabel = pCurrentMesh->iNodeLab;
					//pCurrentMesh->iNodeLab++;
					//pCurrentMesh->pNodes[pCurrentMesh->iNdNo] = NdNew;
					NDF1->Add(NDF->Objs[j]);
					//pCurrentMesh->iNdNo++;
					//MoveObj(NdNew, vA);
				}
				bFirst = FALSE;
			}
			else
			{
				vA = tVec;
				for (j = 0; j < NDF->iNo; j++)
				{
					NdNew = (Node*)NDF1->Objs[j]->Copy(pCurrentMesh);
					NdNew->iLabel = pCurrentMesh->iNodeLab;
					pCurrentMesh->iNodeLab++;
					pCurrentMesh->pNodes[pCurrentMesh->iNdNo] = NdNew;
					NDF2->Objs[j] = NdNew;
					pCurrentMesh->iNdNo++;
					MoveObj(NdNew, vA);
				}
				for (k = 0; k < NDF1->iNo; k++)
				{
					iNlabs[0] = (Node*)NDF1->Objs[k];
					iNlabs[1] = (Node*)NDF2->Objs[k];
					ENew = pCurrentMesh->AddEl(iNlabs, pCurrentMesh->iElementLab, 75, 21, -1, 1, 4, 0, 0, 0, 0, -1, 0);
					pCurrentMesh->iElementLab++;
				}
				for (j = 0; j < NDF->iNo; j++)
				{
					NDF1->Objs[j] = NDF2->Objs[j];
				}
			}
		}
		InvalidateOGL();
		ReDraw();
	}
	delete(ELF);
	delete(NDF);
	delete(NDF1);
	delete(NDF2);
}
//*********************************************************************************
// Pre: Node
// Post: Nodal averaged normal calculated
//*********************************************************************************
C3dVector DBase::GetNodalNormal(Node* pN, ObjList* ELS)
{
	int i;
	double dC=0;
	C3dVector vRet;
	C3dMatrix mS;
	vRet.Set(0, 0, 0);
	ME_Object* ME = pCurrentMesh;
	E_Object* pE;

	for (i=0;i<ELS->iNo;i++)
	{
		pE = (E_Object*) ELS->Objs[i];
		if (pE->NodeInEl(pN))
		{
			mS = pE->GetElSys();
			vRet.x += mS.m_10;
			vRet.y += mS.m_11;
			vRet.z += mS.m_12;
			dC += 1.0;
		}
		
	}
	double dS;
	dS = 1 / dC;
	vRet*= dS;
	vRet.Normalize();
	return (vRet);
}


//*********************************************************************************
// Pre: Node
// Post: Nodal averaged normal calculated
//*********************************************************************************
C3dVector DBase::GetNodalNormal2(Node* pN, ObjList* ELS)
{
	int i;
	double dC = 0;
	C3dVector vRet;
	C3dVector vZ;
	C3dVector vDir;
	C3dVector vN;
	vZ.Set(0, 0, 1);
	vRet.Set(0, 0, 0);
	ME_Object* ME = pCurrentMesh;

	eEdge* pEE1 = (eEdge*) ELS->Objs[0];
	for (i = 0; i < ELS->iNo; i++)
	{
		eEdge* pEE = (eEdge*) ELS->Objs[i];
		if ((pEE->pVertex[0] == pN) || (pEE->pVertex[1] == pN))
		{
			vDir.x = pEE->pVertex[1]->Pt_Point->x - pEE->pVertex[0]->Pt_Point->x;
			vDir.y = pEE->pVertex[1]->Pt_Point->y - pEE->pVertex[0]->Pt_Point->y;
			vDir.z = pEE->pVertex[1]->Pt_Point->z - pEE->pVertex[0]->Pt_Point->z;
			vDir.Normalize();
			vN = vDir.Cross(vZ);
			vRet.x += vN.x;
			vRet.y += vN.y;
			vRet.z += vN.z;
			dC += 1.0;
		}

	}
	double dS;
	dS = 1 / dC;
	vRet *= dS;
	vRet.Normalize();
	return (vRet);
}

double DBase::DirCheck(C3dVector vN, ObjList* ELS)
{
	double dRet = 1;
	double dDot;
	C3dVector vEC;
	C3dVector vEd;
	C3dVector vNe;
	C3dVector vNc;
	ObjList* pEls = new ObjList();
	eEdge* eE = NULL;
	//find edge
	eE = (eEdge*)ELS->Objs[0];
	pCurrentMesh->RelTo(eE->pVertex[0], pEls,3);
	if (pEls->iNo > 0)
	{
		vEC = pEls->Objs[0]->Get_Centroid();
		vEC -= eE->pVertex[0]->Get_Centroid();
		vEd = eE->pVertex[1]->Get_Centroid();
		vEd-= eE->pVertex[0]->Get_Centroid();
		vEC.Normalize();
		vEd.Normalize();
		vNc = vEd.Cross(vEC);
		vNe = vEd.Cross(vN);
		dDot = vNc.Dot(vNe);
		if (dDot > 0)
			dRet = -1;
	}
	else
	{
		outtext1("ERROR: Sweep direction could not be calculated.");
	}
	delete (pEls);
	return(dRet);
}
//*********************************************************************************
// Pre: Valid OML fronts=
// Post: Angle between adjacent segements calculated and stored on the front
//*********************************************************************************
void DBase::CalcAngles(cLinkedList* NDF)
{
	c2dFront* pF = (c2dFront*)NDF->Head;
	c2dFront* pFB = (c2dFront*) NDF->Head;
	c2dFront* pFN = (c2dFront*) NDF->Head;
	//Scip first node as no other element
	pF = (c2dFront*) pF->next;
	C3dVector vA, vB, vC;
	C3dVector v1, v2;
	double dAng;
	while ((pF != NULL) && (pF->next !=NULL))
	{
		pFB = (c2dFront*)pF->before;
		vA = pFB->fNodes->Head->Get_Centroid();
		vB = pF->fNodes->Head->Get_Centroid();
		pFN = (c2dFront*) pF->next;
		vC = pFN->fNodes->Head->Get_Centroid();
		v1 = vA;
		v1 -= vB;
		v2 = vC;
		v2 -= vB;
		v1.Normalize();
		v2.Normalize();
		dAng = acos(v1.Dot(v2))*57.2957795130931;
		pF->dA = dAng;
		pF = (c2dFront*)pF->next;
	}
}

double DBase::CalcAngle(BOOL bL, Node* pN, ObjList* NList)
{
	int i;
	int iB, iA;
	int ind = -1;
	double dRet = 180;
	C3dVector vA, vB, vC;
	C3dVector v1, v2;
	for (i = 0; i < NList->iNo;i++)
	{
		if (NList->Objs[i] == pN)
		{
			ind = i;
			break;
		}
	}
	if (bL)
	{
		if ((ind > 0) && (ind < NList->iNo - 1))
		{
			iB = ind - 1;
			iA = ind + 1;
		}
		else if (ind == 0)
		{
			iB = NList->iNo - 1;
			iA = ind + 1;
		}
		else if (ind == NList->iNo - 1)
		{
			iB = ind - 1;
			iA = 0;
		}
		else
		{
			ind = 0;
			iA = 0;
			iB = 0;
		}
		vC = NList->Objs[ind]->Get_Centroid();
		vA = NList->Objs[iA]->Get_Centroid();
		vB = NList->Objs[iB]->Get_Centroid();
		v1 = vA;
		v2 = vB;
		v1 -= vC;
		v2 -= vC;
		v1.Normalize();
		v2.Normalize();
		double dDot;
		dDot = v1.Dot(v2);
		if (dDot > 1) 
			dDot = 1;
		if (dDot<-1)
			dDot = -1; 
		dRet = acos(dDot) * 57.2957795130931;
	}
	else
	{
		if ((ind > 0) && (ind < NList->iNo - 1))
		{
			iB = ind - 1;
			iA = ind + 1;
			vC = NList->Objs[ind]->Get_Centroid();
			vA = NList->Objs[iA]->Get_Centroid();
			vB = NList->Objs[iB]->Get_Centroid();
			v1 = vA;
			v2 = vB;
			v1 -= vC;
			v2 -= vC;
			v1.Normalize();
			v2.Normalize();
			double dDot;
			dDot = v1.Dot(v2);
			if (dDot > 1)
				dDot = 1;
			if (dDot < -1)
				dDot = -1;
			dRet = acos(dDot) * 57.2957795130931;
		}
	}

	return(dRet);
}


//*********************************************************************************
// Pre: Valid OML fronts=
// Post: Front nodes extruded according to PID
//*********************************************************************************
void DBase::GenFronts(cLinkedList* NDF,int iDir)
{
	int i;
	double t = 0.2;
	c2dFront* pF = (c2dFront*) NDF->Head;
	Node* pBN; 
	Node* pNN;
	C3dVector vBN;
	C3dVector vUp;
	C3dVector vNewNd;
	ME_Object* ME = pCurrentMesh;
	double dCorr = 1;
	PCOMPG* pC;
	int iPID;
	int iNoLay;
	double dTotThk = 0;
	double dDir;
	if (iDir == 0)
		dDir = -1;
	else
		dDir = 1;
	while (pF != NULL)
	{
		iPID = pF->iPID;
		pC =(PCOMPG*) PropsT->GetItem(iPID);
		dTotThk = 0;
		if (pC != NULL)
		{
			dCorr = 1 / sin(0.017453*(pF->dA / 2));
			iNoLay = pC->iNoLays;
			pBN = (Node*)pF->fNodes->Head;
			pBN->iColour = 10; //Using colour to identify g ply id as dont want to add to m3d
			vBN = pBN->Get_Centroid();
			vUp = pF->vN;
			//New Nodes
			for (i = 0; i < iNoLay; i++)
			{
				dTotThk += pC->T[i];
				vNewNd = vBN;
				vNewNd += vUp * dTotThk * dCorr;
				pNN = ME->AddNode(vNewNd, ME->iNodeLab, -1, -1, 124, 0, 0);
				ME->iNodeLab++;
				pNN->iColour = pC->GPLYID[i] + 10;
				pF->fNodes->Add(pNN);
			}
		}
		pF = (c2dFront*) pF->next;
	}
}

//*********************************************************************************
// Pre: Intersecting moveable front
// Post: Front moved
//*********************************************************************************
BOOL  DBase::MoveFront(c2dFront* pMF)
{
	BOOL bRC = FALSE;
	c2dFront* pBefore;
	c2dFront* pAfter;
	pBefore = (c2dFront*) pMF->before;
	pAfter = (c2dFront*) pMF->next;
	Node* pNB;
	Node* pNM;
	Node* pNA;
	C3dVector vMid;
	C3dVector vT;
	if ((pBefore != NULL) && (pAfter != NULL))
	{
		if ((pBefore->fNodes->iCnt == pMF->fNodes->iCnt) && (pAfter->fNodes->iCnt == pMF->fNodes->iCnt))
		{
			pNB = (Node*) pBefore->fNodes->Head;
			pNM = (Node*) pMF->fNodes->Head;
			pNA = (Node*) pAfter->fNodes->Head;
			while (pNM != NULL)
			{
				vMid = pNB->Get_Centroid();
				vT = pNA->Get_Centroid();
				vMid += vT;
				vMid *= 0.5;
				pNM->Pt_Point->Set(vMid.x, vMid.y, vMid.z);
				pNB = (Node*) pNB->next;
				pNM = (Node*) pNM->next;
				pNA = (Node*) pNA->next;
			}
		}

	}
	return (bRC);
}

//*********************************************************************************
// Pre: GenFronts has been executed
// Post: Nodal fronts checked for intersections and moved or deleted to correct
//*********************************************************************************
void DBase::ChkIntersects(cLinkedList* NDF)
{
	//This would be called recursivly until no intersections
	//Only doing it once for this demo
	c2dFront* pF1 = (c2dFront*)NDF->Head;
	c2dFront* pF2;
	c2dFront* pMF; 
	C3dVector S1a;
	C3dVector S1b;
	C3dVector S2a;
	C3dVector S2b;
	C3dVector I0;
	C3dVector I1;
	BOOL bOK;
	int iInt;
	while (pF1->next != NULL)
	{
		pF2 = (c2dFront*)pF1->next;
		S1a = pF1->fNodes->Head->Get_Centroid();
		S1b = pF1->fNodes->pCur->Get_Centroid();
		S2a = pF2->fNodes->Head->Get_Centroid();
		S2b = pF2->fNodes->pCur->Get_Centroid();

		iInt = intersect2D_2Segments(S1a, S1b, S2a, S2b, &I0, &I1);
		if (iInt == 1)
		{
			pMF = NULL;
			//We have a front intersection need to move or delete on move implemented here
			if (pF1->dA > pF2->dA)		//Find the front to move
				pMF = pF1;
			else
				pMF = pF2;
			if (pMF != NULL)
				bOK=MoveFront(pMF);     //This will move the front to middle of adjacent fronts
		}
		pF1 = pF2;
	}
}

//*********************************************************************************
// Pre: Valid fronts
// Post: Elements generated between front
//*********************************************************************************
void DBase::GenElements(cLinkedList* NDF)
{
	Node *pENodes[100];
	c2dFront* pF1 = (c2dFront*) NDF->Head;
	c2dFront* pF2;
	Node* p1;
	Node* p2;
	Node* p3;
	Node* p4;
	Node* p43;
	E_Object* pEL;
	while (pF1->next != NULL)
	{
		pF2 = (c2dFront*) pF1->next;
		if (pF1->fNodes->Head != NULL)
		{
			p1 = (Node*) pF1->fNodes->Head;
			while (p1->next != NULL)
			{
				p2 = (Node*) p1->next;
				p3 = pF2->GetNodeByGID(p2->iColour);
				p4 = pF2->GetNodeByGID(p1->iColour);
				p43 = pF2->isSegBet(p1->iColour, p2->iColour);	//Check for ply addition
				if (p43 != NULL)
				{
					//Create the transition TRI
					pENodes[0] = p1;
					pENodes[1] = p4;
					pENodes[2] = p43;
					if ((p1 != NULL) && (p43 != NULL) && (p4 != NULL))
					{
						pEL = pCurrentMesh->AddEl(pENodes, pCurrentMesh->iElementLab, 74, 91, 1, 1, 3, 0, 0, 0, 0, -1, 0);
						//pEL->Reverse();
						pCurrentMesh->iElementLab++;
					}
					p4 = p43;
				}
				pENodes[0] = p1;
				pENodes[1] = p4;
				pENodes[2] = p3;
				pENodes[3] = p2;
				//we have 4 nodes create a QUAD
				if ((p1 != NULL) && (p2 != NULL) && (p3 != NULL) && (p4 != NULL))
				{
					pEL = pCurrentMesh->AddEl(pENodes, pCurrentMesh->iElementLab, 74, 94, 1, 1, 4, 0, 0, 0, 0, -1, 0);
					pCurrentMesh->iElementLab++;
				}
				p1 = p2;				//Advance along the front
			}
		}
		pF1 = pF2;						//Advance the fronts
	}
}

//*********************************************************************************
// Pre: Valid fronts
// Post: Elements generated between front
//*********************************************************************************
void DBase::GenElements2(BOOL bL,ObjList* NF1, ObjList* NF2)
{
	Node* pENodes[100];
	int i;
	Node* p1;
	Node* p2;
	Node* p3;
	Node* p4;
	E_Object* pEL;
	for (i=0;i<NF1->iNo-1;i++)
	{

		p1 = (Node*) NF1->Objs[i];
		p2 = (Node*) NF1->Objs[i+1];
		p3 = (Node*)NF2->Objs[i + 1];
		p4 = (Node*)NF2->Objs[i];
        pENodes[0] = p1;
		pENodes[1] = p4;
		pENodes[2] = p3;
		pENodes[3] = p2;
        pEL = pCurrentMesh->AddEl(pENodes, pCurrentMesh->iElementLab, 74, 94, 1, 1, 4, 0, 0, 0, 0, -1, 0);
		pCurrentMesh->iElementLab++;
	}
	if (bL) //last elemen
	{
		p1 = (Node*)NF1->Objs[NF1->iNo - 1];
		p2 = (Node*)NF1->Objs[0];
		p3 = (Node*)NF2->Objs[0];
		p4 = (Node*)NF2->Objs[NF1->iNo - 1];
		pENodes[0] = p1;
		pENodes[1] = p4;
		pENodes[2] = p3;
		pENodes[3] = p2;
		pEL = pCurrentMesh->AddEl(pENodes, pCurrentMesh->iElementLab, 74, 94, 1, 1, 4, 0, 0, 0, 0, -1, 0);
		pCurrentMesh->iElementLab++;
	}
}

//*********************************************************************************
// Pre: Valid fronts and resulting element colour
// Post: Elements generated 
//*********************************************************************************
void DBase::GenBEamElements(cLinkedList* NDF,int iCOl)
{
	Node *pENodes[100];
	Node* p1;
	Node* p2;
	E_Object* pEL;
	p1 = (Node*) NDF->Head;
	while (p1->next != NULL)
	{
		p2 = (Node*) p1->next;
        pENodes[0] = p1;
		pENodes[1] = p2;
        if ((p1 != NULL) && (p2 != NULL))
        {
           pEL = pCurrentMesh->AddEl(pENodes, pCurrentMesh->iElementLab, iCOl, 21, -1, -1, 2, 0, 0, 0, 0, -1, 0);
           pCurrentMesh->iElementLab++;
		   AddTempGraphics(pEL);
		   Dsp_Add(pEL);
        }	
		p1 = p2;
	}
}

//*********************************************************************************
// Pre: True
// Post: Test PCOMPG's generated
//*********************************************************************************
void DBase::CreatTestPCOMPS()
{
	//This would normaly be done in the GUI
	//TEST PCOMPG LAYUP PID1
	outtext1("Piggy Piggy");
	PCOMPG* p1 = new PCOMPG();
	p1->sTitle = "APCOMP";
	//aaaa
	p1->iID = 1;
	p1->AddLayer(1, 1, 0.3, 45.0, 0);
	p1->AddLayer(2, 2, 0.2, 0.0, 0);
	p1->AddLayer(4, 2, 0.3, -45.0, 0);
	PropsT->AddItem(p1);
	outtext1("New PCOMPG Created.");
	//TEST PCOMPG LAYUP PID2
	p1 = new PCOMPG();
	p1->sTitle = "PCOMPG1";
	p1->iID = 2;
	p1->AddLayer(1, 1, 0.3, 45.0, 0);
	p1->AddLayer(2, 2, 0.2, 0.0, 0);
	p1->AddLayer(3, 1, 0.4, 90.0, 0);
	p1->AddLayer(4, 2, 0.3, -45.0, 0);
	PropsT->AddItem(p1);
	outtext1("New PCOMPG Created.");
	p1 = new PCOMPG();
	p1->sTitle = "PCOMPG1";
	p1->iID = 3;
	p1->AddLayer(1, 1, 0.06, 45.0, 0);
	p1->AddLayer(2, 2, 0.04, 0.0, 0);
	p1->AddLayer(3, 2, 0.06, -45.0, 0);
	PropsT->AddItem(p1);
	outtext1("New PCOMPG Created.");
}

//*********************************************************************************
//*******************  M A I N  P R O C E D U R E *********************************
//*********************************************************************************
//
//*********************************************************************************
// Pre: User selected 1d elements to extrude and direction indicator
//		Test pcomp mush have aready been created by calling "TEST"
// Post: 1d elements extruded to 2d based on attached PCOMPG
//*********************************************************************************
void DBase::ElSweepB(ObjList* Items,double dDist, int iNo)
{

	char S1[80];
	double dDir = 1;
	int i,j,k,m;
	int iDir = 1;
	C3dVector vNarray[10000];
	double dAngarray[10000];
	BOOL bStop = FALSE; 
	BOOL bLoop = FALSE;
	C3dVector vA;
	C3dVector vN;
	C3dVector vNd;
	eEdge* Ed=NULL;
	eEdge* EC = NULL;
	ObjList* ELF = new ObjList();
	ObjList* EFALL = new ObjList();
	ObjList* NDF1 = new ObjList();
	ObjList* NDF2 = new ObjList();
	double dCorr;
	int iCC = 0;
	double dA;
	dDist /= iNo;

	// Find all nodes on the OML and store as nodal front in linked list NDF
	// Need to items supplied to PROC are elements and are 1d should also
	// chain the 1d element to make sure are continuous
	if (Items->iNo > 0)  
	{
		for (i = 0; i < Items->iNo; i++)		//For all selected items
		{
			if (Items->Objs[i]->iObjType == 8)	//Check its an edges
			{
				Ed = (eEdge*) Items->Objs[i];
				EFALL->Add(Ed);  //All edges stored in ELF
			}
		}
		while (EFALL->iNo > 0)
		{
			BOOL bFirst = TRUE;
			bStop = FALSE;
			ELF->Clear();
			Ed = (eEdge*) EFALL->Objs[0]; //The edge to chain
			ELF->Add(Ed);
			EFALL->Remove(Ed);
			while (!bStop)
			{   //Forward direction from N2
				bStop = TRUE;
				iCC = 0;
				while (iCC< EFALL->iNo)
				{
					EC = (eEdge*) EFALL->Objs[iCC];
					if (EC->pVertex[0] == Ed->pVertex[1])
					{
						ELF->Add(EC);
						Ed = EC;
						EFALL->Remove(EC);
						iCC=0;
						bStop = FALSE;
						break;
					}
					else if (EC->pVertex[1] == Ed->pVertex[1])
					{
						EC->Reverse();
						ELF->Add(EC);
						Ed = EC;
						EFALL->Remove(EC);
						iCC = 0;
						bStop = FALSE;
						break;
					}
					iCC++;
				}
			}
			bLoop = FALSE;
			eEdge* ES = (eEdge*)ELF->Objs[0];
			eEdge* EE = (eEdge*)ELF->Objs[ELF->iNo - 1];
			if (ES->pVertex[0] == EE->pVertex[1])
				bLoop = TRUE;
			if (!bLoop)  
			{
				Ed = (eEdge*)ELF->Objs[0]; //The edge to chain
				bStop = FALSE;
				while (!bStop)
				{   //backward direction from N2
					bStop = TRUE;
					iCC = 0;
					while (iCC < EFALL->iNo)
					{
						EC = (eEdge*)EFALL->Objs[iCC];
						if (EC->pVertex[1] == Ed->pVertex[0])
						{
							ELF->InsertAt(0,EC);
							Ed = EC;
							EFALL->Remove(EC);
							iCC = 0;
							bStop = FALSE;
							break;
						}
						else if (EC->pVertex[0] == Ed->pVertex[0])
						{
							EC->Reverse();
							ELF->InsertAt(0,EC);
							Ed = EC;
							EFALL->Remove(EC);
							iCC = 0;
							bStop = FALSE;
							break;
						}
						iCC++;
					}
				}
			}



			//Create Node front
			NDF1->Clear();
			for (i = 0; i < ELF->iNo; i++)
			{
				eEdge* pEdge;
				pEdge = (eEdge*)ELF->Objs[i];
				sprintf_s(S1, "%i %i", pEdge->pVertex[0]->iLabel, pEdge->pVertex[1]->iLabel);
				outtext1(S1);

				if (bFirst)
				{
					NDF1->Add(pEdge->pVertex[0]);
					bFirst = FALSE;
				}
				NDF1->AddEx(pEdge->pVertex[1]);
			}
			outtext1("---");
			NDF2->Clear();
			bFirst = TRUE;

			for(j = 0; j < iNo; j++)
			{
				for (i = 0; i < NDF1->iNo; i++)
				{
					Node* pN = (Node*)NDF1->Objs[i];
					vNd = pN->Get_Centroid();
					if (j == 0)
					{
						vN = GetNodalNormal2(pN, ELF);
						vNarray[i] = vN;
						dA = CalcAngle(bLoop, pN, NDF1);
						dAngarray[i] = dA;
					}
					else
					{
						vN = vNarray[i];
						dA=dAngarray[i];
					}
					
					if (bFirst)
					{
						dDir = DirCheck(vN, ELF);
						bFirst = FALSE;
					}
					dCorr = 1 / sin(0.017453 * (dA / 2));
					vN *= dDir * dDist * dCorr;
					vNd += vN;
					NDF2->Add(pCurrentMesh->AddNode(vNd, pCurrentMesh->iNodeLab, -1, -1, 124, 0, 0));
					pCurrentMesh->iNodeLab++;
				}
				GenElements2(bLoop, NDF1, NDF2);		//Generate elements between fronts
				NDF1->Clear();
				//Smooth
				Node* nB;
				Node* nA;
				Node* nC;
				for (m = 0; m < 2; m++)
				{
					for (k = 0; k < NDF2->iNo ; k++)
					{
						if ((dAngarray[k] > 179) && (dAngarray[k] < 181))
						{
							if ((bLoop) && (k == 0))
							{
								nB = (Node*)NDF2->Objs[NDF2->iNo-1];
								nA = (Node*)NDF2->Objs[k + 1];
								nC = (Node*)NDF2->Objs[k];
								nC->Pt_Point->x = (nB->Pt_Point->x + nA->Pt_Point->x) / 2;
								nC->Pt_Point->y = (nB->Pt_Point->y + nA->Pt_Point->y) / 2;
								nC->Pt_Point->z = (nB->Pt_Point->z + nA->Pt_Point->z) / 2;
							}
							else if ((bLoop) && (k == NDF2->iNo - 1))
							{
								nB = (Node*)NDF2->Objs[k - 1];
								nA = (Node*)NDF2->Objs[0];
								nC = (Node*)NDF2->Objs[k];
								nC->Pt_Point->x = (nB->Pt_Point->x + nA->Pt_Point->x) / 2;
								nC->Pt_Point->y = (nB->Pt_Point->y + nA->Pt_Point->y) / 2;
								nC->Pt_Point->z = (nB->Pt_Point->z + nA->Pt_Point->z) / 2;
							}
							else if ((k>0) && (k< NDF2->iNo-1))
							{
								nB = (Node*)NDF2->Objs[k - 1];
								nA = (Node*)NDF2->Objs[k + 1];
								nC = (Node*)NDF2->Objs[k];
								nC->Pt_Point->x = (nB->Pt_Point->x + nA->Pt_Point->x) / 2;
								nC->Pt_Point->y = (nB->Pt_Point->y + nA->Pt_Point->y) / 2;
								nC->Pt_Point->z = (nB->Pt_Point->z + nA->Pt_Point->z) / 2;
							}
						}

					}
				}
				for (k=0;k<NDF2->iNo;k++)
				   NDF1->Add(NDF2->Objs[k]);
				NDF2->Clear();
				
			}
			InvalidateOGL();		//Invalidate graphics database
			ReDraw();				//Regen graphics database
		}
	}
	else
	{
		outtext1("ERROR: No edges selected.");
	}
	delete(ELF);
	delete(EFALL);
	delete(NDF1);
	delete(NDF2);
}


void DBase::MoveObjs(ObjList* Items,C3dVector tVec)
{
int i;
if (Items->iNo>0)
{
  for (i=0;i<Items->iNo;i++)
  {
	MoveObj(Items->Objs[i],tVec);
  }

  InvalidateOGL();
  ReGen();  
}
}

void DBase::MoveObj(G_Object* Item,C3dVector tVec)
{
C3dMatrix Glob2WP;
C3dMatrix WP2Glob;
C3dMatrix RotZ;
C3dVector v;
WP_Object* TWP = (WP_Object*) DB_Obj[0];
Glob2WP = TWP->mWPTransform;
WP2Glob=Glob2WP;

v.x=-Glob2WP.m_30;
v.y=-Glob2WP.m_31;
v.z=-Glob2WP.m_32;
Glob2WP.m_30=0;
Glob2WP.m_31=0;
Glob2WP.m_32=0;
Glob2WP.Transpose();

RotZ.Rotate(0,0,tVec.y);


if (Item!=NULL)
{
  if (TWP->iWPMode==0)
  {
    Item->Translate(v);
    Item->Transform(Glob2WP);
    Item->Translate(tVec);
    Item->Transform(WP2Glob);
  }
  else if (TWP->iWPMode==1)
  {
    Item->Translate(v);  //test
    Item->Transform(Glob2WP);
    tVec.y=0;
    Item->Transform(RotZ);
	  C3dVector vA = Item->Get_Centroid();
    vA=CartToCyl(vA);
	  vA.x=tVec.x;
    vA.z=tVec.z;
    vA=CylToCart(vA);
    Item->Translate(vA);
    Item->Transform(WP2Glob);
  }
}
}

void DBase::CurvesToSurface(ObjList* OL1,ObjList* OL2)
{
NSurf* pS;
NCurve* pC;
pS=NULL;
int i;
if (OL1->iNo>0)
{
  if ((OL1->Objs[0]->iObjType=15) ||
      (OL1->Objs[0]->iObjType=16) ||
      (OL1->Objs[0]->iObjType=17))
  {
    pS=(NSurf*) OL1->Objs[0];
  }
}
if (pS!=NULL)
{
  for (i=0;i<OL2->iNo;i++)
  {
    if ((OL2->Objs[i]->iObjType=7) ||
        (OL2->Objs[i]->iObjType=8) ||
        (OL2->Objs[i]->iObjType=9))
    {
      pC=(NCurve*) OL2->Objs[i];
      pS->AddTrimCurve(pC);
    }
  }

}
InvalidateOGL();
ReDraw();
}

void DBase::SurfUnTrim()
{
int iCO;
NSurf* pS;
  for (iCO=0;iCO<S_Count;iCO++)
  {
    if (S_Buff[iCO]->iObjType==15)
    {
      //sprintf_s(buff, "%s%4i","Meshing Surface : ",S_Buff[iCO]->iLabel ); 
	  //outtext1(buff);
      pS = (NSurf*) S_Buff[iCO];
      pS->DeleteExtTrimLoop();
	  pS->DeleteIntTrimLoop();
	}
  }
InvalidateOGL();
ReDraw();
}

void DBase::SurfaceTrim(ObjList* OL1,ObjList* OL2)
{
NSurf* pS;
pS=NULL;
int i;
if (OL1->iNo>0)
{
  if (OL1->Objs[0]->iObjType==15)
  {
    pS=(NSurf*) OL1->Objs[0];
  }
}
BOOL bErr=FALSE;
if (pS!=NULL)
{
  for (i=0;i<OL2->iNo;i++)
  {
    if ((OL2->Objs[i]->iObjType=13) && (OL2->Objs[i]->pParent==pS))
    {
    
    }
    else
    {
      bErr = TRUE;
    }
  }
  if (bErr==FALSE)
  {
     pS->UserTrim(OL2);
  }
  else
  {
    outtext1("ERROR: Curves Must Lie on the Same Surface.");
  }
}
}


void DBase::AddSurf()
{
BOOL bErr;
NSurf* pS = new NSurf();
pS->Create(-1,NULL);

int i;

for (i=0;i<S_Count;i++)
{
  if (S_Buff[i]->iObjType == 7)

  {
    pS->AddCV((NCurve*) S_Buff[i]);
  }
  else if (S_Buff[i]->iObjType == 13)
  {  
     NCurveOnSurf* pSS;
     pSS=(NCurveOnSurf*) S_Buff[i];
     pS->AddCV(pSS->GetSurfaceCVG(pSS->pParent));
  }
}
if (pS->iNoCvs > 1)
{
	bErr = pS->GenerateFit(2, 0, 1);
	pS->iLabel = iSFLabCnt;
	iSFLabCnt++;
}
else
{
	bErr = TRUE;
}

if (bErr==TRUE)
{
  delete(pS);
  outtext1("ERROR: Cannot Build Surface.");
  outtext1("Check Order and Number Off Points.");
}
else
{
	C3dVector pT;
	pT = pS->Get_Centroid();
	Matrix <C3dVector> Mat1;
	pS->deriveAt(0.5, 0.5, 1, Mat1);
	pT = Mat1(0, 0);
  AddObj(pS);
  ReDraw();
}

}

C3dMatrix DBase::CalcTranSsswep(C3dMatrix TMat,C3dVector vDir)
{
double dAng;
C3dMatrix OMat;
C3dMatrix TForm;
TForm=TMat.CalcTran(vDir);
dAng=TForm.GetZRot(TMat);
OMat.MakeUnit();
OMat.Rotate(0,0,dAng);
TForm=TForm*OMat;
return (TForm);
}

void DBase::SweepSurf(NCurve* pC,NCurve* pP,C3dMatrix TMatB,C3dVector vCO,C3dMatrix& TMat)
{
NCurve* pCn;
NCurve* pCn2;
C3dVector Dir;
C3dVector Loc;

double w;
double span;
int i;
double dStep;
int iSteps=10;

span=pP->we-pP->ws;
dStep=span/iSteps;
if (pP->iType==1)  //General curve cant deal with exactly
{
  for (i=0;i<=iSteps;i++)
  {
     w=i*dStep;
     Dir = pP->GetDir(w);
     TMat=CalcTranSsswep(TMat,Dir);
     Loc = pP->GetPt(w);
     pCn=(NCurve*) pC->Copy(NULL);
	 pCn->iLabel=iCVLabCnt;
     iCVLabCnt++;
     pCn->Translate(vCO);
     pCn->Transform(TMatB);
     pCn->Transform(TMat);
     pCn->Translate(Loc);
     AddObj(pCn);
  }
}
else if (pP->iType==2)  //Straigt line
{
     Dir = pP->GetDir(0.5);
     C3dVector vT;
     vT=pP->GetPt(1);
     vT-=pP->GetPt(0);
     TMat=CalcTranSsswep(TMat,Dir);
     Loc = pP->GetPt(pP->ws);
     pCn=(NCurve*) pC->Copy(NULL);
     pCn->iLabel=iCVLabCnt;
     iCVLabCnt++;
     pCn->Translate(vCO);
     pCn->Transform(TMatB);
     pCn->Transform(TMat);
     pCn->Translate(Loc);
     AddObj(pCn);
     Loc = pP->GetPt(pP->we);
     pCn2=(NCurve*) pC->Copy(NULL);
	 pCn2->iLabel=iCVLabCnt;
     iCVLabCnt++;
     pCn2->Translate(vCO);
     pCn2->Transform(TMatB);
     pCn2->Transform(TMat);
     pCn2->Translate(Loc);
     AddObj(pCn2);
     NSurfE* pPE = new NSurfE();
     pPE->Create(pCn,pCn2,vT,iSFLabCnt,NULL);
     iSFLabCnt++;
     pPE->iColour=pC->iColour;
     pPE->Generate(1,0,1);
     AddObj(pPE);
}
else if (pP->iType==3)  //Circle  can deal with exactly
{
     C3dMatrix mG;
     NSurfR* pS = new NSurfR();
     NCircle* pCir = (NCircle*) pP;
     mG.MakeUnit();
     C3dVector vN,vX,vY,vC;
     vC=pCir->Get_Centroid();
     vX=pCir->GetPt(0);
     vY=pCir->GetPt(0.25);
     vX-=vC;
     vY-=vC;
     vX.Normalize();
     vY.Normalize();
     vN=vX.Cross(vY);
     Dir = pCir->GetDir(0);
     Loc = pCir->GetPt(0);
     Dir.Normalize();
     vY=Dir.Cross(vX);
     TMat=CalcTranSsswep(TMat,Dir);
     //TMat.Transpose();
     pCn=(NCurve*) pC->Copy(NULL);
	 pCn->iLabel=iCVLabCnt;
     iCVLabCnt++;
     pCn->Translate(vCO);
     pCn->Transform(TMatB);
     pCn->Transform(TMat);
     pCn->Translate(Loc);
     AddObj(pCn);
     pS->CreateRev(pCn,vN,vC,vX,iSFLabCnt,NULL);
	 iSFLabCnt++;
     pS->iColour=pC->iColour;
     BOOL bErr=pS->Generate(2,pP->ws,pP->we);
     AddObj(pS);
}

}


void DBase::AddSurfSweep(ObjList* pC,ObjList* pP)
{
int i,j;
NCurve* pSC;
NCurve* pPC;
NCurve* pFC;
NCurve* pFP;
ObjList* PCurves = new ObjList();
PCurves->Clear();

C3dMatrix TMat;
C3dMatrix TMatUp;
TMat.MakeUnit();
C3dVector vO;
C3dVector vX;
C3dVector vY;
C3dVector vYo;
vYo.Set(0,1,0);
C3dVector vUp;
C3dVector vZ;
if ((pC->iNo>0) && (pP->iNo>0))
{
    for (i=0;i<pP->iNo;i++)
    {
       pSC=(NCurve*) pP->Objs[i]->Copy(NULL);
       PCurves->Add(pSC);
    }
    BOOL   bErr=ChainPath(PCurves);
    pFC=(NCurve*) pC->Objs[0];
    pFP=(NCurve*) PCurves->Objs[0];
    vO=pFP->GetPt(0);
    vY=pFC->GetPt(0.5);
    vY-=vO;
    vZ=pFP->GetDir(0);
    vY.Normalize();
    vZ.Normalize();
    vX=vY.Cross(vZ);
    vX.Normalize();
    vY=vZ.Cross(vX);
    TMat.SetColVec(1,vX);
    TMat.SetColVec(2,vY);
    TMat.SetColVec(3,vZ);
    TMatUp=TMat;   
    TMat.Transpose();
    
    for (i=0;i<PCurves->iNo;i++)
    {
      pPC=(NCurve*) PCurves->Objs[i];
      for (j=0;j<pC->iNo;j++)
      {
        pSC=(NCurve*) pC->Objs[j];
        SweepSurf(pSC,pPC,TMat,-vO,TMatUp);
        
      }
    }


  for (i=0;i<PCurves->iNo;i++)
  {
     delete (PCurves->Objs[i]);
  }
  ReDraw();

}
delete(PCurves);
}


void DBase::Extract(ObjList* pPObjs)
{

	int iCO;
	
	for (iCO = 0; iCO < pPObjs->iNo; iCO++)
	{
		if (pPObjs->Objs[iCO]->iObjType == 15) 
		{
			if (pPObjs->Objs[iCO]->pParent != NULL)
			{
				NSurf* pCopy = (NSurf*) pPObjs->Objs[iCO]->Copy(NULL);
				pCopy->iLabel = iSFLabCnt;
				pCopy->iColour = 4;
				pCopy->NullCurveRef();
				iSFLabCnt++;
				AddObj(pCopy);
			}
		}
		else if (pPObjs->Objs[iCO]->iObjType == 7)
		{
			if (pPObjs->Objs[iCO]->pParent != NULL)
			{
				NCurve* pCopy = (NCurve*) pPObjs->Objs[iCO]->Copy(NULL);
				pCopy->iLabel = iCVLabCnt;
				pCopy->iColour = 5;
				pCopy->NullPointRef();
				iCVLabCnt++;
				AddObj(pCopy);
			}
		}
		else if (pPObjs->Objs[iCO]->iObjType == 0)
		{
			if (pPObjs->Objs[iCO]->pParent != NULL)
			{
				G_Object* pCopy = pPObjs->Objs[iCO]->Copy(NULL);
				pCopy->iLabel = iPtLabCnt;
				pCopy->iColour = 124;
				iPtLabCnt++;
				AddObj(pCopy);
			}
		}
	}
}

void DBase::Solve()
{
//#ifdef _DEBUG
//   oldMemState.Checkpoint();
//#endif 
if (pCurrentMesh!=NULL)
{
  int iC=pCurrentMesh->pSOLS->iCur;
  if (iC!=-1)
  {
	if (pCurrentMesh->pSOLS->pSols[iC]->iType == 0)
	  pCurrentMesh->IterSol3dLin(PropsT, MatT);
    else if (pCurrentMesh->pSOLS->pSols[iC]->iType==1)
      pCurrentMesh->IterSol1dSS(PropsT,MatT);
	else if (pCurrentMesh->pSOLS->pSols[iC]->iType == 2)
		pCurrentMesh->Test(PropsT, MatT);  //pCurrentMesh->ExplicitSolTest(PropsT, MatT);
  }
else
{
  outtext1("ERROR: No Solution is Active.");
}
}

//#ifdef _DEBUG
//   newMemState.Checkpoint();


//if( diffMemState.Difference( oldMemState, newMemState ) )
//{
//  TRACE( "Memory leaked!\n" );
//  diffMemState.DumpStatistics();
//}
//#endif
}

void DBase::ListAllProps()
{
  outtext1("PROPERTY LISTING:-");
if (pCurrentMesh!=NULL)
{
  PropsT->ListAll();
}
}

void DBase::ListSolutions()
{
  if(pCurrentMesh!=NULL)
  {
    if (pCurrentMesh->pSOLS!=NULL)
    {
      pCurrentMesh->pSOLS->Info();
    }
    else
    {
      outtext1("ERROR: No Solutions Defined.");
    }
  }
}

void DBase::AddSolutions(CString sT,int iSol,double dT)
{
  if(pCurrentMesh!=NULL)
  {
    if (pCurrentMesh->pSOLS!=NULL)
    {
      pCurrentMesh->pSOLS->AddSolution(iSol,sT,dT);
    }
  }

}

BOOL DBase::isValidLCid(int iLC)
{
BOOL brc=FALSE;
if(pCurrentMesh!=NULL)
{
  brc=pCurrentMesh->isValidLCid(iLC);
}
return (brc);
}

BOOL DBase::isValidBCid(int iLC)
{
BOOL brc=FALSE;
if(pCurrentMesh!=NULL)
{
  brc=pCurrentMesh->isValidBCid(iLC);
}
return (brc);
}

BOOL DBase::isValidTCid(int iLC)
{
BOOL brc=FALSE;
if(pCurrentMesh!=NULL)
{
  brc=pCurrentMesh->isValidTCid(iLC);
}
return (brc);
}

BOOL DBase::isActiveSolSet()
{
BOOL brc=FALSE;
if(pCurrentMesh!=NULL)
{
  brc=pCurrentMesh->isActiveSolSet();
}
return (brc);
}

void DBase::AddStep(CString sT,int iLC,int iBC,int iTC,BOOL bRS)
{
if(isActiveSolSet())
{
  pCurrentMesh->pSOLS->AddStep(sT,iLC,iBC,iTC,bRS);
}
}


void DBase::ListAllMats()
{
  outtext1("MATERIAL LISTING:-");
if (pCurrentMesh!=NULL)
{
  MatT->ListAll();
}
}


E_Object* DBase::AddEl(int iPos,BOOL AddDsp)
{
int iNo=pCurrentMesh->GetNoNode(iCurElemType);
BOOL bChk = TRUE;
E_Object* cAddedEl;
Node *pENodes[MaxSelNodes];
cAddedEl=NULL;
int i;
char S1[80];
CString OutT;
if ((S_Count-iPos!=iNo) && (iCurElemType!=122))
{
  BOOL bChk = FALSE;
}
else if ((S_Count-iPos<2) && (iCurElemType==122))
{
  BOOL bChk = FALSE;
}
iNo=S_Count-iPos;
if (bChk==TRUE)
{
//Check to see if all nodes are in cur mesh

  for (i=0;i<iNo;i++)
  {
    if (S_Buff[i]->iObjType==1)
	  {
	    pENodes[i]=(Node*) S_Buff[i];
		if (pCurrentMesh->sName != "NULL")
		{
			if (S_Buff[i]->pParent != pCurrentMesh)
			{
				bChk = FALSE;
			}
		}
	  }
	  else
      {
	    bChk=FALSE;
	  }
	
  }
Node* cAddedNode;
if (bChk==TRUE)
{
  pCurrentMesh->MaxLab();
  if (iCurElemType==1000)
  {
     C3dVector n1,n2,cN;
     n1=pENodes[0]->Get_Centroid();
     n2=pENodes[2]->Get_Centroid();
     cN*=0;
     cN+=n1;
     cN+=n2;
     cN*=0.5;
     iNo=5;
     cAddedNode=pCurrentMesh->AddNode(cN, pCurrentMesh->iNodeLab,0,0,124,0,0);
		 pCurrentMesh->iNodeLab++;
		 Dsp_Add(cAddedNode);
     pENodes[4]=pENodes[3];
     pENodes[3]=pENodes[2];
     pENodes[2]=pENodes[1];
     pENodes[1]=pENodes[0];
     pENodes[0]=cAddedNode;
  }
  

  cAddedEl = pCurrentMesh->AddEl(pENodes,pCurrentMesh->iElementLab,44,iCurElemType,-1,-1,iNo,1,1,1,AddDsp,-1,0); 
  outtext2("//LAB");
  for (i = 0; i < iNo; i++)
  {
	  sprintf_s(S1, "//%i", pENodes[i]->iLabel);
	  outtext2(S1);
  }
  outtext2("//D");
  //Check solids for correct orientation


  pCurrentMesh->iElementLab++;
  cAddedEl->SetToScr(&pModelMat,&pScrMat);
  AddTempGraphics(cAddedEl);
  Dsp_Add(cAddedEl);

}
else
{
  outtext1("ERROR: No Element Created - Check Current Mesh");
}
}

return (cAddedEl);
}

E_Object* DBase::InsSpringEl(int iPos, BOOL AddDsp)
{
	int iNo = pCurrentMesh->GetNoNode(iCurElemType);
	int i;
	E_Object* cAddedEl;
	E_ObjectR* pELP=NULL;
	E_Object* pOE=NULL;
	Node* pENodes[MaxSelNodes];
	Node* pNP = NULL;
	Node* pNS = NULL;
	Node* pNewN = NULL;
	ObjList* pList = new ObjList();
	pList->Clear();
	cAddedEl = NULL;
	char S1[80];
	CString OutT;
	ME_Object* pMesh=NULL;

	if (S_Buff[S_Count-1]->iObjType == 1)
	{
		pNP = (Node*) S_Buff[S_Count - 1];
		pMesh = (ME_Object*)pNP->pParent;
		pNewN = (Node*)pNP->Copy(pMesh);
		pNewN->iLabel = pMesh->iNodeLab;
		pMesh->iNodeLab++;
		if (pMesh->iNdNo < MAX_FESIZE)
		{
			pMesh->pNodes[pMesh->iNdNo] = pNewN;
			pMesh->iNdNo++;
		}
		else
		{
			outtext1("ERROR: Max node limit exceeded.");
			delete(pNewN);
			pNewN = NULL;
		}
		pMesh->RelTo(pNP, pList, 3);
		if (pList->iNo > 1)
		{
			//Find primary element must be type 122 and with centre bide

				for (i = 0; i < pList->iNo; i++)
				{
					pELP = (E_ObjectR*)pList->Objs[i];
					if ((pELP->iType == 122) && (pELP->pVertex[0] != pNP))
					{
						pELP->RepNodeInEl(pNP, pNewN);
					}
				}
			
		}
	}
	else
	{
		outtext1("ERROR: No mesh attached.");
	}
	

	if ((pNP!=NULL) && (pNewN != NULL) && (pMesh != NULL))
	{
		pENodes[0] = pNP;
		pENodes[1] = pNewN;
		cAddedEl = pMesh->AddEl(pENodes, pCurrentMesh->iElementLab, 124, 136, -1, -1, 2, 1, 1, 1, AddDsp, -1, 0);
		pCurrentMesh->iElementLab++;
		cAddedEl->SetToScr(&pModelMat, &pScrMat);
		AddTempGraphics(cAddedEl);
		Dsp_Add(cAddedEl);
		sprintf_s(S1, "Element %i created between nodes %i %i", cAddedEl->iLabel, pNP->iLabel, pNewN->iLabel);
		outtext1(S1);
	}
	else
	{
		outtext1("ERROR: No Element Created");
	}
	pList->Clear();
	delete (pList);
	pList = NULL;
	return (cAddedEl);
}






int DBase::AddEl2(int pVnode[MaxSelNodes], int iLab,int iCol,int iType,int iPID,int iMat, int iNoNodes,int A,int B,int C)
{
E_Object* cAddedEl;
Node *pENodes[100];
int iCnt;
if (pCurrentMesh != NULL)
  {
  for (iCnt = 0; iCnt < iNoNodes; iCnt ++)
  {
    pENodes[iCnt] = pCurrentMesh->GetNode(pVnode[iCnt]);
  }
  cAddedEl = pCurrentMesh-> AddEl(pENodes,iLab,iCol,iType,iPID,iMat,iNoNodes,A,B,C,FALSE,-1,0); 
  cAddedEl->SetToScr(&pModelMat,&pScrMat);
  AddTempGraphics(cAddedEl);
  Dsp_Add(cAddedEl);
  OglDraw(DspFlags);
  }
return (1);
}





void DBase::SetPen(CDC* pDC,int iCol)
{
int iR = 255;
int iG = 0;
int iB = 0;

switch( iCol ) 
{
    case 1:
        iR = 255;iG = 0;iB = 0;
        break;
    case 2 :
        iR = 0;iG = 255;iB = 0;
        break;
    case 3 :
        iR = 0;iG = 0;iB = 255;
        break;
    case 4 :
        iR = 0;iG = 255;iB = 255;
        break;
    case 5 :
        iR = 0;iG = 0;iB = 0;
        break;
    case 6 :
        iR = 255;iG = 255;iB = 255;
        break;
    case 7 :
        iR = 0;iG = 0;iB = 0;
        break;
}

if (pDC!=NULL)
{
  pDC->SelectStockObject(NULL_BRUSH);
  Pen = new CPen(PS_SOLID,2,RGB(iR,iG,iB));
  OldPen = pDC->SelectObject(Pen);
  //createpen
}
}

void DBase::RestorePen(CDC* pDC)
{
if (pDC!=NULL)
{
     pDC->SelectObject(OldPen);
     int t;
     t=Pen->DeleteObject();
}
  
}

void DBase::DrawDrag(CDC* pDC,CPoint p1,CPoint p2)
{
if (isBlackDisp())
  SetPen(pDC,6);
else
  SetPen(pDC,7);
pDC->Rectangle(p1.x,p1.y,p2.x,p2.y);
RestorePen(pDC);
}

void DBase::LineDrag(CDC* pDC, CPoint p1, CPoint p2)
{
	C3dVector vS, vE;
	C3dVector V;
	V.x = pModelMat.m_00 * vLS.x + pModelMat.m_01 * vLS.y + pModelMat.m_02 * vLS.z + pModelMat.m_30;
	V.y = pModelMat.m_10 * vLS.x + pModelMat.m_11 * vLS.y + pModelMat.m_12 * vLS.z + pModelMat.m_31;
	V.z = pModelMat.m_20 * vLS.x + pModelMat.m_21 * vLS.y + pModelMat.m_22 * vLS.z + pModelMat.m_32;
	vS.x = pScrMat.m_00 * V.x + pScrMat.m_01 * V.y + pScrMat.m_02 * V.z + pScrMat.m_30;
	vS.y = pScrMat.m_10 * V.x + pScrMat.m_11 * V.y + pScrMat.m_12 * V.z + pScrMat.m_31;
	vS.z = pScrMat.m_20 * V.x + pScrMat.m_21 * V.y + pScrMat.m_22 * V.z + pScrMat.m_32;
	
	V.x = pModelMat.m_00 * vLE.x + pModelMat.m_01 * vLE.y + pModelMat.m_02 * vLE.z + pModelMat.m_30;
	V.y = pModelMat.m_10 * vLE.x + pModelMat.m_11 * vLE.y + pModelMat.m_12 * vLE.z + pModelMat.m_31;
	V.z = pModelMat.m_20 * vLE.x + pModelMat.m_21 * vLE.y + pModelMat.m_22 * vLE.z + pModelMat.m_32;
	vE.x = pScrMat.m_00 * V.x + pScrMat.m_01 * V.y + pScrMat.m_02 * V.z + pScrMat.m_30;
	vE.y = pScrMat.m_10 * V.x + pScrMat.m_11 * V.y + pScrMat.m_12 * V.z + pScrMat.m_31;
	vE.z = pScrMat.m_20 * V.x + pScrMat.m_21 * V.y + pScrMat.m_22 * V.z + pScrMat.m_32;


	if (isBlackDisp())
		SetPen(pDC, 6);
	else
		SetPen(pDC, 7);
	pDC->MoveTo(vS.x, vS.y);
	pDC->LineTo(vE.x, vE.y);
	RestorePen(pDC);
}

void DBase::SetToScr2(C3dMatrix pM)
{

if (pCurrentMesh!=NULL)
  pCurrentMesh->SetToScr(&pM,&pScrMat);
}

BOOL DBase::isBlackDisp()
{
BOOL brc=FALSE;
  if (DspFlags & DSP_BLACK)
  {
    brc=TRUE;
  }
return (brc);
}

void DBase::Draw(C3dMatrix pM,CDC* pDC,int iDrawmode)
{

int iDB_I;

pModelMat=pM;
mOGLmat = pModelMat.GetOglMat();
if (iDspLstCount > 0)
{
	if (iDrawmode==4)
	{
      for (iDB_I = 0; iDB_I < iDspLstCount; iDB_I++)
      {
	    Dsp_List[iDB_I]->Drawn=1;
        Dsp_List[iDB_I]->SetToScr(&pModelMat,&pScrMat);
	  }
	}
	if ((DspFlags & DSP_LINE) > 0)
	{
		OglDrawW(DspFlags);
	}
	else
	{
		OglDraw(DspFlags);
	}
}
//Do the highlighting if its a full redraw
//or a user forced redraw 
if ((iDrawmode == 4) || (iDrawmode == 5))
{
	SetPen(pDC, 6);
	if (DspFlags & DSP_BLACK)
	{
		SetPen(pDC, 6);
	}
	else
	{
		SetPen(pDC, 7);
	}
	int iHC = 0;
	if (S_Count > 0)
	{
		iHC = S_Count;
		if ((iHLimit>-1) && (iHLimit < iHC))
			iHC = iHLimit;
		for (iDB_I = 0; iDB_I < iHC; iDB_I++)
		{
			if (S_Buff[iDB_I]->Drawn == 0)
			{
				S_Buff[iDB_I]->SetToScr(&pModelMat, &pScrMat);
			}
			S_Buff[iDB_I]->HighLight(pDC);
		}
	}
	//Highlight Points in the point Buffer
	C3dVector vPt;
	for (iDB_I = 0; iDB_I < DB_BuffCount; iDB_I++)
	{
		vPt=DB_PtBuff[iDB_I];
		vPt.SetToScr(&pModelMat, &pScrMat);
		pDC->Ellipse(int(vPt.x + 8), int(vPt.y + 8), int(vPt.x - 8), int(vPt.y - 8));
	}
	if (OTemp->iNo > 0)
	{
		iHC = OTemp->iNo;
		if ((iHLimit > -1) && (iHLimit < iHC))
			iHC = iHLimit;
		for (iDB_I = 0; iDB_I < iHC; iDB_I++)
		{
			OTemp->Objs[iDB_I]->HighLight(pDC);
		}
	}
	if (OTemp2->iNo > 0)
	{
		iHC = OTemp2->iNo;
		if ((iHLimit > -1) && (iHLimit < iHC))
			iHC = iHLimit;
		for (iDB_I = 0; iDB_I < iHC; iDB_I++)
		{
			OTemp2->Objs[iDB_I]->HighLight(pDC);
		}
	}

	RestorePen(pDC);
}


if (iDspLstCount > 0)
{
	if (iDrawmode == 4)
	{
		for (iDB_I = 0; iDB_I < iDspLstCount; iDB_I++)
		{
			Dsp_List[iDB_I]->Drawn = 0;
		}
	}
}

//#ifdef _DEBUG
//   newMemState.Checkpoint();
//#endif

//if( diffMemState.Difference( oldMemState, newMemState ) )
 //     {
 //       TRACE( "Memory leaked!\n" );
 //       diffMemState.DumpStatistics();
 //      }
}



void DBase::CalcMScl()
{
	C3dVector V1(0, 0, 0);
	C3dVector V2(1, 0, 0);
	V1 = pModelMat * V1;
	V1 = pScrMat * V1;
	V2 = pModelMat * V2;
	V2 = pScrMat * V2;
	V2 -= V1;
	dMFullScl = 0.1*dPixelSize / V2.Mag();

}

void DBase::Cycle()
{
	int i;
	int iExit = 0;
	int iDir = 1;
	i = iOGL_Start;
	CDC* pDC = pTheView->GetDC();
	InitOGL(pDC);

	//ReGen();
	do
	{
		iOGLList = i;
		if ((DspFlags & DSP_LINE) > 0)
		  this->OglDrawW(DspFlags);
		else
		  this->OglDraw(DspFlags);
		Sleep(ResFrameDelay);
		iExit++;
		i += iDir;
		if (i == iOGL_Start + iOGL_NoOff - 1)
			iDir = -1;
		if (i == iOGL_Start)
			iDir = 1;
	} while ((DspFlags & DSP_ANIMATION) == 0);
	pTheView->ReleaseDC(pDC);
	InvalidateOGL();
	BOOL OglErr;
	OglErr= wglDeleteContext(hrc);

}

void DBase::AnimatePosNeg()
{
  DspFlags = (DspFlags ^ DSP_ANIMPOSNEG);
  if ((DspFlags & DSP_ANIMPOSNEG) > 0)
  {
	  outtext1("Neg/Pos Animation is OFF");
  }
  else
  {
	  outtext1("Neg/Pos Animation is ON");
  }
}

void DBase::Animate()
{
	if ((DspFlags & DSP_ANIMATION) > 0)
	{
		InvalidateOGL();
		CycleFrames();
	}
	DspFlags = (DspFlags ^ DSP_ANIMATION);
  //bAnimate = FALSE;
  //InvalidateOGL();
  //ReGen();
}

void DBase::GenAnimationW(int iDspFlgs, int iNoFrames)
{
	int i;
	double dSF = 0;
	double dInc;

	if ((DspFlags & DSP_ANIMPOSNEG) > 0)
	{
		dSF = 0;
		dInc = 1.0 / (iNoFrames - 1);
		iOGL_NoOff = iNoFrames;
		iOGL_Start = -1;
		iOGL_Start = glGenLists(iNoFrames);
		iOGLList = iOGL_Start;
		for (i = iOGLList; i < iOGLList + iNoFrames; i++)
		{
			GenAnimationFrameW(iDspFlgs, i, dSF);
			dSF += dInc;
		}
	}
	else
	{
		dSF = -1;
		iNoFrames = 2 * iNoFrames + 1;
		dInc = 2.0 / (iNoFrames - 1);
		iOGL_NoOff = iNoFrames;
		iOGL_Start = -1;
		iOGL_Start = glGenLists(iNoFrames);
		iOGLList = iOGL_Start;
		for (i = iOGLList; i < iOGLList + iNoFrames; i++)
		{
			GenAnimationFrameW(iDspFlgs, i, dSF);
			dSF += dInc;
		}
	}
	this->ReDraw();
}

void DBase::GenAnimationFrameW(int iDspFlgs,int iFrameNo,double dF)
{
	int iDB_I;
	if (pCurrentMesh!=NULL)
	  pCurrentMesh->dResFactor = dF;  //Factor the results

	glNewList(iFrameNo, GL_COMPILE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	if (iDspLstCount > 0)
	{
		for (iDB_I = 0; iDB_I < iDspLstCount; iDB_I++)
		{
			Dsp_List[iDB_I]->OglDrawW(iDspFlgs, dMFullScl, 0);
		}
		TmpOGLCnt = 0;
	}
	glEndList();
}

void DBase::GenAnimationS(int iDspFlgs, int iNoFrames)
{
	int i;
	double dSF = 0;
	double dInc;

	if ((DspFlags & DSP_ANIMPOSNEG) > 0)
	{
		dSF = 0;
		dInc = 1.0 / (iNoFrames - 1);
		iOGL_NoOff = iNoFrames;
		iOGL_Start = -1;
		iOGL_Start = glGenLists(iNoFrames);
		iOGLList = iOGL_Start;
		for (i = iOGLList; i < iOGLList + iNoFrames; i++)
		{
			GenAnimationFrameS(iDspFlgs, i, dSF);
			dSF += dInc;
		}
	}
	else
	{
		dSF = -1;
		iNoFrames = 2 * iNoFrames + 1;
		dInc = 2.0 / (iNoFrames - 1);
		iOGL_NoOff = iNoFrames;
		iOGL_Start = -1;
		iOGL_Start = glGenLists(iNoFrames);
		iOGLList = iOGL_Start;
		for (i = iOGLList; i < iOGLList + iNoFrames; i++)
		{
			GenAnimationFrameS(iDspFlgs, i, dSF);
			dSF += dInc;
		}
	}
	this->ReDraw();
}

void DBase::GenAnimationFrameS(int iDspFlgs, int iFrameNo, double dF)
{
	int iDB_I;
	pCurrentMesh->dResFactor = dF;  //Factor the results

	glNewList(iFrameNo, GL_COMPILE);
	if (iDspLstCount > 0)
	{
		for (iDB_I = 0; iDB_I < iDspLstCount; iDB_I++)
		{
			Dsp_List[iDB_I]->OglDraw(iDspFlgs, dMFullScl, 0);
			if ((iDspFlgs & DSP_SHADED_EDGES) > 0)
			{
				Dsp_List[iDB_I]->OglDrawW(iDspFlgs, dMFullScl, 0);
			}
		}
		TmpOGLCnt = 0;
	}
	glEndList();
}

void DBase::OglDrawW(int iDspFlgs)
{

int i;
CalcMScl();
GLfloat		fMaxObjSize, fAspect;
GLfloat		fNearPlane, fFarPlane;
double dW;
double dH;
//MessageBoxA(0,(char*) glGetString(GL_VERSION), "OPENGL VERSION",0);
dWidth = mCView_Rect.right-mCView_Rect.left;
dHeight = mCView_Rect.bottom-mCView_Rect.top;
double dSize = dWidth;
if (dWidth > dHeight)
{
  dH = WPSize/2;
  dW = dH*dWidth/dHeight;
} 
else
{
  dW = WPSize/2;
  dH = dW*dHeight/dWidth;
} 
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  fAspect = 1.0f;
  fNearPlane = 3.0f;
  fFarPlane = 7.0f;
  fMaxObjSize = 3.0f;
  m_fRadius = fNearPlane + fMaxObjSize / 2.0f;
  glViewport(0,0,mCView_Rect.right,mCView_Rect.bottom);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

    //gluPerspective(45.0f, fAspect, fNearPlane, fFarPlane);
  glOrtho(-dW,dW,-dH,dH,-20*WPSize,20*WPSize);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE); 
  if (iDspFlgs & DSP_BLACK)
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  }
  else
  {
    glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMultMatrixf(mOGLmat.fMat);
  glEnable(GL_AUTO_NORMAL);
  //
  glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
  //glPixelStorei (GL_UNPACK_ALIGNMENT, 2);
  

  if (iOGLList == -1) 
  { 
	  //If animation is on generate multiple frames
	  if ((DspFlags & DSP_ANIMATION) == 0)
	  {
		  GenAnimationW(iDspFlgs, NoResFrame);
	  }
	  else
	  {
		  iOGL_NoOff = 1;
		  iOGL_Start = glGenLists(iOGL_NoOff);
		  iOGLList = iOGL_Start;
		  GenAnimationFrameW(iDspFlgs, iOGL_Start, 1.0);
	  }
  }

glCallList(iOGLList);
for (i=0;i<TmpOGLCnt;i++)
{
  TmpOGL[i]->OglDrawW(iDspFlgs,dMFullScl,0);
}
//Draw the dragging update
if ((pDragObj!=nullptr) && (bIsDrag==TRUE))
   pDragObj->OglDrawW(iDspFlgs, dMFullScl, 0);
 if ((DspFlags & DSP_GRAD) != 0)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glBegin(GL_QUADS);
    //  glColor3f(0.0,0.0,0.0);
    //  glVertex3f((float) -dW,(float) dH,-100);
    //  glColor3f((float) 0.0,(float) 0.0,(float) 0.2);
    //  glVertex3f((float) -dW,(float) -dH,-100);
    //  glColor3f((float) 0.0,(float) 0.0,(float) 0.5);
    //  glVertex3f((float) dW,(float) -dH,-100);
    //  glColor3f((float) 0.0,(float) 0.0,(float) 0.2);
    //  glVertex3f((float) dW,(float) dH,-100);
    //glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f((float)-dW, (float)dH, -100);
	glColor3f((float) 0.2, (float) 0.2, (float) 0.2);
	glVertex3f((float)-dW, (float)-dH, -100);
	glColor3f((float) 0.5, (float) 0.5, (float) 0.5);
	glVertex3f((float)dW, (float)-dH, -100);
	glColor3f((float) 0.2, (float) 0.2, (float) 0.2);
	glVertex3f((float)dW, (float)dH, -100);
	glEnd();
  }
glFlush();
glFinish();
SwapBuffers(wglGetCurrentDC());
}

 


void DBase::OglDraw(int iDspFlgs)
{

CalcMScl();
int i;
GLfloat		fMaxObjSize, fAspect;
GLfloat		fNearPlane, fFarPlane;
double dW;
double dH;

dWidth = mCView_Rect.right-mCView_Rect.left;
dHeight = mCView_Rect.bottom-mCView_Rect.top;

double dSize = dWidth;
if (dWidth > dHeight)
  {
	dH = WPSize/2;
	dW = dH*dWidth/dHeight;
  } 
else
  {
    dW = WPSize/2;
    dH = dW*dHeight/dWidth;
  }
 
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  fAspect = 1.0f;
  fNearPlane = 3.0f;
  fFarPlane = 7.0f;
  fMaxObjSize = 3.0f;
  m_fRadius = fNearPlane + fMaxObjSize / 2.0f;
  glViewport(0,0,mCView_Rect.right,mCView_Rect.bottom);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
    //gluPerspective(45.0f, fAspect, fNearPlane, fFarPlane);
  glOrtho(-dW,dW,-dH,dH,-20*WPSize,20*WPSize);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE); 

  if (DspFlags & DSP_BLACK)
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  }
  else
  {
    glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  GLfloat LightPos[]={0.0f,0.0f,50.0*WPSize,1.0f};
  GLfloat WhiteLight[]={0.9f,0.9f,0.9f};
  GLfloat light_ambient[]={0.5f,0.5f,0.5f,0.5f};
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
  glLightfv(GL_LIGHT0,GL_SPECULAR,WhiteLight);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_ambient);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
  GLfloat MAT_S[]={128.0};
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,MAT_S);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glEnable(GL_NORMALIZE); //Rescale normal vectors to one
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
  glEnable(GL_COLOR_MATERIAL);
  

  glMultMatrixf(mOGLmat.fMat);
  if ((iDspFlgs & DSP_SHADED_EDGES) > 0)
  {
    glPolygonOffset(1.0, 2);
  }
  else
  {
    glPolygonOffset(0.0, 0);
  }

  if (iOGLList == -1)
  {
	  //If animation is on generate multiple frames
	  if ((DspFlags & DSP_ANIMATION) == 0)
	  {
		  GenAnimationS(iDspFlgs, NoResFrame);
	  }
	  else
	  {
		  iOGL_NoOff = 1;
		  iOGL_Start = glGenLists(iOGL_NoOff);
		  iOGLList = iOGL_Start;
		  GenAnimationFrameS(iDspFlgs, iOGL_Start, 1.0);
	  }
  }

glCallList(iOGLList);
for (i=0;i<TmpOGLCnt;i++)
{
  TmpOGL[i]->OglDraw(iDspFlgs,dMFullScl,0);
  if ((DspFlags & DSP_SHADED_EDGES) > 0)
  {
    TmpOGL[i]->OglDrawW(iDspFlgs,dMFullScl,0);
  }
}
//Draw the dragging update
if ((pDragObj != nullptr) && (bIsDrag == TRUE))
pDragObj->OglDrawW(iDspFlgs, dMFullScl, 0);
glLoadIdentity();
if (pCurrentMesh!=NULL)
{
	if ((iDspFlgs & DSP_CONT)==0)
	{
	  DrawColBar(iDspFlgs,dW,dH);
	  pCurrentMesh->WriteResHead(iDspFlgs,(float) dW,(float) dH);
	}
}
//Gradient fill background

  if ((DspFlags & DSP_GRAD) != 0)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
		glVertex3f((float)-dW, (float)dH, -100);
		glColor3f((float) 0.2, (float) 0.2, (float) 0.2);
		glVertex3f((float)-dW, (float)-dH, -100);
		glColor3f((float) 0.5, (float) 0.5, (float) 0.5);
		glVertex3f((float)dW, (float)-dH, -100);
		glColor3f((float) 0.2, (float) 0.2, (float) 0.2);
		glVertex3f((float)dW, (float)dH, -100);
	glEnd();
  }

glFlush();
glFinish();
SwapBuffers(wglGetCurrentDC());
}


//***************************************************
// Element Creation Mode
//***************************************************
void DBase::SetCurEType(int iEType)
{
  iCurElemType = iEType;
}


int DBase::GetCurEType()
{

return (iCurElemType);
}


//***************************************************
// Set buffer for incomming points 
//***************************************************

int DBase::DB_ActiveBuffSet(int iWhichBuff)
{
DB_ActiveBuff = iWhichBuff;
return (DB_ActiveBuff);
}

//***************************************************************
// pt buffer management
//***************************************************************

C3dVector DBase::GetVPt()
{
C3dVector vRet;
C3dVector mPt;
G_Object* pO;
mPt.x=0;
mPt.y=0;
mPt.z=0;
if (S_Count>0)
{
  pO=S_Buff[S_Count-1];
  vRet=pO->Get_Centroid();
}
return(vRet);
}

C3dVector DBase::GetMeshCentre()
{
C3dVector vRet;
vRet.x=0;
vRet.y=0;
vRet.z=0;
if (pCurrentMesh!=NULL)
{
  vRet=pCurrentMesh->Get_Centroid();
}
return(vRet);
}

//This get the maximum y span of the mesh in pixels
//used by zoom all to find a zoom level
//to fit the model
int DBase::GetMeshYExt()
{
int irc=-1; //-1 is error
if (pCurrentMesh!=NULL)
{
  irc=pCurrentMesh->GetMeshYExt();
}
return (irc);
}

BOOL PtrIsIn(G_Object* pThis,G_Object* pIn)
{
BOOL brc=FALSE;
G_Object* pO;
pO=pIn;
while (pO!=NULL)
{
  if (pO==pThis)
  {
    brc=TRUE;
	break;
  }
  pO=pO->pParent;
}

return(brc);
}

void DBase::SetFilter()
{
  CFilterDialog Dlg;
  Dlg.pFilt = &FILTER;
  //CListBox* pItems=(CListBox*) Dlg.GetDlgItem(IDC_LIST1);
  //pItems->AddString("fred");
	Dlg.DoModal();

}

void DBase::QFilterNode()
{
	FILTER.Clear();
	FILTER.SetFilter(1);
	outtext1("Only Nodes are Pickable. ");
}

void DBase::QFilterElement()
{
	FILTER.Clear();
	FILTER.SetFilter(3);
	outtext1("Only Elements are Pickable. ");
}

void DBase::QFilterPoint()
{
	FILTER.Clear();
	FILTER.SetFilter(0);
	outtext1("Only Points are Pickable. ");
}

void DBase::QFilterCurve()
{
	FILTER.Clear();
	FILTER.SetFilter(7);
	outtext1("Only Curvess are Pickable. ");
}

void DBase::QFilterSurface()
{
	FILTER.Clear();
	FILTER.SetFilter(15);
	outtext1("Only Surfaces are Pickable. ");
}

void DBase::QFilterAll()
{
	FILTER.SetAll();
	outtext1("Everything is Pickable. ");
}

int DBase::GetGroupID()
{
int irc;
  CGroupDialog Dlg;
  int i;
  //Dlg.pFilt = &FILTER;
  //CListBox* pItems=(CListBox*) Dlg.GetDlgItem(IDC_LIST1);
  //pItems->AddString("fred");
  for (i=0;i<iNoGPs;i++)
  { 
	  Dlg.AddGroup(Groups[i]->Title); 
  }
  Dlg.iGp=iCurGp;
  Dlg.DoModal();
  irc=Dlg.iGp;
return(irc);
}

int DBase::GetColourID()
{
int irc;
  CColourPickDialog Dlg;
  int i;
  for (i=0;i<167;i++)
  {
    float R =cols[i][0];
    float G =cols[i][1];
    float B =cols[i][2];
    int iR = R*255;
    int iG = G*255;
    int iB = B*255;
    Dlg.AddCol(iR,iG,iB);
  }

//  for (i=0;i<iNoGPs;i++)
//  { 
//	  Dlg.AddGroup(Groups[i]->Title); 
//  }
//  Dlg.iGp=iCurGp;
  Dlg.DoModal();
  irc=Dlg.iSel;
return(irc);
}

int DBase::GetItemType()
{
int irc;

CRelToDialog Dlg;
Dlg.pFilt = &FILTER;
Dlg.DoModal();
irc=Dlg.iType;
return(irc);
}

void DBase::S_BuffAdd2(CDC* pDC,G_Object* cAddObj)
{


BOOL AddIn;
AddIn = S_IsIn(cAddObj);
if (AddIn==FALSE)
{
  cAddObj->HighLight(pDC);
  S_Buff[S_Count] = cAddObj;
  S_Count++;
} 
}

void DBase::S_BuffAdd3(G_Object* cAddObj)
{


BOOL AddIn;
AddIn = S_IsIn(cAddObj);
if (AddIn==FALSE)
{
  S_Buff[S_Count] = cAddObj;
  S_Count++;
} 
}


BOOL DBase::S_IsIn(G_Object* cAddObj)
{
BOOL brc = FALSE;
int i;
for (i=0;i<S_Count;i++)
{
  if (S_Buff[i] == cAddObj)
  {
    brc = TRUE;
	break;
  }
}
return (brc);
}


void DBase::S_Save(ObjList* oList)
{
int i;
oList->Clear();
for (i=0;i<S_Count;i++)
{
  oList->Add(S_Buff[i]);
}
}

void DBase::S_Res()
{
int i;
S_Count = 0;
if (OTemp->iNo>0)
{
  for (i=0;i<OTemp->iNo;i++)
  {
    S_Buff[S_Count] = OTemp->Objs[i];
    S_Count++;
  }
}
if (OTemp2->iNo>0)
{
  for (i=0;i<OTemp2->iNo;i++)
  {
    S_Buff[S_Count] = OTemp2->Objs[i];
    S_Count++;
  }
}
OTemp->Clear();
OTemp2->Clear();
}

//G_Object S_Buff[100];
// Search database for object form coords visible picked
// only nodes search currently
int DBase::S_BuffAdd(G_Object* cAddObj)
{
CDC* pDC=pTheView->GetDC();
int iBuffCnt;
int iRetVal = 1;
G_Object* pO;
G_Object* pT[20];
int iCnt=0;
int i;
pO=cAddObj;
BOOL DoNextLev=TRUE;
pT[iCnt]=pO;
while (pO->pParent!=NULL)
{
  pO=pO->pParent;
  iCnt++;
  pT[iCnt]=pO;
}

if (S_Count>0)
{
  for (i=0;i<iCnt+1;i++)
  { 
	if (DoNextLev==TRUE)
	{
      pO=pT[iCnt-i];
      iBuffCnt=0;
      while (iBuffCnt<S_Count)
      {
        if (S_Buff[iBuffCnt]==pO)
        {
          DoNextLev=FALSE;
		  iRetVal = 0; //removed
		  break;
        }
      iBuffCnt++;
	  }
	}
  }
  iBuffCnt=0;
  while (iBuffCnt<S_Count)
  {
      if (PtrIsIn(pO,S_Buff[iBuffCnt])==TRUE)
      {
        S_Buff[iBuffCnt] = S_Buff[S_Count-1];
        S_Count--;
	    iBuffCnt--;  
		DoNextLev=TRUE;
	  }
	  iBuffCnt++;
  }
} //end if

if (iRetVal == 1)
{
  SetPen(pDC,6);
  cAddObj->HighLight(pDC);
  RestorePen(pDC);
  S_Buff[S_Count] = cAddObj;
  S_Count++;
}

pTheView->ReleaseDC(pDC);
return (iRetVal);
}

void DBase::SelWGName(CString inName)
{
int iCO;
WG_Def* WG;
for (iCO=0;iCO<DB_ObjectCount;iCO++)
{  
  if (DB_Obj[iCO]->iObjType==500)
  {
     WG = (WG_Def*) DB_Obj[iCO];
	 if (WG->Name==inName)
	 {
	  S_BuffAdd(WG);
      break;
	 }
  }
}
}

void DBase::SelAllWGs()
{
int iCO;
WG_Def* WG;
for (iCO=0;iCO<DB_ObjectCount;iCO++)
{  
  if (DB_Obj[iCO]->iObjType==500)
  {
   WG = (WG_Def*) DB_Obj[iCO];
	 S_BuffAdd(WG);
  }
}
}

void DBase::FlipZ()
{
WG_Part* pO;
if (S_Count>0)
{
  if ((S_Buff[S_Count-1]->iObjType==600) || 
     (S_Buff[S_Count-1]->iObjType==602)) 
  {
	pO= (WG_Part*) S_Buff[S_Count-1];
	if (pO->Mesh!=NULL)
	{
	  InvalidateOGL();
	  CDC* pDC = pTheView->GetDC();
	  SetPen(pDC,5);
      pO->Mesh->Draw(pDC,4);
      RestorePen(pDC);
	  pO->FlipZ();
	  pO->Mesh->SetToScr(&pModelMat,&pScrMat);
	  SetPen(pDC,3);
      pO->Mesh->Draw(pDC,4);
      RestorePen(pDC);
      pTheView->ReleaseDC(pDC);

    }
  }
}
}

void DBase::FlipY()
{
WG_Part* pO;
if (S_Count>0)
{
  if ((S_Buff[S_Count-1]->iObjType==600) ||
	 (S_Buff[S_Count-1]->iObjType==602)) 
  {
	pO= (WG_Part*) S_Buff[S_Count-1];
	if (pO->Mesh!=NULL)
	{
	  InvalidateOGL();
	  CDC* pDC = pTheView->GetDC();
	  SetPen(pDC,5);
      pO->Mesh->Draw(pDC,4);
      RestorePen(pDC);
	  pO->FlipY();
	  pO->Mesh->SetToScr(&pModelMat,&pScrMat);
	  SetPen(pDC,3);
      pO->Mesh->Draw(pDC,4);
      RestorePen(pDC);
      pTheView->ReleaseDC(pDC);

    }
  }
}
}

void DBase::UpTree()
{
if (S_Count>0) 
{
  if (S_Buff[S_Count-1]->pParent!=NULL)
  {
    S_Buff[S_Count-1]=S_Buff[S_Count-1]->pParent;
  }
  CDC* pDC = pTheView->GetDC();
  this->Draw(pModelMat,pDC,4);
  pTheView->ReleaseDC(pDC);
}
}


G_Object* DBase::S_Single(CPoint InPT)
{
double SDist = 1E36;
G_Object* cSel = NULL;

int i=0;
G_Object pTarget;
G_ObjectD pO;
if (iDspLstCount > 0)
{
  for (i = 0;i < iDspLstCount;i++)
  {
	   if (Dsp_List[i]->isSelectable() == 1) 
	   {
         pO = Dsp_List[i]->SelDist(InPT,FILTER);
	     if ((pO.Dist < SDist) && (pO.pObj!=NULL))
	     {
			 if ((FILTER.isFilter(pO.pObj->iObjType)==1) || (pO.pObj->iObjType==999))
			 {
			   SDist = pO.Dist;
			   cSel = pO.pObj;
			 }
	     }
       }
   }
}

if ((cSel != NULL) && (SDist < 400) )
{ 
  int i;
  i = S_BuffAdd(cSel);
  if (i==0)
  {
    ReGen();
  }
}
return (cSel);
}

//****************************************************************
//Pre:	pC valid poniter or curve, no of nodes to generate
//		pN should be empty
//Post: Nodes creates and stored in pN
//****************************************************************
void DBase::NodesOnCurve(NCurve* pC,int iNo, cLinkedList* pN)
{
	C3dVector v;
	Node* pNode;
	int i, iCO;
	double dW = 0;
	double dInc;
	double dSpan;

	dW = 0;
	dSpan = pC->we - pC->ws;
	dInc = dSpan / (iNo - 1);
	for (i = 0; i < iNo; i++)
	{
		v = pC->GetPt(dW);
		//AddNode(v, -1,1,1,10,0,0);
		pNode = pCurrentMesh->AddNode(v, pCurrentMesh->iNodeLab, 1, 1, 100, 0, 0);
		pCurrentMesh->iNodeLab++;
		AddTempGraphics(pNode);
		Dsp_Add(pNode);
		dW += dInc;
		if (dW > 1.0) { dW = 1.0; }
		if (pN != NULL)
			pN->Add(pNode);  //Add the newly created node to linked list
	}
}

void DBase::GenNodesOnCircle(NCircle* pCir, int iNo, cLinkedList* pN)
{
	Node* pNode;
	double dRad, dA1, dA2;
	double dSpan, dInc, dAng;
	int i;
	int iDiv;
	C3dMatrix mT;
	C3dVector vTmp;
	C3dVector vCent;
	C3dVector vX;
	C3dVector vY;
	C3dVector vN;
	C3dVector vS;
	C3dVector vE;
	C3dVector vNode;
	//Calculate circle cys and radius
	//calulating explicitly as circle may not have come from M3d
	vTmp.x = 0.5 * (pCir->cPts[4]->Pt_Point->x - pCir->cPts[0]->Pt_Point->x);
	vTmp.y = 0.5 * (pCir->cPts[4]->Pt_Point->y - pCir->cPts[0]->Pt_Point->y);
	vTmp.z = 0.5 * (pCir->cPts[4]->Pt_Point->z - pCir->cPts[0]->Pt_Point->z);
	dRad = vTmp.Mag();
	vCent.x = vTmp.x + pCir->cPts[0]->Pt_Point->x;
	vCent.y = vTmp.y + pCir->cPts[0]->Pt_Point->y;
	vCent.z = vTmp.z + pCir->cPts[0]->Pt_Point->z;
	vX.x = pCir->cPts[0]->Pt_Point->x - vCent.x;
	vX.y = pCir->cPts[0]->Pt_Point->y - vCent.y;
	vX.z = pCir->cPts[0]->Pt_Point->z - vCent.z;
	vY.x = pCir->cPts[2]->Pt_Point->x - vCent.x;
	vY.y = pCir->cPts[2]->Pt_Point->y - vCent.y;
	vY.z = pCir->cPts[2]->Pt_Point->z - vCent.z;
	vN = vX.Cross(vY);
	vX.Normalize(); vY.Normalize(); vN.Normalize();
	mT.SetColVec(1, vX);
	mT.SetColVec(2, vY);
	mT.SetColVec(3, vN);
	mT.m_30 = vCent.x;
	mT.m_31 = vCent.y;
	mT.m_32 = vCent.z;
	vS = pCir->GetPt(pCir->ws);
	vE = pCir->GetPt(pCir->we);
	vS -= vCent; vS.Normalize();
	vE -= vCent; vE.Normalize();
	dA1 = vX.AngSigned(vS, vN);
	dA2 = vX.AngSigned(vE, vN);
	iDiv = iNo;
	if (dA1 != dA2)
		iDiv -= 1;
	if (dA2 == 0)
		dA2 = 360;
	dSpan = dA2 - dA1;
    dInc = dSpan / iDiv;
	//Generate the nodes
	dAng = dA1;
	for (i = 0; i < iNo; i++)
	{
		vNode.x = dRad * cos(dAng * D2R);
		vNode.y = dRad * sin(dAng * D2R);
		vNode.z = 0;
		pNode = pCurrentMesh->AddNode(vNode, pCurrentMesh->iNodeLab, 1, 1, 100, 0, 0);
		pNode->Transform(mT);
		if (pN != NULL)
			pN->Add(pNode);  //Add the newly created node to linked list
		pCurrentMesh->iNodeLab++;
		AddTempGraphics(pNode);
		Dsp_Add(pNode);
		dAng += dInc;
	}
}

void DBase::GenPoinsOnCir(NCircle* pCir, int iNo)
{
	CvPt_Object* pPt;
	double dRad, dA1, dA2;
	double dSpan, dInc, dAng;
	int i;
	int iDiv;
	C3dMatrix mT;
	C3dVector vTmp;
	C3dVector vCent;
	C3dVector vX;
	C3dVector vY;
	C3dVector vN;
	C3dVector vS;
	C3dVector vE;
	C3dVector vNode;
	//Calculate circle cys and radius
	//calulating explicitly as circle may not have come from M3d
	vTmp.x = 0.5 * (pCir->cPts[4]->Pt_Point->x - pCir->cPts[0]->Pt_Point->x);
	vTmp.y = 0.5 * (pCir->cPts[4]->Pt_Point->y - pCir->cPts[0]->Pt_Point->y);
	vTmp.z = 0.5 * (pCir->cPts[4]->Pt_Point->z - pCir->cPts[0]->Pt_Point->z);
	dRad = vTmp.Mag();
	vCent.x = vTmp.x + pCir->cPts[0]->Pt_Point->x;
	vCent.y = vTmp.y + pCir->cPts[0]->Pt_Point->y;
	vCent.z = vTmp.z + pCir->cPts[0]->Pt_Point->z;
	vX.x = pCir->cPts[0]->Pt_Point->x - vCent.x;
	vX.y = pCir->cPts[0]->Pt_Point->y - vCent.y;
	vX.z = pCir->cPts[0]->Pt_Point->z - vCent.z;
	vY.x = pCir->cPts[2]->Pt_Point->x - vCent.x;
	vY.y = pCir->cPts[2]->Pt_Point->y - vCent.y;
	vY.z = pCir->cPts[2]->Pt_Point->z - vCent.z;
	vN = vX.Cross(vY);
	vX.Normalize(); vY.Normalize(); vN.Normalize();
	mT.SetColVec(1, vX);
	mT.SetColVec(2, vY);
	mT.SetColVec(3, vN);
	mT.m_30 = vCent.x;
	mT.m_31 = vCent.y;
	mT.m_32 = vCent.z;
	vS = pCir->GetPt(pCir->ws);
	vE = pCir->GetPt(pCir->we);
	vS -= vCent; vS.Normalize();
	vE -= vCent; vE.Normalize();
	dA1 = vX.AngSigned(vS, vN);
	dA2 = vX.AngSigned(vE, vN);
	iDiv = iNo;
	if (dA1 != dA2)
		iDiv -= 1;
	if (dA2 == 0)
		dA2 = 360;
	dSpan = dA2 - dA1;
	dInc = dSpan / iDiv;
	//Generate the nodes
	dAng = dA1;
	for (i = 0; i < iNo; i++)
	{
		vNode.x = dRad * cos(dAng * D2R);
		vNode.y = dRad * sin(dAng * D2R);
		vNode.z = 0;
		pPt = AddPt(vNode, -1, TRUE);
		pPt->Transform(mT);
		AddTempGraphics(pPt);
		Dsp_Add(pPt);
		dAng += dInc;
	}
}


void DBase::GenNodesOnCurve(int iNo,cLinkedList* pN)
{
C3dVector v;
Node* pNode;
int i,iCO;
double dW=0;
double dInc;
double dSpan;
NCurve* pC;
NCircle* pCir;
if (iNo>0)
{
  for (iCO=0;iCO<S_Count;iCO++)
  {
	//Deal with circles which don't give equal spacings
	//due to parametric nature
	if ((S_Buff[iCO]->iObjType == 7) &&
		(S_Buff[iCO]->iType == 3))
	{
		pCir = (NCircle*) S_Buff[iCO];
		GenNodesOnCircle(pCir, iNo, pN);
	}
    else if ((S_Buff[iCO]->iObjType==7) ||
	    (S_Buff[iCO]->iObjType==13))
    {
      pC = (NCurve*) S_Buff[iCO];
	  dSpan = pC->we-pC->ws;
      // check ends are not coinciden
	  C3dVector vS;
      C3dVector vE;
	  BOOL bEndsMeet= pC->IsClosed();
      //End coincident ends check
	  if (bEndsMeet)
	  {
        dInc = dSpan/(iNo);
	  }
	  else
	  {
        dInc = dSpan/(iNo-1);
	  }
	  dW = pC->ws;
      for (i=0;i<iNo;i++)
	  {
	    v=pC->GetPt(dW);
        //AddNode(v, -1,1,1,10,0,0);
		pNode = pCurrentMesh->AddNode(v, pCurrentMesh->iNodeLab, 1, 1, 100, 0, 0);
		pCurrentMesh->iNodeLab++;
		AddTempGraphics(pNode);
		Dsp_Add(pNode);
	    dW+=dInc;
		if(dW>1.0) 
		  dW=1.0;
		if (pN != NULL)
		  pN->Add(pNode);  //Add the newly created node to linked list
	  }
    }
  }
}
ReDraw();
}

void DBase::GenPointsOnCircle(int iNo)
{
	C3dVector v;
	Node* pNode;
	int i, iCO;
	double dW = 0;
	double dInc;
	double dSpan;
	NCurve* pC;
	NCircle* pCir;
	if (iNo > 0)
	{
		for (iCO = 0; iCO < S_Count; iCO++)
		{
			//Deal with circles which don't give equal spacings
			//due to parametric nature
			if ((S_Buff[iCO]->iObjType == 7) ||
				(S_Buff[iCO]->iType == 3))
			{
				pCir = (NCircle*)S_Buff[iCO];
				GenPoinsOnCir(pCir, iNo);
			}
			
		}
	}
	ReDraw();
}


void DBase::MapMesh(double dU, double dV)
{
int iSNd;
int iFNd;
int iSEl;
int iFEl;
C3dVector v;
int i,j,iCO;
double dIncU;
double dIncV;
double dSpanU;
double dSpanV;
double dUi;
double dVi;
int iU;
int iV;
iU=(int) dU;
iV=(int) dV;

NSurf* pS;

char buff[80];
if (iU<= 0)
   iU=1;
if (iV<= 0)
   iV=1;
Matrix<Node*> Nds(iU+1,iV+1) ;
pCurrentMesh->MaxLab();
iSNd=pCurrentMesh->iNodeLab;
iSEl=pCurrentMesh->iElementLab;
iFNd=iSNd;
iFEl=iSEl;
  for (iCO=0;iCO<S_Count;iCO++)
  {
    if (S_Buff[iCO]->iObjType==15)
    {
		sprintf_s(buff, "%s%4i","Meshing surface : ",S_Buff[iCO]->iLabel ); 
		outtext1(buff);
		pS = (NSurf*) S_Buff[iCO];
		pS->GetBoundingUV(dUi,dVi,dSpanU,dSpanV);
		//dSpanU=pS->pCVsU[0]->we-pS->pCVsU[0]->ws;
		//dSpanV=pS->pCVsV[0]->we-pS->pCVsV[0]->ws;
		dIncU=dSpanU/iU;
		dIncV=dSpanV/iV; 
		 dU=dUi;
      for (i=0;i<=iU;i++)
	    {
		    dV=dVi;
		    for (j=0;j<=iV;j++)
	      {
           v=pS->GetPt(dU,dV);
           //AddNode(v, -1,1,1,10,0,0); 
			     Nds(i,j) = pCurrentMesh->AddNode(v, iFNd,1,1,10,0,0);
           Dsp_Add(Nds(i,j));
			     iFNd++;
           dV+=dIncV;
			     if (dV>1) {dV=1;}
		    }
		    dU+=dIncU;
		    if (dU>1) {dU=1;}
		}
	}
	Node* iNlabs[MaxSelNodes]; 
  E_Object* pEl;
  for (i=0;i<iU;i++)
  {
    for (j=0;j<iV;j++)
    {
        iNlabs[0]=Nds(i,j);
	    iNlabs[1]=Nds(i,j+1);
	    iNlabs[2]=Nds(i+1,j+1);
	    iNlabs[3]=Nds(i+1,j);

		pEl=pCurrentMesh->AddEl(iNlabs,iFEl,pS->iColour,94,1,1,4,0,0,0,0,-1,0);
        Dsp_Add(pEl);
	    iFEl++;
    }
  }
}
sprintf_s(buff, "%s%4i%s%4i","Nodes Generated : ",iSNd," to ", iFNd-1 ); 
outtext1(buff);
sprintf_s(buff, "%s%4i%s%4i","Elements Generated : ",iSEl," to ", iFEl-1 ); 
outtext1(buff);
pCurrentMesh->iNodeLab=iFNd;
pCurrentMesh->iElementLab=iFEl;
Nds.DeleteAll();
InvalidateOGL();
ReDraw();
}





void DBase::MapMeshTri(double dU, double dV)
{
int iSNd;
int iFNd;
int iSEl;
int iFEl;
C3dVector v;
int i,j,iCO;
double dIncU;
double dIncV;
double dSpanU;
double dSpanV;
double dUi;
double dVi;
int iU;
int iV;
iU=dU;
iV=dV;

NSurf* pS;

char buff[80];
if (iU<= 0)
   iU=1;
if (iV<= 0)
   iV=1;
Matrix<Node*> Nds(iU+1,iV+1) ;
pCurrentMesh->MaxLab();
iSNd=pCurrentMesh->iNodeLab;
iSEl=pCurrentMesh->iElementLab;
iFNd=iSNd;
iFEl=iSEl;
  for (iCO=0;iCO<S_Count;iCO++)
  {
    if (S_Buff[iCO]->iObjType==15)
    {
      sprintf_s(buff, "%s%4i","Meshing surface : ",S_Buff[iCO]->iLabel ); 
		  outtext1(buff);
      pS = (NSurf*) S_Buff[iCO];
      pS->GetBoundingUV(dUi,dVi,dSpanU,dSpanV);
      //dSpanU=pS->pCVsU[0]->we-pS->pCVsU[0]->ws;
      //dSpanV=pS->pCVsV[0]->we-pS->pCVsV[0]->ws;
      dIncU=dSpanU/iU;
      dIncV=dSpanV/iV; 
		  dU=dUi;
      for (i=0;i<=iU;i++)
	    {
		    dV=dVi;
		    for (j=0;j<=iV;j++)
	      {
           v=pS->GetPt(dU,dV);
           //AddNode(v, -1,1,1,10,0,0); 
			     Nds(i,j) = pCurrentMesh->AddNode(v, iFNd,1,1,10,0,0);
           Dsp_Add(Nds(i,j));
			     iFNd++;
           dV+=dIncV;
			     if (dV>1) {dV=1;}
		    }
		    dU+=dIncU;
		    if (dU>1) {dU=1;}
		}
	}
	Node* iNlabs[MaxSelNodes]; 
    E_Object* pEl;
    for (i=0;i<iU;i++)
    {
      for (j=0;j<iV;j++)
      {
        iNlabs[1]=Nds(i,j);
	      iNlabs[2]=Nds(i+1,j+1);
	      iNlabs[0]=Nds(i+1,j);
        pEl=pCurrentMesh->AddEl(iNlabs,iFEl,pS->iColour,91,1,1,3,0,0,0,0,0,0);
        Dsp_Add(pEl);
		    iFEl++;
		    iNlabs[2]=Nds(i+1,j+1);
	      iNlabs[1]=Nds(i,j+1);
	      iNlabs[0]=Nds(i,j);
        pEl=pCurrentMesh->AddEl(iNlabs,iFEl,pS->iColour,91,1,1,3,0,0,0,0,0,0);
        Dsp_Add(pEl);
		    iFEl++;
     }
    }
  }
sprintf_s(buff, "%s%4i%s%4i","Nodes Generated : ",iSNd," to ", iFNd-1 ); 
outtext1(buff);
sprintf_s(buff, "%s%4i%s%4i","Elements Generated : ",iSEl," to ", iFEl-1 ); 
outtext1(buff);
pCurrentMesh->iNodeLab=iFNd;
pCurrentMesh->iElementLab=iFEl;
Nds.DeleteAll();
InvalidateOGL();
ReDraw();
}



    

void DBase::Test2()
{
outtext1("TEST PROCEDURE");
   //virtual BOOL GenerateExp(C3dVector cPts[1000],
   //                       double wghts[1000],
   //                       double KnotsU[100],
   //                       double KnotsV[100],
   //                       int noU,
   //                       int noV,
   //                       int pInU,
   //                       int pInV);
C3dVector cPts[1000];
double wghts[1000];
double KnotsU[100];
double KnotsV[100];
int noU=3;
int noV=2;
int pInU=2;
int pInV=1;
cPts[0].Set(0,0,0);
cPts[1].Set(1,0,1);
cPts[2].Set(2,0,0);
cPts[3].Set(0,2,0);
cPts[4].Set(1,2,1);
cPts[5].Set(2,2,0);
wghts[0]=1;
wghts[1]=1;
wghts[2]=1;
wghts[3]=1;
wghts[4]=1;
wghts[5]=1;
KnotsU[0]=0;
KnotsU[1]=0;
KnotsU[2]=0;
KnotsU[3]=1;
KnotsU[4]=1;
KnotsU[5]=1;

KnotsV[0]=0;
KnotsV[1]=0;
KnotsV[2]=1;
KnotsV[3]=1;
NSurf* pS=new NSurf();
pS->GenerateExp(cPts,
                wghts,
                KnotsU,
                KnotsV,
                noU,
                noV,
                pInU,
                pInV);
AddObj(pS);
ReDraw();
}






//*******************************************************
//Basic 2d test produre for Material Point Method
//28/02/2019
//*******************************************************
void DBase::TestMPM2()
{
  outtext1("TEST PROCEDURE FOR 2D MPM");
  if (pCurrentMesh != NULL)
  {
		  pCurrentMesh->ExplicitSolTest(PropsT, MatT);
  }
}

//*******************************************************
//Basic 2d test produre for Material Point Method
//28/02/2019
//*******************************************************
void DBase::TestFL()
{
	GenAnimationW(DspFlags, 8);
}

//*******************************************************
//Insert sphere and render with earth bmp if loaded
//11/01/22
//*******************************************************
void DBase::insPlanet()
{
	Planet* pS;
	pS=new (Planet);
	if (pWorldBMP != NULL)
	{
		pS->AttachTexture(pWorldBMP);
		AddObj(pS);
		ReDraw();
	}
	else
		outtext1("LOAD WORLD BITMAP FIRST");

}

//*******************************************************
//Insert sphere and render with earth bmp if loaded
//11/01/22
//*******************************************************
void DBase::insBackGround()
{
	char buff[200];
	
	BackGround* pS;
	pS = new BackGround(WPSize);

	if (pWorldBMP != nullptr)
	{
		pS->AttachTexture(pWorldBMP);
		sprintf_s(buff, "%x", pWorldBMP->header);
		outtext1(buff);
		AddObj(pS);
		ReDraw();
	}
	else
		outtext1("LOAD BITMAP FIRST");

}

  //SolveIncompFluids();



void DBase::Dsp_CtrlPts()
{
C3dVector v;
int iCO;
double dW=0;
NCurve* pC;
NSurf* pS;

for (iCO=0;iCO<S_Count;iCO++)
{
  if ((S_Buff[iCO]->iObjType==7) ||
	  (S_Buff[iCO]->iObjType==13))
  {
    pC = (NCurve*) S_Buff[iCO];
    pC->DrawCtrlPtsTog();
  }
  if (S_Buff[iCO]->iObjType==15)
  {
    pS = (NSurf*) S_Buff[iCO];
    pS->DrawCtrlPtsTog();
  }
}
InvalidateOGL();
ReDraw();
}


void DBase::CV_ModifW(double dW)
{

int iCO;
CvPt_Object* pC;
if (dW>0)
{
if (S_Count>0)
{
  for (iCO=0;iCO<S_Count;iCO++)
  {
    if (S_Buff[iCO]->iObjType==0) 
    {
      pC = (CvPt_Object*) S_Buff[iCO];
      pC->w=dW;
    }
  }
}
  InvalidateOGL();
  ReDraw();
}
}

void DBase::S_Box(CPoint UL, CPoint LR)
{
int i;
ObjList* pSel = new ObjList();
if (iDspLstCount > 0)
{
  for (i = 0;i < iDspLstCount;i++)
  {
	 if ((Dsp_List[i]->isSelectable() == 1)  )
	 {
       Dsp_List[i]->S_Box(UL,LR,pSel);
	 }
  }
}
//CDC* pDC=pTheView->GetDC();
//SetPen(pDC,6);
for (i=0;i<pSel->iNo;i++)
{  
  if (FILTER.isFilter(pSel->Objs[i]->iObjType)==TRUE)
  {
    S_BuffAdd3(pSel->Objs[i]);
  }
}
//RestorePen(pDC);
//pTheView->ReleaseDC(pDC);
delete(pSel);
pSel = NULL;
//ReDraw();
}

void DBase::S_Invert()
{
int i;

for (i=1;i<iDspLstCount;i++)
  {
	if (Dsp_List[i]->isSelectable()==1)
	{
		S_BuffAdd(Dsp_List[i]);
	}  
  }
ReDraw();
}

void DBase::S_All(int iT)
{
int i;
ObjList* pSel = new ObjList();
for (i=1;i<iDspLstCount;i++)
  {
	if (Dsp_List[i]->isSelectable()==1)
	{
	  if ((Dsp_List[i]->iObjType==iT) || (iT==-1))
	  {
	    if (Dsp_List[i]->iObjType!=4)
	      S_BuffAdd3(Dsp_List[i]);
	  }
      if ((Dsp_List[i]->iObjType==4))
	  {
        ME_Object* pM = (ME_Object*) Dsp_List[i];
	    pM->S_Sel(iT,pSel);
	  }	
	}
  }
for (i=0;i<pSel->iNo;i++)
{  
    S_BuffAdd3(pSel->Objs[i]);
}
delete(pSel);
pSel = NULL;
ReDraw();
}


void DBase::S_Des()
{

S_Count=0;
ReDraw();
}

//***************************************************************
// pt buffer management
//***************************************************************


void DBase::DB_AddPtBuff(C3dVector InPT)
{
if (DB_BuffCount < 500)
  {
  DB_PtBuff[DB_BuffCount] = InPT;
  DB_BuffCount++;
  }
}


void DBase::DB_ClearBuff()
{
DB_BuffCount = 0;
}

C3dVector DBase::DB_GetBuffbyInd(int iInd)
{
	return (DB_PtBuff[iInd]);
}

C3dVector DBase::DB_GetBuff()
{
	return (DB_PtBuff[DB_BuffCount-1]);
}

C3dVector DBase::DB_PopBuff()
{
DB_BuffCount--;
return (DB_PtBuff[DB_BuffCount]);
}

void DBase::DB_Dellast()
{
if (DB_BuffCount > 0) 
  {
  DB_BuffCount--;
  }
}

int DBase::DB_NoInBuff()
{
return (DB_BuffCount);
}



void DBase::DoMsg(int MsgType, CPoint PT1, CPoint PT2)
{

if (MsgType == 1)
{
  G_Object* DB_h = S_Single(PT1);
}
else if (MsgType == 3)
{
  ReDraw();
}
else if (MsgType == 4)
{
  ReDraw();
}

}



void DBase::SetView(CView* pCViewCurrent)
{
pTheView = pCViewCurrent;
mOGLmat = pModelMat.GetOglMat();
pTheView->GetClientRect(mCView_Rect);

}

//The Old Working Version
//Element force data set
//only CQUAD4 force read at now
//Element force data set
//only CQUAD4 force read at now
void DBase::Readdb(FILE* pFile, int Vals[], int &iCnt, int &iKey, int &iRec, CString &sTit, CString &sSubTit,double &dFreq)
{

	int i;
	int iNoW;
	int iWord;
	int ACODE;
	int TCODE;
	int ELTYPE;
	int WID;
	int FORMAT_CODE = 0;
	int STRESS_CODE = 0;
	float fW;
	float ff;
	char sT[8];
	int lLC;
	int iWCnt;
	fread(&sT, 8, 1, pFile);
	fread(&iKey, 4, 1, pFile);
	fread(&sT, 8, 1, pFile);
	fread(&iWord, 4, 1, pFile);
	fread(&sT, 8, 1, pFile);
	fread(&iNoW, 4, 1, pFile);
	if (iNoW == 146)
	{
		fread(&sT, 8, 1, pFile);
		fread(&ACODE, 4, 1, pFile);	   //1
		fread(&TCODE, 4, 1, pFile);	   //2
		fread(&ELTYPE, 4, 1, pFile);   //3
		fread(&lLC, 4, 1, pFile);      //4
		Vals[0] = ACODE;
		Vals[1] = TCODE;
		if (TCODE == 18)
			ELTYPE = 999;
		Vals[2] = ELTYPE;
		Vals[3] = lLC;
		fread(&ff, 4, 1, pFile);  //5 if acode = 5 then this is freq val
		dFreq = ff;
		fread(&Vals[5], 4, 1, pFile);  //6
		//fF = pow(fW, 0.5)/(3.14159265359 *2);
		fread(&WID, 4, 1, pFile);              //7
		fread(&WID, 4, 1, pFile);              //8
		fread(&FORMAT_CODE, 4, 1, pFile);      //9	 format_code - Data types (real or complex)
		fread(&WID, 4, 1, pFile);              //10	 block width
		Vals[6] = WID;
		Vals[7] = FORMAT_CODE;
		fread(&STRESS_CODE, 4, 1, pFile);
		Vals[8] = STRESS_CODE;
		iCnt = 10;
		//if (ACODE=22)
		  //sprintf_s(s80, "MODE ,%i", iM);
		for (i = 11; i < 50; i++)
		{
			fread(&iWord, 4, 1, pFile);
		}
		char sTitle[32 * 4];
		char sSubTitle[32 * 4];

		fread(&sTitle, 32 * 4, 1, pFile);
		fread(&sSubTitle, 32 * 4, 1, pFile);
		sTit = sTitle;
		sTit = sTit.Left(32 * 4);
		sSubTit = sSubTitle;
		sSubTit = sSubTit.Left(32 * 4);

		for (i = 114; i < iNoW; i++)
		{
			fread(&iWord, 4, 1, pFile);
		}
		fread(&sT, 8, 1, pFile);
		fread(&iNoW, 4, 1, pFile);
		fread(&sT, 8, 1, pFile);
		fread(&iNoW, 4, 1, pFile);
		fread(&sT, 8, 1, pFile);
		fread(&iNoW, 4, 1, pFile);
		fread(&sT, 8, 1, pFile);
		fread(&iNoW, 4, 1, pFile);
		fread(&fW, 4, 1, pFile);
		int iTypeGS;
		fread(&iTypeGS, 4, 1, pFile);
		iKey = iNoW;
		iWCnt = 0;
		while (iKey > 0)
		{
			if (ELTYPE == 0)   //Disp
			{
				while (iWCnt != iNoW)
				{
					fread(&Vals[iCnt], 4, 1, pFile);
					iCnt++;
					iWCnt++;
				}
			}
			else if ((ELTYPE == 33) ||   //CQUAD4 
				(ELTYPE == 74) ||   //CTRIA3
				(ELTYPE == 95) ||   //COMP STRESS CQUAD
				(ELTYPE == 97) ||   //COMP STRESS CTRAI
				(ELTYPE == 102) ||   //CBUSH 
				(ELTYPE == 90) ||   //CTRIA3 
				(ELTYPE == 88) ||   //CBUSH 
				(ELTYPE == 34) ||   //CBAR 
				(ELTYPE == 39) ||   //CTETRA LIN
				(ELTYPE == 67) ||   //CHEXA LIN
				(ELTYPE == 68) ||   //CPENTA LIN
				(ELTYPE == 1)  ||   //CROD
				(ELTYPE == 2)  ||   //CBEAM 
				(ELTYPE ==999))
			{
				while (iWCnt != iNoW)
				{
					fread(&Vals[iCnt], 4, 1, pFile);
					iCnt++;
					iWCnt++;
				}
			}
			else
			{
				while (iWCnt != iNoW)
				{
					fread(&iWord, 4, 1, pFile);
					iCnt++;
					iWCnt++;
				}
			}
			fread(&sT, 8, 1, pFile);
			fread(&iKey, 4, 1, pFile);
			if (iKey > 0)
			{
				fread(&sT, 8, 1, pFile);
				iNoW = iKey;
				iWCnt = 0;
			}
			else
			{
				iRec = iKey;
			}
		}
	}
	else
	{
		iRec = 0;
		iKey = 0;
	}
}

void DBase::AddOEFRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->AddOEFRes(Vals,iCnt,sTitle,sSubTitle,inName);
}
}

void DBase::AddOEFResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOEFResF(Vals, iCnt, sTitle, sSubTitle, inName,dF);
	}
}

void DBase::AddOAG1Res(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName,double dF)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOAG1Res(Vals, iCnt, sTitle, sSubTitle, inName,dF);
	}
}

void DBase::AddOQMRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOQMRes(Vals, iCnt, sTitle, sSubTitle, inName, dF);
	}
}

void DBase::AddOUGRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->AddOUGRes(Vals,iCnt,sTitle,sSubTitle,inName);
}
}

void DBase::AddOES1Res(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->AddOES1Res(Vals,iCnt,sTitle,sSubTitle,inName);
}
}

void DBase::AddOES1ResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOES1ResF(Vals, iCnt, sTitle, sSubTitle, inName,dF);
	}
}

void DBase::AddOSTRRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->AddOSTRRes(Vals,iCnt,sTitle,sSubTitle,inName);
}
}

void DBase::AddOSTRResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOSTRResF(Vals, iCnt, sTitle, sSubTitle, inName,dF);
	}
}


void DBase::AddOESNRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->AddOESNRes(Vals,iCnt,sTitle,sSubTitle,inName);
}
}

void DBase::AddOESResR(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOESResR(Vals, iCnt, sTitle, sSubTitle, inName);
	}
}

void DBase::AddOSTRResR(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName,double dFreq)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOSTRResR(Vals, iCnt, sTitle, sSubTitle, inName, dFreq);
	}
}



void DBase::AddOSTRFCPXRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dFreq)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->AddOSTRFCPXRes(Vals, iCnt, sTitle, sSubTitle, inName, dFreq);
	}
}

void DBase::AddONRGRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName)
{
  if (pCurrentMesh != NULL)
  {
    pCurrentMesh->AddONRGRes(Vals, iCnt, sTitle, sSubTitle, inName);
  }
}


void DBase::S_ImportOp2(FILE* pFile,CString inName,int iT)
{
int ACODE = 0;
int TCODE = 0;
int FCODE = 0;
int SCODE = 0;
int iCnt;
int iTC = -1;
int* DataB = (int*) malloc(10000000 * sizeof(int) ); 
CString sTitle;
CString sSubTitle;
double dFreq=0;
char sDataS[5] = "";
int iKey;
int iRecord=0;
char sT[8];
int iWord;
int i;
fread (&iKey,4,1,pFile);
while (!feof(pFile))
{
   fread (&iKey,4,1,pFile);
   if (iKey>0)
   {
     fread (&sT,8,1,pFile);
     if ((iRecord == 0) && (iKey == 2))
     {
        //New data record
        fread (&sDataS,4,1,pFile);
        sDataS[4]=NULL;
        outtext1(sDataS);
        fread (&iWord,4,1,pFile);
     }
     else
     {
         for (i=0;i<iKey;i++)
         {
           fread (&iWord,4,1,pFile);
         }
     }
   }
   else if (iKey < 0)
   {
     //end of record
     iRecord = iKey;
   }
   else
   {
     //end of data block
     iRecord = 0;
   }
   //Read the element forces
   if ((sDataS[0] == 'O') &&
       (sDataS[1] == 'E') &&
       (sDataS[2] == 'F') &&
       (iRecord == -3)) 
   {
      while (iKey != 0)
      {
            iCnt = 0;
            Readdb(pFile,DataB,iCnt,iKey,iRecord,sTitle,sSubTitle, dFreq);
			ACODE = DataB[0];
			TCODE = DataB[1];
			FCODE = DataB[7];	  //newly added so result can be
			SCODE = DataB[8];	  //interprested m
			iTC = TCODE / 1000;
			if (iCnt > 0)
			{
				if (DataB[0] / 10 == 1)	//Linear
				{
					if ((iTC == 0) || (iTC == 2))  //Real sort1 and sort2
						AddOEFRes(DataB, iCnt, sTitle, sSubTitle, inName);
					else if ((iTC == 4) || (iTC == 5)) //Real Random
						AddOEFRes(DataB, iCnt, sTitle, sSubTitle, inName);
				}
				else if (DataB[0] / 10 == 5)	//Freq
				{
					if ((iTC == 1) || (iTC == 3))  //Complex sort1 and sort2
						AddOEFResF(DataB, iCnt, sTitle, sSubTitle, inName, dFreq);
				}
			}
            //WriteF
      }
   }
   else if ((sDataS[0] == 'O') &&
	        (sDataS[1] == 'A') &&
	        (sDataS[2] == 'G') &&
	        (iRecord == -3))
   {
	   while (iKey != 0)
	   {
		   iCnt = 0;
		   Readdb(pFile, DataB, iCnt, iKey, iRecord, sTitle, sSubTitle, dFreq);
		   if (iCnt > 0)
		   {
			   if (DataB[0]/10 == 5)  // Frequency Only
				   AddOAG1Res(DataB, iCnt, sTitle, sSubTitle, inName, dFreq);
		   }
		   //WriteF
	   }
   }
   else if ((sDataS[0] == 'O') &&
	        (sDataS[1] == 'Q') &&
	        (sDataS[2] == 'M') &&
	        (iRecord == -3))
   {   //MPC Forces
	   while (iKey != 0)
	   {
		   iCnt = 0;
		   Readdb(pFile, DataB, iCnt, iKey, iRecord, sTitle, sSubTitle, dFreq);
		   if (iCnt > 0)
		   {
			   if ((DataB[0] / 10 == 1) || (DataB[0] / 10 == 5))   // Static & Frequency Only
				   AddOQMRes(DataB, iCnt, sTitle, sSubTitle, inName, dFreq);
		   }
		   //WriteF
	   }
   }
   else if ((sDataS[0] == 'O') &&
            (sDataS[1] == 'U') &&
            (sDataS[2] == 'G') &&
            (iRecord == -3)) 
   {
      while (iKey != 0)
      {
            iCnt = 0;
            Readdb(pFile,DataB,iCnt,iKey,iRecord,sTitle,sSubTitle, dFreq);
			if (iCnt > 0)
			{
				if ((DataB[0] / 10 == 1) || (DataB[0] / 10 == 2))   // Static or Modes
					AddOUGRes(DataB, iCnt, sTitle, sSubTitle, inName);
			}
            //WriteF
      }
   }
   else if ((sDataS[0] == 'O') &&  
            (sDataS[1] == 'S') &&
            (sDataS[2] == 'T') &&
			(sDataS[3] == 'R') &&
            (iRecord == -3)) 
   {
      while (iKey != 0)
      {
            iCnt = 0;
            Readdb(pFile,DataB,iCnt,iKey,iRecord,sTitle,sSubTitle, dFreq);
			ACODE = DataB[0];
			TCODE = DataB[1];
			FCODE = DataB[7];	  //newly added so result can be
			SCODE = DataB[8];	  //interprested m
			iTC = TCODE / 1000;
			if (iCnt > 0)
			{
				if (ACODE / 10 == 1)  //STATICS	or RANDOM
				{
					if ((iTC == 0) || (iTC == 2))	//statics real sort 1 & 2
						AddOSTRRes(DataB, iCnt, sTitle, sSubTitle, inName);
					else if ((iTC=4) || (iTC=5))	//Random  real sort 1 & 2
						AddOSTRResR(DataB, iCnt, sTitle, sSubTitle, inName, dFreq);

				}
				if (ACODE / 10 == 5)  //Freq
				{
					if ((iTC == 1) || (iTC == 3))  //Complex sort1 and sort2
						AddOSTRResF(DataB, iCnt, sTitle, sSubTitle, inName, dFreq);
				}
			}
            //WriteF
      }
   }
   else if ((sDataS[0] == 'O') &&
            (sDataS[1] == 'E') &&
            (sDataS[2] == 'S') &&
            (iRecord == -3)) 
   {
      while (iKey != 0)
      {
            iCnt = 0;
            Readdb(pFile,DataB,iCnt,iKey,iRecord,sTitle,sSubTitle, dFreq);
			ACODE = DataB[0];
			TCODE = DataB[1];
			FCODE = DataB[7];	  //newly added so result can be
			SCODE = DataB[8];	  //interprested m
			iTC = TCODE / 1000;
			if (iCnt > 0)
			{
				if (ACODE / 10 == 1)  //Statics only
				{
					if ((iTC == 0) || (iTC == 2))  //Real sort1 and sort2
						AddOES1Res(DataB, iCnt, sTitle, sSubTitle, inName);
					else if ((iTC == 4) || (iTC == 5))
						AddOESResR(DataB, iCnt, sTitle, sSubTitle, inName);
				}
				else if (ACODE / 10 == 10) //NON LINEAR STATICS
				{
					AddOESNRes(DataB, iCnt, sTitle, sSubTitle, inName);
				}
				else if (ACODE / 10 == 5)  //Frequency
				{
					if ((iTC == 1) || (iTC == 3))  //Complex sort1 and sort2
					  AddOES1ResF(DataB, iCnt, sTitle, sSubTitle, inName, dFreq);
				}
			}
      }
   }
   else if ((sDataS[0] == 'O') &&  //Strain element desity added 21/02/2019
            (sDataS[1] == 'N') &&  //Does not work yet
            (sDataS[2] == 'R') &&
            (sDataS[3] == 'G') &&
            (iRecord == -3))
   {
     while (iKey != 0)
     {
       iCnt = 0;
       Readdb(pFile, DataB, iCnt, iKey, iRecord, sTitle, sSubTitle, dFreq);
       if (iCnt>0)
         AddONRGRes(DataB, iCnt, sTitle, sSubTitle, inName);
       //WriteF
     }
   }

   fread (&sT,8,1,pFile);
   //iWord = *(int*) &sWord;
   //fWord = *(float*) &sWord; 
}
free(DataB );   
}

void DBase::S_Import(FILE* pFile,CString inName,int iT)
{
ME_Object* Mesh;
Mesh = NULL;
if (iT == 1) 
{
  Mesh = ImportUNV(pFile,inName);
}
else if (iT == 2)
{
  Mesh = ImportNAS(pFile,inName,FALSE);
}
else if (iT == 3)
{
  Mesh = ImportNASTRAN(inName);
}
if (Mesh!=NULL)
{
  Mesh->MaxLab();
  pCurrentMesh=Mesh;
  DB_Obj[DB_ObjectCount] =Mesh;
  DB_ObjectCount++;
  Dsp_Add(Mesh);
  InvalidateOGL();
  ReDraw();
}
}


void DBase::S_ImportGroups(FILE* pFile)
{
  int iStop=0;
  char s1[200];
  CString s8;
  int iID;
  int iCol;
  CString sdl;
  CString sName;
  G_Object* pO;
  if ((pCurrentMesh!=NULL) && (pFile!=NULL))
  {
	fgets (s1,200,pFile);
	fgets (s1,200,pFile);
    while (iStop == 0)
    {
		fgets (s1,200,pFile);
		sdl=s1;
		if ((sdl.Find("GROUP")==0) && (sdl.GetLength()==6))
		{
		  fgets (s1,200,pFile);
          outtext1(s1); 
		  sName=s1;
		  AddGp(sName);
		}
		else if (sdl.Find("ELEM")==0)
		{
		  s8=sdl.Mid(10,10);
		  iID=atoi(s8);
		  s8=sdl.Mid(20,10);
		  iCol=atoi(s8);
		  pO=pCurrentMesh->GetObj(3,iID);
		  if (pO!=NULL)
		  {
		    pO->iColour=iCol;
			Groups[iCurGp]->Add(pO);
		  }
          //outtext1(s8); 
		  
		}
		else if (sdl.Find("NODE")==0)
		{
		  s8=sdl.Mid(10,10);
		  iID=atoi(s8);
		  s8=sdl.Mid(20,10);
		  iCol=atoi(s8);
		  pO=pCurrentMesh->GetObj(1,iID);
		  if (pO!=NULL)
		  {
		    pO->iColour=iCol;
			Groups[iCurGp]->Add(pO);
		  }
          //outtext1(s8); 
		}
	  if (feof(pFile))
      {
        //printf("\nEND OF FILE\n");
        iStop = 1;     
      }
    }
  }
}


void DBase::S_ImportCat(FILE* pFile,CString inName)
{
ME_Object* Mesh;
int iStop=0;
char s1[200];
char sName[200];
char sPath[200];
char sFile[400];
CString SFileN;
if (MeshCat!=NULL) 
{
  delete (MeshCat);
  MeshCat=NULL;
}
MeshCat = new PartsCat(1);
fscanf(pFile,"%s",&sPath);
outtext1("    ****");
outtext1("Loading catalog :-");
while (iStop == 0)
  {
  fscanf(pFile,"%s%s",&s1,&sName);
  sprintf(sFile,"%s%s",sPath,s1);
  outtext1(s1);
  SFileN=sFile;
  //pFile2 = fopen(sFile,"r");

  if ((SFileN.Find(".DAT") > -1) || (SFileN.Find(".dat") > -1) ||
      (SFileN.Find(".BDF") > -1) || (SFileN.Find(".bdf") > -1))
  {
        Mesh = ImportNASTRAN2(sFile,FALSE);
        Mesh->sName=sName;
		MeshCat->Add(Mesh);
  }

  if (feof(pFile))
  {
     //printf("\nEND OF FILE\n");
     iStop = 1;     
  }
 }

outtext1("    ****");
//if (pFile2!=NULL)
//{
//   fclose(pFile2);
//}
}


GLuint DBase::S_loadBMP(CString sFile, CString inName) 
{
	//Load the bitman must read as a binary file
	CT2CA pszConvertedAnsiString(sFile);
	std::string strFileName(pszConvertedAnsiString);

	if (pWorldBMP != nullptr) {
		delete (pWorldBMP);
		pWorldBMP = nullptr;
    }
	//Open file
	std::ifstream file(strFileName.c_str(), std::ios::binary);
	if (!file.is_open()) {
		outtext1("ERROR: Image could not be opened.");
		return 0;
	}

	pWorldBMP = new BMP();
	// Read the BMP header
	if (!file.read(reinterpret_cast<char*>(pWorldBMP->header), 54)) {
		outtext1("ERROR: Not a correct BMP file.");
		file.close();
		delete (pWorldBMP);
		return 0;
	}
	if (pWorldBMP->header[0] != 'B' || pWorldBMP->header[1] != 'M') {
		outtext1("ERROR: Not a correct BMP file.");
		file.close();
		delete (pWorldBMP);
		return 0;
	}
	//// Read ints from the byte array
    pWorldBMP->dataPos = *(int*)&(pWorldBMP->header[0x0A]);
    pWorldBMP->imageSize = *(int*)&(pWorldBMP->header[0x22]);
    pWorldBMP->width = *(int*)&(pWorldBMP->header[0x12]);
    pWorldBMP->height = *(int*)&(pWorldBMP->header[0x16]);
	// Allocate memory for the data buffer
	pWorldBMP->data = new unsigned char[pWorldBMP->imageSize];

	// Check if memory allocation was successful
	if (pWorldBMP->data == nullptr) {
		outtext1("ERROR: Bad Memory Allocation.");
		file.close();
		delete (pWorldBMP);
		return 0;
	}

	// Read the actual data from the file into the buffer
	file.seekg(pWorldBMP->dataPos, file.beg);
	if (!file.read(reinterpret_cast<char*>(pWorldBMP->data), pWorldBMP->imageSize))
	{
		outtext1("ERROR: Data Read Failure.");
		delete[] pWorldBMP->data;
		pWorldBMP->data = nullptr;
		file.close();
		return 0;
	}

	file.close(); // Close the file when done
	return 1;
}








int DBase::S_ImportWG(FILE* pFile,CString inName)
{
int iErr=0;
if (pSecs == NULL)
{
  CString S= GetCommandLine();
  outtext1("ERROR: No Sec Table Loaded.");
  outtext1(S);
}
else
{

InvalidateOGL();
outtext1(inName);
int iStop=0;
char s1[1000];
CString S;
WG_Def* WG= new WG_Def;
WG->Create(1,inName,NULL);
do
  {
  if (fgets(s1,1000,pFile)!=NULL)
  {
	S=s1;
	WG->addLn(S);
  }
  if (feof(pFile))
     {
     //printf("\nEND OF FILE\n");
     iStop = 1;     
     }
 }
while (iStop == 0);

WG->BuildFromDef(&iErr);
iErr=WG->Generate(pSecs,iSMode,iSW,iSH,gdSize,gdASize);
if (iErr!=3)
{
  AddObj(WG);
}
ReGen();
}

return(iErr);
}

double ExtractDouble(CString inS,int iPos)
{
double d=0;
int i1;
int i;
int iCnt=0;
CString S;

i1=0;
for (i=0;i<inS.GetLength();i++)
{
  if (inS[i]==',')
  {
	iCnt++;
	if (iCnt==iPos)
	{
      S=inS.Mid(i1+1,i-i1-1);
	  S.Replace("D", "E");
	  d=atof(S);
	  break;
	}
    i1=i;
  }
}
return (d);
}


G_Object* DBase::GetBasicIGESType(int iD,IgesD (&DirEnt)[100000],IgesP* PDat)
{
G_Object* pRet=NULL;
CString sParam;
C3dVector p1;
C3dVector p2;
C3dVector p3;
sParam=PDat->getPLine(DirEnt[iD].pData,DirEnt[iD].iPLCnt);
if (sParam!=",")
{
	//if (DirEnt[iD].itype==502)
	//{
	////Iges Point
	//  int iNo;
	//  int j;
	//  iNo = (int) ExtractDouble(sParam,2);
	//  for (j=0;j<iNo;j++)
	//  {
	//	p1.x=ExtractDouble(sParam,j*3+3);
	//	p1.y=ExtractDouble(sParam,j*3+4);
	//	p1.z=ExtractDouble(sParam,j*3+5);
	//	pRet=AddPt(p1,DirEnt[iD].iLab,FALSE);
	//	DirEnt[iD].iLab = pRet->iLabel;
	//	DirEnt[iD].pO = pRet;
	//  }
	//}
	if (DirEnt[iD].itype==128)
	{
	  //Iges BSpline Surface
	  if (DirEnt[iD].iFrmNo==0)
	  {
		pRet=BSurfIges(DirEnt[iD],sParam);
		DirEnt[iD].iLab = pRet->iLabel;
	  }
	}
	else if (DirEnt[iD].itype==126)
	{
	//Iges BCurve Curve 
	  if (DirEnt[iD].iFrmNo==0)
	  {
		pRet=BCurveIges(DirEnt[iD],sParam);
		DirEnt[iD].iLab = pRet->iLabel;
	  }
	}
	else if (DirEnt[iD].itype==112)
	{
	//Iges paramtric spline Curve 
	  if (DirEnt[iD].iFrmNo==0)
	  {
		pRet=SplineCurveIges(DirEnt[iD],sParam);
		DirEnt[iD].iLab = pRet->iLabel;
	  }
	}
	else if (DirEnt[iD].itype==110)
	{
	//Iges Line
	  p1.x=ExtractDouble(sParam,2);
	  p1.y=ExtractDouble(sParam,3);
	  p1.z=ExtractDouble(sParam,4);
	  p2.x=ExtractDouble(sParam,5);
	  p2.y=ExtractDouble(sParam,6);
	  p2.z=ExtractDouble(sParam,7);
	  pRet=AddLN(p1,p2,DirEnt[iD].pData,FALSE);
	  DirEnt[iD].iLab = pRet->iLabel;
	}
	else if (DirEnt[iD].itype==116)
	{
	//Iges Point
	  p1.x=ExtractDouble(sParam,2);
	  p1.y=ExtractDouble(sParam,3);
	  p1.z=ExtractDouble(sParam,4);
	  pRet=AddPt(p1,DirEnt[iD].pData,FALSE); 
	  DirEnt[iD].iLab = pRet->iLabel;
	}
	else if (DirEnt[iD].itype==192)
	{
	  int DeLoc,DeAxis,DeRef;
	  double Radius;
	  //Right Circular Cyl
	  DeLoc=(int) ExtractDouble(sParam,2);
	  DeAxis=(int) ExtractDouble(sParam,3);
	  Radius=ExtractDouble(sParam,4);
	  DeRef = (int) ExtractDouble(sParam,5);
	  DeLoc=(DeLoc-1)/2;
	  DeAxis=(DeAxis-1)/2;
	  DeRef=(DeRef-1)/2;
	  sParam=PDat->getPLine(DirEnt[DeLoc].pData,DirEnt[DeLoc].iPLCnt);
	  p1.x=ExtractDouble(sParam,2);
	  p1.y=ExtractDouble(sParam,3);
	  p1.z=ExtractDouble(sParam,4);
	  sParam=PDat->getPLine(DirEnt[DeAxis].pData,DirEnt[DeAxis].iPLCnt);
	  p2.x=ExtractDouble(sParam,2);
	  p2.y=ExtractDouble(sParam,3);
	  p2.z=ExtractDouble(sParam,4);
	  sParam=PDat->getPLine(DirEnt[DeRef].pData,DirEnt[DeRef].iPLCnt);
	  p3.x=ExtractDouble(sParam,2);
	  p3.y=ExtractDouble(sParam,3);
	  p3.z=ExtractDouble(sParam,4);
	  pRet=AddRHDCyl(p2,p1,p3,Radius,DirEnt[iD].pData,FALSE);
	  DirEnt[iD].iLab = pRet->iLabel;
	}
	else if (DirEnt[iD].itype==190)
	{
	  int DeLoc,DeAxis,DeRef;
	  DeLoc=(int) ExtractDouble(sParam,2);
	  DeAxis=(int) ExtractDouble(sParam,3);
	  DeRef = (int) ExtractDouble(sParam,4);
	  DeLoc=(DeLoc-1)/2;
	  DeAxis=(DeAxis-1)/2;
	  DeRef=(DeRef-1)/2;
	  sParam=PDat->getPLine(DirEnt[DeLoc].pData,DirEnt[DeLoc].iPLCnt);
	  p1.x=ExtractDouble(sParam,2);
	  p1.y=ExtractDouble(sParam,3);
	  p1.z=ExtractDouble(sParam,4);
	  sParam=PDat->getPLine(DirEnt[DeAxis].pData,DirEnt[DeAxis].iPLCnt);
	  p2.x=ExtractDouble(sParam,2);
	  p2.y=ExtractDouble(sParam,3);
	  p2.z=ExtractDouble(sParam,4);
	  sParam=PDat->getPLine(DirEnt[DeRef].pData,DirEnt[DeRef].iPLCnt);
	  p3.x=ExtractDouble(sParam,2);
	  p3.y=ExtractDouble(sParam,3);
	  p3.z=ExtractDouble(sParam,4);
	  pRet=AddPlainSurf(p1,p2,p3,DirEnt[iD].pData,FALSE);
	  DirEnt[iD].iLab = pRet->iLabel;
	}
}
return (pRet);
}

IgesD DirEnt[100000];

void InitIgesD()
{
int i;
for (i=0;i<100000;i++)
  DirEnt[i].pO=NULL;
}

int DEIndex(int iDE)
{
    return((iDE-1)/2);
}

void DBase::S_ImportIges(FILE* pFile,CString inName)
{
InitIgesD();
InvalidateOGL();
outtext1(inName);
int iStop=0;
int i,j;
char s1[82];
char type;
CString S;
int iTYPE;
int iPREF;
int iDDD;
int iDES;
int iN1;
int iN2;
int iPTO;
int iSPTR;
int iBPTR;
int iCRTN;
int iCV;
int iN;
int iSURF;
int iOF;
int iLOOP;
int iSENSE;
int iNo=0;
int ii;
int iDE;
IgesP* PDat = new IgesP();
int iDirCount=0;
int iPDatCount = 0;
C3dVector p1;
C3dVector p2;
C3dVector p3;
BOOL isOk;
outtext1("STARTED IGES READ");
do
{
	if (fgets(s1,82,pFile)!=NULL)
	{
		S=s1;
		type=s1[72];
		//outtext1(s1);
		if (type=='D')
		{

			DirEnt[iDirCount].itype=atoi(S.Mid(0,8));
			DirEnt[iDirCount].pData=atoi(S.Mid(8,8));
			DirEnt[iDirCount].pStruct=atoi(S.Mid(16,8));
			DirEnt[iDirCount].pLFont=atoi(S.Mid(24,8));
			DirEnt[iDirCount].pLevel=atoi(S.Mid(32,8));
			DirEnt[iDirCount].pView=atoi(S.Mid(40,8));
			DirEnt[iDirCount].pTForm=atoi(S.Mid(48,8));
			DirEnt[iDirCount].pLabAss=atoi(S.Mid(56,8));
			DirEnt[iDirCount].iStat=atoi(S.Mid(64,8));
			DirEnt[iDirCount].iSeq=atoi(S.Mid(73,7));
			fgets(s1,82,pFile);
			S=s1;
			DirEnt[iDirCount].iWght=atoi(S.Mid(8,8));
			DirEnt[iDirCount].iCol=atoi(S.Mid(16,8));
			DirEnt[iDirCount].iPLCnt=atoi(S.Mid(24,8));
			DirEnt[iDirCount].iFrmNo=atoi(S.Mid(32,8));
			DirEnt[iDirCount].iLab=atoi(S.Mid(56,8));
			DirEnt[iDirCount].iSubNo=atoi(S.Mid(64,8));
			iDirCount++;
		}
		else if (type=='P')
		{
			//outtext1(S);
			PDat->Add(S);
			iPDatCount++;
		}
	}
if (feof(pFile))
	{
		//printf("\nEND OF FILE\n");
		iStop = 1;     
	}
	iNo++;
	//if (iNo==100000)
	//	  iStop=1;
 }
while (iStop == 0);
outtext1("FINISED IGES D");
CString sParam;
CString sParam2;
CString sParam3;  //iDirCount
char sDE[80];
for (i = 0; i<iDirCount; i++)
{
	if (i % 100 == 0)
	{
		sprintf_s(sDE, "DE : %i of %i", i, iDirCount);
		outtext1(_T(sDE));
	}
  //These type left here require other DEs
  //for there creation
	if (i==256) 
	{
		i=256;
	}
	if (DirEnt[i].itype==120)
	{
		//Iges Surface of revolution
		NSurf* pS=NULL;
		sParam=PDat->getPLine(DirEnt[i].pData,DirEnt[i].iPLCnt);
		int L1=(int) ExtractDouble(sParam,2);
		int L2=(int) ExtractDouble(sParam,3);
		double dS=(double) ExtractDouble(sParam,4);
		double dE=(double) ExtractDouble(sParam,5);
		L1=(L1-1)/2;
		L2=(L2-1)/2;
		G_Object* pl1=GetBasicIGESType(L1,DirEnt,PDat);
		G_Object* pl2=GetBasicIGESType(L2,DirEnt,PDat);
		if (pl2==NULL)
		{
			int ttt=DirEnt[L2].itype;
		}
		DirEnt[i].pO=RevSurfIges(pl1,pl2,dS,dE);
	}
	else  // These types maybe needed for higher level types
	{     // Better to extract in a function returning there object
		DirEnt[i].pO=GetBasicIGESType(i,DirEnt,PDat);
	}
}
//All object we support have been read and created
//Their pointers are stored in the DE entry
//Now we need to trim the surfaces
ObjList* Curves = new ObjList();
ObjList* ParaCurves = new ObjList();
//goto FRED;
//for (i=0;i<iDirCount;i++)
for (i = 0; i<iDirCount; i++)
{
  //These type left here require other DEs
  //for there creation
  if (i % 100 == 0)
  {
	  sprintf_s(sDE, "2nd PASS DE : %i of %i", i, iDirCount);
	  outtext1(_T(sDE));
  }
  if (DirEnt[i].itype==144)  //Trim Surface Curves are in Paremetric space
  {
    Curves->Clear();
	ParaCurves->Clear();
    sParam=PDat->getPLine(DirEnt[i].pData,DirEnt[i].iPLCnt);
    iDDD=(int) ExtractDouble(sParam,1);
    iDES=(int) ExtractDouble(sParam,2);
    iN1=(int) ExtractDouble(sParam,3);
    iN2=(int) ExtractDouble(sParam,4);
    iPTO=(int) ExtractDouble(sParam,5);
    G_Object* pS=DirEnt[DEIndex(iDES)].pO;
    //iPTO Directory entry of the trimming curve
    sParam2=PDat->getPLine(DirEnt[DEIndex(iPTO)].pData,DirEnt[DEIndex(iPTO)].iPLCnt);
    iCRTN=(int) ExtractDouble(sParam2,2);
    iSPTR=(int) ExtractDouble(sParam2,3); //Pointer to Surface
    iBPTR=(int) ExtractDouble(sParam2,4); //iBPTR Pointer to thye conposite curve loop
    sParam2=PDat->getPLine(DirEnt[DEIndex(iBPTR)].pData,DirEnt[DEIndex(iBPTR)].iPLCnt);
    iNo;
    ii;
    iDE;
    if (DirEnt[DEIndex(iBPTR)].itype==102)   //Composite curve;
    {
       iNo=(int) ExtractDouble(sParam2,2);
       for (ii=0;ii<iNo;ii++)
       { 
          iDE=(int) ExtractDouble(sParam2,ii+3);
          Curves->Add(DirEnt[DEIndex(iDE)].pO);
       }
       if (pS->iLabel==280) 
       {
         iNo=iNo;
       }
       AddSurfBoundIGES(pS,Curves);
    }
    for (j=0;j<iN2;j++) //Internal trim loops
    {
      iBPTR=(int) ExtractDouble(sParam,6+j);
      sParam2=PDat->getPLine(DirEnt[DEIndex(iBPTR)].pData,DirEnt[DEIndex(iBPTR)].iPLCnt);
      iCRTN=(int) ExtractDouble(sParam2,2);
      iSPTR=(int) ExtractDouble(sParam2,3); //Pointer to Surface
      iBPTR=(int) ExtractDouble(sParam2,4); //iBPTR Pointer to thye conposite curve loop
      sParam3=PDat->getPLine(DirEnt[DEIndex(iBPTR)].pData,DirEnt[DEIndex(iBPTR)].iPLCnt);
      Curves->Clear();
      if (DirEnt[DEIndex(iBPTR)].itype==102)   //Composite curve;
      {
         iNo=(int) ExtractDouble(sParam3,2);
         for (ii=0;ii<iNo;ii++)
         { 
            iDE=(int) ExtractDouble(sParam3,ii+3);
            Curves->Add(DirEnt[DEIndex(iDE)].pO);
         } 
         AddSurfBoundTrimLoopIGES(pS,Curves);
      }
    }
  }
  if (DirEnt[i].itype == 141)  //Boundary Entity in Model Space
  {
	  Curves->Clear();
	  sParam = PDat->getPLine(DirEnt[i].pData, DirEnt[i].iPLCnt);
	  iTYPE = (int)ExtractDouble(sParam, 2);
	  if (iTYPE == 0)  // Then all are model space curves - misxed model / paremetric will have to be delt with
	  {
		  Curves->Clear();
		  iPREF = (int)ExtractDouble(sParam, 3);    //Preference of representation of owner system
		  iSPTR = (int)ExtractDouble(sParam, 4);    //The surface DE
		  G_Object* pS = DirEnt[DEIndex(iSPTR)].pO; //Ptr to surface to bound
		  iN1 = (int)ExtractDouble(sParam, 5);      //Number of curves
		  //this repeats for iN1 curves
		  int iCC=6;
		  for (j = 0; j < iN1; j++)
		  {
			  iCV = (int)ExtractDouble(sParam, iCC);      //The curve DE
			  iCC++;
			  iSENSE = (int)ExtractDouble(sParam, iCC);   //Need reversal
			  iCC++;
			  iN2 = (int)ExtractDouble(sParam, iCC);      //no of paremetic curves should be 0 as iTYPE is 0
			  iCC++;
			  NCurve* pC = (NCurve*)DirEnt[DEIndex(iCV)].pO;
			  if (iSENSE == 2)
				  pC->Reverse();
			  Curves->Add(pC);
		  }
		  AddSurfBoundIGES2(pS, Curves);
	  }
  }
  if (DirEnt[i].itype == 510)  //FACE ENTITY
  {
	  sParam = PDat->getPLine(DirEnt[i].pData, DirEnt[i].iPLCnt);
	  iSURF = (int)ExtractDouble(sParam, 2);
	  iN = (int)ExtractDouble(sParam, 3);
	  iOF = (int)ExtractDouble(sParam, 4);;  //Outer loop flag
	  NSurf* pS = (NSurf*)DirEnt[DEIndex(iSURF)].pO;
	  if (pS->iLabel == 46)
	  {
		  pS->iLabel = 46;
	  }
	  DirEnt[i].pO = pS;
	  for (j = 0; j < iN; j++)
	  {   //DE OF TRIM LOOP IF iOF=1 THEN OUTER LOOP
		  Curves->Clear();
		  ParaCurves->Clear();
		  iLOOP = (int)ExtractDouble(sParam, 5+j);
		  {
			  isOk = TrimLoop508(iSURF, PDat, iLOOP, Curves, ParaCurves, iOF);
			  if (isOk)
			  {
				  if ((iOF == 1) && (j==0))
				  {
						pS->UserTrim(ParaCurves);
				  }
				  else
				  {
						pS->InternalTrim(ParaCurves);
				  }
			  }
		  }
	  }
	  //All model space curves for the loop are in curves - now need curve on surfaces

  }
}
//Parse for shells and brep
for (i = 0; i < iDirCount; i++) //iDirCount
{
	if (DirEnt[i].itype == 186)  //BREP SOLID
	{
		//Create a new part and add to database;
		Part* pPart = new Part(iPartLabCnt);
		pCurrentPart = pPart;
		pPart->sName = "IGES_READ";
		iPartLabCnt++;
		int iSHELL;
		BOOL bORIENT;
		outtext1("BREP FOUND");
		sParam = PDat->getPLine(DirEnt[i].pData, DirEnt[i].iPLCnt);
		iSHELL = (int)ExtractDouble(sParam, 2);
		bORIENT = (int)ExtractDouble(sParam, 3);
		iN = (int)ExtractDouble(sParam, 4);
		AddShell514(pPart, iSHELL, PDat, bORIENT);
		for (j = 0; j < iN * 2; j += 2)
		{
			iSHELL = (int)ExtractDouble(sParam, 5+j);
			bORIENT = (int)ExtractDouble(sParam,5+j+1);
			AddShell514(pPart, iSHELL, PDat, bORIENT);
		}
		CleanFromDB(pPart);
		pPart->CurveColour(151);
		pPart->SurfColour(135);
		AddObj(pPart);
	}
}
//FRED:
delete(Curves);
delete(ParaCurves);
delete(PDat);
outtext1("FINISHED IGES READ");
InvalidateOGL();
S_Count = 0;
ReDraw();

}

Shell* DBase::AddShell514(Part* pP, int iDE, IgesP* PDat, BOOL bOrient)
{
	CString sParam;
	int j;
	int iN;
	int iFACE;
	int iORIENT;
	NSurf* pSurf;
	Face* pF;
	Shell* pShell = new Shell();
	sParam = PDat->getPLine(DirEnt[DEIndex(iDE)].pData, DirEnt[DEIndex(iDE)].iPLCnt);
	iN = (int)ExtractDouble(sParam, 2);
	for (j = 0; j < iN * 2; j += 2)
	{
		iFACE = (int)ExtractDouble(sParam, 2 + j + 1);
		pSurf = (NSurf*)DirEnt[DEIndex(iFACE)].pO;
		iORIENT = (int)ExtractDouble(sParam, 2 + j + 2);
		pF = new Face(pSurf, iORIENT);
		pP->AddSurf(pF);
		pShell->AddFace(pF, iORIENT,pP->iFaceLab);
		pP->iFaceLab++;
	}
	pP->AddShell(pShell);		//Add the shell to the part

	return (pShell);
}

void DBase::CleanFromDB(Part* pP)
{
	//cLinkedList pPartV;		//Vertices used in Part
	//cLinkedList pPartC;		//Space curves used in part
	//cLinkedList pPartS;		//Space Surfaces used in part
	G_Object* pNext;
	pNext = pP->pPartS.Head;
	while (pNext != NULL)
	{
		RemObjNoDel(pNext);
		pNext = (G_Object*)pNext->next;
	}
	pNext = pP->pPartC.Head;
	while (pNext != NULL)
	{
		RemObjNoDel(pNext);
		pNext = (G_Object*)pNext->next;
	}
	pNext = pP->pPartV.Head;
	while (pNext != NULL)
	{
		RemObjNoDel(pNext);
		pNext = (G_Object*)pNext->next;
	}
}


//Trimes a nurbs surfacwe from Iges trim loop 508
//for now oly type edge not vertex supported
BOOL DBase::TrimLoop508(int iS,IgesP* PDat, int iLOOP, ObjList* Curves, ObjList* ParaCurves,BOOL bOut)
{
	CString sParam;
	CString sParamEDE;
	CString sParamPTDE;
	BOOL brc=FALSE;
	NCurveOnSurf* pCurve2;
	int iN;
	int i;
	int iTYPE;
	int iELST;
	int iCnt;
	int iLSTIND;
	int iORIENT;
	int iK;
	int iSVP;
	int iSV;
	int iTVP;
	int iTV;
	C3dVector p1;
	C3dVector p2;
	NCurve* pMC;
	NSurf* pSurf;
	pSurf = (NSurf*)DirEnt[DEIndex(iS)].pO;
	if (pSurf->iLabel == 36)
		pSurf->iLabel = 36;
	sParam = PDat->getPLine(DirEnt[DEIndex(iLOOP)].pData, DirEnt[DEIndex(iLOOP)].iPLCnt);
	iN = (int)ExtractDouble(sParam, 2);
	iCnt = 3;
	int iLST_DE = -1;
	Vec<int> bOrient(iN);
	for (i = 0; i < iN; i++)
	{
		iTYPE = (int)ExtractDouble(sParam, iCnt);  //ITYPE MUST BE EDGE =0 until we can deal with type vertex
		iCnt++;
		iELST = (int)ExtractDouble(sParam, iCnt);  //The Edge List DE
		iCnt++;
		//get the edge list parametric data line
		if (iLST_DE != iELST)
		{
			sParamEDE = PDat->getPLine(DirEnt[DEIndex(iELST)].pData, DirEnt[DEIndex(iELST)].iPLCnt);
			iLST_DE = iELST;
		}
		iLSTIND = (int)ExtractDouble(sParam, iCnt);  //The Edge List Index of the curve
		iCnt++;
		iORIENT = (int)ExtractDouble(sParam, iCnt);  //The orientation of the curve
		iCnt++;
		iK = (int)ExtractDouble(sParam, iCnt);  //No off underline param curves must be 0 for now
		iCnt++;
		//Need to read the Edge List and find the curve ptr
		int iCURVEDE;
		iCURVEDE = (int)ExtractDouble(sParamEDE, (iLSTIND - 1) * 5 + 3);
		//End points;
		iSVP = (int)ExtractDouble(sParamEDE, (iLSTIND - 1) * 5 + 4);
		sParamPTDE = PDat->getPLine(DirEnt[DEIndex(iSVP)].pData, DirEnt[DEIndex(iSVP)].iPLCnt);
		iSV = (int)ExtractDouble(sParamEDE, (iLSTIND - 1) * 5 + 5);
		iSV -= 1;
	    p1.x=ExtractDouble(sParamPTDE, iSV *3+3);
	    p1.y=ExtractDouble(sParamPTDE, iSV *3+4);
	    p1.z=ExtractDouble(sParamPTDE, iSV *3+5);
		iTVP = (int)ExtractDouble(sParamEDE, (iLSTIND - 1) * 5 + 6);
		sParamPTDE = PDat->getPLine(DirEnt[DEIndex(iTVP)].pData, DirEnt[DEIndex(iTVP)].iPLCnt);
		iTV = (int)ExtractDouble(sParamEDE, (iLSTIND - 1) * 5 + 7);
		iTV -= 1;
		p2.x = ExtractDouble(sParamPTDE, iTV * 3 + 3);
		p2.y = ExtractDouble(sParamPTDE, iTV * 3 + 4);
		p2.z = ExtractDouble(sParamPTDE, iTV * 3 + 5);
		//End End Points
		bOrient(i) = iORIENT;
		int aaaa = bOrient(i);
		pMC = (NCurve*) DirEnt[DEIndex(iCURVEDE)].pO;
		pMC->vS = p1;
		pMC->vE = p2;
		if (pMC != NULL)
		{
			Curves->Add(pMC);
		}
	}
	if (pSurf->iLabel == 7)
		pSurf->iLabel = 7;
	if (Curves->iNo != iN)
	{
		
	}
	else
	{
		brc = CurvesToSurface508(iS, PDat, Curves, ParaCurves, bOrient);
		pCurve2 = (NCurveOnSurf*)ParaCurves->Objs[i];
		//Add the curves to the surface
		if (brc)
		{
			for (i = 0; i < ParaCurves->iNo; i++)
			{
				pCurve2 = (NCurveOnSurf*)ParaCurves->Objs[i];
				pSurf->AddTrimCurveExp(pCurve2);
			}
		}

	}
	bOrient.clear();
	return (brc);
}

BOOL DBase::CurvesToSurface508(int iS, IgesP* PDat, ObjList* Curves, ObjList* ParaCurves, Vec<int> bOrient)
{
	BOOL bret = TRUE;
	NSurf* pSurf;
	pSurf = (NSurf*) DirEnt[DEIndex(iS)].pO;
	int i;
	if (pSurf->iLabel == 25)
		i = 0;
	BOOL isClosedU = pSurf->isClosedinU();
	BOOL isClosedV = pSurf->isClosedinV();
	NCurve* pSC;
	C3dVector pt;
	NCurveOnSurf* pS = NULL;
	BOOL bIsCv = FALSE;
	C3dVector p3dC;
	C3dVector pSf;
	C3dVector pSfS;
	C3dVector pSfE;
	C3dVector pTST;
	C3dVector pTPre;
	int iIso=-1;
	int iSt = 0;
	BOOL bPlainar = pSurf->isPlanar();
	NCurveOnSurf* cPre;
	if (bPlainar) 
	{
		//Hopefull if its a planar surface its an easy case?
		for (i = 0; i < Curves->iNo; i++)
		{
			pSC = (NCurve*)Curves->Objs[i];
			pS = pSC->GetSurfaceCV(pSurf);
			if (pS != NULL)
			{
				if (!bOrient(i))
				{
					pS->Reverse();
					pS->bOrient = bOrient(i);
				}
				pS->pSC = pSC;  //Attach the space curve reference
				ParaCurves->Add(pS);
			}
		}
		bret = TRUE;
	}
	else
	{
		if (isClosedU)
		{
			//IF the surface is closed in U we need to find a curve in U to start chain
			//or we ay find a projection problem where a min point can be 0 or 1
			//we can check the curve in the closed direction for the 0-1 problem buy 
			//looking at the value as say 0.1 or 0.99 to see if they agree
			iSt = FindCurveInU(Curves,pSurf);
		}
		else if (isClosedV)
		{
			//IF the surface is closed in V we need to find a curve in V to start chain
			iSt = FindCurveInV(Curves, pSurf);
		}
		else
		{
			//Not closed we don't anticipate any problems with projecting points
			//to the surface.
			iSt = 0;

		}
		//Also do need to consider case of a sphere which ia an exception not
		//covered - closed but only has 2 set of coincident trim curves
		BOOL bFirst = TRUE;
		if (iSt != 0)
		{
			Curves->ReOrder(iSt);
			bOrient.ReOrder(iSt);
			iSt = 0;
		}
		for (i = iSt; i < Curves->iNo; i++) 
		{
			pSC = (NCurve*) Curves->Objs[i];
			iIso = pSC->isIsoCurve(pSurf);
			if (iIso > -1)
				pS = GetIsoCurve(pSurf, pSC, iIso, TRUE);
			else
			    pS = pSC->GetSurfaceCV4(pSurf); //this the planar version
												//INCORRECT
			if ((!bOrient(i)) && (pS!=NULL))
			{
				pS->Reverse();
				pS->bOrient = bOrient(i);
			}
			//Now need to chain ends make sure all is ok
			if ((!bFirst) && (pS != NULL))
			{

				cPre = (NCurveOnSurf*) ParaCurves->Objs[ParaCurves->iNo-1];
				pTPre = cPre->GetLastPt();
				pS->cPts[0]->Pt_Point->x = pTPre.x;
				pS->cPts[0]->Pt_Point->y = pTPre.y;
				if (iIso==1)
					pS->cPts[1]->Pt_Point->x = pTPre.x;
				if (iIso == 2)
					pS->cPts[1]->Pt_Point->y = pTPre.y;
			}
			bFirst = FALSE;
			if (pS != NULL)
			{
				pS->pSC = pSC;  //Attach the space curve reference
				ParaCurves->Add(pS);
			}

			//*********************************************************
		}
		for (i = 0; i < Curves->iNo-1; i++)
		{
			cPre = (NCurveOnSurf*)ParaCurves->Objs[i];
			pTPre = cPre->GetLastPt();
			NCurveOnSurf* pCF = (NCurveOnSurf*)ParaCurves->Objs[i+1];
			pCF->cPts[0]->Pt_Point->x = pTPre.x;
			pCF->cPts[0]->Pt_Point->y = pTPre.y;
			pCF->cPts[0]->Pt_Point->z = 0;
		}
		cPre = (NCurveOnSurf*)ParaCurves->Objs[Curves->iNo - 1];
		pTPre = cPre->GetLastPt();
		NCurveOnSurf* pCF = (NCurveOnSurf*)ParaCurves->Objs[0];
		pCF->cPts[0]->Pt_Point->x = pTPre.x;
		pCF->cPts[0]->Pt_Point->y = pTPre.y;
		pCF->cPts[0]->Pt_Point->z = 0;
	}

	return(bret);
}

int DBase::FindCurveInU(ObjList* Curves, NSurf* pSurf)  //Return index of curve that varies in V on surface
{
	int iret = -1;
	int i;
	NCurve* pC;
	C3dVector vSS;
	C3dVector vSE;
	C3dVector vPS;
	C3dVector vPE;
	double dU;
	double dMaxU=0;

	for (i = 0; i < Curves->iNo; i++)
	{
		pC = (NCurve*) Curves->Objs[i];
		vSS = pC->GetPt(0.1);
		vSE = pC->GetPt(0.9);
		vPS = pSurf->MinPtW(vSS);
		vPE = pSurf->MinPtW(vSE);
		dU = abs(vPS.x - vPE.x); //Change on surface in U
		if ((dU > dMaxU) && (dU < 0.95))
		{
			iret = i;
			dMaxU = dU;
		}
	}
	return (iret);
}

int DBase::FindCurveInV(ObjList* Curves, NSurf* pSurf)  //Return index of curve that varies in V on surface
{
	int iret = -1;
	int i;
	NCurve* pC;
	C3dVector vSS;
	C3dVector vSE;
	C3dVector vPS;
	C3dVector vPE;
	double dV;
	double dMaxV = 0;

	for (i = 0; i < Curves->iNo; i++)
	{
		pC = (NCurve*)Curves->Objs[i];
		vSS = pC->GetPt(0.1);
		vSE = pC->GetPt(0.9);
		vPS = pSurf->MinPtW(vSS);
		vPE = pSurf->MinPtW(vSE);
		dV = abs(vPS.y - vPE.y); //Change on surface in U
		if ((dV > dMaxV) && (dV<0.95))
		{
			iret = i;
			dMaxV = dV;
		}
	}
	return (iret);
}

BOOL  DBase::EndChecks(ObjList* Curves, ObjList* ParaCurves)
{
	bool brc = FALSE;
	int i;
	int j;
	NCurveOnSurf* p1;
	if (Curves->iNo == ParaCurves->iNo)
	{
		for (i = 0; i < ParaCurves->iNo; i++)
		{
			p1 = (NCurveOnSurf*) ParaCurves->Objs[i];
			for (j = 0; j < p1->iNoCPts; j++)
			{
				if (p1->cPts[j]->Pt_Point->x < 0)
					p1->cPts[j]->Pt_Point->x = 0;
				if (p1->cPts[j]->Pt_Point->x > 1)
					p1->cPts[j]->Pt_Point->x = 1;
				if (p1->cPts[j]->Pt_Point->y < 0)
					p1->cPts[j]->Pt_Point->y = 0;
				if (p1->cPts[j]->Pt_Point->y > 1)
					p1->cPts[j]->Pt_Point->y = 1;
			}
			//p2 = (NCurveOnSurf*) ParaCurves->Objs[i+1];
			//p2->cPts[0]->Pt_Point->x = p1->cPts[p1->iNoCPts - 1]->Pt_Point->x;
			//p2->cPts[0]->Pt_Point->y = p1->cPts[p1->iNoCPts - 1]->Pt_Point->y;
		}
	}

	return (brc);
}

NCurveOnSurf* DBase::GetIsoCurve(NSurf* pSurf, NCurve* pSC,int iIso,BOOL EndChk)
{
	NCurveOnSurf* pS=NULL;
	C3dVector p3dC;
	C3dVector pSfS;
	C3dVector pSfE;
	C3dVector pTST;
	p3dC = pSC->GetPt(pSC->ws);
	pSfS = pSurf->MinPtW(p3dC);
	p3dC = pSC->GetPt(pSC->we);
	pSfE = pSurf->MinPtW(p3dC);

	if (EndChk)
	{
		pSC->EndPtChk01(pSurf, pSC->ws, &pSfS, pSC->we, &pSfE);
	}
	pS = CreateTrimLine(pSurf, pSC, pSfS, pSfE);
	return (pS);
}

NCurveOnSurf* DBase::CreateTrimLine(NSurf* pSurf,NCurve* pSC,C3dVector v1,C3dVector v2)
{
	NCurveOnSurf* pS = new NCurveOnSurf();
	pS->iLabel = pSC->iLabel;
	pS->p = 1;
	pS->ws = pSC->ws;
	pS->we = pSC->we;
	pS->pParent = pSurf;
	pS->AddVert(v1, 1);
	pS->AddVert(v2, 1);
	pS->knots[0] = 0.0;
	pS->knots[1] = 0.0;
	pS->knots[2] = 1.0;
	pS->knots[3] = 1.0;
	return (pS);
}

NSurf* DBase::RevSurfIges(G_Object* pAxis,G_Object* pGen,double dS,double dE)
{
BOOL bErr;
C3dVector vN;
C3dVector vC;
NSurfR* pS=NULL;
double dP1;
double dP2;
dP1=dS/(2*Pi);
dP2=dE/(2*Pi);
double dT;
dT=dP2-dP1;
if (dT > 1)
dT = 1.0;
if ((pAxis->iObjType == 7) && (pAxis->iType == 2) && (pGen!=NULL))
{
  vN=pAxis->GetDir(0.5);
  vC=pAxis->GetPt(0.0);
    if (pGen->iObjType == 7) 
    {
	  pS = new NSurfR();
      pS->Create((NCurve*) pGen,vN,vC,0,NULL,dS);
      bErr=pS->Generate(2,0,dT);
      pS->dVs=dS;
      if (bErr==TRUE)
      {
        delete(pS);
        outtext1("ERROR: Cannot Build Surface.");
        outtext1("Check Order and Number Off Points.");
      }
      else
      {
        DB_Obj[DB_ObjectCount]=pS;
        DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
        Dsp_Add(pS);
        pS->iLabel=iSFLabCnt;
        iSFLabCnt++;
        DB_ObjectCount++;
        AddTempGraphics(pS);
      }
    }
  //ReDraw();
}

return (pS);
}

NSurf* DBase::BSurfIges(IgesD DE,CString PLine)
{
int i;
C3dVector cPts[10000];
double wghts[10000];
double KnotsU[200];
double KnotsV[200];
int noU= (int) ExtractDouble(PLine,2)+1;
int noV= (int) ExtractDouble(PLine,3)+1;
int pInU=(int) ExtractDouble(PLine,4);
int pInV=(int) ExtractDouble(PLine,5);
int iCnt=11;
double dSpU;
double dFU;
double dSpV;
double dFV;
for(i=0;i<noU+pInU+1;i++)
{
  KnotsU[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}
dSpU=KnotsU[noU+pInU]-KnotsU[0];
dFU=KnotsU[0];

for(i=0;i<noU+pInU+1;i++)
{
  KnotsU[i]=(KnotsU[i]-dFU)/dSpU;
  if (KnotsU[i]<0) KnotsU[i]=0;
  if (KnotsU[i]>1) KnotsU[i]=1;
}

for(i=0;i<noV+pInV+1;i++)
{
  KnotsV[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}
dSpV=KnotsV[noV+pInV]-KnotsV[0];
dFV=KnotsV[0];
for(i=0;i<noV+pInV+1;i++)
{
  KnotsV[i]=(KnotsV[i]-dFV)/dSpV;
  if (KnotsV[i]<0) KnotsV[i]=0;
  if (KnotsV[i]>1) KnotsV[i]=1;
}

double dUs=KnotsU[0];
double dVs=KnotsV[0];
//Need to sort this not vet
//KnotsU[0]=0;
//KnotsU[1]=0;
//KnotsU[2]=1;
//KnotsU[3]=1;
//KnotsV[0]=0;
//KnotsV[1]=0;
//KnotsV[2]=1;
//KnotsV[3]=1;
for(i=0;i<noU*noV;i++)
{
  wghts[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}
double x,y,z;
for(i=0;i<noU*noV+1;i++)
{
  x=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  y=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  z=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  cPts[i].Set(x,y,z);
}

NSurf* pS=new NSurf();
pS->iLabel = DE.iLab;
pS->dUs=dFU;
pS->dVs=dFV;
pS->dUspan=dSpU;
pS->dVspan=dSpV;
pS->GenerateExp(cPts,
                wghts,
                KnotsU,
                KnotsV,
                noU,
                noV,
                pInU,
                pInV);
pS->TrimLoop(0.0,1.0,0.0,1.0);
pS->iLabel=iCVLabCnt;
iCVLabCnt++;

AddObj(pS);
//ReDraw();
return(pS);
}

NCurve* DBase::SplineCurveIges(IgesD DE,CString PLine)
{
int i;
int iCTYPE= (int) ExtractDouble(PLine,2);
int iDIM= (int) ExtractDouble(PLine,4);
int iNoSegs= (int) ExtractDouble(PLine,5);
Vec<double> BreakPts;
BreakPts.Size(iNoSegs+1);
Vec<double> AX; AX.Size(iNoSegs);
Vec<double> BX; BX.Size(iNoSegs);
Vec<double> CX; CX.Size(iNoSegs);
Vec<double> DX; DX.Size(iNoSegs);
Vec<double> AY; AY.Size(iNoSegs);
Vec<double> BY; BY.Size(iNoSegs);
Vec<double> CY; CY.Size(iNoSegs);
Vec<double> DY; DY.Size(iNoSegs);
Vec<double> AZ; AZ.Size(iNoSegs);
Vec<double> BZ; BZ.Size(iNoSegs);
Vec<double> CZ; CZ.Size(iNoSegs);
Vec<double> DZ; DZ.Size(iNoSegs);

int iCnt=6;
for(i=0;i<iNoSegs+1;i++)
{
  BreakPts[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}
for(i=0;i<iNoSegs;i++)
{
  AX[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  BX[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  CX[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  DX[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;

  AY[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  BY[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  CY[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  DY[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;

  AZ[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  BZ[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  CZ[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  DZ[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}

double du;
double dx;
double dy;
double dz;
int iN=2;
int j;
double ds;
for(i=0;i<iNoSegs;i++)
{
  ds=BreakPts[i+1]-BreakPts[i];
  ds=ds/iN;
  for(j=0;j<iN+1;j++)
  {
    du=ds*j;
	dx=AX[i]+BX[i]*du+CX[i]*du*du+DX[i]*du*du*du;
	dy=AY[i]+BY[i]*du+CY[i]*du*du+DY[i]*du*du*du;
	dz=AZ[i]+BZ[i]*du+CZ[i]*du*du+DZ[i]*du*du*du;
	AddPt2(dx,dy,dz,-1);
  }
  //AddPt2(AX[i],AY[i],AZ[i],-1);
}
return (NULL);
}

NCurve* DBase::BCurveIges(IgesD DE,CString PLine)
{
int i;
Vec<C4dVector> cPts;
Vec<double> knots;


int noU= (int) ExtractDouble(PLine,2)+1;
int pInU=(int) ExtractDouble(PLine,3);

cPts.Size(noU);
knots.Size(noU+pInU+1);

int iCnt=8;
for(i=0;i<noU+pInU+1;i++)
{
  knots[i]=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}
//not sure about this
double dSpan;
double dSt;
dSt=knots[0];
dSpan=knots[noU+pInU]-knots[0];
for(i=0;i<noU+pInU+1;i++)
{
  knots[i]=(knots[i]-dSt)/dSpan;
}

for(i=0;i<noU;i++)
{
  cPts[i].w=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}

for(i=0;i<noU;i++)
{
  cPts[i].xw=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  cPts[i].yw=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
  cPts[i].zw=(double) ExtractDouble(PLine,iCnt);
  iCnt++;
}
double dS,dE;
dS=(double) ExtractDouble(PLine,iCnt);
iCnt++;
dE=(double) ExtractDouble(PLine,iCnt);
iCnt++;


//
NCurve* pC=new NCurve();

pC->GenerateExp(pInU,cPts,knots);
pC->iLabel = iCVLabCnt;
iCVLabCnt++;
//pS->GenerateExp(cPts,
//                wghts,
//                KnotsU,
//                KnotsV,
//                noU,
//                noV,
//                pInU,
//                pInV);
//pS->TrimLoop(0.0,1.0,0.0,1.0);
//pS->iLabel=DE.pData;
AddObj(pC);
//ReDraw();
return(pC);
}


void DBase::ReDraw()
{

CDC* pDC = pTheView->GetDC();
this->Draw(pModelMat,pDC,5);
pTheView->ReleaseDC(pDC);

}


void DBase::ReGen()
{

CDC* pDC = pTheView->GetDC();
this->Draw(pModelMat,pDC,4);
pTheView->ReleaseDC(pDC);
}
//*****************************************************
// INIT OLG 
//*****************************************************
void DBase::InitOGL(CDC* pDC)
{


m_pDC = pDC;
ASSERT(m_pDC != NULL);
if (!bSetupPixelFormat())
        return;
//n = ::GetPixelFormat(m_pDC->GetSafeHdc());
 //   ::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
//CreateRGBPalette();
hrc = wglCreateContext(m_pDC->GetSafeHdc());
wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

CreateTexture(bRevColBar);
//iOGLList=-1;
}

void DBase::InvalidateOGL()
{
GLenum aa;
if ((DspFlags & DSP_ANIMATION) > 0)
{
	if (iOGLList != -1)
	{
		glDeleteLists(iOGL_Start, iOGL_NoOff);
		aa = glGetError();
	}
	iOGLList = -1;
	iOGL_Start = -1;
	iOGL_NoOff = -1;
}
}

void DBase::SetDrawType(int iType)
{

DB_DrawState = iType;
if (DB_DrawState==0)
{
   if ((DspFlags & DSP_LINE) == 0)
   {
     DspFlags = (DspFlags ^ DSP_LINE);
   }
}
if (DB_DrawState==1)
{
   if ((DspFlags & DSP_LINE) > 0)
   {
     DspFlags = (DspFlags ^ DSP_LINE);
   }
}
}

int DBase::GetDrawType()
{
return(DB_DrawState);
}



void DBase::SetFastView()
{
outtext1("Toggling Node Visbility.");
int iCO;
for (iCO=0;iCO<S_Count;iCO++)
{   
	if (S_Buff[iCO]->iObjType==4)
    {
	   ME_Object* Me = (ME_Object*) S_Buff[iCO];
	   if (Me->bDrawN==TRUE)
	   {
         Me->bDrawN=FALSE;
	   }
	   else
	   {
         Me->bDrawN=TRUE;
	   }
	}   
}

InvalidateOGL();
ReDraw();
}

int DBase::GetFastView()
{
return(iFastView);
}


BOOL DBase::bSetupPixelFormat()
{
    static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL |          // support OpenGL
          PFD_DOUBLEBUFFER,             // double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int pixelformat;

    if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
    {
//        MessageBox("ChoosePixelFormat failed");
        return FALSE;
    }

    if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
//        MessageBox("SetPixelFormat failed");
        return FALSE;
    }

    return TRUE;
}

unsigned char DBase::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
    unsigned char val;

    val = (unsigned char) (i >> shift);
    switch (nbits) 
	{

    case 1:
        val &= 0x1;
        return oneto8[val];
    case 2:
        val &= 0x3;
        return twoto8[val];
    case 3:
        val &= 0x7;
        return threeto8[val];

    default:
        return 0;
    }
}


void DBase::CreateRGBPalette()
{
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE *pPal;
    int n, i;
 
    n = ::GetPixelFormat(m_pDC->GetSafeHdc());
    ::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

    if (pfd.dwFlags & PFD_NEED_PALETTE)
    {
        n = 1 << pfd.cColorBits;
        pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

        ASSERT(pPal != NULL);

        pPal->palVersion = 0x300;
        pPal->palNumEntries = n;
        for (i=0; i<n; i++)
        {
            pPal->palPalEntry[i].peRed =
                    ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
            pPal->palPalEntry[i].peGreen =
                    ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
            pPal->palPalEntry[i].peBlue =
                    ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
            pPal->palPalEntry[i].peFlags = 0;
        }

        /* fix up the palette to include the default GDI palette */
        if ((pfd.cColorBits == 8)                           &
            (pfd.cRedBits   == 3) & (pfd.cRedShift   == 0) &
            (pfd.cGreenBits == 3) & (pfd.cGreenShift == 3) &
            (pfd.cBlueBits  == 2) & (pfd.cBlueShift  == 6)
           )
        {
			for (i = 1 ; i <= 12 ; i++)
                pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
        }

        m_cPalette.CreatePalette(pPal);
        delete pPal;

        m_pOldPalette = m_pDC->SelectPalette(&m_cPalette, FALSE);
        m_pDC->RealizePalette();
    }
}

void DBase::TogMeshD()
{
if (iSH==6)
{
  iSH=4;
  iSW=2;
  outtext1("MeshD Now 4*2");
}
else
{
  iSH=6;
  iSW=4;
  outtext1("MeshD Now 6*4");
}
}

void DBase::DeleteObj()
{
	outtext1("Deleting Selected Items.");
	int iCO = 0;
	int i;
	if (S_Count>0)
	{
		do 
		{  
			if (S_Buff[iCO]->iObjType==4)
			{
				ME_Object* Me = (ME_Object*)S_Buff[iCO];
				if (Me!=pCurrentMesh)
				{
					for (i = 0; i < Me->iElNo; i++)
					{
					   RemObj(Me->pElems[i]);
					   Dsp_Rem(Me->pElems[i]);
					   Dsp_RemGP(Me->pElems[i]);
					}
					for (i = 0; i < Me->iCYS; i++)
					{
					   RemObj(Me->pSys[i]);
					   Dsp_Rem(Me->pSys[i]);
					   Dsp_RemGP(Me->pSys[i]);
					}
					for (i = 0; i < Me->iNdNo; i++)
					{
					   RemObj(Me->pNodes[i]);
					   Dsp_Rem(Me->pNodes[i]);
					   Dsp_RemGP(Me->pNodes[i]);
					}
					for (i = 0; i < Me->iBCLDs; i++)
					{
					   RemObj(Me->pBCLDs[i]);
					   Dsp_Rem(Me->pBCLDs[i]);
					   Dsp_RemGP(Me->pBCLDs[i]);
					}
					RemObj(S_Buff[iCO]);
					Dsp_Rem(S_Buff[iCO]);
					Dsp_RemGP(S_Buff[iCO]);
					Me = NULL;
				}
				else
				{
				   outtext1("ERROR: Cannot Delete the Active Mesh?");
				}

			}
			else if (S_Buff[iCO]->iObjType==3)
			{
     
				ME_Object* Me = (ME_Object*) S_Buff[iCO]->pParent;
				if (Me->CanDeleteEl((E_Object*) S_Buff[iCO])==TRUE)
				{
					//RemObj(S_Buff[iCO]);
					Dsp_Rem(S_Buff[iCO]);
					Dsp_RemGP(S_Buff[iCO]);
					Me->DeleteEl((E_Object*)S_Buff[iCO]);
				}
			} 
			else if (S_Buff[iCO]->iObjType==12)
			{
				ME_Object* Me = (ME_Object*) S_Buff[iCO]->pParent;
				if (Me->DeleteCys((CoordSys*) S_Buff[iCO])==TRUE)
				{
					//RemObj(S_Buff[iCO]);
					Dsp_Rem(S_Buff[iCO]);
					Dsp_RemGP(S_Buff[iCO]);
				}
			} 
			else if ((S_Buff[iCO]->iObjType==321) || 
				(S_Buff[iCO]->iObjType==322) || 
				(S_Buff[iCO]->iObjType==323) || 
				(S_Buff[iCO]->iObjType==324) || 
				(S_Buff[iCO]->iObjType==325) || 
				(S_Buff[iCO]->iObjType==326) || 
				(S_Buff[iCO]->iObjType==327) || 
				(S_Buff[iCO]->iObjType==328) || 
				(S_Buff[iCO]->iObjType==329) ||
				(S_Buff[iCO]->iObjType==331) ||
				(S_Buff[iCO]->iObjType==332))
			{
				ME_Object* Me = (ME_Object*) S_Buff[iCO]->pParent->pParent;
				if (Me->DeleteBC((BCLD*) S_Buff[iCO])==TRUE)
				{
					Dsp_Rem(S_Buff[iCO]);
					Dsp_RemGP(S_Buff[iCO]);
				}
			} 
			else if (S_Buff[iCO]->iObjType==1)
			{
				ME_Object* Me = (ME_Object*) S_Buff[iCO]->pParent;
				if (Me->DeleteNd((Node*) S_Buff[iCO])==TRUE)
				{
					//RemObj(S_Buff[iCO]);
					Dsp_Rem(S_Buff[iCO]);
					Dsp_RemGP(S_Buff[iCO]);
				}
			}  
			else if((S_Buff[iCO]->iObjType==0) || (S_Buff[iCO]->iObjType==2) ||(S_Buff[iCO]->iObjType==5) || (S_Buff[iCO]->iObjType==6) ||(S_Buff[iCO]->iObjType==7) || (S_Buff[iCO]->iObjType == 10) || (S_Buff[iCO]->iObjType==15) || (S_Buff[iCO]->iObjType==18) || (S_Buff[iCO]->iObjType==500))
			{
				if (S_Buff[iCO]->pParent==NULL)
				{
					RemObj(S_Buff[iCO]);
					Dsp_Rem(S_Buff[iCO]);
					Dsp_RemGP(S_Buff[iCO]);
				}
				else
				{//************************************
					if (S_Buff[iCO]->pParent->iObjType == 20)
					{
						Part* pPrt = (Part*)S_Buff[iCO]->pParent;
						// Delete Surface & Face from Part
						if ((S_Buff[iCO]->iObjType == 15) || (S_Buff[iCO]->iObjType == 16) || (S_Buff[iCO]->iObjType == 17))
						{
							ObjList* pFaces = new ObjList();
							pPrt->GetFaceRef(S_Buff[iCO], pFaces);
							//Delete Faces also need face ref edge ref
							for (i = 0; i < pFaces->iNo; i++)
							{
								Dsp_Rem(pFaces->Objs[i]);
								Dsp_RemGP(pFaces->Objs[i]);
								//pPrt->DeleteFace(pFaces->Objs[i]);
								Shell* pShell = (Shell*) pFaces->Objs[i]->pParent;
								if (pShell != NULL)
								{
									pShell->RemoveFaceUses((Face*) pFaces->Objs[i]);
									pShell->DeleteFace(pFaces->Objs[i]);
								}
							}
							pPrt->DeleteSurface(S_Buff[iCO]);
							Dsp_Rem(S_Buff[iCO]);
							Dsp_RemGP(S_Buff[iCO]);
							delete (pFaces);
						}
						// Delete Space Curves on if Uses = 0
						else if (S_Buff[iCO]->iObjType == 7)
						{
							int iC;
							NCurve* pSC;
							pSC =(NCurve*) S_Buff[iCO];
							iC = pPrt->GetCurveUseCnt(pSC);
							if (iC == 0)  //No Uses is Deleteable
							{
								pPrt->RemoveCurveUses(pSC);
								pPrt->DeleteCurve(pSC);
							}
						}
						else if (S_Buff[iCO]->iObjType == 0)
						{
							int iC;
							CvPt_Object* pSP;
							pSP = (CvPt_Object*) S_Buff[iCO];
							iC = pPrt->GetPointUseCnt(pSP);
							if (iC == 0)  //No Uses is Deleteable
							{
								//pPrt->RemoveCurveUses(pSP);
								pPrt->DeletePoint(pSP);
							}
						}
					}
					else if (S_Buff[iCO]->pParent->iObjType == 19)
					{
						//Delete Face Only From Part
						if (S_Buff[iCO]->iObjType == 18)
						{
							Shell* pShell = (Shell*) S_Buff[iCO]->pParent;
							Face* pF = pShell->GetFace(S_Buff[iCO]);
							if (pF!=NULL)
							{
								Dsp_Rem(pF);
								Dsp_RemGP(pF);
								pShell->RemoveFaceUses(pF);
								pShell->DeleteFace(pF);
							}
						}
					}
				}//****************************************
			}
		iCO++;	
		}
		while (iCO<S_Count);
		S_Count=0;
		InvalidateOGL();
		ReDraw();
	}
}

//***************************************************
// Pre :
// Post :Deform
//***************************************************

void DBase::UserCalc()
{
int iCO;
WG_Def* WG;
for (iCO=0;iCO<DB_ObjectCount;iCO++)
{  
  if (DB_Obj[iCO]->iObjType==500)
  {
     WG = (WG_Def*) DB_Obj[iCO];
	 int iErr=WG->GenMesh(pSecs,PropsT,iSMode,MeshCat,gDim);
  }
}
InvalidateOGL();
ReGen();
}

void DBase::ExportCMesh(FILE* pFile2)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->ExportUNV(pFile2,NULL);
}
}

void DBase::ExportMesh(FILE* pFile2)
{
if (this->pCurrentMesh!=NULL)
{
  pCurrentMesh->ExportUNV(pFile2,pSecs);
  fprintf(pFile2,"%6s\n","-1");
}
fclose(pFile2);
}

void DBase::ExportMesh2STL(CString sFile)
{
	if (this->pCurrentMesh != NULL)
	{
		pCurrentMesh->ExportSTL(sFile);
	}

}

void DBase::ImportMesh2STL(CString sFile)
{
	if (this->pCurrentMesh != NULL)
	{
		pCurrentMesh->ImportSTL(sFile);
		InvalidateOGL();
		ReDraw();
	}

}




void DBase::ExportDXF(FILE* pFile2)
{
	outtext1("WARNING: DXF Output in Developement.");
	int iCO;
	fprintf(pFile2, "0\n");				// write a line with value 0
	fprintf(pFile2, "SECTION\n");		// write the SECTION header
	fprintf(pFile2, "2\n");				// write a line with value 2
	fprintf(pFile2, "ENTITIES\n");		// write the ENTITIES header
	fprintf(pFile2, "0\n");				// write a line with value 0
	for (iCO = 0; iCO < DB_ObjectCount; iCO++)
	{ 
		//Curves and Points so far
		if ((DB_Obj[iCO]->iObjType == 7) && (DB_Obj[iCO]->iType == 1))
		{   //need to deal with trimmed curves

			NCurve* pC = (NCurve*)DB_Obj[iCO];
			NCurve* pC1 = nullptr;
			NCurve* pC2 = nullptr;
			NCurve* pC3 = nullptr;
			NCurve* pC4 = nullptr;
			NCurve* pT = nullptr;
			C3dVector vs, ve;
			vs = pC->GetPt(pC->ws);
			ve = pC->GetPt(pC->we);
			pT = pC;
            if (pC->ws>0)
			{
				CurveDivide(pC, pC1, pC2, vs);
				pT = pC2;
			}
			if (pC->we < 1)
			{
				CurveDivide(pT, pC3, pC4, ve);
				pT = pC3;
			}
			pT->ExportDXF(pFile2);
			delete(pC1);
			delete(pC2);
			delete(pC3);
			delete(pC4);

		}
		else if ((DB_Obj[iCO]->iObjType == 0) 
			    || (DB_Obj[iCO]->iObjType == 6)
			    || (DB_Obj[iCO]->iObjType == 7)
			    || (DB_Obj[iCO]->iObjType == 10))
		{
			DB_Obj[iCO]->ExportDXF(pFile2);
		}

	}
	fprintf(pFile2, "ENDSEC\n");			// end the section
	fprintf(pFile2, "0\n");				// write a line with value 0
	fprintf(pFile2, "EOF\n");			// end the file
	fclose(pFile2);
}

void DBase::ExportPermGroupsTXT(FILE* pFile2)
{
int i;
int j;
Node* pN;
E_Object* pE;
 fprintf(pFile2,"%-10s%-10s%-10s%-10s%-10s\n","$ELEM","ID","COL","PID","TYPE");
 fprintf(pFile2,"%-10s%-10s%-10s%-10s%-10s\n","$NODE","ID","COL","DEF","OUT");
for (i=0;i<iNoGPs ;i++)
{
  fprintf(pFile2,"%-s\n","GROUP");
  fprintf(pFile2,"%-s\n",Groups[i]->Title);
  for(j=0;j<Groups[i]->iNo;j++)
  {
    if (Groups[i]->Objs[j]!=NULL)
    {
      if ((Groups[i]->Objs[j]->iObjType==1) && (Groups[i]->Objs[j]->pParent==pCurrentMesh))
      {
        pN=(Node*) Groups[i]->Objs[j];
        fprintf(pFile2,"%-10s%-10i%-10i%-10i%-10i\n","NODE",pN->iLabel,pN->iColour,pN->DefSys,pN->OutSys);
      }
      else if ((Groups[i]->Objs[j]->iObjType==3) && (Groups[i]->Objs[j]->pParent==pCurrentMesh))
      {
        pE=(E_Object*) Groups[i]->Objs[j];
        fprintf(pFile2,"%-10s%-10i%-10i%-10i%-10i\n","ELEM",pE->iLabel,pE->iColour,pE->PID,pE->iType);
      }
    }

  }

}

}

void DBase::ExportGroupsTXT(FILE* pFile2)
{
if (this->pCurrentMesh!=NULL)
{
  pCurrentMesh->ExportGroups(pFile2);
}
}


void DBase::ExportRes(FILE* pFile2)
{
if (this->pCurrentMesh!=NULL)
{
    COleDateTime timeStart;
    timeStart = COleDateTime::GetCurrentTime();

    int Year=timeStart.GetYear();
    int Mon=timeStart.GetMonth();
    int Day=timeStart.GetDay();
    int Hour=timeStart.GetHour();
    int Min=timeStart.GetMinute();
    int Sec=timeStart.GetSecond();

    fprintf(pFile2,"%s\n","**********************************************************");
    fprintf(pFile2,"%s %i:%i:%i\n","DATE",Day,Mon,Year);
    fprintf(pFile2,"%s %i:%i:%i\n","TIME",Hour,Min,Sec);
    fprintf(pFile2,"%s\n","**********************************************************");
    pCurrentMesh->ExportRes(pFile2);
}
fclose(pFile2);
}



void DBase::ExportMeshNAS(FILE* pFile2, int iFile)
{
if (this->pCurrentMesh!=NULL)
{
    COleDateTime timeStart;
    timeStart = COleDateTime::GetCurrentTime();

    int Year=timeStart.GetYear();
    int Mon=timeStart.GetMonth();
    int Day=timeStart.GetDay();
    int Hour=timeStart.GetHour();
    int Min=timeStart.GetMinute();
    int Sec=timeStart.GetSecond();

    if (Year<3000)
    {
    fprintf(pFile2,"%s\n","$**********************************************************");
    fprintf(pFile2,"%s\n","$      NASTRAN DECK EXPORTED FROM M3D");
    fprintf(pFile2,"%s\n","$      VERSION 7.2");
    fprintf(pFile2,"%s\n","$      www.M3dFea.com");
    fprintf(pFile2,"%s %i:%i:%i\n","$      DATE",Day,Mon,Year);
    fprintf(pFile2,"%s %i:%i:%i\n","$      TIME",Hour,Min,Sec);
    fprintf(pFile2,"%s\n","$**********************************************************");
	if (pCurrentMesh->pSOLS != NULL)
		pCurrentMesh->ExportNASExec(pFile2, pSecs);
	if (iFile == -1)
	{
		fprintf(pFile2, "%s\n", "BEGIN BULK");
		fprintf(pFile2, "%s\n", "PARAM,POST,-1");
	}
	fprintf(pFile2, "%s\n", "$******************** MATERIALS ***************************");
    MatT->ExportNAS(pFile2, iFile);
    fprintf(pFile2,"%s\n","$******************* PROPERTIES ***************************");
	PropsT->ExportNAS(pFile2, iFile);
    pCurrentMesh->ExportNAS(pFile2,pSecs,iFile);
	pCurrentMesh->ExportNAS_SETS(pFile2, pSecs, iFile);
	if (iFile == -1)
	   fprintf(pFile2, "%s\n", "ENDDATA");
    }
    else
    {
      outtext1("Nastran Export Expired.");
    }
}
fclose(pFile2);
}


void DBase::ExportToText(FILE* pFile2)
{
if (this->pCurrentMesh!=NULL)
{
    COleDateTime timeStart;
    timeStart = COleDateTime::GetCurrentTime();

    int Year=timeStart.GetYear();
    int Mon=timeStart.GetMonth();
    int Day=timeStart.GetDay();
    int Hour=timeStart.GetHour();
    int Min=timeStart.GetMinute();
    int Sec=timeStart.GetSecond();

    if (Year<2030)
    {
      fprintf(pFile2,"%s\n","$**********************************************************");
      fprintf(pFile2,"%s\n","$      NASTRAN DECK EXPORTED FROM M3D");
      fprintf(pFile2,"%s\n","$      VERSION 6.1");
      fprintf(pFile2,"%s\n","$      WWW.M3d.org.uk");
      fprintf(pFile2,"%s %i:%i:%i\n","$      DATE",Day,Mon,Year);
      fprintf(pFile2,"%s %i:%i:%i\n","$      TIME",Hour,Min,Sec);
      fprintf(pFile2,"%s\n","$**********************************************************");
    int iCO;
	CString OutS;
	
    for (iCO=0;iCO<S_Count;iCO++)
    {
	  OutS=S_Buff[iCO]->ToString();
      fprintf(pFile2,OutS);
    }
	}
    else
    {
      outtext1("Export Expired.");
    }
}
fclose(pFile2);
}

void DBase::ExportViewMat(FILE* pFile2)
{
  

  if (pFile2 != nullptr)
  {
	  fprintf(pFile2, "%s\n", "MAT");
	  fprintf(pFile2, "%lf %lf %lf %lf\n", pModelMat.m_00, pModelMat.m_01, pModelMat.m_02, pModelMat.m_03);
	  fprintf(pFile2, "%lf %lf %lf %lf\n", pModelMat.m_10, pModelMat.m_11, pModelMat.m_12, pModelMat.m_13);
	  fprintf(pFile2, "%lf %lf %lf %lf\n", pModelMat.m_20, pModelMat.m_21, pModelMat.m_22, pModelMat.m_23);
	  fprintf(pFile2, "%lf %lf %lf %lf\n", pModelMat.m_30, pModelMat.m_31, pModelMat.m_32, pModelMat.m_33);
	  fclose(pFile2);
	  outtext1("View Matrix saved.");
  }
  else 
  {
	  outtext1("ERROR: Unable to save View Matrix.");
  }
}

void DBase::ImportViewMat(FILE* pFile)
{

	char s1[200];
	C3dMatrix mT;
	int irc;
	BOOL bErr = FALSE;

	if (pFile != nullptr)
	{
		irc = fscanf(pFile, "%s", &s1);
		if (irc != 1)
			bErr = TRUE;
		irc = fscanf(pFile, "%lf %lf %lf %lf", &mT.m_00, &mT.m_01, &mT.m_02, &mT.m_03);
		if (irc != 4)
			bErr = TRUE;
		if (!bErr)
		    irc = fscanf(pFile, "%lf %lf %lf %lf", &mT.m_10, &mT.m_11, &mT.m_12, &mT.m_13);
		if (irc != 4)
			bErr = TRUE;
		if (!bErr)
		    irc = fscanf(pFile, "%lf %lf %lf %lf", &mT.m_20, &mT.m_21, &mT.m_22, &mT.m_23);
		if (irc != 4)
			bErr = TRUE;
		if (!bErr)
		    irc = fscanf(pFile, "%lf %lf %lf %lf", &mT.m_30, &mT.m_31, &mT.m_32, &mT.m_33);
		if (irc != 4)
			bErr = TRUE;
		if (!bErr)
		{
			outtext1("View Matrix loaded.");
			tOrient.PushMat(mT);
			pModelMat = mT;
			InvalidateOGL();
			ReDraw();
		}
		else
		{
			outtext1("ERROR: Invalid Matrix Format.");
		}
	}
	else 
	{
		outtext1("ERROR: Unable to load View Matrix.");
	}
}


void DBase::BuildAssembly(CString sModName)
{
int iCO;
WG_Def* WG;
int iN=1;
int iE=1;

ME_Object* Me = new ME_Object();
Me->iLabel = 10;
Me->sName=sModName;
for (iCO=0;iCO<S_Count;iCO++)
{  
  if (S_Buff[iCO]->iObjType==500)
  {
       WG = (WG_Def*) S_Buff[iCO];
	   ME_Object* MT;
	   MT=WG->GetMesh();
	   Me->Append(MT,iN,iE);
	   delete(MT);
  }
  else if (S_Buff[iCO]->iObjType==4)
  {
     ME_Object* MT = (ME_Object*) S_Buff[iCO]->Copy(NULL);
	   Me->Append(MT,iN,iE);
	   delete(MT);
  }
}
if (Me!=NULL)
{
  pCurrentMesh = Me;
  pCurrentMesh->UpdatePropRef(PropsT);
  AddObj(Me);
  BuildGroupsFromCurrentFEM();
  ReDraw();
}
}


void DBase::BuildGroupsFromCurrentFEM()
{
int i;
int j;
G_Object* pEl;
int iD;
int iT;
if (pCurrentMesh!=NULL)
{
  for (i=0;i<pCurrentMesh->iNoGps;i++)
  {
     AddGp(pCurrentMesh->GPs[i]->Title);
     for (j=0;j<pCurrentMesh->GPs[i]->iNo;j++)
     {
        iD = pCurrentMesh->GPs[i]->ids[j];
        iT = pCurrentMesh->GPs[i]->iType[j];
        if (iT==1)
        {
          pEl=pCurrentMesh->GetNode(iD);
          Groups[iCurGp]->Add(pEl);
        }
        else if (iT==3)
        {
          pEl=pCurrentMesh->GetElement(iD);
          Groups[iCurGp]->Add(pEl);
        }
     }
  }
}
}


void DBase::UserCalc2()
{

}

C3dVector DBase::ClosestTo(C3dVector vPt)
{
C3dVector vRet;
if (S_Count>0)
{
  vRet=S_Buff[S_Count-1]->MinPt(vPt);
  S_Count--;
  ReDraw();
}
return (vRet);
}

void DBase::KnotModify(NCurve* pC,CString sKnot)
{
  pC->knots[3] = 0.8541;
}

void DBase::KnotInsertion(NCurve* pC,C3dVector vPt)
{
  Vec<C4dVector> cPts;
  Vec<double> knots;
  C3dVector pM;
  pM.Set(0.0, 1.0, 0.0);
  double p;  //order
  int r;
  int k = 0;
  double dU;
  NCurve* pNewC=NULL;

  if (pC != NULL)
  {
    outtext1("Curve found for knot insertion.");
    p = pC->p;
    dU = pC->MinWPt(vPt);
    if ((dU > 0) && (dU < 1))
    {
      r = pC->knotInsertion(dU, pC->p+1,k, cPts, knots);
      pNewC = new NCurve();
      pNewC->GenerateExp(p, cPts, knots);
      pNewC->Move(pM);
	  pNewC->iLabel = pC->iLabel;
      AddObj(pNewC);
	  //Remove original
	  if (pC->pParent == NULL)
	  {
		  RemObj(pC);
		  Dsp_Rem(pC);
		  Dsp_RemGP(pC);
	  }
	  InvalidateOGL();
      ReDraw();
    }
    else
    {
      outtext1("ERROR: No Projection onto Curve.");
    }
  }
  else
  {
    outtext1("ERROR: No Curve Selected.");
  }
}

//Divide a curve into 2 at point
//pC original
//pC1 first new curve pC2 remainder of curve
void DBase::CurveDivide(NCurve* pC, NCurve* &pC1, NCurve* &pC2, C3dVector vPt)
{
	double dU;
	Vec<C4dVector> cPts;
	Vec<double> knots;
	Vec<C4dVector> cPtsSeg;
	Vec<double> knotsSeg;
	C3dVector pM;
	pM.Set(0.0, 1.0, 0.0);
	double p;  //order
	double dTmp;
	int r;
	int i;
	int k = 0;
	p = pC->p;
	dU = pC->MinWPt(vPt);
	if ((dU > 0) && (dU < 1))
	{
		r = pC->knotInsertion(dU, pC->p + 1, k, cPts, knots);
		cPtsSeg.Size(k + 1);
		knotsSeg.Size(k + r + 1);
		for (i = 0; i < k + 1; i++)
			cPtsSeg[i] = cPts[i];
		for (i = 0; i < k + r + 1; i++)
		{
			dTmp = knots[i] / knots[k + r];
			knotsSeg[i] = dTmp;
		}
		if (pC->iType == 1)
			pC1 = new NCurve();
		else
			pC1 = new NLine();
		pC1->GenerateExp(p, cPtsSeg, knotsSeg);
		pC1->iLabel = pC->iLabel;
		//AddObj(pNewC);
		cPtsSeg.DeleteAll();
		knotsSeg.DeleteAll();
		//cPts.DeleteAll();
		//knots.DeleteAll();
		//Second segment curve
		int iSS;
		cPtsSeg.Size(cPts.n - (k + 1));
		knotsSeg.Size(cPtsSeg.n + r);
		for (i = (k + 1); i < cPts.n; i++)
			cPtsSeg[i - (k + 1)] = cPts[i];
		for (i = k + 1; i < cPts.n + r; i++)
		{
			dTmp = (knots[i] - knots[k + 1]) / (knots[cPts.n + r - 1] - knots[k + 1]);
			knotsSeg[i - (k + 1)] = dTmp;
		}
		if (pC->iType == 1)
			pC2 = new NCurve();
		else
			pC2 = new NLine();
		pC2->GenerateExp(p, cPtsSeg, knotsSeg);
		pC2->iLabel = iCVLabCnt;
		iCVLabCnt++;
		//AddObj(pNewC);
		cPtsSeg.DeleteAll();
		knotsSeg.DeleteAll();

	}
	cPts.DeleteAll();
    knots.DeleteAll();
}


void DBase::CurveSplit(NCurve* pC, C3dVector vPt)
{
	Vec<C4dVector> cPts;
	double dU;
	NCurve* pNewC1 = NULL;
	NCurve* pNewC2 = NULL;
	NCircle* pCir = NULL;
	if (pC != NULL)
	{
		if (pC->iType == 3)
		{
			outtext1("Circle Split.");
			dU = pC->MinWPt(vPt);
			if ((dU > 0) && (dU < 1))
			{
				pCir = (NCircle *) pC->Copy(pC->pParent);
				pCir->iLabel = iCVLabCnt;
				iCVLabCnt++;
				AddObj(pCir);
				pCir->ws = dU;
				pCir->we = pC->we;
				pC->we = dU;
			}
			else
			{
				outtext1("ERROR: No Projection onto Circle.");
			}
		}
		else
		{
			outtext1("Curve found for knot insertion.");
			CurveDivide(pC, pNewC1, pNewC2, vPt);
			if ((pNewC1 != nullptr) && (pNewC2 != nullptr))
			{
				AddObj(pNewC1);
				AddObj(pNewC2);
				//Remove original
				if (pC->pParent == NULL)
				{
					RemObj(pC);
					Dsp_Rem(pC);
					Dsp_RemGP(pC);
				}
				InvalidateOGL();
				S_Des();
			}
		}
	}
	else
	{
		outtext1("ERROR: No Curve Selected.");
	}
	S_Des();

}

C3dVector DBase::Intersect(BOOL &bErr, CPoint nPt)
{
C3dVector vRet;
NCurve* Ln=NULL;
NCurve* Ln1=NULL;
C3dVector pN1;
pN1 = PickPointToGlobal(nPt);
bErr=FALSE;
if (S_Count>1)
{
  if (S_Buff[S_Count-2]->iObjType==7)
     
  {
    Ln= (NCurve*)  S_Buff[S_Count-2];
  }
  else
  {
    bErr=TRUE;  
  }
  if (S_Buff[S_Count-2]->iObjType==7)
  {
    Ln1= (NCurve*) S_Buff[S_Count-1];
  }
  else
  {
    bErr=TRUE; 
  }
  if (!bErr)
  {
    vRet=NLnInt3(Ln,Ln1,&pN1);
    S_Count--;
    S_Count--;
    ReDraw();
  }
}
return (vRet);
}

void DBase::Corner2(CPoint PNear1,CPoint PNear2)
{
//double R;
//R=dR;
NLine* Ln=NULL;
NLine* Ln1=NULL;
BOOL bErr=FALSE;
NCircle* cCir;
cCir=NULL;
C3dVector pN1,pN2;
pN1=PickPointToGlobal(PNear1);
pN2=PickPointToGlobal(PNear2);
if (S_Count>1)
{
  if ((S_Buff[S_Count-2]->iObjType == 7) &&
	  (S_Buff[S_Count - 2]->iType == 2))
  {
    Ln=(NLine*) S_Buff[S_Count-2];
  }
  else
  {
    bErr=TRUE;  
  }
  if ((S_Buff[S_Count-1]->iObjType == 7) &&
	  (S_Buff[S_Count - 2]->iType == 2))
  {
    Ln1=(NLine*) S_Buff[S_Count-1];
  }
  else
  {
    bErr=TRUE; 
  }
  if (!bErr)
  {
    Corner(Ln,Ln1,pN1,pN2);
    S_Count--;
    S_Count--;
    InvalidateOGL();
    ReDraw();
  }
}
}

void DBase::Trim(CPoint PNear1, CPoint PNear2) {
	char S1[200];
	CString OutT;
	double dU;
	double dUse, dUse2;
	NLine* Ln = nullptr;
	NLine* Ln1 = nullptr;
	NCurve* Cv = nullptr;
	NCurve* Cv1 = nullptr;
	BOOL bErr = FALSE;
	NCircle* cCir;
	cCir = nullptr;
	C3dVector pN1, pN2, vRet;
	pN1 = PickPointToGlobal(PNear1);
	pN2 = PickPointToGlobal(PNear2);

	if (S_Count > 1) {
		// Check if both selected items are curves
		if ((S_Buff[S_Count - 1]->iObjType == 7) && (S_Buff[S_Count - 2]->iObjType == 7)) {
			if ((S_Buff[S_Count - 1]->iType == 2) && (S_Buff[S_Count - 2]->iType == 2)) { // Two lines, only 1 possible intersection
				Ln = (NLine*)S_Buff[S_Count - 2];
				Ln1 = (NLine*)S_Buff[S_Count - 1];
				vRet = NLnInt2(Ln, Ln1, &pN1);
				dU = Ln->MinWPt(vRet); // U at intersect
				dUse = Ln->MinWPt(pN1);
				sprintf_s(S1, " Debug W: ,%f,%f", dU, dUse);
				if ((dUse < dU) && (Ln->we > dU)) // This is trim
					Ln->ws = dU;
				else if ((dUse > dU) && (Ln->ws < dU))
					Ln->we = dU;
				else if ((dUse > dU) && (Ln->ws > dU)) // This is extend
					Ln->ws = dU;
				else if ((dUse < dU) && (Ln->we < dU))
					Ln->we = dU;
				S_Count -= 2;
				InvalidateOGL();
				ReDraw();
			}
			else { // Two curves, possible multiple intersections
				int iNoInts = 0;
				C3dVector vInts[10];
				double uInts[10];
				outtext1("Search for multiple intersections.");
				Cv = (NCurve*)S_Buff[S_Count - 2];
				Cv1 = (NCurve*)S_Buff[S_Count - 1];
				if (Cv->iType == 3)
					cCir = (NCircle*)Cv;
				// iNoInts = TentativeInt(Cv, Cv1, vInts, uInts);
				dUse = Cv->MinWPt(pN1);
				dUse2 = Cv->MinWPt(pN2);
				if (iNoInts > 0) {
					int pNr = FindNearest(iNoInts, uInts, dUse2);
					dU = uInts[pNr];
				}
				else {
					dU = dUse2;
				}
				C3dVector pNr2;
				pNr2 = Cv->GetPt(dU);
				vRet = NLnInt3(Cv, Cv1, &pNr2);
				dU = Cv->MinWPt(vRet); // U at intersect
				sprintf_s(S1, " Debug W: ,%f,%f", dU, dUse);
				if (cCir != nullptr)
				{
					//if ((dUse < dU) && (Cv->we > dU)) // This is trim
					if (abs(Cv->ws - dUse) < abs(Cv->we-dUse))
					    cCir->RotateToUS(dU);
					else if ((dUse > dU) && (Cv->ws < dU))
						Cv->we = dU;
					// else if ((dUse > dU) && (Cv->ws > dU)) // This is extend
					//	cCir->RotateToUS(dU);
					else if ((dUse < dU) && (Cv->we < dU))
						Cv->we = dU;
					if (Cv->we - Cv->ws < 0)
					{

						Cv->ws = 0;
						Cv->we = 1;
					}
				}
				else
				{
					if ((dUse < dU) && (Cv->we > dU)) // This is trim
						Cv->ws = dU;
					else if ((dUse > dU) && (Cv->ws < dU))
						Cv->we = dU;
					else if ((dUse > dU) && (Cv->ws > dU)) // This is extend
						Cv->ws = dU;
					else if ((dUse < dU) && (Cv->we < dU))
						Cv->we = dU;
				}
				S_Count -= 2;
				InvalidateOGL();
				ReDraw();
			}
		}
		else {
			outtext1("ERROR: Two curves must be selected.");
			S_Count -= 2;
			ReDraw();
		}
	}
	else {
		outtext1("ERROR: .");
	}
}







void DBase::Corner(NLine* Ln, NLine* Ln1, C3dVector PNear1, C3dVector PNear2) {
	double w = 0;
	double wNr = 0;
	C3dVector pt;
	double d1, d2;
	C3dVector vE1, vE2, vV;

	// The intersection of the lines
	pt = NLnInt(Ln, Ln1, NULL);

	// Find line end nearest to pt LINE 1
	vE1 = Ln->cPts[0]->Get_Centroid();
	vE2 = Ln->cPts[1]->Get_Centroid();
	vV = vE1;
	vV -= PNear1;
	d1 = vV.Mag();
	vV = vE2;
	vV -= PNear1;
	d2 = vV.Mag();
	if (d1 < d2) 
	{
		d1 = Ln->getLen();
		Ln->cPts[0]->Pt_Point->Set(pt.x, pt.y, pt.z);
		d2 = Ln->getLen();
		Ln->ws = 0;
		Ln->we = 1 - (1 - Ln->we) * d1 / d2;
	}
	else 
	{
		d1 = Ln->getLen();
		Ln->cPts[1]->Pt_Point->Set(pt.x, pt.y, pt.z);
		d2 = Ln->getLen();
		Ln->we = 1;
		Ln->ws = Ln->ws * d1 / d2;
	}

	// Find line end nearest to pt LINE 2
	vE1 = Ln1->cPts[0]->Get_Centroid();
	vE2 = Ln1->cPts[1]->Get_Centroid();
	vV = vE1;
	vV -= PNear2;
	d1 = vV.Mag();
	vV = vE2;
	vV -= PNear2;
	d2 = vV.Mag();
	if (d1 < d2) 
	{
		d1 = Ln1->getLen();
		Ln1->cPts[0]->Pt_Point->Set(pt.x, pt.y, pt.z);
		d2 = Ln1->getLen();
		Ln1->ws = 0;
		Ln1->we = 1 - (1 - Ln1->we) * d1 / d2;
	}
	else 
	{
		d1 = Ln1->getLen();
		Ln1->cPts[1]->Pt_Point->Set(pt.x, pt.y, pt.z);
		d2 = Ln1->getLen();
		Ln1->we = 1;
		Ln1->ws = Ln1->ws * d1 / d2;
	}
}


NCircle* DBase::Fillet2(double dR, CPoint PNear1, CPoint PNear2)
{
	NLine* Ln = nullptr;
	NLine* Ln1 = nullptr;
	BOOL bErr = FALSE;
	NCircle* cCir = nullptr;

	C3dVector pN1 = PickPointToGlobal(PNear1);
	C3dVector pN2 = PickPointToGlobal(PNear2);


	if (dR > 0)
	{
		if (S_Count > 1)
		{
			if ((S_Buff[S_Count - 2]->iObjType == 7))
				Ln = (NLine*)S_Buff[S_Count - 2];
			else
				bErr = TRUE;
			if ((S_Buff[S_Count - 1]->iObjType == 7))
				Ln1 = (NLine*)S_Buff[S_Count - 1];
			else
				bErr = TRUE;
			if (!bErr)
			{
				if ((Ln->iType==2) && (Ln1->iType == 2))
				   cCir = Fillet(Ln, Ln1, dR, pN1, pN2);	//for lines only
				else
				   cCir = FilletIter(Ln, Ln1, dR, pN1, pN2); //for lines only
				if (cCir != nullptr)
				{
					AddObj(cCir);
					cCir->iLabel = iCVLabCnt;
					iCVLabCnt++;
					InvalidateOGL();
				}
				S_Count--;
				S_Count--;
				ReDraw();

			}
		}
	}
	return cCir;
}

NCircle* DBase::Fillet(NLine* Ln, NLine* Ln1, double dR, C3dVector PNear1, C3dVector PNear2)
{
	double R = dR;
	BOOL LStart = TRUE;
	BOOL L1Start = TRUE;
	double wL = 0;
	double wL1 = 0;
	C3dVector p1, p2, p3, pT, vL1Dir, * pLT1, * pLT2, v1, v2, v3;

	// The intersection of the lines
	p2 = NLnInt(Ln, Ln1, NULL);

	// Choose the other ends of lines to keep
	// Choose the ones with the longest distance
	pT = Ln->cPts[0]->Pt_Point;
	v1 = pT - p2;
	v2 = PNear1 - p2;
	pT = Ln->cPts[1]->Pt_Point;
	v3 = pT - p2;

	// Both points are on the same side
	if (v3.Dot(v1) > 0)
	{
		if (v1.Mag() < v3.Mag())
		{
			p1 = Ln->cPts[1]->Pt_Point;
			pLT1 = Ln->cPts[0]->Pt_Point;
		}
		else
		{
			p1 = Ln->cPts[0]->Pt_Point;
			pLT1 = Ln->cPts[1]->Pt_Point;
			LStart = FALSE;
		}
	}
	else
	{
		if (v1.Dot(v2) > 0)
		{
			p1 = Ln->cPts[0]->Pt_Point;
			pLT1 = Ln->cPts[1]->Pt_Point;
			LStart = FALSE;
		}
		else
		{
			p1 = Ln->cPts[1]->Pt_Point;
			pLT1 = Ln->cPts[0]->Pt_Point;
		}
	}

	vL1Dir = pLT1;
	vL1Dir -= p1;
	vL1Dir.Normalize();

	pT = Ln1->cPts[0]->Pt_Point;
	v1 = pT - p2;
	v2 = PNear2 - p2;
	pT = Ln1->cPts[1]->Pt_Point;
	v3 = pT - p2;

	// Both points are on the same side
	if (v3.Dot(v1) > 0)
	{
		if (v1.Mag() < v3.Mag())
		{
			p3 = Ln1->cPts[1]->Pt_Point;
			pLT2 = Ln1->cPts[0]->Pt_Point;
		}
		else
		{
			p3 = Ln1->cPts[0]->Pt_Point;
			pLT2 = Ln1->cPts[1]->Pt_Point;
			L1Start = FALSE;
		}
	}
	else
	{
		if (v1.Dot(v2) > 0)
		{
			p3 = Ln1->cPts[0]->Pt_Point;
			pLT2 = Ln1->cPts[1]->Pt_Point;
			L1Start = FALSE;
		}
		else
		{
			p3 = Ln1->cPts[1]->Pt_Point;
			pLT2 = Ln1->cPts[0]->Pt_Point;
		}
	}

	v1 = p2;
	v1 -= p1;
	v2 = p3;
	v2 -= p2;

	C3dVector vn = v1.Cross(v2);
	vn.Normalize();
	C3dVector v1o, v2o;
	v1o = v1.Cross(vn);
	v2o = v2.Cross(vn);
	v1o.Normalize();
	v2o.Normalize();
	v1o *= R;
	v2o *= R;

	if (v1o.Dot(v2) < 0)
		v1o *= -1;
	if (v2o.Dot(v1) > 0)
		v2o *= -1;

	C3dVector p1o, p2o, p3o, p4o;
	p1o = p1;
	p1o += v1o;
	p2o = p2;
	p2o += v1o;
	p3o = p2;
	p3o += v2o;
	p4o = p3;
	p4o += v2o;

	NLine* Ln2 = new NLine;
	Ln2->Create(p1o, p2o, 1, NULL);
	NLine* Ln3 = new NLine;
	Ln3->Create(p3o, p4o, 1, NULL);

	C3dVector IntPt;
	IntPt = NLnInt(Ln2, Ln3, NULL);
	NCircle* cCir = new NCircle();
	cCir->Create(vn, IntPt, R, -1, NULL);

	C3dVector IntPt1;
	IntPt1 = Ln->MinPt(IntPt);
	//pLT1->Set(IntPt1.x, IntPt1.y, IntPt1.z);  // Trim the end point
	wL= Ln->MinWPt(IntPt);
	if (LStart)
		Ln->ws = wL;
	else
		Ln->we = wL;
		
	C3dVector IntPt2;
	IntPt2 = Ln1->MinPt(IntPt);
	//pLT2->Set(IntPt2.x, IntPt2.y, IntPt2.z);  // Trim the end point
	wL1 = Ln1->MinWPt(IntPt2);
	if (L1Start)
		Ln1->ws = wL1;
	else
		Ln1->we = wL1;
	double d1q;
	d1q = cCir->MinWPt(IntPt1);
	C3dVector vRef;
	C3dVector vDir;
	vRef = IntPt1;
	vDir = cCir->GetDir(d1q);
	vDir.Normalize();
	vRef -= cCir->vCent;
	vRef.Normalize();
	if (vDir.Dot(vL1Dir) < 0)
	{
		vn *= -1;
	}
	delete (cCir);
	cCir = new NCircle();
	cCir->Create2(vn, IntPt, vRef, R, -1, NULL);
	double d2q;
	d2q = cCir->MinWPt(IntPt2);
	cCir->we = d2q;
	delete (Ln2);
	delete (Ln3);

	return cCir;
}


//Fillet between 2 arbitrary curves
//need to iterate for rad circle centre
NCircle* DBase::FilletIter(NLine* Ln1, NLine* Ln2, double dR, C3dVector PNear1, C3dVector PNear2)
{
	NCircle* cCir = nullptr;
	int iter = 0;
	CvPt_Object* pPt;
	BOOL bErr;
	double dDir1c = 1;      //Direction check
	double dDir2c = 1;      //Direction check
	double dMinDist, dDist;
	double dTD;
	double w1, w2;				//the w values of the near point on the 2 curves
	double Deltaw1, Deltaw2;
	int i;
	C3dVector v1, v2;			//The actual points on curve
	C3dVector vCur1, vCur2;
	C3dVector vD1, vD2, vDir1, vDir2;;			//The direction vectors
	C3dVector vBet1, vBet2;
	C3dVector vAC;				//Apperent interection
	C3dVector vAN;              //Apperent Normal
	C3dVector vAD1, vAD2;       //Apperent Directions
	C3dVector vBet;             //Between point v1,v2
	C3dVector vX1,vX2;
	w1 = Ln1->MinWPt(PNear1);
	w2 = Ln2->MinWPt(PNear2);
	v1 = Ln1->GetPt(w1);
	v2 = Ln2->GetPt(w2);
	vDir1 = Ln1->GetDir(w1); vDir1.Normalize();
	vDir2 = Ln2->GetDir(w2); vDir2.Normalize();
	vD1 = vDir1; vD2 = vDir2;
	vD1 += v1; vD2 += v2;
	bErr = LnIntByPoints(v1, vD1, v2, vD2, vAC);
	if (bErr)
	{
		vAD1 = (v1 - vAC); vAD1.Normalize();
		vAD2 = (v2 - vAC); vAD2.Normalize();
		vAN = vAD1.Cross(vAD2);
		vAN.Normalize();
		//Direction Check between point
		vBet = v1; vBet += v2; vBet *= 0.5;
		//pPt = AddPt(vBet, -1, TRUE);
		vX1 = vDir1.Cross(vAN); vX1.Normalize();
		vX2 = vDir2.Cross(vAN); vX2.Normalize();

		//Need to check both vX vectors point to between point
		vBet1 = vBet - v1;
		vBet1.Normalize();
		vBet2 = vBet -v2;
		vBet2.Normalize();
		if (vBet1.Dot(vX1) < 0)
			dDir1c = -1;  //Direction need reversing
		if (vBet2.Dot(vX2) < 0)
			dDir2c = -1;
		vX1 *= dDir1c;
		vX2 *= dDir2c;
		//Start of iteration.
		//The initial centre ooints
		vX1 *= dR;
		vX2 *= dR;
		vCur1 = v1 + vX1;
		vCur2 = v2 + vX2;
		dMinDist = vCur1.Dist(vCur2);
		Deltaw1 = 0.005;
		Deltaw2 = 0.005;
		do
		{
			w1 += Deltaw1;
			w2 += Deltaw2;
			if (w1 < 0)
				w1 = 0;
			else if (w1 > 1)
				w1 = 1;
			if (w2 < 0)
				w2 = 0;
			else if (w2 > 1)
				w2 = 1;

			//need to do one point at a time
			v1 = Ln1->GetPt(w1);
			vDir1 = Ln1->GetDir(w1); vDir1.Normalize();
			vX1 = vDir1.Cross(vAN); vX1.Normalize();
			vX1 *= dDir1c;
			vX1 *= dR;
			vCur1 = v1 + vX1;
			dTD = vCur1.Dist(vCur2);
			if (dTD < dMinDist)
			{
				dMinDist = dTD;
			}
			else 
			{
				dMinDist = dTD;
				Deltaw1 *= -0.75;
			}
			// Second Curve
			v2 = Ln2->GetPt(w2);
			vDir2= Ln2->GetDir(w2); vDir2.Normalize();
			vX2 = vDir2.Cross(vAN); vX2.Normalize();
			vX2 *= dDir2c;
			vX2 *= dR;
			vCur2 = v2 + vX2;
			dTD = vCur1.Dist(vCur2);
			if (dTD < dMinDist)
			{
				dMinDist = dTD;
			}
			else
			{
				dMinDist = dTD;
				Deltaw2 *= -0.75;
			}
			
			iter++;
		} while ((dMinDist > dTol) && (iter<1000000));
		pPt = AddPt(vCur2, -1, TRUE);
		char buff[200];
		sprintf_s(buff, "Interation to Intersect %i Tol %g", iter, dMinDist);
		outtext1(buff);
		if (iter < 1000000)
		{
			//create the circle
			
			cCir = new NCircle();
			cCir->Create(vAN, vCur2, dR, -1, NULL);
		}
	}
	else
	{
		outtext1("ERROR: Intersection Error.");
	}
	return (cCir);
}



NCircle* DBase::Circ3Pts(C3dVector p1,C3dVector p2,C3dVector p3)
{
NCircle* cCir =NULL;
C3dVector v1;
C3dVector v2;
C3dVector vMid1;
C3dVector vMid2;
C3dVector vN;
C3dVector v1D;
C3dVector v2D; 
double dDot;
v1=p2;
v1-=p1;
v2=p3;
v2-=p2;


vMid1=v1;
vMid1*=0.5;
vMid1+=p1;

vMid2=v2;
vMid2*=0.5;
vMid2+=p2;

v1.Normalize();
v2.Normalize();

dDot=abs(v1.Dot(v2));
if (dDot<0.9999)
{
  vN=v1.Cross(v2);
  v1D=vN.Cross(v1);
  v2D=vN.Cross(v2);

  v1D+=vMid1;
  v2D+=vMid2;

  //Need to check for colinear point here

  NLine* Ln1 = new NLine;
  Ln1->Create(vMid1,v1D,1,NULL);
  NLine* Ln2 = new NLine;
  Ln2->Create(vMid2,v2D,1,NULL);
  C3dVector IntPt;
  IntPt=NLnInt(Ln1,Ln2,NULL);
  C3dVector vRef;
  vRef=p1;
  vRef-=IntPt;
  double dR;
  dR=vRef.Mag();
  if (dR>0)
  {
    cCir = new NCircle();
    cCir->Create2(vN,IntPt,vRef,dR,iCVLabCnt,NULL);
	iCVLabCnt++;
    AddObj(cCir);
    ReDraw();
  }
  else
  {
    outtext1("ERROR: Points are Coincident.");
  }
  delete (Ln1);
  delete (Ln2);

}
else
{
  outtext1("ERROR: Points are Co-linear.");
}
return(cCir);
}

NCircle* DBase::Arc3Pts(C3dVector p1,C3dVector p2,C3dVector p3)
{
NCircle* cCir =NULL;
C3dVector v1;
C3dVector v2;
C3dVector vMid1;
C3dVector vMid2;
C3dVector vN;
C3dVector v1D;
C3dVector v2D; 
double dDot;
v1=p2;
v1-=p1;
v2=p3;
v2-=p2;


vMid1=v1;
vMid1*=0.5;
vMid1+=p1;

vMid2=v2;
vMid2*=0.5;
vMid2+=p2;

v1.Normalize();
v2.Normalize();

dDot=abs(v1.Dot(v2));
if (dDot<0.9999)
{
  vN=v1.Cross(v2);
  v1D=vN.Cross(v1);
  v2D=vN.Cross(v2);

  v1D+=vMid1;
  v2D+=vMid2;

  //Need to check for colinear point here

  NLine* Ln1 = new NLine;
  Ln1->Create(vMid1,v1D,1,NULL);
  NLine* Ln2 = new NLine;
  Ln2->Create(vMid2,v2D,1,NULL);
  C3dVector IntPt;
  IntPt=NLnInt(Ln1,Ln2,NULL);
  C3dVector vRef;
  vRef=p1;
  vRef-=IntPt;
  double dR;
  dR=vRef.Mag();
  if (dR>0)
  {
    cCir = new NCircle();
    cCir->Create2(vN,IntPt,vRef,dR,-1,NULL);
    double d2q;
    d2q=cCir->MinWPt(p3);
    cCir->we=d2q;

    AddObj(cCir);
    ReDraw();
  }
  else
  {
    outtext1("ERROR: Points are Coincident.");
  }
  delete (Ln1);
  delete (Ln2);
}
else
{
  outtext1("ERROR: Points are Co-linear.");
}
return(cCir);
}

void DBase::TestTrans()
{
int i;
int NoOff;

C3dMatrix TMat;
TMat.MakeUnit();
TMat.Translate(0.5,0,0);
NoOff = DB_ObjectCount;
G_Object* gcp;
for (i=2;i<NoOff;i++)
{
  gcp=DB_Obj[i]->Copy(NULL);
  gcp->Transform(TMat);
  AddObj(gcp);
}
}


void DBase::RemTempGraphics(G_Object* gIn)
{
int i;
for (i=0;i<TmpOGLCnt;i++)
{
  if (TmpOGL[i]==gIn)
  {
    TmpOGL[i]=TmpOGL[TmpOGLCnt-1];
    TmpOGLCnt--;
    break;
  }
}
}

void DBase::AddTempGraphics(G_Object* gIn)
{
if (TmpOGLCnt<MAX_TEMPGRP)
{
  TmpOGL[TmpOGLCnt]=gIn;
  TmpOGLCnt++;
}
else
{
  InvalidateOGL();
  TmpOGLCnt=0;
}
}

void DBase::AddObj(G_Object* gIn)
{
DB_Obj[DB_ObjectCount]=gIn;
DB_Obj[DB_ObjectCount]->SetToScr(&pModelMat,&pScrMat);
Dsp_Add(gIn);
DB_ObjectCount++;
AddTempGraphics(gIn);
}

void DBase::RemObjNoDel(G_Object* gIn)
{
	int i;
	for (i = 0; i < DB_ObjectCount; i++)
	{
		if (DB_Obj[i] == gIn)
		{
			DB_Obj[i] = DB_Obj[DB_ObjectCount - 1];
			DB_ObjectCount--;
			break;
		}
	}
}

void DBase::RemObj(G_Object* gIn)
{
int i;
for (i=0;i<DB_ObjectCount;i++)
{
  if (DB_Obj[i]==gIn)
  {
	  delete(DB_Obj[i]);
      DB_Obj[i]=DB_Obj[DB_ObjectCount-1];
	  DB_ObjectCount--;
	  break;
  }
}
}


//***************************************************
// Pre :file pointer and name
// Post :universal file read and the mesh returned
//***************************************************

ME_Object* DBase::ImportUNV(FILE* pFile,CString inName)
{
int i1;
int i2;
int i3;
int i4;
char s1[200];
char s2[200];
char s3[200];
double d1;
double d2;
double d3;
int iStop = 0;
int iInVal;
E_Object* cAddedEl;
ME_Object* RetMesh;
C3dVector vPtIn[8];
//Create a new mesh for this unv
RetMesh = new ME_Object();
RetMesh->Create(inName,NULL,iMeshCnt);
iMeshCnt++;
RetMesh->TempList = new ObjTempList();
do
  {
  d1=0;
  fscanf(pFile,"%s",&s1);
  d1 = atof(s1);
  if (d1 == -1)
    {
    fscanf(pFile,"%s",&s1);
    fscanf(pFile,"%s",&s1);
    iInVal = atoi(s1);
    if (iInVal == 2411)
       {
       
      do
       {
       fscanf(pFile,"%i%i%i%i",&i1,&i2,&i3,&i4);
       fscanf(pFile,"%s%s%s",&s1,&s2,&s3);   
       d1 = atof(s1);
       d2 = atof(s2);
       d3 = atof(s3);
	     vPtIn[0].x = d1;
	     vPtIn[0].y = d2;
	     vPtIn[0].z = d3;
       if (i1 != -1)
        {
        RetMesh->AddNode(vPtIn[0], i1,i2,i3,i4+150,0,0);
        }
       else
        {
        iStop = 1;  
        }
       }
      while (iStop == 0);
       }
     } 
  if (feof(pFile))
     {
     iStop = 1;
     }
  }
while (iStop == 0);
rewind(pFile);
int i5;
int i6;
int i;
int iT=0;
iStop = 0;
int iNlabs[MaxSelNodes];
do
  {
  d1=0;
  fscanf(pFile,"%s",&s1);
  d1 = atof(s1);
  if (d1 == -1)
    {
    fscanf(pFile,"%s",&s1);
    fscanf(pFile,"%s",&s1);
    iInVal = atoi(s1);
    if (iInVal == 2412)     
     {
      do
      {
       fscanf(pFile,"%d %d %d %d %d %d",&i1,&i2,&i3,&i4,&i5,&i6);
       if ((i2 == 91) || (i2 == 94) || (i2 == 115) || (i2 == 112) || (i2 == 111) || (i2 == 122) || (i2 == 121) || (i2 == 136) || (i2 == 137) || (i2 == 181)  || (i2==161))
       {
          for (i=0;i<i6;i++)
          {
            fscanf(pFile,"%s",&s1);
            iNlabs[i] = atoi(s1);
          } 
          if (i2==121)
          {
            i2=i2;
          }
          cAddedEl=(E_Object*) RetMesh->AddEl2(iNlabs,i1,i5+150,i2,i3,i4,i6,0,0,0,-1,0);
          cAddedEl->PIDunv=i3;
       }
       else if ((i2==21) || (i2==22))
       {
		   int iA;
		   int iB;
		   int iC;
         fscanf(pFile,"%d %d %d",&iA,&iB,&iC);
         for (i=0;i<i6;i++)
         {
            fscanf(pFile,"%s",&s1);
            iNlabs[i] = atoi(s1);
         } 
		   cAddedEl=(E_Object*) RetMesh->AddEl2(iNlabs,i1,i5+150,i2,i3,i4,i6,iA,iB,iC,-1,0);
       cAddedEl->PIDunv=i3;
       }

       else
       {
         iStop = 1;
       } 
      }
      while (iStop == 0);
    }
  }

  if (feof(pFile))
     {
     //printf("\nEND OF FILE\n");
     iStop = 1;
     }
 }
while (iStop == 0);
delete(RetMesh->TempList);
RetMesh->TempList = NULL;
outtext1("Finished Read.");
return (RetMesh);
}




double atofNAS(CString SIN)
{
double drc=0;
int ifind = -1;
int il;
int i;
BOOL bDot=FALSE;;

CString SIN2;

il =SIN.GetLength();
for (i=0;i<il;i++)
{
  if (SIN[i]=='.')
  {
    bDot = TRUE;
  }
  if (bDot == TRUE)
  {
    if ((SIN[i]=='+') || (SIN[i]=='-'))
	{
	  if ((SIN[i-1]!='e') && (SIN[i-1]!='E'))
	  {
        SIN2+="e";
	  }
	}
  }
  SIN2+= SIN[i];
}
drc = atof(SIN2);
return (drc);
}

//***************************************************
//              NASTRAN FILE IMPORT
//***************************************************

CoordSys* NASReadCoord(ME_Object* pM,
                       NasCard& oC,
                       int iType,
	                   int iF)
{

  int iID;
  int iRID;
  C3dMatrix rMat;
  CoordSys* pRet;
  C3dVector Org;
  C3dVector X;
  C3dVector Y;
  C3dVector Z;
  iID=atoi(oC.GetField(0));
  iRID=atoi(oC.GetField(1));
  Org.x=atofNAS(oC.GetField(2));
  Org.y=atofNAS(oC.GetField(3));
  Org.z=atofNAS(oC.GetField(4));
  Z.x=atofNAS(oC.GetField(5));
  Z.y=atofNAS(oC.GetField(6));
  Z.z=atofNAS(oC.GetField(7));
  X.x=atofNAS(oC.GetField(8));
  X.y=atofNAS(oC.GetField(9));
  X.z=atofNAS(oC.GetField(10));
  Z-=Org;
  X-=Org;
  X.Normalize();
  Z.Normalize();
  Y = Z.Cross(X); 
  //Normalize below added
  Y.Normalize();
  X = Y.Cross(Z);
  rMat.MakeUnit();
  rMat.m_00 = X.x;
  rMat.m_10 = X.y;
  rMat.m_20 = X.z;
  rMat.m_01 = Y.x;
  rMat.m_11 = Y.y;
  rMat.m_21 = Y.z;
  rMat.m_02 = Z.x;
  rMat.m_12 = Z.y;
  rMat.m_22 = Z.z;
  pRet = pM->AddSys(Org,rMat,iRID,iType,iID,12);
  pRet->iFile = iF;
  return (pRet);
}

void NASReadGRID(ME_Object* pM,
                 NasCard& oC,
                 int iType,
	             int iF)
{
int iID;
int iDef;
int iOut;
double d1;
double d2;
double d3;
Node* pRet;
C3dVector vPtIn;
iID=atoi(oC.GetField(0));
iDef=atoi(oC.GetField(1));
d1=atofNAS(oC.GetField(2));
d2=atofNAS(oC.GetField(3));
d3=atofNAS(oC.GetField(4));
iOut=atoi(oC.GetField(5));
vPtIn.x = d1;
vPtIn.y = d2;
vPtIn.z = d3;
if (iID==6821383)
{
  iID=iID;
}
pRet=pM->AddNode(vPtIn, iID,1,1,1,iDef,iOut);
pRet->iFile = iF;
}

void NASReadGRIDD(ME_Object* pM,
                 FILE* pFile,
                 CString* L1, 
                 CString* LNext,
                 int iType,
	             int iF)
{
Node* pRet;
int iID;
int iDef;
int iOut;
double d1;
double d2;
double d3;
char s1[200];
C3dVector vPtIn;
iID=atoi(L1->Mid(8,8));
iDef=atoi(L1->Mid(16,16));
d1=atofNAS(L1->Mid(32,16));
d2=atofNAS(L1->Mid(48,16));
*L1=*LNext;
fgets(s1,200,pFile);
*LNext=s1;
d3=atofNAS(L1->Mid(8,16));
iOut=atoi(L1->Mid(24,16));
vPtIn.x = d1;
vPtIn.y = d2;
vPtIn.z = d3;
pRet=pM->AddNode(vPtIn, iID,1,1,1,iDef,iOut);
pRet->iFile = iF;
}


E_Object* NASReadCHEXA(NasCard& oC,
                        ME_Object* pM,
                        NEList* newPids,
                        int iType,
	                    int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;
iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));
iNlabs[2] = atoi(oC.GetField(4));
iNlabs[3] = atoi(oC.GetField(5));
iNlabs[4] = atoi(oC.GetField(6));
iNlabs[5] = atoi(oC.GetField(7));

iNlabs[6] = atoi(oC.GetField(8));
iNlabs[7] = atoi(oC.GetField(9));
E_Object* El=(E_Object*) pM->AddEl2(iNlabs,iID,159,115,iPID,1,8,0,0,0,-1,0);
El->PIDunv=iPID;
El->iFile = iF;
return (El);
}


E_Object* NASReadCONM2(NasCard& oC,
                       ME_Object* pM,
                       NEList* newPids,
                       int iType,
	                   int iF)
{
int iNlabs[MaxSelNodes];
int iID;
E_Object1* pE;
iID=atoi(oC.GetField(0));
iNlabs[0] = atoi(oC.GetField(1));
pE = (E_Object1*) (pM->AddEl2(iNlabs,iID,159,161,-1,1,1,0,0,0,-1,0));
pE->iCID= atoi(oC.GetField(2));
pE->dM= (ae(oC.GetField(3)));
pE->dX1= (ae(oC.GetField(4)));
pE->dX2= (ae(oC.GetField(5)));
pE->dX3= (ae(oC.GetField(6)));
if (oC.iNo>8)
{
  pE->dI11= (ae(oC.GetField(8)));
  pE->dI21= (ae(oC.GetField(9)));
  pE->dI22= (ae(oC.GetField(10)));
  pE->dI31= (ae(oC.GetField(11)));
  pE->dI32= (ae(oC.GetField(12)));
  pE->dI33= (ae(oC.GetField(13)));
}
pE->PIDunv=-1;
pE->iFile = iF;
return (pE);
}

E_Object* NASReadCONM1(NasCard& oC,
                       ME_Object* pM,
                       NEList* newPids,
                       int iType,
	                   int iF)
{
	outtext1("WARNING: CONM1 is not supported.");
	int iNlabs[MaxSelNodes];
	int iID;
	E_Object1* pE;
	iID = atoi(oC.GetField(0));
	iNlabs[0] = atoi(oC.GetField(1));
	pE = (E_Object1*)(pM->AddEl2(iNlabs, iID, 159, 161, -1, 1, 1, 0, 0, 0, -1, 0));
	pE->iCID = atoi(oC.GetField(2));
	pE->dM = (ae(oC.GetField(3)));
	//pE->dX1 = (ae(oC.GetField(4)));
	//pE->dX2 = (ae(oC.GetField(5)));
	//pE->dX3 = (ae(oC.GetField(6)));
	//if (oC.iNo > 8)
	//{
	//	pE->dI11 = (ae(oC.GetField(8)));
	//	pE->dI21 = (ae(oC.GetField(9)));
	//	pE->dI22 = (ae(oC.GetField(10)));
	//	pE->dI31 = (ae(oC.GetField(11)));
	//	pE->dI32 = (ae(oC.GetField(12)));
	//	pE->dI33 = (ae(oC.GetField(13)));
	//}
	pE->PIDunv = -1;
	pE->iFile = iF;
	return (pE);
}

E_Object* NASReadCQUAD4(NasCard& oC,
                        ME_Object* pM,
                        NEList* newPids,
                        int iType,
	                    int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;
int MCID;
double dAng;
CString sT;

iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));
iNlabs[2] = atoi(oC.GetField(4));
iNlabs[3] = atoi(oC.GetField(5));
sT=oC.GetField(6);
if ((sT.Find('.') > -1) || (sT.Find("        ") > -1) || (sT=="\n"))
{
	dAng = atofNAS(sT);
	MCID = -1;
}
else
{
	dAng = 0;
	MCID = atoi(sT);;
}
double dZ;
dZ = ae(oC.GetField(7));
E_Object4* El= (E_Object4*) pM->AddEl2(iNlabs,iID,157,94,iPID,1,4,0,0,0,MCID,dAng);
El->dZOFFS=dZ;
El->PIDunv=iPID;
El->iFile = iF;
return (El);
}

E_Object* NASReadCTRIA3(NasCard& oC,
                        ME_Object* pM,
                        NEList* newPids,
                        int iType,
	                    int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;
int MCID;
double dAng;
CString sT;

iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));
iNlabs[2] = atoi(oC.GetField(4));
sT=oC.GetField(5);
if ((sT.Find('.') > -1) || (sT.Find("        ") > -1) || (sT == "\n"))
{
   dAng=atofNAS(sT);
   MCID=-1;
}
else
{
   dAng=0;
   MCID=atoi(sT);;
}
double dZ;
dZ = ae(oC.GetField(6));
E_Object3* El=(E_Object3*) pM->AddEl2(iNlabs,iID,156,91,iPID,1,3,0,0,0,MCID,dAng);
El->dZOFFS=dZ;
El->PIDunv=iPID;
El->iFile = iF;
return (El);
}

E_Object* NASReadCQUAD4D(ME_Object* pM,
                         NEList* newPids,
                  FILE* pFile,
                  CString* L1, 
                  CString* LNext,
                  int iType,
	              int iF)
{
int iNlabs[MaxSelNodes];
char s1[200];
int iID;
int iPID;
int MCID;
double dAng;
CString sT;

iID=atoi(L1->Mid(8,8));
iPID=atoi(L1->Mid(16,16)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(L1->Mid(32,16));
iNlabs[1] = atoi(L1->Mid(48,16));
*L1=*LNext;
fgets(s1,200,pFile);
*LNext=s1;
iNlabs[2] = atoi(L1->Mid(8,16));
iNlabs[3] = atoi(L1->Mid(24,16));
sT=L1->Mid(40,16);
if ((sT.Find('.') > -1) || (sT.Find("        ") > -1) || (sT == "\n"))
{
   dAng=atofNAS(sT);
   MCID=-1;
}
else
{
   dAng=0;
   MCID=atoi(sT);;
}

E_Object* pE=(E_Object*) pM->AddEl2(iNlabs,iID,7,94,iPID,1,4,0,0,0,MCID,dAng);
pE->PIDunv=iPID;
pE->iFile = iF;
return (pE);
}


E_Object* NASReadCPENTA(NasCard& oC,
                        ME_Object* pM,
                        NEList* newPids,
                        int iType,
                        int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;

iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));
iNlabs[2] = atoi(oC.GetField(4));
iNlabs[3] = atoi(oC.GetField(5));
iNlabs[4] = atoi(oC.GetField(6));
iNlabs[5] = atoi(oC.GetField(7));
E_Object* pE=(E_Object*) pM->AddEl2(iNlabs,iID,159,112,iPID,1,6,0,0,0,-1,0);
pE->PIDunv=iPID;
pE->iFile = iF;
return (pE);
}

E_Object2* NASReadCBUSH(NasCard& oC,
                       ME_Object* pM,
                       NEList* newPids,
                       int iType,
					   int& iONID,
					   C3dVector& pUp,
	                   int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;
CString sOmid;

iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));

pUp.x=(ae(oC.GetField(4)));
pUp.y=(ae(oC.GetField(5)));
pUp.z=(ae(oC.GetField(6)));

sOmid=oC.GetField(4);
iONID=-1;
if (sOmid.Find(".")==-1)
{
  iONID=atoi(oC.GetField(7));
}

E_Object2* pE=(E_Object2*) pM->AddEl2(iNlabs,iID,7,136,iPID,1,2,0,0,0, iONID,0);
pE->PIDunv=iPID;
pE->iFile = iF;
return(pE);
}

E_Object2B* NASReadCBAR(NasCard& oC,
                        ME_Object* pM,
                        NEList* newPids,
                        int iType,
					   int& iONID,
					   C3dVector& pUp,
					   C3dVector& OffA,
					   C3dVector& OffB,
	                   int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;
CString sOmid;


E_Object2B* pB;
E_Object* pE;
iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));

pUp.x=(ae(oC.GetField(4)));
pUp.y=(ae(oC.GetField(5)));
pUp.z=(ae(oC.GetField(6)));

sOmid=oC.GetField(4);
iONID=-1;
if (sOmid.Find(".")==-1)
{
  iONID=atoi(oC.GetField(4));
}
CString Pin1="";
CString Pin2="";
pE = pM->AddEl2(iNlabs,iID,7,21,iPID,1,2,0,0,0,-1,0);
pB=(E_Object2B*) pE;
OffA*=0;
OffB*=0;
if (oC.iNo>8)
{
  Pin1=oC.GetField(8);
  Pin2=oC.GetField(9);
  OffA.x=(ae(oC.GetField(10)));
  OffA.y=(ae(oC.GetField(11)));
  OffA.z=(ae(oC.GetField(12)));
  OffB.x=(ae(oC.GetField(13)));
  OffB.y=(ae(oC.GetField(14)));
  OffB.z=(ae(oC.GetField(15)));
}
pB->SetDOFStringA(Pin1);
pB->SetDOFStringB(Pin2);
pB->PIDunv=iPID;
pB->iFile = iF;
return (pB);
}

E_Object2B* NASReadCBEAM(NasCard& oC,
                       ME_Object* pM,
                       NEList* newPids,
                       int iType,
					   int& iONID,
					   C3dVector& pUp,
					   C3dVector& OffA,
					   C3dVector& OffB,
	                   int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;
CString sOmid;


E_Object2B* pB;
E_Object* pE;
iID=atoi(oC.GetField(0));
if (iID==68700267)
  iID=iID;

iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));

pUp.x=(ae(oC.GetField(4)));
pUp.y=(ae(oC.GetField(5)));
pUp.z=(ae(oC.GetField(6)));

sOmid=oC.GetField(4);
iONID=-1;
if (sOmid.Find(".")==-1)
{
  iONID=atoi(oC.GetField(4));
}
CString Pin1="";
CString Pin2="";
pE = pM->AddEl2(iNlabs,iID,7,22,iPID,1,2,0,0,0,-1,0);
pB=(E_Object2B*) pE;
OffA*=0;
OffB*=0;
if (oC.iNo>8)
{
  Pin1=oC.GetField(8);
  Pin2=oC.GetField(9);
  OffA.x=(ae(oC.GetField(10)));
  OffA.y=(ae(oC.GetField(11)));
  OffA.z=(ae(oC.GetField(12)));
  OffB.x=(ae(oC.GetField(13)));
  OffB.y=(ae(oC.GetField(14)));
  OffB.z=(ae(oC.GetField(15)));
}
pB->SetDOFStringA(Pin1);
pB->SetDOFStringB(Pin2);
pB->PIDunv=iPID;
pB->iFile = iF;
return (pB);
}


E_Object* NASReadCTETRA(NasCard& oC,
                        ME_Object* pM,
                        NEList* newPids,
                        int iType,
                        int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID;

iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1)); 
iPID=newPids->Get(iPID);
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));
iNlabs[2] = atoi(oC.GetField(4));
iNlabs[3] = atoi(oC.GetField(5));
iNlabs[4] = atoi(oC.GetField(6));
iNlabs[5] = atoi(oC.GetField(7));
iNlabs[6] = atoi(oC.GetField(8));
iNlabs[7] = atoi(oC.GetField(9));
iNlabs[8] = atoi(oC.GetField(10));
iNlabs[9] = atoi(oC.GetField(11));
E_Object* pE;
if (iNlabs[5]==0)
   pE=(E_Object*) pM->AddEl2(iNlabs,iID,162,111,iPID,1,4,0,0,0,-1,0);
else
   pE = (E_Object*)pM->AddEl2(iNlabs, iID, 162, 310, iPID, 1, 10, 0, 0, 0, -1, 0);
pE->PIDunv=iPID;
pE->iFile = iF;
return (pE);
}

E_Object* NASReadRBE2(NasCard& oC,
                      ME_Object* pM,
                      NEList* newPids,
                      int iType,
	                  int iF)
{
int iNlabs[MaxSelNodes];
int iID;
int iPID=0;
int iFN;
int i;
int iNDID;
double dCTE = 0.0;
CString sDof;
CString sF;
iID=atoi(oC.GetField(0));
iNlabs[0] = atoi(oC.GetField(1));
sDof=oC.GetField(2); 
iFN=4;
int iCnt=1;
for (i=3;i<oC.iNo;i++)
{
  sF = oC.GetField(i);
  iNDID= atoi(sF);
  if ((iNDID>0) && (sF.Find(".")==-1))
  {
    iNlabs[iCnt] = iNDID;
    iCnt++;
	if (iCnt > 199) 
	   {
		outtext1("ERROR: Max Number of Nodes in RBE2 Reached.");
		break;
	   }
  } 
  else if (sF.Find(".") != -1)
	  dCTE = atofNAS(sF);
}
//sF = oC.GetField(oC.iNo-3);


E_ObjectR* pR =(E_ObjectR*) pM->AddEl2(iNlabs,iID,160,122,iPID,1,iCnt,0,0,0,-1,0);
pR->SetDOFString(sDof);
pR->dALPHA = dCTE;
pR->iFile = iF;
return (pR);
}


E_Object* NASReadRBAR(NasCard& oC,
                      ME_Object* pM,
                      NEList* newPids,
                      int iType,
	                  int iF)
{
int iNlabs[MaxSelNodes];

int iID;
int iPID=0;

double ALPHA;
CString CNA;
CString CNB;
CString CMA;
CString CMB;

iID=atoi(oC.GetField(0));
iNlabs[0] = atoi(oC.GetField(1));
iNlabs[1] = atoi(oC.GetField(2));
CNA= oC.GetField(3);
CNB= oC.GetField(4);
CMA= oC.GetField(5);
CMA= oC.GetField(6);
ALPHA= atofNAS(oC.GetField(7));
//sDof=L1->Mid(24,8); 

//iNDID= atoi(L1->Mid(iFN*8,8));

E_ObjectR2* pR =(E_ObjectR2*) pM->AddEl2(iNlabs,iID,160,121,iPID,1,2,0,0,0,-1,0);
pR->SetOther(CNA,CNB,CMA,CMA,ALPHA);
pR->iFile = iF;
return (pR);
}

E_Object* NASReadCROD(NasCard& oC,
                      ME_Object* pM,
                      NEList* newPids,
                      int iType,
                      int iF)
{
int iNlabs[MaxSelNodes];

int iID;
int iPID=0;


iID=atoi(oC.GetField(0));
iPID=atoi(oC.GetField(1));
iNlabs[0] = atoi(oC.GetField(2));
iNlabs[1] = atoi(oC.GetField(3));

E_ObjectR2* pR =(E_ObjectR2*) pM->AddEl2(iNlabs,iID,160,11,iPID,1,2,0,0,0,-1,0);
pR->iFile = iF;
return (pR);
}

void NASReadSPC(NasCard& oC,
	            ME_Object* pM,
	            int iF)
{
	char S1[200];
	cLinkedListB* pBCSET = nullptr;
	Node* pN = nullptr;
	int iID;
	int iND;
	double dEnf;
	int iSet;
	CString sDOF;
	BOOL xon, yon, zon, rxon, ryon, rzon;
	xon = FALSE; yon = FALSE; zon = FALSE;
	rxon = FALSE; ryon = FALSE; rzon = FALSE;

	iID = atoi(oC.GetField(0));
	iND = atoi(oC.GetField(1));
	sDOF = oC.GetField(2);
	dEnf = atofNAS(oC.GetField(3));

	//if it exists get the BC Set else create one
	pBCSET = pM->GetBC(iID);
	if (pBCSET == nullptr)
	{
		sprintf_s(S1, "BC SET : %i", iID);
		iSet = pM->CreateBC(iID, S1);
		pBCSET = pM->GetBC(iID);
	}
	pN = pM->GetNode(iND);
	if ((pN != nullptr) && (pBCSET != nullptr))
	{
		if (sDOF.Find("1", 0))
			xon = TRUE;
		if (sDOF.Find("2", 0))
			yon = TRUE;
		if (sDOF.Find("3", 0))
			zon = TRUE;
		if (sDOF.Find("4", 0))
			rxon = TRUE;
		if (sDOF.Find("5", 0))
			ryon = TRUE;
		if (sDOF.Find("6", 0))
			rzon = TRUE;
		G_Object* cAddedR = pM->AddRestraint(pN, xon, yon, zon, rxon, ryon, rzon, iID);

	}
	else
	{
		outtext1("ERROR: In Creating SPC.");
		return;
	}	
}

void NASReadFORCE(NasCard& oC,
	              ME_Object* pM,
	              int iF)
{
	char S1[200];
	cLinkedList* pLCSET = nullptr;
	Node* pN = nullptr;
	int iID;
	int iND;
	int iCID = 0;
	double dS = 0;
	C3dMatrix TMat;
	TMat.MakeUnit();
	C3dVector F;
	F.Set(0, 0, 0);
	int iSet;
	iID = atoi(oC.GetField(0));
	iND = atoi(oC.GetField(1));
	iCID = atoi(oC.GetField(2));
	dS = atofNAS(oC.GetField(3));
	F.x = atofNAS(oC.GetField(4));
	F.y = atofNAS(oC.GetField(5));
	F.z = atofNAS(oC.GetField(6));
	//if it exists get the BC Set else create one
	pLCSET = pM->GetLC(iID);
	if (pLCSET == nullptr)
	{
		sprintf_s(S1, "LC SET : %i", iID);
		iSet = pM->CreateLC(iID, S1);
		pLCSET = pM->GetLC(iID);
	}
	pN = pM->GetNode(iND);
	if ((pN != nullptr) && (pLCSET != nullptr))
	{
		if (pN->OutSys != 0)
		{
			TMat = pM->GetNodalSys(pN);
		}
		G_Object* cAddedF = pM->AddForce((Node*)pN, TMat * F, iID);
	}
	else
	{
		outtext1("ERROR: In Creating FORCE.");
		return;
	}
}

void NASReadMOMENT(NasCard& oC,
	ME_Object* pM,
	int iF)
{
	char S1[200];
	cLinkedList* pLCSET = nullptr;
	Node* pN = nullptr;
	int iID;
	int iND;
	int iCID = 0;
	double dS = 0;
	C3dMatrix TMat;
	TMat.MakeUnit();
	C3dVector F;
	F.Set(0, 0, 0);
	int iSet;
	iID = atoi(oC.GetField(0));
	iND = atoi(oC.GetField(1));
	iCID = atoi(oC.GetField(2));
	dS = atofNAS(oC.GetField(3));
	F.x = atofNAS(oC.GetField(4));
	F.y = atofNAS(oC.GetField(5));
	F.z = atofNAS(oC.GetField(6));
	//if it exists get the BC Set else create one
	pLCSET = pM->GetLC(iID);
	if (pLCSET == nullptr)
	{
		sprintf_s(S1, "LC SET : %i", iID);
		iSet = pM->CreateLC(iID, S1);
		pLCSET = pM->GetLC(iID);
	}
	pN = pM->GetNode(iND);
	if ((pN != nullptr) && (pLCSET != nullptr))
	{
		if (pN->OutSys != 0)
		{
			TMat = pM->GetNodalSys(pN);
		}
		G_Object* cAddedF = pM->AddMoment((Node*)pN, TMat * F, iID);
	}
	else
	{
		outtext1("ERROR: In Creating MOMENT.");
		return;
	}
}


void NASReadPLOAD(NasCard& oC,
	ME_Object* pM,
	int iF)
{
	char S1[200];
	cLinkedList* pLCSET = nullptr;
	E_Object* pE = nullptr;
	int iID;
	int iN1 = -1;
	int iN2 = -1;
	int iN3 = -1;
	int iN4 = -1;
	int iSet;
	double dPr = 0;
	C3dVector vP;
	iID = atoi(oC.GetField(0));
	dPr = atofNAS(oC.GetField(1));
	iN1 = atoi(oC.GetField(2));
	iN2 = atoi(oC.GetField(3));
	iN3 = atoi(oC.GetField(4));
	iN4 = atoi(oC.GetField(5));
	//if it exists get the BC Set else create one
	pLCSET = pM->GetLC(iID);
	if (pLCSET == nullptr)
	{
		sprintf_s(S1, "LC SET : %i", iID);
		iSet = pM->CreateLC(iID, S1);
		pLCSET = pM->GetLC(iID);
	}
	//pE=pM->FindElement()
	pE = pM->GetShellFromNodes(iN1, iN2, iN3);
	if ((pE != nullptr) && (pLCSET != nullptr))
	{
		//presure is stored in vector x only
		vP.x = dPr; vP.y = 0; vP.z = 0;
		G_Object* PLoad = pM->AddPressure((E_Object*)pE, vP, iID);
	}
	else
	{
		outtext1("ERROR: In Creating PLOAD.");
		return;
	}
}

void NASReadTEMP(NasCard& oC,
	             ME_Object* pM,
	             int iF)
{
	char S1[200];
	cLinkedList* pTSET = nullptr;
	Node* pN = nullptr;
	int iSID = -1;
	int iID = -1;
	int iSet = -1;
	double dT = 0;
	C3dVector vP;
	iSID = atoi(oC.GetField(0));
	iID = atoi(oC.GetField(1));
	dT = atofNAS(oC.GetField(2));

	//if it exists get the BC Set else create one
	pTSET = pM->GetTSET(iSID);
	if (pTSET == nullptr)
	{
		sprintf_s(S1, "TSET : %i", iSID);
		iSet = pM->CreateTSET(iSID, S1);
		pTSET = pM->GetTSET(iSID);
	}
	//pE=pM->FindElement()
	pN = pM->GetNode(iID);
	if ((pN != nullptr) && (pTSET != nullptr))
	{
		G_Object* pT = pM->AddTemperature(pN,dT, iSet);
	}
	else
	{
		outtext1("ERROR: In Creating TEMP.");
		return;
	}
}

void NASReadTEMPD(NasCard& oC,
	ME_Object* pM,
	int iF)
{
	char S1[200];
	cLinkedList* pTSET = nullptr;
	//Node* pN = nullptr;
	int iSID = -1;
	int iSet = -1;
	//int iID = -1;
	double dT = 0;
	iSID = atoi(oC.GetField(0));

	dT = atofNAS(oC.GetField(1));

	////if it exists get the BC Set else create one
	pTSET = pM->GetTSET(iSID);
	if (pTSET == nullptr)
	{
		sprintf_s(S1, "TEMPD : %i", iSID);
		iSet = pM->CreateTSET(iSID, S1);
		pTSET = pM->GetTSET(iSID);
	}

	if (pTSET != nullptr)
	{
		G_Object* pT = pM->AddTempD(dT, iSID);
	}
	else
	{
		outtext1("ERROR: In Creating TEMPD.");
		return;
	}
}


void NASReadGRAV(NasCard& oC,
	             ME_Object* pM,
	             int iF)
{
	char S1[200];
	cLinkedList* pLSET = nullptr;
	int iSID = -1;
	int iCID = -1;
	int iSet = -1;
	double dScl = 0;
	C3dVector vV;
	iSID = atoi(oC.GetField(0));
	iCID = atoi(oC.GetField(1));
	dScl = atofNAS(oC.GetField(2));
	vV.x = atofNAS(oC.GetField(3));
	vV.y = atofNAS(oC.GetField(4));
	vV.z = atofNAS(oC.GetField(5));

	////if it exists get the BC Set else create one
	pLSET = pM->GetLC(iSID);
	if (pLSET == nullptr)
	{
		sprintf_s(S1, "GRAV : %i", iSID);
		iSet = pM->CreateLC(iSID, S1);
		pLSET = pM->GetLC(iSID);
	}

	if (pLSET != nullptr)
	{
		G_Object* pT = pM->AddGRAV(iSID, iCID, dScl,vV);
	}
	else
	{
		outtext1("ERROR: In Creating GRAV.");
		return;
	}
}

void NASReadPSHELL(NasCard& oC,
                   PropTable* pM,
                   NEList* cPID,
                   int iType,
                   BOOL Relab,
	               int iF)
{

PSHELL* pS=new PSHELL();
CString sisNext;
pS->iType=1;
pS->sTitle="PSHELL CARD";
pS->iID=atoi(oC.GetField(0));
pS->iMID1=atoi(oC.GetField(1)); 
pS->dT=atofNAS(oC.GetField(2)); 
pS->iMID2=atoi(oC.GetField(3)); 
pS->d12IT3=atofNAS(oC.GetField(4)); 
pS->iMID3=atoi(oC.GetField(5));
pS->dTST=atofNAS(oC.GetField(6)); 
pS->dNSM=atofNAS(oC.GetField(7));
if (oC.iNo>8)
{
  pS->dZ1=atofNAS(oC.GetField(8));
  pS->dZ2=atofNAS(oC.GetField(9));
  pS->iMID4=atoi(oC.GetField(10));
}

int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
cPID->Add(pS->iID,NextID);
pS->iID=NextID;
pS->iFile = iF;
pM->AddItem(pS);
}

void NASReadPBAR(NasCard& oC,
                 PropTable* pM,
                 NEList* cPID,
                 int iType,
                 BOOL Relab,
	             int iF)
{
PBAR* pS=new PBAR();
pS->iType=4;
pS->sTitle="PBAR CARD";
pS->iID=atoi(oC.GetField(0));
pS->iMID=atoi(oC.GetField(1));
pS->dA=(ae(oC.GetField(2)));
pS->dI1=(ae(oC.GetField(3)));
pS->dI2=(ae(oC.GetField(4)));
pS->dJ=(ae(oC.GetField(5)));
pS->dNSM=(ae(oC.GetField(6)));
if (oC.iNo>8)
{
  pS->dC1=(ae(oC.GetField(8)));
  pS->dC2=(ae(oC.GetField(9)));
  pS->dD1=(ae(oC.GetField(10)));
  pS->dD2=(ae(oC.GetField(11)));
  pS->dE1=(ae(oC.GetField(12)));
  pS->dE2=(ae(oC.GetField(13)));
  pS->dF1=(ae(oC.GetField(14)));
  pS->dF2=(ae(oC.GetField(15)));
}
if (oC.iNo>15)
{
  pS->dK1=(ae(oC.GetField(16)));
  pS->dK2=(ae(oC.GetField(17)));
  pS->dI12=(ae(oC.GetField(18)));
}
int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
cPID->Add(pS->iID,NextID);
pS->iID=NextID;
pS->CreateSec();
pS->iFile = iF;
pM->AddItem(pS);
}


void NASReadPROD(NasCard& oC,
                 PropTable* pM,
                 NEList* cPID,
                 int iType,
                 BOOL Relab,
	             int iF)
{
PROD* pS=new PROD();
pS->iType=11;
pS->sTitle="PROD CARD";
pS->iID=atoi(oC.GetField(0));
pS->iMID=atoi(oC.GetField(1));
pS->A=(ae(oC.GetField(2)));
pS->J=(ae(oC.GetField(3)));

int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
cPID->Add(pS->iID,NextID);
pS->iID=NextID;
pS->CreateSec();
pS->iFile = iF;
pM->AddItem(pS);
}

void NASReadPBUSH(NasCard& oC,
	              PropTable* pM,
	              NEList* cPID,
	              int iType,
	              BOOL Relab,
	              int iF)
{
	PBUSH* pS = new PBUSH();
	pS->iType = 138;
	pS->sTitle = "PBUSH CARD";
	pS->sFlg = "K";
	pS->iID = atoi(oC.GetField(0));
	pS->dK1 = (ae(oC.GetField(2)));
	pS->dK2 = (ae(oC.GetField(3)));
	pS->dK3 = (ae(oC.GetField(4)));
	pS->dK4 = (ae(oC.GetField(5)));
	pS->dK5 = (ae(oC.GetField(6)));
	pS->dK6 = (ae(oC.GetField(7)));
	int NextID;
	if (Relab)
		NextID = pM->NextID();
	else
		NextID = pS->iID;
	cPID->Add(pS->iID, NextID);
	pS->iID = NextID;
	pS->iFile = iF;
	pM->AddItem(pS);
}

BOOL NASReadPBEAM_C2(FILE* pFile,
	                 CString* L1,
	                 CString* LNext,
	                 PBEAM* pS,
	                 int iF)
{
char s1[200];
BOOL bN=FALSE;
BOOL bRet=FALSE;
CString SONext;
SONext=LNext->Mid(8,8);
if ((SONext.Find ("YES")>-1) && (SONext.Find ("YESA")==-1))
{
bN=TRUE;
}
if ((SONext.Find ("NO")>-1) ||
    (SONext.Find ("YES")>-1))
{
  bRet=TRUE;
  fgets(s1,200,pFile);
  *L1=*LNext;
  *LNext=s1;

  pS->SO[pS->iNo]=L1->Mid(8,8);
  pS->XXB[pS->iNo]=(aeB(L1->Mid(16,8)));
  pS->A[pS->iNo]=(aeB(L1->Mid(24,8)));
  pS->I1[pS->iNo]=(aeB(L1->Mid(32,8)));
  pS->I2[pS->iNo]=(aeB(L1->Mid(40,8)));
  pS->I12[pS->iNo]=(aeB(L1->Mid(48,8)));
  pS->J[pS->iNo]=(aeB(L1->Mid(56,8)));
  pS->NSM[pS->iNo]=(aeB(L1->Mid(64,8)));
  fgets(s1,200,pFile);
  if (bN==TRUE)
  {
    *L1=*LNext;
    *LNext=s1;
    pS->C1[pS->iNo]=(aeB(L1->Mid(8,8)));
    pS->C2[pS->iNo]=(aeB(L1->Mid(16,8)));
    pS->D1[pS->iNo]=(aeB(L1->Mid(24,8)));
    pS->D2[pS->iNo]=(aeB(L1->Mid(32,8)));
    pS->E1[pS->iNo]=(aeB(L1->Mid(40,8)));
    pS->E2[pS->iNo]=(aeB(L1->Mid(48,8)));
    pS->F1[pS->iNo]=(aeB(L1->Mid(56,8)));
    pS->F2[pS->iNo]=(aeB(L1->Mid(64,8)));
    
  }
  pS->iNo++;
  pS->iFile = iF;
}
return (bRet);
}

void NASReadPBEAM(NasCard& oC,
                  PropTable* pM,
                  NEList* cPID,
                  int iType,
                  BOOL Relab,
	              int iF)
{
PBEAM* pS=new PBEAM();
pS->iType=6;
pS->sTitle="PBEAM CARD";
pS->iID=atoi(oC.GetField(0));
if (pS->iID==68735132)
  pS->iID=pS->iID;
pS->iMID=atoi(oC.GetField(1));
pS->A[0]=(aeB(oC.GetField(2)));
pS->I1[0]=(aeB(oC.GetField(3)));
pS->I2[0]=(aeB(oC.GetField(4)));
pS->I12[0]=(aeB(oC.GetField(5)));
pS->J[0]=(aeB(oC.GetField(6)));
pS->NSM[0]=(aeB(oC.GetField(7)));
//fgets(s1,200,pFile);
//*L1=*LNext;
//*LNext=s1;
//pS->C1[0]=(aeB(L1->Mid(8,8)));
//pS->C2[0]=(aeB(L1->Mid(16,8)));
//pS->D1[0]=(aeB(L1->Mid(24,8)));
//pS->D2[0]=(aeB(L1->Mid(32,8)));
//pS->E1[0]=(aeB(L1->Mid(40,8)));
//pS->E2[0]=(aeB(L1->Mid(48,8)));
//pS->F1[0]=(aeB(L1->Mid(56,8)));
//pS->F2[0]=(aeB(L1->Mid(64,8)));
//
//BOOL bR;
//do
//{
//bR= NASReadPBEAM_C2(pFile,L1,LNext,pS);
//}
//while (bR==TRUE);
//CString ssN;
//ssN=LNext->Mid(0,1);
//if ((ssN==" ") || (ssN=="+"))
//{
//  fgets(s1,200,pFile);
//  *L1=*LNext;
//  *LNext=s1;
//  pS->K1=aeB(L1->Mid(8,8));
//  pS->K2=aeB(L1->Mid(16,8));
//  pS->S1=aeB(L1->Mid(24,8));
//  pS->S2=aeB(L1->Mid(32,8));
//  pS->NSIA=aeB(L1->Mid(40,8));
//  pS->NSIB=aeB(L1->Mid(48,8));
//  pS->CWA=aeB(L1->Mid(56,8));
//  pS->CWB=aeB(L1->Mid(64,8));
//}
//ssN=LNext->Mid(0,1);
//if ((ssN==" ") || (ssN=="+"))
//{
//  fgets(s1,200,pFile);
//  *L1=*LNext;
//  *LNext=s1;
//  pS->M1A=aeB(L1->Mid(8,8));
//  pS->M2A=aeB(L1->Mid(16,8));
//  pS->M1B=aeB(L1->Mid(24,8));
//  pS->M2B=aeB(L1->Mid(32,8));
//  pS->N1A=aeB(L1->Mid(40,8));
//  pS->N2A=aeB(L1->Mid(48,8));
//  pS->N1B=aeB(L1->Mid(56,8));
//  pS->N2B=aeB(L1->Mid(64,8));
//}
//
//
int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
cPID->Add(pS->iID,NextID);
pS->iID=NextID;
pS->CreateSec();
pS->iFile = iF;
pM->AddItem(pS);
}

void NASReadPBARL(NasCard& oC,
                   PropTable* pM,
                   NEList* cPID,
                   int iType,
                   BOOL Relab,
	               int iF)
{
PBARL* pS=new PBARL();
pS->iType=5;
pS->sTitle="PBARL CARD";
pS->iID=atoi(oC.GetField(0));
pS->iMID=atoi(oC.GetField(1));
pS->sGROUP=oC.GetField(2);
pS->sSecType=oC.GetField(3);
int iNoDims=pS->GetNoDims();
pS->iNoDims=iNoDims;
int i;
int iCnt;
iCnt=8;
for (i=8;i<iNoDims+8;i++)
{
  pS->dDIMs[i-8]=(ae(oC.GetField(i)));
  iCnt++;
}
pS->dNSM=(ae(oC.GetField(iCnt)));
pS->CreateSec();

int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
cPID->Add(pS->iID,NextID);
pS->iID=NextID;
pS->iFile = iF;
pM->AddItem(pS);
}


void NASReadPSOLID(NasCard& oC,
                   PropTable* pM,
                   NEList* cPID,
                   int iType,
                   BOOL Relab,
	               int iF)
{
PSOLID* pS=new PSOLID();
pS->iType=3;
pS->sTitle="PSOLID CARD";
pS->iID=atoi(oC.GetField(0));
pS->iMID=atoi(oC.GetField(1)); 
pS->iCORDM=atoi(oC.GetField(2)); 
pS->sIN=oC.GetField(3); 
pS->sSTRESS=oC.GetField(4); 
pS->sISOP=oC.GetField(5);
pS->sFCTN=oC.GetField(6); 

int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
cPID->Add(pS->iID,NextID);
pS->iID=NextID;
pS->iFile = iF;
pM->AddItem(pS);
}

void NASReadMAT1(NasCard& oC,
                 MatTable* pM,
                 NEList* nMats,
                 int iType,
                 BOOL Relab,
	             int iF)
{
MAT1* pS=new MAT1();
pS->iType=1;
pS->sTitle="MAT1 CARD";
pS->iID=atoi(oC.GetField(0));
pS->dE=(ae(oC.GetField(1)));
if (oC.GetField(2)!="        ")
  pS->dG=(aeB(oC.GetField(2)));
else
  pS->dG = 0;
pS->dNU=atof(oC.GetField(3));
pS->dRHO=atof(oC.GetField(4));
pS->dA=(ae(oC.GetField(5)));
pS->dTREF=atof(oC.GetField(6));
pS->dGE=atof(oC.GetField(7));
//
//pS->dST=atof(L1->Mid(8,8));
//pS->dSC=atof(L1->Mid(16,8));
//pS->dSS=atof(L1->Mid(24,8));
//pS->iMCSID=atoi(L1->Mid(32,8));
int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
nMats->Add(pS->iID,NextID);
pS->iID=NextID;
pS->iFile = iF;
pM->AddItem(pS);
}

void NASReadMAT8(NasCard& oC,
                 MatTable* pM,
                 NEList* nMats,
                 int iType,
                 BOOL Relab,
	             int iF)
{
MAT8* pS=new MAT8();
pS->iType=8;
pS->sTitle="MAT8 CARD";
pS->iID=atoi(oC.GetField(0));
pS->dE1=(ae(oC.GetField(1)));
pS->dE2=(ae(oC.GetField(2)));
pS->dNU12=(ae(oC.GetField(3)));
pS->dG12=(ae(oC.GetField(4)));
pS->dG1Z=(ae(oC.GetField(5)));
pS->dG2Z=(ae(oC.GetField(6)));
pS->dRHO=(ae(oC.GetField(7)));

pS->dA1=(ae(oC.GetField(8)));
pS->dA2=(ae(oC.GetField(9)));
pS->dTREF=(ae(oC.GetField(10)));
pS->dXt=(ae(oC.GetField(11)));
pS->dXc=(ae(oC.GetField(12)));
pS->dYt=(ae(oC.GetField(13)));
pS->dYc=(ae(oC.GetField(14)));
pS->dS=(ae(oC.GetField(15)));

pS->dGE=(ae(oC.GetField(16)));
pS->F12=(ae(oC.GetField(17)));
CString sT = oC.GetField(18);
if (sT.Find("STRN") >= 0)
  pS->STRN=1;


int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
nMats->Add(pS->iID,NextID);
pS->iID=NextID;
pS->iFile = iF;
pM->AddItem(pS);
}

void NASReadPCOMP(NasCard& oC,
                  PropTable* pM,
                  NEList* cPID,
                  int iType,
                  BOOL Relab,
	              int iF)
{
int iFT;
int iStop=0;
int iM;
double dThk;
double dTh;
bool bOut=FALSE;
CString sT;

PCOMP* pS=new PCOMP();
pS->iType=2;
pS->sTitle="PCOMP CARD";
pS->iID=atoi(oC.GetField(0));

pS->dNSM=atofNAS(oC.GetField(2)); 
pS->dSB=atofNAS(oC.GetField(3)); 
sT=oC.GetField(4); 
if (sT.Find("HILL") >= 0)
	iFT = 1;
else if (sT.Find("HOFF") >= 0)
	iFT = 2;
else if (sT.Find("TSAI") >= 0)
	iFT = 3;
else if (sT.Find("STRESS") >= 0)
	iFT = 4;
else if ((sT.Find("STRAIN") >= 0) || (sT.Find("STRN") >= 0))
	iFT = 5;
else if (sT.Find("LARCO2") >= 0)
	iFT = 6;
else if (sT.Find("PUCK") >= 0)
	iFT = 7;
else if (sT.Find("MCT") >= 0)
	iFT = 8;
else
	iFT=0;
pS->FT=iFT;
pS->dRefT=atofNAS(oC.GetField(5)); 
pS->dGE=atofNAS(oC.GetField(6));
sT=oC.GetField(7);
if (sT.Find("SYM") >= 0)
  pS->bLAM=TRUE;
else
  pS->bLAM=FALSE;
int iCnt=8;
do
{
  iM=atoi(oC.GetField(iCnt)); 
  dThk=atofNAS(oC.GetField(iCnt+1));
  dTh=atofNAS(oC.GetField(iCnt+2));
  sT=oC.GetField(iCnt+3);
  if (sT.Find("YES") >= 0)
    bOut=TRUE;
  else if (sT.Find("NO") >= 0)
    bOut=FALSE;
  else
	bOut = FALSE;
  if (iM!=0)
    pS->AddLayer(iM,dThk,dTh,bOut);
  iCnt=iCnt+4;
}
while (iCnt<oC.iNo);
if (oC.isVoid(1))
  pS->dZ0=-pS->GetThk()/2;
else
  pS->dZ0=atofNAS(oC.GetField(1)); 

int NextID;
if (Relab)
 NextID=pM->NextID();
else 
 NextID=pS->iID;
cPID->Add(pS->iID,NextID);
pS->iID=NextID;
pS->iFile = iF;
pM->AddItem(pS);

}

void NASReadPCOMPG(NasCard& oC,
	               PropTable* pM,
	               NEList* cPID,
	               int iType,
	               BOOL Relab,
	               int iF)
{
	int iFT;
	int iStop = 0;
	int iPlyID;
	int iM;
	double dThk;
	double dTh;
	bool bOut = FALSE;
	CString sT;

	PCOMPG* pS = new PCOMPG();
	pS->iType = 222;
	pS->sTitle = "PCOMPG CARD";
	pS->iID = atoi(oC.GetField(0));

	pS->dNSM = atofNAS(oC.GetField(2));
	pS->dSB = atofNAS(oC.GetField(3));
	sT = oC.GetField(4);
	if (sT.Find("HILL") >= 0)
		iFT = 1;
	else if (sT.Find("HOFF") >= 0)
		iFT = 2;
	else if (sT.Find("TSAI") >= 0)
		iFT = 3;
	else if (sT.Find("STRESS") >= 0)
		iFT = 4;
	else if ((sT.Find("STRAIN") >= 0) || (sT.Find("STRN") >= 0))
		iFT = 5;
	else if (sT.Find("LARCO2") >= 0)
		iFT = 6;
	else if (sT.Find("PUCK") >= 0)
		iFT = 7;
	else if (sT.Find("MCT") >= 0)
		iFT = 8;
	else
		iFT = 0;
	pS->FT = iFT;
	pS->dRefT = atofNAS(oC.GetField(5));
	pS->dGE = atofNAS(oC.GetField(6));
	sT = oC.GetField(7);
	if (sT.Find("SYM") >= 0)
		pS->bLAM = TRUE;
	else
		pS->bLAM = FALSE;
	int iCnt = 8;
	do
	{
		iPlyID = atoi(oC.GetField(iCnt));
		iM = atoi(oC.GetField(iCnt+1));
		dThk = atofNAS(oC.GetField(iCnt + 2));
		dTh = atofNAS(oC.GetField(iCnt + 3));
		sT = oC.GetField(iCnt + 4);
		if (sT.Find("YES") >= 0)
			bOut = TRUE;
		else if (sT.Find("NO") >= 0)
			bOut = FALSE;
		else
			bOut = FALSE;
		if (iM != 0)
			pS->AddLayer(iPlyID,iM, dThk, dTh, bOut);
		iCnt = iCnt + 8;
	} while (iCnt < oC.iNo);
	if (oC.isVoid(1))
		pS->dZ0 = -pS->GetThk() / 2;
	else
		pS->dZ0 = atofNAS(oC.GetField(1));

	int NextID;
	if (Relab)
		NextID = pM->NextID();
	else
		NextID = pS->iID;
	cPID->Add(pS->iID, NextID);
	pS->iID = NextID;
	pS->iFile = iF;
	pM->AddItem(pS);

}

//***************************************************
// Pre :file pointer and name
// Post :Nastran file read and the mesh returned
//***************************************************
C3dVector DBase::CalcBeamUpVec(E_Object2* EB,int iONID,C3dVector vU)
{
C3dVector vRetUp;
C3dVector vX;
C3dVector vY;
C3dVector vZ;
C3dVector vN1=EB->pVertex[0]->Get_Centroid();
C3dVector vN2=EB->pVertex[1]->Get_Centroid();
ME_Object* pM;
pM=(ME_Object*) EB->pParent;
if (pM!=NULL)
{
  vX=vN2;
  vX-=vN1;
  vX.Normalize();
  if (iONID!=-1)
  {
    Node* pN=pM->GetNode(iONID);
    if (pN!=NULL)
    {
      vY=pM->GetNode(iONID)->GetCoords();
      vY-=vN1;
      vY.Normalize();
      vZ=vX.Cross(vY);
      vRetUp=vY;
      EB->iONID=iONID;
    }
  }
  else
  { 
    C3dMatrix oMat;
    oMat.MakeUnit();
    CoordSys* pSys;
    if (EB->pVertex[0]->OutSys>0)
    {
      pSys=pM->GetSys(EB->pVertex[0]->OutSys);
      if (pSys!=NULL)
      { 
        oMat=pSys->GetTMat();
      }
    }
    vY=oMat*vU;
    vY.Normalize();
    vZ=vX.Cross(vY);
    vZ.Normalize();
    vY=vZ.Cross(vX);
    vRetUp=vY;
    EB->iONID=0;
  }

}
return (vRetUp);
}

void DBase::SetBeamOffs(E_Object2B* EB,C3dVector vOffA,C3dVector vOffB)
{
ME_Object* pM=(ME_Object*) EB->pParent;
C3dMatrix oMat;
CoordSys* pSys;
if (pM!=NULL)
{
  if (EB->pVertex[0]->OutSys>0)
  {
    pSys=pM->GetSys(EB->pVertex[0]->OutSys);
    if (pSys!=NULL)
    { 
      oMat=pSys->GetTMat();
      vOffA=oMat*vOffA;
    }
  }
  if (EB->pVertex[1]->OutSys>0)
  {
    pSys=pM->GetSys(EB->pVertex[1]->OutSys);
    if (pSys!=NULL)
    { 
      oMat=pSys->GetTMat();
      vOffB=oMat*vOffB;
    }
  }
}
EB->OffA=vOffA;
EB->OffB=vOffB;
}

BOOL DBase::isSupportedNAS(CString sKwrd)
{
CString s8;
BOOL brc=FALSE;
s8 = sKwrd.Mid(0,8);

if ((s8 == "GRID    ") || (s8 == "GRID*   ")) 
  brc = TRUE;
else if ((s8 == "CQUAD4  ") || (s8 == "CQUAD4* ")) 
  brc = TRUE;
else if ((s8 == "CTRIA3  ") || (s8 == "CTRIA3* ")) 
  brc = TRUE;
else if ((s8 == "CHEXA   ") || (s8 == "CHEXA*  ")) 
  brc = TRUE;
else if ((s8 == "CPENTA  ") || (s8 == "CPENTA* ")) 
  brc = TRUE;
else if ((s8 == "CTETRA  ") || (s8 == "CTETRA* ")) 
  brc = TRUE;
else if ((s8 == "CBUSH   ") || (s8 == "CBUSH*  ")) 
  brc = TRUE;
else if ((s8 == "CROD    ") || (s8 == "CROD*   ")) 
  brc = TRUE;
else if ((s8 == "CORD2R  ") || (s8 == "CORD2R* ")) 
  brc = TRUE;
else if ((s8 == "CORD2C  ") || (s8 == "CORD2C* ")) 
  brc = TRUE;
else if ((s8 == "CORD2S  ") || (s8 == "CORD2S* ")) 
  brc = TRUE;
else if ((s8 == "CORD1R  ") || (s8 == "CORD1R* ")) 
  brc = TRUE;
else if ((s8 == "CORD1C  ") || (s8 == "CORD1C* ")) 
  brc = TRUE;
else if ((s8 == "CORD1S  ") || (s8 == "CORD1S* ")) 
  brc = TRUE;
else if ((s8 == "PSHELL  ") || (s8 == "PSHELL* ")) 
  brc = TRUE;
else if ((s8 == "PBUSH   ") || (s8 == "PBUSH*  ")) 
  brc = TRUE;
else if ((s8 == "CBEAM   ") || (s8 == "CBEAM*  ")) 
  brc = TRUE;
else if ((s8 == "PCOMP   ") || (s8 == "PCOMP*  ")) 
  brc = TRUE;
else if ((s8 == "PCOMPG  ") || (s8 == "PCOMPG* ")) 
  brc = TRUE;
else if ((s8 == "PSOLID  ") || (s8 == "PSOLID* ")) 
  brc = TRUE;
else if ((s8 == "PROD    ") || (s8 == "PROD*   ")) 
  brc = TRUE;
else if ((s8 == "MAT8    ") || (s8 == "MAT8*   ")) 
  brc = TRUE;
else if ((s8 == "MAT2    ") || (s8 == "MAT2*   ")) 
  brc = TRUE;
else if ((s8 == "MAT1    ") || (s8 == "MAT1*   ")) 
  brc = TRUE;
else if ((s8 == "CELAS1  ") || (s8 == "CELAS1* ")) 
  brc = TRUE;
else if ((s8 == "CELAS2  ") || (s8 == "CELAS2* ")) 
  brc = TRUE;
else if ((s8 == "PELAS   ") || (s8 == "PELAS*  ")) 
  brc = TRUE;
else if ((s8 == "CBAR    ") || (s8 == "CBAR*   ")) 
  brc = TRUE;
else if ((s8 == "PBAR    ") || (s8 == "PBAR*   ")) 
  brc = TRUE;
else if ((s8 == "PBARL   ") || (s8 == "PBARL*  ")) 
  brc = TRUE;
else if ((s8 == "SPCD    ") || (s8 == "SPCD*   ")) 
  brc = TRUE;
else if ((s8 == "RBE2    ") || (s8 == "RBE2*   ")) 
  brc = TRUE;
else if ((s8 == "SPC     ") || (s8 == "SPC*    "))
brc = TRUE;
return (brc);
};

BOOL DBase::isSupportedNASCYS(CString sKwrd)
{
CString s8;
BOOL brc=FALSE;
s8 = sKwrd.Mid(0,8);


if ((s8 == "CORD2R  ") || (s8 == "CORD2R* ")) 
  brc = TRUE;
else if ((s8 == "CORD2C  ") || (s8 == "CORD2C* ")) 
  brc = TRUE;
else if ((s8 == "CORD2S  ") || (s8 == "CORD2S* ")) 
  brc = TRUE;
else if ((s8 == "PSHELL  ") || (s8 == "PSHELL* ")) 
  brc = TRUE;
else if ((s8 == "PCOMP   ") || (s8 == "PCOMP*  ")) 
  brc = TRUE;
else if ((s8 == "PCOMPG  ") || (s8 == "PCOMPG* "))
  brc = TRUE;
else if ((s8 == "PSOLID  ") || (s8 == "PSOLID* ")) 
  brc = TRUE;
else if ((s8 == "PBAR    ") || (s8 == "PBAR*   ")) 
  brc = TRUE;
else if ((s8 == "PBUSH   ") || (s8 == "PBUSH*  "))
  brc = TRUE;
else if ((s8 == "PROD    ") || (s8 == "PROD*   ")) 
  brc = TRUE;
else if ((s8 == "PBEAM   ") || (s8 == "PBEAM*  ")) 
  brc = TRUE;
else if ((s8 == "PBARL   ") || (s8 == "PBARL*  ")) 
  brc = TRUE;
else if ((s8 == "MAT1    ") || (s8 == "MAT1*   ")) 
  brc = TRUE;
else if ((s8 == "MAT8    ") || (s8 == "MAT8*   ")) 
  brc = TRUE;
//else if ((s8 == "CORD1R  ") || (s8 == "CORD1R* ")) 
//  brc = TRUE;
//else if ((s8 == "CORD1C  ") || (s8 == "CORD1C* ")) 
//  brc = TRUE;
//else if ((s8 == "CORD1S  ") || (s8 == "CORD1S* ")) 
//  brc = TRUE;

return (brc);
};

BOOL DBase::isSupportedNASGRID(CString sKwrd)
{
CString s8;
BOOL brc=FALSE;
s8 = sKwrd.Mid(0,8);

if ((s8 == "GRID    ") || (s8 == "GRID*   ")) 
  brc = TRUE;

return (brc);
};

BOOL DBase::isSupportedNASELEM(CString sKwrd)
{
CString s8;
BOOL brc=FALSE;
s8 = sKwrd.Mid(0,8);

if ((s8 == "CQUAD4  ") || (s8 == "CQUAD4* ")) 
  brc = TRUE;
else if ((s8 == "CHEXA   ") || (s8 == "CHEXA*  ")) 
  brc = TRUE;
else if ((s8 == "CONM2   ") || (s8 == "CONM2*  ")) 
  brc = TRUE;
else if ((s8 == "CONM1   ") || (s8 == "CONM1*  "))
brc = TRUE;
else if ((s8 == "CPENTA  ") || (s8 == "CPENTA* ")) 
  brc = TRUE;
else if ((s8 == "RBE2    ") || (s8 == "RBE2*   ")) 
  brc = TRUE;
else if ((s8 == "RBAR    ") || (s8 == "RBAR*   ")) 
  brc = TRUE;
else if ((s8 == "CROD    ") || (s8 == "CROD*   ")) 
  brc = TRUE;
else if ((s8 == "CTETRA  ") || (s8 == "CTETRA* ")) 
  brc = TRUE;
else if ((s8 == "CBUSH   ") || (s8 == "CBUSH*  ")) 
  brc = TRUE;
else if ((s8 == "CTRIA3  ") || (s8 == "CTRIA3* ")) 
  brc = TRUE;
else if ((s8 == "CBAR    ") || (s8 == "CBAR*   ")) 
  brc = TRUE;
else if ((s8 == "CBEAM   ") || (s8 == "CBEAM*  ")) 
  brc = TRUE;
else if ((s8 == "SPC     ") || (s8 == "SPC*    "))
brc = TRUE;
else if ((s8 == "FORCE   ") || (s8 == "FORCE*  "))
brc = TRUE;
else if ((s8 == "MOMENT  ") || (s8 == "MOMENT* "))
brc = TRUE;
else if ((s8 == "PLOAD   ") || (s8 == "PLOAD*  "))
brc = TRUE;
else if ((s8 == "TEMP    ") || (s8 == "TEMP*   "))
brc = TRUE;
else if ((s8 == "TEMPD   ") || (s8 == "TEMPD*  "))
brc = TRUE;
else if ((s8 == "GRAV    ") || (s8 == "GRAV*   "))
brc = TRUE;
return (brc);
};

//chatgpt written
int ExtractIntegerFromCString(const CString& str) {
	// Find the position of the first digit
	int startIndex = str.FindOneOf(_T("0123456789"));

	if (startIndex != -1) 
	{
		// Extract the substring containing the number
		CString numStr = str.Mid(startIndex);
		// Convert CString to integer
		int num = _tstoi(numStr);
		return num;
	}
	else 
	{
		// Return a default value or handle the case as needed
		return -1; // Or any other suitable default value
	}
}

bool hasNoCharactersBeforeKeyword(const CString& str, const CString& keyword) {
	// Find the position of the keyword in the string
	int keywordPos = str.Find(keyword);
	if (keywordPos == -1) 
	{
		// Keyword not found in the string
		return false;
	}

	// Check if there are only spaces or no characters before the keyword
	return std::all_of(str.GetString(), str.GetString() + keywordPos, [](TCHAR c) { return std::isspace(c); });
}

//this is the chatgpt simplified version - old version below
void DBase::ImportNASTRAN_SOL(CString inName, ME_Object* pME) {
	BOOL bSOL101 = FALSE;
	BOOL bSBUB = FALSE;
	BOOL bret = FALSE;
	int iSUBID = -1;
	int iLC = -1;
	int iBC = -1;
	int iTS = -1;
	char s1[200];
	int iCurFileNo = -1;
	FILE* pFile;
	CString datline;
	CString datlineNxt;
	CString sInc;
	CString sLine;
	CString sKeyWrd;
	CString sTit;
	NasCard oCard;
	BOOL bDone = FALSE;
	pFile = fopen(inName, "r");

	if (pFile != NULL) {
		iCurFileNo = GetFileByNo(inName);
		if (iCurFileNo == -1) {
			sFiles[iFileNo] = inName;
			iCurFileNo = iFileNo;
			iFileNo++;
		}

		do {
			if (feof(pFile)) {
				bDone = TRUE;
			}
			else {
				fgets(s1, 200, pFile);
				datlineNxt = s1;
			}

			if (IsInclude(datline)) {
				sInc = GetIncName(datline);
				ImportNASTRAN_SOL(sInc, pME);
			}

			sLine = datline;
			sKeyWrd = "BEGIN BULK";
			if ((sLine.Find(sKeyWrd) > -1) && hasNoCharactersBeforeKeyword(sLine, sKeyWrd)) {
				bDone = TRUE;
				if (bSOL101) {
					sTit.Format(_T("SUBCASE %d"), iSUBID);
					pME->pSOLS->AddStep(sTit, iLC, iBC, iTS, FALSE);
					bret = pME->pSOLS->SetCurStep(iSUBID - 1);
				}
			}

			sKeyWrd = "SOL";
			if ((sLine.Find(sKeyWrd) > -1) && (sLine.Find("101") > -1) && hasNoCharactersBeforeKeyword(sLine, sKeyWrd)) {
				//Linear static solve
				bSOL101 = TRUE;
				pME->pSOLS->AddSolution(0, "SOL 101 STATICS", gDEF_SOL_TOL);
				outtext1("Solution Added and Set as Active.");
			}

			if (bSOL101) {
				if ((sLine.Find("SUBCASE") > -1) && hasNoCharactersBeforeKeyword(sLine, "SUBCASE")) {
					iSUBID = ExtractIntegerFromCString(sLine);
					iLC = iBC = iTS = -1; // Resetting the values
					if (bSBUB) {
						sTit.Format(_T("SUBCASE %d"), iSUBID);
						pME->pSOLS->AddStep(sTit, iLC, iBC, iTS, FALSE);
						bret = pME->pSOLS->SetCurStep(iSUBID - 1);
					}
					bSBUB = !bSBUB;
				}
				else if ((sLine.Find("LOAD") > -1) && hasNoCharactersBeforeKeyword(sLine, "LOAD")) {
					iLC = ExtractIntegerFromCString(sLine);
				}
				else if ((sLine.Find("SPC") > -1) && hasNoCharactersBeforeKeyword(sLine, "SPC")) {
					iBC = ExtractIntegerFromCString(sLine);
				}
				else if ((sLine.Find("TEMP") > -1) && hasNoCharactersBeforeKeyword(sLine, "TEMP")) {
					iTS = ExtractIntegerFromCString(sLine);
				}
			}

			datline = datlineNxt;
		} while (!bDone);

		fclose(pFile);
	}
}


//void DBase::ImportNASTRAN_SOL(CString inName, ME_Object* pME)
//{
//	BOOL bSOL101 = FALSE;
//	BOOL bSBUB = FALSE;
//	BOOL bret = FALSE;
//	int iSUBID = -1;
//	int iSUB = -1;
//	int iLC = -1;;
//	int iBC = -1;;
//	int iTS = -1;
//	char s1[200];
//	int iCurFileNo = -1;
//	FILE* pFile;
//	CString datline;
//	CString datlineNxt;
//	CString sInc;
//	CString sLine;
//	CString sKeyWrd;
//	CString sTit;
//	NasCard oCard;
//	BOOL bDone = FALSE;
//	CoordSys* pRet;
//	pFile = fopen(inName, "r");
//	if (pFile != NULL)
//	{
//		iCurFileNo = GetFileByNo(inName);
//		if (iCurFileNo == -1)
//		{
//			sFiles[iFileNo] = inName;
//			iCurFileNo = iFileNo;
//			iFileNo++;
//		}
//		do
//		{
//			if (feof(pFile))
//			{
//				bDone = TRUE;
//			}
//			else
//			{
//				fgets(s1, 200, pFile);
//				datlineNxt = s1;
//			}
//
//			if (IsInclude(datline) == TRUE)
//			{
//				sInc = GetIncName(datline);
//				ImportNASTRAN_SOL(sInc, pME);
//			}
//			sLine = datline;
//			sKeyWrd = "BEGIN BULK";
//			if ((sLine.Find(sKeyWrd) > -1) && 
//				hasNoCharactersBeforeKeyword(sLine, sKeyWrd))
//			{
//				bDone = TRUE;
//				if (bSOL101)
//				{
//					sTit.Format(_T("SUBCASE %d"), iSUBID);
//					pME->pSOLS->AddStep(sTit, iLC, iBC, iTS, FALSE);
//					bret = pME->pSOLS->SetCurStep(iSUBID-1);
//				}
//			}
//			sKeyWrd = "SOL";
//			if ((sLine.Find(sKeyWrd) > -1) && (sLine.Find("101") > -1) &&
//				hasNoCharactersBeforeKeyword(sLine, sKeyWrd))
//			{
//				//Linear static solve
//				bSOL101 = TRUE;
//				pME->pSOLS->AddSolution(0,"SOL 101 STATICS", gDEF_SOL_TOL);
//				outtext1("Solution Added and Set as Active.");
//			}
//			if (bSOL101)  //look for subcases
//			{
//				if ((sLine.Find("SUBCASE") > -1)  &&
//					hasNoCharactersBeforeKeyword(sLine, "SUBCASE"))
//				{
//					iSUBID = ExtractIntegerFromCString(sLine);
//					int iLC = -1;;
//					int iBC = -1;;
//					int iTS = -1;
//					if (!bSBUB)
//					{
//						bSBUB = TRUE;
//					}
//					else
//					{
//						bSBUB = FALSE;
//						if (bSOL101)
//						{
//							sTit.Format(_T("SUBCASE %d"), iSUBID);
//							pME->pSOLS->AddStep(sTit, iLC, iBC, iTS, FALSE);
//							bret = pME->pSOLS->SetCurStep(iSUBID-1);
//						}
//					}
//				}
//				else if ((sLine.Find("LOAD") > -1) && 
//					      hasNoCharactersBeforeKeyword(sLine, "LOAD"))
//				{
//					iLC = ExtractIntegerFromCString(sLine);
//				}
//				else if ((sLine.Find("SPC") > -1) &&
//					      hasNoCharactersBeforeKeyword(sLine, "SPC"))
//				{
//					iBC = ExtractIntegerFromCString(sLine);
//				}
//				else if ((sLine.Find("TEMP") > -1) &&
//					      hasNoCharactersBeforeKeyword(sLine, "TEMP"))
//				{
//					iTS = ExtractIntegerFromCString(sLine);
//				}
//			}
//
//			datline = datlineNxt;
//		} while (bDone == FALSE);
//		fclose(pFile);
//	}
//
//}

void DBase::ImportNASTRANFirstPass(CString inName, ME_Object* pME,NEList* PIDs,NEList* MATs)
{
char s1[200];
int iCurFileNo = -1;
FILE* pFile;
CString datline;  
CString datlineNxt;
CString sInc;
CString sKwrd;
CString sKeyWrd;
NasCard oCard;
BOOL bDone=FALSE;
CoordSys* pRet;
pFile = fopen(inName,"r");
if (pFile!=NULL)
{
	iCurFileNo = GetFileByNo(inName);
	if (iCurFileNo == -1)
	{
		sFiles[iFileNo] = inName;
		iCurFileNo = iFileNo;
		iFileNo++;
	}
  do
  {
   if (feof(pFile)) 
   {
     bDone = TRUE;
   }
   else
   {
     fgets(s1,200,pFile);
     datlineNxt=s1;
   }

    if (IsInclude(datline)==TRUE)
    {
      sInc = GetIncName(datline);
      ImportNASTRANFirstPass (sInc,pME,PIDs,MATs);
    }
	int iIII = datline.Find(",",0);
	if (datline.Find(",",0)==-1)
	{
	  sKwrd = datline.Left(8);
	}
	else
	{
	  sKwrd = datline.Left(datline.Find(",",0));
	  sKwrd+="          ";
	  sKwrd = sKwrd.Left(8);
	}
    if (isSupportedNASCYS(sKwrd)==TRUE)
    {
      oCard.Clear();
      oCard.Read(pFile,datline,datlineNxt);
      if ((sKwrd.Find("CORD2R") == 0) && (datline.Find(",") == -1))
        {pRet = NASReadCoord(pME,oCard,1,iCurFileNo);}
      else if ((sKwrd.Find("CORD2C") == 0))
        {pRet = NASReadCoord(pME,oCard,2, iCurFileNo);}
      else if ((sKwrd.Find("CORD2S") == 0))
        {pRet = NASReadCoord(pME,oCard,3, iCurFileNo);}
      else if ((sKwrd.Find("PSHELL") == 0))
        {NASReadPSHELL(oCard,PropsT,PIDs,2,FALSE, iCurFileNo);}
	  else if ((sKwrd.Find("PCOMPG") == 0))
	  {NASReadPCOMPG(oCard, PropsT, PIDs, 2, FALSE, iCurFileNo);}
      else if ((sKwrd.Find("PCOMP") == 0))
        {NASReadPCOMP(oCard,PropsT,PIDs,2,FALSE, iCurFileNo);}
      else if ((sKwrd.Find("PSOLID") == 0))
        {NASReadPSOLID(oCard,PropsT,PIDs,2,FALSE, iCurFileNo);}
      else if ((sKwrd.Find("PBARL") == 0))
        {NASReadPBARL(oCard,PropsT,PIDs,2,FALSE, iCurFileNo);}
      else if ((sKwrd.Find("PBAR ") == 0))
        {NASReadPBAR(oCard,PropsT,PIDs,2,FALSE, iCurFileNo);}
      else if ((sKwrd.Find("PROD ") == 0))
        {NASReadPROD(oCard,PropsT,PIDs,2,FALSE, iCurFileNo);}
	  else if ((sKwrd.Find("PBUSH") == 0))
	    {NASReadPBUSH(oCard, PropsT, PIDs, 2, FALSE, iCurFileNo);}
      else if ((sKwrd.Find("PBEAM") == 0))
        {NASReadPBEAM(oCard,PropsT,PIDs,2,FALSE, iCurFileNo);} //NOT DONE
     else if ((sKwrd.Find("MAT1") == 0))
        {NASReadMAT1(oCard,MatT,MATs,2,FALSE, iCurFileNo);}
     else if ((sKwrd.Find("MAT8") == 0))
        {NASReadMAT8(oCard,MatT,MATs,2,FALSE, iCurFileNo);}
    }
    datline = datlineNxt;
  } 
  while (bDone==FALSE);
  fclose(pFile);
} 

}

void DBase::ImportNASTRANGRID(CString inName, ME_Object* pME)
{
int iCurFileNo = -1;
char s1[200];
FILE* pFile;
CString datline;
CString datlineNxt;
CString sInc;
CString sKwrd;
CString sKeyWrd;
NasCard oCard;
BOOL bDone=FALSE;
pFile = fopen(inName,"r");
if (pFile!=NULL)
{
	iCurFileNo = GetFileByNo(inName);
	if (iCurFileNo == -1)
	{
		sFiles[iFileNo] = inName;
		iCurFileNo = iFileNo;
		iFileNo++;
	}
  do
  {
   if (feof(pFile)) 
   {
     bDone = TRUE;
   }
   else
   {
     fgets(s1,200,pFile);
     datlineNxt=s1;
   }

    if (IsInclude(datline)==TRUE)
    {
      sInc = GetIncName(datline);
      ImportNASTRANGRID (sInc,pME);
    }
    if (datline.Find(",",0)==-1)
	{
	  sKwrd = datline.Left(8);
	}
	else
	{
	  sKwrd = datline.Left(datline.Find(",",0));
	  sKwrd+="          ";
	  sKwrd = sKwrd.Left(8);
	}
    if (isSupportedNASGRID(sKwrd)==TRUE)
    {
      oCard.Clear();
      oCard.Read(pFile,datline,datlineNxt);
      if ((sKwrd.Find("GRID") == 0))
          NASReadGRID(pME,oCard,1, iCurFileNo);
    }
    datline = datlineNxt;
  } 
  while (bDone==FALSE);
  fclose(pFile);
} 

}


void DBase::ImportNASTRANELEM(CString inName, ME_Object* pME,NEList* PIDs)
{
int iCurFileNo = -1;
char s1[200];
E_Object* El;
FILE* pFile;
CString datline;
CString datlineNxt;
CString sInc;
CString sKwrd;
CString sKeyWrd;
NasCard oCard;
BOOL bDone=FALSE;
pFile = fopen(inName,"r");
if (pFile!=NULL)
{
	iCurFileNo = GetFileByNo(inName);
	if (iCurFileNo == -1)
	{
		sFiles[iFileNo] = inName;
		iCurFileNo = iFileNo;
		iFileNo++;
	}
  do
  {

   if (feof(pFile)) 
   {
     bDone = TRUE;
   }
   else
   {
     fgets(s1,200,pFile);
     datlineNxt=s1;
   }

    if (IsInclude(datline)==TRUE)
    {
      sInc = GetIncName(datline);
      ImportNASTRANELEM (sInc,pME,PIDs);
    }
    if (datline.Find(",",0)==-1)
	{
	  sKwrd = datline.Left(8);
	}
	else
	{
	  sKwrd = datline.Left(datline.Find(",",0));
	  sKwrd+="          ";
	  sKwrd = sKwrd.Left(8);
	}
    if (isSupportedNASELEM(sKwrd)==TRUE)
    {
      oCard.Clear();
      oCard.Read(pFile,datline,datlineNxt);
      if ((sKwrd.Find("CQUAD4") == 0))
          El = NASReadCQUAD4(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("CONM2") == 0))
          El = NASReadCONM2(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("CONM1") == 0))
		  El = NASReadCONM1(oCard, pME, PIDs, 2, iCurFileNo);
	  else if ((sKwrd.Find("CHEXA") == 0))
          El = NASReadCHEXA(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("CPENTA") == 0))
          El = NASReadCPENTA(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("RBE2") == 0))
          El = NASReadRBE2(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("RBAR") == 0))
          El = NASReadRBAR(oCard,pME,PIDs,2, iCurFileNo);
    else if ((sKwrd.Find("CROD") == 0))
          El = NASReadCROD(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("CTETRA") == 0))
          El = NASReadCTETRA(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("CBUSH ") == 0))
	  { 
		  E_Object2* EB;
		  C3dVector vUP;
		  C3dVector pUp;
		  int iONID;
          EB = NASReadCBUSH(oCard,pME,PIDs,2,iONID,pUp, iCurFileNo);
		  vUP=CalcBeamUpVec(EB,iONID,pUp);
          EB->vUp=vUP;
	  }
	  else if ((sKwrd.Find("CTRIA3") == 0))
          El = NASReadCTRIA3(oCard,pME,PIDs,2, iCurFileNo);
	  else if ((sKwrd.Find("CBAR ") == 0))
	  {
		 E_Object2B* EB;
		 int iONID;
		 C3dVector pUp;
		 C3dVector OffA;
		 C3dVector OffB;
		 C3dVector vUP;
		 EB = NASReadCBAR(oCard,pME,PIDs,2,iONID,pUp,OffA,OffB, iCurFileNo);
		 vUP=CalcBeamUpVec(EB,iONID,pUp);
         SetBeamOffs(EB,OffA,OffB);
         EB->vUp=vUP;
	  }
	  else if ((sKwrd.Find("CBEAM") == 0))
	  {
		 E_Object2B* EB;
		 int iONID;
		 C3dVector pUp;
		 C3dVector OffA;
		 C3dVector OffB;
		 C3dVector vUP;
		 EB = NASReadCBEAM(oCard,pME,PIDs,2,iONID,pUp,OffA,OffB, iCurFileNo);
		 vUP=CalcBeamUpVec(EB,iONID,pUp);
         SetBeamOffs(EB,OffA,OffB);
         EB->vUp=vUP;
	  }  //LOADS AND BOUNDARY CONDITIONS
	  else if ((sKwrd.Find("SPC") == 0))
		 NASReadSPC(oCard, pME, iCurFileNo);
	  else if ((sKwrd.Find("FORCE") == 0))
		  NASReadFORCE(oCard, pME, iCurFileNo);
	  else if ((sKwrd.Find("MOMENT") == 0))
		  NASReadMOMENT(oCard, pME, iCurFileNo);
	  else if ((sKwrd.Find("PLOAD") == 0))
		  NASReadPLOAD(oCard, pME, iCurFileNo);
	  else if ((sKwrd.Find("TEMP ") == 0))
		  NASReadTEMP(oCard, pME, iCurFileNo);
	  else if ((sKwrd.Find("TEMPD") == 0))
		  NASReadTEMPD(oCard, pME, iCurFileNo);
	  else if ((sKwrd.Find("GRAV") == 0))
		  NASReadGRAV(oCard, pME, iCurFileNo);
    }
    datline = datlineNxt;
  } 
  while (bDone==FALSE);
  fclose(pFile);
} 

}


ME_Object* DBase::ImportNASTRAN(CString inName)
{
int i;
iFileNo = 0;
CString sP;
CString sF;
int iRC;
sP=getPath(inName);
sF=getName(inName);
iRC=SetCurrentDirectory (sP);

ME_Object* RetMesh;
RetMesh = new ME_Object();
RetMesh->Create(inName,NULL,iMeshCnt);
iMeshCnt++;

RetMesh->TempList = new ObjTempList();
NEList* newPids = new NEList();
NEList* newMats = new NEList();
//*************************************************************************
ImportNASTRAN_SOL(sF, RetMesh);
ImportNASTRANFirstPass(sF,RetMesh,newPids,newMats);
ImportNASTRANGRID(sF,RetMesh);
ImportNASTRANELEM(sF,RetMesh,newPids);
//*************************************************************************

delete(RetMesh->TempList);
RetMesh->TempList = NULL;
RetMesh->UpdatePropRef(PropsT);
RetMesh->CoordToGlocal();
outtext1("Finished Read.");
RetMesh->iFileNo = iFileNo;
char buff[200];
for (i = 0; i < iFileNo; i++)
{
	RetMesh->sFiles[i] = sFiles[i];
	sprintf_s(buff, "File No %i %s", i, sFiles[i]);
	outtext1(buff);
}

delete (newPids);
delete (newMats);
return (RetMesh);

}

ME_Object* DBase::ImportNASTRAN2(CString inName,BOOL ReLab)
{
CString sP;
CString sF;
int iRC;
sP=getPath(inName);
sF=getName(inName);
iRC=SetCurrentDirectory (sP);

ME_Object* RetMesh;
RetMesh = new ME_Object();
RetMesh->Create(inName,NULL,iMeshCnt);
iMeshCnt++;

RetMesh->TempList = new ObjTempList();
NEList* newPids = new NEList();
NEList* newMats = new NEList();
//*************************************************************************
ImportNASTRAN_SOL(sF, RetMesh);
ImportNASTRANFirstPass(sF,RetMesh,newPids,newMats);
ImportNASTRANGRID(sF,RetMesh);
ImportNASTRANELEM(sF,RetMesh,newPids);
//*************************************************************************

delete(RetMesh->TempList);
RetMesh->TempList = NULL;
RetMesh->UpdatePropRef(PropsT);
outtext1("Finished Read.");
delete (newPids);
delete (newMats);
return (RetMesh);

}

ME_Object* DBase::ImportNAS(FILE* pFile,CString inName,BOOL ReLab)
{
int iCurFileNo = -1;
char s1[200];
CString sKeyWrd;
CString sKeyWrdNext;
int iStop = 0;
ME_Object* RetMesh;
RetMesh = new ME_Object();
RetMesh->Create(inName,NULL,iMeshCnt);
iMeshCnt++;
//Read GRIDS
RetMesh->TempList = new ObjTempList();
NEList* newPids = new NEList();
NEList* newMats = new NEList();
do
{
  //Read the coordinate systems first as other depend on it
  sKeyWrd=sKeyWrdNext;
  fgets(s1,200,pFile);
	sKeyWrdNext=s1;
  if (sKeyWrd!="")
  {
	  if ((sKeyWrd.Find("CORD2R") == 0) && (sKeyWrd.Find(",") == -1))
    {
      // CoordSys* pRet = NASReadCoord(RetMesh,pFile,&sKeyWrd,&sKeyWrdNext,1);
       //outtext1("REC SYS FOUND");
    }
    else if ((sKeyWrd.Find("CORD2C") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //CoordSys* pRet = NASReadCoord(RetMesh,pFile,&sKeyWrd,&sKeyWrdNext,2);
      //outtext1("CYL SYS FOUND");
    }
    else if ((sKeyWrd.Find("CORD2S") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //CoordSys* pRet = NASReadCoord(RetMesh,pFile,&sKeyWrd,&sKeyWrdNext,3);
      //outtext1("SPH SYS FOUND");
    }
    else if ((sKeyWrd.Find("PSHELL ") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //NASReadPSHELL(PropsT,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2,ReLab);
    }
    else if ((sKeyWrd.Find("PCOMP ") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //NASReadPCOMP(PropsT,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
    else if ((sKeyWrd.Find("PSOLID") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //NASReadPSOLID(PropsT,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2,ReLab);
    }
    else if ((sKeyWrd.Find("PBAR ") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //NASReadPBAR(PropsT,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2,ReLab);
    }
    else if ((sKeyWrd.Find("PBEAM ") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //NASReadPBEAM(PropsT,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2,ReLab);
    }
    else if ((sKeyWrd.Find("PBARL") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //NASReadPBARL(PropsT,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2,ReLab);
    }
     else if ((sKeyWrd.Find("MAT1") == 0) && (sKeyWrd.Find(",") == -1))
    {
     // NASReadMAT1(MatT,newMats,pFile,&sKeyWrd,&sKeyWrdNext,2,ReLab);
    }
    else if ((sKeyWrd.Find("MAT8") == 0) && (sKeyWrd.Find(",") == -1))
    {
     // NASReadMAT8(MatT,newMats,pFile,&sKeyWrd,&sKeyWrdNext,2,ReLab);
    }
  }
  if (feof(pFile))
  {
    iStop = 1;
  }
}
while (iStop == 0);
if (ReLab)
{
  PropsT->UpdateMats(newMats);
}
iStop = 0;
rewind(pFile);
do
{
  sKeyWrd=sKeyWrdNext;
  fgets(s1,200,pFile);
	sKeyWrdNext=s1;
  if (sKeyWrd!="")
  {
	if ((sKeyWrd.Find("GRID ") == 0) && (sKeyWrd.Find(",") == -1))
    {
     // NASReadGRID(RetMesh,pFile,&sKeyWrd,&sKeyWrdNext,1);
    }
    else if (sKeyWrd.Find("GRID*") == 0)
	{
      NASReadGRIDD(RetMesh,pFile,&sKeyWrd,&sKeyWrdNext,1, iCurFileNo);
	}
  }
  if (feof(pFile))
  {
    iStop = 1;
  }
}
while (iStop == 0);
rewind(pFile);
iStop = 0;
E_Object* El;
int iStop2=0;
do
{
  sKeyWrd=sKeyWrdNext;
  fgets(s1,200,pFile);
	sKeyWrdNext=s1;
  if (sKeyWrd!="")
  {
    if ((sKeyWrd.Find("CONM2") == 0) && (sKeyWrd.Find(",") == -1))
    {
     // El = NASReadCONM2(RetMesh,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
	if ((sKeyWrd.Find("CONM1") == 0) && (sKeyWrd.Find(",") == -1))
	{
		// El = NASReadCONM2(RetMesh,pFile,&sKeyWrd,&sKeyWrdNext,2);
	}
	if ((sKeyWrd.Find("CHEXA") == 0) && (sKeyWrd.Find(",") == -1))
    {
    //  El = NASReadCHEXA(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
    else if ((sKeyWrd.Find("CPENTA") == 0) && (sKeyWrd.Find(",") == -1))
    {
   //   El = NASReadCPENTA(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
    else if ((sKeyWrd.Find("RBE2") == 0) && (sKeyWrd.Find(",") == -1))
    {
     // El = NASReadRBE2(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
    else if ((sKeyWrd.Find("RBAR") == 0) && (sKeyWrd.Find(",") == -1))
    {
      //El = NASReadRBAR(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
    else if ((sKeyWrd.Find("CTETRA") == 0) && (sKeyWrd.Find(",") == -1))
    {
    //  El = NASReadCTETRA(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
	  else if ((sKeyWrd.Find("CQUAD4 ") == 0) && (sKeyWrd.Find(",") == -1))
    {
  //    El = NASReadCQUAD4(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
	  else if ((sKeyWrd.Find("CBUSH ") == 0) && (sKeyWrd.Find(",") == -1))
    {
     // El = NASReadCBUSH(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
    else if ((sKeyWrd.Find("CQUAD4* ") == 0) && (sKeyWrd.Find(",") == -1))
    {
      El = NASReadCQUAD4D(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2, iCurFileNo);
    }
	  else if ((sKeyWrd.Find("CTRIA3") == 0) && (sKeyWrd.Find(",") == -1))
    {
     // El = NASReadCTRIA3(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,2);
    }
    else if ((sKeyWrd.Find("CBAR ") == 0) && (sKeyWrd.Find(",") == -1))
    {
      /*C3dVector vU;
      C3dVector vUP;
      C3dVector vOffA;
      C3dVector vOffB;
      CString sD1="";
      CString sD2="";
      vOffA*=0;
      vOffB*=0;
      int iONID=0;
      E_Object2B* EB;
      EB = (E_Object2B*) NASReadCBAR(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,&iONID,&vU,&vOffA,&vOffB,&sD1,&sD2);
      if (sD1!="")
      {
        EB->SetDOFStringA(sD1);
      }
      if (sD2!="")
      {
        EB->SetDOFStringB(sD2);
      }
      vUP=CalcBeamUpVec(EB,iONID,vU);
      SetBeamOffs(EB,vOffA,vOffB);
      EB->vUp=vUP;*/
    }
    else if ((sKeyWrd.Find("CBEAM") == 0) && (sKeyWrd.Find(",") == -1))
    {
     /*       C3dVector vU;
      C3dVector vUP;
      C3dVector vOffA;
      C3dVector vOffB;
      CString sD1="";
      CString sD2="";
      vOffA*=0;
      vOffB*=0;
      int iONID=0;
      E_Object2B* EB;
      EB = (E_Object2B*) NASReadCBEAM(RetMesh,newPids,pFile,&sKeyWrd,&sKeyWrdNext,&iONID,&vU,&vOffA,&vOffB,&sD1,&sD2);
      if (sD1!="")
      {
        EB->SetDOFStringA(sD1);
      }
      if (sD2!="")
      {
        EB->SetDOFStringB(sD2);
      }
      vUP=CalcBeamUpVec(EB,iONID,vU);
      SetBeamOffs(EB,vOffA,vOffB);
      EB->vUp=vUP;*/
    }

    else
    {
    }
  }
  if (feof(pFile))
  {
    iStop = 1;
  }
}
while (iStop == 0);
delete(RetMesh->TempList);
RetMesh->TempList = NULL;
RetMesh->UpdatePropRef(PropsT);
outtext1("Finished Read.");
delete (newPids);
delete (newMats);
return (RetMesh);
}



//************************************************
//                   GROUPS
//************************************************

void DBase::DelAll_Group()
{
int i;
if (iNoGPs>0)
{
  for (i=0;i<iNoGPs;i++)
  {
    if (Groups[i]!=NULL)
    {
       delete(Groups[i]);
    }
  }
}
iNoGPs=0;
iCurGp=-1;
}

void DBase::Del_Group(int iThisGp)
{
int i;
char buff[80];

if ((iThisGp>-1) && (iThisGp<iNoGPs))
{
  sprintf_s(buff, "%s%s","Deleting Group : ",Groups[iThisGp]->Title);
  delete(Groups[iThisGp]);
  outtext1(buff);
  for (i=iThisGp;i<iNoGPs-1;i++)
  {
    Groups[i]=Groups[i+1];
  }
  iNoGPs--;
  if ((iThisGp>-1) && (iThisGp<iNoGPs))
  {iCurGp=iThisGp;}
  else
  {iCurGp=-1;}
}
}

int DBase::AddGp(CString inTit)
{
if (iNoGPs < MAX_GPS)
{
  Groups[iNoGPs] = new ObjGp(inTit);
  iCurGp = iNoGPs;
  iNoGPs++;
}
else
{
  outtext1("ERROR: Max Number of Groups Reached.");
}
return(iCurGp);
}


void DBase::NextGp()
{

outtext1("Next Group.");
if ((iCurGp<iNoGPs-1) && (iNoGPs>=0))
{
  iCurGp++;
  Dsp_Group();
}
}

void DBase::PrevGp()
{

outtext1("Previous Group.");
if (iCurGp>0) 
{
  iCurGp--;
  Dsp_Group();
}
}

void DBase::GPAddGP(int iGP)
{
int i;
if ((iGP<iNoGPs) && (iGP>=0))
{
  if(iGP!=iCurGp)
  {
    for (i=0;i<Groups[iGP]->iNo;i++)
	{
       Groups[iCurGp]->Add(Groups[iGP]->Objs[i]);
	}
  }
}
Dsp_Group();
}

void DBase::GPRemGP(int iGP)
{
int i=0;
if ((iGP<iNoGPs) && (iGP>=0))
{
  if(iGP!=iCurGp)
  {
  do
	{
       Groups[iCurGp]->Rem(Groups[iGP]->Objs[i]);
	   i++;
	}
	while (i<Groups[iGP]->iNo);
  }
}
Dsp_Group();
}



void DBase::SetCurrentGP(int iGP)
{
char buff[80];
if ((iGP<iNoGPs) && (iGP>=0))
{
  iCurGp=iGP;
  sprintf_s(buff, "%3i%s%s",iCurGp," : ",Groups[iCurGp]->Title );
  outtext1(buff);
}
}

void DBase::InsertCat(C3dVector p1)
{
ME_Object* pCatPart=NULL;
if (MeshCat!=NULL)
{
   pCatPart=MeshCat->GetCur();
   if (pCatPart !=NULL)
   {
     pCatPart->Translate(p1);
     AddObj(pCatPart);
     InvalidateOGL();
     ReDraw();
   }
}
}

void DBase::ListGp()
{
int i;
char buff[80];
CString iGp;
CString oLine;
outtext1("GROUP LISTING:-");

for (i=0;i<iNoGPs;i++)
{ 
	sprintf_s(buff, "%3i%s%s",i," : ",Groups[i]->Title );
    //oLine=buff;
    outtext1(buff);
}
if ((iNoGPs > 0) && (iCurGp<iNoGPs))
{
  outtext1("Active Group :");
  sprintf_s(buff, "%3i%s%s",iCurGp," : ",Groups[iCurGp]->Title );
  outtext1(buff);
}
else
{
  outtext1("ERROR: No Active Group.");
}
}


void DBase::ListResSets()
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->ListResSets();
}
else
{
  outtext1("ERROR: No Mesh Active.");
}
}

void DBase::ListVecSets()
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->ListVecSets();
	}
	else
	{
		outtext1("ERROR: No Mesh Active.");
	}
}

void DBase::DelResSets()
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->DeleteAllResults();
}
else
{
  outtext1("ERROR: No Mesh Active.");
}
}

void DBase::ListResSet()
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->ListResSet();
}
else
{
  outtext1("ERROR: No Mesh Active.");
}
}
void DBase::ResSetScale(CString sSeq, double dS)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->ResSetScale(sSeq, dS);
	}
	else
	{
		outtext1("ERROR: No Mesh Active.");
	}
}

void DBase::ResSetDivInTo(CString sSeq, double dS)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->ResSetDivInTo(sSeq, dS);
	}
	else
	{
		outtext1("ERROR: No Mesh Active.");
	}
}

void DBase::ResSetEnvMax(CString sSeq[],int iNo)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->ResEnvMax(sSeq, iNo);
	}
	else
	{
		outtext1("ERROR: No Mesh Active.");
	}
}

void DBase::ResSetEnvMin(CString sSeq[], int iNo)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->ResEnvMin(sSeq, iNo);
	}
	else
	{
		outtext1("ERROR: No Mesh Active.");
	}
}

void DBase::SetCurrentResSet(int iRS,int iRV,int iOPT)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->SetCurrentResSet(iRS,iRV,iOPT);
  InvalidateOGL();
  ReDraw();
}
else
{
  outtext1("ERROR: No Mesh Active.");
}

}

void DBase::DeleteResVec()
{
	int i;
	if (pCurrentMesh != NULL)
	{
		i = 0;
		S_Count = 0;  //Deselect all
		do //Remove from the display list
		{
			if (Dsp_List[i]->iObjType==330)
			{
				//Dsp_RemGP(Dsp_List[i]);
				Dsp_List[i] = Dsp_List[iDspLstCount - 1];
				iDspLstCount--;
				i--;
			}
			i++;
		} while (i != iDspLstCount);
		pCurrentMesh->DeleteResVectors(); //Delete the vectors
		InvalidateOGL();
		ReDraw();
	}
}

void DBase::SetCurrentResVec(int iRS, int iRV,int iD)
{
	if (pCurrentMesh != NULL)
	{

		pCurrentMesh->GenResVectors(iRS, iRV, iD);
		InvalidateOGL();
		ReDraw();
	}
	else	
	{ 
		outtext1("ERROR: No Mesh Active.");
	}
}

void DBase::RevColourBar()
{
if (bRevColBar==FALSE)
  bRevColBar=TRUE;
else
  bRevColBar=FALSE;
InvalidateOGL();
CreateTexture(bRevColBar);
ReDraw();
}

void DBase::SetColourBar(double dMin,double dMax)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->SetColourBar((float) dMax,(float) dMin);
  pCurrentMesh->bUserColBar=TRUE;
  InvalidateOGL();
  ReDraw();
}
else
{
  outtext1("ERROR: No Mesh Active.");
}

}


void DBase::SetDefScale(double dS)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->dScale=dS;
  InvalidateOGL();
  ReDraw();
}
else
{
  outtext1("ERROR: No Mesh Active.");
}
}

void DBase::SetVecScale(double dS)
{
	if (pCurrentMesh != NULL)
	{
		pCurrentMesh->dScaleVec = dS;
		InvalidateOGL();
		ReDraw();
	}
	else
	{
		outtext1("ERROR: No Mesh Active.");
	}
}


void DBase::SetCurrentResSetDef(int iRS,int iRV)
{
if (pCurrentMesh!=NULL)
{
  pCurrentMesh->SetCurrentResSetDef(iRS,iRV);
}
else
{
  outtext1("ERROR: No Mesh Active.");
}
}

void DBase::Dsp_Group()
{
int iCO;
bDispAll=FALSE;
char buff[80];
if (iCurGp!=-1)
{
  sprintf_s(buff, "%3i%s%s",iCurGp," : ",Groups[iCurGp]->Title );
  outtext1(buff);
}
else
{
  outtext1("No Groups Exist!");
}
if ((iNoGPs>0) && (iCurGp<iNoGPs)) 
{
  iDspLstCount = 0;
  Dsp_Add(DB_Obj[0]);
  for (iCO=0;iCO<Groups[iCurGp]->iNo;iCO++)
  {
    Dsp_Add(Groups[iCurGp]->Objs[iCO]);
  }
  InvalidateOGL();
  ReDraw();
}
}


void DBase::AddToGroup()
{

int iCO;
if (iCurGp!=-1)
{
  for (iCO=0;iCO<S_Count;iCO++)
  {
	if (S_Buff[iCO]->iObjType!=330)  //do not add results vectors as volitie
      Groups[iCurGp]->Add(S_Buff[iCO]);
  }
  ReDraw();
}
}

void DBase::SelbyTYPE(int PID)
{

int iCO;
for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
{
  if ((pCurrentMesh->pElems[iCO]->iType==PID)) // && (IsOnScr(pCurrentMesh->pElems[iCO]))
  {
    if ((bDispAll==FALSE) && (IsOnScr(pCurrentMesh->pElems[iCO])))
    {
	  S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
      S_Count++;
    }
    else if (bDispAll==TRUE)
    {
      S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
      S_Count++;
    }
  }
}
ReDraw();
}

void DBase::SelbyCOL(int PID)
{

int iCO;
for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
{
  if ((pCurrentMesh->pElems[iCO]->iColour==PID))// && (IsOnScr(pCurrentMesh->pElems[iCO])))
  {
    if ((bDispAll==FALSE) && (IsOnScr(pCurrentMesh->pElems[iCO])))
    {
	    S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
      S_Count++;
    }
    else if (bDispAll==TRUE)
    {
      S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
      S_Count++;
    }
  }
}
ReDraw();
}

//set relative displacement offset
void DBase::SetResDispOff(Node* pN)
{

	if (pCurrentMesh != NULL)
	{
	  if (pN != NULL)
	  {
		if (pN->pResD != NULL)
		{

				pCurrentMesh->vRelDispOff = pN->pResD->GetVec();
				outtext1("Relative Results Offset is ON");

			}
		}
	  else
	  {
		  pCurrentMesh->vRelDispOff.Set(0, 0, 0);
		  outtext1("Relative Results Offset is OFF");
	  }
	  InvalidateOGL();
	  ReDraw();
	}
	//vRelDispOff.vset
}


void DBase::SelNodesbyCOL(int PID)
{

int iCO;
for (iCO=0;iCO<pCurrentMesh->iNdNo;iCO++)
{
  if ((pCurrentMesh->pNodes[iCO]->iColour==PID))// && (IsOnScr(pCurrentMesh->pNodes[iCO])))
  {
    if ((bDispAll==FALSE) && (IsOnScr(pCurrentMesh->pNodes[iCO])))
    {
	  S_Buff[S_Count] = pCurrentMesh->pNodes[iCO];
      S_Count++;
    }
    else if (bDispAll==TRUE)
    {
      S_Buff[S_Count] = pCurrentMesh->pNodes[iCO];
      S_Count++;
    }
  }
}
ReDraw();
}

void DBase::SelSurfsbyCOL(int iCOl)
{

int iCO;
for (iCO = 0; iCO < iDspLstCount; iCO++)
{
  if (Dsp_List[iCO]->iObjType==15)
  {
    if (Dsp_List[iCO]->iColour==iCOl)
    {
      S_Buff[S_Count] = Dsp_List[iCO];
      S_Count++;
    }
  }
}
ReDraw();
}

void DBase::SelPtsbyCOL(int iCOl)
{

int iCO;
S_Count=0;
for (iCO = 0; iCO < iDspLstCount; iCO++)
{
  if (Dsp_List[iCO]->iObjType==0)
  {
    if (Dsp_List[iCO]->iColour==iCOl)
    {
      S_Buff[S_Count] = Dsp_List[iCO];
      S_Count++;
    }
  }
}
ReDraw();
}

void DBase::SelCursbyCOL(int iCOl)
{

int iCO;
for (iCO = 0; iCO < iDspLstCount; iCO++)
{
  if (Dsp_List[iCO]->iObjType==7)
  {
    if (Dsp_List[iCO]->iColour==iCOl)
    {
      S_Buff[S_Count] = Dsp_List[iCO];
      S_Count++;
    }
  }
}
ReDraw();
}

void DBase::SelCursbyLAY(int iLAY)
{

	int iCO;
	for (iCO = 0; iCO < iDspLstCount; iCO++)
	{
		if ((Dsp_List[iCO]->iObjType == 0) || (Dsp_List[iCO]->iObjType == 6) || (Dsp_List[iCO]->iObjType == 7) || (Dsp_List[iCO]->iObjType == 10))
		{
			if (Dsp_List[iCO]->iFile == iLAY)
			{
				S_Buff[S_Count] = Dsp_List[iCO];
				S_Count++;
			}
		}
	}
	ReDraw();
}

void DBase::EditMat(int MID,BOOL bPID)
{
  Property* P = NULL;
  Material* M = NULL;
  int iMID=-1;
  if (bPID)
  {
    P = PropsT->GetItem(MID);
    if (P!=NULL)
    {
      iMID=P->GetMat();
    }
  }
  else
  {
    iMID=MID;
  }
  M = MatT->GetItem(iMID);
  if (M!=NULL)
  {
    CEntEditDialog Dlg;
    Dlg.pEnt = M;
    Dlg.DoModal();
	if (Dlg.bDel == TRUE)
		MatT->Delete(M);
  }
  else
  {

  }
}

void DBase::EditProp(int PID)
{
  Property* P = NULL;
  P = PropsT->GetItem(PID);
  if (P != NULL)
  {
    CEntEditDialog* Dlg = NULL;
	Dlg = new CEntEditDialog();
	if (Dlg != NULL)
	{
		Dlg->pEnt = P;
		Dlg->DoModal();
		if (Dlg->bDel == TRUE)
			PropsT->Delete(P);
		delete (Dlg);
		Dlg = NULL;
		InvalidateOGL();
		ReGen();
	}
  }
  else
  {

  }
}

void DBase::ViewLam(int iP)
{
	Property* P = NULL;
	P = PropsT->GetItem(iP);
	if (P != NULL)
	{
		if (P->iType == 2)
		{
			CPcompEditor* Dlg = new CPcompEditor();
			Dlg->pEnt = P;
			Dlg->DoModal();
			delete (Dlg);
			InvalidateOGL();
			ReGen();
		}
	}
	else
	{

	}
}


void DBase::EditObject()
{
	G_Object* pO;
	pO = S_Buff[S_Count - 1];
	if (pO != NULL)
	{
		CEntEditDialog Dlg;
		//PropTable* PropsT
		Dlg.PT = PropsT;
		Dlg.pO = pO;
		Dlg.DoModal();
		S_Count--;
		InvalidateOGL();
		ReGen();

	}
	else
	{

	}

}


void DBase::EditGlobals()
{
	//need to create a dummy G_Object with all
	//global values in
	G_ObjectDUM* pO = new G_ObjectDUM();

	if (pO != NULL)
	{
		CEntEditDialog Dlg;
		//PropTable* PropsT
		Dlg.PT = PropsT;
		Dlg.pO = pO;
		Dlg.DoModal();
		S_Count--;
		InvalidateOGL();
		ReGen();
		delete (pO);

	}
	else
	{

	}

}




void DBase::ListMat(int MID, BOOL bPID)
{
  Property* P = NULL;
  Material* M = NULL;
  int iMID = -1;
  if (bPID)
  {
    P = PropsT->GetItem(MID);
    if (P != NULL)
    {
      iMID = P->GetMat();
    }
  }
  else
  {
    iMID = MID;
  }
  M = MatT->GetItem(iMID);
  if (M != NULL)
    M->Info();
}

void DBase::ListProp(int PID)
{
Property* P = PropsT->GetItem(PID);
if (P!=NULL)
{
  P->List();
}
}

void DBase::lMeasure(C3dVector v1,C3dVector v2)
{
  C3dVector v1a,v2a,v,vg;
  v1a=v1;
  v2a=v2;
  v=v2a-v1a;

  v1a=v1;
  v2a=v2;
  v1a=GlobaltoWP(v1a);
  v2a=GlobaltoWP(v2a);
  vg=v2a-v1a;
  char S1[200];
  CString OutT;
  WP_Object* pWPlane = (WP_Object*) DB_Obj[iWP];
  outtext1("LINEAR DISTANCE (GLOBAL)"); 
  sprintf_s(S1,"GL: X,%f,Y,%f,Z,%f",v.x,v.y,v.z);
  OutT=S1;
  outtext1(OutT); 
  if (pWPlane->iWPMode == 1)
  {
    
    sprintf_s(S1,"WP: R,%f,T,%f,Z,%f",vg.x,vg.y,vg.z);
  }
  else
  {
    sprintf_s(S1,"WP: X,%f,Y,%f,Z,%f",vg.x,vg.y,vg.z);
  }
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"MAG: %f",vg.Mag());
  OutT=S1;
  outtext1(OutT); 

}

void DBase::AMeasure(C3dVector v1, C3dVector v2, C3dVector v3)
{
  C3dVector v1a, v2a;
  double dDot;
  double dAng;

  v1a = v1-v2;
  v2a = v3-v2;
  v1a.Normalize();
  v2a.Normalize();
  dDot = v1a.Dot(v2a);
  dAng = acos(dDot) * 180/Pi;
  char S1[200];
  CString OutT;
  outtext1("ANGLE BETWEEN VECTORS:-");
  sprintf_s(S1, "ANG: %f,", dAng);
  OutT = S1;
  outtext1(OutT);
}


void DBase::SelbyPID(int PID)
{

int iCO;
for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
{
  if ((pCurrentMesh->pElems[iCO]->PID==PID))// )
  {
    if ((bDispAll==FALSE) && (IsOnScr(pCurrentMesh->pElems[iCO])))
    {
	    S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
      S_Count++;
    }
    else if (bDispAll==TRUE)
    {
      S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
      S_Count++;
    }
  }
}
ReDraw();
}

void DBase::SelbyMID(int inMID)
{

int iCO;
Property* pP;
for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
{
  pP=PropsT->GetItem(pCurrentMesh->pElems[iCO]->PID);
  if (pP!=NULL)
  {
    if (pP->HasMat(inMID))
    {
      if ((bDispAll==FALSE) && (IsOnScr(pCurrentMesh->pElems[iCO])))
      {
	      S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
        S_Count++;
      }
      else if (bDispAll==TRUE)
      {
        S_Buff[S_Count] = pCurrentMesh->pElems[iCO];
        S_Count++;
      }
    }
  }
}
ReDraw();
}


BOOL DBase::IsOnScr(G_Object* pThis)
{
int j;
BOOL bRet=FALSE;
for (j=0;j<iDspLstCount;j++)
{
  if (Dsp_List[j]==pThis)
  {
    bRet=TRUE;
    break;
  }
}
return (bRet);
}

void DBase::RelatedTo(int iType)
{
ObjList* pObj=new ObjList();
pObj->Clear();
int i,j;
for (j=0;j<S_Count;j++)
{
  if ((S_Buff[j]->iObjType == 8) && (iType == 1))
  {
	S_Buff[j]->RelTo(S_Buff[j], pObj, iType);
  }
  else if ((S_Buff[j]->iObjType == 9) && (iType == 1))
  {
	S_Buff[j]->RelTo(S_Buff[j], pObj, iType);
  }
  else if (S_Buff[j]->pParent!=NULL)
  {
    S_Buff[j]->pParent->RelTo(S_Buff[j],pObj,iType);       //all 
  }
  else
  {
	S_Buff[j]->RelTo(S_Buff[j], pObj, iType);
  }
}
S_Count=0;
for (i=0;i<pObj->iNo;i++)
{
	S_Buff[S_Count] = pObj->Objs[i];
    S_Count++;
}
delete(pObj);
ReDraw();
}

void DBase::CreateCoordLine()
{
ObjList* pObj=new ObjList();
ObjList* pEls=new ObjList();
E_Object* pE;
C3dVector vO;
C3dVector p1;
C3dVector p2;
C3dVector vXa;
C3dVector vX;
C3dVector vY;
C3dVector vZ;
C3dMatrix rMat;

pObj->Clear();
int i,j;
p1=S_Buff[0]->Get_Centroid();
p2=S_Buff[S_Count-1]->Get_Centroid();
vXa=p2-p1;
vXa.Normalize();

for (j=0;j<S_Count;j++)
{
  if (S_Buff[j]->iObjType==1)
  {
    pEls->Clear();
    vO=S_Buff[j]->Get_Centroid();
    S_Buff[j]->pParent->RelTo(S_Buff[j],pEls,3);    
    for (i=0;i<pEls->iNo;i++)
    {
      pE=(E_Object*) pEls->Objs[i]; 
      if ((pE->iType==94) && (IsOnScr(pE)))
      {
        vZ=pE->Get_Normal();  
		    //vZ=-vZ;
        vZ.Normalize();
        vY = vZ.Cross(vXa);
        vX = vY.Cross(vZ);
        rMat.MakeUnit();
        rMat.m_00 = vX.x;
        rMat.m_10 = vX.y;
        rMat.m_20 = vX.z;
        rMat.m_01 = vY.x;
        rMat.m_11 = vY.y;
        rMat.m_21 = vY.z;
        rMat.m_02 = vZ.x;
        rMat.m_12 = vZ.y;
        rMat.m_22 = vZ.z;
        CoordSys* pRet = pCurrentMesh->AddSys(vO,rMat,-1,1,S_Buff[j]->iLabel,55);
        Node* pN = (Node*) S_Buff[j];
        pN->OutSys = pRet->iLabel;
        pObj->Add(pRet);
        S_Buff[j]->iColour=124;
        break;
      }
    }
  }
}
S_Count=0;
for (i=0;i<pObj->iNo;i++)
{
	  S_Buff[S_Count] = pObj->Objs[i];
    Dsp_Add(pObj->Objs[i]); 
    AddTempGraphics(pObj->Objs[i]);
    S_Count++;
}
delete(pObj);
delete(pEls);
ReDraw();
}

void DBase::NoOfElementOnANode(int iNo)
{
ObjList* pObj=new ObjList();
ObjList* pEls=new ObjList();
E_Object* pE;
C3dVector vO;
int iCnt;
pObj->Clear();
int i,j;


for (j=0;j<S_Count;j++)
{
  if (S_Buff[j]->iObjType==1)
  {
    pEls->Clear();
    iCnt=0;
    S_Buff[j]->pParent->RelTo(S_Buff[j],pEls,3);    
    for (i=0;i<pEls->iNo;i++)
    {
      pE=(E_Object*) pEls->Objs[i]; 
      if ((pE->iType==94) || (pE->iType==92))
      {
        iCnt++;
      }
    }
    if (iCnt>=iNo)
    {
       pObj->AddEx(S_Buff[j]);
    }
  }
}
S_Count=0;
for (i=0;i<pObj->iNo;i++)
{
  S_Buff[S_Count] = pObj->Objs[i];
  S_Count++;
}
delete(pObj);
delete(pEls);
ReDraw();
}

void DBase::AddToGroupbyPID(int PID)
{
  NEList* PIDS= new NEList();
  CString sTit;
  CString sNum;
  int iPID;
  int iCO;
  int iGP;
  for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
  {
    iPID=pCurrentMesh->pElems[iCO]->PID;
    //if (iPID!=-1)
    //{
      iGP=PIDS->Get(iPID);  //See if group has beeen created
      if (iGP==-1)
      {//PID Group does exist
	      sNum.Format(_T("%d"), iPID);
        sTit="PROP "; 
	      sTit+=sNum;
  	    iGP=AddGp(sTit);
   	    PIDS->Add(iPID,iGP);
      }
      Groups[iGP]->Add(pCurrentMesh->pElems[iCO]);
   //}
 }
  delete (PIDS);
}

void DBase::ColourByPID(int PID)
{
	NEList* PIDS = new NEList();
	CString sTit;
	CString sNum;
	int iCurCol = 2;
	int iPID;
	int iCO;
	int iCol;
	for (iCO = 0; iCO < pCurrentMesh->iElNo; iCO++)
	{
		iPID = pCurrentMesh->pElems[iCO]->PID;
		iCol = PIDS->Get(iPID);  
		if (iCol == -1)
		{
			PIDS->Add(iPID, iCurCol);
			iCol = iCurCol;
			iCurCol++;
			if (iCurCol > 122)
				iCurCol = 2;
		}
		pCurrentMesh->pElems[iCO]->iColour = iCol;
	}
	delete (PIDS);
	InvalidateOGL();
	ReDraw();
}

void DBase::ColourByINC(int PID)
{
	NEList* PIDS = new NEList();
	CString sTit;
	CString sNum;
	int iCurCol = 2;
	int iINC;
	int iCO;
	int iCol;
	for (iCO = 0; iCO < pCurrentMesh->iElNo; iCO++)
	{
		iINC = pCurrentMesh->pElems[iCO]->iFile;
		iCol = PIDS->Get(iINC);
		if (iCol == -1)
		{
			PIDS->Add(iINC, iCurCol);
			iCol = iCurCol;
			iCurCol++;
			if (iCurCol > 122)
				iCurCol = 2;
		}
		pCurrentMesh->pElems[iCO]->iColour = iCol;
	}
	delete (PIDS);
	InvalidateOGL();
	ReDraw();
}


void DBase::ChkNegJac()
{
  CString sTit;
  CString sNum;
  int iGP;
  int i;
  int iBad = 0;
  //Add a groups for the negative elements
  sTit = "NEG ELEMENTS ";
  iGP = AddGp(sTit);

  for (i = 0; i<pCurrentMesh->iElNo; i++)
  {
    if (pCurrentMesh->pElems[i]->ChkNegJac() == TRUE)
    {
      Groups[iGP]->Add(pCurrentMesh->pElems[i]);
      iBad++;
    }
  }
  outtext1("A New Checking Group has been Created.");
  sNum.Format(_T("%d"), iBad);
  sNum += " : Found.";
  outtext1(sNum);
}

void DBase::AddToGroupbyMID(int PID)
{
int iMID;
int i;
CString sTit;
CString sNum;
int iGP;
int iCO;
Property* pP;
int iPID;

if (pCurrentMesh!=NULL)
{
	for (i=0;i<MatT->iNo;i++)
	{
	  iMID=MatT->pEnts[i]->iID;
	  sNum.Format(_T("%d"), iMID);
	  sTit="MAT "; 
	  sTit+=sNum;
	  iGP=AddGp(sTit);
	  for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
	  {
		iPID=pCurrentMesh->pElems[iCO]->PID;
		pP=PropsT->GetItem(iPID);
		if (pP!=NULL)
		{
		  if (pP->HasMat(iMID))
		  {
			Groups[iGP]->Add(pCurrentMesh->pElems[iCO]);
		  }
		}
	  }
	}
}
else
{
}
}

void DBase::GPByInclude(int iFile)
{

	CString sTit;
	CString sNum;
	int iCO;
	int iGP;

	sNum.Format(_T("%d"), iFile);
	sTit = "INCLUDE ";
	sTit += sNum;
	iGP = AddGp(sTit);
	pCurrentMesh->IncludeToGroup(iFile,Groups[iGP]);

}


void DBase::AddToGroupbyCol(int PID)
{

NEList* PIDS= new NEList();
CString sTit;
CString sNum;

int iPID;
int iCO;
int iGP;
for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
{
  iPID=pCurrentMesh->pElems[iCO]->iColour;
  if (iPID!=-1)
  {
    iGP=PIDS->Get(iPID);  //See if group has beeen created
    if (iGP==-1)
    {//PID Group does exist
	  sNum.Format(_T("%d"), iPID);
      sTit="COLOUR "; 
	  sTit+=sNum;
  	  iGP=AddGp(sTit);
   	  PIDS->Add(iPID,iGP);
    }
    Groups[iGP]->Add(pCurrentMesh->pElems[iCO]);
  }
}
delete (PIDS);
}

void DBase::AddToGroupbyNDCol(int PID)
{

NEList* PIDS= new NEList();
CString sTit;
CString sNum;

int iPID;
int iCO;
int iGP;
for (iCO=0;iCO<pCurrentMesh->iNdNo;iCO++)
{
  iPID=pCurrentMesh->pNodes[iCO]->iColour;
  if (iPID!=-1)
  {
    iGP=PIDS->Get(iPID);  //See if group has beeen created
    if (iGP==-1)
    {//PID Group does exist
	  sNum.Format(_T("%d"), iPID);
      sTit="NDCOLOUR "; 
	  sTit+=sNum;
  	  iGP=AddGp(sTit);
   	  PIDS->Add(iPID,iGP);
    }
    Groups[iGP]->Add(pCurrentMesh->pNodes[iCO]);
  }
}
delete (PIDS);
}

void DBase::AddToGroupbyNDOSYS(int PID)
{

NEList* PIDS= new NEList();
CString sTit;
CString sNum;

int iPID;
int iCO;
int iGP;
for (iCO=0;iCO<pCurrentMesh->iNdNo;iCO++)
{
  iPID=pCurrentMesh->pNodes[iCO]->OutSys;
  if (iPID!=-1)
  {
    iGP=PIDS->Get(iPID);  //See if group has beeen created
    if (iGP==-1)
    {//PID Group does exist
	  sNum.Format(_T("%d"), iPID);
      sTit="NDOSYS "; 
	  sTit+=sNum;
  	  iGP=AddGp(sTit);
   	  PIDS->Add(iPID,iGP);
    }
    Groups[iGP]->Add(pCurrentMesh->pNodes[iCO]);
  }
}
delete (PIDS);
}

void DBase::AddToGroupbyNDDSYS(int PID)
{

NEList* PIDS= new NEList();
CString sTit;
CString sNum;

int iPID;
int iCO;
int iGP;
for (iCO=0;iCO<pCurrentMesh->iNdNo;iCO++)
{
  iPID=pCurrentMesh->pNodes[iCO]->DefSys;
  if (iPID!=-1)
  {
    iGP=PIDS->Get(iPID);  //See if group has beeen created
    if (iGP==-1)
    {//PID Group does exist
	  sNum.Format(_T("%d"), iPID);
      sTit="NDDSYS "; 
	  sTit+=sNum;
  	  iGP=AddGp(sTit);
   	  PIDS->Add(iPID,iGP);
    }
    Groups[iGP]->Add(pCurrentMesh->pNodes[iCO]);
  }
}
delete (PIDS);
}

void DBase::AddToGroupbyType(int PID)
{

NEList* PIDS= new NEList();
CString sTit;
CString sNum;

int iPID;
int iCO;
int iGP;
for (iCO=0;iCO<pCurrentMesh->iElNo;iCO++)
{
  iPID=pCurrentMesh->pElems[iCO]->iType;
  if (iPID!=-1)
  {
    iGP=PIDS->Get(iPID);  //See if group has beeen created
    if (iGP==-1)
    {//PID Group does exist
	  sNum.Format(_T("%d"), iPID);
      sTit="TYPE "; 
	  sTit+=sNum;
  	  iGP=AddGp(sTit);
   	  PIDS->Add(iPID,iGP);
    }
    Groups[iGP]->Add(pCurrentMesh->pElems[iCO]);
  }
}
delete (PIDS);
}

void DBase::RemFromGroup()
{

int iCO;
if (iCurGp!=-1)
{
  for (iCO=0;iCO<S_Count;iCO++)
  {
    Groups[iCurGp]->Rem(S_Buff[iCO]);
  }
}
//Dsp_Group();
}

void DBase::Colour(int iCol)
{

int iCO;
if ((iCol>=0) && (iCol<=167))
{
  for (iCO=0;iCO<S_Count;iCO++)
  {
	  S_Buff[iCO]->Colour(iCol);
  }
InvalidateOGL();
ReDraw();
}
}

void DBase::ModIncludeNo(int iF)
{
	int iNoC = 0;
	char s1[200];
	int iCO;
    for (iCO = 0; iCO < S_Count; iCO++)
	{
		if ((S_Buff[iCO]->iObjType == 0) || (S_Buff[iCO]->iObjType == 7))
		{
			//IGNORE AS ARE USED FOR DXF LAY NO
		}
		else
		{
			S_Buff[iCO]->iFile = iF;
			iNoC++;
		}
	}
	sprintf_s(s1, "%s%i", "Number of Entities Modified : ", iNoC);
	outtext1(_T(s1));

}

void DBase::ModLayerNo(int iF)
{
	int iNoC = 0;
	char s1[200];
	int iCO = 0;
	for (iCO = 0; iCO < S_Count; iCO++)
	{
		if ((S_Buff[iCO]->iObjType == 0) || (S_Buff[iCO]->iObjType == 7) || (S_Buff[iCO]->iObjType == 6) || (S_Buff[iCO]->iObjType == 10))
		{
			S_Buff[iCO]->ModLayNo(iF); //iFile is used as layer for point and curves
			iNoC++;
		}
	}
	sprintf_s(s1, "%s%i", "Number of Entities Modified : ", iNoC);
	outtext1(_T(s1));

}

void DBase::CountItems()
{
	char S1[200];
	int iNode = 0;
	int iEl = 0;
	int iCYS = 0;
	int iNodeMin = 99999999;
	int iElMin = 99999999;
	int iCYSMin = 99999999;
	int iNodeMax = 0;
	int iElMax = 0;
	int iCYSMax = 0;

	int iCO;
	for (iCO = 0; iCO < S_Count; iCO++)
	{
		if (S_Buff[iCO]->iObjType == 1)
		{
			iNode++;
			if (S_Buff[iCO]->iLabel < iNodeMin)
				iNodeMin = S_Buff[iCO]->iLabel;
			if (S_Buff[iCO]->iLabel > iNodeMax)
				iNodeMax = S_Buff[iCO]->iLabel;
		}
		else if (S_Buff[iCO]->iObjType == 3)
		{
			iEl++;
			if (S_Buff[iCO]->iLabel < iElMin)
				iElMin = S_Buff[iCO]->iLabel;
			if (S_Buff[iCO]->iLabel > iElMax)
				iElMax = S_Buff[iCO]->iLabel;
		}
		else if (S_Buff[iCO]->iObjType == 12)
		{
			iCYS++;
			if (S_Buff[iCO]->iLabel < iCYSMin)
				iCYSMin = S_Buff[iCO]->iLabel;
			if (S_Buff[iCO]->iLabel > iCYSMax)
				iCYSMax = S_Buff[iCO]->iLabel;
		}

	}
	if (iNodeMin == 99999999)
		iNodeMin = 0;
	if (iElMin == 99999999)
		iElMin = 0;
	if (iCYSMin == 99999999)
		iCYSMin = 0;

	outtext1("Count of Selected F.E. Items:-");
	sprintf_s(S1, "%s%i", "Number of Nodes : ", iNode);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Number of Elements : ", iEl);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Number of Coord-Systems : ", iCYS);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Min Node Label : ", iNodeMin);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Min Elem Label : ", iElMin);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Min CSYS Label : ", iCYSMin);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Max Node Label : ", iNodeMax);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Max Elem Label : ", iElMax);
	outtext1(S1);
	sprintf_s(S1, "%s%i", "Max CSYS Label : ", iCYSMax);
	outtext1(S1);
	ReDraw();

}



void DBase::LabEnt()
{

int iCO;
for (iCO=0;iCO<S_Count;iCO++)
{
   if (S_Buff[iCO]->bDrawLab==FALSE)
     {S_Buff[iCO]->bDrawLab=TRUE;}
   else
     {S_Buff[iCO]->bDrawLab=FALSE;}
}
InvalidateOGL();
ReDraw();
}

void DBase::ElementReverse()
{
int iCO;

CString OutT;
BOOL bReGen=FALSE;
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 3)
  {
    E_Object* pE = (E_Object*) S_Buff[iCO];
    pE->Reverse();
	bReGen=TRUE;
  }
}
if (bReGen==TRUE)
{
  InvalidateOGL();
  ReDraw();
}
}


void DBase::TetCircumSphere()
{
	char s1[200];
	int iCO;
	CString OutT;
	BOOL bReGen = FALSE;
	C3dVector v0, v1, v2, v3;
	C3dVector vC;
	double dR;
	for (iCO = 0; iCO < S_Count; iCO++)
	{
		if (S_Buff[iCO]->iObjType == 3)
		{
			E_Object* pE = (E_Object*)S_Buff[iCO];
			if (pE->iType == 111) //Its a TET
			{
				E_Object34* pEtet = (E_Object34*) pE;
				//asas
				v0 = pEtet->GetNodalCoords(0);
				v1 = pEtet->GetNodalCoords(1);
				v2 = pEtet->GetNodalCoords(2);
				v3 = pEtet->GetNodalCoords(3);
				Circumsphere(&v0, &v1, &v2, &v3,&vC,&dR);
				sprintf_s(s1, "%s%g", "Circum Radius : ", dR);
				outtext1(_T(s1));
				sprintf_s(s1, "%s X: %g Y: %g Z: %g", "Circum Centre : ", vC.x,vC.y,vC.z);
				outtext1(_T(s1));
			}
		}
	}
}

void DBase::ElemntMoPID(int iPID)
{
int iCO;
char s1[200];
CString OutT;
BOOL bReGen=FALSE;
BOOL bC=FALSE;
int iNoC=0;
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 3)
  {
    E_Object* pE = (E_Object*) S_Buff[iCO];
    ME_Object* pM=(ME_Object*) pE->pParent;
    Property* pr=PropsT->GetItem(iPID);
    if (pr!=NULL)
    {
      bC=pE->SetProperty(pr);
      bReGen=TRUE;
      if (bC)
        iNoC++;
    }
  }
}
sprintf_s(s1,"%s%i","Number of Elements Modified : ",iNoC);
outtext1(_T(s1));
if (bReGen==TRUE)
{
  InvalidateOGL();
  ReDraw();
}
}

void DBase::SelRBENode(ObjList* Items)
{
	int iNoC=0;
	char s1[200];
	CString OutT;
	BOOL bReGen = FALSE;
	BOOL bC = FALSE;
	int i = 0;
	for (i = 0; i < Items->iNo; i++)
	{
		if (Items->Objs[i]->iObjType == 3)
		{
			E_Object* pE = (E_Object*)Items->Objs[i];
			if (pE->iType == 122)
			{
				E_ObjectR* pR = (E_ObjectR*)pE;
				if (pR->pVertex[0] != NULL)
				{
					S_BuffAdd(pR->pVertex[0]);
					iNoC++;
				}
			}
		}
	}
	sprintf_s(s1, "%s%i", "Number of RBE Nodes Found : ", iNoC);
	outtext1(_T(s1));
	Items->Clear();
	ReDraw();
}

void DBase::SpringMoCSys(int iSys)
{
int iCO;
char s1[200];
CoordSys* pSYS=NULL;
int iCnt=0;
  if (pCurrentMesh!=NULL)
  {
    pSYS=pCurrentMesh->GetSys(iSys);
  }
  if ((pSYS!=NULL) || (iSys==-1))
  {
    for (iCO=0;iCO<S_Count;iCO++)
    {
      if (S_Buff[iCO]->iObjType == 3)
      {
        E_Object* pE= (E_Object*) S_Buff[iCO];
        if (pSYS!=NULL)
        {
          if (pSYS->pParent==pE->pParent)
          {
            if ((pE->iType==136) || (pE->iType==137) || (pE->iType == 138))
            {
              E_Object2* pE2=(E_Object2*) pE;
              pE2->iCSYS=iSys;
              iCnt++;
            }
          }
        }
        else if (iSys==-1)
        {
          if ((pE->iType==136) || (pE->iType==137))
          {
            E_Object2* pE2=(E_Object2*) pE;
            pE2->iCSYS=-1;
            iCnt++;
          }
        }
      }
    }
    sprintf_s(s1,"%s%i","Number of Elements Modified : ",iCnt);
    outtext1(_T(s1));
  }
  else
  {
    outtext1("ERROR: Coordinate System Does Not Exist.");
  }
}

void DBase::ShellMoCSys(int iSys)
{
  int iCO;
  char s1[200];
  CoordSys* pSYS = NULL;
  int iCnt = 0;
  if (pCurrentMesh != NULL)
  {
    pSYS = pCurrentMesh->GetSys(iSys);
  }
  if ((pSYS != NULL) || (iSys == -1))
  {
    for (iCO = 0; iCO<S_Count; iCO++)
    {
      if (S_Buff[iCO]->iObjType == 3)
      {
        E_Object* pE = (E_Object*)S_Buff[iCO];
        if (pSYS != NULL)
        {
          if (pSYS->pParent == pE->pParent)
          {
            if (pE->iType == 91) 
            {
              E_Object3* pE3 = (E_Object3*) pE;
              pE3->iMCys = iSys;
			  pE3->MAng = 0.0;
              iCnt++;
            }
            else if (pE->iType == 94)
            {
              E_Object4* pE4 = (E_Object4*)pE;
              pE4->iMCys = iSys;
			  pE4->MAng = 0.0;
              iCnt++;
            }
          }
        }
        else if (iSys == -1)
        {
          if (pE->iType == 91)
          {
            E_Object3* pE3 = (E_Object3*)pE;
            pE3->iMCys = -1;
            iCnt++;
          }
          else if (pE->iType == 94)
          {
            E_Object4* pE4 = (E_Object4*)pE;
            pE4->iMCys = -1;
            iCnt++;
          }
        }
      }
    }
    sprintf_s(s1, "%s%i", "Number of Elements Modified : ", iCnt);
    outtext1(_T(s1));
  }
  else
  {
    outtext1("ERROR: Coordinate System Does Not Exist.");
  }
}

void DBase::NodeMoOSys(int iSys)
{
int iCO=0;
int iNoC=0;
char s1[200];
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 1)
  {
    Node* pN = (Node*) S_Buff[iCO];  
    pN->OutSys=iSys;
	iNoC++;
  }
}
sprintf_s(s1, "%s%i", "Number of Nodes Modified : ", iNoC);
outtext1(_T(s1));
}

void DBase::ElementMoLab(int iN)
{
int iCO;
int iNewLab;
char S1[200];
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 3)
  {
    E_Object* pN = (E_Object*) S_Buff[iCO];  
    iNewLab=pN->iLabel+iN;
    if (pCurrentMesh==pN->pParent)
    {
      //Check to see if the node exists;
      E_Object* pNC=pCurrentMesh->GetElement(iNewLab);
      if (pNC==NULL)
      {
        pN->iLabel=iNewLab;
      }
      else
      { 
        CString OutT;
        sprintf_s(S1,"%s%i","Element Label Not Modified For EL: ",pN->iLabel);
        OutT=S1;
        outtext1(OutT);
      }
    }
  }
}
pCurrentMesh->MaxLab();
InvalidateOGL();
ReDraw();
}

void DBase::ElementMoLab2(int iN)
{
int iCO;
int iNewLab;
char S1[200];
iNewLab=iN;
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 3)
  {
    E_Object* pN = (E_Object*) S_Buff[iCO];  
    if (pCurrentMesh==pN->pParent)
    {
      //Check to see if the node exists;
      E_Object* pNC=pCurrentMesh->GetElement(iNewLab);
      if (pNC==NULL)
      {
        pN->iLabel=iNewLab;
        iNewLab++;
      }
      else
      { 
        CString OutT;
        sprintf_s(S1,"%s%i","Element Label Not Modified For EL: ",pN->iLabel);
        OutT=S1;
        outtext1(OutT);
      }
    }
  }
}
pCurrentMesh->MaxLab();
InvalidateOGL();
ReDraw();
}
void DBase::NodeMoLab(int iN)
{
int iCO;
int iNewLab;
char S1[200];
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 1)
  {
    Node* pN = (Node*) S_Buff[iCO];  
    iNewLab=pN->iLabel+iN;
    if (pCurrentMesh==pN->pParent)
    {
      //Check to see if the node exists;
      Node* pNC=pCurrentMesh->GetNode(iNewLab);
      if (pNC==NULL)
      {
        pN->iLabel=iNewLab;
      }
      else
      { 
        CString OutT;
        sprintf_s(S1,"%s%i","Node Label Not Modified For ND: ",pN->iLabel);
        OutT=S1;
        outtext1(OutT);
      }
    }
  }
}
pCurrentMesh->MaxLab();
InvalidateOGL();
ReDraw();
}

void DBase::NodeMoLab2(int iN)
{
int iCO;
int iNewLab;
char S1[200];
iNewLab=iN;
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 1)
  {
    Node* pN = (Node*) S_Buff[iCO];  
    if (pCurrentMesh==pN->pParent)
    {
      //Check to see if the node exists;
      Node* pNC=pCurrentMesh->GetNode(iNewLab);
      if (pNC==NULL)
      {
        pN->iLabel=iNewLab;
        iNewLab++;
      }
      else
      { 
        CString OutT;
        sprintf_s(S1,"%s%i","Node Label Not Modified For ND: ",pN->iLabel);
        OutT=S1;
        outtext1(OutT);
      }
    }
  }
}
pCurrentMesh->MaxLab();
InvalidateOGL();
ReDraw();
}

void DBase::NodeMoRSys(int iSys)
{
int iCO=0;
int iNoC=0;
char s1[200];
for (iCO=0;iCO<S_Count;iCO++)
{
  if (S_Buff[iCO]->iObjType == 1)
  {
    Node* pN = (Node*) S_Buff[iCO];  
    pN->DefSys=iSys;
	iNoC++;
  }
}
sprintf_s(s1, "%s%i", "Number of Nodes Modified : ", iNoC);
outtext1(_T(s1));
}
void DBase::Dsp_RemGP(G_Object* gIn)
{
int i;
int j;

for (j=0;j<iNoGPs;j++)
{
  i = 0;
  do
  {
    if (Groups[j]->Objs[i]==gIn)
    {
      Groups[j]->Objs[i]=Groups[j]->Objs[Groups[j]->iNo-1];
      Groups[j]->iNo--;
      break;
    }
    else
    {
	    i++;
    }
  }
  while (i < Groups[j]->iNo);
}
}

void DBase::ReCalcScreenMat()
{
double dSize = dWidth;
if (dWidth > dHeight)
  {
  dSize = dHeight;
  } 
double dScScale = dSize / WPSize;
double invScale;
pScrMat.MakeUnit();
pScrMat.m_11 = -1;
pScrMat.Scale(dScScale);
pScrMat.Translate(dWidth/2,dHeight/2,0);
pScrInvMat.MakeUnit();
if (dScScale > 0){ 
  invScale = 1/dScScale;}
else {
invScale = 1;}
pScrInvMat.Scale(invScale); 
pScrInvMat.Translate(dWidth/2,dHeight/2,0);
}


void DBase::SetScreenMat(CRect rRect)
{

//pTheView->GetClientRect(mCView_Rect);
dWidth = mCView_Rect.right-mCView_Rect.left;
dHeight = mCView_Rect.bottom-mCView_Rect.top;

double dSize = dWidth;
if (dWidth > dHeight)
  {
  dSize = dHeight;
  } 
double dScScale = dSize / WPSize;
double invScale;
pScrMat.MakeUnit();
pScrMat.m_11 = -1;
pScrMat.Scale(dScScale);
pScrMat.Translate(dWidth/2,dHeight/2,0);
pScrInvMat.MakeUnit();
if (dScScale > 0){ 
  invScale = 1/dScScale;}
else {
invScale = 1;}
pScrInvMat.Scale(invScale); 
pScrInvMat.Translate(dWidth/2,dHeight/2,0);
dPixelSize=dSize;
}	


void DBase::CreatePrBar(CString sT,int iPID,int iMID,double dW,double dH)
{
PBARL* pBar = new PBARL();
pBar->sSecType = "BAR";
pBar->sTitle=sT;
pBar->iMID=iMID;
pBar->iID=iPID;
pBar->iNoDims=2;
pBar->dDIMs[0]=dW;
pBar->dDIMs[1]=dH;
pBar->CreateSec();
PropsT->AddItem(pBar);
outtext1("New BAR Section Created.");
}

void DBase::CreatePrShell(CString sT,int iPID,int iMID,double dT,double dNSM)
{
PSHELL* pShell = new PSHELL();
pShell->sTitle=sT;
pShell->iMID1=iMID;
pShell->iMID2=iMID;
pShell->iMID3=iMID;
pShell->iID=iPID;
pShell->dT=dT;
pShell->dNSM=dNSM;

PropsT->AddItem(pShell);
outtext1("New Shell Property Created.");
}

//iP ith to extract
CString ExtractSubString(int iP,CString sIn)
{
	sIn.Replace(",", " ");
	int i;
	int iS = 0;
	int iLen = sIn.GetLength();
	CString sOut;
	int iOCnt = 0;
	int iCBlock = 0;
	BOOL bF = FALSE;
	for (i = 0; i < iLen ; i++)
	{
		if (sIn[i] != ' ')
		{
			if (bF == FALSE)
			{
				bF = TRUE;
				iCBlock++;
			}
			
			if (iCBlock == iP)
			{
				sOut += sIn[i];
				iOCnt++;
			}
		}
		else
		{
			bF = FALSE;
		}
	}
	return(sOut);
}

void DBase::CreatePrPCOMP(CString sT, int iPID, double dNSM,int iNoLay, CString sLay[])
{
	int i;
	int iMID;
	double dThk;
	double dTheta;
	CString s;
	PCOMP* pC = new PCOMP();
	pC->sTitle = sT;
	pC->iID = iPID;
	pC->dNSM = dNSM;
	for (i = 0; i < iNoLay; i++)
	{
		iMID = atoi(ExtractSubString(1, sLay[i]));
		dThk = atof(ExtractSubString(2, sLay[i]));
		dTheta = atof(ExtractSubString(3, sLay[i]));
		pC->AddLayer(iMID, dThk, dTheta, 0);
	}
	PropsT->AddItem(pC);
	outtext1("New PCOMP Property Created.");
}

void DBase::CreatePrSpringT(CString sT,int iPID,double dkx,double dky,double dkz,double dkt)
{
PSPRINGT* pST = new PSPRINGT();
pST->sTitle=sT;
pST->iID=iPID;
pST->dkx=dkx;
pST->dky=dky;
pST->dkz=dkz;
pST->dkcoeff=dkt;
PropsT->AddItem(pST);
outtext1("New Translational Spring Property Created.");
}

void DBase::CreatePrBUSH(CString sT, int iPID, double dk1, double dk2, double dk3, double dk4, double dk5, double dk6)
{
	PBUSH* pST = new PBUSH();
	pST->sTitle = sT;
	pST->iID = iPID;
	pST->dK1 = dk1;
	pST->dK2 = dk2;
	pST->dK3 = dk3;
	pST->dK4 = dk4;
	pST->dK5 = dk5;
	pST->dK6 = dk6;
	PropsT->AddItem(pST);
	outtext1("New Nastran PBUSH Property Created.");
}

void DBase::CreatePrLumpedMass(CString sT, int iPID, double dM)
{
  PMASS* pST = new PMASS();
  pST->sTitle = sT;
  pST->iID = iPID;
  pST->dM = dM;
  PropsT->AddItem(pST);
  outtext1("New Lumped Mass Property Created.");
}

void DBase::CreatePrSpringR(CString sT,int iPID,double dkx,double dky,double dkz,double dkt)
{
PSPRINGR* pST = new PSPRINGR();
pST->sTitle=sT;
pST->iID=iPID;
pST->dkx=dkx;
pST->dky=dky;
pST->dkz=dkz;
pST->dkcoeff=dkt;
PropsT->AddItem(pST);
outtext1("New Rotational Spring Property Created.");
}



void DBase::CreatePrSolid(CString sT,int iPID,int iMID)
{
PSOLID* pSolid = new PSOLID();
pSolid->sTitle=sT;
pSolid->iMID=iMID;
pSolid->iCORDM=0;
pSolid->iID=iPID;

PropsT->AddItem(pSolid);
outtext1("New Solid Property Created.");
}

void DBase::ChkShellAspect(ObjList* Elems, double dT, BOOL bList)
{
  CString sTit;
  CString sNum;
  char S1[200];
  E_Object* pE;
  int iGP;
  int i;
  int iBad = 0;
  //Add a groups for the failing elements
  sTit = "SHELL ASPECT ";
  iGP = AddGp(sTit);
  if (bList)
    outtext1("Elements Failing Criteria:-");
  for (i = 0; i<Elems->iNo; i++)
  {
    if (Elems->Objs[i]->iObjType == 3)  // its an element
    {
      pE = (E_Object*)Elems->Objs[i];
      if ((pE->iType == 91) || (pE->iType == 94))
      {
        double dA;
        dA = pE->QualAspect();
        if (dA>dT)
        {
          if (bList)
          {
            sprintf_s(S1, "ELEMENT: %8i VAL: %f", pE->iLabel, dA);
            outtext1(S1);
          }
          Groups[iGP]->Add(pE);
          iBad++;
        }
      }
    }
  }
  outtext1("A New Checking Group has been Created.");
  sNum.Format(_T("%d"), iBad);
  sNum += " : Found Failing.";
  outtext1(sNum);
}


void DBase::ChkTetCollapse(ObjList* Elems, double dT, BOOL bList)
{
  CString sTit;
  CString sNum;
  char S1[200];
  E_Object* pE;
  E_Object34* pTET;
  int iGP;
  int i;
  int iBad = 0;
  //Add a groups for the failing elements
  sTit = "TET COLLAPSE ";
  iGP = AddGp(sTit);
  if (bList)
    outtext1("Elements Failing Criteria:-");
  for (i = 0; i<Elems->iNo; i++)
  {
    if (Elems->Objs[i]->iObjType == 3)  // its an element
    {
      pE = (E_Object*)Elems->Objs[i];
      if (pE->iType == 111) 
      {
        pTET = (E_Object34*) pE;
        double dA;
        dA = pTET->TetCollapse();
        if (dA<dT)
        {
          if (bList)
          {
            sprintf_s(S1, "ELEMENT: %8i VAL: %f", pE->iLabel, dA);
            outtext1(S1);
          }
          Groups[iGP]->Add(pE);
          iBad++;
        }
      }
    }
  }
  outtext1("A New Checking Group has been Created.");
  sNum.Format(_T("%d"), iBad);
  sNum += " : Found Failing.";
  outtext1(sNum);
}

void DBase::GetClosestNodes(ObjList* pSource,C3dVector pTrg, ObjList* pRes, double dTol)
{
	int i;
	double dDist;
	C3dVector pN;
	pRes->Clear();
	for (i = 0; i < pSource->iNo; i++)
	{
		pN = pSource->Objs[i]->Get_Centroid();
		dDist = pN.Dist(pTrg);
		if (dDist < dTol)
			pRes->Add(pSource->Objs[i]);
	}
}

void DBase::CNodesMerge2(ObjList* Nodes,double dTol,BOOL UpLab,BOOL bDel)
{
char S1[200];
int i;
CString OutT;
ObjList* CNodes = new ObjList();
ObjList* ChkNodes = new ObjList();
sprintf_s(S1,"%s%f","Merging Coincident Nodes, Tol:",dTol);

//Check all node for checking are in current mesh
if (pCurrentMesh!=NULL)
{
  for (i=0;i<Nodes->iNo;i++)
  {
     if ((Nodes->Objs[i]->iObjType==1) && (Nodes->Objs[i]->pParent==pCurrentMesh))
     {
         ChkNodes->Add(Nodes->Objs[i]);     
     }
  }
}
else
{
    outtext1("ERROR: Unable to Merge - No Current Mesh.");
}
Node* pKeep=NULL;
if (ChkNodes->iNo>0)
{
  outtext1("Coincident Node List:-");
  do
  {
    Node* pN = (Node*) ChkNodes->Objs[0];
    GetClosestNodes(ChkNodes,pN->GetCoords(),CNodes,dTol);
    ChkNodes->RemoveGP(CNodes);
    if (CNodes->iNo>1)
    {
      CNodes->ListIDs();
      if (bDel)         //Thean merge else just list
      {
        if (UpLab)
          pKeep=(Node*) CNodes->GetMaxLabItem();
        else
          pKeep=(Node*) CNodes->GetMinLabItem();
        if (pKeep!=NULL)
        {
          for (i=0;i<CNodes->iNo;i++)
          {
            pCurrentMesh->RepNodeInEl((Node*) CNodes->Objs[i],pKeep);
          }
        }
      }
    }
  }
  while  (ChkNodes->iNo>0);
}
delete (CNodes);
delete (ChkNodes);
InvalidateOGL();
ReDraw();
}

void DBase::EqLab(ObjList* Nodes, double dTol, BOOL UpLab, BOOL bDel)
{
	char S1[200];
	int i;
	CString OutT;
	ObjList* CNodes = new ObjList();
	ObjList* ChkNodes = new ObjList();
	sprintf_s(S1, "%s%f", "Relabeling Coincident Nodes Across Meshes, Tol:", dTol);



	for (i = 0; i < Nodes->iNo; i++)
	{
		if (Nodes->Objs[i]->iObjType == 1) 
		{
			ChkNodes->Add(Nodes->Objs[i]);
		}
	}

	Node* pKeep = NULL;
	if (ChkNodes->iNo > 0)
	{
		outtext1("Coincident Node List:-");
		do
		{
			Node* pN = (Node*)ChkNodes->Objs[0];
			GetClosestNodes(ChkNodes, pN->GetCoords(), CNodes, dTol);
			ChkNodes->RemoveGP(CNodes);
			int iLabN;
			if (CNodes->iNo > 1)
			{
				CNodes->ListIDs();
                for (i = 0; i < CNodes->iNo; i++)
				{
					if (CNodes->Objs[i]->pParent != pCurrentMesh)
					{
						iLabN = CNodes->Objs[i]->iLabel;
						break;
					}
				}
				Node* pRetPt;
				for (i = 0; i < CNodes->iNo; i++)
				{
					if (CNodes->Objs[i]->pParent == pCurrentMesh)
					{
						pRetPt=pCurrentMesh->GetNode(iLabN);
						if (pRetPt != NULL)
						{
							sprintf_s(S1, "%s %i %s %i", "WARNING: Node", iLabN, "Exists Renaming to", pCurrentMesh->iNodeLab);
							pRetPt->iLabel = pCurrentMesh->iNodeLab;
							pCurrentMesh->iNodeLab++;
							outtext1(S1);
						}
						CNodes->Objs[i]->iLabel = iLabN;
						CNodes->Objs[i]->iColour = 124;
						break;
					}
				}
			}
		}   while (ChkNodes->iNo > 0);
	}
	delete (CNodes);
	delete (ChkNodes);
	InvalidateOGL();
	ReDraw();
}

UINT MyThreadProc( LPVOID pParam )
{
    DBase* pObject = (DBase*) pParam;
    if (pObject == NULL ||
        !pObject->IsKindOf(RUNTIME_CLASS(DBase)))
    return 1;   // if pObject is not valid
    
    // do something with 'pObject'
    pObject->SolveCFD();
    return 0;   // thread completed successfully
}


void DBase::SolveIncompFluids()
{
AfxBeginThread(MyThreadProc, this);

//SolveCFD();
}

UINT MyThreadProc1( LPVOID pParam )
{

    DBase* pObject = (DBase*) pParam;
    if (pObject == NULL ||
        !pObject->IsKindOf(RUNTIME_CLASS(DBase)))
    return 1;   // if pObject is not valid
    
    // do something with 'pObject'
    pObject->Solve();
    return 0;   // thread completed successfully
}


void DBase::SolveStress()
{
AfxBeginThread(MyThreadProc1, this);

//SolveCFD();
}


UINT CycleThread(LPVOID pParam)
{

	DBase* pObject = (DBase*)pParam;
	if (pObject == NULL ||
		!pObject->IsKindOf(RUNTIME_CLASS(DBase)))
		return 1;   // if pObject is not valid

		// do something with 'pObject'
	pObject->Cycle();

	
	return 0;   // thread completed successfully
}

void DBase::CycleFrames()
{
	AfxBeginThread(CycleThread, this);
}

void DBase::CNodesMerge(double dTol)
{
char S1[200];
CString OutT;
sprintf_s(S1,"%s%f","Merging coincident nodes, Tol:",dTol);
if (pCurrentMesh!=NULL)
{
   outtext1(S1);
   pCurrentMesh->CNodesMerge(dTol);
}
else
{
  outtext1("ERROR: Unable to Merge - No Current Mesh.");
}

}


void DBase::ModifyPrMat(int iPID,int iMID1,int iMID2)
{
Property* pR=PropsT->GetItem(iPID);
if (pR!=NULL)
{
   pR->ChangeMat(iMID1,iMID2);
   outtext1 ("Changing property material");
}
else
{
   outtext1 ("Property does not exist");
}
}


void DBase::CreateMat1(CString sT,int iMID,double dE,double dV,double dDen,double dAlpha,double dkt)
{
MAT1* pMat = new MAT1();
pMat->sTitle=sT;
pMat->iID=iMID;
pMat->iType=1;
pMat->dE=dE;
pMat->dNU=dV;
pMat->dRHO=dDen;
pMat->dA=dAlpha;
pMat->dk=dkt;
MatT->AddItem(pMat);
outtext1("New Material Created.");
}

void DBase::CreateMat8(CString sInTit,
                       int iInMID,
                       double dInE1,
                       double dInE2,
                       double dInNU12,
                       double dInG12,
                       double dInG1Z,
                       double dInG2Z,
                       double dINRHO,
                       double dInA1,
                       double dInA2,
                       double dk)
{
  MAT8* pMat = new MAT8();
  pMat->sTitle = sInTit;
  pMat->iID = iInMID;
  pMat->iType = 8;
  pMat->dE1= dInE1;
  pMat->dE2= dInE2;
  pMat->dNU12= dInNU12;
  pMat->dG12= dInG12;
  pMat->dG1Z= dInG1Z;
  pMat->dG2Z= dInG2Z;
  pMat->dRHO= dINRHO;
  pMat->dA1= dInA1;
  pMat->dA2= dInA2;
  MatT->AddItem(pMat);
  outtext1("New Material Created.");
}

void DBase::CreatePrBox(CString sT,int iPID,int iMID,double dW,double dH,double dWT,double dHT)
{
PBARL* pBar = new PBARL();
pBar->sSecType = "BOX";
pBar->sTitle=sT;
pBar->iMID=iMID;
pBar->iID=iPID;
pBar->iNoDims=4;
pBar->dDIMs[0]=dW;
pBar->dDIMs[1]=dH;
pBar->dDIMs[2]=dWT;
pBar->dDIMs[3]=dHT;
pBar->CreateSec();
PropsT->AddItem(pBar);
outtext1("New BAR Section Created.");
}

void DBase::CreatePrL(CString sT, int iPID, int iMID, double dW, double dH, double dWT, double dHT)
{
	//NOTE this element is not support in NASTRAN but added fot
	//M3d solver
	PBARL* pBar = new PBARL();
	pBar->sSecType = "L ";
	pBar->sTitle = sT;
	pBar->iMID = iMID;
	pBar->iID = iPID;
	pBar->iNoDims = 4;
	pBar->dDIMs[0] = dW;
	pBar->dDIMs[1] = dH;
	pBar->dDIMs[2] = dWT;
	pBar->dDIMs[3] = dHT;
	pBar->CreateSec();
	PropsT->AddItem(pBar);
	outtext1("New BAR Section Created.");
}

void DBase::CreatePrT2(CString sT, int iPID, int iMID, double dW, double dH, double dWT, double dHT)
{
	PBARL* pBar = new PBARL();
	pBar->sSecType = "T2";
	pBar->sTitle = sT;
	pBar->iMID = iMID;
	pBar->iID = iPID;
	pBar->iNoDims = 4;
	pBar->dDIMs[0] = dW;
	pBar->dDIMs[1] = dH;
	pBar->dDIMs[2] = dWT;
	pBar->dDIMs[3] = dHT;
	pBar->CreateSec();
	PropsT->AddItem(pBar);
	outtext1("New T2 Beam Section Created.");
}

void DBase::CreatePrCHAN2(CString sT, int iPID, int iMID, double dW, double dH, double dWT, double dHT)
{
	PBARL* pBar = new PBARL();
	pBar->sSecType = "CHAN2";
	pBar->sTitle = sT;
	pBar->iMID = iMID;
	pBar->iID = iPID;
	pBar->iNoDims = 4;
	pBar->dDIMs[0] = dHT;
	pBar->dDIMs[1] = dWT;
	pBar->dDIMs[2] = dH;
	pBar->dDIMs[3] = dW;
	pBar->CreateSec();
	PropsT->AddItem(pBar);
	outtext1("New CHAN2 Beam Section Created.");
}

void DBase::CreatePrI2(CString sT, int iPID, int iMID, double d1, double d2, double d3, double d4, double d5, double d6)
{
	PBARL* pBar = new PBARL();
	pBar->sSecType = "I ";
	pBar->sTitle = sT;
	pBar->iMID = iMID;
	pBar->iID = iPID;
	pBar->iNoDims = 6;
	pBar->dDIMs[0] = d1;
	pBar->dDIMs[1] = d2;
	pBar->dDIMs[2] = d3;
	pBar->dDIMs[3] = d4;
	pBar->dDIMs[4] = d5;
	pBar->dDIMs[5] = d6;
	pBar->CreateSec();
	PropsT->AddItem(pBar);
	outtext1("New I2 Beam Section Created.");
}


void DBase::CreatePrTube(CString sT,int iPID,int iMID,double dR,double dr)
{
PBARL* pBar = new PBARL();
pBar->sSecType = "TUBE";
pBar->sTitle=sT;
pBar->iMID=iMID;
pBar->iID=iPID;
pBar->iNoDims=2;
pBar->dDIMs[0]=dR;
pBar->dDIMs[1]=dr;
pBar->CreateSec();
PropsT->AddItem(pBar);
outtext1("New TUBE Section Created.");
}


void DBase::CreatePrRod(CString sT,int iPID,int iMID,double dR)
{
PBARL* pBar = new PBARL();
pBar->sSecType = "ROD";
pBar->sTitle=sT;
pBar->iMID=iMID;
pBar->iID=iPID;
pBar->iNoDims=1;
pBar->dDIMs[0]=dR;
pBar->CreateSec();
pBar->CalcProps();
PropsT->AddItem(pBar);
pBar->CreateSec();
outtext1("New BAR Section Created.");
}

void DBase::CreatePRBar2(CString sT, int iPID, int iMID, double dA, double dI1,  double dI2, double dJ)
{
	PBAR* pS = new PBAR();
	pS->sTitle = sT;
	pS->iMID = iMID;
	pS->iID = iPID;
	pS->dA = dA;
	pS->dI1 = dI1;
	pS->dI2 = dI2;
	pS->dJ = dJ;
	pS->CreateSec();
	PropsT->AddItem(pS);
	outtext1("New BAR Section Created.");
}

void DBase::CreatePRod(CString sT,int iPID,int iMID,double dA,double dJ)
{
PROD* pBar = new PROD();
pBar->sSecType = "PROD";
pBar->sTitle=sT;
pBar->iMID=iMID;
pBar->iID=iPID;
pBar->A=dA;
pBar->J=dJ;
pBar->CreateSec();
PropsT->AddItem(pBar);
outtext1("New ROD Section Created.");
}

//************************************************
//                  END DBASE
//************************************************




SecTable::SecTable()
{
iNo = 0;
//defualt section
this->add(1, 
		  1, 
		  1, 
		  10, 
		  10, 
		  1, 
		  99,
		  299, 
		  99,
		  1,
      FALSE,0,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1);


}

void SecTable::ExportSecs(FILE* pFile)
{
char Name[20];
int i;
double w;
double h;
double t;
int id;
// WG Sections
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","776");
for(i=0;i<iNo;i++)
{
  if (Secs[i]->bFlex==FALSE)
  {
    sprintf_s(Name,"%s%i%s%f2%i","WR",Secs[i]->WR,"_t",Secs[i]->THK,Secs[i]->Opt);
    w=Secs[i]->W/1000+Secs[i]->THK/1000;
    h=Secs[i]->H/1000+Secs[i]->THK/1000;
    t=Secs[i]->THK/1000;
    id=Secs[i]->SecNo;
    fprintf(pFile,"%10i%10i%10i\n",id,2,0);
    fprintf(pFile,"%20s\n",Name);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E%13.6E%13.6E\n",w,h,t,t,0.0,0.0);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0,0.0,0.0);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0,0.0,0.0);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0,w/2,h/2);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0,0.0,0.0);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0,0.0,0.0);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0,0.0,0.0);
    fprintf(pFile,"%13.6E%13.6E%13.6E%13.6E\n",0.0,0.0,0.0,0.0);
    fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",6,6,6,6,6,6);
    fprintf(pFile,"%10i%10i%10i%10i%13.6E\n",0,45,1,11,1.0);
  }
  }
fprintf(pFile,"%6s\n","-1");
}

void SecTable::add(int iWR, 
		           int iWG, 
		           double dTHK, 
		           double dW, 
		           double dH, 
		           int iCOL, 
		           int iPID, 
				        int iPID2,
		           int iSecNo,
				       int iOpt,
               BOOL inF,
               double dr,
               int iM1,
               int iM2,
               double THK2,
               double dLFR,
               double dINSMS,
               double dINSMB,
               int iP1,
               int iP2,
               int iP3,
               int iP4,
               int iP5,
               int iP6)
{
if (iNo<MaxSecs) 
{
  Secs[iNo] = new SecProp();
  Secs[iNo]->WR=iWR; 
  Secs[iNo]->WG=iWG; 
  Secs[iNo]->THK=dTHK; 
  Secs[iNo]->W=dW; 
  Secs[iNo]->H=dH; 
  Secs[iNo]->COL=iCOL; 
  Secs[iNo]->PID=iPID; 
  Secs[iNo]->PID2=iPID2; 
  Secs[iNo]->SecNo=iSecNo;
  Secs[iNo]->Opt=iOpt;
  Secs[iNo]->bFlex=inF;
  Secs[iNo]->dR=dr;
  Secs[iNo]->iMat1=iM1;
  Secs[iNo]->iMat2=iM2;
  Secs[iNo]->THK2=THK2;
  Secs[iNo]->dLFR=dLFR;
  Secs[iNo]->dNSMS=dINSMS;
  Secs[iNo]->dNSMB=dINSMB;
  Secs[iNo]->iP1=iP1;
  Secs[iNo]->iP2=iP2;
  Secs[iNo]->iP3=iP3;
  Secs[iNo]->iP4=iP4;
  Secs[iNo]->iP5=iP5;
  Secs[iNo]->iP6=iP6;
  iNo++;
}
else
{
  outtext1("ERROR: Max Sections Exceeded.");
}
}


Section* SecTable::GetSec(int iWR,double dThk,int iOpt,int iSW,int iSH,BOOL bis)
{
int i;
int iSec=-1;
double dT;
double dH;
double dW;

Section* Sec = new Section();
if (bis==FALSE)
{
  for(i=0;i<iNo;i++)
  {
    if ((Secs[i]->WR == iWR) &&
        (Secs[i]->THK == dThk) &&
	      (Secs[i]->Opt == iOpt) &&
        (Secs[i]->bFlex == FALSE))
    {
      iSec=i;
	    break;
    }
  }
}
else
{
  for(i=0;i<iNo;i++)
  {
    if ((Secs[i]->WR == iWR) &&
       (Secs[i]->bFlex == TRUE))
    {
      iSec=i;
	    break;
    }
  }
}
if (iSec==-1)
{
  outtext1("ERROR: Invalid Section.");
  iSec=0;
}
Sec->Create(iSec,Secs[iSec]->PID,Secs[iSec]->PID2,
			Secs[iSec]->SecNo,Secs[iSec]->COL,NULL);
Sec->dWall=Secs[iSec]->THK/1000;
dT=Secs[iSec]->THK/1000;
dH=Secs[iSec]->H/1000;
dW=Secs[iSec]->W/1000;
if ((iOpt>10) && (iSW>3))
{
   iSW=iSW-2;
}
Sec->AddLine(-dW/2,-dH/2,dW/2,-dH/2,iSW);
Sec->AddLine(dW/2,-dH/2,dW/2,dH/2,iSH);
Sec->AddLine(dW/2,dH/2,-dW/2,dH/2,iSW);
Sec->AddLine(-dW/2,dH/2,-dW/2,-dH/2,iSH);
return(Sec);
}

SecProp* SecTable::GetSecP(int iWR,double dThk,int iOpt,int iSW,int iSH)
{
SecProp* retSec=NULL;
int i;
for(i=0;i<iNo;i++)
{
  if ((Secs[i]->WR == iWR) &&
      (Secs[i]->THK == dThk) &&
	    (Secs[i]->Opt == iOpt))
  {
     retSec=Secs[i];
	   break;
  }
}
return (retSec);
}

SecProp* SecTable::GetSecPF(int iWR)
{
SecProp* retSec=NULL;
int i;
for(i=0;i<iNo;i++)
{
  if ((Secs[i]->WR == iWR) &&
      (Secs[i]->bFlex == TRUE))
  {
     retSec=Secs[i];
	   break;
  }
}
return (retSec);
}


BEGIN_MESSAGE_MAP(DBase, CCmdTarget)
//  ON_COMMAND(ID_MATERIAL_ISENTROPIC, &DBase::OnMaterialIsentropic)
//ON_COMMAND(ID_SURFACE_SWEEP, &DBase::OnSurfaceSweep)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(DBase, CCmdTarget)
	DISP_FUNCTION_ID(DBase, "GetNo", dispidGetNo, GetNo, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(DBase, "AddNode", dispidAddNode, API_AddNode, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(DBase, "ReDrawWindow", dispidReDrawWindow, ReDrawWindow, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// Note: we add support for IID_IDBase to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {45542F2E-3541-4330-9BE0-A4B59B3D392C}
static const IID IID_IDBase =
{ 0x45542F2E, 0x3541, 0x4330, { 0x9B, 0xE0, 0xA4, 0xB5, 0x9B, 0x3D, 0x39, 0x2C } };

BEGIN_INTERFACE_MAP(DBase, CCmdTarget)
	INTERFACE_PART(DBase, IID_IDBase, Dispatch)
END_INTERFACE_MAP()


// DBase message handlers

LONG DBase::GetNo(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	// TODO: Add your dispatch handler code here
	return DB_ObjectCount;
}



//void DBase::OnMaterialIsentropic()
//{
//  // TODO: Add your command handler code here
//}

//void DBase::OnSurfaceSweep()
//{
//  // TODO: Add your command handler code here
//}




void CalcPCorr(Matrix <double> &UVPS,double dx,double dy,double dt)
{
double a;
double b;
double c;
double d;
int i;
int j;

double t;
double dS;
double dSLast;
int iCnt;

a = 2 * (dt / (dx*dx) + dt / (dy*dy));
b = -dt / (dx*dx);
c = -dt / (dy*dy);
//Set existing values to 0
for (j = 0; j< UVPS.n+1;j++)
{
   for (i = 0;i< UVPS.m+1;i++)
   {
      if ((i%2!=0) && (j%2!=0))
      {
        UVPS(i, j) = 0;
      }
   }
}
dSLast = 100;
dS=100;
iCnt = 0;

//Do while the pressure correction is not changing to a certain tol or just keep going until
//interupted by Esc key
    do
    {
    dSLast = dS;
    iCnt = iCnt + 1;
    dS = 0;
    for (j=2;j<UVPS.n-1;j++)
    {
       for (i=2;i<UVPS.m-1;i++)
       {
          if ((i%2!=0) && (j%2!=0))
          {
             d = 1.0 / dx * (UVPS(i + 1, j) - UVPS(i - 1, j)) 
               + 1.0 / dy * (UVPS(i, j + 1) - UVPS(i, j - 1));
             t = -(1 / a) * (b * UVPS(i + 2, j) + 
                             b * UVPS(i - 2, j) + 
                             c * UVPS(i, j + 2) + 
                             c * UVPS(i, j - 2) + d);
             if (abs(UVPS(i, j) - t) > dS)
             {
               dS = abs(UVPS(i, j) - t);
             }
             UVPS(i, j) = UVPS(i, j) + 0.3 * (t - UVPS(i, j)); //'Relaxation of 0.3
          }
       }
    }

//ws.Cells(2, 1) = dS 'report the pressure change
} 
while  ((iCnt<50));
//ws.Cells(2, 2) = iCnt 'report the count

}


//Calc uStar
double CalcpU(Matrix <double> &UVP,int i,int j,double dx,double dy,double dt,double Re)
{
double pUStar;
double vb;
double vbb;
double AStar;

vb = 0.5 * (UVP(i - 1, j + 1) + UVP(i + 1, j + 1));
vbb = 0.5 * (UVP(i - 1, j - 1) + UVP(i + 1, j - 1));
AStar = -((UVP(i + 2, j) *UVP(i + 2, j) - UVP(i - 2, j)*UVP(i - 2, j)) / (2 * dx) + 
           (UVP(i, j + 2) * vb - UVP(i, j - 2) * vbb) / (2 * dy)) + 
            (1 / Re) * ((UVP(i + 2, j) - 2 * UVP(i, j) + UVP(i - 2, j)) / (dx*dx) + (UVP(i, j + 2) - 2 * UVP(i, j) + UVP(i, j - 2)) / (dy*dy));

pUStar = AStar * dt - dt * (UVP(i + 1, j) - UVP(i - 1, j)) / dx;
return (pUStar);
}

//Calc vStar
double CalcpV(Matrix <double> &UVP,int i,int j,double dx,double dy,double dt,double Re)
{
double pVStar;
double ub;
double ubb;
double BStar;

ub = 0.5 * (UVP(i + 1, j - 1) + UVP(i + 1, j + 1));
ubb = 0.5 * (UVP(i - 1, j - 1) + UVP(i - 1, j + 1));
BStar = -((UVP(i + 2, j) * ub - UVP(i - 2, j) * ubb) / (2 * dx) + 
          (UVP(i, j + 2)*UVP(i, j + 2) - UVP(i, j - 2)*UVP(i, j - 2)) / (2 * dy)) + 
          (1 / Re) * ((UVP(i + 2, j) - 2 * UVP(i, j) + UVP(i - 2, j)) / (dx*dx) + (UVP(i, j + 2) - 2 * UVP(i, j) + UVP(i, j - 2)) / (dy*dy));
        
pVStar = BStar * dt - dt * (UVP(i, j + 1) - UVP(i, j - 1)) / dx;

return(pVStar);
}



void  DBase::SolveCFD2()
{
//clear all;clf;clc;
double re=1000; // for higher reynolds number(>500-1000), use under relaxation
double rex=0.1; // underrelaxation, 0<rex<1
double rexb=rex;
double dx; 
double dy;
int nx=51; 
int ny=51;
dx=1.0/(nx-1); 
dy=1.0/(ny-1);
double fac;
int i;
int j;
int k;
CDC* pDC = pTheView->GetDC();
InitOGL(pDC);
fac=2*(1/(dx*dx)+1/(dy*dy));
double Y=1.0;
double uo=1.0;
double nu;
nu=Y/(uo*re);

ObjList* pVec = new ObjList();

// initial condition

//p(1:nx,1:ny)=0; 
Matrix <double> p(nx+1,ny+1);
//o(1:nx,1:ny)=0;
Matrix <double> o(nx+1,ny+1);
//psi(1:nx,1:ny)=0;
Matrix <double> psi(nx+1,ny+1);
//omega(1:nx,1:ny)=0;
Matrix <double> omega(nx+1,ny+1);
//uact(1:nx,1:ny)=0;
Matrix <double> uact(nx+1,ny+1);
//vact(1:nx,1:ny)=0;
Matrix <double> vact(nx+1,ny+1);
//u(1:nx,1:ny)=0;
Matrix <double> u(nx+1,ny+1);
//v(1:nx,1:ny)=0;
Matrix <double> v(nx+1,ny+1);
for(i=0;i<p.m;i++){for(j=0;j<p.n;j++){p(i,j) = 0;}}
for(i=0;i<u.m;i++){for(j=0;j<u.n;j++){u(i,j) = 0;}}
for(i=0;i<v.m;i++){for(j=0;j<v.n;j++){v(i,j) = 0;}}
for(i=0;i<o.m;i++){for(j=0;j<o.n;j++){o(i,j) = 0;}}
for(i=0;i<omega.m;i++){for(j=0;j<omega.n;j++){omega(i,j) = 0;}}

for (k=1;k<nx+1;k++)
{
  //u(k,ny)=1.0;
}
u(25,25)=1.0;
for (k=1;k<500000;k++)
{
  //disp(['iteration= ',int2str(iteration)]) 
  //stream function(internal nodes)
double f1;

for (i=2;i<nx;i++)
{
  for (j=2;j<ny;j++)
  {
    //pold(i,j)=p(i,j);
    f1=1/fac*(o(i,j)+(p(i+1,j)+p(i-1,j))/(dx*dx)+(p(i,j+1)+p(i,j-1))/(dy*dy));
    p(i,j)=p(i,j)+rex*(f1-p(i,j));
    
  }
}

//Vorticity (Boundary nodes)
double fab;
double fcd;
for (j=1;j<ny+1;j++)
{
  fab=-2*p(2,j)/(dx*dx); //left side(AB)
  o(1,j)=o(1,j)+rexb*(fab-o(1,j));
  fcd=-2*p(nx-1,j)/(dx*dx); //right side(CD)
  o(nx,j)=o(nx,j)+rexb*(fcd-o(nx,j));
  //o(20,20)=10;  //this will add a vortex
}

double fad;
double fbc;
for (i=1;i<nx+1;i++)
{
  fad=-2*p(i,2)/(dy*dy); //bottom side(AD)
  o(i,1)=o(i,1)+rexb*(fad-o(i,1));
  fbc=-(2*p(i,ny-1)+2*uo*dy)/(dy*dy); //top side (BC)
  o(i,ny)=o(i,ny)+rexb*(fbc-o(i,ny));
}

//vorticity internal nodes 
double f2;

for (i=2;i<nx;i++)
{
  for (j=2;j<ny;j++)
  {
    //oold(i,j)=o(i,j);
    f2=1/fac*((o(i+1,j)+o(i-1,j))/(dx*dx)+(o(i,j+1)+o(i,j-1))/(dy*dy)
    -re*(p(i,j+1)-p(i,j-1))*(o(i+1,j)-o(i-1,j))/(4*dx*dy)
    +re*(p(i+1,j)-p(i-1,j))*(o(i,j+1)-o(i,j-1))/(4*dx*dy));
    o(i,j)=o(i,j)+rex*(f2-o(i,j)); 
  }
}

// Calculate the velocity (u and v)

for (i=2;i<nx;i++)
{
  for (j=2;j<ny;j++)
  {
  u(i,j)=(p(i,j+1)-p(i,j-1))/(2*dy);
  v(i,j)=-(p(i+1,j)-p(i-1,j))/(2*dx);
  }
}
PlotSol2(pVec,u,v,dx,dy);
}
outtext1("Done");
PlotData2(pVec,u,v,dx,dy);
//PlotSol2(pVec,u,v,dx,dy);
delete (pVec);
pTheView->ReleaseDC(pDC);
 /* % rearrange in cartesian coordinate 
  %(which originally in matrix coordinate)
  for i=1:nx
  for j=1:ny
  k=i; 
  l=j;
  psi(l,k)=p(i,j);
  omega(l,k)=o(i,j);
  uact(l,k)=u(i,j);
  vact(l,k)=v(i,j);
  end
  end
  figure(1)% Streamline plot with number
  Z = psi(1:ny,1:nx); 
  X = linspace(0,1,size(Z,2));
  Y = linspace(0,1,size(Z,1));
  [c,h] = contour(X,Y,Z);

  axis equal
  axis([0 1 0 1])
  drawnow
  end*/


}

void  BCS(Matrix <double>  &a)
{

//for(i=2;i<a.m-2;i+=2)
//{
//  a.elem(i, a.n-1) = 1.0;
//}
a.elem(2, 21)=0.5;
a.elem(2, 23)=0.5;
a.elem(2, 25)=0.5;
a.elem(2, 27)=0.5;


}

void  DBase::SolveCFD()
{
int i;
int j;
int k;



double dt = 0.001;         //Timestep
double dx ;               //Spacing in X
double dy ;               //Spacing in Y
int NP = 51;              //No of pressure points
int iNJ = 2 * NP - 1;      //Array size in x note this twice the size of the number of"
int iNI = 2 * NP - 1 ;     //Pressure points specified as velocities are at between location
dx=1.0/50.0;
dy=1.0/50.0;
ObjList* pVec = new ObjList();

//for a staggered grid
double Re = 2000;          //Re Number
CDC* pDC = pTheView->GetDC();
InitOGL(pDC);


double pUStar;
double pVStar;
char S1[80];
Matrix <double> UVP(iNI+1,iNJ+1);
Matrix <double> UVPS(iNI+1,iNJ+1);
for(i=0;i<UVP.m;i++){for(j=0;j<UVP.n;j++){UVP(i,j) = 0;}}
for(i=0;i<UVPS.m;i++){for(j=0;j<UVPS.n;j++){UVPS(i,j) = 0;}}

BCS(UVP);


for (k=1;k<10000;k++)
{
    //ws.Cells(1, 1) = k      //Report the iteration number to the worksheet
    
    //Print the matrix to excel every 20 steps
    //If (k Mod 20 = 0) Then
    //  PrintA UVP, ws, 5, 5
    //End If
    double tt;
    for(i=0;i<UVPS.m;i++){for(j=0;j<UVPS.n;j++){UVPS(i,j) = UVP(i,j);}}
    for (j=3;j<iNJ-1;j++)           //for all internal velocities which can be calculated
    {
       for (i=3;i<iNI-1;i++) 
       {
         tt=UVPS(i, j);
          if ((i%2==0) && (j%2!=0))  
          {//its a U velocity
             pUStar = CalcpU(UVP, i, j,dx,dy,dt,Re);      //calc the next value
             UVP(i, j) = UVP(i, j) + pUStar;
          }
          if ((i%2!=0) && (j%2==0))                       //its a V velocity
          {
             pVStar = CalcpV(UVP, i, j,dx,dy,dt,Re);      //calc the next value
             UVP(i, j) = UVP(i, j) + pVStar;
          }
       }
    }
    
    for(i=0;i<UVPS.m;i++){for(j=0;j<UVPS.n;j++){UVPS(i,j) = UVP(i,j);}}
    //PrintA UVP, ws, 5, 5
    CalcPCorr (UVPS,dx,dy,dt);                           //Calculate the pressure correction

    //Update Velocities uvp matrix
    for (j=3;j<iNJ-1;j++)           //for all internal velocities which can be calculated
    {
       for (i=3;i<iNI-1;i++) 
       {
          if ((i%2==0) && (j%2!=0))  
          {
             UVP(i, j) = UVPS(i, j);
          }
          if ((i%2!=0) && (j%2==0)) 
          {
             UVP(i, j) = UVPS(i, j);
          }
       }
    }
    //Update the pressures by the correction but note the 0.5 relaxation
    //which you decide
    //this only serves to stabalise the solution and slow it down
    for (j=2;j<iNJ;j++)           //for all internal velocities which can be calculated
    {
       for (i=2;i<iNI;i++) 
       {
          if ((i%2!=0) && (j%2!=0))
          {
            UVP(i, j) = UVP(i, j) + 0.3 * UVPS(i, j);
          }
       }
    }
    //Velocity corrections due to the pressure corection
    //also note the relaxation
    for (j=2;j<iNJ-1;j++)           
    {
       for (i=2;i<iNI-1;i++) 
       {
              if ((i%2==0) && (j%2!=0))
              {
                 UVP(i, j) = UVP(i, j) - 0.3 * dt * (UVPS(i + 1, j) - UVPS(i - 1, j)) / (dx);
              }
              if ((i%2!=0) && (j%2==0))
              {
                 UVP(i, j) = UVP(i, j) - 0.3 * dt * (UVPS(i, j + 1) - UVPS(i, j - 1)) / (dy);
              }
       }
    }
    //Update boundary velocities on ghost grids
    for (i=1;i<iNI+1;i++) 
    {
     if (i%2!=0) 
     {
       UVP(i, 2) =  1/ 3 * UVP(i, 4);
       UVP(i, iNJ - 1) =  1/ 3 * UVP(i, iNJ - 3);
       UVP(1, iNJ - 1) =UVP(1, iNJ - 3);
       UVP(3, iNJ - 1) =UVP(3, iNJ - 3);
       UVP(5, iNJ - 1) =UVP(5, iNJ - 3);
       UVP(7, iNJ - 1) =UVP(7, iNJ - 3);
       UVP(9, iNJ - 1) =UVP(9, iNJ - 3);
     }
    }
    for (i=1;i<iNJ+1;i++) 
    {
     if (i%2!=0) 
     {
       UVP(2, i) = 1 / 3 * UVP(4, i);
       UVP(iNI - 1, i) =  1 / 3 *UVP(iNI - 3, i);
     }
    }
    //Update boundary Pressures on boundary grids
    for (i=1;i<iNI+1;i++) 
    {
     if (i%2!=0) 
     {
       UVP(i, 1) = UVP(i, 3);
       UVP(i, iNJ) = UVP(i, iNJ - 2);
       UVP(1, iNJ- 2) =0;
       UVP(3, iNJ- 2) =0;
       UVP(5, iNJ- 2) =0;
       UVP(7, iNJ- 2) =0;
       UVP(9, iNJ- 2) =0;
     }
    }
    for (i=1;i<iNJ+1;i++) 
    {
     if (i%2!=0) 
     {
       UVP(1, i) = UVP(3, i);
       UVP(iNI, i) = UVP(iNI - 2, i);
     }
     if (i%2==0) 
     {
       UVP(1, i) = 0;
       UVP(iNI, i) = 0;
     }
    }
    BCS(UVP);                 //re-afirm the lid velocity
    if (k%10==0)
    {
    sprintf_s(S1,"%s%i","Iteration:",k);
    outtext1(S1);
    PlotSol(pVec,UVP,dx,dy);
    }
}
PlotData(pVec,UVP,dx,dy);
delete (pVec);
pTheView->ReleaseDC(pDC);
}

void  DBase::PlotSol(ObjList* pVec,Matrix<double> &UVP,double dx,double dy)
{

double u;
double v;
double x;
double y;
double Mag;
int i;
int j;
int iL;
C3dVector a;
C3dVector b;
NLine* LnIn;
if (pVec->iNo==0)
{
  for (j=1;j<UVP.n;j+=2)
  {
    for (i=1;i<UVP.m;i+=2)
    {
        if ((i%2!=0) && (i%2!=0)) 
        {
          u = 0.5 * (UVP(i + 1, j) + UVP(i - 1, j));
          v = 0.5 * (UVP(i, j + 1) + UVP(i, j - 1));
          Mag = sqrt(u*u + v*v);
          x = 4*i * dx-4;
          y = 4*j * dy-4;
          a.x=x;
          a.y=y;
          a.z=0;
          b.x=x+u;
          b.y=y+v;
          b.z=0;
          LnIn = new NLine();
          LnIn->Create(a,b,0,NULL);
          AddObj(LnIn);
          pVec->Add(LnIn);
        }
    }
  }
  
}
else
{
iL=0;
  for (j=1;j<UVP.n;j+=2)
  {
    for (i=1;i<UVP.m;i+=2)
    {
        if ((i%2!=0) && (i%2!=0)) 
        {
          u = 0.5 * (UVP(i + 1, j) + UVP(i - 1, j));
          v = 0.5 * (UVP(i, j + 1) + UVP(i, j - 1));
          Mag = sqrt(u*u + v*v);
          x = 4*i * dx-4;
          y = 4*j * dy-4;
          b.x=x+u;
          b.y=y+v;
          b.z=0;
          LnIn=(NLine*) pVec->Objs[iL];
          LnIn->cPts[1]->Pt_Point->Set(b.x,b.y,0);  
          iL++;
        }
    }
  }
}

InvalidateOGL();
ReDraw();
}

void  DBase::PlotSol2(ObjList* pVec,Matrix<double> &U,Matrix<double> &V,double dx,double dy)
{

double u;
double v;
double x;
double y;
double Mag;
int i;
int j;
int iL;
C3dVector a;
C3dVector b;
NLine* LnIn;
if (pVec->iNo==0)
{
  for (j=1;j<U.n-2;j+=2)
  {
    for (i=1;i<V.m-2;i+=2)
    {
          u = U(i , j);
          v = V(i , j);
          Mag = sqrt(u*u + v*v);
          x = 3*i * dx;
          y = 3*j * dy;
          a.x=x;
          a.y=y;
          a.z=0;
          b.x=x+u;
          b.y=y+v;
          b.z=0;
          LnIn = new NLine();
          LnIn->Create(a,b,0,NULL);
          AddObj(LnIn);
          pVec->Add(LnIn);
     }
   } 
}
else
{
iL=0;
  for (j=1;j<U.n-2;j+=2)
  {
    for (i=1;i<V.m-2;i+=2)
    {
          u = U(i , j);
          v = V(i , j);
          Mag = sqrt(u*u + v*v);
          x = 3*i * dx;
          y = 3*j * dy;
          b.x=x+u;
          b.y=y+v;
          b.z=0;
          LnIn=(NLine*) pVec->Objs[iL];
          LnIn->cPts[1]->Pt_Point->Set(b.x,b.y,0);  
          iL++;
     }
   }
}
InvalidateOGL();
ReDraw();
}

void  DBase::PlotData2(ObjList* pVec,Matrix<double> &U,Matrix <double> &V,double dx,double dy)
{

double u;
double v;



int i;
int j;

C3dVector a;
C3dVector b;

char S1[80];
outtext1("Centre Line Data.");
if (pVec->iNo!=0)
{
  for (j=1;j<U.n;j++)
  {
        i=U.n/2;
        if (j%2!=0)
        {
          u = U(i,j);
          v = V(j,i);
          sprintf_s(S1,"%s%f%s%f","X ",u," Y ",v);
          outtext1(S1);
        }
  }
}
outtext1("End of Report.");
}


void  DBase::PlotData(ObjList* pVec,Matrix<double> &UVP,double dx,double dy)
{

double u;
double v;



int i;
int j;

C3dVector a;
C3dVector b;

char S1[80];
outtext1("Centre Line Data.");
if (pVec->iNo!=0)
{
  for (j=1;j<UVP.n;j++)
  {
        i=UVP.n/2+1;
        if (j%2!=0)
        {
          u = UVP(i,j);
          v = UVP(j,i);
          sprintf_s(S1,"%s%f%s%f","X ",u," Y ",v);
          outtext1(S1);
        }
  }
}
outtext1("End of Report.");
}


void DBase::ResSelect()
{
  CResSelDialog Dlg;
  if (pCurrentMesh!=NULL)
  {
    Dlg.SetData(FALSE,pCurrentMesh->ResultsSets,pCurrentMesh->iNoRes,pCurrentMesh->iCurResSet,pCurrentMesh->iResVal,pCurrentMesh->iSecID);
	Dlg.iCurResSet=pCurrentMesh->iCurResSet;
    Dlg.iResVal=pCurrentMesh->iResVal;
	Dlg.DoModal();

    if (Dlg.iCurResSet!=-1)
      pCurrentMesh->iCurResSet=Dlg.iCurResSet;
    if (Dlg.iResVal!=-1)
      pCurrentMesh->iResVal=Dlg.iResVal;
	if (Dlg.iSecResID!=-1)
      pCurrentMesh->iSecID=Dlg.iSecResID;
    else
      pCurrentMesh->iResVal=-1;
    char OutT[20];
    sprintf_s(OutT,"%i,%i,%i",pCurrentMesh->iCurResSet,pCurrentMesh->iResVal,pCurrentMesh->iSecID);
    outtextMSG2("RESSEL");
    outtextMSG2(OutT);
  }
  else
  {
    outtext1("ERROR: No Mesh Active.");
  }
}

void DBase::ResSelectVec()
{
	CResSelDialog Dlg;
	if (pCurrentMesh != NULL)
	{
		Dlg.SetData(TRUE,pCurrentMesh->ResultsSets, pCurrentMesh->iNoRes, pCurrentMesh->iCurResVecSet, pCurrentMesh->iResVec, pCurrentMesh->iSecVecID);
		Dlg.DoModal();

		if (Dlg.iCurResSet != -1)
			pCurrentMesh->iCurResVecSet = Dlg.iCurResSet;
		if (Dlg.iResVal != -1)
			pCurrentMesh->iResVec = Dlg.iResVal;
		if (Dlg.iSecResID != -1)
			pCurrentMesh->iSecVecID = Dlg.iSecResID;
		else
			pCurrentMesh->iResVec = -1;
		char OutT[20];
		sprintf_s(OutT, "%i,%i,%i", pCurrentMesh->iCurResVecSet, pCurrentMesh->iResVec, pCurrentMesh->iSecVecID);
		outtextMSG2("RESVEC");
		outtextMSG2(OutT);
	}
	else
	{
		outtext1("ERROR: No Mesh Active.");
	}
}


void DBase::ResSelectDef()
{
  CResSelDialog Dlg;
  if (pCurrentMesh!=NULL)
  {
    Dlg.SetData(FALSE,pCurrentMesh->ResultsSets,pCurrentMesh->iNoRes,pCurrentMesh->iCurResSetDef,pCurrentMesh->iResValDef,pCurrentMesh->iSecID);
	  Dlg.DoModal();
    if (Dlg.iCurResSet!=-1)
      pCurrentMesh->iCurResSetDef=Dlg.iCurResSet;
    if (Dlg.iResVal!=-1)
      pCurrentMesh->iResValDef=Dlg.iResVal;
    else
      pCurrentMesh->iResValDef=-1;
    char OutT[20];
    sprintf_s(OutT,"%i,%i",pCurrentMesh->iCurResSetDef,pCurrentMesh->iResValDef);
    outtextMSG2("RESDEF");
    outtextMSG2(OutT);
  }
  else
  {
    outtext1("ERROR: No Mesh Active.");
  }
}

void DBase::DoDeformedDisp()
{
if ((DspFlags & DSP_RESDEF) == 0)
{
   pCurrentMesh->BuildDeromedVecs();
}
else
{
  pCurrentMesh->DeleteDeromedVecs();
}
InvalidateOGL();
ReDraw();
}

//****************************28/09/2016 SYMBOLS TABLE****************************
void DBase::ClearSymTable()
{
int i;
if (iNoSymbols>0)
{
  for(i=0;i<iNoSymbols;i++)
  {
    delete(pSymTable[i]);
  }
}
iNoSymbols=0;
}


void DBase::AddSymbol(Symbol* pSym)
{
  if (iNoSymbols<MAX_SYMBOLS)
  {
     pSymTable[iNoSymbols]=pSym;
     iNoSymbols++;
  }
}




//*********************************************************
// Text to be inserted at vInPt and transformed to vN
//*********************************************************
void DBase::AddText(C3dVector vN, C3dVector vDir, C3dVector vInPt, CString inText, double dH)
{
	Text* pText = new Text(vInPt,vN,vDir,iTxtLabCnt,inText, dH,nullptr);
	iTxtLabCnt++;
	if (pText != nullptr)
	{
		AddObj(pText);
		ReDraw();
	}
}





void DBase::displaySymTable()
{
int i;
C3dVector vM;
vM.Set(0, 0, 0);
Symbol* pSym;
Symbol* pSymN;
for (i=0;i<iNoSymbols;i++)
{
	pSym = pSymTable[i];
	pSymN = (Symbol*) pSym->Copy(NULL);
	pSymN->Translate(vM);
    AddObj (pSymN);
	vM.x += 1.25*pSym->w;
}
ReDraw();
}

void DBase::SymTableCalcMetrics()
{
int i;
//These are the average symbol heights and widths
dAveH=0;
dAveW=0;
Symbol* pS = NULL;
if (iNoSymbols > 0)
{
	for (i = 0; i < iNoSymbols; i++)
	{
		pSymTable[i]->CalculateMetrics();
		dAveH += pSymTable[i]->h;
		dAveW += pSymTable[i]->w;
	}
	dAveH /= iNoSymbols;
	dAveW /= iNoSymbols;
	//Set space width, which will calculated as 0
	//pS = GetSymbol(32);
	//pS->w = dAveW;
	for (i = 0; i < iNoSymbols; i++)
	{
		if (pSymTable[i]->iLabel == 32)
		{
			pSymTable[i]->w= dAveW;;
			break;
		}
	}
}
}


void DBase::LoadSymbols(FILE* pFileA)
{

int iStop =0;
char s1[1000];
char s2[20];
char s3[20]; 
//These are globals
iNoSymbols = 0;
dAveW = 1;
dAveH = 1;
//******************
C3dVector vP1;
C3dVector vP2;

int iLab;
Symbol* pSym;
outtext1("Loading Symbols Table.");
ClearSymTable();
C3dVector vPt(0,0,0);
  do
  {
  if (fgets(s1,1000,pFileA)!=NULL)
  {
    if ((s1[0]=='S') && (s1[1]=='Y') && (s1[2]=='M'))
    {
      outtext1(s1);
	  pSym=new Symbol();
      sscanf(s1,"%s%s",s2,s3);
	  iLab=atoi(s3);
      pSym->Create(iLab,vPt,NULL);
	  AddSymbol(pSym);
    }
    else
    {
      sscanf(s1,"%s%s",s2,s3);
      vP1.x=atof(s2);
      vP1.y=atof(s3);
	  vP1.z=0;
	  fgets(s1,1000,pFileA);
	  sscanf(s1,"%s%s",s2,s3);
      vP2.x=atof(s2);
      vP2.y=atof(s3);
	  vP2.z=0;
	  pSym->addSeg(vP1,vP2);
    }
  }
   if ((s1[0]=='E') && (s1[1]=='N') && (s1[2]=='D'))
	 iStop = 1;
   if (feof(pFileA))
     iStop = 1;
  }
  while (iStop == 0);
SymTableCalcMetrics();
displaySymTable();
}

//********************************************************************
// Pre: TRUE
// Post: Symbols table loaded from SymTable.h stored internally
//********************************************************************
void DBase::LoadSymbolsInternal()
{
	int iStop = 0;
	CString s1;
	char s2[20];
	char s3[20];

	C3dVector vP1;
	C3dVector vP2;

	int iLab;
	int i = 0;
	Symbol* pSym;
	//outtext1("Loading Internal Symbols Table.");
	ClearSymTable();
	C3dVector vPt(0, 0, 0);
	do
	{
		s1 = SymTableData[i];
		i++;
		if ((s1[0] == 'E') && (s1[1] == 'N') && (s1[2] == 'D'))
		{
			iStop = 1;
		}
		else if ((s1[0] == 'S') && (s1[1] == 'Y') && (s1[2] == 'M'))
		{
			pSym = new Symbol();
			sscanf(s1, "%s%s", s2, s3);
			iLab = atoi(s3);
			pSym->Create(iLab, vPt, NULL);
			AddSymbol(pSym);
		}
		else
		{
			sscanf(s1, "%s%s", s2, s3);
			vP1.x = atof(s2);
			vP1.y = atof(s3);
			vP1.z = 0;
			s1 = SymTableData[i];
			i++;
			sscanf(s1, "%s%s", s2, s3);
			vP2.x = atof(s2);
			vP2.y = atof(s3);
			vP2.z = 0;
			pSym->addSeg(vP1, vP2);
		}
	} while (iStop == 0);
	SymTableCalcMetrics();
	//displaySymTable();
}

void DBase::FreeMeshTri(double dS)
{

	C3dVector v;
	int iCO;
	NSurf* pS;

	for (iCO = 0; iCO < S_Count; iCO++)
	{
		if ((S_Buff[iCO]->iObjType == 15) ||
			(S_Buff[iCO]->iObjType == 16) ||
			(S_Buff[iCO]->iObjType == 17))
		{
			pS = (NSurf*)S_Buff[iCO];
			FreeMeshTriSurf(dS, pS);
		}
	}
}


void DBase::FreeMeshTriSurf(double dS, NSurf* pS)
{
	int i;
	C3dVector vPt;
	C3dVector vPt3d;
	for (i = 0; i < pS->iNoExtCvs; i++)
	{
		vPt = pS->pExtLoop[i]->GetPt(0.5);
		//vPt3d=pS->GetPt(vPt.x,vPt.y);
		this->AddNode(vPt, -1, 124, 1, 1, 1, 1);
		vPt = pS->pExtLoop[i]->GetPt(0.0);
		this->AddNode(vPt, -1, 124, 1, 1, 1, 1);
		vPt = pS->pExtLoop[i]->GetPt(1.0);
		this->AddNode(vPt, -1, 124, 1, 1, 1, 1);
	}

}

void DBase::TestCircleCir()
{
	//TEST Circle
	double RR;
	c2dParPt p1, p2;
	C2dVector p3, pc;
	cSeg* pTSeg = new cSeg();
	p1.PP.x = 0;
	p1.PP.y = 0;
	p2.PP.x = 1;
	p2.PP.y = 0;
	p3.x = 1;
	p3.y = 1;
	pTSeg->pt[0] = &p1;
	pTSeg->pt[1] = &p2;
	RR = CirCircle(pTSeg, p3, pc);
}

//Check the proposed point is not near seg
double  DBase::ProximityChk(ObjList* pSegs, c2dParPt* vPt)
{
	double dMinDist = 1e36;
	double dDist;
	int i;
	cSeg* s;


	for (i = 0; i < pSegs->iNo; i++)
	{
		s = (cSeg*)pSegs->Objs[i];
		dDist = DistPtSeg(s, vPt->PP);
		if (dDist < dMinDist)
			dMinDist = dDist;
	}
	return (dMinDist);
}

double  DBase::ProximityChk2d(ObjList* pSegs, c2dParPt* vPt, double dSX, double dSY)
{
	double dMinDist = 1e36;
	double dDist;
	int i;
	cSeg* s;


	for (i = 0; i < pSegs->iNo; i++)
	{
		s = (cSeg*)pSegs->Objs[i];
		dDist = DistPtSeg2d(s, vPt->PP, dSX, dSY);
		if (dDist < dMinDist)
			dMinDist = dDist;
	}
	return (dMinDist);
}

BOOL DBase::CheckInt(ObjList* pSegs,cSeg* bS, c2dParPt* vPt)
{
	BOOL brc = FALSE;
	int i;
	cSeg* s;
	double dTol = 0.000001;
	C2dVector s1A, s1B, s2A, s2B, X1, X2;

	//Intersection base seg P1-vPt with all seges in pSegs
	s1A = bS->pt[0]->PP;
	s1B = vPt->PP;

	for (i = 0; i < pSegs->iNo; i++)
	{ 
		s = (cSeg*) pSegs->Objs[i];
		if (!s->HasCommonVert(bS->pt[0],vPt))  //if they share a common vertex they can't interset
		{
			s2A = s->pt[0]->PP;
			s2B = s->pt[1]->PP;
			brc = intersect2DUV_2Segments(s1A, s1B,s2A,s2B,&X1,&X2);
			if (brc)
				break;
		}
	}
	if (!brc)
	{
		s1A = vPt->PP; 
		s1B = bS->pt[1]->PP;

		for (i = 0; i < pSegs->iNo; i++)
		{
			s = (cSeg*)pSegs->Objs[i];
			if (!s->HasCommonVert(bS->pt[1],vPt))  //if they share a common vertex they cant interset
			{
				s2A = s->pt[0]->PP;
				s2B = s->pt[1]->PP;
				brc = intersect2DUV_2Segments(s1A, s1B, s2A, s2B, &X1, &X2);
				if (brc)
					break;
			}
		}


	}


	return(brc);
}

//********************************************************************
//Advancing Front Surface Mesh generator
//********************************************************************


BOOL DBase::UpdateFront(NSurf* pSf, int &iNodeLab, int &iSegLab, BOOL isNewNd, cSeg* pBaseSeg, ObjList* Pts, cLinkedList* Segs, c2dParPt* pbFNd, C2dVector pTmp, ObjList* pEls)
{
	BOOL brc = FALSE;
	C2dVector MidPt;
	cSeg* pS;
	if (pbFNd != NULL) //It a node on existing front
	{
		BOOL bR;
		//Seg1 midpoint
		MidPt.x = 0.5*(pBaseSeg->pt[0]->PP.x + pbFNd->PP.x);
		MidPt.y = 0.5*(pBaseSeg->pt[0]->PP.y + pbFNd->PP.y);
		//IF its in remove from segs else add
		pS = (cSeg*) Segs->Head;
		bR = FALSE;
		while (pS != NULL)  
		{
			if (pS->MpT.Dist(MidPt) < 0.0000001)
			{
				Segs->Remove2(pS);
				bR = TRUE;
				pS = NULL;
			}
			else
			{
				pS = (cSeg*) pS->next;
			}
		}
		if (!bR) // need to add the new seg;
		{ 
			pS = new cSeg(pSf);
			pS->pt[0] = pBaseSeg->pt[0];
			pS->pt[1] = pbFNd;
			pS->CalcMids();
			pS->iLabel = iSegLab; iSegLab++;
			Segs->Add(pS);
		}
		MidPt.x = 0.5*(pBaseSeg->pt[1]->PP.x + pbFNd->PP.x);
		MidPt.y = 0.5*(pBaseSeg->pt[1]->PP.y + pbFNd->PP.y);
		//IF its in remove from segs else add
		pS = (cSeg*)Segs->Head;
		bR = FALSE;
		while (pS != NULL)
		{
			if (pS->MpT.Dist(MidPt) < 0.0000001)
			{
				Segs->Remove2(pS);
				bR = TRUE;
				pS = NULL;
			}
			else
			{
				pS = (cSeg*)pS->next;
			}
		}
		if (!bR) // need to add the new seg;
		{
			pS = new cSeg(pSf);
			pS->pt[0] = pbFNd;
			pS->pt[1] = pBaseSeg->pt[1];
			pS->CalcMids();
			pS->iLabel = iSegLab; iSegLab++;
			Segs->Add(pS);
		}
		pEls->Add(pBaseSeg->pt[0]);
		pEls->Add(pbFNd);
		pEls->Add(pBaseSeg->pt[1]);
		Segs->Remove2(pBaseSeg);
	}
	else //create a new inteiror point and the new segs
	{ 
	//Create the new point
		c2dParPt* pPt = new c2dParPt(pTmp.x, pTmp.y);
		pPt->pParent = pSf;
		pPt->iLabel = iNodeLab; iNodeLab++;
		Pts->Add(pPt);
		pS = new cSeg(pSf);
		pS->pt[0] = pBaseSeg->pt[0];
		pS->pt[1] = pPt;
		pS->CalcMids();
		pS->iLabel = iSegLab; iSegLab++;
		Segs->Add(pS);
		pS = new cSeg(pSf);
		pS->pt[0] = pPt;
		pS->pt[1] = pBaseSeg->pt[1];
		pS->CalcMids();
		pS->iLabel = iSegLab; iSegLab++;
		Segs->Add(pS);
		pEls->Add(pBaseSeg->pt[0]);
		pEls->Add(pPt);
		pEls->Add(pBaseSeg->pt[1]);
		Segs->Remove2(pBaseSeg);
	}
	return(brc);
}

//Generates a tesselation that can be attached to surface
//but for now just createing nodes and element
//for debugging mesh generator
CONST int MAX_PTS_2D = 50000;
eFaceList* DBase::GenTesselation(ObjList* pN, ObjList* pE)
{
	Node* PtRealXYX[MAX_PTS_2D];
	int i;
	int N1,N2,N3;
	NSurf* pS;
	c2dParPt* pPt;
	C3dVector ptXYZ;
	Node* pENodes[100];
	E_Object3* pRet;
	if (pN->iNo < MAX_PTS_2D)
	{
		//Convert all the pN to real nodes
		for (i = 0; i < pN->iNo; i++)
		{

			if (pCurrentMesh->iNodeLab == 339)
				i = i;
			pPt = (c2dParPt*)pN->Objs[i];
			pS = (NSurf*)pPt->pParent;
			ptXYZ = pS->GetPt(pPt->PP.x, pPt->PP.y);
			//ptXYZ.x = pPt->PP.x;  // to be deleted
			//ptXYZ.y = pPt->PP.y;  // to be deleted
			//ptXYZ.z = 0;  // to be deleted
			PtRealXYX[i] = pCurrentMesh->AddNode(ptXYZ, pCurrentMesh->iNodeLab, 0, 0, 50, 0, 0);
			pCurrentMesh->iNodeLab++;
		}
		for (i = 0; i < pE->iNo; i += 3)
		{
			N1 = pN->IsIn2(pE->Objs[i]);
			N2 = pN->IsIn2(pE->Objs[i + 1]);
			N3 = pN->IsIn2(pE->Objs[i + 2]);
			pENodes[0] = PtRealXYX[N1];
			pENodes[1] = PtRealXYX[N2];
			pENodes[2] = PtRealXYX[N3];
			pRet = (E_Object3*)pCurrentMesh->AddEl(pENodes, pCurrentMesh->iElementLab, 162, 91, -1, -1, 3, 1, 1, 1, FALSE, -1, 0);
			Dsp_Add(pRet);
			pCurrentMesh->iElementLab++;
		}
	}
	else
	{
		outtext1("ERROR: Max Nodes Exceeded for 2d Mesh.");
	}
	return(NULL);
}

//Do 1 cycle of Lapacian smoothing
void DBase::Smooth(ObjList* pN, ObjList* pE)
{
	c2dParPt* pSN;
	c2dParPt* pEN;
	C2dVector vNewPos;
	int iCnt;
	int i;
	int j;
	for (i = 0; i < pN->iNo; i++)
	{
		pSN = (c2dParPt *)pN->Objs[i];
		iCnt = 0;
		vNewPos.x = 0; vNewPos.y = 0;
		if (pSN->iColour != 4)  //Then its an interior node so Smooth
		{
			//Find All Element Conected to this Node
			for (j = 0; j < pE->iNo; j+=3)
			{
				if ((pE->Objs[j] == pSN) || (pE->Objs[j + 1] == pSN) || (pE->Objs[j + 2] == pSN))
				{
					if (pE->Objs[j] != pSN)
					{
					   pEN = (c2dParPt*)pE->Objs[j];
					   vNewPos += pEN->PP;
					   iCnt++;
					}
					if (pE->Objs[j+1] != pSN)
					{
						pEN = (c2dParPt*)pE->Objs[j+1];
						vNewPos += pEN->PP;
						iCnt++;
					}
					if (pE->Objs[j+2] != pSN)
					{
						pEN = (c2dParPt*)pE->Objs[j+2];
						vNewPos += pEN->PP;
						iCnt++;
					}
				}
			}
			vNewPos.x/=iCnt; vNewPos.y /= iCnt;
			pSN->PP = vNewPos;
		}
	}
}

BOOL DBase::NodeInTri(C2dVector t1, C2dVector t2, C2dVector t3, C2dVector pt)
{
	BOOL bRet=TRUE;
	C2dVector v1, v2, v3, vt;
	double dCross1;
	v1 = t2 - t1;
	v2 = t3 - t2;
	v3 = t1 - t3;
	v1.Normalize();
	v2.Normalize();
	v3.Normalize();
	vt = pt - t1;
	vt.Normalize();
	dCross1 = v1.Cross(vt);
	if (dCross1 < 0)
		return(FALSE);
	vt = pt - t2;
	vt.Normalize();
	dCross1 = v2.Cross(vt);
	if (dCross1 < 0)
		return(FALSE);
	vt = pt - t3;
	vt.Normalize();
	dCross1 = v3.Cross(vt);
	if (dCross1 < 0)
		return(FALSE);

	return(TRUE);
}

BOOL DBase::isSegIn(ObjList* pSegs, c2dParPt* pS1, c2dParPt* pS2)
{
	int i;
	BOOL bRet = FALSE;
	cSeg* pSeg;
	for (i = 0; i < pSegs->iNo; i++)
	{
		pSeg = (cSeg*) pSegs->Objs[i];
		if ((pSeg->pt[0] == pS1) && (pSeg->pt[1] == pS2))
		{
			bRet = TRUE;
			break;
		}
	}
	return (bRet);
}

BOOL DBase::isNodeInCircle(ObjList* pN, int iExclude, double dRad, C2dVector Cpt)
{
	BOOL bRet = FALSE;
	C2dVector vPt;
	int i;
	for (i = 0; i < pN->iNo; i++)
    {
	  c2dParPt* pPt = (c2dParPt*)pN->Objs[i];
	  if (i != iExclude)
	  {
		  vPt = pPt->PP;
		  vPt -= Cpt;
		  if (vPt.Mag() < dRad-0.0000001)
			  bRet = TRUE;
	  }
    }

	return (bRet);
}

BOOL DBase::isNodeInCircle2d(ObjList* pN, int iExclude, double dRad, C2dVector Cpt, double dSX, double dSY)
{
	BOOL bRet = FALSE;
	C2dVector vPt;
	int i;
	for (i = 0; i < pN->iNo; i++)
	{
		c2dParPt* pPt = (c2dParPt*)pN->Objs[i];
		if (i != iExclude)
		{
			vPt = pPt->PP;
			vPt.x *= dSX;
			vPt.y *= dSY;
			vPt -= Cpt;
			if (vPt.Mag() < dRad - 0.0000001)
				bRet = TRUE;
		}
	}

	return (bRet);
}

//***************************************************************************
//                     EXPERIMENTAL QMORPH
// Cpnvert tri mesh to quads
// Advancing Front Quadrilateral Meshing Using Triangle Transformations
// Steven J. Owen1,2, Matthew L. Staten2, Scott A. Canann1,2 and Sunil Saigal1
//***************************************************************************
void DBase::QMorph(ObjList* Els)
{
	int i;
	eEdgeList* LkList = NULL;
	ObjList* Els2 = new ObjList();
	for (i = 0; i < Els->iNo; i++)
	{
		if ((Els->Objs[i]->iObjType == 3) && (Els->Objs[i]->pParent == this->pCurrentMesh))
		{
			E_Object* pE = (E_Object*)Els->Objs[i];
			//TRI ELEMENTS ONLY
			if (pE->iType == 91)
			{
				Els2->Add(pE);
			}
		}
	}
	if (Els2->iNo == 0)
	{
		outtext1("ERROR: No Valid Elements Selected.");
	}
	else
	{
		//Start QMORPHing
		if (pCurrentMesh->LkList != NULL)
		{
			Dsp_Rem(pCurrentMesh->LkList);
			RemTempGraphics(pCurrentMesh->LkList);
			delete(pCurrentMesh->LkList);
			pCurrentMesh->LkList = NULL;
		}
		LkList = FindEdges(Els2);
		if ((pCurrentMesh->LkList == NULL) && (LkList != NULL))
		{
			pCurrentMesh->LkList = LkList;
			eEdge* pNext = LkList->Head;
			while (pNext != NULL)
			{
				Dsp_Add(pNext);
				pNext = (eEdge*)pNext->next;
			}
			InvalidateOGL();
			ReDraw();
		}
	}
	delete(Els2);
	//delete(LkList);
}

//*****************************************************************************
//               SET LINE MESH SIZE ON CURVES
//				 AND MESH INCLUDED FOR NOW
//*****************************************************************************
void DBase::MeshBeamSize(ObjList* pCurves, double dS)
{
	int iCO;
	int i, j;
	int iInc;
	double dL;
	char S1[200];
	NCurve* pEdge = NULL;
	if (dS < 0)
	{
		outtext1("ERROR: Element mesh size must be > 0.");
	}
	else
	{
		for (iCO = 0; iCO < pCurves->iNo; iCO++)
		{
			if (pCurves->Objs[iCO]->iObjType == 7)
			{
				pEdge = (NCurve*) pCurves->Objs[iCO];
				pEdge->dLSize = dS;		//Set size on element
				dL = pEdge->getLen();	//Get the length of the edge
				iInc = dL / dS;			//Calculate the number of elements
				if (iInc < 1)			//Can't have less than 1 element
					iInc = 1;
				if ((pEdge->iType==3) && (iInc<4))	//Case of sircle
					iInc = 4;			//Use a min of 4 elements
				pEdge->iInc = iInc;
				sprintf_s(S1, "INFO: %i Elements Set For Curve %i Set", iInc, pEdge->iLabel);
				outtext1(S1);
			}
		}
		MeshBeams(pCurves);
	}
}

//Pre: MeshBeamSize has already been called to set iInc
//Post: Beam nodes and elemenet geerated for all curves
//      in pCureves and added to current mesh
void DBase::MeshBeams(ObjList* pCurves)
{
	NCurve* pEdge = NULL;
	int i = 0;
	int iInc=0;		//No of elements increments
	int iC = 124;	//Colour of curve to transfur to element
	cLinkedList* pNds = new cLinkedList();
	for (i = 0; i < pCurves->iNo; i++)
	{
		if (pCurves->Objs[i]->iObjType == 7)  //Its a curve
		{
			pNds->Clear();
			pEdge = (NCurve*)pCurves->Objs[i];
			if (pEdge != NULL)
			{
				iInc = pEdge->iInc;
				iInc += 1;
				//Generate nodes on curve and store in pNds;
				NodesOnCurve(pEdge,iInc,pNds);
				GenBEamElements(pNds, pEdge->iColour);
				ReDraw();
			}
			else
			{
				
			}
			//sprintf_s(S1, "INFO: %i Elements Set For Curve %i Set", iInc, pEdge->iLabel);
			//outtext1(S1);
		}
	}
	delete (pNds);
}

//*****************************************************************************
//               SET 2D MESH SIZE ON SURFACE
//               AND DIVIDE EDGES INTO SEG DIVISIONS
//*****************************************************************************
void DBase::MeshSurfSize(ObjList* pSurfs, double dS)
{
	int iCO;
	int i, j;
	int iInc;
	double dL;
	NSurf* pS = NULL;
	NCurve* pEdge = NULL;
	if (dS < 0)
	{
		outtext1("ERROR: Element mesh size must be > 0.");
	}
	else
	{
		for (iCO = 0; iCO < pSurfs->iNo; iCO++)
		{
			if ((pSurfs->Objs[iCO]->iObjType == 15) ||
				(pSurfs->Objs[iCO]->iObjType == 16) ||
				(pSurfs->Objs[iCO]->iObjType == 17))
			{
				pS = (NSurf*) pSurfs->Objs[iCO];
				pS->dSSize = dS;		//Set size on element
				//Calculate the number of increment on edges
				for (i = 0; i < pS->iNoExtCvs; i++)
				{
					if (pS->pExtLoop[i]->pSC != NULL)
					{
						pEdge = (NCurve*) pS->pExtLoop[i]->pSC;
						dL = pEdge->getLen();
						iInc = dL / dS;
						if ((pS->iNoExtCvs == 1) && (iInc < 4))
						{
							iInc = 4;
						}
						if (iInc < 1)
							iInc = 1;
						if (iInc > pEdge->iInc)
						{
							pEdge->iInc = iInc;
							pS->pExtLoop[i]->iInc = iInc;
						}
					}
				}
				for (i = 0; i < pS->iNoIntLoops; i++)
				{
					for (j = 0; j < pS->iNoIntCvs[i]; j++)
					{
						if (pS->pIntLoop[i][j]->pSC != NULL)
						{
							pEdge = (NCurve*)pS->pIntLoop[i][j]->pSC;
							dL = pEdge->getLen();
							iInc = dL / dS;
							if ((pS->iNoIntCvs[i] == 1) && (iInc < 4))
							{
								iInc = 4;
							}
							if (iInc < 1)
								iInc = 1;
							if (iInc > pEdge->iInc)
							{
								pEdge->iInc = iInc;
								pS->pIntLoop[i][j]->iInc = iInc;
							}
						}
					}
				}
			}
		}
	}
}

//*****************************************************************************
//               2D SURFACE ADVANCING MESHING ALGORITHM
//*****************************************************************************
void DBase::MeshSurfAF(ObjList* pSurfs, double dSz)
{

	char S1[80];
	outtext1("**** STARTING AFM GEN 2D ****");
	PrintTime("START TIME: ");
	BOOL bNinT;
	int iNoEls;
	bool bExitFail = FALSE;
	C2dVector t1(0, 0);
	C2dVector t2(1, 0);
	C2dVector t3(0, 1);
	C2dVector vTPt(1, 1);
	bNinT = NodeInTri(t1, t2, t3, vTPt);
	C3dVector v;
	double dMinDst;
	int iNodeLab = 1;
	int iSegLab = 1;
	int i;
	int j;
	int iCO;
	NSurf* pS;
	double RR;
	double RRF;
	BOOL bIs;
	eFaceList* pTesselation;
	ObjList* Pts = new ObjList();
	cLinkedList* Segs = new cLinkedList();  //The FRONT
	ObjList* pCandidateSegs = new ObjList();
	ObjList* pFrontNodes = new ObjList();
	ObjList* pEls = new ObjList();
	//AddObj(Segs); //If this is left in can save and reload model
	BOOL bExit=TRUE;
	c2dParPt* pPt;
	c2dParPt* pPtN = new c2dParPt();
	cSeg* pSeg;
	C2dVector pTmp;
	C2dVector pC;
	C2dVector vD;
	C3dVector p3d;
	C3dVector dSSpc1;
	C3dVector dSSpc2;
	double dMinR;
	int iID;
	c2dParPt* pbFNd;
	BOOL isNewNd;
	int iDBCnt;
	double dSclU;
	double dSclV;
	double dSclPU;
	double dSclPV;
	double dS;
	dS = dSz;
	Matrix<C3dVector> der;
	C3dVector v1;
	C3dVector v2;
	for (iCO = 0; iCO < pSurfs->iNo; iCO++)
	{
		if (pSurfs->Objs[iCO]->iObjType == 15) 
		{

			bExitFail = FALSE;
			pS = (NSurf*) pSurfs->Objs[iCO];
			//if (pS->iLabel == 87)
			//	pS->iLabel = 87;
			if (pS->dSSize > 0)
				dS = pS->dSSize;
			CreateBSegs(Pts, Segs,dS, pS);
			Pts->GenIDS(iNodeLab);
			Segs->GenIDS(iSegLab);
			//Display the initial front
			//GenPts(pS, Pts);
			i = 0;
			j = 0;
			iDBCnt = DB_ObjectCount;
			//Calulate element size in parametric ordinates
			//U only at present
			pSeg = (cSeg*)Segs->Head;
			//**********Need to CHECK***********

			//**********************************
			do
			{
				if (j == 30)
					j = j;
				pSeg = (cSeg*)Segs->Head;
				//Calculate a node position away from seg
				if (pSeg != NULL)
				{
					//local scale factor
					pS->deriveAt(pSeg->MpT.x, pSeg->MpT.y, 1, der);
					v1 = der(1, 0);
					dSclPU = v1.Mag();
					dSclU = dS / dSclPU;
					v2 = der(0, 1);
					dSclPV = v2.Mag();
					dSclV = dS / dSclPV;
					der.DeleteAll(); 
					//end local scale factor
					vD.x = pSeg->pt[0]->PP.y - pSeg->pt[1]->PP.y;
					vD.y = pSeg->pt[1]->PP.x - pSeg->pt[0]->PP.x;
					vD.Normalize();
					vD.x *= dSclU;
					vD.y *= dSclV;
					pTmp.x = pSeg->MpT.x + vD.x;
					pTmp.y = pSeg->MpT.y + vD.y;
					pTmp.Clamp(0, 1);
					RR = CirCircle2d(pSeg, pTmp, pC,dSclPU, dSclPV);
					C3dVector vCC = pS->GetPt(pC.x, pC.y);
					//Need to check the new node is acceptable
					//for now lets say it is
					isNewNd = TRUE;
					//Need to check this point pTmp is deluany and away from front and non intersecting.
					//p3d = pS->GetPt(pTmp.x, pTmp.y);  //Just for visualisation
					//pRealPt = AddPt(p3d, 111, TRUE);
					//pRealPt->iLabel = iNodeLab; iNodeLab++;
					pCandidateSegs->iNo=0;
					pFrontNodes->iNo = 0;
					GetCandiatesSeg2d(pSeg,Segs, pC, 2*RR, pCandidateSegs, dSclPU, dSclPV);
					GetCandiatesNodes2d(pSeg,pCandidateSegs, pC, 2*RR, pFrontNodes, dSclPU, dSclPV);
					//Get Best node from boundary short list
					dMinR = RR;
					pbFNd = NULL;
					pPtN->PP.x = pTmp.x; pPtN->PP.y = pTmp.y;
					dMinDst = ProximityChk2d(pCandidateSegs, pPtN, dSclPU, dSclPV);
					if (dMinDst > 0.5*RR)
					{
						if (CheckInt(pCandidateSegs, pSeg, pPtN))
						{
							RR = 10000000000;
							dMinR = RR;
						}
					}
					else
					{
						RR = 10000000000;
						dMinR = RR;
					}
					if (pFrontNodes->iNo==0)
						outtext1("WARNING: No Cnadidate Nodes.");
					for (i=0;i< pFrontNodes->iNo;i++)
					{ 
						pPt = (c2dParPt*) pFrontNodes->Objs[i];
						if (!CheckInt(pCandidateSegs, pSeg, pPt))
						{

							BOOL bNoGood = FALSE;
							RRF = CirCircle2d(pSeg, pPt->PP, pC, dSclPU, dSclPV);
							//Check no other nodes fall in circumcirle
							bIs = isNodeInCircle2d(pFrontNodes, i, RRF, pC, dSclPU, dSclPV);
							if (!bIs)
							{
							  //if seg[0],pPt and seg[1],pPt are in seg list
							  //it must form an element
							  if (RRF < dMinR)
							  {
							    iID = pPt->iLabel;
								pbFNd = pPt;
								dMinR = RRF;
							  }
							  if ((isSegIn(pCandidateSegs, pSeg->pt[1], pPt)) &&
								  (isSegIn(pCandidateSegs, pPt, pSeg->pt[0])))
							  {
								  iID = pPt->iLabel;
								  pbFNd = pPt;
								  dMinR = RRF;
								  break;
							  }
							}
							else
							{
								//outtext1("ERROR: Node in Circumcircle.");
								//bExitFail = TRUE;
							}
						}
					}
					//if an acceptable node from the boundary is available use it
					//else create the new a new point at pTmp
					//SHOULD do a quality check to decide which is the best option
					if (dMinR == 10000000000)
					{
						bExitFail = TRUE; //Need to swap
						outtext1("ERROR: Meshing Failed.");
					}
					else
					  UpdateFront(pS,iNodeLab, iSegLab,isNewNd,pSeg,Pts, Segs, pbFNd, pTmp, pEls);
				}
				//if (j>1)

				j++;
				//if (j==155)
				//   bExitFail = TRUE;
			} while  ((Segs->iCnt > 0) && (!bExitFail));
		}
		//Smoothing Cycle
		outtext1("Performing 1 Smoothing Cycle");
		//PrintTime("TIME: ");
		if (!bExitFail)
		   Smooth(Pts, pEls);
		//Generate Faces from pEls
		iNoEls = pEls->iNo / 3;
		pTesselation = GenTesselation(Pts, pEls);

		Pts->DeleteAll();
		Segs->DeleteAll();
		pEls->Clear();
		sprintf_s(S1, "Number off Tri Elements Generated: %i", iNoEls);
		outtext1(S1);

	}
	InvalidateOGL();
	ReGen();
	delete(Pts);
	delete(pEls);
	Dsp_Rem(Segs);
	RemTempGraphics(Segs);
	RemObj(Segs);
	PrintTime("END TIME: ");
	outtext1("**** END AFM GEN 2D ****");
	

	//Need to delete these too
	//pFrontNodes
	//pCandidateSegs
	//pEls
}





double DBase::CirCircle(cSeg* pSeg, C2dVector pt, C2dVector &pC)
{
	double drc = 1e36;
	double x1, y1, x2, y2, P, Q;
	double A1, A2, B1, B2;
	double AA, BB, AB, DET, C1, C2, XX, YY, XC, YC, RR;

	x1 = pSeg->pt[0]->PP.x;
	y1 = pSeg->pt[0]->PP.y;
	x2 = pSeg->pt[1]->PP.x;
	y2 = pSeg->pt[1]->PP.y;
	P = pt.x;
	Q = pt.y;
	A1 = x2 - x1;
	A2 = y2 - y1;
	B1 = P - x1;
	B2 = Q - y1;
	AA = A1 * A1 + A2 * A2;
	BB = B1 * B1 + B2 * B2;
	AB = A1 * B1 + A2 * B2;
	DET = AA * BB - AB * AB;
	C1 = 0.5*BB*(AA - AB) / DET;
	C2 = 0.5*AA*(BB - AB) / DET;
	XX = C1 * A1 + C2 * B1;
	YY = C1 * A2 + C2 * B2;
	RR = pow(XX*XX + YY*YY,0.5);
	pC.x = x1 + XX;
	pC.y = y1 + YY;
	return (RR);

}

//****************************************************************
//Scaled Paremtric Version
//U and V are scaled to local real spacing
//****************************************************************
double DBase::CirCircle2d(cSeg* pSeg, C2dVector pt, C2dVector &pC, double dSX, double dSY)
{
	double drc = 1e36;
	double x1, y1, x2, y2, P, Q;
	double A1, A2, B1, B2;
	double AA, BB, AB, DET, C1, C2, XX, YY, XC, YC, RR;

	x1 = pSeg->pt[0]->PP.x*dSX;
	y1 = pSeg->pt[0]->PP.y*dSY;
	x2 = pSeg->pt[1]->PP.x*dSX;
	y2 = pSeg->pt[1]->PP.y*dSY;
	P = pt.x*dSX;
	Q = pt.y*dSY;
	A1 = x2 - x1;
	A2 = y2 - y1;
	B1 = P - x1;
	B2 = Q - y1;
	AA = A1 * A1 + A2 * A2;
	BB = B1 * B1 + B2 * B2;
	AB = A1 * B1 + A2 * B2;
	DET = AA * BB - AB * AB;
	C1 = 0.5*BB*(AA - AB) / DET;
	C2 = 0.5*AA*(BB - AB) / DET;
	XX = C1 * A1 + C2 * B1;
	YY = C1 * A2 + C2 * B2;
	RR = pow(XX*XX + YY * YY, 0.5);
	pC.x = x1 + XX;
	pC.y = y1 + YY;
	return (RR);
}

double DBase::DistPtSeg(cSeg* pSeg, C2dVector pt)
{
	double dd,dP;
	C2dVector pS1, pS2;
	C2dVector AB, AC, ABT;
	pS1 = pSeg->pt[0]->PP;
	pS2 = pSeg->pt[1]->PP;
	//Second Method
	AB= pS2; AB -= pS1;
	AC= pt; AC -= pS1;
	// Cross Product Method
	//  double ABxAC;
	//  ABxAC = AB.Cross(AC);
	//  dd = abs(ABxAC / AB.Mag());
	// Second Method
	double ABM;
	ABM = AB.Mag();
	AB.Normalize();
	ABT.x = -AB.y;
	ABT.y =  AB.x;
	dd = abs(ABT.Dot(AC));
	dP = AB.Dot(AC) / ABM;
	if ((dP < -0.5) || (dP > 1.5)) //No int with segement
		dd = 1e36;
	return (dd);

}

double DBase::DistPtSeg2d(cSeg* pSeg, C2dVector pt, double dSX, double dSY)
{
	double dd, dP;
	C2dVector pS1, pS2;
	C2dVector AB, AC, ABT;
	pS1 = pSeg->pt[0]->PP;
	pS1.x *= dSX;
	pS1.y *= dSY;
	pS2 = pSeg->pt[1]->PP;
	pS2.x *= dSX;
	pS2.y *= dSY;

	//Second Method
	AB = pS2; AB -= pS1;
	AC = pt; 
	AC.x *= dSX;
	AC.y *= dSY;
	AC -= pS1;
	// Cross Product Method
	//  double ABxAC;
	//  ABxAC = AB.Cross(AC);
	//  dd = abs(ABxAC / AB.Mag());
	// Second Method
	double ABM;
	ABM = AB.Mag();
	AB.Normalize();
	ABT.x = -AB.y;
	ABT.y = AB.x;
	dd = abs(ABT.Dot(AC));
	dP = AB.Dot(AC) / ABM;
	if ((dP < -0.5) || (dP > 1.5)) //No int with segement
		dd = 1e36;
	return (dd);

}

void DBase::GetCandiatesSeg(cSeg* pNot, cLinkedList* pFrom, C2dVector vC, double dCD, ObjList* pRes)
{
	C2dVector vT;
	pRes->Clear();
	G_Object* pO;
	double dDist;
	cSeg* pSeg;
	pO = pFrom->Head;
	while (pO != NULL)
	{
		if ((pO != NULL) && (pO!= pNot))
		{
			pSeg = (cSeg*) pO;
			vT = pSeg->Get_Mid();
			dDist = vT.Dist(vC);
			//dDist = DistPtSeg(pSeg, vC);
			if (dDist < dCD)         // if node is smaller than critical distance it a posible
				pRes->Add(pO);
		}
		pO = (G_Object*)pO->next;
	}


}


void DBase::GetCandiatesNodes(cSeg* pNot, ObjList* pFrom, C2dVector vC, double dCD, ObjList* pRes)
{
	int i;
	C2dVector vT;
	pRes->Clear();
	G_Object* pO;
	double dDist;
	cSeg* pSeg;
	c2dParPt* N;
	C2dVector vB;
	C2dVector vP;
	double dCross;
	vB.x = pNot->pt[1]->PP.x - pNot->pt[0]->PP.x;
	vB.y = pNot->pt[1]->PP.y - pNot->pt[0]->PP.y;
	vB.Normalize();
	//vB is base segement direction vector;

	for (i = 0; i < pFrom->iNo; i++)
	{
		pO = pFrom->Objs[i];
		if (pO != NULL) 
		{
			pSeg = (cSeg*)pO;
			N = pSeg->pt[0];
			if ((N != pNot->pt[0]) && (N != pNot->pt[1]))
			{
				vT.x = N->PP.x;
				vT.y = N->PP.y;
				dDist = vT.Dist(vC);
				vT -= pNot->pt[0]->PP;
				vT.Normalize();
				dCross = vB.Cross(vT);  //is to right
				if (dCross > 0.05)       // if node is smaller than critical distance it a posible
					pRes->AddEx(N);
			}
			N = pSeg->pt[1];
			if ((N != pNot->pt[0]) && (N != pNot->pt[1]))
			{
				vT.x = N->PP.x;
				vT.y = N->PP.y;
				dDist = vT.Dist(vC);
				vT -= pNot->pt[0]->PP;
				vT.Normalize();
				dCross = vB.Cross(vT);  //is to right
				if (dCross > 0.05)         // if node is smaller than critical distance it a posible
					pRes->AddEx(N);
			}
		}
	}
}

//Scaled stretch paremetic coordinate version all points 
//scaled by dSX,dSY
void DBase::GetCandiatesNodes2d(cSeg* pNot, ObjList* pFrom, C2dVector vC, double dCD, ObjList* pRes, double dSX, double dSY)
{
	int i;
	C2dVector vT;
	pRes->Clear();
	G_Object* pO;
	cSeg* pSeg;
	c2dParPt* N;
	C2dVector vB;
	C2dVector vP;
	double dCross;
	vB.x = pNot->pt[1]->PP.x - pNot->pt[0]->PP.x;
	vB.y = pNot->pt[1]->PP.y - pNot->pt[0]->PP.y;
	vB.x *= dSX;
	vB.y *= dSY;
	vB.Normalize();
	//vB is base segement direction vector;
	BOOL bb = FALSE;
	for (i = 0; i < pFrom->iNo; i++)
	{
		pO = pFrom->Objs[i];
		pSeg = (cSeg*) pO;
		if (pSeg == pNot)
			bb = TRUE;

		if (pO != NULL)
		{
			N = pSeg->pt[0];
			if (!CheckInt(pFrom, pNot, N))
			{
				if ((N != pNot->pt[0]) && (N != pNot->pt[1]))
				{
					vT.x = N->PP.x;
					vT.y = N->PP.y;
					vT -= pNot->pt[0]->PP;
					vT.x *= dSX;
					vT.y *= dSY;
					vT.Normalize();
					dCross = vB.Cross(vT);  //is to right
					if (dCross > 0.05)       // if node is smaller than critical distance it a posible
						pRes->AddEx(N);
				}
			}
			N = pSeg->pt[1];
			if (!CheckInt(pFrom, pNot, N))
			{
				if ((N != pNot->pt[0]) && (N != pNot->pt[1]))
				{
					vT.x = N->PP.x;
					vT.y = N->PP.y;
					vT -= pNot->pt[0]->PP;
					vT.x *= dSX;
					vT.y *= dSY;
					vT.Normalize();
					dCross = vB.Cross(vT);  //is to right
					if (dCross > 0.05)         // if node is smaller than critical distance it a posible
						pRes->AddEx(N);
				}
			}
		}
	}
}

//Scaled stretch paremetic coordinate version all points 
//scaled by dSX,dSY
void DBase::GetCandiatesSeg2d(cSeg* pNot, cLinkedList* pFrom, C2dVector vC, double dCD, ObjList* pRes, double dSX, double dSY)
{
	C2dVector vT;
	pRes->Clear();
	G_Object* pO;
	double dDist;
	cSeg* pSeg;
	pO = pFrom->Head;
	while (pO != NULL)
	{
		if ((pO != NULL) && (pO != pNot))
		{
			pSeg = (cSeg*)pO;
			vT = pSeg->Get_Mid();
			//Added Scaling to stretch para ords
			vT.x *= dSX;
			vT.y *= dSY;
			dDist = vT.Dist(vC);
			//dDist = DistPtSeg(pSeg, vC);
			if (dDist < dCD)         // if node is smaller than critical distance it a posible
				pRes->Add(pO);
		}
		pO = (G_Object*)pO->next;
	}


}

void DBase::CreateBSegs(ObjList* pP, cLinkedList* pS, double dS, NSurf* pSf)
{


	int i;
	int j;
	int k;
	double dL;
	int iInc=-1;
	C3dVector vPt;
	C3dVector vPt3d;
	double dSInc;
	double dSp;
	c2dParPt* pPt;
	cSeg* pSeg;
	NCurve* pEdge;
	for (i = 0; i < pSf->iNoExtCvs; i++)
	{
		iInc = -1;
		if (pSf->pExtLoop[i]->pSC != NULL)
		{
			pEdge = (NCurve*)pSf->pExtLoop[i]->pSC;
			iInc = pEdge->iInc;
		}
		if (iInc == -1)
		{
			dL = pSf->pExtLoop[i]->getLen();
			if (dL > dTol)
			{
				iInc = dL / dS;
				if ((pSf->iNoExtCvs == 1) && (iInc < 4))
				{
					iInc = 4;
				}
				if (iInc < 1)
					iInc = 1;
			}
			else
			{
				iInc = -1;
			}
		}
		dSInc = (pSf->pExtLoop[i]->we- pSf->pExtLoop[i]->ws)/iInc;
		dSp = pSf->pExtLoop[i]->ws;
		for (j = 0; j < iInc; j++)
		{

			vPt = pSf->pExtLoop[i]->GetParaPt(dSp);
			pPt = new c2dParPt(vPt.x, vPt.y);
			pPt->iColour = 4; //Identify as a boundary pt
			pPt->pParent = pSf;
			pP->Add(pPt);
			dSp += dSInc;
		}
	}
	//Generate External Segements
	for (i = 0; i < pP->iNo-1; i++)
	{
			pSeg = new cSeg(pSf);
			pS->Add(pSeg);
			pSeg->pt[0] = (c2dParPt*)pP->Objs[i];
			pSeg->pt[1] = (c2dParPt*)pP->Objs[i+1];
			pSeg->CalcMids();
	}
	//Last closing segement
	pSeg = new cSeg(pSf);
	pS->Add(pSeg);
	pSeg->pt[0] = (c2dParPt*)pP->Objs[pP->iNo - 1];
	pSeg->pt[1] = (c2dParPt*)pP->Objs[0];
	pSeg->CalcMids();
	int iSt;
	for (k = 0; k < pSf->iNoIntLoops; k++)
	{
		iSt = pP->iNo;
		for (i = 0; i < pSf->iNoIntCvs[k]; i++)
		{
			iInc = -1;
			if (pSf->pIntLoop[k][i]->pSC != NULL)
			{
				pEdge = (NCurve*)pSf->pIntLoop[k][i]->pSC;
				iInc = pEdge->iInc;
			}
			if (iInc == -1)
			{
				dL = pSf->pIntLoop[k][i]->getLen();
				iInc = dL / dS;
				if ((pSf->iNoIntCvs[k] == 1) && (iInc < 4))
				{
					iInc = 4;
				}
				if (iInc < 1)
					iInc = 1;
			}

			dSInc = (pSf->pIntLoop[k][i]->we - pSf->pIntLoop[k][i]->ws) / iInc;
			dSp = pSf->pIntLoop[k][i]->ws;
			for (j = 0; j < iInc; j++)
			{

				vPt = pSf->pIntLoop[k][i]->GetParaPt(dSp);
				pPt = new c2dParPt(vPt.x, vPt.y);
				pPt->iColour = 4;
				pPt->pParent = pSf;
				pP->Add(pPt);
				dSp += dSInc;
			}
		}
		//Generate Internal Segments
		for (i = iSt; i < pP->iNo - 1; i++)
		{
			pSeg = new cSeg(pSf);
			pS->Add(pSeg);
			pSeg->pt[0] = (c2dParPt*)pP->Objs[i];
			pSeg->pt[1] = (c2dParPt*)pP->Objs[i + 1];
			pSeg->CalcMids();
		}
		//Last closing segement
		pSeg = new cSeg(pSf);
		pS->Add(pSeg);
		pSeg->pt[0] = (c2dParPt*)pP->Objs[pP->iNo - 1];
		pSeg->pt[1] = (c2dParPt*)pP->Objs[iSt];
		pSeg->CalcMids();
	}
}


void DBase::GenPts(NSurf* pS, ObjList* Pts)
{
	C2dVector pTmp;
	C3dVector p3d;
	c2dParPt* ppt;
	int i;
	for (i = 0; i < Pts->iNo; i++)
	{
		ppt = (c2dParPt*) Pts->Objs[i];

		pTmp.x = ppt->PP.x;
		pTmp.y = ppt->PP.y;
		pTmp.Clamp(0, 1);
		if (pS != NULL)
		{
			p3d = pS->GetPt(pTmp.x, pTmp.y);
			CvPt_Object* pThePt = new CvPt_Object;
			pThePt->Create(p3d, 1, ppt->iLabel, 0, 0, ppt->iColour, NULL);
			AddObj(pThePt);
		}
	}
}

void DBase::LabGapsMP(int iGap)
{
	//PropTable* PropsT;
	//MatTable* MatT;
	char buff[200];
	int i = 0;
	int iCur;
	int iS;
	vector<int> iLabs;
	sprintf_s(buff, "%s %i", "Finding Material Labeling Gaps > ", iGap);
	outtext1(buff);
	//Material label sparsity
	if ((MatT->iNo > 2) && (iGap > 0))
	{
		for (i = 0; i < MatT->iNo; i++)
			iLabs.push_back(MatT->pEnts[i]->iID);
		sort(iLabs.begin(), iLabs.end());

		for (i = 1; i < iLabs.size(); i++)
		{
			iCur = iLabs.at(i - 1);
			iS = iLabs.at(i) - iCur;
			if (iS > iGap)
			{
				sprintf_s(buff, "%s %i to %i size %i", "Gap Found at:  ", iCur + 1, iLabs.at(i) - 1, iS - 1);
				outtext1(buff);
				iCur = iLabs.at(i);
			}
		}
	}
	else
	{
		outtext1("ERROR: No Node Gaps Found.");
	}
	iLabs.clear();
	//Property label sparsity
	sprintf_s(buff, "%s %i", "Finding Property Labeling Gaps > ", iGap);
	outtext1(buff);
	if ((PropsT->iNo > 2) && (iGap > 0))
	{
		for (i = 0; i < PropsT->iNo; i++)
			iLabs.push_back(PropsT->pEnts[i]->iID);
		sort(iLabs.begin(), iLabs.end());

		for (i = 1; i < iLabs.size(); i++)
		{
			iCur = iLabs.at(i - 1);
			iS = iLabs.at(i) - iCur;
			if (iS > iGap)
			{
				sprintf_s(buff, "%s %i to %i size %i", "Gap Found at:  ", iCur + 1, iLabs.at(i) - 1, iS - 1);
				outtext1(buff);
				iCur = iLabs.at(i);
			}
		}
	}
	else
	{
		outtext1("ERROR: No Node Gaps Found.");
	}


}

//********************************************************************
//****************************    End      ***************************
//********************************************************************



//void  ME_Object::SolveLidCav()
//{
//int i,j;
//double dt=0.001;
//double dX;
//double dY;
//dList X;
//dList Y;
//int indi;
//int indj;
//int iNJ;
//int iNI;
////Mesh building
//for (i=0;i<iNdNo;i++)
//{
//  X.AddEx(pNodes[i]->Pt_Point->x);
//  Y.AddEx(pNodes[i]->Pt_Point->y);
//}
//X.Sort();
//Y.Sort();
//
//iNJ = 2 * Y.iNo - 1      
//iNI = 2 * X.iNo - 1 
//
//Matrix <int> A(X.iNo,Y.iNo);
//for(i=0;i<A.m;i++){for(j=0;j<A.n;j++){A(i,j) = 0;}}
//
////Store the pressure point node IDs
//for (i=0;i<iNdNo;i++)
//{
//  indj=X.IsIn(pNodes[i]->Pt_Point->x);
//  indi=Y.IsIn(pNodes[i]->Pt_Point->y);
//  A(indi,indj)=pNodes[i]->iLabel;
//}
//
//Matrix <double> Sol(Y.iNo+2,X.iNo);
//Matrix <double> Diff(Y.iNo+2,X.iNo);
//
//for(i=0;i<Sol.m;i++){for(j=0;j<Sol.n;j++){Sol(i,j) = 0;}}
//for(i=0;i<Sol.m;i++){for(j=0;j<Sol.n;j++){Diff(i,j) = 0;}}
////Test Case BD
//Pt_Object* pNd;
//pNd=this->GetNode(78);
//indj=X.IsIn(pNd->Pt_Point->x);
//indi=Y.IsIn(pNd->Pt_Point->y);
//int isUCalc=-1;
////Begin of solution
//int k;
////This is the cavity lid driven test case
//
//// 
//for (k=0;k<5000;k++)
//{
//  
//  BCCavLid2(Sol);
//  BCCavLid(Sol);
//  isUCalc=-1;
//  //Sol.elem(indi+1,indj+1)=30;
//  for (i=2;i<Y.iNo;i++)
//  {
//    for (j=2;j<X.iNo;j++)
//    {
//      if (isUCalc==-1)
//      {
//        if (j%2!=0)
//        {
//          CalcU2(Sol,i,j);
//        }
//        
//      }
//      else
//      {
//        if (j%2==0)
//        {
//          CalcV2(Sol,i,j);
//        }
//      }
//    }
//    isUCalc*=-1;
//  }
// //Presures and velocity Corrections Diff
//
//  int il;
//  for(i=0;i<Diff.m;i++){for(j=0;j<Diff.n;j++){Diff(i,j) = 0;}}
//  for (il=0;il<50;il++)
//  {
//    for (i=2;i<Y.iNo-1;i++)
//    {
//      for (j=2;j<X.iNo-1;j++)
//      {
//          if ((j%2==0) && (i%2==0))
//          {
//            CalcP(Sol,Diff,i,j);
//          }
//      }
//    }
//  }
//  int isUCalc=-1;
//  //Velocity Corretions
//  /*for (i=2;i<Diff.m-2;i++)
//  {
//    for (j=2;j<Diff.n-2;j++)
//    {
//      if (isUCalc==-1)
//      {
//        if (j%2!= 0)
//        {
//          Diff.elem(i,j)=(Diff.elem(i,j+1)-Diff.elem(i,j-1))/(dX*dt);
//        }
//        
//      }
//      else
//      {
//        if (j%2==0)
//        {
//          Diff.elem(i,j)=(Diff.elem(i+1,j)-Diff.elem(i-1,j))/(dY*dt);
//        }
//      }
//    }
//    isUCalc*=-1;
//  }*/
//  for(i=0;i<A.m;i++)
//  {
//    for(j=0;j<A.n;j++)
//    {
//         Sol(i,j) += 0.1*Diff(i,j);
//    }
//  }
//}
////DiagNostics
//Sol.diag();
//Diff.diag();
//A.DeleteAll();
//Sol.DeleteAll();
//}



void DBase::API_AddNode(DOUBLE X, DOUBLE Y, DOUBLE Z, LONG ID, LONG COL)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: Add your dispatch handler code here
	C3dVector v;
	if (pCurrentMesh != NULL)
	{
		v.Set(X, Y, Z);
		pCurrentMesh->AddNode(v, ID, -1, -1, COL, 0, 0);
	}
}


void DBase::ReDrawWindow()
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	InvalidateOGL();
	ReDraw();
	// TODO: Add your dispatch handler code here
}
