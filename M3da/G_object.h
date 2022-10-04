#include "stdafx.h"


#include <stdlib.h>
#include "resource.h"
#include "FONT_DEF.h"
#include "3dSupport.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
using namespace std;

#define DBL_MAX 1.7976931348623158e+308 /* max value */
//Arrow head definition
const double AHead [7][3] =
{{2.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.500000},
{0.000000, 0.433012, 0.250000},
{0.000000, 0.433012, -0.25000},
{0.000000, 0.000000, -0.50000},
{0.000000, -0.43301, -0.25000},
{0.000000, -0.43301, 0.250000} };

//FEMAP COLORS
const float cols[167][3] ={{0.0f,0.0f,0.0f},
{0.254901960784314f,0.0f,0.0f},
{0.501960784313725f,0.0f,0.0f},
{0.752941176470588f,0.0f,0.0f},
{1.0f,0.0f,0.0f},
{0.0f,0.254901960784314f,0.0f},
{0.254901960784314f,0.254901960784314f,0.0f},
{0.501960784313725f,0.254901960784314f,0.0f},
{0.752941176470588f,0.254901960784314f,0.0f},
{1.0f,0.254901960784314f,0.0f},
{0.0f,0.501960784313725f,0.0f},
{0.254901960784314f,0.501960784313725f,0.0f},
{0.501960784313725f,0.501960784313725f,0.0f},
{0.752941176470588f,0.501960784313725f,0.0f},
{1.0f,0.501960784313725f,0.0f},
{0.0f,0.752941176470588f,0.0f},
{0.254901960784314f,0.752941176470588f,0.0f},
{0.501960784313725f,0.752941176470588f,0.0f},
{0.752941176470588f,0.752941176470588f,0.0f},
{1.0f,0.752941176470588f,0.0f},
{0.0f,1.0f,0.0f},
{0.254901960784314f,1.0f,0.0f},
{0.501960784313725f,1.0f,0.0f},
{0.752941176470588f,1.0f,0.0f},
{1.0f,1.0f,0.0f},
{0.0f,0.0f,0.254901960784314f},
{0.254901960784314f,0.0f,0.254901960784314f},
{0.501960784313725f,0.0f,0.254901960784314f},
{0.752941176470588f,0.0f,0.254901960784314f},
{1.0f,0.0f,0.254901960784314f},
{0.0f,0.254901960784314f,0.254901960784314f},
{0.254901960784314f,0.254901960784314f,0.254901960784314f},
{0.501960784313725f,0.254901960784314f,0.254901960784314f},
{0.752941176470588f,0.254901960784314f,0.254901960784314f},
{1.0f,0.254901960784314f,0.254901960784314f},
{0.0f,0.501960784313725f,0.254901960784314f},
{0.254901960784314f,0.501960784313725f,0.254901960784314f},
{0.501960784313725f,0.501960784313725f,0.254901960784314f},
{0.752941176470588f,0.501960784313725f,0.254901960784314f},
{1.0f,0.501960784313725f,0.254901960784314f},
{0.0f,0.752941176470588f,0.254901960784314f},
{0.254901960784314f,0.752941176470588f,0.254901960784314f},
{0.501960784313725f,0.752941176470588f,0.254901960784314f},
{0.752941176470588f,0.752941176470588f,0.254901960784314f},
{1.0f,0.752941176470588f,0.254901960784314f},
{0.0f,1.0f,0.254901960784314f},
{0.254901960784314f,1.0f,0.254901960784314f},
{0.501960784313725f,1.0f,0.254901960784314f},
{0.752941176470588f,1.0f,0.254901960784314f},
{1.0f,1.0f,0.254901960784314f},
{0.0f,0.0f,0.501960784313725f},
{0.254901960784314f,0.0f,0.501960784313725f},
{0.501960784313725f,0.0f,0.501960784313725f},
{0.752941176470588f,0.0f,0.501960784313725f},
{1.0f,0.0f,0.501960784313725f},
{0.0f,0.254901960784314f,0.501960784313725f},
{0.254901960784314f,0.254901960784314f,0.501960784313725f},
{0.501960784313725f,0.254901960784314f,0.501960784313725f},
{0.752941176470588f,0.254901960784314f,0.501960784313725f},
{1.0f,0.254901960784314f,0.501960784313725f},
{0.0f,0.501960784313725f,0.501960784313725f},
{0.254901960784314f,0.501960784313725f,0.501960784313725f},
{0.501960784313725f,0.501960784313725f,0.501960784313725f},
{0.752941176470588f,0.501960784313725f,0.501960784313725f},
{1.0f,0.501960784313725f,0.501960784313725f},
{0.0f,0.752941176470588f,0.501960784313725f},
{0.254901960784314f,0.752941176470588f,0.501960784313725f},
{0.501960784313725f,0.752941176470588f,0.501960784313725f},
{0.752941176470588f,0.752941176470588f,0.501960784313725f},
{1.0f,0.752941176470588f,0.501960784313725f},
{0.0f,1.0f,0.501960784313725f},
{0.254901960784314f,1.0f,0.501960784313725f},
{0.501960784313725f,1.0f,0.501960784313725f},
{0.752941176470588f,1.0f,0.501960784313725f},
{1.0f,1.0f,0.501960784313725f},
{0.0f,0.0f,0.752941176470588f},
{0.254901960784314f,0.0f,0.752941176470588f},
{0.501960784313725f,0.0f,0.752941176470588f},
{0.752941176470588f,0.0f,0.752941176470588f},
{1.0f,0.0f,0.752941176470588f},
{0.0f,0.254901960784314f,0.752941176470588f},
{0.254901960784314f,0.254901960784314f,0.752941176470588f},
{0.501960784313725f,0.254901960784314f,0.752941176470588f},
{0.752941176470588f,0.254901960784314f,0.752941176470588f},
{1.0f,0.254901960784314f,0.752941176470588f},
{0.0f,0.501960784313725f,0.752941176470588f},
{0.254901960784314f,0.501960784313725f,0.752941176470588f},
{0.501960784313725f,0.501960784313725f,0.752941176470588f},
{0.752941176470588f,0.501960784313725f,0.752941176470588f},
{1.0f,0.501960784313725f,0.752941176470588f},
{0.0f,0.752941176470588f,0.752941176470588f},
{0.254901960784314f,0.752941176470588f,0.752941176470588f},
{0.501960784313725f,0.752941176470588f,0.752941176470588f},
{0.752941176470588f,0.752941176470588f,0.752941176470588f},
{1.0f,0.752941176470588f,0.752941176470588f},
{0.0f,1.0f,0.752941176470588f},
{0.254901960784314f,1.0f,0.752941176470588f},
{0.501960784313725f,1.0f,0.752941176470588f},
{0.752941176470588f,1.0f,0.752941176470588f},
{1.0f,1.0f,0.752941176470588f},
{0.0f,0.0f,1.0f},
{0.254901960784314f,0.0f,1.0f},
{0.501960784313725f,0.0f,1.0f},
{0.752941176470588f,0.0f,1.0f},
{1.0f,0.0f,1.0f},
{0.0f,0.254901960784314f,1.0f},
{0.254901960784314f,0.254901960784314f,1.0f},
{0.501960784313725f,0.254901960784314f,1.0f},
{0.752941176470588f,0.254901960784314f,1.0f},
{1.0f,0.254901960784314f,1.0f},
{0.0f,0.501960784313725f,1.0f},
{0.254901960784314f,0.501960784313725f,1.0f},
{0.501960784313725f,0.501960784313725f,1.0f},
{0.752941176470588f,0.501960784313725f,1.0f},
{1.0f,0.501960784313725f,1.0f},
{0.0f,0.752941176470588f,1.0f},
{0.254901960784314f,0.752941176470588f,1.0f},
{0.501960784313725f,0.752941176470588f,1.0f},
{0.752941176470588f,0.752941176470588f,1.0f},
{1.0f,0.752941176470588f,1.0f},
{0.0f,1.0f,1.0f},
{0.254901960784314f,1.0f,1.0f},
{0.501960784313725f,1.0f,1.0f},
{0.752941176470588f,1.0f,1.0f},
{1.0f,1.0f,1.0f},
{0.0392156862745098f,0.0392156862745098f,0.0392156862745098f},
{0.0784313725490196f,0.0784313725490196f,0.0784313725490196f},
{0.117647058823529f,0.117647058823529f,0.117647058823529f},
{0.156862745098039f,0.156862745098039f,0.156862745098039f},
{0.196078431372549f,0.196078431372549f,0.196078431372549f},
{0.235294117647059f,0.235294117647059f,0.235294117647059f},
{0.274509803921569f,0.274509803921569f,0.274509803921569f},
{0.313725490196078f,0.313725490196078f,0.313725490196078f},
{0.352941176470588f,0.352941176470588f,0.352941176470588f},
{0.392156862745098f,0.392156862745098f,0.392156862745098f},
{0.431372549019608f,0.431372549019608f,0.431372549019608f},
{0.470588235294118f,0.470588235294118f,0.470588235294118f},
{0.509803921568627f,0.509803921568627f,0.509803921568627f},
{0.549019607843137f,0.549019607843137f,0.549019607843137f},
{0.588235294117647f,0.588235294117647f,0.588235294117647f},
{0.627450980392157f,0.627450980392157f,0.627450980392157f},
{0.666666666666667f,0.666666666666667f,0.666666666666667f},
{0.705882352941177f,0.705882352941177f,0.705882352941177f},
{0.745098039215686f,0.745098039215686f,0.745098039215686f},
{0.784313725490196f,0.784313725490196f,0.784313725490196f},
{0.823529411764706f,0.823529411764706f,0.823529411764706f},
{0.862745098039216f,0.862745098039216f,0.862745098039216f},
{0.901960784313726f,0.901960784313726f,0.901960784313726f},
{0.941176470588235f,0.941176470588235f,0.941176470588235f},
{0.980392156862745f,0.980392156862745f,0.980392156862745f},
{0.00f, 0.00f, 0.00f},    //150 Black
{0.00f, 0.00f, 1.00f},    //151 Blue
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
{1.00f, 0.00f, 1.00f},    //162 Magenta
{1.00f, 0.33f, 1.00f},    //163 Light Magenta
{1.00f, 0.66f, 1.00f},    //164 Pink
{1.00f, 1.00f, 1.00f},    //165 White
{0.6f, 0.6f, 0.6f}};      //166Grey

const int MAX_RESSETS=50000;
class Part;
class Graph;
class ME_Object;
class G_Object;
class G_ObjectD;
class SecTable;
class ObjList;
class NCurveOnSurf;
class NSurf;
class CoordSys;
class Section;
class BSec;
class NEList;
class dList;
class Table;
class PropTable;
class MatTable;
class Restraint;
class ParPt;
class SolSets;
class CEntEditDialog;
class Ndata;
class Lamina;
//DIPLAY FLAGS
const int DSP_ALL = 0xFFFFFFF;
const int DSP_LINE = 0x00000001;
const int DSP_NODES = 0x00000002;
const int DSP_NODES_ASK = 0x00000004;
const int DSP_SHADED_EDGES = 0x00000008;
const int DSP_ELEMENTS = 0x00000010;
const int DSP_CURVES = 0x00000020;
const int DSP_SURFACES = 0x00000040;
const int DSP_THK = 0x00000080;
const int DSP_OFF = 0x00000100;
const int DSP_SURC = 0x00000200;
const int DSP_POINTS = 0x00000400;
const int DSP_BLACK = 0x00000800;
const int DSP_ASSEM = 0x00001000;
const int DSP_CONT = 0x00002000;
const int DSP_RESLAB = 0x00004000;
const int DSP_RESDEF = 0x00008000;
const int DSP_ELSYS = 0x00010000;
const int DSP_BC = 0x00020000;
const int DSP_GRAD = 0x00040000;
const int DSP_MATL = 0x00080000;
const int DSP_COORD = 0x00100000;
const int DSP_WP = 0x00200000;
const int DSP_SURFU = 0x00400000;
const int DSP_ANIMATION = 0x00800000;
const int DSP_ANIMPOSNEG = 0x01000000;
const int DSP_VEC = 0x20000000;
//DOF FLAGS
const int DOF_ALL = 0xFFFFFFFF;
const int DOF_1 = 0x00000001;
const int DOF_2 = 0x00000002;
const int DOF_3 = 0x00000004;
const int DOF_4 = 0x00000008;
const int DOF_5 = 0x00000010;
const int DOF_6 = 0x00000020;

//Defines the type and meaning of the results
class ResDef
{
public:
	CString sResType;
	// Define results type
		//0 Scalar    1 value    
		//1 Vector1   3 values
		//3 2D Tensor 3 Values + 2 Principals
		//4 3D Tensor 6 Values + 3 Principals
	int iResType = -1;
	// Defines results location
	// 0 Nodal
	// 1 Element Centroid
	// 2 Node on Element
	int iLoc = -1;
	// The locations of the components in results array
	int iComponents[9]; //adition components to send principles
	CString Lab9[9];
	int iCompNo = -1;



	ResDef()
	{
		iResType = -1;
		iCompNo = -1;
		sResType = "NULL";
		iLoc = -1;
		Lab9[0] = "0"; Lab9[1] = "1"; Lab9[2] = "2";
		Lab9[3] = "3"; Lab9[4] = "4"; Lab9[5] = "5";
		Lab9[6] = "6"; Lab9[7] = "7"; Lab9[8] = "8";
	}

	void GenDefualtHeaders()
	{
		if (iResType == 1)  //Vector
		{
			Lab9[0] = "Comp 1";
			Lab9[1] = "Comp 2";
			Lab9[2] = "Comp 3";
			Lab9[3] = "FULL";
		}
		else if (iResType == 3) //2d Tensor
		{
			Lab9[0] = "Comp 11";
			Lab9[1] = "Comp 22";
			Lab9[2] = "Comp 12";
			Lab9[3] = "Prin 1";
			Lab9[4] = "Prin 2";
		}
		else if (iResType == 4) //3d Tensor
		{
			Lab9[0] = "Comp 11";
			Lab9[1] = "Comp 22";
			Lab9[2] = "Comp 33";
			Lab9[3] = "Comp 12";
			Lab9[4] = "Comp 23";
			Lab9[5] = "Comp 13";
			Lab9[6] = "Prin 1";
			Lab9[7] = "Prin 2";
			Lab9[8] = "Prin 3";
		}
	}
};

class Res
{
public:

int ID;
Res* next;
C3dVector* pVec;

Res()
{
  next=NULL;
  pVec=NULL;
}

virtual C3dVector GetVec()
{
C3dVector pR;
pR.Set(0,0,0);
if (pVec!=NULL)
{
  pR.Set(pVec->x,pVec->y,pVec->z);
}

return (pR);
}

virtual float* GetAddress(int ind)
{
return (NULL);
}

};

