#include "G_Object.h"

#include "M3Da.h"
#define D2R  0.01745329251994
#define R2D  57.2957795130931
const double Pi = 3.1415926535;
#include "math.h"


GLubyte BMPX[13] = {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3};
GLubyte BMPY[13] = {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3};
GLubyte BMPZ[13] = {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff};
GLubyte BMPT[13] = {0x00, 0x00, 0x18, 0x24, 0x42, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x42, 0x24, 0x18};
GLubyte BMPR[13] = {0x00, 0x00, 0x42, 0x42, 0x44, 0x72, 0x50, 0x7c, 0x42, 0x42, 0x62, 0x58, 0x00};
GLubyte BMPP[13] = {0x00, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x3e, 0x49, 0x49, 0x49, 0x08, 0x08, 0x3e};
GLubyte BMPSP[13] = {0x04, 0x04, 0x04, 0x0a, 0x0a, 0x09, 0x91, 0x90, 0x50, 0x50, 0x20, 0x20, 0x20};
GLubyte BMPU[13] = {0x01,0x3D, 0x43, 0x81,  0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x00};


//Colour bar 
float cBarMax;
float cBarMin;

void SetColBar(float fMin,float fMax)
{
  cBarMax=fMax;
  cBarMin=fMin;
}


float GetContourCol(float Val)
{
float fN;
fN=(Val-cBarMin)/(cBarMax-cBarMin);
if (fN>=1.0)
{fN=0.99999;}
if (fN<=0.0)
{fN=0.000001;}
return (fN);
}

CString RemTrailingZeros(CString sIn)
{
int iLen;
int i;
CString sRet;
int iLPos;
iLen=sIn.GetLength();
iLPos=iLen;
sRet=sIn;
CString sC;

for (i=iLen;i>0;i--)
{
  sC=sRet.Mid(i-1,1);
  if (sC=="0")
  {

  }
  else
  {
    iLPos=i;
    break;
  }
}
sRet=sRet.Left(iLPos);
return(sRet);
}

CString ncr(CString sIn)
{

sIn.Replace("\n",""); 
sIn.Replace(" ",""); 
return(sIn);
}

CString f8(double dIn)
{

char s80[80];
  CString s8;
if (dIn==0)
{
  s8="0.0";
}
else
{
  sprintf (s80, "%-f",dIn);
  s8=s80;
  s8=s8.Left(8);
}
return(s8);
}

CString f4(double dIn)
{

  char s80[80];
  CString s8;

  sprintf (s80, "%-f",dIn);
  s8=s80;
  s8=s8.Left(5);
  s8+="   ";
return(s8);
}


CString e8(double dIn)
{

char s80[80];
sprintf (s80, "%e",dIn);
CString s8;
CString sRet;
CString sExp;
CString sNum;
double dExp;
s8=s80;
int iD;
int iL;
if (dIn==DBL_MAX)
{
   sRet="        ";
}
else
{
if (dIn==0)
{
  sRet="0.0";
}
else
{
  iD=s8.Find('e');
  iL=s8.GetLength();
  sExp=s8.Right(3);
  dExp=atoi(sExp);
  if (dExp>4)
  {
    if (dExp>99)
     {sNum=s8.Left(4);
      sNum=RemTrailingZeros(sNum);
      sExp=s8.Right(3);}
    else if (dExp>9)
     {sNum=s8.Left(5);
      sNum=RemTrailingZeros(sNum);
      sExp=s8.Right(2);}
    else
     {sNum=s8.Left(6);
      sNum=RemTrailingZeros(sNum);
      sExp=s8.Right(1);} 
    if (s8.Find('+')>-1)
    {
      sRet=sNum+'+'+sExp;
    }
    else
    {
      sRet=sNum+'-'+sExp;
    }
  }
  else
  {
    sRet=f8(dIn);
    sRet=RemTrailingZeros(sRet);
  }
}
}
return(sRet);
}




void OglString(int iDspFlgs,double x, double y, double z,char *s)
{
int iLen;
int i;
int iC;
iLen = strlen(s);
  if (iDspFlgs & DSP_BLACK)
  {
    glColor3fv(cols[124]);
  }
  else
  {
    glColor3fv(cols[0]);
  }
glRasterPos3f (x,y,z);
for (i=0;i<iLen;i++)
{
  iC=s[i];
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, Font1[iC-32]);
}
}


int Factorial(int n)
{
int izp;
int iRetzVal;
iRetzVal = 1;
for(izp = 0;izp < n;izp++)
  {
  iRetzVal = iRetzVal*(izp+1);
  }
return (iRetzVal);
};

CString float8NAS(double d)
{
char s1[80];
CString sRet;
sprintf_s(s1,"%8.7f",d);
sRet=s1;
sRet=sRet.Left(8);
return(sRet);
}

int minimum(int a,int b)
{
int irc;
irc = a;
if (b<a)
{
  irc = b;
}
return (irc);
}

//Results set class
ResSet::ResSet()
{
iCnt=0;
iNoV=0;
Head=NULL;
pCur=NULL;
}

Res* ResSet::Get(int ID)
{
int i;
Res* pC;
Res* pR=NULL;
pC=Head;
for (i=0;i<iCnt;i++)
{
  if (pC->ID==ID)
  {
     pR=pC;
     break;
  }
  else
  {
     pC=pC->next;
  }
}
return pR;
}


void ResSet::Add(Res* inRes)
{
  if (Head==NULL)
  {
     Head=inRes;
     pCur=inRes;
     iCnt++;
  }
  else
  {
     pCur->next = inRes;
     pCur=inRes;
     pCur->next=NULL;
     iCnt++;
  }
 
}

Filter::Filter()
{
iNo=0;

iType[0] = (0); //POINT	
iType[1] =(1); //NODE
iType[2] =(2); //LINE
iType[3] =(3); //ELEMENT
iType[4] =(4); //MESH
iType[5] =(5); //CIRCLE
iType[6] =(6); //CURVE
iType[7] =(7); //NURBS CURVE
iType[8] =(8); //NURBS CIRCLE
iType[9] =(9); //NURBS LINE
iType[10] =(10); //SURFACE EX
iType[11] =(11); //SURFACE REV
iType[12] =(12); //COORDSYS
iType[13] =(13); //CURVE ON SURFACE
iType[14] =(15); //NURBS SURFACE
iType[15] =(16); //NURBS SURFACE REVOLVE
iType[16] =(17); //NURBS SURFACE EXTRUDE
iType[17] =(500); //WG DEF
iType[18] =(600); //PART
iType[19] =(601); //ELBOW
iType[20] =(602); //BRK
iType[21] =(603); //SWEEP
iType[22] =(604); //SWEEP
iType[23] =(605); //BRK INT
iType[24] =(321); //FORCE
iType[25] =(323); //MOMENT
iType[26] =(324); //PRESSURE
iType[27] =(322); //RESTRAINT
iType[28] =(606); //SWEEPF
sType[0] = "POINT";
sType[1] = "NODE";
sType[2] = "LINE NOT USED";
sType[3] = "ELEMENT";
sType[4] = "MESH";
sType[5] = "CIRCLE N/A";
sType[6] = "CURVE N/A";
sType[7] = "CURVE";
sType[8] = "CIRCLE";
sType[9] = "LINE";
sType[10] = "SURFACE EX N/A";
sType[11] = "SURFACE REV N/A";
sType[12] = "COORDSYS";
sType[13] = "CURVE ON SURFACE";
sType[14] = "SURFACE";
sType[15] = "SURFACE REVOLVE";
sType[16] = "SURFACE EXTRUDE";
sType[17] = "WG DEFINITION";
sType[18] = "WG PART";
sType[19] = "WG ELBOW";
sType[20] = "WG BRK CLAMP";
sType[21] = "SWEEP";
sType[22] = "SWEEP BEND";
sType[23] = "BRK INT";
sType[24] = "FORCE";
sType[25] = "MOMENT";
sType[26] = "PRESSURE";
sType[27] = "RESTRAINT";
sType[28] ="FLEXIBLE";
iNoOfType=29;
}

void Filter::SetAll()
{
iNo=0;
int i;
for (i=0;i<iNoOfType;i++)
{
  SetFilter(iType[i]);
}
}

void Filter::Clear()
{
iNo=0;
}

int Filter::isIn(int iThisType)
{
int iRC=-1;
int i;
for(i=0;i<iNo;i++)
{
  if (Filt[i]==iThisType)
  {
     iRC=i;
	 break;
  }
}
return (iRC);
}


void Filter::SetFilter(int iThisType)
{
if (isIn(iThisType)==-1)
{
	Filt[iNo]=iThisType;
	iNo++;
} 
}

void Filter::RemFilter(int iThisType)
{
int ind;
ind = isIn(iThisType);
if (ind!=-1)
{
	Filt[ind]=Filt[iNo-1];
	iNo--;
} 
}

BOOL Filter::isFilter(int iThisType)
{
if (isIn(iThisType)!=-1)
{
  return(TRUE);
}
else
{
  return (FALSE);
}
}




dList::dList()
{
iNo=0;
}

void dList::Init()
{
  iNo=0;
}

void dList::Add(double indbl)
{
  if (iNo<1000)
  {
    d[iNo]=indbl;
    iNo++;
  }
  else
  {
     outtext1("Error dList items exceeded");
  }
}

void dList::AddEx(double indbl)
{
  if (iNo<1000)
  {
    if (IsIn(indbl)==-1)
    {
      d[iNo]=indbl;
      iNo++;
    }
  }
  else
  {
     outtext1("Error dList items exceeded");
  }
}


void dList::Sort()
{
int i,j;
double tD;

for (i=0;i<iNo;i++)
{
  for (j=i;j<iNo;j++)
  {
    if (d[j]<d[i])
    {
      tD=d[i];
      d[i]=d[j];
      d[j]=tD;
    }
  }
}
}

int dList::IsIn(double indbl)
{
int iRet=-1;
int i;
for (i=0;i<iNo;i++)
{
  if (d[i]==indbl)
  {
     iRet=i;
     break;
  }
}
return (iRet);
}


NEList::NEList()
{
Title="NULL";
iNo=0;
}

int NEList::Get(int iD)
{
int iRet=-1;
int i;
for (i=0;i<iNo;i++)
{
  if (ids[i]==iD)
  {
    iRet=iType[i];
    break;
  }
}
return (iRet);
}

void NEList::Add(int iP,int iT)
{
if (iNo<MAX_LITEMS)
{
  ids[iNo]=iP;
  iType[iNo]=iT;
  iNo++;
}
else
{
   outtext1("Error NEList items exceeded");
}

}



ObjList::ObjList()
{
iNo=0;
}

void ObjList::Add(G_Object* inItem)
{
if (iNo<MAX_GP_ITEMS)
{
  Objs[iNo] = inItem;
  iNo++;
}
}

void ObjList::AddEx(G_Object* inItem)
{
BOOL bIsIn;
bIsIn=IsIn(inItem);
if (bIsIn==FALSE)
{
  Objs[iNo] = inItem;
  iNo++;
}
}

BOOL ObjList::IsIn(G_Object* inItem)
{
int i;
BOOL bRet=FALSE;
for (i=0;i<iNo;i++)
{
  if (Objs[i]==inItem)
  {
    bRet=TRUE;
    break;
  }
}
return (bRet);
}

int ObjList::IsIn2(G_Object* inItem)
{
int i;
int iRet=-1;
for (i=0;i<iNo;i++)
{
  if (Objs[i]==inItem)
  {
    iRet=i;
    break;
  }
}
return (iRet);
}

void ObjList::Clear()
{
iNo=0;
}

ObjGp::ObjGp()
{
Title="";
iNo=0;
}



ObjGp::ObjGp(CString inTit)
{
Title=inTit;
iNo=0;
}

void ObjGp::Clear()
{
iNo=0;
}


void ObjGp::Add(G_Object* inItem)
{
if (IsIn(inItem)==-1)
{
  if (iNo<MAX_GP_ITEMS)
  {
    Objs[iNo] = inItem;
    iNo++;
  }
  else
  {
    outtext1("Group overflow");
  }
}
}

void ObjGp::Rem(G_Object* inItem)
{

int i;
for (i=0;i<iNo;i++)
{
  if (Objs[i] == inItem)
  {
    Objs[i] = Objs[iNo-1];
	iNo--;
	break;
  }
}
}

int ObjGp::IsIn(G_Object* inItem)
{

int i;
int iRet=-1;
for (i=0;i<iNo;i++)
{
  if (Objs[i] == inItem)
  {
    iRet=i;
	break;
  }
}
return (iRet);
}

// Create Shade Representation of object

IMPLEMENT_DYNAMIC( G_Object, CObject )


void G_Object::SetVisable(int iOnOff)
{
Visable = iOnOff;
}

void G_Object::SetSelectable(int iOnOff)
{
Selectable = iOnOff;
}

int G_Object::GetCol()
{
int irc;
if ((G_Colour>=0) && (G_Colour<=17))
{
  irc=G_Colour;
}
else
{
  irc=7;
}
return (G_Colour);
}

void G_Object::SetDrawn(int iOnOff)
{
Drawn = iOnOff;
}


G_Object* G_Object::GetObj(int iType,int iLab)
{

return (NULL);
}


int G_Object::isVisable()
{
return (Visable);
}

int G_Object::isDrawn()
{
return (Drawn);
}

int G_Object::isSelectable()
{
return (Selectable);
}

G_Object::G_Object()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
bDrawLab = FALSE;
pParent=NULL;
}

G_Object::~G_Object()
{

}

// Create Object
		
void G_Object::Create()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
pParent=NULL;
bDrawLab = FALSE;
}


C3dVector G_Object::MinPt(C3dVector inPt)
{
C3dVector vRet;
return vRet;
}


G_Object* G_Object::Copy(G_Object* parrent)
{
//G_Object* gret = new G_Object;
//gret->iObjType=iObjType;
//gret->G_label=G_label;
//gret->G_Colour=G_Colour;
//gret->Drawn = Drawn;
//gret->Selectable  = Selectable; 
//gret->Visable  = Visable;
return (NULL);
}


void G_Object::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    ar << iObjType;
    ar << G_label;
    ar << G_Colour;
    ar << Drawn;
    ar << Selectable; 
    ar << Visable;
	}
	else
	{
    ar >> iObjType;
    ar >> G_label;
    ar >> G_Colour;
    ar >> Drawn;
    ar >> Selectable; 
    ar >> Visable;
	}
}


void G_Object::Info()
{
  char S1[80];
  CString OutT;
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  OutT+=S1;
  outtext1(OutT); 
  
}

C3dVector G_Object::Get_Centroid()
{
C3dVector vRet;
vRet.Set(0,0,0);
return (vRet);
}

C3dVector G_Object::Get_Normal()
{
C3dVector vRet;
vRet.Set(0,0,1);
return (vRet);
}

void G_Object::Draw(CDC* pDC,int iDrawmode)
{
}

void G_Object::OglDraw(int iDspFlgs,double dS1,double dS2)
{
}

void G_Object::OglDrawW(int DspFlags,double dS1,double dS2)
{
}



void G_Object::Transform(C3dMatrix TMat)
{

}

void G_Object::Translate(C3dVector vIn)
{


}




void G_Object::Move(C3dVector vM)
{

}

G_Object* G_Object::OffSet(C3dVector vN,C3dVector vDir,double Dist)
{
return (NULL);
}










C3dVector G_Object::GetPt(double w)
{
C3dVector vR;
return (vR);
}

C3dVector G_Object::GetInPt()
{
C3dVector vR;
return (vR);
}


C3dVector G_Object::GetDir(double w)
{
C3dVector vR;
return (vR);
}

double G_Object::getLen()
{
return (0);
}

void G_Object::HighLight(CDC* pDC)
{
pDC->Ellipse(SelPt.x+5,SelPt.y+5,SelPt.x-5,SelPt.y-5);
}

void G_Object::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
C3dVector vC;
vC=Get_Centroid();
vC.SetToScr(pModMat,pScrTran);
SelPt=vC;
}

G_ObjectD G_Object::SelDist(CPoint InPT,Filter FIL)
{
G_ObjectD Ret;
double x,y,d;
x =  SelPt.x-InPT.x;
y =  SelPt.y-InPT.y;
d=(x*x+y*y);
Ret.Dist=d;
Ret.pObj=this;
return (Ret);
}

void G_Object::S_Box(CPoint P1,CPoint P2,ObjList* pSel)
{
if ((SelPt.x > P1.x) && 
	  (SelPt.x < P2.x) &&
    (SelPt.y > P1.y) &&
    (SelPt.y < P2.y))
{
	pSel->Add(this);
}
}

void G_Object::Colour(int iCol)
{
G_Colour = iCol;
}


void G_Object::RelTo(G_Object* pThis,ObjList* pList,int iType)
{
  if (pThis->pParent!=NULL)
  {
     if (pThis->pParent->iObjType==iType)
     {
        pList->AddEx(pThis->pParent);
     }
  }
}
//***********************************************

IMPLEMENT_DYNAMIC( Pt_Object, CObject )
// Create Object
Pt_Object::~Pt_Object()
{
 delete(Pt_Point);
 delete(DSP_Point);
 Pt_Point=NULL;
 DSP_Point=NULL;
}
		
void Pt_Object::Create(C3dVector InPt, int iLab,int i2,int i3, int iC,int iDef,int iOut,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 1;
G_Colour = iC;
G_label = iLab;
Pt_Point = new C3dVector(InPt.x,InPt.y,InPt.z);
DSP_Point = new C3dVector();
pParent=Parrent;
dof[0]=0;
dof[1]=0;
dof[2]=0;
dof[3]=0;
dof[4]=0;
dof[5]=0;
DefSys=iDef;
OutSys=iOut;
pResV=NULL;
pResD=NULL;
}

void Pt_Object::Info()
{
  char S1[80];
  sprintf_s(S1,"GRID %8i X %s Y %s Z %s DEFSYS %i OUTSYS %i",G_label,float8NAS(Pt_Point->x),float8NAS(Pt_Point->y),float8NAS(Pt_Point->z),DefSys,OutSys);
  outtext1(S1); 
}

C3dVector Pt_Object::MinPt(C3dVector inPt)
{
C3dVector vRet;
vRet.Set(Pt_Point->x,Pt_Point->y,Pt_Point->z);
return (vRet);
}


void Pt_Object::ExportUNV(FILE* pFile)
{
fprintf(pFile,"%10i%10i%10i%10i\n",G_label,1,1,G_Colour-150);
fprintf(pFile,"%25.16E%25.16E%25.16E\n",Pt_Point->x,Pt_Point->y,Pt_Point->z);
}

void Pt_Object::ExportNAS(FILE* pFile, CoordSys* pD)
{
   //New to handle the DEF system eventually
  if (G_label==3000039)
  {
    int kk;
    kk=0;
  }
  C3dVector pt(Pt_Point->x,Pt_Point->y,Pt_Point->z);
  if (pD!=NULL)
  {
    C3dMatrix A=pD->mOrientMat;
    A.Transpose();
    if (pD->CysType==1)
    {
      pt-=pD->Origin;
	    pt = A*pt;
    }
    else if (pD->CysType==2)
    {
      pt-=pD->Origin;
	    pt = A*pt;
      C3dVector pCyl;
      pCyl.x=sqrt(pt.x*pt.x+pt.y*pt.y);
      pCyl.y=atan2(pt.y,pt.x)*R2D;
      pCyl.z=pt.z;
      pt=pCyl;
    }
    else if (pD->CysType==3)
    {
      pt-=pD->Origin;
	    pt = A*pt;
      C3dVector pCyl;
      pCyl.x=sqrt(pt.x*pt.x+pt.y*pt.y+pt.z*pt.z);
      pCyl.y=acos(pt.z/pCyl.x)*R2D;
      pCyl.z=atan2(pt.y,pt.x)*R2D;
      pt=pCyl;
    }
  }
   fprintf(pFile,"%8s%8i%8i%8s%8s%8s%8i\n","GRID    ",G_label,DefSys,e8(pt.x),e8(pt.y),e8(pt.z),OutSys);
}

G_Object* Pt_Object::Copy(G_Object* Parrent)
{
Pt_Object* PtRet = new Pt_Object;
PtRet->Drawn = Drawn;
PtRet->Selectable  = Selectable; 
PtRet->Visable  = Visable;
PtRet->G_Colour = G_Colour;
PtRet->iObjType = iObjType;
PtRet->G_label = G_label;
PtRet->Pt_Point = new C3dVector(Pt_Point->x,Pt_Point->y,Pt_Point->z);
PtRet->DSP_Point = new C3dVector();
PtRet->OutSys = OutSys;
PtRet->DefSys = DefSys;
PtRet->pParent=Parrent;
pResV=NULL;
pResD=NULL;
return (PtRet);
}

void Pt_Object::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
	  ar<<DefSys;
    ar<<OutSys;
    ar<<Pt_Point->x;
    ar<<Pt_Point->y;
    ar<<Pt_Point->z;  
	}
	else
	{
    G_Object::Serialize(ar);
	  ar>>DefSys;
    ar>>OutSys;
    Pt_Point = new C3dVector();
    DSP_Point = new C3dVector();
    ar>>Pt_Point->x;
    ar>>Pt_Point->y;
    ar>>Pt_Point->z; 
    pResV=NULL;
    pResD=NULL;
	}
}





void Pt_Object::Clear()
{

}

C3dVector Pt_Object::GetCoords() 
{
C3dVector vRet;
vRet.Set(Pt_Point->x,Pt_Point->y,Pt_Point->z);
return (vRet);
}

C3dVector Pt_Object::Get_Centroid()
{
return (GetCoords());
}



// Draw Object line
void Pt_Object::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) DSP_Point->x-4,(int) DSP_Point->y+4);
pDC->LineTo((int) DSP_Point->x+4,(int) DSP_Point->y-4);
pDC->MoveTo((int) DSP_Point->x+4,(int) DSP_Point->y+4);
pDC->LineTo((int) DSP_Point->x-4,(int) DSP_Point->y-4);
pDC->MoveTo((int) DSP_Point->x+4,(int) DSP_Point->y);
pDC->LineTo((int) DSP_Point->x-5,(int) DSP_Point->y);
pDC->MoveTo((int) DSP_Point->x,(int) DSP_Point->y-4);
pDC->LineTo((int) DSP_Point->x,(int) DSP_Point->y+4);
//pDC->SetPixel(DSP_Point->x, DSP_Point->y+4, 255 );

//pDC->Ellipse(DSP_Point->x+3,DSP_Point->y+3,DSP_Point->x-3,DSP_Point->y-3);
}




GLubyte BmpND[22] = {0x04,0x00,0x44,0x40,0x24,0x80,0x15,0x00,0x0e,0x00,0xff,0xe0,0x0e,0x00,0x15,0x00,0x24,0x80,0x44,0x40,0x04,0x00};

void Pt_Object::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
double x;
double y;
double z;
double dS=0;
int ind;
C3dVector vD;
ME_Object* ME=(ME_Object*) this->pParent;
dS=ME->dScale;
ind=ME->iCVar;
if ((iDspFlgs & DSP_NODES)>0)
{
  x=Pt_Point->x;
  y=Pt_Point->y;
  z=Pt_Point->z;
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    if (pResD!=NULL)
    {
       vD=pResD->GetVec();
       x+=vD.x*dS;
       y+=vD.y*dS;
       z+=vD.z*dS;
    }
  }

	Selectable=1;
	glColor3fv(cols[GetCol()]);
  glPointSize(4.0f); 
	if ((iDspFlgs & DSP_NODES_ASK)>0)
	{
	  glBegin(GL_POINTS);
    glVertex3f((float) x,(float) y,(float) z);
    glEnd();   

	}
	else
	{
     glRasterPos3f ((float) x,(float) y,(float) z);
     glBitmap(11,11, 5.0, 5.0, 0.0, 0.0, BmpND);
	}

	if (bDrawLab==TRUE)
	{
	  sprintf_s(sLab,"N%i",G_label);
	  OglString(iDspFlgs,(float) x,(float) y,(float) z,&sLab[0]);
  }
  if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
  {
    sprintf_s(sLab,"%f",*pResV->GetAddress(ind));
    OglString(iDspFlgs,(float) x,(float) y,(float) z,&sLab[0]);
  }
}
else
{
   Selectable=0;
}
}

void Pt_Object::OglDraw(int iDspFlgs,double dS1,double dS2)
{
   OglDrawW(iDspFlgs,dS1,dS2);
}

void Pt_Object::Move(C3dVector vM)
{
Pt_Point->x +=vM.x;
Pt_Point->y +=vM.y;
Pt_Point->z +=vM.z;
}

void Pt_Object::Transform(C3dMatrix TMAt)
{
C3dVector R;
R.x =  TMAt.m_00 * Pt_Point->x +  TMAt.m_01 * Pt_Point->y +  TMAt.m_02 * Pt_Point->z +  TMAt.m_30;
R.y =  TMAt.m_10 * Pt_Point->x +  TMAt.m_11 * Pt_Point->y +  TMAt.m_12 * Pt_Point->z +  TMAt.m_31;
R.z =  TMAt.m_20 * Pt_Point->x +  TMAt.m_21 * Pt_Point->y +  TMAt.m_22 * Pt_Point->z +  TMAt.m_32;
Pt_Point->x =R.x;
Pt_Point->y =R.y;
Pt_Point->z =R.z;

}

void Pt_Object::Translate(C3dVector vIn)
{
Pt_Point->x +=vIn.x;
Pt_Point->y +=vIn.y;
Pt_Point->z +=vIn.z;
}



void Pt_Object::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{

C3dVector V;
C3dVector R;
G_Object::SetToScr(pModMat, pScrTran);
  
R.x = Pt_Point->x;
R.y = Pt_Point->y;
R.z = Pt_Point->z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;

R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;


DSP_Point->x = R.x;
DSP_Point->y = R.y;
DSP_Point->z = 0;
}

void Pt_Object::SetTo(C3dVector cInVect)
{
Pt_Point->x = cInVect.x;
Pt_Point->y = cInVect.y;
Pt_Point->z = cInVect.z;
}

cFace::cFace()
{
iColor=-1;
NoVert=0;
vVerts[0]=NULL;
vVerts[1]=NULL;
vVerts[2]=NULL;
vVerts[3]=NULL;
pParent=NULL;
before=NULL;
}

cFace::~cFace()
{
iColor=-1;
NoVert=0;
vVerts[0]=NULL;
vVerts[1]=NULL;
vVerts[2]=NULL;
vVerts[3]=NULL;
pParent=NULL;
before=NULL;
}

BOOL cFace::isSame(cFace* inFace)
{
BOOL brc=FALSE;
int i,j,iC;
iC=0;
if (NoVert==inFace->NoVert)
{
  for (i=0;i<NoVert;i++)
  {
    for (j=0;j<NoVert;j++)
    {
      if (vVerts[i]==inFace->vVerts[j])
	  {
        iC++;
	  }
    }
  }
  if (iC==NoVert)
  {
    brc=TRUE;
  }
}
return (brc);
}

void cFace::OglDraw(int iDspFlgs)
{
C3dVector v1;
C3dVector v2;
C3dVector Vn;
if (NoVert==3)
{
  v1.x = vVerts[1]->Pt_Point->x-vVerts[0]->Pt_Point->x;
  v1.y = vVerts[1]->Pt_Point->y-vVerts[0]->Pt_Point->y;
  v1.z = vVerts[1]->Pt_Point->z-vVerts[0]->Pt_Point->z;

  v2.x = vVerts[2]->Pt_Point->x-vVerts[1]->Pt_Point->x;
  v2.y = vVerts[2]->Pt_Point->y-vVerts[1]->Pt_Point->y;
  v2.z = vVerts[2]->Pt_Point->z-vVerts[1]->Pt_Point->z;
  Vn = v1.Cross(v2);

  Vn.Normalize();
  glBegin(GL_POLYGON);
  glColor3fv(cols[iColor]);
  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
  glVertex3f((float) vVerts[0]->Pt_Point->x,(float) vVerts[0]->Pt_Point->y,(float) vVerts[0]->Pt_Point->z);
  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
  glVertex3f((float) vVerts[1]->Pt_Point->x,(float) vVerts[1]->Pt_Point->y,(float) vVerts[1]->Pt_Point->z);
  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
  glVertex3f((float) vVerts[2]->Pt_Point->x,(float) vVerts[2]->Pt_Point->y,(float) vVerts[2]->Pt_Point->z);
  glEnd();
}
else if (NoVert==4)
{
  v1.x = vVerts[1]->Pt_Point->x-vVerts[0]->Pt_Point->x;
  v1.y = vVerts[1]->Pt_Point->y-vVerts[0]->Pt_Point->y;
  v1.z = vVerts[1]->Pt_Point->z-vVerts[0]->Pt_Point->z;
  v2.x = vVerts[2]->Pt_Point->x-vVerts[1]->Pt_Point->x;
  v2.y = vVerts[2]->Pt_Point->y-vVerts[1]->Pt_Point->y;
  v2.z = vVerts[2]->Pt_Point->z-vVerts[1]->Pt_Point->z;
  Vn = v1.Cross(v2);
  Vn.Normalize();
  glBegin(GL_POLYGON);
  glColor3fv(cols[iColor]);
  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
  glVertex3f((float) vVerts[0]->Pt_Point->x,(float) vVerts[0]->Pt_Point->y,(float) vVerts[0]->Pt_Point->z);
  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
  glVertex3f((float) vVerts[1]->Pt_Point->x,(float) vVerts[1]->Pt_Point->y,(float) vVerts[1]->Pt_Point->z);
  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
  glVertex3f((float) vVerts[2]->Pt_Point->x,(float) vVerts[2]->Pt_Point->y,(float) vVerts[2]->Pt_Point->z);
  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
  glVertex3f((float) vVerts[3]->Pt_Point->x,(float) vVerts[3]->Pt_Point->y,(float) vVerts[3]->Pt_Point->z);
  glEnd();
}
}


cLink::cLink()
{
iColor=-1;
vVerts[0]=NULL;
vVerts[1]=NULL;
pParent=NULL;
before=NULL;
}

cLink::~cLink()
{
iColor=-1;
vVerts[0]=NULL;
vVerts[1]=NULL;
pParent=NULL;
before=NULL;
}

BOOL cLink::isSame(cLink* inLink)
{
BOOL brc=FALSE;
if ((vVerts[0]==inLink->vVerts[0]) &&
	(vVerts[1]==inLink->vVerts[1]))
{
  brc=TRUE;
}
else if ((vVerts[1]==inLink->vVerts[0]) &&
	     (vVerts[0]==inLink->vVerts[1]))
{
  brc=TRUE;
}
return (brc);
}

void cLink::OglDrawW()
{
glColor3fv(cols[iColor]);
glBegin(GL_LINES);
glVertex3f((float) vVerts[0]->Pt_Point->x,(float) vVerts[0]->Pt_Point->y,(float) vVerts[0]->Pt_Point->z);
glVertex3f((float) vVerts[1]->Pt_Point->x,(float) vVerts[1]->Pt_Point->y,(float) vVerts[1]->Pt_Point->z);
glEnd();
}


cFaceList::cFaceList()
{
Face=NULL;
Last=NULL;
}

cFaceList::~cFaceList()
{
cFace* pNext;
cFace* p;
p=Face;
while (p!=NULL)
{ 
  pNext=p->pParent;
  delete (p);
  p=pNext;
}
}

cFace* cFaceList::IsIn(cFace* inFace)
{
cFace* pRet=NULL;
cFace* pNext;
pNext=Face;
while (pNext!=NULL)
{
  if (pNext->isSame(inFace)==TRUE)
  {
    pRet=pNext;
	break;
  }
  pNext=pNext->pParent;
}
return (pRet);
}

void cFaceList::Add(cFace* inFace)
{

cFace* ind;
ind=IsIn(inFace);
if (ind==NULL)
{
  if (Face==NULL)
  {
    Face=inFace;
	Face->before=NULL;
    Last=inFace;
	iNo++;
  }
  else
  {
    Last->pParent=inFace;
    Last->pParent->before=Last;
    Last=inFace;
    Last->pParent=NULL;
    iNo++;
  }
}
else
{
  Remove(ind);
  delete(inFace);
}
}

void cFaceList::Remove(cFace* inFace)
{
cFace* ind;
ind=inFace;
if (ind!=NULL)
{
  if ((ind->pParent!=NULL) && (ind->before!=NULL))
  {
    ind->before->pParent=ind->pParent;
    ind->pParent->before=ind->before;
	delete(ind);
    iNo--;
  }
  else if (ind->pParent==NULL) 
  {
	Last=ind->before;
    Last->pParent=NULL;
	delete(ind);
    iNo--;
  }
  else if (ind->before==NULL) 
  {
    Face=ind->pParent;
	Face->before=NULL;
	delete(ind);
    iNo--;
  }
}
}

void cFaceList::OglDraw(int iDspFlgs)
{
cFace* pNext;
pNext=Face;
while (pNext!=NULL)
{
  pNext->OglDraw(iDspFlgs);
  pNext=pNext->pParent;
}
}


cLinkList::cLinkList()
{
iNo=0;
Link=NULL;
}

cLinkList::~cLinkList()
{
cLink* pNext;
cLink* p;
p=Link;
while (p!=NULL)
{ 
  pNext=p->pParent;
  delete (p);
  p=pNext;
}
}

cLink* cLinkList::IsIn(cLink* inLink)
{
cLink* pRet=NULL;
cLink* pNext;
pNext=Link;
while (pNext!=NULL)
{
  if (pNext->isSame(inLink)==TRUE)
  {
    pRet=pNext;
	break;
  }
  pNext=pNext->pParent;
}
return (pRet);
}

void cLinkList::Add(cLink* inLink)
{
cLink* ind;
ind=IsIn(inLink);
if (ind==NULL)
{
  if (Link==NULL)
  {
    Link=inLink;
	Link->before=NULL;
    Last=inLink;
  }
  Last->pParent=inLink;
  Last->pParent->before=Last;
  Last=inLink;
  Last->pParent=NULL;
  iNo++;
}
else
{
  delete(inLink);
}
}

void cLinkList::Remove(cLink* inLink)
{
cLink* ind;
ind=inLink;
if (ind==NULL)
{
  Last->pParent=inLink;
  Last->pParent->before=Last;
  Last=inLink;
  iNo++;
}
else
{
  if ((ind->pParent!=NULL) && (ind->before!=NULL))
  {
    ind->before->pParent=ind->pParent;
    ind->pParent->before=ind->before;
	delete(ind);
    iNo--;
  }
  else if (ind->pParent==NULL) 
  {
	Last=ind->before;
    Last->pParent=NULL;
	delete(ind);
    iNo--;
  }
  else if (ind->before==NULL) 
  {
    Link=ind->pParent;
	delete(ind);
    iNo--;
  }
}
}

void cLinkList::OglDrawW(int iDspFlgs)
{
cLink* pNext;
pNext=Link;
while (pNext!=NULL)
{
  pNext->OglDrawW();
  pNext=pNext->pParent;
}
}




IMPLEMENT_DYNAMIC( Line_Object, CObject )


Line_Object::~Line_Object()
{
delete (pVertex1);
delete (pVertex2);
}

void Line_Object::Create(C3dVector* pInVertex1,C3dVector* pInVertex2, int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
int i=0;
iObjType = 2;
G_label = iLab;
C3dVector InVect;
InVect.x = pInVertex1->x;
InVect.y = pInVertex1->y;
InVect.z = pInVertex1->z;
pVertex1 = new CvPt_Object;
pVertex1->Create(InVect,0,0,0,0,11,this);
pVertex1->SetVisable(0);
InVect.x = pInVertex2->x;
InVect.y = pInVertex2->y;
InVect.z = pInVertex2->z;
pVertex2 = new CvPt_Object;
pVertex2->Create(InVect,0,0,0,0,11,this);
pVertex2->SetVisable(0);
pParent=Parrent;
}

void Line_Object::SetP1(double dx,double dy,double dz)
{
pVertex1->Pt_Point->x=dx;
pVertex1->Pt_Point->y=dy;
pVertex1->Pt_Point->z=dz;
}

void Line_Object::SetP2(double dx,double dy,double dz)
{
pVertex2->Pt_Point->x=dx;
pVertex2->Pt_Point->y=dy;
pVertex2->Pt_Point->z=dz;
}

C3dVector Line_Object::MinPt(C3dVector inPt)
{
C3dVector vRet;
C3dVector v1;
C3dVector v2;
C3dVector P1;
C3dVector P2;
double dm;
double dDot;
P1.Set(pVertex1->Pt_Point->x,
       pVertex1->Pt_Point->y,
       pVertex1->Pt_Point->z);
P2.Set(pVertex2->Pt_Point->x,
       pVertex2->Pt_Point->y,
       pVertex2->Pt_Point->z);
v1=P2;
v1-=P1;
v2=inPt;
v2-=P1;
dm=v2.Mag();
v1.Normalize();
v2.Normalize();
dDot=v2.Dot(v1);
dm=dm*dDot;
vRet=P1+v1*dm;
return vRet;
}




void Line_Object::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
    pVertex1->Serialize(ar);
    pVertex2->Serialize(ar); 
	}
	else
	{
    G_Object::Serialize(ar);
    pVertex1= new CvPt_Object;
    pVertex2= new CvPt_Object;
    pVertex1->Serialize(ar);
    pVertex2->Serialize(ar);
	}
}

C3dVector Line_Object::Get_Centroid()
{
return (GetPt(0.5));
}

G_Object* Line_Object::Copy(G_Object* parrent)
{
Line_Object* rLn = new Line_Object;
rLn->Drawn = Drawn;
rLn->Selectable  = Selectable; 
rLn->Visable  = Visable;
rLn->G_Colour = G_Colour;
rLn->iObjType = iObjType;
rLn->G_label = G_label;
rLn->pVertex1 = (CvPt_Object *) pVertex1->Copy(rLn);
rLn->pVertex2 = (CvPt_Object *) pVertex2->Copy(rLn);
pParent = parrent;
return  (rLn);
}

void Line_Object::Info()
{
  char S1[80];
  CString OutT;
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  OutT+=S1;
  outtext1("LINE OBJECT");
  outtext1(OutT); 
  outtext1("    ****");
}

CvPt_Object* Line_Object::GetTEnd()
{
if (dUsel < 0.5)
  {
  return (pVertex1);
  }
else
  {
  return (pVertex2);
  }
}




void Line_Object::Draw(CDC* pDC,int iDrawmode)
{
pDC->MoveTo((int) pVertex1->DSP_Point->x,(int) pVertex1->DSP_Point->y);
pDC->LineTo((int) pVertex2->DSP_Point->x,(int) pVertex2->DSP_Point->y);
}

void Line_Object::OglDraw(int iDspFlgs,double dS1,double dS2)
{
glColor3fv(cols[GetCol()]);
glBegin(GL_LINES);
glVertex3f((float) pVertex1->Pt_Point->x,(float) pVertex1->Pt_Point->y,(float) pVertex1->Pt_Point->z);
glVertex3f((float) pVertex2->Pt_Point->x,(float) pVertex2->Pt_Point->y,(float) pVertex2->Pt_Point->z);
glEnd();
}

void Line_Object::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
glColor3fv(cols[GetCol()]);
glBegin(GL_LINES);
glVertex3f((float) pVertex1->Pt_Point->x,(float) pVertex1->Pt_Point->y,(float) pVertex1->Pt_Point->z);
glVertex3f((float) pVertex2->Pt_Point->x,(float) pVertex2->Pt_Point->y,(float) pVertex2->Pt_Point->z);
glEnd();
}

void Line_Object::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
pVertex1->SetToScr(pModMat, pScrTran);
pVertex2->SetToScr(pModMat, pScrTran);
}

void Line_Object::HighLight(CDC* pDC)
{
pDC->MoveTo((int) pVertex1->DSP_Point->x,(int) pVertex1->DSP_Point->y);
pDC->LineTo((int) pVertex2->DSP_Point->x,(int) pVertex2->DSP_Point->y);
}

void Line_Object::Transform(C3dMatrix TMat)
{
pVertex1->Transform(TMat);
pVertex2->Transform(TMat);
}

G_ObjectD Line_Object::SelDist(CPoint InPT,Filter FIL)
{
CPoint cPt;
G_ObjectD Ret;
double MinDist = 100000000000000.0;
double dDist = 0;
double fred;
int iCnt1;

  for (iCnt1 = 5; iCnt1 < 16; iCnt1++)
     {
	 fred = iCnt1*0.05;
     cPt.x = (long) (fred*(pVertex2->DSP_Point->x-pVertex1->DSP_Point->x)+pVertex1->DSP_Point->x)-InPT.x;
     cPt.y = (long) (fred*(pVertex2->DSP_Point->y-pVertex1->DSP_Point->y)+pVertex1->DSP_Point->y)-InPT.y;
     dDist = cPt.x*cPt.x+cPt.y*cPt.y;

	 if (dDist < MinDist)
	   {
       MinDist = dDist;
	   dUsel = fred;
	   }
     //pDC->Ellipse(ThePoint.DSP_Point->x+5,ThePoint.DSP_Point->y+5,ThePoint.DSP_Point->x-5,ThePoint.DSP_Point->y-5);
     }
Ret.Dist=MinDist;
Ret.pObj=this;
return (Ret);
}

C3dVector Line_Object::GetPt(double dU)
{
C3dVector vRet;
double dX,dY,dZ;

dX = (pVertex2->Pt_Point->x-pVertex1->Pt_Point->x)*dU;
dY = (pVertex2->Pt_Point->y-pVertex1->Pt_Point->y)*dU;
dZ = (pVertex2->Pt_Point->z-pVertex1->Pt_Point->z)*dU;
vRet.x = pVertex1->Pt_Point->x + dX;
vRet.y = pVertex1->Pt_Point->y + dY;
vRet.z = pVertex1->Pt_Point->z + dZ;
return (vRet);
}



C3dVector Line_Object::GetDir(double w)
{
C3dVector DirA;
C3dVector DirB;
DirA = this->GetPt(0.0);
DirB = this->GetPt(1.0);
DirB-=DirA;
DirB.Normalize();
return (DirB);
}


double Line_Object::MinDist(C3dVector vInPt)
{
C3dVector vRet;
double dX,dY,dZ,dU;
int iCnt1;
double MinDist = 100000000000000.0;
double dDist = 0;

for (iCnt1 = 1; iCnt1 < 1000; iCnt1++)
{
dU = iCnt1*0.001;
dX = (pVertex2->Pt_Point->x-pVertex1->Pt_Point->x)*dU;
dY = (pVertex2->Pt_Point->y-pVertex1->Pt_Point->y)*dU;
dZ = (pVertex2->Pt_Point->z-pVertex1->Pt_Point->z)*dU;
vRet.x = pVertex1->Pt_Point->x + dX;
vRet.y = pVertex1->Pt_Point->y + dY;
vRet.z = pVertex1->Pt_Point->z + dZ;
dDist = pow((pow((vRet.x - vInPt.x),2)+pow((vRet.y - vInPt.y),2)+pow((vRet.z - vInPt.z),2)),0.5);
if (dDist < MinDist)
  {
  MinDist = dDist;
  }
}
return (MinDist);
}





double Line_Object::getLen()
{
double dRet=0;
int i;
int iIncs=1;
double dStp;
double w;
C3dVector p1;
C3dVector p2;

dStp = 1/iIncs;
w=0;
p1=GetPt(w);
for (i=0;i<iIncs;i++)
{
  w+=dStp;
  p2=GetPt(w);
  dRet+=p2.Dist(p1);
  p1=p2;
}
return (dRet);
}



IMPLEMENT_DYNAMIC(Curve, CObject )

void Curve::Draw(CDC* pDC,int iDrawmode)
{
  ContrPolyW::Draw(pDC,iDrawmode,0,1);
}

void Curve::OglDraw(int iDspFlgs,double dS1,double dS2)
{
ContrPolyW::OglDraw(0.0,1.0);
}

void Curve::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
ContrPolyW::OglDrawW(0.0,1.0);
}


void Curve::HighLight(CDC* pDC)
{
  ContrPolyW::Draw(pDC,4,0,1);
}

IMPLEMENT_DYNAMIC( ContrPolyW, CObject )


ContrPolyW::ContrPolyW()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
iNoVerts = 0;
G_label = -1;
iObjType = 6;

}


    // CvPt_Object* pVertex[20];
void ContrPolyW::Create(int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
iNoVerts = 0;
G_label = iLab;
iObjType = 6;
pParent=Parrent;
}

C3dVector ContrPolyW::Get_Centroid()
{
return (GetPt(0.5));
}

void ContrPolyW::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
    ar << iNoVerts;
	  for (i=0;i<iNoVerts;i++)
    {
      ar << pCVertex[i]->xw;
      ar << pCVertex[i]->yw;
      ar << pCVertex[i]->zw;
      ar << pCVertex[i]->w;
    }
	}
	else
	{
    G_Object::Serialize(ar);
    ar >> iNoVerts;
	  for (i=0;i<iNoVerts;i++)
    {
      pCVertex [i] = new C4dVector();
      ar >> pCVertex[i]->xw;
      ar >> pCVertex[i]->yw;
      ar >> pCVertex[i]->zw;
      ar >> pCVertex[i]->w;
    }
	}
}

G_Object* ContrPolyW::Copy(G_Object* parrent)
{
int i;
ContrPolyW* cPoly = new ContrPolyW;
cPoly->Drawn = Drawn;
cPoly->Selectable  = Selectable; 
cPoly->Visable  = Visable;
cPoly->G_Colour = G_Colour;
cPoly->iObjType = iObjType;
cPoly->G_label = G_label;
cPoly->iNoVerts = iNoVerts;
for (i=0;i<iNoVerts;i++)
{
  cPoly->pCVertex [i] = new C4dVector();
  cPoly->pCVertex [i]->xw = pCVertex[i]->xw;
  cPoly->pCVertex [i]->yw = pCVertex[i]->yw;
  cPoly->pCVertex [i]->zw = pCVertex[i]->zw;
  cPoly->pCVertex [i]->w = pCVertex[i]->w;
}
cPoly->pParent = parrent;
return (cPoly);
}

void ContrPolyW::AddVert(C3dVector* pInVertex1, double dWght)
{
if (dWght == 0)
  {
  dWght = 1;
  }
if (iNoVerts < 20)
  {
  pCVertex [iNoVerts] = new C4dVector();
  pCVertex [iNoVerts]->xw = pInVertex1->x*dWght;
  pCVertex [iNoVerts]->yw = pInVertex1->y*dWght;
  pCVertex [iNoVerts]->zw = pInVertex1->z*dWght;
  pCVertex [iNoVerts]->w = dWght;
  iNoVerts++;
  }
}

void ContrPolyW::CPolyRot(double dAng)
{
int i;
C3dVector vT1,a,b;

for (i = 0; i < iNoVerts; i++)
   {
   vT1.x = pCVertex [i]->xw;
   vT1.y = pCVertex [i]->yw;
   vT1.z = pCVertex [i]->zw;
   vT1.Rotate(a,b,dAng);
   pCVertex [i]->xw = vT1.x;
   pCVertex [i]->yw = vT1.y;
   pCVertex [i]->zw = vT1.z;
   }
}

void ContrPolyW::CWeight (double dW)
{
int i;
C3dVector vT1,a,b;

for (i = 0; i < iNoVerts; i++)
   {
   vT1.x = pCVertex [i]->xw / pCVertex [i]->w;
   vT1.y = pCVertex [i]->yw / pCVertex [i]->w;
   vT1.z = pCVertex [i]->zw / pCVertex [i]->w;
   pCVertex [i]->xw = vT1.x * dW;
   pCVertex [i]->yw = vT1.y * dW;
   pCVertex [i]->zw = vT1.z * dW;
   pCVertex [i]->w = dW;

   }

}


void ContrPolyW::AddVertW(C4dVector pInVertex1)
{
if (iNoVerts < 20)
  {
  pCVertex [iNoVerts] = new C4dVector();
  pCVertex [iNoVerts]->xw = pInVertex1.xw;
  pCVertex [iNoVerts]->yw = pInVertex1.yw;
  pCVertex [iNoVerts]->zw = pInVertex1.zw;
  pCVertex [iNoVerts]->w = pInVertex1.w;
  iNoVerts++;
  }
}
void ContrPolyW::Set2(ContrPolyW* vS4)
{
int i;

for  (i = 0; i < vS4->iNoVerts; i++)
  {
  AddVert(&vS4->pCVertex[i]->GetPoint(),vS4->pCVertex[i]->GetWght());
  }
}

void ContrPolyW::Translate (C3dVector vTVect)
{
int i;

for (i = 0; i < iNoVerts; i++)
   {
   pCVertex [i]->Translate(vTVect);
   }
}


void ContrPolyW::Clear()
{
int i;
for (i = 0; i<iNoVerts; i++)
   {
   delete(pCVertex[i]);
   }
iNoVerts = 0;
}


int ContrPolyW::GetOrder()
{

return (iNoVerts - 2);
}


C4dVector ContrPolyW::deCastelJau1(double u)
{

C4dVector Q[20]; 
int i;
int k;

for (i=0;i<=(iNoVerts-1);i++)
  {
  Q[i].xw= pCVertex[i]->xw;
  Q[i].yw= pCVertex[i]->yw;
  Q[i].zw= pCVertex[i]->zw;
  Q[i].w= pCVertex[i]->w;
  }
for (k=1;k<=(iNoVerts-1);k++)
  {
  for (i=0;i<=((iNoVerts-1)-k);i++)
    {
    Q[i] =Q[i]*(1.0-u)+Q[i+1]*u;
	//Q[i].x=(1.0-u)*Q[i].x+u*Q[i+1].x;
	//Q[i].y=(1.0-u)*Q[i].y+u*Q[i+1].y;
	//Q[i].z=(1.0-u)*Q[i].z+u*Q[i+1].z;
    }
  }

C4dVector vRetVect;
vRetVect.xw = Q[0].xw;
vRetVect.yw = Q[0].yw;
vRetVect.zw = Q[0].zw;
vRetVect.w = Q[0].w;

return (vRetVect);
}

  
void ContrPolyW::Draw(CDC* pDC,int iDrawmode,
                      double sw,double ew)
{
const double dInc = 0.01;
double w;

C3dVector pt;
pt=GetPt(sw);
Pt_Object* ThePoint = new Pt_Object;
ThePoint->Create(pt,1,0,0,11,0,0,NULL);
ThePoint->Pt_Point->x = pt.x; 
ThePoint->Pt_Point->y = pt.y;
ThePoint->Pt_Point->z = pt.z;
ThePoint->SetToScr(pModZ,pScrZ);
pDC->MoveTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);
w=sw;

do
{
  w=w+dInc;
  if (w>ew)
  {
    w = ew;
  }
  pt=GetPt(w);
  ThePoint->Pt_Point->x = pt.x; 
  ThePoint->Pt_Point->y = pt.y;
  ThePoint->Pt_Point->z = pt.z;
  ThePoint->SetToScr(pModZ,pScrZ);
  pDC->LineTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);  
}
while (w<ew);
delete(ThePoint);
}


void ContrPolyW::OglDraw(double sw,double ew)
{
GLfloat* ctrlpts;
int iu;
int icu;
int iInd = 0;
iu = iNoVerts;


ctrlpts = (GLfloat*) malloc(iu*4*sizeof(GLfloat));
for (icu = 0;icu < iu;icu++)
{
  ctrlpts[iInd]   = (float) pCVertex[icu]->xw;
  ctrlpts[iInd+1] = (float) pCVertex[icu]->yw;
  ctrlpts[iInd+2] = (float) pCVertex[icu]->zw;
  ctrlpts[iInd+3] = (float) pCVertex[icu]->w;
  iInd = iInd+4;
}  

glEnable(GL_MAP1_VERTEX_4);
glMap1f(GL_MAP1_VERTEX_4,0.0f,1.0f,4,iu,ctrlpts);
//glEnable(GL_MAP1_VERTEX_4);
glMapGrid1f(20,(float) sw,(float) ew);
glEvalMesh1(GL_LINE,0,20);
//glFlush();
free(ctrlpts);
}

void ContrPolyW::OglDrawW(double sw,double ew)
{
OglDraw(sw,ew);
}


void ContrPolyW::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
//int iCnt;
//for (iCnt=0;iCnt<iNoVerts;iCnt++)
//    {
//    pVertex[iCnt]->SetToScr(pScrTran);
//    }
pModZ = pModMat;
pScrZ = pScrTran;
}

void ContrPolyW::Transform(C3dMatrix TMat)
{
int i;
for (i=0;i<iNoVerts;i++)
{
  pCVertex[i]->Transform(TMat);
}
}


void ContrPolyW::HighLight(CDC* pDC,double sw,double ew)
{
Draw(pDC,4,sw,ew);
}

G_ObjectD ContrPolyW::SelDist(CPoint InPT,Filter FIL)
{
int iCnt1;
G_ObjectD Ret;
double MinDist = 1e36;
double dDist = 0;
double fred;
C3dVector vDrawPt;
C4dVector vWpt;
Pt_Object ThePoint;
ThePoint.Create(vDrawPt,0,0,0,11,0,0,NULL);
for (iCnt1 = 1; iCnt1 < 21; iCnt1++)
{
	fred = iCnt1*0.05;
  //vDrawPt = GetParaPoint(fred);	 
	vWpt = deCastelJau1 (fred);
	ThePoint.Pt_Point->x = vWpt.xw/vWpt.w;
    ThePoint.Pt_Point->y = vWpt.yw/vWpt.w;
    ThePoint.Pt_Point->z = vWpt.zw/vWpt.w;
	ThePoint.SetToScr(pModZ,pScrZ);
    dDist = pow((ThePoint.DSP_Point->x-InPT.x),2)+pow((ThePoint.DSP_Point->y-InPT.y),2);
	if (dDist < MinDist)
	{
      MinDist = dDist;
	}
  //pDC->Ellipse(ThePoint.DSP_Point->x+5,ThePoint.DSP_Point->y+5,ThePoint.DSP_Point->x-5,ThePoint.DSP_Point->y-5);
}
ThePoint.Clear();
Ret.Dist=MinDist;
Ret.pObj=this;
return (Ret);
}


C3dVector ContrPolyW::GetPt(double w)
{
C3dVector vR;
C4dVector vWpt;
if (iNoVerts > 2)
  {
	 vWpt = deCastelJau1 (w);
	 vR.x = vWpt.xw/vWpt.w;
     vR.y = vWpt.yw/vWpt.w;
     vR.z = vWpt.zw/vWpt.w;     
  }
return (vR);
}


C3dVector ContrPolyW::GetDir(double w)
{
C3dVector DirA;
C3dVector DirB;
if (w < 0.99999)
{
  DirA = this->GetPt(w);
  DirB = this->GetPt(w+0.00001);
}
else
{
  DirA = this->GetPt(w-0.00001);
  DirB = this->GetPt(w);
}
DirB-=DirA;
DirB.Normalize();
return (DirB);
}











IMPLEMENT_DYNAMIC(Circ1, CObject )
//	 int iNoVerts;
  //   CvPt_Object* pVertex[8]; //control polygon
//	 double dRadius;
//	 C3dMatrix* pScrZ;


void Circ1::Create(C3dVector vN,C3dVector vC,double dRad,int iLab,G_Object* Parrent)
{
dS=0;
dE=1;
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 5;
dRadius = dRad;
C3dVector Pt;
pParent=Parrent;
vNorm=new C3dVector(0,0,1);
vCent=new C3dVector(0,0,0);

pSegs[0] = new ContrPolyW();
pSegs[0]->Create(iLab,this);
Pt.x=dRadius;Pt.y=0;Pt.z=0;
pSegs[0]->AddVert(&Pt,1);
Pt.x=dRadius;Pt.y=dRadius;Pt.z=0;
pSegs[0]->AddVert(&Pt,1);
Pt.x=0;Pt.y=dRadius;Pt.z=0;
pSegs[0]->AddVert(&Pt,2);

pSegs[1] = new ContrPolyW();
pSegs[1]->Create(iLab,this);
pSegs[1]->AddVert(&Pt,1);
Pt.x=-dRadius;Pt.y=dRadius;Pt.z=0;
pSegs[1]->AddVert(&Pt,1);
Pt.x=-dRadius;Pt.y=0;Pt.z=0;
pSegs[1]->AddVert(&Pt,2);

pSegs[2] = new ContrPolyW();
pSegs[2]->Create(iLab,this);
pSegs[2]->AddVert(&Pt,1);
Pt.x=-dRadius;Pt.y=-dRadius;Pt.z=0;
pSegs[2]->AddVert(&Pt,1);
Pt.x=0;Pt.y=-dRadius;Pt.z=0;
pSegs[2]->AddVert(&Pt,2);

pSegs[3] = new ContrPolyW();
pSegs[3]->Create(iLab,this);
pSegs[3]->AddVert(&Pt,1);
Pt.x=dRadius;Pt.y=-dRadius;Pt.z=0;
pSegs[3]->AddVert(&Pt,1);
Pt.x=dRadius;Pt.y=0;Pt.z=0;
pSegs[3]->AddVert(&Pt,2);
C3dMatrix RMat;
RMat=RMat.CalcTran(vN);
C3dMatrix TMat;
this->Transform(RMat);
TMat.Translate(vC.x,vC.y,vC.z);
this->Transform(TMat);
}


void Circ1::Reverse()
{
C4dVector* p[12];
vNorm->x = -vNorm->x;
vNorm->y = -vNorm->y;
vNorm->z = -vNorm->z;
p[0] = pSegs[0]->pCVertex[0];
p[1] = pSegs[0]->pCVertex[1];
p[2] = pSegs[0]->pCVertex[2];

p[3] = pSegs[1]->pCVertex[0];
p[4] = pSegs[1]->pCVertex[1];
p[5] = pSegs[1]->pCVertex[2];

p[6] = pSegs[2]->pCVertex[0];
p[7] = pSegs[2]->pCVertex[1];
p[8] = pSegs[2]->pCVertex[2];

p[9] = pSegs[3]->pCVertex[0];
p[10] = pSegs[3]->pCVertex[1];
p[11] = pSegs[3]->pCVertex[2];

pSegs[0]->pCVertex[0] = p[11];
pSegs[0]->pCVertex[1] = p[10];
pSegs[0]->pCVertex[2] = p[9];

pSegs[1]->pCVertex[0] = p[8];
pSegs[1]->pCVertex[1] = p[7];
pSegs[1]->pCVertex[2] = p[6];

pSegs[2]->pCVertex[0] = p[5];
pSegs[2]->pCVertex[1] = p[4];
pSegs[2]->pCVertex[2] = p[3];

pSegs[3]->pCVertex[0] = p[2];
pSegs[3]->pCVertex[1] = p[1];
pSegs[3]->pCVertex[2] = p[0];


}


void Circ1::Info()
{
  char S1[80];
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  outtext1("CIRCLE OBJECT");
  outtext1(S1); 
  sprintf_s(S1,"%s%f","Radius : ",dRadius);
  outtext1(S1); 
  sprintf_s(S1,"%s%f%s%f%s%f","Centre : ",vCent->x,",",vCent->y,",",vCent->z);
  outtext1(S1); 
  sprintf_s(S1,"%s%f%s%f%s%f","Normal : ",vNorm->x,",",vNorm->y,",",vNorm->z);
  outtext1(S1);
  outtext1("    ****");
}



void Circ1::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
    ar<<dRadius;
	ar<<dS;
	ar<<dE;
    ar << vNorm->x;
    ar << vNorm->y;
    ar << vNorm->z;
    ar << vCent->x;
    ar << vCent->y;
    ar << vCent->z;
    pSegs[0]->Serialize(ar);
    pSegs[1]->Serialize(ar);
    pSegs[2]->Serialize(ar);
    pSegs[3]->Serialize(ar);
	}
	else
	{
    G_Object::Serialize(ar);
    ar>>dRadius;
	ar>>dS;
	ar>>dE;
    vNorm=new C3dVector(0,0,1);
    vCent=new C3dVector(0,0,0);
    ar >> vNorm->x;
    ar >> vNorm->y;
    ar >> vNorm->z;
    ar >> vCent->x;
    ar >> vCent->y;
    ar >> vCent->z;
    pSegs[0] = new ContrPolyW();
    pSegs[1] = new ContrPolyW();
    pSegs[2] = new ContrPolyW();
    pSegs[3] = new ContrPolyW();
    pSegs[0]->Serialize(ar);
    pSegs[1]->Serialize(ar);
    pSegs[2]->Serialize(ar);
    pSegs[3]->Serialize(ar);
	}
}

G_Object* Circ1::Copy(G_Object* Parrent)
{
Circ1* rCir = new Circ1;
rCir->dS=dS;
rCir->dE=dE;
rCir->Drawn = Drawn;
rCir->Selectable  = Selectable; 
rCir->Visable  = Visable;
rCir->G_Colour = G_Colour;
rCir->iObjType = iObjType;
rCir->G_label = G_label;
rCir-> pModZ = pModZ;
rCir-> pScrZ = pScrZ;
rCir->dRadius=dRadius;
rCir->vNorm=new C3dVector(0,0,1);
rCir->vCent=new C3dVector(0,0,0);
rCir->vNorm->x=vNorm->x;
rCir->vNorm->y=vNorm->y;
rCir->vNorm->z=vNorm->z;
rCir->vCent->x=vCent->x;
rCir->vCent->y=vCent->y;
rCir->vCent->z=vCent->z;
rCir->pSegs[0] = new ContrPolyW();
rCir->pSegs[1] = new ContrPolyW();
rCir->pSegs[2] = new ContrPolyW();
rCir->pSegs[3] = new ContrPolyW();
rCir->pSegs[0]=(ContrPolyW *) pSegs[0]->Copy(this);
rCir->pSegs[1]=(ContrPolyW *) pSegs[1]->Copy(this);
rCir->pSegs[2]=(ContrPolyW *) pSegs[2]->Copy(this);
rCir->pSegs[3]=(ContrPolyW *) pSegs[3]->Copy(this);
return (rCir);
}

double Circ1::Bernstein(double dU,int ii,int inn)
{
double dCoeA;
double dCoeB;
double dRet;
dCoeA = Factorial(inn)/(Factorial(ii)*Factorial(inn-ii));
dCoeB = 1-dU;
dRet = dCoeA*pow(dU,ii)*pow(dCoeB,inn-ii);
return dRet;
}


void Circ1::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
pModZ = pModMat;
pScrZ = pScrTran;

pSegs[0]->SetToScr(pModMat,pScrTran);
pSegs[1]->SetToScr(pModMat,pScrTran);
pSegs[2]->SetToScr(pModMat,pScrTran);
pSegs[3]->SetToScr(pModMat,pScrTran);

}

void Circ1::Transform(C3dMatrix TMat)
{

pSegs[0]->Transform(TMat);
pSegs[1]->Transform(TMat);
pSegs[2]->Transform(TMat);
pSegs[3]->Transform(TMat);
*vCent=TMat.Mult(*vCent);
TMat.Translate2(0,0,0);
*vNorm=TMat.Mult(*vNorm);
}

C3dVector Circ1::Get_Centroid()
{
C3dVector vT;
vT.Set(vCent->x,vCent->y,vCent->z);
return (vT);
}


void Circ1::Draw(CDC* pDC,int iDrawmode)
{
double dLS;
double dLE;

if (dS<=0.25)
{
  dLS=4*(dS);
  dLE=4*(dE);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[0]->Draw(pDC,iDrawmode,dLS,dLE);
}
if ((dS<=0.5) && (dE>0.25))
{
  dLS=4*(dS-0.25);
  dLE=4*(dE-0.25);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[1]->Draw(pDC,iDrawmode,dLS,dLE);
}
if ((dS<=0.75) && (dE>0.5))
{
  dLS=4*(dS-0.5);
  dLE=4*(dE-0.5);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[2]->Draw(pDC,iDrawmode,dLS,dLE);
}
if ((dS<=1) && (dE>0.75))
{
  dLS=4*(dS-0.75);
  dLE=4*(dE-0.75);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[3]->Draw(pDC,iDrawmode,dLS,dLE);
}

}

void Circ1::OglDraw(int iDspFlgs)
{
double dLS;
double dLE;

if (dS<=0.25)
{
  dLS=4*(dS);
  dLE=4*(dE);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[0]->OglDraw(dLS,dLE);
}
if ((dS<=0.5) && (dE>0.25))
{
  dLS=4*(dS-0.25);
  dLE=4*(dE-0.25);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[1]->OglDraw(dLS,dLE);
}
if ((dS<=0.75) && (dE>0.5))
{
  dLS=4*(dS-0.5);
  dLE=4*(dE-0.5);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[2]->OglDraw(dLS,dLE);
}
if ((dS<=1) && (dE>0.75))
{
  dLS=4*(dS-0.75);
  dLE=4*(dE-0.75);
  if (dLS<0){dLS=0;}
  if (dLE>1){dLE=1;}
  pSegs[3]->OglDraw(dLS,dLE);
}
}

void Circ1::OglDrawW(int iDspFlgs)
{
  OglDraw(iDspFlgs);
}



void Circ1::HighLight(CDC* pDC)
{
Draw(pDC,4);
}

G_ObjectD Circ1::SelDist(CPoint InPT,Filter FIL)
{
int iC;
double dDist = 1e36;
G_ObjectD Ret;
for (iC = 0;iC < 4;iC++)
{
if (pSegs[iC]->SelDist(InPT,FIL).Dist < dDist)
  {
  Ret = pSegs[iC]->SelDist(InPT,FIL);
  dDist=Ret.Dist;
  }
}
Ret.pObj=this;
return (Ret);
}

C3dVector Circ1::MinPt(C3dVector inPt)
{
C3dVector vRet;
const double dTol = 0.000000001;
const double dIncs = 36;
int i;
double dStp = 1/dIncs;
double dlStp;
double dW=0;
double dMinW=0;
C3dVector cPt;
C3dVector tPt;
C3dVector cNextPt;
double dWScl;
double Dist;
double minDist = 1e36;
C3dVector v1;
C3dVector v2;
double dM;
double dDot;
cPt=GetPt(dW);
tPt=GetPt(dW+dStp);
dWScl = cPt.Dist(tPt);
for(i=0;i<dIncs;i++)
{
  dW=i*dStp;
  cPt=GetPt(dW);
  Dist=cPt.Dist(inPt);
  if (Dist<minDist)
  {
    minDist=Dist;
    dMinW=dW;
  }
}
//start of iteration
dW=dMinW;
dlStp=dStp;
i=0;
do
{
  cPt=GetPt(dW);
  cNextPt=GetPt(dW+0.000001);
  v1=cNextPt;
  v1-=cPt;
  v2=inPt;
  v2-=cPt;
  dM=v2.Mag();
  v1.Normalize();
  v2.Normalize();
  dDot=v2.Dot(v1);
  dlStp=(dM*dDot/dWScl)*1*dStp;
  dW=dW+dlStp;
  i++;
}
while ((pow((dlStp*dlStp),0.5)>dTol) & (i<10000));

vRet=GetPt(dW);
return (vRet);
}

double Circ1::MinWPt(C3dVector inPt)
{
C3dVector vRet;
const double dTol = 0.000000001;
const double dIncs = 36;
int i;
double dStp = 1/dIncs;
double dlStp;
double dW=0;
double dMinW=0;
C3dVector cPt;
C3dVector tPt;
C3dVector cNextPt;
double dWScl;
double Dist;
double minDist = 1e36;
C3dVector v1;
C3dVector v2;
double dM;
double dDot;
cPt=GetPt(dW);
tPt=GetPt(dW+dStp);
dWScl = cPt.Dist(tPt);
for(i=0;i<dIncs;i++)
{
  dW=i*dStp;
  cPt=GetPt(dW);
  Dist=cPt.Dist(inPt);
  if (Dist<minDist)
  {
    minDist=Dist;
    dMinW=dW;
  }
}
//start of iteration
dW=dMinW;
dlStp=dStp;
i=0;
do
{
  cPt=GetPt(dW);
  cNextPt=GetPt(dW+0.000001);
  v1=cNextPt;
  v1-=cPt;
  v2=inPt;
  v2-=cPt;
  dM=v2.Mag();
  v1.Normalize();
  v2.Normalize();
  dDot=v2.Dot(v1);
  dlStp=(dM*dDot/dWScl)*1*dStp;
  dW=dW+dlStp;
  i++;
}
while ((pow((dlStp*dlStp),0.5)>dTol) & (i<10000));
return (dW);
}

C3dVector Circ1::GetPt(double w)
{
C3dVector vR;
vR.x=0;vR.y=0,vR.z=0;;
int TheSeg = -1;
double aw;
if (w>1)
{
	w=w-1;
}
if ((w>=0) && (w<0.25))
{
  TheSeg=0;
  aw =w*4;
}
else if ((w>=0.25) && (w<0.5))
{
  TheSeg=1; 
  aw =(w-0.25)*4;
}
else if ((w>=0.5) && (w<0.75))
{
  TheSeg=2; 
  aw =(w-0.5)*4;
}
else if ((w>=0.75) && (w<=1))
{
  TheSeg=3; 
  aw =(w-0.75)*4;
}
if (TheSeg!=-1)
{
vR = pSegs[TheSeg]->GetPt(aw);
}
return (vR);
}


C3dVector Circ1::GetDir(double w)
{
C3dVector vR;
vR.x=0;vR.y=0,vR.z=0;;
int TheSeg = -1;
double aw;
if (w>1)
{w-=1;}
if ((w>=0) && (w<0.25))
{
  TheSeg=0;
  aw =w*4;
}
else if ((w>=0.25) && (w<0.5))
{
  TheSeg=1; 
  aw =(w-0.25)*4;
}
else if ((w>=0.5) && (w<0.75))
{
  TheSeg=2; 
  aw =(w-0.5)*4;
}
else if ((w>=0.75) && (w<=1))
{
  TheSeg=3; 
  aw =(w-0.75)*4;
}
if (TheSeg!=-1)
{
vR = pSegs[TheSeg]->GetDir(aw);
}
return (vR);
}



//Extruded Surface
IMPLEMENT_DYNAMIC( Surf_Ex1, CObject )

//ContrPolyW* pWCurve[2];
//C3dVector vTranVec;
//C3dMatrix* pScrZ;

void Surf_Ex1::Create(ContrPolyW* pWCurveIn, C3dVector vTranVecIn, int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 10;
pParent=Parrent;
vTranVec = vTranVecIn;

pWCurve[0] = pWCurveIn;
pWCurve[1] = new ContrPolyW;
pWCurve[1]->Create(1,this);
pWCurve[1]->Set2(pWCurve[0]);
pWCurve[1]->Translate(vTranVecIn);


pWCurve[2] = new ContrPolyW;
pWCurve[2]->Create(1,this);
pWCurve[2]->AddVert(&pWCurve[0]->pCVertex[0]->GetPoint(),1);
pWCurve[2]->AddVert(&pWCurve[1]->pCVertex[0]->GetPoint(),1);


pWCurve[3] = new ContrPolyW;
pWCurve[3]->Create(1,this);
pWCurve[3]->AddVert(&pWCurve[0]->pCVertex[pWCurve[0]->iNoVerts-1]->GetPoint(),1);
pWCurve[3]->AddVert(&pWCurve[1]->pCVertex[pWCurve[0]->iNoVerts-1]->GetPoint(),1);

}

void Surf_Ex1::Draw(CClientDC* pDC,int iDrawmode)
{
pWCurve[0]->SetToScr(pModZ,pScrZ);
pWCurve[1]->SetToScr(pModZ,pScrZ);
pWCurve[2]->SetToScr(pModZ,pScrZ);
pWCurve[3]->SetToScr(pModZ,pScrZ);
pWCurve[0]->Draw(pDC,4,0,1);
pWCurve[1]->Draw(pDC,4,0,1);
pWCurve[2]->Draw(pDC,4,0,1);
pWCurve[3]->Draw(pDC,4,0,1);

int iCnt1;
double fred;
C3dVector vDrawPt;
C4dVector vWpt;
Pt_Object ThePoint;
ThePoint.Create(vDrawPt,0,0,0,11,0,0,NULL);
vDrawPt = deCastelJau2(0,0.5).GetPoint();
ThePoint.Pt_Point->x  = vDrawPt.x;
ThePoint.Pt_Point->y  = vDrawPt.y;
ThePoint.Pt_Point->z  = vDrawPt.z;
ThePoint.SetToScr(pModZ,pScrZ);
pDC->MoveTo((int) ThePoint.DSP_Point->x,(int) ThePoint.DSP_Point->y);
for (iCnt1 = 1; iCnt1 < 21; iCnt1++)
{
	fred = iCnt1*0.05;
	vDrawPt = deCastelJau2(fred,0.5).GetPoint();
	ThePoint.Pt_Point->x  = vDrawPt.x;
  ThePoint.Pt_Point->y  = vDrawPt.y;
  ThePoint.Pt_Point->z  = vDrawPt.z;
	ThePoint.SetToScr(pModZ,pScrZ);
  pDC->LineTo((int) ThePoint.DSP_Point->x,(int)ThePoint.DSP_Point->y);
}
vDrawPt = deCastelJau2(0.5,0).GetPoint();
ThePoint.Pt_Point->x  = vDrawPt.x;
ThePoint.Pt_Point->y  = vDrawPt.y;
ThePoint.Pt_Point->z  = vDrawPt.z;
ThePoint.SetToScr(pModZ,pScrZ);
pDC->MoveTo((int) ThePoint.DSP_Point->x,(int) ThePoint.DSP_Point->y);
vDrawPt = deCastelJau2(0.5,1).GetPoint();
ThePoint.Pt_Point->x  = vDrawPt.x;
ThePoint.Pt_Point->y  = vDrawPt.y;
ThePoint.Pt_Point->z  = vDrawPt.z;
ThePoint.SetToScr(pModZ,pScrZ);
pDC->LineTo((int) ThePoint.DSP_Point->x,(int) ThePoint.DSP_Point->y);

}


void Surf_Ex1::OglDraw(int iDspFlgs)
{
GLfloat* ctrlpts;
int iu;
int iv;
int icu,icv;
int iInd = 0;
iu = pWCurve[0]->iNoVerts;
iv = pWCurve[2]->iNoVerts;

ctrlpts = (GLfloat*) malloc(iv*iu*4*sizeof(GLfloat));

for (icv = 0;icv < iv; icv++)
{
  for (icu = 0;icu < iu;icu++)
  {
  ctrlpts[iInd]   = (float) pWCurve[icv]->pCVertex[icu]->xw;
  ctrlpts[iInd+1] = (float) pWCurve[icv]->pCVertex[icu]->yw;
  ctrlpts[iInd+2] = (float) pWCurve[icv]->pCVertex[icu]->zw;
  ctrlpts[iInd+3] = (float) pWCurve[icv]->pCVertex[icu]->w;
  iInd = iInd+4;
  }  
}


glColor3fv(cols[G_Colour]);
glEnable(GL_MAP2_VERTEX_4);
//glBegin(GL_POINTS);
//glVertex4fv(&ctrlpts[0]);
//glVertex4fv(&ctrlpts[4]);
//glVertex4fv(&ctrlpts[8]);
//glVertex4fv(&ctrlpts[12]);
//glVertex4fv(&ctrlpts[16]);
//glVertex4fv(&ctrlpts[20]);
//glEnd();

glMap2f(GL_MAP2_VERTEX_4,0.0f,1.0f,4,iu,0.0f,1.0f,iu*4,iv,ctrlpts);
glEnable(GL_MAP2_VERTEX_4);
glMapGrid2f(20,0.0f,1.0f,20,0.0f,1.0f);
glEvalMesh2(GL_FILL,0,20,0,20);
glFlush();
free(ctrlpts);
pWCurve[1]->OglDraw(0,1);
}

void Surf_Ex1::OglDrawW()
{
GLfloat* ctrlpts;
int iu;
int iv;
int icu,icv;
int iInd = 0;
iu = pWCurve[0]->iNoVerts;
iv = pWCurve[2]->iNoVerts;

ctrlpts = (GLfloat*) malloc(iv*iu*4*sizeof(GLfloat));

for (icv = 0;icv < iv; icv++)
{
  for (icu = 0;icu < iu;icu++)
  {
  ctrlpts[iInd]   = (float) pWCurve[icv]->pCVertex[icu]->xw;
  ctrlpts[iInd+1] = (float) pWCurve[icv]->pCVertex[icu]->yw;
  ctrlpts[iInd+2] = (float) pWCurve[icv]->pCVertex[icu]->zw;
  ctrlpts[iInd+3] = (float) pWCurve[icv]->pCVertex[icu]->w;
  iInd = iInd+4;
  }  
}


glColor3fv(cols[G_Colour]);
glEnable(GL_MAP2_VERTEX_4);

glMap2f(GL_MAP2_VERTEX_4,0.0f,1.0f,4,iu,0.0f,1.0f,iu*4,iv,ctrlpts);
glEnable(GL_MAP2_VERTEX_4);
glMapGrid2f(20,0.0f,1.0f,20,0.0f,1.0f);
glEvalMesh2(GL_LINE,0,20,0,20);
glFlush();
free(ctrlpts);
pWCurve[1]->OglDraw(0,1);
}


void Surf_Ex1::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
pModZ = pModMat;
pScrZ = pScrTran;
}

void Surf_Ex1::HighLight(CClientDC* pDC)
{
Draw(pDC,4);
}

G_ObjectD Surf_Ex1::SelDist(CPoint InPT,Filter FIL)
{
double dSelD;
G_ObjectD Ret;
Pt_Object ThePoint;
C3dVector vDrawPt;
ThePoint.Create(vDrawPt,0,0,0,11,0,0,NULL);
vDrawPt = deCastelJau2(0.5,0.5).GetPoint();
ThePoint.Pt_Point->x  = vDrawPt.x;
ThePoint.Pt_Point->y  = vDrawPt.y;
ThePoint.Pt_Point->z  = vDrawPt.z;
ThePoint.SetToScr(pModZ,pScrZ);
dSelD = pow(ThePoint.DSP_Point->x-InPT.x,2)+pow(ThePoint.DSP_Point->y-InPT.y,2);
ThePoint.Clear();
Ret.Dist=dSelD;
Ret.pObj=this;
return (Ret);
}

C4dVector Surf_Ex1::deCastelJau2(double u,double v)
	 
{
C4dVector vRetPt;

ContrPolyW cLast;
					
cLast.Create(1,NULL);

cLast.AddVertW(pWCurve[0]->deCastelJau1(u));
cLast.AddVertW(pWCurve[1]->deCastelJau1(u));  
vRetPt = cLast.deCastelJau1(v);

cLast.Clear();
return (vRetPt);
}



//Extruded Surface
IMPLEMENT_DYNAMIC( Surf_R, CObject )

//ContrPolyW* pWCurve[2];
//C3dVector vTranVec;
//C3dMatrix* pScrZ;

void Surf_R::Create(ContrPolyW* pWCurveIn, C3dVector vRotVecIn, int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 11;
pParent=Parrent;
vRotVec = vRotVecIn;


pWCurve[0] = pWCurveIn;
pWCurve[1] = new ContrPolyW;
pWCurve[1]->Create(1,this);
pWCurve[1]->Set2(pWCurve[0]);
pWCurve[1]->CPolyRot(45);


pWCurve[2] = new ContrPolyW;
pWCurve[2]->Create(1,this);
pWCurve[2]->Set2(pWCurve[0]);
pWCurve[2]->CPolyRot(90);
pWCurve[2]->CWeight(2);

pWCurve[3] = new ContrPolyW;
pWCurve[3]->Create(1,this);
pWCurve[3]->AddVertW(*pWCurve[0]->pCVertex[0]);
pWCurve[3]->AddVertW(*pWCurve[1]->pCVertex[0]);
pWCurve[3]->AddVertW(*pWCurve[2]->pCVertex[0]);


pWCurve[4] = new ContrPolyW;
pWCurve[4]->Create(1,this);
pWCurve[4]->AddVertW(*pWCurve[0]->pCVertex[pWCurve[0]->iNoVerts-1]);
pWCurve[4]->AddVertW(*pWCurve[1]->pCVertex[pWCurve[0]->iNoVerts-1]);
pWCurve[4]->AddVertW(*pWCurve[2]->pCVertex[pWCurve[0]->iNoVerts-1]);

}

void Surf_R::Draw(CDC* pDC,int iDrawmode)
{
pWCurve[0]->SetToScr(pModZ,pScrZ);
pWCurve[1]->SetToScr(pModZ,pScrZ);
pWCurve[2]->SetToScr(pModZ,pScrZ);
pWCurve[3]->SetToScr(pModZ,pScrZ);
pWCurve[4]->SetToScr(pModZ,pScrZ);
pWCurve[0]->Draw(pDC,4,0,1);
//pWCurve[1]->Draw(pDC,4);
pWCurve[2]->Draw(pDC,4,0,1);
pWCurve[3]->Draw(pDC,4,0,1);
pWCurve[4]->Draw(pDC,4,0,1);


C3dVector vDrawPt;
C4dVector vWpt;
//Pt_Object ThePoint;


//  ThePoint.Create(vDrawPt,0);
//  vDrawPt = deCastelJau2(0,0.5).GetPoint();
//  ThePoint.Pt_Point->x  = vDrawPt.x;
//  ThePoint.Pt_Point->y  = vDrawPt.y;
//  ThePoint.Pt_Point->z  = vDrawPt.z;
//  ThePoint.SetToScr(pScrZ);
//  pDC->MoveTo(ThePoint.DSP_Point->x,ThePoint.DSP_Point->y);
//   for (iCnt1 = 1; iCnt1 < 21; iCnt1++)
//       {
//	   fred = iCnt1*0.05;
//	   vDrawPt = deCastelJau2(fred,0.5).GetPoint();
//	   ThePoint.Pt_Point->x  = vDrawPt.x;
//       ThePoint.Pt_Point->y  = vDrawPt.y;
//       ThePoint.Pt_Point->z  = vDrawPt.z;
//	   ThePoint.SetToScr(pScrZ);
//       pDC->LineTo(ThePoint.DSP_Point->x,ThePoint.DSP_Point->y);
//       }


}


void Surf_R::OglDraw(int iDspFlgs)
{
GLfloat* ctrlpts;
int iu;
int iv;
int icu,icv;
int iInd = 0;
iu = pWCurve[0]->iNoVerts;
iv = pWCurve[3]->iNoVerts;

ctrlpts = (GLfloat*) malloc(iv*iu*4*sizeof(GLfloat));

for (icv = 0;icv < iv; icv++)
{
  for (icu = 0;icu < iu;icu++)
  {
	 
  ctrlpts[iInd]   = (float) pWCurve[icv]->pCVertex[icu]->xw;
  ctrlpts[iInd+1] = (float) pWCurve[icv]->pCVertex[icu]->yw;
  ctrlpts[iInd+2] = (float)-pWCurve[icv]->pCVertex[icu]->zw;
  ctrlpts[iInd+3] = (float) pWCurve[icv]->pCVertex[icu]->w;
  iInd = iInd+4;
  }  
}



glEnable(GL_MAP2_VERTEX_4);
//glBegin(GL_POINTS);
//glVertex4fv(&ctrlpts[0]);
//glVertex4fv(&ctrlpts[4]);
//glVertex4fv(&ctrlpts[8]);
//glVertex4fv(&ctrlpts[12]);
//glVertex4fv(&ctrlpts[16]);
//glVertex4fv(&ctrlpts[20]);
//glEnd();

glMap2f(GL_MAP2_VERTEX_4,0.0f,1.0f,4,iu,0.0f,1.0f,iu*4,iv,ctrlpts);
glEnable(GL_MAP2_VERTEX_4);
glMapGrid2f(20,0.0f,1.0f,20,0.0f,1.0f);
glEvalMesh2(GL_FILL,0,20,0,20);
glFlush();
free(ctrlpts);
}

void Surf_R::OglDrawW(int iDspFlgs)
{
GLfloat* ctrlpts;
int iu;
int iv;
int icu,icv;
int iInd = 0;
iu = pWCurve[0]->iNoVerts;
iv = pWCurve[3]->iNoVerts;

ctrlpts = (GLfloat*) malloc(iv*iu*4*sizeof(GLfloat));

for (icv = 0;icv < iv; icv++)
{
  for (icu = 0;icu < iu;icu++)
  {
	 
  ctrlpts[iInd]   = (float) pWCurve[icv]->pCVertex[icu]->xw;
  ctrlpts[iInd+1] = (float) pWCurve[icv]->pCVertex[icu]->yw;
  ctrlpts[iInd+2] = (float)-pWCurve[icv]->pCVertex[icu]->zw;
  ctrlpts[iInd+3] = (float) pWCurve[icv]->pCVertex[icu]->w;
  iInd = iInd+4;
  }  
}



glEnable(GL_MAP2_VERTEX_4);
//glBegin(GL_POINTS);
//glVertex4fv(&ctrlpts[0]);
//glVertex4fv(&ctrlpts[4]);
//glVertex4fv(&ctrlpts[8]);
//glVertex4fv(&ctrlpts[12]);
//glVertex4fv(&ctrlpts[16]);
//glVertex4fv(&ctrlpts[20]);
//glEnd();

glMap2f(GL_MAP2_VERTEX_4,0.0f,1.0f,4,iu,0.0f,1.0f,iu*4,iv,ctrlpts);
glEnable(GL_MAP2_VERTEX_4);
glMapGrid2f(20,0.0f,1.0f,20,0.0f,1.0f);
glEvalMesh2(GL_LINE,0,20,0,20);
glFlush();
free(ctrlpts);
}


void Surf_R::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
pModZ =	pModMat;
pScrZ = pScrTran;
}

void Surf_R::HighLight(CDC* pDC)
{
Draw(pDC,4);
}

G_ObjectD Surf_R::SelDist(CPoint InPT,Filter FIL)
{
double dSelD;
G_ObjectD Ret;
Pt_Object ThePoint;
C3dVector vDrawPt;
ThePoint.Create(vDrawPt,0,0,0,11,0,0,NULL);
vDrawPt = deCastelJau2(0.5,0.5).GetPoint();
ThePoint.Pt_Point->x  = vDrawPt.x;
ThePoint.Pt_Point->y  = vDrawPt.y;
ThePoint.Pt_Point->z  = vDrawPt.z;
ThePoint.SetToScr(pModZ, pScrZ);
dSelD = pow(ThePoint.DSP_Point->x-InPT.x,2)+pow(ThePoint.DSP_Point->y-InPT.y,2);
ThePoint.Clear();

Ret.pObj=this;
Ret.Dist=dSelD;
return (Ret);
}

C4dVector Surf_R::deCastelJau2(double u,double v)
	 
{
C4dVector vRetPt;
ContrPolyW cLast;					
cLast.Create(1,this);
cLast.AddVertW(pWCurve[0]->deCastelJau1(u));
cLast.AddVertW(pWCurve[1]->deCastelJau1(u));  
cLast.AddVertW(pWCurve[2]->deCastelJau1(u)); 
vRetPt = cLast.deCastelJau1(v);
cLast.Clear();
return (vRetPt);
}


//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_Object38, CObject )


E_Object38::~E_Object38()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
pVertex[2]=NULL;
pVertex[3]=NULL;
pVertex[4]=NULL;
pVertex[5]=NULL;
pVertex[6]=NULL;
pVertex[7]=NULL;
}

void E_Object38::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
int i=0;
for (i=0;i<8;i++)
{
  pVertex[i] = pInVertex[i];
}


}

void E_Object38::Reverse()
{
Pt_Object* pT[8];
pT[0]=pVertex[0];
pT[1]=pVertex[1];
pT[2]=pVertex[2];
pT[3]=pVertex[3];
pT[4]=pVertex[4];
pT[5]=pVertex[5];
pT[6]=pVertex[6];
pT[7]=pVertex[7];
pVertex[0] = pT[0];
pVertex[1] = pT[3];
pVertex[2] = pT[2];
pVertex[3] = pT[1];
pVertex[4] = pT[4];
pVertex[5] = pT[7];
pVertex[6] = pT[6];
pVertex[7] = pT[5];
}

G_Object* E_Object38::GetNode(int i)
{
return (pVertex[i]);
}

int E_Object38::GetLinkList(cLink* Links[12])
{
int ic;
ic=GetCol();
Links[0]=new cLink;
Links[0]->vVerts[0]=pVertex[0];
Links[0]->vVerts[1]=pVertex[1];
Links[0]->iColor=ic;
Links[1]=new cLink;
Links[1]->vVerts[0]=pVertex[1];
Links[1]->vVerts[1]=pVertex[2];
Links[1]->iColor=ic;
Links[2]=new cLink;
Links[2]->vVerts[0]=pVertex[2];
Links[2]->vVerts[1]=pVertex[3];
Links[2]->iColor=ic;
Links[3]=new cLink;
Links[3]->vVerts[0]=pVertex[3];
Links[3]->vVerts[1]=pVertex[0];
Links[3]->iColor=ic;

Links[4]=new cLink;
Links[4]->vVerts[0]=pVertex[4];
Links[4]->vVerts[1]=pVertex[5];
Links[4]->iColor=ic;
Links[5]=new cLink;
Links[5]->vVerts[0]=pVertex[5];
Links[5]->vVerts[1]=pVertex[6];
Links[5]->iColor=ic;
Links[6]=new cLink;
Links[6]->vVerts[0]=pVertex[6];
Links[6]->vVerts[1]=pVertex[7];
Links[6]->iColor=ic;
Links[7]=new cLink;
Links[7]->vVerts[0]=pVertex[7];
Links[7]->vVerts[1]=pVertex[4];
Links[7]->iColor=ic;

Links[8]=new cLink;
Links[8]->vVerts[0]=pVertex[0];
Links[8]->vVerts[1]=pVertex[4];
Links[8]->iColor=ic;
Links[9]=new cLink;
Links[9]->vVerts[0]=pVertex[1];
Links[9]->vVerts[1]=pVertex[5];
Links[9]->iColor=ic;
Links[10]=new cLink;
Links[10]->vVerts[0]=pVertex[2];
Links[10]->vVerts[1]=pVertex[6];
Links[10]->iColor=ic;
Links[11]=new cLink;
Links[11]->vVerts[0]=pVertex[3];
Links[11]->vVerts[1]=pVertex[7];
Links[11]->iColor=ic;

return (12);
}

int E_Object38::GetfaceList(cFace* Faces[6])
{
int ic;
ic=GetCol();
Faces[0]=new cFace();
Faces[0]->vVerts[0]=pVertex[0];
Faces[0]->vVerts[1]=pVertex[3];
Faces[0]->vVerts[2]=pVertex[2];
Faces[0]->vVerts[3]=pVertex[1];
Faces[0]->NoVert=4;
Faces[0]->iColor=ic;

Faces[1]=new cFace();
Faces[1]->vVerts[0]=pVertex[4];
Faces[1]->vVerts[1]=pVertex[5];
Faces[1]->vVerts[2]=pVertex[6];
Faces[1]->vVerts[3]=pVertex[7];
Faces[1]->NoVert=4;
Faces[1]->iColor=ic;

Faces[2]=new cFace();
Faces[2]->vVerts[0]=pVertex[0];
Faces[2]->vVerts[1]=pVertex[1];
Faces[2]->vVerts[2]=pVertex[5];
Faces[2]->vVerts[3]=pVertex[4];
Faces[2]->NoVert=4;
Faces[2]->iColor=ic;

Faces[3]=new cFace();
Faces[3]->vVerts[0]=pVertex[1];
Faces[3]->vVerts[1]=pVertex[2];
Faces[3]->vVerts[2]=pVertex[6];
Faces[3]->vVerts[3]=pVertex[5];
Faces[3]->NoVert=4;
Faces[3]->iColor=ic;

Faces[4]=new cFace();
Faces[4]->vVerts[0]=pVertex[2];
Faces[4]->vVerts[1]=pVertex[3];
Faces[4]->vVerts[2]=pVertex[7];
Faces[4]->vVerts[3]=pVertex[6];
Faces[4]->NoVert=4;
Faces[4]->iColor=ic;

Faces[5]=new cFace();
Faces[5]->vVerts[0]=pVertex[0];
Faces[5]->vVerts[1]=pVertex[4];
Faces[5]->vVerts[2]=pVertex[7];
Faces[5]->vVerts[3]=pVertex[3];
Faces[5]->NoVert=4;
Faces[5]->iColor=ic;

return (6);
}

void E_Object38::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}
}


BOOL E_Object38::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_Object38::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << pVertex[2]->G_label;
    ar << pVertex[3]->G_label;
    ar << pVertex[4]->G_label;
    ar << pVertex[5]->G_label;
    ar << pVertex[6]->G_label;
    ar << pVertex[7]->G_label;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[2] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[3] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[4] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[5] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[6] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[7] = MESH->GetNode(iNd);
	}
}

G_Object* E_Object38::Copy(G_Object* Parrent)
{
ME_Object* MESH = (ME_Object*) Parrent;
E_Object38* gret = new E_Object38;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->pVertex[2] = MESH->GetNode(pVertex[2]->G_label);
gret->pVertex[3] = MESH->GetNode(pVertex[3]->G_label);
gret->pVertex[4] = MESH->GetNode(pVertex[4]->G_label);
gret->pVertex[5] = MESH->GetNode(pVertex[5]->G_label);
gret->pVertex[6] = MESH->GetNode(pVertex[6]->G_label);
gret->pVertex[7] = MESH->GetNode(pVertex[7]->G_label);
gret->pPr=pPr;
gret->pParent=MESH;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object38::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object38* gret = new E_Object38;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[2]);
gret->pVertex[2] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[3]);
gret->pVertex[3] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[4]);
gret->pVertex[4] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[5]);
gret->pVertex[5] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[6]);
gret->pVertex[6] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[7]);
gret->pVertex[7] = Target->pNodes[EInd+iSInd];
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object38::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object38* gret = new E_Object38;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] =  pInVertex[0];
gret->pVertex[1] =  pInVertex[1];
gret->pVertex[2] =  pInVertex[2];
gret->pVertex[3] =  pInVertex[3];
gret->pVertex[4] =  pInVertex[4];
gret->pVertex[5] =  pInVertex[5];
gret->pVertex[6] =  pInVertex[6];
gret->pVertex[7] =  pInVertex[7];
gret->pPr=pPr;
gret->pParent=Parrent;
gret->pResV = NULL;
return (gret);
}

// Draw Object line
void E_Object38::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);
pDC->LineTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);

pDC->LineTo((int) pVertex[4]->DSP_Point->x,(int) pVertex[4]->DSP_Point->y);
pDC->LineTo((int) pVertex[5]->DSP_Point->x,(int) pVertex[5]->DSP_Point->y);
pDC->LineTo((int) pVertex[6]->DSP_Point->x,(int) pVertex[6]->DSP_Point->y);
pDC->LineTo((int) pVertex[7]->DSP_Point->x,(int) pVertex[7]->DSP_Point->y);
pDC->LineTo((int) pVertex[4]->DSP_Point->x,(int) pVertex[4]->DSP_Point->y);

pDC->MoveTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[5]->DSP_Point->x,(int) pVertex[5]->DSP_Point->y);

pDC->MoveTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[6]->DSP_Point->x,(int) pVertex[6]->DSP_Point->y);

pDC->MoveTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);
pDC->LineTo((int) pVertex[7]->DSP_Point->x,(int) pVertex[7]->DSP_Point->y);
}

void E_Object38::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
C3dVector d[8];
int i;
int ind;

for (i=0;i<8;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;
ind=ME->iCVar;

if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<8;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
  Selectable=1;
  if ((iDspFlgs & DSP_LINE) > 0)
  {
    glColor3fv(cols[G_Colour]);
  }
  else
  {
    glColor3fv(cols[0]);
  }
	glBegin(GL_LINES);
	glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);

	glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);

	glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);

	glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);



	glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);

	glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);

	glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);
	glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);

	glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
	glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);



	glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);

	glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);

	glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);

	glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
  glEnd();
  C3dVector vCent;
  vCent=Get_Centroid();
  if (bDrawLab==TRUE)
	{
	  sprintf_s(sLab,"E%i",G_label);
	  OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
	}
  if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
  {
    sprintf_s(sLab,"%f",*pResV->GetAddress(ind));
    OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  } 
}
else
{
  Selectable=0;
}
}

void E_Object38::OglDraw(int iDspFlgs,double dS1,double dS2)
{
C3dVector d[8];
int i;
for (i=0;i<8;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;

      float fCols[8]={0,0,0,0,0,0,0,0};
      BOOL bD=FALSE;
      int iVar;
      iVar=ME->iCVar;
      //Nodal data

      if ((pVertex[0]->pResV != NULL) &&
          (pVertex[1]->pResV != NULL) &&
          (pVertex[2]->pResV != NULL) &&
          (pVertex[3]->pResV != NULL) &&
          (pVertex[4]->pResV != NULL) &&
          (pVertex[5]->pResV != NULL) &&
          (pVertex[6]->pResV != NULL) &&
          (pVertex[7]->pResV != NULL))
      {
        bD=TRUE;
        fCols[0]=GetContourCol(*pVertex[0]->pResV->GetAddress(iVar));
        fCols[1]=GetContourCol(*pVertex[1]->pResV->GetAddress(iVar));
        fCols[2]=GetContourCol(*pVertex[2]->pResV->GetAddress(iVar));
        fCols[3]=GetContourCol(*pVertex[3]->pResV->GetAddress(iVar));
        fCols[4]=GetContourCol(*pVertex[4]->pResV->GetAddress(iVar));
        fCols[5]=GetContourCol(*pVertex[5]->pResV->GetAddress(iVar));
        fCols[6]=GetContourCol(*pVertex[6]->pResV->GetAddress(iVar));
        fCols[7]=GetContourCol(*pVertex[7]->pResV->GetAddress(iVar));
      }
      if (pResV!=NULL)
      {
        bD=TRUE;
        float fC;
        if (G_label==106)
        {
           bD=TRUE;   
        }
        fC=GetContourCol(*pResV->GetAddress(iVar));
        fCols[0]=fC;
        fCols[1]=fC;
        fCols[2]=fC;
        fCols[3]=fC;
        fCols[4]=fC;
        fCols[5]=fC;
        fCols[6]=fC;
        fCols[7]=fC;
      }

C3dVector v1;
C3dVector v2;
C3dVector Vn;
if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<8;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
	Selectable=1;
  glColor3fv(cols[G_Colour]);
  if (((iDspFlgs & DSP_CONT)>0) || (bD==FALSE))
  {
	  v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v2.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v2.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
  	
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glEnd();

	  v1.x = pVertex[5]->Pt_Point->x-pVertex[4]->Pt_Point->x;
	  v1.y = pVertex[5]->Pt_Point->y-pVertex[4]->Pt_Point->y;
	  v1.z = pVertex[5]->Pt_Point->z-pVertex[4]->Pt_Point->z;

	  v2.x = pVertex[6]->Pt_Point->x-pVertex[5]->Pt_Point->x;
	  v2.y = pVertex[6]->Pt_Point->y-pVertex[5]->Pt_Point->y;
	  v2.z = pVertex[6]->Pt_Point->z-pVertex[5]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
	  glEnd();

	  v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[5]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v2.y = pVertex[5]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v2.z = pVertex[5]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	  glEnd();

	  v1.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v1.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v1.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;

	  v2.x = pVertex[5]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	  v2.y = pVertex[5]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	  v2.z = pVertex[5]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	  glEnd();

	  v1.x = pVertex[6]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	  v1.y = pVertex[6]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	  v1.z = pVertex[6]->Pt_Point->z-pVertex[2]->Pt_Point->z;

	  v2.x = pVertex[7]->Pt_Point->x-pVertex[6]->Pt_Point->x;
	  v2.y = pVertex[7]->Pt_Point->y-pVertex[6]->Pt_Point->y;
	  v2.z = pVertex[7]->Pt_Point->z-pVertex[6]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glEnd();

	  v1.x = pVertex[3]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[3]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[3]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[7]->Pt_Point->x-pVertex[3]->Pt_Point->x;
	  v2.y = pVertex[7]->Pt_Point->y-pVertex[3]->Pt_Point->y;
	  v2.z = pVertex[7]->Pt_Point->z-pVertex[3]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	  glEnd();
  }
  else
  {

      if (bD)
      {
        glColor3fv(cols[124]);
        glEnable(GL_TEXTURE_1D);
	      glBegin(GL_POLYGON);
	      glTexCoord1f(fCols[0]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	      glTexCoord1f(fCols[1]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	      glTexCoord1f(fCols[2]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	      glTexCoord1f(fCols[3]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	      glEnd();

	      v1.x = pVertex[5]->Pt_Point->x-pVertex[4]->Pt_Point->x;
	      v1.y = pVertex[5]->Pt_Point->y-pVertex[4]->Pt_Point->y;
	      v1.z = pVertex[5]->Pt_Point->z-pVertex[4]->Pt_Point->z;

	      v2.x = pVertex[6]->Pt_Point->x-pVertex[5]->Pt_Point->x;
	      v2.y = pVertex[6]->Pt_Point->y-pVertex[5]->Pt_Point->y;
	      v2.z = pVertex[6]->Pt_Point->z-pVertex[5]->Pt_Point->z;
	      Vn = v1.Cross(v2);

	      Vn.Normalize();
	      glBegin(GL_POLYGON);
	      glTexCoord1f(fCols[4]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	      glTexCoord1f(fCols[5]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	      glTexCoord1f(fCols[6]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);
	      glTexCoord1f(fCols[7]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
	      glEnd();

	      v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	      v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	      v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	      v2.x = pVertex[5]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	      v2.y = pVertex[5]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	      v2.z = pVertex[5]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	      Vn = v1.Cross(v2);

	      Vn.Normalize();
	      glBegin(GL_POLYGON);
	      glTexCoord1f(fCols[0]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
        glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	      glTexCoord1f(fCols[1]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	      glTexCoord1f(fCols[5]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	      glTexCoord1f(fCols[4]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	      glEnd();

	      v1.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	      v1.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	      v1.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;

	      v2.x = pVertex[5]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	      v2.y = pVertex[5]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	      v2.z = pVertex[5]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	      Vn = v1.Cross(v2);

	      Vn.Normalize();
	      glBegin(GL_POLYGON);
	      glTexCoord1f(fCols[1]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	      glTexCoord1f(fCols[2]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	      glTexCoord1f(fCols[6]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);
	      glTexCoord1f(fCols[5]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	      glEnd();

	      v1.x = pVertex[6]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	      v1.y = pVertex[6]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	      v1.z = pVertex[6]->Pt_Point->z-pVertex[2]->Pt_Point->z;

	      v2.x = pVertex[7]->Pt_Point->x-pVertex[6]->Pt_Point->x;
	      v2.y = pVertex[7]->Pt_Point->y-pVertex[6]->Pt_Point->y;
	      v2.z = pVertex[7]->Pt_Point->z-pVertex[6]->Pt_Point->z;
	      Vn = v1.Cross(v2);

	      Vn.Normalize();
	      glBegin(GL_POLYGON);
	      glTexCoord1f(fCols[2]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	      glTexCoord1f(fCols[6]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[6]->Pt_Point->x+d[6].x,(float) pVertex[6]->Pt_Point->y+d[6].y,(float) pVertex[6]->Pt_Point->z+d[6].z);
	      glTexCoord1f(fCols[7]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
	      glTexCoord1f(fCols[3]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	      glEnd();

	      v1.x = pVertex[3]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	      v1.y = pVertex[3]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	      v1.z = pVertex[3]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	      v2.x = pVertex[7]->Pt_Point->x-pVertex[3]->Pt_Point->x;
	      v2.y = pVertex[7]->Pt_Point->y-pVertex[3]->Pt_Point->y;
	      v2.z = pVertex[7]->Pt_Point->z-pVertex[3]->Pt_Point->z;
	      Vn = v1.Cross(v2);

	      Vn.Normalize();
	      glBegin(GL_POLYGON);
	      glTexCoord1f(fCols[0]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	      glTexCoord1f(fCols[3]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	      glTexCoord1f(fCols[7]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[7]->Pt_Point->x+d[7].x,(float) pVertex[7]->Pt_Point->y+d[7].y,(float) pVertex[7]->Pt_Point->z+d[7].z);
	      glTexCoord1f(fCols[4]);
        glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	      glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	      glEnd();
        glDisable(GL_TEXTURE_1D);
      }
  }
}
else
{
  Selectable=0;
}
}

void E_Object38::ExportUNV(FILE* pFile)
{
int i;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%10i",pVertex[i]->G_label);
}
fprintf(pFile,"\n","");
}

void E_Object38::ExportNAS(FILE* pFile)
{

fprintf(pFile,"%8s%8i%8i","CHEXA   ",G_label,PID);
fprintf(pFile,"%8i",pVertex[0]->G_label);
fprintf(pFile,"%8i",pVertex[1]->G_label);
fprintf(pFile,"%8i",pVertex[2]->G_label);
fprintf(pFile,"%8i",pVertex[3]->G_label);
fprintf(pFile,"%8i",pVertex[4]->G_label);
fprintf(pFile,"%8i",pVertex[5]->G_label);
fprintf(pFile,"\n","");
fprintf(pFile,"%8s","        ");
fprintf(pFile,"%8i",pVertex[6]->G_label);
fprintf(pFile,"%8i",pVertex[7]->G_label);
fprintf(pFile,"\n","");
}



Mat E_Object38::getCoords3d()
{
int i;
Mat coord(iNoNodes,3);
for (i=0;i<iNoNodes;i++)
{
  *coord.mn(i+1, 1) = pVertex[i]->Pt_Point->x;
  *coord.mn(i+1, 2) = pVertex[i]->Pt_Point->y;
  *coord.mn(i+1, 3) = pVertex[i]->Pt_Point->z;
}
return (coord);
}

C3dVector E_Object38::Get_Centroid()
{
Mat fun;
Mat FunPnt(1,3);
*FunPnt.mn(1,1)=0.0;
*FunPnt.mn(1,2)=0.0;
*FunPnt.mn(1,3)=0.0;
fun=ShapeFun(FunPnt,1);
C3dVector vT;
vT.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vT+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
}

fun.clear();
FunPnt.clear();
return (vT);
}

int E_Object38::MaxBW()
{
int i;
int j;
int MaxDof;
int MinDof;
MaxDof=0;
MinDof=99999999;
for (i=0;i<iNoNodes;i++)
{
  for(j=0;j<6;j++)
  {
    if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j]>MaxDof))
	{
       MaxDof=pVertex[i]->dof[j];
    }
	if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j] < MinDof))
	{
       MinDof=pVertex[i]->dof[j];
	}
  }
}
int iRC;
if (MaxDof-MinDof<0)
{
  iRC=0;
}
else
{
  iRC=MaxDof-MinDof;
}
return (iRC);
}

Mat E_Object38::Sample(int iNo)
{
Mat Pts(iNo,4);

if (iNo ==8)
{
  double r3 = 1.0 / sqrt(3.0);
  double weight = 1.0;
  *Pts.mn(1,1) = -r3;   *Pts.mn(1,2) = -r3;   *Pts.mn(1,3) = -r3;   *Pts.mn(1,4) = weight;
  *Pts.mn(2,1) =  r3;   *Pts.mn(2,2) = -r3;   *Pts.mn(2,3) = -r3;   *Pts.mn(2,4) = weight;
  *Pts.mn(3,1) =  r3;   *Pts.mn(3,2) =  r3;   *Pts.mn(3,3) = -r3;   *Pts.mn(3,4) = weight;
  *Pts.mn(4,1) = -r3;   *Pts.mn(4,2) =  r3;   *Pts.mn(4,3) = -r3;   *Pts.mn(4,4) = weight;
  *Pts.mn(5,1) = -r3;   *Pts.mn(5,2) = -r3;   *Pts.mn(5,3) =  r3;   *Pts.mn(5,4) = weight;
  *Pts.mn(6,1) =  r3;   *Pts.mn(6,2) = -r3;   *Pts.mn(6,3) =  r3;   *Pts.mn(6,4) = weight;
  *Pts.mn(7,1) =  r3;   *Pts.mn(7,2) =  r3;   *Pts.mn(7,3) =  r3;   *Pts.mn(7,4) = weight;
  *Pts.mn(8,1) = -r3;   *Pts.mn(8,2) =  r3;   *Pts.mn(8,3) =  r3;   *Pts.mn(8,4) = weight;
}
return (Pts);
}

Mat E_Object38::ShapeFun(Mat Points, int i)
{
Mat fun(1,8);
double xi,eta,zeta;
xi = *Points.mn(i, 1);
eta = *Points.mn(i, 2);
zeta = *Points.mn(i, 3);

*fun.mn(1,1) = 0.125*(1.0-xi)*(1.0-eta)*(1.0-zeta);
*fun.mn(1,2) = 0.125*(1.0+xi)*(1.0-eta)*(1.0-zeta);
*fun.mn(1,3) = 0.125*(1.0+xi)*(1.0+eta)*(1.0-zeta);
*fun.mn(1,4) = 0.125*(1.0-xi)*(1.0+eta)*(1.0-zeta);
*fun.mn(1,5) = 0.125*(1.0-xi)*(1.0-eta)*(1.0+zeta);
*fun.mn(1,6) = 0.125*(1.0+xi)*(1.0-eta)*(1.0+zeta);
*fun.mn(1,7) = 0.125*(1.0+xi)*(1.0+eta)*(1.0+zeta);
*fun.mn(1,8) = 0.125*(1.0-xi)*(1.0+eta)*(1.0+zeta);

return(fun);
}

Mat E_Object38::ShapeDer(Mat Points, int i)
{
Mat der(3,8);

  *der.mn(1,1) = -0.125 * (1 - *Points.mn(i,2)) * (1 - *Points.mn(i,3));
  *der.mn(1,2) =  0.125 * (1 - *Points.mn(i,2)) * (1 - *Points.mn(i,3));
  *der.mn(1,3) =  0.125 * (1 + *Points.mn(i,2)) * (1 - *Points.mn(i,3));
  *der.mn(1,4) = -0.125 * (1 + *Points.mn(i,2)) * (1 - *Points.mn(i,3));
  *der.mn(1,5) = -0.125 * (1 - *Points.mn(i,2)) * (1 + *Points.mn(i,3));
  *der.mn(1,6) =  0.125 * (1 - *Points.mn(i,2)) * (1 + *Points.mn(i,3));
  *der.mn(1,7) =  0.125 * (1 + *Points.mn(i,2)) * (1 + *Points.mn(i,3));
  *der.mn(1,8) = -0.125 * (1 + *Points.mn(i,2)) * (1 + *Points.mn(i,3));
  
  *der.mn(2,1) = -0.125 * (1 - *Points.mn(i,1)) * (1 - *Points.mn(i,3));
  *der.mn(2,2) = -0.125 * (1 + *Points.mn(i,1)) * (1 - *Points.mn(i,3));
  *der.mn(2,3) =  0.125 * (1 + *Points.mn(i,1)) * (1 - *Points.mn(i,3));
  *der.mn(2,4) =  0.125 * (1 - *Points.mn(i,1)) * (1 - *Points.mn(i,3));
  *der.mn(2,5) = -0.125 * (1 - *Points.mn(i,1)) * (1 + *Points.mn(i,3));
  *der.mn(2,6) = -0.125 * (1 + *Points.mn(i,1)) * (1 + *Points.mn(i,3));
  *der.mn(2,7) =  0.125 * (1 + *Points.mn(i,1)) * (1 + *Points.mn(i,3));
  *der.mn(2,8) =  0.125 * (1 - *Points.mn(i,1)) * (1 + *Points.mn(i,3));
  
  *der.mn(3,1) = -0.125 * (1 - *Points.mn(i,1)) * (1 - *Points.mn(i,2));
  *der.mn(3,2) = -0.125 * (1 + *Points.mn(i,1)) * (1 - *Points.mn(i,2));
  *der.mn(3,3) = -0.125 * (1 + *Points.mn(i,1)) * (1 + *Points.mn(i,2));
  *der.mn(3,4) = -0.125 * (1 - *Points.mn(i,1)) * (1 + *Points.mn(i,2));
  *der.mn(3,5) =  0.125 * (1 - *Points.mn(i,1)) * (1 - *Points.mn(i,2));
  *der.mn(3,6) =  0.125 * (1 + *Points.mn(i,1)) * (1 - *Points.mn(i,2));
  *der.mn(3,7) =  0.125 * (1 + *Points.mn(i,1)) * (1 + *Points.mn(i,2));
  *der.mn(3,8) =  0.125 * (1 - *Points.mn(i,1)) * (1 + *Points.mn(i,2));  
return(der);
}

Vec<int> E_Object38::GetSteerVec2d()
{
Vec<int> V(8*3);
*V.nn(1)=pVertex[0]->dof[0];
*V.nn(2)=pVertex[0]->dof[1];
*V.nn(3)=pVertex[0]->dof[2];
*V.nn(4)=pVertex[1]->dof[0];
*V.nn(5)=pVertex[1]->dof[1];
*V.nn(6)=pVertex[1]->dof[2];
*V.nn(7)=pVertex[2]->dof[0];
*V.nn(8)=pVertex[2]->dof[1];
*V.nn(9)=pVertex[2]->dof[2];
*V.nn(10)=pVertex[3]->dof[0];
*V.nn(11)=pVertex[3]->dof[1];
*V.nn(12)=pVertex[3]->dof[2];
*V.nn(13)=pVertex[4]->dof[0];
*V.nn(14)=pVertex[4]->dof[1];
*V.nn(15)=pVertex[4]->dof[2];
*V.nn(16)=pVertex[5]->dof[0];
*V.nn(17)=pVertex[5]->dof[1];
*V.nn(18)=pVertex[5]->dof[2];
*V.nn(19)=pVertex[6]->dof[0];
*V.nn(20)=pVertex[6]->dof[1];
*V.nn(21)=pVertex[6]->dof[2];
*V.nn(22)=pVertex[7]->dof[0];
*V.nn(23)=pVertex[7]->dof[1];
*V.nn(24)=pVertex[7]->dof[2];
return(V);
}

int E_Object38::noDof()
{
return(3);
}







//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_Object36, CObject )

E_Object36::~E_Object36()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
pVertex[2]=NULL;
pVertex[3]=NULL;
pVertex[4]=NULL;
pVertex[5]=NULL;
}

void E_Object36::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
int i=0;
for (i=0;i<6;i++)
   {
    pVertex[i] = pInVertex[i];
   }

}

void E_Object36::Reverse()
{
Pt_Object* pT[8];
pT[0]=pVertex[0];
pT[1]=pVertex[1];
pT[2]=pVertex[2];
pT[3]=pVertex[3];
pT[4]=pVertex[4];
pT[5]=pVertex[5];
pVertex[0] = pT[0];
pVertex[1] = pT[2];
pVertex[2] = pT[1];
pVertex[3] = pT[3];
pVertex[4] = pT[5];
pVertex[5] = pT[4];
}

void E_Object36::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}
}

BOOL E_Object36::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_Object36::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << pVertex[2]->G_label;
    ar << pVertex[3]->G_label;
    ar << pVertex[4]->G_label;
    ar << pVertex[5]->G_label;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[2] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[3] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[4] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[5] = MESH->GetNode(iNd);
	}
}

G_Object* E_Object36::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object36* gret = new E_Object36;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->pVertex[2] = MESH->GetNode(pVertex[2]->G_label);
gret->pVertex[3] = MESH->GetNode(pVertex[3]->G_label);
gret->pVertex[4] = MESH->GetNode(pVertex[4]->G_label);
gret->pVertex[5] = MESH->GetNode(pVertex[5]->G_label);
gret->pPr=pPr;
gret->pParent=MESH;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object36::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object36* gret = new E_Object36;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[2]);
gret->pVertex[2] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[3]);
gret->pVertex[3] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[4]);
gret->pVertex[4] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[5]);
gret->pVertex[5] = Target->pNodes[EInd+iSInd];
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object36::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object36* gret = new E_Object36;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv=inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = pInVertex[0];
gret->pVertex[1] = pInVertex[1];
gret->pVertex[2] = pInVertex[2];
gret->pVertex[3] = pInVertex[3];
gret->pVertex[4] = pInVertex[4];
gret->pVertex[5] = pInVertex[5];
gret->pPr=pPr;
gret->pParent=Parrent;
gret->pResV = NULL;
return (gret);
}
// Draw Object line
void E_Object36::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);

pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);
pDC->LineTo((int) pVertex[4]->DSP_Point->x,(int) pVertex[4]->DSP_Point->y);
pDC->LineTo((int) pVertex[5]->DSP_Point->x,(int) pVertex[5]->DSP_Point->y);
pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);


pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);

pDC->MoveTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[4]->DSP_Point->x,(int) pVertex[4]->DSP_Point->y);

pDC->MoveTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[5]->DSP_Point->x,(int) pVertex[5]->DSP_Point->y);
}

void E_Object36::OglDraw(int iDspFlgs,double dS1,double dS2)
{
C3dVector d[6];
int i;
for (i=0;i<6;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;

      float fCols[6]={0,0,0,0,0,0};
      BOOL bD=FALSE;
      int iVar;
      iVar=ME->iCVar;
      //Nodal data
      if ((pVertex[0]->pResV != NULL) &&
          (pVertex[1]->pResV != NULL) &&
          (pVertex[2]->pResV != NULL) &&
          (pVertex[3]->pResV != NULL) &&
          (pVertex[4]->pResV != NULL) &&
          (pVertex[5]->pResV != NULL))
      {
        bD=TRUE;
        fCols[0]=GetContourCol(*pVertex[0]->pResV->GetAddress(iVar));
        fCols[1]=GetContourCol(*pVertex[1]->pResV->GetAddress(iVar));
        fCols[2]=GetContourCol(*pVertex[2]->pResV->GetAddress(iVar));
        fCols[3]=GetContourCol(*pVertex[3]->pResV->GetAddress(iVar));
        fCols[4]=GetContourCol(*pVertex[4]->pResV->GetAddress(iVar));
        fCols[5]=GetContourCol(*pVertex[5]->pResV->GetAddress(iVar));
      }
      if (pResV!=NULL)
      {
        bD=TRUE;
        fCols[0]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[1]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[2]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[3]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[4]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[5]=GetContourCol(*pResV->GetAddress(iVar));

      }
C3dVector v1;
C3dVector v2;
C3dVector Vn;
if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<6;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }

	Selectable=1;
  if (((iDspFlgs & DSP_CONT)>0) || (bD==FALSE))
  {
	  v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v2.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v2.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glColor3fv(cols[G_Colour]);
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glEnd();

	  v1.x = pVertex[4]->Pt_Point->x-pVertex[3]->Pt_Point->x;
	  v1.y = pVertex[4]->Pt_Point->y-pVertex[3]->Pt_Point->y;
	  v1.z = pVertex[4]->Pt_Point->z-pVertex[3]->Pt_Point->z;

	  v2.x = pVertex[5]->Pt_Point->x-pVertex[4]->Pt_Point->x;
	  v2.y = pVertex[5]->Pt_Point->y-pVertex[4]->Pt_Point->y;
	  v2.z = pVertex[5]->Pt_Point->z-pVertex[4]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	  glEnd();

	  v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[4]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v2.y = pVertex[4]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v2.z = pVertex[4]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glEnd();

	  v1.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v1.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v1.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;

	  v2.x = pVertex[5]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	  v2.y = pVertex[5]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	  v2.z = pVertex[5]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	  glEnd();

	  v1.x = pVertex[0]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	  v1.y = pVertex[0]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	  v1.z = pVertex[0]->Pt_Point->z-pVertex[2]->Pt_Point->z;

	  v2.x = pVertex[3]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v2.y = pVertex[3]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v2.z = pVertex[3]->Pt_Point->z-pVertex[0]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	  glEnd();
  }
  else
  {

   if (bD)
   {
      glColor3fv(cols[124]);
      glEnable(GL_TEXTURE_1D);
	    v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	    v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	    v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	    v2.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	    v2.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	    v2.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[0]);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[1]);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[2]);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	    glEnd();

	    v1.x = pVertex[4]->Pt_Point->x-pVertex[3]->Pt_Point->x;
	    v1.y = pVertex[4]->Pt_Point->y-pVertex[3]->Pt_Point->y;
	    v1.z = pVertex[4]->Pt_Point->z-pVertex[3]->Pt_Point->z;

	    v2.x = pVertex[5]->Pt_Point->x-pVertex[4]->Pt_Point->x;
	    v2.y = pVertex[5]->Pt_Point->y-pVertex[4]->Pt_Point->y;
	    v2.z = pVertex[5]->Pt_Point->z-pVertex[4]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[3]);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[4]);
	    glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[5]);
	    glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	    glEnd();

	    v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	    v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	    v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	    v2.x = pVertex[4]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	    v2.y = pVertex[4]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	    v2.z = pVertex[4]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[0]);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[1]);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[4]);
	    glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[3]);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	    glEnd();

	    v1.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	    v1.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	    v1.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;

	    v2.x = pVertex[5]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	    v2.y = pVertex[5]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	    v2.z = pVertex[5]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[1]);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[2]);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[5]);
	    glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[4]);
	    glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
	    glEnd();

	    v1.x = pVertex[0]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	    v1.y = pVertex[0]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	    v1.z = pVertex[0]->Pt_Point->z-pVertex[2]->Pt_Point->z;

	    v2.x = pVertex[3]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	    v2.y = pVertex[3]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	    v2.z = pVertex[3]->Pt_Point->z-pVertex[0]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[2]);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[0]);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[3]);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[5]);
	    glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
	    glEnd();
      glDisable(GL_TEXTURE_1D);
    }
  }
}
else
{
  Selectable=0;
}
}

void E_Object36::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
C3dVector d[6];
int i;
int ind;

for (i=0;i<6;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;
ind=ME->iCVar;

if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<6;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
  Selectable=1;
  if ((iDspFlgs & DSP_LINE) > 0)
  {
    glColor3fv(cols[G_Colour]);
  }
  else
  {
    glColor3fv(cols[0]);
  }
  glBegin(GL_LINES);
  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
  glVertex3f((float) pVertex[4]->Pt_Point->x+d[4].x,(float) pVertex[4]->Pt_Point->y+d[4].y,(float) pVertex[4]->Pt_Point->z+d[4].z);
  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
  glVertex3f((float) pVertex[5]->Pt_Point->x+d[5].x,(float) pVertex[5]->Pt_Point->y+d[5].y,(float) pVertex[5]->Pt_Point->z+d[5].z);
  glEnd();
  C3dVector vCent;
  vCent=Get_Centroid();
  if (bDrawLab==TRUE)
  {
     sprintf_s(sLab,"E%i",G_label);
     OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  }
  if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
  {
     sprintf_s(sLab,"%f",*pResV->GetAddress(ind));
     OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  }
}
else
{
  Selectable=0;
}
}

void E_Object36::ExportUNV(FILE* pFile)
{
int i;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%10i",pVertex[i]->G_label);
}
fprintf(pFile,"\n","");
}


void E_Object36::ExportNAS(FILE* pFile)
{

fprintf(pFile,"%8s%8i%8i","CPENTA  ",G_label,PID);
fprintf(pFile,"%8i",pVertex[0]->G_label);
fprintf(pFile,"%8i",pVertex[1]->G_label);
fprintf(pFile,"%8i",pVertex[2]->G_label);
fprintf(pFile,"%8i",pVertex[3]->G_label);
fprintf(pFile,"%8i",pVertex[4]->G_label);
fprintf(pFile,"%8i",pVertex[5]->G_label);
fprintf(pFile,"\n","");
}



C3dVector E_Object36::Get_Centroid()
{
Mat fun;
Mat FunPnt(1,3);
*FunPnt.mn(1,1)=0.333;
*FunPnt.mn(1,2)=0.333;
*FunPnt.mn(1,3)=0.0;
fun=ShapeFun(FunPnt,1);
C3dVector vT;
vT.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vT+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
}

fun.clear();
FunPnt.clear();
return (vT);
}


G_Object* E_Object36::GetNode(int i)
{
return (pVertex[i]);
}


int E_Object36::GetLinkList(cLink* Links[200])
{
int ic;
ic=GetCol();
Links[0]=new cLink;
Links[0]->vVerts[0]=pVertex[0];
Links[0]->vVerts[1]=pVertex[1];
Links[0]->iColor=ic;
Links[1]=new cLink;
Links[1]->vVerts[0]=pVertex[1];
Links[1]->vVerts[1]=pVertex[2];
Links[1]->iColor=ic;
Links[2]=new cLink;
Links[2]->vVerts[0]=pVertex[2];
Links[2]->vVerts[1]=pVertex[0];
Links[2]->iColor=ic;
Links[3]=new cLink;
Links[3]->vVerts[0]=pVertex[3];
Links[3]->vVerts[1]=pVertex[4];
Links[3]->iColor=ic;

Links[4]=new cLink;
Links[4]->vVerts[0]=pVertex[4];
Links[4]->vVerts[1]=pVertex[5];
Links[4]->iColor=ic;
Links[5]=new cLink;
Links[5]->vVerts[0]=pVertex[5];
Links[5]->vVerts[1]=pVertex[3];
Links[5]->iColor=ic;
Links[6]=new cLink;
Links[6]->vVerts[0]=pVertex[0];
Links[6]->vVerts[1]=pVertex[3];
Links[6]->iColor=ic;
Links[7]=new cLink;
Links[7]->vVerts[0]=pVertex[1];
Links[7]->vVerts[1]=pVertex[4];
Links[7]->iColor=ic;

Links[8]=new cLink;
Links[8]->vVerts[0]=pVertex[2];
Links[8]->vVerts[1]=pVertex[5];
Links[8]->iColor=ic;
return (9);
}
int E_Object36::GetfaceList(cFace* Faces[6])
{
int ic;
ic=GetCol();
Faces[0]=new cFace();
Faces[0]->vVerts[0]=pVertex[0];
Faces[0]->vVerts[1]=pVertex[1];
Faces[0]->vVerts[2]=pVertex[2];
Faces[0]->NoVert=3;
Faces[0]->iColor=ic;

Faces[1]=new cFace();
Faces[1]->vVerts[0]=pVertex[3];
Faces[1]->vVerts[1]=pVertex[4];
Faces[1]->vVerts[2]=pVertex[5];
Faces[1]->NoVert=3;
Faces[1]->iColor=ic;

Faces[2]=new cFace();
Faces[2]->vVerts[0]=pVertex[1];
Faces[2]->vVerts[1]=pVertex[2];
Faces[2]->vVerts[2]=pVertex[5];
Faces[2]->vVerts[3]=pVertex[4];
Faces[2]->NoVert=4;
Faces[2]->iColor=ic;

Faces[3]=new cFace();
Faces[3]->vVerts[0]=pVertex[0];
Faces[3]->vVerts[1]=pVertex[3];
Faces[3]->vVerts[2]=pVertex[5];
Faces[3]->vVerts[3]=pVertex[2];
Faces[3]->NoVert=4;
Faces[3]->iColor=ic;

Faces[4]=new cFace();
Faces[4]->vVerts[0]=pVertex[0];
Faces[4]->vVerts[1]=pVertex[1];
Faces[4]->vVerts[2]=pVertex[4];
Faces[4]->vVerts[3]=pVertex[3];
Faces[4]->NoVert=4;
Faces[4]->iColor=ic;
return (5);
}



int E_Object36::noDof()
{
return(3);
}

Vec<int> E_Object36::GetSteerVec2d()
{
Vec<int> V(6*3);
*V.nn(1)=pVertex[0]->dof[0];
*V.nn(2)=pVertex[0]->dof[1];
*V.nn(3)=pVertex[0]->dof[2];
*V.nn(4)=pVertex[1]->dof[0];
*V.nn(5)=pVertex[1]->dof[1];
*V.nn(6)=pVertex[1]->dof[2];
*V.nn(7)=pVertex[2]->dof[0];
*V.nn(8)=pVertex[2]->dof[1];
*V.nn(9)=pVertex[2]->dof[2];
*V.nn(10)=pVertex[3]->dof[0];
*V.nn(11)=pVertex[3]->dof[1];
*V.nn(12)=pVertex[3]->dof[2];
*V.nn(13)=pVertex[4]->dof[0];
*V.nn(14)=pVertex[4]->dof[1];
*V.nn(15)=pVertex[4]->dof[2];
*V.nn(16)=pVertex[5]->dof[0];
*V.nn(17)=pVertex[5]->dof[1];
*V.nn(18)=pVertex[5]->dof[2];
return(V);
}

int E_Object36::MaxBW()
{
int i;
int j;
int MaxDof;
int MinDof;
MaxDof=0;
MinDof=99999999;
for (i=0;i<iNoNodes;i++)
{
  for(j=0;j<6;j++)
  {
    if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j]>MaxDof))
	{
       MaxDof=pVertex[i]->dof[j];
    }
	if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j] < MinDof))
	{
       MinDof=pVertex[i]->dof[j];
	}
  }
}
int iRC;
if (MaxDof-MinDof<0)
{
  iRC=0;
}
else
{
  iRC=MaxDof-MinDof;
}
return (iRC);
}

Mat E_Object36::getCoords3d()
{
int i;
Mat coord(iNoNodes,3);
for (i=0;i<iNoNodes;i++)
{
  *coord.mn(i+1, 1) = pVertex[i]->Pt_Point->x;
  *coord.mn(i+1, 2) = pVertex[i]->Pt_Point->y;
  *coord.mn(i+1, 3) = pVertex[i]->Pt_Point->z;
}
return (coord);
}

Mat E_Object36::Sample(int iNo)
{
Mat Pts(iNo,4);
if (iNo ==6)
{
  double r16 = 1.0/6.0;
  double r23 = 2.0/3.0;
  double weight = 1.0/6.0;   //unknown at moment
  *Pts.mn(1,1)=r16;*Pts.mn(1,2)=r16;*Pts.mn(1,3)=-0.5;*Pts.mn(1,4)=weight;
  *Pts.mn(2,1)=r23;*Pts.mn(2,2)=r16;*Pts.mn(2,3)=-0.5;*Pts.mn(2,4)=weight;
  *Pts.mn(3,1)=r16;*Pts.mn(3,2)=r23;*Pts.mn(3,3)=-0.5;*Pts.mn(3,4)=weight;
  *Pts.mn(4,1)=r16;*Pts.mn(4,2)=r16;*Pts.mn(4,3)=0.5;*Pts.mn(4,4)=weight;
  *Pts.mn(5,1)=r23;*Pts.mn(5,2)=r16;*Pts.mn(5,3)=0.5;*Pts.mn(5,4)=weight;
  *Pts.mn(6,1)=r16;*Pts.mn(6,2)=r23;*Pts.mn(6,3)=0.5;*Pts.mn(6,4)=weight;
}
return (Pts);
}

Mat E_Object36::ShapeFun(Mat Points, int i)
{
Mat fun(1,6);
double xi,eta,zeta;
double r,s,t;
eta = *Points.mn(i, 2);
xi = *Points.mn(i, 1);
zeta = *Points.mn(i, 3);
r=xi;
s=eta;
t=1-xi-eta;

*fun.mn(1,1) = 0.5*(1-zeta)*r;
*fun.mn(1,2) = 0.5*(1-zeta)*s;
*fun.mn(1,3) = 0.5*(1-zeta)*t;
*fun.mn(1,4) = 0.5*(1+zeta)*r;
*fun.mn(1,5) = 0.5*(1+zeta)*s;
*fun.mn(1,6) = 0.5*(1+zeta)*t;

return(fun);
}

Mat E_Object36::ShapeDer(Mat Points, int i)
{
Mat der(3,6);
double xi,eta,zeta;
double r,s,t;
eta = *Points.mn(i, 2);
xi = *Points.mn(i, 1);
zeta = *Points.mn(i, 3);
r=xi;
s=eta;
t=1-xi-eta;
*der.mn(1,1) =  0.5*(1-zeta);
*der.mn(1,2) =  0;
*der.mn(1,3) = -0.5*(1-zeta);
*der.mn(1,4) =  0.5*(1+zeta);
*der.mn(1,5) =  0;
*der.mn(1,6) =  -0.5*(1+zeta);

*der.mn(2,1) =  0;
*der.mn(2,2) =  0.5*(1-zeta);
*der.mn(2,3) = -0.5*(1-zeta);
*der.mn(2,4) =  0;
*der.mn(2,5) =  0.5*(1+zeta);
*der.mn(2,6) = -0.5*(1+zeta);

*der.mn(3,1) = -0.5*r;
*der.mn(3,2) = -0.5*s;
*der.mn(3,3) = -0.5*t;
*der.mn(3,4) =  0.5*r;
*der.mn(3,5) =  0.5*s;
*der.mn(3,6) =  0.5*t;

return(der);
}
//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_Object34, CObject )

E_Object34::~E_Object34()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
pVertex[2]=NULL;
pVertex[3]=NULL;
}

void E_Object34::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
int i=0;
for (i=0;i<4;i++)
{
  pVertex[i] = pInVertex[i];
}

}

void E_Object34::Reverse()
{
Pt_Object* pT[8];
pT[0]=pVertex[0];
pT[1]=pVertex[1];
pT[2]=pVertex[2];
pT[3]=pVertex[3];
pVertex[0] = pT[0];
pVertex[1] = pT[2];
pVertex[2] = pT[1];
pVertex[3] = pT[3];
}


BOOL E_Object34::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_Object34::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}
}

G_Object* E_Object34::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object34* gret = new E_Object34;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->pVertex[2] = MESH->GetNode(pVertex[2]->G_label);
gret->pVertex[3] = MESH->GetNode(pVertex[3]->G_label);
gret->pPr=pPr;
gret->pParent=MESH;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object34::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object34* gret = new E_Object34;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[2]);
gret->pVertex[2] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[3]);
gret->pVertex[3] = Target->pNodes[EInd+iSInd];
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}


G_Object* E_Object34::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object34* gret = new E_Object34;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv= inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = pInVertex[0];
gret->pVertex[1] = pInVertex[1];
gret->pVertex[2] = pInVertex[2];
gret->pVertex[3] = pInVertex[3];
gret->pPr=pPr;
gret->pParent=Parrent;
gret->pResV = NULL;
return (gret);
}

void E_Object34::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << pVertex[2]->G_label;
    ar << pVertex[3]->G_label;
	}
	else
	{
    E_Object::Serialize(ar,MESH);    
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[2] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[3] = MESH->GetNode(iNd);
	}
}

int E_Object34::GetLinkList(cLink* Links[200])
{
int ic;
ic=GetCol();
Links[0]=new cLink;
Links[0]->vVerts[0]=pVertex[0];
Links[0]->vVerts[1]=pVertex[1];
Links[0]->iColor=ic;
Links[1]=new cLink;
Links[1]->vVerts[0]=pVertex[1];
Links[1]->vVerts[1]=pVertex[2];
Links[1]->iColor=ic;
Links[2]=new cLink;
Links[2]->vVerts[0]=pVertex[2];
Links[2]->vVerts[1]=pVertex[0];
Links[2]->iColor=ic;
Links[3]=new cLink;
Links[3]->vVerts[0]=pVertex[0];
Links[3]->vVerts[1]=pVertex[3];
Links[3]->iColor=ic;
Links[4]=new cLink;
Links[4]->vVerts[0]=pVertex[1];
Links[4]->vVerts[1]=pVertex[3];
Links[4]->iColor=ic;
Links[5]=new cLink;
Links[5]->vVerts[0]=pVertex[2];
Links[5]->vVerts[1]=pVertex[3];
Links[5]->iColor=ic;
return (6);
}

// Draw Object line
void E_Object34::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);


pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);
pDC->LineTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);

pDC->MoveTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);
pDC->MoveTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);

}

void E_Object34::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
C3dVector d[4];
int i;
int ind;

for (i=0;i<4;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;
ind=ME->iCVar;

if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<4;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
  Selectable=1;
  if ((iDspFlgs & DSP_LINE) > 0)
  {
    glColor3fv(cols[G_Colour]);
  }
  else
  {
    glColor3fv(cols[0]);
  }
  glBegin(GL_LINES);
  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
  glEnd();
  C3dVector vCent;
  vCent=Get_Centroid();
  if (bDrawLab==TRUE)
  {
	sprintf_s(sLab,"E%i",G_label);
	OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  }
  if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
  {
    sprintf_s(sLab,"%f",*pResV->GetAddress(ind));
    OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  }
}
else
{
  Selectable=0;
}
}


void E_Object34::OglDraw(int iDspFlgs,double dS1,double dS2)
{
C3dVector d[4];
int i;
for (i=0;i<4;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;

    float fCols[4]={0,0,0,0};
    BOOL bD=FALSE;
    int iVar;
    iVar=ME->iCVar;
    //Nodal data
    if ((pVertex[0]->pResV != NULL) &&
        (pVertex[1]->pResV != NULL) &&
        (pVertex[2]->pResV != NULL) &&
        (pVertex[3]->pResV != NULL))
    {
      bD=TRUE;
      fCols[0]=GetContourCol(*pVertex[0]->pResV->GetAddress(iVar));
      fCols[1]=GetContourCol(*pVertex[1]->pResV->GetAddress(iVar));
      fCols[2]=GetContourCol(*pVertex[2]->pResV->GetAddress(iVar));
      fCols[3]=GetContourCol(*pVertex[3]->pResV->GetAddress(iVar));
    }
    if (pResV!=NULL)
    {
      bD=TRUE;
      fCols[0]=GetContourCol(*pResV->GetAddress(iVar));
      fCols[1]=GetContourCol(*pResV->GetAddress(iVar));
      fCols[2]=GetContourCol(*pResV->GetAddress(iVar));
      fCols[3]=GetContourCol(*pResV->GetAddress(iVar));
    }

C3dVector v1;
C3dVector v2;
C3dVector Vn;
if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<4;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
	Selectable=1;
	glColor3fv(cols[G_Colour]);
  if (((iDspFlgs & DSP_CONT)>0) || (bD==FALSE))
  {
	  v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v2.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v2.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glEnd();

	  v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[3]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v2.y = pVertex[3]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v2.z = pVertex[3]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glEnd();

	  v1.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	  v1.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	  v1.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;

	  v2.x = pVertex[3]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	  v2.y = pVertex[3]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	  v2.z = pVertex[3]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glEnd();

	  v1.x = pVertex[2]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	  v1.y = pVertex[2]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	  v1.z = pVertex[2]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	  v2.x = pVertex[3]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	  v2.y = pVertex[3]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	  v2.z = pVertex[3]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	  Vn = v1.Cross(v2);

	  Vn.Normalize();
	  glBegin(GL_POLYGON);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	  glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	  glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	  glEnd();
  }
  else
  {

    if (bD)
    {
      glColor3fv(cols[124]);
      glEnable(GL_TEXTURE_1D);
	    v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	    v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	    v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	    v2.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	    v2.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	    v2.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);

	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[0]);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[1]);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[2]);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	    glEnd();

	    v1.x = pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	    v1.y = pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	    v1.z = pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	    v2.x = pVertex[3]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	    v2.y = pVertex[3]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	    v2.z = pVertex[3]->Pt_Point->z-pVertex[1]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[0]);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[1]);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[3]);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	    glEnd();

	    v1.x = pVertex[2]->Pt_Point->x-pVertex[1]->Pt_Point->x;
	    v1.y = pVertex[2]->Pt_Point->y-pVertex[1]->Pt_Point->y;
	    v1.z = pVertex[2]->Pt_Point->z-pVertex[1]->Pt_Point->z;

	    v2.x = pVertex[3]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	    v2.y = pVertex[3]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	    v2.z = pVertex[3]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[1]);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+d[1].x,(float) pVertex[1]->Pt_Point->y+d[1].y,(float) pVertex[1]->Pt_Point->z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[2]);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[3]);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	    glEnd();

	    v1.x = pVertex[2]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	    v1.y = pVertex[2]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	    v1.z = pVertex[2]->Pt_Point->z-pVertex[0]->Pt_Point->z;

	    v2.x = pVertex[3]->Pt_Point->x-pVertex[2]->Pt_Point->x;
	    v2.y = pVertex[3]->Pt_Point->y-pVertex[2]->Pt_Point->y;
	    v2.z = pVertex[3]->Pt_Point->z-pVertex[2]->Pt_Point->z;
	    Vn = v1.Cross(v2);

	    Vn.Normalize();
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[0]);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+d[0].x,(float) pVertex[0]->Pt_Point->y+d[0].y,(float) pVertex[0]->Pt_Point->z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[2]);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+d[2].x,(float) pVertex[2]->Pt_Point->y+d[2].y,(float) pVertex[2]->Pt_Point->z+d[2].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
      glTexCoord1f(fCols[3]);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+d[3].x,(float) pVertex[3]->Pt_Point->y+d[3].y,(float) pVertex[3]->Pt_Point->z+d[3].z);
	    glEnd();
      glDisable(GL_TEXTURE_1D);
    }
  }
}
else
{
  Selectable=0;
}
}

G_Object* E_Object34::GetNode(int i)
{
return (pVertex[i]);
}

int E_Object34::GetfaceList(cFace* Faces[6])
{
int ic;
ic=GetCol();
Faces[0]=new cFace();
Faces[0]->vVerts[0]=pVertex[0];
Faces[0]->vVerts[1]=pVertex[1];
Faces[0]->vVerts[2]=pVertex[2];
Faces[0]->NoVert=3;
Faces[0]->iColor=ic;

Faces[1]=new cFace();
Faces[1]->vVerts[0]=pVertex[1];
Faces[1]->vVerts[1]=pVertex[2];
Faces[1]->vVerts[2]=pVertex[3];
Faces[1]->NoVert=3;
Faces[1]->iColor=ic;

Faces[2]=new cFace;
Faces[2]->vVerts[0]=pVertex[2];
Faces[2]->vVerts[1]=pVertex[3];
Faces[2]->vVerts[2]=pVertex[0];
Faces[2]->NoVert=3;
Faces[2]->iColor=ic;

Faces[3]=new cFace;
Faces[3]->vVerts[0]=pVertex[0];
Faces[3]->vVerts[1]=pVertex[1];
Faces[3]->vVerts[2]=pVertex[3];
Faces[3]->NoVert=3;
Faces[3]->iColor=ic;
return (4);
}

void E_Object34::ExportNAS(FILE* pFile)
{

fprintf(pFile,"%8s%8i%8i","CTETRA  ",G_label,PID);
fprintf(pFile,"%8i",pVertex[0]->G_label);
fprintf(pFile,"%8i",pVertex[1]->G_label);
fprintf(pFile,"%8i",pVertex[2]->G_label);
fprintf(pFile,"%8i",pVertex[3]->G_label);
fprintf(pFile,"\n","");
}

void E_Object34::ExportUNV(FILE* pFile)
{
int i;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%10i",pVertex[i]->G_label);
}
fprintf(pFile,"\n","");
}




C3dVector E_Object34::Get_Centroid()
{
Mat fun;
Mat FunPnt(1,3);
*FunPnt.mn(1,1)=0.25;
*FunPnt.mn(1,2)=0.25;
*FunPnt.mn(1,3)=0.25;
fun=ShapeFun(FunPnt,1);
C3dVector vT;
vT.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vT+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
}

fun.clear();
FunPnt.clear();

return (vT);
}







Mat E_Object34::getCoords3d()
{
int i;
Mat coord(iNoNodes,3);
for (i=0;i<iNoNodes;i++)
{
  *coord.mn(i+1, 1) = pVertex[i]->Pt_Point->x;
  *coord.mn(i+1, 2) = pVertex[i]->Pt_Point->y;
  *coord.mn(i+1, 3) = pVertex[i]->Pt_Point->z;
}
return (coord);
}

Mat E_Object34::Sample(int iNo)
{
Mat Pts(iNo,4);
if (iNo==1)
{
*Pts.mn(1,1) = 0.25;
*Pts.mn(1,2) = 0.25;   
*Pts.mn(1,3) = 0.25;   
*Pts.mn(1,4) = 1.0/6.0;
}
else if (iNo==4)
{
	double coord1 = 0.585410196624968;
	double coord2 = 0.138196601125010;
	//the weight is divided by 6 because the determinant gives the volume of a
	//qube and a tetraedron has a 6 times smaller volume (0.25/6.0 = 0.04166666) 
	double weight = 0.0416666666666666;
	*Pts.mn(1,1) = coord1; *Pts.mn(1,2) = coord2; *Pts.mn(1,3) = coord2; *Pts.mn(1,4) = weight;
	*Pts.mn(2,1) = coord2; *Pts.mn(2,2) = coord1; *Pts.mn(2,3) = coord2; *Pts.mn(2,4) = weight;
	*Pts.mn(3,1) = coord2; *Pts.mn(3,2) = coord2; *Pts.mn(3,3) = coord1; *Pts.mn(3,4) = weight;
	*Pts.mn(4,1) = coord2; *Pts.mn(4,2) = coord2; *Pts.mn(4,3) = coord2; *Pts.mn(4,4) = weight;
}
return (Pts);
}



Mat E_Object34::ShapeFun(Mat Points, int i)
{
Mat fun(1,4);
double v1,v2,v3,v4;
v1=*Points.mn(i,1);
v2=*Points.mn(i,2);
v3=*Points.mn(i,3);
v4=1-v1-v2-v3;
*fun.mn(1,1)=v1;
*fun.mn(1,2)=v2;
*fun.mn(1,3)=v3;
*fun.mn(1,4)=v4;
return(fun);
}

int E_Object34::noDof()
{
return(3);
}

Mat E_Object34::ShapeDer(Mat Points, int i)
{
Mat der(3,4);
*der.mn(1,1) = 1;
*der.mn(1,2) = 0;
*der.mn(1,3) = 0;
*der.mn(1,4) = -1;

*der.mn(2,1) = 0;
*der.mn(2,2) = 1;
*der.mn(2,3) = 0;
*der.mn(2,4) = -1;

*der.mn(3,1) = 0;
*der.mn(3,2) = 0;
*der.mn(3,3) = 1;
*der.mn(3,4) = -1;
return(der);
}

int E_Object34::MaxBW()
{
int i;
int j;
int MaxDof;
int MinDof;
MaxDof=0;
MinDof=99999999;
for (i=0;i<iNoNodes;i++)
{
  for(j=0;j<6;j++)
  {
    if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j]>MaxDof))
	{
       MaxDof=pVertex[i]->dof[j];
    }
	if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j] < MinDof))
	{
       MinDof=pVertex[i]->dof[j];
	}
  }
}
int iRC;
if (MaxDof-MinDof<0)
{
  iRC=0;
}
else
{
  iRC=MaxDof-MinDof;
}
return (iRC);
}

Vec<int> E_Object34::GetSteerVec2d()
{
Vec<int> V(4*3);
*V.nn(1)=pVertex[0]->dof[0];
*V.nn(2)=pVertex[0]->dof[1];
*V.nn(3)=pVertex[0]->dof[2];
*V.nn(4)=pVertex[1]->dof[0];
*V.nn(5)=pVertex[1]->dof[1];
*V.nn(6)=pVertex[1]->dof[2];
*V.nn(7)=pVertex[2]->dof[0];
*V.nn(8)=pVertex[2]->dof[1];
*V.nn(9)=pVertex[2]->dof[2];
*V.nn(10)=pVertex[3]->dof[0];
*V.nn(11)=pVertex[3]->dof[1];
*V.nn(12)=pVertex[3]->dof[2];
return(V);
}

IMPLEMENT_DYNAMIC(BCLD, CObject )
void BCLD::Serialize(CArchive& ar,ME_Object* MESH)

{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
	}
	else
	{
    G_Object::Serialize(ar);
	}
}

void BCLD::ExportNAS(FILE* pFile)
{

}

BOOL BCLD::NodeIn(Pt_Object* pN)
{
BOOL brc=FALSE;
if (pObj==pN)
{
  brc=TRUE;
}
return (brc);
}
//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_Object, CObject )


void E_Object::Create( int iLab,int iCol,int iType, int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 3;
iELType = iType;
G_label = iLab;
G_Colour = iCol;
PID=iPID;
iMatID = iMat;
iNoNodes = iNo;
pParent=Parrent;
pPr=inPr;
PIDunv=PIDunv;
pResV=NULL;
}

Mat E_Object::Sample(int iNo)
{
Mat M(0,0);
return(M);
}

BOOL E_Object::NodeInEl(Pt_Object* pN)
{
return (FALSE);
}

void E_Object::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

}

int E_Object::noDof()
{
return(0);
}

Mat E_Object::ShapeDer(Mat Points, int i)
{
Mat M(0,0);
return(M);
}

Mat E_Object::ShapeFun(Mat Points, int i)
{
Mat M(0,0);
return(M);
}

Mat E_Object::getCoords3d()
{
Mat M(0,0);
return(M);
}

Mat E_Object::getCoords2d()
{
Mat M(0,0);
return(M);
}


Mat E_Object::bmat2d(Mat& coord,
                   Mat& deriv)
{
Mat M(0,0);
return(M);
}

int E_Object::GetfaceList(cFace* Faces[6])
{
return (0);
}

int E_Object::GetLinkList(cLink* Links[200])
{
return (0);
}

G_Object* E_Object::GetNode(int i)
{
return (NULL);
}

void E_Object::Transform(C3dMatrix TMat)
{

}

CString E_Object::GetDOFString(int iDOF)
{
  char sDOF[8];
  CString sRet;
  sDOF[0]=' ';
  sDOF[1]=' ';
  sDOF[2]=' ';
  sDOF[3]=' ';
  sDOF[4]=' ';
  sDOF[5]=' ';
  int iN=0;
  if (iDOF& DOF_1)
  {
    sDOF[iN]='1';
    iN++;
  }
  if (iDOF & DOF_2)
  {
    sDOF[iN]='2';
    iN++;
  }
  if (iDOF & DOF_3)
  {
    sDOF[iN]='3';
    iN++;
  }
  if (iDOF & DOF_4)
  {
    sDOF[iN]='4';
    iN++;
  }
  if (iDOF & DOF_5)
  {
    sDOF[iN]='5';
    iN++;
  }
  if (iDOF & DOF_6)
  {
    sDOF[iN]='6';
    iN++;
  }
  sDOF[iN]=NULL;
  sRet=sDOF;
  return (sRet);
}

void E_Object::Reverse()
{

}

C3dMatrix E_Object::GetElSys()
{
C3dMatrix vR;
vR.MakeUnit();
return (vR);
}

int E_Object::GetDOFInt(CString sDOF)
{
  int iDOF=0;
  if (sDOF.GetLength()>0)
  {
    if (sDOF.Find('1')>-1)
    {
       iDOF=iDOF^DOF_1;
    }
    if (sDOF.Find('2')>-1)
    {
       iDOF=iDOF^DOF_2;
    }
    if (sDOF.Find('3')>-1)
    {
       iDOF=iDOF^DOF_3;
    }
    if (sDOF.Find('4')>-1)
    {
       iDOF=iDOF^DOF_4;
    }
    if (sDOF.Find('5',0)>-1)
    {
       iDOF=iDOF^DOF_5;
    }
    if (sDOF.Find('6',0)>-1)
    {
       iDOF=iDOF^DOF_6;
    }
  }
  return(iDOF);
}

void E_Object::SetProperty(Property* Pr)
{
pPr=NULL;
if (Pr!=NULL)
{
  if (iELType == 115)
  {
    if (Pr->iType==3)
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if (iELType == 112)
  {
    if (Pr->iType==3)
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if (iELType == 94)
  {
      if ((Pr->iType==1) || (Pr->iType==2))
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if (iELType == 91)
  {
      if ((Pr->iType==1) || (Pr->iType==2))
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if (iELType == 21)
  {
      if ((Pr->iType==4) || (Pr->iType==5))
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if  (iELType == 22)
  {
      if (Pr->iType==6) 
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if  (iELType == 11)
  {
      if (Pr->iType==11) 
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if (iELType == 161)
  {

  }
  else if ((iELType == 121) || (iELType == 136) || (iELType == 137))
  {

  }
  else if ((iELType == 21) || (iELType == 22))
  {

  }
  else if (iELType == 111)
  {
    if (Pr->iType==3)
      {pPr=Pr;
       PID=pPr->iID;
      }
  }
  else if (iELType == 122)
  {

  }
}
}

void E_Object::Info()
{
  char S1[80];
  sprintf_s(S1,"%s%i%s%i%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour," PID; ",PID," ELTYPE; ",iELType);
  outtext1(S1); 
}


Mat E_Object::bmat(Mat& coord,
                   Mat& deriv,
				   int iD,
				   int iDof)
{
int nod,k,l,m;
double x,y;
nod = deriv.n;
Mat bee(iD,iDof*iNoNodes);
if (iD==3)
{
  for (m=1;m<nod+1;m++)
  {
   k = 2 * m;
   l = k - 1;
   x = *deriv.mn(1, m);
   *bee.mn(1, l) = x;
   *bee.mn(3, k) = x;
   y = *deriv.mn(2, m);
   *bee.mn(2, k) = y;
   *bee.mn(3, l) = y;
  }
}
else if (iD==6)
{
  for (k=1;k<nod+1;k++)//was m
  {
   *bee.mn(1,(k)*3-3+1) = *deriv.mn(1,k);
   *bee.mn(2,(k)*3-2+1) = *deriv.mn(2,k);
   *bee.mn(3,(k)*3-1+1) = *deriv.mn(3,k);
   *bee.mn(4,(k)*3-3+1) = *deriv.mn(2,k);
   *bee.mn(4,(k)*3-2+1) = *deriv.mn(1,k);
   *bee.mn(5,(k)*3-2+1) = *deriv.mn(3,k);
   *bee.mn(5,(k)*3-1+1) = *deriv.mn(2,k);
   *bee.mn(6,(k)*3-3+1) = *deriv.mn(3,k);
   *bee.mn(6,(k)*3-1+1) = *deriv.mn(1,k);
  }
}

return (bee);
}

BOOL E_Object::ChkNegJac()
{
BOOL brc=FALSE;
Mat coord;
Mat deriv;
Mat Points;
Mat jac;
double det;
int iDof;


iDof=noDof();
if ((iELType==91) ||
    (iELType==94) ||
    (iELType==111) ||
    (iELType==112) ||
    (iELType==115))
{

  if (iDof==2)  
  {
     coord=getCoords2d();   
  }
  else
  {
     coord=getCoords3d();
  }

  Points=Sample(1);
  det = 0;
  deriv=ShapeDer(Points, 1);
  jac = deriv*coord;
  jac=jac.InvertJac(det);
  if (det<0)
  {
    brc=TRUE;
  }
}
else
{
  brc=FALSE;
}
return(brc);
}

Mat E_Object::GetStiffMat(PropTable* PropsT,MatTable* MatT)
{
Mat bee;   //strain displacement matrix
Mat dee;   //stress strain
int nip=0;
Mat coord;
Mat coord2;
Mat deriv;
Mat deriv2;
Mat fun;
Mat Points;
Mat jac;
int i;
double det;
Mat bT;
Mat db;
Mat bdb;
int iDof;
int iS;
int MID=-1;
double dE=210e9;
double dv=0.29;
char S1[80];
double dthk=0.001;

Property* pS=PropsT->GetItem(PID);
if (pS!=NULL)
{
  MID=pS->GetDefMatID();
}
Material* pM=MatT->GetItem(MID);
if (pS==NULL)
{
  sprintf_s(S1,"PROPERTY NOT FOUND FOR EL %i",G_label);
  outtext1(S1);
}
if (pM==NULL)
{  
  sprintf_s(S1,"MATERIAL NOT FOUND FOR EL %i",G_label);
  outtext1(S1); 
}
//Get Shell thick ness

if (((iELType==91) || (iELType==94)) && (pS!=NULL))
{
  PSHELL* pSh = (PSHELL*) pS;
  dthk=pSh->dT;
}

if ((pM!=NULL) && (pM->iType = 1))
{
  MAT1* pIsen = (MAT1*) pM;
  dE=pIsen->dE;
  dv=pIsen->dNU;
}


if (iELType==91)
{
iDof=2;
nip=1;
iS=3;
}
else if (iELType==94)
{
iDof=2;
nip=4;
iS=3;
}
else if (iELType==115)
{
iDof=3;
nip=8;
iS=6;
}
else if (iELType==111)
{
iDof=3;
nip=1;
iS=6;
}
else if (iELType==112)
{
iDof=3;
nip=6;
iS=6;
}
Mat KM(iDof*iNoNodes,iDof*iNoNodes);





if ((iELType==91) || (iELType==94) || (iELType==115) || (iELType==111) || (iELType==112))
{
  Mat dee=DeeMat(dE,dv,iS);
  if (iDof==2)
  {
    coord=getCoords2d();
  }
  else
  {
    coord=getCoords3d();
  }
  //coord.diag();
  Points=Sample(nip);
  for(i=1;i<nip+1;i++)
  {
    det = 0;
    fun=ShapeFun(Points, i);
    deriv=ShapeDer(Points, i);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee=bmat(coord, deriv2,iS,iDof);
    bT = bee;
    bT.Transpose();
    db = dee*bee;
    bdb = bT*db;
	if (iDof==3){det*=*Points.mn(i,4);}
	else if (iDof==2){det*=*Points.mn(i,3);}
    bdb*=det;
    KM+=bdb;
  }
}
//for plain stress problems factor shells KM by dthk
if ((iELType==91) || (iELType==94))
{
  KM*=dthk;
}
//KM.diag();
return (KM);
}

Vec<int> E_Object::GetSteerVec2d()
{
Vec<int> V(0);
return(V);
}

int E_Object::MaxBW()
{
return (-1);
}


void E_Object::Serialize(CArchive& ar,ME_Object* MESH)

{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
    ar<<iELType;
    ar<<PID;
    ar<<PIDunv;
    ar<<iMatID;
    ar<<iNoNodes;
	}
	else
	{
    G_Object::Serialize(ar);
    ar>>iELType;
    ar>>PID;
    ar>>PIDunv;
    ar>>iMatID;
    ar>>iNoNodes;
    pResV=NULL;
    pPr=NULL;
	}

}

G_Object* E_Object::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object* gret = new E_Object;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pPr = NULL;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
E_Object* gret = new E_Object;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}


G_Object* E_Object::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{

E_Object* gret = new E_Object;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pParent=Parrent;
gret->pResV = NULL;
return (gret);
}

void E_Object::ExportNAS(FILE* pFile)
{
  fprintf(pFile,"%s %i\n","$ERROR MISSING ELEMENT DEFINITION - ELEMENT:",G_label);
}

void E_Object::ExportUNV(FILE* pFile)
{

}

Mat E_Object::DeeMat(double E, double v,int iD)
{
double C,v2,vv;
int i;
Mat dee(iD,iD);
if (iD==3)  //Plain Stress
{
  C = E / (1-v*v);
  *dee.mn(1, 1) = C;
  *dee.mn(2, 2) = C;
  *dee.mn(3, 3) = 0.5*(1-v)*C;
  *dee.mn(1, 2) = v*C;
  *dee.mn(2, 1) = v*C;
}
else if(iD==6)
{
  //v2=v/(1-v);
  //vv=0.5*(1-2*v)/(1-v);
  //for (i=1;i<4;i++)
  //{
  //  *dee.mn(i, i)=1;
  //}
  //for (i=4;i<7;i++)
  //{
  //  *dee.mn(i, i)=vv;
  //}
  //*dee.mn(1, 2)=vv;
  //*dee.mn(2, 1)=vv;
  //*dee.mn(1, 3)=vv;
  //*dee.mn(3, 1)=vv;
  //*dee.mn(2, 3)=vv;
  //*dee.mn(3, 2)=vv;
  //dee*=E/(2*(1+v)*vv);

  v2=v/(1-v);
  vv=0.5*(1-2*v)/(1-v);
  for (i=1;i<4;i++)
  {
    *dee.mn(i, i)=1;
  }
  for (i=4;i<7;i++)
  {
    *dee.mn(i, i)=vv;
  }
  *dee.mn(1, 2)=v2;
  *dee.mn(2, 1)=v2;
  *dee.mn(1, 3)=v2;
  *dee.mn(3, 1)=v2;
  *dee.mn(2, 3)=v2;
  *dee.mn(3, 2)=v2;
  dee*= E*(1-v)/((1+v)*(1-2*v));
}
return (dee);
}

//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_Object2, CObject )

E_Object2::~E_Object2()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
}

void E_Object2::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType, int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
int i=0;
for (i=0;i<2;i++)
{
  pVertex[i] = pInVertex[i];
}
A=0;
B=0;
C=0;
}

BOOL E_Object2::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_Object2::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}
}

void E_Object2::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
	  vUp.Serialize(ar);
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << A;
    ar << B;
	  ar << C;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
	  vUp.Serialize(ar);
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
	  ar >> A;
    ar >> B;
	  ar >> C;
	}
}


G_Object* E_Object2::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object2* gret = new E_Object2;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->vUp=vUp;
gret->A=A;
gret->B=B;
gret->C=C;
gret->pPr=pPr;
gret->pParent=MESH;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object2::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object2* gret = new E_Object2;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
gret->vUp=vUp;
Pt_Object* nA=Source->GetNode(A);
if (nA!=NULL)
{
  EInd=Source->GetNodeInd(nA);
  gret->A = Target->pNodes[EInd+iSInd]->G_label;  //Orientation Node
}
else
{
  gret->A=A;
}
gret->B=B;
gret->C=C;
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}


G_Object* E_Object2::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object2* gret = new E_Object2;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = pInVertex[0];
gret->pVertex[1] = pInVertex[1];
gret->vUp=vUp;
gret->A=A;
gret->B=B;
gret->C=C;
gret->pPr=pPr;
gret->pParent=Parrent;
gret->pResV = NULL;
return (gret);
}

// Draw Object line
void E_Object2::Draw(CDC* pDC,int iDrawmode)
{
pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
}

int E_Object2::GetLinkList(cLink* Links[200])
{
Links[0]=new cLink;
Links[0]->iColor=GetCol();
Links[0]->vVerts[0]=pVertex[0];
Links[0]->vVerts[1]=pVertex[1];
return (1);
}

G_Object* E_Object2::GetNode(int i)
{
return (pVertex[i]);
}

void E_Object2::OglDraw(int iDspFlgs,double dS1,double dS2)
{
glColor3fv(cols[G_Colour]);
glBegin(GL_LINES);
glVertex3f((float) pVertex[0]->Pt_Point->x,(float) pVertex[0]->Pt_Point->y,(float) pVertex[0]->Pt_Point->z);
glVertex3f((float) pVertex[1]->Pt_Point->x,(float) pVertex[1]->Pt_Point->y,(float) pVertex[1]->Pt_Point->z);
glEnd();
}

void E_Object2::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
glColor3fv(cols[G_Colour]);
glBegin(GL_LINES);
glVertex3f((float) pVertex[0]->Pt_Point->x,(float) pVertex[0]->Pt_Point->y,(float) pVertex[0]->Pt_Point->z);
glVertex3f((float) pVertex[1]->Pt_Point->x,(float) pVertex[1]->Pt_Point->y,(float) pVertex[1]->Pt_Point->z);
glEnd();
C3dVector vCent;
char sLab[20];
vCent=Get_Centroid();
glRasterPos3f ((float) vCent.x,(float) vCent.y,(float) vCent.z);
glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPSP);

if (bDrawLab==TRUE)
{
	sprintf_s(sLab,"E%i",G_label);
  OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
}
if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
{
   sprintf_s(sLab,"%f",*pResV);
   OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
}
}




C3dVector E_Object2::Get_Centroid()
{
C3dVector vT;
vT.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vT+=pVertex[j]->Get_Centroid();
}
vT.x/=iNoNodes;
vT.y/=iNoNodes;
vT.z/=iNoNodes;
return (vT);
}


void E_Object2::SetUpVec(C3dVector vIn)
{
 vUp=vIn;
}

void E_Object2::SetSec(int iA,int iB,int iC)
{
A=iA;
B=iB;
C=iC;
}


void E_Object2::ExportUNV(FILE* pFile)
{
int i;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
if ((iELType==21) || (iELType==22))
{
  fprintf(pFile,"%10i%10i%10i\n",A,B,C);
}
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%10i",pVertex[i]->G_label);
}
fprintf(pFile,"\n","");
}



void E_Object2::ExportUPVecs(FILE* pFile)
{
double dA1;
C3dVector Vz;
C3dVector Vy;
C3dVector Vx;
C3dVector Vu;
C3dMatrix M;
if (A==0)
{
  M.MakeUnit();
  Vu.Set(vUp.x,vUp.y,vUp.z);
	Vz.x=pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	Vz.y=pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	Vz.z=pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;
	Vz.Normalize();
	Vy.Set(0,0,1);
	double dDot;
	dDot = abs(Vy.Dot(Vz));
	if (dDot==1) 
	{
	  Vx.Set(0,1,0);
	  Vy=Vz.Cross(Vx);
	  Vy.Normalize();
	  Vx=Vy.Cross(Vz);
	  Vx.Normalize();

	}
	else
	{
	  Vx=Vy.Cross(Vz);
	  Vx.Normalize();
	  Vy=Vz.Cross(Vx);
	  Vy.Normalize();
	}
	M.SetColVec(1,Vx);
	M.SetColVec(2,Vy);
	M.SetColVec(3,Vz);
	M.Transpose();
	Vu=M.Mult(Vu);
	if (Vu.y!=0)
	{
	   dA1=atan2(Vu.x,Vu.y);
	   dA1=dA1*180/3.1415926535897932384626433832795;
	}
	else
	{
		dA1=0;
	}
	dA1+=90.0;
	fprintf(pFile,"%10i%10i\n",G_label,21);
	fprintf(pFile,"%10i%10i%10i%10i%10i\n",8,0,0,0,0);
	fprintf(pFile,"%15.6E%15.6E%15.6E\n",dA1,0.0,0.0);
}
else
{
	fprintf(pFile,"%10i%10i\n",G_label,21);
	fprintf(pFile,"%10i%10i%10i%10i%10i\n",0,1,0,0,0);
}
}


//----------------------------------------------------------------------------
//    ROD E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_Object2R, CObject )

E_Object2R::E_Object2R()
{
iDOFA=0;
iDOFB=0;
}

E_Object2R::~E_Object2R()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
}

void E_Object2R::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType, int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
int i=0;
for (i=0;i<2;i++)
{
  pVertex[i] = pInVertex[i];
}
A=0;
B=0;
C=0;
iONID=0;
OffA*=0;
OffB*=0;
}

void E_Object2R::SetDOFStringA(CString sDOF)
{
  iDOFA=GetDOFInt(sDOF);
}

void E_Object2R::SetDOFStringB(CString sDOF)
{
  iDOFB=GetDOFInt(sDOF);
}

void E_Object2R::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}
}

BOOL E_Object2R::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_Object2R::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
	  vUp.Serialize(ar);
    OffA.Serialize(ar);
    OffB.Serialize(ar);
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << A;
    ar << B;
	  ar << C;
    ar << iDOFA;
    ar << iDOFB;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
	  vUp.Serialize(ar);
    OffA.Serialize(ar);
    OffB.Serialize(ar);
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
	  ar >> A;
    ar >> B;
	  ar >> C;
    ar >> iDOFA;
    ar >> iDOFB;
	}
}


G_Object* E_Object2R::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object2R* gret = new E_Object2R;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->vUp=vUp;
gret->OffA=OffA;
gret->OffB=OffB;
gret->A=A;
gret->B=B;
gret->C=C;
gret->iDOFA=iDOFA;
gret->iDOFB=iDOFB;
gret->iONID=iONID;
gret->pPr=pPr;
gret->pParent=MESH;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object2R::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object2R* gret = new E_Object2R;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
gret->vUp=vUp;
gret->OffA=OffA;
gret->OffB=OffB;
Pt_Object* pT=Source->GetNode(iONID);
if (pT!=NULL)
{
  EInd=Source->GetNodeInd(pT);
  gret->iONID=Target->pNodes[iSInd+EInd]->G_label;
}
else
{
  gret->iONID=-1;
}
Pt_Object* nA=Source->GetNode(A);
if (nA!=NULL)
{
  EInd=Source->GetNodeInd(nA);
  gret->A = Target->pNodes[EInd+iSInd]->G_label;  //Orientation Node
}
else
{
  gret->A=A;
}
gret->B=B;
gret->C=C;
gret->iDOFA=iDOFA;
gret->iDOFB=iDOFB;
gret->pPr=NULL;
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}


G_Object* E_Object2R::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object2R* gret = new E_Object2R;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = pInVertex[0];
gret->pVertex[1] = pInVertex[1];
gret->vUp=vUp;
gret->OffA=OffA;
gret->OffB=OffB;
gret->A=A;
gret->B=B;
gret->C=C;
gret->iDOFA=iDOFA;
gret->iDOFB=iDOFB;
gret->pPr=pPr;
gret->pParent=Parrent;
gret->pResV = NULL;
return (gret);
}

// Draw Object line
void E_Object2R::Draw(CDC* pDC,int iDrawmode)
{
pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
}

int E_Object2R::GetLinkList(cLink* Links[200])
{
Links[0]=new cLink;
Links[0]->iColor=GetCol();
Links[0]->vVerts[0]=pVertex[0];
Links[0]->vVerts[1]=pVertex[1];
return (1);
}

G_Object* E_Object2R::GetNode(int i)
{
return (pVertex[i]);
}

void E_Object2R::OglDraw(int iDspFlgs,double dS1,double dS2)
{

glColor3fv(cols[G_Colour]);
C3dVector d[3];
int i;
for (i=0;i<2;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;
//Contour colours bit
float fCols[2]={0,0};
BOOL bD=FALSE;
int iVar;
iVar=ME->iCVar;
//Nodal data
if ((pVertex[0]->pResV != NULL) &&
    (pVertex[1]->pResV != NULL))
{
  bD=TRUE;
  fCols[0]=GetContourCol(*pVertex[0]->pResV->GetAddress(iVar));
  fCols[1]=GetContourCol(*pVertex[1]->pResV->GetAddress(iVar));
}
if (pResV!=NULL)
{
  bD=TRUE;
  fCols[0]=GetContourCol(*pResV->GetAddress(iVar));
  fCols[1]=GetContourCol(*pResV->GetAddress(iVar));
}

if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<2;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
  Selectable=1;
  if (pPr!=NULL)
  {
    BSec* pS = pPr->GetSec();
    if (pS!=NULL)
    {
      C3dMatrix TA=GetBeamTformA();
      C3dMatrix TB=GetBeamTformB();
      pS->OglDraw(iDspFlgs,TA,TB,d[0],d[1],fCols[0],fCols[1],bD);
    }
  }
  else
  {
    if (((iDspFlgs & DSP_CONT)==0) || (bD=TRUE))
    {
      glColor3fv(cols[124]);
      glEnable(GL_TEXTURE_1D);

      glBegin(GL_LINES);
        glTexCoord1f(fCols[0]);
        glVertex3f(pVertex[0]->Pt_Point->x+d[0].x,pVertex[0]->Pt_Point->y+d[0].y,pVertex[0]->Pt_Point->z+d[0].z);
        glTexCoord1f(fCols[1]);
        glVertex3f(pVertex[1]->Pt_Point->x+d[1].x,pVertex[1]->Pt_Point->y+d[1].y,pVertex[1]->Pt_Point->z+d[1].z);
      glEnd();
      glDisable(GL_TEXTURE_1D);
    }
    
  }
}
else
{
  Selectable=0;
}

}

void E_Object2R::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
C3dVector d[2];
int i;
int ind;
for (i=0;i<2;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;
ind=ME->iCVar;

if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<2;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
  Selectable=1;
  if ((iDspFlgs & DSP_LINE) > 0)
  {
    glColor3fv(cols[G_Colour]);
  }
  else
  {
    glColor3fv(cols[0]);
  }
  glBegin(GL_LINES);
    glVertex3f((float) pVertex[0]->Pt_Point->x+OffA.x+d[0].x,(float) pVertex[0]->Pt_Point->y+OffA.y+d[0].y,(float) pVertex[0]->Pt_Point->z+OffA.z+d[0].z);
    glVertex3f((float) pVertex[1]->Pt_Point->x+OffB.x+d[1].x,(float) pVertex[1]->Pt_Point->y+OffB.y+d[1].y,(float) pVertex[1]->Pt_Point->z+OffB.z+d[1].z);
  glEnd();
  C3dVector vCent;
  vCent=Get_Centroid();
  if (bDrawLab==TRUE)
  {
	  sprintf_s(sLab,"E%i",G_label);
    OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  }
  if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
  {
     sprintf_s(sLab,"%f",*pResV->GetAddress(ind));
     OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  }
  if (pPr!=NULL)
  {
    BSec* pS = pPr->GetSec();
    if (pS!=NULL)
    {
      C3dMatrix TMat=GetBeamTform();
      pS->OglDrawW(iDspFlgs,TMat,d[0],d[1]);
    }
  }
  if ((iDspFlgs & DSP_ELSYS)==0)
  {
    C3dMatrix mS = GetElSys();
    C3dVector vC = Get_Centroid();
    mS.Transpose();
    C3dVector vX=mS.GetColVec(1);
    C3dVector vY=mS.GetColVec(2);;
    C3dVector vZ=mS.GetColVec(3);;

    vX*=0.5*dS1; vY*=0.5*dS1; vZ*=0.5*dS1;
    vX+=vC;vY+=vC;vZ+=vC;

    glBegin(GL_LINES);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vX.x,(float) vX.y,(float) vX.z);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vY.x,(float) vY.y,(float) vY.z);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vZ.x,(float) vZ.y,(float) vZ.z);
    glEnd();
    glRasterPos3f ((float) vX.x,(float) vX.y,(float) vX.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPX);
    glRasterPos3f ((float) vY.x,(float) vY.y,(float) vY.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPY);
    glRasterPos3f ((float) vZ.x,(float) vZ.y,(float) vZ.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPZ);
  }
}
else
{
  Selectable=0;
}
}




C3dVector E_Object2R::Get_Centroid()
{
C3dVector v1;
C3dVector v2;
C3dVector vC;
v1=pVertex[0]->Get_Centroid();
v2=pVertex[1]->Get_Centroid();
v1+=OffA;
v2+=OffB;
vC=v2;
vC+=v1;
vC*=0.5;

return (vC);
}

C3dVector E_Object2R::GetDir()
{
C3dVector vRet;
C3dVector v1;
C3dVector v2;
v1=pVertex[0]->GetCoords();
v1+=OffA;
v2=pVertex[1]->GetCoords();
v2+=OffB;
vRet=v2;
vRet-=v1;
vRet.Normalize();
return (vRet);
}

void E_Object2R::SetUpVec(C3dVector vIn)
{
 vUp=vIn;
}

C3dMatrix E_Object2R::GetBeamTform()
{
C3dMatrix TRet;
C3dVector vX;
C3dVector vY;
C3dVector vZ;

vX=this->GetDir();;
vY=vUp;
vY.Normalize();
vZ=vY.Cross(vX);
vZ.Normalize();
vY=vZ.Cross(vX);
TRet.SetColVec(1,vZ);
TRet.SetColVec(2,vY);
TRet.SetColVec(3,vX);
C3dVector vC = Get_Centroid();
TRet.Translate2(vC.x,vC.y,vC.z);
return (TRet);
}

C3dMatrix E_Object2R::GetBeamTformA()
{
C3dMatrix TRet;
C3dVector vX;
C3dVector vY;
C3dVector vZ;

vX=this->GetDir();;
vY=vUp;
vY.Normalize();
vZ=vY.Cross(vX);
vZ.Normalize();
vY=vZ.Cross(vX);
TRet.SetColVec(1,vZ);
TRet.SetColVec(2,vY);
TRet.SetColVec(3,vX);

C3dVector vC = pVertex[0]->Get_Centroid();
vC+=OffA;
TRet.Translate2(vC.x,vC.y,vC.z);
return (TRet);
}

C3dMatrix E_Object2R::GetBeamTformB()
{
C3dMatrix TRet;
C3dVector vX;
C3dVector vY;
C3dVector vZ;

vX=this->GetDir();;
vY=vUp;
vY.Normalize();
vZ=vY.Cross(vX);
vZ.Normalize();
vY=vZ.Cross(vX);
TRet.SetColVec(1,vZ);
TRet.SetColVec(2,vY);
TRet.SetColVec(3,vX);
C3dVector vC = pVertex[1]->Get_Centroid();
vC+=OffB;
TRet.Translate2(vC.x,vC.y,vC.z);
return (TRet);
}


void E_Object2R::Transform(C3dMatrix TMat)
{
TMat.ClearTranslations();
vUp=TMat*vUp;
OffA=TMat*OffA;
OffB=TMat*OffB;
}

int E_Object2R::noDof()
{
return (3);
}

int E_Object2R::MaxBW()
{
int i;
int j;
int MaxDof;
int MinDof;
MaxDof=0;
MinDof=99999999;
for (i=0;i<iNoNodes;i++)
{
  for(j=0;j<noDof();j++)
  {
    if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j]>MaxDof))
	  {
       MaxDof=pVertex[i]->dof[j];
    }
	  if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j] < MinDof))
	  {
       MinDof=pVertex[i]->dof[j];
	  }
  }
}
int iRC;
if (MaxDof-MinDof<0)
{
  iRC=0;
}
else
{
  iRC=MaxDof-MinDof;
}
return (iRC);
}

Mat E_Object2R::GetStiffMat(PropTable* PropsT,MatTable* MatT)
{
double ea=10000;
double eal=10000;
double x1,y1,z1,x2,y2,z2;
double ell;
int MID=-1;
char S1[80];
Mat KM(6,6);
Mat t(6,6);
Mat tt(6,6);
KM.MakeZero();
t.MakeZero();
tt.MakeZero();

Property* pS=PropsT->GetItem(PID);
if (pS!=NULL)
{
  MID=pS->GetDefMatID();
}
Material* pM=MatT->GetItem(MID);
if (pS==NULL)
{
  sprintf_s(S1,"ERROR PROPERTY NOT FOUND FOR EL %i",G_label);
  outtext1(S1);
}
if (pM==NULL)
{  
  sprintf_s(S1,"ERROR MATERIAL NOT FOUND FOR EL %i",G_label);
  outtext1(S1); 
}
if ((pS!=NULL) && (pM!=NULL))
{
  if (pS->iType==11)
  {
    PROD* pB=(PROD*) pS;
    MAT1* pM1=(MAT1*) pM;
    ea=pB->A*pM1->dE;
  }
  else
  {
    sprintf_s(S1,"ERROR INVALIS PROPERTY FOR EL %i",G_label);
    outtext1(S1);
  }
}
else
{
  sprintf_s(S1,"ERROR UNABLE TO CALCULATE PROPERTIES FOR EL %i",G_label);
  outtext1(S1); 
}



x1=pVertex[0]->Pt_Point->x;
y1=pVertex[0]->Pt_Point->y;
z1=pVertex[0]->Pt_Point->z;
x2=pVertex[1]->Pt_Point->x;
y2=pVertex[1]->Pt_Point->y;
z2=pVertex[1]->Pt_Point->z;
x1-=x2;y1-=y2;z1-=z2;
ell=pow(x1*x1+y1*y1+z1*z1,0.5);
eal=ea/ell;

*KM.mn(1,1)=eal;
*KM.mn(4,4)=eal;
*KM.mn(1,4)=-eal;
*KM.mn(4,1)=-eal;
KM.diag();
C3dMatrix r;
r=GetElSys();
Mat mr(3,3);
*mr.mn(1,1)=r.m_00; *mr.mn(1,2)=r.m_01; *mr.mn(1,3)=r.m_02;
*mr.mn(2,1)=r.m_10; *mr.mn(2,2)=r.m_11; *mr.mn(2,3)=r.m_12;
*mr.mn(3,1)=r.m_20; *mr.mn(3,2)=r.m_21; *mr.mn(3,3)=r.m_22;


int i,j;
for (i=1;i<4;i++)
{
  for (j=1;j<4;j++)
  {
     *t.mn(i,j) = *mr.mn(i,j);
     *t.mn(i+3,j+3) = *mr.mn(i,j);
     *tt.mn(i,j) = *mr.mn(i,j);
     *tt.mn(i+3,j+3) = *mr.mn(i,j);
  }
}
tt.Transpose();
Mat Kmt;
Mat tKmt;
Kmt=KM*t;
tKmt=tt*Kmt;

KM=tKmt;
t.clear();
tt.clear();
Kmt.clear();
tKmt.clear();
mr.clear();
return (KM);
}

Vec<int> E_Object2R::GetSteerVec2d()
{
Vec<int> V(2*3);
*V.nn(1)=pVertex[0]->dof[0];
*V.nn(2)=pVertex[0]->dof[1];
*V.nn(3)=pVertex[0]->dof[2];
*V.nn(4)=pVertex[1]->dof[0];
*V.nn(5)=pVertex[1]->dof[1];
*V.nn(6)=pVertex[1]->dof[2];

return(V);
}

C3dMatrix E_Object2R::GetElSys()
{
C3dMatrix vR;
C3dVector vX;
C3dVector vY;
C3dVector vZ;

vX.x=pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
vX.y=pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
vX.z=pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;
vZ=vUp;
vX.Normalize();
vZ.Normalize();
vY=vZ.Cross(vX);
vY.Normalize();
vZ=vX.Cross(vY);
vR.SetColVec(1,vX);
vR.SetColVec(2,vY);
vR.SetColVec(3,vZ);
vR.Transpose();
return (vR);
}


void E_Object2R::SetSec(int iA,int iB,int iC)
{
A=iA;
B=iB;
C=iC;
}

void E_Object2R::ExportNAS(FILE* pFile)
{
C3dMatrix TMat;
if (iELType==11)
{
  fprintf(pFile,"%8s%8i%8i%8i%8i\n","CROD    ",G_label,PID,pVertex[0]->G_label,pVertex[1]->G_label);
}
}




void E_Object2R::ExportUNV(FILE* pFile)
{
int i;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
if ((iELType==21) || (iELType==22))
{
  fprintf(pFile,"%10i%10i%10i\n",A,B,C);
}
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%10i",pVertex[i]->G_label);
}
fprintf(pFile,"\n","");
}



void E_Object2R::ExportUPVecs(FILE* pFile)
{
double dA1;
C3dVector Vz;
C3dVector Vy;
C3dVector Vx;
C3dVector Vu;
C3dMatrix M;
if (A==0)
{
  M.MakeUnit();
  Vu.Set(vUp.x,vUp.y,vUp.z);
	Vz.x=pVertex[1]->Pt_Point->x-pVertex[0]->Pt_Point->x;
	Vz.y=pVertex[1]->Pt_Point->y-pVertex[0]->Pt_Point->y;
	Vz.z=pVertex[1]->Pt_Point->z-pVertex[0]->Pt_Point->z;
	Vz.Normalize();
	Vy.Set(0,0,1);
	double dDot;
	dDot = abs(Vy.Dot(Vz));
	if (dDot==1) 
	{
	  Vx.Set(0,1,0);
	  Vy=Vz.Cross(Vx);
	  Vy.Normalize();
	  Vx=Vy.Cross(Vz);
	  Vx.Normalize();

	}
	else
	{
	  Vx=Vy.Cross(Vz);
	  Vx.Normalize();
	  Vy=Vz.Cross(Vx);
	  Vy.Normalize();
	}
	M.SetColVec(1,Vx);
	M.SetColVec(2,Vy);
	M.SetColVec(3,Vz);
	M.Transpose();
	Vu=M.Mult(Vu);
	if (Vu.y!=0)
	{
	   dA1=atan2(Vu.x,Vu.y);
	   dA1=dA1*180/3.1415926535897932384626433832795;
	}
	else
	{
		dA1=0;
	}
	dA1+=90.0;
	fprintf(pFile,"%10i%10i\n",G_label,21);
	fprintf(pFile,"%10i%10i%10i%10i%10i\n",8,0,0,0,0);
	fprintf(pFile,"%15.6E%15.6E%15.6E\n",dA1,0.0,0.0);
}
else
{
	fprintf(pFile,"%10i%10i\n",G_label,21);
	fprintf(pFile,"%10i%10i%10i%10i%10i\n",0,1,0,0,0);
}
}
//----------------------------------------------------------------------------
//    CBEAM E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC(E_Object2B, CObject )

void E_Object2B::ExportNAS(FILE* pFile)
{
C3dMatrix TMat;
if (iELType==21)
{
  fprintf(pFile,"%8s%8i%8i%8i%8i","CBAR    ",G_label,PID,pVertex[0]->G_label,pVertex[1]->G_label);
}
else if (iELType==22)
{
  fprintf(pFile,"%8s%8i%8i%8i%8i","CBEAM   ",G_label,PID,pVertex[0]->G_label,pVertex[1]->G_label);
}
if (iONID>0)
{
  fprintf(pFile,"%8i\n",iONID);
}
else
{
  TMat.MakeUnit();
  if (pVertex[0]->OutSys>0)
  {
    ME_Object* pM = (ME_Object*) this->pParent;
    CoordSys* pSys=pM->GetSys(pVertex[0]->OutSys);
    if (pSys!=NULL)
    {
      TMat=pSys->GetTMat();
      TMat.Transpose();
    }
  }
  C3dVector vU;
  vU=TMat*vUp;
  fprintf(pFile,"%8s%8s%8s\n",e8(vU.x),e8(vU.y),e8(vU.z));
}
fprintf(pFile,"%8s%8s%8s","        ",GetDOFString(iDOFA),GetDOFString(iDOFB));

  TMat.MakeUnit();
  if (pVertex[0]->OutSys>0)
  {
    ME_Object* pM = (ME_Object*) this->pParent;
    CoordSys* pSys=pM->GetSys(pVertex[0]->OutSys);
    if (pSys!=NULL)
    {
      TMat=pSys->GetTMat();
      TMat.Transpose();
    }
  }
  C3dVector vD1;
  vD1=TMat*OffA;
  fprintf(pFile,"%8s%8s%8s",e8(vD1.x),e8(vD1.y),e8(vD1.z));
  TMat.MakeUnit();
  if (pVertex[0]->OutSys>0)
  {
    ME_Object* pM = (ME_Object*) this->pParent;
    CoordSys* pSys=pM->GetSys(pVertex[1]->OutSys);
    if (pSys!=NULL)
    {
      TMat=pSys->GetTMat();
      TMat.Transpose();
    }
  }
  C3dVector vD2;
  vD2=TMat*OffB;
  fprintf(pFile,"%8s%8s%8s\n",e8(vD2.x),e8(vD2.y),e8(vD2.z));

}

int E_Object2B::noDof()
{
return (6);
}



Mat E_Object2B::GetStiffMat(PropTable* PropsT,MatTable* MatT)
{
Mat KM(12,12);
Mat t(12,12);
Mat tt(12,12);
KM.MakeZero();
t.MakeZero();
tt.MakeZero();
double ea=50000;
double eiy=10000;
double eiz=10000;
double gj=10000;
double x1,y1,z1,x2,y2,z2;
double a1,a2,a3,a4,a5,a6,a7,a8,a9;
double ell;
int MID=-1;
char S1[80];
Property* pS=PropsT->GetItem(PID);
if (pS!=NULL)
{
  MID=pS->GetDefMatID();
}
Material* pM=MatT->GetItem(MID);
if (pS==NULL)
{
  sprintf_s(S1,"ERROR PROPERTY NOT FOUND FOR EL %i",G_label);
  outtext1(S1);
}
if (pM==NULL)
{  
  sprintf_s(S1,"ERROR MATERIAL NOT FOUND FOR EL %i",G_label);
  outtext1(S1); 
}
if ((pS!=NULL) && (pM!=NULL))
{
  if (pS->iType==5)
  {
    PBARL* pB=(PBARL*) pS;
    MAT1* pM1=(MAT1*) pM;
    ea=pB->A*pM1->dE;
    eiy=pB->Iyy*pM1->dE;
    eiz=pB->Izz*pM1->dE;
    double g;
    g=pM1->dE/(2*(1+pM1->dNU));
    gj=g*pB->J;
  }
  else
  {
    sprintf_s(S1,"ERROR INVALIS PROPERTY FOR EL %i",G_label);
    outtext1(S1);
  }
}
else
{
  sprintf_s(S1,"ERROR UNABLE TO CALCULATE PROPERTIES FOR EL %i",G_label);
  outtext1(S1); 
}

x1=pVertex[0]->Pt_Point->x;
y1=pVertex[0]->Pt_Point->y;
z1=pVertex[0]->Pt_Point->z;
x2=pVertex[1]->Pt_Point->x;
y2=pVertex[1]->Pt_Point->y;
z2=pVertex[1]->Pt_Point->z;

x1-=x2;y1-=y2;z1-=z2;
ell=pow(x1*x1+y1*y1+z1*z1,0.5);


a1=ea/ell; a2=12.0*eiz/(ell*ell*ell);
a3=12.0*eiy/(ell*ell*ell);a4=6.0*eiz/(ell*ell);
a5=6.0*eiy/(ell*ell);a6=4.0*eiz/ell;
a7=4.0*eiy/ell;a8=gj/ell;
*KM.mn(1,1)=a1;
*KM.mn(7,7)=a1;
*KM.mn(1,7)=-a1;
*KM.mn(7,1)=-a1;
*KM.mn(2,2)=a2;
*KM.mn(8,8)=a2;

*KM.mn(2,8)=-a2;
*KM.mn(8,2)=-a2;
*KM.mn(3,3)=a3;
*KM.mn(9,9)=a3;
*KM.mn(3,9)=-a3;
*KM.mn(9,3)=-a3;

*KM.mn(4,4)=a8;
*KM.mn(10,10)=a8;
*KM.mn(4,10)=-a8;
*KM.mn(10,4)=-a8;
*KM.mn(5,5)=a7;

*KM.mn(11,11)=a7;
*KM.mn(5,11)=0.5*a7;
*KM.mn(11,5)=0.5*a7;
*KM.mn(6,6)=a6;
*KM.mn(12,12)=a6;

*KM.mn(6,12)=0.5*a6;
*KM.mn(12,6)=0.5*a6;
*KM.mn(2,6)=a4;
*KM.mn(6,2)=a4;
*KM.mn(2,12)=a4;

*KM.mn(12,2)=a4;
*KM.mn(6,8)=-a4;
*KM.mn(8,6)=-a4;
*KM.mn(8,12)=-a4;
*KM.mn(12,8)=-a4;

*KM.mn(5,9)=a5;
*KM.mn(9,5)=a5;
*KM.mn(9,11)=a5;
*KM.mn(11,9)=a5;
*KM.mn(3,5)=-a5;
*KM.mn(5,3)=-a5;
*KM.mn(3,11)=-a5;
*KM.mn(11,3)=-a5;
C3dMatrix r;
r=GetElSys();
Mat mr(3,3);
*mr.mn(1,1)=r.m_00; *mr.mn(1,2)=r.m_01; *mr.mn(1,3)=r.m_02;
*mr.mn(2,1)=r.m_10; *mr.mn(2,2)=r.m_11; *mr.mn(2,3)=r.m_12;
*mr.mn(3,1)=r.m_20; *mr.mn(3,2)=r.m_21; *mr.mn(3,3)=r.m_22;


int i,j;
for (i=1;i<4;i++)
{
  for (j=1;j<4;j++)
  {
     *t.mn(i,j) = *mr.mn(i,j);
     *t.mn(i+3,j+3) = *mr.mn(i,j);
     *t.mn(i+6,j+6) = *mr.mn(i,j);
     *t.mn(i+9,j+9) = *mr.mn(i,j);
     *tt.mn(i,j) = *mr.mn(i,j);
     *tt.mn(i+3,j+3) = *mr.mn(i,j);
     *tt.mn(i+6,j+6) = *mr.mn(i,j);
     *tt.mn(i+9,j+9) = *mr.mn(i,j);
  }
}
tt.Transpose();
Mat Kmt;
Mat tKmt;
Kmt=KM*t;
tKmt=tt*Kmt;

KM=tKmt;
t.clear();
tt.clear();
Kmt.clear();
tKmt.clear();
mr.clear();
return (KM);
}

Vec<int> E_Object2B::GetSteerVec2d()
{
Vec<int> V(2*6);
*V.nn(1)=pVertex[0]->dof[0];
*V.nn(2)=pVertex[0]->dof[1];
*V.nn(3)=pVertex[0]->dof[2];
*V.nn(4)=pVertex[0]->dof[3];
*V.nn(5)=pVertex[0]->dof[4];
*V.nn(6)=pVertex[0]->dof[5];
*V.nn(7)=pVertex[1]->dof[0];
*V.nn(8)=pVertex[1]->dof[1];
*V.nn(9)=pVertex[1]->dof[2];
*V.nn(10)=pVertex[1]->dof[3];
*V.nn(11)=pVertex[1]->dof[4];
*V.nn(12)=pVertex[1]->dof[5];
return(V);
}



IMPLEMENT_DYNAMIC( E_Object3, CObject )
//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//-
E_Object3::~E_Object3()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
pVertex[2]=NULL;
}

void E_Object3::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,int inMCys,double inMAng,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
iMCys=inMCys;
MAng=inMAng;
int i=0;
for (i=0;i<3;i++)
   {
    pVertex[i] = pInVertex[i];
   }
dZOFFS=0;
}

void E_Object3::Reverse()
{
Pt_Object* pT[8];
pT[0]=pVertex[0];
pT[1]=pVertex[1];
pT[2]=pVertex[2];
pVertex[0] = pT[0];
pVertex[1] = pT[2];
pVertex[2] = pT[1];
}


void E_Object3::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}

}

BOOL E_Object3::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_Object3::GetKMat()
{
//No integeration needed for
//this element as constant strain	

//Bmem[0][0] = Y2 - Y3;
//Bmem[0][1] = 0;
//Bmem[0][2] = Y3 - Y1;
//Bmem[0][3] = 0;
//Bmem[0][4] = Y1 - Y2;
//Bmem[0][5] = 0;

//Bmem[1][0] = 0;
//Bmem[1][1] = X3 - X2;
//Bmem[1][2] = 0;
//Bmem[1][3] = X1 - X3;
//Bmem[1][4] = 0;
//Bmem[1][5] = X2 - X1;

//Bmem[2][0] = X3 - X2;
//Bmem[2][1] = Y2 - Y3;
//Bmem[2][2] = X1 - X3;
//Bmem[2][3] = Y3 - Y1;
//Bmem[2][4] = X2 - X1;
//Bmem[2][5] = Y1 - Y2;
}

void E_Object3::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
    ar<<iMCys;
    ar<<MAng;
    ar<<dZOFFS;
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << pVertex[2]->G_label;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
    ar>>iMCys;
    ar>>MAng;
    ar>>dZOFFS;
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[2] = MESH->GetNode(iNd);
	}
  pPr=NULL;
}

void E_Object3::ExportNAS(FILE* pFile)
{
int i;
fprintf(pFile,"%8s%8i%8i","CTRIA3  ",G_label,PID);
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%8i",pVertex[i]->G_label);
}
fprintf(pFile,"%8s%8s\n",e8(MAng),e8(dZOFFS));
}

void E_Object3::ExportUNV(FILE* pFile)
{
int i;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%10i",pVertex[i]->G_label);
}
fprintf(pFile,"\n","");
}

G_Object* E_Object3::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object3* gret = new E_Object3;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->pVertex[2] = MESH->GetNode(pVertex[2]->G_label);
gret->pParent=MESH;
gret->iMCys=iMCys;
gret->MAng=MAng;
gret->dZOFFS=dZOFFS;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object3::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object3* gret = new E_Object3;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;

EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[2]);
gret->pVertex[2] = Target->pNodes[EInd+iSInd];

gret->pParent=Target;
gret->iMCys=iMCys;
gret->MAng=MAng;
gret->dZOFFS=dZOFFS;
gret->pPr=NULL;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object3::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object3* gret = new E_Object3;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = pInVertex[0];
gret->pVertex[1] = pInVertex[1];
gret->pVertex[2] = pInVertex[2];
gret->pParent=Parrent;
gret->iMCys=iMCys;
gret->MAng=MAng;
gret->dZOFFS=dZOFFS;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

// Draw Object line
void E_Object3::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
}

int E_Object3::GetLinkList(cLink* Links[200])
{
int ic;

ic=GetCol();
Links[0]=new cLink;
Links[0]->vVerts[0]=pVertex[0];
Links[0]->vVerts[1]=pVertex[1];
Links[0]->iColor=ic;
Links[1]=new cLink;
Links[1]->vVerts[0]=pVertex[1];
Links[1]->vVerts[1]=pVertex[2];
Links[1]->iColor=ic;
Links[2]=new cLink;
Links[2]->vVerts[0]=pVertex[2];
Links[2]->vVerts[1]=pVertex[0];
Links[2]->iColor=ic;
return (3);
}

G_Object* E_Object3::GetNode(int i)
{
return (pVertex[i]);
}

void E_Object3::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
C3dVector d[3];
int i;
int ind;
for (i=0;i<3;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;
ind=ME->iCVar;
if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<3;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
  Selectable=1;
  if ((iDspFlgs & DSP_ELEMENTS)>0)
  {

    if ((iDspFlgs & DSP_LINE) > 0)
    {
      glColor3fv(cols[G_Colour]);
    }
    else
    {
      glColor3fv(cols[0]);
    }
    C3dVector vN;
    C3dVector vOff;
    vN=Get_Normal();
    //Need to calculate the offsets here
    if (((iDspFlgs & DSP_OFF)>0) && (dZOFFS!=DBL_MAX))
    {
       vOff=vN;
       vOff*=dZOFFS;
    }
    else
    {
       vOff*=0; 
    }
    double dt=0;
    if (pPr!=NULL)
    {
      dt=pPr->GetThk();
      dt*=0.5;
    }
    vN*=dt;
    if ((iDspFlgs & DSP_THK)>0)
    {
  	  glBegin(GL_LINES);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	   
      glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);

      glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
      glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
      glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
      glEnd();
    }
    else
    {
      vN*=0;
      glBegin(GL_LINES);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
      glEnd();
    }
	  C3dVector vCent;
    vCent=Get_Centroid();
    if (bDrawLab==TRUE)
	  {
	    sprintf_s(sLab,"E%i",G_label);
	    OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
	  }
    if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
    {
       sprintf_s(sLab,"%f",*pResV->GetAddress(ind));
       OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
    }
  }
  if ((iDspFlgs & DSP_ELSYS)==0)
  {
    C3dMatrix mS = GetElSys();
    C3dVector vC = Get_Centroid();
    mS.Transpose();
    C3dVector vX=mS.GetColVec(1);
    C3dVector vY=mS.GetColVec(2);;
    C3dVector vZ=mS.GetColVec(3);;

    vX*=0.5*dS1; vY*=0.5*dS1; vZ*=0.5*dS1;
    vX+=vC;vY+=vC;vZ+=vC;

    glBegin(GL_LINES);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vX.x,(float) vX.y,(float) vX.z);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vY.x,(float) vY.y,(float) vY.z);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vZ.x,(float) vZ.y,(float) vZ.z);
    glEnd();
    glRasterPos3f ((float) vX.x,(float) vX.y,(float) vX.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPX);
    glRasterPos3f ((float) vY.x,(float) vY.y,(float) vY.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPY);
    glRasterPos3f ((float) vZ.x,(float) vZ.y,(float) vZ.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPZ);

    //C3dVector vTP=GetTestPt();
    //glBegin(GL_LINES);
    //  glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
    //  glVertex3f((float) vTP.x,(float) vTP.y,(float) vTP.z);
    //glEnd();
  }
}
else
{
  Selectable=0;
}
}

void E_Object3::OglDraw(int iDspFlgs,double dS1,double dS2)
{
C3dVector d[3];
int i;
for (i=0;i<3;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;

      BOOL bD=FALSE;
      float fCols[3]={0,0,0};
      int iVar;
      iVar=ME->iCVar;
      //Nodal data
      if ((pVertex[0]->pResV != NULL) &&
          (pVertex[1]->pResV != NULL) &&
          (pVertex[2]->pResV != NULL))
      {
        bD=TRUE;
        fCols[0]=GetContourCol(*pVertex[0]->pResV->GetAddress(iVar));
        fCols[1]=GetContourCol(*pVertex[1]->pResV->GetAddress(iVar));
        fCols[2]=GetContourCol(*pVertex[2]->pResV->GetAddress(iVar));
      }
      if (pResV!=NULL)
      {
        bD=TRUE;
        fCols[0]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[1]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[2]=GetContourCol(*pResV->GetAddress(iVar));
      }

C3dVector v1;
C3dVector v2;
C3dVector Vn;

C3dVector vN;
C3dVector vOff;
vN=Get_Normal();
if (((iDspFlgs & DSP_OFF)>0) && (dZOFFS!=DBL_MAX))
{
  vOff=vN;
  vOff*=dZOFFS;
}
else
{
  vOff*=0; 
}

double dt=0;
if (pPr!=NULL)
{
  dt=pPr->GetThk();
  dt*=0.5;
}
vN*=dt;
Vn =Get_Normal();
Vn.Normalize();

if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<3;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
	Selectable=1;
	glColor3fv(cols[G_Colour]);
  if (((iDspFlgs & DSP_CONT)>0) || (bD==FALSE))
  {
    if ((iDspFlgs & DSP_THK)>0)
    {
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glEnd();
      glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
      glEnd();

      glBegin(GL_POLYGON);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
      glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glEnd();

      glBegin(GL_POLYGON);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
      glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glEnd();

      glBegin(GL_POLYGON);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
      glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glEnd();

    }
    else
    {
      vN*=0;
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glEnd();
    }
  }
  else
  {
      vN*=0;

      if (bD)
      {
      glColor3fv(cols[124]);
      glEnable(GL_TEXTURE_1D);
	    glBegin(GL_POLYGON);
      glTexCoord1f(fCols[0]);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
      glTexCoord1f(fCols[1]);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
      glTexCoord1f(fCols[2]);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glEnd();
      glDisable(GL_TEXTURE_1D);
      }
  }
}
else
{
  Selectable=0;
}
}

int E_Object3::GetfaceList(cFace* Faces[6])
{
Faces[0]=new cFace();
Faces[0]->vVerts[0]=pVertex[0];
Faces[0]->vVerts[1]=pVertex[1];
Faces[0]->vVerts[2]=pVertex[2];
Faces[0]->NoVert=3;
Faces[0]->iColor=GetCol();
return(1);
}

//void E_Object3::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
//{
////int j=0;
////for (j=0;j<iNoNodes;j++)
////{
////   pVertex[j]->SetToScr(pModMat,pScrTran);
////}
//C3dVector vC;
//vC=Get_Centroid();
//vC.SetToScr(pModMat,pScrTran);
//SelPt=vC;
//
//}



C3dVector E_Object3::Get_Centroid()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=0.333;
*FunPnt.mn(1,2)=0.333;
fun=ShapeFun(FunPnt,1);
C3dVector vT;
vT.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vT+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
}

fun.clear();
FunPnt.clear();
return (vT);
}

C3dMatrix E_Object3::GetElSys()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=0.33;
*FunPnt.mn(1,2)=0.33;
fun=ShapeDer(FunPnt,1);
C3dVector vX,vY,vT;
vX.Set(0,0,0);
vY.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vX+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
   vY+=pVertex[j]->Get_Centroid()**fun.mn(2,j+1);
}
vT=vX.Cross(vY);
vT.Normalize();
vX=pVertex[1]->GetCoords();
vX-=pVertex[0]->GetCoords();
vX.Normalize();
vY=vT.Cross(vX);
fun.clear();
FunPnt.clear();
C3dMatrix vR;
vR.SetColVec(1,vX);
vR.SetColVec(2,vY);
vR.SetColVec(3,vT);
vR.Transpose();
return (vR);
}

C3dVector E_Object3::GetTestPt()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=1;
*FunPnt.mn(1,2)=0;
fun=ShapeFun(FunPnt,1);
C3dVector vX;
vX.Set(0,0,0);

int j=0;
for (j=0;j<iNoNodes;j++)
{
   vX+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
}
return (vX);
}


void E_Object3::Info()
{
  char S1[80];
  sprintf_s(S1,"LAB: %i COL: %i PID: %i ELTP: %i MCID: %i ANG: %f ",G_label,G_Colour,PID,iELType,iMCys,MAng);
  outtext1(S1); 
  sprintf_s(S1,"NODES %i %i %i",pVertex[0]->G_label,pVertex[1]->G_label,pVertex[2]->G_label);
  outtext1(S1); 
}

C3dVector E_Object3::Get_Normal()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=0.333;
*FunPnt.mn(1,2)=0.333;
fun=ShapeDer(FunPnt,1);
C3dVector vX,vY,vT;
vX.Set(0,0,0);
vY.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vX+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
   vY+=pVertex[j]->Get_Centroid()**fun.mn(2,j+1);
}
vT=vX.Cross(vY);
fun.clear();
FunPnt.clear();
vT.Normalize();
return (vT);
}



//void E_Object3::HighLight(CDC* pDC)
//{
////CPoint cPt1;
////CPoint cPt2;
////cPt1.x = (long) 0.5*((long) pVertex[2]->DSP_Point->x-(long) pVertex[0]->DSP_Point->x)+(long) pVertex[0]->DSP_Point->x;
////cPt1.y = (long) 0.5*((long) pVertex[2]->DSP_Point->y-(long) pVertex[0]->DSP_Point->y)+(long) pVertex[0]->DSP_Point->y;
////cPt2.x = (long) (0.3*((long) pVertex[1]->DSP_Point->x-cPt1.x)+cPt1.x);
////cPt2.y = (long) (0.3*((long) pVertex[1]->DSP_Point->y-cPt1.y)+cPt1.y);
//pDC->Ellipse(SelPt.x+5,SelPt.y+5,SelPt.x-5,SelPt.y-5);
//}


//G_ObjectD E_Object3::SelDist(CPoint InPT,Filter FIL)
//{
//G_ObjectD Ret;
//double x,y,d;
//x =  SelPt.x-InPT.x;
//y =  SelPt.y-InPT.y;
//d=(x*x+y*y);
//Ret.Dist=d;
//Ret.pObj=this;
//return (Ret);
//}



Mat E_Object3::Sample(int iNo)
{
Mat Pts(iNo,3);
if (iNo == 1)
{
  *Pts.mn(1,1) = (double) 1/3;
  *Pts.mn(1,2) = (double) 1/3;
  *Pts.mn(1,3) = (double) 0.5;
}
else if (iNo == 3)
{
  *Pts.mn(1,1) = (double) 0.5;
  *Pts.mn(1,2) = (double) 0.5;
  *Pts.mn(1,3) = (double) 1/3;

  *Pts.mn(1,1) = (double) 0.5;
  *Pts.mn(1,2) = (double) 0;
  *Pts.mn(1,3) = (double) 1/3;

  *Pts.mn(1,1) = (double) 0;
  *Pts.mn(1,2) = (double) 0.5;
  *Pts.mn(1,3) = (double) 1/3;
}
return (Pts);
}


int E_Object3::MaxBW()
{
int i;
int j;
int MaxDof;
int MinDof;
MaxDof=0;
MinDof=99999999;
for (i=0;i<iNoNodes;i++)
{
  for(j=0;j<6;j++)
  {
    if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j]>MaxDof))
	{
       MaxDof=pVertex[i]->dof[j];
    }
	if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j] < MinDof))
	{
       MinDof=pVertex[i]->dof[j];
	}
  }
}
int iRC;
if (MaxDof-MinDof<0)
{
  iRC=0;
}
else
{
  iRC=MaxDof-MinDof;
}
return (iRC);
}

Mat E_Object3::getCoords2d()
{
int i;
Mat coord(iNoNodes,2);
for (i=0;i<iNoNodes;i++)
{
  *coord.mn(i+1, 1) = pVertex[i]->Pt_Point->x;
  *coord.mn(i+1, 2) = pVertex[i]->Pt_Point->y;
}
return (coord);
}

//*******************************************************************
//Get The coordinates after transforming the element to the XY plain
//********************************************************************
Mat E_Object3::getCoords3d()
{
int i;
C3dVector p;
Mat coord(iNoNodes,2);
C3dMatrix M3=this->GetElSys();
//M3.Transpose();
for (i=0;i<iNoNodes;i++)
{
  C3dVector p,v;
  p.x=pVertex[i]->Pt_Point->x;
  p.y=pVertex[i]->Pt_Point->y;
  p.z=pVertex[i]->Pt_Point->z;
  v=M3.Mult(p);
  *coord.mn(i+1,1)=v.x;
  *coord.mn(i+1,2)=v.y;
}
return (coord);
}


Mat E_Object3::ShapeDer(Mat Points, int i)
{
Mat der(2,3);
*der.mn(1, 1) = 1;
*der.mn(1, 2) = 0;
*der.mn(1, 3) = -1;
*der.mn(2, 1) = 0;
*der.mn(2, 2) = 1;
*der.mn(2, 3) = -1;
return(der);
}

Vec<int> E_Object3::GetSteerVec2d()
{
Vec<int> V(18);
*V.nn(1)=pVertex[0]->dof[0];
*V.nn(2)=pVertex[0]->dof[1];
*V.nn(3)=pVertex[0]->dof[2];
*V.nn(4)=pVertex[0]->dof[3];
*V.nn(5)=pVertex[0]->dof[4];
*V.nn(6)=pVertex[0]->dof[5];

*V.nn(7)=pVertex[1]->dof[0];
*V.nn(8)=pVertex[1]->dof[1];
*V.nn(9)=pVertex[1]->dof[2];
*V.nn(10)=pVertex[1]->dof[3];
*V.nn(11)=pVertex[1]->dof[4];
*V.nn(12)=pVertex[1]->dof[5];

*V.nn(13)=pVertex[2]->dof[0];
*V.nn(14)=pVertex[2]->dof[1];
*V.nn(15)=pVertex[2]->dof[2];
*V.nn(16)=pVertex[2]->dof[3];
*V.nn(17)=pVertex[2]->dof[4];
*V.nn(18)=pVertex[2]->dof[5];

return(V);
}

Mat E_Object3::ShapeFun(Mat Points, int i)
{
Mat fun(1,3);
double xi,eta;
double c1,c2,c3;
eta = *Points.mn(i, 2);
xi = *Points.mn(i, 1);
c1=xi;
c2=eta;
c3=1-xi-eta;

*fun.mn(1,1) = c1;
*fun.mn(1,2) = c2;
*fun.mn(1,3) = c3;
return(fun);
}

int E_Object3::noDof()
{
return(6);
}

Mat E_Object3::GetStiffMat(PropTable* PropsT,MatTable* MatT)
{
Mat bee;   //strain displacement matrix
int nip=0;

Mat coord2;
Mat deriv;
Mat deriv2;
Mat fun;
Mat Points;
Mat jac;
int i;
double det;
Mat bT;
Mat db;
Mat bdb;
int iDof;
int iS;
int MID=-1;
double dE=210e9;
double dv=0.29;
char S1[80];
double dthk=0.001;

Property* pS=PropsT->GetItem(PID);
if (pS!=NULL)
{
  MID=pS->GetDefMatID();
}
Material* pM=MatT->GetItem(MID);
if (pS==NULL)
{
  sprintf_s(S1,"PROPERTY NOT FOUND FOR EL %i",G_label);
  outtext1(S1);
}
if (pM==NULL)
{  
  sprintf_s(S1,"MATERIAL NOT FOUND FOR EL %i",G_label);
  outtext1(S1); 
}
//Get Shell thick ness

if (((iELType==91) || (iELType==94)) && (pS!=NULL))
{
  PSHELL* pSh = (PSHELL*) pS;
  dthk=pSh->dT;
}

if ((pM!=NULL) && (pM->iType = 1))
{
  MAT1* pIsen = (MAT1*) pM;
  dE=pIsen->dE;
  dv=pIsen->dNU;
}
//This part calculates the 2d membraine stiffness
iDof=2;   //2 dof X,Y per node
nip=1;    //1 intergration points
iS=3;

Mat KM(iDof*iNoNodes,iDof*iNoNodes);
Mat dee=DeeMat(dE,dv,iS);
Mat coord=getCoords3d();
C3dMatrix M3=this->GetElSys();
Points=Sample(nip);
//Membraine stiffness calculation
//for dof 12
  for(i=1;i<nip+1;i++)
  {
    det = 0;
    fun.clear();deriv.clear();jac.clear(),deriv2.clear();
    bT.clear();db.clear();bdb.clear();bee.clear();
    fun=ShapeFun(Points, i);
    deriv=ShapeDer(Points, i);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee=bmat(coord, deriv2,iS,iDof);
    bT = bee;
    bT.Transpose();
    db = dee*bee;
    bdb = bT*db;
    det*=*Points.mn(i,3);
    bdb*=det;
    KM+=bdb;
  }
KM*=dthk;
fun.clear();deriv.clear();jac.clear(),deriv2.clear();
bT.clear();db.clear();bdb.clear();bee.clear();
//Mindlin Formulation
//Sheer Stifness Calculation
//Full intergation at this point 4 sample point 
//I think need to be reduced integration 1 sample point
double G,kk;
int k;
dee.clear();
dee.Create(2,2);
G=0.5*dE/(1+dv);
kk=5.0/6.0;
*dee.mn(1,1) = kk*G*dthk;
*dee.mn(2,2) = kk*G*dthk;
*dee.mn(1,2) = 0;
*dee.mn(2,1) = 0;
Mat KM2(12,12); 
nip=1;
Points=Sample(nip);
for(i=1;i<nip+1;i++)
  {
    det = 0;
    fun.clear();deriv.clear();jac.clear(),deriv2.clear();
    bT.clear();db.clear();bdb.clear();bee.clear();
    fun=ShapeFun(Points, i);
    deriv=ShapeDer(Points, i);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee.clear();
    bee.Create(2,12);
    for (k=1;k<iNoNodes+1;k++)//was m
    {
      *bee.mn(1,(k)*3-2) = *deriv2.mn(1,k);
      *bee.mn(1,(k)*3-1) = 0;
      *bee.mn(1,(k)*3-0) = *fun.mn(1,k);
      *bee.mn(2,(k)*3-2) = *deriv2.mn(2,k);
      *bee.mn(2,(k)*3-1) = -*fun.mn(1,k);
      *bee.mn(2,(k)*3-0) = 0;
    }
    bT = bee;
    bT.Transpose();
    db = dee*bee;
    bdb = bT*db;
    det*=*Points.mn(i,3);
    bdb*=det;
    KM2+=bdb;
  }
fun.clear();deriv.clear();jac.clear(),deriv2.clear();
bT.clear();db.clear();bdb.clear();bee.clear();
//The bending part
dee.clear();
dee.Create(3,3);
double Cf;
Cf=dE*dthk*dthk*dthk/(12*(1-dv*dv));
nip=3;
Points=Sample(nip);
*dee.mn(1,1) = 1;
*dee.mn(1,2) = dv;
*dee.mn(1,3) = 0;
*dee.mn(2,1) = dv;
*dee.mn(2,2) = 1;
*dee.mn(2,3) = 0;
*dee.mn(3,1) = 0;
*dee.mn(3,2) = 0;
*dee.mn(3,3) = (1-dv);
dee*=Cf;
Mat KM3(12,12); 
for(i=1;i<nip+1;i++)
  {
    fun.clear();deriv.clear();jac.clear(),deriv2.clear();
    bT.clear();db.clear();bdb.clear();bee.clear();
    det = 0;
    fun=ShapeFun(Points, i);
    deriv=ShapeDer(Points, i);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee.clear();
    bee.Create(3,12);
    for (k=1;k<iNoNodes+1;k++)//was m
    {
      *bee.mn(1,(k)*3-2) = 0;
      *bee.mn(1,(k)*3-1) = 0;
      *bee.mn(1,(k)*3-0) = -*deriv2.mn(1,k);
      *bee.mn(2,(k)*3-2) = 0;
      *bee.mn(2,(k)*3-1) = *deriv2.mn(2,k);
      *bee.mn(2,(k)*3-0) = 0;
      *bee.mn(3,(k)*3-2) = 0;
      *bee.mn(3,(k)*3-1) = *deriv2.mn(1,k);
      *bee.mn(3,(k)*3-0) = -*deriv2.mn(2,k);
    }
    bT = bee;
    bT.Transpose();
    db = dee*bee;
    bdb = bT*db;
    det*=*Points.mn(i,3);
    bdb*=det;
    KM3+=bdb;
  }
KM2+=KM3;
fun.clear();deriv.clear();jac.clear(),deriv2.clear();
bT.clear();db.clear();bdb.clear();bee.clear();
//Assemble all the components inplain,shear and bending in KMf
Mat KMf(6*iNoNodes,6*iNoNodes);
Vec<int> V(6);
*V.nn(1)=1;
*V.nn(2)=2;
*V.nn(3)=7;
*V.nn(4)=8;
*V.nn(5)=13;
*V.nn(6)=14;

int j;
for (i=1;i<=6;i++)
{
  for (j=1;j<=6;j++)
  {
    *KMf.mn(V[i-1],V[j-1])=*KM.mn(i,j);
  }
}
Vec<int> V1(9);
*V1.nn(1)=3;
*V1.nn(2)=4;
*V1.nn(3)=5;
*V1.nn(4)=9;
*V1.nn(5)=10;
*V1.nn(6)=11;
*V1.nn(7)=15;
*V1.nn(8)=16;
*V1.nn(9)=17;

for (i=1;i<=9;i++)
{
  for (j=1;j<=9;j++)
  {
    *KMf.mn(V1[i-1],V1[j-1])=*KM2.mn(i,j);
  }
}

for (i=6;i<=18;i+=6)
{
  *KMf.mn(i,i)=100;
}
//Transform to global
//M3.Transpose();
Mat TMAT(18,18);

for (i=1;i<18;i+=3)
{
    *TMAT.mn(i,i)=M3.m_00;
    *TMAT.mn(i+1,i)=M3.m_10;
    *TMAT.mn(i+2,i)=M3.m_20;

    *TMAT.mn(i,i+1)=M3.m_01;
    *TMAT.mn(i+1,i+1)=M3.m_11;
    *TMAT.mn(i+2,i+1)=M3.m_21;

    *TMAT.mn(i,i+2)=M3.m_02;
    *TMAT.mn(i+1,i+2)=M3.m_12;
    *TMAT.mn(i+2,i+2)=M3.m_22;
}
//TMAT.diag();
Mat TMATT=TMAT;
TMATT.Transpose();
Mat T;
Mat TT;
T=KMf*TMAT;
TT=TMATT*T;
KM.clear();
KM2.clear();
TMATT.clear();
TMAT.clear();
T.clear();
return (TT);
}


//*********************************
IMPLEMENT_DYNAMIC( E_Object1, CObject )

E_Object1::~E_Object1()
{
pVertex=NULL;
}

void E_Object1::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
pVertex = pInVertex[0];
iCID=0;
dM=0;
dX1=0;
dX2=0;
dX3=0;
dI11=0;
dI21=0;
dI22=0;
dI31=0;
dI32=0;
dI33=0;
}

G_Object* E_Object1::GetNode(int i)
{
return (pVertex);
}

BOOL E_Object1::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
if (pVertex==pN)
{
  brc=TRUE;
}
return (brc);
}

void E_Object1::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

if (pVertex==pThis)
{
  pVertex=pWith;
}
}


void E_Object1::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
	  // TODO: add storing code here
      E_Object::Serialize(ar,MESH);
      ar << pVertex->G_label;
      ar << iCID;
      ar << dM;
      ar << dX1;
      ar << dX2;
      ar << dX3;
      ar << dI11;
      ar << dI21;
      ar << dI22;
      ar << dI31;
      ar << dI32;
      ar << dI33;
	}
	else
	{
      E_Object::Serialize(ar,MESH);
      ar>>iNd;
      pVertex = MESH->GetNode(iNd);
      ar >> iCID;
      ar >> dM;
      ar >> dX1;
      ar >> dX2;
      ar >> dX3;
      ar >> dI11;
      ar >> dI21;
      ar >> dI22;
      ar >> dI31;
      ar >> dI32;
      ar >> dI33;
	}
}


void E_Object1::ExportUNV(FILE* pFile)
{
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
fprintf(pFile,"%10i",pVertex->G_label);
fprintf(pFile,"\n","");
}

void E_Object1::ExportNAS(FILE* pFile)
{
fprintf(pFile,"%8s%8i%8i%8i%8s%8s%8s%8s\n","CONM2   ",G_label,pVertex->G_label,iCID,e8(dM),e8(dX1),e8(dX2),e8(dX3));
fprintf(pFile,"%8s%8s%8s%8s%8s%8s%8s\n","        ",e8(dI11),e8(dI21),e8(dI22),e8(dI31),e8(dI32),e8(dI33));
}

void E_Object1::Transform(C3dMatrix TMat)
{
TMat.ClearTranslations();
C3dVector vOff;
vOff.Set(dX1,dX2,dX3);
vOff=TMat*vOff;
C3dMatrix mI;
mI.MakeUnit();

mI.m_00=dI11;
mI.m_10=dI21;
mI.m_20=dI31;

mI.m_01=dI21;
mI.m_11=dI22;
mI.m_21=dI32;

mI.m_02=dI31;
mI.m_12=dI32;
mI.m_22=dI33;
mI*=TMat;
dI11=mI.m_00;
dI21=mI.m_10;
dI31=mI.m_20;

dI21=mI.m_01;
dI22=mI.m_11;
dI32=mI.m_21;

dI31=mI.m_02;
dI32=mI.m_12;
dI33=mI.m_22;
}

G_Object* E_Object1::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object1* gret = new E_Object1;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex = MESH->GetNode(this->pVertex->G_label);

gret->iCID=iCID;
gret->dM=dM;
gret->dX1=dX1;
gret->dX2=dX2;
gret->dX3=dX3;
gret->dI11=dI11;
gret->dI21=dI21;
gret->dI22=dI22;
gret->dI31=dI31;
gret->dI32=dI32;
gret->dI33=dI33;
gret->pPr=pPr;
gret->pParent=MESH;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object1::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object1* gret = new E_Object1;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex);
EInd+=iSInd;
gret->pVertex = Target->pNodes[EInd];
gret->iCID=iCID;
gret->dM=dM;
gret->dX1=dX1;
gret->dX2=dX2;
gret->dX3=dX3;
gret->dI11=dI11;
gret->dI21=dI21;
gret->dI22=dI22;
gret->dI31=dI31;
gret->dI32=dI32;
gret->dI33=dI33;
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}



G_Object* E_Object1::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object1* gret = new E_Object1;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex = pInVertex[0];
gret->iCID=iCID;
gret->dM=dM;
gret->dX1=dX1;
gret->dX2=dX2;
gret->dX3=dX3;
gret->dI11=dI11;
gret->dI21=dI21;
gret->dI22=dI22;
gret->dI31=dI31;
gret->dI32=dI32;
gret->dI33=dI33;
gret->pPr=pPr;
gret->pParent=Parrent;
gret->pResV = NULL;
return (gret);
}

// Draw Object line
void E_Object1::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) pVertex->DSP_Point->x-5,(int) pVertex->DSP_Point->y-5);
pDC->LineTo((int) pVertex->DSP_Point->x+5,(int) pVertex->DSP_Point->y-5);
pDC->LineTo((int) pVertex->DSP_Point->x+5,(int) pVertex->DSP_Point->y+5);
pDC->LineTo((int) pVertex->DSP_Point->x-5,(int) pVertex->DSP_Point->y+5);
pDC->LineTo((int) pVertex->DSP_Point->x-5,(int) pVertex->DSP_Point->y-5);
}



void E_Object1::OglDraw(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
C3dVector vCent;
vCent=this->Get_Centroid();
if ((iDspFlgs & DSP_ELEMENTS)>0)
{
	Selectable=1;
	glColor3fv(cols[GetCol()]);
  glPointSize(16.0f); 
	glBegin(GL_POINTS);
  glVertex3f((float) vCent.x,(float) vCent.y,(float) vCent.z);
  glEnd();
}
else
{
   Selectable=0;
}

if (bDrawLab==TRUE)
{
	  sprintf_s(sLab,"N%i",G_label);
	  OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
}
}

void E_Object1::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
OglDraw(iDspFlgs,dS1,dS2);
}





C3dVector E_Object1::Get_Centroid()
{
C3dVector vT;
vT.x = pVertex->Pt_Point->x;
vT.y = pVertex->Pt_Point->y;
vT.z = pVertex->Pt_Point->z;
return (vT);
}




IMPLEMENT_DYNAMIC( E_CellS , CObject )

E_CellS ::~E_CellS ()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
pVertex[2]=NULL;
pVertex[3]=NULL;
pVertex[4]=NULL;
}

void E_CellS ::Create(Pt_Object* pInVertex[100], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);

int i=0;
for (i=0;i<5;i++)
   {
    pVertex[i] = pInVertex[i];
   }

}

void E_CellS::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << pVertex[2]->G_label;
    ar << pVertex[3]->G_label;
    ar << pVertex[4]->G_label;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[2] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[3] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[4] = MESH->GetNode(iNd);
	}
  pPr=NULL;
}

G_Object* E_CellS::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_CellS* gret = new E_CellS;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->pVertex[2] = MESH->GetNode(pVertex[2]->G_label);
gret->pVertex[3] = MESH->GetNode(pVertex[3]->G_label);
gret->pVertex[4] = MESH->GetNode(pVertex[4]->G_label);
gret->pParent=MESH;
gret->pPr=pPr;

return (gret);
}

G_Object* E_CellS::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_CellS* gret = new E_CellS;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[2]);
gret->pVertex[2] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[3]);
gret->pVertex[3] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[4]);
gret->pVertex[4] = Target->pNodes[EInd+iSInd];
gret->pParent=Target;
gret->pPr=NULL;
return (gret);
}


G_Object* E_CellS::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_CellS* gret = new E_CellS;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  =inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = pInVertex[0];
gret->pVertex[1] = pInVertex[1];
gret->pVertex[2] = pInVertex[2];
gret->pVertex[3] = pInVertex[3];
gret->pVertex[4] = pInVertex[4];
gret->pParent=Parrent;
gret->pPr=pPr;
return (gret);
}

// Draw Object line
void E_CellS::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);
pDC->MoveTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[4]->DSP_Point->x,(int) pVertex[4]->DSP_Point->y);

}

BOOL E_CellS::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	  break;
  }
}
return (brc);
}

void E_CellS::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}

}

G_Object* E_CellS::GetNode(int i)
{
return (pVertex[i]);
}

C3dVector E_CellS::Get_Centroid()
{
  return (pVertex[0]->Get_Centroid());
}


void E_CellS::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  Selectable=1;
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1,0x0101);
  glColor3fv(cols[G_Colour]);
  glBegin(GL_LINES);
  glVertex3f((float) pVertex[1]->Pt_Point->x,(float) pVertex[1]->Pt_Point->y,(float) pVertex[1]->Pt_Point->z);
  glVertex3f((float) pVertex[3]->Pt_Point->x,(float) pVertex[3]->Pt_Point->y,(float) pVertex[3]->Pt_Point->z);
  glVertex3f((float) pVertex[2]->Pt_Point->x,(float) pVertex[2]->Pt_Point->y,(float) pVertex[2]->Pt_Point->z);
  glVertex3f((float) pVertex[0]->Pt_Point->x,(float) pVertex[0]->Pt_Point->y,(float) pVertex[0]->Pt_Point->z);
  glEnd();
  glDisable(GL_LINE_STIPPLE);
  glBegin(GL_LINES);
  glVertex3f((float) pVertex[0]->Pt_Point->x,(float) pVertex[0]->Pt_Point->y,(float) pVertex[0]->Pt_Point->z);
  glVertex3f((float) pVertex[4]->Pt_Point->x,(float) pVertex[4]->Pt_Point->y,(float) pVertex[4]->Pt_Point->z);
  glEnd();
  C3dVector vCent;
  vCent=Get_Centroid();
  if (bDrawLab==TRUE)
  {
    sprintf_s(sLab,"E%i",G_label);
    OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
  }
}
else
{
  Selectable=0;
}
}

void E_CellS::OglDraw(int iDspFlgs,double dS1,double dS2)
{

OglDrawW(iDspFlgs,dS1,dS2);
}

//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_Object4, CObject )

E_Object4::~E_Object4()
{
pVertex[0]=NULL;
pVertex[1]=NULL;
pVertex[2]=NULL;
pVertex[3]=NULL;
}

int E_Object4::MaxBW()
{
int i;
int j;
int MaxDof;
int MinDof;
MaxDof=0;
MinDof=99999999;
for (i=0;i<iNoNodes;i++)
{
  for(j=0;j<6;j++)
  {
    if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j]>MaxDof))
	{
       MaxDof=pVertex[i]->dof[j];
    }
	if ((pVertex[i]->dof[j] != 0) && (pVertex[i]->dof[j] < MinDof))
	{
       MinDof=pVertex[i]->dof[j];
	}
  }
}
int iRC;
if (MaxDof-MinDof<0)
{
  iRC=0;
}
else
{
  iRC=MaxDof-MinDof;
}
return (iRC);
}

Mat E_Object4::Sample(int iNo)
{
Mat Pts(iNo,3);
if (iNo == 4)
{
  double r3 = 0.577350269189626;;
  *Pts.mn(1,1) = -r3;
  *Pts.mn(2,1) = r3;
  *Pts.mn(3,1) = r3;
  *Pts.mn(4,1) = -r3;

  *Pts.mn(1,2) = -r3;
  *Pts.mn(2,2) = -r3;
  *Pts.mn(3,2) = +r3;
  *Pts.mn(4,2) = +r3;

  *Pts.mn(1,3) = 1;
  *Pts.mn(2,3) = 1;
  *Pts.mn(3,3) = 1;
  *Pts.mn(4,3) = 1;
}
else if (iNo == 1)
{
  *Pts.mn(1,1) = 0;
  *Pts.mn(1,2) = 0;
  *Pts.mn(1,3) = 4;
}
return (Pts);
}

Mat E_Object4::ShapeDer(Mat Points, int i)
{
Mat der(2,4);
double xi,eta;
xi = *Points.mn(i, 1);
eta = *Points.mn(i, 2);

*der.mn(1,1) = 0.25*(-1+eta);
*der.mn(1,2) = 0.25*(1-eta);
*der.mn(1,3) = 0.25*(1+eta);
*der.mn(1,4) = 0.25*(-1-eta);

*der.mn(2,1) = 0.25*(-1+xi);
*der.mn(2,2) = 0.25*(-1-xi);
*der.mn(2,3) = 0.25*(1+xi);
*der.mn(2,4) = 0.25*(1-xi);

return(der);
}

Mat E_Object4::ShapeFun(Mat Points, int i)
{
Mat fun(1,4);
double xi,eta;
xi = *Points.mn(i, 1);
eta = *Points.mn(i, 2);

*fun.mn(1,1) = 0.25*(1-xi)*(1-eta);
*fun.mn(1,2) = 0.25*(1+xi)*(1-eta);
*fun.mn(1,3) = 0.25*(1+xi)*(1+eta);
*fun.mn(1,4) = 0.25*(1-xi)*(1+eta);
return(fun);
}

Mat E_Object4::getCoords2d()
{
int i;
Mat coord(iNoNodes,2);
for (i=0;i<iNoNodes;i++)
{
  *coord.mn(i+1, 1) = pVertex[i]->Pt_Point->x;
  *coord.mn(i+1, 2) = pVertex[i]->Pt_Point->y;
}
return (coord);
}

//*******************************************************************
//Get The coordinates after transforming the element to the XY plain
//********************************************************************
Mat E_Object4::getCoords3d()
{
int i;
C3dVector p;
Mat coord(iNoNodes,2);
C3dMatrix M3=this->GetElSys();
//M3.Transpose();
for (i=0;i<iNoNodes;i++)
{
  C3dVector p,v;
  p.x=pVertex[i]->Pt_Point->x;
  p.y=pVertex[i]->Pt_Point->y;
  p.z=pVertex[i]->Pt_Point->z;
  v=M3.Mult(p);
  *coord.mn(i+1,1)=v.x;
  *coord.mn(i+1,2)=v.y;
}
return (coord);
}

Vec<int> E_Object4::GetSteerVec2d()
{
Vec<int> V(24);
*V.nn(1)=pVertex[0]->dof[0];
*V.nn(2)=pVertex[0]->dof[1];
*V.nn(3)=pVertex[0]->dof[2];
*V.nn(4)=pVertex[0]->dof[3];
*V.nn(5)=pVertex[0]->dof[4];
*V.nn(6)=pVertex[0]->dof[5];

*V.nn(7)=pVertex[1]->dof[0];
*V.nn(8)=pVertex[1]->dof[1];
*V.nn(9)=pVertex[1]->dof[2];
*V.nn(10)=pVertex[1]->dof[3];
*V.nn(11)=pVertex[1]->dof[4];
*V.nn(12)=pVertex[1]->dof[5];

*V.nn(13)=pVertex[2]->dof[0];
*V.nn(14)=pVertex[2]->dof[1];
*V.nn(15)=pVertex[2]->dof[2];
*V.nn(16)=pVertex[2]->dof[3];
*V.nn(17)=pVertex[2]->dof[4];
*V.nn(18)=pVertex[2]->dof[5];

*V.nn(19)=pVertex[3]->dof[0];
*V.nn(20)=pVertex[3]->dof[1];
*V.nn(21)=pVertex[3]->dof[2];
*V.nn(22)=pVertex[3]->dof[3];
*V.nn(23)=pVertex[3]->dof[4];
*V.nn(24)=pVertex[3]->dof[5];
return(V);
}

Mat E_Object4::bmatAxi(double& radius,
                       Mat& coord,
                       Mat& deriv,
                       Mat& fun)
{
int nod,i,k,l,m;
double x,y;
nod = deriv.n;
Mat bee(4,8);
radius = 0;
for (i=1;i<4+1;i++)
{
  radius = radius + *fun.mn(1,i) * *coord.mn(i, 1);
}
for (m=1;m<nod+1;m++)
{
  k = 2 * m;
  l = k - 1;
  x = *deriv.mn(1, m);
  *bee.mn(1, l) = x;
  *bee.mn(3, k) = x;
  y = *deriv.mn(2, m);
  *bee.mn(2, k) = y;
  *bee.mn(3, l) = y;
  *bee.mn(4, l) = *fun.mn(1,m) / radius;
}
return (bee);
}

Mat E_Object4::GetStiffMat(PropTable* PropsT,MatTable* MatT)
{
Mat bee;   //strain displacement matrix
int nip=0;

Mat coord2;
Mat deriv;
Mat deriv2;
Mat fun;
Mat Points;
Mat jac;
int i;
double det;
Mat bT;
Mat db;
Mat bdb;
int iDof;
int iS;
int MID=-1;
double dE=210e9;
double dv=0.29;
char S1[80];
double dthk=0.001;

Property* pS=PropsT->GetItem(PID);
if (pS!=NULL)
{
  MID=pS->GetDefMatID();
}
Material* pM=MatT->GetItem(MID);
if (pS==NULL)
{
  sprintf_s(S1,"PROPERTY NOT FOUND FOR EL %i",G_label);
  outtext1(S1);
}
if (pM==NULL)
{  
  sprintf_s(S1,"MATERIAL NOT FOUND FOR EL %i",G_label);
  outtext1(S1); 
}
//Get Shell thick ness

if (((iELType==91) || (iELType==94)) && (pS!=NULL))
{
  PSHELL* pSh = (PSHELL*) pS;
  dthk=pSh->dT;
}

if ((pM!=NULL) && (pM->iType = 1))
{
  MAT1* pIsen = (MAT1*) pM;
  dE=pIsen->dE;
  dv=pIsen->dNU;
}
//This part calculates the 2d membraine stiffness
iDof=2;   //3 dof X,Y per node
nip=4;    //4 intergration points
iS=3;

Mat KM(iDof*iNoNodes,iDof*iNoNodes);
Mat dee=DeeMat(dE,dv,iS);
Mat coord=getCoords3d();
C3dMatrix M3=this->GetElSys();
Points=Sample(nip);
//Membraine stiffness calculation
//for dof 12
  for(i=1;i<nip+1;i++)
  {
    det = 0;
    fun.clear();deriv.clear();jac.clear(),deriv2.clear();
    bT.clear();db.clear();bdb.clear();bee.clear();
    fun=ShapeFun(Points, i);
    deriv=ShapeDer(Points, i);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee=bmat(coord, deriv2,iS,iDof);
    bT = bee;
    bT.Transpose();
    db = dee*bee;
    bdb = bT*db;
    det*=*Points.mn(i,3);
    bdb*=det;
    KM+=bdb;
  }
KM*=dthk;
fun.clear();deriv.clear();jac.clear(),deriv2.clear();
bT.clear();db.clear();bdb.clear();bee.clear();
//Mindlin Formulation
//Sheer Stifness Calculation
//Full intergation at this point 4 sample point 
//I think need to be reduced integration 1 sample point
double G,kk;
int k;
dee.clear();
dee.Create(2,2);
G=0.5*dE/(1+dv);
kk=5.0/6.0;
*dee.mn(1,1) = kk*G*dthk;
*dee.mn(2,2) = kk*G*dthk;
*dee.mn(1,2) = 0;
*dee.mn(2,1) = 0;
Mat KM2(12,12); 
nip=1;
Points=Sample(nip);
for(i=1;i<nip+1;i++)
  {
    det = 0;
    fun.clear();deriv.clear();jac.clear(),deriv2.clear();
    bT.clear();db.clear();bdb.clear();bee.clear();
    fun=ShapeFun(Points, i);
    deriv=ShapeDer(Points, i);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee.clear();
    bee.Create(2,12);
    for (k=1;k<4+1;k++)//was m
    {
      *bee.mn(1,(k)*3-2) = *deriv2.mn(1,k);
      *bee.mn(1,(k)*3-1) = 0;
      *bee.mn(1,(k)*3-0) = *fun.mn(1,k);
      *bee.mn(2,(k)*3-2) = *deriv2.mn(2,k);
      *bee.mn(2,(k)*3-1) = -*fun.mn(1,k);
      *bee.mn(2,(k)*3-0) = 0;
    }
    bT = bee;
    bT.Transpose();
    db = dee*bee;
    bdb = bT*db;
    det*=*Points.mn(i,3);
    bdb*=det;
    KM2+=bdb;
  }
fun.clear();deriv.clear();jac.clear(),deriv2.clear();
bT.clear();db.clear();bdb.clear();bee.clear();
//The bending part
dee.clear();
dee.Create(3,3);
double Cf;
Cf=dE*dthk*dthk*dthk/(12*(1-dv*dv));
nip=4;
Points=Sample(nip);
*dee.mn(1,1) = 1;
*dee.mn(1,2) = dv;
*dee.mn(1,3) = 0;
*dee.mn(2,1) = dv;
*dee.mn(2,2) = 1;
*dee.mn(2,3) = 0;
*dee.mn(3,1) = 0;
*dee.mn(3,2) = 0;
*dee.mn(3,3) = (1-dv);
dee*=Cf;
Mat KM3(12,12); 
for(i=1;i<nip+1;i++)
  {
    fun.clear();deriv.clear();jac.clear(),deriv2.clear();
    bT.clear();db.clear();bdb.clear();bee.clear();
    det = 0;
    fun=ShapeFun(Points, i);
    deriv=ShapeDer(Points, i);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee.clear();
    bee.Create(3,12);
    for (k=1;k<4+1;k++)//was m
    {
      *bee.mn(1,(k)*3-2) = 0;
      *bee.mn(1,(k)*3-1) = 0;
      *bee.mn(1,(k)*3-0) = -*deriv2.mn(1,k);
      *bee.mn(2,(k)*3-2) = 0;
      *bee.mn(2,(k)*3-1) = *deriv2.mn(2,k);
      *bee.mn(2,(k)*3-0) = 0;
      *bee.mn(3,(k)*3-2) = 0;
      *bee.mn(3,(k)*3-1) = *deriv2.mn(1,k);
      *bee.mn(3,(k)*3-0) = -*deriv2.mn(2,k);
    }
    bT = bee;
    bT.Transpose();
    db = dee*bee;
    bdb = bT*db;
    det*=*Points.mn(i,3);
    bdb*=det;
    KM3+=bdb;
  }
KM2+=KM3;
fun.clear();deriv.clear();jac.clear(),deriv2.clear();
bT.clear();db.clear();bdb.clear();bee.clear();
//Assemble all the components inplain,shear and bending in KMf
Mat KMf(6*iNoNodes,6*iNoNodes);
Vec<int> V(8);
*V.nn(1)=1;
*V.nn(2)=2;
*V.nn(3)=7;
*V.nn(4)=8;
*V.nn(5)=13;
*V.nn(6)=14;
*V.nn(7)=19;
*V.nn(8)=20;
int j;
for (i=1;i<=8;i++)
{
  for (j=1;j<=8;j++)
  {
    *KMf.mn(V[i-1],V[j-1])=*KM.mn(i,j);
  }
}
Vec<int> V1(12);
*V1.nn(1)=3;
*V1.nn(2)=4;
*V1.nn(3)=5;
*V1.nn(4)=9;
*V1.nn(5)=10;
*V1.nn(6)=11;
*V1.nn(7)=15;
*V1.nn(8)=16;
*V1.nn(9)=17;
*V1.nn(10)=21;
*V1.nn(11)=22;
*V1.nn(12)=23;

for (i=1;i<=12;i++)
{
  for (j=1;j<=12;j++)
  {
    *KMf.mn(V1[i-1],V1[j-1])=*KM2.mn(i,j);
  }
}

for (i=6;i<=24;i+=6)
{
  *KMf.mn(i,i)=100;
}
//Transform to global
//M3.Transpose();
Mat TMAT(24,24);

for (i=1;i<24;i+=3)
{
    *TMAT.mn(i,i)=M3.m_00;
    *TMAT.mn(i+1,i)=M3.m_10;
    *TMAT.mn(i+2,i)=M3.m_20;

    *TMAT.mn(i,i+1)=M3.m_01;
    *TMAT.mn(i+1,i+1)=M3.m_11;
    *TMAT.mn(i+2,i+1)=M3.m_21;

    *TMAT.mn(i,i+2)=M3.m_02;
    *TMAT.mn(i+1,i+2)=M3.m_12;
    *TMAT.mn(i+2,i+2)=M3.m_22;
}
//TMAT.diag();
Mat TMATT=TMAT;
TMATT.Transpose();
Mat T;
Mat TT;
T=KMf*TMAT;
TT=TMATT*T;
KM.clear();
KM2.clear();
TMATT.clear();
TMAT.clear();
T.clear();
return (TT);
}

int E_Object4::noDof()
{
return(6);
}


void E_Object4::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,int inMCys,double inMAng,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
iMCys= inMCys;
MAng= inMAng;
int i=0;
for (i=0;i<4;i++)
   {
    pVertex[i] = pInVertex[i];
   }
dZOFFS=0;
}

void E_Object4::Reverse()
{

Pt_Object* pT[8];
pT[0]=pVertex[0];
pT[1]=pVertex[1];
pT[2]=pVertex[2];
pT[3]=pVertex[3];
pVertex[0] = pT[0];
pVertex[1] = pT[3];
pVertex[2] = pT[2];
pVertex[3] = pT[1];
}

void E_Object4::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}
}

BOOL E_Object4::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_Object4::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    E_Object::Serialize(ar,MESH);
    ar<<iMCys;
    ar<<MAng;
    ar<<dZOFFS;
    ar << pVertex[0]->G_label;
    ar << pVertex[1]->G_label;
    ar << pVertex[2]->G_label;
    ar << pVertex[3]->G_label;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
    ar>>iMCys;
    ar>>MAng;
    ar>>dZOFFS;
    ar>>iNd;
    pVertex[0] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[1] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[2] = MESH->GetNode(iNd);
    ar>>iNd;
    pVertex[3] = MESH->GetNode(iNd);
	}
  pPr=NULL;
}


void E_Object4::ExportUNV(FILE* pFile)
{
int i;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%10i",pVertex[i]->G_label);
}
fprintf(pFile,"\n","");
}

void E_Object4::ExportNAS(FILE* pFile)
{
int i;
fprintf(pFile,"%8s%8i%8i","CQUAD4  ",G_label,PID);
for (i=0;i<iNoNodes;i++)
{
  fprintf(pFile,"%8i",pVertex[i]->G_label);
}
fprintf(pFile,"%8s%8s\n",e8(MAng),e8(dZOFFS));
}


G_Object* E_Object4::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object4* gret = new E_Object4;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = MESH->GetNode(pVertex[0]->G_label);
gret->pVertex[1] = MESH->GetNode(pVertex[1]->G_label);
gret->pVertex[2] = MESH->GetNode(pVertex[2]->G_label);
gret->pVertex[3] = MESH->GetNode(pVertex[3]->G_label);
gret->pParent=MESH;
gret->iMCys=iMCys;
gret->MAng=MAng;
gret->dZOFFS=dZOFFS;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

G_Object* E_Object4::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
E_Object4* gret = new E_Object4;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
EInd=Source->GetNodeInd(pVertex[0]);
gret->pVertex[0] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[1]);
gret->pVertex[1] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[2]);
gret->pVertex[2] = Target->pNodes[EInd+iSInd];
EInd=Source->GetNodeInd(pVertex[3]);
gret->pVertex[3] = Target->pNodes[EInd+iSInd];
gret->pParent=Target;
gret->iMCys=iMCys;
gret->MAng=MAng;
gret->dZOFFS=dZOFFS;
gret->pPr=NULL;
gret->pResV = NULL;
return (gret);
}


G_Object* E_Object4::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
ME_Object* MESH =(ME_Object*) Parrent;
E_Object4* gret = new E_Object4;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  =inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
gret->pVertex[0] = pInVertex[0];
gret->pVertex[1] = pInVertex[1];
gret->pVertex[2] = pInVertex[2];
gret->pVertex[3] = pInVertex[3];
gret->pParent=Parrent;
gret->iMCys=iMCys;
gret->MAng=MAng;
gret->dZOFFS=dZOFFS;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

// Draw Object line
void E_Object4::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
pDC->LineTo((int) pVertex[2]->DSP_Point->x,(int) pVertex[2]->DSP_Point->y);
pDC->LineTo((int) pVertex[3]->DSP_Point->x,(int) pVertex[3]->DSP_Point->y);
pDC->LineTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);

}

G_Object* E_Object4::GetNode(int i)
{
return (pVertex[i]);
}

int E_Object4::GetLinkList(cLink* Links[200])
{
int ic;
ic=GetCol();
Links[0]=new cLink;
Links[0]->vVerts[0]=pVertex[0];
Links[0]->vVerts[1]=pVertex[1];
Links[0]->iColor=ic;
Links[1]=new cLink;
Links[1]->vVerts[0]=pVertex[1];
Links[1]->vVerts[1]=pVertex[2];
Links[1]->iColor=ic;
Links[2]=new cLink;
Links[2]->vVerts[0]=pVertex[2];
Links[2]->vVerts[1]=pVertex[3];
Links[2]->iColor=ic;
Links[3]=new cLink;
Links[3]->vVerts[0]=pVertex[3];
Links[3]->vVerts[1]=pVertex[0];
Links[3]->iColor=ic;
return (4);
}

void E_Object4::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
C3dVector d[4];
int i;
int ind;

for (i=0;i<4;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;
ind=ME->iCVar;

if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<4;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
  Selectable=1;
  if ((iDspFlgs & DSP_ELEMENTS)>0)
  {
    if ((iDspFlgs & DSP_LINE) > 0)
    {
      glColor3fv(cols[G_Colour]);
    }
    else
    {
      glColor3fv(cols[0]);
    }
    C3dVector vN;
    C3dVector vOff;
    vN=Get_Normal();
    //Need to calculate the offsets here
    if (((iDspFlgs & DSP_OFF)>0) && (dZOFFS!=DBL_MAX))
    {
       vOff=vN;
       vOff*=dZOFFS;
    }
    else
    {
       vOff*=0; 
    }
    double dt=0;
    if (pPr!=NULL)
    {
      dt=pPr->GetThk();
      dt*=0.5;
    }
    vN*=dt;
    if ((iDspFlgs & DSP_THK)>0)
    {
  	  glBegin(GL_LINES);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);

      glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x-vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y-vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z-vN.z+d[3].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x-vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y-vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z-vN.z+d[3].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);

      glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
      glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
      glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
      glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x-vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y-vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z-vN.z+d[3].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glEnd();
    }
    else
    {
      vN*=0;
      glBegin(GL_LINES);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glEnd();
    }
	  C3dVector vCent;
    vCent=Get_Centroid();
    if (bDrawLab==TRUE)
	  {
	      sprintf_s(sLab,"E%i",G_label);
	      OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
	  }
    if (((iDspFlgs & DSP_RESLAB)==0) && (pResV!=NULL))
    {
       sprintf_s(sLab,"%f",*pResV->GetAddress(ind));
       OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
    }
    
    //Results Label

	  
  }
  if ((iDspFlgs & DSP_ELSYS)==0)
  {
    C3dMatrix mS = GetElSys();
    C3dVector vC = Get_Centroid();
    mS.Transpose();
    C3dVector vX=mS.GetColVec(1);
    C3dVector vY=mS.GetColVec(2);;
    C3dVector vZ=mS.GetColVec(3);;

    vX*=0.5*dS1; vY*=0.5*dS1; vZ*=0.5*dS1;
    vX+=vC;vY+=vC;vZ+=vC;

    glBegin(GL_LINES);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vX.x,(float) vX.y,(float) vX.z);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vY.x,(float) vY.y,(float) vY.z);
      glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
      glVertex3f((float) vZ.x,(float) vZ.y,(float) vZ.z);
    glEnd();
    glRasterPos3f ((float) vX.x,(float) vX.y,(float) vX.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPX);
    glRasterPos3f ((float) vY.x,(float) vY.y,(float) vY.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPY);
    glRasterPos3f ((float) vZ.x,(float) vZ.y,(float) vZ.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPZ);

    //C3dVector vTP=GetTestPt();
    //glBegin(GL_LINES);
    //  glVertex3f((float) vC.x,(float) vC.y,(float) vC.z);
    //  glVertex3f((float) vTP.x,(float) vTP.y,(float) vTP.z);
    //glEnd();
  }
}
else
{
  Selectable=0;
}
}

void E_Object4::OglDraw(int iDspFlgs,double dS1,double dS2)
{
C3dVector d[4];
int i;
for (i=0;i<4;i++)
{d[i].x=0;d[i].y=0;d[i].z=0;}
ME_Object* ME=(ME_Object*) this->pParent;
double S;
S=ME->dScale;

      float fCols[4]={0,0,0,0};
      BOOL bD=FALSE;
      int iVar;
      iVar=ME->iCVar;
      //Nodal data
      if ((pVertex[0]->pResV != NULL) &&
          (pVertex[1]->pResV != NULL) &&
          (pVertex[2]->pResV != NULL) &&
          (pVertex[3]->pResV != NULL))
      {
        bD=TRUE;
        fCols[0]=GetContourCol(*pVertex[0]->pResV->GetAddress(iVar));
        fCols[1]=GetContourCol(*pVertex[1]->pResV->GetAddress(iVar));
        fCols[2]=GetContourCol(*pVertex[2]->pResV->GetAddress(iVar));
        fCols[3]=GetContourCol(*pVertex[3]->pResV->GetAddress(iVar));
      }
      if (pResV!=NULL)
      {
        bD=TRUE;
        fCols[0]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[1]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[2]=GetContourCol(*pResV->GetAddress(iVar));
        fCols[3]=GetContourCol(*pResV->GetAddress(iVar));
      }

C3dVector v1;
C3dVector v2;
C3dVector Vn;

C3dVector vN;
C3dVector vOff;
vN=Get_Normal();
if (((iDspFlgs & DSP_OFF)>0) && (dZOFFS!=DBL_MAX))
{
  vOff=vN;
  vOff*=dZOFFS;
}
else
{
  vOff*=0; 
}

double dt=0;
if (pPr!=NULL)
{
  dt=pPr->GetThk();
  dt*=0.5;
}
vN*=dt;
Vn =Get_Normal();


if ((iDspFlgs & DSP_ELEMENTS)>0)
{
  if ((iDspFlgs & DSP_RESDEF)==0)
  {
    for(i=0;i<4;i++)
    {
       if (pVertex[i]->pResD!=NULL)
       {
         d[i]=pVertex[i]->pResD->GetVec();
         d[i]*=S;
       }
    }
  }
	Selectable=1;
	glColor3fv(cols[G_Colour]);
  if (((iDspFlgs & DSP_CONT)>0) || (bD==FALSE))
  {
    if ((iDspFlgs & DSP_THK)>0)
    {
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glEnd();
      glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x-vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y-vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z-vN.z+d[3].z);
	    glEnd();

      glBegin(GL_POLYGON);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
      glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
	    glEnd();

      glBegin(GL_POLYGON);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x-vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y-vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z-vN.z+d[1].z);
      glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
	    glEnd();

      glBegin(GL_POLYGON);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x-vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y-vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z-vN.z+d[2].z);
      glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x-vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y-vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z-vN.z+d[3].z);
	    glEnd();

      glBegin(GL_POLYGON);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x-vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y-vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z-vN.z+d[3].z);
      glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x-vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y-vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z-vN.z+d[0].z);
	    glEnd();
    }
    else
    {
      vN*=0;
	    glBegin(GL_POLYGON);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glEnd();
    }
  }
  else
  {
      vN*=0;

      if (bD)
      {
      glColor3fv(cols[124]);
      glEnable(GL_TEXTURE_1D);
	    glBegin(GL_POLYGON);
      glTexCoord1f(fCols[0]);
	    glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[0]->Pt_Point->x+vOff.x+vN.x+d[0].x,(float) pVertex[0]->Pt_Point->y+vOff.y+vN.y+d[0].y,(float) pVertex[0]->Pt_Point->z+vOff.z+vN.z+d[0].z);
      glTexCoord1f(fCols[1]);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[1]->Pt_Point->x+vOff.x+vN.x+d[1].x,(float) pVertex[1]->Pt_Point->y+vOff.y+vN.y+d[1].y,(float) pVertex[1]->Pt_Point->z+vOff.z+vN.z+d[1].z);
      glTexCoord1f(fCols[2]);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[2]->Pt_Point->x+vOff.x+vN.x+d[2].x,(float) pVertex[2]->Pt_Point->y+vOff.y+vN.y+d[2].y,(float) pVertex[2]->Pt_Point->z+vOff.z+vN.z+d[2].z);
      glTexCoord1f(fCols[3]);
      glNormal3f((float) Vn.x,(float) Vn.y,(float) Vn.z);
	    glVertex3f((float) pVertex[3]->Pt_Point->x+vOff.x+vN.x+d[3].x,(float) pVertex[3]->Pt_Point->y+vOff.y+vN.y+d[3].y,(float) pVertex[3]->Pt_Point->z+vOff.z+vN.z+d[3].z);
	    glEnd();
      glDisable(GL_TEXTURE_1D);
      }
  }
}
else
{
  Selectable=0;
}
}

int E_Object4::GetfaceList(cFace* Faces[6])
{
int ic;
ic=GetCol();
Faces[0]=new cFace();
Faces[0]->vVerts[0]=pVertex[0];
Faces[0]->vVerts[1]=pVertex[1];
Faces[0]->vVerts[2]=pVertex[2];
Faces[0]->vVerts[3]=pVertex[3];
Faces[0]->NoVert=4;
Faces[0]->iColor=ic;
return(1);
}





C3dVector E_Object4::Get_Centroid()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=0;
*FunPnt.mn(1,2)=0;
fun=ShapeFun(FunPnt,1);
C3dVector vT;
vT.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vT+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
}

fun.clear();
FunPnt.clear();
return (vT);
}

void E_Object4::Info()
{
  char S1[80];
  sprintf_s(S1,"LAB: %i COL: %i PID: %i ELTP: %i MCID: %i ANG: %f ",G_label,G_Colour,PID,iELType,iMCys,MAng);
  outtext1(S1); 
  sprintf_s(S1,"NODES %i %i %i %i",pVertex[0]->G_label,pVertex[1]->G_label,pVertex[2]->G_label,pVertex[3]->G_label);
  outtext1(S1); 
}

C3dVector E_Object4::Get_Normal()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=0;
*FunPnt.mn(1,2)=0;
fun=ShapeDer(FunPnt,1);
C3dVector vX,vY,vT;
vX.Set(0,0,0);
vY.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vX+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
   vY+=pVertex[j]->Get_Centroid()**fun.mn(2,j+1);
}
vT=vX.Cross(vY);
vT.Normalize();
fun.clear();
FunPnt.clear();
return (vT);
}

C3dMatrix E_Object4::GetElSys()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=0;
*FunPnt.mn(1,2)=0;
fun=ShapeDer(FunPnt,1);
C3dVector vX,vY,vT;
vX.Set(0,0,0);
vY.Set(0,0,0);
int j=0;
for (j=0;j<iNoNodes;j++)
{
   vX+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
   vY+=pVertex[j]->Get_Centroid()**fun.mn(2,j+1);
}
vX.Normalize();
vY.Normalize();
vT=vX.Cross(vY);
vY=vT.Cross(vX);
fun.clear();
FunPnt.clear();
C3dMatrix vR;
vR.SetColVec(1,vX);
vR.SetColVec(2,vY);
vR.SetColVec(3,vT);
vR.Transpose();
return (vR);
}

C3dVector E_Object4::GetTestPt()
{
Mat fun;
Mat FunPnt(1,2);
*FunPnt.mn(1,1)=1;
*FunPnt.mn(1,2)=0;
fun=ShapeFun(FunPnt,1);
C3dVector vX;
vX.Set(0,0,0);

int j=0;
for (j=0;j<iNoNodes;j++)
{
   vX+=pVertex[j]->Get_Centroid()**fun.mn(1,j+1);
}
return (vX);
}








//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( E_ObjectR, CObject )

E_ObjectR::E_ObjectR()
{
iDOF=DOF_ALL;
PID=999;
PIDunv=999;
dALPHA=0;
}

void E_ObjectR::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
int i=0;
for (i=0;i<iNoNodes;i++)
   {
    pVertex[i] = pInVertex[i];
   }
iDOF=DOF_ALL;
}

void E_ObjectR::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}

}

BOOL E_ObjectR::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	break;
  }
}
return (brc);
}

void E_ObjectR::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
  int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here

    E_Object::Serialize(ar,MESH);
    for (i=0;i<iNoNodes;i++)
    {
      ar << pVertex[i]->G_label;
    }
    ar << iDOF;
    ar << dALPHA;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
    for (i=0;i<iNoNodes;i++)
    {
      ar>>iNd;;
      pVertex[i] = MESH->GetNode(iNd);
    }
    ar >> iDOF;
    ar >> dALPHA;
	}
}

G_Object* E_ObjectR::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
int i;
E_ObjectR* gret = new E_ObjectR;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
for (i=0;i<iNoNodes;i++)
{
  gret->pVertex[i] = MESH->GetNode(pVertex[i]->G_label);
}
gret->iDOF=iDOF;
gret->pParent=MESH;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

G_Object* E_ObjectR::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
int i;
E_ObjectR* gret = new E_ObjectR;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
for (i=0;i<iNoNodes;i++)
{
  EInd=Source->GetNodeInd(pVertex[i]);
  gret->pVertex[i] = Target->pNodes[EInd+iSInd];
}
gret->iDOF=iDOF;
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}

G_Object* E_ObjectR::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
int i;
ME_Object* MESH =(ME_Object*) Parrent;
E_ObjectR* gret = new E_ObjectR;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
for (i=0;i<iNoNodes;i++)
{
  gret->pVertex[i] = pInVertex[i];
}
gret->iDOF=iDOF;
gret->pParent=Parrent;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

void E_ObjectR::ExportUNV(FILE* pFile)
{
int i;
int iC;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
iC=0;
for (i=0;i<iNoNodes;i++)
{
  if (iC==8)
  {
    fprintf(pFile,"\n","");
	iC=0;
  }
  fprintf(pFile,"%10i",pVertex[i]->G_label);
  iC++;
}
fprintf(pFile,"\n","");
}

void E_ObjectR::ExportNAS(FILE* pFile)
{
int i;
int iFN;
CString sDof;
sDof=GetDOFString(iDOF);
fprintf(pFile,"%8s%8i%8i%8s","RBE2    ",G_label,pVertex[0]->G_label,sDof);
iFN=5;

for (i=1;i<iNoNodes;i++)
{
 fprintf(pFile,"%8i",pVertex[i]->G_label);
 iFN++;
 if (iFN>9)
 {
   iFN=2;
   fprintf(pFile,"\n","");
   fprintf(pFile,"%8s","        ");
 }
}
fprintf(pFile,"%8s\n",e8(dALPHA));
}

// Draw Object line
void E_ObjectR::Draw(CDC* pDC,int iDrawmode)
{
int i;
for (i=0;i<iNoNodes;i++)
  {
    pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
    pDC->LineTo((int) pVertex[i]->DSP_Point->x,(int) pVertex[i]->DSP_Point->y);
  }
}



void E_ObjectR::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
OglDraw(iDspFlgs,dS1,dS2);
}

G_Object* E_ObjectR::GetNode(int i)
{
return (pVertex[i]);
}

void E_ObjectR::SetDOFString(CString sDOF)
{
  iDOF=GetDOFInt(sDOF);
}

void E_ObjectR::Info()
{
  char S1[80];
  CString sDOF;
  sDOF=GetDOFString(iDOF);
  sprintf_s(S1,"LAB: %i COL: %i PID: %i ELTP: %i",G_label,G_Colour,PID,iELType);
  outtext1(S1); 
  outtext1(sDOF); 
}





void E_ObjectR::OglDraw(int iDspFlgs,double dS1,double dS2)
{
int i;
glColor3fv(cols[G_Colour]);
glBegin(GL_LINES);
for (i=1;i<iNoNodes;i++)
{
  glVertex3f((float) pVertex[0]->Pt_Point->x,(float) pVertex[0]->Pt_Point->y,(float) pVertex[0]->Pt_Point->z);
  glVertex3f((float) pVertex[i]->Pt_Point->x,(float) pVertex[i]->Pt_Point->y,(float) pVertex[i]->Pt_Point->z); 
}
glEnd(); 
}

int E_ObjectR::GetLinkList(cLink* Links[200])
{
int ic;
ic=GetCol();
int i;
for (i=0;i<iNoNodes-1;i++)
{
  Links[i]=new cLink;
  Links[i]->vVerts[0]=pVertex[0];
  Links[i]->vVerts[1]=pVertex[i+1];
  Links[i]->iColor=ic;
}
return (iNoNodes-1);
}



C3dVector E_ObjectR::Get_Centroid()
{
C3dVector vT;
vT.x = pVertex[0]->Pt_Point->x; 
vT.y = pVertex[0]->Pt_Point->y;
vT.z = pVertex[0]->Pt_Point->z;
return (vT);
}








IMPLEMENT_DYNAMIC( E_ObjectR2, CObject )

E_ObjectR2::E_ObjectR2()
{
iCNA=DOF_ALL;
iCNB=0;
iCMA=0;
iCMB=0;
dALPHA=0;
PIDunv=999;
}

void E_ObjectR2::Create(Pt_Object* pInVertex[200], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr)
{
E_Object::Create(iLab,iCol,iType,iPID,iMat,iNo,Parrent,inPr);
int i=0;
for (i=0;i<iNoNodes;i++)
   {
    pVertex[i] = pInVertex[i];
   }

}

void E_ObjectR2::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
  int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here

    E_Object::Serialize(ar,MESH);
    for (i=0;i<iNoNodes;i++)
    {
      ar << pVertex[i]->G_label;
    }
    ar << dALPHA;
    ar << iCNA;
    ar << iCNB;
    ar << iCMA;
    ar << iCMB;
	}
	else
	{
    E_Object::Serialize(ar,MESH);
    for (i=0;i<iNoNodes;i++)
    {
      ar>>iNd;;
      pVertex[i] = MESH->GetNode(iNd);
    }
    ar >> dALPHA;
    ar >> iCNA;
    ar >> iCNB;
    ar >> iCMA;
    ar >> iCMB;
	}
}

G_Object* E_ObjectR2::Copy(G_Object* Parrent)
{
ME_Object* MESH =(ME_Object*) Parrent;
int i;
E_ObjectR2* gret = new E_ObjectR2;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
for (i=0;i<iNoNodes;i++)
{
  gret->pVertex[i] = MESH->GetNode(pVertex[i]->G_label);
}
gret->iDOF=iDOF;
gret->pParent=MESH;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

G_Object* E_ObjectR2::CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source)
{
int EInd;
int i;
E_ObjectR2* gret = new E_ObjectR2;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = PID;
gret->PIDunv  = PIDunv;
gret->iELType  = iELType;
gret->iMatID = iMatID;
gret->iNoNodes = iNoNodes;
for (i=0;i<iNoNodes;i++)
{
  EInd=Source->GetNodeInd(pVertex[i]);
  gret->pVertex[i] = Target->pNodes[EInd+iSInd];
}
gret->iDOF=iDOF;
gret->pParent=Target;
gret->pResV = NULL;
return (gret);
}

G_Object* E_ObjectR2::Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv)
{
int i;
ME_Object* MESH =(ME_Object*) Parrent;
E_ObjectR2* gret = new E_ObjectR2;
gret->iObjType=iObjType;
gret->G_label=G_label;
gret->G_Colour=G_Colour;
gret->Drawn = Drawn;
gret->Selectable  = Selectable; 
gret->Visable  = Visable;
gret->PID  = inPID;
gret->PIDunv  = inPIDunv;
gret->iELType  = iELType;
gret->iMatID = inMID;
gret->iNoNodes = iNoNodes;
for (i=0;i<iNoNodes;i++)
{
  gret->pVertex[i] = pInVertex[i];
}
gret->iDOF=iDOF;
gret->pParent=Parrent;
gret->pPr=pPr;
gret->pResV = NULL;
return (gret);
}

C3dVector E_ObjectR2::Get_Centroid()
{
C3dVector vT;
vT.x = pVertex[0]->Pt_Point->x; 
vT.y = pVertex[0]->Pt_Point->y;
vT.z = pVertex[0]->Pt_Point->z;
return (vT);
}

void E_ObjectR2::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
  OglDraw(iDspFlgs,dS1,dS2);
}


void E_ObjectR2::OglDraw(int iDspFlgs,double dS1,double dS2)
{

glColor3fv(cols[G_Colour]);
glBegin(GL_LINES);
glVertex3f((float) pVertex[0]->Pt_Point->x,(float) pVertex[0]->Pt_Point->y,(float) pVertex[0]->Pt_Point->z);
glVertex3f((float) pVertex[1]->Pt_Point->x,(float) pVertex[1]->Pt_Point->y,(float) pVertex[1]->Pt_Point->z); 
glEnd(); 
}

void E_ObjectR2::Draw(CDC* pDC,int iDrawmode)
{
int i;
for (i=0;i<iNoNodes;i++)
  {
    pDC->MoveTo((int) pVertex[0]->DSP_Point->x,(int) pVertex[0]->DSP_Point->y);
    pDC->LineTo((int) pVertex[1]->DSP_Point->x,(int) pVertex[1]->DSP_Point->y);
  }
}

BOOL E_ObjectR2::NodeInEl(Pt_Object* pN)
{
BOOL brc=FALSE;
int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pN)
  {
    brc=TRUE;
	  break;
  }
}
return (brc);
}


void E_ObjectR2::RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith)
{

int i=0;
for (i=0;i<iNoNodes;i++)
{
  if (pVertex[i] == pThis)
  {
    pVertex[i]=pWith;
	  break;
  }
}
}

void E_ObjectR2::ExportUNV(FILE* pFile)
{
int i;
int iC;
fprintf(pFile,"%10i%10i%10i%10i%10i%10i\n",G_label,iELType,PIDunv,iMatID,G_Colour-150,iNoNodes);
iC=0;
for (i=0;i<iNoNodes;i++)
{
  if (iC==8)
  {
    fprintf(pFile,"\n","");
	iC=0;
  }
  fprintf(pFile,"%10i",pVertex[i]->G_label);
  iC++;
}
fprintf(pFile,"\n","");
}

void E_ObjectR2::SetOther(CString s1,
                          CString s2,
                          CString s3,
                          CString s4,
                          double dAlp)
{

dALPHA=dAlp;
iCNA=GetDOFInt(s1);
iCNB=GetDOFInt(s2);
iCMA=GetDOFInt(s3);
iCMB=GetDOFInt(s4);
}

void E_ObjectR2::ExportNAS(FILE* pFile)
{

CString sDof1;
CString sDof2;
CString sDof3;
CString sDof4;
sDof1=GetDOFString(iCNA);
sDof2=GetDOFString(iCNB);
sDof3=GetDOFString(iCMA);
sDof4=GetDOFString(iCMB);

fprintf(pFile,"%8s%8i%8i%8i%8s%8s%8s%8s%8s\n","RBAR    ",G_label,pVertex[0]->G_label,pVertex[1]->G_label,sDof1,sDof2,sDof3,sDof4,e8(dALPHA));

}

//----------------------------------------------------------------------------
//    W O R K  P L A N E    O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( WP_Object, CObject )

void WP_Object::Create(double dWPSize)
{
double ds = 0.1*dWPSize;
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour =50;
iObjType = -1;
mWPTransform.MakeUnit();
//mWPTransform.Rotate(30,0,45);
//mWPTransform.Translate(3,0,2);

iWPMode = 0;  //Defualt cartesian
Pt_Point[0] = new C3dVector(-dWPSize/2,-dWPSize/2,0);
Pt_Point[1] = new C3dVector(dWPSize/2,-dWPSize/2,0);
Pt_Point[2] = new C3dVector(dWPSize/2,dWPSize/2,0);
Pt_Point[3] = new C3dVector(-dWPSize/2,dWPSize/2,0);



Pt_Point[4] = new C3dVector(-dWPSize/2+ds*0.5,-dWPSize/2+ds*0.5,0);
Pt_Point[5] = new C3dVector(-dWPSize/2+ds*2,-dWPSize/2+ds*0.5,0);
Pt_Point[6] = new C3dVector(-dWPSize/2+ds*2,-dWPSize/2+ds*0.25,0);
Pt_Point[7] = new C3dVector(-dWPSize/2+ds*2.4,-dWPSize/2+ds*0.75,0);
Pt_Point[8] = new C3dVector(-dWPSize/2+ds*2,-dWPSize/2+ds*1.25,0);
Pt_Point[9] = new C3dVector(-dWPSize/2+ds*2,-dWPSize/2+ds*1,0);

Pt_Point[10] = new C3dVector(-dWPSize/2+ds*1,-dWPSize/2+ds*1,0);

Pt_Point[11] = new C3dVector(-dWPSize/2+ds*1,-dWPSize/2+ds*2,0);
Pt_Point[12] = new C3dVector(-dWPSize/2+ds*1.25,-dWPSize/2+ds*2,0);
Pt_Point[13] = new C3dVector(-dWPSize/2+ds*0.75,-dWPSize/2+ds*2.4,0);
Pt_Point[14] = new C3dVector(-dWPSize/2+ds*0.25,-dWPSize/2+ds*2,0);
Pt_Point[15] = new C3dVector(-dWPSize/2+ds*0.5,-dWPSize/2+ds*2,0);

Pt_Point[16] = new C3dVector(-dWPSize/2+ds*2.5,-dWPSize/2+ds*0.25,0);
Pt_Point[17] = new C3dVector(-dWPSize/2+ds*3,-dWPSize/2+ds*1.25,0);
Pt_Point[18] = new C3dVector(-dWPSize/2+ds*2.5,-dWPSize/2+ds*1.25,0);
Pt_Point[19] = new C3dVector(-dWPSize/2+ds*3,-dWPSize/2+ds*0.25,0);


Pt_Point[20] = new C3dVector(-dWPSize/2+ds*0.75,-dWPSize/2+ds*2.5,0);
Pt_Point[21] = new C3dVector(-dWPSize/2+ds*0.75,-dWPSize/2+ds*3,0);
Pt_Point[22] = new C3dVector(-dWPSize/2+ds*1,-dWPSize/2+ds*3.5,0);
Pt_Point[23] = new C3dVector(-dWPSize/2+ds*0.5,-dWPSize/2+ds*3.5,0);

//The Cross Hairs
Pt_Point[24] = new C3dVector(0,-dWPSize/2,0);
Pt_Point[25] = new C3dVector(0,dWPSize/2,0);
Pt_Point[26] = new C3dVector(-dWPSize/2,0,0);
Pt_Point[27] = new C3dVector(dWPSize/2,0,0);
// The R
Pt_Point[28] = new C3dVector(-dWPSize/2+ds*2.5,-dWPSize/2+ds*0.25,0);
Pt_Point[29] = new C3dVector(-dWPSize/2+ds*3,-dWPSize/2+ds*0.25,0);
Pt_Point[30] = new C3dVector(-dWPSize/2+ds*2.5,-dWPSize/2+ds*1.25,0.0);
Pt_Point[31] = new C3dVector(-dWPSize/2+ds*3.0,-dWPSize/2+ds*1.25,0.0);
Pt_Point[32] = new C3dVector(-dWPSize/2+ds*3.0,-dWPSize/2+ds*0.75,0.0);
Pt_Point[33] = new C3dVector(-dWPSize/2+ds*2.5,-dWPSize/2+ds*0.75,0.0);
// the thete
Pt_Point[34] = new C3dVector(-dWPSize/2+ds*0.5,-dWPSize/2+ds*2.5,0);
Pt_Point[35] = new C3dVector(-dWPSize/2+ds*1.0,-dWPSize/2+ds*2.5,0);
Pt_Point[36] = new C3dVector(-dWPSize/2+ds*0.5,-dWPSize/2+ds*3.5,0.0);
Pt_Point[37] = new C3dVector(-dWPSize/2+ds*1.0,-dWPSize/2+ds*3.5,0.0);
Pt_Point[38] = new C3dVector(-dWPSize/2+ds*1.0,-dWPSize/2+ds*3.0,0.0);
Pt_Point[39] = new C3dVector(-dWPSize/2+ds*0.5,-dWPSize/2+ds*3.0,0.0);

DSP_Point[0] = new C3dVector();
DSP_Point[1] = new C3dVector();
DSP_Point[2] = new C3dVector();
DSP_Point[3] = new C3dVector();
DSP_Point[4] = new C3dVector();
DSP_Point[5] = new C3dVector();
DSP_Point[6] = new C3dVector();
DSP_Point[7] = new C3dVector();
DSP_Point[8] = new C3dVector();
DSP_Point[9] = new C3dVector();
DSP_Point[10] = new C3dVector();
DSP_Point[11] = new C3dVector();
DSP_Point[12] = new C3dVector();
DSP_Point[13] = new C3dVector();
DSP_Point[14] = new C3dVector();
DSP_Point[15] = new C3dVector();

DSP_Point[16] = new C3dVector();
DSP_Point[17] = new C3dVector();
DSP_Point[18] = new C3dVector();
DSP_Point[19] = new C3dVector();

DSP_Point[20] = new C3dVector();
DSP_Point[21] = new C3dVector();
DSP_Point[22] = new C3dVector();
DSP_Point[23] = new C3dVector();

DSP_Point[24] = new C3dVector();
DSP_Point[25] = new C3dVector();
DSP_Point[26] = new C3dVector();
DSP_Point[27] = new C3dVector();

DSP_Point[28] = new C3dVector();
DSP_Point[29] = new C3dVector();
DSP_Point[30] = new C3dVector();
DSP_Point[31] = new C3dVector();
DSP_Point[32] = new C3dVector();
DSP_Point[33] = new C3dVector();

DSP_Point[34] = new C3dVector();
DSP_Point[35] = new C3dVector();
DSP_Point[36] = new C3dVector();
DSP_Point[37] = new C3dVector();
DSP_Point[38] = new C3dVector();
DSP_Point[39] = new C3dVector();
}




void WP_Object::ReSize(double dWPSize)
{
double ds = 0.1*dWPSize;

if (dWPSize>0)
{

Pt_Point[0]->Set(-dWPSize/2,-dWPSize/2,0);
Pt_Point[1]->Set(dWPSize/2,-dWPSize/2,0);
Pt_Point[2]->Set(dWPSize/2,dWPSize/2,0);
Pt_Point[3]->Set(-dWPSize/2,dWPSize/2,0);

Pt_Point[24]->Set(0,-dWPSize/2,0);
Pt_Point[25]->Set(0,dWPSize/2,0);
Pt_Point[26]->Set(-dWPSize/2,0,0);
Pt_Point[27]->Set(dWPSize/2,0,0);

Pt_Point[4]->Set(-dWPSize/2+ds*0.5,-dWPSize/2+ds*0.5,0);
Pt_Point[5]->Set(-dWPSize/2+ds*2,-dWPSize/2+ds*0.5,0);
Pt_Point[6]->Set(-dWPSize/2+ds*2,-dWPSize/2+ds*0.25,0);
Pt_Point[7]->Set(-dWPSize/2+ds*2.4,-dWPSize/2+ds*0.75,0);
Pt_Point[8]->Set(-dWPSize/2+ds*2,-dWPSize/2+ds*1.25,0);
Pt_Point[9]->Set(-dWPSize/2+ds*2,-dWPSize/2+ds*1,0);

Pt_Point[10]->Set(-dWPSize/2+ds*1,-dWPSize/2+ds*1,0);

Pt_Point[11]->Set(-dWPSize/2+ds*1,-dWPSize/2+ds*2,0);
Pt_Point[12]->Set(-dWPSize/2+ds*1.25,-dWPSize/2+ds*2,0);
Pt_Point[13]->Set(-dWPSize/2+ds*0.75,-dWPSize/2+ds*2.4,0);
Pt_Point[14]->Set(-dWPSize/2+ds*0.25,-dWPSize/2+ds*2,0);
Pt_Point[15]->Set(-dWPSize/2+ds*0.5,-dWPSize/2+ds*2,0);

Pt_Point[16]->Set(-dWPSize/2+ds*2.5,-dWPSize/2+ds*0.25,0);
Pt_Point[17]->Set(-dWPSize/2+ds*3,-dWPSize/2+ds*1.25,0);
Pt_Point[18]->Set(-dWPSize/2+ds*2.5,-dWPSize/2+ds*1.25,0);
Pt_Point[19]->Set(-dWPSize/2+ds*3,-dWPSize/2+ds*0.25,0);


Pt_Point[20]->Set(-dWPSize/2+ds*0.75,-dWPSize/2+ds*2.5,0);
Pt_Point[21]->Set(-dWPSize/2+ds*0.75,-dWPSize/2+ds*3,0);
Pt_Point[22]->Set(-dWPSize/2+ds*1,-dWPSize/2+ds*3.5,0);
Pt_Point[23]->Set(-dWPSize/2+ds*0.5,-dWPSize/2+ds*3.5,0);

Pt_Point[28]->Set(-dWPSize/2+ds*2.5,-dWPSize/2+ds*0.25,0);
Pt_Point[29]->Set(-dWPSize/2+ds*3,-dWPSize/2+ds*0.25,0);
Pt_Point[30]->Set(-dWPSize/2+ds*2.5,-dWPSize/2+ds*1.25,0.0);
Pt_Point[31]->Set(-dWPSize/2+ds*3.0,-dWPSize/2+ds*1.25,0.0);
Pt_Point[32]->Set(-dWPSize/2+ds*3.0,-dWPSize/2+ds*0.75,0.0);
Pt_Point[33]->Set(-dWPSize/2+ds*2.5,-dWPSize/2+ds*0.75,0.0);

Pt_Point[34]->Set(-dWPSize/2+ds*0.5,-dWPSize/2+ds*2.5,0);
Pt_Point[35]->Set(-dWPSize/2+ds*1.0,-dWPSize/2+ds*2.5,0);
Pt_Point[36]->Set(-dWPSize/2+ds*0.5,-dWPSize/2+ds*3.5,0.0);
Pt_Point[37]->Set(-dWPSize/2+ds*1.0,-dWPSize/2+ds*3.5,0.0);
Pt_Point[38]->Set(-dWPSize/2+ds*1.0,-dWPSize/2+ds*3.0,0.0);
Pt_Point[39]->Set(-dWPSize/2+ds*0.5,-dWPSize/2+ds*3.0,0.0);
}
}

// Draw Object line
void WP_Object::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) DSP_Point[0]->x,(int) DSP_Point[0]->y);
pDC->LineTo((int) DSP_Point[1]->x,(int) DSP_Point[1]->y);
pDC->LineTo((int) DSP_Point[2]->x,(int) DSP_Point[2]->y);
pDC->LineTo((int) DSP_Point[3]->x,(int) DSP_Point[3]->y);
pDC->LineTo((int) DSP_Point[0]->x,(int) DSP_Point[0]->y);

pDC->MoveTo((int) DSP_Point[4]->x,(int) DSP_Point[4]->y);
pDC->LineTo((int) DSP_Point[5]->x,(int) DSP_Point[5]->y);
pDC->LineTo((int) DSP_Point[6]->x,(int) DSP_Point[6]->y);
pDC->LineTo((int) DSP_Point[7]->x,(int) DSP_Point[7]->y);
pDC->LineTo((int) DSP_Point[8]->x,(int) DSP_Point[8]->y);
pDC->LineTo((int) DSP_Point[9]->x,(int) DSP_Point[9]->y);
pDC->LineTo((int) DSP_Point[10]->x,(int) DSP_Point[10]->y);
pDC->LineTo((int) DSP_Point[11]->x,(int) DSP_Point[11]->y);
pDC->LineTo((int) DSP_Point[12]->x,(int) DSP_Point[12]->y);
pDC->LineTo((int) DSP_Point[13]->x,(int) DSP_Point[13]->y);
pDC->LineTo((int) DSP_Point[14]->x,(int) DSP_Point[14]->y);
pDC->LineTo((int) DSP_Point[15]->x,(int) DSP_Point[15]->y);
pDC->LineTo((int) DSP_Point[4]->x,(int) DSP_Point[4]->y);

pDC->MoveTo((int) DSP_Point[16]->x,(int) DSP_Point[16]->y);
pDC->LineTo((int) DSP_Point[17]->x,(int) DSP_Point[17]->y);
pDC->MoveTo((int) DSP_Point[18]->x,(int) DSP_Point[18]->y);
pDC->LineTo((int) DSP_Point[19]->x,(int) DSP_Point[19]->y);

pDC->MoveTo((int) DSP_Point[20]->x,(int) DSP_Point[20]->y);
pDC->LineTo((int) DSP_Point[21]->x,(int) DSP_Point[21]->y);
pDC->LineTo((int) DSP_Point[22]->x,(int) DSP_Point[22]->y);
pDC->MoveTo((int) DSP_Point[21]->x,(int) DSP_Point[21]->y);
pDC->LineTo((int) DSP_Point[23]->x,(int) DSP_Point[23]->y);
}

void WP_Object::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
OglDraw(iDspFlgs,dS1,dS2);
}

void WP_Object::OglDraw(int iDspFlgs,double dS1,double dS2)
{
C3dVector T_Point[40];
C3dVector V;
int i;

for (i=0;i<40;i++)
{
  V.x = Pt_Point[i]->x;
	V.y = Pt_Point[i]->y;
	V.z = Pt_Point[i]->z;
	T_Point[i] = mWPTransform * V; 
}





glColor3fv(cols[GetCol()]);
glBegin(GL_LINE_LOOP);
glVertex3f((float) T_Point[0].x,(float) T_Point[0].y,(float) T_Point[0].z);
glVertex3f((float) T_Point[1].x,(float) T_Point[1].y,(float) T_Point[1].z);
glVertex3f((float) T_Point[2].x,(float) T_Point[2].y,(float) T_Point[2].z);
glVertex3f((float) T_Point[3].x,(float) T_Point[3].y,(float) T_Point[3].z);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f((float) T_Point[4].x,(float) T_Point[4].y,(float) T_Point[4].z);
glVertex3f((float) T_Point[5].x,(float) T_Point[5].y,(float) T_Point[5].z);
glVertex3f((float) T_Point[6].x,(float) T_Point[6].y,(float) T_Point[6].z);
glVertex3f((float) T_Point[7].x,(float) T_Point[7].y,(float) T_Point[7].z);
glVertex3f((float) T_Point[8].x,(float) T_Point[8].y,(float) T_Point[8].z);
glVertex3f((float) T_Point[9].x,(float) T_Point[9].y,(float) T_Point[9].z);
glVertex3f((float) T_Point[10].x,(float) T_Point[10].y,(float) T_Point[10].z);
glVertex3f((float) T_Point[11].x,(float) T_Point[11].y,(float) T_Point[11].z);
glVertex3f((float) T_Point[12].x,(float) T_Point[12].y,(float) T_Point[12].z);
glVertex3f((float) T_Point[13].x,(float) T_Point[13].y,(float) T_Point[13].z);
glVertex3f((float) T_Point[14].x,(float) T_Point[14].y,(float) T_Point[14].z);
glVertex3f((float) T_Point[15].x,(float) T_Point[15].y,(float) T_Point[15].z);
glEnd();




//The R
if (iWPMode==1)
{
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[28].x,(float) T_Point[28].y,(float) T_Point[28].z);
  glVertex3f((float) T_Point[30].x,(float) T_Point[30].y,(float) T_Point[30].z);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[30].x,(float) T_Point[30].y,(float) T_Point[30].z);
  glVertex3f((float) T_Point[31].x,(float) T_Point[31].y,(float) T_Point[31].z);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[31].x,(float) T_Point[31].y,(float) T_Point[31].z);
  glVertex3f((float) T_Point[32].x,(float) T_Point[32].y,(float) T_Point[32].z);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[32].x,(float) T_Point[32].y,(float) T_Point[32].z);
  glVertex3f((float) T_Point[33].x,(float) T_Point[33].y,(float) T_Point[33].z);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[33].x,(float) T_Point[33].y,(float) T_Point[33].z);
  glVertex3f((float) T_Point[29].x,(float) T_Point[29].y,(float) T_Point[29].z);
  glEnd();
  //Theta
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[38].x,(float) T_Point[38].y,(float) T_Point[38].z);
  glVertex3f((float) T_Point[39].x,(float) T_Point[39].y,(float) T_Point[39].z);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f((float) T_Point[34].x,(float) T_Point[34].y,(float) T_Point[34].z);
  glVertex3f((float) T_Point[35].x,(float) T_Point[35].y,(float) T_Point[35].z);
  glVertex3f((float) T_Point[37].x,(float) T_Point[37].y,(float) T_Point[37].z);
  glVertex3f((float) T_Point[36].x,(float) T_Point[36].y,(float) T_Point[36].z);
  glEnd();
}
else
{
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[16].x,(float) T_Point[16].y,(float) T_Point[16].z);
  glVertex3f((float) T_Point[17].x,(float) T_Point[17].y,(float) T_Point[17].z);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[18].x,(float) T_Point[18].y,(float) T_Point[18].z);
  glVertex3f((float) T_Point[19].x,(float) T_Point[19].y,(float) T_Point[19].z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f((float) T_Point[20].x,(float) T_Point[20].y,(float) T_Point[20].z);
  glVertex3f((float) T_Point[21].x,(float) T_Point[21].y,(float) T_Point[21].z);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[21].x,(float) T_Point[21].y,(float) T_Point[21].z);
  glVertex3f((float) T_Point[22].x,(float) T_Point[22].y,(float) T_Point[22].z);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f((float) T_Point[21].x,(float) T_Point[21].y,(float) T_Point[21].z);
  glVertex3f((float) T_Point[23].x,(float) T_Point[23].y,(float) T_Point[23].z);
  glEnd();
}
glColor3fv(cols[154]);
glEnable(GL_LINE_STIPPLE);
glLineStipple(1,0x0101);
glBegin(GL_LINES);
glVertex3f((float) T_Point[24].x,(float) T_Point[24].y,(float) T_Point[24].z);
glVertex3f((float) T_Point[25].x,(float) T_Point[25].y,(float) T_Point[25].z);
glEnd();
glBegin(GL_LINES);
glVertex3f((float) T_Point[26].x,(float) T_Point[26].y,(float) T_Point[26].z);
glVertex3f((float) T_Point[27].x,(float) T_Point[27].y,(float) T_Point[27].z);
glEnd();
glDisable(GL_LINE_STIPPLE);
}

void WP_Object::Reset()
{
mWPTransform.MakeUnit();
}

void WP_Object::Align(C3dVector p1,C3dVector p2,C3dVector p3)
{
C3dVector vX;
C3dVector vZ;
C3dVector vYP;
vX=p2;
vX-=p1;
vX.Normalize();
vYP=p3;
vYP-=p1;
vYP.Normalize();
if ((vX.Mag()!=0) && (vYP.Mag()!=0))
{
  if (abs(vX.Dot(vYP))!=1)
  {
    vZ=vX.Cross(vYP);
    vYP=vZ.Cross(vX);
	  vX.Normalize();
    vYP.Normalize();
	  vZ.Normalize();
    mWPTransform.SetColVec(1,vX);
    mWPTransform.SetColVec(2,vYP);
    mWPTransform.SetColVec(3,vZ);
	  mWPTransform.Translate2(p1.x,p1.y,p1.z);
  }
}
}


void WP_Object::CentrePt(C3dVector p1)
{
  mWPTransform.Translate2(p1.x,p1.y,p1.z);
}

void WP_Object::AlignZ(C3dVector p1,C3dVector p2,C3dVector p3)
{
//  TWP->AlignZ(pO,pX,pZ);
C3dVector vX;
C3dVector vZ;
C3dVector vYP;
vX=p2;
vX-=p1;
vX.Normalize();
vZ=p3;
vZ.Normalize();
if ((vX.Mag()!=0) && (vZ.Mag()!=0))
{
  if (abs(vX.Dot(vZ))!=1)
  {
    //vZ=vX.Cross(vYP);
    vYP=vZ.Cross(vX);
    vX=vYP.Cross(vZ);
	  vX.Normalize();
    vYP.Normalize();
	  vZ.Normalize();
    mWPTransform.SetColVec(1,vX);
    mWPTransform.SetColVec(2,vYP);
    mWPTransform.SetColVec(3,vZ);
	  mWPTransform.Translate2(p1.x,p1.y,p1.z);
  }
}
}


void WP_Object::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
int j=0;
C3dVector V;
C3dVector R;
C3dMatrix mM;

for (j=0;j<28;j++)
   {
    V.x = Pt_Point[j]->x;
	  V.y = Pt_Point[j]->y;
	  V.z = Pt_Point[j]->z;
	  R = mWPTransform * V; 
    V = pModMat->Mult(R);
    R = pScrTran->Mult(V);
    DSP_Point[j]->x = R.x;
	  DSP_Point[j]->y = R.y;
	  DSP_Point[j]->z = R.z;
   }

}

void WP_Object::Transform(C3dMatrix TMat)
{
mWPTransform = TMat;
}


void WP_Object::HighLight(CDC* pDC)
{
Draw(pDC,4);
}


G_ObjectD WP_Object::SelDist(CPoint InPT,Filter FIL)
{
double d;
G_ObjectD Ret;
G_Object* pO;
d = 10000000000.0;
pO=this;
Ret.Dist=d;
Ret.pObj=pO;
return (Ret);
}







//----------------------------------------------------------------------------
//    W O R K  P L A N E    O B J E C T
//----------------------------------------------------------------------------



IMPLEMENT_DYNAMIC( ME_Object, CObject )

	
ME_Object::~ME_Object()
{
   int i;
   for(i=0;i<iBCLDs;i++)
   {
     delete(pBCLDs[i]);
     pBCLDs[i]=NULL;
   }
   for(i=0;i<iElNo;i++)
   {
     delete(pElems[i]);
   }
   for(i=0;i<iNdNo;i++)
   {
     delete(pNodes[i]);
   }
   for(i=0;i<iNoGps;i++)
   {
     delete(GPs[i]);
   }

}

ME_Object::ME_Object()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 0;
iObjType = 4;
iNdNo = 0;
iElNo = 0;
iNoGps = 0;
Name="NULL";
TransMat.MakeUnit();
pParent=NULL;
iNodeLab=0;
iElementLab=0;
bDrawN=TRUE;
isList=FALSE;
TempList=NULL;
iCYS=0;
iCYSLab=1;
iNodeLab=1;
iElementLab=1;

dScale=0;
iNoRes=0;
iCurResSet=-1;
iResVal=-1;
iCurResSetDef=-1;
iResValDef=-1;
}

void ME_Object::Create(CString inName,G_Object* Parrent,int iLab)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 0;
iObjType = 4;
iNdNo = 0;
iElNo = 0;
iBCLDs=0;
iNoGps = 0;
Name=inName;
TransMat.MakeUnit();
pParent=Parrent;
iNodeLab=1;
iElementLab=1;
G_label = iLab;
TempList=NULL;
iCYS=0;
iCYSLab=1;
CResSet=NULL;
CResSetDef=NULL;
iCVar=0;
iCVarDef=0;
dScale=0.5;
}



void ME_Object::Info()
{
  char S1[80];
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  outtext1("MESH OBJECT");
  outtext1(S1); 
  sprintf_s(S1,"%s%s","Name : ",Name);
  outtext1(S1);
  sprintf_s(S1,"%s%i","No of Nodes : ",iNdNo);

  outtext1(S1); 
  sprintf_s(S1,"%s%i","No of Elements : ",iElNo);
  outtext1(S1); 
  outtext1("    ****");
}

void ME_Object::RelTo(G_Object* pThis,ObjList* pList,int iType)
{
int i;
int j;
if ((iType==1) ||  (iType==3) ||  (iType==4) ||  (iType==12))
{
if ((pThis->iObjType==1) ||  (pThis->iObjType==3) ||  (pThis->iObjType==321) ||  (pThis->iObjType==322) ||  (pThis->iObjType==324))
{
  if (iType==4)
  {
    if (pThis->pParent!=NULL)
    {
     pList->AddEx(pThis->pParent);
    }
  }
  else if ((iType==1) &&  (pThis->iObjType==3)  &&  (pThis->pParent==this))
  {
     //Node related to element pThis
     for (i=0;i<iElNo;i++)
     {
       if (pElems[i]== pThis)
       {
          for (j=0;j<pElems[i]->iNoNodes;j++)
          {
             pList->AddEx(pElems[i]->GetNode(j));
          }
          break;
       }
     }
  }
  else if ((iType==1) &&  (pThis->iObjType==321)  &&  (pThis->pParent==this))
  {
     //Node related to element pThis
     G_Object* pN;
     pN=GetNode(pThis->G_label);
     if (pN!=NULL)
       pList->AddEx(pN);
  }
  else if ((iType==1) &&  (pThis->iObjType==322)  &&  (pThis->pParent==this))
  {
     //Node related to element pThis
     G_Object* pN;
     pN=GetNode(pThis->G_label);
     if (pN!=NULL)
       pList->AddEx(pN);
  }
  else if ((iType==3) &&  (pThis->iObjType==324)  &&  (pThis->pParent==this))
  {
     //Node related to element pThis
     E_Object* pE;
     pE=GetElement(pThis->G_label);
     if (pE!=NULL)
       pList->AddEx(pE);
  }
  else if ((iType==3) &&  (pThis->iObjType==1)  &&  (pThis->pParent==this))
  {
     //Element related to Node pThis
     for (i=0;i<iElNo;i++)
     {
       for (j=0;j<pElems[i]->iNoNodes;j++)
       {
         if (pElems[i]->GetNode(j)==pThis)
         {
             pList->AddEx(pElems[i]);
         }
       }
     }
  }
  else if ((iType==12) &&  (pThis->iObjType==1)  &&  (pThis->pParent==this))
  {
     //Coord related to Node pThis
     G_Object* pC;
	 Pt_Object* pN;
	 pN=(Pt_Object*) pThis;
	 if (pN->DefSys>0)
	 {
       pC=GetSys(pN->DefSys);
       if (pC!=NULL)
	   {
         pList->AddEx(pC);
	   }
	 }
	 if (pN->OutSys>0)
	 {
       pC=GetSys(pN->OutSys);
       if (pC!=NULL)
	   {
         pList->AddEx(pC);
	   }
     }
  }
}
}
}

void ME_Object::Serialize(CArchive& ar)
{
  int i;
  int iE;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
    ar<<Name;
	  ar<<bDrawN;
	  ar<<TransMat.m_00; ar<<TransMat.m_01; ar<<TransMat.m_02; ar<<TransMat.m_03;
	  ar<<TransMat.m_10; ar<<TransMat.m_11; ar<<TransMat.m_12; ar<<TransMat.m_13;
	  ar<<TransMat.m_20; ar<<TransMat.m_21; ar<<TransMat.m_22; ar<<TransMat.m_23;
	  ar<<TransMat.m_30; ar<<TransMat.m_31; ar<<TransMat.m_32; ar<<TransMat.m_33;

    ar<<iCYS;
	  for (i=0;i<iCYS;i++)
    {
      pSys[i]->Serialize(ar);
    }
    ar<<iNdNo;
    for (i=0;i<iNdNo;i++)
    {
      pNodes[i]->Serialize(ar);
    }
    ar << iElNo;
    for (i=0;i<iElNo;i++)
    {
      ar<<pElems[i]->iELType;
      pElems[i]->Serialize(ar,this);
    }
	  ar << iBCLDs;
	  for (i=0;i<iBCLDs;i++)
    {
      ar<<pBCLDs[i]->iObjType;
      pBCLDs[i]->Serialize(ar,this);
    }

	}
	else
	{
	  
    G_Object::Serialize(ar);
    ar>>Name;
	  ar>>bDrawN;
    ar>>TransMat.m_00; ar>>TransMat.m_01; ar>>TransMat.m_02; ar>>TransMat.m_03;
	  ar>>TransMat.m_10; ar>>TransMat.m_11; ar>>TransMat.m_12; ar>>TransMat.m_13;
	  ar>>TransMat.m_20; ar>>TransMat.m_21; ar>>TransMat.m_22; ar>>TransMat.m_23;
	  ar>>TransMat.m_30; ar>>TransMat.m_31; ar>>TransMat.m_32; ar>>TransMat.m_33;


    ar>>iCYS;
	  for (i=0;i<iCYS;i++)
    {
      pSys[i]= new CoordSys;
      pSys[i]->Serialize(ar);
      pSys[i]->pParent=this;
    }
	  ar>>iNdNo;
    if (iNdNo>5000)
      {TempList=new ObjTempList();}
    for (i=0;i<iNdNo;i++)
    {
      pNodes[i]= new Pt_Object;
      pNodes[i]->Serialize(ar);
      pNodes[i]->pParent=this;
      if (TempList!=NULL)
        {TempList->Objs[pNodes[i]->G_label]=pNodes[i];}
    }
    ar >> iElNo;
    for (i=0;i<iElNo;i++)
    {
      ar>>iE;
      switch(iE) 
      {
		    case 161:
          pElems[i] = new E_Object1;
          break;
		    case 21:
          pElems[i] = new E_Object2B;
          break;
        case 11:
          pElems[i] = new E_Object2R;
          break;
        case 22:
          pElems[i] = new E_Object2B;
          break;
        case 121:
          pElems[i] = new E_ObjectR2;
          break;
		    case 136:
          pElems[i] = new E_Object2;
          break;
		    case 137:
          pElems[i] = new E_Object2;
          break;
        case 91:
          pElems[i] = new E_Object3;
          break;
        case 94:
          pElems[i] = new E_Object4;
          break;
        case 115:
          pElems[i] = new E_Object38;
          break;
        case 111:
          pElems[i] = new E_Object34;
          break;
        case 112:
          pElems[i] = new E_Object36;
          break;
        case 122:
          pElems[i] = new E_ObjectR;
          break;
         case 1000:
          pElems[i] = new E_CellS;
          break;
        }
      pElems[i]->Serialize(ar,this);
	    pElems[i]->pParent=this;
    }
	  ar >> iBCLDs;
	  for (i=0;i<iBCLDs;i++)
    {
      ar>>iE;
      switch(iE) 
      {
		    case 321:
          pBCLDs[i] = new Force;
          break;
		    case 322:
          pBCLDs[i] = new Restraint;
          break;
        case 323:
          pBCLDs[i] = new Moment;
          break;
        case 324:
          pBCLDs[i] = new Pressure;
          break;
      }
      pBCLDs[i]->Serialize(ar,this);
    }
    if (TempList!=NULL)
    {
      delete(TempList);
      TempList = NULL;
    }
    this->MaxLab();
  }
}




G_Object* ME_Object::Copy(G_Object* Parrent)
{
int i;
int iE;
ME_Object* rME = new ME_Object;
rME->Drawn = Drawn;
rME->Selectable  = Selectable; 
rME->Visable  = Visable;
rME->G_Colour = G_Colour;
rME->iObjType = iObjType;
rME->G_label = G_label;
rME->Name = Name;
rME->iNdNo=iNdNo;
rME->bDrawN=bDrawN;
rME->pParent = NULL;

//rME->iNoMats=iNoMats;
//for (i=0;i<iNoMats;i++)
//{
//  rME->pMats[i]=pMats[i]->Copy();
//}
for (i=0;i<iNdNo;i++)
{
  rME->pNodes[i]= new Pt_Object;
  rME->pNodes[i]= (Pt_Object*) pNodes[i]->Copy(rME);
}

rME->iElNo=iElNo;
for (i=0;i<iElNo;i++)
{
  iE=pElems[i]->iELType;
  switch(iE) 
  {
	case 161:
      rME->pElems[i] = (E_Object1*) pElems[i]->Copy(rME);
      break;
	case 21:
      rME->pElems[i] = (E_Object2*) pElems[i]->Copy(rME);
      break;
	case 22:
      rME->pElems[i] = (E_Object2*) pElems[i]->Copy(rME);
      break;
    case 121:
      rME->pElems[i] = (E_Object2*) pElems[i]->Copy(rME);
      break;
    case 136:
      rME->pElems[i] = (E_Object2*) pElems[i]->Copy(rME);
      break;
    case 137:
      rME->pElems[i] = (E_Object2*) pElems[i]->Copy(rME);
      break;
    case 91:
      rME->pElems[i] = (E_Object3*) pElems[i]->Copy(rME);
      break;
    case 94:
      rME->pElems[i] = (E_Object4*) pElems[i]->Copy(rME);
      break;
    case 115:
      rME->pElems[i] = (E_Object38*) pElems[i]->Copy(rME);
      break;
    case 111:
      rME->pElems[i] = (E_Object34*) pElems[i]->Copy(rME);
      break;
	  case 112:
      rME->pElems[i] = (E_Object36*) pElems[i]->Copy(rME);
      break;
    case 122:
      rME->pElems[i] = (E_ObjectR*) pElems[i]->Copy(rME);
      break;
  }
  rME->pElems[i]->pParent = rME;
}
rME->iCYS=iCYS;
for (i=0;i<iCYS;i++)
{
  rME->pSys[i] = (CoordSys*) pSys[i]->Copy(rME);
}


return (rME);
}

BOOL ME_Object::isFaceDeletable(cFace* inFace)
{
BOOL bRet=TRUE;
cFace* Fc[8];
int iN;
int i,j;
int iC;
iC=0;
for(i=0;i<iElNo;i++)
{
  iN = pElems[i]->GetfaceList(Fc);
  if (iN>0)
  {
    for (j=0;j<iN;j++)
    {
      if (inFace->isSame(Fc[j])==TRUE)
	  {
        iC++;
		delete(Fc[j]);
	  }
    }
	if (iC>1){break;}
  }
}
if (iC>1)
{
  bRet=FALSE;
}
return(bRet);
}

BOOL ME_Object::isLinkDeletable(cLink* inLink)
{
BOOL bRet=TRUE;
cLink* Lk[12];
int iN;
int i,j;
int iC;
iC=0;
for(i=0;i<iElNo;i++)
{
  iN = pElems[i]->GetLinkList(Lk);

  if (iN>0)
  {
    for (j=0;j<iN;j++)
    {
      if (inLink->isSame(Lk[j])==TRUE)
	  {
        iC++;
		delete(Lk[j]);
	  }
    }
	if (iC>1){break;}
  }
}
if (iC>1)
{
  bRet=FALSE;
}
return(bRet);
}

void ME_Object::GenList()
{
cFace* Fc[8];
cLink* Lk[200];
int iN;
int i,j;
for(i=0;i<iElNo;i++)
{
  iN = pElems[i]->GetfaceList(Fc);
  if (iN>0)
  {
    for (j=0;j<iN;j++)
    {
      FcList.Add(Fc[j]);
    }
  }
  iN = pElems[i]->GetLinkList(Lk);
  if (iN>0)
  {
    for (j=0;j<iN;j++)
    {
       LkList.Add(Lk[j]);
    }
  }
}
outtext1("Finished List generation");
}


void ME_Object::Append(ME_Object* pMexh,int iNInc,int iEInc)
{
int i;
int iSNodePos;

int iPIDold;

iSNodePos=this->iNdNo;


if (pMexh!=NULL)
{
  GPs[iNoGps] = new NEList();
  GPs[iNoGps]->Title = pMexh->Name;
  iNoGps++;
  for (i=0;i<pMexh->iNdNo;i++)
  {
    this->pNodes[iNdNo]= new Pt_Object;
    this->pNodes[iNdNo]= (Pt_Object*) pMexh->pNodes[i]->Copy(this);
    this->pNodes[iNdNo]->G_label=iNdNo+1+iNInc; 
    GPs[iNoGps-1]->ids[GPs[iNoGps-1]->iNo] = this->pNodes[iNdNo]->G_label;
    GPs[iNoGps-1]->iType[GPs[iNoGps-1]->iNo] = 1;
    GPs[iNoGps-1]->iNo++;
    iNdNo++;
  }
  int iE;
  for (i=0;i<pMexh->iElNo;i++)
  {
    iE=pMexh->pElems[i]->iELType;
    switch(iE) 
    {
	  case 161:
      this->pElems[iElNo] = (E_Object1*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
	  case 21:
      this->pElems[iElNo] = (E_Object2*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 22:
      this->pElems[iElNo] = (E_Object2*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 121:
      this->pElems[iElNo] = (E_Object2*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 136:
      this->pElems[iElNo] = (E_Object2*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 137:
      this->pElems[iElNo] = (E_Object2*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 91:
      this->pElems[iElNo] = (E_Object3*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 94:
      this->pElems[iElNo] = (E_Object4*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 115:
      this->pElems[iElNo] = (E_Object38*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 111:
      this->pElems[iElNo] = (E_Object34*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
	  case 112:
      this->pElems[iElNo] = (E_Object36*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    case 122:
      this->pElems[iElNo] = (E_ObjectR*) pMexh->pElems[i]->CopyAppend(iSNodePos,this,pMexh);
      break;
    }
    this->pElems[iElNo]->G_label=iElNo+1+iEInc;
    this->pElems[iElNo]->pPr=NULL;
    GPs[iNoGps-1]->ids[GPs[iNoGps-1]->iNo] = this->pElems[iElNo]->G_label;
    GPs[iNoGps-1]->iType[GPs[iNoGps-1]->iNo] = 3;
    GPs[iNoGps-1]->iNo++;
    iElNo++;
  }
}

}

ME_Object* ME_Object::GetMesh()    //GetPtr to this
{
return (this);
}


void ME_Object::ExportSec(FILE* pFile,int id,CString Name, double w,double h,double t)
{
double Area;
double w1;
double h1;
double Ixx;
double Iyy;
w1=w-2*t;
h1=h-2*t;
Area=w*h-w1*h1;
Ixx=(w*h*h*h)/12-(w1*h1*h1*h1)/12;
Iyy=(h*w*w*w)/12-(h1*w1*w1*w1)/12;

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

void ME_Object::ExportNAS(FILE* pFile,SecTable* pS)	 
{
int i;
fprintf(pFile,"%s\n","$***************COORDINATE SYSTEMS*************************");
for (i=0;i<iCYS;i++)
{
	pSys[i]->ExportNAS(pFile);
}

fprintf(pFile,"%s\n","$********************NODES*********************************");
for (i=0;i<iNdNo;i++)
{
  CoordSys* pDef = GetSys(pNodes[i]->DefSys);
	pNodes[i]->ExportNAS(pFile,pDef);
}
fprintf(pFile,"%s\n","$*******************ELEMENTS******************************");
for (i=0;i<iElNo;i++)
{
	pElems[i]->ExportNAS(pFile);
}
fprintf(pFile,"%s\n","$********************FORCES*******************************");
for (i=0;i<iBCLDs;i++)
{
  if ((pBCLDs[i]->iObjType==321) || (pBCLDs[i]->iObjType==323))
   pBCLDs[i]->ExportNAS(pFile);
}
fprintf(pFile,"%s\n","$*******************RESTRAINTS***************************");
for (i=0;i<iBCLDs;i++)
{
  if (pBCLDs[i]->iObjType==322)
	  pBCLDs[i]->ExportNAS(pFile);
}
}

void ME_Object::SetColourBar(float fMax,float fMin)
{
SetColBar(fMin,fMax);
}

void ME_Object::PostElResScalar(ResSet* pRes,int iVar,float &fMax,float &fMin)
{
int i;
fMax=-1e+20;
fMin=1e+20;

if (pRes!=CResSet)
{
  for (i = 0; i < iNdNo; i++)
  {
    pNodes[i]->pResV=NULL;
  }
  for (i = 0; i < iElNo; i++)
  {
    pElems[i]->pResV=NULL;
  }
  if ((iElNo > 0) && (pRes->TCODE==4))
  {
    for (i = 0; i < iElNo; i++)
    {
        Res* pR=pRes->Get(pElems[i]->G_label);
        if (pR!=NULL)
        {
          pElems[i]->pResV=pR;
        }  
    }
  }

  if (iNdNo > 0) 
  {
    if ((pRes->TCODE==1) || (pRes->TCODE==7))
    {
      for (i = 0; i < iNdNo; i++)
      {
        if (pRes->iNoV==6)
        {
          Res6* pR=(Res6*) pRes->Get(pNodes[i]->G_label);
          if (pR!=NULL)
          {
            pNodes[i]->pResV=pR;
          }
        }
      }
    }
  }
}
float fResVal;
//Calculate Max Min
  if (iNdNo > 0) 
  {
    if ((pRes->TCODE==1)||(pRes->TCODE==7))
    {
      for (i = 0; i < iNdNo; i++)
      {
        if (pNodes[i]->pResV!=NULL)
        {
           fResVal=*pNodes[i]->pResV->GetAddress(iVar);
           if (fResVal>fMax){fMax=fResVal;}
           if (fResVal<fMin){fMin=fResVal;}
        }
      }
    }
  }
  if ((iElNo > 0) && (pRes->TCODE==4))
  {
    for (i = 0; i < iElNo; i++)
    {
      if (pElems[i]->pResV!=NULL)
      {
         fResVal=*pElems[i]->pResV->GetAddress(iVar);
         if (fResVal>fMax){fMax=fResVal;}
         if (fResVal<fMin){fMin=fResVal;}
      }
    }
  }
pRes->fMaxV=fMax;
pRes->fMinV=fMin;
CResSet=pRes;
iCVar=iVar;
SetColBar(fMin,fMax);
}

void ME_Object::PostElResDef(ResSet* pRes,int iVar,float &fMax,float &fMin)
{
int i;
fMax=-1e+20;
fMin=1e+20;

if (pRes!=CResSetDef) 
{
  for (i = 0; i < iNdNo; i++)
  {
    pNodes[i]->pResD=NULL;
  }
  if (iNdNo > 0) 
  {
    if ((pRes->TCODE==1) || (pRes->TCODE==7))
    {
      for (i = 0; i < iNdNo; i++)
      {
        if (pRes->iNoV==6)
        {
          Res6* pR=(Res6*) pRes->Get(pNodes[i]->G_label);
          if (pR!=NULL)
          {
            pNodes[i]->pResD=pR;
          }
        }
      }
    }
  }
}

CResSetDef=pRes;
iCVarDef=iVar;
BuildDeromedVecs();
}

void ME_Object::BuildDeromedVecs()
{
int i;
C3dVector* pV;
if (CResSetDef!=NULL)
{
  if (iNdNo > 0) 
  {
    if ((CResSetDef->TCODE==1) || (CResSetDef->TCODE==7))
    {
      for (i = 0; i < iNdNo; i++)
      {
        Res* pR=pNodes[i]->pResD;
        if (pR!=NULL)
        {
           if (pR->pVec!=NULL)
           {
             delete(pR->pVec);
             pR->pVec=NULL;
           }
             pR->pVec=new C3dVector();

             pR->pVec->x=*pR->GetAddress(0);
             pR->pVec->y=*pR->GetAddress(1);
             pR->pVec->z=*pR->GetAddress(2);
             if (iResValDef==0)
             {
               pR->pVec->y=0;
               pR->pVec->z=0;
             }
             if (iResValDef==1)
             {
               pR->pVec->x=0;
               pR->pVec->z=0;
             }
             if (iResValDef==2)
             {
               pR->pVec->x=0;
               pR->pVec->y=0;
             }
        }
      }
    }
  }
}
}

void ME_Object::DeleteDeromedVecs()
{
    int i;
    for (i = 0; i < iNdNo; i++)
    {
      Res* pR=pNodes[i]->pResD;
      if (pR!=NULL)
      {
         if (pR->pVec!=NULL)
         {
           delete(pR->pVec);
           pR->pVec=NULL;
         }
      }
    }
}

void ME_Object::ExportGroups(FILE* pFile)	 
{
int i;
int j;
E_Object* pE;
Pt_Object* pN;
 fprintf(pFile,"%-10s%-10s%-10s%-10s%-10s\n","ELEM","ID","COL","PID","TYPE");
 fprintf(pFile,"%-10s%-10s%-10s%-10s%-10s\n","NODE","ID","COL","DEF","OUT");
for (i=0;i<iNoGps;i++)
{
  fprintf(pFile,"%-s\n","GROUP");
  fprintf(pFile,"%-s\n",GPs[i]->Title);
  fprintf(pFile,"%-i\n",GPs[i]->iNo);
  for (j=0;j<GPs[i]->iNo;j++)
  {
    if (GPs[i]->iType[j]==3)
    {
      pE=this->GetElement(GPs[i]->ids[j]);
      if (pE!=NULL)
	    fprintf(pFile,"%-10s%-10i%-10i%-10i%-10i\n","ELEM",GPs[i]->ids[j],pE->G_Colour,pE->PID,pE->iELType);
    }
    if (GPs[i]->iType[j]==1)
    {
      pN=this->GetNode(GPs[i]->ids[j]);
      if (pN!=NULL)
	    fprintf(pFile,"%-10s%-10i%-10i%-10i%-10i\n","NODE",GPs[i]->ids[j],pN->G_Colour,pN->DefSys,pN->OutSys);
    }
  }
}
}



void ME_Object::ExportUNV(FILE* pFile,SecTable* pS)	 
{
int i;
int j;
COleDateTime timeStart;
timeStart = COleDateTime::GetCurrentTime();

int year=timeStart.GetYear();
int Mon=timeStart.GetMonth();
if (year<2012)
{
BOOL bNL;
//Dataset 164 Units
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","164");
fprintf(pFile,"%10i%20s%10i\n",1,"Meter (newton)               ",2);
fprintf(pFile,"%25.16E%25.16E%25.16E\n",1.0,1.0,1.0);
fprintf(pFile,"%25.16E\n",1.0);
fprintf(pFile,"%6s\n","-1");
if (pS!=NULL)
{
  pS->ExportSecs(pFile);
}
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","2411");
for (i=0;i<iNdNo;i++)
{
	pNodes[i]->ExportUNV(pFile);
}
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","2412");
for (i=0;i<iElNo;i++)
{
	pElems[i]->ExportUNV(pFile);
}
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","2438");
for (i=0;i<iElNo;i++)
{
  if (pElems[i]->iELType==21)
  {
    E_Object2B* E = (E_Object2B*) pElems[i];
	  E->ExportUPVecs(pFile);
  }
}
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","-1");
fprintf(pFile,"%6s\n","2435");
for (i=0;i<iNoGps;i++)
{
  fprintf(pFile,"%10i%10i%10i%10i%10i%10i%10i%10i\n",i+1,0,0,0,0,0,0,GPs[i]->iNo);
  fprintf(pFile,"%s\n",GPs[i]->Title);
  bNL=FALSE;
  for (j=0;j<GPs[i]->iNo;j++)
  {
  if (GPs[i]->iType[j]==3)
  {
	  fprintf(pFile,"%10i%10i%10i%10i",8,GPs[i]->ids[j],0,0);
  }
  else if (GPs[i]->iType[j]==1)
  {
	  fprintf(pFile,"%10i%10i%10i%10i",7,GPs[i]->ids[j],0,0);
  }
	if (bNL==FALSE)
	{
      bNL=TRUE;
	}
    else
	{
      bNL=FALSE;
      fprintf(pFile,"\n","");
	}

  }
  if (bNL==TRUE)
  {
      fprintf(pFile,"\n","");
  }
}
fprintf(pFile,"%6s\n","-1");
}
}

int ME_Object::GetNoNode(int iType)
{
int iRC=-1;
switch(iType) 
{
case 115: iRC = 8; //115 //BRICK 8
	break;
case 112: iRC = 6; //WEDGE 6 
    break;
case 111: iRC = 4; //TET 4
	break;
case 94 : iRC = 4; //QUAD 4
    break;
case 91: iRC = 3;  //TRI 3
    break;
case 161: iRC = 1; //SCALAR
    break;
case 121: iRC = 2; //UNKNOWN 2
    break;
case 136: iRC = 2; //UNKNOWN 2
    break;
case 137: iRC = 2; //UNKNOWN 2
    break;
case 21: iRC = 2;  //BEAM 2
    break;
case 11: iRC = 2;  //ROD 2
    break;
case 22: iRC = 2;    //UNKNOWN 2
    break;
case 122: iRC = 200; //RIGID 200
    break;
case 1000: iRC = 4; //STAGGERED CELL
    break;
}
return (iRC);
}





void ME_Object::Test(PropTable* PropsT,MatTable* MatT)
{
int i,j,neq;
COleDateTime timeStart;
timeStart = COleDateTime::GetCurrentTime();
int Hour=timeStart.GetHour();
int Min=timeStart.GetMinute();
int Sec=timeStart.GetSecond();
char s1[80];
  

FILE* pFile;
sprintf(s1,"%s %i:%i:%i\n","START TIME",Hour,Min,Sec);
outtext1(s1);
for(i=0;i<iNdNo;i++)
{
  for (j=0;j<6;j++)
  {
    pNodes[i]->dof[j]=0;
  }
}



Mat KME;
//Mat dee=DeeMat(100,0.29,6);
this->ApplyRes();
neq=GenDofs();
if (neq==0)
{
  outtext1("Error no degrees of freedom exist");
  outtext1("Ensure the correct F.E. model is active");
}
else
{
  Vec<double> FVec;
  Vec<int> Steer;
  FVec = GetForceVec(neq);
  GetPressureLoads(neq,FVec);
  int iBW=this->MaxBW();

  Vec <double> KM(neq*(iBW+1));
  LocalRes(neq,Steer,KM);
  outtext1("STARTING ASSY");
  E_Object* pE;


  for (i=0;i<iElNo;i++)
  {
    pE=pElems[i];
    
    if (pE->ChkNegJac()==FALSE)
    {
      KME=pE->GetStiffMat(PropsT,MatT);
      Steer=pE->GetSteerVec2d();
    }
    else
    {

      pE=(E_Object*) pElems[i]->Copy(this);
      pE->Reverse();
      KME=pE->GetStiffMat(PropsT,MatT);
      Steer=pE->GetSteerVec2d();
      delete(pE);
      pE=NULL;
    }

    formkv(KM,KME,Steer,neq);
    KME.diag();
    KME.clear();
  }

  KM.diag();
  outtext1("STARTING BAND REDUCTION");
  banred(KM,neq);
  outtext1("STARTING BACK SUBSTITUTION");
  bacsub(KM,FVec);
  outtext1("FINISHED SOLUTION");
  Displacements(Steer,FVec);
  StressesBeam(PropsT,MatT,Steer,FVec);
  Stresses2d(PropsT,MatT,Steer,FVec);
  Stresses3d(PropsT,MatT,Steer,FVec);
  KM.DeleteAll();
  Steer.DeleteAll();
}
timeStart = COleDateTime::GetCurrentTime();
Hour=timeStart.GetHour();
Min=timeStart.GetMinute();
Sec=timeStart.GetSecond();
sprintf(s1,"%s %i:%i:%i\n","END TIME",Hour,Min,Sec);
outtext1(s1);
}

Mat GetG(Vec<double> &AA,Vec<int> &G)
{
int iS;
int i;
iS=G.n;

Mat pMult(iS,1);
for (i=1;i<=iS;i++)
{
  if (*G.nn(i)>0)
  {
    int ii;
    ii=*G.nn(i);
    double pM=*AA.nn(ii);
    *pMult.mn(i,1)=*AA.nn(ii);
  }
}        
return (pMult);
}

double IterConv(Vec<double> &X,Vec<double> &XNew)
{
int iS;
int i;
double dD=0;
double dDa=0;
double MaxDiff=0;
double MaxDiff1=0;
iS=X.n;
for (i=0;i<iS;i++)
{
  double a=XNew(i);
  double b=X(i);
  dD=abs(XNew(i)-X(i));
  dDa=abs(XNew(i));
  if (dD>MaxDiff) MaxDiff=dD;
  if (dDa>MaxDiff1) MaxDiff1=dDa;
}
return(MaxDiff/MaxDiff1);
}



double DotProd(Vec<double> &AA,Vec<double> &BB)
{
int iS;
int i;
double dP=0;
iS=AA.n;
for (i=0;i<iS;i++)
{
double f=AA(i);
double p=BB(i);
dP+=AA(i)*BB(i);
}
return(dP);
}

void PutG(Vec<double> &AA,Vec<int> &G,Mat& M)
{
int iS;
int i;
iS=G.n;
int ii;

for (i=1;i<=iS;i++)
{

  ii=*G.nn(i);
  if (ii>0)
  {
    double mmm=*M.mn(i,1);
    *AA.nn(ii)+=*M.mn(i,1);
  }
}        

}


void ME_Object::IterSol(PropTable* PropsT,MatTable* MatT)
{
int i,j,neq;
COleDateTime timeStart;
timeStart = COleDateTime::GetCurrentTime();
int Hour=timeStart.GetHour();
int Min=timeStart.GetMinute();
int Sec=timeStart.GetSecond();
char s1[80];
double dErr;
int iELCnt;
   


sprintf(s1,"%s %i:%i:%i\n","START TIME",Hour,Min,Sec);
outtext1(s1);
for(i=0;i<iNdNo;i++)
{
  for (j=0;j<6;j++)
  {
    pNodes[i]->dof[j]=0;
  }
}
int m;


Mat KME;
//This applies glodal retraints
//local restraints will be delt with later
this->ApplyRes();
neq=GenDofs();
sprintf(s1,"%s: %i\n","No of Equations",neq);
outtext1(s1);
if (neq==0)
{
  outtext1("Error no degrees of freedom exist");
  outtext1("Ensure the correct F.E. model is active");
}
else
{
  Vec<double> FVec;
  Vec<int> Steer;
  FVec = GetForceVec(neq);
  GetPressureLoads(neq,FVec);
  int iBW=this->MaxBW();
  iELCnt=0;
  int iNoRestEl=LocalResCount();
  Mat* KM = new Mat[iElNo+iNoRestEl];
  Vec<int>* G = new Vec<int>[iElNo+iNoRestEl];
  //Get the local global restrain fictisous element
    Mat KResT(6,6);
    Vec<int> SResT(6);
    Mat KResB(6,6);
    Vec<int> SResB(6);
    for (i=0;i<iBCLDs;i++)
    {
      if (pBCLDs[i]->iObjType==322)
      {
        Restraint* pR=(Restraint*) pBCLDs[i];
        Pt_Object* pNode=(Pt_Object*) pR->pObj;
        if (pNode->OutSys!=0)
        {
          LocalResIter(pR,SResT,KResT,SResB,KResB);
          KM[iELCnt]=KResT;
          G[iELCnt]=SResT;
          iELCnt++;
          KM[iELCnt]=KResB;
          G[iELCnt]=SResB;
          iELCnt++;
        }
      }
    }
  //End of local restraints
  outtext1("STARTING ASSY");
  E_Object* pE;
  Vec<double> DiagPrecon(neq);
  for (i=0;i<iElNo;i++)
  {
    pE=pElems[i];
    if (pE->ChkNegJac()==FALSE)
    {
      KME=pE->GetStiffMat(PropsT,MatT);
      Steer=pE->GetSteerVec2d();
    }
    else
    {
      pE=(E_Object*) pElems[i]->Copy(this);
      pE->Reverse();
      KME=pE->GetStiffMat(PropsT,MatT);
      Steer=pE->GetSteerVec2d();
      delete(pE);
      pE=NULL;
    }
    KM[iELCnt]=KME;
    G[iELCnt]=Steer;

    iELCnt++;
    KME.clear();
    Steer.clear();
  }
  for (i=0;i<iELCnt;i++)
  {
    for (m=1;m<=KM[i].m;m++)
    {
      if (G[i](m-1)>0)
      { double d1;
        d1=G[i](m-1);
        *DiagPrecon.nn(G[i](m-1))+=*KM[i].mn(m,m);
      }
    }
  }
  //Invert DiagPrecon
  Vec<double> d(neq);
  Vec<double> p(neq);
  for (i=0;i<neq;i++)
  {
    DiagPrecon(i)=1.0/DiagPrecon(i);
    double dT=DiagPrecon(i)*FVec(i);
    d(i)=DiagPrecon(i)*FVec(i);
    p(i)=d(i);
  }
  double up;
  double beta;
  double alpha;
  Mat pMult;
  Vec<double> x(neq);
  Vec<double> xnew(neq);
  outtext1("STARTING ITERATIVE SOLUTION");
  i=0;
  do
  {

     Vec<double> u(neq);
     for (j=0;j<iELCnt;j++)
     {
       pMult=GetG(p,G[j]);
       Mat uTemp=KM[j]*pMult;
       PutG(u,G[j],uTemp);
       pMult.clear();
     }
     up=DotProd(FVec,d);
     if (up==0) 
     {
       outtext1("WARNING Forced stop");
       break;
     }
     alpha=up/DotProd(p,u);
     for (m=0;m<xnew.n;m++)
     {
       xnew(m)=x(m)+p(m)*alpha;
       FVec(m)=FVec(m)-u(m)*alpha;
       d(m)=DiagPrecon(m)*FVec(m);
     }
     beta=DotProd(FVec,d)/up;
     for (m=0;m<xnew.n;m++)
     {
       p(m)=d(m)+p(m)*beta;
     }
     dErr=IterConv(x,xnew);
     x=xnew;
     if (i%100==0)
     {
        sprintf(s1,"%s: %i %s: %1.16f\n","ITER",i,"Err",dErr);
        outtext1(s1);
     }
     u.clear();
     i++;   
  }
  while(dErr>0.000001);
  sprintf(s1,"%s: %1.16f\n","FINAL ERR",dErr);
  outtext1(s1);
  for (i=0;i<iELCnt;i++)
  {
      KM[i].clear();
      G[i].clear();
  }
  delete [] KM;
  delete [] G;
  outtext1("FINISHED SOLUTION");
  Displacements(Steer,xnew);
  StressesBeam(PropsT,MatT,Steer,xnew);
  Stresses2d(PropsT,MatT,Steer,xnew);
  Stresses3d(PropsT,MatT,Steer,xnew);
}

timeStart = COleDateTime::GetCurrentTime();
Hour=timeStart.GetHour();
Min=timeStart.GetMinute();
Sec=timeStart.GetSecond();
sprintf(s1,"%s %i:%i:%i\n","END TIME",Hour,Min,Sec);
outtext1(s1);
}


int ME_Object::MaxBW()
{
int iMaxBW=0;
int iMB;
int i;
for (i=0;i<iElNo;i++)
{
  iMB=pElems[i]->MaxBW();
  if (iMB>iMaxBW)
  {
    iMaxBW=iMB;
  }
}
return (iMaxBW);
}

G_Object* ME_Object::AddForce(Pt_Object* pInNode,C3dVector inF,int inSetID)
{
Force* pF=new Force;;
pF->Create(pInNode,
		       this,
		       inF,
		       inSetID);
pBCLDs[iBCLDs] = pF;
iBCLDs++;
return (pBCLDs[iBCLDs-1]);
}

G_Object* ME_Object::AddMoment(Pt_Object* pInNode,C3dVector inF,int inSetID)
{
Moment* pF=new Moment;;
pF->Create(pInNode,
		       this,
		       inF,
		       inSetID);
pBCLDs[iBCLDs] = pF;
iBCLDs++;
return (pBCLDs[iBCLDs-1]);
}

G_Object* ME_Object::AddPressure(E_Object* pInE,C3dVector inF,int inSetID)
{
Pressure* pF=new Pressure();
pF->Create(pInE,
		       this,
		       inF,
		       inSetID);
pBCLDs[iBCLDs] = pF;
iBCLDs++;
return (pBCLDs[iBCLDs-1]);
}


void ME_Object::GetPressureLoads(int neq,Vec<double> &FVec)
{
int i,j,k;
double P;
Mat coord;
Mat Press;
Mat deriv;
Mat deriv2;
Mat fun;
Mat jac;
Mat Points;
double det;
double nip;

for (i=0;i<iBCLDs;i++)
{
  if (pBCLDs[i]->iObjType==324)
  {
     E_Object* pE = (E_Object*) pBCLDs[i]->pObj;
     Pressure* pP=(Pressure*) pBCLDs[i];
     P=pP->F.x;
     if (pE->iELType==91)
     {
       nip=1;
     }
     else if (pE->iELType==94)
     {
       nip=4;
     }
     coord.clear();
     Points.clear();
     Press.clear();
     Press.Create(1,pE->iNoNodes);
     coord=pE->getCoords3d();
     Points=pE->Sample(nip);
     for(k=1;k<nip+1;k++)
     {
       det = 0;
       fun=pE->ShapeFun(Points, k);
       deriv=pE->ShapeDer(Points, k);
       jac = deriv*coord;
       jac=jac.InvertJac(det);
       for (j=0;j<pE->iNoNodes;j++)
       {
        *Press.mn(1,j+1)+=*fun.mn(1,j+1)*P*det**Points.mn(k,3);
        double pp=*Press.mn(1,j+1);
        pp=pp;
       }
     }
     C3dVector vN;
     vN=pE->Get_Normal();
     vN.Normalize();
     Pt_Object* pN;
     for (j=0;j<pE->iNoNodes;j++)
     {
       pN=(Pt_Object*) pE->GetNode(j);
       if (pN->dof[0]>0)
	     {
         *FVec.nn(pN->dof[0])+=*Press.mn(1,j+1)*vN.x;
	     }
       if (pN->dof[1]>0)
	     {
         *FVec.nn(pN->dof[1])+=*Press.mn(1,j+1)*vN.y;
	     }
       if (pN->dof[2]>0)
	     {
         *FVec.nn(pN->dof[2])+=*Press.mn(1,j+1)*vN.z;
	     }
     }
  }
}
}


Vec <double> ME_Object::GetForceVec(int neq)
{
Vec <double> FVec(neq);
int i;
for (i=0;i<iBCLDs;i++)
{
  if (pBCLDs[i]->iObjType==321)
  {
     Pt_Object* pNode = (Pt_Object*) pBCLDs[i]->pObj;
     Force* pF=(Force*) pBCLDs[i];
     if (pNode->dof[0]>0)
	   {
       *FVec.nn(pNode->dof[0])=pF->F.x;
	   }
	   if (pNode->dof[1]>0)
	   {
       *FVec.nn(pNode->dof[1])=pF->F.y;
	   }
	   if (pNode->dof[2]>0)
	   {
       *FVec.nn(pNode->dof[2])=pF->F.z;
	   }
  }
  else if (pBCLDs[i]->iObjType==323)
  {
     Pt_Object* pNode = (Pt_Object*) pBCLDs[i]->pObj;
     Moment* pF=(Moment*) pBCLDs[i];
     if (pNode->dof[3]>0)
	   {
       *FVec.nn(pNode->dof[3])=pF->F.x;
	   }
	   if (pNode->dof[4]>0)
	   {
       *FVec.nn(pNode->dof[4])=pF->F.y;
	   }
	   if (pNode->dof[5]>0)
	   {
       *FVec.nn(pNode->dof[5])=pF->F.z;
	   }
  }
}
return (FVec);
}




G_Object* ME_Object::AddRestraint(Pt_Object* pInNode,
								  BOOL xon,
								  BOOL yon,
								  BOOL zon,
								  BOOL rxon,
								  BOOL ryon,
								  BOOL rzon,
								  int inSetID)
{
Restraint* pR=new Restraint;
pR->Create(pInNode,
		   this,
		   xon,yon,zon,rxon,ryon,rzon,
		   inSetID);
pBCLDs[iBCLDs] = pR;
iBCLDs++;
return (pBCLDs[iBCLDs-1]);
}

void ME_Object::ApplyRes()
{
int i,j;

for (i=0;i<iBCLDs;i++)
{
  if (pBCLDs[i]->iObjType==322)
  {
   Restraint* pR=(Restraint*) pBCLDs[i];
   Pt_Object* pNode=(Pt_Object*) pR->pObj;
   // only apply the restrain if it a global dof restraint
   // else it local and need transformation
   if (pNode->OutSys==0)
   {
	   for (j=0;j<6;j++)
	   {
	     if (pR->REST[j]==TRUE)
	     {
            pNode->dof[j]=-1;  
	     }
	   }
   }
  }
}

}

void ME_Object::LocalRes(int neq,Vec<int> &Steer,Vec<double> &KMA)
{
int i,j,k;
C3dVector K;
C3dMatrix r;
CoordSys* pS;
Vec<int> V(2*3);
Mat KM(6,6);
Mat t(6,6);
Mat tt(6,6);
Mat Kmt;
Mat tKmt;
int idof;
for (k=0;k<iBCLDs;k++)
{
  if (pBCLDs[k]->iObjType==322)
  {
   Restraint* pR=(Restraint*) pBCLDs[k];
   Pt_Object* pNode=(Pt_Object*) pR->pObj;
   if (pNode->OutSys!=0)
   {
     pS=this->GetSys(pNode->OutSys);
     if (pS!=NULL)
     {
       //This composes the stiffness tranformation matrix
       r=GetNodalSys(pNode);
       r.Transpose();
       Mat mr(3,3);
       *mr.mn(1,1)=r.m_00; *mr.mn(1,2)=r.m_01; *mr.mn(1,3)=r.m_02;
       *mr.mn(2,1)=r.m_10; *mr.mn(2,2)=r.m_11; *mr.mn(2,3)=r.m_12;
       *mr.mn(3,1)=r.m_20; *mr.mn(3,2)=r.m_21; *mr.mn(3,3)=r.m_22;
       for (i=1;i<4;i++)
       {
          for (j=1;j<4;j++)
          {
             *t.mn(i,j) = *mr.mn(i,j);
             *t.mn(i+3,j+3) = *mr.mn(i,j);
             *tt.mn(i,j) = *mr.mn(i,j);
             *tt.mn(i+3,j+3) = *mr.mn(i,j);
          }
       }
       tt.Transpose();
       //This composes the local stiffness matrix
       KM*=0;
	     if (pR->REST[0]==TRUE)  //X
       {
         *KM.mn(1,1)=1e15;*KM.mn(4,4)=1e15;*KM.mn(1,4)=-1e15;*KM.mn(4,1)=-1e15;
       }
       if (pR->REST[1]==TRUE)  //Y
       {
         *KM.mn(2,2)=1e15;*KM.mn(5,5)=1e15;*KM.mn(2,5)=-1e15;*KM.mn(5,2)=-1e15;
       }
       if (pR->REST[2]==TRUE)  //Z
       {
         *KM.mn(3,3)=1e15;*KM.mn(6,6)=1e15;*KM.mn(3,6)=-1e15;*KM.mn(6,3)=-1e15;
       }
       //This transforms the local stiffness to global coord sys
        Kmt.clear(); tKmt.clear();
        Kmt=KM*t;tKmt=tt*Kmt;
        //The steering vector
        *V.nn(1)=-1;*V.nn(2)=-1;*V.nn(3)=-1;
        *V.nn(4)=pNode->dof[0];*V.nn(5)=pNode->dof[1];*V.nn(6)=pNode->dof[2];
        //Put into global KM array
        formkv(KMA,tKmt,V,neq);
       // do sae for rotational restrains
       KM*=0;
	     if (pR->REST[3]==TRUE)  //X
       {
         *KM.mn(1,1)=1e15;*KM.mn(4,4)=1e15;*KM.mn(1,4)=-1e15;*KM.mn(4,1)=-1e15;
       }
       if (pR->REST[4]==TRUE)  //Y
       {
         *KM.mn(2,2)=1e15;*KM.mn(5,5)=1e15;*KM.mn(2,5)=-1e15;*KM.mn(5,2)=-1e15;
       }
       if (pR->REST[5]==TRUE)  //Z
       {
         *KM.mn(3,3)=1e15;*KM.mn(6,6)=1e15;*KM.mn(3,6)=-1e15;*KM.mn(6,3)=-1e15;
       }
       //This transforms the local stiffness to global coord sys
        Kmt.clear(); tKmt.clear();
        Kmt=KM*t;tKmt=tt*Kmt;
        //The steering vector
        *V.nn(1)=-1;*V.nn(2)=-1;*V.nn(3)=-1;
        *V.nn(4)=pNode->dof[3];*V.nn(5)=pNode->dof[4];*V.nn(6)=pNode->dof[5];
        //Put into global KM array
        formkv(KMA,tKmt,V,neq);
     }
   }
  }
}
}

//Count the number retraint element need before KM can be allocated
int ME_Object::LocalResCount()
{
int iCnt=0;
int k;
for (k=0;k<iBCLDs;k++)
{
  if (pBCLDs[k]->iObjType==322)
  {
   Restraint* pR=(Restraint*) pBCLDs[k];
   Pt_Object* pNode=(Pt_Object*) pR->pObj;
   if (pNode->OutSys!=0)
   {
     iCnt++;
     iCnt++;
   }
  }
}
return (iCnt);
}
//This version for iterative solver where no
//syatem matrix (KM) exists
void ME_Object::LocalResIter(Restraint* pR,Vec<int> &SteerT,Mat &KMAT,Vec<int> &SteerB,Mat &KMAB)
{
int i,j,k,cc;
C3dVector K;
C3dMatrix r;
CoordSys* pS;
Vec<int> V(2*3);

Mat KM(6,6);
Mat t(6,6);
Mat tt(6,6);
Mat Kmt;
Mat tKmt;
int idof;

Pt_Object* pNode=(Pt_Object*) pR->pObj;
if (pNode->OutSys!=0)
{
 pS=this->GetSys(pNode->OutSys);
 if (pS!=NULL)
 {
   //This composes the stiffness tranformation matrix
   r=GetNodalSys(pNode);
   r.Transpose();
   Mat mr(3,3);
   *mr.mn(1,1)=r.m_00; *mr.mn(1,2)=r.m_01; *mr.mn(1,3)=r.m_02;
   *mr.mn(2,1)=r.m_10; *mr.mn(2,2)=r.m_11; *mr.mn(2,3)=r.m_12;
   *mr.mn(3,1)=r.m_20; *mr.mn(3,2)=r.m_21; *mr.mn(3,3)=r.m_22;
   for (i=1;i<4;i++)
   {
      for (j=1;j<4;j++)
      {
         *t.mn(i,j) = *mr.mn(i,j);
         *t.mn(i+3,j+3) = *mr.mn(i,j);
         *tt.mn(i,j) = *mr.mn(i,j);
         *tt.mn(i+3,j+3) = *mr.mn(i,j);
      }
   }
   tt.Transpose();
   //This composes the local stiffness matrix
   KM*=0;
   if (pR->REST[0]==TRUE)  //X
   {
     *KM.mn(1,1)=1e13;*KM.mn(4,4)=1e13;*KM.mn(1,4)=-1e13;*KM.mn(4,1)=-1e13;
   }
   if (pR->REST[1]==TRUE)  //Y
   {
     *KM.mn(2,2)=1e13;*KM.mn(5,5)=1e13;*KM.mn(2,5)=-1e13;*KM.mn(5,2)=-1e13;
   }
   if (pR->REST[2]==TRUE)  //Z
   {
     *KM.mn(3,3)=1e13;*KM.mn(6,6)=1e13;*KM.mn(3,6)=-1e13;*KM.mn(6,3)=-1e13;
   }
   //This transforms the local stiffness to global coord sys
    Kmt.clear(); tKmt.clear();
    Kmt=KM*t;tKmt=tt*Kmt;
    //The steering vector
    *V.nn(1)=-1;*V.nn(2)=-1;*V.nn(3)=-1;
    *V.nn(4)=pNode->dof[0];*V.nn(5)=pNode->dof[1];*V.nn(6)=pNode->dof[2];
    SteerT=V;
    KMAT=tKmt;
    //Put into global KM array
    //formkv(KMA,tKmt,V,neq);
   // do sae for rotational restrains

    
   KM*=0;
   if (pR->REST[3]==TRUE)  //X
   {
     *KM.mn(1,1)=1e13;*KM.mn(4,4)=1e13;*KM.mn(1,4)=-1e13;*KM.mn(4,1)=-1e13;
   }
   if (pR->REST[4]==TRUE)  //Y
   {
     *KM.mn(2,2)=1e13;*KM.mn(5,5)=1e13;*KM.mn(2,5)=-1e13;*KM.mn(5,2)=-1e13;
   }
   if (pR->REST[5]==TRUE)  //Z
   {
     *KM.mn(3,3)=1e13;*KM.mn(6,6)=1e13;*KM.mn(3,6)=-1e13;*KM.mn(6,3)=-1e13;
   }
   //This transforms the local stiffness to global coord sys
    Kmt.clear(); tKmt.clear();
    Kmt=KM*t;tKmt=tt*Kmt;
    //The steering vector
    *V.nn(1)=-1;*V.nn(2)=-1;*V.nn(3)=-1;
    *V.nn(4)=pNode->dof[3];*V.nn(5)=pNode->dof[4];*V.nn(6)=pNode->dof[5];
    SteerB=V;
    KMAB=tKmt;

 }
}
}


int ME_Object::GenDofs()
{

int i,j;
int iDof=1;
int mdof;
FILE* pFile;
pFile = fopen("GENDOF_DIAG.txt","w");

fprintf(pFile,"%s%i\n","NO of Nodes ",iNdNo);
for(i=0;i<iNdNo;i++)
{
  mdof=MaxDof(pNodes[i]);
  for (j=0;j<mdof;j++)
  {
    if (pNodes[i]->dof[j]!=-1)
    {
      fprintf(pFile,"%s %i %s %i\n","Node ",pNodes[i]->G_label,"DOF",j);
      pNodes[i]->dof[j]=iDof;
      iDof++;
    }
  }
  for (j=mdof;j<6;j++)
  {
    pNodes[i]->dof[j]=0;
  }
}
fprintf(pFile,"%s%i\n","iDof ",iDof);
fclose(pFile);
return(iDof-1);
}


C3dMatrix ME_Object::GetNodalSys(Pt_Object* pN)
{
C3dMatrix mRC;
C3dMatrix mInvRC;
C3dVector pt;
C3dVector pO;
CoordSys* pC;
double ang;

  pC=GetSys(pN->OutSys);
  if (pC!=NULL)
  {
    mRC=pC->GetTMat();
    if (pC->CysType==2)
    {
      pt=pN->GetCoords();
      pO=pC->Get_Centroid();
      pt-=pO;
      mRC.Transpose();
      pt=mRC*pt;
      ang=atan2(pt.y,pt.x)*180/Pi;
      mInvRC.MakeUnit();
      mInvRC.Rotate(0,0,ang);
      mRC.Transpose();
      mRC*=mInvRC;
      mInvRC=mRC;
    }
    else if (pC->CysType==1)
    {
      mInvRC=mRC;
    }
    else
    {
      outtext1("Spherical coord sys not supported");
    }
  }
  else
  {
    outtext1("Coord sys not found");
  }

return (mInvRC);
}

BOOL ME_Object::DeleteNd(Pt_Object* pN)
{
BOOL b1=FALSE;
BOOL brc=FALSE;
int i;
b1 = NodeInResF(pN);
if (b1==FALSE)
{
  b1=NodeInEl(pN);
}
if (b1==FALSE)
{ 
  for(i=0;i<iNdNo;i++)
  {
    if (pNodes[i]==pN)
    {
      delete(pNodes[i]);
      pNodes[i]=pNodes[iNdNo-1];
      pNodes[iNdNo-1]=NULL;
      iNdNo--;
	    brc=TRUE;
      break;
    }
  }
}
return (brc);
}


BOOL ME_Object::DeleteEl(E_Object* pEl)
{
int i;
BOOL brc=FALSE;
for(i=0;i<iElNo;i++)
{
  if (pElems[i]==pEl)
  {
   //need to check no body loads 
   //on element
   delete(pElems[i]);
   pElems[i]=pElems[iElNo-1];
   pElems[iElNo-1]=NULL;
   iElNo--;
   brc=TRUE;
   break;
  }
}
return (brc);
}

BOOL ME_Object::DeleteCys(CoordSys* pS)
{
int i;
BOOL brc=FALSE;
for(i=0;i<iCYS;i++)
{
  if ((pSys[i]==pS) && (pS!=NULL))
  {
   //need to check no body loads 
   //on element
   delete(pSys[i]);
   pSys[i]=pSys[iCYS-1];
   pSys[iCYS-1]=NULL;
   iCYS--;
   brc=TRUE;
   break;
  }
}
return (brc);
}

BOOL ME_Object::DeleteBC(BCLD* pS)
{
int i;
BOOL brc=FALSE;
  for(i=0;i<iBCLDs;i++)
  {
    if (pBCLDs[i]==pS)
    {
     delete(pBCLDs[i]);
     pBCLDs[i]=pBCLDs[iBCLDs-1];
     pBCLDs[iBCLDs-1]=NULL;
     iBCLDs--;
     brc=TRUE;
     break;
    }
  }
return (brc);
}

BOOL ME_Object::NodeInResF(Pt_Object* pN)
{
int i;
BOOL brc=FALSE;
for(i=0;i<iBCLDs;i++)
{
  if (pBCLDs[i]->NodeIn(pN)==TRUE)
  {
	brc=TRUE;
    break;
  }
}
return (brc);
}

Pt_Object* ME_Object::GetClosestNode(Pt_Object* pIn,double* dMinDist)
{
int i;
double dDist=1e36;
*dMinDist=1e36;

Pt_Object* pRet=NULL;
C3dVector pT;
C3dVector pS=pIn->GetCoords();
for (i=0;i<iNdNo;i++)
{
   
   pT=pNodes[i]->GetCoords();
   pT-=pS;
   dDist=pT.Mag();
   if (pNodes[i]!=pIn)
   {
     if (dDist<*dMinDist)
     {
        *dMinDist=dDist;
        pRet=pNodes[i];
     }
   }
}
return (pRet);
}

void ME_Object::CNodesMerge(double dTol)
{
Pt_Object* pWith=NULL;
double dDist;
int i;
int j;

for (i=0;i<iNdNo;i++)
{
   if (pNodes[i]->G_Colour==160)
   {
     if ((pNodes[i]->G_label==1059) || (pNodes[i]->G_label==1079))
     {
       dDist=dDist;
     }

     pWith=GetClosestNode(pNodes[i], &dDist);
     if ((dDist<dTol) && (pWith!=NULL))
     {
       for (j=0;j<iElNo;j++)
       {
         pElems[j]->RepNodeInEl(pNodes[i], pWith);
       }
      // DeleteNd(pNodes[i]);
     }
   }
}
}





ObjList* ME_Object::CNodesMerge2(double dTol,BOOL UpLab,BOOL bDel)
{
Pt_Object* pWith=NULL;
ObjList* DelNode=new ObjList();
double dDist;
int i;
int j;

for (i=0;i<iNdNo;i++)
{
     pWith=GetClosestNode(pNodes[i], &dDist);
     if ((dDist<dTol) && (pWith!=NULL))
     {
       if ((pWith->G_label>pNodes[i]->G_label) && (UpLab==TRUE))
       {
         for (j=0;j<iElNo;j++)
         {
           pElems[j]->RepNodeInEl(pNodes[i], pWith);
         }
         if (bDel==TRUE)
         DelNode->AddEx(pNodes[i]);
       }
       else
       {
         for (j=0;j<iElNo;j++)
         {
           pElems[j]->RepNodeInEl(pWith,pNodes[i]);
         }
         if (bDel==TRUE)
          DelNode->AddEx(pWith);
       }
         
     }
}
return (DelNode);
}

BOOL ME_Object::NodeInEl(Pt_Object* pN)
{
int i;
BOOL brc=FALSE;
for(i=0;i<iElNo;i++)
{
  if (pElems[i]->NodeInEl(pN)==TRUE)
  {
	brc=TRUE;
    break;
  }
}
return (brc);
}


int ME_Object::MaxDof(Pt_Object* pN)
{
int i;
int id=0;
int imax=0;
for(i=0;i<iElNo;i++)
{
  if (pElems[i]->NodeInEl(pN)==TRUE)
  {
    id=pElems[i]->noDof();
    if (id>imax)
	  {
	    imax=id;
    }
  }
}
return (imax);
}

void ME_Object::UpdatePropRef(PropTable* pT)
{
int i;
Property* p;
for (i=0;i<iElNo;i++)
{
  p=pT->GetItem(pElems[i]->PID);
  if (p!=NULL)
  {
    pElems[i]->SetProperty(p);
  }
  else
  {
     //sprintf_s(S1,"%s%i","Property not found PID",pElems[i]->PID);
     //outtext1(S1); 
  }
}
}

E_Object* ME_Object::AddEl2(int pVnode[200], int iLab,int iCol,int iType,int iPID,int iMat, int iNoNodes,int A,int B,int C,int iMatCys,double dMatAng)
{
  int iCnt;
  E_Object* cAddedEl;
  Pt_Object *pENodes[100];
  if (TempList!=NULL)
  {
    for (iCnt = 0; iCnt < iNoNodes; iCnt ++)
    {
      pENodes[iCnt] =(Pt_Object*) TempList->Objs[pVnode[iCnt]];
    }
  }
  else
  {
    for (iCnt = 0; iCnt < iNoNodes; iCnt ++)
    {
      pENodes[iCnt] = GetNode(pVnode[iCnt]);
    }
  }
  if (iLab>iElementLab)
  {
    iElementLab=iLab;
  }
  cAddedEl = AddEl(pENodes,iLab,iCol,iType,iPID,iMat,iNoNodes,A,B,C,FALSE,iMatCys,dMatAng); 
  return (cAddedEl);
}

void ME_Object::MaxLab()
{
int iCnt;
iNodeLab=0;
iElementLab=0;
iCYSLab=0;
for (iCnt = 0; iCnt < iNdNo; iCnt ++)
{
   if (pNodes[iCnt]->G_label>iNodeLab)
   {
     iNodeLab=pNodes[iCnt]->G_label;
   }
}
for (iCnt = 0; iCnt < iElNo; iCnt ++)
{
   if (pElems[iCnt]->G_label>iElementLab)
   {
     iElementLab=pElems[iCnt]->G_label;
   }
}
for (iCnt = 0; iCnt < iCYS; iCnt ++)
{
   if (pSys[iCnt]->G_label>iCYSLab)
   {
     iCYSLab=pSys[iCnt]->G_label;
   }
}
iNodeLab++;
iElementLab++;
iCYSLab++;
}

E_Object* ME_Object::AddEl(Pt_Object* pInVertex[200],int iLab,int iCol,int iType,int iPID,int iMat,int iNo,int iA,int iB,int iC,BOOL AddDisp,int iMatCys,double dMatAng)
{
E_Object* pERet=NULL;

if (iElNo<MAX_FESIZE)
{
if (iType == 115)
  {
  E_Object38 *pEL8 = new E_Object38();
  pEL8->Create(pInVertex, iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  if (pEL8->ChkNegJac()==TRUE)
  {
     pEL8->Reverse();
  }
  pElems[iElNo] = pEL8;
  pERet= pEL8;
  iElNo++;
  }
else if (iType == 112)
  {
  E_Object36 *pEL6 = new E_Object36();
  pEL6->Create(pInVertex, iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  if (pEL6->ChkNegJac()==TRUE)
  {
     pEL6->Reverse();
  }
  pElems[iElNo] = pEL6;
  pERet= pEL6;
  iElNo++;
  }
else if (iType == 94)
  {
  E_Object4 *pEL4 = new E_Object4();
  pEL4->Create(pInVertex, iLab,iCol,iType,iPID,iMat,iNo,iMatCys,dMatAng,this,NULL);
  pElems[iElNo] = pEL4;
  pERet= pEL4;
  iElNo++;
  }
else if (iType == 91)
  {
  E_Object3 *pEL3 = new E_Object3();
  pEL3->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,iMatCys,dMatAng,this,NULL);
  pElems[iElNo] = pEL3;
  pERet= pEL3;
  //AddElEdges(pElems[iElNo]);
  iElNo++;
  }
else if (iType == 161)
  {
  E_Object1 *pEL1 = new E_Object1();
  pEL1->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  pElems[iElNo] = pEL1;
  pERet= pEL1;
  iElNo++;
  }
else if ((iType == 136) || (iType == 137))
  {
  E_Object2 *pEL2 = new E_Object2();
  pEL2->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  pElems[iElNo] = pEL2;
  pERet= pEL2;
  iElNo++;
  }
else if (iType == 121) 
  {
  E_ObjectR2 *pEL2 = new E_ObjectR2();
  pEL2->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  pElems[iElNo] = pEL2;
  pERet= pEL2;
  iElNo++;
  }
else if ((iType == 21) || (iType == 22))
  {
  E_Object2B *pEL2 = new E_Object2B();
  pEL2->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  pEL2->SetSec(iA,iB,iC);
  pElems[iElNo] = pEL2;
  pERet= pEL2;
  iElNo++;
  }
else if (iType == 11)
  {
  E_Object2R *pEL2 = new E_Object2R();
  pEL2->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  pEL2->SetSec(iA,iB,iC);
  pElems[iElNo] = pEL2;
  pERet= pEL2;
  iElNo++;
  }
else if (iType == 111)
  {
  E_Object34 *pEL34 = new E_Object34();
  pEL34->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  if (pEL34->ChkNegJac()==FALSE)
  {
     pEL34->Reverse();
  }
  pElems[iElNo] = pEL34;
  pERet= pEL34;
  iElNo++;
  }
else if (iType == 122)
  {
  E_ObjectR *pELR = new E_ObjectR();
  pELR->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  pElems[iElNo] = pELR;
  pERet= pELR;
  iElNo++;
  }
else if (iType == 1000)
  {
  E_CellS* pELR = new E_CellS();
  pELR->Create(pInVertex,iLab,iCol,iType,iPID,iMat,iNo,this,NULL);
  pElems[iElNo] = pELR;
  pERet= pELR;
  iElNo++;
  }
}
else
{
  outtext1("FATAL ERROR Max ELMAX SIZE");
}



return (pERet);
}








Pt_Object* ME_Object::AddNode(C3dVector InPt, int iLab,int i2,int i3, int iC,int iDef,int iOut)
{

if (iNdNo<MAX_FESIZE)
{
  CoordSys* Cys;
  //int CysID;
  if (iDef!=0)
  {
    Cys=GetSys(iDef);
    if (Cys == NULL)
    {
      outtext1("Error Cys not found");
    }
    else
    {
      C3dMatrix A = Cys->mOrientMat;
      if (Cys->CysType==1)
      {
	      InPt = A*InPt;
        InPt+=Cys->Origin;
      }
      else if (Cys->CysType==2)
      {
        C3dVector pCart;
        pCart.x=InPt.x*cos(D2R*InPt.y);
        pCart.y=InPt.x*sin(D2R*InPt.y);
        pCart.z=InPt.z;
        pCart = A*pCart;
        pCart+=Cys->Origin;
        InPt=pCart;
      }
      else if (Cys->CysType==3)
      {
        C3dVector pCart;
        pCart.x=InPt.x*sin(D2R*InPt.y)*cos(D2R*InPt.z);
        pCart.y=InPt.x*sin(D2R*InPt.y)*sin(D2R*InPt.z);
        pCart.z=InPt.x*cos(D2R*InPt.y);
        pCart = A*pCart;
        pCart+=Cys->Origin;
        InPt=pCart;
      }
    }
  }
  pNodes[iNdNo] = new Pt_Object;
  pNodes[iNdNo]->Create(InPt,iLab,i2,i3,iC,iDef,iOut,this);
  if (TempList!=NULL)
  {
    TempList->Objs[iLab]=pNodes[iNdNo];
  }
  if (iLab>iNodeLab)
  {
    iNodeLab=iLab;
  }
  iNdNo++;
}
else
{
  outtext1("FATAL ERROR Max NDMAX SIZE");
}
return (pNodes[iNdNo-1]);
}

CoordSys* ME_Object::AddSys(C3dVector Orig,C3dMatrix RMat,int iRID,int iTp, int iLab, int iC)
{
if (iCYS<MAX_FESIZE)
{
  pSys[iCYS] = new CoordSys;
  pSys[iCYS]->Create(Orig,RMat,iRID,iTp,iLab,iC,this);
  if (iLab>iCYSLab)
  {
    iCYSLab=iLab;
  }
  iCYS++;
}
else
{
  outtext1("FATAL ERROR Max CYSMAX SIZE");
}

if (iRID>0)
{
  outtext1("ERROR ONLY ONE LEVEL OF COORDINATE SYSTEM SUPPORTED AT PRESENT");
  
}
return (pSys[iCYS-1]);
}




CoordSys* ME_Object::GetSys(int iLab)
{
int i;
CoordSys* oRet=NULL;
if ((iLab > 0) && (iCYS>0))
{
  for (i=0;i<iCYS;i++)
  {
    if (pSys[i]->G_label == iLab)
	{
       oRet = pSys[i];
	   break;
	}
  }
}
return (oRet);
}


Pt_Object* ME_Object::GetNode(int iRLab)
{
int iCnt;
Pt_Object *pRetPt = NULL;
if (TempList!=NULL)
{
  pRetPt = (Pt_Object*) TempList->Objs[iRLab];
}
else
{
for (iCnt = 0; iCnt < iNdNo;iCnt++)
   {
    if (pNodes[iCnt]->G_label == iRLab)  
	   {
	   pRetPt = pNodes[iCnt];
	   break;
	   } 
   }
}
return (pRetPt);
}

int ME_Object::GetNodeInd(Pt_Object* pThisNode)
{
int iCnt;

for (iCnt = 0; iCnt < iNdNo;iCnt++)
{
  if (pNodes[iCnt] == pThisNode)  
	{
	  break;
	} 
}
return (iCnt);
}

E_Object* ME_Object::GetElement(int iRLab)
{
int iCnt;
E_Object *pRetPt = NULL;

for (iCnt = 0; iCnt < iElNo;iCnt++)
   {
    if (pElems[iCnt]->G_label == iRLab)  
	   {
	   pRetPt = pElems[iCnt];
	   break;
	   } 
   }

return (pRetPt);
}
	

// contour map
//float Texture17[30][3] =
//{
//{0.00f, 0.00f, 1.00f},    //151 Blue
//{0.00f, 0.33f, 1.00f},    //152 Grey Blue
//{0.00f, 0.66f, 1.00f},    //153 Light Blue
//{0.00f, 1.00f, 1.00f},    //154 Cyan
//{1.00f, 0.33f, 1.00f},    //163 Light Magenta
//{1.00f, 0.00f, 1.00f},    //162 Magenta
//{0.00f, 0.33f, 0.00f},    //155 Dark Olive
//{0.00f, 0.66f, 0.00f},    //156 Dark Green
//{0.00f, 1.00f, 0.00f},    //157 Green
//{1.00f, 1.00f, 0.00f},    //158 Yellow
//{1.00f, 0.66f, 0.00f},    //159 Golden Orange
//{1.00f, 0.33f, 0.00f},    //160 Orange
//{1.00f, 0.00f, 0.00f}};   //161 Red

float Texture17[30][3] =
{
{0.00f, 0.00f, 1.00f},    //151 Blue
{0.00f, 0.33f, 1.00f},    //152 Grey Blue
{0.00f, 0.66f, 1.00f},    //153 Light Blue
{0.00f, 1.00f, 0.66f},    //154 Cyan
{0.00f, 1.00f, 0.33f},    //163 Light Magenta
{0.33f, 1.00f, 0.00f},    //162 Magenta
{0.66f, 1.00f, 0.00f},    //155 Dark Olive
{1.00f, 0.90f, 0.00f},    //156 Dark Green
{1.00f, 0.50f, 0.00f},    //157 Green
{1.00f, 0.00f, 0.00f}};   //161 Red

void CreateTexture()
{
 //This bit does the results contour mapping
  // Set pixel stora    glTexCoord1f(TOrd[i]);ge mode 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  // Generate a texture name
  GLuint m_nTexName=NULL;
  glGenTextures(1, &m_nTexName);
// Create a texture object
  glBindTexture(GL_TEXTURE_1D, m_nTexName);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glTexImage1D(GL_TEXTURE_1D, 0, 3,10, 0, GL_RGB, 
               GL_FLOAT, Texture17);
}


void DrawColBar(int iDspFlgs,double dW,double dH)
{

int iNoCols=13;
float YOrd[30];
float TOrd[30];
float VOrd[30];
float fCw;
fCw=0.1*dW;
int i;
float dHS;
float dWInc;
float fSpan;
float fInc;
float tCol;
fSpan=cBarMax-cBarMin;
fInc=fSpan/iNoCols;

dHS=(float) 2*dH/(iNoCols+2);
dWInc=0.3*dW;
for (i=0;i<iNoCols+1;i++)
{
  YOrd[i]=-dH+dHS+dHS*i;
  TOrd[i]=fInc*i/fSpan;
  VOrd[i]=cBarMin+fInc*i;
}
glColor3fv(cols[124]);
glEnable(GL_TEXTURE_1D);
for (i=0;i<iNoCols;i++)
{
  tCol=(TOrd[i]+TOrd[i+1])/2;
  glBegin(GL_POLYGON);
    glTexCoord1f(tCol);
    glNormal3f(0,0,1);
    glVertex3f(dW-fCw-dWInc,YOrd[i],100);
    glTexCoord1f(tCol);
    glNormal3f(0,0,1);
    glVertex3f(dW-dWInc,YOrd[i],100);
    glTexCoord1f(tCol);
    glNormal3f(0,0,1);
    glVertex3f(dW-dWInc,YOrd[i+1],100);
    glTexCoord1f(tCol);
    glNormal3f(0,0,1);
    glVertex3f(dW-fCw-dWInc,YOrd[i+1],100);
  glEnd();
}
glDisable(GL_TEXTURE_1D);
char sLab[80];
for (i=0;i<iNoCols+1;i++)
{
       sprintf_s(sLab,"%f",VOrd[i]);
       OglString(iDspFlgs,dW-0.95*dWInc,YOrd[i],100,&sLab[0]);
}
}


void ME_Object::OglDraw(int iDspFlgs,double dS1,double dS2)
{
int i;

 

if (iElNo > 0)
{
  for (i = 0; i< iElNo; i++)
  {
    pElems[i]->OglDraw(iDspFlgs,dS1,dS2);	
  }
}
if ((iNdNo>0) && (bDrawN==TRUE))
{
  for (i=0;i<iNdNo;i++)
  {
	  pNodes[i]->OglDraw(iDspFlgs,dS1,dS2);
  }
}
if (iCYS>0) 
{
  for (i = 0; i < iCYS; i++)
  {
     pSys[i]->OglDraw(iDspFlgs,dS1,dS2);	
  }
}

}

void ME_Object::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
int i;
char sLab[80];
if (iElNo > 0)
{
  for (i = 0; i < iElNo; i++)
  {
    pElems[i]->OglDrawW(iDspFlgs,dS1,dS2);	
  }
}
if ((iNdNo>0) && (bDrawN==TRUE))
{
  for (i=0;i<iNdNo;i++)
  {
	  pNodes[i]->OglDrawW(iDspFlgs,dS1,dS2);
  }
}
if (iBCLDs>0)
{
  for (i=0;i<iBCLDs;i++)
  {
	  pBCLDs[i]->OglDrawW(iDspFlgs,dS1,dS2);
  }
}
if (iCYS>0) 
{
  for (i = 0; i < iCYS; i++)
  {
     pSys[i]->OglDraw(iDspFlgs,dS1,dS2);	
  }
}

C3dVector vCent;
vCent=Get_Centroid();
if (bDrawLab==TRUE)
{
  sprintf_s(sLab,"ME: %s",Name);
	OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,sLab);
}
}

void ME_Object::Draw(CDC* pDC,int iDrawmode)
{
int i;
if (iDrawmode != 2)
{
if ((iNdNo>0) && (bDrawN==TRUE))
  {
    for (i = 0; i < iNdNo; i++)
    {
      pNodes[i]->Draw(pDC,iDrawmode);
    }
  }
  if (iElNo > 0)
  {
    for (i = 0; i < iElNo; i++)
    {
    pElems[i]->Draw(pDC,iDrawmode);	
    }
  }
  if (iBCLDs > 0)
  {
    for (i = 0; i < iBCLDs; i++)
    {
    pBCLDs[i]->Draw(pDC,iDrawmode);	
    }
  }
  if (iCYS > 0)
  {
    for (i = 0; i < iCYS; i++)
    {
      pSys[i]->Draw(pDC,iDrawmode);	
    }
  }
}
}

void ME_Object::Colour(int iCol)
{
int i;
if (iNdNo > 0)
{
  for (i = 0; i < iNdNo; i++)
  {
    pNodes[i]->Colour(iCol);	
  }
}

if (iElNo > 0)
{
  for (i = 0; i < iElNo; i++)
  {
    pElems[i]->Colour(iCol);	
  }
}

if (iBCLDs > 0)
{
  for (i = 0; i < iBCLDs; i++)
  {
    pBCLDs[i]->Colour(iCol);	
  }
}
if (iCYS > 0)
{
for (i = 0; i < iCYS; i++)
  {
     pSys[i]->Colour(iCol);	
  }
}
}


void ME_Object::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
int i;
if (iNdNo > 0)
{
  for (i = 0; i < iNdNo; i++)
  {
    pNodes[i]->SetToScr(pModMat, pScrTran);
  }
}

if (iElNo > 0)
{
  for (i = 0; i < iElNo; i++)
  {
    pElems[i]->SetToScr(pModMat, pScrTran);
  }
}

if (iBCLDs > 0)
{
  for (i = 0; i < iBCLDs; i++)
  {
    pBCLDs[i]->SetToScr(pModMat, pScrTran);
  }
}
if (iCYS > 0)
{
for (i = 0; i < iCYS; i++)
  {
     pSys[i]->SetToScr(pModMat, pScrTran);	
  }
}
}


void ME_Object::Transform(C3dMatrix TMat)
{
int i;
TransMat=TMat;
if (iNdNo > 0)
{
  for (i = 0; i < iNdNo; i++)
  {
    pNodes[i]->Transform(TMat);
  }
}
if (iElNo > 0)
{
  for (i = 0; i < iElNo; i++)
  {
    pElems[i]->Transform(TMat);
  }
}
}


void ME_Object::Translate (C3dVector vIn)
{
int i;
if (iNdNo > 0)
{
  for (i = 0; i < iNdNo; i++)
  {
    pNodes[i]->Translate(vIn);
  }
}

if (iCYS > 0)
{
  for (i = 0; i < iCYS; i++)
  {
    pSys[i]->Translate(vIn);
  }
}
}

void ME_Object::HighLight(CDC* pDC)
{
int i;
if (iElNo > 0)
  {
  for (i = 0; i < iElNo; i++)
    {
    pElems[i]->Draw(pDC,4);	
    }
  }
}



C3dVector ME_Object::Get_Centroid()
{
C3dVector vRet;
vRet.Set(0,0,0);
int i;
if (iNdNo > 0)
{
  for (i = 0; i < iNdNo; i++)
  {
    vRet+=pNodes[i]->Get_Centroid();
  }
  vRet.x=vRet.x/iNdNo;
  vRet.y=vRet.y/iNdNo;
  vRet.z=vRet.z/iNdNo;
}
return (vRet);
}

G_ObjectD ME_Object::SelDist(CPoint InPT,Filter FIL)
{
G_Object* pSel=NULL;
G_Object* pMinSel=NULL;
G_ObjectD Ret;
int i;
double dDist = 1e36;
Ret.pObj=NULL;
Ret.Dist=dDist;
//search the node regardless of
//filter so we can  get a dist
//for the mesh
if (iNdNo > 0)
{
  for (i = 0; i < iNdNo; i++)
  {
    if (pNodes[i]->isSelectable()==1)
	{
	  Ret = pNodes[i]->SelDist(InPT,FIL);
      if (Ret.Dist < dDist)
	  {
	    pMinSel=Ret.pObj;
	    dDist=Ret.Dist;
	  }
	}
  }
}

if (FIL.isFilter(3))
{
if (iElNo > 0)
{
  for (i = 0; i < iElNo; i++)
  {
	if (pElems[i]->isSelectable()==1)
	{
	  Ret = pElems[i]->SelDist(InPT,FIL);
      if (Ret.Dist < dDist)
	  {
	    pMinSel=Ret.pObj;
	    dDist=Ret.Dist;
	  }
	}
  }
}
}

if (FIL.isFilter(321))
{
if (iBCLDs > 0)
{
  for (i = 0; i < iBCLDs; i++)
  {
	Ret = pBCLDs[i]->SelDist(InPT,FIL);
    if (Ret.Dist < dDist)
	{
	  pMinSel=Ret.pObj;
	  dDist=Ret.Dist;
	}
  }
}
}
if (FIL.isFilter(322))
{
if (iBCLDs > 0)
{
  for (i = 0; i < iBCLDs; i++)
  {
	Ret = pBCLDs[i]->SelDist(InPT,FIL);
  if (Ret.Dist <= dDist)
	{
	  pMinSel=Ret.pObj;
	  dDist=Ret.Dist;
	}
  }
}
}
if (FIL.isFilter(12))
{
if (iCYS > 0)
{
  for (i = 0; i < iCYS; i++)
  {
	Ret = pSys[i]->SelDist(InPT,FIL);
    if (Ret.Dist < dDist)
	{
	  pMinSel=Ret.pObj;
	  dDist=Ret.Dist;
	}
  }
}
}

if ((FIL.isFilter(3)==TRUE) 
|| (FIL.isFilter(1)==TRUE)
|| (FIL.isFilter(321)==TRUE)
|| (FIL.isFilter(322)==TRUE)
|| (FIL.isFilter(12)==TRUE))
{
  Ret.pObj=pMinSel;
  Ret.Dist=dDist;
}
else
{
  Ret.pObj=this;
  Ret.Dist=dDist;
}
return (Ret);
}


void ME_Object::S_Box(CPoint P1,CPoint P2,ObjList* pSel)
{
int i;
if (iNdNo > 0)
{
  for (i = 0; i < iNdNo; i++)
  {
    if (pNodes[i]->isSelectable()==1)
	{
	  pNodes[i]->S_Box(P1,P2,pSel);
	}
  }
}

if (iElNo > 0)
{
  for (i = 0; i < iElNo; i++)
  {
	if (pElems[i]->isSelectable()==1)
	{
	  pElems[i]->S_Box(P1,P2,pSel);
	}
  }
}

if (iCYS > 0)
{
  for (i = 0; i < iCYS; i++)
  {
	pSys[i]->S_Box(P1,P2,pSel);
  }
}

if (iBCLDs > 0)
{
  for (i = 0; i < iBCLDs; i++)
  {
	  pBCLDs[i]->S_Box(P1,P2,pSel);
  }
}

}





G_Object* ME_Object::GetObj(int iType,int iLab)
{
G_Object* pRet;
pRet = NULL;
if (iType == 1)
{
   pRet = GetNode(iLab);
}
else if (iType == 3)
{
   pRet = GetElement(iLab);
}
else if (iType == 12)
{
   pRet = GetSys(iLab);
}

return (pRet);
}
//************************************************************************
// Coeff Mat ,el stiff matrix,steering vec and no off equ
// Post : el assembled into bk
//************************************************************************
void ME_Object::formkv(Vec<double> &bk,Mat &KM,Vec<int> &g,int neq)
{
int i,j,ndof,icd,ival;
ndof = KM.m;
for (i=1;i<ndof+1;i++)
{
  if (*g.nn(i) > 0)
  {
    for (j=1;j<ndof+1;j++)
	  {
      if (*g.nn(j) > 0)
	    {
        icd = *g.nn(j) - *g.nn(i) + 1;
        if ((icd - 1) >= 0)
		    {
          ival = neq * (icd - 1) + *g.nn(i);
          *bk.nn(ival) = *bk.nn(ival) + *KM.mn(i, j);
        }
	    }
    }
  }
}
}


//************************************************************************
// Coeff Mat in upper baned vector form and no of equs
// Post : guass reduction
//************************************************************************
void ME_Object::banred(Vec<double> &bk,int neq)
{
int iw,i,j,il1,kbl,ij;
double sum;
int m,nkb,ni,nj;
sum=0;
iw = bk.n/neq-1;
for (i=2;i<neq+1;i++)
{
  il1=i-1;
  kbl=il1+iw+1;
  if (kbl-neq>0)
  {
    kbl=neq;
  }
  for(j=i;j<kbl+1;j++)
  {
    ij=(j-i)*neq+i;
    sum=bk.v[ij-1];
    nkb=j-iw;
    if(nkb<=0)
	  {
      nkb=1;
    }
    if (nkb-il1<=0)
	  {
      for (m=nkb;m<il1+1;m++)
	    {
        ni=(i-m)*neq+m;
        nj=(j-m)*neq+m;
        sum=sum-bk.v[ni-1]* bk.v[nj-1]/bk.v[m-1];
      }
    }
    bk.v[ij-1]=sum;
  }
}
}

//************************************************************************
// Reduced Coeff Matrix and load vector
// Post : load vector contain solution
//************************************************************************
void ME_Object::bacsub(Vec<double> &bk, Vec<double> &Loads)
{
double sum;
int nkb, k,i,jn,jj,i1,n,iw;
n = Loads.n;
iw = bk.n / n - 1;
*Loads.nn(1) = *Loads.nn(1) / (*bk.nn(1));
 for (i=2;i<n+1;i++)
 {
   sum = *Loads.nn(i);
   i1=i-1;
   nkb=i-iw;
   if (nkb<=0)
   {
     nkb=1;
   }
   for (k=nkb;k<i1+1;k++)
   {
     jn=(i-k)*n+k;
     sum=sum-*bk.nn(jn)**Loads.nn(k);
   }
   *Loads.nn(i)=sum/(*bk.nn(i));
 }
 for(jj=2;jj<n+1;jj++)
 {
  i=n-jj+1;
  sum=0;
  i1=i+1;
  nkb=i+iw;
  if ((nkb-n)>0)
  {
    nkb=n;
  }
  for (k=i1;k<nkb+1;k++)
  {
    jn=(k-i)*n+i;
    sum=sum+*bk.nn(jn)**Loads.nn(k);
  }
  *Loads.nn(i) = *Loads.nn(i) - sum / (*bk.nn(i));
 }
}



double ME_Object::GetDisp(int iDof,Vec<int> &Steer,Vec<double> &Disp)
{
double dret=0;
dret=*Disp.nn(iDof);
return(dret);
}


void ME_Object::Displacements(Vec<int> &Steer,Vec<double> &Disp)
{

ResSet* Res=new ResSet();
Res->ACODE=22;
Res->TCODE=1;
Res->TYPE=0;
Res->LC=1;
Res->WID=8;

Res->sName="DISPLACEMENT";
Res->iNoV=6;
Res->lab[0]="TX";
Res->lab[1]="TY";
Res->lab[2]="TZ";
Res->lab[3]="RX";
Res->lab[4]="RY";
Res->lab[5]="RZ";

int i;
FILE* pFile;
pFile = fopen("DispRes.txt","w");
fprintf(pFile,"%s\n","DISPLACEMENTS");
float X,Y,Z;

for(i=0;i<iNdNo;i++)
{
    Res6* pRes=new Res6;
    pRes->ID = pNodes[i]->G_label;
    pRes->v[0]=0;
    pRes->v[1]=0;
    pRes->v[2]=0;
    pRes->v[3]=0;
    pRes->v[4]=0;
    pRes->v[5]=0;
    

  X=0;Y=0;Z=0;
  if (pNodes[i]->dof[0]>0)
  {
	X=GetDisp(pNodes[i]->dof[0],Steer,Disp);
  pRes->v[0]=X;
  }
  if (pNodes[i]->dof[1]>0)
  {
	Y=GetDisp(pNodes[i]->dof[1],Steer,Disp);
  pRes->v[1]=Y;
  }
  if (pNodes[i]->dof[2]>0)
  {
	Z=GetDisp(pNodes[i]->dof[2],Steer,Disp);
  pRes->v[2]=Z;
  }

  if (pNodes[i]->dof[3]>0)
  {
	Z=GetDisp(pNodes[i]->dof[3],Steer,Disp);
  pRes->v[3]=Z;
  }
  if (pNodes[i]->dof[4]>0)
  {
	Z=GetDisp(pNodes[i]->dof[4],Steer,Disp);
  pRes->v[4]=Z;
  }
  if (pNodes[i]->dof[5]>0)
  {
	Z=GetDisp(pNodes[i]->dof[5],Steer,Disp);
  pRes->v[5]=Z;
  }
  Res->Add(pRes);
  fprintf(pFile,"%s%6i%s%6.4f%s%6.4f%s%6.4f\n","Node ",pNodes[i]->G_label," X: ",X," Y: ",Y," Z: ",Z);
}
fclose(pFile);
ResultsSets[iNoRes]=Res;
iNoRes++;
}

void ME_Object::StressesBeam(PropTable* PropsT,MatTable* MatT,Vec<int> &Steer,Vec<double> &Disp)
{
int i,j,k,iNoNodes;
double dof1;
ResSet* ResS=new ResSet();
ResS->ACODE=22;
ResS->TCODE=4;
ResS->TYPE=0;
ResS->LC=1;
ResS->WID=8;

ResS->sName="BEAM GRID PT REACTIONS";
ResS->iNoV=12;
ResS->lab[0]="END A FX";
ResS->lab[1]="END A FY";
ResS->lab[2]="END A FZ";
ResS->lab[3]="END A BX";
ResS->lab[4]="END A BY";
ResS->lab[5]="END A BZ";
ResS->lab[6]="END B FX";
ResS->lab[7]="END B FY";
ResS->lab[8]="END B FZ";
ResS->lab[9]="END B BX";
ResS->lab[10]="END B BY";
ResS->lab[11]="END B BZ";

Mat disp;
Mat KM;
Mat Res;
C3dMatrix TMAT;
C3dVector TRA;
C3dVector RRA;
C3dVector TRB;
C3dVector RRB;
for(i=0;i<iElNo;i++)
{
  iNoNodes=0;
  if (pElems[i]->iELType==21)
  {
    TMAT=pElems[i]->GetElSys();
    iNoNodes=2;
    disp.Create(12,1);
    for (j=0;j<iNoNodes;j++)
    {
      for (k=0;k<6;k++)
      {
        dof1=0;
        Pt_Object* pN=(Pt_Object*) pElems[i]->GetNode(j);
        if (pN->dof[k]>0)
        {
          dof1=GetDisp(pN->dof[k],Steer,Disp);
        }
        *disp.mn(6*j+(k+1),1)=dof1;
      }
    }
    KM=pElems[i]->GetStiffMat(PropsT,MatT);
    Res=KM*disp;
    TRA.x=*Res.mn(1,1);
    TRA.y=*Res.mn(2,1);
    TRA.z=*Res.mn(3,1);
    RRA.x=*Res.mn(4,1);
    RRA.y=*Res.mn(5,1);
    RRA.z=*Res.mn(6,1);

    TRB.x=*Res.mn(7,1);
    TRB.y=*Res.mn(8,1);
    TRB.z=*Res.mn(9,1);
    RRB.x=*Res.mn(10,1);
    RRB.y=*Res.mn(11,1);
    RRB.z=*Res.mn(12,1);

    TRA=TMAT*TRA;
    RRA=TMAT*RRA;
    TRB=TMAT*TRB;
    RRB=TMAT*RRB;

    KM.clear();
    Res.clear();
    disp.clear();
    //Need to transform to local
    Res12* pRes=new Res12;
    pRes->ID = pElems[i]->G_label;
    pRes->v[0]=TRA.x;
    pRes->v[1]=TRA.y;
    pRes->v[2]=TRA.z;
    pRes->v[3]=RRA.x;
    pRes->v[4]=RRA.y;
    pRes->v[5]=RRA.z;

    pRes->v[6]=TRB.x;
    pRes->v[7]=TRB.y;
    pRes->v[8]=TRB.z;
    pRes->v[9]=RRB.x;
    pRes->v[10]=RRB.y;
    pRes->v[11]=RRB.z;

    ResS->Add(pRes);
  }
}
ResultsSets[iNoRes]=ResS;
iNoRes++;
}

void ME_Object::Stresses2d(PropTable* PropsT,MatTable* MatT,Vec<int> &Steer,Vec<double> &Disp)
{

ResSet* ResS=new ResSet();
ResS->ACODE=22;
ResS->TCODE=4;
ResS->TYPE=0;
ResS->LC=1;
ResS->WID=8;

ResS->sName="2d EL STRESSES";
ResS->iNoV=7;
ResS->lab[0]="Stress X";
ResS->lab[1]="Stress Y";
ResS->lab[2]="Stress XY";
ResS->lab[3]="Max Prin";
ResS->lab[4]="Min Prin";
ResS->lab[5]="Max Shear";
ResS->lab[6]="Von Mises";
ResSet* ResSt=new ResSet();
ResSt->ACODE=22;
ResSt->TCODE=4;
ResSt->TYPE=0;
ResSt->LC=1;
ResSt->WID=8;

ResSt->sName="2d EL STRAINS";
ResSt->iNoV=6;
ResSt->lab[0]="Strain X";
ResSt->lab[1]="Strain Y";
ResSt->lab[2]="Strain XY";
ResSt->lab[3]="Max Prin";
ResSt->lab[4]="Min Prin";
ResSt->lab[5]="Max Shear";

int i;
int j;
int k;
Mat disp;
Mat disp3d;
double SX,SY,SXY;
int iNoNodes=0;
for(i=0;i<iElNo;i++)
{
  iNoNodes=0;
  if (pElems[i]->iELType==91)
  {
    iNoNodes=3;
    disp.Create(6,1);
    disp3d.Create(3,3);
  }
  else if (pElems[i]->iELType==94)
  {
    iNoNodes=4;
    disp.Create(8,1);
    disp3d.Create(3,4);
  }
  Mat dee;      //stress strain
  Mat bee;      //Strain displacement
  int nip=1;    //Centroid stresses only
  Mat coord;    //Nodal Coordinates
  Mat deriv;    //shape function derivatives
  Mat fun;      //shape function
  Mat Points;   //sample points
  Mat deriv2;
  Mat jac;
  Mat db;
  Mat Res;
  //Defualt values


  double det;
  double dof1;
  double dE=210e9;
  double dv=0.29;
  double dthk=0.001;
  int MID=-1;
  Property* pS=PropsT->GetItem(pElems[i]->PID);
  if (pS!=NULL)
  {
    MID=pS->GetDefMatID();
  }
  Material* pM=MatT->GetItem(MID);
//Get Shell thick ness

 if (((pElems[i]->iELType==91) || (pElems[i]->iELType==94)) && (pS!=NULL))
 {
   PSHELL* pSh = (PSHELL*) pS;
   dthk=pSh->dT;
 }

 if ((pM!=NULL) && (pM->iType = 1))
 {
   MAT1* pIsen = (MAT1*) pM;
   dE=pIsen->dE;
   dv=pIsen->dNU;
 }
  if (iNoNodes>0)
  {
    for (j=0;j<iNoNodes;j++)
    {  //Get the displacements
      for (k=0;k<3;k++)
      {
        dof1=0;
        Pt_Object* pN=(Pt_Object*) pElems[i]->GetNode(j);
        if (pN->dof[k]>0)
        {
	        dof1=GetDisp(pN->dof[k],Steer,Disp);
        }
        *disp3d.mn(k+1,j+1)=dof1;
      }
    }
    C3dMatrix M=pElems[i]->GetElSys();
    C3dVector v;
    int n;
    for (j=0;j<iNoNodes;j++)
    {
      v.x=*disp3d.mn(1,j+1);
      v.y=*disp3d.mn(2,j+1);
      v.z=*disp3d.mn(3,j+1);
      v=M.Mult(v);
      n=1+j*2;
      *disp.mn(n,1)=v.x;
      *disp.mn(n+1,1)=v.y;
    }
    disp3d.clear();
    //pE=pElems[i];
    //if (pE->ChkNegJac()==TRUE)
    //{
    //  pE=(E_Object*) pElems[i]->Copy(this);
    //  pE->Reverse();
    //}
    dee=pElems[i]->DeeMat(dE,dv,3);  
    coord=pElems[i]->getCoords3d();
    Mat NdDisp(iNoNodes,2);
    Points=pElems[i]->Sample(nip);
    det = 0;
    fun=pElems[i]->ShapeFun(Points, 1);
    deriv=pElems[i]->ShapeDer(Points, 1);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee=pElems[i]->bmat(coord, deriv2,3,2);
    db=bee*disp;
    SX=*db.mn(1,1);
    SY=*db.mn(2,1);
    SXY=*db.mn(3,1);
    Res6* pResS=new Res6;
    pResS->ID = pElems[i]->G_label;
    pResS->v[0]=SX;
    pResS->v[1]=SY;
    pResS->v[2]=SXY;
    pResS->v[3]=0;
    pResS->v[4]=0;
    pResS->v[5]=0;
    ResSt->Add(pResS);

    Res=dee*db;
    SX=*Res.mn(1,1);
    SY=*Res.mn(2,1);
    SXY=*Res.mn(3,1);
    Res7* pRes=new Res7;
    pRes->ID = pElems[i]->G_label;
    pRes->v[0]=SX;
    pRes->v[1]=SY;
    pRes->v[2]=SXY;
    double cS;
    double Mag;
    cS=(SX+SY)*0.5;
    Mag= pow((SX-cS)*(SX-cS)+(SXY*SXY),0.5);
    double p1,p2;
    p2=cS+Mag;
    p1=cS-Mag;
    pRes->v[3]=cS+Mag;
    pRes->v[4]=cS-Mag;
    pRes->v[5]=Mag;
    pRes->v[6]=pow(p1*p1-p1*p2+p2*p2,0.5);
    ResS->Add(pRes);
  }
}
ResultsSets[iNoRes]=ResSt;
iNoRes++;
ResultsSets[iNoRes]=ResS;
iNoRes++;
}


void ME_Object::CalcPrinStress(double XX,double YY,double ZZ,
                               double XY,double YZ,double XZ,
                               double &P1,double &P2,double &P3)
{
double a,b,c,d;
a=1;
b=-1*(XX+YY+ZZ);
c=XX*YY+YY*ZZ+XX*ZZ-XY*XY-YZ*YZ-XZ*XZ;
d=-1*(XX*YY*ZZ+2*XY*YZ*XZ-XY*XY*ZZ-YZ*YZ*XX-XZ*XZ*YY);
//Use the equation from above to get your cubic equation and combine all constant terms possible to
//give you a reduced equation we will use a, b, c and d to denote the coefficients of this equation.
double x,y,z;

x = ((3*c/a) - (b*b/(a*a)))/3.0;
y = ((2*b*b*b/(a*a*a)) - (9*b*c/(a*a)) + (27*d/a))/27.0;
z = y*y/4 + x*x*x/27;
// 
double i, j, k, m, n, p;
i = pow((y*y/4 - z),0.5);
j = -pow(i,(1.0/3.0));
k = acos(-(y/(2*i)));
m = cos(k/3);
n = pow(3,0.5)*sin(k/3);
p = b/(3*a);
// 
double Eig1, Eig2, Eig3;
Eig1 = -(2*j*m + p);
Eig2 = -(-j *(m + n) + p);
Eig3 = -(-j*(m - n) + p);
P1=Eig1;
if (Eig2>P1) P1=Eig2;
if (Eig3>P1) P1=Eig3;
P3=Eig1;
if (Eig2<P3) P3=Eig2;
if (Eig3<P3) P3=Eig3;
P2=Eig1;
if ((Eig1<P1) && (Eig1>P3)) P2=Eig1;
if ((Eig2<P1) && (Eig2>P3)) P2=Eig2;
if ((Eig3<P1) && (Eig3>P3)) P2=Eig3;
}


void ME_Object::Stresses3d(PropTable* PropsT,MatTable* MatT,Vec<int> &Steer,Vec<double> &Disp)
{

ResSet* ResS=new ResSet();
ResS->ACODE=22;
ResS->TCODE=4;
ResS->TYPE=0;
ResS->LC=1;
ResS->WID=8;

ResS->sName="3d GLOBAL STRESSES";
ResS->iNoV=11;
ResS->lab[0]="Stress GX";
ResS->lab[1]="Stress GY";
ResS->lab[2]="Stress GZ";
ResS->lab[3]="Stress GXY";
ResS->lab[4]="Stress GYZ";
ResS->lab[5]="Stress GXZ";
ResS->lab[6]="Stress Max Prin";
ResS->lab[7]="Stress Mid Prin";
ResS->lab[8]="Stress Min Prin1";
ResS->lab[9]="Stress Max Shear";
ResS->lab[10]="Stress Von Mises";
ResSet* ResSt=new ResSet();
ResSt->ACODE=22;
ResSt->TCODE=4;
ResSt->TYPE=0;
ResSt->LC=1;
ResSt->WID=8;

ResSt->sName="3d GLOBAL STRAINS";
ResSt->iNoV=6;
ResSt->lab[0]="Strain GX";
ResSt->lab[1]="Strain GY";
ResSt->lab[2]="Strain GZ";
ResSt->lab[3]="Strain GXY";
ResSt->lab[4]="Strain GYZ";
ResSt->lab[5]="Strain GXZ";

int i;
int j;
int k;
Mat disp;

double SX,SY,SZ;
double SXY,SYZ,SXZ;
int iNoNodes=0;
for(i=0;i<iElNo;i++)
{
  iNoNodes=0;
  if (pElems[i]->iELType==115)
  {
    iNoNodes=8;
    disp.Create(24,1);
    
  }
  else if (pElems[i]->iELType==112)
  {
    iNoNodes=6;
    disp.Create(18,1);
  }
  else if (pElems[i]->iELType==111)
  {
    iNoNodes=4;
    disp.Create(12,1);
  }
  
  Mat dee;      //stress strain
  Mat bee;      //Strain displacement
  int nip=1;    //Centroid stresses only
  Mat coord;    //Nodal Coordinates
  Mat deriv;    //shape function derivatives
  Mat fun;      //shape function
  Mat Points;   //sample points
  Mat deriv2;
  Mat jac;
  Mat db;
  Mat Res;
  //Defualt values
  double det;
  double dof1;
  double dE=210e9;
  double dv=0.29;
  char S1[80];
  double dthk=0.001;
  int MID=-1;
  Property* pS=PropsT->GetItem(pElems[i]->PID);
  if (pS!=NULL)
  {
    MID=pS->GetDefMatID();
  }
  Material* pM=MatT->GetItem(MID);
  if ((pM!=NULL) && (pM->iType = 1))
  {
    MAT1* pIsen = (MAT1*) pM;
    dE=pIsen->dE;
    dv=pIsen->dNU;
  }
  if (iNoNodes>0)
  {
    for (j=0;j<iNoNodes;j++)
    {  //Get the displacements
      for (k=0;k<3;k++)
      {
        dof1=0;
        Pt_Object* pN=(Pt_Object*) pElems[i]->GetNode(j);
        if (pN->dof[k]>0)
	        dof1=GetDisp(pN->dof[k],Steer,Disp);
        int n;
        n=j*3+k+1;
        *disp.mn(n,1)=dof1;
      }
    }
    dee=pElems[i]->DeeMat(dE,dv,6);  
    coord=pElems[i]->getCoords3d();
    Points=pElems[i]->Sample(nip);
    det = 0;
    fun=pElems[i]->ShapeFun(Points, 1);
    deriv=pElems[i]->ShapeDer(Points, 1);
    jac = deriv*coord;
    jac=jac.InvertJac(det);
    deriv2 = jac*deriv;
    bee=pElems[i]->bmat(coord, deriv2,6,3);
    db=bee*disp;
    SX=*db.mn(1,1);
    SY=*db.mn(2,1);
    SZ=*db.mn(3,1);
    SXY=*db.mn(4,1);
    SYZ=*db.mn(5,1);
    SXZ=*db.mn(6,1);
    Res6* pResS=new Res6;
    pResS->ID = pElems[i]->G_label;
    pResS->v[0]=SX;
    pResS->v[1]=SY;
    pResS->v[2]=SZ;
    pResS->v[3]=SXY;
    pResS->v[4]=SYZ;
    pResS->v[5]=SXZ;
    ResSt->Add(pResS);

    Res=dee*db;
    SX=*Res.mn(1,1);
    SY=*Res.mn(2,1);
    SZ=*Res.mn(3,1);
    SXY=*Res.mn(4,1);
    SYZ=*Res.mn(5,1);
    SXZ=*Res.mn(6,1);
    double p1,p2,p3;

    CalcPrinStress(SX,SY,SZ,SXY,SYZ,SXZ,p1,p2,p3);
    Res11* pRes=new Res11;
    pRes->ID = pElems[i]->G_label;
    pRes->v[0]=SX;
    pRes->v[1]=SY;
    pRes->v[2]=SZ;
    pRes->v[3]=SXY;
    pRes->v[4]=SYZ;
    pRes->v[5]=SXZ;
    pRes->v[6]=p1;
    pRes->v[7]=p2;
    pRes->v[8]=p3;
    pRes->v[9]=0.5*(p1-p3);
    pRes->v[10]=pow(0.5*((p1-p2)*(p1-p2)+(p2-p3)*(p2-p3)+(p1-p3)*(p1-p3)),0.5);
    ResS->Add(pRes);
  }
}
ResultsSets[iNoRes]=ResSt;
iNoRes++;
ResultsSets[iNoRes]=ResS;
iNoRes++;
}

void ME_Object::AddOEFRes(int Vals[],int iCnt)
{
int i;

ResultsSets[iNoRes]=new ResSet();
ResultsSets[iNoRes]->ACODE=Vals[0];
ResultsSets[iNoRes]->TCODE=Vals[1];
ResultsSets[iNoRes]->TYPE=Vals[2];
ResultsSets[iNoRes]->LC=Vals[3];
ResultsSets[iNoRes]->WID=Vals[4];
CString sEL;
BOOL isGood=FALSE;

if (Vals[2]==33)
{
  isGood=TRUE;
  sEL="FORCE CQUAD4";
}
else if (Vals[2]==74)
{
  isGood=TRUE;
  sEL="FORCE CTRIA3";
}
else if (Vals[2]==2)
{
  sEL="FORCE CBEAM (not read)";
  ResultsSets[iNoRes]->sName=sEL;
}
else if (Vals[2]==102)
{
  sEL="FORCE CBUSH";
}
if ((iCnt>5) && (isGood))
{
  ResultsSets[iNoRes]->sName=sEL;
  ResultsSets[iNoRes]->iNoV=8;
  ResultsSets[iNoRes]->lab[0]="FX";
  ResultsSets[iNoRes]->lab[1]="FY";
  ResultsSets[iNoRes]->lab[2]="FXY";
  ResultsSets[iNoRes]->lab[3]="MX";
  ResultsSets[iNoRes]->lab[4]="MY";
  ResultsSets[iNoRes]->lab[5]="MXY";
  ResultsSets[iNoRes]->lab[6]="TX";
  ResultsSets[iNoRes]->lab[7]="TY";
  for (i=5;i<iCnt;i+=9)
  {
    Res8* pRes=new Res8;
    pRes->ID=Vals[i] / 10;
    pRes->v[0]=*(float*) &Vals[i+1];
    pRes->v[1]=*(float*) &Vals[i+2];
    pRes->v[2]=*(float*) &Vals[i+3];
    pRes->v[3]=*(float*) &Vals[i+4];
    pRes->v[4]=*(float*) &Vals[i+5];
    pRes->v[5]=*(float*) &Vals[i+6];
    pRes->v[6]=*(float*) &Vals[i+7];
    pRes->v[7]=*(float*) &Vals[i+8];
    ResultsSets[iNoRes]->Add(pRes);
  }
}

if ((iCnt>5) && (ResultsSets[iNoRes]->TYPE==102))
{
  ResultsSets[iNoRes]->sName=sEL;
  ResultsSets[iNoRes]->iNoV=6;
  ResultsSets[iNoRes]->lab[0]="FX";
  ResultsSets[iNoRes]->lab[1]="FY";
  ResultsSets[iNoRes]->lab[2]="FZ";
  ResultsSets[iNoRes]->lab[3]="MX";
  ResultsSets[iNoRes]->lab[4]="MY";
  ResultsSets[iNoRes]->lab[5]="MZ";

  for (i=5;i<iCnt;i+=7)
  {
    Res6* pRes=new Res6;
    pRes->ID=Vals[i] / 10;
    pRes->v[0]=*(float*) &Vals[i+1];
    pRes->v[1]=*(float*) &Vals[i+2];
    pRes->v[2]=*(float*) &Vals[i+3];
    pRes->v[3]=*(float*) &Vals[i+4];
    pRes->v[4]=*(float*) &Vals[i+5];
    pRes->v[5]=*(float*) &Vals[i+6];
    ResultsSets[iNoRes]->Add(pRes);
  }

}
iNoRes++;
}

void ME_Object::AddOUGRes(int Vals[],int iCnt)
{
int i;

ResultsSets[iNoRes]=new ResSet();
ResultsSets[iNoRes]->ACODE=Vals[0];
ResultsSets[iNoRes]->TCODE=Vals[1];
ResultsSets[iNoRes]->TYPE=Vals[2];
ResultsSets[iNoRes]->LC=Vals[3];
ResultsSets[iNoRes]->WID=Vals[4];
if (iCnt>5)
{
  ResultsSets[iNoRes]->sName="DISPLACEMENT";
  ResultsSets[iNoRes]->iNoV=6;
  ResultsSets[iNoRes]->lab[0]="TX";
  ResultsSets[iNoRes]->lab[1]="TY";
  ResultsSets[iNoRes]->lab[2]="TZ";
  ResultsSets[iNoRes]->lab[3]="RX";
  ResultsSets[iNoRes]->lab[4]="RY";
  ResultsSets[iNoRes]->lab[5]="RZ";
  for (i=5;i<iCnt;i+=8)
  {
    Res6* pRes=new Res6;
    pRes->ID=Vals[i] / 10;
    pRes->v[0]=*(float*) &Vals[i+2];
    pRes->v[1]=*(float*) &Vals[i+3];
    pRes->v[2]=*(float*) &Vals[i+4];
    pRes->v[3]=*(float*) &Vals[i+5];
    pRes->v[4]=*(float*) &Vals[i+6];
    pRes->v[5]=*(float*) &Vals[i+7];
    ResultsSets[iNoRes]->Add(pRes);
  }

}

iNoRes++;
}

void ME_Object::ListResSets()
{
int i;
char buff[80];
outtext1("Results Listing:");
for (i=0;i<iNoRes;i++)
{ 
	  sprintf(buff, "%3i%s%8i%s%s",i," : LC ",ResultsSets[i]->LC," ",ResultsSets[i]->sName );
    outtext1(buff);
}
}

void ME_Object::ListResSet()
{
int i;
char buff[80];
outtext1("Current Results Listing:");
if ((iCurResSet<iNoRes) && (iCurResSet>=0))
{ 
	  sprintf(buff, "%3i%s%8i%s%s",iCurResSet," : LC ",ResultsSets[iCurResSet]->LC," ",ResultsSets[iCurResSet]->sName );
    outtext1(buff);
    outtext1("Variable:-");
    for (i=0;i<ResultsSets[iCurResSet]->iNoV;i++)
    {
       sprintf(buff, "%3i%s%s",i," : ",ResultsSets[iCurResSet]->lab[i]);
       outtext1(buff);
    }
    sprintf(buff, "%s%s","Current variable : ",ResultsSets[iCurResSet]->lab[iResVal]);
    outtext1(buff);
    sprintf(buff, "%s%f","Max Value : ",fMaxRes);
    outtext1(buff);
    sprintf(buff, "%s%f","Min Value : ",fMinRes);
    outtext1(buff);
}
else
{
  outtext1("No Results Selected:");
}
}


void ME_Object::SetCurrentResSet(int iRS,int iRV)
{
if ((iRS<iNoRes) && (iRV>=0))
{
  iCurResSet=iRS;
  iResVal=0;
  if ((iRV<ResultsSets[iCurResSet]->iNoV) && (iRV>=0))
  {
    iResVal=iRV;
    PostElResScalar(ResultsSets[iCurResSet],iResVal,fMaxRes,fMinRes);

  }
  else
  {
    outtext1("Invalid Variable ID");
    PostElResScalar(ResultsSets[iCurResSet],iResVal,fMaxRes,fMinRes);
  }
}
else
{
  outtext1("Invalid LC ID");
}

}

void ME_Object::WriteResHead(int iDspFlgs,float dW,float dH)
{
char sLab[80];
if ((iCurResSet>-1) && (CResSet!=NULL))
{
   sprintf_s(sLab,"%s",ResultsSets[iCurResSet]->sName);
   OglString(iDspFlgs,-dW+0.02*dW,dH-0.1*dH,100,&sLab[0]);
   sprintf_s(sLab,"%s %i","Load Case :", ResultsSets[iCurResSet]->LC);
   OglString(iDspFlgs,-dW+0.02*dW,dH-0.2*dH,100,&sLab[0]);
   sprintf_s(sLab,"%s %s","Variable  :", ResultsSets[iCurResSet]->lab[iResVal]);
   OglString(iDspFlgs,-dW+0.02*dW,dH-0.3*dH,100,&sLab[0]);
   sprintf_s(sLab,"%s %f","Max Value :", ResultsSets[iCurResSet]->fMaxV);
   OglString(iDspFlgs,-dW+0.02*dW,dH-0.4*dH,100,&sLab[0]);
   sprintf_s(sLab,"%s %f","Min Value :", ResultsSets[iCurResSet]->fMinV);
   OglString(iDspFlgs,-dW+0.02*dW,dH-0.5*dH,100,&sLab[0]);
}
}

void ME_Object::SetDefScale(double dS)
{
  dScale=dS;
}


void ME_Object::SetCurrentResSetDef(int iRS,int iRV)
{
if ((iRS<iNoRes) && (iRS>-1) && (iRV>=-1))
{
  iCurResSetDef=iRS;
  iResValDef=-1;
  if ((iRV<ResultsSets[iCurResSetDef]->iNoV) && (iRV>=-1))
  {
    iResValDef=iRV;
    PostElResDef(ResultsSets[iCurResSetDef],iResValDef,fMaxRes,fMinRes);
  }
}
else
{
  outtext1("Invalid LC ID");
}

}
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
//  A(indi,indj)=pNodes[i]->G_label;
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
//
//----------------------------------------------------------------------------
//    E L E M E N T   O B J E C T
//----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC( WG_Def, CObject )

WG_Def::WG_Def()
{
isMeshed=FALSE;
Name="NULL";
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
int i=0;
iObjType = 500;
G_label = -1;
G_Colour = 2;
iTCnt=0;
iPartCnt=0;
vStart.Set(0,0,0);
iWG=0;
dWall=0;
dSize=0.005;
iWG2=0;
dWall2=0;
bQ1=FALSE;
bQ2=FALSE;
iTarnsitionPos=-1;
}


void WG_Def:: Create(int iLab,CString sN,G_Object* Parrent)

{
Drawn = 0;
Name=sN;
Selectable  = 1; 
Visable  = 1;
iObjType = 500;
G_label = iLab;
G_Colour = 2;
iTCnt=0;
iPartCnt=0;
isMeshed=FALSE;
iWG=0;
dWall=0;
dSize=0.005;
pParent=Parrent;
iWG2=0;
dWall2=0;
bQ1=FALSE;
bQ2=FALSE;
iTarnsitionPos=-1;
}

void WG_Def::Serialize(CArchive& ar)
{
	int i;
	int iType;
	if (ar.IsStoring())
	{		// TODO: add storing code here
    G_Object::Serialize(ar); 
	  ar<<Name;
	  ar<<dSize;
    ar<<iTCnt;
	  ar<<isMeshed;
	  ar<<vStart.x;
	  ar<<vStart.y;
	  ar<<vStart.z;
    ar<<iWG;
    ar<<dWall;
    ar<<iWG2;
    ar<<dWall2;
    ar<<bQ1;
    ar<<bQ2;
    ar<<iTarnsitionPos;
	  for (i=0;i<iTCnt;i++)
	  {
		  ar<<Text[i];
	  }
    ar<<iPartCnt;
	  for (i=0;i<iPartCnt;i++)
	  {
		  ar<<WGParts[i]->iObjType;
      WGParts[i]->Serialize(ar); 
	  }
	}
	else
	{
    G_Object::Serialize(ar);
	  ar>>Name;
	  ar>>dSize;
    ar>>iTCnt;
	  ar>>isMeshed;
	  ar>>vStart.x;
	  ar>>vStart.y;
	  ar>>vStart.z;
    ar>>iWG;
    ar>>dWall;
    ar>>iWG2;
    ar>>dWall2;
    ar>>bQ1;
    ar>>bQ2;
    ar>>iTarnsitionPos;
	  for (i=0;i<iTCnt;i++)
	  {
		  ar>>Text[i];
	  }
      ar>>iPartCnt;
	  for (i=0;i<iPartCnt;i++)
	  {
	      ar>>iType;
		  switch(iType)
		  {
		    case 600:
            WGParts[i] = new WG_Part;
			      break;
        case 601:
            WGParts[i] = new WG_Elbow;    
			      break;
       case 602:
            WGParts[i] = new WG_Brk;    
			      break;
		   case 603:
            WGParts[i] = new Sweep;    
			      break;
		   case 604:
            WGParts[i] = new SweepB;    
			      break;
       case 605:
            WGParts[i] = new WG_Brk_Int;    
			      break;
       case 606:
            WGParts[i] = new SweepF;    
			      break;
       case 607:
            WGParts[i] = new SweepFB;    
			      break;
		  }
      WGParts[i]->Serialize(ar); 
		  WGParts[i]->pParent=this;
	  }
	}

	
}

void WG_Def::UpdatePropRef(PropTable* pT)
{
ME_Object* pM;
int i;
	  for (i=0;i<iPartCnt;i++)
	  {
      if ((WGParts[i]->iObjType==600) ||
          (WGParts[i]->iObjType==601) ||
          (WGParts[i]->iObjType==602) ||
          (WGParts[i]->iObjType==605))
		   {
            WG_Part* pPart =(WG_Part*)  WGParts[i];
            pM=pPart->GetMesh();
            if (pM!=NULL)
            {
              pM->UpdatePropRef(pT);
            }
       }
       else if  ((WGParts[i]->iObjType==603) ||
                 (WGParts[i]->iObjType==604))
       {
            Sweep* pSweep= (Sweep*) WGParts[i]; 
            pM=pSweep->GetMesh();
            if (pM!=NULL)
            {
              pM->UpdatePropRef(pT);
            }
		   }
    }
}

// Draw Object line
void WG_Def::Draw(CDC* pDC,int iDrawmode)
{
int i;
for (i=0;i<iPartCnt;i++)
{
  WGParts[i]->Draw(pDC,iDrawmode);
}
}



void WG_Def::OglDraw(int iDspFlgs,double dS1,double dS2)
{
int j=0;
if ((iDspFlgs & DSP_ASSEM)>0)
{
  Selectable=1;
  for (j=0;j<iPartCnt;j++)
  {
    WGParts[j]->OglDraw(iDspFlgs,dS1,dS2);
  }
}
else
{
  Selectable=0;
}
}

void WG_Def::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
int j=0;
if ((iDspFlgs & DSP_ASSEM)>0)
{
  Selectable=1;
  for (j=0;j<iPartCnt;j++)
  {
    Selectable=1;
    WGParts[j]->OglDrawW(iDspFlgs, dS1, dS2);
  }
}
else
{
  Selectable=0;
  for (j=0;j<iPartCnt;j++)
  {
    WGParts[j]->Selectable=0;
  }
}
}
void WG_Def::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
int i;
for (i=0;i<iPartCnt;i++)
{
  WGParts[i]->SetToScr(pModMat,pScrTran);
}

}


C3dVector WG_Def::Get_Centroid()
{
int i;
C3dVector vT;
vT.Set(0,0,0);
if (iPartCnt>0) 
{
  for (i=0;i<iPartCnt;i++)
  {
    vT+=WGParts[i]->Get_Centroid();
  }
  vT/=iPartCnt;
}
return (vT);
}

//*********************************************
//String extration procedures for build WG Proc
//*********************************************

int ExtractRad(CString inS,double* dRad)
{
int iRet=1;
int i1;
int i2;

CString sR;
CString sVec;

i1=inS.Find("Bend Rad=");
sVec=inS.Right(inS.GetLength()-i1-9);
i2=sVec.Find("(Angle");
sVec=sVec.Left(i2);
*dRad=atof(sVec)/1000;
return (iRet);
}

int ExtractTwistLen(CString inS,double* dTw)
{
int iRet=1;
int i1;
int i2;

CString sR;
CString sVec;

i1=inS.Find("MM");
if (i1<0)
{
  i1=inS.Find("mm");
}
sVec=inS.Left(i1);
i2=sVec.ReverseFind('_');
sVec=sVec.Right(sVec.GetLength()-i2-1);
*dTw=atof(sVec)/1000;
return (iRet);
}

int ExtractTwistAng(CString inS,double* dA)
{
int iRet=1;
int i1;
int i2;

CString sR;
CString sVec;

i1=inS.Find("DEG");
if (i1<0)
{
  i1=inS.Find("deg");
}
sVec=inS.Left(i1);
i2=sVec.ReverseFind('_');
sVec=sVec.Right(sVec.GetLength()-i2-1);
*dA=atof(sVec);
return (iRet);
}


int ExtractWG(CString inS,int* iW,double* dW,int* iW2,double* dW2,BOOL* bQ1,BOOL* bQ2)
{
int iRet=1;
int i1;
int i2;

CString sR;
CString sVec;
CString sWG2;
CString sWG1;

sWG1=inS;
i1=inS.Find(",");
if (i1>-1)
{
sWG1=sWG1.Left(i1);
}
  i1=sWG1.Find("_WR");
  sVec=sWG1.Right(sWG1.GetLength()-i1-3);
  i2=sVec.Find("_");
  sR=sVec.Left(i2);
  *iW=atoi(sVec);
  sVec=sVec.Right(sVec.GetLength()-i2);
  i2=sVec.Find("MM");
  sR=sVec.Left(i2);
  i1=sR.Find("_Q_");
  if (i1>-1)
  {
    *bQ1=TRUE;
    sR=sR.Right(sR.GetLength()-3);
  }
  else
  {
    sR=sR.Right(sR.GetLength()-1);
  }
  *dW=atof(sR);
i1=inS.Find(",");
if (i1>-1)
{
  sWG2=inS.Right(inS.GetLength()-i1-1);
  i1=sWG2.Find("_WR");
  sVec=sWG2.Right(sWG2.GetLength()-i1-3);
  i2=sVec.Find("_");
  sR=sVec.Left(i2);
  *iW2=atoi(sVec);
  sVec=sVec.Right(sVec.GetLength()-i2);
  i2=sVec.Find("MM");
  sR=sVec.Left(i2);
  i1=sR.Find("_Q_");
  if (i1>-1)
  {
    *bQ2=TRUE;
    sR=sR.Right(sR.GetLength()-3);
  }
  else
  {
    sR=sR.Right(sR.GetLength()-1);
  }
  *dW2=atof(sR);
}


return (iRet);
}

int ExtractPt(CString inS,C3dVector* inVec)
{
int iRet=1;
int i1;
double dx;
double dy;
double dz;
CString sX;
CString sY;
CString sVec;
i1=inS.Find(":");
sVec=inS.Right(inS.GetLength()-i1-1);
i1=sVec.Find(",");
sX=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
i1=sVec.Find(",");
sY=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
i1=sVec.Find(".");
sVec=sVec.Left(i1+3);
dx=atof(sX);
dy=atof(sY);
dz=atof(sVec);
inVec->Set(dx/1000,dy/1000,dz/1000);
return (iRet);
}



int ExtractPtS(CString inS,C3dVector* inVec)
{
int iRet=1;
int i1;
double dx;
double dy;
double dz;
CString sX;
CString sY;
CString sVec;
i1=inS.Find("(");
sVec=inS.Right(inS.GetLength()-i1-1);
i1=sVec.Find(",");
sX=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
i1=sVec.Find(",");
sY=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
i1=sVec.Find(")");
sVec=sVec.Left(i1);
dx=atof(sX);
dy=atof(sY);
dz=atof(sVec);
inVec->Set(dx/1000,dy/1000,dz/1000);
return (iRet);
}


int ExtractName(CString inS,CString* sName)
{
int iRet=1;
CString S;
int i1;

S = inS.Right(inS.GetLength()-57);
i1=S.Find(" ");
*sName=S.Left(i1);
return (iRet);
}





int ExtractOPt(CString inS,C3dVector* inVec)

{
int iRet=1;
int i1;
double dx;
double dy;
double dz;
CString sX;
CString sY;
CString sVec;

sVec=inS;
i1=sVec.Find(",");
sX=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
i1=sVec.Find(",");
sY=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
dx=atof(sX);
dy=atof(sY);
dz=atof(sVec);
inVec->Set(dx/1000,dy/1000,dz/1000);
return (iRet);
}

int ExtractOOPt(CString inS,C3dVector* inVec)

{
int iRet=1;
int i1;
double dx;
double dy;
double dz;
CString sX;
CString sY;
CString sVec;
i1=inS.Find(":");
sVec=inS.Right(inS.GetLength()-i1-1);
i1=sVec.Find(",");
sX=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
i1=sVec.Find(",");
sY=sVec.Left(i1);
sVec=sVec.Right(sVec.GetLength()-i1-1);
dx=atof(sX);
dy=atof(sY);
dz=atof(sVec);
inVec->Set(dx/1000,dy/1000,dz/1000);
return (iRet);
}


//*********************************************
//END String extraction procedure s
//*********************************************


void WG_Def::BuildFromDef(int* iErr)
{
outtext1("First pass build of waveguide");
outtext1("Parts Found :-");
CString s1;
CString s11;
C3dVector vPt;
C3dVector vPt2;
C3dVector vPt3;
CString sName;
double dRad;
int i;
int k=0;
int irc;
BOOL bStart=TRUE;
BOOL bFirst=TRUE;
for (i=0;i<iTCnt;i++)
{
	s1=Text[i].Left(32);
	s11=Text[i].Left(5);
	if (s11=="Type ")
	{
    irc=ExtractWG(Text[i],&iWG,&dWall,&iWG2,&dWall2,&bQ1,&bQ2);
	}
  if (s11=="Start")
	{
    irc=ExtractPtS(Text[i],&vStart);
	}
  if ((s1) == "FlangeStandard                  ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     if (bStart==FALSE)
	   {
	     irc=ExtractPt(Text[i+1],&vPt);
       vPt+=vStart;
     }
     WG_Part* Fl = new WG_Part;
	   Fl->Create(k,sName,vPt,this);
	   AddPart  (Fl);
	   bStart=FALSE;
     k++;
  }
  if ((s1) == "FlangeSpecial                   ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     if (bStart==FALSE)
	   {
	     irc=ExtractPt(Text[i+1],&vPt);
       vPt+=vStart;
     }
     WG_Part* Fl = new WG_Part;
	   Fl->Create(k,sName,vPt,this);
	   AddPart  (Fl);
	   bStart=FALSE;
     k++;
  }
  if ((s1) == "ElbowHParts                     ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     WG_Elbow* Fl = new WG_Elbow;
	   Fl->Create(k,sName,vPt,TRUE,this);
	   AddPart  (Fl);
     k++;
  }
  if ((s1) == "ThermalFin                      ") 
  {
	   outtext1(s1);
     irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
     WG_Part* Fl = new WG_Part;
	   Fl->Create(k,"NULL",vPt,this);
	   AddPart  (Fl);
  }
  if ((s1) == "CollarFlexible                  ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     WG_Part* Fl = new WG_Part;
	   Fl->Create(k,sName,vPt,this);
     Fl->bFlipZ=bFirst;
	   AddPart  (Fl);
     k++;
     if (bFirst==TRUE)
      {bFirst=FALSE;}
     else
      {bFirst=TRUE;}
  }
  if ((s1) == "Transition                      ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     WG_Part* Fl = new WG_Part;
	   Fl->Create(k,sName,vPt,this);
	   iTarnsitionPos=AddPart  (Fl);
     k++;
     //Need to chect to see if part needs zfilp
     if (iWG<iWG2)
     {Fl->bFlipZ=TRUE;}
     else if (dWall<dWall2) 
     {Fl->bFlipZ=TRUE;} 
     else if (bQ1==TRUE)
     {Fl->bFlipZ=TRUE;}
  }
  if ((s1) == "CollarTransition                ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     WG_Part* Fl = new WG_Part;
	   Fl->Create(k,sName,vPt,this);
	   iTarnsitionPos=AddPart  (Fl);
     k++;
     if (iWG<iWG2)
     {Fl->bFlipZ=TRUE;}
     else if (dWall<dWall2) 
     {Fl->bFlipZ=TRUE;} 
     else if (bQ1==TRUE)
     {Fl->bFlipZ=TRUE;}
  }
  //if ((s1) == "BracketTie                      ") 
  //{
	 //  outtext1(s1);
	 //  irc=ExtractPt(Text[i],&vPt);
  //   vPt+=vStart;
	 //  irc=ExtractName(Text[i],&sName);
  //   WG_Part* Fl = new WG_Part;
	 //  Fl->Create(k,sName,vPt,this);
	 //  AddPart  (Fl);
  //   k++;
  //}  
  if ((s1 == "BracketIntegrated               ") 
   || (s1 == "BracketTie                      "))
  {
	  outtext1(s1);
	  irc=ExtractPt(Text[i],&vPt);
	  vPt+=vStart;
	  irc=ExtractName(Text[i],&sName);
	  irc=ExtractOPt(Text[i+1],&vPt2);
	  vPt2+=vStart;
	  irc=ExtractOOPt(Text[i+1],&vPt3);
	  vPt3+=vStart;
    WG_Brk_Int* Bl = new WG_Brk_Int;
	  Bl->Create(k,sName,vPt,vPt2,vPt3,this);
	  AddPart(Bl);
    k++;
  }  
  if (s1 == "BracketFlange                   ")
  {
	  outtext1(s1);
	  irc=ExtractPt(Text[i],&vPt);
	  vPt+=vStart;
	  irc=ExtractName(Text[i],&sName);
	  irc=ExtractOPt(Text[i+1],&vPt2);
	  vPt2+=vStart;
	  irc=ExtractOOPt(Text[i+1],&vPt3);
	  vPt3+=vStart;
    if (bStart==FALSE)
	   {
	     irc=ExtractPt(Text[i+2],&vPt);
       vPt+=vStart;
     }
    WG_Brk_Int* Bl = new WG_Brk_Int;
	  Bl->Create(k,sName,vPt,vPt2,vPt3,this);
	  AddPart(Bl);
    bStart=FALSE;
    k++;
  }  
  if ((s1) == "FlexibleStraight                ") 
  {
	   outtext1(s1);
     SweepF* Bl = new SweepF;
	   Bl->PreCreate(k,"FLEXI",0);
	   AddPart(Bl);
     k++;
  }
  if ((s1 == "TwistVariable                   ") || 
      (s1 == "TwistFixed                      "))
  {
	   outtext1(s1);
     double dA;
     double dT;
     C3dVector VDir;
     C3dVector vP2;
     VDir=GetLastInsPos();
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     WG_Part* Fl = new WG_Part;
	   Fl->Create(k,"NULL",vPt,this);
	   AddPart  (Fl);
     k++;
     
     irc=ExtractTwistLen(sName,&dT);
     irc=ExtractTwistAng(sName,&dA);
     Sweep* Bl = new Sweep;
	   Bl->PreCreate(k,sName,dA);
	   AddPart(Bl);
     k++;
     vP2=vPt;
     vPt-=VDir;
     vPt.Normalize();
     vPt*=dT;
     vPt+=vP2;
     Fl = new WG_Part;
	   Fl->Create(k,"NULL",vPt,this);
	   AddPart  (Fl);
     k++;
  }
  if ((s1) == "ElbowEParts                     ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
     vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
     WG_Elbow* Fl = new WG_Elbow;
	   Fl->Create(k,sName,vPt,FALSE,this);
	   AddPart  (Fl);
     k++;
  }
	else if ((s1 == "ElbowHFixed                     ") ||
		       (s1 == "ElbowHVariable                  "))
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
	   vPt+=vStart;
	   irc=ExtractRad(Text[i],&dRad);
     SweepB* El = new SweepB;
	   El->PreCreate(k,"NULL",vPt,dRad,1,0);
	   AddPart(El);
     k++;
  }
  else if (s1 == "ElbowHFlexible                  ")
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
	   vPt+=vStart;
	   irc=ExtractRad(Text[i],&dRad);
     SweepFB* El = new SweepFB;
	   El->PreCreate(k,"NULL",vPt,dRad,1,0);
	   AddPart(El);
     k++;
  }
	else if ((s1 == "ElbowEFixed                     ")  ||
		       (s1 == "ElbowEVariable                  "))
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
	   vPt+=vStart;
	   irc=ExtractRad(Text[i],&dRad);
     SweepB* El = new SweepB;
	   El->PreCreate(k,"NULL",vPt,dRad,0,0);
	   AddPart(El);
     k++;
  }
  	else if (s1 == "ElbowEFlexible                  ")
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
	   vPt+=vStart;
	   irc=ExtractRad(Text[i],&dRad);
     SweepFB* El = new SweepFB;
	   El->PreCreate(k,"NULL",vPt,dRad,0,0);
	   AddPart(El);
     k++;
  }
  else if ((s1) == "ElbowEParts                     ") 
  {
	   outtext1(s1);
	   irc=ExtractPt(Text[i],&vPt);
	   vPt+=vStart;
	   irc=ExtractName(Text[i],&sName);
	   irc=ExtractOPt(Text[i+1],&vPt2);
	   vPt2+=vStart;
     WG_Brk* Bl = new WG_Brk;
	   Bl->Create(k,sName,vPt,vPt2,this);
	   AddPart(Bl);
     k++;
  }
  else if ((s1) == "BracketClamp                    ") 
  {
	  outtext1(s1);
	  irc=ExtractPt(Text[i],&vPt);
	  vPt+=vStart;
	  irc=ExtractName(Text[i],&sName);
	  irc=ExtractOPt(Text[i+1],&vPt2);
	  vPt2+=vStart;
    WG_Brk* Bl = new WG_Brk;
	  Bl->Create(k,sName,vPt,vPt2,this);
	  AddPart(Bl);
    k++;
  }
	else if ((s1) == "Straight Rectangular Waveguide  ") 
  {
	   outtext1(s1);
	   if (WGParts[iPartCnt-1]->iObjType!=603)
	   {
        Sweep* Bl = new Sweep;
	      Bl->PreCreate(k,"TEST",0);
	      AddPart(Bl);
	   }
	   else
	   {
        Sweep* Bl = (Sweep*) WGParts[iPartCnt-1];
		    Bl->Twist=90;
	   }
     k++;
  }
}
SetFlexMarkers();
}

void WG_Def::SetFlexMarkers()
{
int i;
Sweep* pS;
bool bFirst=TRUE;
for (i=0;i<iPartCnt-1;i++)
{
  if ((WGParts[i]->iObjType == 606) || 
      (WGParts[i]->iObjType == 607) )
  {
     pS=(Sweep*) WGParts[i];
     if (bFirst==TRUE)
     {
        pS->isStart=TRUE;
        bFirst=FALSE;
        if ((WGParts[i+1]->iObjType == 606) || 
            (WGParts[i+1]->iObjType == 607) )
        {
           pS->isEnd=FALSE;
        }
        else
        {
           pS->isEnd=TRUE;
           bFirst=TRUE;
        }
     }
     else
     {
        pS->isStart=FALSE;
     }
  }
  else
  {

  }
}
}

C3dMatrix WG_Def::GetOrientMat()
{
C3dVector VN;
C3dVector VD;
C3dVector vUX;
C3dMatrix mUp;
int iS=0;
int isHB=0;
double dT=0;
int i;
//******************************************************************
// This bit find the up vector from the first bend
// Need now to acount for a twist before
// and should also condifer elbow parts
//******************************************************************

for (i=0;i<iPartCnt;i++)
{
  if ((WGParts[i]->iObjType == 604) || 
      (WGParts[i]->iObjType == 607) )
  {
    SweepB* SN = (SweepB*) WGParts[i];
    VN=SN->GetNVec();
    VD=SN->GetSVec();
    isHB=SN->isHBend;
    iS=i;
    break;
  }
  else if (WGParts[i]->iObjType == 601)
  {
    WG_Elbow* SN = (WG_Elbow*) WGParts[i];
    VN=WGParts[i+1]->GetDir(0);
    VD=WGParts[i-1]->GetDir(0);
    VN=VN.Cross(VD);
    isHB=SN->isHBend;
    iS=i;
    break;
  }
}

//Check for sweeps with twists which change the orientaion 
for (i=0;i<iS;i++)
{
  if ((WGParts[i]->iObjType == 603) || (WGParts[i]->iObjType == 606))
  {
    Sweep* SN = (Sweep*) WGParts[i];
    dT+=SN->Twist;
  }
}

vUX=VN.Cross(VD);
if (isHB)
{
  mUp.SetColVec(1,VN);
  mUp.SetColVec(2,-vUX);
  mUp.SetColVec(3,VD);
}
else
{
  mUp.SetColVec(1,vUX);
  mUp.SetColVec(2,VN);
  mUp.SetColVec(3,VD);
}
//Now corect for the twist dT
C3dMatrix mR;
mR.Rotate(0,0,-dT);
mUp*=mR;
return (mUp);
}

int WG_Def::Generate(SecTable* pSecs,int iM,int iSW,int iSH,double dS,double dSA)
{
int irc=0;
C3dMatrix mUp;
dSize=dS;
dASize=dSA;
outtext1("Second pass build of waveguide");
outtext1("Generating Sweeps");
C3dVector A;
C3dVector B;
NLine* L1;
NLine* L2;

Section* Sec = NULL;
SecProp* SecP = NULL;
int iGenWG;
double dGenWall;
double dH;
int i;
int iQM;
try
{
iGenWG=iWG;
dGenWall=dWall;  
iQM=iM;
if (bQ1)
 {iQM=iM+10;}
SecP = pSecs->GetSecP(iGenWG,dGenWall,iQM,iSW,iSH);

if (SecP!=NULL)
{
  dW=SecP->W;
  dH=SecP->H;
}

for (i=0;i<iPartCnt;i++)
{
  if (iTarnsitionPos==i)
  {
    iGenWG=iWG2;
    dGenWall=dWall2;
    iQM=iM;
    if (bQ2)
    {iQM=iM+10;}
    SecP = pSecs->GetSecP(iGenWG,dGenWall,iQM,iSW,iSH);
    if (SecP!=NULL)
    {
      dW=SecP->W;
      dH=SecP->H;
    }
  }
  else
  {

  }
  if (WGParts[i]->iObjType == 603)
  {
    Sec=pSecs->GetSec(iGenWG,dGenWall,iQM,iSW,iSH,FALSE);
	  A=WGParts[i-1]->GetInPt();
	  B=WGParts[i+1]->GetInPt();
    NLine* Ln = new NLine;
    Ln->Create(A,B,1,NULL);
	  Sweep* Sw =  (Sweep*) WGParts[i];
    Sw->Create(-1,Ln,Sec,this);
  }
  else  if (WGParts[i]->iObjType == 606)
  {
    Sec=pSecs->GetSec(iGenWG,dGenWall,iQM,iSW,iSH,TRUE);
    SecP = pSecs->GetSecPF(iGenWG);
    if (SecP!=NULL)
    {
      Sec->FilletCrns(SecP->dR/1000); 
    }
    else
    {
      Sec->FilletCrns(0.003);
    }
	  A=WGParts[i-1]->GetInPt();
	  B=WGParts[i+1]->GetInPt();
    NLine* Ln = new NLine;
    Ln->Create(A,B,1,NULL);
	  SweepF* Sw =  (SweepF*) WGParts[i];
    Sw->Create(-1,Ln,Sec,this);
  }
}
iQM=iM;
if (bQ1)
{iQM=iM+10;}
SecP = pSecs->GetSecP(iWG,dWall,iQM,iSW,iSH);
iGenWG=iWG;
dGenWall=dWall;
if (SecP!=NULL)
{
  dW=SecP->W;
  dH=SecP->H;
}
for (i=0;i<iPartCnt;i++)
{
  if (iTarnsitionPos==i)
  {
    iQM=iM;
    if (bQ2)
    {iQM=iM+10;}
    iGenWG=iWG2;
    dGenWall=dWall2;
    SecP = pSecs->GetSecP(iGenWG,dGenWall,iQM,iSW,iSH);
    if (SecP!=NULL)
    {
      dW=SecP->W;
      dH=SecP->H;
    }
  }
  if (WGParts[i]->iObjType == 604)
  {
	  if (((WGParts[i-1]->iObjType==603) || (WGParts[i-1]->iObjType==606)) && ((WGParts[i+1]->iObjType==603) || (WGParts[i+1]->iObjType==606)))
	  {
      Sec=pSecs->GetSec(iGenWG,dGenWall,iQM,iSW,iSH,FALSE);
      SweepB* SB = (SweepB*) WGParts[i];
      Sweep* S1= (Sweep*) WGParts[i-1];
      Sweep* S2= (Sweep*) WGParts[i+1];
	    L1 = (NLine*) S1->pPath;
	    L2 = (NLine*) S2->pPath;
	    NCircle* C = NFillet(L1,L2,SB->dRad);
	    SweepB* SwB =  (SweepB*) WGParts[i];
      SwB->Create(-1,C,Sec,this);
	  }
  }
  if (WGParts[i]->iObjType == 607)
  {
	  if (((WGParts[i-1]->iObjType==603) || (WGParts[i-1]->iObjType==606)) && ((WGParts[i+1]->iObjType==603) || (WGParts[i+1]->iObjType==606)))
	  {
      Sec=pSecs->GetSec(iGenWG,dGenWall,iQM,iSW,iSH,TRUE);
      SecP = pSecs->GetSecPF(iGenWG);
      if (SecP!=NULL)
      {
        Sec->FilletCrns(SecP->dR/1000); 
      }
      else
      {
        Sec->FilletCrns(0.003);
      }
      SweepB* SB = (SweepB*) WGParts[i];
      Sweep* S1= (Sweep*) WGParts[i-1];
      Sweep* S2= (Sweep*) WGParts[i+1];
	    L1 = (NLine*) S1->pPath;
	    L2 = (NLine*) S2->pPath;
	    NCircle* C = NFillet(L1,L2,SB->dRad);
	    SweepB* SwB =  (SweepB*) WGParts[i];
      SwB->Create(-1,C,Sec,this);
	  }
  }
}


//******************************************************************
mUp=GetOrientMat();
SweepB* SwB;
Sweep* SwS;
for (i=0;i<iPartCnt;i++)
{
  if (WGParts[i]->iObjType == 604)
  {
    SwB = (SweepB*) WGParts[i];
    SwB->Generate(mUp,dASize); 
    mUp =SwB->GetLastYMap();
  }
  if (WGParts[i]->iObjType == 607)
  {
    SwB = (SweepB*) WGParts[i];
    SwB->Generate(mUp,dASize); 
    mUp =SwB->GetLastYMap();
  }
  if (WGParts[i]->iObjType == 603)
  {
    SwS = (Sweep*) WGParts[i];
    SwS->Generate(mUp,dSize); 
    mUp =SwS->GetLastYMap();
  }
  if (WGParts[i]->iObjType == 606)
  {
    SweepF* SwF = (SweepF*) WGParts[i];
    SecP = pSecs->GetSecPF(iGenWG);
    if (SecP!=NULL)
    {
      SwF->Generate(mUp,dSize,SecP->dLFR/1000); 
    }
    else
    {
      SwF->Generate(mUp,dSize,0.001); 
    }
    mUp =SwS->GetLastYMap();
  }
}
}
catch(...)
{
 irc=3;
 outtext1("WG Generation FAILED");
}
return (irc);
}

//The initial orientation of the parts is taken
//for the sweep vector at on side of the part
//note this assume each part has a sweep either
//side of it
C3dMatrix WG_Def::GetTMat(int iPindex)
{
C3dMatrix mrc;
Sweep* Sw;
mrc.MakeUnit();
double dL;
if ((WGParts[iPindex]->iObjType==600) ||
    (WGParts[iPindex]->iObjType==601) ||
    (WGParts[iPindex]->iObjType==602) ||
    (WGParts[iPindex]->iObjType==605))
{

  if (iPindex<iPartCnt-1)
  {
    Sw = (Sweep*) WGParts[iPindex+1];
    dL=Sw->pPath->getLen();
    if (dL>0.000001)
    {
      mrc= Sw->GetFirstYMap();
    }
    else
    {
      Sw = (Sweep*) WGParts[iPindex-1];
      mrc= Sw->GetLastYMap();
      mrc.ReverseZ();
    }
  }
  else
  {
    Sw = (Sweep*) WGParts[iPindex-1];
    mrc= Sw->GetLastYMap();
    mrc.ReverseZ();
  }
}
return (mrc);
}

C3dVector WG_Def::GetVA(int iPindex)
{
C3dVector vrc;
C3dMatrix mrc;
vrc.Set(0,0,0);
Sweep* Sw;
if (iPindex>0)
{
  if ((WGParts[iPindex-1]->iObjType == 603) ||
     (WGParts[iPindex-1]->iObjType == 604))
  {
    Sw = (Sweep*) WGParts[iPindex-1];
    mrc= Sw->GetLastYMap();
    vrc=mrc.GetColVec(3);
  }
}
return (vrc);
}

C3dVector WG_Def::GetVB(int iPindex)
{
C3dVector vrc;
C3dMatrix mrc;
Sweep* Sw;
vrc.Set(0,0,0);
if (iPindex<iPartCnt-1)
{
  if ((WGParts[iPindex+1]->iObjType == 603) ||
     (WGParts[iPindex+1]->iObjType == 604))
  {
    Sw = (Sweep*) WGParts[iPindex+1];
    mrc= Sw->GetFirstYMap();
    vrc=mrc.GetColVec(3);
  }
}
return (vrc);
}

PBARL* WG_Def::CreatePBARL(PropTable* pT,CString sT,double W,double H, double dTHK,double dNSM,int iM,int PIDB)
{
Property* pP=NULL;
PBARL* pBar=NULL;
int iPID;
pP=pT->GetItem(PIDB);
if ((pP != NULL) && (pP->iType==5))
{
  pBar=(PBARL*) pP;
}
else
{
  pBar = new PBARL();
  if (pT->Exists(PIDB)==TRUE)
  {
    iPID=pT->NextID()+10000;
  }
  else
  {
    iPID=PIDB;
  }
  pBar->sSecType = "BOX     ";
  pBar->sTitle="Waveguide Beam";
  pBar->iMID=iM;
  pBar->iID=iPID;
  pBar->iNoDims=4;
  pBar->dDIMs[0]=W/1000;
  pBar->dDIMs[1]=H/1000;
  pBar->dDIMs[2]=dTHK/1000;
  pBar->dDIMs[3]=dTHK/1000;
  pBar->CreateSec();
  pBar->dNSM=dNSM;
  pT->AddItem(pBar);
}
return (pBar);
}


PSHELL* WG_Def::CreateShell(PropTable* pT, double dTHK,double dNSM,int iM,int PIDS)
{
Property* pP=NULL;
PSHELL* pShell=NULL;
int iPID;
pP=pT->GetItem(PIDS);
if ((pP != NULL) && (pP->iType==1))
{
  pShell=(PSHELL*) pP;
}
else
{
  pShell=new PSHELL();
  if (pT->Exists(PIDS)==TRUE)
  {
    iPID=pT->NextID()+10000;
  }
  else
  {
    iPID=PIDS;
  }
  pShell->sTitle="Waveguide Shell";
  pShell->iMID1=iM;
  pShell->iMID2=iM;
  pShell->iMID3=iM;
  pShell->iID=iPID;
  pShell->dT=dTHK/1000;
  pShell->dNSM=dNSM;
  pT->AddItem(pShell);
}
return (pShell);
}

int WG_Def::GenMesh(SecTable* pSecs,PropTable* pT,int iM,PartsCat* Cat, int iDim)
{
int irc=0;
int i;
SecProp* SecP = NULL;
C3dMatrix TMat;
C3dVector vA;
C3dVector vB;
PSHELL* pShell=NULL;
PBARL* pBar=NULL;
double ddH=0;
double ddW=0;
double ddT=0;
double iGenWG=iWG;
double dGenWall=dWall;
int iQM;
int iMAT1=1;
int iMAT2=1;
double dnsmS=0;
double dnsmB=0;
int PIDS;
int PIDB;
//******************************************************************



//******************************************************************
try
{
  if (isMeshed==FALSE)
  {
    outtext1("Generating Mesh");
    // This bit orientates the parts
    if (Cat!=NULL)
    {
      for (i=0;i<iPartCnt;i++)
      {
        if ((WGParts[i]->iObjType == 600) ||
            (WGParts[i]->iObjType == 601) ||
            (WGParts[i]->iObjType == 602) ||
            (WGParts[i]->iObjType == 605))
        {  
           TMat=GetTMat(i);
           vA=GetVA(i);
           vB=GetVB(i);
   	       WG_Part* P =  (WG_Part*) WGParts[i];
	         ME_Object* pM = Cat->Get(P->Name);
           if (P->bFlipZ==TRUE)
           {
             TMat.m_02*=-1;
             TMat.m_12*=-1;
             TMat.m_22*=-1;
           }
	         if (pM!=NULL)
	         {
             P->AttachMesh(pM,TMat,vA,vB);	
	         }
        }
      }
   }
   BOOL CutA=FALSE;
   BOOL CutB=FALSE;
   ME_Object* MeshA = NULL;
   ME_Object* MeshB = NULL;
  //NEED TO DO CUTBACKS BEFORE GENERATING SWEEPS
   for (i=0;i<iPartCnt;i++) 
   {   //Cutback straight sweeps
     if ((WGParts[i]->iObjType == 603) || (WGParts[i]->iObjType == 606))
     {  
	     CutA=FALSE;
       CutB=FALSE;
       Sweep* s = (Sweep*) WGParts[i];
       if ((WGParts[i-1]->iObjType != 604) && (WGParts[i-1]->iObjType != 607))
       {
         
	       WG_Part* WGP = (WG_Part*) WGParts[i-1];
         MeshA=WGP->GetMesh();
         if (WGP->Name!="NULL") 
           {CutA=TRUE;}
	     }
	     if ((WGParts[i+1]->iObjType != 604)  && (WGParts[i+1]->iObjType != 607))
       {
	       WG_Part* WGP = (WG_Part*) WGParts[i+1];
         MeshB=WGP->GetMesh();
         if (WGP->Name!="NULL")
           {CutB=TRUE;}
	     }
	     s->CutBack(CutA,CutB,MeshA,MeshB);
     }
   }
  iGenWG=iWG;
  dGenWall=dWall;
  iQM=iM;
  if (bQ1)
  {iQM=iM+10;}
  SecP = pSecs->GetSecP(iGenWG,dGenWall,iQM,0,0);
  if (SecP!=NULL)
  {
    ddW=SecP->W;
    ddH=SecP->H;
    ddT=SecP->THK;
    iMAT1=SecP->iMat1;
    iMAT2=SecP->iMat2;
    dnsmS=SecP->dNSMS;
    dnsmB=SecP->dNSMB;
    PIDS=SecP->PID;
    PIDB=SecP->PID2;
  }
  else
  {
    outtext1("Section not found");
  }
  pShell = CreateShell(pT,ddT,dnsmS,iMAT1,PIDS);
  pBar= CreatePBARL(pT,"BOX     ",ddW,ddH,ddT,dnsmB,iMAT2,PIDB);
   for (i=0;i<iPartCnt;i++)
   {
     if (iTarnsitionPos==i)
     {   iQM=iM;
         if (bQ2)
         {iQM=iM+10;}
        iGenWG=iWG2;
        dGenWall=dWall2;
        SecP = pSecs->GetSecP(iGenWG,dGenWall,iQM,0,0);
        if (SecP!=NULL)
        {
          ddW=SecP->W;
          ddH=SecP->H;
          ddT=SecP->THK;
          iMAT1=SecP->iMat1;
          iMAT2=SecP->iMat2;
          dnsmS=SecP->dNSMS;
          dnsmB=SecP->dNSMB;
          PIDS=SecP->PID;
          PIDB=SecP->PID2;
        }
        else
        {
           outtext1("Section not found");
        }
        pShell = CreateShell(pT,ddT,dnsmS,iMAT1,PIDS);
        pBar= CreatePBARL(pT,"BOX     ",ddW,ddH,ddT,dnsmB,iMAT2,PIDB);
     }
     if ((WGParts[i]->iObjType == 603) || (WGParts[i]->iObjType == 604))
     {
       Sweep* s = (Sweep*) WGParts[i];
	     s->GenMesh(iDim,pShell,pBar);
	     //s->DeleteSections();
     }
     if (WGParts[i]->iObjType == 606) 
     {
       SecP = pSecs->GetSecPF(iGenWG);
       PSHELL* pShell1 = (PSHELL*) pT->GetItem(SecP->iP1);
       PSHELL* pShell2 = (PSHELL*) pT->GetItem(SecP->iP2);
       PSHELL* pShell3 = (PSHELL*) pT->GetItem(SecP->iP3);
       PSHELL* pShell4 = (PSHELL*) pT->GetItem(SecP->iP4);
       PBARL* pBar1 = (PBARL*) pT->GetItem(SecP->iP5);
       PBARL* pBar2 = (PBARL*) pT->GetItem(SecP->iP6);
       SweepF* s = (SweepF*) WGParts[i];
	     s->GenMesh(iDim,pShell1,pShell2,pShell3,pShell4,pBar1,pBar2);
	     //s->DeleteSections();
     }
     if (WGParts[i]->iObjType == 607) 
     {
       SecP = pSecs->GetSecPF(iGenWG);
       PSHELL* pShell1 = (PSHELL*) pT->GetItem(SecP->iP1);
       PSHELL* pShell2 = (PSHELL*) pT->GetItem(SecP->iP2);
       PSHELL* pShell3 = (PSHELL*) pT->GetItem(SecP->iP3);
       PSHELL* pShell4 = (PSHELL*) pT->GetItem(SecP->iP4);
       PBARL* pBar1 = (PBARL*) pT->GetItem(SecP->iP5);
       PBARL* pBar2 = (PBARL*) pT->GetItem(SecP->iP6);
       SweepFB* s = (SweepFB*) WGParts[i];
	     s->GenMesh(iDim,pShell1,pShell2,pShell3,pShell4,pBar1,pBar2);
	     //s->DeleteSections();
     }
   }
 }
 isMeshed=TRUE;
}
catch(...)
{
isMeshed=FALSE;
  for (i=0;i<iPartCnt;i++)
  {
	  if ((WGParts[i]->iObjType == 603) || (WGParts[i]->iObjType == 604))
    {
      Sweep* s = (Sweep*) WGParts[i];
      if (s->Mesh!=NULL)
      {
	      delete(s->Mesh);
	      s->Mesh=NULL;
      }
	  }
  }
  irc=3;
}
return (irc);
}

ME_Object* WG_Def::GetMesh()
{
int iE=10000;
int iN=10000;
if (isMeshed)
{
ME_Object* Me = new ME_Object();
Me->Name=Name;
int i;
for (i=0;i<iPartCnt;i++)
{
  if ((WGParts[i]->iObjType == 603)  ||
	    (WGParts[i]->iObjType == 604)  ||
      (WGParts[i]->iObjType == 606)  ||
      (WGParts[i]->iObjType == 607))

  {
     Sweep* SP=(Sweep*) WGParts[i];
     Me->Append(SP->GetMesh(),iN,iE);
	   iN+=10000;
	   iE+=10000;
  }
  else
  {
     WG_Part* WP=(WG_Part*) WGParts[i];
     Me->Append(WP->GetMesh(),iN,iE);
	   iN+=10000;
	   iE+=10000;
  }
}
return (Me);
}
else
{
return (NULL);
}
}


void WG_Def::addLn(CString inT)
{

if (iTCnt<MaxT)
{
	Text[iTCnt]=inT;
	iTCnt++;
}
}

int WG_Def::AddPart(G_Object* inP)
{
if (iPartCnt<MaxP)
{
	WGParts[iPartCnt]=inP;
	iPartCnt++;
}
return (iPartCnt-1);
}

C3dVector WG_Def::GetLastInsPos()
{
  int i;

  C3dVector vRet;
  for (i=iPartCnt-1;i>=0;i--)
  {
    if ((WGParts[i]->iObjType==600) ||
        (WGParts[i]->iObjType==601) ||
        (WGParts[i]->iObjType==602) ||
        (WGParts[i]->iObjType==605) )
    {
       WG_Part* pP = (WG_Part*) WGParts[i];
	     vRet=pP->GetInPt();
       break;
    }
    else if ((WGParts[i]->iObjType==604) || 
             (WGParts[i]->iObjType==607))
    {
       SweepB* pP = (SweepB*) WGParts[i];
	     vRet=pP->GetInPt();
       break;
    }
  }
  return (vRet);
}


void WG_Def::HighLight(CDC* pDC)
{
int i;
for (i=0;i<iPartCnt;i++)
{
  WGParts[i]->HighLight(pDC);
}
}

void WG_Def::Info()
{
  char S1[80];
  int i;
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  outtext1("WAVEGUIDE OBJECT");
  outtext1(Name); 
  outtext1(S1); 

  for(i=0;i<iTCnt;i++)
  {
    outtext1(Text[i]); 
  }
  sprintf_s(S1,"%s%i%s%f","Type ",iWG,"    WALL ",dWall);
  outtext1(S1); 

}

void WG_Def::S_Box(CPoint P1,CPoint P2,ObjList* pSel)
{
int i;

  for (i=0;i<iPartCnt;i++)
  {
    WGParts[i]->S_Box(P1,P2,pSel);
  }
}


G_ObjectD WG_Def::SelDist(CPoint InPT,Filter FIL)
{

G_ObjectD Ret;
G_Object* pMinSel;
double ds=1e36;
double Minds=1e36;
Ret.pObj=NULL;
Ret.Dist=Minds;
int i;

  for (i=0;i<iPartCnt;i++)
  {
    Ret=WGParts[i]->SelDist(InPT,FIL);
    if (Ret.Dist<Minds)
    {
	    Minds=Ret.Dist;
      pMinSel=Ret.pObj;
    }
  }

Ret.Dist=Minds;
Ret.pObj=pMinSel;
return (Ret);
}


Circ1* WG_Def::Fillet(Line_Object* Ln,Line_Object* Ln1,double dR)
{
double R;
R=dR;
C3dVector p1;
p1.Set(Ln->pVertex1->Pt_Point->x,
	   Ln->pVertex1->Pt_Point->y,
	   Ln->pVertex1->Pt_Point->z);
C3dVector p2;
p2.Set(Ln->pVertex2->Pt_Point->x,
	   Ln->pVertex2->Pt_Point->y,
	   Ln->pVertex2->Pt_Point->z);
C3dVector p3;
p3.Set(Ln1->pVertex2->Pt_Point->x,
	   Ln1->pVertex2->Pt_Point->y,
	   Ln1->pVertex2->Pt_Point->z);

C3dVector v1;
v1=p2;
v1-=p1;
C3dVector v2;
v2=p3;
v2-=p2;

C3dVector vn;
vn=v1.Cross(v2);
vn.Normalize();
C3dVector v1o;
C3dVector v2o;

v1o=v1.Cross(vn);
v2o=v2.Cross(vn);
v1o.Normalize();
v2o.Normalize();
v1o*=R;
v2o*=R;
if (v1o.Dot(v2)<0)
  v1o*=-1;
if (v2o.Dot(v1)>0)
  v2o*=-1;
C3dVector p1o;
C3dVector p2o;
C3dVector p3o;
C3dVector p4o;

p1o=p1;
p1o+=v1o;
p2o=p2;
p2o+=v1o;
p3o=p2;
p3o+=v2o;
p4o=p3;
p4o+=v2o;
Line_Object* Ln2 = new Line_Object;
Ln2->Create(&p1o,&p2o,1,NULL);
Line_Object* Ln3 = new Line_Object;
Ln3->Create(&p3o,&p4o,1,NULL);
C3dVector IntPt;
IntPt=LnInt(Ln2,Ln3);
Circ1* cCir = new Circ1();
cCir->Create(vn,IntPt,R,-1,NULL);

C3dVector IntPt1;
IntPt1=Ln->MinPt(IntPt);
Ln->SetP2(IntPt1.x,IntPt1.y,IntPt1.z);
C3dVector IntPt2;
IntPt2=Ln1->MinPt(IntPt);
Ln1->SetP1(IntPt2.x,IntPt2.y,IntPt2.z);
double d1;
double d2;
C3dVector LVec;
C3dVector CVec;
d1=cCir->MinWPt(IntPt1);
d2=cCir->MinWPt(IntPt2);
LVec=Ln->GetDir(1);
CVec=cCir->GetDir(d1);
if (LVec.Dot(CVec)<0)
{
cCir->Reverse();
d1=cCir->MinWPt(IntPt1);
d2=cCir->MinWPt(IntPt2);
}
if (d2<d1)
{
	d2+=1;
}
if (d1<0)
{
	d1=0;
}
cCir->dS=d1;
cCir->dE=d2;

delete (Ln2);
delete (Ln3);
return(cCir);
}

//This is taken from DBase
NCircle* WG_Def::NFillet(NLine* Ln,NLine* Ln1,double dR)
{
C3dVector PNear1;
C3dVector PNear2;
double R;
R=dR;
C3dVector p1;
C3dVector p2;
C3dVector p3;
C3dVector pT;
C3dVector vL1Dir;
C3dVector* pLT1;
C3dVector* pLT2;
C3dVector v1;
C3dVector v2;
C3dVector v3;
C3dVector vRef;
C3dVector vDir;
// The intersection of the lines



v1=Ln->GetDir(0.5);

v2=Ln1->GetDir(0.5);;
p1=Ln->GetPt(0);
pLT1=Ln->cPts[1]->Pt_Point;
p2=NLnInt(Ln,Ln1);
//p2=pLT1;
p3=Ln1->GetPt(1);
pLT2=Ln1->cPts[0]->Pt_Point;
C3dVector vn;
vn=v1.Cross(v2);
vn.Normalize();
C3dVector v1o;
C3dVector v2o;

v1o=v1.Cross(vn);
v2o=v2.Cross(vn);
v1o.Normalize();
v2o.Normalize();
v1o*=R;
v2o*=R;
if (v1o.Dot(v2)<0)
  v1o*=-1;
if (v2o.Dot(v1)>0)
  v2o*=-1;
C3dVector p1o;
C3dVector p2o;
C3dVector p3o;
C3dVector p4o;

p1o=p1;
p1o+=v1o;
p2o=p2;
p2o+=v1o;
p3o=p2;
p3o+=v2o;
p4o=p3;
p4o+=v2o;
NLine* Ln2 = new NLine;
Ln2->Create(p1o,p2o,1,NULL);
NLine* Ln3 = new NLine;
Ln3->Create(p3o,p4o,1,NULL);
C3dVector IntPt;
IntPt=NLnInt(Ln2,Ln3);


C3dVector IntPt1;
IntPt1=Ln->MinPt(IntPt);
vRef=IntPt1;
vRef-=IntPt;
vRef.Normalize();

NCircle* cCir = new NCircle();
cCir->Create2(vn,IntPt,vRef,R,-1,NULL);
cCir->vNorm=vn; // Note the transform method in Create2 changes the normal
                //so set it back 
pLT1->Set(IntPt1.x,IntPt1.y,IntPt1.z);  //trim the end point
C3dVector IntPt2;
IntPt2=Ln1->MinPt(IntPt);
pLT2->Set(IntPt2.x,IntPt2.y,IntPt2.z);  //trim the end point

//d1q=cCir->MinWPt(IntPt1);

//vRef=IntPt1;
//vDir=cCir->GetDir(d1q);
//vDir.Normalize();
//vRef-=cCir->vCent;
//vRef.Normalize();
  //if (vDir.Dot(vL1Dir)<0)
  //{
  //  vn*=-1;
  //}
  //delete (cCir);
  //cCir = new NCircle();
  //cCir->Create2(vn,IntPt,vRef,R,-1,NULL);
  //d1q=cCir->MinWPt(IntPt1);
double d2q;
d2q=cCir->MinWPt(IntPt2);
cCir->we=d2q;

delete (Ln2);
delete (Ln3);

return(cCir);
}

C3dVector WG_Def::NLnInt(NCurve* L1,NCurve* L2)
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
while ((dDist>dTol) && (iMaxIt<100000));
return (P2);
}

C3dVector WG_Def::LnInt(Line_Object* L1,G_Object* L2)
{
int i=0;
double MinDist = 10000000;
double dDist = 0;
double dDistB = 0;
const double dTol = 0.00001;
C3dVector P1;
C3dVector P2;

P1.Set(L1->pVertex1->Pt_Point->x,
       L1->pVertex1->Pt_Point->y,
       L1->pVertex1->Pt_Point->z);

do
{
  P2=L2->MinPt(P1);
  P1=L1->MinPt(P2);
  dDist=P2.Dist(P1);
}
while (dDist>dTol);
return (P2);
}

IMPLEMENT_DYNAMIC( WG_Part, CObject )

WG_Part::WG_Part()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 600;
G_label = -1;
G_Colour = 2;
inPt=NULL;
Mesh=NULL;
bFlipZ=FALSE;
}

void WG_Part::Create(int iLab,CString inName,
					 C3dVector inP,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 600;
G_label = iLab;
G_Colour = 2;
Mesh=NULL;
Name=inName;
pParent=Parrent;
if (inPt!=NULL)
{ delete(inPt);}
inPt=new CvPt_Object;
inPt->Create(inP,0,-1,0,0,1,this);
bFlipZ=FALSE;
}


C3dVector WG_Part:: GetInPt()
{
C3dVector vR;
vR.x=inPt->Pt_Point->x;
vR.y=inPt->Pt_Point->y;
vR.z=inPt->Pt_Point->z;
return (vR);
}


// Draw Object line
void WG_Part::Draw(CDC* pDC,int iDrawmode)
{
if (inPt!=NULL)
  {inPt->Draw(pDC,iDrawmode);
   pDC->MoveTo((int) inPt->DSP_Point->x+20,(int) inPt->DSP_Point->y);
   pDC->LineTo((int) inPt->DSP_Point->x,(int) inPt->DSP_Point->y+20);
   pDC->LineTo((int) inPt->DSP_Point->x-20,(int) inPt->DSP_Point->y);
   pDC->LineTo((int) inPt->DSP_Point->x,(int) inPt->DSP_Point->y-20);
   pDC->LineTo((int) inPt->DSP_Point->x+20,(int) inPt->DSP_Point->y);
}
if (Mesh!=NULL)
  {Mesh->Draw(pDC,iDrawmode);}
}

void WG_Part::HighLight(CDC* pDC)
{
if (inPt!=NULL)
  {inPt->Draw(pDC,4);
   pDC->MoveTo((int) inPt->DSP_Point->x+20,(int) inPt->DSP_Point->y);
   pDC->LineTo((int) inPt->DSP_Point->x,(int) inPt->DSP_Point->y+20);
   pDC->LineTo((int) inPt->DSP_Point->x-20,(int) inPt->DSP_Point->y);
   pDC->LineTo((int) inPt->DSP_Point->x,(int) inPt->DSP_Point->y-20);
   pDC->LineTo((int) inPt->DSP_Point->x+20,(int) inPt->DSP_Point->y);
   }
}

void WG_Part::OglDraw(int iDspFlgs,double dS1,double dS2)
{
if (inPt!=NULL)
{
  glColor3fv(cols[inPt->GetCol()]);
  glPointSize(16.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) inPt->Pt_Point->x,(float) inPt->Pt_Point->y,(float) inPt->Pt_Point->z);
  glEnd();
}
if (Mesh!=NULL)
  {Mesh->OglDraw(iDspFlgs,dS1,dS2);}
}

void WG_Part::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
if (inPt!=NULL)
{
  glColor3fv(cols[inPt->GetCol()]);
  glPointSize(16.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) inPt->Pt_Point->x,(float) inPt->Pt_Point->y,(float) inPt->Pt_Point->z);
  glEnd();
}
if (Mesh!=NULL)
  {Mesh->OglDrawW(iDspFlgs,dS1,dS2);}
}

void WG_Part::Info()
{
outtext1("Wave Guide Part");
G_Object::Info();
outtext1(Name);
}


C3dVector WG_Part::MinPt(C3dVector inPt)
{
C3dVector vRet;
vRet.x=this->inPt->Pt_Point->x;
vRet.y=this->inPt->Pt_Point->y;
vRet.z=this->inPt->Pt_Point->z;

return (vRet);
}

ME_Object* WG_Part::GetMesh()
{
return (Mesh);
}

void WG_Part::AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB)
{
Mesh=pM;
TMat.Translate2(inPt->Pt_Point->x,inPt->Pt_Point->y,inPt->Pt_Point->z);
Mesh->Transform(TMat);
AttachTform(TMat);
Mesh->pParent=this;
}

void WG_Part::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
if (inPt!=NULL)
  {inPt->SetToScr(pModMat,pScrTran);}
if (Mesh!=NULL)
  {Mesh->SetToScr(pModMat,pScrTran);}
}

G_ObjectD WG_Part::SelDist(CPoint InPT,Filter FIL)
{
double d;
G_ObjectD Ret;
d=1000;

if (Mesh==NULL)
{
  Ret=inPt->SelDist(InPT,FIL);
  Ret.pObj=this;
}
else
{
  Ret=Mesh->SelDist(InPT,FIL);
}
return (Ret);
}

void WG_Part::S_Box(CPoint P1,CPoint P2,ObjList* pSel)
{
if (Mesh!=NULL)
{
  Mesh->S_Box(P1,P2,pSel);
}
}




C3dVector WG_Part::Get_Centroid()
{
return (inPt->Get_Centroid());
}


void WG_Part::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{  		// TODO: add storing code here
      G_Object::Serialize(ar);
	  ar<<OMat.m_00;ar<<OMat.m_01;ar<<OMat.m_02;ar<<OMat.m_03;
      ar<<OMat.m_10;ar<<OMat.m_11;ar<<OMat.m_12;ar<<OMat.m_13;
      ar<<OMat.m_20;ar<<OMat.m_21;ar<<OMat.m_22;ar<<OMat.m_23;
      ar<<OMat.m_30;ar<<OMat.m_31;ar<<OMat.m_32;ar<<OMat.m_33;
      ar<<Name;
      ar<<bFlipZ;
	  inPt->Serialize(ar);
	  int iISMesh=0;
	  if (Mesh!=NULL)
	  {
       iISMesh=1;
       ar<<iISMesh;
       Mesh->Serialize(ar);
	  }
	  else
      {
	   iISMesh=0;
       ar<<iISMesh;
	  }
	}
	else
	{
      G_Object::Serialize(ar);
	    ar>>OMat.m_00;ar>>OMat.m_01;ar>>OMat.m_02;ar>>OMat.m_03;
      ar>>OMat.m_10;ar>>OMat.m_11;ar>>OMat.m_12;ar>>OMat.m_13;
      ar>>OMat.m_20;ar>>OMat.m_21;ar>>OMat.m_22;ar>>OMat.m_23;
      ar>>OMat.m_30;ar>>OMat.m_31;ar>>OMat.m_32;ar>>OMat.m_33;
      ar>>Name;
      ar>>bFlipZ;
	    inPt=new CvPt_Object;
	    inPt->Serialize(ar);
	    int iISMesh=0;
      ar>>iISMesh;
	    if (iISMesh==1)
	    {
	      Mesh = new ME_Object();
	      Mesh->pParent=this;
        Mesh->Serialize(ar);
	    }
    }
}


void WG_Part::AttachTform(C3dMatrix inMat)
{
  OMat=inMat;
}

void WG_Part::FlipZ()
{
C3dMatrix invOMat;
C3dMatrix ZRot;

if (Mesh!=NULL)
{
  ZRot.Rotate(0,0,180);
  invOMat.MakeUnit();
  invOMat.m_30=-inPt->Pt_Point->x;
  invOMat.m_31=-inPt->Pt_Point->y;
  invOMat.m_32=-inPt->Pt_Point->z;
  Mesh->Transform(invOMat);
  invOMat.MakeUnit();
  invOMat=OMat;
  invOMat.Transpose();
  invOMat.m_30=0;
  invOMat.m_31=0;
  invOMat.m_32=0;
  Mesh->Transform(invOMat);

  invOMat=OMat*ZRot;
  invOMat.m_30=inPt->Pt_Point->x;
  invOMat.m_31=inPt->Pt_Point->y;
  invOMat.m_32=inPt->Pt_Point->z;
  Mesh->Transform(invOMat);
  AttachTform(invOMat);
}
}


void WG_Part::FlipY()
{
C3dMatrix invOMat;
C3dMatrix ZRot;

if (Mesh!=NULL)
{
  ZRot.Rotate(0,90,0);
  invOMat.MakeUnit();
  invOMat.m_30=-inPt->Pt_Point->x;
  invOMat.m_31=-inPt->Pt_Point->y;
  invOMat.m_32=-inPt->Pt_Point->z;
  Mesh->Transform(invOMat);
  invOMat.MakeUnit();
  invOMat=OMat;
  invOMat.Transpose();
  invOMat.m_30=0;
  invOMat.m_31=0;
  invOMat.m_32=0;
  Mesh->Transform(invOMat);

  invOMat=OMat*ZRot;
  invOMat.m_30=inPt->Pt_Point->x;
  invOMat.m_31=inPt->Pt_Point->y;
  invOMat.m_32=inPt->Pt_Point->z;
  Mesh->Transform(invOMat);
  AttachTform(invOMat);
}
}

IMPLEMENT_DYNAMIC( WG_Elbow, CObject )

WG_Elbow::WG_Elbow()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 601;
G_label = -1;
G_Colour = 2;
inPt=NULL;
isHBend=0;
}

void WG_Elbow::Create(int iLab,CString inName,
					 C3dVector inP,int HB,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 601;
G_label = iLab;
G_Colour = 2;
pParent=Parrent;
Name=inName;
if (inPt!=NULL)
{ delete(inPt);}
inPt=new CvPt_Object;
inPt->Create(inP,0,-1,0,0,11,this);
isHBend=HB;
}

void WG_Elbow::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{  		// TODO: add storing code here
      WG_Part::Serialize(ar);
      ar<<isHBend;
	}
	else
	{
      WG_Part::Serialize(ar);
      ar>>isHBend;
    }
}


void WG_Elbow::AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB)
{

C3dMatrix Forward;
C3dMatrix Back;

C3dVector vZ;
C3dVector vNA;
C3dVector vNB;
TMat.MakeUnit();
vA*=-1;
vZ=vA.Cross(vB);
vB=vZ.Cross(vA);
Forward.SetColVec(1,vA);
Forward.SetColVec(2,vB);
Forward.SetColVec(3,vZ);

Mesh=pM;
Pt_Object* pANd =Mesh->GetNode(1);
Pt_Object* pBNd =Mesh->GetNode(2);
if ((pANd!=NULL) && (pBNd!=NULL))
{
  vNA = pANd->GetCoords();
  vNB = pBNd->GetCoords();
  vNA.Normalize();
  vNB.Normalize();
  vZ=vNA.Cross(vNB);
  vNB=vZ.Cross(vNA);
  Back.SetColVec(1,vNA);
  Back.SetColVec(2,vNB);
  Back.SetColVec(3,vZ);
  Back.Transpose();
  TMat*=Forward;
  TMat*=Back;
}
TMat.Translate2(inPt->Pt_Point->x,inPt->Pt_Point->y,inPt->Pt_Point->z);
Mesh->Transform(TMat);
AttachTform(TMat);
Mesh->pParent=this;
}

IMPLEMENT_DYNAMIC( WG_Brk, CObject )

WG_Brk::WG_Brk()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 602;
G_label = -1;
G_Colour = 2;
inPt=NULL;
OPt=NULL;
}

void WG_Brk::Create(int iLab,CString inName,
					 C3dVector inP,C3dVector inOP,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 602;
G_label = iLab;
G_Colour = 2;
pParent=Parrent;
Name=inName;
if (inPt!=NULL)
{ delete(inPt);}
inPt=new CvPt_Object;
inPt->Create(inP,0,-1,0,0,11,this);
if (OPt!=NULL)
{ delete(OPt);}
OPt=new CvPt_Object;
OPt->Create(inOP,0,-1,0,0,11,this);
}

void WG_Brk::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{  		// TODO: add storing code here
      WG_Part::Serialize(ar);
      OPt->Serialize(ar);
	}
	else
	{
      WG_Part::Serialize(ar);
	    OPt=new CvPt_Object;
      OPt->Serialize(ar);
    }
}


G_ObjectD WG_Brk::SelDist(CPoint InPT,Filter FIL)
{
double Minds;
G_ObjectD Ret;
G_Object* pMinSel;
Minds=1e36;
Ret.pObj=NULL;
Ret.Dist=Minds;

if (Mesh!=NULL)
{
  Ret=Mesh->SelDist(InPT,FIL);
  pMinSel=Ret.pObj;
  Minds=Ret.Dist;
}

if (inPt!=NULL)
{
  Ret=inPt->SelDist(InPT,FIL);
  if (Ret.Dist<Minds)
  {
    pMinSel=Ret.pObj;
    Minds=Ret.Dist;
  }
}
if (OPt!=NULL)
{
  Ret=OPt->SelDist(InPT,FIL);
  if (Ret.Dist<Minds)
  {
    pMinSel=Ret.pObj;
    Minds=Ret.Dist;
  }
}
Ret.Dist=Minds;
Ret.pObj=pMinSel;

return (Ret);
}

void WG_Brk::AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB)
{
Mesh=pM;
TMat.Translate2(inPt->Pt_Point->x,inPt->Pt_Point->y,inPt->Pt_Point->z);
Mesh->Transform(TMat);
AttachTform(TMat);
Pt_Object* pXNd =Mesh->GetNode(3);
if (pXNd!=NULL)
{
   C3dVector XPt;
	 C3dVector XAcctPt;
   XPt.x=pXNd->Pt_Point->x-inPt->Pt_Point->x;
   XPt.y=pXNd->Pt_Point->y-inPt->Pt_Point->y;
   XPt.z=pXNd->Pt_Point->z-inPt->Pt_Point->z;
	 XPt.Normalize();
   XAcctPt.x=OPt->Pt_Point->x-inPt->Pt_Point->x;
	 XAcctPt.y=OPt->Pt_Point->y-inPt->Pt_Point->y;
	 XAcctPt.z=OPt->Pt_Point->z-inPt->Pt_Point->z;
	 XAcctPt.Normalize();
	 double ddot;
   ddot=XPt.Dot(XAcctPt);
	 if (ddot<-0.5)
	 {
			FlipZ();
	 }	      }

Mesh->pParent=this;
}

void WG_Brk::Draw(CDC* pDC,int iDrawmode)
{
WG_Part::Draw(pDC,iDrawmode);
if ((inPt!=NULL) && (OPt!=NULL))
  {
   inPt->Draw(pDC,iDrawmode);
   pDC->MoveTo((int) inPt->DSP_Point->x,(int) inPt->DSP_Point->y);
   pDC->LineTo((int) OPt->DSP_Point->x,(int) OPt->DSP_Point->y);

  }

}

void WG_Brk::OglDraw(int iDspFlgs,double dS1,double dS2)
{
if (OPt!=NULL)
  {OPt->OglDraw(iDspFlgs,dS1,dS2);}
if (Mesh!=NULL)
  {Mesh->OglDraw(iDspFlgs,dS1,dS2);}
}

void WG_Brk::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
if (inPt!=NULL)
{
  glColor3fv(cols[inPt->GetCol()]);
  glPointSize(16.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) inPt->Pt_Point->x,(float) inPt->Pt_Point->y,(float) inPt->Pt_Point->z);
  glEnd();
}
if (OPt!=NULL)
{
  glColor3fv(cols[OPt->GetCol()]);
  glPointSize(16.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) OPt->Pt_Point->x,(float) OPt->Pt_Point->y,(float) OPt->Pt_Point->z);
  glEnd();
}
if (Mesh!=NULL)
  {Mesh->OglDrawW(iDspFlgs,dS1,dS2);}
}

void WG_Brk::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
if ((inPt!=NULL) && (OPt!=NULL))
  {
	inPt->SetToScr(pModMat,pScrTran);
	OPt->SetToScr(pModMat,pScrTran);
  }
if (Mesh!=NULL)
{Mesh->SetToScr(pModMat,pScrTran);}
}
//******************************************************
IMPLEMENT_DYNAMIC(WG_Brk_Int, CObject )

WG_Brk_Int::WG_Brk_Int()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 605;
G_label = -1;
G_Colour = 2;
inPt=NULL;
OPt=NULL;
OPt2=NULL;
}

void WG_Brk_Int::Create(int iLab,CString inName,
					  C3dVector inP,C3dVector inOP,C3dVector inOP2,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 605;
G_label = iLab;
G_Colour = 2;
pParent=Parrent;
Name=inName;
if (inPt!=NULL)
{ delete(inPt);}
inPt=new CvPt_Object;
inPt->Create(inP,0,-1,0,0,11,this);
if (OPt!=NULL)
{ delete(OPt);}
OPt=new CvPt_Object;
OPt->Create(inOP,0,-1,0,0,11,this);
if (OPt2!=NULL)
{ delete(OPt2);}
OPt2=new CvPt_Object;
OPt2->Create(inOP2,0,-1,0,0,11,this);
}

void WG_Brk_Int::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{  		// TODO: add storing code here
      WG_Part::Serialize(ar);
      OPt->Serialize(ar);
      OPt2->Serialize(ar);
	}
	else
	{
      WG_Part::Serialize(ar);
	    OPt=new CvPt_Object;
      OPt->Serialize(ar);
      OPt2=new CvPt_Object;
      OPt2->Serialize(ar);
    }
}

G_ObjectD WG_Brk_Int::SelDist(CPoint InPT,Filter FIL)
{
double Minds;
G_ObjectD Ret;
G_Object* pMinSel;

Minds=1e36;
Ret.pObj=NULL;
Ret.Dist=Minds;
Ret=WG_Brk::SelDist(InPT,FIL);
Minds=Ret.Dist;
pMinSel=Ret.pObj;

if (OPt2!=NULL)
{
  Ret=OPt2->SelDist(InPT,FIL);
  if (Ret.Dist<Minds)
  {
    pMinSel=Ret.pObj;
    Minds=Ret.Dist;
  }
}
Ret.Dist=Minds;
Ret.pObj=pMinSel;
return(Ret);
}


void WG_Brk_Int::AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB)
{
C3dVector vD;
double dd=0;
double dMin=100000;
C3dVector vX;
C3dVector vY;
C3dVector vZ;
C3dVector vDown;
C3dVector vFEM;
C3dVector vREP;
TMat.ClearTranslations();

double dAng=0;
int i;

if (vA.Mag()==0)
{
  vA=vB;
}

Mesh=pM;
Pt_Object* pXNd1 =Mesh->GetNode(3);
//Pt_Object* pXNd2 =Mesh->GetNode(4);
C3dMatrix SaveTMat;
SaveTMat=TMat;
C3dMatrix ZRot;
vREP=OPt->GetCoords();
C3dMatrix MinTmat;
if (pXNd1!=NULL)
  {
  for (i=0;i<8;i++)
  {
    ZRot.Rotate(0,0,dAng);
    TMat=SaveTMat*ZRot;
    vFEM=pXNd1->Get_Centroid();
    vFEM=TMat.Mult(vFEM);
    vFEM+=inPt->GetCoords();
    vD=vFEM;
    vD-=vREP;
    dd=vD.Mag();
    if (dd<dMin)
    {
      dMin=dd;
      MinTmat=TMat;
    }
    if (i==3)
    {
       vX=SaveTMat.GetColVec(1);
       vZ=SaveTMat.GetColVec(3);
       vX*=-1;
       vZ*=-1;
       SaveTMat.SetColVec(1,vX);
       SaveTMat.SetColVec(3,vZ);
    }
    dAng+=90.0;
  }  
}
else
{
  outtext1("Mesh cannot be orientated chexk nodes 3 & 4");
}
MinTmat.Translate2(inPt->Pt_Point->x,inPt->Pt_Point->y,inPt->Pt_Point->z);
Mesh->Transform(MinTmat);
AttachTform(MinTmat);
Mesh->pParent=this;
}

void WG_Brk_Int::Draw(CDC* pDC,int iDrawmode)
{
WG_Part::Draw(pDC,iDrawmode);
if ((inPt!=NULL) && (OPt!=NULL) && (OPt2!=NULL))
  {
   inPt->Draw(pDC,iDrawmode);
   pDC->MoveTo((int) inPt->DSP_Point->x,(int) inPt->DSP_Point->y);
   pDC->LineTo((int) OPt->DSP_Point->x,(int) OPt->DSP_Point->y);
   pDC->LineTo((int) OPt2->DSP_Point->x,(int) OPt2->DSP_Point->y);
  }

}

void WG_Brk_Int::OglDraw(int iDspFlgs,double dS1,double dS2)
{
if (OPt!=NULL)
  {OPt->OglDraw(iDspFlgs,dS1,dS2);}
if (OPt2!=NULL)
  {OPt2->OglDraw(iDspFlgs,dS1,dS2);}
if (Mesh!=NULL)
  {Mesh->OglDraw(iDspFlgs,dS1,dS2);}
}

void WG_Brk_Int::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
if (inPt!=NULL)
{
  glColor3fv(cols[inPt->GetCol()]);
  glPointSize(16.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) inPt->Pt_Point->x,(float) inPt->Pt_Point->y,(float) inPt->Pt_Point->z);
  glEnd();
}
if (OPt!=NULL)
{
  glColor3fv(cols[OPt->GetCol()]);
  glPointSize(16.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) OPt->Pt_Point->x,(float) OPt->Pt_Point->y,(float) OPt->Pt_Point->z);
  glEnd();
}
if (OPt2!=NULL)
{
  glColor3fv(cols[OPt->GetCol()]);
  glPointSize(16.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) OPt2->Pt_Point->x,(float) OPt2->Pt_Point->y,(float) OPt2->Pt_Point->z);
  glEnd();
}
if (Mesh!=NULL)
  {Mesh->OglDrawW(iDspFlgs,dS1,dS2);}
}

void WG_Brk_Int::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
if ((inPt!=NULL) && (OPt!=NULL) && (OPt2!=NULL))
  {
	inPt->SetToScr(pModMat,pScrTran);
	OPt->SetToScr(pModMat,pScrTran);
  OPt2->SetToScr(pModMat,pScrTran);
  }
if (Mesh!=NULL)
{Mesh->SetToScr(pModMat,pScrTran);}
}
//*****************************************************

IMPLEMENT_DYNAMIC( Section, CObject )

Section::~Section()
{
int i;
for (i=0;i<iLnCnt;i++)
{
  delete (pLn[i]);
  pLn[i]=NULL;
}
}

void Section::Create(int iLab,int inPID,int inPID2,int inSec,int inCol,G_Object* Parrent)
{
TMat.MakeUnit();
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 200;
G_label = iLab;
G_Colour = inCol;
iLnCnt=0;
iSec=inSec;
iPID=inPID;
iPID2=inPID2;
pParent=Parrent;
}



void Section::Serialize(CArchive& ar)
{
  int i;
  int iT;
	if (ar.IsStoring())
	{
		// TODO: add storing code here

	G_Object::Serialize(ar);
	ar<<iSec;
    ar<<iPID;
	ar<<iPID2;
    ar<<TMat.m_00;ar<<TMat.m_01;ar<<TMat.m_02;ar<<TMat.m_03;
    ar<<TMat.m_10;ar<<TMat.m_11;ar<<TMat.m_12;ar<<TMat.m_13;
    ar<<TMat.m_20;ar<<TMat.m_21;ar<<TMat.m_22;ar<<TMat.m_23;
    ar<<TMat.m_30;ar<<TMat.m_31;ar<<TMat.m_32;ar<<TMat.m_33;
	  inPt.Serialize(ar);
    ar<<iLnCnt;
    for(i=0;i<iLnCnt;i++)
    {
      ar << NoSegs[i];
      ar << pLn[i]->iObjType;
      pLn[i]->Serialize(ar);;
    }
	}
	else
	{
    G_Object::Serialize(ar);
	  ar>>iSec;
    ar>>iPID;
	  ar>>iPID2;
    ar>>TMat.m_00;ar>>TMat.m_01;ar>>TMat.m_02;ar>>TMat.m_03;
    ar>>TMat.m_10;ar>>TMat.m_11;ar>>TMat.m_12;ar>>TMat.m_13;
    ar>>TMat.m_20;ar>>TMat.m_21;ar>>TMat.m_22;ar>>TMat.m_23;
    ar>>TMat.m_30;ar>>TMat.m_31;ar>>TMat.m_32;ar>>TMat.m_33;
	  inPt.Serialize(ar);
    ar>>iLnCnt;
    for(i=0;i<iLnCnt;i++)
    {
      ar >> NoSegs[i];
      ar >> iT;
      if (iT==8)
      {
        pLn[i]=new NCircle;
        pLn[i]->Serialize(ar);
      }
      else
      {
        pLn[i]=new NLine;
        pLn[i]->Serialize(ar);
      }
    }
	}	
}

G_Object* Section::Copy(G_Object* Parrent)
{
int i;
Section* NewSec = new Section;
NewSec->Create(G_label,iPID,iPID2,iSec,G_Colour,NULL);
for (i=0;i<iLnCnt;i++)
{
  NewSec->pLn[i]=(NCurve*) pLn[i]->Copy(this);
  NewSec->NoSegs[i]=NoSegs[i];

}
NewSec->iLnCnt=iLnCnt;
NewSec->pParent=Parrent;
return (NewSec);
}

// Draw Object line
void Section::Draw(CDC* pDC,int iDrawmode)
{
int j=0;
if (iLnCnt != 0)
{
for (j=0;j<iLnCnt;j++)
   {
   pLn[j]->HighLight(pDC);
   }
}
}

void Section::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
  OglDraw(iDspFlgs,dS1,dS2);
}

void Section::OglDraw(int iDspFlgs,double dS1,double dS2)
{
int j=0;
if (iLnCnt != 0)
{
for (j=0;j<iLnCnt;j++)
   {
   pLn[j]->OglDraw(iDspFlgs,dS1,dS2);
   }
}

}


void Section::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
int j;
if (iLnCnt != 0)
{
  for (j=0;j<iLnCnt;j++)
  {
    pLn[j]->SetToScr(pModMat,pScrTran);
  }
}
}

void Section::Transform(C3dMatrix inTMat)
{
TMat=inTMat;
int j=0;
if (iLnCnt != 0)
  {
  for (j=0;j<iLnCnt;j++)
   {
    pLn[j]->Transform(inTMat);
   }
  }
}



C3dVector Section::Get_Centroid()
{
C3dVector vT;
vT.x = 0; //to be done
vT.y = 0;
vT.z = 0;
return (vT);
}


void Section::HighLight(CDC* pDC)
{
Draw(pDC,4);
}


G_ObjectD Section::SelDist(CPoint InPT,Filter FIL)
{
G_ObjectD Ret;
Ret.Dist=1000;
Ret.pObj=this;
return (Ret);
}

void Section::ChangeCol(int iCOl)
{
int i;
for (i=0;i<iLnCnt;i++)
  {pLn[i]->G_Colour= iCOl;}
}

void Section::AddLine(double X1,double Y1,
                      double X2,double Y2,
                      int NoDivs)
{
C3dVector pt1;
pt1.Set(X1,Y1,0);
C3dVector pt2;
pt2.Set(X2,Y2,0);
if (iLnCnt < 50) 
{
  NLine* pL = new NLine();

  pL->Create(pt1,pt2,iLnCnt,this);
  pL->pParent=this;
  pLn[iLnCnt] = pL;
  NoSegs[iLnCnt] =NoDivs;
  iLnCnt++;
}
}

void Section::MakeSpace(int iPos)
{
int i;
if (iLnCnt<50)
{
  for (i=iLnCnt;i>iPos;i--)
  {
    NoSegs[i] =NoSegs[i-1];
    pLn[i] =pLn[i-1];
  }
  pLn[iPos]=NULL;
  iLnCnt++;
}

}

void Section::FilletCrns(double dR)
{
NCircle* pC;
NoSegs[0]-=2;
NoSegs[1]-=2;
NoSegs[2]-=2;
NoSegs[3]-=2;

pC=NFillet((NLine*) pLn[0],(NLine*) pLn[1],dR);
MakeSpace(1);
pLn[1]=(NCircle*) pC;
pLn[1]->pParent=this;
NoSegs[1]=2;
pC=NFillet((NLine*) pLn[2],(NLine*) pLn[3],dR);
MakeSpace(3);
pLn[3]=(NCircle*) pC;
pLn[3]->pParent=this;
NoSegs[3]=2;
pC=NFillet((NLine*) pLn[4],(NLine*) pLn[5],dR);
MakeSpace(5);
pLn[5]=(NCircle*) pC;
pLn[5]->pParent=this;
NoSegs[5]=2;
  pC=NFillet((NLine*) pLn[6],(NLine*) pLn[0],dR);
  MakeSpace(7);
  pLn[7]=(NCircle*) pC;
  pLn[7]->pParent=this;
  NoSegs[7]=2;
}


int Section::GetNoLines()
{
return(iLnCnt);
}

int Section::GetDivs(int iL)
{
return (NoSegs[iL]);
}


C3dVector Section::GetPt(int iSeg,int iPos)
{
C3dVector vRet;


double dw;
double dPos;
dPos=iPos;
dw=dPos/NoSegs[iSeg];
if (pLn[iSeg]->iObjType==8)
{
  dw*=0.25;
}

vRet=pLn[iSeg]->GetPt(dw);
return (vRet);
}

BOOL Section::isClosedSec()
{
BOOL brc = FALSE;
double dDist;
double dw=1;
C3dVector S;
C3dVector E;
S=pLn[0]->GetPt(0);
if (pLn[iLnCnt-1]->iObjType==8)
{
  dw*=0.25;
}
E=pLn[iLnCnt-1]->GetPt(dw);
dDist=S.Dist(E);
if (dDist<0.00001)
{
  brc=TRUE;
}
return (brc);
}

C3dVector Section::NLnInt(NCurve* L1,NCurve* L2)
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
while ((dDist>dTol) && (iMaxIt<100000));
return (P2);
}

//This is taken from DBase
NCircle* Section::NFillet(NLine* Ln,NLine* Ln1,double dR)
{
C3dVector PNear1;
C3dVector PNear2;
double R;
R=dR;
C3dVector p1;
C3dVector p2;
C3dVector p3;
C3dVector pT;
C3dVector vL1Dir;
C3dVector* pLT1;
C3dVector* pLT2;
C3dVector v1;
C3dVector v2;
C3dVector v3;
C3dVector vRef;
C3dVector vDir;
// The intersection of the lines



v1=Ln->GetDir(0.5);

v2=Ln1->GetDir(0.5);;
p1=Ln->GetPt(0);
pLT1=Ln->cPts[1]->Pt_Point;
p2=NLnInt(Ln,Ln1);
//p2=pLT1;
p3=Ln1->GetPt(1);
pLT2=Ln1->cPts[0]->Pt_Point;
C3dVector vn;
vn=v1.Cross(v2);
vn.Normalize();
C3dVector v1o;
C3dVector v2o;

v1o=v1.Cross(vn);
v2o=v2.Cross(vn);
v1o.Normalize();
v2o.Normalize();
v1o*=R;
v2o*=R;
if (v1o.Dot(v2)<0)
  v1o*=-1;
if (v2o.Dot(v1)>0)
  v2o*=-1;
C3dVector p1o;
C3dVector p2o;
C3dVector p3o;
C3dVector p4o;

p1o=p1;
p1o+=v1o;
p2o=p2;
p2o+=v1o;
p3o=p2;
p3o+=v2o;
p4o=p3;
p4o+=v2o;
NLine* Ln2 = new NLine;
Ln2->Create(p1o,p2o,1,NULL);
NLine* Ln3 = new NLine;
Ln3->Create(p3o,p4o,1,NULL);
C3dVector IntPt;
IntPt=NLnInt(Ln2,Ln3);


C3dVector IntPt1;
IntPt1=Ln->MinPt(IntPt);
vRef=IntPt1;
vRef-=IntPt;
vRef.Normalize();

NCircle* cCir = new NCircle();
cCir->Create2(vn,IntPt,vRef,R,-1,NULL);
cCir->vNorm=vn; // Note the transform method in Create2 changes the normal
                //so set it back 
pLT1->Set(IntPt1.x,IntPt1.y,IntPt1.z);  //trim the end point
C3dVector IntPt2;
IntPt2=Ln1->MinPt(IntPt);
pLT2->Set(IntPt2.x,IntPt2.y,IntPt2.z);  //trim the end point

//d1q=cCir->MinWPt(IntPt1);

//vRef=IntPt1;
//vDir=cCir->GetDir(d1q);
//vDir.Normalize();
//vRef-=cCir->vCent;
//vRef.Normalize();
  //if (vDir.Dot(vL1Dir)<0)
  //{
  //  vn*=-1;
  //}
  //delete (cCir);
  //cCir = new NCircle();
  //cCir->Create2(vn,IntPt,vRef,R,-1,NULL);
  //d1q=cCir->MinWPt(IntPt1);
double d2q;
d2q=cCir->MinWPt(IntPt2);
cCir->we=d2q;

delete (Ln2);
delete (Ln3);

return(cCir);
}

void Section::SetInPt(C3dVector Pt)
{
inPt = Pt;
}




IMPLEMENT_DYNAMIC( Sweep, CObject )

Sweep::Sweep()
{
pPath=NULL; 
pBaseSec=NULL;
Mesh=NULL;
iSecCnt=0;
Twist=0;
isVoid=FALSE;
pParent=NULL;
iMeshCnt = 0;
isStart=FALSE;
isEnd=FALSE;
iObjType = 603;
}

void Sweep::PreCreate(int iLab,CString inName,double dT)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_label = iLab;
G_Colour = 2;
iSecCnt=0;
Name=inName;
Twist=dT;
}

void Sweep::Create(int iLab,G_Object* inPath,
                   Section* inSec,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_label = iLab;
G_Colour = 2;
iSecCnt=0;
Mesh=NULL;
isVoid=FALSE;
pPath= inPath->Copy(this); 
pBaseSec=(Section*) inSec->Copy(this);
pPath->pParent=this;
pBaseSec->pParent=this;
pParent=Parrent;
}

void Sweep::Serialize(CArchive& ar)
{
  int i;
  int iTp;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
	  ar<<iMeshCnt;
    ar<<iSecCnt;
    ar<<Twist;
	  ar<<isVoid;
    ar << isStart;
    ar << isEnd;
    ar << dElLength;
    ar << pPath->iObjType;
    pPath->Serialize(ar); 
    pBaseSec->Serialize(ar); 
    for (i=0;i<iSecCnt;i++)
    {
      pAllSecs[i]->Serialize(ar); 
    }
	  int iISMesh=0;
	  if (Mesh!=NULL)
	  {
       iISMesh=1;
       ar<<iISMesh;
       Mesh->Serialize(ar);
	  }
	  else
    {
	     iISMesh=0;
       ar<<iISMesh;
	  }
	}
	else
	{
    G_Object::Serialize(ar);
	  ar>>iMeshCnt;
    ar>>iSecCnt;
    ar>>Twist;
    ar>>isVoid;
    ar >> isStart;
    ar >> isEnd;
    ar >> dElLength;
    ar >>iTp;
    if (iTp==9)
    {
      pPath=new NLine;
    }
    else if (iTp==7)
    {
      pPath= new NCurve;
    }
    else if (iTp==8)
    {
      pPath= new NCircle;
    }
    pPath->Serialize(ar);
	  pPath->pParent=this;
    pBaseSec=new Section;
    pBaseSec->Serialize(ar); 
    pBaseSec->pParent=this;
    for (i=0;i<iSecCnt;i++)
    {
      pAllSecs[i]=new Section;
      pAllSecs[i]->Serialize(ar); 
	    pAllSecs[i]->pParent=this;
    }
	  int iISMesh=0;
    ar>>iISMesh;
	  if (iISMesh==1)
	  {
	   Mesh = new ME_Object();
     Mesh->Serialize(ar);
	   Mesh->pParent=this;
	  }
	}
}

C3dVector Sweep::GetInPt()
{
C3dVector vRet;
return (vRet);
}

C3dVector Sweep::GetDir(double w)
{

C3dVector vN;
vN=pPath->GetDir(w);
return(vN);
}

C3dVector Sweep::MinPt(C3dVector inPt)
{
C3dVector vRet(0,0,0);
if (pPath!=NULL)
{
  vRet=pPath->GetPt(0.5);
}
return (vRet);
}

// Draw Object line
void Sweep::Draw(CDC* pDC,int iDrawmode)
{
int j=0;
if (iSecCnt != 0)
{
  for (j=0;j<iSecCnt;j++)
  {
    pAllSecs[j]->Draw(pDC,iDrawmode);
  }
}
if (pPath != NULL)
{
  pPath->Draw(pDC,iDrawmode);
}
if (Mesh!=NULL)
{
  Mesh->Draw(pDC,iDrawmode);
}
}

void Sweep::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
int j=0;
if (iSecCnt != 0)
{
for (j=0;j<iSecCnt;j++)
   {
   pAllSecs[j]->OglDrawW(iDspFlgs,dS1,dS2);
   }
}
if (pPath != NULL)
{
   pPath->OglDrawW(iDspFlgs,dS1,dS2);
}
if (Mesh!=NULL)
{
  Mesh->OglDrawW(iDspFlgs,dS1,dS2);
}
}

void Sweep::OglDraw(int iDspFlgs,double dS1,double dS2)
{

int j=0;
if (iSecCnt != 0)
{
for (j=0;j<iSecCnt;j++)
   {
   pAllSecs[j]->OglDraw(iDspFlgs,dS1,dS2);
   }
}
if (pPath != NULL)
{
   pPath->OglDraw(iDspFlgs,dS1,dS2);
}
if (Mesh!=NULL)
{
  Mesh->OglDraw(iDspFlgs,dS1,dS2);
}
}


void Sweep::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
int j=0;
if (iSecCnt != 0)
{
  for (j=0;j<iSecCnt;j++)
  {
    pAllSecs[j]->SetToScr(pModMat,pScrTran);
  }
}
if (pPath != NULL)
{
  pPath->SetToScr(pModMat,pScrTran);
}
if (Mesh!=NULL)
 {Mesh->SetToScr(pModMat,pScrTran);}

}

void Sweep::Transform(C3dMatrix inTMat)
{
int j=0;
if (iSecCnt != 0)
{
  for (j=0;j<iSecCnt;j++)
  {
    pAllSecs[j]->Transform(inTMat);
  }
}
if (pPath != NULL)
{
  pPath->Transform(inTMat);
}
}



C3dVector Sweep::Get_Centroid()
{
C3dVector vT;
if (pPath!=NULL)
{
  vT=pPath->Get_Centroid();
}
return (vT);
}


void Sweep::HighLight(CDC* pDC)
{
int j=0;
if (iSecCnt != 0)
{
  for (j=0;j<iSecCnt;j++)
  {
    pAllSecs[j]->Draw(pDC,4);
  }
}
if (pPath != NULL)
{
  pPath->Draw(pDC,4);
}
}


G_ObjectD Sweep::SelDist(CPoint InPT,Filter FIL)
{
G_ObjectD Ret;
double dS=10000;
if ((pPath!=NULL) && (Mesh==NULL))
{
  Ret=pPath->SelDist(InPT,FIL);
  Ret.pObj=this;
}
else if (Mesh!=NULL)
{
  Ret=Mesh->SelDist(InPT,FIL);
}
else
{
  Ret.pObj=this;
}
return (Ret);
}

void Sweep::S_Box(CPoint P1,CPoint P2,ObjList* pSel)
{
if (Mesh!=NULL)
{
  Mesh->S_Box(P1,P2,pSel);
}
} 

void Sweep::DeleteSections()
{
int i; 
for (i=0;i<iSecCnt;i++)
{	
  //pAllSecs[i]->~Section();
  delete(pAllSecs[i]);
}
iSecCnt=0;
}

double Sweep::GetSecSpacing()
{
double dRet=0;
C3dVector p1,p2;
if (iSecCnt>1)
{
  p1=pAllSecs[0]->GetPt(0,0);
  p2=pAllSecs[1]->GetPt(0,0);
  dRet=p1.Dist(p2);
}


return(dRet);
}


void Sweep::CutBack(BOOL bEA,BOOL bEB,ME_Object* MeshA,ME_Object* MeshB)
{
double cBW;
double dDist;
C3dVector pCPt;
C3dVector p1;
C3dVector vDirO;
C3dVector vDirN;
Pt_Object* pCN1;
Pt_Object* pCN2;
C3dMatrix mUp = GetFirstYMap();
NLine* pL;
pL = (NLine*) pPath;
vDirO=pL->GetDir(0);
double dD = GetSecSpacing();
DeleteSections();
double dLen=pL->getLen();
cBW=0.75*dD/dLen;
if ((MeshA!=NULL) && (bEA==TRUE))
{
  //Cutback nodes in standaard parts definition
  pCN1=MeshA->GetNode(1);
  pCN2=MeshA->GetNode(2);
  if (pCN1!=NULL)
  {
    pCPt=pCN1->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[0]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  } 
  if (pCN2!=NULL)
  {
    pCPt=pCN2->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[0]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  }
}
else if ((MeshA==NULL) && (bEA==TRUE))
{
  p1=pL->GetPt(cBW);
  pL->cPts[0]->Pt_Point->Set(p1.x,p1.y,p1.z);
}


if ((MeshB!=NULL) && (bEB==TRUE))
{
  //Cutback nodes in standaard parts definition
  pCN1=MeshB->GetNode(1);
  pCN2=MeshB->GetNode(2);
  if (pCN1!=NULL)
  {
    pCPt=pCN1->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[1]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  } 
  if (pCN2!=NULL)
  {
    pCPt=pCN2->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[1]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  }
}
else if ((MeshB==NULL) && (bEB==TRUE))
{
  p1=pL->GetPt(1-cBW);
  pL->cPts[1]->Pt_Point->Set(p1.x,p1.y,p1.z);
}
vDirN=pL->GetDir(0);
double dDot;
dDot=vDirO.Dot(vDirN);
if (dDot<0)
{
  isVoid=TRUE;
}
Generate(mUp,dElLength);
}



void Sweep::Generate(C3dMatrix mUp,double dElLen)
{
#ifdef _DEBUG
    CMemoryState oldMemState, newMemState, diffMemState;
#endif
dElLength=dElLen;
C3dVector Loc;
C3dVector Dir;
C3dMatrix TMat;
C3dMatrix OMat;
double dAng;
double dA=0;
int i;
int k=0;
double w;
double dInc;
double dRem;
int iSteps;
double dSteps;
double dLen;
#ifdef _DEBUG
   oldMemState.Checkpoint();
#endif 
if (isVoid==FALSE)
{
if (dElLen<=0)
{
  dElLen=0.005;
}
if ((pPath->iObjType == 7) || (pPath->iObjType == 8) || (pPath->iObjType == 9))
{  
  dLen=pPath->getLen();
  dSteps=dLen/dElLen;
  iSteps=(int) dSteps;
  
  dRem=dSteps-iSteps;

  if (iSteps==0)
  {
	iSteps=1;    
  }
  if (dRem>0.5)
  {
	iSteps+=1;
  }

  dSteps=(double) iSteps;
  dInc=1/dSteps;
  
  w=0;
  for (i=0;i<iSteps+1;i++)
  {
    Dir = pPath->GetDir(w);
    TMat=TMat.CalcTran(Dir);
    Loc = pPath->GetPt(w);
    //Calculate the sections
    //orientation
    if (i>0)
    {
      //Get last sections orientation
      mUp = GetLastYMap();
	    dA=Twist/iSteps;
    }
    dAng=TMat.GetZRot(mUp);
	  dAng+=dA;
    OMat.MakeUnit();
    OMat.Rotate(0,0,dAng);
    TMat=TMat*OMat;
    TMat.Translate2(Loc.x,Loc.y,Loc.z);
    pAllSecs[iSecCnt] = (Section*) pBaseSec->Copy(this);
    pAllSecs[iSecCnt]->SetInPt(Loc);
    pAllSecs[iSecCnt]->Transform(TMat);

    iSecCnt++;
    w+=dInc;
	if (w>1)
	{w=1;}
  }
}
//DeleteSections();

#ifdef _DEBUG
   newMemState.Checkpoint();
   if( diffMemState.Difference( oldMemState, newMemState ) )
      {
        TRACE( "Memory leaked!\n" );
        diffMemState.DumpStatistics();
      }

#endif 
}
}

void Sweep::GenMesh(int iDim,PSHELL* pS,PBARL* pB)
{
int i;
int j;
int k;
Pt_Object* S1[500][100];
Pt_Object* E1[2000];
Pt_Object* pNd;
C3dVector Nd;
int iCnt1=0;
int iNlab=1;
int iPID;
int iSecT;
int iCol;
BOOL isClosed=FALSE;
Property* Prop;
E_Object* pE;
if (isVoid==FALSE)
{
if (pAllSecs[0]!= NULL)
{
  isClosed=pAllSecs[0]->isClosedSec();
  if (iDim==1) 
  {
	  Prop=pB;
    iPID=pBaseSec->iPID2;
  }
  else
  {
    Prop=pS;
    iPID=pBaseSec->iPID;
  }
  iSecT=pBaseSec->iSec;
  iCol=pBaseSec->G_Colour;
}
if (this->pPath->getLen()>0.000001)
{
if (iDim==2)
{
  Mesh=new ME_Object();
  Mesh->Create("",this,iMeshCnt);
  for (i=0;i<iSecCnt;i++)
  {
    iCnt1=0;
	for (j=0;j<pAllSecs[i]->GetNoLines();j++)
	{
    for(k=0;k<pAllSecs[i]->GetDivs(j);k++)
	  {
      Nd=pAllSecs[i]->GetPt(j,k);
      pNd=Mesh->AddNode(Nd,iNlab,0,0,11,0,0);
      iNlab++;
      S1[i][iCnt1]=pNd;
      iCnt1++;
      if ((j==pAllSecs[i]->GetNoLines()-1) &&
	       (k==pAllSecs[i]->GetDivs(j)-1))
      {
        if (isClosed==FALSE)
	      {
          Nd=pAllSecs[i]->GetPt(j,pAllSecs[i]->GetDivs(j));
          pNd=Mesh->AddNode(Nd,iNlab,0,0,11,0,0);
	        iNlab++;
          S1[i][iCnt1]=pNd;
          iCnt1++;
	      }
	      else
	      {
          S1[i][iCnt1]=S1[i][0];
          iCnt1++;
	      }
      }
	  }
	}
  }
  int iECnt=1;
  for(i=0;i<iSecCnt-1;i++)
  {
    for (j=0;j<iCnt1-1;j++)
    {
      E1[0]=S1[i+1][j];
      E1[1]=S1[i][j];
      E1[2]=S1[i][j+1];
      E1[3]=S1[i+1][j+1];
      pE= Mesh->AddEl(E1,iECnt,152,94,Prop->iID,1,4,0,0,1,FALSE,-1,0);
      pE->PIDunv=iPID;
      pE->pPr=Prop;
      iECnt++;
    }
  }
}
else if (iDim==1)
{
  Mesh=new ME_Object();
  Mesh->Create("",this,iMeshCnt);
  for (i=0;i<iSecCnt;i++)
  {
    Nd=pAllSecs[i]->inPt;
	  pNd=Mesh->AddNode(Nd,i+1,0,0,11,0,0);
	  iNlab++;
	  S1[i][0]=pNd;
  }
  for(i=0;i<iSecCnt-1;i++)
  {
    E1[0]=S1[i][0];
	  E1[1]=S1[i+1][0];
    pE= Mesh->AddEl(E1,i+1,152,21,Prop->iID,1,2,0,1,1,FALSE,-1,0);
    pE->pPr=Prop;
    pE->PIDunv=iPID;
	  E_Object2* pE1 =(E_Object2*) pE;
    C3dVector vv;
    vv=pAllSecs[i]->TMat.GetUpVec();
	  pE1->SetUpVec(vv);
    pE1->B=iSecT;
    pE1->C=iSecT;
  }
}
}
if (iDim==1)
{
  S1[0][0]->G_Colour=160;
  S1[iSecCnt-1][0]->G_Colour=160;
}
else if (iDim==2)
{
 for (j=0;j<iCnt1-1;j++)
 {
   S1[0][j]->G_Colour=160;
 }
 for (j=0;j<iCnt1-1;j++)
 {
   S1[iSecCnt-1][j]->G_Colour=160;
 }
}
}
}

ME_Object*  Sweep::GetMesh()
{
return (Mesh);
}

 C3dMatrix Sweep::GetLastYMap()
{
C3dMatrix mRet;
if (iSecCnt>0)
{
  mRet=pAllSecs[iSecCnt-1]->TMat;
}
return (mRet);
}

C3dMatrix Sweep::GetFirstYMap()
{
C3dMatrix mRet;
if (iSecCnt>0)
{
  mRet=pAllSecs[0]->TMat;
}
return (mRet);
}


IMPLEMENT_DYNAMIC(SweepF, CObject )

SweepF::SweepF()
{
Sweep::Sweep();
iObjType = 606;
pParent=NULL;
isStart=TRUE;
isEnd=TRUE;
}

void SweepF::PreCreate(int iLab,CString inName,double dT)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_label = iLab;
G_Colour = 2;
iSecCnt=0;
Name=inName;
Twist=dT;
}

void SweepF::Generate(C3dMatrix mUp,double dElLen,double dLenFR)
{
C3dVector Loc;
C3dVector Dir;
C3dMatrix TMat;
C3dMatrix OMat;
dElLength=dElLen;
double dAng;
double dA=0;
dFR=dLenFR;
int i;
int k=0;
double w;
double dInc;
double dRem;
int iSteps;
double dSteps;
double dLen;
double dS=0;
double dF=1;
if (isVoid==FALSE)
{
if (dElLen<=0)
{
  dElLen=0.005;
}
if (dLenFR<=0)
{
  dLenFR=0.001;
}
if ((pPath->iObjType == 7) || (pPath->iObjType == 8) || (pPath->iObjType == 9))
{  
  dLen=pPath->getLen();
  if (isStart==TRUE)
  {
    //dLen=dLen-dLenFR;
    dS=dLenFR/dLen;
  }
  if (isEnd==TRUE)
  {
    //dLen=dLen-dLenFR;
    dF=1-dLenFR/dLen;
  }
  dSteps=dLen/dElLen;
  iSteps=(int) dSteps;
  
  dRem=dSteps-iSteps;

  if (iSteps==0)
  {
	iSteps=1;    
  }
  if (dRem>0.5)
  {
	iSteps+=1;
  }

  dSteps=(double) iSteps;
  dInc=(dF-dS)/dSteps;
  
  if (isStart==TRUE)
  {
    Dir = pPath->GetDir(0);
    TMat=TMat.CalcTran(Dir);
    Loc = pPath->GetPt(0);
    dAng=TMat.GetZRot(mUp);
	  dAng+=dA;
    OMat.MakeUnit();
    OMat.Rotate(0,0,dAng);
    TMat=TMat*OMat;
    TMat.Translate2(Loc.x,Loc.y,Loc.z);
    pAllSecs[iSecCnt] = (Section*) pBaseSec->Copy(this);
    pAllSecs[iSecCnt]->ChangeCol(4);
    pAllSecs[iSecCnt]->SetInPt(Loc);
    pAllSecs[iSecCnt]->Transform(TMat);
    iSecCnt++;
  }

  w=dS;
  for (i=0;i<iSteps+1;i++)
  {
    Dir = pPath->GetDir(w);
    TMat=TMat.CalcTran(Dir);
    Loc = pPath->GetPt(w);
    //Calculate the sections
    //orientation
    if (i>0)
    {
      //Get last sections orientation
      mUp = GetLastYMap();
	    dA=Twist/iSteps;
    }
    dAng=TMat.GetZRot(mUp);
	  dAng+=dA;
    OMat.MakeUnit();
    OMat.Rotate(0,0,dAng);
    TMat=TMat*OMat;
    TMat.Translate2(Loc.x,Loc.y,Loc.z);
    pAllSecs[iSecCnt] = (Section*) pBaseSec->Copy(this);
    pAllSecs[iSecCnt]->ChangeCol(55);
    pAllSecs[iSecCnt]->SetInPt(Loc);
    pAllSecs[iSecCnt]->Transform(TMat);

    iSecCnt++;
    w+=dInc;
	  if (w>1)
	  {w=1;}
  }
}
if (isEnd==TRUE)
  {
    Dir = pPath->GetDir(1);
    TMat=TMat.CalcTran(Dir);
    Loc = pPath->GetPt(1);
    //Calculate the sections
    //orientation
    if (i>0)
    {
      //Get last sections orientation
      mUp = GetLastYMap();
	    dA=Twist/iSteps;
    }
    dAng=TMat.GetZRot(mUp);
	  dAng+=dA;
    OMat.MakeUnit();
    OMat.Rotate(0,0,dAng);
    TMat=TMat*OMat;
    TMat.Translate2(Loc.x,Loc.y,Loc.z);
    pAllSecs[iSecCnt] = (Section*) pBaseSec->Copy(this);
    pAllSecs[iSecCnt]->ChangeCol(4);
    pAllSecs[iSecCnt]->SetInPt(Loc);
    pAllSecs[iSecCnt]->Transform(TMat);
    iSecCnt++;
  }
}
}

void SweepF::CutBack(BOOL bEA,BOOL bEB,ME_Object* MeshA,ME_Object* MeshB)
{
double cBW;
double dDist;
C3dVector pCPt;
C3dVector p1;
C3dVector vDirO;
C3dVector vDirN;
Pt_Object* pCN1;
Pt_Object* pCN2;
C3dMatrix mUp = GetFirstYMap();
NLine* pL;
pL = (NLine*) pPath;
vDirO=pL->GetDir(0);
double dD = GetSecSpacing();
DeleteSections();
double dLen=pL->getLen();
cBW=0.75*dD/dLen;
if ((MeshA!=NULL) && (bEA==TRUE))
{
  //Cutback nodes in standaard parts definition
  pCN1=MeshA->GetNode(1);
  pCN2=MeshA->GetNode(2);
  if (pCN1!=NULL)
  {
    pCPt=pCN1->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[0]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  } 
  if (pCN2!=NULL)
  {
    pCPt=pCN2->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[0]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  }
}
else if ((MeshA==NULL) && (bEA==TRUE))
{
  p1=pL->GetPt(cBW);
  pL->cPts[0]->Pt_Point->Set(p1.x,p1.y,p1.z);
}


if ((MeshB!=NULL) && (bEB==TRUE))
{
  //Cutback nodes in standaard parts definition
  pCN1=MeshB->GetNode(1);
  pCN2=MeshB->GetNode(2);
  if (pCN1!=NULL)
  {
    pCPt=pCN1->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[1]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  } 
  if (pCN2!=NULL)
  {
    pCPt=pCN2->GetCoords();
	  dDist=pL->MinDist(pCPt);
	  if (dDist<0.001)
	  {
      pL->cPts[1]->Pt_Point->Set(pCPt.x,pCPt.y,pCPt.z);
	  }
  }
}
else if ((MeshB==NULL) && (bEB==TRUE))
{
  p1=pL->GetPt(1-cBW);
  pL->cPts[1]->Pt_Point->Set(p1.x,p1.y,p1.z);
}
vDirN=pL->GetDir(0);
double dDot;
dDot=vDirO.Dot(vDirN);
if (dDot<0)
{
  isVoid=TRUE;
}
Generate(mUp,dElLength,dFR);
}

BOOL isCorner(Pt_Object* P1,Pt_Object* P2,Pt_Object* P3,Pt_Object* P4)
{
BOOL brc = FALSE;
if ((P1->G_Colour==3) &&
    (P2->G_Colour==3) &&
    (P3->G_Colour==3) &&
    (P4->G_Colour==3))
{
  brc=TRUE;
}

return(brc);
}


void SweepF::GenMesh(int iDim,PSHELL* pS1,PSHELL* pS2
                             ,PSHELL* pS3,PSHELL* pS4
                             ,PBARL* pB1,PBARL* pB2)
{
int i;
int j;
int k;
Pt_Object* S1[500][100];
Pt_Object* E1[2000];
Pt_Object* pNd;
C3dVector Nd;
int iCnt1=0;
int iNlab=1;
int iPID;

int iCol;
BOOL isClosed=FALSE;
Property* Prop;
E_Object* pE;
if (isVoid==FALSE)
{
if (pAllSecs[0]!= NULL)
{
  isClosed=pAllSecs[0]->isClosedSec();
}

if (iDim==2)
{
  Mesh=new ME_Object();
  Mesh->Create("",this,iMeshCnt);

  for (i=0;i<iSecCnt;i++)
  {
  iCnt1=0;
	for (j=0;j<pAllSecs[i]->GetNoLines();j++)
	{
    int iNoD;
    iNoD=pAllSecs[i]->GetDivs(j);
    for(k=0;k<iNoD;k++)
	  {
      Nd=pAllSecs[i]->GetPt(j,k);
      if ((pAllSecs[i]->pLn[j]->iObjType==8) || (k==0))
      {
        pNd=Mesh->AddNode(Nd,iNlab,0,0,3,0,0);
      }
      else
      {
        pNd=Mesh->AddNode(Nd,iNlab,0,0,55,0,0);
      }
      iNlab++;
      S1[i][iCnt1]=pNd;
      iCnt1++;
      if ((j==pAllSecs[i]->GetNoLines()-1) &&
	       (k==pAllSecs[i]->GetDivs(j)-1))
      {
        if (isClosed==FALSE)
	      {
          Nd=pAllSecs[i]->GetPt(j,pAllSecs[i]->GetDivs(j));
          pNd=Mesh->AddNode(Nd,iNlab,0,0,11,0,0);
	        iNlab++;
          S1[i][iCnt1]=pNd;
          iCnt1++;
	      }
	      else
	      {
          S1[i][iCnt1]=S1[i][0];
          iCnt1++;
	      }
      }
	  }
	}
  }
  int iECnt=1;
  int iELCol;
  for(i=0;i<iSecCnt-1;i++)
  {

    for (j=0;j<iCnt1-1;j++)
    {
      E1[0]=S1[i+1][j];
      E1[1]=S1[i][j];
      E1[2]=S1[i][j+1];
      E1[3]=S1[i+1][j+1];
      
      if (((i==0) && (isStart==TRUE)) &&
          (isCorner(E1[0],E1[1],E1[2],E1[3])==FALSE))
      {
        iELCol=153;
        Prop=pS1;
        iPID=pS1->iID;
      }
      else if (((i==iSecCnt-2) && (isEnd==TRUE)) &&
              (isCorner(E1[0],E1[1],E1[2],E1[3])==FALSE))
      {
        iELCol=153;
        Prop=pS1;
        iPID=pS1->iID;
      }
      else if (((i==0) && (isStart==TRUE)) &&
          (isCorner(E1[0],E1[1],E1[2],E1[3])==TRUE))
      {
        iELCol=162;
        Prop=pS2;
        iPID=pS2->iID;
      }
      else if (((i==iSecCnt-2) && (isEnd==TRUE)) &&
          (isCorner(E1[0],E1[1],E1[2],E1[3])==TRUE))
      {
        iELCol=162;
        Prop=pS2;
        iPID=pS2->iID;
      }
      else if (isCorner(E1[0],E1[1],E1[2],E1[3])==TRUE)
      {
         iELCol=3;
         Prop=pS4;
         iPID=pS4->iID;
      }
      else
      {
         iELCol=55;
         Prop=pS3;
         iPID=pS3->iID;
      }
      pE= Mesh->AddEl(E1,iECnt,iELCol,94,iPID,1,4,0,0,1,FALSE,-1,0);
      pE->PIDunv=iPID;
      pE->pPr=Prop;
      iECnt++;
    }
  }
}
else if (iDim==1)
{
  Mesh=new ME_Object();
  Mesh->Create("",this,iMeshCnt);
  for (i=0;i<iSecCnt;i++)
  {
    Nd=pAllSecs[i]->inPt;
	  pNd=Mesh->AddNode(Nd,i+1,0,0,11,0,0);
	  iNlab++;
	  S1[i][0]=pNd;
  }
    int iELCol;
  for(i=0;i<iSecCnt-1;i++)
  {
    E1[0]=S1[i][0];
	  E1[1]=S1[i+1][0];
      if ((i==0) && (isStart==TRUE))
      {
        iELCol=153;
        Prop=pB1;
        iPID=pB1->iID;
      }
      else if ((i==iSecCnt-2) && (isEnd==TRUE)) 
      {
        iELCol=153;
        Prop=pB1;
        iPID=pB1->iID;
      }
      else
      {
        iELCol=55;
        Prop=pB2;
        iPID=pB2->iID;
      }
    pE= Mesh->AddEl(E1,i+1,iELCol,21,iPID,1,2,0,1,1,FALSE,-1,0);
    pE->pPr=Prop;
    pE->PIDunv=iPID;
	  E_Object2* pE1 =(E_Object2*) pE;
    C3dVector vv;
    vv=pAllSecs[i]->TMat.GetUpVec();
    if (vv.Mag()==0)
    {
      int ff;
      ff++;
    }
	  pE1->SetUpVec(vv);
  }
}
}
  for (i=0;i<iSecCnt;i++)
  {
    Nd=pAllSecs[i]->inPt;
	  pNd=Mesh->AddNode(Nd,i+1,0,0,11,0,0);
	  iNlab++;
	  S1[i][0]=pNd;
  }
if (iDim==1)
{
  S1[0][0]->G_Colour=160;
  S1[iSecCnt-1][0]->G_Colour=160;
}
else if (iDim==2)
{
 for (j=0;j<iCnt1-1;j++)
 {
   S1[0][j]->G_Colour=160;
 }
 for (j=0;j<iCnt1-1;j++)
 {
   S1[iSecCnt-1][j]->G_Colour=160;
 }
}
}


IMPLEMENT_DYNAMIC(SweepFB, CObject )

SweepFB::SweepFB()
{
SweepB::SweepB();
iObjType = 607;
pParent=NULL;
}

void SweepFB::PreCreate(int iLab,CString inName,
					   C3dVector inP,double dR,int EH,double dT)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_label = iLab;
G_Colour = 2;
iSecCnt=0;
Name=inName;
dRad=dR;
Twist=dT;
if (inPt!=NULL)
  {delete(inPt);}
inPt=new CvPt_Object;
inPt->Create(inP,0,-1,0,0,11,this);
isHBend=EH;
}

void SweepFB::GenMesh(int iDim,PSHELL* pS1,PSHELL* pS2
                             ,PSHELL* pS3,PSHELL* pS4
                             ,PBARL* pB1,PBARL* pB2)
{
int i;
int j;
int k;
Pt_Object* S1[500][100];
Pt_Object* E1[2000];
Pt_Object* pNd;
C3dVector Nd;
int iCnt1=0;
int iNlab=1;
int iPID;

int iCol;
BOOL isClosed=FALSE;
Property* Prop;
E_Object* pE;
if (isVoid==FALSE)
{
if (pAllSecs[0]!= NULL)
{
  isClosed=pAllSecs[0]->isClosedSec();
}

if (iDim==2)
{
  Mesh=new ME_Object();
  Mesh->Create("",this,iMeshCnt);

  for (i=0;i<iSecCnt;i++)
  {
  iCnt1=0;
	for (j=0;j<pAllSecs[i]->GetNoLines();j++)
	{
    int iNoD;
    iNoD=pAllSecs[i]->GetDivs(j);
    for(k=0;k<iNoD;k++)
	  {
      Nd=pAllSecs[i]->GetPt(j,k);
      if ((pAllSecs[i]->pLn[j]->iObjType==8) || (k==0))
      {
        pNd=Mesh->AddNode(Nd,iNlab,0,0,3,0,0);
      }
      else
      {
        pNd=Mesh->AddNode(Nd,iNlab,0,0,55,0,0);
      }
      iNlab++;
      S1[i][iCnt1]=pNd;
      iCnt1++;
      if ((j==pAllSecs[i]->GetNoLines()-1) &&
	       (k==pAllSecs[i]->GetDivs(j)-1))
      {
        if (isClosed==FALSE)
	      {
          Nd=pAllSecs[i]->GetPt(j,pAllSecs[i]->GetDivs(j));
          pNd=Mesh->AddNode(Nd,iNlab,0,0,11,0,0);
	        iNlab++;
          S1[i][iCnt1]=pNd;
          iCnt1++;
	      }
	      else
	      {
          S1[i][iCnt1]=S1[i][0];
          iCnt1++;
	      }
      }
	  }
	}
  }
  int iECnt=1;
  int iELCol;
  for(i=0;i<iSecCnt-1;i++)
  {

    for (j=0;j<iCnt1-1;j++)
    {
      
      E1[0]=S1[i+1][j];
      E1[1]=S1[i][j];
      E1[2]=S1[i][j+1];
      E1[3]=S1[i+1][j+1];
      if (isCorner(E1[0],E1[1],E1[2],E1[3])==TRUE)
      {
         iELCol=3;
         Prop=pS4;
         iPID=pS4->iID;
      }
      else
      {
         iELCol=55;
         Prop=pS3;
         iPID=pS3->iID;
      }
      pE= Mesh->AddEl(E1,iECnt,iELCol,94,iPID,1,4,0,0,1,FALSE,-1,0);
      pE->PIDunv=iPID;
      pE->pPr=Prop;
      iECnt++;
    }
  }
}
else if (iDim==1)
{
  Mesh=new ME_Object();
  Mesh->Create("",this,iMeshCnt);
  for (i=0;i<iSecCnt;i++)
  {
    Nd=pAllSecs[i]->inPt;
	  pNd=Mesh->AddNode(Nd,i+1,0,0,11,0,0);
	  iNlab++;
	  S1[i][0]=pNd;
  }
    int iELCol;
  for(i=0;i<iSecCnt-1;i++)
  {
    E1[0]=S1[i][0];
	  E1[1]=S1[i+1][0];

        iELCol=55;
        Prop=pB2;
        iPID=pB2->iID;

    pE= Mesh->AddEl(E1,i+1,iELCol,21,iPID,1,2,0,1,1,FALSE,-1,0);
    pE->pPr=Prop;
    pE->PIDunv=iPID;
	  E_Object2* pE1 =(E_Object2*) pE;
    C3dVector vv;
    vv=pAllSecs[i]->TMat.GetUpVec();
	  pE1->SetUpVec(vv);
  }
}
}
if (iDim==1)
{
  S1[0][0]->G_Colour=160;
  S1[iSecCnt-1][0]->G_Colour=160;
}
else if (iDim==2)
{
 for (j=0;j<iCnt1-1;j++)
 {
   S1[0][j]->G_Colour=160;
 }
 for (j=0;j<iCnt1-1;j++)
 {
   S1[iSecCnt-1][j]->G_Colour=160;
 }
}
}


IMPLEMENT_DYNAMIC(SweepB, CObject )

SweepB::SweepB()
{
Sweep::Sweep();
iObjType = 604;
dRad=0;
isHBend=0;
inPt=NULL;
pParent=NULL;
}

void SweepB::Create(int iLab,NCurve* inPath,
                   Section* inSec,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_label = iLab;
G_Colour = 2;
iSecCnt=0;
pPath=(NCurve*) inPath->Copy(this); 
pBaseSec=(Section*) inSec->Copy(this);
pPath->pParent =this;
pBaseSec->pParent =this;
pParent=Parrent;
}

void SweepB::PreCreate(int iLab,CString inName,
					   C3dVector inP,double dR,int EH,double dT)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 604;
G_label = iLab;
G_Colour = 2;
iSecCnt=0;
Name=inName;
dRad=dR;
Twist=dT;
if (inPt!=NULL)
  {delete(inPt);}
inPt=new CvPt_Object;
inPt->Create(inP,0,-1,0,0,11,this);
isHBend=EH;
}

void SweepB::Serialize(CArchive& ar)
{
Sweep::Serialize(ar);
if (ar.IsStoring())
  {
	ar<<dRad;
	ar<<isHBend;
	inPt->Serialize(ar);
  } 
  else
  {
	ar>>dRad;
	ar>>isHBend;
	inPt=new CvPt_Object;
	inPt->Serialize(ar);
  }
}
// Draw Object line
void SweepB::Draw(CDC* pDC,int iDrawmode)
{
Sweep::Draw(pDC,iDrawmode);
inPt->Draw(pDC,iDrawmode);
}


void SweepB::OglDraw(int iDspFlgs,double dS1,double dS2)
{
Sweep::OglDraw(iDspFlgs,dS1,dS2);
inPt->OglDraw(iDspFlgs,dS1,dS2);
}


void SweepB::Generate(C3dMatrix mUp,double dElLen)
{
C3dVector Loc;
C3dVector Dir;
C3dMatrix TMat;
C3dMatrix TMat2;
C3dMatrix OMat;
dElLength=dElLen;
double dAng;
double dS;
double dE;
double dInc;
NCurve* C=(NCurve*) pPath;
dS=C->ws;
dE=C->we;

int i;
double w;
int iSteps;
double dDegStep=dElLen; //10degrees
double dT;
double dRem;
dT=((dE-dS))*360/dDegStep;
iSteps=(int) dT;
dRem=dT-iSteps;
if (dRem>0)
{
  iSteps+=1;
}
if (iSteps==0)
{
  iSteps=1;
}
dInc = (dE-dS)/iSteps;
if ((pPath->iObjType == 7) || (pPath->iObjType == 8) || (pPath->iObjType == 9))
{  
  w=dS;
  for (i=0;i<iSteps+1;i++)
  {
    //Twist
    //TMat2.Rotate(0,0,5);
    Dir = pPath->GetDir(w);
    TMat=TMat.CalcTran(Dir);
    Loc = pPath->GetPt(w);
    //Calculate the sections
    //orientation
    if (i>0)
    {
      //Get last sections orientation
      mUp = GetLastYMap();
    }
    dAng=TMat.GetZRot(mUp);
    OMat.MakeUnit();
    OMat.Rotate(0,0,dAng);
    TMat=TMat*OMat;
    TMat.Translate2(Loc.x,Loc.y,Loc.z);
    pAllSecs[iSecCnt] = (Section*) pBaseSec->Copy(this);
    //pAllSecs[iSecCnt]->Transform(TMat2);
    //pAllSecs[iSecCnt]->Transform(OMat);
	  pAllSecs[iSecCnt]->SetInPt(Loc);
    pAllSecs[iSecCnt]->Transform(TMat);
    iSecCnt++;
    w+=dInc;
  }
}
}


void SweepB::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
Sweep::SetToScr(pModMat, pScrTran);
inPt->SetToScr(pModMat, pScrTran);
}

void SweepB::Transform(C3dMatrix inTMat)
{
Sweep::Transform(inTMat);
inPt->Transform(inTMat);
}


C3dVector SweepB::GetNVec()
{
C3dVector vN;
NCircle* C =(NCircle*) pPath;
vN.x=C->vNorm.x;
vN.y=C->vNorm.y;
vN.z=C->vNorm.z;
return(vN);
}

C3dVector SweepB::GetSVec()
{
C3dVector vN;
NCircle* C =(NCircle*) pPath;
vN=C->GetDir(0);
vN.Normalize();
return(vN);
}

C3dVector SweepB:: GetInPt()
{
C3dVector vR;
vR.x=inPt->Pt_Point->x;
vR.y=inPt->Pt_Point->y;
vR.z=inPt->Pt_Point->z;
return (vR);
}

 IMPLEMENT_DYNAMIC( PartsCat, CObject )




 //int iNo;
 //int iCurDsp;
 //ME_Object* P_Obj[100];
 
PartsCat::PartsCat(int iLab)
{
G_label = iLab;
iNo = 0;
iCurDsp = -1;
}



PartsCat::~PartsCat()
{
int i;
for(i=0;i<iNo;i++)
{
  delete(P_Obj[i]);
}
}

void PartsCat::Create(int iLab)
{
G_label = iLab;
iNo = 0;
iCurDsp = -1;
}




void PartsCat::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{

	}
}


void PartsCat::Info()
{
  char S1[80];
  CString OutT;
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  OutT+=S1;
  outtext1("PARTS CAT");
  outtext1(OutT); 
  outtext1("    ****");
}

void PartsCat::Draw(CDC* pDC,int iDrawmode)
{
if ((iCurDsp >= 0) && (iCurDsp<iNo))
{
  if (P_Obj[iCurDsp]!= NULL)
  {
    P_Obj[iCurDsp]->Draw(pDC,iDrawmode);
	pDC->TextOut(20,20,P_Obj[iCurDsp]->Name);
  }
}
}

void PartsCat::OglDraw(int iDspFlgs,double dS1,double dS2)
{
char sLab[200];
C3dVector pCent;
if ((iCurDsp >= 0) && (iCurDsp<iNo))
{
  if (P_Obj[iCurDsp]!= NULL)
  {
    sprintf_s(sLab,"%s",P_Obj[iCurDsp]->Name);
    pCent=P_Obj[iCurDsp]->Get_Centroid();
	  OglString(iDspFlgs,pCent.x,pCent.y,pCent.z,&sLab[0]);
    P_Obj[iCurDsp]->OglDraw(iDspFlgs,dS1,dS2);
  }
}
}

void PartsCat::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[200];
C3dVector pCent;
if ((iCurDsp >= 0) && (iCurDsp<iNo))
{
  if (P_Obj[iCurDsp]!= NULL)
  {
    sprintf_s(sLab,"%s",P_Obj[iCurDsp]->Name);
    pCent=P_Obj[iCurDsp]->Get_Centroid();
	  OglString(iDspFlgs,pCent.x,pCent.y,pCent.z,&sLab[0]);
    P_Obj[iCurDsp]->OglDrawW(iDspFlgs,dS1,dS2);
  }
}
}

void PartsCat::HighLight(CDC* pDC)
{
if ((iCurDsp >= 0) && (iCurDsp<iNo))
{
  if (P_Obj[iCurDsp]!= NULL)
  {
    P_Obj[iCurDsp]->HighLight(pDC);
  }
}
}

void PartsCat::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
if ((iCurDsp >= 0) && (iCurDsp<iNo))
{
  if (P_Obj[iCurDsp]!= NULL)
  {
    P_Obj[iCurDsp]->SetToScr(pModMat,pScrTran);
  }
}
}

void PartsCat::Next()
{
if (iCurDsp<iNo-1) 
{
  iCurDsp++;
}
}

void PartsCat::Previous()
{
if (iCurDsp>0) 
{
  iCurDsp--;
}
}


void PartsCat::Transform(C3dMatrix TMat)
{

}

G_ObjectD PartsCat::SelDist(CPoint InPT,Filter FIL)
{
double d;
G_Object* pO;
G_ObjectD Ret;
d=1e36;
pO=this;
pO->pParent=NULL;
Ret.Dist=d;
Ret.pObj=pO;
return (Ret);
}


void PartsCat::Add(ME_Object* inMesh)
{
if (iNo < MaxPrtNo)
{
  P_Obj[iNo]=inMesh;
  iNo++;
  iCurDsp=0;
}
}

ME_Object* PartsCat::Get(CString inName)
{
ME_Object* pRet;
pRet=NULL;
int i;
for (i=0;i<iNo;i++)
{
  if (P_Obj[i]->Name==inName)
  {
    pRet=(ME_Object*) P_Obj[i]->Copy(this);
    break;
  }
}

return (pRet);
}

ME_Object* PartsCat::GetCur()
{
ME_Object* pRet;
pRet=NULL;
if (iCurDsp!=-1)
{
  pRet=(ME_Object*) P_Obj[iCurDsp]->Copy(this);
  pRet->pParent=NULL;
}
return (pRet);
}


IMPLEMENT_DYNAMIC( pRecord, CObject )

 
pRecord::pRecord(int iIndex,int iType)
{
iT=iType;
iID=iIndex;
iCnt=0;
}

pRecord::~pRecord()
{
int i;
for(i=0;i<iCnt;i++)
{
  delete(propVals[i]);
}
}

void pRecord::Serialize(CArchive& ar)
{
int i;
if (ar.IsStoring())
{
  ar<<iID;
  ar<<iT;
  ar<<iCnt;
  for (i=0;i<iCnt;i++)
  {
   propVals[i]->Serialize(ar);
  }    
}
else
{
  ar>>iID;
  ar>>iT;
  ar>>iCnt;
  for (i=0;i<iCnt;i++)
  {
	if (iT==1)
	{
      propVals[i]= new piVal;
	}
	else if (iT==2)
	{
      propVals[i]= new pdVal;
	}
	else if (iT==3)
	{
      propVals[i]= new psVal;
	}
    propVals[i]->Serialize(ar);
  }  
}
}


void pRecord::Add(pVal* inP)
{
if (iCnt<50)
{
  propVals[iCnt]= inP;
  iCnt++;
}
}




IMPLEMENT_DYNAMIC( pVal, CObject )

void pVal::Serialize(CArchive& ar)
{
if (ar.IsStoring())
{
     
}
else
{
 
}
}


IMPLEMENT_DYNAMIC( piVal, CObject )

void piVal::Serialize(CArchive& ar)
{
if (ar.IsStoring())
{
    ar<<iVal; 
}
else
{
    ar>>iVal; 
}
}

IMPLEMENT_DYNAMIC( pdVal, CObject )

void pdVal::Serialize(CArchive& ar)
{
if (ar.IsStoring())
{
    ar<<dVal; 
}
else
{
     ar>>dVal; 
}
}


IMPLEMENT_DYNAMIC( psVal, CObject )

void psVal::Serialize(CArchive& ar)
{
if (ar.IsStoring())
{
    ar<<sVal; 
}
else
{
     ar>>sVal; 
}
}



IMPLEMENT_DYNAMIC( Prop, CObject )



Prop::Prop(int inD,int inT,
		int inN,int inP,CString inName)
{
iCnt=0;
iD=inD;
iT=inT;
iN=inN;
iP=inP;
Name=inName;
}

Prop::Prop()
{
iCnt=0;
iD=-1;
iT=-1;
iN=-1;
iP=-1;
Name="ROYBLOWS";
}

Prop::~Prop()
{
int i;
for (i=0;i<iCnt;i++)
{
  delete(pRecs[i]);
}
}


void Prop::Serialize(CArchive& ar)
{
int i;
if (ar.IsStoring())
{
	ar<<iCnt;
	ar<<iD;
	ar<<iT;
	ar<<iN;
	ar<<iP;
	ar<<Name;
}
else
{
	ar>>iCnt;
	ar>>iD;
	ar>>iT;
	ar>>iN;
	ar>>iP;
	ar>>Name;
}
for (i=0;i<iCnt;i++)
{
  pRecs[i]->Serialize(ar);
}
}


void Prop::Add(pRecord* inRec)
{
if (iCnt<MaxRec)
{
  pRecs[iCnt]=inRec;
  iCnt++;
}
}



IMPLEMENT_DYNAMIC(Entity , CObject )

Entity::Entity()
{
sTitle="";
iID = -1;
iType= -1;
}

void Entity::Create(CString inTitle,
                      int inPid,
                      int inType)
{
sTitle=inTitle;
iID = inPid;
iType= inType;
}

void Entity::List()
{
  char S1[200];
  CString OutT;
  sprintf_s(S1,"%s %i %s %i","ID",iID,"TYPE",iType);
  OutT=S1;
  outtext1(OutT); 
}

void Entity::ListShort()
{
  char S1[200];
  CString OutT;
  sprintf_s(S1,"%s %i %s %i","ID",iID,"TYPE",iType);
  OutT=S1;
  outtext1(OutT); 
}

void Entity::ExportNAS(FILE* pFile)
{
}

Entity* Entity::Copy()
{
Entity* pREt=new Entity();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
return (pREt);
}


void Entity::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar<<iType;
    ar<<sTitle;
    ar<<iID;
  }
  else
  {
    ar>>iType;
    ar>>sTitle;
    ar>>iID;
  }
}

IMPLEMENT_DYNAMIC(Property , CObject )

BOOL Property::HasMat(int inMID)
{
return (FALSE);
}

double Property::GetThk()
{
return(0);
}

BSec* Property::GetSec()
{
return(NULL);
}

void Property::UpdateMats(NEList* newMats)
{
}

int Property::GetDefMatID()
{
  return (-1);
}

void Property::ChangeMat(int thisMat,int inMID)
{
}

// MAT
IMPLEMENT_DYNAMIC(Material , CObject )




IMPLEMENT_DYNAMIC(PSOLID , CObject)

PSOLID::PSOLID()
{
sTitle="";
iID = -1;
iType= 3;
iMID=-1;
iCORDM=-1;
sIN="TWO     ";
sSTRESS="GRID    ";
sISOP="REDUCED ";
sFCTN="        ";
}

void PSOLID::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar << iType;
    ar << sTitle;
    ar << iID;
    ar << iMID;
    ar << iCORDM;
    ar << sIN;
    ar << sSTRESS;
    ar << sISOP;
    ar << sFCTN;
  }
  else
  {
    ar >> iType;
    ar >> sTitle;
    ar >> iID;
    ar >> iMID;
    ar >> iCORDM;
    ar >> sIN;
    ar >> sSTRESS;
    ar >> sISOP;
    ar >> sFCTN;
  }
}

BOOL PSOLID::HasMat(int inMID)
{
  BOOL brc=FALSE;
  if (iMID==inMID)
  {
    brc=TRUE;
  }
  return (brc);
}

void PSOLID::UpdateMats(NEList* newMats)
{
 iMID=newMats->Get(iMID);
}

void PSOLID::ChangeMat(int thisMat,int inMID)
{
if (iMID==thisMat)
 iMID=inMID;
}

int PSOLID::GetDefMatID()
{
return (iMID);
}

void PSOLID::ExportNAS(FILE* pFile)
{
fprintf(pFile,"$%s\n",sTitle);
fprintf(pFile,"%8s%8i%8i%8i%8s%8s%8s%8s\n","PSOLID  ",iID,iMID,iCORDM,sIN,sSTRESS,sISOP,sFCTN);
}

PSOLID* PSOLID::Copy()
{
PSOLID* pREt=new PSOLID();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
pREt->iMID=iMID;
pREt->iCORDM=iCORDM;
pREt->sIN=sIN;
pREt->sSTRESS=sSTRESS;
pREt->sISOP=sISOP;
pREt->sFCTN=sFCTN;
return (pREt);
}
//

IMPLEMENT_DYNAMIC(PBAR , CObject)

PBAR::PBAR()
{
sTitle="";
iID = -1;
iType= 4;
iMID=-1;
dA=0;
dI1=0;
dI2=0;
dJ=0;
dNSM=0;
dC1=0;
dC2=0;
dD1=0;
dD2=0;
dE1=0;
dE2=0;
dF1=0;
dF2=0;
dK1=0;
dK2=0;
dI12=0;
DspSec.Clear();
}

void PBAR::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar << iType;
    ar << sTitle;
    ar << iID;
    ar << iMID;

    ar << dA;
    ar << dI1;
    ar << dI2;
    ar << dJ;
    ar << dNSM;
    ar << dC1;
    ar << dC2;
    ar << dD1;
    ar << dD2;
    ar << dE1;
    ar << dE2;
    ar << dF1;
    ar << dF2;
    ar << dK1;
    ar << dK2;
    ar << dI12;
    DspSec.Serialize(ar);
  }
  else
  {
    ar >> iType;
    ar >> sTitle;
    ar >> iID;
    ar >> iMID;

    ar >> dA;
    ar >> dI1;
    ar >> dI2;
    ar >> dJ;
    ar >> dNSM;
    ar >> dC1;
    ar >> dC2;
    ar >> dD1;
    ar >> dD2;
    ar >> dE1;
    ar >> dE2;
    ar >> dF1;
    ar >> dF2;
    ar >> dK1;
    ar >> dK2;
    ar >> dI12;
    DspSec.Serialize(ar);
  }
}

void PBAR::UpdateMats(NEList* newMats)
{
iMID=newMats->Get(iMID);
}

void PBAR::ChangeMat(int thisMat,int inMID)
{
if (iMID==thisMat)
  iMID=inMID;
}

void PBAR::CreateSec()
{
double dSize;
if (dA>0)
{
  dSize=sqrt(dA);
}
else
{
  dSize=0.01;
}
DspSec.CreateDefSec(dSize/2,55);
}

BOOL PBAR::HasMat(int inMID)
{
  BOOL brc=FALSE;
  if (iMID==inMID)
  {
    brc=TRUE;
  }
  return (brc);
}

void PBAR::ExportNAS(FILE* pFile)
{
fprintf(pFile,"$%s\n",sTitle);
fprintf(pFile,"%-8s%8i%8i%8s%8s%8s%8s%8s\n","PBAR    ",iID,iMID,e8(dA),e8(dI1),e8(dI2),e8(dJ),e8(dNSM));
fprintf(pFile,"%-8s%8s%8s%8s%8s%8s%8s%8s%8s\n","        ",e8(dC1),e8(dC2),e8(dD1),e8(dD2),e8(dE1),e8(dE2),e8(dF1),e8(dF2));
fprintf(pFile,"%-8s%8s%8s%8s\n","        ",e8(dK1),e8(dK2),e8(dI12));

}

PBAR* PBAR::Copy()
{
int  i;
PBAR* pREt=new PBAR();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
pREt->iMID=iMID;

pREt->dA=dA;
pREt->dI1=dI1;
pREt->dI2=dI2;
pREt->dJ=dJ;
pREt->dNSM=dNSM;
pREt->dC1=dC1;
pREt->dC2=dC2;
pREt->dD1=dD1;
pREt->dD2=dD2;
pREt->dE1=dE1;
pREt->dE2=dE2;
pREt->dF1=dF1;
pREt->dF2=dF2;
pREt->dK1=dK1;
pREt->dK2=dK2;
pREt->dI12=dI12;
pREt->DspSec.iLnCnt1=DspSec.iLnCnt1;
pREt->DspSec.iLnCnt2=DspSec.iLnCnt2;
for (i=0;i<DspSec.iLnCnt1;i++)
{
  pREt->DspSec.pLnLoop1[i] = DspSec.pLnLoop1[i];
}
for (i=0;i<DspSec.iLnCnt2;i++)
{
  pREt->DspSec.pLnLoop2[i] = DspSec.pLnLoop2[i];
}
return (pREt);
}

BSec* PBAR::GetSec()
{
return (&DspSec);
}


IMPLEMENT_DYNAMIC(PBEAM , CObject)

PBEAM::PBEAM()
{
sTitle="";
iID = -1;
iType= 6;
iMID=-1;

iNo=1;
A[0]=0.0001;

K1=DBL_MAX;
K2=DBL_MAX;
S1=DBL_MAX;
S2=DBL_MAX;
NSIA=DBL_MAX;
NSIB=DBL_MAX;
CWA=DBL_MAX;
CWB=DBL_MAX;
M1A=DBL_MAX;
M2A=DBL_MAX;
M1B=DBL_MAX;
M2B=DBL_MAX;
N1A=DBL_MAX;
N2A=DBL_MAX;
N1B=DBL_MAX;
N2B=DBL_MAX;
DspSec.Clear();
}

void PBEAM::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
    ar << iType;
    ar << sTitle;
    ar << iID;
    ar << iMID;
    ar << iNo;
    for (i=0;i<iNo;i++)
    {
      ar << A[i];
      ar << I1[i];
      ar << I2[i];
      ar << I12[i];
      ar << J[i];
      ar << NSM[i];
      ar << C1[i];
      ar << C2[i];
      ar << D1[i];
      ar << D2[i];
      ar << E1[i];
      ar << E2[i];
      ar << F1[i];
      ar << F2[i];
      ar << SO[i];
      ar << XXB[i];
    }
    ar << K1;
    ar << K2; 
    ar << S1; 
    ar << S2; 
    ar << NSIA;
    ar << NSIB;
    ar << CWA;
    ar << CWB;
    ar << M1A;
    ar << M2A;
    ar << M1B;
    ar << M2B;
    ar << N1A;
    ar << N2A;
    ar << N1B;
    ar << N2B;
    DspSec.Serialize(ar);
  }
  else
  {
    ar >> iType;
    ar >> sTitle;
    ar >> iID;
    ar >> iMID;
    ar >> iNo;
    for (i=0;i<iNo;i++)
    {
      ar >> A[i];
      ar >> I1[i];
      ar >> I2[i];
      ar >> I12[i];
      ar >> J[i];
      ar >> NSM[i];
      ar >> C1[i];
      ar >> C2[i];
      ar >> D1[i];
      ar >> D2[i];
      ar >> E1[i];
      ar >> E2[i];
      ar >> F1[i];
      ar >> F2[i];
      ar >> SO[i];
      ar >> XXB[i];
    }
    ar >> K1;
    ar >> K2; 
    ar >> S1; 
    ar >> S2; 
    ar >> NSIA;
    ar >> NSIB;
    ar >> CWA;
    ar >> CWB;
    ar >> M1A;
    ar >> M2A;
    ar >> M1B;
    ar >> M2B;
    ar >> N1A;
    ar >> N2A;
    ar >> N1B;
    ar >> N2B;
    DspSec.Serialize(ar);
  }
}

void PBEAM::UpdateMats(NEList* newMats)
{
iMID=newMats->Get(iMID);
}

void PBEAM::ChangeMat(int thisMat,int inMID)
{
if (iMID==thisMat)
  iMID=inMID;
}

void PBEAM::CreateSec()
{
double dSize;
if (A[0]>0)
{
  dSize=sqrt(A[0]);
}
else
{
  dSize=0.01;
}
DspSec.CreateDefSec(dSize/2,55);
}

BOOL PBEAM::HasMat(int inMID)
{
  BOOL brc=FALSE;
  if (iMID==inMID)
  {
    brc=TRUE;
  }
  return (brc);
}

void PBEAM::ExportNAS(FILE* pFile)
{
int i;
fprintf(pFile,"$%s\n",sTitle);
fprintf(pFile,"%8s%8i%8i%8s%8s%8s%8s%8s%8s\n","PBEAM   ",iID,iMID,e8(A[0]),e8(I1[0]),e8(I2[0]),e8(I12[0]),e8(J[0]),e8(NSM[0]));
fprintf(pFile,"%8s%8s%8s%8s%8s%8s%8s%8s%8s\n","        ",e8(C1[0]),e8(C2[0]),e8(D1[0]),e8(D2[0]),e8(E1[0]),e8(E2[0]),e8(F1[0]),e8(F2[0]));
for (i=1;i<iNo;i++)
{
  fprintf(pFile,"%8s%8s%8s%8s%8s%8s%8s%8s%8s\n","        ",SO[i],e8(XXB[i]),e8(A[i]),e8(I1[i]),e8(I2[i]),e8(I12[i]),e8(J[i]),e8(NSM[i]));
  if ((SO[i].Find("YESA")>-1) || (SO[i].Find("NO")>-1))
  {
  }
  else
  {
    fprintf(pFile,"%8s%8s%8s%8s%8s%8s%8s%8s%8s\n","        ",e8(C1[i]),e8(C2[i]),e8(D1[i]),e8(D2[i]),e8(E1[i]),e8(E2[i]),e8(F1[i]),e8(F2[i]));
  }
}

fprintf(pFile,"%8s%8s%8s%8s%8s%8s%8s%8s%8s\n","        ",e8(K1),e8(K2),e8(S1),e8(S2),e8(NSIA),e8(NSIB),e8(CWA),e8(CWB));
fprintf(pFile,"%8s%8s%8s%8s%8s%8s%8s%8s%8s\n","        ",e8(M1A),e8(M2A),e8(M1B),e8(M2B),e8(N1A),e8(N2A),e8(N1B),e8(N2B));


//fprintf(pFile,"%-8s%-8s%-8s%-8s\n","        ",e8(dK1),e8(dK2),e8(dI12));

}

PBEAM* PBEAM::Copy()
{
int  i;
PBEAM* pREt=new PBEAM();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
pREt->iMID=iMID;

for (i=0;i<9;i++)
{
  pREt->A[i]=A[i];
  pREt->I1[i]=I1[i];
  pREt->I2[i]=I2[i];
  pREt->I12[i]=I12[i];
  pREt->J[i]=J[i];
  pREt->NSM[i]=NSM[i];
  pREt->C1[i]=C1[i];
  pREt->C2[i]=C2[i];
  pREt->D1[i]=D1[i];
  pREt->D2[i]=D2[i];
  pREt->E1[i]=E1[i];
  pREt->E2[i]=E2[i];
  pREt->F1[i]=F1[i];
  pREt->F2[i]=F2[i];
  pREt->SO[i]=SO[i];
  pREt->XXB[i]=XXB[i];
}
 pREt->K1=K1;
 pREt->K2=K2; 
 pREt->S1=S1; 
 pREt->S2=S2; 
 pREt->NSIA=NSIA;
 pREt->NSIB=NSIB;
 pREt->CWA=CWA;
 pREt->CWB=CWB;
 pREt->M1A=M1A;
 pREt->M2A=M2A;
 pREt->M1B=M1B;
 pREt->M2B=M2B;
 pREt->N1A=N1A;
 pREt->N2A=N2A;
 pREt->N1B=N1B;
 pREt->N2B=N2B;
pREt->DspSec.iLnCnt1=DspSec.iLnCnt1;
pREt->DspSec.iLnCnt2=DspSec.iLnCnt2;
for (i=0;i<DspSec.iLnCnt1;i++)
{
  pREt->DspSec.pLnLoop1[i] = DspSec.pLnLoop1[i];
}
for (i=0;i<DspSec.iLnCnt2;i++)
{
  pREt->DspSec.pLnLoop2[i] = DspSec.pLnLoop2[i];
}
return (pREt);
}

BSec* PBEAM::GetSec()
{
return (&DspSec);
}



IMPLEMENT_DYNAMIC(PBARL , CObject)

PBARL::PBARL()
{
sTitle="";
iID = -1;
iType= 5;
iMID=-1;
iNoDims=0;
sSecType="";
DspSec.Clear();
sGROUP="MSCBML0";
dNSM=0;
A=0;
Izz=0;
Iyy=0;
J=0;
}

void PBARL::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
    ar << iType;
    ar << sTitle;
    ar << iID;
    ar << iMID;
    ar << sGROUP;
    ar << sSecType;
    ar << iNoDims;
    ar << dNSM;
    for (i=0;i<iNoDims;i++)
    {
      ar << dDIMs[i];
    }
    DspSec.Serialize(ar);
  }
  else
  {
    ar >> iType;
    ar >> sTitle;
    ar >> iID;
    ar >> iMID;
    ar >> sGROUP;
    ar >> sSecType;
    ar >> iNoDims;
    ar >> dNSM;
    for (i=0;i<iNoDims;i++)
    {
      ar >> dDIMs[i];
    }
    DspSec.Serialize(ar);
    CalcProps();
  }
}

void PBARL::CreateSec()
{

if (sSecType.Find("BOX")>-1)
{
  DspSec.CreateBox(dDIMs[0],dDIMs[1],dDIMs[2],dDIMs[3]);
}
else if (sSecType.Find("BAR")>-1)
{
  DspSec.CreateBar(dDIMs[0],dDIMs[1]);
}
else if (sSecType.Find("ROD")>-1)
{
  DspSec.CreateRod(dDIMs[0]);
}
else if (sSecType.Find("TUBE")>-1)
{
  DspSec.CreateTube(dDIMs[0],dDIMs[1]);
}
else if (sSecType.Find("I  ")>-1)
{
  DspSec.CreateI(dDIMs[0],dDIMs[1],dDIMs[2],dDIMs[3],dDIMs[4],dDIMs[5]);
}
}

BOOL PBARL::HasMat(int inMID)
{
  BOOL brc=FALSE;
  if (iMID==inMID)
  {
    brc=TRUE;
  }
  return (brc);
}

int PBARL::GetNoDims()
{
int iRet=-1;
if (sSecType.Find("BOX")>-1)
{
   iRet=4;
}
else if (sSecType.Find("BAR")>-1)
{
   iRet=2;
}
else if (sSecType.Find("ROD")>-1)
{
   iRet=1;
}
else if (sSecType.Find("TUBE")>-1)
{
   iRet=2;
}
else if (sSecType.Find("I   ")>-1)
{
   iRet=6;
}
return iRet;
}

void PBARL::ExportNAS(FILE* pFile)
{
int i;
fprintf(pFile,"$%s\n",sTitle);
fprintf(pFile,"%8s%8i%8i%8s%8s%8s\n","PBARL   ",iID,iMID,sGROUP,ncr(sSecType)," ");
fprintf(pFile,"%8s"," ");
for (i=0;i<iNoDims;i++)
{
  fprintf(pFile,"%8s",e8(dDIMs[i]));
}
fprintf(pFile,"%8s\n",e8(dNSM));
}

PBARL* PBARL::Copy()
{
int  i;
PBARL* pREt=new PBARL();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
pREt->iMID=iMID;
pREt->sGROUP=sGROUP;
pREt->sSecType=sSecType;
pREt->iNoDims=iNoDims;
pREt->dNSM=dNSM;
    for (i=0;i<iNoDims;i++)
    {
      pREt->dDIMs[i]=dDIMs[i];
    }
pREt->DspSec.iLnCnt1=DspSec.iLnCnt1;
pREt->DspSec.iLnCnt2=DspSec.iLnCnt2;
for (i=0;i<DspSec.iLnCnt1;i++)
{
  pREt->DspSec.pLnLoop1[i] = DspSec.pLnLoop1[i];
}
for (i=0;i<DspSec.iLnCnt2;i++)
{
  pREt->DspSec.pLnLoop2[i] = DspSec.pLnLoop2[i];
}
return (pREt);
}

BSec* PBARL::GetSec()
{
return (&DspSec);
}

void PBARL::UpdateMats(NEList* newMats)
{
iMID=newMats->Get(iMID);
}

void PBARL::ChangeMat(int thisMat,int inMID)
{
if (iMID==thisMat)
  iMID=inMID;
}

int PBARL::GetDefMatID()
{
  return (iMID);
}

void PBARL::CalcProps()
{
if (sSecType == "ROD")
{
  double R=dDIMs[0];
  A=Pi*R*R;
  Izz=Pi*R*R*R*R/4;
  Iyy=Izz;
  J=Pi*R*R*R*R/2;
}
else if (sSecType == "TUBE")
{
  double Do=2*dDIMs[0];
  double Di=2*dDIMs[1];
  A=Pi*(Do*Do-Di*Di)/4;
  Izz=Pi*(Do*Do*Do*Do-Di*Di*Di*Di)/64;
  Iyy=Izz;
  J=Pi*(Do*Do*Do*Do-Di*Di*Di*Di)/32;
}
else if (sSecType == "BAR")
{
  double W=dDIMs[0];
  double H=dDIMs[1];
  double a,b;
  a=W;
  b=H;
  if (a<b)
  {
    a=H;
    b=W;
  }
  A=W*H;
  Izz=H*W*W*W/12;
  Iyy=W*H*H*H/12;
  J=a*b*b*b*(0.333333333-0.21*b/a*(1-b*b*b*b/(12*a*a*a*a)));

}
else if (sSecType == "BOX")
{
  double Wo=dDIMs[0];
  double Ho=dDIMs[1];
  double Wi=Wo-2*dDIMs[2];
  double Hi=Ho-2*dDIMs[3];
  A=Wo*Ho-Wi*Hi;
  Izz=Ho*Wo*Wo*Wo/12-Hi*Wi*Wi*Wi/12;
  Iyy=Wo*Ho*Ho*Ho/12-Wi*Hi*Hi*Hi/12;
  J=Izz+Iyy;
}
else
{
  outtext1("Unable to calculate beam properties");
}
}

//************************************************
IMPLEMENT_DYNAMIC(PROD , CObject)

PROD::PROD()
{
sTitle="PROD";
iID = -1;
iType= 11;
iMID=-1;
sSecType="VIEW";
DspSec.Clear();
A=0;
J=0;
}

void PROD::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
    ar << iType;
    ar << sTitle;
    ar << iID;
    ar << iMID;
    ar << sGROUP;
    ar << sSecType;
    ar << A;
    ar << J;
    DspSec.Serialize(ar);
  }
  else
  {
    ar >> iType;
    ar >> sTitle;
    ar >> iID;
    ar >> iMID;
    ar >> sGROUP;
    ar >> sSecType;
    ar >> A;
    ar >> J;
    DspSec.Serialize(ar);
  }
}

void PROD::CreateSec()
{
double W;
W=pow(A,0.5);
W*=0.5;
DspSec.CreateDefSec(W,4);
}

BOOL PROD::HasMat(int inMID)
{
  BOOL brc=FALSE;
  if (iMID==inMID)
  {
    brc=TRUE;
  }
  return (brc);
}





PROD* PROD::Copy()
{
int  i;
PROD* pREt=new PROD();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
pREt->iMID=iMID;
pREt->sGROUP=sGROUP;
pREt->sSecType=sSecType;

pREt->DspSec.iLnCnt1=DspSec.iLnCnt1;
pREt->DspSec.iLnCnt2=DspSec.iLnCnt2;
for (i=0;i<DspSec.iLnCnt1;i++)
{
  pREt->DspSec.pLnLoop1[i] = DspSec.pLnLoop1[i];
}
for (i=0;i<DspSec.iLnCnt2;i++)
{
  pREt->DspSec.pLnLoop2[i] = DspSec.pLnLoop2[i];
}
return (pREt);
}

BSec* PROD::GetSec()
{
return (&DspSec);
}

void PROD::UpdateMats(NEList* newMats)
{
iMID=newMats->Get(iMID);
}

void PROD::ChangeMat(int thisMat,int inMID)
{
if (iMID==thisMat)
  iMID=inMID;
}

int PROD::GetDefMatID()
{
  return (iMID);
}

void PROD::CalcProps()
{

}

void PROD::ExportNAS(FILE* pFile)
{
fprintf(pFile,"%8s%8i%8i%8s%8s\n","PROD    ",iID,iMID,e8(A),e8(J));
}
//***************************************************

IMPLEMENT_DYNAMIC(PSHELL , CObject)

void PSHELL::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar<< iType;
    ar<< sTitle;
    ar<< iID;
    ar<< iMID1;
    ar<< dT;
    ar<< iMID2;
    ar<< d12IT3;
    ar<< iMID3;
    ar<< dTST;
    ar<< dNSM;
    ar<< dZ1;
    ar<< dZ2;
    ar<<iMID4;
  }
  else
  {
    ar>>iType;
    ar>>sTitle;
    ar>>iID;
    ar>> iMID1;
    ar>> dT;
    ar>> iMID2;
    ar>> d12IT3;
    ar>> iMID3;
    ar>> dTST;
    ar>> dNSM;
    ar>> dZ1;
    ar>> dZ2;
    ar>>iMID4;
  }
}

BOOL PSHELL::HasMat(int inMID)
{
  BOOL brc=FALSE;
  if (iMID1==inMID)
  {
    brc=TRUE;
  }
  return (brc);
}

void PSHELL::List()
{
  char S1[200];
  CString OutT;
  outtext1("Poperty listing");
  sprintf_s(S1,"%s %i %s %s","PID",iID,"TYPE ","SHELL");
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %s","TITLE : ",sTitle);
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %i","MAT1  : ",iMID1);
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %f","THK   : ",dT);
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %i","MAT2  : ",iMID2);
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %f","12IT3 : ",d12IT3);
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %i","MAT3  : ",iMID3);
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %f","TST   : ",dTST);
  OutT=S1;
  outtext1(OutT); 
  sprintf_s(S1,"%s %f","NSM   : ",dNSM);
  OutT=S1;
  outtext1(OutT); 
  if ((dZ1!=DBL_MAX) || (dZ2!=DBL_MAX) || (iMID4>0))
  {
    sprintf_s(S1,"%s %f","Z1    : ",dZ1);
    OutT=S1;
    outtext1(OutT); 
    sprintf_s(S1,"%s %f","Z2    : ",dZ2);
    OutT=S1;
    outtext1(OutT); 
  }
}

double PSHELL::GetThk()
{
return(dT);
}

void PSHELL::UpdateMats(NEList* newMats)
{
 iMID1=newMats->Get(iMID1);
 iMID2=newMats->Get(iMID2);
 iMID3=newMats->Get(iMID3);
 iMID4=newMats->Get(iMID4);
}

void PSHELL::ChangeMat(int thisMat,int inMID)
{
if (iMID1==thisMat)
{iMID1=inMID;}
if (iMID2==thisMat)
{iMID2=inMID;}
if (iMID3==thisMat)
{iMID3=inMID;}

}

int PSHELL::GetDefMatID()
{
return(iMID1);
}

PSHELL* PSHELL::Copy()
{
PSHELL* pREt=new PSHELL();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
pREt->iMID1=iMID1;
pREt->dT=dT;
pREt->iMID2=iMID2;
pREt->d12IT3=d12IT3;
pREt->iMID3=iMID3;
pREt->dTST=dTST;
pREt->dNSM=dNSM;
pREt->dZ1=dZ1;
pREt->dZ2=dZ2;
return (pREt);
}


void PSHELL::ExportNAS(FILE* pFile)
{
fprintf(pFile,"$%s\n",sTitle);
fprintf(pFile,"%8s%8i%8i%8s%8i%8s%8i%8s%8s\n","PSHELL  ",iID,iMID1,e8(dT),iMID2,e8(d12IT3),iMID3,e8(dTST),e8(dNSM));
if ((dZ1!=DBL_MAX) || (dZ2!=DBL_MAX) || (iMID4>0))
{
  fprintf(pFile,"%8s%8s%8s","        ",e8(dZ1),e8(dZ2));
  if (iMID4>0) 
  {
     fprintf(pFile,"%8i",iMID4);
  }
  fprintf(pFile,"\n","");
}
}

PSHELL::PSHELL()
{
  sTitle="";
  iID = -1;
  iType= 1;
  iMID1=-1;
  dT=0;
  iMID2=-1;
  d12IT3=1.0;
  iMID3=-1;
  dTST=.833333;
  dNSM=0;
  dZ1=DBL_MAX;
  dZ2=DBL_MAX;
  iMID4=-1;
}

//MAt1
IMPLEMENT_DYNAMIC(MAT1 , CObject)

MAT1* MAT1::Copy()
{
MAT1* pREt=new MAT1();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;
pREt->dE=dE;
pREt->dG=dG;
pREt->dNU=dNU;
pREt->dRHO=dRHO;
pREt->dA=dA;
pREt->dTREF=dTREF;
pREt->dGE=dGE;
pREt->dST=dST;
pREt->dSC=dSC;
pREt->dSS=dSS;
pREt->iMCSID=iMCSID;
return (pREt);
}

void MAT1::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar << iType;
    ar << sTitle;
    ar << iID;
    ar << dE;
    ar << dG;
    ar << dNU;
    ar << dRHO;
    ar << dA;
    ar << dTREF;
    ar << dGE;
    ar << dST;
    ar << dSC;
    ar << dSS;
    ar << iMCSID;
  }
  else
  {
    ar >> iType;
    ar >> sTitle;
    ar >> iID;
    ar >> dE;
    ar >> dG;
    ar >> dNU;
    ar >> dRHO;
    ar >> dA;
    ar >> dTREF;
    ar >> dGE;
    ar >> dST;
    ar >> dSC;
    ar >> dSS;
    ar >> iMCSID;
  }
}


void MAT1::ExportNAS(FILE* pFile)
{
fprintf(pFile,"$%s\n",sTitle);
CString sG="        ";
if (dG>0)
{
  sG=e8(dG);
}
fprintf(pFile,"%8s%8i%8s%8s%8s%8s%8s%8s%8s\n","MAT1    ",iID,e8(dE),sG,e8(dNU),e8(dRHO),e8(dA),e8(dTREF),e8(dGE));
//fprintf(pFile,"%8s%8s%8s%8s%8i\n","        ",e8(dST),e8(dSC),e8(dSS),iMCSID);
}

MAT1::MAT1()
{
sTitle="";
iID = -1;
iType = 1;
dE=210e9;
dG=0;
dNU=0.29;
dRHO=0;
dA=0;
dTREF=0;
dGE=0;
dST=0;
dSC=0;
dSS=0;
iMCSID=-1;
}


//MAt8
IMPLEMENT_DYNAMIC(MAT8 , CObject)

MAT8* MAT8::Copy()
{
MAT8* pREt=new MAT8();
pREt->iType=iType;
pREt->sTitle=sTitle;
pREt->iID=iID;
pREt->dE1=dE1;
pREt->dE2=dE2;
pREt->dNU12=dNU12;
pREt->dG12=dG12;
pREt->dG1Z=dG1Z;
pREt->dG2Z=dG2Z;
pREt->dRHO=dRHO;

pREt->dA1=dA1;
pREt->dA2=dA2;
pREt->dTREF=dTREF;
pREt->dXt=dXt;
pREt->dXc=dXc;
pREt->dYt=dYt;
pREt->dYc=dYc;

pREt->dS=dS;
pREt->dGE=dGE;
pREt->F12=F12;
pREt->STRN=STRN;
return (pREt);
}

void MAT8::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar << iType;
    ar << sTitle;
    ar << iID;
    ar << dE1;
    ar << dE2;
    ar << dNU12;
    ar << dG12;
    ar << dG1Z;
    ar << dG2Z;
    ar << dRHO;

    ar << dA1;
    ar << dA2;
    ar << dTREF;
    ar << dXt;
    ar << dXc;
    ar << dYt;
    ar << dYc;

    ar << dS;
    ar << dGE;
    ar << F12;
    ar << STRN;

  }
  else
  {
    ar >> iType;
    ar >> sTitle;
    ar >> iID;
    ar >> dE1;
    ar >> dE2;
    ar >> dNU12;
    ar >> dG12;
    ar >> dG1Z;
    ar >> dG2Z;
    ar >> dRHO;

    ar >> dA1;
    ar >> dA2;
    ar >> dTREF;
    ar >> dXt;
    ar >> dXc;
    ar >> dYt;
    ar >> dYc;

    ar >> dS;
    ar >> dGE;
    ar >> F12;
    ar >> STRN;
  }
}


void MAT8::ExportNAS(FILE* pFile)
{
fprintf(pFile,"$%s\n",sTitle);
fprintf(pFile,"%8s%8i%8s%8s%8s%8s%8s%8s%8s\n","MAT8    ",iID,e8(dE1),e8(dE2),e8(dNU12),e8(dG12),e8(dG1Z),e8(dG2Z),e8(dRHO));
fprintf(pFile,"%8s%8s%8s%8s%8s%8s%8s%8s%8s\n","        ",e8(dA1),e8(dA2),e8(dTREF),e8(dXt),e8(dXc),e8(dYt),e8(dYc),e8(dS));
fprintf(pFile,"%8s%8s%8s\n","        ",e8(dGE),e8(F12),e8(STRN));
}

MAT8::MAT8()
{

sTitle="";
iID = -1;
iType = 8;
dE1 = 0;
dE2 = 0;
dNU12 = 0;
dG12 = 0;
dG1Z = 0;
dG2Z = 0;
dRHO = 0;

dA1 = 0;
dA2 = 0;
dTREF = 0;
dXt = 0;
dXc = 0;
dYt = 0;
dYc = 0;

dS = 0;
dGE = 0;
F12 = 0;
STRN = 0;
}
IMPLEMENT_DYNAMIC(PCOMP , CObject)

void PCOMP::Serialize(CArchive& ar)
{
int i;
	if (ar.IsStoring())
	{
    ar<<sTitle;
    ar<<iID;
    ar<<iType;
    ar<<dZ0;
    ar<<dNSM;
    ar<<dSB;
    ar<<FT;
    ar<<dRefT;
    ar<<dGE;
    ar<<bLAM;
    ar<<iNoLays;
    for (i=0;i<iNoLays;i++)
    {
      ar<< MID[i];
      ar<< T[i];
      ar<< Theta[i];
      ar<< sOut[i];
    }
  }
  else
  {
    ar>>sTitle;
    ar>>iID;
    ar>>iType;
    ar>>dZ0;
    ar>>dNSM;
    ar>>dSB;
    ar>>FT;
    ar>>dRefT;
    ar>>dGE;
    ar>>bLAM;
    ar>>iNoLays;
    for (i=0;i<iNoLays;i++)
    {
      ar>> MID[i];
      ar>> T[i];
      ar>> Theta[i];
      ar>> sOut[i];
    }
  }
}

void PCOMP::List()
{
  int i;
  char S1[200];
  CString OutT;
  outtext1("PCOMP"); 
  Property::List();
  outtext1("Mat,Thk,Theta"); 
  for (i=0;i<iNoLays;i++)
  {
    sprintf_s(S1,"%i,%f,%f",MID[i],T[i],Theta[i]);
    OutT=S1;
    outtext1(OutT); 
  }
}

double PCOMP::GetThk()
{
int i;
double dRet=0;
for (i=0;i<iNoLays;i++)
{
  dRet+=T[i];
}
return (dRet);
}

void PCOMP::UpdateMats(NEList* newMats)
{
  int i;
  for (i=0;i<iNoLays;i++)
  {
    MID[i]=newMats->Get(MID[i]);
  }
}

void PCOMP::ChangeMat(int thisMat,int inMID)
{
  int i;
  for (i=0;i<iNoLays;i++)
  {
    if (MID[i]==inMID)
    {
      MID[i]=inMID;
    }
  }
}

BOOL PCOMP::HasMat(int inMID)
{
  int i;
  BOOL brc=FALSE;
  for (i=0;i<iNoLays;i++)
  {
    if (MID[i]==inMID)
    {
      brc=TRUE;
      break;
    }
  }
  return (brc);
}

void PCOMP::ExportNAS(FILE* pFile)
{
}

PCOMP* PCOMP::Copy()
{
int i;
PCOMP* pREt=new PCOMP();
pREt->iID=iID;
pREt->sTitle=sTitle;
pREt->iType=iType;

pREt->dZ0=dZ0;
pREt->dNSM=dNSM;
pREt->dSB=dSB;
pREt->FT=FT;
pREt->dRefT=dRefT;
pREt->dGE=dGE;
pREt->bLAM=bLAM;
pREt->iNoLays=iNoLays;
for (i=0;i<iNoLays;i++)
{
  pREt->MID[i]=MID[i];
  pREt->T[i]=T[i];
  pREt->Theta[i]=Theta[i];
  pREt->sOut[i]=sOut[i];
}
return (pREt);
}

void PCOMP::AddLayer(int inMID,double inT,double inThe,BOOL inSo)
{
if (iNoLays<MAX_LAYERS)
{
   MID[iNoLays]=inMID;
   T[iNoLays]=inT;
   Theta[iNoLays]=inThe;
   sOut[iNoLays]=inSo;
   iNoLays++;
}
else
{
   outtext1("ERROR Max no layers in pcomp reached");
}


}

PCOMP::PCOMP()
{
sTitle="";
iID = -1;
iType= 2;
dZ0=-0.5;
dNSM=0;
dSB=0;
FT=4;
dRefT=0;
dGE=0;
bLAM=FALSE;
iNoLays=0;
}

IMPLEMENT_DYNAMIC(Moment, CObject)

void Moment::Create(G_Object* pInNode,
				            G_Object* Parrent,
				            C3dVector inF,
				            int inSetID)
{
Drawn=0;
Selectable=1; 
Visable=1;
iObjType=323;
G_label=pInNode->G_label;
G_Colour=4;
pParent=Parrent;
pObj= pInNode;
Pt_Object* pNode=(Pt_Object*) pInNode;
SetID=inSetID;
F=inF;
Point[0].x=pNode->Pt_Point->x;
Point[0].y=pNode->Pt_Point->y;
Point[0].z=pNode->Pt_Point->z;
Point[1]=F;
Point[1].Normalize();
Point[1]+=Point[0];
}

void Moment::ExportNAS(FILE* pFile)
{

fprintf(pFile,"%8s%8s%8i%8s%8s%8s%8s%8s\n","MOMENT  ","       1",pObj->G_label,"       0","     1.0",e8(F.x),e8(F.y),e8(F.z));
}


IMPLEMENT_DYNAMIC(Pressure, CObject)

void Pressure::Create(E_Object* pInEl,
				              G_Object* Parrent,
				              C3dVector inF,
				              int inSetID)
{
Drawn=0;
Selectable=1; 
Visable=1;
iObjType=324;
G_label=pInEl->G_label;
G_Colour=4;
pParent=Parrent;
pObj=pInEl;
SetID=inSetID;
F=inF;
Point[0]=pInEl->Get_Centroid();
Point[1]=pInEl->Get_Normal();
Point[1].Normalize();
Point[1]+=Point[0];
}

void Pressure::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
if ((iDspFlgs & DSP_BC)>0)
{
  Selectable=1;
  E_Object* pE=(E_Object*) pObj;
  Point[1]=pE->Get_Normal();
  Point[1].Normalize();
  Point[1]*=dS1;
  Point[1]+=Point[0];
  glColor3fv(cols[G_Colour]);
  glBegin(GL_LINES);
  glVertex3f((float) Point[0].x,(float) Point[0].y,(float) Point[0].z);
  glVertex3f((float) Point[1].x,(float) Point[1].y,(float) Point[1].z);
  glEnd();
  char sLab[20];
  sprintf_s(sLab,"%3.0f",F.Mag());
  OglString(iDspFlgs,Point[1].x,Point[1].y,Point[1].z,&sLab[0]);
}
else
{
  Selectable=0;
}
}

void Pressure::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
G_Object::SetToScr(pModMat, pScrTran);
E_Object* pE = (E_Object*) pObj;
Point[0]=pE->Get_Centroid();

C3dVector V;
C3dVector R;
R.x = Point[0].x;
R.y = Point[0].y;
R.z = Point[0].z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;
R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;
DSP_Point[0].x = R.x;
DSP_Point[0].y = R.y;
DSP_Point[0].z = 0;

R.x = Point[1].x;
R.y = Point[1].y;
R.z = Point[1].z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;
R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;
DSP_Point[1].x = R.x;
DSP_Point[1].y = R.y;
DSP_Point[1].z = 0;
}

void Pressure::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iEL;
	if (ar.IsStoring())
	{
	  G_Object::Serialize(ar);
	  ar<<SetID;
    F.Serialize(ar);
    ar << pObj->G_label;
	}
	else
	{
	  G_Object::Serialize(ar);
    ar>>SetID;
    F.Serialize(ar);
    ar>>iEL;
    pObj = MESH->GetElement(iEL);
	  pParent=MESH;
	}
}

void Pressure::ExportNAS(FILE* pFile)
{

//fprintf(pFile,"%8s%8s%8i%8s%8s%8s%8s%8s\n","MOMENT  ","       1",pNode->G_label,"       0","     1.0",e8(F.x),e8(F.y),e8(F.z));
}


IMPLEMENT_DYNAMIC( Force, CObject )

void Force::Create(G_Object* pInNode,
				   G_Object* Parrent,
				   C3dVector inF,
				   int inSetID)
{
Drawn=0;
Selectable=1; 
Visable=1;
iObjType=321;
G_label=pInNode->G_label;
G_Colour=55;
pParent=Parrent;
pObj= pInNode;
SetID=inSetID;
F=inF;
//Pt_Object* pNode = (Pt_Object*) pInNode;
Point[0]=pObj->Get_Centroid();
Point[1]=F;
Point[1].Normalize();
Point[1]+=Point[0];

}

void Force::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
	  G_Object::Serialize(ar);
	  ar<<SetID;
      F.Serialize(ar);
      ar << pObj->G_label;
	}
	else
	{
	  G_Object::Serialize(ar);
      ar>>SetID;
      F.Serialize(ar);
      ar>>iNd;
      pObj = MESH->GetNode(iNd);
	  pParent=MESH;

	}
}

G_Object* Force::Copy(G_Object* Parrent)
{
ME_Object* MESH = (ME_Object*) Parrent;
G_Object* pPt=MESH->GetNode(pObj->G_label);
Force* gret = new Force;
gret->Create(pPt,
			MESH,
			F,
			SetID);
return (gret);
}

Force::~Force()
{
SetID=-1;
pObj=NULL;
}

void Force::ExportUNV(FILE* pFile)
{

}

void Force::ExportNAS(FILE* pFile)
{

fprintf(pFile,"%8s%8s%8i%8s%8s%8s%8s%8s\n","FORCE   ","       1",pObj->G_label,"       0","     1.0",e8(F.x),e8(F.y),e8(F.z));
}


C3dVector Force::Get_Centroid()
{
C3dVector vT;
vT =Point[0];
vT+=Point[1];
vT*=0.5;
return (vT);
}


void Force::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
G_Object::SetToScr(pModMat, pScrTran);
Pt_Object* pNode = (Pt_Object*) pObj;
Point[0].x=pNode->Pt_Point->x;
Point[0].y=pNode->Pt_Point->y;
Point[0].z=pNode->Pt_Point->z;
//Point[1]=F;
//Point[1].Normalize();
//Point[1]*=0.05;
//Point[1]+=Point[0];
C3dVector V;
C3dVector R;
R.x = Point[0].x;
R.y = Point[0].y;
R.z = Point[0].z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;
R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;
DSP_Point[0].x = R.x;
DSP_Point[0].y = R.y;
DSP_Point[0].z = 0;

R.x = Point[1].x;
R.y = Point[1].y;
R.z = Point[1].z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;
R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;
DSP_Point[1].x = R.x;
DSP_Point[1].y = R.y;
DSP_Point[1].z = 0;
}

void Force::Draw(CDC* pDC,int iDrawmode)
{
pDC->MoveTo((int) DSP_Point[0].x,(int) DSP_Point[0].y);
pDC->LineTo((int) DSP_Point[1].x,(int) DSP_Point[1].y);
}

void Force::HighLight(CDC* pDC)
{
this->Draw(pDC,4);
}

void Force::OglDraw(int iDspFlgs,double dS1,double dS2)
{
  OglDrawW(iDspFlgs,dS1,dS2);
}

void Force::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
if ((iDspFlgs & DSP_BC)>0)
{
  Selectable=1;
  Point[1]=F;
  Point[1].Normalize();
  Point[1]*=dS1;
  Point[1]+=Point[0];
  glColor3fv(cols[G_Colour]);
  glBegin(GL_LINES);
  glVertex3f((float) Point[0].x,(float) Point[0].y,(float) Point[0].z);
  glVertex3f((float) Point[1].x,(float) Point[1].y,(float) Point[1].z);
  glEnd();
  char sLab[20];
  sprintf_s(sLab,"%3.0f",F.Mag());
  OglString(iDspFlgs,Point[1].x,Point[1].y,Point[1].z,&sLab[0]);
}
else
{
  Selectable=0;
}
}

G_ObjectD Force::SelDist(CPoint InPT,Filter FIL)
{

CPoint cPt2;
double dt;
double d;
G_ObjectD Ret;


dt =  0.5*(DSP_Point[0].x+DSP_Point[1].x)-InPT.x;
cPt2.x = long (dt);
dt =  0.5*(DSP_Point[0].y+DSP_Point[1].y)-InPT.y;
cPt2.y = long (dt);
d=(cPt2.x*cPt2.x+cPt2.y*cPt2.y);
Ret.Dist=d;
Ret.pObj=this;
return (Ret);
}

void Force::Info()
{
  char S1[80];
  CString OutT;
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  OutT+=S1;
  outtext1("FORCE VECTOR");
  outtext1(OutT); 
  sprintf_s(S1,"%s%8.5f,%8.5f,%8.5f","FORCE: ",F.x,F.y,F.z);
  OutT=S1;
  outtext1(OutT); 
}



IMPLEMENT_DYNAMIC( Restraint, CObject )

void Restraint::Create(G_Object* pInNode,
					             G_Object* Parrent,
					             BOOL xon,
                       BOOL yon,
                       BOOL zon,
                       BOOL rxon,
                       BOOL ryon,
                       BOOL rzon,		   
				               int inSetID)
{
Drawn=0;
Selectable=1; 
Visable=1;
iObjType=322;
G_label=pInNode->G_label;
G_Colour=2;
pParent=Parrent;
pObj=pInNode;
SetID=inSetID;
REST[0]=xon;
REST[1]=yon;
REST[2]=zon;
REST[3]=rxon;
REST[4]=ryon;
REST[5]=rzon;
}

void Restraint::Serialize(CArchive& ar,ME_Object* MESH)

{
  int iNd;
	if (ar.IsStoring())
	{
	  G_Object::Serialize(ar);
	  ar<<SetID;
    ar << pObj->G_label;
	  ar<<REST[0];
	  ar<<REST[1];
	  ar<<REST[2];
	  ar<<REST[3];
	  ar<<REST[4];
	  ar<<REST[5];
	}
	else
	{
	  G_Object::Serialize(ar);
      ar>>SetID;
      ar>>iNd;
      pObj = MESH->GetNode(iNd);
      Pt_Object* pN = (Pt_Object*) pObj;
      Point=pN->GetCoords();
	  ar>>REST[0];
	  ar>>REST[1];
	  ar>>REST[2];
	  ar>>REST[3];
	  ar>>REST[4];
	  ar>>REST[5];
	  pParent=MESH;
	}
}

G_Object* Restraint::Copy(ME_Object* MESH,int iOff)
{
Pt_Object* pPt=MESH->GetNode(pObj->G_label+iOff);
Restraint* gret = new Restraint;
gret->Create(pPt,
			 MESH,
			 REST[0],
			 REST[1],
			 REST[2],
			 REST[3],
			 REST[4],
			 REST[5],
			 SetID);
return (gret);
}

Restraint::~Restraint()
{
SetID=-1;
pObj=NULL;
}

void Restraint::ExportUNV(FILE* pFile)
{

}

void Restraint::ExportNAS(FILE* pFile)
{

C3dVector vCent;
vCent=Get_Centroid();
char S1[7];
sprintf_s(S1,"%s",GetDofStr());

fprintf(pFile,"%8s%8s%8i%8s%8s\n","SPC     ","       1",pObj->G_label,GetDofStr(),"     0.0");

}

C3dVector Restraint::Get_Centroid()
{
return (Point);
}


void Restraint::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
G_Object::SetToScr(pModMat, pScrTran);
Pt_Object* pNode = (Pt_Object*) pObj;
Point.x=pNode->Pt_Point->x;
Point.y=pNode->Pt_Point->y;
Point.z=pNode->Pt_Point->z;
//Point[1]=F;
//Point[1].Normalize();
//Point[1]*=0.05;
//Point[1]+=Point[0];
C3dVector V;
C3dVector R;
R.x = Point.x;
R.y = Point.y;
R.z = Point.z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;
R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;
DSP_Point.x = R.x;
DSP_Point.y = R.y;
DSP_Point.z = 0;

}

void Restraint::Draw(CDC* pDC,int iDrawmode)
{
pDC->MoveTo((int) DSP_Point.x,(int) DSP_Point.y);
pDC->LineTo((int) DSP_Point.x-10,(int) DSP_Point.y-10);
pDC->LineTo((int) DSP_Point.x-10,(int) DSP_Point.y+10);
pDC->LineTo((int) DSP_Point.x,(int) DSP_Point.y);
}

void Restraint::HighLight(CDC* pDC)
{
this->Draw(pDC,4);
}

CString Restraint::GetDofStr()
{
CString sRet;
char sLab[7];
int i=0;
if (REST[0]) 
{
   sLab[i]='1'; 
   i++;
}
if (REST[1]) 
{
   sLab[i]='2'; 
   i++;
}
if (REST[2]) 
{
   sLab[i]='3'; 
   i++;
}
if (REST[3]) 
{
   sLab[i]='4'; 
   i++;
}
if (REST[4]) 
{
   sLab[i]='5'; 
   i++;
}
if (REST[5]) 
{
   sLab[i]='6'; 
   i++;
}
sLab[i]=NULL;
sRet=sLab;
return (sRet);
}

void Restraint::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
if ((iDspFlgs & DSP_BC)>0)
{
  Selectable=1;
  glColor3fv(cols[G_Colour]);
  C3dVector vCent;
  vCent=pObj->Get_Centroid();
  glRasterPos3f ((float) vCent.x,(float) vCent.y,(float) vCent.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPR);
  char S1[7];
  sprintf_s(S1,"%s",GetDofStr());
  OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&S1[0]);
}
else
{
  Selectable=0;
}
}

void Restraint::OglDraw(int iDspFlgs,double dS1,double dS2)
{

OglDrawW(iDspFlgs,dS1,dS2);
}

//G_ObjectD Restraint::SelDist(CPoint InPT,Filter FIL)
//{
//CPoint cPt2;
//G_ObjectD Ret;
//
//cPt2.x = DSP_Point.x-InPT.x;
//cPt2.y = DSP_Point.y-InPT.y;
//Ret.Dist=(cPt2.x*cPt2.x+cPt2.y*cPt2.y);
//Ret.pObj=this;
//return (Ret);
//}

void Restraint::Info()
{
  char S1[80];
  CString OutT;
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  OutT+=S1;
  outtext1("RESTRAINT");
  outtext1(OutT); 
  sprintf_s(S1,"%s%s,","DOF STR: ",GetDofStr());
  OutT=S1;
  outtext1(OutT); 
}


IMPLEMENT_DYNAMIC( CoordSys, CObject )
void CoordSys::Create(C3dVector Orig,C3dMatrix RMat,int inRID,int inTp, int iLab, int iC,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 12;
G_Colour = iC;
G_label = iLab;
mOrientMat=RMat;
Origin = Orig;
dScl=1;
pParent=Parrent;
RID = inRID;
CysType = inTp;
}

C3dMatrix CoordSys::GetTMat()
{
return (mOrientMat);
}

G_Object* CoordSys::Copy(G_Object* Parrent)
{
CoordSys* cSys = new CoordSys;
cSys->Drawn = Drawn;
cSys->Selectable  = Selectable; 
cSys->Visable  = Visable;
cSys->G_Colour = G_Colour;
cSys->iObjType = iObjType;
cSys->G_label = G_label;
cSys->mOrientMat=mOrientMat;
cSys->Origin=Origin;
cSys->dScl=dScl;
cSys->RID=RID;
cSys->CysType=CysType;
cSys->pParent = Parrent;
return (cSys);
}

void CoordSys::ExportNAS(FILE* pFile)
{
C3dVector pB;
C3dVector pC;
CString sType;
if (CysType==3)
{
  sType="CORD2S  ";
}
else if (CysType==2)
{
  sType="CORD2C  ";
}
else
{
  sType="CORD2R  ";
}
pB.x	= mOrientMat.m_02;
pB.y  = mOrientMat.m_12;
pB.z  = mOrientMat.m_22;
pC.x	= mOrientMat.m_00;
pC.y  = mOrientMat.m_10;
pC.z  = mOrientMat.m_20;
pB+=Origin;
pC+=Origin;

fprintf(pFile,"%8s%8i%8i%8s%8s%8s%8s%8s%8s\n",sType,G_label,RID,e8(Origin.x),e8(Origin.y),e8(Origin.z),e8(pB.x),e8(pB.y),e8(pB.z));
fprintf(pFile,"%8s%8s%8s%8s\n","        ",e8(pC.x),e8(pC.y),e8(pC.z));
}

void CoordSys::Info()
{
  char S1[200];
  CString OutT;
  //G_Object::Info();
  sprintf_s(S1,"%i,%8.5f,%8.5f,%8.5f,,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f",
            G_label,Origin.x,Origin.y,Origin.z,
            mOrientMat.m_00, mOrientMat.m_10, mOrientMat.m_20,
            mOrientMat.m_01, mOrientMat.m_11, mOrientMat.m_21,
            mOrientMat.m_02, mOrientMat.m_12, mOrientMat.m_22);
  OutT=S1;
  outtext1(OutT); 
}



C3dVector CoordSys::Get_Centroid() 
{

return (Origin);
}

void CoordSys::Translate (C3dVector vIn)
{
Origin.Translate(vIn);
}



void CoordSys::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
      G_Object::Serialize(ar);
      mOrientMat.Serialize(ar);
	  Origin.Serialize(ar);
	  ar<<dScl;
	  ar<<RID;
	  ar<<CysType;
	}
	else
	{
	  G_Object::Serialize(ar);
      mOrientMat.Serialize(ar);
	  Origin.Serialize(ar);
	  ar>>dScl;
	  ar>>RID;
	  ar>>CysType;
	}
}




void CoordSys::OglDrawW(int iDspFlgs,double dS1,double dS2)
{

C3dVector X;
C3dVector Y;
C3dVector Z;


X.x = mOrientMat.m_00;
X.y = mOrientMat.m_10;
X.z = mOrientMat.m_20;

Y.x = mOrientMat.m_01;
Y.y = mOrientMat.m_11;
Y.z = mOrientMat.m_21;

Z.x = mOrientMat.m_02;
Z.y = mOrientMat.m_12;
Z.z = mOrientMat.m_22;

X*=dS1;
Y*=dS1;
Z*=dS1;

X+=Origin;
Y+=Origin;
Z+=Origin;

glColor3fv(cols[GetCol()]);
glBegin(GL_LINES);


glVertex3f((float) Origin.x,(float) Origin.y,(float) Origin.z);
glVertex3f((float) X.x,(float) X.y,(float) X.z);

glVertex3f((float) Origin.x,(float) Origin.y,(float) Origin.z);
glVertex3f((float) Y.x,(float) Y.y,(float) Y.z);

glVertex3f((float) Origin.x,(float) Origin.y,(float) Origin.z);
glVertex3f((float) Z.x,(float) Z.y,(float) Z.z);
glEnd();

glColor3fv(cols[124]);
if (CysType==2)
{
  glRasterPos3f ((float) X.x,(float) X.y,(float) X.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPR);
  glRasterPos3f ((float) Y.x,(float) Y.y,(float) Y.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPT);
  glRasterPos3f ((float) Z.x,(float) Z.y,(float) Z.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPZ);
}
else if (CysType==3)
{
  glRasterPos3f ((float) X.x,(float) X.y,(float) X.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPR);
  glRasterPos3f ((float) Y.x,(float) Y.y,(float) Y.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPT);
  glRasterPos3f ((float) Z.x,(float) Z.y,(float) Z.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPP);
}
else
{
  glRasterPos3f ((float) X.x,(float) X.y,(float) X.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPX);
  glRasterPos3f ((float) Y.x,(float) Y.y,(float) Y.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPY);
  glRasterPos3f ((float) Z.x,(float) Z.y,(float) Z.z);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPZ);
}
char sLab[20];
C3dVector vCent;
vCent=Get_Centroid();
if (bDrawLab==TRUE)
{
	sprintf_s(sLab,"Cys%i",G_label);
	OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
}
}


void CoordSys::OglDraw(int iDspFlgs,double dS1,double dS2)
{
OglDrawW(iDspFlgs,dS1,dS2);
}



IMPLEMENT_DYNAMIC( CvPt_Object , CObject )
// Create Object
CvPt_Object ::~CvPt_Object ()
{
 if (Pt_Point!=NULL)
 {
   delete(Pt_Point);
   Pt_Point=NULL;
 }

 if (DSP_Point!=NULL)
 {
   delete(DSP_Point);
   DSP_Point=NULL;
 }

}
		
void CvPt_Object::Create(C3dVector InPt,double Inw, int iLab,int i2,int i3, int iC,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
iObjType = 0;
G_Colour = iC;
G_label = iLab;
Pt_Point = new C3dVector(InPt.x,InPt.y,InPt.z);
DSP_Point = new C3dVector();
pParent=Parrent;
w=Inw;
}

void CvPt_Object::Info()
{
  char S1[80];
  CString OutT;

  sprintf_s(S1,"LAB: %i X: %f Y: %f Z: %f",G_label,Pt_Point->x,Pt_Point->y,Pt_Point->z);
  OutT=S1;
  outtext1(OutT); 
  
}

C3dVector CvPt_Object::MinPt(C3dVector inPt)
{
C3dVector vRet;
vRet.Set(Pt_Point->x,Pt_Point->y,Pt_Point->z);
return (vRet);
}




G_Object* CvPt_Object::Copy(G_Object* Parrent)
{
CvPt_Object* PtRet = new CvPt_Object;
PtRet->Drawn = Drawn;
PtRet->Selectable  = Selectable; 
PtRet->Visable  = Visable;
PtRet->G_Colour = G_Colour;
PtRet->iObjType = iObjType;
PtRet->G_label = G_label;
PtRet->Pt_Point = new C3dVector(Pt_Point->x,Pt_Point->y,Pt_Point->z);
PtRet->DSP_Point = new C3dVector();
PtRet->pParent=Parrent;
PtRet->w=w;
return (PtRet);
}

void CvPt_Object::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
    ar<<Pt_Point->x;
    ar<<Pt_Point->y;
    ar<<Pt_Point->z;  
	ar<<w;
	}
	else
	{
    G_Object::Serialize(ar);
    Pt_Point = new C3dVector();
    DSP_Point = new C3dVector();
    ar>>Pt_Point->x;
    ar>>Pt_Point->y;
    ar>>Pt_Point->z; 
    ar>>w;
	}
}





void CvPt_Object::Clear()
{

}

C3dVector CvPt_Object::GetCoords() 
{
C3dVector vRet;
vRet.Set(Pt_Point->x,Pt_Point->y,Pt_Point->z);
return (vRet);
}

C3dVector CvPt_Object::Get_Centroid()
{
return (GetCoords());
}



// Draw Object line
void CvPt_Object::Draw(CDC* pDC,int iDrawmode)
{

pDC->MoveTo((int) DSP_Point->x-4,(int) DSP_Point->y+4);
pDC->LineTo((int) DSP_Point->x+4,(int) DSP_Point->y-4);
pDC->MoveTo((int) DSP_Point->x+4,(int) DSP_Point->y+4);
pDC->LineTo((int) DSP_Point->x-4,(int) DSP_Point->y-4);
pDC->MoveTo((int) DSP_Point->x+4,(int) DSP_Point->y);
pDC->LineTo((int) DSP_Point->x-5,(int) DSP_Point->y);
pDC->MoveTo((int) DSP_Point->x,(int) DSP_Point->y-4);
pDC->LineTo((int) DSP_Point->x,(int) DSP_Point->y+4);
//pDC->SetPixel(DSP_Point->x, DSP_Point->y+4, 255 );

//pDC->Ellipse(DSP_Point->x+3,DSP_Point->y+3,DSP_Point->x-3,DSP_Point->y-3);
}


void CvPt_Object::OglDraw(int iDspFlgs,double dS1,double dS2)
{
OglDrawW(iDspFlgs,dS1,dS2);
}

void CvPt_Object::OglDrawW(int iDspFlgs,double dS1,double dS2)
{

if ((iDspFlgs & DSP_POINTS) > 0)
{
  Selectable=1;
  glColor3fv(cols[GetCol()]);
  glPointSize(4.0f);
  glBegin(GL_POINTS);
  glVertex3f((float) Pt_Point->x,(float) Pt_Point->y,(float) Pt_Point->z);
  glEnd();
}
else
{
  Selectable=0;
}

}

void CvPt_Object::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{

C3dVector V;
C3dVector R;
G_Object::SetToScr(pModMat,pScrTran);
  
R.x = Pt_Point->x;
R.y = Pt_Point->y;
R.z = Pt_Point->z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;

R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;


DSP_Point->x = R.x;
DSP_Point->y = R.y;
DSP_Point->z = 0;
}

void CvPt_Object::Move(C3dVector vM)
{
Pt_Point->x +=vM.x;
Pt_Point->y +=vM.y;
Pt_Point->z +=vM.z;
}

void CvPt_Object::Transform(C3dMatrix TMAt)
{
C3dVector R;
R.x =  TMAt.m_00 * Pt_Point->x +  TMAt.m_01 * Pt_Point->y +  TMAt.m_02 * Pt_Point->z +  TMAt.m_30;
R.y =  TMAt.m_10 * Pt_Point->x +  TMAt.m_11 * Pt_Point->y +  TMAt.m_12 * Pt_Point->z +  TMAt.m_31;
R.z =  TMAt.m_20 * Pt_Point->x +  TMAt.m_21 * Pt_Point->y +  TMAt.m_22 * Pt_Point->z +  TMAt.m_32;
Pt_Point->x =R.x;
Pt_Point->y =R.y;
Pt_Point->z =R.z;

}

void CvPt_Object::Translate(C3dVector vIn)
{
Pt_Point->x +=vIn.x;
Pt_Point->y +=vIn.y;
Pt_Point->z +=vIn.z;
}

void CvPt_Object::ScaleX(double d)
{
Pt_Point->x *=d;
}


void CvPt_Object::HighLight(CDC* pDC)
{
pDC->Ellipse((int) DSP_Point->x+5,(int) DSP_Point->y+5,(int) DSP_Point->x-5,(int) DSP_Point->y-5);

}





void CvPt_Object::S_Box(CPoint P1,CPoint P2,ObjList* pSel)
{
if ((DSP_Point->x > P1.x) && 
	  (DSP_Point->x < P2.x) &&
    (DSP_Point->y > P1.y) &&
    (DSP_Point->y < P2.y))
{
	pSel->Add(this);
}
}


void CvPt_Object::SetTo(C3dVector cInVect)
{
Pt_Point->x = cInVect.x;
Pt_Point->y = cInVect.y;
Pt_Point->z = cInVect.z;
}


IMPLEMENT_DYNAMIC( CvPt_ObjectW , CObject )
void CvPt_ObjectW::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
G_Object::SetToScr(pModMat,pScrTran);
C3dVector V;
C3dVector R;
double x,y;
NSurf* pS;
pS=(NSurf*) this->pParent->pParent;
if (pS!=NULL)
{
  x=Pt_Point->x;
  y=Pt_Point->y;
  w=w;
  R=pS->GetPt(x,y);
  V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
  V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
  V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;
  R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
  R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
  R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;
  DSP_Point->x = R.x;
  DSP_Point->y = R.y;
  DSP_Point->z = 0;
}
}

C3dVector CvPt_ObjectW::Get_Centroid()
{

C3dVector V;
C3dVector R;
double x,y;
NSurf* pS;
pS=(NSurf*) this->pParent->pParent;
if (pS!=NULL)
{
  x=Pt_Point->x;
  y=Pt_Point->y;
  w=w;
  R=pS->GetPt(x,y);
}
return (R);
}

IMPLEMENT_DYNAMIC(NCurve, CObject)

NCurve ::~NCurve ()
{
int i;
for (i=0;i<iNoCPts;i++)
{
  if (cPts [i]!=NULL)
  {
    delete(cPts[i]);
    cPts[i]=NULL;
  }
}
}

void NCurve::Clean()
{
int i;
for (i=0;i<iNoCPts;i++)
{
  if (cPts [i]!=NULL)
  {
    delete(cPts[i]);
    cPts[i]=NULL;
  }
}
iNoCPts=0;
}

NCurve::NCurve()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = -1;
iObjType = 7;
iNoCPts=0;
p=3;
ws=0;
we=1;
DrawCPts=FALSE;
DrawNoCvs=FALSE;
}


    // CvPt_Object* pVertex[20];
void NCurve::Create(int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 7;
iNoCPts=0;
p=3;
ws=0.0;
we=1.0;
pParent=Parrent;
DrawCPts=FALSE;
DrawNoCvs=FALSE;
}

C3dVector NCurve::Get_Centroid()
{
return (GetPt(0.5));
}

void NCurve::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
      G_Object::Serialize(ar);
	  ar << iNoCPts;
      ar << p;
      ar << ws;
      ar << we;
	  ar << DrawCPts;
	  for (i=0;i<iNoCPts;i++)
      {
        cPts[i]->Serialize(ar);
      }
      for (i=0;i<iNoCPts+p+1;i++)
      {
        ar << knots[i];
      }
	}
	else
	{
      G_Object::Serialize(ar);
	  ar >> iNoCPts;
      ar >> p;
      ar >> ws;
      ar >> we;
	  ar >> DrawCPts;
	  for (i=0;i<iNoCPts;i++)
      {
        cPts[i]=new CvPt_Object();
        cPts[i]->Serialize(ar);
        cPts[i]->pParent=this;
      }
      for (i=0;i<iNoCPts+p+1;i++)
      {
        ar >> knots[i];
      }
	}
}

G_Object* NCurve::Copy(G_Object* Parrent)
{
int i;
NCurve* cPoly = new NCurve();
cPoly->Drawn = Drawn;
cPoly->Selectable  = Selectable; 
cPoly->Visable  = Visable;
cPoly->G_Colour = G_Colour;
cPoly->iObjType = iObjType;
cPoly->G_label = G_label;
cPoly->iNoCPts = iNoCPts;
cPoly->p = p;
cPoly->ws = ws;
cPoly->we = we;
cPoly->pParent=Parrent;

for (i=0;i<iNoCPts;i++)
{
  cPoly->cPts[i]=new CvPt_Object();
  cPoly->cPts[i]=(CvPt_Object*) cPts[i]->Copy(cPoly);
}
for (i=0;i<iNoCPts+p+1;i++)
{
  cPoly->knots[i]=knots[i];
}
return (cPoly);
}

void NCurve::GetContolPts(Vec <C4dVector> & Cpts)
{
int i;
double w;
Cpts.Size(iNoCPts);

for (i=0;i<iNoCPts;i++)
{
  w=cPts[i]->w;
  Cpts(i).xw=cPts[i]->Pt_Point->x*w;
  Cpts(i).yw=cPts[i]->Pt_Point->y*w;
  Cpts(i).zw=cPts[i]->Pt_Point->z*w;
  Cpts(i).w;
}
}

void NCurve::Get3dPts(Vec <C3dVector> & Cpts)
{
int i;

Cpts.Size(iNoCPts);

for (i=0;i<iNoCPts;i++)
{
  Cpts(i).x=cPts[i]->Pt_Point->x;
  Cpts(i).y=cPts[i]->Pt_Point->y;
  Cpts(i).z=cPts[i]->Pt_Point->z;
}
}


void NCurve::GetKnotVec(Vec<double>& U)
{
int i;

int iNoK = (iNoCPts)+p+1;
U.Size(iNoK);
for (i=0;i<iNoK;i++)
{
  U(i)=knots[i];
}
}

int NCurve::knotInsertion(double u, int r, Vec <C4dVector> & ncP,Vec <double> & ncU)
{
  // Compute k and s      u = [ u_k , u_k+1)  with u_k having multiplicity s
  int k=0,s=0 ;
  int i,j ;
  int deg_ = p;
  Vec <C4dVector> P;
  GetContolPts(P);
  Vec<double> U;
  GetKnotVec(U);
  if(u<U[deg_] || u>U[P.n])
  {
     //Error out of range
  }
  for(i=0;i<U.n;i++)
  {
    if(U[i]>u) 
    {
      k = i-1 ;
      break ;
    }
  }

  if(u<=U[k]){
    s = 1 ;
    for(i=k;i>deg_;i--){
      if(U[i]<=U[i-1])
	    s++ ;
      else
	break ;
    }
  }
  else{
    s=0 ;
  }

  if((r+s)>p+1)
    r = p+1-s ;

  if(r<=0)
    return 0 ; 


  ncU.Size(U.n+r);

  // Load new knot vector
  for(i=0;i<=k;i++)
    ncU[i] = U[i] ;
  for(i=1;i<=r;i++)
    ncU[k+i] = u ;
  for(i=k+1;i<U.n; i++)
    ncU[i+r] = U[i] ;

  // Save unaltered control points
  ncP.Size(P.n+r);
  Vec <C4dVector> R(p+1);

  for(i=0; i<=k-p ; i++)
    ncP[i] = P[i] ;
  for(i=k-s ; i< P.n ; i++)
    ncP[i+r] = P[i] ;
  for(i=0; i<=p-s; i++)
    R[i] = P[k-p+i] ;

  // Insert the knot r times
  int L=0;
  double alpha;
  for(j=1; j<=r ; j++){
    L = k-p+j ;
    for(i=0;i<=p-j-s;i++){
      alpha = (u-U[L+i])/(U[i+k+1]-U[L+i]) ;
      R[i] = R[i+1]*alpha + R[i]*(1.0-alpha) ;
    }
    ncP[L] = R[0] ;
    if(p-j-s > 0)
      ncP[k+r-j-s] = R[p-j-s] ;
  }

  // Load remaining control points
  for(i=L+1; i<k-s ; i++){
    ncP[i] = R[i-L] ;
  }
  P.DeleteAll();
  U.DeleteAll();
  R.DeleteAll();

  return r; 
}


void NCurve::refineKnotVector(Vec<double>& XVec,Vec <C4dVector> & P,Vec <double> & U)
{
  int deg_ = p;
  Vec <C4dVector> cP;
  GetContolPts(cP);
  Vec<double> cU;
  GetKnotVec(cU);

  int n = cP.n-1 ;
  int m = n+p+1 ;
  int a,b ;
  int r = XVec.n-1 ;


  P.Size(r+1+n+1);
  U.Size(r+1+n+1+p+1);

  a = FindSpan(XVec[0]) ;
  b = FindSpan(XVec[r]) ;
  ++b ;
  int j ;
  for(j=0; j<=a-p ; j++)
    P[j] = cP[j] ;
  for(j = b-1 ; j<=n ; j++)
    P[j+r+1] = cP[j] ;
  for(j=0; j<=a ; j++)
    U[j] = cU[j] ;
  for(j=b+p ; j<=m ; j++)
    U[j+r+1] = cU[j] ;
  int i = b+p-1 ; 
  int k = b+p+r ;
  for(j=r; j>=0 ; j--){
    while(XVec[j] <= cU[i] && i>a){
      P[k-p-1] = cP[i-p-1] ;
      U[k] = cU[i] ;
      --k ;
      --i ;
    }
    P[k-p-1] = P[k-p] ;
    for(int l=1; l<=p ; l++){
      int ind = k-p+l ;
      double alpha = U[k+l] - XVec[j] ;
      if(alpha==0.0)
	     P[ind-1] = P[ind] ;
      else
	     alpha /= U[k+l]-cU[i-p+l] ;
       P[ind-1] = P[ind-1]*alpha + P[ind]*(1.0-alpha) ;
    }
    U[k] = XVec[j] ;
    --k ;
  }
}

double NCurve::chordLengthParam(const Vec<C3dVector> & Q, Vec<double> &ub)
 {
  int i ;
  double d=0;
  C3dVector T;
  ub.Size(Q.n) ;
  ub[0] = 0 ; 
  for(i=1;i<ub.n;i++){
    T=Q[i];
    T-=Q[i-1];
    d += T.Mag();
  }
  if(d>0){
    for(i=1;i<ub.n-1;++i){
      T=Q[i];
      T-=Q[i-1];
      ub[i] = ub[i-1] + T.Mag()/d ;
    }
    ub[ub.n-1] = 1.0 ; // In case there is some addition round-off
  }
  return d ;
}

void NCurve::knotAveraging(const Vec<double>& uk, int deg, Vec<double>& U)
{
  U.Size(uk.n+deg+1);

  int j ;
  for(j=1;j<uk.n-deg;++j){
    U[j+deg] = 0.0 ;
    for(int i=j;i<j+deg;++i)
      U[j+deg] += uk[i] ;
    U[j+deg] /= deg ;
  }
  for(j=0;j<=deg;++j)
    U[j] = 0.0 ;
  for(j=U.n-deg-1;j<U.n;++j)
    U[j] = 1.0 ;
}

void NCurve::globalInterp(int d,Vec <C4dVector> &nP,Vec<double> &nU)
{
  int i,j ;
  Vec <C3dVector> Q;
  Vec <double> ub;
  p=d;
  Get3dPts(Q);
  chordLengthParam(Q,ub);

  nP.Size(Q.n) ;
  nU.Size(Q.n+d+1);

  Matrix <double> A(Q.n,Q.n) ;
  knotAveraging(ub,d,nU);

  // Initialize the basis matrix A
  double N[10];
   for(i=0;i<A.m;i++){
    for(j=0;j<A.n;j++) 
	    A(i,j) = 0;
  } 


  for(i=1;i<Q.n-1;i++){
    int span = FindSpan2(d,nU,ub[i]);
    BasisFun2(d,span,ub[i],nU,N) ;
    for(j=0;j<=d;j++) 
	    A(i,span-d+j) = N[j];
  }
  A(0,0)  = 1.0 ;
  A(Q.n-1,Q.n-1) = 1.0 ;

  //// Init matrix for LSE
  Matrix<double> qq(Q.n,3) ;
  Matrix<double> xx;
  for(i=0;i<Q.n;i++)
  {
      qq(i,0) = Q[i].x;
      qq(i,1) = Q[i].y;
      qq(i,2) = Q[i].z;
  }
  double dd;
  for (i=0;i<A.m;i++)
  {
     dd=A(i,0);
  }
  A.Invert();
  for (i=0;i<A.m;i++)
  {
     dd=A(i,0);
  }

  A.Mult(qq,xx);
  for(i=0;i<Q.n;i++)
  {
      nP[i].xw = xx(i,0);
      nP[i].yw = xx(i,1);
      nP[i].zw = xx(i,2);
      nP[i].w = 1;
  }
  //clean up
  A.DeleteAll();
  qq.DeleteAll();
  ub.DeleteAll();
  Q.DeleteAll();
  xx.DeleteAll();

  //solve(A,qq,xx) ;

  //// Store the data
  //for(i=0;i<xx.rows();i++){
  //  for(j=0;j<D;j++)
  //    P[i].data[j] = (T)xx(i,j) ;
  //  P[i].w() = 1.0 ;
  //}

}


void NCurve::AddVert(C3dVector pInVertex1, double dWght)
{


if (iNoCPts<MAX_CVPTS)
{
  cPts [iNoCPts] = new CvPt_Object();
  cPts [iNoCPts]->Create(pInVertex1,dWght,0,0,0,12,this);
  iNoCPts++;
}
else
{
  outtext1("Error max points exceeded");
}

}



void NCurve::Generate(int inp)
{
p = inp;
int i;
int ind=0;
double span;
span = 1.0/(iNoCPts-p);

for(i=0;i<p;i++)
{
  knots[ind]=0;
  ind++;
}
for(i=0;i<iNoCPts-p+1;i++)
{
  knots[ind]=span*i;
  ind++;
}
for(i=0;i<p;i++)
{
  knots[ind]=1;
  ind++;
}
}




void NCurve::GenerateExp(double Deg,Vec <C4dVector> & P,Vec<double> & U)
{
int i;
C3dVector V;
double W;
Clean();
p=Deg;
for(i=0;i<P.n;i++)
{
  if (iNoCPts<MAX_CVPTS)
  {
    W=P[i].w;
    V.x=P[i].xw/W;
    V.y=P[i].yw/W;
    V.z=P[i].zw/W;
    cPts [iNoCPts] = new CvPt_Object();
    cPts [iNoCPts]->Create(V,W,0,0,0,12,this);
    iNoCPts++;
  }
  else
  {
    outtext1("Error max points exceeded");
  }
}
for(i=0;i<U.n;i++)
{
  knots[i] = U[i];
}
}


int NCurve::FindSpan(double u)
{
int iRet;
int low,mid,high;

if (u==knots[iNoCPts])
{
  iRet=iNoCPts-1;
}
else
{
  low=p;
  high=iNoCPts;
  mid=(low+high)/2;
  while((u<knots[mid]) || (u>=knots[mid+1]))
  {
    if (u<knots[mid])
	{
	  high=mid;
	}
	else
	{
      low=mid;
	}
    mid=(low+high)/2;
  }
iRet=mid;
}
return (iRet);
}

int NCurve::FindSpan2(double deg,const Vec <double> & U, double u)
{
int iRet;
int low,mid,high;

if (u==U[iNoCPts])
{
  iRet=iNoCPts-1;
}
else
{
  low=deg;
  high=iNoCPts;
  mid=(low+high)/2;
  while((u<U[mid]) || (u>=U[mid+1]))
  {
    if (u<U[mid])
	{
	  high=mid;
	}
	else
	{
      low=mid;
	}
    mid=(low+high)/2;
  }
iRet=mid;
}
return (iRet);
}

void NCurve::BasisFun(double deg,int i,double u,double N[10])
{
int j;
int r;
double left[20];
double right[20];
double saved;
double temp;
N[0]=1.0;
for (j=1;j<=deg;j++)
{
  left[j]=u-knots[i+1-j];
  right[j]=knots[i+j]-u;
  saved=0.0;
  for (r=0;r<j;r++)
  {
    temp=N[r]/(right[r+1]+left[j-r]);
	  N[r]=saved+right[r+1]*temp;
    saved=left[j-r]*temp;
  }
  N[j]=saved;
}
}

void NCurve::BasisFun2(double deg,int i,double u,const Vec <double> & U,double N[10])
{
int j;
int r;
double left[20];
double right[20];
double saved;
double temp;
N[0]=1.0;
for (j=1;j<=deg;j++)
{
  left[j]=u-U[i+1-j];
  right[j]=U[i+j]-u;
  saved=0.0;
  for (r=0;r<j;r++)
  {
    temp=N[r]/(right[r+1]+left[j-r]);
	  N[r]=saved+right[r+1]*temp;
    saved=left[j-r]*temp;
  }
  N[j]=saved;
}
}

void NCurve::binomialCoef(Mat* Bin)
{
  int n,k ;
  // Setup the first line
  *Bin->mn2(0,0) = 1.0 ;
  for(k=Bin->n-1;k>0;--k)
  {
    *Bin->mn2(0,k) = 0.0 ;
  }
  // Setup the other lines
  for(n=0;n<Bin->m-1;n++)
  {
    *Bin->mn2(n+1,0) = 1.0 ;
    for(k=1;k<Bin->n;k++)
    {
      if(n+1<k)
	      *Bin->mn2(n,k) = 0.0 ;
      else
	      *Bin->mn2(n+1,k) = *Bin->mn2(n,k) + *Bin->mn2(n,k-1) ;
    }
  }
}

void NCurve::deriveAt(double u,int d,C3dVector CK[10])
{
  C4dVector ders[10];
  int deg_=p;
  int du;
  du = d;
  if (deg_ < d)
  {
    du = deg_;
  }
  int iSpan ;
  Mat* derF ;

  iSpan = FindSpan(u) ;
  derF = dersBasisFuns(du,u,iSpan) ;

  int k;
  for(k=du;k>=0;--k)
  {
    ders[k].Clear();
    for(int j=deg_;j>=0;--j)
    {
      ders[k].xw += *derF->mn2(k,j)*(cPts[iSpan-deg_+j]->Pt_Point->x*cPts[iSpan-deg_+j]->w) ;
      ders[k].yw += *derF->mn2(k,j)*(cPts[iSpan-deg_+j]->Pt_Point->y*cPts[iSpan-deg_+j]->w) ;
      ders[k].zw += *derF->mn2(k,j)*(cPts[iSpan-deg_+j]->Pt_Point->z*cPts[iSpan-deg_+j]->w) ;
      ders[k].w += *derF->mn2(k,j)*(cPts[iSpan-deg_+j]->w) ;
    }
  }
    Mat* Bin = new Mat(d+1,d+1);
    binomialCoef(Bin);
    C3dVector v;
    int i;
    for (k=0;k<=du;k++)
    {
     v.x=ders[k].xw;
     v.y=ders[k].yw;
     v.z=ders[k].zw;
     for (i=1;i<=k;i++)
     {
       v.x=v.x-(*Bin->mn2(k,i))*ders[i].w*CK[k-i].x;
       v.y=v.y-(*Bin->mn2(k,i))*ders[i].w*CK[k-i].y;
       v.z=v.z-(*Bin->mn2(k,i))*ders[i].w*CK[k-i].z;
     }
     CK[k].x=v.x/ders[0].w;
     CK[k].y=v.y/ders[0].w;
     CK[k].z=v.z/ders[0].w;
    }
  delete(derF);
  delete(Bin);
}


Mat* NCurve::dersBasisFuns(int n,double u, int span)  
{
int deg_ =p;
double* left = new double[2*(deg_+1)]; 
double* right = &left[deg_+1] ;
  
Mat* ndu= new Mat(deg_+1,deg_+1);
double saved,temp ;
int j,r ;

Mat*  ders= new Mat(n+1,deg_+1) ;

  *ndu->mn2(0,0) = 1.0 ;
  for(j=1; j<= deg_ ;j++)
  {
    left[j] = u-knots[span+1-j] ;
    right[j] = knots[span+j]-u ;
    saved = 0.0 ;
    for(r=0;r<j ; r++)
    {
      // Lower triangle
      *ndu->mn2(j,r) = right[r+1]+left[j-r] ;
      temp = *ndu->mn2(r,j-1)/(*ndu->mn2(j,r)) ;
      // Upper triangle
      *ndu->mn2(r,j) = saved+right[r+1] * temp ;
      saved = left[j-r] * temp ;
    }

    *ndu->mn2(j,j) = saved ;
  }

  for(j=deg_;j>=0;--j)
    *ders->mn2(0,j) = *ndu->mn2(j,deg_) ;

  // Compute the derivatives
  Mat* a = new Mat(deg_+1,deg_+1) ;
  for(r=0;r<=deg_;r++){
    int s1,s2 ;
    s1 = 0 ; s2 = 1 ; // alternate rows in array a
    *a->mn2(0,0) = 1.0 ;
    // Compute the kth derivative
    for(int k=1;k<=n;k++){
      double d ;
      int rk,pk,j1,j2 ;
      d = 0.0 ;
      rk = r-k ; pk = deg_-k ;

      if(r>=k)
      {
	      *a->mn2(s2,0) = (*a->mn2(s1,0))/(*ndu->mn2(pk+1,rk)) ;
	      d = *a->mn2(s2,0)*(*ndu->mn2(rk,pk));
      }

      if(rk>=-1){
	      j1 = 1 ;
      }
      else{
	      j1 = -rk ;
      }

      if(r-1 <= pk){
	       j2 = k-1 ;
      }
      else{
	       j2 = deg_-r ;
      }

      for(j=j1;j<=j2;j++)
      {
	      *a->mn2(s2,j) = (*a->mn2(s1,j)-*a->mn2(s1,j-1))/(*ndu->mn2(pk+1,rk+j)) ;
	      d += *a->mn2(s2,j)**ndu->mn2(rk+j,pk) ;
      }
      
      if(r<=pk)
      {
	     *a->mn2(s2,k) = -(*a->mn2(s1,k-1))/(*ndu->mn2(pk+1,r)) ;
	     d += *a->mn2(s2,k)*(*ndu->mn2(r,pk)) ;
      }
      *ders->mn2(k,r) = d ;
      j = s1 ; s1 = s2 ; s2 = j ; // Switch rows
    }
  }

  // Multiply through by the correct factors
  r = deg_ ;
  for(int k=1;k<=n;k++)
  {
    for(j=deg_;j>=0;--j)
      *ders->mn2(k,j) *= r ;
    r *= deg_-k ;
  }
delete (a);
delete (left);
delete (ndu);
return (ders);
}

void NCurve::CPolyRot(double dAng)
{
int i;
C3dVector vT1,a,b;
for (i = 0; i < iNoCPts; i++)
{
   vT1.x = cPts [i]->Pt_Point->x;
   vT1.y = cPts [i]->Pt_Point->y;
   vT1.z = cPts [i]->Pt_Point->z;
   vT1.Rotate(a,b,dAng);
   cPts [i]->Pt_Point->x = vT1.x;
   cPts [i]->Pt_Point->y = vT1.y;
   cPts [i]->Pt_Point->z = vT1.z;
}
}


void NCurve::Translate (C3dVector vIn)
{
int i;

for (i = 0; i < iNoCPts; i++)
{
  cPts[i]->Pt_Point->x+=vIn.x;  
  cPts[i]->Pt_Point->y+=vIn.y;
  cPts[i]->Pt_Point->z+=vIn.z;
}
}

void NCurve::ScaleX(double d)
{
int i;

for (i = 0; i < iNoCPts; i++)
{
  cPts[i]->Pt_Point->x*=d;  
}
}

void NCurve::ScaleW(double dIn)
{
int i;
for (i = 0; i < iNoCPts; i++)
{
  cPts[i]->w*=dIn;  
}
}

int NCurve::GetOrder()
{

return (p);
}

C3dVector NCurve::MinPt(C3dVector inPt)
{
C3dVector vRet;
const double dTol = 0.000000001;
const double dIncs = 36;
int i;
double dStp = 1/dIncs;
double dlStp;
double dW=0;
double dMinW=0;
C3dVector cPt;
C3dVector tPt;
C3dVector cNextPt;
double dWScl;
double Dist;
double minDist = 1e36;
C3dVector v1;
C3dVector v2;
double dM;
double dDot;
cPt=GetPt(dW);
tPt=GetPt(dW+dStp);
dWScl = cPt.Dist(tPt);
for(i=0;i<dIncs;i++)
{
  dW=i*dStp;
  cPt=GetPt(dW);
  Dist=cPt.Dist(inPt);
  if (Dist<minDist)
  {
    minDist=Dist;
    dMinW=dW;
  }
}
//start of iteration
dW=dMinW;
dlStp=dStp;
i=0;
do
{
  cPt=GetPt(dW);
  //cNextPt=GetPt(dW+0.000001);
  //v1=cNextPt;
  //v1-=cPt;
  v1=GetDir(dW);
  v2=inPt;
  v2-=cPt;
  dM=v2.Mag();
  v1.Normalize();
  v2.Normalize();
  dDot=v2.Dot(v1);
  dlStp=(dM*dDot/dWScl)*1*dStp;
  dW=dW+dlStp;
  if (dW>1)
    dW=1;
  if (dW<0)
    dW=0;
  i++;
}
while ((pow((dlStp*dlStp),0.5)>dTol) && (i<100));
vRet=GetPt(dW);
return (vRet);
}

double NCurve::MinWPt(C3dVector inPt)
{
C3dVector vRet;
const double dTol = 0.000001;
const double dIncs = 36;
int i;
double dStp = 1/dIncs;
double dlStp;
double dW=0;
double dMinW=0;
C3dVector cPt;
C3dVector tPt;
C3dVector cNextPt;
double dWScl;
double Dist;
double minDist = 1e36;
C3dVector v1;
C3dVector v2;
double dM;
double dDot;
cPt=GetPt(dW);
tPt=GetPt(dW+dStp);
dWScl = cPt.Dist(tPt);
for(i=0;i<dIncs;i++)
{
  dW=i*dStp;
  cPt=GetPt(dW);
  Dist=cPt.Dist(inPt);
  if (Dist<minDist)
  {
    minDist=Dist;
    dMinW=dW;
  }
}
//start of iteration
dW=dMinW;
dlStp=dStp;
i=0;
do
{
  cPt=GetPt(dW);
  //cNextPt=GetPt(dW+0.0000001);
  //v1=cNextPt;
  v1=GetDir(dW);
  v2=inPt;
  v2-=cPt;
  dM=v2.Mag();
  v1.Normalize();
  v2.Normalize();
  dDot=v2.Dot(v1);
  dlStp=(dM*dDot/dWScl)*1*dStp;
  dW=dW+dlStp;
  if (dW<0)
  {
    dW=0;
  }
  if (dW>1)
  {
    dW=1;
  }
  i++;
}
while ((pow((dlStp*dlStp),0.5)>dTol) & (i<10000));
vRet=GetPt(dW);
return (dW);
}

NCurveOnSurf* NCurve::GetSurfaceCV(NSurf* pSurf)
{
int i;
C3dVector pt;
NCurveOnSurf* pS = new NCurveOnSurf();
pS->Drawn = Drawn;
pS->Selectable  = Selectable; 
pS->Visable  = Visable;
pS->G_Colour = G_Colour;
pS->iObjType = 13;
pS->G_label = G_label;
pS->iNoCPts = iNoCPts;
pS->p = p;
pS->ws = ws;
pS->we = we;
pS->pParent=pSurf;

for (i=0;i<iNoCPts+p+1;i++)
{
  pS->knots[i]=knots[i];
}

for (i=0;i<iNoCPts;i++)
{
  pt=cPts[i]->Pt_Point;
  pt=pSurf->MinPtW(pt);
  pS->cPts[i]=new CvPt_Object();
  pS->cPts[i]->Create(pt,cPts[i]->w,-1,55,1,1,pS);
}
return(pS);
}


void NCurve::DrawCtrlPtsTog()
{
if (DrawCPts==TRUE)
{
  DrawCPts=FALSE;
}
else
{
  DrawCPts=TRUE;
}
}


void NCurve::OglDraw(int iDspFlgs,double dS1,double dS2)
{
OglDrawW(iDspFlgs,dS1,dS2);
}

void NCurve::OglDrawCtrlPts()
{
int i;
glColor3fv(cols[G_Colour]);
glPointSize(5.0f);
glBegin(GL_POINTS);
for (i = 0; i < iNoCPts; i++)
{
  glVertex3f((float) cPts[i]->Pt_Point->x,(float) cPts[i]->Pt_Point->y,(float) cPts[i]->Pt_Point->z);
}
glEnd();
}

void NCurve::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[80];
if ((iDspFlgs & DSP_CURVES)>0)
{
Selectable=1;
int i;
glColor3fv(cols[G_Colour]);
if (DrawCPts==TRUE)
{
  OglDrawCtrlPts();
}
C3dVector vPt;
C3dVector vPt2;
double dw=0;
double dSpan;
double dInc=0.01;
int iNo;

dSpan = we-ws;
if (p>0)
{
  double dt;
  dt= dSpan/dInc;
  iNo = (int) dt;
}
//else
//{
//  iNo = 2;
//  dInc = dSpan;
//}
  
vPt=GetPt(ws);
dw=ws;

glBegin(GL_LINES);
for (i = 0; i < iNo; i++)
{
  dw=dw+dInc;
  if (dw>1.0){dw=1;}
  vPt2=GetPt(dw);
  glVertex3f((float) vPt.x,(float) vPt.y,(float) vPt.z);
  glVertex3f((float) vPt2.x,(float) vPt2.y,(float) vPt2.z);
  vPt=vPt2;
}
glEnd();

  C3dVector vCent;
  vCent=Get_Centroid();
  if (bDrawLab==TRUE)
	{
	  sprintf_s(sLab,"C%i",G_label);
	  OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
	}
}
else
{
  Selectable=0;
}
}

double NCurve::getLen()
{
int i;
C3dVector p1;
C3dVector p2;
double dw=0;
double dLen=0;
for (i=0;i<99;i++)
{
  p1=GetPt(dw);
  p2=GetPt(dw+0.01);
  p1-=p2;
  dLen+=p1.Mag();
  dw+=0.01;
}
return (dLen);
}

void NCurve::Reverse()
{
int i;
CvPt_Object* cPtsCp[MAX_CTPTS];
//Note IMPORTANT for a non uniform knot seq
//Need to reverse that to
for (i=0;i<iNoCPts;i++)
{
  cPtsCp[i] = cPts[iNoCPts-i-1];
}
for (i=0;i<iNoCPts;i++)
{
  cPts[i] = cPtsCp[i];
}
}


void NCurve::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
int i;
G_Object::SetToScr(pModMat,pScrTran);
pModZ = pModMat;
pScrZ = pScrTran;
for (i = 0; i < iNoCPts; i++)
{
  cPts[i]->SetToScr(pModMat,pScrTran);
}
}

void NCurve::Transform(C3dMatrix TMat)
{
int i;
for (i = 0; i < iNoCPts; i++)
{
  cPts[i]->Transform(TMat);
}
}


void NCurve::HighLight(CDC* pDC)
{
double dw=0;
double dSpan;
double dInc=0.01;
C3dVector vPt;
int iNo;
int i;

dSpan = we-ws;
double dt;
dt=dSpan/dInc;
iNo = (int) dt;
dw=ws;
vPt=GetPt(dw);
Pt_Object* ThePoint = new Pt_Object;
ThePoint->Create(vPt,1,0,0,11,0,0,NULL);
ThePoint->SetToScr(pModZ,pScrZ);
pDC->MoveTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);
for (i=0;i<iNo-1;i++)
{
  dw=dw+dInc;
  vPt=GetPt(dw);
  ThePoint->Pt_Point->x = vPt.x; 
  ThePoint->Pt_Point->y = vPt.y;
  ThePoint->Pt_Point->z = vPt.z;
  ThePoint->SetToScr(pModZ,pScrZ);
  pDC->LineTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);  
}
delete(ThePoint);
}

G_ObjectD NCurve::SelDist(CPoint InPT,Filter FIL)
{
G_ObjectD Ret;
double MinDist = 1e36;
double dDist = 0;
double dw=0;
double dSpan;
double dInc=0.01;
C3dVector vPt;
int iNo;
int i;

dSpan = we-ws;
double dt;
dt=dSpan/dInc;
iNo = (int) dt;
dw=ws;

Pt_Object* ThePoint = new (Pt_Object);
ThePoint->Create(vPt,0,0,0,11,0,0,NULL);
for (i = 0; i < iNo-1; i++)
{	 
	vPt = GetPt (dw);
	if ((dw>0.05) && (dw<0.95))
	{
	  ThePoint->Pt_Point->x = vPt.x;
      ThePoint->Pt_Point->y = vPt.y;
      ThePoint->Pt_Point->z = vPt.z;
	  ThePoint->SetToScr(pModZ,pScrZ);
      dDist = pow((ThePoint->DSP_Point->x-InPT.x),2)+pow((ThePoint->DSP_Point->y-InPT.y),2);
	  if (dDist < MinDist)
	  {
        MinDist = dDist;
	  }
	}
	dw=dw+dInc;
}
delete(ThePoint);
Ret.pObj=NULL;


if (FIL.isFilter(0))
{
for (i = 0; i < iNoCPts; i++)
  {
    dDist = pow((cPts[i]->DSP_Point->x-InPT.x),2)+pow((cPts[i]->DSP_Point->y-InPT.y),2);
    if (dDist <= MinDist)
    {
      MinDist = dDist;
      Ret.Dist=MinDist;
      Ret.pObj=cPts[i];
    }
  }
}

if (Ret.pObj==NULL)
{
  Ret.Dist=MinDist;
  Ret.pObj=this;
}
return (Ret);
}


C3dVector NCurve::GetPt(double w)
{
C4dVector Pt;
C4dVector PtSum;
C3dVector vR;
int iSpan;
int i;
double N[20];
if (w>1)
  w=1;
//if (w<0)
//  w=0;
iSpan = FindSpan(w);
BasisFun(p,iSpan,w,N);
PtSum.Clear();
for (i=0;i<=p;i++)
{

  Pt.xw = cPts[iSpan-p+i]->Pt_Point->x*cPts[iSpan-p+i]->w;
  Pt.yw = cPts[iSpan-p+i]->Pt_Point->y*cPts[iSpan-p+i]->w;
  Pt.zw = cPts[iSpan-p+i]->Pt_Point->z*cPts[iSpan-p+i]->w;
  Pt.w = cPts[iSpan-p+i]->w;
  PtSum=PtSum+Pt*N[i];
}
vR.x=PtSum.xw/PtSum.w;
vR.y=PtSum.yw/PtSum.w;
vR.z=PtSum.zw/PtSum.w;
return (vR);
}


C3dVector NCurve::GetDir(double w)
{
C3dVector DirA[10];
deriveAt(w,1,DirA);
return (DirA[1]);
}


IMPLEMENT_DYNAMIC(NCurveOnSurf, CObject)

//BlowsR
void NCurveOnSurf::Create(int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 13;
iNoCPts=0;
p=3;
ws=0.0;
we=1.0;
pParent=Parrent;
DrawCPts=FALSE;
DrawNoCvs=FALSE;
}

C3dVector NCurveOnSurf::Get_Centroid()
{
BOOL isCir;
C3dVector v1;
C3dVector v2;
C3dVector vRet;
isCir=isCircle();
if (isCir==TRUE)
{
   v1=GetPt(0.0);
   v2=GetPt(0.5);
   vRet=(v2-v1);
   vRet*=0.5;
   vRet+=v1;
}
else
{
  vRet=GetPt(0.5);
}
return (vRet);
}

BOOL NCurveOnSurf::isCircle()
{
// this need to be more of a verbose check
// doing it quickly
C3dVector v1;
C3dVector v2;
BOOL bRet;
bRet=FALSE;
double dMag;

if (iNoCPts==9)
{
  v1=cPts[0]->Pt_Point;
  v2=cPts[8]->Pt_Point;
  v1-=v2;
  dMag=v1.Mag();
  if (dMag<0.000000001)
  {
    bRet=TRUE;
  }
}
return (bRet);
}

void NCurveOnSurf::AddVert(C3dVector pInVertex1, double dWght)
{
if (iNoCPts<MAX_CVPTS)
{
  cPts [iNoCPts] = new CvPt_ObjectW();
  cPts [iNoCPts]->Create(pInVertex1,dWght,0,0,0,12,this);
  iNoCPts++;
}
else
{
  outtext1("Error max points exceeded");
}
}

void NCurveOnSurf::OglDrawW(int iDspFlgs)
{
int i;
double dw=0;
double dSpan;
double dInc=0.01;
C3dVector vPt;
C3dVector vPt2;
double dt;
int iNo;
if (pParent!=NULL)
{
  NSurf* pS= (NSurf*) pParent;
  glColor3fv(cols[G_Colour]);
  dSpan = we-ws;
  dt= dSpan/dInc;
  iNo = (int) dt;
  vPt=NCurve::GetPt(ws);
  vPt=pS->GetPt(vPt.x,vPt.y);
  dw=ws;
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1,0x0101);
  glBegin(GL_LINES);
  for (i = 0; i < iNo; i++)
  {
    dw=dw+dInc;
    if (dw>1.0){dw=1;}
    vPt2=NCurve::GetPt(dw);
    vPt2=pS->GetPt(vPt2.x,vPt2.y);
    glVertex3f((float) vPt.x,(float) vPt.y,(float) vPt.z);
    glVertex3f((float) vPt2.x,(float) vPt2.y,(float) vPt2.z);
    vPt=vPt2;
  }
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}
}

//void NCurveOnSurf::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
//{
//int i;
//pModZ = pModMat;
//pScrZ = pScrTran;
//C3dVector V;
//C3dVector R;
//NSurf* pS;
//double x,y,w;
//pS=(NSurf*) this->pParent;
//
//for (i = 0; i < iNoCPts; i++)
//{
//  x=cPts[i]->Pt_Point->x;
//  y=cPts[i]->Pt_Point->y;
//  w=cPts[i]->w;
//  R=pS->GetPt(x/w,y/w);
//
//  V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
//  V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
//  V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;
//  R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
//  R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
//  R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;
//  cPts[i]->DSP_Point->x = R.x;
//  cPts[i]->DSP_Point->y = R.y;
//  cPts[i]->DSP_Point->z = 0;
//}
//}

G_ObjectD NCurveOnSurf::SelDist(CPoint InPT,Filter FIL)
{
G_ObjectD Ret;
double MinDist = 1e36;
double dDist = 0;
double dw=0;
double dSpan;
double dInc=0.01;
double dt;
Pt_Object* ThePoint = new (Pt_Object);
C3dVector vPt;
int iNo;
int i;
if (pParent!=NULL)
{
  NSurf* pS= (NSurf*) pParent;
  dSpan = we-ws;
  dt=dSpan/dInc;
  iNo = (int) dt;
  dw=ws;
  ThePoint->Create(vPt,0,0,0,11,0,0,NULL);
  for (i = 0; i < iNo-1; i++)
  {	 
    vPt = NCurve::GetPt (dw);
    vPt=pS->GetPt(vPt.x,vPt.y);
	  if ((dw>0.05) && (dw<0.95))
	  {
	    ThePoint->Pt_Point->x = vPt.x;
        ThePoint->Pt_Point->y = vPt.y;
        ThePoint->Pt_Point->z = vPt.z;
	    ThePoint->SetToScr(pModZ,pScrZ);
        dDist = pow((ThePoint->DSP_Point->x-InPT.x),2)+pow((ThePoint->DSP_Point->y-InPT.y),2);
	    if (dDist < MinDist)
	    {
        MinDist = dDist;
	    }
	  }
	  dw=dw+dInc; 
  } 

  Ret.pObj=NULL;
  if (FIL.isFilter(0))
  {
  for (i = 0; i < iNoCPts; i++)
    {
      dDist = pow((cPts[i]->DSP_Point->x-InPT.x),2)+pow((cPts[i]->DSP_Point->y-InPT.y),2);
      if (dDist <= MinDist)
      {
        MinDist = dDist;
        Ret.Dist=MinDist;
        Ret.pObj=cPts[i];
      }
    }
  }

  if (Ret.pObj==NULL)
  {
    Ret.Dist=MinDist;
    Ret.pObj=this;
  }
}
delete(ThePoint);
return (Ret);
}


C3dVector NCurveOnSurf::GetPt(double w)
{
C3dVector Pt;
if (pParent!=NULL)
{
  NSurf* pS= (NSurf*) pParent;
  Pt=NCurve::GetPt(w);
  Pt = pS->GetPt(Pt.x,Pt.y);
}
return (Pt);
}

void NCurveOnSurf::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    G_Object::Serialize(ar);
	  ar << iNoCPts;
    ar << p;
    ar << ws;
    ar << we;
	  ar << DrawCPts;
	  for (i=0;i<iNoCPts;i++)
    {
      cPts[i]->Serialize(ar);
    }
    for (i=0;i<iNoCPts+p+1;i++)
    {
        ar << knots[i];
    }
	}
	else
	{
    G_Object::Serialize(ar);
	  ar >> iNoCPts;
    ar >> p;
    ar >> ws;
    ar >> we;
	  ar >> DrawCPts;
	  for (i=0;i<iNoCPts;i++)
    {
      cPts[i]=new CvPt_ObjectW();
      cPts[i]->Serialize(ar);
      cPts[i]->pParent=this;
    }
    for (i=0;i<iNoCPts+p+1;i++)
    {
      ar >> knots[i];
    }
	}
}

void NCurveOnSurf::HighLight(CDC* pDC)
{
double dw=0;
double dSpan;
double dInc=0.1;
C3dVector vPt;
int iNo;
int i;
double dt;
Pt_Object* ThePoint = new Pt_Object;
if (pParent!=NULL)
{
  NSurf* pS= (NSurf*) pParent;
  dSpan = we-ws;
  dt=dSpan/dInc;
  iNo = (int) dt;
  dw=ws;
  vPt=NCurve::GetPt(dw);
  vPt=pS->GetPt(vPt.x,vPt.y);
  ThePoint->Create(vPt,1,0,0,11,0,0,NULL);
  ThePoint->SetToScr(pModZ,pScrZ);
  pDC->MoveTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);
  for (i=0;i<iNo-1;i++)
  {
    dw=dw+dInc;
    vPt=NCurve::GetPt(dw);
    vPt=pS->GetPt(vPt.x,vPt.y);
    ThePoint->Pt_Point->x = vPt.x; 
    ThePoint->Pt_Point->y = vPt.y;
    ThePoint->Pt_Point->z = vPt.z;
    ThePoint->SetToScr(pModZ,pScrZ);
    pDC->LineTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);  
  }
}
delete(ThePoint);
}

C3dVector NCurveOnSurf::MinPt(C3dVector inPt)
{
C3dVector vRet;
const double dTol = 0.000000001;
const double dIncs = 36;
int i;
double dStp = 1/dIncs;
double dlStp;
double dW=0;
double dMinW=0;
C3dVector cPt;
C3dVector tPt;
C3dVector cNextPt;
double dWScl;
double Dist;
double minDist = 1e36;
C3dVector v1;
C3dVector v2;
double dM;
double dDot;
if (pParent!=NULL)
{
  NSurf* pS= (NSurf*) pParent;
  cPt=NCurve::GetPt(dW);
  cPt=pS->GetPt(cPt.x,cPt.y);
  tPt=NCurve::GetPt(dW+dStp);
  tPt=pS->GetPt(tPt.x,tPt.y);
  dWScl = cPt.Dist(tPt);
  for(i=0;i<dIncs;i++)
  {
    dW=i*dStp;
    cPt=NCurve::GetPt(dW);
    cPt=pS->GetPt(cPt.x,cPt.y);
    Dist=cPt.Dist(inPt);
    if (Dist<minDist)
    {
      minDist=Dist;
      dMinW=dW;
    }
  }
//start of iteration
  dW=dMinW;
  dlStp=dStp;
  i=0;
  do
  {
    cPt=NCurve::GetPt(dW);
    cPt=pS->GetPt(cPt.x,cPt.y);
    cNextPt=NCurve::GetPt(dW+0.000001);
    cNextPt=pS->GetPt(cNextPt.x,cNextPt.y);
    v1=cNextPt;
    v1-=cPt;
    v2=inPt;
    v2-=cPt;
    dM=v2.Mag();
    v1.Normalize();
    v2.Normalize();
    dDot=v2.Dot(v1);
    dlStp=(dM*dDot/dWScl)*1*dStp;
    dW=dW+dlStp;
    i++;
  }
  while ((pow((dlStp*dlStp),0.5)>dTol) && (i<100));
  vRet=NCurve::GetPt(dW);
  vRet=pS->GetPt(vRet.x,vRet.y);
}
return (vRet);
}

G_Object* NCurveOnSurf::Copy(G_Object* Parrent)
{
int i;
C3dVector pt;
NCurveOnSurf* pS = new NCurveOnSurf();
pS->Drawn = Drawn;
pS->Selectable  = Selectable; 
pS->Visable  = Visable;
pS->G_Colour = G_Colour;
pS->iObjType = 13;
pS->G_label = G_label;
pS->iNoCPts = iNoCPts;
pS->p = p;
pS->ws = ws;
pS->we = we;
pS->pParent=Parrent;

for (i=0;i<iNoCPts+p+1;i++)
{
  pS->knots[i]=knots[i];
}

for (i=0;i<iNoCPts;i++)
{
  pS->cPts[i]=new CvPt_Object();
  pS->cPts[i]=(CvPt_Object*) cPts[i]->Copy(Parrent);
}
return(pS);
}

void NCurveOnSurf::TrimOGL(GLUnurbsObj* pSurf)
{
int ku;
int i;
int iInd;
GLfloat* ctrlpts;
GLfloat* KnotsU;
ku=iNoCPts+p+1;
KnotsU = (GLfloat*) malloc(ku*sizeof(GLfloat));
for (i = 0;i < ku;i++)
{
 KnotsU[i] = (float) knots[i];
}
ctrlpts = (GLfloat*) malloc(3*iNoCPts*sizeof(GLfloat));
iInd=0;
double w;
for (i=0;i<iNoCPts;i++)
  {
    w=cPts[i]->w;
    ctrlpts[iInd]   = (float) cPts[i]->Pt_Point->x*w;
    ctrlpts[iInd+1] = (float) cPts[i]->Pt_Point->y*w;
    ctrlpts[iInd+2] = (float) w;
    iInd = iInd+3;
  }
gluNurbsCurve (pSurf, ku, KnotsU, 3, ctrlpts, p+1, GLU_MAP1_TRIM_3);
free(ctrlpts);
free(KnotsU);
}

IMPLEMENT_DYNAMIC(NCircle, CObject)

void NCircle::Create(C3dVector vN,C3dVector vC,double dRad,int iLab,G_Object* Parrent)
{
ws=0;
we=1;
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 8;
dRadius = dRad;
pParent=Parrent;
iNoCPts=0;
p=2;
ws=0.0;
we=1.0;
vNorm=vN;
//Note vCent gets set after the followin transformations
//don't set it explicitly here
vCent.Set(0,0,0);
C3dVector vPt;

double r2 = 0.70710678118654752440084436210485;

vPt.x = dRadius; vPt.y = 0; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = dRadius; vPt.y = dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = 0; vPt.y = dRadius; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = -dRadius; vPt.y = dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = -dRadius; vPt.y = 0; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = -dRadius; vPt.y = -dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = 0; vPt.y = -dRadius; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = dRadius; vPt.y = -dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = dRadius; vPt.y = 0; vPt.z = 0;
AddVert(vPt, 1);

knots[0]=0;
knots[1]=0;
knots[2]=0;

knots[3]=0.25;
knots[4]=0.25;

knots[5]=0.5;
knots[6]=0.5;

knots[7]=0.75;
knots[8]=0.75;

knots[9]=1.0;
knots[10]=1.0;
knots[11]=1.0;

C3dMatrix RMat;
RMat=RMat.CalcTran(vN);
C3dMatrix TMat;
this->Transform(RMat);
TMat.Translate(vC.x,vC.y,vC.z);
this->Transform(TMat);
vCent.Set(vC.x,vC.y,vC.z);
}

void NCircle::Create2(C3dVector vN,C3dVector vC,C3dVector vR,double dRad,int iLab,G_Object* Parrent)
{
ws=0;
we=1;
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 8;
dRadius = dRad;
pParent=Parrent;
iNoCPts=0;
p=2;
ws=0.0;
we=1.0;
vNorm=vN;
vCent=vC;


C3dVector vPt;

double r2 = 0.70710678118654752440084436210485;

vPt.x = dRadius; vPt.y = 0; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = dRadius; vPt.y = dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = 0; vPt.y = dRadius; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = -dRadius; vPt.y = dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = -dRadius; vPt.y = 0; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = -dRadius; vPt.y = -dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = 0; vPt.y = -dRadius; vPt.z = 0;
AddVert(vPt, 1);
vPt.x = dRadius; vPt.y = -dRadius; vPt.z = 0;
AddVert(vPt, r2);
vPt.x = dRadius; vPt.y = 0; vPt.z = 0;
AddVert(vPt, 1);

knots[0]=0;
knots[1]=0;
knots[2]=0;

knots[3]=0.25;
knots[4]=0.25;

knots[5]=0.5;
knots[6]=0.5;

knots[7]=0.75;
knots[8]=0.75;

knots[9]=1.0;
knots[10]=1.0;
knots[11]=1.0;

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
this->Transform(RMat);
TMat.Translate(vC.x,vC.y,vC.z);
this->Transform(TMat);
vNorm=vN;
vCent=vC;
}

void NCircle::Serialize(CArchive& ar)
{
NCurve::Serialize(ar);
if (ar.IsStoring())
{
		// TODO: add storing code here
  vNorm.Serialize(ar);
  vCent.Serialize(ar);
  ar<<dRadius;
}
else
{
  vNorm.Serialize(ar);
  vCent.Serialize(ar);
  ar>>dRadius;
}
}

C3dVector NCircle::Get_Centroid()
{
return(vCent);
}

void NCircle::Reverse()
{
int i;
C3dVector* p[9];
double w[9];
vNorm = -vNorm;

for (i=0;i<9;i++)
{
  p[i] = cPts[i]->Pt_Point;
  w[i] =cPts[i]->w;
}
for (i=0;i<9;i++)
{
  cPts[i]->Pt_Point = p[8-i];
  cPts[i]->w = w[8-i];
}

ws=1-we;
we=1;

}

G_Object* NCircle::Copy(G_Object* Parrent)
{

NCircle* cPoly =  new NCircle();
int i;

cPoly->Drawn = Drawn;
cPoly->Selectable  = Selectable; 
cPoly->Visable  = Visable;
cPoly->G_Colour = G_Colour;
cPoly->iObjType = iObjType;
cPoly->G_label = G_label;
cPoly->iNoCPts = iNoCPts;
cPoly->p = p;
cPoly->ws = ws;
cPoly->we = we;
cPoly->pParent=Parrent;
cPoly->dRadius=dRadius;
for (i=0;i<iNoCPts;i++)
{
  cPoly->cPts[i]=new CvPt_Object();
  cPoly->cPts[i]=(CvPt_Object*) cPts[i]->Copy(cPoly);
}
for (i=0;i<iNoCPts+p+1;i++)
{
  cPoly->knots[i]=knots[i];
}

cPoly->vCent=vCent;
cPoly->vNorm=vNorm;
return(cPoly);
}

void NCircle::Translate(C3dVector vIn)
{
NCurve::Translate(vIn);
vCent+=vIn;
}

void NCircle::Transform(C3dMatrix TMat)
{
  NCurve::Transform(TMat);
  vCent=TMat.Mult(vCent);
  TMat.m_30=0;
  TMat.m_31=0;
  TMat.m_32=0;
  vNorm=TMat.Mult(vNorm);
}


void NCircle::Info()
{
  char S1[80];
  sprintf_s(S1,"%s%i%s%i%s%i","Type ",iObjType,"; Label ",G_label," Col; ",G_Colour);
  outtext1("CIRCLE OBJECT");
  outtext1(S1); 
  sprintf_s(S1,"%s%f","Radius : ",dRadius);
  outtext1(S1); 
  sprintf_s(S1,"%s%f%s%f%s%f","Centre : ",vCent.x,",",vCent.y,",",vCent.z);
  outtext1(S1); 
  sprintf_s(S1,"%s%f%s%f%s%f","Normal : ",vNorm.x,",",vNorm.y,",",vNorm.z);
  outtext1(S1);
  outtext1("    ****");
}


IMPLEMENT_DYNAMIC(NLine, CObject)

void NLine::Create(C3dVector vP1,C3dVector vP2,int iLab,G_Object* Parrent)
{

Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 3;
G_label = iLab;
iObjType = 9;
pParent=Parrent;
iNoCPts=0;
p=1;
ws=0.0;
we=1.0;


AddVert(vP1, 1);
AddVert(vP2, 1);

knots[0]=0.0;
knots[1]=0.0;
knots[2]=1.0;
knots[3]=1.0;
}




void NLine::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
int i;
glColor3fv(cols[G_Colour]);
C3dVector vPt1;
C3dVector vPt2;
vPt1=GetPt(ws);
vPt2=GetPt(we);

glBegin(GL_LINES);
for (i = 0; i < iNoCPts-1; i++)
{
  glVertex3f((float) vPt1.x,(float) vPt1.y,(float) vPt1.z);
  glVertex3f((float) vPt2.x,(float) vPt2.y,(float) vPt2.z);
}
glEnd();
}



void NLine::HighLight(CDC* pDC)
{
double dw=0;
double dSpan;
double dInc=0.01;
C3dVector vPt;
int iNo;
dSpan = we-ws;
double dt;
dt=dSpan/dInc;
iNo = (int) dt;
dw=ws;
vPt=GetPt(ws);
Pt_Object* ThePoint = new Pt_Object;
ThePoint->Create(vPt,1,0,0,11,0,0,NULL);
ThePoint->SetToScr(pModZ,pScrZ);
pDC->MoveTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);
vPt=GetPt(we);
ThePoint->Pt_Point->x = vPt.x; 
ThePoint->Pt_Point->y = vPt.y;
ThePoint->Pt_Point->z = vPt.z;
ThePoint->SetToScr(pModZ,pScrZ);
pDC->LineTo((int) ThePoint->DSP_Point->x,(int)ThePoint->DSP_Point->y);  

delete(ThePoint);
}


C3dVector NLine::MinPt(C3dVector inPt)
{
C3dVector vRet;
C3dVector v1;
C3dVector v2;
C3dVector P1;
C3dVector P2;
double dm;
double dDot;
P1.Set(cPts[0]->Pt_Point->x,
       cPts[0]->Pt_Point->y,
       cPts[0]->Pt_Point->z);
P2.Set(cPts[1]->Pt_Point->x,
       cPts[1]->Pt_Point->y,
       cPts[1]->Pt_Point->z);
v1=P2;
v1-=P1;
v2=inPt;
v2-=P1;
dm=v2.Mag();
v1.Normalize();
v2.Normalize();
dDot=v2.Dot(v1);
dm=dm*dDot;
vRet=P1+v1*dm;
return vRet;
}

G_Object* NLine::Copy(G_Object* Parrent)
{
int i;
NLine* cPoly = new NLine();
cPoly->Drawn = Drawn;
cPoly->Selectable  = Selectable; 
cPoly->Visable  = Visable;
cPoly->G_Colour = G_Colour;
cPoly->iObjType = iObjType;
cPoly->G_label = G_label;
cPoly->iNoCPts = iNoCPts;
cPoly->p = p;
cPoly->ws = ws;
cPoly->we = we;
cPoly->pParent=Parrent;

for (i=0;i<iNoCPts;i++)
{
  cPoly->cPts[i]=new CvPt_Object();
  cPoly->cPts[i]=(CvPt_Object*) cPts[i]->Copy(cPoly);
}
for (i=0;i<iNoCPts+p+1;i++)
{
  cPoly->knots[i]=knots[i];
}
return (cPoly);
}

double NLine::MinDist(C3dVector inPt)
{
C3dVector vRet;
double dX,dY,dZ,dU;
int iCnt1;
double MinDist = 100000000000000.0;
double dDist = 0;

for (iCnt1 = 1; iCnt1 < 1000; iCnt1++)
{
dU = iCnt1*0.001;
dX = (cPts[1]->Pt_Point->x-cPts[0]->Pt_Point->x)*dU;
dY = (cPts[1]->Pt_Point->y-cPts[0]->Pt_Point->y)*dU;
dZ = (cPts[1]->Pt_Point->z-cPts[0]->Pt_Point->z)*dU;
vRet.x = cPts[0]->Pt_Point->x + dX;
vRet.y = cPts[0]->Pt_Point->y + dY;
vRet.z = cPts[0]->Pt_Point->z + dZ;
dDist = pow((pow((vRet.x - inPt.x),2)+pow((vRet.y - inPt.y),2)+pow((vRet.z - inPt.z),2)),0.5);
if (dDist < MinDist)
  {
  MinDist = dDist;
  }
}
return (MinDist);
}


double NLine::getLen()
{
C3dVector p1;
C3dVector p2;
p1=GetPt(0);
p2=GetPt(1);
p1-=p2;
return (p1.Mag());
}

G_Object* NLine::OffSet(C3dVector vN,C3dVector vDir,double Dist)
{

C3dVector p1;
C3dVector p2;

p1.Set(cPts[0]->Pt_Point->x,
	     cPts[0]->Pt_Point->y,
	     cPts[0]->Pt_Point->z);

p2.Set(cPts[1]->Pt_Point->x,
	     cPts[1]->Pt_Point->y,
	     cPts[1]->Pt_Point->z);


C3dVector v1;
C3dVector v2;
C3dVector v1o;
v1=p2; v1-=p1;
v2=vDir; v2-=p1;
v2.Normalize();
v1o=v1.Cross(vN);
v1o.Normalize();
v1o*=Dist;

if (v1o.Dot(v2)<0)
  v1o*=-1;

NLine* Ln2 = new NLine;
Ln2->Create(p1+v1o,p2+v1o,1,NULL);
return (Ln2);
}

IMPLEMENT_DYNAMIC(NSurf, CObject)

NSurf ::~NSurf ()
{
int i;
for (i=0;i<iNoCvs;i++)
{
  delete(pCVsU [i]);
  pCVsU [i]=NULL;
}

if (pCVsV[0]!=NULL)
{
  //Note the control point have already been deleted above
  //dont delete again
  pCVsV[0]->iNoCPts=0;
  delete(pCVsV[0]);
  pCVsV[0]=NULL;
}
if (pCVsV[1]!=NULL)
{
  //Note the control point have already been deleted above
  //dont delete again
  pCVsV[1]->iNoCPts=0;
  delete(pCVsV[1]);
  pCVsV[1]=NULL;
}
for (i=0;i<iNoTrimCvs;i++)
{
  delete(pSurfCvs [i]);
  pSurfCvs [i]=NULL;
}
iNoTrimCvs=0;
iNoExtCvs=0;
}


NSurf::NSurf()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 13;
G_label = -1;
iObjType = 15;
iNoCvs = 0;
DrawCPts=FALSE;
pCVsV[0]=NULL;
pCVsV[1]=NULL;
iNoTrimCvs=0;
iNoExtCvs=0;
}


    // CvPt_Object* pVertex[20];
void NSurf::Create(int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 16;
G_label = iLab;
iObjType = 15;
iNoCvs = 0;
DrawCPts=FALSE;
pParent=Parrent;
pCVsV[0]=NULL;
pCVsV[1]=NULL;
iNoTrimCvs=0;
iNoExtCvs=0;
iNoIntLoops=0;
}


G_Object* NSurf::Copy(G_Object* Parrent)
{
int i,j;
NSurf* pSurf = new NSurf();
pSurf->Drawn = Drawn;
pSurf->Selectable  = Selectable; 
pSurf->Visable  = Visable;
pSurf->G_Colour = G_Colour;
pSurf->iObjType = iObjType;
pSurf->G_label = G_label;
pSurf->iNoCvs = iNoCvs;
pSurf->pU = pU;
pSurf->pV = pV;
pSurf->pParent=Parrent;
pSurf->iNoTrimCvs=iNoTrimCvs;


for (i=0;i<iNoCvs;i++)
{
  pSurf->pCVsU [i] = (NCurve*) pCVsU[i]->Copy(pSurf);
}
for (i=0;i<2;i++)
{
  pSurf->pCVsV [i] = (NCurve*) pCVsV[i]->Copy(pSurf);
}
for (i=0;i<iNoTrimCvs;i++)
{
  pSurf->pSurfCvs [i] = (NCurveOnSurf*) pSurfCvs[i]->Copy(pSurf);
}
pSurf->iNoTrimCvs=iNoTrimCvs;
for (i=0;i<iNoExtCvs;i++)
{
  pSurf->pExtLoop [i] = pExtLoop[i];
}
pSurf->iNoExtCvs=iNoExtCvs;
for (i=0;i<iNoIntLoops;i++)
{
  pSurf->iNoIntCvs [i] = iNoIntCvs[i];
}
pSurf->iNoIntLoops=iNoIntLoops;
for (i=0;i<iNoIntLoops;i++)
{
  for(j=0;j<iNoIntCvs[i];j++)
  {
    pSurf->pIntLoop[i][j]=pIntLoop[i][j];
  }
}
return (pSurf);
}

void NSurf::Copy2(NSurf* pSurf)
{
int i,j;

pSurf->Drawn = Drawn;
pSurf->Selectable  = Selectable; 
pSurf->Visable  = Visable;
pSurf->G_Colour = G_Colour;
pSurf->iObjType = iObjType;
pSurf->G_label = G_label;
pSurf->iNoCvs = iNoCvs;
pSurf->pU = pU;
pSurf->pV = pV;
pSurf->pParent=NULL;
pSurf->iNoTrimCvs=iNoTrimCvs;
for (i=0;i<iNoCvs;i++)
{
  pSurf->pCVsU [i] = (NCurve*) pCVsU[i]->Copy(pSurf);
}
for (i=0;i<2;i++)
{
  pSurf->pCVsV [i] = (NCurve*) pCVsV[i]->Copy(pSurf);
}
for (i=0;i<iNoTrimCvs;i++)
{
  pSurf->pSurfCvs [i] = (NCurveOnSurf*) pSurfCvs[i]->Copy(pSurf);
}
pSurf->iNoTrimCvs=iNoTrimCvs;
for (i=0;i<iNoExtCvs;i++)
{
  pSurf->pExtLoop [i] = pExtLoop[i];
}
pSurf->iNoExtCvs=iNoExtCvs;
for (i=0;i<iNoIntLoops;i++)
{
  pSurf->iNoIntCvs [i] = iNoIntCvs[i];
}
pSurf->iNoIntLoops=iNoIntLoops;
for (i=0;i<iNoIntLoops;i++)
{
  for(j=0;j<iNoIntCvs[i];j++)
  {
    pSurf->pIntLoop[i][j]=pIntLoop[i][j];
  }
}
}

C3dVector NSurf::Get_Centroid()
{
return (GetPt(0.5,0.5));
}


void NSurf::Serialize(CArchive& ar)
{
int i,j;
int iObj;
if (ar.IsStoring())
{
// TODO: add storing code here
  G_Object::Serialize(ar);
  ar << iNoCvs;
  ar << pU;
  ar << pV;
  ar << DrawCPts;
  ar<<iNoTrimCvs;
  ar<<iNoExtCvs;
  ar<<iNoIntLoops;
  
  for (i=0;i<iNoCvs;i++)
  {
    ar<<pCVsU[i]->iObjType;
    pCVsU[i]->Serialize(ar);
  }
  for (i=0;i<2;i++)
  {
    ar<<pCVsV[i]->iObjType;
    pCVsV[i]->Serialize(ar);
  }
  for (i=0;i<iNoTrimCvs;i++)
  {
    pSurfCvs[i]->Serialize(ar);
  }
  for (i=0;i<iNoExtCvs;i++)
  {
    ar<<pExtLoop[i];
  }
  for (i=0;i<iNoIntLoops;i++)
  {
    ar<<iNoIntCvs[i];
  }
  for (i=0;i<iNoIntLoops;i++)
  {
    for(j=0;j<iNoIntCvs[i];j++)
    {
      ar<<pIntLoop[i][j];
    }
  }
}
else
{
  G_Object::Serialize(ar);
  ar >> iNoCvs;
  ar >> pU;
  ar >> pV;
  ar >> DrawCPts;
  ar>>iNoTrimCvs;
  ar>>iNoExtCvs;
  ar>>iNoIntLoops;
  for (i=0;i<iNoCvs;i++)
  {
    ar>>iObj;
    if (iObj==7)
    {
      pCVsU[i]= new NCurve();
    }
    else if (iObj==8)
    {
      pCVsU[i]= new NCircle();
    }
    else if (iObj==9)
    {
      pCVsU[i]= new NLine();
    }
    pCVsU[i]->Serialize(ar);
    pCVsU[i]->pParent=this;
  }
  for (i=0;i<2;i++)
  {
    ar>>iObj;
    if (iObj==7)
    {
      pCVsV[i]= new NCurve();
    }
    else if (iObj==8)
    {
      pCVsV[i]= new NCircle();
    }
    else if (iObj==9)
    {
      pCVsV[i]= new NLine();
    }
    pCVsV[i]->Serialize(ar);
	  pCVsV[i]->pParent=this;
  }
  for (i=0;i<iNoTrimCvs;i++)
  {
    pSurfCvs[i]= new NCurveOnSurf();
    pSurfCvs[i]->Serialize(ar);
    pSurfCvs[i]->pParent=this;
  }
  for (i=0;i<iNoExtCvs;i++)
  {
    ar>>pExtLoop[i];
  }
  for (i=0;i<iNoIntLoops;i++)
  {
    ar>>iNoIntCvs[i];
  }
  for (i=0;i<iNoIntLoops;i++)
  {
    for(j=0;j<iNoIntCvs[i];j++)
    {
      ar>>pIntLoop[i][j];
    }
  }
}
}



void NSurf::AddCV(NCurve* inCV)
{
if (iNoCvs<MAX_CVS)
{
  pCVsU[iNoCvs] = (NCurve*) inCV->Copy(this);
  iNoCvs++;
}
else
{
  outtext1("Error max curves in surf");
}
}


void NSurf::OglDrawW(int iDspFlgs,double dS1,double dS2)
{
char sLab[20];
if ((iDspFlgs & DSP_SURFACES)>0)
{
int i;
int j;
Selectable=1;
GLfloat* ctrlpts;
GLfloat* KnotsU;
GLfloat* KnotsV;
int nu;
int nv;
int ku;
int kv;
int icu;

C3dVector vU;
vU=this->GetPt(0.25,0);

for (i=0;i<iNoTrimCvs;i++)
{
  if ((iDspFlgs & DSP_SURC) > 0)
  {
    pSurfCvs[i]->Selectable=1;
    pSurfCvs[i]->OglDrawW(DSP_CURVES);
  }
  else
  {
    pSurfCvs[i]->Selectable=0;
  }
}


if ((iDspFlgs & DSP_LINE) > 0)
{
    glColor3fv(cols[G_Colour]);
    glRasterPos3f ((float) vU.x,(float) vU.y,(float) vU.z);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, BMPU);
}
else
{
    glColor3fv(cols[0]);
}



nu = pCVsU[0]->iNoCPts;
ku=nu+pU+1;
nv = iNoCvs;
kv=nv+pV+1;



KnotsU = (GLfloat*) malloc(ku*sizeof(GLfloat));
for (icu = 0;icu < ku;icu++)
{
 KnotsU[icu] = (float) pCVsU[0]->knots[icu];
}
KnotsV = (GLfloat*) malloc(kv*sizeof(GLfloat));
for (icu = 0;icu < kv;icu++)
{
 KnotsV[icu] = (float) pCVsV[0]->knots[icu];
}

int iInd = 0;
double dW;
ctrlpts = (GLfloat*) malloc(4*nv*nu*sizeof(GLfloat));
for (i=0;i<nv;i++)
{
  for (j=0;j<nu;j++)
  {
    dW = pCVsU[i]->cPts[j]->w;
    ctrlpts[iInd]   = (float) pCVsU[i]->cPts[j]->Pt_Point->x*(float) dW;
    ctrlpts[iInd+1] = (float) pCVsU[i]->cPts[j]->Pt_Point->y*(float) dW;
    ctrlpts[iInd+2] = (float) pCVsU[i]->cPts[j]->Pt_Point->z*(float) dW;
    ctrlpts[iInd+3] = (float) dW;
    iInd = iInd+4;
  }
}


GLUnurbsObj* pSurf;
pSurf=gluNewNurbsRenderer();
gluNurbsProperty(pSurf, GLU_SAMPLING_TOLERANCE, 20.0 );
gluNurbsProperty(pSurf, GLU_AUTO_LOAD_MATRIX, GL_TRUE);
gluNurbsProperty(pSurf, GLU_DISPLAY_MODE, GLU_OUTLINE_PATCH);
gluBeginSurface(pSurf);       
      gluNurbsSurface(pSurf,  
                      ku,  
                      KnotsU,  
                      kv,  
                      KnotsV,  
                      4,  
                      4*nu,  
                      ctrlpts,  
                      pU+1,  
                      pV+1,  
                      GL_MAP2_VERTEX_4); 
gluBeginTrim (pSurf);
for (i=0;i<iNoExtCvs;i++)
{
      //gluPwlCurve (pSurf, 5, &edgePt[0][0], 2, GLU_MAP1_TRIM_2);
   pSurfCvs[pExtLoop[i]]->TrimOGL(pSurf);
}
gluEndTrim (pSurf);
gluEndSurface(pSurf); 
gluDeleteNurbsRenderer(pSurf);
free(ctrlpts);
free(KnotsU);
free(KnotsV);

if (DrawCPts==TRUE)
{
  for (i = 0; i < iNoCvs; i++)
  {
    pCVsU[i]->OglDrawCtrlPts();
  }
}
  C3dVector vCent;
  vCent=Get_Centroid();
  if (bDrawLab==TRUE)
	{
	  sprintf_s(sLab,"S%i",G_label);
	  OglString(iDspFlgs,vCent.x,vCent.y,vCent.z,&sLab[0]);
	}
}
else
{
  Selectable=0;
}
}

void NSurf::OglDraw(int iDspFlgs,double dS1,double dS2)
{
//Below draw the curve using the open gl nurbs render
//which i cant trim at the moment so
//doing it the hard way above
if ((iDspFlgs & DSP_SURFACES)>0)
{
	Selectable=1;
  GLfloat* ctrlpts;
  GLfloat* KnotsU;
  GLfloat* KnotsV;
   GLfloat knots[6] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
   GLfloat edgePt[5][2] = /* counter clockwise */
      {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}, 
       {0.0, 0.0}};


int nu;
int nv;
int ku;
int kv;
int icu;
glColor3fv(cols[G_Colour]);
nu = pCVsU[0]->iNoCPts;
ku=nu+pU+1;
nv = iNoCvs;
kv=nv+pV+1;

KnotsU = (GLfloat*) malloc(ku*sizeof(GLfloat));
for (icu = 0;icu < ku;icu++)
{
 KnotsU[icu] = (float) pCVsU[0]->knots[icu];
}
KnotsV = (GLfloat*) malloc(kv*sizeof(GLfloat));
for (icu = 0;icu < kv;icu++)
{
 KnotsV[icu] = (float) pCVsV[0]->knots[icu];
}

int iInd = 0;
int j;
int i;
double dW;
ctrlpts = (GLfloat*) malloc(4*nv*nu*sizeof(GLfloat));
for (i=0;i<nv;i++)
{
  for (j=0;j<nu;j++)
  {
    dW = pCVsU[i]->cPts[j]->w;
    ctrlpts[iInd]   = (float) pCVsU[i]->cPts[j]->Pt_Point->x*(float) dW;
    ctrlpts[iInd+1] = (float) pCVsU[i]->cPts[j]->Pt_Point->y*(float) dW;
    ctrlpts[iInd+2] = (float) pCVsU[i]->cPts[j]->Pt_Point->z*(float) dW;
    ctrlpts[iInd+3] = (float) dW;
    iInd = iInd+4;
  }
}


GLUnurbsObj* pSurf;
pSurf=gluNewNurbsRenderer();
//gluNurbsProperty(pSurf, GLU_SAMPLING_METHOD,GLU_OBJECT_PATH_LENGTH);
gluNurbsProperty(pSurf, GLU_SAMPLING_TOLERANCE, 20.0f );
gluNurbsProperty(pSurf, GLU_AUTO_LOAD_MATRIX, GL_TRUE);
gluNurbsProperty(pSurf, GLU_DISPLAY_MODE, GLU_FILL);
gluBeginSurface(pSurf);       
      gluNurbsSurface(pSurf,  
                      ku,  
                      KnotsU,  
                      kv,  
                      KnotsV,  
                      4,  
                      4*nu,  
                      ctrlpts,  
                      pU+1,  
                      pV+1,  
                      GL_MAP2_VERTEX_4); 
  //gluBeginTrim (pSurf);
  //    gluPwlCurve (pSurf, 5, &edgePt[0][0], 2,
  //                 GLU_MAP1_TRIM_2);
  // gluEndTrim (pSurf);

gluBeginTrim (pSurf);
for (i=0;i<iNoExtCvs;i++)
{
      //gluPwlCurve (pSurf, 5, &edgePt[0][0], 2, GLU_MAP1_TRIM_2);
   pSurfCvs[pExtLoop[i]]->TrimOGL(pSurf);
}
gluEndTrim (pSurf);
//internal loop
if (iNoIntLoops>0)
{
  for (i=0;i<iNoIntLoops;i++)
  {
    gluBeginTrim (pSurf);
    for (j=0;j<iNoIntCvs[i];j++)
    {
      pSurfCvs[pIntLoop[i][j]]->TrimOGL(pSurf);
    }
    gluEndTrim (pSurf);
  }
}
gluEndSurface(pSurf); 
gluDeleteNurbsRenderer(pSurf);
free(ctrlpts);
free(KnotsU);
free(KnotsV);
}
else
{
  Selectable=0;
}
}


void NSurf::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{
pModZ = pModMat;
pScrZ = pScrTran;
G_Object::SetToScr( pModMat,pScrTran);
int i;
for (i = 0; i < iNoCvs; i++)
{
  pCVsU[i]->SetToScr(pModMat,pScrTran);
}
pCVsV[0]->SetToScr(pModMat,pScrTran);
pCVsV[1]->SetToScr(pModMat,pScrTran);
if (iNoTrimCvs>0)
{
  for (i = 0; i < iNoTrimCvs; i++)
  {
    pSurfCvs[i]->SetToScr(pModMat,pScrTran);
  }
}

}



void NSurf::DrawCtrlPtsTog()
{
if (DrawCPts==FALSE)
{
  DrawCPts=TRUE;
}
else
{
  DrawCPts=FALSE;
}
}



void NSurf::HighLight(CDC* pDC)
{
int i;
if (iNoExtCvs>0)
{
  for (i=0;i<iNoExtCvs;i++)
  {
    pSurfCvs[pExtLoop[i]]->HighLight(pDC);
  }
}
}


G_ObjectD NSurf::SelDist(CPoint InPT,Filter FIL)
{
G_ObjectD Ret;
G_ObjectD vT;
C3dVector vPt;
int i,j;
double v=0.1;
double u=0.1;
double dDist;
double MinDist=1e36;
Pt_Object* ThePoint = new (Pt_Object);
ThePoint->Create(vPt,0,0,0,11,0,0,NULL);

for (j=1;j<=9;j++)
{
  v=0.1;
  for (i=1;i<=9;i++)
  {
    vPt=GetPt(u,v);
    ThePoint->Pt_Point->x = vPt.x;
    ThePoint->Pt_Point->y = vPt.y;
    ThePoint->Pt_Point->z = vPt.z;
	  ThePoint->SetToScr(pModZ,pScrZ);
    dDist = pow((ThePoint->DSP_Point->x-InPT.x),2)+pow((ThePoint->DSP_Point->y-InPT.y),2);
	if (dDist < MinDist)
	{
      MinDist = dDist;
	}
	v+=0.1;
  }
  u+=0.1;
}
delete(ThePoint);
Ret.pObj=NULL;
// Check the control points
if (FIL.isFilter(7))
{
  if (DrawCPts==TRUE)
  {
    for (i = 0; i < iNoCvs; i++)
    {
      for (j=0;j<pCVsU[i]->iNoCPts;j++)
	  {
         vT=pCVsU[i]->cPts[j]->SelDist(InPT,FIL);
		 if (vT.Dist<MinDist)
	     {
           MinDist=vT.Dist;
           Ret.Dist=MinDist;
           Ret.pObj=vT.pObj;
	     }
	  }
    }
  }
}

if (iNoTrimCvs>0)
{
  if (FIL.isFilter(13))
  {
    for (i=0;i<iNoTrimCvs;i++)
    {
        vT=pSurfCvs[i]->SelDist(InPT,FIL);
	    if (vT.Dist<MinDist)
	    {
        MinDist=vT.Dist;
        Ret.Dist=MinDist;
        Ret.pObj=vT.pObj;
	    }
    }
  }
}

//if (FIL.isFilter(0))
//{
//for (i = 0; i < iNoCPts; i++)
//  {
//    dDist = pow((cPts[i]->DSP_Point->x-InPT.x),2)+pow((cPts[i]->DSP_Point->y-InPT.y),2);
//    if (dDist <= MinDist)
//    {
//      MinDist = dDist;
//      Ret.Dist=MinDist;
//      Ret.pObj=cPts[i];
//    }
//  }
//}

if (Ret.pObj==NULL)
{
  Ret.Dist=MinDist;
  Ret.pObj=this;
}

return (Ret);
}

void NSurf::Translate (C3dVector vIn)
{
int i;
for (i = 0; i < iNoCvs; i++)
{
  pCVsU[i]->Translate(vIn);
}
}

void NSurf::Transform(C3dMatrix TMat)
{
int i;
for (i = 0; i < iNoCvs; i++)
{
  pCVsU[i]->Transform(TMat);
}
}

C3dVector NSurf::GetPt(double dU,double dV)
{
C3dVector vRet;
int l,k;
int uspan;
int vspan;
double W;
double NU[20];
double NV[20];
C4dVector temp[20];
C4dVector pt;
C4dVector SW;

uspan = pCVsU[0]->FindSpan(dU);
pCVsU[0]->BasisFun(pCVsU[0]->p,uspan,dU,NU);
vspan = pCVsV[0]->FindSpan(dV);
pCVsV[0]->BasisFun(pCVsV[0]->p,vspan,dV,NV);
for (l=0;l<=pV;l++)
{
  temp[l].Clear();
  for(k=0;k<=pU;k++)
  {
    W=pCVsU[vspan-pV+l]->cPts[uspan-pU+k]->w;
    pt.xw = pCVsU[vspan-pV+l]->cPts[uspan-pU+k]->Pt_Point->x*W;
    pt.yw = pCVsU[vspan-pV+l]->cPts[uspan-pU+k]->Pt_Point->y*W;
    pt.zw = pCVsU[vspan-pV+l]->cPts[uspan-pU+k]->Pt_Point->z*W;
    pt.w = W;
    temp[l] = temp[l]+pt*NU[k];
  }
}
SW.Clear();
for (l=0;l<=pV;l++)
{
  SW=SW+temp[l]*NV[l];
}
vRet.x=SW.xw/SW.w;
vRet.y=SW.yw/SW.w;
vRet.z=SW.zw/SW.w;
return (vRet);
}

void NSurf::binomialCoef(Mat* Bin)
{
  int n,k ;
  // Setup the first line
  *Bin->mn2(0,0) = 1.0 ;
  for(k=Bin->n-1;k>0;--k)
  {
    *Bin->mn2(0,k) = 0.0 ;
  }
  // Setup the other lines
  for(n=0;n<Bin->m-1;n++)
  {
    *Bin->mn2(n+1,0) = 1.0 ;
    for(k=1;k<Bin->n;k++)
    {
      if(n+1<k)
	      *Bin->mn2(n,k) = 0.0 ;
      else
	      *Bin->mn2(n+1,k) = *Bin->mn2(n,k) + *Bin->mn2(n,k-1) ;
    }
  }
}

NCurveOnSurf* NSurf::AddTrimCurve(NCurve* pCurve)
{
NCurveOnSurf* pSCv;
if (pCurve!=NULL)
{
  pSCv=pCurve->GetSurfaceCV(this);
  pSCv->pParent=this;
  pSurfCvs[iNoTrimCvs]=pSCv;
  pSCv->SetToScr(pModZ,pScrZ);
  iNoTrimCvs++;
}
return (pSCv);
}

C3dVector NSurf::GetNormal(double dU,double dV)
{
C3dVector v1;
C3dVector v2;
C3dVector vN;
Matrix<C3dVector> der;
deriveAt(dU,dV,1,der);
v1=der(1,0);
v2=der(0,1);
der.DeleteAll();
vN=v1.Cross(v2);
return (vN);
}

C3dVector NSurf::MinPt(C3dVector inPt)
{
C3dVector vRet;
const double dTol = 0.00000001;
const double dIncs = 10;
int i;
int j;
double dStp = 1/dIncs;

double dWu=0;
double dWv=0;
double dMinWu=0;
double dMinWv=0;
C3dVector cPt;
C3dVector cNextPt;
double Dist;
double minDist = 1e36;
C3dVector v1;
C3dVector v2;

double dDotU;
double dDotV;
cPt=GetPt(dWu,dWv);
for(i=0;i<dIncs;i++)
{
  for(j=0;j<dIncs;j++)
  {
    dWu=i*dStp;
    dWv=j*dStp;
    cPt=GetPt(dWu,dWv);
    Dist=cPt.Dist(inPt);
    if (Dist<minDist)
    {
      minDist=Dist;
      dMinWu=dWu;
      dMinWv=dWv;
    }
  }
}

//start of iteration
dWu=dMinWu;
dWv=dMinWv;

i=0;
Matrix<C3dVector> der;
C3dVector Vec;
double dUscl;
double dVscl;
double dErr1=1e36;
double dErr=1e36;
double absErr;
do
{
  der.DeleteAll();
  cPt=GetPt(dWu,dWv);
  Vec=inPt-cPt;
  dErr1=dErr;
  dErr=Vec.Mag();
  absErr=abs(dErr-dErr1);
  deriveAt(dWu,dWv,1,der);
  v1=der(1,0);
  v2=der(0,1);
  dUscl=v1.Mag();
  dVscl=v2.Mag();
  v1.Normalize();
  v2.Normalize();
//  Vec.Normalize();
  dDotU=v1.Dot(Vec)/dUscl;
  dDotV=v2.Dot(Vec)/dVscl;
  dWu+=dDotU;
  dWv+=dDotV;
  if (dWu>1){dWu=1;}
  if (dWv>1){dWv=1;}
  if (dWu<0){dWu=0;}
  if (dWv<0){dWv=0;}
  i++;
}
while ((absErr>dTol) && (i<100));
vRet=GetPt(dWu,dWv);
der.DeleteAll();
return (vRet);
}

C3dVector NSurf::MinPtW(C3dVector inPt)
{
C3dVector vRet;
const double dTol = 0.00000001;
const double dIncs = 10;
int i;
int j;
double dStp = 1/dIncs;

double dWu=0;
double dWv=0;
double dMinWu=0;
double dMinWv=0;
C3dVector cPt;
C3dVector cNextPt;
double Dist;
double minDist = 1e36;
C3dVector v1;
C3dVector v2;

double dDotU;
double dDotV;
cPt=GetPt(dWu,dWv);
for(i=0;i<dIncs;i++)
{
  for(j=0;j<dIncs;j++)
  {
    dWu=i*dStp;
    dWv=j*dStp;
    cPt=GetPt(dWu,dWv);
    Dist=cPt.Dist(inPt);
    if (Dist<minDist)
    {
      minDist=Dist;
      dMinWu=dWu;
      dMinWv=dWv;
    }
  }
}

//start of iteration
dWu=dMinWu;
dWv=dMinWv;

i=0;
Matrix<C3dVector> der;
C3dVector Vec;
double dUscl;
double dVscl;
double dErr1=1e36;
double dErr=1e36;
double absErr;
do
{
  der.DeleteAll();
  cPt=GetPt(dWu,dWv);
  Vec=inPt-cPt;
  dErr1=dErr;
  dErr=Vec.Mag();
  absErr=abs(dErr-dErr1);
  deriveAt(dWu,dWv,1,der);
  v1=der(1,0);
  v2=der(0,1);
  dUscl=v1.Mag();
  dVscl=v2.Mag();
  v1.Normalize();
  v2.Normalize();
//  Vec.Normalize();
  dDotU=v1.Dot(Vec)/dUscl;
  dDotV=v2.Dot(Vec)/dVscl;
  dWu+=dDotU;
  dWv+=dDotV;
  if (dWu>1){dWu=1;}
  if (dWv>1){dWv=1;}
  if (dWu<0){dWu=0;}
  if (dWv<0){dWv=0;}
  i++;
}
while ((absErr>dTol) && (i<100));
vRet.Set(dWu,dWv,0);
der.DeleteAll();
return (vRet);
}
Mat* NSurf::Surfacederive(double u, double v, int d,Matrix <C4dVector> &skl)
{
  int k,l,du,dv;
  //Mat* skl = new Mat(d+1,d+1);
  skl.Size(d+1,d+1);
  du = minimum(d,pU) ;
  for(k=pU+1;k<=d;++k)
  {
    for(l=0;l<=d-k;++l)
    {
      skl(k,l).Clear();
    }
  }
  dv=minimum(d,pV) ;
  for(l=pV+1;l<=d;++l)
  {
    for(k=0;k<=d-l;++k)
    {
      skl(k,l).Clear();
      C4dVector A=skl(k,l);
    }
  }
  int uspan = pCVsU[0]->FindSpan(u) ;
  int vspan = pCVsV[0]->FindSpan(v) ;
  Mat* Nu;
  Mat* Nv;
  Nu=pCVsU[0]->dersBasisFuns(du,u,uspan); 
  Nv=pCVsV[0]->dersBasisFuns(dv,v,vspan); 
  double W;
  C4dVector temp[10];
  int dd,r,s ;
  C4dVector pt;
  for(k=0;k<=du;++k)
  {
    for(s=0;s<=pV;++s)
    {
      temp[s].Clear();
      for(r=0;r<=pU;++r)
      {
	      //temp[s] += Nu(k,r)*pCVsU[uspan-degU+r]->cPts[vspan-degV+s] ;
            W=pCVsU[vspan-pV+s]->cPts[uspan-pU+r]->w;
            pt.xw = pCVsU[vspan-pV+s]->cPts[uspan-pU+r]->Pt_Point->x*W;
            pt.yw = pCVsU[vspan-pV+s]->cPts[uspan-pU+r]->Pt_Point->y*W;
            pt.zw = pCVsU[vspan-pV+s]->cPts[uspan-pU+r]->Pt_Point->z*W;
            pt.w = W;
            temp[s] = temp[s]+pt**Nu->mn2(k,r);
      }
    }
    dd = minimum(d-k,dv) ;
    for(l=0;l<=dd;++l)
    {
      skl(k,l).Clear();
      for(s=0;s<=pV;++s)
      {
	      skl(k,l).xw += temp[s].xw**Nv->mn2(l,s);
        skl(k,l).yw += temp[s].yw**Nv->mn2(l,s);
        skl(k,l).zw += temp[s].zw**Nv->mn2(l,s);
        skl(k,l).w += temp[s].w**Nv->mn2(l,s);
      }
    }
  }

delete (Nu);
delete (Nv);
return(NULL);
}


void NSurf::deriveAt(double u, double v,int d,Matrix <C3dVector> &skl)
{
int i,j,k,l; 
C3dVector pv;
C3dVector pv2;
C3dVector a;
Matrix <C4dVector> ders;
Surfacederive(u,v,d,ders);
skl.Size(d+1,d+1);
Mat* Bin = new Mat(d+1,d+1);
binomialCoef(Bin);

for(k=0;k<=d;++k)
{
  for(l=0;l<=d-k;++l)
  {
      pv.x = ders(k,l).xw;
      pv.y = ders(k,l).yw;
      pv.z = ders(k,l).zw;
      for(j=1;j<=l;j++)
      {
	     pv -=skl(k,l-j)**Bin->mn2(l,j)*ders(0,j).w;
      }
      for(i=1;i<=k;i++)
      {
	      pv -= skl(k-i,l)**Bin->mn2(k,i)*ders(i,0).w;
	      pv2.Set(0,0,0) ;
	      for(j=1;j<=l;j++)
        {
	        pv2 += skl(k-i,l-j)**Bin->mn2(l,j)*ders(i,j).w ;
        }
	      pv -= pv2**Bin->mn2(k,i) ;
      }
      skl(k,l) = pv;
      skl(k,l) /=ders(0,0).w;
  }
 }

delete (Bin);
ders.DeleteAll();
}

BOOL NSurf::Generate(int pInV,double dvs,double dve)
{
BOOL bRet=FALSE;
int i;

//Check no pts and order in each U curve
if (iNoCvs>1)
{
  for (i=1;i<iNoCvs;i++)
  {
    if ((pCVsU[0]->p!=pCVsU[i]->p) || (pCVsU[0]->iNoCPts!=pCVsU[i]->iNoCPts)) 
    {
      bRet=TRUE;
    }
  }
}
else
{
bRet=TRUE;
}
if (bRet==FALSE)
{

  pU = pCVsU[0]->p;
  if (iNoCvs>=pInV+1)
  {
    pV = pInV;
  }
  else
  {
    pV = iNoCvs-1;
  }
  pCVsV[0]=new NCurve();
  pCVsV[1]=new NCurve();

  pCVsV[0]->Create(-1,this);
  pCVsV[1]->Create(-1,this);
  pCVsV[0]->iNoCPts = iNoCvs;
  pCVsV[1]->iNoCPts = iNoCvs;

  for (i=0;i<iNoCvs;i++)
  {
    pCVsV[0]->cPts[i]=pCVsU[i]->cPts[0];
    pCVsV[1]->cPts[i]=pCVsU[i]->cPts[pCVsU[0]->iNoCPts-1];
  }
  pCVsV[0]->Generate(pV);
  pCVsV[1]->Generate(pV);
}
  pCVsV[0]->ws=dvs;
  pCVsV[1]->ws=dvs;
  pCVsV[0]->we=dve;
  pCVsV[1]->we=dve;
DefualtTrim();
return (bRet);
}

BOOL NSurf::GenerateFit(int pInV,double dvs,double dve)
{
BOOL bRet=FALSE;
int i;
int j;
//Check no pts and order in each U curve
if (iNoCvs>1)
{
  for (i=1;i<iNoCvs;i++)
  {
    if ((pCVsU[0]->p!=pCVsU[i]->p) || (pCVsU[0]->iNoCPts!=pCVsU[i]->iNoCPts)) 
    {
      bRet=TRUE;
    }
  }
}
else
{
bRet=TRUE;
}
Vec<C4dVector> P;
Vec<double> U;
if (bRet==FALSE)
{

// Interpolate the points in the V direction
  for (j=0;j<pCVsU[0]->iNoCPts;j++)
  {
    NCurve* cPolyW = new NCurve();
    cPolyW->Create(0,NULL);
    for (i=0;i<iNoCvs;i++)
    {
      C3dVector a=pCVsU[i]->cPts[j]->GetCoords();
      cPolyW->AddVert(pCVsU[i]->cPts[j]->GetCoords(),pCVsU[i]->cPts[j]->w);
    }
    cPolyW->globalInterp(pInV,P,U);
    cPolyW->GenerateExp(pInV,P,U); 
    for (i=0;i<iNoCvs;i++)
    {
      //pCVsU[i]->cPts[j]->w=cPolyW->cPts[i]->w;
      pCVsU[i]->cPts[j]->Pt_Point->x=cPolyW->cPts[i]->Pt_Point->x;
      pCVsU[i]->cPts[j]->Pt_Point->y=cPolyW->cPts[i]->Pt_Point->y;
      pCVsU[i]->cPts[j]->Pt_Point->z=cPolyW->cPts[i]->Pt_Point->z;
    }
    P.DeleteAll();
    U.DeleteAll();
    delete(cPolyW);
  }

//
  pU = pCVsU[0]->p;
  if (iNoCvs>=pInV+1)
  {
    pV = pInV;
  }
  else
  {
    pV = iNoCvs-1;
  }
  pCVsV[0]=new NCurve();
  pCVsV[1]=new NCurve();

  pCVsV[0]->Create(-1,this);
  pCVsV[1]->Create(-1,this);
  pCVsV[0]->iNoCPts = iNoCvs;
  pCVsV[1]->iNoCPts = iNoCvs;

  for (i=0;i<iNoCvs;i++)
  {
    pCVsV[0]->cPts[i]=pCVsU[i]->cPts[0];
    pCVsV[1]->cPts[i]=pCVsU[i]->cPts[pCVsU[0]->iNoCPts-1];
  }
  pCVsV[0]->Generate(pV);
  pCVsV[1]->Generate(pV);
}
  pCVsV[0]->ws=dvs;
  pCVsV[1]->ws=dvs;
  pCVsV[0]->we=dve;
  pCVsV[1]->we=dve;
DefualtTrim();
return (bRet);
}
BOOL NSurf::GenerateExp(C3dVector cPts[1000],
                      double wghts[1000],
                      double KnotsU[100],
                      double KnotsV[100],
                      int noU,
                      int noV,
                      int pInU,
                      int pInV)
{
BOOL bRet=FALSE;
int i;
int j;
Create(-1,NULL);
pU=pInU;
pV=pInV;
Vec<C4dVector> P;
Vec<double> U;
P.Size(noU);
U.Size(noU+pInU+1);
NCurve* cPolyW;
for (j=0;j<noU+pInU+1;j++)
{
  U[j]=KnotsU[j];
}
for (i=0;i<noV;i++)
{ 
  cPolyW = new NCurve();
  for (j=0;j<noU;j++)
  {
    P[j].xw=cPts[j+(i*noU)].x;
    P[j].yw=cPts[j+(i*noU)].y;
    P[j].zw=cPts[j+(i*noU)].z;
    P[j].w=wghts[j+(i*noU)];
  }

  cPolyW->GenerateExp(pU,P,U);
  this->AddCV(cPolyW);

}
P.clear();
P.Size(iNoCvs);
U.clear();
U.Size(noV+pInV+1);

for (i=0;i<iNoCvs;i++)
{
  P[i].xw=pCVsU[i]->cPts[0]->Pt_Point->x;
  P[i].yw=pCVsU[i]->cPts[0]->Pt_Point->y;
  P[i].zw=pCVsU[i]->cPts[0]->Pt_Point->z;
  P[i].w=pCVsU[i]->cPts[0]->w;
}
for (j=0;j<noV+pInV+1;j++)
{
  U[j]=KnotsV[j];
}
cPolyW = new NCurve();
cPolyW->GenerateExp(pV,P,U);
pCVsV[0]=cPolyW;

for (i=0;i<iNoCvs;i++)
{
  P[i].xw=pCVsU[i]->cPts[pCVsU[0]->iNoCPts-1]->Pt_Point->x;
  P[i].yw=pCVsU[i]->cPts[pCVsU[0]->iNoCPts-1]->Pt_Point->y;
  P[i].zw=pCVsU[i]->cPts[pCVsU[0]->iNoCPts-1]->Pt_Point->z;
  P[i].w=pCVsU[i]->cPts[pCVsU[0]->iNoCPts-1]->w;
}
cPolyW = new NCurve();
cPolyW->GenerateExp(pV,P,U);
pCVsV[1]=cPolyW;

//DefualtTrim();

P.DeleteAll();
////U.DeleteAll;
//Check no pts and order in each U curve
//if (iNoCvs>1)
//{
//  for (i=1;i<iNoCvs;i++)
//  {
//    if ((pCVsU[0]->p!=pCVsU[i]->p) || (pCVsU[0]->iNoCPts!=pCVsU[i]->iNoCPts)) 
//    {
//      bRet=TRUE;
//    }
//  }
//}
//else
//{
//bRet=TRUE;
//}
//if (bRet==FALSE)
//{
//  pU = pCVsU[0]->p;
//  if (iNoCvs>=pInV+1)
//  {
//    pV = pInV;
//  }
//  else
//  {
//    pV = iNoCvs-1;
//  }
//  pCVsV[0]=new NCurve();
//  pCVsV[1]=new NCurve();
//  pCVsV[0]->Create(-1,this);
//  pCVsV[1]->Create(-1,this);
//  pCVsV[0]->iNoCPts = iNoCvs;
//  pCVsV[1]->iNoCPts = iNoCvs;
//
//  for (i=0;i<iNoCvs;i++)
//  {
//    pCVsV[0]->cPts[i]=pCVsU[i]->cPts[0];
//    pCVsV[1]->cPts[i]=pCVsU[i]->cPts[pCVsU[0]->iNoCPts-1];
//  }
//  pCVsV[0]->Generate(pV);
//  pCVsV[1]->Generate(pV);
//}
//DefualtTrim();
return (bRet);
}


int NSurf::GetTrimCvInd(G_Object* pCV)
{
int irc=-1;
int i;
for (i=0;i<iNoTrimCvs;i++)
{
  if (pSurfCvs[i]==pCV)
  {
    irc=i;
    break;
  }
}
return (irc);
}


void NSurf::InternalTrim(ObjList* pCvs)
{
int i;
int irc;
BOOL berr=FALSE;

for (i=0;i<pCvs->iNo;i++)
{
  irc=GetTrimCvInd(pCvs->Objs[i]);
  pIntLoop[iNoIntLoops][i]=irc;
  iNoIntCvs[iNoIntLoops]=pCvs->iNo;
}
iNoIntLoops++;
}

void NSurf::UserTrim(ObjList* pCvs)
{
int i;
int irc;
BOOL berr=FALSE;

for (i=0;i<pCvs->iNo;i++)
{
  irc=GetTrimCvInd(pCvs->Objs[i]);
  pExtLoop[i]=irc;
  iNoExtCvs=pCvs->iNo;
}
}


void NSurf::DefualtTrim()
{
double ut = pCVsU[0]->we;
double vt = pCVsV[0]->we;;
double us = pCVsU[0]->ws;
double vs = pCVsV[0]->ws;;
pSurfCvs[0]=new NCurveOnSurf();
pSurfCvs[0]->Create(-1,this);
C3dVector Pt;
Pt.Set(us,vs,0);
pSurfCvs[0]->AddVert(Pt,1);
Pt.Set(ut,vs,0);
pSurfCvs[0]->AddVert(Pt,1);
pSurfCvs[0]->Generate(1);
iNoTrimCvs++;
pSurfCvs[1]=new NCurveOnSurf();
pSurfCvs[1]->Create(-1,this);
Pt.Set(ut,vs,0);
pSurfCvs[1]->AddVert(Pt,1);
Pt.Set(ut,vt,0);
pSurfCvs[1]->AddVert(Pt,1);
pSurfCvs[1]->Generate(1);
iNoTrimCvs++;
pSurfCvs[2]=new NCurveOnSurf();
pSurfCvs[2]->Create(-1,this);
Pt.Set(ut,vt,0);
pSurfCvs[2]->AddVert(Pt,1);
Pt.Set(us,vt,0);
pSurfCvs[2]->AddVert(Pt,1);
pSurfCvs[2]->Generate(1);
iNoTrimCvs++;
pSurfCvs[3]=new NCurveOnSurf();
pSurfCvs[3]->Create(-1,this);
Pt.Set(us,vt,0);
pSurfCvs[3]->AddVert(Pt,1);
Pt.Set(us,vs,0);
pSurfCvs[3]->AddVert(Pt,1);
pSurfCvs[3]->Generate(1);
iNoTrimCvs++;
pExtLoop[0]=0;
iNoExtCvs++;
pExtLoop[1]=1;
iNoExtCvs++;
pExtLoop[2]=2;
iNoExtCvs++;
pExtLoop[3]=3;
iNoExtCvs++;
}

void NSurf::TrimLoop(double us,double ue,double vs, double ve)
{

pSurfCvs[0]=new NCurveOnSurf();
pSurfCvs[0]->Create(-1,this);
C3dVector Pt;
Pt.Set(us,vs,0);
pSurfCvs[0]->AddVert(Pt,1);
Pt.Set(ue,vs,0);
pSurfCvs[0]->AddVert(Pt,1);
pSurfCvs[0]->Generate(1);
iNoTrimCvs++;
pSurfCvs[1]=new NCurveOnSurf();
pSurfCvs[1]->Create(-1,this);
Pt.Set(ue,vs,0);
pSurfCvs[1]->AddVert(Pt,1);
Pt.Set(ue,ve,0);
pSurfCvs[1]->AddVert(Pt,1);
pSurfCvs[1]->Generate(1);
iNoTrimCvs++;
pSurfCvs[2]=new NCurveOnSurf();
pSurfCvs[2]->Create(-1,this);
Pt.Set(ue,ve,0);
pSurfCvs[2]->AddVert(Pt,1);
Pt.Set(us,ve,0);
pSurfCvs[2]->AddVert(Pt,1);
pSurfCvs[2]->Generate(1);
iNoTrimCvs++;
pSurfCvs[3]=new NCurveOnSurf();
pSurfCvs[3]->Create(-1,this);
Pt.Set(us,ve,0);
pSurfCvs[3]->AddVert(Pt,1);
Pt.Set(us,vs,0);
pSurfCvs[3]->AddVert(Pt,1);
pSurfCvs[3]->Generate(1);
iNoTrimCvs++;
pExtLoop[0]=0;
iNoExtCvs++;
pExtLoop[1]=1;
iNoExtCvs++;
pExtLoop[2]=2;
iNoExtCvs++;
pExtLoop[3]=3;
iNoExtCvs++;
}

IMPLEMENT_DYNAMIC(NSurfR, CObject)


NSurfR::NSurfR()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 13;
G_label = -1;
iObjType = 16;
iNoCvs = 0;
DrawCPts=FALSE;
pCVsV[0]=NULL;
pCVsV[1]=NULL;
iNoTrimCvs=0;
iNoExtCvs=0;
}


    // CvPt_Object* pVertex[20];
void NSurfR::Create(C3dMatrix Glob, NCurve* pCIn,C3dVector vN,C3dVector vC,int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 16;
G_label = iLab;
iObjType = 16;
iNoCvs = 0;
DrawCPts=FALSE;
pParent=Parrent;
pCVsV[0]=NULL;
pCVsV[1]=NULL;
iNoTrimCvs=0;
iNoExtCvs=0;
iNoIntLoops=0;
vNorm=vN;
vCent=vC;
double r2;
r2=1.4142135623730950488016887242097;

AddCV(pCIn);
C3dVector v;
C3dMatrix Glob2;
Glob2=Glob;
v.x=-Glob.m_30;
v.y=-Glob.m_31;
v.z=-Glob.m_32;
Glob.m_30=0;
Glob.m_31=0;
Glob.m_32=0;


Glob.Transpose();
pCVsU[0]->Translate(v);
pCVsU[0]->Transform(Glob);

AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(45);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->CPolyRot(90);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(135);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->CPolyRot(180);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(225);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->CPolyRot(270);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(315);
AddCV(pCVsU[0]);



int i;
for (i=0;i<iNoCvs;i++)
{
  pCVsU[i]->Transform(Glob2);
}
}

void NSurfR::CreateRev(NCurve* pCIn,C3dVector vN,C3dVector vC,C3dVector vRef,int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 16;
G_label = iLab;
iObjType = 16;
iNoCvs = 0;
DrawCPts=FALSE;
pParent=Parrent;
pCVsV[0]=NULL;
pCVsV[1]=NULL;
iNoTrimCvs=0;
iNoExtCvs=0;
iNoIntLoops=0;
vNorm=vN;
vCent=vC;
C3dMatrix Glob;
C3dVector vX,vY,vZ;
double r2;
r2=1.4142135623730950488016887242097;

AddCV(pCIn);
C3dVector v;
C3dMatrix Glob2;

v=-vC;
vX=vRef;
vY=vN;
vX.Normalize();
vY.Normalize();
vZ=vX.Cross(vY);
Glob.SetColVec(1,vX);
Glob.SetColVec(2,vY);
Glob.SetColVec(3,vZ);
Glob2=Glob;
Glob2.Translate(vC.x,vC.y,vC.z);
Glob.Transpose();
pCVsU[0]->Translate(v);
pCVsU[0]->Transform(Glob);

AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(45);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->CPolyRot(90);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(135);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->CPolyRot(180);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(225);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->CPolyRot(270);
AddCV(pCVsU[0]);
pCVsU[iNoCvs-1]->ScaleX(r2);
pCVsU[iNoCvs-1]->ScaleW(r2/2);
pCVsU[iNoCvs-1]->CPolyRot(315);
AddCV(pCVsU[0]);



int i;
for (i=0;i<iNoCvs;i++)
{
  pCVsU[i]->Transform(Glob2);
}
}


BOOL NSurfR::Generate(int pInV,double dvs,double dve)
{
BOOL brc;
brc = NSurf::Generate(2,dvs,dve);
if (brc==FALSE)
{
  pCVsV[0]->knots[0]=0;
  pCVsV[0]->knots[1]=0;
  pCVsV[0]->knots[2]=0;
  pCVsV[0]->knots[3]=0.25;
  pCVsV[0]->knots[4]=0.25;
  pCVsV[0]->knots[5]=0.5;
  pCVsV[0]->knots[6]=0.5;
  pCVsV[0]->knots[7]=0.75;
  pCVsV[0]->knots[8]=0.75;
  pCVsV[0]->knots[9]=1.0;
  pCVsV[0]->knots[10]=1.0;
  pCVsV[0]->knots[11]=1.0;

  pCVsV[1]->knots[0]=0;
  pCVsV[1]->knots[1]=0;
  pCVsV[1]->knots[2]=0;
  pCVsV[1]->knots[3]=0.25;
  pCVsV[1]->knots[4]=0.25;
  pCVsV[1]->knots[5]=0.5;
  pCVsV[1]->knots[6]=0.5;
  pCVsV[1]->knots[7]=0.75;
  pCVsV[1]->knots[8]=0.75;
  pCVsV[1]->knots[9]=1.0;
  pCVsV[1]->knots[10]=1.0;
  pCVsV[1]->knots[11]=1.0;

}

return(brc);
}

void NSurfR::Serialize(CArchive& ar)
{
NSurf::Serialize(ar);
vNorm.Serialize(ar);
vCent.Serialize(ar);
}

G_Object* NSurfR::Copy(G_Object* Parrent)
{

NSurfR* pSurf = new NSurfR();
NSurf::Copy2(pSurf);
pSurf->pParent=Parrent;
pSurf->vNorm=vNorm;
pSurf->vCent=vCent;
return(pSurf);
}

IMPLEMENT_DYNAMIC(NSurfE, CObject)


NSurfE::NSurfE()
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 13;
G_label = -1;
iObjType = 17;
iNoCvs = 0;
DrawCPts=FALSE;
pCVsV[0]=NULL;
pCVsV[1]=NULL;
iNoTrimCvs=0;
iNoExtCvs=0;
}


    // CvPt_Object* pVertex[20];
void NSurfE::Create(NCurve* pCIn1,NCurve* pCIn2,C3dVector vTr,int iLab,G_Object* Parrent)
{
Drawn = 0;
Selectable  = 1; 
Visable  = 1;
G_Colour = 16;
G_label = iLab;
iObjType = 17;
iNoCvs = 0;
DrawCPts=FALSE;
pParent=Parrent;
pCVsV[0]=NULL;
pCVsV[1]=NULL;
vTran=vTr;
iNoTrimCvs=0;
iNoExtCvs=0;
AddCV(pCIn1);
AddCV(pCIn2);
iNoIntLoops=0;
}

BOOL NSurfE::Generate(int pInV,double dvs,double dve)
{
BOOL brc;
brc = NSurf::Generate(1,dvs,dve);
return(brc);
}

G_Object* NSurfE::Copy(G_Object* Parrent)
{

NSurfE* pSurf = new NSurfE();
NSurf::Copy2(pSurf);
pSurf->pParent=Parrent;
pSurf->vTran=vTran;
return(pSurf);
}

void NSurfE::Serialize(CArchive& ar)
{
NSurf::Serialize(ar);
vTran.Serialize(ar);
}


IgesP::IgesP()
{

iNo=0;
}

void IgesP::Add(CString inSt)
{
P[iNo]=inSt;
iNo++;
}

CString IgesP::getPLine(int pInd,int iNo)
{
int i;
int iC;
CString sL="";
for (i=0;i<iNo;i++)
{
  sL+=P[pInd-1+i];
	if (i==iNo-1)
	{
    iC=sL.ReverseFind(';');
	  sL=sL.Left(iC);
	}
	else
	{
    iC=sL.ReverseFind(',');
	  sL=sL.Left(iC+1);
	}
    
}
sL+=',';
return (sL);





}BEGIN_MESSAGE_MAP(CFilterDialog, CDialog)
ON_LBN_SELCHANGE(IDC_LIST1, &CFilterDialog::OnLbnSelchangeList1)
ON_LBN_DBLCLK(IDC_LIST1, &CFilterDialog::OnLbnDblclkList1)
ON_LBN_DBLCLK(IDC_LIST2, &CFilterDialog::OnLbnDblclkList2)
ON_BN_CLICKED(IDC_BUTTON1, &CFilterDialog::OnBnClickedButton1)
ON_BN_CLICKED(IDC_CLEAR_FIL, &CFilterDialog::OnBnClickedClearFil)
ON_BN_CLICKED(IDC_BUTTON2, &CFilterDialog::OnBnClickedButton2)
END_MESSAGE_MAP()

//*****************************************************************
//The filter dialog box
//*****************************************************************
CFilterDialog::CFilterDialog()
	: CDialog(CFilterDialog::IDD, NULL)
{
}

void CFilterDialog::OnLbnSelchangeList1()
{
  // TODO: Add your control notification handler code here
}


void CFilterDialog::ReSet()
{
  int i;
  CListBox* pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST1);
  CListBox* pItemsNonSelectable=(CListBox*) GetDlgItem(IDC_LIST2);
  char OutT[80];

  for (i=0;i<pFilt->iNoOfType;i++)
  {
    sprintf_s(OutT,"%i : %s",pFilt->iType[i],pFilt->sType[i]);
    if (pFilt->isFilter(pFilt->iType[i])==TRUE)
    {
      pItemsNonSelectable->AddString(OutT);
    }
    else
    {
      pItemsSelectable->AddString(OutT);
    }
  }
}

BOOL CFilterDialog::OnInitDialog()
{

  CDialog::OnInitDialog();
  
  // TODO:  Add extra initialization here
  ReSet();
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilterDialog::OnLbnDblclkList1()
{
  // TODO: Add your control notification handler code here
  CListBox* pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST1);
  int ind = pItemsSelectable->GetCurSel();
  CString cT;
  pItemsSelectable->GetText(ind,cT);
  int i1;
  CString sR;
  i1=cT.Find(":");
  sR=cT.Left(i1-1);
  ind=atoi(sR);
  pFilt->SetFilter(ind);
  pItemsSelectable->ResetContent();
  pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST2);
  pItemsSelectable->ResetContent();
  ReSet();
}

void CFilterDialog::OnLbnDblclkList2()
{
  // TODO: Add your control notification handler code here
  CListBox* pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST2);
  int ind = pItemsSelectable->GetCurSel();
  CString cT;
  pItemsSelectable->GetText(ind,cT);
  int i1;
  CString sR;
  i1=cT.Find(":");
  sR=cT.Left(i1-1);
  ind=atoi(sR);
  pFilt->RemFilter(ind);
  pItemsSelectable->ResetContent();
  pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST1);
  pItemsSelectable->ResetContent();
  ReSet();
  
}

void CFilterDialog::OnBnClickedButton1()
{
  pFilt->SetAll();
  CListBox* pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST2);
  pItemsSelectable->ResetContent();
  pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST1);
  pItemsSelectable->ResetContent();
  ReSet();
}

void CFilterDialog::OnBnClickedClearFil()
{
  // TODO: Add your control notification handler code here
  pFilt->Clear();
  CListBox* pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST2);
  pItemsSelectable->ResetContent();
  pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST1);
  pItemsSelectable->ResetContent();
  ReSet();
}

void CFilterDialog::OnBnClickedButton2()
{
  // TODO: Add your control notification handler code here
  int ind;
  int ind2;
  int i1;
  CString cT;
  CString sR;
  CListBox* pItemsSelectable=(CListBox*) GetDlgItem(IDC_LIST2);
  CListBox* pItemsNonSelectable=(CListBox*) GetDlgItem(IDC_LIST1);
  ind=pItemsSelectable->GetCurSel();
  ind2=pItemsNonSelectable->GetCurSel();
  if ((ind>=0) || (ind2>=0))
  {

    pFilt->Clear();
  }
  if (ind>=0)
  {
    pItemsSelectable->GetText(ind,cT);
    i1=cT.Find(":");
    sR=cT.Left(i1-1);
    ind=atoi(sR);
    pFilt->SetFilter(ind);
  }
  if (ind2>=0)
  {
    pItemsNonSelectable->GetText(ind2,cT);
    i1=cT.Find(":");
    sR=cT.Left(i1-1);
    ind2=atoi(sR);
    pFilt->SetFilter(ind2);
  }
  if ((ind>=0) || (ind2>=0))
  {
    pItemsSelectable->ResetContent();
    pItemsNonSelectable->ResetContent();
    ReSet();
  }
  OnOK();
}




CGroupDialog::CGroupDialog()
	: CDialog(CGroupDialog::IDD, NULL)
{
iNo=0;
}


void CGroupDialog::AddGroup(CString sName)
{
Groups[iNo]=sName;
iNo++;
}

BOOL CGroupDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  int i;
  char OutT[80];
  CListBox* pGroups=(CListBox*) GetDlgItem(IDC_GROUP_SEL);

  for (i=0;i<iNo;i++)
  {
    sprintf_s(OutT,"%i : %s",i,Groups[i]);
    pGroups->AddString(OutT);
  }
  if (iGp!=-1)
  {
    pGroups->SetCurSel(iGp);
  }
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
  

BEGIN_MESSAGE_MAP(CGroupDialog, CDialog)
  ON_BN_CLICKED(IDOK, &CGroupDialog::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &CGroupDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

void CGroupDialog::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  CListBox* pGroups=(CListBox*) GetDlgItem(IDC_GROUP_SEL);
  iGp=pGroups->GetCurSel();
  OnOK();
}

void CGroupDialog::OnBnClickedCancel()
{
  // TODO: Add your control notification handler code here
  iGp=-1;
  OnCancel();
}


CRelToDialog::CRelToDialog()
	: CDialog(CRelToDialog::IDD, NULL)
{
}


BOOL CRelToDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

int i;
  CListBox* pTypes=(CListBox*) GetDlgItem(IDC_LIST_RELTO);
  char OutT[80];
  for (i=0;i<pFilt->iNoOfType;i++)
  {
    sprintf_s(OutT,"%i : %s",pFilt->iType[i],pFilt->sType[i]);
    pTypes->AddString(OutT);
  }

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CRelToDialog, CDialog)
  ON_LBN_DBLCLK(IDC_LIST_RELTO, &CRelToDialog::OnLbnDblclkListRelto)
END_MESSAGE_MAP()

void CRelToDialog::OnLbnDblclkListRelto()
{
  int ind;
  int i1;
  CString sR;
  // TODO: Add your control notification handler code here
  CListBox* pTypes=(CListBox*) GetDlgItem(IDC_LIST_RELTO);
  iType=pTypes->GetCurSel();
  CString cT;
  pTypes->GetText(iType,cT);
  i1=cT.Find(":");
  sR=cT.Left(i1-1);
  ind=atoi(sR);
  iType=ind;
  OnOK();
}


IMPLEMENT_DYNAMIC( BSec, CObject )

BSec::~BSec()
{
iLnCnt1=0;
iLnCnt2=0;
}

void BSec::Clear()
{
iLnCnt1=0;
iLnCnt2=0;
}

BSec::BSec()
{
int iLnCnt1=0;
int iLnCnt2=0;
}

void BSec::Create()
{
int iLnCnt1=0;
int iLnCnt2=0;
}

void BSec::CreateDefSec(double W,int iC)
{
Clear();
AddOutPt(-W,-W);
AddOutPt(-W,+W);
AddOutPt(+W,+W);
AddOutPt(+W,-W);
AddOutPt(-W,-W);
}

void BSec::CreateBox(double W,double H,double Wthk,double Hthk)
{
Clear();
W/=2;
H/=2;
AddOutPt(-W,-H);
AddOutPt(-W,+H);
AddOutPt(+W,+H);
AddOutPt(+W,-H);
AddOutPt(-W,-H);
W-=Wthk;
H-=Hthk;
AddInPt(-W,-H);
AddInPt(-W,+H);
AddInPt(+W,+H);
AddInPt(+W,-H);
AddInPt(-W,-H);
}

void BSec::CreateBar(double W,double H)
{
Clear();
W/=2;
H/=2;
AddOutPt(-W,-H);
AddOutPt(-W,+H);
AddOutPt(+W,+H);
AddOutPt(+W,-H);
AddOutPt(-W,-H);
}

void BSec::CreateI(double WH,double BW,double TW,double WT,double BWT,double TWT)
{
Clear();
WH/=2;
BW/=2;
TW/=2;
AddOutPt(-BW,-WH);
AddOutPt(+BW,-WH);
AddOutPt(+BW,-WH+BWT);
AddOutPt(+WT/2,-WH+BWT);
AddOutPt(+WT/2, WH-TWT);
AddOutPt(TW, WH-TWT);
AddOutPt(TW, WH);
AddOutPt(-TW, WH);
AddOutPt(-TW, WH-TWT);
AddOutPt(-WT/2, WH-TWT);
AddOutPt(-WT/2, -WH+BWT);
AddOutPt(-BW,-WH+BWT);
AddOutPt(-BW,-WH);
}


void BSec::CreateRod(double R)
{
Clear();
int i;
double Ang=0;
double AngInc;
AngInc=(360.0/(MAX_SECPTS-1))*D2R;
for (i=0;i<MAX_SECPTS-1;i++)
{
  AddOutPt(R*sin(Ang),R*cos(Ang));
  Ang+=AngInc;
}
AddOutPt(R*sin(0.0),R*cos(0.0));
}

void BSec::CreateTube(double R,double r)
{
Clear();
int i;
double Ang=0;
double AngInc;
AngInc=(360.0/(MAX_SECPTS-1))*D2R;
for (i=0;i<MAX_SECPTS-1;i++)
{
  AddOutPt(R*sin(Ang),R*cos(Ang));
  Ang+=AngInc;
}
AddOutPt(R*sin(0.0),R*cos(0.0));
Ang=0;
for (i=0;i<MAX_SECPTS-1;i++)
{
  AddInPt(r*sin(Ang),r*cos(Ang));
  Ang+=AngInc;
}
AddInPt(r*sin(0.0),r*cos(0.0));
}


void BSec::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
	  ar<<iLnCnt1;
    ar<<iLnCnt2;
	  ar<<inPt.x;
    ar<<inPt.y;
    ar<<inPt.z;
    ar<<iLnCnt1;
    for(i=0;i<iLnCnt1;i++)
    {
      ar<<pLnLoop1[i].x;
      ar<<pLnLoop1[i].y;
      ar<<pLnLoop1[i].z;
    }
    ar<<iLnCnt2;
    for(i=0;i<iLnCnt2;i++)
    {
      ar<<pLnLoop2[i].x;
      ar<<pLnLoop2[i].y;
      ar<<pLnLoop2[i].z;
    }
	}
	else
	{
	  ar>>iLnCnt1;
    ar>>iLnCnt2;
	  ar>>inPt.x;
    ar>>inPt.y;
    ar>>inPt.z;
    ar>>iLnCnt1;
    for(i=0;i<iLnCnt1;i++)
    {
      ar>>pLnLoop1[i].x;
      ar>>pLnLoop1[i].y;
      ar>>pLnLoop1[i].z;
    }
    ar>>iLnCnt2;
    for(i=0;i<iLnCnt2;i++)
    {
      ar>>pLnLoop2[i].x;
      ar>>pLnLoop2[i].y;
      ar>>pLnLoop2[i].z;
    }
	}	
}

void BSec::OglDraw(int iDspFlgs,C3dMatrix TA,C3dMatrix TB,C3dVector d0,C3dVector d1,float C1,float C2,BOOL bD)
{

C3dVector p1;
C3dVector p2;
C3dVector p3;
C3dVector p4;


int j=0;
if (((iDspFlgs & DSP_CONT)>0) || (bD=FALSE))
{
  if (iLnCnt1 > 1)
  {
    for (j=0;j<iLnCnt1-1;j++)
    {
      p1=TA*pLnLoop1[j+1];
      p2=TA*pLnLoop1[j];
      p3=TB*pLnLoop1[j];
      p4=TB*pLnLoop1[j+1];
      glBegin(GL_POLYGON);
	      glVertex3f((float) p1.x+d0.x,(float) p1.y+d0.y,(float) p1.z+d0.z);
        glVertex3f((float) p4.x+d1.x,(float) p4.y+d1.y,(float) p4.z+d1.z);
        glVertex3f((float) p3.x+d1.x,(float) p3.y+d1.y,(float) p3.z+d1.z);
        glVertex3f((float) p2.x+d0.x,(float) p2.y+d0.y,(float) p2.z+d0.z);
         
      glEnd();
    }
  }
  if (iLnCnt2 > 1)
  {
    for (j=0;j<iLnCnt2-1;j++)
    {
      p1=TA*pLnLoop2[j];
      p2=TA*pLnLoop2[j+1];
      p3=TB*pLnLoop2[j+1];
      p4=TB*pLnLoop2[j];
      glBegin(GL_POLYGON);
	      glVertex3f((float) p1.x+d0.x,(float) p1.y+d0.y,(float) p1.z+d0.z);
        glVertex3f((float) p4.x+d1.x,(float) p4.y+d1.y,(float) p4.z+d1.z);
        glVertex3f((float) p3.x+d1.x,(float) p3.y+d1.y,(float) p3.z+d1.z);
        glVertex3f((float) p2.x+d0.x,(float) p2.y+d0.y,(float) p2.z+d0.z);
      glEnd();
    }
  }
}
else
{
  glColor3fv(cols[124]);
  glEnable(GL_TEXTURE_1D);
  if (iLnCnt1 > 1)
  {
    for (j=0;j<iLnCnt1-1;j++)
    {
      p1=TA*pLnLoop1[j+1];
      p2=TA*pLnLoop1[j];
      p3=TB*pLnLoop1[j];
      p4=TB*pLnLoop1[j+1];
      glBegin(GL_POLYGON);
        glTexCoord1f(C1);
	      glVertex3f((float) p1.x+d0.x,(float) p1.y+d0.y,(float) p1.z+d0.z);
        glTexCoord1f(C2);
        glVertex3f((float) p4.x+d1.x,(float) p4.y+d1.y,(float) p4.z+d1.z);
        glTexCoord1f(C2);
        glVertex3f((float) p3.x+d1.x,(float) p3.y+d1.y,(float) p3.z+d1.z);
        glTexCoord1f(C1);
        glVertex3f((float) p2.x+d0.x,(float) p2.y+d0.y,(float) p2.z+d0.z);


      glEnd();
    }
  }
  if (iLnCnt2 > 1)
  {
    for (j=0;j<iLnCnt2-1;j++)
    {
      p1=TA*pLnLoop2[j];
      p2=TA*pLnLoop2[j+1];
      p3=TB*pLnLoop2[j+1];
      p4=TB*pLnLoop2[j];
      glBegin(GL_POLYGON);
	      glVertex3f((float) p1.x+d0.x,(float) p1.y+d0.y,(float) p1.z+d0.z);
        glVertex3f((float) p4.x+d1.x,(float) p4.y+d1.y,(float) p4.z+d1.z);
        glVertex3f((float) p3.x+d1.x,(float) p3.y+d1.y,(float) p3.z+d1.z);
        glVertex3f((float) p2.x+d0.x,(float) p2.y+d0.y,(float) p2.z+d0.z);
      glEnd();
    }
  }
glDisable(GL_TEXTURE_1D);
}
}

void BSec::OglDrawW(int iDspFlgs,C3dMatrix TMat,C3dVector d0,C3dVector d1)
{
C3dVector p1;
C3dVector p2;
C3dVector vOf;
vOf=d0;
vOf+=d1;
vOf*=0.5;
int j=0;
if (iLnCnt1 > 1)
{
  for (j=0;j<iLnCnt1-1;j++)
  {
    p1=TMat*pLnLoop1[j];
    p2=TMat*pLnLoop1[j+1];
    glBegin(GL_LINES);
	    glVertex3f((float) p1.x+vOf.x,(float) p1.y+vOf.y,(float) p1.z+vOf.z);
      glVertex3f((float) p2.x+vOf.x,(float) p2.y+vOf.y,(float) p2.z+vOf.z);
    glEnd();
  }
}
if (iLnCnt2>1)
{
  for (j=0;j<iLnCnt2-1;j++)
  {
    p1=TMat*pLnLoop2[j];
    p2=TMat*pLnLoop2[j+1];
    glBegin(GL_LINES);
	    glVertex3f((float) p1.x+vOf.x,(float) p1.y+vOf.y,(float) p1.z+vOf.z);
      glVertex3f((float) p2.x+vOf.x,(float) p2.y+vOf.y,(float) p2.z+vOf.z);
    glEnd();
  }
}
}


void BSec::AddOutPt(double X1,double Y1)
{
if (iLnCnt1<MAX_SECPTS)
{
  pLnLoop1[iLnCnt1].Set(X1,Y1,0);
  iLnCnt1++;
}
}


void BSec::AddInPt(double X1,double Y1)
{
if (iLnCnt2<MAX_SECPTS)
{
  pLnLoop2[iLnCnt2].Set(X1,Y1,0);
  iLnCnt2++;
}
}

IMPLEMENT_DYNAMIC(MatTable, CObject )

Material* MatTable::GetItem(int iID)
{
Material* pRet;
pRet=(Material*) Table::GetItem(iID);
return (pRet);
}



void MatTable::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
    ar << iNo;
	  for (i=0;i<iNo;i++)
    {
      ar<<pEnts[i]->iType;
      pEnts[i]->Serialize(ar);
    }
  }
  else
  {
    int iE;
    ar >> iNo;
	  for (i=0;i<iNo;i++)
    {
      ar>>iE;
      switch(iE) 
      {
		    case 1:
          pEnts[i] = new MAT1;
          break;
		    case 8:
          pEnts[i] = new MAT8;
          break;
      }
      pEnts[i]->Serialize(ar);
    }
  }
}


IMPLEMENT_DYNAMIC(PropTable, CObject )

Property* PropTable::GetItem(int iID)
{
Property* pRet;
pRet=(Property*) Table::GetItem(iID);
return (pRet);
}

void PropTable::UpdateMats(NEList* newMats)
{
int i;
Property* pRet;
for (i=0;i<iNo;i++)
{
  pRet=(Property*) pEnts[i];
  pRet->UpdateMats(newMats);
}

}

PBARL* PropTable::GetPBARL(CString sT,double W,double H, double dTHK,double dNSM,int iM)
{
int i;
PBARL* pRet=NULL;
PBARL* pB=NULL;
for (i=0;i<iNo;i++)
{
  if (pEnts[i]->iType==5)
  {
    pB=(PBARL*) pEnts[i];
    if ((pB->sSecType==sT) &&
        (pB->dNSM==dNSM) &&
        (pB->iMID==iM) &&
        (pB->dDIMs[0]==W) &&
        (pB->dDIMs[1]==H) &&
        (pB->dDIMs[2]==dTHK))
    {
      pRet=pB;
    }
  }
}
return(pRet);
}

PSHELL* PropTable::GetShell(double dTHK,double dNSM,int iM)
{
int i;
PSHELL* pRet=NULL;
PSHELL* pS=NULL;
for (i=0;i<iNo;i++)
{
  if (pEnts[i]->iType==1)
  {
    pS=(PSHELL*) pEnts[i];
    if ((pS->dT==dTHK) &&
        (pS->iMID1==iM) &&
        (pS->dNSM==dNSM))
    {pRet=pS;}
  }
}

return(pRet);
}


void PropTable::Serialize(CArchive& ar)
{
  int i;
	if (ar.IsStoring())
	{
    ar << iNo;
	  for (i=0;i<iNo;i++)
    {
      ar<<pEnts[i]->iType;
      pEnts[i]->Serialize(ar);
    }
  }
  else
  {
    int iE;
    ar >> iNo;
	  for (i=0;i<iNo;i++)
    {
      ar>>iE;
      switch(iE) 
      {
		    case 1:
          pEnts[i] = new PSHELL;
          break;
		    case 2:
          pEnts[i] = new PCOMP;
          break;
        case 3:
          pEnts[i] = new PSOLID;
          break;
        case 4:
          pEnts[i] = new PBAR;
          break;
        case 5:
          pEnts[i] = new PBARL;
          break;
        case 6:
          pEnts[i] = new PBEAM;
          break;
        case 11:
          pEnts[i] = new PROD;
          break;
      }
      pEnts[i]->Serialize(ar);
      if (iE==4)
      {
        PBAR* pbar = (PBAR*) pEnts[i];
        pbar->CreateSec();
      }
      else if (iE==6)
      {
        PBEAM* pbar = (PBEAM*) pEnts[i];
        pbar->CreateSec();
      }
    }
  }
}
//****************************************************************
//PROPERTY TABLE
//****************************************************************
IMPLEMENT_DYNAMIC(Table, CObject )

Table::Table()
{
  iNo=0;
}

void Table::AddItem(Entity* pIn)
{
BOOL bisIn =  Exists(pIn->iID);
if (bisIn==FALSE)
{
  if (iNo<MAX_ENTS)
  {
     pEnts[iNo]=pIn;
     iNo++;
  }
  else
  {

       outtext1("ERROR Max no in Table exceeded");
  }
}
else
{
    char S1[80];
    sprintf_s(S1,"%s%i","Warning Property Conflict ",pIn->iID);
    outtext1(S1); 
}
}

 BOOL Table::Exists(int iPID)
{
int i;
BOOL bRet=FALSE;
for (i=0;i<iNo;i++)
{
  if (pEnts[i]->iID==iPID)
  {
     bRet=TRUE;
     break;
  }
}
return (bRet);

}



Entity* Table::GetItem(int iID)
{
Entity* pRet=NULL;
int i;
for (i=0;i<iNo;i++)
{
  if (pEnts[i]->iID==iID)
  {
     pRet=pEnts[i];
     break;
  }
}
return (pRet);
}

void Table::ExportNAS(FILE* pF)
{
int i;
for (i=0;i<iNo;i++)
{
   pEnts[i]->ExportNAS(pF);
}
}

void Table::ListAll()
{
int i;
if (iNo>0)
{
  for (i=0;i<iNo;i++)
  {
   pEnts[i]->ListShort();
  }
}
else
{
  outtext1("None defined");
}
}

int Table::NextID()
{
int i;
int iRet=0;
if (iNo>0)
{
  for (i=0;i<iNo;i++)
  {
   if (pEnts[i]->iID>iRet)
   {
     iRet=pEnts[i]->iID;
   }
  }
}
iRet++;
return (iRet);
}

void Table::Serialize(CArchive& ar)
{

}

BEGIN_MESSAGE_MAP(CResSelDialog, CDialog)
  ON_BN_CLICKED(IDOK, &CResSelDialog::OnBnClickedOk)
  ON_LBN_SELCANCEL(IDC_LIST_RES, &CResSelDialog::OnLbnSelcancelListRes)
  ON_LBN_SELCHANGE(IDC_LIST_RES, &CResSelDialog::OnLbnSelchangeListRes)
END_MESSAGE_MAP()

//*****************************************************************
//The Res dialog box
//*****************************************************************
CResSelDialog::CResSelDialog()
	: CDialog(CResSelDialog::IDD, NULL)
{
  iNoRes=0;
  iCurResSet=-1;
  iResVal=-1;
}

void CResSelDialog::SetData(ResSet* pInRes[],int iInNoRes,int iInCurResSet,int iInResVal)
{
int i;
iNoRes=iInNoRes;
for (i=0;i<iInNoRes;i++)
{
  pRes[i]=pInRes[i];
}
iCurResSet=iInCurResSet;
iResVal=iInResVal;
}

void CResSelDialog::Init()
{
int i;
CListBox* pResList=(CListBox*) GetDlgItem(IDC_LIST_RES);
char OutT[80];
if (iNoRes>0)
{
  for (i=0;i<iNoRes;i++)
  {
    sprintf_s(OutT,"%i: LC %i : %s",i,pRes[i]->LC,pRes[i]->sName);
    pResList->AddString(OutT);
  }
}
}

void CResSelDialog::OnBnClickedOk()
{
CListBox* pResList=(CListBox*) GetDlgItem(IDC_LIST_RES);
CListBox* pValList=(CListBox*) GetDlgItem(IDC_LIST_VAL);
  // TODO: Add your control notification handler code here
  OnOK();
iCurResSet=pResList->GetCurSel();
iResVal=pValList->GetCurSel();
}

BOOL CResSelDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  Init();
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CResSelDialog::OnLbnSelcancelListRes()
{
  // TODO: Add your control notification handler code here

}

void CResSelDialog::OnLbnSelchangeListRes()
{
  // TODO: Add your control notification handler code here
  int i;
CListBox* pResList=(CListBox*) GetDlgItem(IDC_LIST_RES);
CListBox* pValList=(CListBox*) GetDlgItem(IDC_LIST_VAL);
int ind = pResList->GetCurSel();
pValList->ResetContent();
char OutT[80];
for (i=0;i<pRes[ind]->iNoV;i++)
{
  sprintf_s(OutT,"%i : %s",i,pRes[ind]->lab[i]);
  pValList->AddString(OutT);
}
}