class Res8 : public Res
{
public:
float v[8];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res10 : public Res
{
public:
float v[10];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res11 : public Res
{
public:
float v[11];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res12 : public Res
{
public:
float v[12];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res15 : public Res
{
public:
float v[15];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res13 : public Res
{
public:
	float v[13];

	virtual float* GetAddress(int ind)
	{
		return (&v[ind]);
	}

};

class Res16 : public Res
{
public:
float v[16];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res18 : public Res
{
public:
float v[18];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res21 : public Res
{
public:
	float v[21];

	virtual float* GetAddress(int ind)
	{
		return (&v[ind]);
	}

};

class Res189 : public Res
{
public:
int iSID;
char sType[4];
int iNoActive;

float v[189];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};


class Res147 : public Res
{
public:
int iSID;
char sType[4];
int iNoActive;

float v[147];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res105 : public Res
{
public:
int iSID;
char sType[4];
int iNoActive;

float v[105];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};


class Res24 : public Res
{
public:
float v[24];

virtual float* GetAddress(int ind)
{
return (&v[ind]);
}

};

class Res2 : public Res
{
public:
float v[2];
  virtual float* GetAddress(int ind)
  {
  return (&v[ind]);
  }
};

class Res1 : public Res
{
public:
float v[1];
  virtual float* GetAddress(int ind)
  {
  return (&v[ind]);
  }
};

class Res4 : public Res
{
public:
float v[4];
  virtual float* GetAddress(int ind)
  {
  return (&v[ind]);
  }
};

class Res3 : public Res
{
public:
float v[3];
  virtual float* GetAddress(int ind)
  {
  return (&v[ind]);
  }
};

class Res5 : public Res
{
public:
float v[5];
  virtual float* GetAddress(int ind)
  {
  return (&v[ind]);
  }
};

class Res6 : public Res
{
public:
float v[6];
  virtual float* GetAddress(int ind)
  {
  return (&v[ind]);
  }
};

class Res7 : public Res
{
public:
float v[7];
  virtual float* GetAddress(int ind)
  {
  return (&v[ind]);
  }
};





//const int MAX_RES=1000000;
const int MAX_RES_DEF = 5;

class ResSet
{
public:

int ACODE;
int TCODE;
int TYPE;
int LC;
int FCODE;			//format code
int SCODE;			//stress code
double dFreq;		//Freq
int WID;
int iCnt;
int iNoV;
float fMaxV;
float fMinV;
//For misc value
int i1;
double d1;
Res* Head;
Res* pCur;
CString lab[200];
CString sName;
CString sTitle;
CString sSubTitle;
CString sFile;
CString sOpName;
int iSecondaryID;
int iDefID;
//Define the type of results conatained in terms of 
//components ie vector / 2d stress tensor
ResDef* ResDefintion[10];
int iNoResDef = 0;

ResSet();
~ResSet();
void AddResDef(ResDef* rD);
ResDef* GetResDef(int iN);
void Add(Res* inRes);
Res* Get(int ID,int iOpt);
void PrintToFile(FILE* pFile);
CString ToStringDL(Res* pR);
CString ToStringHead();
int getMaxSecondaryID();
};




class pVal : public CObject
{
DECLARE_DYNAMIC( pVal )

public:
virtual void Serialize(CArchive& ar,int iV);

};

class piVal : public pVal
{
DECLARE_DYNAMIC( piVal )

public:
int iVal;
virtual void Serialize(CArchive& ar,int iV);

};

class pdVal : public pVal
{
DECLARE_DYNAMIC( pdVal )
public:
double dVal;
virtual void Serialize(CArchive& ar,int iV);

};


class psVal : public pVal
{
DECLARE_DYNAMIC( psVal )
public:
CString sVal;
virtual void Serialize(CArchive& ar,int iV);

};


class pRecord : public CObject
{
DECLARE_DYNAMIC( pRecord )
public:
int iID;
int iT;
int iCnt;
pVal* propVals[50];
pRecord(int iIndex,int iType);
~pRecord();
virtual void Serialize(CArchive& ar,int iV);
void Add(pVal* inP);
};

const int MaxRec = 100;
class Prop : public CObject
{
DECLARE_DYNAMIC( Prop )
public:
int iD;
int iT;
int iN;
int iP;
int iCnt;
CString Name;

pRecord* pRecs[MaxRec];
Prop();
Prop(int inD,int inT,
		int inN,int inP,CString inName);
~Prop();
virtual void Serialize(CArchive& ar,int iV);
void Add(pRecord* inRec);
};




class Entity : public CObject
{
DECLARE_DYNAMIC(Entity)
public:
CString sTitle;
int iID;
int iType;
Entity();
virtual void Serialize(CArchive& ar,int iV);
virtual void Create(CString inTitle,
                    int inPid,
                    int inType);
virtual void List();
virtual void ListShort();
virtual void ExportNAS(FILE* pFile);
virtual Entity* Copy();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};

class Property : public Entity
{
DECLARE_DYNAMIC(Property)
public:
  virtual int GetMat();
  virtual BOOL HasMat(int inMID);
  virtual double GetThk();
  virtual BSec* GetSec();
  virtual void UpdateMats(NEList* newMats);
  virtual void ChangeMat(int thisMat,int inMID);
  virtual int GetDefMatID();
};


class Material : public Entity
{
DECLARE_DYNAMIC(Material)
public:
virtual void Info();
virtual double GetDensity();
virtual double GetCTE();
virtual double GetE();
virtual double GetV();
};

class PSHELL : public Property
{
DECLARE_DYNAMIC(PSHELL)
public:
int iMID1;
double dT;
int iMID2;
double d12IT3;
int iMID3;
double dTST;
double dNSM;
double dZ1;
double dZ2;
int iMID4;
PSHELL();
virtual void Serialize(CArchive& ar,int iV);
virtual BOOL HasMat(int inMID);
virtual int GetMat();
virtual void ExportNAS(FILE* pFile);
virtual CString ToString();
virtual PSHELL* Copy();
virtual double GetThk();
virtual void List();
virtual void UpdateMats(NEList* newMats);
virtual void ChangeMat(int thisMat,int inMID);
virtual int GetDefMatID();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};

//this is the beam section graphics bit
const int MAX_SECPTS=20;
class  BSec : public CObject
{
DECLARE_DYNAMIC(BSec)
public:

C3dVector pLnLoop1[MAX_SECPTS];
C3dVector pLnLoop2[MAX_SECPTS];
C3dVector inPt;
int iLnCnt1;
int iLnCnt2;
BSec();
virtual ~BSec();
void Create();
void CreateBar(double W, double H);
void CreateDefSec(double W,int iC);
void CreateBox(double W,double H,double Wthk,double Hthk);
void CreateL(double W, double H, double Wthk, double Hthk, double yb, double zb);
void CreateRod(double R);
void CreateTube(double R,double r);
void CreateT2(double W, double H, double Wthk, double Hthk,double yb);
void CreateCHAN2(double d1, double d2, double d3, double d4, double yb);
void CreateI2(double d1,double d2,double d3,double d4,double d5,double d6, double yb);
void Clear();
void Serialize(CArchive& ar,int iV);
void OglDraw(int iDspFlgs,C3dMatrix TA,C3dMatrix TB,C3dVector d0,C3dVector d1,float C1,float C2,BOOL bD);
void OglDrawW(int iDspFlgs,C3dMatrix TMat,C3dVector d0,C3dVector d1);
void AddOutPt(double X1,double Y1);
void AddInPt(double X1,double Y1);
void MoveY(double yBar);
void MoveX(double zBar);

//BSec* Copy();

};

class PBAR : public Property
{
DECLARE_DYNAMIC(PBAR)
public:
int iMID;
BSec DspSec;
double dA;
double dI1;
double dI2;
double dJ;
double dNSM;
double dC1;
double dC2;
double dD1;
double dD2;
double dE1;
double dE2;
double dF1;
double dF2;
double dK1;
double dK2;
double dI12;
PBAR();

virtual void CreateSec();
virtual void Serialize(CArchive& ar,int iV);
virtual void ExportNAS(FILE* pFile);
virtual int GetMat();
virtual int GetDefMatID();
BOOL HasMat(int inMID);
virtual PBAR* Copy();
virtual BSec* GetSec();
virtual void UpdateMats(NEList* newMats);
virtual void ChangeMat(int thisMat,int inMID);
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};

class PBEAM : public Property
{
DECLARE_DYNAMIC(PBEAM)
public:
int iMID;
BSec DspSec;
int iNo;
double A[9];
double I1[9];
double I2[9];
double I12[9];
double J[9];
double NSM[9];
double C1[9];
double C2[9];
double D1[9];
double D2[9];
double E1[9];
double E2[9];
double F1[9];
double F2[9];
CString SO[9];
double XXB[9];

double K1;
double K2; 
double S1; 
double S2; 
double NSIA;
double NSIB;
double CWA;
double CWB;
double M1A;
double M2A;
double M1B;
double M2B;
double N1A;
double N2A;
double N1B;
double N2B;

PBEAM();
virtual void CreateSec();
virtual void Serialize(CArchive& ar,int iV);
virtual void ExportNAS(FILE* pFile);
virtual int GetMat();
BOOL HasMat(int inMID);
virtual PBEAM* Copy();
virtual BSec* GetSec();
virtual void UpdateMats(NEList* newMats);
virtual void ChangeMat(int thisMat,int inMID);
};

class PBARL : public Property
{
DECLARE_DYNAMIC(PBARL)
public:
int iMID;
double A;
double Izz;
double Iyy;
double J;
double ybar;
double zbar;
CString sSecType;
CString sGROUP;
double dDIMs[8];
int iNoDims;
BSec DspSec;
double dNSM;
PBARL();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
virtual void CreateSec();
virtual void List();
virtual void Serialize(CArchive& ar,int iV);
virtual void ExportNAS(FILE* pFile);
virtual int GetMat();
BOOL HasMat(int inMID);
int GetNoDims();
virtual PBARL* Copy();
virtual BSec* GetSec();
virtual void UpdateMats(NEList* newMats);
virtual void ChangeMat(int thisMat,int inMID);
virtual void CalcProps();
virtual int GetDefMatID();

};

class PROD : public Property
{
DECLARE_DYNAMIC(PROD)
public:
int iMID;
double A;
double J;
CString sSecType;
CString sGROUP;
BSec DspSec;

PROD();
virtual void List();
virtual int GetMat();
virtual void CreateSec();
virtual void Serialize(CArchive& ar,int iV);
BOOL HasMat(int inMID);
virtual PROD* Copy();
virtual BSec* GetSec();
virtual void UpdateMats(NEList* newMats);
virtual void ChangeMat(int thisMat,int inMID);
virtual void CalcProps();
virtual int GetDefMatID();
virtual void ExportNAS(FILE* pFile);
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};


class PSOLID : public Property
{
DECLARE_DYNAMIC(PSOLID)
public:
int iMID;
int iCORDM;
CString sIN;
CString sSTRESS;
CString sISOP;
CString sFCTN;
PSOLID();
virtual void List();
virtual void Serialize(CArchive& ar,int iV);
virtual int GetMat();
virtual BOOL HasMat(int inMID);
virtual void ExportNAS(FILE* pFile);
virtual PSOLID* Copy();
virtual void UpdateMats(NEList* newMats);
virtual void ChangeMat(int thisMat,int inMID);
virtual int GetDefMatID();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};

class PSPRINGT : public Property
{
DECLARE_DYNAMIC(PSPRINGT)
public:
double dkx;
double dky;
double dkz;
double dkcoeff;
PSPRINGT();
virtual void Serialize(CArchive& ar,int iV);
virtual PSPRINGT* Copy();
virtual void List();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
virtual void ExportNAS(FILE* pFile);
};

class PBUSH : public Property
{
	DECLARE_DYNAMIC(PBUSH)
public:
	CString sFlg = "K";
	double dK1;
	double dK2;
	double dK3;
	double dK4;
	double dK5;
	double dK6;
	PBUSH();
	virtual void Serialize(CArchive& ar, int iV);
	virtual PBUSH* Copy();
	virtual void List();
	virtual int GetVarHeaders(CString sVar[]);
	virtual int GetVarValues(CString sVar[]);
	virtual void PutVarValues(int iNo, CString sVar[]);
	virtual void ExportNAS(FILE* pFile);
};

class PMASS : public Property
{
  DECLARE_DYNAMIC(PMASS)
public:
  double dM;
  PMASS();
  virtual void Serialize(CArchive& ar, int iV);
  virtual PMASS* Copy();
  virtual void List();
  virtual int GetVarHeaders(CString sVar[]);
  virtual int GetVarValues(CString sVar[]);
  virtual void PutVarValues(int iNo, CString sVar[]);
};

class PSPRINGR : public PSPRINGT
{
DECLARE_DYNAMIC(PSPRINGR)
PSPRINGR();
virtual void List();
virtual int GetVarHeaders(CString sVar[]);
void ExportNAS(FILE* pFile);
};


class MAT1 : public Material
{
DECLARE_DYNAMIC(MAT1)
public:

double dE;
double dG;
double dNU;
double dRHO;
double dA;
double dk;
double dTREF;
double dGE;
double dST;
double dSC;
double dSS;
int iMCSID;
MAT1();
virtual void Info();
virtual void Serialize(CArchive& ar,int iV);
virtual void ExportNAS(FILE* pFile);
virtual MAT1* Copy();
virtual double GetDensity();
virtual double GetCTE();
virtual double GetE();
virtual double GetV();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};

class MAT8 : public Material
{
DECLARE_DYNAMIC(MAT8)
public:

double dE1;
double dE2;
double dNU12;
double dG12;
double dG1Z;
double dG2Z;
double dRHO;

double dA1;
double dA2;
double dTREF;
double dXt;
double dXc;
double dYt;
double dYc;

double dS;
double dGE;
double F12;
double STRN;
MAT8();
virtual void Serialize(CArchive& ar,int iV);
virtual void ExportNAS(FILE* pFile);
virtual CString ToString();
virtual MAT8* Copy();
virtual double GetDensity();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};

const int MAX_LAYERS = 500;
class PCOMP : public Property
{
DECLARE_DYNAMIC(PCOMP)
public:
double dZ0;
double dNSM;
double dSB;
int FT;
double dRefT;
double dGE;
BOOL bLAM;
int iNoLays;
int MID[MAX_LAYERS];
double T[MAX_LAYERS];
double Theta[MAX_LAYERS];
BOOL sOut[MAX_LAYERS];
PCOMP();
virtual void Serialize(CArchive& ar,int iV);
void AddLayer(int inMID,double inT,double inThe,BOOL inSo);
virtual void List();
virtual BOOL HasMat(int inMID);
virtual PCOMP* Copy();
virtual CString ToString();
virtual void ExportNAS(FILE* pFile);
virtual double GetThk();
virtual void UpdateMats(NEList* newMats);
virtual void ChangeMat(int thisMat,int inMID);
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(int iNo, CString sVar[]);
};

class PCOMPG : public Property
{
	DECLARE_DYNAMIC(PCOMPG)
public:
	double dZ0;
	double dNSM;
	double dSB;
	int FT;
	double dRefT;
	double dGE;
	BOOL bLAM;
	int iNoLays;
	int GPLYID[MAX_LAYERS];
	int MID[MAX_LAYERS];
	double T[MAX_LAYERS];
	double Theta[MAX_LAYERS];
	BOOL sOut[MAX_LAYERS];
	PCOMPG();
	virtual void Serialize(CArchive& ar, int iV);
	void AddLayer(int inPLYID,int inMID, double inT, double inThe, BOOL inSo);
	//virtual void List();
	//virtual BOOL HasMat(int inMID);
	//virtual PCOMP* Copy();
	//virtual CString ToString();
	//virtual void ExportNAS(FILE* pFile);
	//virtual double GetThk();
	//virtual void UpdateMats(NEList* newMats);
	//virtual void ChangeMat(int thisMat, int inMID);
	virtual int GetVarHeaders(CString sVar[]);
	virtual int GetVarValues(CString sVar[]);
	virtual void PutVarValues(int iNo, CString sVar[]);
};



//Display Filter
class Filter
{
public:
int Filt[100];
int iType[100];
CString sType[100];
int iNo;
int iNoOfType;
Filter();
void SetAll();
int isIn(int iThisType);
BOOL isFilter(int iThisType);
void SetFilter(int iThisType);
void RemFilter(int iThisType);
void Clear();
};

class CSETSDialog : public CDialog
{
public:
  enum {IDD = IDD_SETS};
  int* iNoS;
  int* iCurS;
  CString sTitle;
  CString sSET;
  CString sDEL;
  CString sLIST;
  CString sACT;
  CString SETS[1000];
  CSETSDialog();
  void AttachSets(int* iNo, int *iCur);
  void AddSet(int ind, CString sTit);
  void RemoveSet(int ind);
  void Refresh();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedCreate();
  virtual BOOL OnInitDialog();
  afx_msg void OnStnClickedSetlabel();
  afx_msg void OnBnClickedCdelset();
  afx_msg void OnBnClickedCsetcur();
  afx_msg void OnBnClickedCsetlist();
  afx_msg void OnEnChangeSetid();
  afx_msg void OnBnClickedNoneact();
};

class CSTEPSDialog : public CDialog
{
public:
  SolSets* pSOL;
  CString sTitle;
  int iNoLC;
  int iNoBC;
  int iNoTC;
  CString sLC[100];
  CString sBC[100];
  CString sTC[100];
  int iLC[100];
  int iBC[100];
  int iTC[100];
  enum {IDD = IDD_DIA_STEP};
  CSTEPSDialog();
  int GetLCInd(int ID);
  int GetBCInd(int ID);
  int GetTCInd(int ID);
  virtual BOOL OnInitDialog();
  void AddSet(int iID,CString sTXT,int iT);
  void Refresh();
  DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnLbnSelchangeStepLbx();
  afx_msg void OnBnClickedCreate();
  afx_msg void OnBnClickedActStep();
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedStepDel();
};

class CSOLDialog : public CDialog
{
public:
  SolSets* pSOL;
  CString sTitle;
  //int iNoLC;
  //int iNoBC;
  //int iNoTC;
  //CString sLC[100];
  //CString sBC[100];
  //CString sTC[100];
  //int iLC[100];
  //int iBC[100];
  //int iTC[100];
  enum {IDD = IDD_SOL};
  CSOLDialog();
  //int GetLCInd(int ID);
  //int GetBCInd(int ID);
  //int GetTCInd(int ID);
  virtual BOOL OnInitDialog();
  void Refresh();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedCr();
  afx_msg void OnBnClickedAct();
  afx_msg void OnBnClickedDel();
  afx_msg void OnBnClickedOk();
};

class CResSelDialog : public CDialog
{
public:
  enum {IDD = IDD_RES_SEL};
  ResSet* pRes[MAX_RESSETS];
  BOOL bIsVec;
  int iNoRes;
  int iCurResSet;
  int iResVal;
  int iSecResID;
  CResSelDialog();
  void SetData(BOOL isVec, ResSet* pInRes[],int iInNoRes,int iInCurResSet,int iInResVal,int inSecResID);
  void Init();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedOk();
  virtual BOOL OnInitDialog();
  afx_msg void OnLbnSelcancelListRes();
  afx_msg void OnLbnSelchangeListRes();
//  afx_msg void OnStnClickedLctext();
  afx_msg void OnSelchangeListVal();
};

class CFilterDialog : public CDialog
{
public:
	enum {IDD = IDD_DIALOG2};
  Filter* pFilt;
  CFilterDialog();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnLbnSelchangeList1();
  virtual BOOL OnInitDialog();
  afx_msg void OnLbnDblclkList1();
  void ReSet();
  afx_msg void OnLbnDblclkList2();
  afx_msg void OnBnClickedButton1();
  afx_msg void OnBnClickedClearFil();
  afx_msg void OnBnClickedButton2();
};

class Lamina
{
public:
	double dMAng;
	int iMID;
	double dThk;
	double dZOFFS;
	C3dVector pVertex[4];
	Lamina();
	~Lamina();
	void SetZ(double dZ);
	void SetAng(double dA);
	void SetThk(double dT);
	void SetMID(int ID);
	void OglDraw();
};


class cWndOGL : public CWnd
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

class CEntEditDialog : public CDialog
{
public:
	Lamina Laminate[200];
	
	int iNoLayers = 0;
	HDC hdc;
	HGLRC hrc;
	HDC hdcOld;
	HGLRC hrcOld;
	cWndOGL* pDrg = NULL;
	C3dMatrix vMat;
	int m_nPixelFormat = 0;
	void InitOGL();
	void AddVisLayer(double dA, double dZ, double dT, int iM);
	void OglDraw();
	void Build(); //build the visual layers from the PCOMP
	void Build2();//Build from table so paint can update when pcomp changes
  enum {IDD = IDD_ENTEDITOR};
  virtual void DoDataExchange(CDataExchange* pDX);
  CListCtrl m_List;
  CEdit Ed_Title;
  CEdit Ed_ID;
  CEdit* eEdit=NULL;
  int m_iItemBeingEdited;
  int iNo=0;
  int iNo2=0;
  BOOL bDel = FALSE;
  Entity* pEnt=NULL;
  G_Object* pO=NULL;
  PropTable* PT=NULL;
  CEntEditDialog();
  virtual ~CEntEditDialog();
  virtual BOOL OnInitDialog();
  void Populate1();
  void Populate2();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnEnChangeEditFloat();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedEntlist();
  afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedMfclink2();
  afx_msg void OnPaint();
  afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
//  afx_msg void OnLvnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnLvnItemchangingList1(NMHDR* pNMHDR, LRESULT* pResult);
//  afx_msg void OnNMReturnList1(NMHDR* pNMHDR, LRESULT* pResult);
//  afx_msg void OnNMReturnList1(NMHDR* pNMHDR, LRESULT* pResult);
//  afx_msg void OnLvnOdcachehintList1(NMHDR* pNMHDR, LRESULT* pResult);
//  afx_msg void OnLvnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnNMReturnList1(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnBnClickedCdelete();
  afx_msg void OnBnClickedCancel();
};






// CPcompEditor dialog

class CPcompEditor : public CDialog
{
public:
  CPcompEditor();   // standard constructor
  virtual ~CPcompEditor();
  Entity* pEnt;
  Lamina Laminate[200];
  
  int iNoLayers=0;
  HDC hdc;
  HGLRC hrc;
  HDC hdcOld;
  HGLRC hrcOld;
  CWnd* pDrg = NULL;
  C3dMatrix vMat;
  int m_nPixelFormat=0;
  void InitOGL();
  void OglDraw();
  void AddVisLayer(double dA, double dZ, double dT, int iM);
  void Build(); //build the visual layers from the PCOMP
  enum { IDD = IDD_PCOMPEDIT };
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedOk();
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedButton1();
//  afx_msg void OnPaint();
  afx_msg void OnPaint();
};

class CRelToDialog : public CDialog
{
public:
	enum {IDD = IDD_RELTO};
  Filter* pFilt;
  int iType;
	CRelToDialog();
  virtual BOOL OnInitDialog();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnLbnDblclkListRelto();
};

const int  MAX_COL=500;
class CColourPickDialog : public CDialog
{

public:
  int iSel;
  int iNoCols;
  int R[MAX_COL];
  int G[MAX_COL];
  int B[MAX_COL];
  CRect Rects[MAX_COL];
  enum {IDD = IDD_COLOURPICK};
  CColourPickDialog();
  void AddCol(int inR,int inG,int inB);
  DECLARE_MESSAGE_MAP()
  afx_msg void OnPaint();
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnBnClickedCancel();
};

const int MAX_GRAPHS = 100;
class CGraphDialog : public CDialog
{

public:
	CPen* Pen;
	CPen* oldPen;
	Graph* pGs[MAX_GRAPHS];
	int iNo = 0;
	int iActPlot = 0;
	float fW = 500;
	float fH = 500;
	float fxoff = 80;
	float fyoff = 50;
	float fxspan = fW - fxoff - 50;
	float fyspan = fH - fyoff - 50;
	float minX=0;
	float maxX=0;
	float minY=0;
	float maxY=0;
	vector <int> vTC;
	vector <int> vLC;
	vector <int> vE;
	enum { IDD = IDD_GRAPH };

	ME_Object* pME=NULL;
	CWnd* pDrg = NULL;
	C3dMatrix vMat;
	int m_nPixelFormat = 0;
	CGraphDialog();
	~CGraphDialog();
	int GetColourID();
	void SetPen(CDC* pDC,int iC,int iS);
	void RestorePen(CDC* pDC);
	void SetTextCol(HDC hdc, int iC);
	void ResetMaxMin();
	void DeleteAll();
	void InitOGL();
	void GDIDraw();
	float AxisTickMarks(float fMaxV, int &itargetSteps);
	void popResVec(); //populate available response data list box
	void popEnt(int iTC,int iLC); //populate available response nore / element
	virtual BOOL OnInitDialog();
	void GenGraph(CString sRT, CString sID, CString sVar, int iTC, int iLC, int iEnt, int iVar);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnLbnSelchangeRespvec();
	afx_msg void OnBnClickedPlot();
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClear();
	afx_msg void OnLbnSelchangePlots();
	afx_msg void OnBnClickedColour();
	afx_msg void OnBnClickedList();
	afx_msg void OnBnClickedRedraw();
	afx_msg void OnBnClickedLog();
};

class CGroupDialog : public CDialog
{
public:
  enum {IDD = IDD_GROUPS_LIST};
  int iGp;
  CGroupDialog();
  CString Groups[1000]; 
  int iNo;
  void AddGroup(CString sName);
  void RefreshGPS();
  void DeleteGP(int iThisGp);
  virtual BOOL OnInitDialog();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  afx_msg void OnBnClickedGroupaddgp();
  afx_msg void OnBnClickedGroupremgrp();
  afx_msg void OnBnClickedGroupdspcurrent();
  afx_msg void OnBnClickedGroupdspall();
  afx_msg void OnBnClickedGroupdels();
};

class BMP : public CObject
{
DECLARE_DYNAMIC(BMP)
// Data read from the header of the BMP file
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3                          
unsigned char * data;    // Actual RGB data
BMP();
virtual ~BMP();
};

//Base Class of graphics objects
class G_Object : public CObject
{
DECLARE_DYNAMIC( G_Object )

public:
  G_Object* pParent;
  G_Object* next;
  G_Object* before;
  C3dVector SelPt;
  int iObjType;
  int iType; //Secondary type specifier
  int iLabel;
  int iColour;
  int Drawn;    
  int Selectable; 
  int Visable; //Object Visability
  BOOL bDrawLab;
  void SetVisable(int iOnOff);
  void SetSelectable(int iOnOff);
  void SetDrawn(int iOnOff);
  int isVisable();
  int isDrawn();
  int isSelectable();
  int GetCol();
  G_Object();
  virtual ~G_Object();
  virtual void Create();
  virtual void Info();
  virtual CString ToString();
  virtual C3dVector MinPt(C3dVector inPt);
  virtual G_Object* Copy(G_Object* Parrent);
  virtual void Serialize(CArchive& ar,int iV);
  virtual void Draw(CDC* pDC,int iDrawmode);
  virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
  virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
  virtual void Transform(C3dMatrix TMat);
  virtual void Translate(C3dVector vIn);  
    //Curve specific
  virtual C3dVector GetPt(double w);
  virtual C3dVector GetDir(double w);
  virtual C3dVector GetInPt();
  virtual C3dVector Get_Centroid();
  virtual C3dVector Get_Normal();
  virtual double getLen();
  virtual G_Object* GetObj(int iType,int iLab);
  virtual void Move(C3dVector vM);
  virtual G_Object* OffSet(C3dVector vN,C3dVector vDir,double Dist);
  virtual void HighLight(CDC* pDC);
  virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
  virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
  virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
  virtual void RelTo(G_Object* pThis,ObjList* pList,int iType);
  virtual void Colour(int iCol);
  virtual double GetCharSize();
  virtual void GetBoundingBox(C3dVector& vll,C3dVector& vur);
  virtual CString GetName();
  virtual int GetVarHeaders(CString sVar[]);
  virtual int GetVarValues(CString sVar[]);
  virtual void PutVarValues(PropTable* PT,int iNo, CString sVar[]);
};

class cLinkedList : public G_Object
{
DECLARE_DYNAMIC(cLinkedList)
public:
  int iCnt;
  G_Object* Head;
  G_Object* pCur;
  CString sTitle;
  cLinkedList();
  ~cLinkedList();
  void Clear();
  void DeleteAll();
  void Add(G_Object* inItem);
  void AddEx(G_Object* inItem);
  G_Object* IsIn(G_Object* inItem);
  void RemNoDelete(G_Object* inItem);
  void Remove(G_Object* inItem);
  void Remove2(G_Object* inItem);
  G_Object* Get(int ID);
  G_Object* GetObj(int iType,int iLab);
  G_Object* GetByPtr(G_Object* pThis);
  void GenIDS(int& iS);
  virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
  virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
  virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
  virtual void Draw(CDC* pDC,int iDrawmode);
  virtual void HighLight(CDC* pDC);
  virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
  virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
  virtual void RelTo(G_Object* pThis,ObjList* pList,int iType);
  virtual void Info();
  virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
};

class cLinkedListB : public cLinkedList
{
DECLARE_DYNAMIC(cLinkedListB)
public:
cLinkedListB();
virtual void Info();
};

class cLinkedListT : public cLinkedList
{
DECLARE_DYNAMIC(cLinkedListT)
public:
cLinkedListT();
virtual void Info();
};

class G_ObjectD
{
public:
double Dist;
double Z;
G_Object* pObj;
};

const int MAX_GP_ITEMS = 1000000;

class ObjList
{
public:
G_Object* Objs[MAX_GP_ITEMS];
int iNo;
ObjList();
~ObjList();
void Add(G_Object* inItem);
BOOL IsIn(G_Object* inItem);
int IsIn2(G_Object* inItem);
void AddEx(G_Object* inItem);
void Remove(G_Object* inItem);
void RemoveGP(ObjList* inRemGp);
void MinDistSort(C3dVector vPt);
void MinSizeSort();
void Clear();
void DeleteAll();
void ListIDs();
void GenIDS(int& iS);
void ReOrder(int iStart);
G_Object* GetByLab(int iLab);
G_Object* GetMaxLabItem();
G_Object* GetMinLabItem();
};





class ObjTempList
{
public:

G_Object* Objs[99999999];
};



class ObjGp : public CObject
{
public:
CString Title;
G_Object* Objs[MAX_GP_ITEMS];
ObjGp();
ObjGp(CString inTit);
int iNo;
void Add(G_Object* inItem);
void Rem(G_Object* inItem);
int IsIn(G_Object* inItem);
void Clear();
};

const int MAX_LITEMS=2000000;

class NEList
{
public:
CString Title;
int ids[MAX_LITEMS];
int iType[MAX_LITEMS];
int iNo;
NEList();
int Get(int iD);
BOOL IsIn(int iD);
void Add(int iP,int iT);
};

class dList
{
public:
double d[1000];
int iNo;
dList();
void Init();
void Add(double indbl);
void AddEx(double indbl);
int IsIn(double indbl);
void Sort();
};

class IgesP
{
public:
CString P[1000000];
int iNo;
IgesP();
void Add(CString inSt);
CString getPLine(int pInd,int iNo);
};


class IgesD
{
public:
int itype;
int pData;
int pStruct;
int pLFont;
int pLevel;
int pView;
int pTForm;
int pLabAss;
int iStat;
int iSeq;
int iWght;
int iCol;
int iPLCnt;
int iFrmNo;
int iLab;
int iSubNo;
G_Object* pO;
};



class WP_Object : public G_Object
{
DECLARE_DYNAMIC( WP_Object )

public:
	C3dVector* Pt_Point[41];
	C3dVector* DSP_Point[41];
	C3dMatrix  mWPTransform;
	int iWPMode;  //0 cart 1 cyl 2 sph
    virtual void Create(double dWPSize);
	virtual void Draw(CDC* pDC,int iDrawmode);
	virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
	virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
	virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
	virtual void HighLight(CDC* pDC);
	virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);  
	virtual void Translate(C3dVector vIn);
    virtual void Transform(C3dMatrix TMat);
	virtual void Align(C3dVector p1,C3dVector p2,C3dVector p3);
    virtual void AlignZ(C3dVector p1,C3dVector p2,C3dVector p3);
    virtual void CentrePt(C3dVector p1);
	virtual void Reset();
    virtual void ReSize(double dWPSize);
	virtual C3dVector Get_Centroid();
};


//**********************************************************************
//Test class for the planet
//**********************************************************************
class Planet : public G_Object
{
  DECLARE_DYNAMIC(Planet)

public:
  Planet();
  virtual ~Planet();
  BMP* pTexture;
  void AttachTexture(BMP* pT);
  virtual void Draw(CDC* pDC, int iDrawmode);
  virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
  virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
};


class Pt_Object : public G_Object
{
DECLARE_DYNAMIC(Pt_Object)

public:
   Pt_Object();
   virtual ~Pt_Object();
   C3dVector* Pt_Point;
   C3dVector* DSP_Point;
   int DefSys;
   int OutSys;
   int dof[6];
   Res* pResV;
   Res* pResD;
   Ndata* pN;
   virtual void Create(C3dVector InPt, int iLab,int i2,int i3, int iC,int iDef,int iOut,G_Object* Parrent);
   virtual C3dVector MinPt(C3dVector inPt);
   virtual void Clear();
   virtual void Info();
   virtual CString ToString();
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   C3dVector GetCoords(); 
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void SetTo(C3dVector cInVect);
   virtual void Transform(C3dMatrix TMAt);
   virtual void Translate(C3dVector vIn);
   virtual void Move(C3dVector vM);
   virtual void Serialize(CArchive& ar,int iV);
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile,CoordSys* pD);
   virtual C3dVector Get_Centroid();
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT,int iNo, CString sVar[]);

};






class CvPt_Object : public G_Object
{
DECLARE_DYNAMIC( CvPt_Object )
public:
   double w;
   CvPt_Object();
   virtual ~CvPt_Object();
   C3dVector* Pt_Point;
   C3dVector* DSP_Point;
   virtual void Create(C3dVector InPt,double Inw, int iLab,int i2,int i3, int iC,G_Object* Parrent);
   virtual C3dVector MinPt(C3dVector inPt);
   virtual void Clear();
   void Info();
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   C3dVector GetCoords(); 
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC);
   //virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   virtual void SetTo(C3dVector cInVect);
   virtual void Transform(C3dMatrix TMAt);
   virtual void Translate(C3dVector vIn);
   void ScaleX(double d);
   virtual void Move(C3dVector vM);
   virtual void Serialize(CArchive& ar,int iV);
   virtual C3dVector Get_Centroid();
   virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
};

class CvPt_ObjectW : public CvPt_Object
{
DECLARE_DYNAMIC( CvPt_ObjectW )
public:
  virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
  virtual C3dVector Get_Centroid();
};


class Line_Object : public G_Object
{
DECLARE_DYNAMIC(Line_Object)
public:
  CvPt_Object* pVertex1;
  CvPt_Object* pVertex2;
  double dUsel;
  virtual ~Line_Object();
  virtual void Create(C3dVector* pInVertex1,C3dVector* pInVertex2, int iLab,G_Object* Parrent);
  virtual G_Object* Copy(G_Object* Parrent);
  virtual C3dVector MinPt(C3dVector inPt);
  virtual void Draw(CDC* pDC,int iDrawmode);
  virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
  virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
  virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
  virtual void HighLight(CDC* pDC);
  virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
  virtual double MinDist(C3dVector vInPt);
  virtual void Transform(C3dMatrix TMat);
  virtual C3dVector GetPt(double dU);
  virtual C3dVector GetDir(double dU);
  virtual void Serialize(CArchive& ar,int iV);
  virtual void Info();
  void SetP1(double dx,double dy,double dz);
  void SetP2(double dx,double dy,double dz);
  virtual double getLen();
  virtual C3dVector Get_Centroid();
	CvPt_Object* GetTEnd();
  
};




class ContrPolyW : public G_Object
{
DECLARE_DYNAMIC( ContrPolyW)
public:
   ContrPolyW();
   int iNoVerts;
   C4dVector* pCVertex[20];
   C3dMatrix* pModZ;
   C3dMatrix* pScrZ;
   virtual void Create(int iLab,G_Object* Parrent);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Serialize(CArchive& ar,int iV);
   virtual void AddVert(C3dVector* pInVertex1,double dWght);
   virtual void AddVertW(C4dVector pInVertex1);
   virtual void Draw(CDC* pDC,int iDrawmode,double sw,double ew);
   virtual void OglDraw(double sw,double ew);
   virtual void OglDrawW(double sw,double ew);
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC,double sw,double ew);
   virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   virtual void Translate (C3dVector vTVect);
   virtual void CWeight (double dW);
   void CPolyRot(double dAng);
   virtual void Clear ();
   int  GetOrder();
   C4dVector deCastelJau1(double u);
   void Set2(ContrPolyW* vS4);
   void Transform(C3dMatrix TMat);
   virtual C3dVector GetPt(double dU);
   virtual C3dVector GetDir(double dU);
   virtual C3dVector Get_Centroid();
};

class Curve : public ContrPolyW
{
DECLARE_DYNAMIC( Curve)
public:
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void HighLight(CDC* pDC);
};

//26/09/2016
//Link class simples way of storing lists of lines
//used for symbols
class Link
{
public:
Link* pNext;
CvPt_Object* p1;
CvPt_Object* p2;
Link();
Link(double x1, double y1, double z1,
	 double x2, double y2, double z2);
~Link();
};


class Text : public G_Object
{
DECLARE_DYNAMIC(Text)
public:
	CvPt_Object* inPt=NULL;         //Insertion Point
	C3dVector vNorm;				//Normal
	double dTextHeight;				//Text Height
	cLinkedList* pSyms;				//Sybols list forming text
	CString sText;
	Text();
	Text(int iLab, CString sT,double dH);
	~Text();
	virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
	virtual G_ObjectD SelDist(CPoint InPT, Filter FIL);
	virtual void S_Box(CPoint P1, CPoint P2, ObjList* pSel);
	virtual void SetToScr(C3dMatrix* pModMat, C3dMatrix* pScrTran);
	virtual void HighLight(CDC* pDC);
	virtual void Transform(C3dMatrix TMAt);
	virtual void Translate(C3dVector vIn);
	virtual void Move(C3dVector vM);
	virtual void Serialize(CArchive& ar, int iV);
	virtual C3dVector Get_Centroid();
	virtual G_Object* Copy(G_Object* Parrent);
	virtual CString GetName();
	virtual int GetVarHeaders(CString sVar[]);
	virtual int GetVarValues(CString sVar[]);
	virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);

};


//26/09/2016
//symbol class used for compounds of lines
// fonts, hatches etc
class Symbol : public G_Object
{
DECLARE_DYNAMIC(Symbol)
public:
   Link* pL = NULL;
   CvPt_Object* inPt;          //Insertion Point
   CvPt_Object* vCent;         //Centroid
   double w = 0;                   //symbol width
   double h = 0;                   //symbol height
   int iSegs = 0;
   Symbol();
   virtual ~Symbol();
   virtual void Create(int iLab,C3dVector inP,G_Object* Parrent);
   void addSeg(C3dVector pt1,C3dVector pt2);
   virtual C3dVector MinPt(C3dVector inPt);
   virtual void Info();
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   void CalculateMetrics();
   C3dVector GetCoords(); 
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC);
   virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);  //use defualt gObject which uses getCentroid
   //virtual void SetTo(C3dVector cInVect);
   virtual void Transform(C3dMatrix TMAt);
   virtual void Translate(C3dVector vIn);
   virtual void Move(C3dVector vM);
   virtual void Serialize(CArchive& ar,int iV);
   virtual C3dVector Get_Centroid();
   //virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
};

const int MAX_CVPTS = 1000;
const int MAX_CTPTS = 1000;
const int MAX_CVS = 200;
const int MAX_LOOPCVS = 200;
const int MAX_INT_LOOPS = 100;

class NCurve : public G_Object
{
DECLARE_DYNAMIC(NCurve)
public:
   //Object type 7
   //Curve Type 1
   //Nurbs curve to superceed ContolPoly
	//***************310320*****************************
	// Added for Auto Meshing
   double dLSize;       //Line Mesh Size 
   int iInc;            //Curve mesh increment size on edge  
   ~NCurve();
   NCurve();
   int iNoCPts;
   int iLnThk;
   int iLnType;
 
//****************************************************************************
// Added for BREP purposes
//*******************************************************************************
   CvPt_Object* pS;					//Start Vertex		
   CvPt_Object* pE;					//End Vertex
   C3dVector vS;					//Start Vertex		
   C3dVector vE;					//End Vertex
   CvPt_Object* cPts[MAX_CTPTS];	//Control point data

   double knots[MAX_CTPTS];			//knot vevtor
   int p;							//Degree
   double ws,we;					//Start and end w values
   C3dMatrix* pModZ;
   C3dMatrix* pScrZ;
   BOOL DrawCPts;
   BOOL DrawNoCvs;
   virtual void Create(int iLab,G_Object* Parrent);
   virtual void Clean();
   virtual void Info();
   virtual CString GetKnotString();
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Serialize(CArchive& ar,int iV);
   virtual void AddVert(C3dVector pInVertex1,double dWght);
   //virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawCtrlPts();
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC);
   virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   virtual void S_Box(CPoint P1, CPoint P2, ObjList* pSel);
   virtual void Translate (C3dVector vIn);
   void ScaleX(double d);
   virtual void CPolyRot(double dAng);
   virtual int  GetOrder();
   virtual void Transform(C3dMatrix TMat);
   virtual C3dVector GetPt(double dU);
   virtual C3dVector GetDir(double dU);
   virtual C3dVector Get_Centroid();
   virtual void Generate(int inp);
   virtual void GenerateExp(double Deg,Vec <C4dVector> & P,Vec<double> & U);
   virtual int FindSpan(double u);
   virtual int FindSpan2(double deg,const Vec <double> & U, double u);
   virtual void BasisFun(double deg,int i,double u,double N[10]);
   virtual void BasisFun2(double deg,int i,double u,const Vec <double> & U,double N[10]);
   virtual Mat* dersBasisFuns(int n,double u, int span); 
   virtual void DrawCtrlPtsTog();
   virtual void ScaleW(double dIn);
   virtual void deriveAt(double u,int d,C3dVector CK[10]);
   virtual void binomialCoef(Mat* Bin);
   virtual void GetContolPts(Vec <C4dVector> & Cpts);
   //Get all control points
   virtual void GetcPts(Vec <C3dVector> & Cpts);
   virtual void GetKnotVec(Vec<double>& U);
   virtual int knotInsertion(double u, int r, Vec <C4dVector> & ncP,Vec <double> & ncU);
   virtual void refineKnotVector(Vec<double>& XVec,Vec <C4dVector> & P,Vec <double> & U);
   virtual double chordLengthParam(const Vec<C3dVector> & Q, Vec<double> &ub);
   virtual void knotAveraging(const Vec<double>& uk, int deg, Vec<double>& U);
   virtual void globalInterp(int d,Vec <C4dVector> & nP,Vec<double> & nU);
   virtual C3dVector MinPt(C3dVector inPt);
   virtual double MinWPt(C3dVector inPt);
   // This check for the ambiguity of projecting 0 & 1 paremetric 
   // values to a closed surface
   virtual void EndPtChk01(NSurf* pSurf, double dS, C3dVector* pSfS, double dE, C3dVector* pSfE);
   //PLANAR CURVE CASE
   virtual NCurveOnSurf* GetSurfaceCV(NSurf* pSurf);
   //UNKNOWN
   virtual NCurveOnSurf* GetSurfaceCV2(NSurf* pSurf);
   //ISOCURVE VERSION
   virtual NCurveOnSurf* GetSurfaceCV3(NSurf* pSurf);
   //NON PLANAR SURF NOT ISOCURVE GENERAL CASE
   virtual NCurveOnSurf* GetSurfaceCV4(NSurf* pSurf);
   virtual int isIsoCurve(NSurf* pSurf);
   virtual void Reverse();
   virtual double getLen();
   virtual double CorrectW(double w);
   virtual void NullPointRef();
};

class NCurveOnSurf : public NCurve
{
DECLARE_DYNAMIC(NCurveOnSurf)
//Parrent must be set to a surface object 
public:
BOOL bOrient;
NCurve* pSC; //Pointer to the underlying space curve
NCurveOnSurf();
virtual void Create(int iLab,G_Object* Parrent);
void OglDrawCtrlPts();
virtual void OglDrawW(int iDspFlgs);
virtual void HighLight(CDC* pDC);
virtual void Translate (C3dVector vIn);
virtual void Transform(C3dMatrix TMat);
virtual void Serialize(CArchive& ar,int iV);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual C3dVector GetPt(double w);
virtual double getLen();
virtual C3dVector GetParaPt(double w);
virtual C3dVector MinPt(C3dVector inPt);
virtual void TrimOGL(GLUnurbsObj* pSurf);
virtual G_Object* Copy(G_Object* Parrent);
virtual void AddVert(C3dVector pInVertex1, double dWght);
virtual C3dVector Get_Centroid();
BOOL isCircle();
virtual NCurve* GetSurfaceCVG(G_Object* pSurf);
C3dVector GetLastPt();
};

class NSurf : public G_Object
{
DECLARE_DYNAMIC(NSurf)
public:
	// Added for Auto Meshing
	double dSSize;            //Surface Mesh Size     
   //Object type 7
   //Nurbs curve to superceed ContolPoly
   //Iges Knot Offsets of iges import Only
   double dUs;
   double dVs;
   double dUspan;
   double dVspan;
   ~NSurf();
   NSurf();
   int iNoCvs;
   NCurve* pCVsU[MAX_CVS];  
   NCurve* pCVsV[2]; 
   NCurveOnSurf* pSurfCvs[MAX_LOOPCVS];
   int iNoTrimCvs;
   int iNoExtCvs;
   NCurveOnSurf* pExtLoop[MAX_LOOPCVS];
   int iNoIntLoops;											//The number of internal loops
   int iNoIntCvs[MAX_INT_LOOPS];							//the number of curves in each loop
   NCurveOnSurf* pIntLoop[MAX_INT_LOOPS][MAX_LOOPCVS];		//Pointers to the curves in each loop
   //Get Bounding UV coordinates from externaml loop
   //or return (0,0)
   void GetBoundingUV(double& MinU,
                      double& MinV,
                      double& SpanU,
                      double& SpanV);


   int pU;          //Degree U
   int pV;          //Degree V     
   C3dMatrix* pModZ;
   C3dMatrix* pScrZ;
   BOOL DrawCPts;
   virtual void Create(int iLab,G_Object* Parrent);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Copy2(NSurf* pSurf);
   virtual void Info();
   virtual void Serialize(CArchive& ar,int iV);
   virtual void AddCV(NCurve* inCV);
   //virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void RelTo(G_Object* pThis, ObjList* pList, int iType);
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC);
   virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   void S_Box(CPoint P1, CPoint P2, ObjList* pSel);
   virtual G_ObjectD SelDistFace(CPoint InPT, Filter FIL);
   virtual void Translate (C3dVector vTVect);
   virtual void Transform(C3dMatrix TMat);
   virtual C3dVector GetPt(double dU,double dV);
   virtual C3dVector Get_Normal(double dU,double dV);
   virtual BOOL isPlanar();
   virtual BOOL isClosedinU();
   virtual BOOL isClosedinV();
   virtual C3dVector Get_Centroid();
   virtual BOOL Generate(int pInV,double dvs,double dve);
   virtual BOOL GenerateFit(int pInV,double dvs,double dve);
   virtual void DrawCtrlPtsTog();
   virtual Mat* Surfacederive(double u, double v, int d,Matrix <C4dVector> &der);
   virtual void deriveAt(double u, double v,int d,Matrix <C3dVector> &skl);
   virtual void binomialCoef(Mat* Bin);
   virtual NCurveOnSurf* AddTrimCurve(NCurve* pCurve);
   virtual void AddTrimCurveExp(NCurveOnSurf* pCurve);
   virtual void CleanExternalTrim();
   virtual C3dVector MinPt(C3dVector inPt);
   virtual C3dVector MinPtW(C3dVector inPt);
   virtual void DefualtTrim();
   virtual void DeleteExtTrimLoop();
   virtual void DeleteIntTrimLoop();
   virtual void TrimLoop(double us,double ue,double vs, double ve);
   virtual void UserTrim(ObjList* pCvs);
   virtual void InternalTrim(ObjList* pCvs);
   virtual void ReverseExtTrimLoop();
   virtual void ReverseIntTrimLoops();
   virtual BOOL ChkExtLoopDir();
   int GetTrimCvInd(G_Object* pCV);
   void RemoveTrimCv(int ind);
   virtual BOOL GenerateExp(C3dVector cPts[1000],
                          double wghts[1000],
                          double KnotsU[100],
                          double KnotsV[100],
                          int noU,
                          int noV,
                          int pInU,
                          int pInV);
   virtual void NSurf::NullCurveRef();
};

class NSurfR : public NSurf
{
DECLARE_DYNAMIC(NSurfR)
public:
C3dVector vNorm;
C3dVector vCent;
NSurfR();
virtual void Create(NCurve* pCIn,C3dVector vN,C3dVector vC,int iLab,G_Object* Parrent, double dS);
virtual void CreateRev(NCurve* pCIn,C3dVector vN,C3dVector vC,C3dVector vRef,
                       int iLab,G_Object* Parrent);

virtual BOOL Generate(int pInV,double dvs,double dve);
virtual void Serialize(CArchive& ar,int iV);
virtual G_Object* Copy(G_Object* Parrent);
};

class NSurfE : public NSurf
{
DECLARE_DYNAMIC(NSurfE)
public:
C3dVector vTran;
NSurfE();
virtual void Create(NCurve* pCIn1,NCurve* pCIn2,C3dVector vTr,int iLab,G_Object* Parrent);
virtual BOOL Generate(int pInV,double dvs,double dve);
virtual void Serialize(CArchive& ar,int iV);
virtual G_Object* Copy(G_Object* Parrent);
};

class NCircle : public NCurve
{
DECLARE_DYNAMIC(NCircle)
public:
   double dRadius;
   C3dVector vNorm;
   C3dVector vCent;
   NCircle();
   virtual void Create(C3dVector vN,C3dVector vC,double dRad,int iLab,G_Object* Parrent);
   virtual void Create2(C3dVector vN,C3dVector vC,C3dVector vR,double dRad,int iLab,G_Object* Parrent);
   virtual void Serialize(CArchive& ar,int iV);
   virtual void Info();
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* OffSet(C3dVector vN,C3dVector vDir,double Dist);
   virtual C3dVector Get_Centroid();
   virtual void Translate (C3dVector vIn);
   virtual void Transform(C3dMatrix TMat);
   virtual void Reverse();
   virtual double CorrectW(double w);
};


class NLine : public NCurve
{
DECLARE_DYNAMIC(NLine)
public:
   NLine();
   virtual void Create(C3dVector vP1,C3dVector vP2,int iLab,G_Object* Parrent);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void HighLight(CDC* pDC);
   virtual C3dVector MinPt(C3dVector inPt);
   virtual G_Object* OffSet(C3dVector vN,C3dVector vDir,double Dist);
   virtual double getLen();
   virtual double MinDist(C3dVector inPt);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Info();

};

class Surf_Ex1 : public G_Object
{
DECLARE_DYNAMIC(Surf_Ex1)
public:
	 
   ContrPolyW* pWCurve[4];
   C3dVector vTranVec;
   C3dMatrix* pScrZ;
   C3dMatrix* pModZ;
   virtual void Create(ContrPolyW* pWCurveIn, C3dVector vTranVecIn, int iLab,G_Object* Parrent);
   virtual void Draw(CClientDC* pDC,int iDrawmode);
	virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
	 virtual void HighLight(CClientDC* pDC);
	 virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
	 virtual C4dVector deCastelJau2(double u,double v);
	 virtual void OglDraw(int iDspFlgs);
	 virtual void OglDrawW();
};

class Surf_R : public G_Object
{
DECLARE_DYNAMIC(Surf_R)
public:
	 
  ContrPolyW* pWCurve[5];
  C3dVector vRotVec;
  C3dMatrix* pModZ;
  C3dMatrix* pScrZ;
  virtual void Create(ContrPolyW* pWCurveIn, C3dVector vRotVecIn, int iLab,G_Object* Parrent);
  virtual void Draw(CDC* pDC,int iDrawmode);
  virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
  virtual void HighLight(CDC* pDC);
  virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
  virtual C4dVector deCastelJau2(double u,double v);
  virtual void OglDraw(int iDspFlgs);
  virtual void OglDrawW(int iDspFlgs);
};


class Circ1 : public G_Object
{
DECLARE_DYNAMIC( Circ1)
public:
   ContrPolyW* pSegs[4]; //control polygon
   double dRadius;
   double dS;
   double dE;
   C3dVector* vNorm;
   C3dVector* vCent;
   C3dMatrix* pModZ;
   C3dMatrix* pScrZ;
   void Create(C3dVector vN,C3dVector vC,double dRad,int iLab,G_Object* Parrent);
   void Reverse();
   virtual void Info();
   virtual void Serialize(CArchive& ar,int iV);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs);
   virtual void OglDrawW(int iDspFlgs);
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC);
   virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   virtual double Bernstein(double dU,int ii,int inn);
   virtual void Transform(C3dMatrix TMat);
   virtual C3dVector GetPt(double dU);
   virtual C3dVector GetDir(double dU);
   virtual C3dVector MinPt(C3dVector inPt);
   virtual double MinWPt(C3dVector inPt);
   virtual C3dVector Get_Centroid();
};

//*****************************************************************************************
//Useages for of BREP information
//*****************************************************************************************
const int MAX_USES = 6;
class USE : public G_Object
{
	DECLARE_DYNAMIC(USE)
public:

	int iNo;
	G_Object* pObj;				//The object counting the uses
	G_Object* Use[MAX_USES];    //Pointer to the object use
	USE();
	BOOL IsIn(G_Object* pUse);
	void Add(G_Object* pUse);
	void AddEx(G_Object* pUse);
	void Remove(G_Object* pUse);
};

//*****************************************************************************************
//Face part of BREP inplementation
//*****************************************************************************************
class Face : public G_Object
{
	DECLARE_DYNAMIC(Face)
public:
	//Object type 18
	NSurf* pSurf; // Pointer to underlying trimmed surface
	BOOL bOrient; // Orientation relatine to pSurf TRUE -> agrees
	Face();
	Face(NSurf* pS,BOOL bO);
	~Face();
	virtual void Serialize(CArchive& ar, int iV);
	virtual void Info();
	virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
	virtual void SetToScr(C3dMatrix* pModMat, C3dMatrix* pScrTran);
	virtual void HighLight(CDC* pDC);
	virtual G_ObjectD SelDist(CPoint InPT, Filter FIL);
	virtual void S_Box(CPoint P1, CPoint P2, ObjList* pSel);
	virtual void Translate(C3dVector vTVect);
	virtual void Transform(C3dMatrix TMat);
	virtual C3dVector GetPt(double dU, double dV);
	virtual C3dVector Get_Normal(double dU, double dV);
	virtual C3dVector Get_Centroid();
	virtual void RelTo(G_Object* pThis, ObjList* pList, int iType);
};

//*****************************************************************************************
//Face part of BREP inplementation
//*****************************************************************************************
class Shell : public G_Object
{
	DECLARE_DYNAMIC(Shell)
	BOOL bOrient;			//Orientatopn of shell wet underlying surfaces TRUE=Agree
	BOOL isOuter;
	cLinkedList pFaces;		//Faces used in shell
	cLinkedList CurveUSES;  // Curves uses in shells
	cLinkedList PtUSES;		// Points uses in shells
	Shell();
	Shell(BOOL isOut);
	Shell(BOOL isOut, int iLab);
	~Shell();
	virtual void Serialize(CArchive& ar, int iV,Part* pP);
	virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
	virtual G_ObjectD SelDist(CPoint InPT, Filter FIL);
	virtual void HighLight(CDC* pDC);
	virtual void RelTo(G_Object* pThis, ObjList* pList, int iType);
	virtual void Info();
	void AddFace(Face *pF, BOOL bO, int iLab);
	virtual Face* GetFace(G_Object* pF);
	virtual void DeleteFace(G_Object* pF);
	//Remove Curve Face uses and Pt Curve Uses
	virtual void RemoveFaceUses(Face* pF);
	virtual void RemoveCurveUses(NCurve* pSC);
};

class Part : public G_Object
{
	DECLARE_DYNAMIC(Part)
	float Alpha=0.2f;
	C3dVector vBoxMin; //Minimum point of bounding box
	C3dVector vBoxMax; //Maximum point of bounding box
	CvPt_Object BBox[8];
	CString sName;
	int iShellLab;
	int iVertexLab;
	int iCurveLab;
	int iFaceLab;
	int iSurfLab;
	cLinkedList pShells;	//Pointer to all Shells forming part
	cLinkedList pPartV;		//Vertices used in Part
	cLinkedList pPartC;		//Space curves used in part
	cLinkedList pPartS;		//Space Surfaces used in part
	cLinkedList FaceUSES;	//Face USES in shells
	Part();
	~Part();
	Part(int iLab);
	virtual void Serialize(CArchive& ar, int iV);
	void AddShell(Shell* pShell);
	CvPt_Object* GetVert(C3dVector pPt, double dTol);
	void ReConectCvEndPts(double dTol);
	void AddSurf(Face* pF);
	void CurveColour(int iCol);
	void SurfColour(int iCol);
	virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
	virtual void GetBoundingBox(C3dVector& vll, C3dVector& vur);
	virtual void SetToScr(C3dMatrix* pModMat, C3dMatrix* pScrTran);
	virtual void HighLight(CDC* pDC);
	virtual G_ObjectD SelDist(CPoint InPT, Filter FIL);
	virtual int GetVarHeaders(CString sVar[]);
	virtual int GetVarValues(CString sVar[]);
	virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
	virtual void RelTo(G_Object* pThis, ObjList* pList, int iType);
	virtual void Info();
	virtual G_Object* GetObj(int iType, int iLab);
	virtual void Translate(C3dVector vIn);
	virtual void Transform(C3dMatrix TMat);
	virtual CString GetName();
	virtual void S_Box(CPoint P1, CPoint P2, ObjList* pSel);
	virtual void DeleteSurface(G_Object* pS);
	virtual void DeletePoint(G_Object* pS);
	virtual void DeleteCurve(G_Object* pS);
	virtual void DeleteFace(G_Object* pS);
	virtual void GetFaceRef(G_Object* pS, ObjList* pFaces);
	virtual int GetPointUseCnt(CvPt_Object* pPT);
	virtual int GetCurveUseCnt(NCurve* pSC);
	virtual void GetFace(G_Object* pF, ObjList* pFaces);
	virtual void RemoveCurveUses(NCurve* pSC);
};

//*****************************************************************************************


class cFace : public G_Object
{
public:
int NoVert;
Pt_Object* pVertex[4];
cFace();
~cFace();
BOOL isSame(cFace* inFace);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
};

class cLink : public G_Object
{
public:
Pt_Object* pVertex[2];
cLink();
~cLink();
BOOL isSame(cLink* inLink);
int isSameWithDir(cLink* inLink);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
};

class c2dParPt : public G_Object

{// 2d Vector 
public:
	C2dVector PP;
	c2dParPt();
	~c2dParPt();
	c2dParPt(double x, double y);

};

class cSeg : public G_Object
{
public:
	c2dParPt* pt[2];
	C2dVector MpT;
	double dL;
	cSeg();
	cSeg(G_Object* pP);
	cSeg(G_Object* pP,double x1,double y1,double x2, double y2);
	~cSeg();
	void CalcMids();
	BOOL HasCommonVert(c2dParPt* p1, c2dParPt* p2);
	//int isSameWithDir(cLink* inLink);
	C2dVector Get_Mid();
    virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
};

class c2dFront : public G_Object
{
public:
	C3dVector vN;
	double dA;
	int iPID;
	cLinkedList* fNodes;
	c2dFront();
	~c2dFront();
	Pt_Object* isSegBet(int pL, int pH);
	Pt_Object* GetNodeByGID(int iGID);
	virtual void SetToScr(C3dMatrix* pModMat, C3dMatrix* pScrTran);
	virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
};

class cLinkList : public G_Object
{
public:
int iNo;
cLink* Head;
cLink* pCur;
cLinkList();
~cLinkList();
cLink* IsIn(cLink* inLink);
void Add(cLink* inLink);
void AddIncOnly(cLink* inLink);
void AddGp(int iN, cLink* inLink[]);
void Remove(cLink* inLink);
void Purge();
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
};

class cFaceList : public G_Object
{
public:
int iNo;
cFace* Head;
cFace* pCur;
cFaceList();
~cFaceList();
cFace* IsIn(cFace* inFace);
void Add(cFace* inFace);
void Remove(cFace* inFace);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
};

class ParPt
{
  public:
  double u;
  double v;
  ParPt(double dU,double dV);
};




class BCLD : public G_Object
{
DECLARE_DYNAMIC(BCLD)
public:
G_Object* pObj;
int SetID;
virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
virtual BOOL NodeIn(Pt_Object* pN);
virtual void ExportNAS(FILE* pFile);
virtual void RelTo(G_Object* pThis,ObjList* pList,int iType);
};

class CoordSys : public G_Object
{
DECLARE_DYNAMIC(CoordSys)
public:
C3dVector Origin;
C3dVector DSP_Point;
C3dMatrix mOrientMat;
C3dMatrix DispMat;
BOOL bG = FALSE; //flag to indicated the cys has beee set to global
int CysType; // 1 rec,2 cyl,3sph
int RID;
double dScl;
virtual void Create(C3dVector Orig,C3dMatrix RMat,int inRID,int inTp, int iLab, int iC,G_Object* Parrent);
//virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void Serialize(CArchive& ar,int iV);
virtual C3dVector Get_Centroid();
virtual void Translate (C3dVector vIn);
virtual G_Object* Copy(G_Object* Parrent);
virtual void Info ();
virtual CString ToString ();
virtual void ExportNAS(FILE* pFile);
C3dMatrix GetTMat();
virtual CString GetName();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};

class E_Object : public G_Object
{
DECLARE_DYNAMIC(E_Object)
public:
  //int iType;
  int iMatID;
  int PID;
  int PIDunv;   
  int iNoNodes;
     double dTemp;    //Used as a temporary variable (thermal alpha delta T etc)
     Res* pResV;
     Property* pPr;
     E_Object();
     virtual void Create(int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr);
     virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
     virtual G_Object* Copy(G_Object* Parrent);
     virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
     virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
	 virtual void ExportUNV(FILE* pFile);
     virtual void ExportNAS(FILE* pFile);
     virtual Mat Sample(int iNo);
	 virtual Mat ShapeDer(Mat Points, int i);
	 virtual Mat ShapeFun(Mat Points, int i);
	 virtual Mat getCoords2d();
	 virtual Mat getCoords3d();
	 virtual Mat bmat(Mat& coord,
                      Mat& deriv,
				      int iD,
				      int iDof);
	 virtual Mat bmat2d(Mat& coord,
                        Mat& deriv);
   virtual Mat GetElNodalMass(PropTable* PropsT,MatTable* MatT);
   virtual Mat GetThermalStrainMat3d(PropTable* PropsT,MatTable* MatT,double dT);
   virtual Mat GetStiffMat(PropTable* PropsT,MatTable* MatT);
   virtual Mat GetThermMat(PropTable* PropsT,MatTable* MatT);
   virtual int MaxBW();
   virtual Vec<int>GetSteerVec3d();
   virtual Vec<int>GetSteerVec1d();
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
   virtual Mat KayMat(double K, int iD);
   virtual Mat DeeMat(double E, double v,int iD);
   virtual int noDof();
   virtual BOOL ChkNegJac();
   virtual int GetfaceList(cFace* Faces[6]);
   virtual int GetLinkList(cLink* Links[200]);
   virtual void Info();
   virtual G_Object* GetNode(int i);
   virtual C3dVector GetNodalCoords(int i);
   virtual BOOL SetProperty(Property* Pr);
   virtual void Transform(C3dMatrix TMat);
   int GetDOFInt(CString sDOF);
   CString GetDOFString(int iDOF);
   virtual void Reverse();
   virtual C3dMatrix GetElSys();
   virtual C3dVector GetFirstEdge();
   virtual double QualAspect();
   virtual double GetCentriodVal(int iDof, Vec<int> &Steer, Vec<double> &Disp);
};





class E_Object38 : public E_Object
{
DECLARE_DYNAMIC( E_Object38 )
public:
   ~E_Object38();
   Pt_Object* pVertex[8];
   virtual void Info();
   virtual void Create(Pt_Object* pInVertex[100], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
   virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual C3dVector Get_Centroid();
   virtual C3dMatrix GetElSys();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
   virtual Mat getCoords3d();
   virtual Mat Sample(int iNo);
   virtual Mat ShapeDer(Mat Points, int i);
   virtual Mat ShapeFun(Mat Points, int i);
   virtual Vec<int>GetSteerVec3d();
   virtual Vec<int>GetSteerVec1d();
   virtual int MaxBW();
   virtual int noDof();
   virtual int GetfaceList(cFace* Faces[6]);
   virtual int GetLinkList(cLink* Links[200]);
   virtual G_Object* GetNode(int i);
   virtual void Reverse();
   virtual double GetCentriodVal(int iDof, Vec<int> &Steer, Vec<double> &Disp);
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};


class E_Object36 : public E_Object
{
DECLARE_DYNAMIC( E_Object36 )
public:
   ~E_Object36();
   Pt_Object* pVertex[6];
   virtual void Create(Pt_Object* pInVertex[100], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
   virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual C3dVector Get_Centroid();
   virtual C3dMatrix GetElSys();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
   virtual int noDof();
   virtual Mat ShapeFun(Mat Points, int i);
   virtual Mat ShapeDer(Mat Points, int i);
   virtual Mat Sample(int iNo);
   virtual Mat getCoords3d();
   virtual  int MaxBW();
   virtual Vec<int> GetSteerVec3d();
   virtual Vec<int> GetSteerVec1d();
   virtual int GetfaceList(cFace* Faces[6]);
   virtual int GetLinkList(cLink* Links[200]);
   virtual G_Object* GetNode(int i);
   virtual void Reverse();
   virtual double GetCentriodVal(int iDof, Vec<int> &Steer, Vec<double> &Disp);
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};



class E_Object2 : public E_Object
{
DECLARE_DYNAMIC(E_Object2)
public:
  E_Object2();
  ~E_Object2();
  Pt_Object* pVertex[2];
  C3dVector vUp;
  int iCSYS;
  int iONID;
  int A;
  int B;
  int C;
  virtual void Create(Pt_Object* pInVertex[200], int iLab, int iCol, int iType, int iPID, int iMat, int iNo, G_Object* Parrent, Property* inPr);
  virtual G_Object* Copy(G_Object* Parrent);
  virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
  virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
  virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
  virtual void Draw(CDC* pDC,int iDrawmode);
  virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
  virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
  virtual C3dVector Get_Centroid();
  void SetUpVec(C3dVector vIn);
  void SetSec(int iA,int iB,int iC);
  virtual void ExportUNV(FILE* pFile);
  virtual CString ToString();
  virtual void ExportNAS(FILE* pFile);
  virtual void ExportUPVecs(FILE* pFile);
  virtual BOOL NodeInEl(Pt_Object* pN);
  virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
  virtual int GetLinkList(cLink* Links[200]);
  virtual G_Object* GetNode(int i);
  virtual C3dMatrix GetElSys();
  virtual int noDof();
  virtual void Info();
  virtual Mat GetThermMat(PropTable* PropsT,MatTable* MatT);
  virtual Mat GetStiffMat(PropTable* PropsT,MatTable* MatT);
  virtual Vec<int> GetSteerVec3d();
  virtual Vec<int> GetSteerVec1d();
  C3dMatrix GetSpringSys(CoordSys* pC);
  Mat GetSpringTMat(CoordSys* pCSYS);
  double GetCentriodVal(int iDof, Vec<int> &Steer, Vec<double> &Disp);
  virtual CString GetName();
  virtual int GetVarHeaders(CString sVar[]);
  virtual int GetVarValues(CString sVar[]);
  virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};

class E_Object2R : public E_Object2
{
DECLARE_DYNAMIC(E_Object2R)
public:
  ~E_Object2R();
  E_Object2R();

  C3dVector OffA;
  C3dVector OffB;
  int iONID;
  int iDOFA;
  int iDOFB;

  virtual void SetDOFStringA(CString sDOF);
  virtual void SetDOFStringB(CString sDOF);
  virtual void Create(Pt_Object* pInVertex[100], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr);
  virtual G_Object* Copy(G_Object* Parrent);
  virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
  virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
  virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
  virtual void Draw(CDC* pDC,int iDrawmode);
  virtual void Info();
  virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
  virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
  virtual C3dVector Get_Centroid();
  void SetUpVec(C3dVector vIn);
  C3dVector GetDir();
  void SetSec(int iA,int iB,int iC);
  virtual void ExportUNV(FILE* pFile);
  virtual void ExportNAS(FILE* pFile);
  CString ToString();
  virtual void ExportUPVecs(FILE* pFile);
  virtual BOOL NodeInEl(Pt_Object* pN);
  virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
  virtual int GetLinkList(cLink* Links[200]);
  virtual G_Object* GetNode(int i);
  C3dMatrix GetBeamTform();
  C3dMatrix GetBeamTformA();
  C3dMatrix GetBeamTformB();
  virtual void Transform(C3dMatrix TMat);
  virtual int noDof();
  virtual int MaxBW();
  virtual Mat GetThermMat(PropTable* PropsT,MatTable* MatT);
  virtual Mat GetStiffMat(PropTable* PropsT,MatTable* MatT);
  virtual Mat GetElNodalMass(PropTable* PropsT,MatTable* MatT);
  Mat GetThermalStrainMat3d(PropTable* PropsT,MatTable* MatT,double dT);
  virtual Vec<int> GetSteerVec3d();
  virtual Vec<int> GetSteerVec1d();
  virtual C3dMatrix GetElSys();
  virtual CString GetName();
};

class E_Object2B : public E_Object2R
{
DECLARE_DYNAMIC(E_Object2B)
public:
E_Object2B();
virtual CString ToString();
virtual void ExportNAS(FILE* pFile);
virtual int noDof();
virtual Mat GetThermMat(PropTable* PropsT,MatTable* MatT);
virtual Mat GetStiffMat(PropTable* PropsT,MatTable* MatT);
virtual Vec<int> GetSteerVec3d();
virtual Vec<int> GetSteerVec1d();
virtual G_Object* Copy(G_Object* Parrent);
virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
CString GetName();
};


class E_Object1 : public E_Object
{
DECLARE_DYNAMIC( E_Object1 )
public:
   int iCID=0;
   CString sLab = "";
   double dM = 0;
   double dX1 = 0;
   double dX2 = 0;
   double dX3 = 0;
   double dI11 = 0;
   double dI21 = 0;
   double dI22 = 0;
   double dI31 = 0;
   double dI32 = 0;
   double dI33 = 0;
   E_Object1();
   ~E_Object1();
   Pt_Object* pVertex;
   virtual void Create(Pt_Object* pInVertex[200], int iLab, int iCol, int iType, int iPID, int iMat, int iNo, G_Object* Parrent, Property* inPr);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
   virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual C3dVector Get_Centroid();
   virtual void ExportUNV(FILE* pFile);
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual G_Object* GetNode(int i);
   virtual CString ToString();
   virtual void ExportNAS(FILE* pFile);
   virtual void Transform(C3dMatrix TMat);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
   virtual Mat GetElNodalMass(PropTable* PropsT, MatTable* MatT);
   virtual Vec<int> GetSteerVec3d();
   virtual Mat GetStiffMat(PropTable* PropsT, MatTable* MatT);
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
   virtual void Info();
};

class E_Object3 : public E_Object
{
DECLARE_DYNAMIC( E_Object3 )
public:
	int iNoRemesh;	  //Added tempoary for tet mesh generation debugging 
   int iMCys;
   double MAng;
   double dZOFFS;
   E_Object3();
   ~E_Object3();
   Pt_Object* pVertex[3];
   virtual void Create(Pt_Object* pInVertex[200], int iLab, int iCol, int iType, int iPID, int iMat, int iNo, int inMCys, double inMAng, G_Object* Parrent, Property* inPr);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
   virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);  
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual int GetfaceList(cFace* Faces[6]);
   virtual C3dVector Get_Centroid();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   Mat Sample(int iNo);
   void GetKMat();
   Mat ShapeDer(Mat Points, int i);
   Mat ShapeFun(Mat Points, int i);
   Mat DetCoords2d();         //used for 2d MPM example
   Mat GetParticlePos();      //used for 2d MPM example
   Mat getCoords2d();
   Mat getCoords3d();
   //Mat getCoords3d();
   virtual Vec<int> GetSteerVec3d();
   virtual Vec<int> GetSteerVec1d();
   int MaxBW();
   virtual Mat GetStiffMat(PropTable* PropsT,MatTable* MatT);
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
   virtual int noDof();
   virtual int GetLinkList(cLink* Links[200]);
   virtual G_Object* GetNode(int i);
   virtual C3dVector Get_Normal();
   virtual void Info();
   virtual CString ToString();
   virtual void Reverse();
   virtual C3dMatrix GetElSys();
   virtual C3dVector GetTestPt();
   virtual C3dVector GetFirstEdge();
   virtual double GetCharSize();
   virtual void GetBoundingBox(C3dVector& vll,C3dVector& vur);
   virtual double QualAspect();
   virtual double GetCentriodVal(int iDof, Vec<int> &Steer, Vec<double> &Disp);
   //These were comented out not sure why
   //so we carefull
   void TranslateAVF(C3dVector vIn);
   void TransformAVF(C3dMatrix TMat);
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT,int iNo, CString sVar[]);
   double GetArea2d();
   virtual Mat GetElNodalMass(PropTable* PropsT, MatTable* MatT);
};

class E_CellS : public E_Object
{
DECLARE_DYNAMIC(E_CellS)
public:
Pt_Object* pVertex[5];
~E_CellS();
virtual void Create(Pt_Object* pInVertex[100], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr);
virtual G_Object* Copy(G_Object* Parrent);
virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual C3dVector Get_Centroid();
virtual G_Object* GetNode(int i);
virtual BOOL NodeInEl(Pt_Object* pN);
virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
};

class E_Object4 : public E_Object
{
DECLARE_DYNAMIC(E_Object4)
public:
	int iMCys;
	double MAng;
	double dZOFFS;
	Pt_Object* pVertex[4];
	~E_Object4();
	virtual void Create(Pt_Object* pInVertex[200], int iLab, int iCol, int iType, int iPID, int iMat, int iNo, int inMCys, double inMAng, G_Object* Parrent, Property* inPr);	 
	virtual G_Object* Copy(G_Object* Parrent);
	virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
	virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
	virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
	virtual void Draw(CDC* pDC,int iDrawmode);
	virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
	virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
	 //virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
	 //virtual void HighLight(CDC* pDC);
	 //virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
	virtual C3dVector Get_Centroid();
	virtual void ExportUNV(FILE* pFile);
	virtual void ExportNAS(FILE* pFile);
	virtual Mat Sample(int iNo);
	virtual Mat ShapeDer(Mat Points, int i);
	virtual Mat ShapeFun(Mat Points, int i);
	virtual Mat getCoords2d();
	virtual Mat getCoords3d();
	virtual Mat bmatAxi(double& radius,
                         Mat& coord,
                         Mat& deriv,
                         Mat& fun);
	virtual int MaxBW();
	virtual Mat E_Object4::GetStiffMat(PropTable* PropsT,MatTable* MatT);
	virtual Mat E_Object4::GetStiffMat_Ex(PropTable* PropsT, MatTable* MatT);
	Mat E_Object4::GetB_1pt(double &det);
	virtual Vec<int>GetSteerVec3d();
	virtual Vec<int> GetSteerVec3d_E();
	virtual Vec<int>GetSteerVec1d();
	virtual BOOL NodeInEl(Pt_Object* pN);
	virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
	virtual int noDof();
	virtual int GetfaceList(cFace* Faces[6]);
	virtual int GetLinkList(cLink* Links[200]);
	virtual G_Object* GetNode(int i);
	virtual C3dVector Get_Normal();
	virtual void Info();
	virtual CString ToString();
	virtual void Reverse();
	virtual C3dMatrix GetElSys();
	virtual C3dMatrix GetElSys_Ex(Vec<int> &Steer, Vec<double> &Disp);
	virtual C3dVector GetTestPt();
	virtual C3dVector GetFirstEdge();
	virtual double QualAspect();
	virtual double GetCentriodVal(int iDof, Vec<int> &Steer, Vec<double> &Disp);
	virtual CString GetName();
	virtual int GetVarHeaders(CString sVar[]);
	virtual int GetVarValues(CString sVar[]);
	virtual void PutVarValues(PropTable* PT,int iNo, CString sVar[]);
	double GetArea2d();
	virtual Mat GetElNodalMass(PropTable* PropsT, MatTable* MatT);
};


class E_Object34 : public E_Object
{
DECLARE_DYNAMIC( E_Object34 )
public:
   ~E_Object34();
   Pt_Object* pVertex[4];
   virtual void Create(Pt_Object* pInVertex[100], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
   virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);   
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Info();
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   //virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   //virtual void HighLight(CDC* pDC);
   //virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   virtual C3dVector Get_Centroid();
   virtual C3dMatrix GetElSys();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
   virtual Mat getCoords3d();
   virtual Mat Sample(int iNo);
   virtual Mat ShapeDer(Mat Points, int i);
   virtual Mat ShapeFun(Mat Points, int i);
   virtual Vec<int> GetSteerVec3d();
   virtual Vec<int>GetSteerVec1d();
   virtual int MaxBW();
   virtual int noDof();
   virtual int GetfaceList(cFace* Faces[6]);
   virtual int GetLinkList(cLink* Links[200]);
   virtual G_Object* GetNode(int i);
   virtual C3dVector GetNodalCoords(int i);
   virtual void Reverse();
   virtual double GetCharSize();
   double GetTETHeight(C3dVector vFCent);
   virtual void GetBoundingBox(C3dVector& vll,C3dVector& vur);
   double height(int n1, int n2, int n3, int p);
   double area(int n1, int n2, int n3);
   double longEdge();
   double TetCollapse();
   double GetCentriodVal(int iDof, Vec<int> &Steer, Vec<double> &Disp);
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};


class E_Object310 : public E_Object
{
	DECLARE_DYNAMIC(E_Object310)
public:
	~E_Object310();
	Pt_Object* pVertex[10];
	virtual void Create(Pt_Object* pInVertex[100], int iLab, int iCol, int iType, int iPID, int iMat, int iNo, G_Object* Parrent, Property* inPr);
	virtual G_Object* Copy(G_Object* Parrent);
	virtual G_Object* Copy2(G_Object* Parrent, Pt_Object* pInVertex[200], int inPID, int inMID, int inPIDunv);
	virtual G_Object* CopyAppend(int iSInd, ME_Object* Target, ME_Object* Source);
	virtual void Serialize(CArchive& ar, int iV, ME_Object* MESH);
	virtual void Info();
	virtual void Draw(CDC* pDC, int iDrawmode);
	virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
	//virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
	//virtual void HighLight(CDC* pDC);
	//virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
	virtual C3dVector Get_Centroid();
	virtual C3dMatrix GetElSys();
	virtual void ExportUNV(FILE* pFile);
	virtual void ExportNAS(FILE* pFile);

	virtual BOOL NodeInEl(Pt_Object* pN);
	virtual void RepNodeInEl(Pt_Object* pThis, Pt_Object* pWith);
	virtual Mat getCoords3d();
	virtual Mat Sample(int iNo);
	virtual Mat ShapeDer(Mat Points, int i);
	virtual Mat ShapeFun(Mat Points, int i);
	virtual Vec<int> GetSteerVec3d();
	virtual Vec<int>GetSteerVec1d();
	virtual int MaxBW();
	virtual int noDof();
	virtual int GetfaceList(cFace* Faces[6]);
	virtual int GetLinkList(cLink* Links[200]);
	virtual G_Object* GetNode(int i);
	virtual C3dVector GetNodalCoords(int i);
	virtual void Reverse();
	virtual double GetCharSize();
	double GetTETHeight(C3dVector vFCent);
	virtual void GetBoundingBox(C3dVector& vll, C3dVector& vur);
	double height(int n1, int n2, int n3, int p);
	double area(int n1, int n2, int n3);
	double longEdge();
	double TetCollapse();
	double GetCentriodVal(int iDof, Vec<int>& Steer, Vec<double>& Disp);
	virtual CString GetName();
	virtual int GetVarHeaders(CString sVar[]);
	virtual int GetVarValues(CString sVar[]);
	virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};

class E_ObjectR : public E_Object
{
DECLARE_DYNAMIC( E_ObjectR)
public:
   Pt_Object* pVertex[200];

   int iDOF;
   double dALPHA;
   E_ObjectR();
   virtual void Create(Pt_Object* pInVertex[200], int iLab, int iCol, int iType, int iPID, int iMat, int iNo, G_Object* Parrent, Property* inPr);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
   virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual C3dVector Get_Centroid();
   virtual void ExportUNV(FILE* pFile);
   virtual CString ToString();
   virtual void ExportNAS(FILE* pFile);
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
   int GetLinkList(cLink* Links[200]);
   virtual G_Object* GetNode(int i);
   virtual void SetDOFString(CString sDOF);
   virtual void Info();
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};


class E_ObjectR2 : public E_ObjectR
{
DECLARE_DYNAMIC(E_ObjectR2)
public:
   Pt_Object* pVertex[2];
  double dALPHA;
  int iCNA;
  int iCNB;
  int iCMA;
  int iCMB;
   E_ObjectR2();
   virtual void Create(Pt_Object* pInVertex[100], int iLab,int iCol,int iType,int iPID,int iMat,int iNo,G_Object* Parrent,Property* inPr);
   virtual G_Object* Copy(G_Object* Parrent);
   virtual G_Object* Copy2(G_Object* Parrent,Pt_Object* pInVertex[200],int inPID,int inMID,int inPIDunv);
   virtual G_Object* CopyAppend(int iSInd,ME_Object* Target,ME_Object* Source);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual void SetOther(CString s1,
                           CString s2,
                           CString s3,
                           CString s4,
                           double dAlp);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual C3dVector Get_Centroid();
   virtual BOOL NodeInEl(Pt_Object* pN);
   virtual void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
};

const int MAX_MATS=1000000;
const int MAX_ENTS=5000000;
const int MAX_FESIZE=5000000;


class Table : public CObject
{
DECLARE_DYNAMIC(Table)
public:
Table();
~Table();
Entity* pEnts[MAX_ENTS];
int iNo;
virtual void DeleteAll();
void Delete(Entity* pO);
virtual void AddItem(Entity* pIn);
virtual Entity* GetItem(int iID);
virtual int NextID();
virtual void ListAll();
virtual void Serialize(CArchive& ar,int iV);
virtual void ExportNAS(FILE* pF);
virtual BOOL Exists(int iPID);
};

class PropTable : public Table
{
DECLARE_DYNAMIC(PropTable)

virtual Property* GetItem(int iID);
virtual void Serialize(CArchive& ar,int iV);
void UpdateMats(NEList* newMats);
PSHELL* GetShell(double dTHK,double dNSM,int iM);
PBARL* GetPBARL(CString sT,double W,double H, double dTHK,double dNSM,int iM);

};

class MatTable : public Table
{
DECLARE_DYNAMIC(MatTable)

virtual Material* GetItem(int iID);
virtual void Serialize(CArchive& ar,int iV);
};

void DrawColBar(int iDspFlgs,double dW,double dH);
void CreateTexture(BOOL bRev);
//The max number of load BC and TSets
const int MAX_SETS=1000;

//****************************************************************************
//           S O L U T I O N    S E T    O B J E C T S
//****************************************************************************
const int MAX_STEPS=100;
const int MAX_SOLS=100;

class Solution : public CObject
{
DECLARE_DYNAMIC(Solution) 
public:
int iType;
int iCur;
CString sTitle;
int iNo;
double dTol;            //Solution accuracy 
int LS[MAX_STEPS];
int BS[MAX_STEPS];
int TS[MAX_STEPS];
CString sStepTitle[MAX_STEPS];
BOOL RS[MAX_STEPS];
Solution();
Solution(int iT,CString sTit,double dT);
~Solution();
void AddStep(CString sT,int idLS,int idBS,int idTS,BOOL bRS);
void DelStep(int ind);
void Serialize(CArchive& ar,int iV);
void Info(int iD);
BOOL SetCurStep(int iC);
int GetCurStep();
CString GetStepTitleString(int iC);
CString GetSolutionTitleString();
};

class SolSets : public CObject
{
DECLARE_DYNAMIC(SolSets) 
public:
int iCur;
int iNo;
CString sTitle;
Solution* pSols[MAX_SOLS];
Solution* GetCurSolution();
BOOL SetCurSol(int iC);
BOOL SetCurStep(int iC);
int  GetCurStep();
SolSets();
SolSets(CString sTitle);
~SolSets();
void AddSolution(int iT,CString sTit,double dT);
void DelSolution(int ind);
void Serialize(CArchive& ar,int iV);
void AddStep(CString sT,int idLS,int idBS,int idTS,BOOL bRS);
void Info();
CString GetTitleString(int iC);

};




//****************************************************************************
//                 T H E    M E S H    O B J E C T
//****************************************************************************
class ME_Object : public G_Object
{
DECLARE_DYNAMIC(ME_Object)
public:
   ME_Object();
   ~ME_Object();
   cFaceList* FcList;
   cLinkList* LkList;
   CvPt_Object BBox[8]; //bounding box
   int iNdNo;				  //No of Nodes
   int iElNo;//No of Elems	
   int iBCLDs;
   int iCYS;
   int iNodeLab;
   int iElementLab;
   int iCYSLab;
   int iNodeMinLab;
   int iElementMinLab;
   int iCYSMinLab;
   double dScale;
   double dScaleVec;
   double dResFactor; //Factor for animation
   C3dVector vRelDispOff; //Relative displacement offset
   //**************************************************************************
   //                    THE    SOLUTION    SETS
   //**************************************************************************
   SolSets* pSOLS;
   //**************************************************************************
   //         LOADS    BOUNDARY CONDITIONS     TEMPERATURE SETS
   //**************************************************************************
   int iCurLC;
   int iNoLCs;
   int iCurBC;
   int iNoBCs;
   int iCurTSet;
   int iNoTSets;
   cLinkedList* LCS[MAX_SETS];
   cLinkedListB* BCS[MAX_SETS];
   cLinkedListT* TSETS[MAX_SETS];
   //**************************************************
   //Results Vector for Display
   cLinkedList* pResVectors;
   void SetCurLC(int iSet);
   void SetCurBC(int iSet);
   void SetCurTSET(int iSet);
   cLinkedList* GetLC(int iSet);
   cLinkedListB* GetBC(int iSet);
   cLinkedListT* GetTSET(int iSet);
   int GetLCID(int ind);
   int GetBCID(int ind);
   int GetTSETID(int ind);
   int GetLCind(int ID);
   int GetBCind(int ID);
   int GetTSETind(int ID);
   BOOL isValidLCid(int iLC);
   BOOL isValidBCid(int iLC);
   BOOL isValidTCid(int iLC);
   int NestTSetID();
   BOOL isActiveSolSet();
   void ListLC();
   void ListBC();
   void ListTSET();
   void DeleteLC(int iSet);
   void DeleteBC(int iSet);
   void DeleteTSET(int iSet);
   int CreateLC(int ID, CString sTit);
   int CreateBC(int ID, CString sTit);
   int CreateTSET(int ID, CString sTit);
   //Post Processing
   //Results Sets
   float fMaxRes;
   float fMinRes;
   BOOL bUserColBar;
   ResSet* ResultsSets[MAX_RESSETS];
   int iNoRes;
   int iCurResSet;
   int iPostOpt;
   int iResVal;
   int iSecID;
   int iCurResVecSet;
   int iResVec;
   int iSecVecID;

   int iCurResSetDef;
   int iResValDef;
   ResSet* CResSet;
   ResSet* CResSetDef;
   //
   int iCVar;
   int iCVarDef;

   NEList* GPs[500];
   int iNoGps;
   ObjTempList* TempList;
   CString sName;
   C3dMatrix TransMat;
   CoordSys* pSys[MAX_FESIZE];     //Cys
   Pt_Object* pNodes[MAX_FESIZE];  //Nodes
   E_Object* pElems[MAX_FESIZE];   //Elements
   BCLD* pBCLDs[MAX_FESIZE];
   void CoordToGlocal();
   void UpdatePropRef(PropTable* pT);
   ME_Object* GetMesh();    //GetPtr to this

   int NodeToGlobal(C3dVector &vRet,int iDef);
   void GlobalToLocal(C3dVector& vRet, int iDef);
   C3dVector CartToCylCYS(CoordSys* pCy, C3dVector pP);
   int VecToGlobal(Pt_Object* pN,C3dVector &vRet,int iDef);
   Pt_Object* AddNode(C3dVector InPt, int iLab,int i2,int i3, int iC,int iDef,int iOut);
   E_Object* AddEl2(int pVnode[200], int iLab,int iCol,int iType,int iPID,int iMat, int iNoNodes,int A,int B,int C,int iMatCys,double dMatAng);
   Pt_Object* GetNode(int iRLab); 
   E_Object* GetElement(int iRLab);

   virtual G_Object* GetObj(int iType,int iLab);
   //Elplicitly add an element directly
   void AddElEx(E_Object* pEl);
   E_Object* AddEl(Pt_Object* pInVertex[200], int iLab, int iCol, int iType, int iPID, int iMat, int iNo, int iA, int iB, int iC, BOOL AddDisp, int iMatCys, double dMatAng);
   BOOL CanDeleteEl(E_Object* pEl);
   BOOL DeleteEl(E_Object* pEl);
   BOOL DeleteCys(CoordSys* pS);
   BOOL DeleteBC(BCLD* pS);
   BOOL DeleteNd(Pt_Object* pN);
   C3dMatrix GetNodalSys(Pt_Object* pN);
   virtual void Create(CString inName,G_Object* Parrent,int iLab);
   virtual void Info();
   void BuildNodeList();
   void DeleteNodeList();
   virtual G_Object* Copy(G_Object* Parrent);
   virtual void Serialize(CArchive& ar,int iV);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void RelTo(G_Object* pThis,ObjList* pList,int iType);
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void Transform(C3dMatrix TMat);
   virtual void Translate (C3dVector vIn);
   virtual void HighLight(CDC* pDC);
   virtual void Colour(int iCol);
   void MaxLab();
   virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   void Append(ME_Object* pMexh,int iNInc,int iEInc);
   void ExportUNV(FILE* pFile,SecTable* pS);
   void ExportNASExec(FILE* pFile, SecTable* pS);
   void ExportNASCase101(FILE* pFile, SecTable* pS);
   void ExportNAS(FILE* pFile,SecTable* pS);
   void ExportRes(FILE* pFile);
   void ExportSec(FILE* pFile,int id,CString Name, double w,double h,double t);
   virtual C3dVector Get_Centroid();
   int GetMeshYExt();
   int GetNoNode(int iType);
   G_Object* AddFluxQ(Pt_Object* pInNode,double inT,int inSetID);
   G_Object* AddTemperatureBC(Pt_Object* pInNode,double inT,int inSetID);
   G_Object* AddAccel(E_Object* pInE,C3dVector vA,int inSetID);
   G_Object* AddRotAccel(E_Object* pE, C3dVector vAxisD, C3dVector vAxisC, double dw, int inSetID);
   G_Object* AddTemperature(E_Object* pInE,double inT,int inSetID);
   G_Object* AddForce(Pt_Object* pInNode,C3dVector inF,int inSetID);
   G_Object* AddMoment(Pt_Object* pInNode,C3dVector inF,int inSetID);
   G_Object* AddPressure(E_Object* pInE,C3dVector inF,int inSetID);
   G_Object* AddRestraint(Pt_Object* pInNode,							  BOOL xon,
								  BOOL yon,
								  BOOL zon,
								  BOOL rxon,
								  BOOL ryon,
								  BOOL rzon,
								  int inSetID);
int GenDofs();          //General gen dof for mixed elements
int GenDofs1D(int iD);  //1 dof problems   
int GenDofs3D(int iD);  //3 dof problems
int MaxBW();
void ApplyRes(cLinkedListB* pBC);

int ApplyResSS(cLinkedListB* pBC);
int LocalResCount();
void LocalRes(int neq,Vec<int> &Steer,Vec<double> &KMA);
void GenLocalResraints(Mat *KM,Vec<int> *G, int &iELCnt);
void LocalResIter(Restraint* pR,Vec<int> &SteerT,Mat &KMAT,Vec<int> &SteerB,Mat &KMAB);
Vec<double> GetForceVec(cLinkedList* pLC,int neq);
Vec <double> GetTempVec(cLinkedList* pTS,int neq);
void ReportQResultant(Vec<double> &QVec);
void ReportFResultant(Vec<double> &FVec);
void GetPressureLoads(cLinkedList* pLC,int neq,Vec<double> &FVec);
void BuildForceVector(PropTable* PropsT,MatTable* MatT,cLinkedList* pLC,cLinkedList* pTC,int neq,Vec<double> &FVec);
void GetAccelLoads(PropTable* PropsT,MatTable* MatT,cLinkedList* pLC,int neq,Vec<double> &FVec);
void GetRotAccelLoads(PropTable* PropsT, MatTable* MatT, cLinkedList* pLC, int neq, Vec<double> &FVec);
void GetThermalLoads(PropTable* PropsT,MatTable* MatT,cLinkedList* pTC,int neq,Vec<double> &FVec);
void ZeroThermalStrains();
void Test(PropTable* PropsT,MatTable* MatT);
void PrintTime(CString cS);
void ZeroDOF();
BOOL GetStepCasesLinStat(int &iStep, CString &sSol, CString &sStep, double &dTol,cLinkedList* &pLC,cLinkedListB* &pBC,cLinkedListT* &pTC,BOOL &bRS);
void IterSol3dLin(PropTable* PropsT,MatTable* MatT);
void IterSol1dSS(PropTable* PropsT,MatTable* MatT);
Mat LocalDisp_E(C3dMatrix TMAT, Vec<int> &Steer, Vec<double> &Disp);
void FtoGlobal_E(Mat* LForce, C3dMatrix TMAT, Vec<int> &Steer, Vec<double> &Disp);
void ExplicitSolTest(PropTable* PropsT, MatTable* MatT);
void formkv(Vec<double> &bk,Mat &KM,Vec<int> &g,int neq);
void banred(Vec<double> &bk,int neq);
void bacsub(Vec<double> &bk, Vec<double> &Loads);
void RadiationLoss(Vec<int> &Steer, Vec<double> &T, Vec<double> &Q);
double GetDisp(int iDof,Vec<int> &Steer,Vec<double> &Disp);
void Displacements(int iLC, CString sSol, CString sStep, Vec<int> &Steer,Vec<double> &Disp);
void Temperatures(int iLC,CString sSol,CString sStep,Vec<int> &Steer,Vec<double> &Disp);
void TempBCSet(int iLC, CString sSol, CString sStep, Vec<int> &Steer, Vec<double> &Disp);
void TranslationalSpringForces(int iLC, CString sSol, CString sStep, PropTable* PropsT,MatTable* MatT,Vec<int> &Steer,Vec<double> &Disp);
void StressesBeam(int iLC, CString sSol, CString sStep, PropTable* PropsT,MatTable* MatT,Vec<int> &Steer,Vec<double> &Disp);
ResSet* Create2dStressResSet(CString sTitle, int iLC, CString sStep, CString sSol);
ResSet* Create2dStrainResSet(CString sTitle, int iLC, CString sStep, CString sSol);
void Add2dStressRes(ResSet* pSSet, int ID, Mat Res, Mat ResZ1, Mat ResZ2);
void Stresses2d(int iLC, CString sSol, CString sStep, PropTable* PropsT,MatTable* MatT,Vec<int> &Steer,Vec<double> &Disp);
void Stresses3d(int iLC, CString sSol, CString sStep, PropTable* PropsT,MatTable* MatT,Vec<int> &Steer,Vec<double> &Disp);
BOOL NodeInEl(Pt_Object* pN);
BOOL ElemInBCSet(E_Object* pN);
BOOL NodeInBCSet(Pt_Object* pN);
int  MaxDof(Pt_Object* pN);
BOOL bDrawN;
BOOL bDrawCYS;
void BuildLinkList();
BOOL isFaceDeletable(cFace* inFace);
BOOL isLinkDeletable(cLink* inLink);
virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
virtual void S_Sel(int iT,ObjList* pSel);
CoordSys* AddSys(C3dVector Orig,C3dMatrix RMat,int iRID,int iTp, int iLab, int iC);
CoordSys* GetSys(int iLab);
void CNodesMerge(double dTol);
void RepNodeInEl(Pt_Object* pThis,Pt_Object* pWith);
ObjList* CNodesMerge2(double dTol,BOOL UpLab,BOOL bDel);
Pt_Object* GetClosestNode(Pt_Object* pIn,double* dMinDist);
Pt_Object* GetClosestNode2(C3dVector pIn, double &dMinDist);
void GetClosestNodes(C3dVector pTrg,ObjList* pRes,double dTol);
int GetNodeInd(Pt_Object* pThisNode);
void ExportGroups(FILE* pFile);	 
ResSet* GetResultsSet(int iSet);
void NullResults();
void DeleteAllResults();
void ResEnvMin(CString sSeq[], int iNo);
void ResEnvMax(CString sSeq[], int iNo);
void ResSetDivInTo(CString sSeq, double dS);
void ResSetScale(CString sSeq, double dS);
void PostElResScalar(ResSet* pRes,int iVar,int iOpt,float &fMax,float &fMin);
void PostElResDef(ResSet* pRes,int iVar,float &fMax,float &fMin);
void DeleteResVectors();
void GenResVectors(int iSet, int iVec, int iDf);
void SetColourBar(float fMax,float fMin);
void BuildDeromedVecs();
void DeleteDeromedVecs();
void AddOUGRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOAG1Res(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOQMRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOEFRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOEFResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);  
void AddOES1Res(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOES1ResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOSTRRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOSTRResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOESNRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOESResR(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName);
void AddOSTRResR(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dFreq);
void AddOSTRFCPXRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dFreq);
void AddONRGRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName);
void ListResSets();
void ListVecSets();
void ListResSet();
void SetCurrentResSetDef(int iRS,int iRV);
void SetDefScale(double dS);
void SetDefScaleVec(double dS);
void SetCurrentResSet(int iRS,int iRV,int iOPT);
void WriteResHead(int iDspFlgs,float dW,float dH);
void ResListRespData(int iEnt);
void ResLabRespItems();
void ResListRespDataFull(int iEnt);
C3dVector EigenVector3d(int iEID, C3dVector rX, C3dVector rY, C3dVector rZ, double lambda);
C3dVector EigenVector2d(int iEID, C3dVector rX, C3dVector rY, double lambda);
void CalcPrinStress(double XX,double YY,double ZZ,
                    double XY,double YZ,double XZ,
                    double &P1,double &P2,double &P3);
virtual void GetBoundingBox(C3dVector& vll, C3dVector& vur);
virtual CString GetName();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);

};


//*******************************************************
//*******************************************************
//The Waveguide Object
//*******************************************************
//*******************************************************
class  WG_Part : public G_Object
{
DECLARE_DYNAMIC(WG_Part)
public:
ME_Object* Mesh;
WG_Part();
CString Name;
CvPt_Object* inPt;
C3dMatrix OMat;
BOOL bFlipZ;
virtual void Create(int iLab,CString inName,C3dVector inP,G_Object* Parrent);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual void HighLight(CDC* pDC);
virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
virtual C3dVector Get_Centroid();
virtual void Serialize(CArchive& ar,int iV);
virtual void AttachTform(C3dMatrix inMat);
virtual C3dVector GetInPt();
virtual ME_Object* GetMesh();
virtual void FlipZ();
virtual void FlipY();
virtual C3dVector MinPt(C3dVector inPt);
virtual void AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB);
virtual void Info();
};

class  WG_Elbow : public WG_Part
{
DECLARE_DYNAMIC(WG_Elbow)
public:
int isHBend;
WG_Elbow();
virtual void Create(int iLab,CString inName,C3dVector inP,int HB,G_Object* Parrent);
virtual void Serialize(CArchive& ar,int iV);
virtual void AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB);
};

class  WG_Brk : public WG_Part
{
DECLARE_DYNAMIC(WG_Brk)
public:
CvPt_Object* OPt;

WG_Brk();
virtual void Create(int iLab,CString inName,C3dVector inP,C3dVector inOP,G_Object* Parrent);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual void Serialize(CArchive& ar,int iV);
virtual void AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB);
virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
};

class  WG_Brk_Int : public WG_Brk
{
DECLARE_DYNAMIC(WG_Brk_Int)
public:
//CvPt_Object* OPt;
CvPt_Object* OPt2;
WG_Brk_Int();
virtual void Create(int iLab,CString inName,C3dVector inP,C3dVector inOP,C3dVector inOP2,G_Object* Parrent);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual void Serialize(CArchive& ar,int iV);
virtual void AttachMesh(ME_Object* pM,C3dMatrix TMat,C3dVector vA,C3dVector vB);
virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
};

const int MaxPrtNo = 100;

class PartsCat : public G_Object
{
DECLARE_DYNAMIC( PartsCat )

public:
   ~PartsCat();
   int iNo;
   int iCurDsp;
   ME_Object* P_Obj[MaxPrtNo];
   PartsCat(int iLab);
   virtual void Create(int iLab);
	 //virtual void Clear();
   virtual void Info();
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   //virtual G_Object* Copy();
   virtual void Draw(CDC* pDC,int iDrawmode);
	 virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
	 virtual void HighLight(CDC* pDC);
	 virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
	 //virtual void SetTo(C3dVector cInVect);
   virtual void Transform(C3dMatrix TMAt);
   virtual void Serialize(CArchive& ar,int iV);
   virtual void Add(ME_Object* inMesh);
   virtual void Next();
   virtual void Previous();
   virtual ME_Object* Get(CString inName);
   virtual ME_Object* GetCur();
};


class  Section : public G_Object
{
DECLARE_DYNAMIC(Section)
public:
int iSec;
int iPID;
int iPID2;
C3dMatrix TMat; 
NCurve* pLn[50];
C3dVector inPt;
int NoSegs[50];
int iLnCnt;
double dWall;
virtual ~Section();
virtual void Create(int iLab,int inPID,int inPID2,int inSec,int inCol,G_Object* Parrent);
virtual void Serialize(CArchive& ar,int iV);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual void HighLight(CDC* pDC);
virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
virtual C3dVector Get_Centroid();
virtual void AddLine(double X1,double Y1,double X2,double Y2,int NoDivs);
virtual void ChangeCol(int iCOl);
virtual void Transform(C3dMatrix TMat);
virtual G_Object* Copy(G_Object* Parrent);
C3dVector GetPt(int iSeg,int iPos);
int GetNoLines();
int GetDivs(int iL);
void SetInPt(C3dVector Pt);
BOOL isClosedSec();
C3dVector NLnInt(NCurve* L1,NCurve* L2);
NCircle* NFillet(NLine* Ln,NLine* Ln1,double dR);
void MakeSpace(int iPos);
void FilletCrns(double dR);
};



const int MaxT = 1000;
const int MaxP = 100;

class  WG_Def : public G_Object
{
DECLARE_DYNAMIC(WG_Def)
public:
CString Name;
CString Text[MaxT];
double dSize;
double dASize;
int iTCnt;
int iPartCnt;
int iWG;
double dWall;
int iWG2;
double dWall2;
BOOL bQ1;
BOOL bQ2;
double dW;
double dH;
int iTarnsitionPos;
C3dVector vStart;
BOOL isMeshed;
G_Object* WGParts[MaxP];
WG_Def();
virtual void Create(int iLab,CString sN,G_Object* Parrent);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual void HighLight(CDC* pDC);
virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
virtual C3dVector Get_Centroid();
void addLn(CString inT);
void BuildFromDef(int* iErr);
int Generate(SecTable* pSecs,int iM,int iSW,int iSH,double dS,double dSA);
int  AddPart(G_Object* inP);
virtual void Serialize(CArchive& ar,int iV);
NCircle* NFillet(NLine* Ln,NLine* Ln1,double dR);
Circ1* Fillet(Line_Object* Ln,Line_Object* Ln1,double dR);
C3dVector NLnInt(NCurve* L1,NCurve* L2);
C3dVector LnInt(Line_Object* L1,G_Object* L2);
virtual void Info();
C3dMatrix GetTMat(int iPindex);
C3dVector GetVA(int iPindex);
C3dVector GetVB(int iPindex);
int GenMesh(SecTable* pSecs,PropTable* pT,int iM,PartsCat* Cat,int iDim);
ME_Object* GetMesh();
C3dVector GetLastInsPos();
C3dMatrix GetOrientMat();
void UpdatePropRef(PropTable* pT);
void WG_Def::SetFlexMarkers();
PSHELL* CreateShell(PropTable* pT, double dTHK,double NSM,int iM,int PIDS);
PBARL* CreatePBARL(PropTable* pT,CString sT,double W,double H, double dTHK,double dNSM,int iM,int PIDB);
};











class  Sweep : public G_Object
{
DECLARE_DYNAMIC(Sweep)
public:
int iPID;
G_Object* pPath; 
Section* pBaseSec;
Section* pAllSecs[500];
ME_Object* Mesh;
CString Name;
int iSecCnt;
double Twist;
BOOL isVoid;
double dElLength;
BOOL isStart;
BOOL isEnd;
Sweep();
int iMeshCnt;
virtual void PreCreate(int iLab,CString inName,double dT);
virtual void Create(int iLab,G_Object* inPath,
                    Section* inSec,G_Object* Parrent);
virtual void Serialize(CArchive& ar,int iV);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual void HighLight(CDC* pDC);
virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
virtual void S_Box(CPoint P1,CPoint P2,ObjList* pSel);
virtual C3dVector Get_Centroid();
virtual void Generate(C3dMatrix mUp,double dElLen);
virtual void Transform(C3dMatrix TMat);
virtual C3dMatrix GetLastYMap();
virtual C3dMatrix GetFirstYMap();
virtual void DeleteSections();
virtual void GenMesh(int iDim,PSHELL* pS,PBARL* pB);
virtual double GetSecSpacing();
virtual void CutBack(BOOL bEA,BOOL bEB,ME_Object* MeshA,ME_Object* MeshB);
virtual ME_Object* GetMesh();
virtual C3dVector MinPt(C3dVector inPt);
virtual C3dVector GetInPt();
virtual C3dVector GetDir(double w);

};

class  SweepF : public Sweep
{
DECLARE_DYNAMIC(SweepF)
public:

SweepF();
double dFR;
virtual void PreCreate(int iLab,CString inName,double dT);
virtual void Generate(C3dMatrix mUp,double dElLen,double dLenFR);
virtual void GenMesh(int iDim,PSHELL* pS1,PSHELL* pS2
                             ,PSHELL* pS3,PSHELL* pS4
                             ,PBARL* pB1,PBARL* pB2);
virtual void CutBack(BOOL bEA,BOOL bEB,ME_Object* MeshA,ME_Object* MeshB);

};

class  SweepB : public Sweep
{
DECLARE_DYNAMIC(SweepB)
public:
double dRad;
int isHBend;
CvPt_Object* inPt;
SweepB();
virtual void PreCreate(int iLab,CString inName,
					    C3dVector inP,double dR,int EH,double dT);
virtual void Create(int iLab,NCurve* inPath,
                    Section* inSec,G_Object* Parrent);

virtual void Serialize(CArchive& ar,int iV);
virtual void Draw(CDC* pDC,int iDrawmode);
virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
virtual void Transform(C3dMatrix TMat);
virtual C3dVector GetInPt();
virtual void Generate(C3dMatrix mUp,double dElLen);
virtual C3dVector GetNVec();
virtual C3dVector GetSVec();

};

class  SweepFB : public SweepB
{
DECLARE_DYNAMIC(SweepFB)
public:
SweepFB();
virtual void PreCreate(int iLab,CString inName,
					   C3dVector inP,double dR,int EH,double dT);
virtual void GenMesh(int iDim,PSHELL* pS1,PSHELL* pS2
                             ,PSHELL* pS3,PSHELL* pS4
                             ,PBARL* pB1,PBARL* pB2);

}; 

class  SecProp 
{
public:
int WR;
int WG;
double THK;
double W;
double H;
int COL;
int PID;
int PID2;
int SecNo;
int Opt;
BOOL bFlex;
double dR;
int iMat1;
int iMat2;
double THK2;
double dLFR;
double dNSMS;
double dNSMB;
int iP1;
int iP2;
int iP3;
int iP4;
int iP5;
int iP6;
};

const int MaxSecs=100;
class  SecTable 
{
public:
SecProp* Secs[MaxSecs];
int iNo;
SecTable();
void add(int iWR, 
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
     int iP6);

void ExportSecs(FILE* pFile);
Section* GetSec(int iWR,double dThk,int iOpt,int iSW,int iSH,BOOL bis);
SecProp* GetSecP(int iWR,double dThk,int iOpt,int iSW,int iSH);
SecProp* GetSecPF(int iWR);
};


class Force : public BCLD
{
DECLARE_DYNAMIC(Force)
public:
   ~Force();
   C3dVector F;
   C3dVector DSP_Point[2];
   C3dVector Point[2];
   int SetID;
   virtual void Create(G_Object* pInNode,
	                     G_Object* Parrent,
					     C3dVector inF,
					     int inSetID);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC);
   virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   virtual C3dVector Get_Centroid();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual void Info(); 
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT,int iNo, CString sVar[]);
};

class Temperature : public BCLD
{
DECLARE_DYNAMIC(Temperature)
public:
   Temperature();
   ~Temperature();
   double dV;
   C3dVector DSP_Point;
   C3dVector Point;

   virtual void Create(G_Object* pInE,
	                     G_Object* Parrent,
					             double inV,
					             int inSetID);

   virtual void SetToScr(C3dMatrix* pModMat, C3dMatrix* pScrTran);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual C3dVector Get_Centroid();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual void Info(); 

};

class AccelLoad : public BCLD
{
DECLARE_DYNAMIC(AccelLoad)
public:
   AccelLoad();
   ~AccelLoad();
   C3dVector vA;
   C3dVector DSP_Point;
   C3dVector Point;

   virtual void Create(G_Object* pInE,
	                     G_Object* Parrent,
					             C3dVector inV,
					             int inSetID);
   virtual void SetToScr(C3dMatrix* pModMat, C3dMatrix* pScrTran);
   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual C3dVector Get_Centroid();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual void Info(); 
};

class RotationLoad : public BCLD
{
DECLARE_DYNAMIC(RotationLoad)
public:
  RotationLoad();
  ~RotationLoad();
  C3dVector vAxisD;         //Axis Dir
  C3dVector vAxisC;         //Axis Centre
  double w;             //Rotational speed in radians a second
  C3dVector DSP_Point;
  C3dVector Point;

  virtual void Create(G_Object* pInE,
                      G_Object* Parrent,
                      C3dVector inD,
                      C3dVector inC,
                      double dW,
                      int inSetID);
  virtual void SetToScr(C3dMatrix* pModMat, C3dMatrix* pScrTran);
  virtual void Serialize(CArchive& ar, int iV, ME_Object* MESH);
  virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
  virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
  virtual C3dVector Get_Centroid();
  virtual void Info();
};

//****************************************************************************
//****************************************************************************
//                       For thermal analysis
//****************************************************************************
//****************************************************************************
class TemperatureBC : public Temperature
{
DECLARE_DYNAMIC(TemperatureBC)
TemperatureBC();
~TemperatureBC();
virtual void Create(G_Object* pInNode,
G_Object* Parrent,
double inV,
int inSetID);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
};

class FluxLoad : public Temperature
{
DECLARE_DYNAMIC(FluxLoad)
FluxLoad();
~FluxLoad();
virtual void Create(G_Object* pInNode,
	                  G_Object* Parrent,
					          double inV,
					          int inSetID);
virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
};
//****************************************************************************
//****************************************************************************

class Moment : public Force
{
DECLARE_DYNAMIC(Moment)
public:
   virtual void Create(G_Object* pInNode,
	                   G_Object* Parrent,
					   C3dVector inF,
					   int inSetID);
virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
void ExportNAS(FILE* pFile);
virtual CString GetName();
};

class Pressure : public Force
{
DECLARE_DYNAMIC(Pressure)
public:
virtual void Create(E_Object* pInEl,
	                G_Object* Parrent,
					C3dVector inF,
					int inSetID);
void ExportNAS(FILE* pFile);
void Serialize(CArchive& ar,int iV,ME_Object* MESH);
void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
void OglDrawW(int iDspFlgs,double dS1,double dS2);
virtual CString GetName();
virtual int GetVarHeaders(CString sVar[]);
virtual int GetVarValues(CString sVar[]);
virtual void PutVarValues(PropTable* PT,int iNo, CString sVar[]);
};


class Restraint : public BCLD
{
DECLARE_DYNAMIC(Restraint)
public:
   ~Restraint();
   C3dVector DSP_Point;
   C3dVector Point;
   BOOL REST[6];

   virtual void Create(G_Object* pInNode,
	                   G_Object* Parrent,
					           BOOL xon,
                     BOOL yon,
                     BOOL zon,
                     BOOL rxon,
                     BOOL ryon,
                     BOOL rzon,
					   int inSetID);

   virtual void Serialize(CArchive& ar,int iV,ME_Object* MESH);
   virtual void Draw(CDC* pDC,int iDrawmode);
   virtual void OglDraw(int iDspFlgs,double dS1,double dS2);
   virtual void OglDrawW(int iDspFlgs,double dS1,double dS2);
   virtual void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
   virtual void HighLight(CDC* pDC);
   //virtual G_ObjectD SelDist(CPoint InPT,Filter FIL);
   virtual C3dVector Get_Centroid();
   virtual void ExportUNV(FILE* pFile);
   virtual void ExportNAS(FILE* pFile);
   virtual void Info();
   CString GetDofStr(); 
   virtual CString GetName();
   virtual int GetVarHeaders(CString sVar[]);
   virtual int GetVarValues(CString sVar[]);
   virtual void PutVarValues(PropTable* PT, int iNo, CString sVar[]);
};


// Results Vector Display Object
class ResultsVec : public G_Object
{
	DECLARE_DYNAMIC(ResultsVec)
public:

	int iType; //
	vector<int> vector_name;
	C3dVector DSP_Point;
	C3dVector Point;
	C3dVector Vector;
	int iSign;
	int iDof; //1 to 3 0=All 
	ResultsVec(int iD, C3dVector Pt, C3dVector Vec, int iC, int iDf,int iS, int iTp);
	virtual void Create(int iD, C3dVector Pt, C3dVector Vec, int iC);
	virtual C3dVector Get_Centroid();
	virtual void OglDraw(int iDspFlgs, double dS1, double dS2);
	virtual void OglDrawW(int iDspFlgs, double dS1, double dS2);
	void DrawVector(int iDspFlgs,double dS1, double dS2,double dS, double dRF);
	void DrawTenVector(int iDspFlgs,double dS1, double dS2, double dS, double dRF);
	virtual void Info();
	//virtual void HighLight(CDC* pDC);
};

// Graph Object
// first class to use vector objevt
class Graph : public CObject
{
	DECLARE_DYNAMIC(Graph)
public:
	int iCol=0;
	CString	sTitle;
	CString	sSubTitle;
	CString sResType;
	CString sEntID;
	CString	sVar;
	float GminX;
	float GmaxX;
	float GminY;
	float GmaxY;
	vector <float> fx;
	vector <float> fy;
	Graph();
	~Graph();
	float GetMaxfx();
	float GetMinfx();
	float GetMaxfy();
	float GetMinfy();
	void genMaxMin();
	void List();
};


//************************************************************************
//   D E L A U N A Y  TRIANGULATION
//************************************************************************
class Facest3
{
public:
C3dVector* pV[3];
C3dVector vC;
double CirR;

Facest3(C3dVector* v1,C3dVector* v2,C3dVector* v3);
};

//Class for storing nastran fields
const int MAX_FIELDS=5000;
class NasCard
{
public:
int iNo;
int iLnCnt;
CString Fields[MAX_FIELDS];
NasCard();
void Clear();
BOOL isVoid(int iField);
CString GetField(int iField);
BOOL AddLn(CString sStr);
void Read(FILE* pFile,CString& sLine,CString& sLineN);
};

const int MAX_TRI=1000;

class Trianguation
{
public:
Facest3* Tri[MAX_TRI];
int iNo;
Trianguation();
void AddTriangle(C3dVector* v1,C3dVector* v2,C3dVector* v3);
};

class Delaunay2d
{
Trianguation Tris;
C3dVector Nodes[MAX_TRI];
int iNo;
Delaunay2d();
void AddPt(double x,double y,double z);
};


//***************************************************
// 2d Material Point Method State Variable
// 06/03/2019
//***************************************************
class MPMVar2d
{
public:
  MPMVar2d();
  ~MPMVar2d();
  int Pid;           //Particle ID
  Pt_Object* pNode;
  int Eid;           //Base element ID
  int BCellid;       //Back groud grid ID (Euler Cell ID)
  double dMp;        //Particle Mass
  double dVol;       //Particle Volume
  double dVol0;       //Particle Volume
  Mat dvFp;          //Deformation gradient  
  Mat ds;            //Stress
  Mat deps;          //Strain
  Mat dVp;           //Velocity
  Mat dXp;           //Position
};

class Ndata
{
public:
  Ndata();
  ~Ndata();
  double nMass;
  void Reset();
  Mat nMomentum;
  Mat nIForce;
  Mat nEforce;
};
