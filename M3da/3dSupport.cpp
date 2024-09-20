
#include "stdafx.h"
#include "3dSupport.h"
#include <math.h>
#define D2R  0.01745329251994
#define R2D  57.2957795130931
double Pi = 3.1415926535;









IMPLEMENT_DYNAMIC(C3dObject, CObject)

C3dObject::C3dObject()
{
	m_hr = 0;
}

C3dObject::~C3dObject()
{
}


double RadToDeg(double dARad)
{
 return ((dARad/3.1415926535)*180);

}

//   C3dVector vAxisPts[4];
//   C3dVector vEyePt;
//	 C3dMatrix mOrientMat;


     







//////////////////////////////////////////////////////////////////
// C3dVector

C2dVector::C2dVector()
{
	x = 1;
	y = 1;
}

C2dVector::~C2dVector()
{
}


C2dVector::C2dVector(double _x, double _y)
{
	x = _x;
	y = _y;
}

C2dVector C2dVector::operator = (const C2dVector r)
{
	x = r.x;
	y = r.y;
	return *this;
}

C2dVector C2dVector::operator = (const C2dVector* r)
{
	x = r->x;
	y = r->y;
	return *this;
}

C2dVector C2dVector::operator = (const double r)
{
	x = r;
	y = r;
	return *this;
}

BOOL C2dVector::operator == (const C2dVector r)
{
	BOOL brc = FALSE;
	if ((x == r.x) && (y == r.y))
	{
		brc = TRUE;
	}
	return (brc);
}


C2dVector C2dVector::operator + (const C2dVector b)
{
	return C2dVector(x + b.x,y + b.y);
}

C2dVector C2dVector::operator - (const C2dVector b)
{
	return C2dVector(x - b.x,y - b.y);
}

C2dVector& C2dVector::operator += (const C2dVector& r)
{
	x += r.x;
	y += r.y;
	return *this;
}



C2dVector& C2dVector::operator -= (const C2dVector& r)
{
	x -= r.x;
	y -= r.y;
	return *this;
}

C2dVector& C2dVector::operator *= (const double s)
{
	x *= s;
	y *= s;
	return *this;
}

void C2dVector::Clamp(double dMin, double dMax)
{
	if (x < dMin)
		x = dMin;
	if (x > dMax)
		x = dMax;
	if (y < dMin)
		y = dMin;
	if (y > dMax)
		y = dMax;
}

double C2dVector::Cross(C2dVector vIn)
{
	double drc;
	drc = x * vIn.y - vIn.x*y;
	return (drc);
}


double C2dVector::Dist(C2dVector inPt)
{
	double dx,dy,d;
	dx = (inPt.x - x);
	dy = (inPt.y - y);
	d = pow(dx*dx + dy * dy, 0.5);
	return (d);
}

BOOL C2dVector::Normalize()
{
	double l;
	l = pow(x*x + y * y, 0.5);
	x /= l;
	y /= l;
	return TRUE;
}

double C2dVector::Mag()
{
	return (pow(x*x + y * y, 0.5));
}

double C2dVector::Dot(C2dVector v)
{
	return (x * v.x + y * v.y);
}


//////////////////////////////////////////////////////////////////
// C3dVector

C3dVector::C3dVector()
{
	x = 1;
	y = 1;
	z = 1;
}

C3dVector::~C3dVector()
{
}

//C3dVector::C3dVector(const D3DVECTOR& r)
//{
//	x = r.x;
//	y = r.y;
//	z = r.z;
//}

C3dVector::C3dVector(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}


void C3dVector::Serialize(CArchive& ar,int iV)
{
	if (ar.IsStoring())
	{
    ar<<x;
    ar<<y;
    ar<<z;  
	}
	else
	{
    ar>>x;
    ar>>y;
    ar>>z; 
	}
}

void C3dVector::Set(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}


C3dVector C3dVector::operator = (const C3dVector r)
{
	x = r.x;
	y = r.y;
	z = r.z;
	return *this;
}

C3dVector C3dVector::operator = (const C3dVector* r)
{
	x = r->x;
	y = r->y;
	z = r->z;
	return *this;
}

C3dVector C3dVector::operator = (const double r)
{
	x = r;
	y = r;
	z = r;
	return *this;
}

BOOL C3dVector::operator == (const C3dVector r)
{
BOOL brc=FALSE;
if ((x == r.x) && (y == r.y)  && (z == r.z))
{
  brc=TRUE;
}
return (brc);
}


C3dVector C3dVector::operator + (const C3dVector b)
{
    return C3dVector(x + b.x,
                     y + b.y,
                     z + b.z);
}

C3dVector C3dVector::operator - (const C3dVector b)
{
    return C3dVector(x - b.x,
                     y - b.y,
                     z - b.z);
}

C3dVector& C3dVector::operator += (const C3dVector& r)
{
    x += r.x;
    y += r.y;
    z += r.z;
    return *this;
}

C3dVector operator - (const C3dVector& a, const C3dVector& b)
{
    return C3dVector(a.x - b.x,
                     a.y - b.y,
                     a.z - b.z);
}

C3dVector& C3dVector::operator -= (const C3dVector& r)
{
    x -= r.x;
    y -= r.y;
    z -= r.z;
    return *this;
}

C3dVector C3dVector::operator - ()
{
	return C3dVector(-x, -y, -z);
}

// vector (cross) product
C3dVector operator * (const C3dVector& a, const C3dVector& b)
{
    return C3dVector(a.y * b.z - a.z * b.y,
					 a.z * b.x - a.x * b.z,
					 a.x * b.y - a.y * b.x);
}

// vector (cross) product
C3dVector& C3dVector::operator *= (const C3dVector& r)
{
    // deliberately create a temp to hold result
    *this = *this * r;
    return *this;
}
                      
// magnitude change
C3dVector C3dVector::operator * (const double s)
{
    return C3dVector(x * s,
					 y * s,
					 z * s);
}



// magnitude change
C3dVector& C3dVector::operator *= (const double s)
{
	x *= s;
	y *= s;
	z *= s;
    return *this;
}

C3dVector& C3dVector::operator /= (const double s)
{
	x /= s;
	y /= s;
	z /= s;
    return *this;
}

double C3dVector::Ang(const C3dVector& r)
{
    double da;
	double db;
	double dc;

	da = Mag();
    db = sqrt(r.x * r.x + r.y * r.y + r.z * r.z);
    dc = da*db;
	
	da = (x * r.x + y * r.y + z * r.z);
	if (dc !=  0) 
	  {
	  
		db = acos(da/dc)*R2D;
		if (da/dc < 0)
		  {
		  db = db+90;	
		  }
	  }
	else
	  {
		db = 90;
	  }
	return (db);
}

double C3dVector::AngSigned(C3dVector r, C3dVector vN)
{
	double dot = this->Dot(r);
	double magV1 = this->Mag();
	double magV2 = r.Mag();

	// Using the dot product formula to find the angle between the vectors
	double angle = acos(dot / (magV1 * magV2));

	// Convert the angle to degrees
	double angleDegrees = angle * R2D;

	// Determine the sign of the angle
	C3dVector crossProduct;
	crossProduct = this->Cross(r);

	if (vN.Dot(crossProduct) < 0)
	{
		angleDegrees = 360-angleDegrees;

	}

	return angleDegrees;
}

void C3dVector::Rotate(C3dVector vA1,C3dVector vA2,double dAng)
{
C3dVector vRotVec;
vRotVec = vA2-vA1;
vRotVec.Normalize();
C3dVector vThis = *this;

C3dMatrix TMat;

TMat.MakeUnit();


//TMat.Translate(-vA1.x,-vA1.y,-vA1.z);
TMat.Rotate(0,dAng,0);
*this = TMat*vThis;
}

void C3dVector::Translate (C3dVector vIn)
{
x+=vIn.x;
y+=vIn.y;
z+=vIn.z;
}


// dot (scalar) product
double C3dVector::Dot(const C3dVector&r)
{
	return x * r.x + y * r.y + z * r.z;
}


C3dVector C3dVector::Cross(C3dVector vIn)
{
C3dVector vRet;
vRet.x = y*vIn.z-z*vIn.y;
vRet.y = -(x*vIn.z-z*vIn.x);
vRet.z = x*vIn.y-y*vIn.x;
return (vRet);
}






// magnitude (length)
double C3dVector::Mag()
{
	return sqrt(x * x + y * y + z * z);
}

// Normalize a vector (make it unit lebgth)
BOOL C3dVector::Normalize()
{
	double l = Mag();
	if (l == 0) return FALSE;
	x /= l;
	y /= l;
	z /= l;
	return TRUE;
}

// test for coincidence
BOOL C3dVector::Coincident(const C3dVector& r)
{
	C3dVector a(*this);
	a.Normalize();
	C3dVector b(r);
	b.Normalize();
	if ((a.x == b.x) 
	&& (a.y == b.y)
	&& (a.z == b.z)) {
		return TRUE;
	}
	return FALSE;
}

// Compute an arbitrary up vector
C3dVector C3dVector::GenerateUp()
{
	Normalize();

	// Create an initial up vector
	C3dVector vu(0, 1, 0);

	// make sure the up and dir vectors are not the same
	if (Coincident(vu) || Coincident(-vu)) {

		// d is 'up' or 'down' so just set up to be x
		return C3dVector(1, 0, 0);

	} 

	// compute the 'right' vector from the requested up
	// vector and the direction vector
	C3dVector vr = *this * vu;

	// compute the actual up vector as from the dir and right vectors
	return vr * *this;
}

//Nomalised Direction Vector
//Arbitary orthoganal vector returned

C3dMatrix C3dVector::GetTMat()
{
	C3dMatrix mT;
	C3dVector vX;
	C3dVector vY;
	C3dVector vT;
	double dotX;
	double dotY;
	vX.Set(1.0, 0.0, 0.0);
	vY.Set(0.0, 1.0, 0.0);
	dotX = abs(this->Dot(vX));
	dotY = abs(this->Dot(vY));
	if (dotX < dotY)
		vT = vX;
	else
		vT = vY;
	vY = this->Cross(vT);
	vX = vY.Cross(*this);
	mT.SetColVec(1, *this);
	mT.SetColVec(2, vX);
	mT.SetColVec(3, vY);


	return (mT);
}



BOOL C3dVector::IsNull()
{
	if ((x == 0.0) && (y == 0) && (z ==  0)) {
		return TRUE;
	}
	return FALSE;
}

C3dVector& C3dVector::TGet()
{
return (*this);
}

double C3dVector::Dist(C3dVector inPt)
{
double dx;
double dy;
double dz;

dx= inPt.x - x;
dy= inPt.y - y;
dz= inPt.z - z;
return (pow((dx*dx+dy*dy+dz*dz),0.5));
}


void C3dVector::SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran)
{

C3dVector V;
C3dVector R;

R.x = x;
R.y = y;
R.z = z;
V.x =  pModMat->m_00 * R.x +  pModMat->m_01 * R.y +  pModMat->m_02 * R.z +  pModMat->m_30;
V.y =  pModMat->m_10 * R.x +  pModMat->m_11 * R.y +  pModMat->m_12 * R.z +  pModMat->m_31;
V.z =  pModMat->m_20 * R.x +  pModMat->m_21 * R.y +  pModMat->m_22 * R.z +  pModMat->m_32;

R.x =  pScrTran->m_00 * V.x +  pScrTran->m_01 * V.y +  pScrTran->m_02 * V.z +  pScrTran->m_30;
R.y =  pScrTran->m_10 * V.x +  pScrTran->m_11 * V.y +  pScrTran->m_12 * V.z +  pScrTran->m_31;
R.z =  pScrTran->m_20 * V.x +  pScrTran->m_21 * V.y +  pScrTran->m_22 * V.z +  pScrTran->m_32;


x = R.x;
y = R.y;
z = 0;
}

C4dVector::C4dVector()
{
	xw = 1;
	yw = 1;
	zw = 1;
	w = 1;
}

C4dVector::~C4dVector()
{
}

C4dVector::C4dVector(double dx, double dy, double dz, double dw)
{
	xw = dx;
	yw = dy;
	zw = dz;
	w = dw;
}

void C4dVector::Serialize(CArchive& ar,int iV)
{
	if (ar.IsStoring())
	{
    ar<<xw;
    ar<<yw;
    ar<<zw;
	ar<<w;
	}
	else
	{
    ar>>xw;
    ar>>yw;
    ar>>zw; 
	ar<<w;
	}
}

C4dVector C4dVector::operator = (const C4dVector r)
{
	xw = r.xw;
	yw = r.yw;
	zw = r.zw;
	w = r.w;
	return *this;
}

C4dVector C4dVector::operator = (const double r)
{
	xw = r;
	yw = r;
	zw = r;
	w = r;
	return *this;
}

C4dVector C4dVector::operator + (const C4dVector b)
{
    return C4dVector(xw + b.xw,
                     yw + b.yw,
                     zw + b.zw,
					 w + b.w);
}

C4dVector C4dVector::operator * (const double s)
{
    return C4dVector(xw * s,
					 yw * s,
					 zw * s,
					 w * s);
}


void C4dVector::Translate(C3dVector vS)
{
 
xw = ((xw / w)+vS.x)*w;	
yw = ((yw / w)+vS.y)*w;
zw = ((zw / w)+vS.z)*w;	
}

C3dVector C4dVector::GetPoint()
{
C3dVector vRet;
vRet.x = xw/w;
vRet.y = yw/w;
vRet.z = zw/w;
return (vRet);
}


void C4dVector::Clear()
{
xw=0;
yw=0;
zw=0;
w=0;
}


double C4dVector::GetWght()
{
return (w);
}

void C4dVector::Transform(C3dMatrix TMAt)
{
C3dVector R;
C3dVector v;
v.x = xw/w;
v.y = yw/w;
v.z = zw/w;
R.x =  TMAt.m_00 * v.x +  TMAt.m_01 * v.y +  TMAt.m_02 * v.z +  TMAt.m_30;
R.y =  TMAt.m_10 * v.x +  TMAt.m_11 * v.y +  TMAt.m_12 * v.z +  TMAt.m_31;
R.z =  TMAt.m_20 * v.x +  TMAt.m_21 * v.y +  TMAt.m_22 * v.z +  TMAt.m_32;
xw =R.x*w;
yw =R.y*w;
zw =R.z*w;
}


//////////////////////////////////////////////////////////////////
// C3dMatrix

//IMPLEMENT_DYNAMIC(C3dMatrix, C3dObject)

C3dMatrix::C3dMatrix()
{
    m_00=1.0; m_01=0.0;  m_02=0.0; m_03=0.0;
    m_10=0.0; m_11=1.0;  m_12=0.0; m_13=0.0;
    m_20=0.0; m_21=0.0;  m_22=1.0; m_23=0.0;
    m_30=0.0; m_31=0.0;  m_32=0.0; m_33=1.0;
}

C3dMatrix::~C3dMatrix()
{
}

void C3dMatrix::Serialize(CArchive& ar,int iV)
{
	if (ar.IsStoring())
	{
      ar<<m_00;ar<<m_01;ar<<m_02;ar<<m_03;
      ar<<m_10;ar<<m_11;ar<<m_12;ar<<m_13;
      ar<<m_20;ar<<m_21;ar<<m_22;ar<<m_23;
      ar<<m_30;ar<<m_31;ar<<m_32;ar<<m_33;
	}
	else
	{
      ar>>m_00;ar>>m_01;ar>>m_02;ar>>m_03;
      ar>>m_10;ar>>m_11;ar>>m_12;ar>>m_13;
      ar>>m_20;ar>>m_21;ar>>m_22;ar>>m_23;
      ar>>m_30;ar>>m_31;ar>>m_32;ar>>m_33;
	}
}

void C3dMatrix::SetColVec(int iC,C3dVector inV)
{
  switch(iC) 
  {
    case 1:
      {
        m_00=inV.x;
        m_10=inV.y;
        m_20=inV.z;
        break;
      }
    case 2:
      {
        m_01=inV.x;
        m_11=inV.y;
        m_21=inV.z;
        break;
      }
    case 3:
      {
        m_02=inV.x;
        m_12=inV.y;
        m_22=inV.z;
        break;
      }
    case 4:
      {
        m_03=inV.x;
        m_13=inV.y;
        m_23=inV.z;
        break;
      }
  }
}

C3dVector C3dMatrix::GetColVec(int iC)
{
  C3dVector vRet;
  switch(iC) 
  {
    case 1:
      {
        vRet.x = m_00;
        vRet.y = m_10;
        vRet.z = m_20;
        break;
      }
    case 2:
      {
        vRet.x = m_01;
        vRet.y = m_11;
        vRet.z = m_21;
        break;
      }
    case 3:
      {
        vRet.x = m_02;
        vRet.y = m_12;
        vRet.z = m_22;
        break;
      }
  }
return (vRet);
}


C3dVector C3dMatrix::GetUpVec()
{
return (GetColVec(2));
}

C3dMatrix::C3dMatrix(const C3dMatrix& r)
{
    m_00=r.m_00; m_01=r.m_01; m_02=r.m_02; m_03=r.m_03; 
    m_10=r.m_10; m_11=r.m_11; m_12=r.m_12; m_13=r.m_13; 
    m_20=r.m_20; m_21=r.m_21; m_22=r.m_22; m_23=r.m_23; 
    m_30=r.m_30; m_31=r.m_31; m_32=r.m_32; m_33=r.m_33; 
}



C3dMatrix::C3dMatrix(double v00, double v01, double v02, double v03,
                     double v10, double v11, double v12, double v13,
                     double v20, double v21, double v22, double v23,
                     double v30, double v31, double v32, double v33)
{
    m_00=v00; m_01=v01; m_02=v02; m_03=v03; 
    m_10=v10; m_11=v11; m_12=v12; m_13=v13; 
    m_20=v20; m_21=v21; m_22=v22; m_23=v23; 
    m_30=v30; m_31=v31; m_32=v32; m_33=v33; 
}

C3dMatrix& C3dMatrix::operator = (const C3dMatrix &r)
{
    m_00=r.m_00; m_01=r.m_01; m_02=r.m_02; m_03=r.m_03; 
    m_10=r.m_10; m_11=r.m_11; m_12=r.m_12; m_13=r.m_13; 
    m_20=r.m_20; m_21=r.m_21; m_22=r.m_22; m_23=r.m_23; 
    m_30=r.m_30; m_31=r.m_31; m_32=r.m_32; m_33=r.m_33; 
    return *this;
}

C3dMatrix C3dMatrix::operator + (const C3dMatrix& b)
{
    return C3dMatrix(m_00 + b.m_00,
                     m_01 + b.m_01,
                     m_02 + b.m_02,
                     m_03 + b.m_03,
                     m_10 + b.m_10,
                     m_11 + b.m_11,
                     m_12 + b.m_12,
                     m_13 + b.m_13,
                     m_20 + b.m_20,
                     m_21 + b.m_21,
                     m_22 + b.m_22,
                     m_23 + b.m_23,
                     m_30 + b.m_30,
                     m_31 + b.m_31,
                     m_32 + b.m_32,
                     m_33 + b.m_33);
}

C3dMatrix& C3dMatrix::operator += (const C3dMatrix& r)
{
    m_00+=r.m_00; m_01+=r.m_01; m_02+=r.m_02; m_03+=r.m_03;
    m_10+=r.m_10; m_11+=r.m_11; m_12+=r.m_12; m_13+=r.m_13;
    m_20+=r.m_20; m_21+=r.m_21; m_22+=r.m_22; m_23+=r.m_23;
    m_30+=r.m_30; m_31+=r.m_31; m_32+=r.m_32; m_33+=r.m_33;
    return *this;
}

// friend
C3dMatrix C3dMatrix::operator * (const C3dMatrix& b)
{
    return C3dMatrix(m_00*b.m_00 + m_01*b.m_10 + m_02*b.m_20 + m_03*b.m_30,
                     m_00*b.m_01 + m_01*b.m_11 + m_02*b.m_21 + m_03*b.m_31,
                     m_00*b.m_02 + m_01*b.m_12 + m_02*b.m_22 + m_03*b.m_32,
                     m_00*b.m_03 + m_01*b.m_13 + m_02*b.m_23 + m_03*b.m_33,
                     m_10*b.m_00 + m_11*b.m_10 + m_12*b.m_20 + m_13*b.m_30,
                     m_10*b.m_01 + m_11*b.m_11 + m_12*b.m_21 + m_13*b.m_31,
                     m_10*b.m_02 + m_11*b.m_12 + m_12*b.m_22 + m_13*b.m_32,
                     m_10*b.m_03 + m_11*b.m_13 + m_12*b.m_23 + m_13*b.m_33,
                     m_20*b.m_00 + m_21*b.m_10 + m_22*b.m_20 + m_23*b.m_30,
                     m_20*b.m_01 + m_21*b.m_11 + m_22*b.m_21 + m_23*b.m_31,
                     m_20*b.m_02 + m_21*b.m_12 + m_22*b.m_22 + m_23*b.m_32,
                     m_20*b.m_03 + m_21*b.m_13 + m_22*b.m_23 + m_23*b.m_33,
                     m_30*b.m_00 + m_31*b.m_10 + m_32*b.m_20 + m_33*b.m_30,
                     m_30*b.m_01 + m_31*b.m_11 + m_32*b.m_21 + m_33*b.m_31,
                     m_30*b.m_02 + m_31*b.m_12 + m_32*b.m_22 + m_33*b.m_32,
                     m_30*b.m_03 + m_31*b.m_13 + m_32*b.m_23 + m_33*b.m_33);
}

// friend
C3dVector C3dMatrix::operator * (const C3dVector& v)
{
	C3dVector r;
	r.x = m_00 * v.x + m_01 * v.y + m_02 * v.z + m_30;
	r.y = m_10 * v.x + m_11 * v.y + m_12 * v.z + m_31;
	r.z = m_20 * v.x + m_21 * v.y + m_22 * v.z + m_32;
	return r;
}

C3dMatrix& C3dMatrix::operator *= (const C3dMatrix& r)
{
    // deliberately create a temp to hold result
    *this = *this * r;
    return *this;
}
                      
// rotate n degrees about each axis
void C3dMatrix::Rotate(double rx, double ry, double rz)
{
  double sinx = sin(rx*D2R) ;
	double cosx = cos(rx*D2R);
  double siny = sin(ry*D2R);
	double cosy = cos(ry*D2R);
  double sinz = sin(rz*D2R) ;
	double cosz = cos(rz*D2R) ;

	C3dMatrix mx(1, 0,     0,    0,
                 0,  cosx, -sinx, 0,
                 0, sinx, cosx, 0,
                 0, 0,     0,    1);

    C3dMatrix my(cosy, 0, siny, 0,
                 0,    1, 0,     0,
                 -siny, 0,  cosy, 0,
                 0,    0, 0,     1);

    C3dMatrix mz( cosz, -sinz, 0, 0,
                 sinz, cosz, 0, 0,
                 0,     0,    1, 0,
                 0,     0,    0, 1);

    *this *= mx * my * mz;
}




void C3dMatrix::Translate(double dx, double dy, double dz)
{
    C3dMatrix tx( 1, 0,  0, 0,
                  0, 1,  0, 0,
                  0, 0,  1, 0,
                 dx, dy, dz,1);

    *this *= tx;
}

void C3dMatrix::Translate2(double dx, double dy, double dz)
{

m_30 =dx;
m_31 =dy;
m_32 =dz;
}

void C3dMatrix::Scale(double sx, double sy, double sz)
{
    C3dMatrix tx(sx,  0,  0, 0,
                  0, sy,  0, 0,
                  0,  0, sz, 0,
                  0,  0,  0, 1);

    *this *= tx;
}

void C3dMatrix::MakeUnit()
{
    m_00=1.0; m_01=0.0;  m_02=0.0; m_03=0.0;
    m_10=0.0; m_11=1.0;  m_12=0.0; m_13=0.0;
    m_20=0.0; m_21=0.0;  m_22=1.0; m_23=0.0;
    m_30=0.0; m_31=0.0;  m_32=0.0; m_33=1.0;
}

OglMat C3dMatrix::GetOglMat()
{
OglMat retMat;
retMat.fMat[0] =(float) m_00;
retMat.fMat[1] =(float) m_10;
retMat.fMat[2] =(float) m_20;
retMat.fMat[3] =(float) m_03;

retMat.fMat[4] =(float) m_01;
retMat.fMat[5] =(float) m_11;
retMat.fMat[6] =(float) m_21;
retMat.fMat[7] =(float) m_13;

retMat.fMat[8] =(float) m_02;
retMat.fMat[9] =(float) m_12;
retMat.fMat[10] =(float) m_22;
retMat.fMat[11] =(float) m_23;

retMat.fMat[12] =(float) m_30;
retMat.fMat[13] =(float) m_31;
retMat.fMat[14] =(float) m_32;
retMat.fMat[15] =(float) m_33;


return (retMat);
}



C3dVector C3dMatrix::Mult(C3dVector vInVect)
{
C3dVector vRes;

vRes.x = m_00 * vInVect.x + m_01 * vInVect.y + m_02 * vInVect.z + m_30;
vRes.y = m_10 * vInVect.x + m_11 * vInVect.y + m_12 * vInVect.z + m_31;
vRes.z = m_20 * vInVect.x + m_21 * vInVect.y + m_22 * vInVect.z + m_32;

return (vRes);
}

C3dVector C3dMatrix::MultBack(C3dVector vInVect)
{
C3dVector vRes;
vInVect.x+=m_30;
vInVect.y+=m_31;
vInVect.z+=m_32;
vRes.x = m_00 * vInVect.x + m_01 * vInVect.y + m_02 * vInVect.z ;
vRes.y = m_10 * vInVect.x + m_11 * vInVect.y + m_12 * vInVect.z ;
vRes.z = m_20 * vInVect.x + m_21 * vInVect.y + m_22 * vInVect.z ;

return (vRes);
}

void C3dMatrix::Transpose() 
{ 
double dzz; 

dzz = m_01; 
m_01 = m_10; 
m_10 = dzz; 

dzz = m_02; 
m_02 = m_20; 
m_20 = dzz; 


dzz = m_12; 
m_12 = m_21; 
m_21 = dzz; 

} 

double C3dMatrix::det() 
{ 
return (m_00*m_11*m_22-m_00*m_12*m_21+m_01*m_12*m_20-m_01*m_10*m_22+m_02*m_10*m_21-m_02*m_11*m_20); 
} 

//NOT SURE THIS IS CORRECT VERSION
//SEE MFIX FOR NEW VERSION
C3dMatrix C3dMatrix::Inv() 
{ 
C3dMatrix InvMat; 
InvMat.MakeUnit(); 
double dDet; 
dDet = det(); 
printf("%s %13E\n","Determinant : ", dDet); 


InvMat.m_00 = (m_11*m_22-m_12*m_21) / dDet; 
InvMat.m_01 = -(m_10*m_22-m_12*m_20) / dDet; 
InvMat.m_02 = (m_10*m_21-m_11*m_20) / dDet; 

InvMat.m_10 = -(m_01*m_22-m_02*m_21) / dDet; 
InvMat.m_11 = (m_00*m_22-m_02*m_20) / dDet; 
InvMat.m_12 = -(m_00*m_21-m_01*m_20) / dDet; 

InvMat.m_20 = (m_01*m_12-m_02*m_11) / dDet; 
InvMat.m_21 = -(m_00*m_12-m_02*m_10) / dDet; 
InvMat.m_22= (m_00*m_11-m_01*m_10) / dDet; 

InvMat.Transpose(); 
InvMat.m_30 = -m_30; 
InvMat.m_31 = -m_31; 
InvMat.m_32 = -m_32; 
return (InvMat); 
} 

//*********************************************************************************
// Pre  : nodal normal 
// Post : returned geometic transformation
//        note only Z axis plane is orientated
//        new X,Y axis direction could point anywhere on plane
//*********************************************************************************

C3dMatrix C3dMatrix::CalcTran(C3dVector vIn)
{
double dX=0;
double dX1=0;
double dY=0;
double dY1=0;

C3dMatrix cMx;
C3dVector vTmp;
//Calculate  Y ang to rotate invec to
//Y-Z plain
double dd;
dd=vIn.x;
if (vIn.x==0) 
  {
	if (vIn.z<0)
	{
      dY1=180;
	}
  }
else
  {
  dY = atan2(vIn.x,vIn.z);
  dY1 = dY*360/(2*3.14159265359);
  }

cMx.MakeUnit();
cMx.Rotate(0,-dY1,0);
vTmp = cMx*vIn;
//Calculate  X ang to rotate invec to
//to Z axis
if  (vTmp.y == 0) 
  {
  
  }
else
  { 
  dX = atan2(vTmp.y,vTmp.z);
  dX1 = dX*360/(2*3.14159265359);
  }
cMx.MakeUnit();
// Calc the transfer matrix to
// align invec to global Z axiz
// Note the order of execution of
// the two rotations is important
cMx.Rotate(dX1,-dY1,0);
// We want the transformation togo the
// other way (Z to inec)
// The inv of a orthoganl matrix
// is simply the mat transposed
cMx.Transpose();
return (cMx);
}

C3dMatrix C3dMatrix::CalcTranVUP(C3dVector vDir,C3dVector vUp)
{
C3dVector vX;
C3dVector vY;
C3dMatrix TMat;
vDir.Normalize();
vUp.Normalize();
vX=vUp.Cross(vDir);
vX.Normalize();
vY=vDir.Cross(vX);
vY.Normalize();

TMat.SetColVec(1,vX);
TMat.SetColVec(2,vY);
TMat.SetColVec(3,vDir);
return (TMat);
}





void C3dMatrix::ClearTranslations()
{
m_03=0;
m_13=0;
m_23=0;
m_30=0;
m_31=0;
m_32=0;
m_33=0;
}

void C3dMatrix::ReverseZ()
{
 m_00=-m_00;
 m_10=-m_10;
 m_20=-m_20;

 m_02=-m_02;
 m_12=-m_12;
 m_22=-m_22;
}



double C3dMatrix::GetZRot(C3dMatrix mUp)
{
double dAng=0;
int i;
double dDotMax =0;
double dDot =0;
C3dMatrix RMat;
C3dVector vX;
C3dVector vY;
C3dVector vXt;
C3dVector vYt;
C3dVector vXd;
C3dVector vYd;
C3dVector  vUpX=mUp.GetColVec(1);
C3dVector  vUpY=mUp.GetColVec(2);
vX.x=1;vX.y=0;vX.z=0;
vY.x=0;vY.y=1;vY.z=0;
for (i=0;i<360;i++)
{
  RMat.MakeUnit();
  RMat.Rotate(0,0,i);
  vXt=RMat*vX;
  vYt=RMat*vY;
  vXt=Mult(vXt);
  vYt=Mult(vYt);
  dDot = vUpX.Dot(vXt);
  dDot = dDot +vUpY.Dot(vYt);
  if (dDot>dDotMax) 
  {
    dDotMax=dDot;
    dAng=i;
  }
}

double dotLast=0;
double dInc=0.25;
int iErr=0;
double dDir=1;
dotLast=dDot;
while (iErr<100)
{
  RMat.MakeUnit();
  RMat.Rotate(0,0,dAng);
  vXt=RMat*vX;
  vYt=RMat*vY;
  vXt=Mult(vXt);
  vYt=Mult(vYt);
  dDot = vUpX.Dot(vXt);
  dDot = dDot +vUpY.Dot(vYt);
  if (dDot>dotLast) 
  {
   
  }
  else
  {
    dDir=-1*dDir;
	dInc=dInc/2;
  }
  dotLast=dDot;
  dAng=dAng+dDir*dInc;
  iErr++;
}






return (dAng);
}

//Circumsphere to 4 points (TET)
//Returns Centre and Radius
void Circumsphere(C3dVector* v0, C3dVector* v1, C3dVector*  v2, C3dVector*  v3, C3dVector*  center, double* radius)
{
	//http://eastafricaschoolserver.org/Wikipedia/wp/t/Tetrahedron.htm
    //Create the rows of our "unrolled" 3x3 matrix
	//Create the rows of our "unrolled" 3x3 matrix
	C3dVector Row1;
	Row1.x = v1->x - v0->x; Row1.y = v1->y - v0->y; Row1.z = v1->z - v0->z;
	double sqLength1 = Row1.Mag();
	sqLength1 *= sqLength1;
	C3dVector Row2;
	Row2.x = v2->x - v0->x; Row2.y = v2->y - v0->y; Row2.z = v2->z - v0->z;
	double sqLength2 = Row2.Mag();
	sqLength2 *= sqLength2;
	C3dVector Row3;
	Row3.x = v3->x - v0->x; Row3.y = v3->y - v0->y; Row3.z = v3->z - v0->z;
	double sqLength3 = Row3.Mag();
	sqLength3 *= sqLength3;
	//Compute the determinant of said matrix
	const double determinant = 
		  Row1.x * (Row2.y * Row3.z - Row3.y * Row2.z)
		- Row2.x * (Row1.y * Row3.z - Row3.y * Row1.z)
		+ Row3.x * (Row1.y * Row2.z - Row2.y * Row1.z);

	// Compute the volume of the tetrahedron, and precompute a scalar quantity for re-use in the formula
	const double volume = determinant / 6.f;
	const double iTwelveVolume = 1.f / (volume * 12.f);

	center->x = v0->x + iTwelveVolume * ((Row2.y * Row3.z - Row3.y * Row2.z) * sqLength1 - (Row1.y * Row3.z - Row3.y * Row1.z) * sqLength2 + (Row1.y * Row2.z - Row2.y * Row1.z) * sqLength3);
	center->y = v0->y + iTwelveVolume * (-(Row2.x * Row3.z - Row3.x * Row2.z) * sqLength1 + (Row1.x * Row3.z - Row3.x * Row1.z) * sqLength2 - (Row1.x * Row2.z - Row2.x * Row1.z) * sqLength3);
	center->z = v0->z + iTwelveVolume * ((Row2.x * Row3.y - Row3.x * Row2.y) * sqLength1 - (Row1.x * Row3.y - Row3.x * Row1.y) * sqLength2 + (Row1.x * Row2.y - Row2.x * Row1.y) * sqLength3);

	//Once we know the center, the radius is clearly the distance to any vertex
	C3dVector A;
	A.x = center->x - v0->x;
	A.y = center->y - v0->y;
	A.z = center->z - v0->z;
	*radius = A.Mag();
}

double TetVolume(C3dVector* v0, C3dVector* v1, C3dVector*  v2, C3dVector*  v3)
{
	//Create the rows of our "unrolled" 3x3 matrix
	C3dVector Row1;
	Row1.x = v1->x - v0->x; Row1.y = v1->y - v0->y; Row1.z = v1->z - v0->z;
	C3dVector Row2;
	Row2.x = v2->x - v0->x; Row2.y = v2->y - v0->y; Row2.z = v2->z - v0->z;
	C3dVector Row3;
	Row3.x = v3->x - v0->x; Row3.y = v3->y - v0->y; Row3.z = v3->z - v0->z;
	//Compute the determinant of said matrix
	const double determinant =
		  Row1.x * (Row2.y * Row3.z - Row3.y * Row2.z)
		- Row2.x * (Row1.y * Row3.z - Row3.y * Row1.z)
		+ Row3.x * (Row1.y * Row2.z - Row2.y * Row1.z);

	// Compute the volume of the tetrahedron, and precompute a scalar quantity for re-use in the formula
	double volume = determinant / 6.f;
	return (volume);
}


void DSP_Triad::Create(double WPS)
{
//Origin
ds = 0.1*WPS;
vAxisPts[0].x = 0;
vAxisPts[0].y = 0;
vAxisPts[0].z = 0;
//x axis
vAxisPts[1].x = 1;
vAxisPts[1].y = 0;
vAxisPts[1].z = 0;

//y axis
vAxisPts[2].x = 0;
vAxisPts[2].y = 1;
vAxisPts[2].z = 0;

//z axis
vAxisPts[3].x = 0;
vAxisPts[3].y = 0;
vAxisPts[3].z = 1;
dSclFact = 1;

vEyePt.x=0;
vEyePt.y=0;
vEyePt.z=0;

//mOrientMat.MakeUnit;
}

void DSP_Triad::ReSet()
{
//Origin
vAxisPts[0].x = 0;
vAxisPts[0].y = 0;
vAxisPts[0].z = 0;
//x axis
vAxisPts[1].x = 1;
vAxisPts[1].y = 0;
vAxisPts[1].z = 0;

//y axis
vAxisPts[2].x = 0;
vAxisPts[2].y = 1;
vAxisPts[2].z = 0;

//z axis
vAxisPts[3].x = 0;
vAxisPts[3].y = 0;
vAxisPts[3].z = 1;
}


void  DSP_Triad::SetTopView()
{
  //Origin
  C3dMatrix mT;
  mT.MakeUnit();
  mT.Rotate(90, 0, 0);
  C3dVector vE;
  vE = mT.Mult(vEyePt);
  vAxisPts[0] = -vE;
  vAxisPts[1] = -vE;
  vAxisPts[2] = -vE;
  vAxisPts[3] = -vE;
  vAxisPts[0].x += 0;
  vAxisPts[0].y += 0;
  vAxisPts[0].z += 0;
  //x axis
  vAxisPts[1].x += 1;
  vAxisPts[1].y += 0;
  vAxisPts[1].z += 0;

  //y axis
  vAxisPts[2].x += 0;
  vAxisPts[2].y += 0;
  vAxisPts[2].z += 1;

  //z axis
  vAxisPts[3].x += 0;
  vAxisPts[3].y += -1;
  vAxisPts[3].z += 0;

}

void  DSP_Triad::SetLeftView()
{
  //Origin
  C3dMatrix mT;
  mT.MakeUnit();
  mT.Rotate(0,90, 0);
  C3dVector vE;
  vE = mT.Mult(vEyePt);
  vAxisPts[0] = -vE;
  vAxisPts[1] = -vE;
  vAxisPts[2] = -vE;
  vAxisPts[3] = -vE;
  vAxisPts[0].x += 0;
  vAxisPts[0].y += 0;
  vAxisPts[0].z += 0;
  //x axis
  vAxisPts[1].x += 0;
  vAxisPts[1].y += 0;
  vAxisPts[1].z += -1;
  //y axis
  vAxisPts[2].x += 0;
  vAxisPts[2].y += 1;
  vAxisPts[2].z += 0;
  //z axis
  vAxisPts[3].x += 1;
  vAxisPts[3].y += 0;
  vAxisPts[3].z += 0;
}

void  DSP_Triad::SetBackView()
{
  //Origin
  C3dMatrix mT;
  mT.MakeUnit();
  mT.Rotate(0, 180, 0);
  C3dVector vE;
  vE = mT.Mult(vEyePt);
  vAxisPts[0] = -vE;
  vAxisPts[1] = -vE;
  vAxisPts[2] = -vE;
  vAxisPts[3] = -vE;
  vAxisPts[0].x += 0;
  vAxisPts[0].y += 0;
  vAxisPts[0].z += 0;
  //x axis
  vAxisPts[1].x += -1;
  vAxisPts[1].y += 0;
  vAxisPts[1].z += 0;
  //y axis
  vAxisPts[2].x += 0;
  vAxisPts[2].y += 1;
  vAxisPts[2].z += 0;
  //z axis
  vAxisPts[3].x += 0;
  vAxisPts[3].y += 0;
  vAxisPts[3].z += -1;
}

void  DSP_Triad::SetRightView()
{
  //Origin
  C3dMatrix mT;
  mT.MakeUnit();
  mT.Rotate(0, -90, 0);
  C3dVector vE;
  vE = mT.Mult(vEyePt);
  vAxisPts[0] = -vE;
  vAxisPts[1] = -vE;
  vAxisPts[2] = -vE;
  vAxisPts[3] = -vE;
  vAxisPts[0].x += 0;
  vAxisPts[0].y += 0;
  vAxisPts[0].z += 0;
  //x axis
  vAxisPts[1].x += 0;
  vAxisPts[1].y += 0;
  vAxisPts[1].z += 1;
  //y axis
  vAxisPts[2].x += 0;
  vAxisPts[2].y += 1;
  vAxisPts[2].z += 0;
  //z axis
  vAxisPts[3].x += -1;
  vAxisPts[3].y += 0;
  vAxisPts[3].z += 0;
}

void  DSP_Triad::SetBottomView()
{
  //Origin
  C3dMatrix mT;
  mT.MakeUnit();
  mT.Rotate(-90, 0, 0);
  C3dVector vE;
  vE = mT.Mult(vEyePt);
  vAxisPts[0] = -vE;
  vAxisPts[1] = -vE;
  vAxisPts[2] = -vE;
  vAxisPts[3] = -vE;
  vAxisPts[0].x += 0;
  vAxisPts[0].y += 0;
  vAxisPts[0].z += 0;
  //x axis
  vAxisPts[1].x += 1;
  vAxisPts[1].y += 0;
  vAxisPts[1].z += 0;
  //y axis
  vAxisPts[2].x += 0;
  vAxisPts[2].y += 0;
  vAxisPts[2].z += -1;
  //z axis
  vAxisPts[3].x += 0;
  vAxisPts[3].y += 1;
  vAxisPts[3].z += 0;
}

void  DSP_Triad::SetVIEW(C3dMatrix mT)
{
  //Origin
  C3dVector vE;
  mT.m_30 = 0;
  mT.m_31 = 0;
  mT.m_32 = 0;
  mT.Transpose();
  vE = mT.Mult(vEyePt);
  vAxisPts[0] = -vE;
  vAxisPts[1] = -vE;
  vAxisPts[2] = -vE;
  vAxisPts[3] = -vE;

  vAxisPts[0].x += 0;
  vAxisPts[0].y += 0;
  vAxisPts[0].z += 0;
  //x axis
  vAxisPts[1].x += mT.m_00;
  vAxisPts[1].y += mT.m_10;
  vAxisPts[1].z += mT.m_20;
  //y axis
  vAxisPts[2].x += mT.m_01;
  vAxisPts[2].y += mT.m_11;
  vAxisPts[2].z += mT.m_21;
  //z axis
  vAxisPts[3].x += mT.m_02;
  vAxisPts[3].y += mT.m_12;
  vAxisPts[3].z += mT.m_22;
}


void  DSP_Triad::SetFrontView()
{
  //Origin
  vAxisPts[0] = -vEyePt;
  vAxisPts[1] = -vEyePt;
  vAxisPts[2] = -vEyePt;
  vAxisPts[3] = -vEyePt;

  vAxisPts[0].x += 0;
  vAxisPts[0].y += 0;
  vAxisPts[0].z += 0;
  //x axis
  vAxisPts[1].x += 1;
  vAxisPts[1].y += 0;
  vAxisPts[1].z += 0;
  //y axis
  vAxisPts[2].x += 0;
  vAxisPts[2].y += 1;
  vAxisPts[2].z += 0;
  //z axis
  vAxisPts[3].x += 0;
  vAxisPts[3].y += 0;
  vAxisPts[3].z += 1;
}


void DSP_Triad::ReSet2()
{

}

void DSP_Triad::Draw(CDC* pDC,C3dMatrix pMod,C3dMatrix pScrTran)
{
//C3dVector vDspPts[4];
//C3dVector vAxisDsp[4];

//vAxisDsp[0].x = 0;
//vAxisDsp[0].y = 0;
//vAxisDsp[0].z = 0;
//x axis
//vAxisDsp[1].x = ds*1;
//vAxisDsp[1].y = 0;
//vAxisDsp[1].z = 0;

//y axis
//vAxisDsp[2].x = 0;
//vAxisDsp[2].y = ds*1;
//vAxisDsp[2].z = 0;

//z axis
//vAxisDsp[3].x = 0;
//vAxisDsp[3].y = 0;
//vAxisDsp[3].z = ds*1;

//vDspPts[0] = pMod.Mult(vAxisDsp[0]);
//vDspPts[1] = pMod.Mult(vAxisDsp[1]);
//vDspPts[2] = pMod.Mult(vAxisDsp[2]);
//vDspPts[3] = pMod.Mult(vAxisDsp[3]);

//vDspPts[0] = pScrTran.Mult(vDspPts[0]);
//vDspPts[1] = pScrTran.Mult(vDspPts[1]);
//vDspPts[2] = pScrTran.Mult(vDspPts[2]);
//vDspPts[3] = pScrTran.Mult(vDspPts[3]);

//pDC->MoveTo((int) vDspPts[0].x,(int) vDspPts[0].y);
//pDC->LineTo((int) vDspPts[1].x,(int) vDspPts[1].y);

//pDC->MoveTo((int) vDspPts[0].x,(int) vDspPts[0].y);
//pDC->LineTo((int) vDspPts[2].x,(int) vDspPts[2].y);
//pDC->SetBkMode(TRANSPARENT);
//COLORREF fco = 0x00FF00FF;
//pDC->SetTextColor(fco);

//CString OutT;
//OutT = "x";
//pDC->TextOut((int) vDspPts[1].x,(int) vDspPts[1].y,OutT);
//OutT = "y";
//pDC->TextOut((int) vDspPts[2].x,(int) vDspPts[2].y,OutT);
//OutT = "z";

//pDC->TextOut((int) vDspPts[3].x,(int) vDspPts[3].y,OutT);
//pDC->MoveTo((int) vDspPts[0].x,(int) vDspPts[0].y);
//pDC->LineTo((int) vDspPts[3].x,(int) vDspPts[3].y);
}


void DSP_Triad::SetEye(double x,double y ,double z)
{
///Trans(-vAxisPts[0].x*dSclFact,-vAxisPts[0].y*dSclFact,-vAxisPts[0].z*dSclFact);
//Trans(-x*dSclFact,-y*dSclFact,-z*dSclFact);
vEyePt.x =x;
vEyePt.y =y;
vEyePt.z =z;
ReSet();
vAxisPts[0]-=vEyePt;
vAxisPts[1]-=vEyePt;
vAxisPts[2]-=vEyePt;
vAxisPts[3]-=vEyePt;
}






void DSP_Triad::Rot(float fAx,float fAy,float fAz)
{
C3dMatrix mTemp;
C3dVector vTemp;

mTemp.MakeUnit();
mTemp.Rotate (fAx,fAy,fAz);
vTemp = mTemp*vAxisPts[0];
vAxisPts[0] = vTemp;
vTemp = mTemp*vAxisPts[1];
vAxisPts[1] = vTemp;
vTemp = mTemp*vAxisPts[2];
vAxisPts[2] = vTemp;
vTemp = mTemp*vAxisPts[3];
vAxisPts[3] = vTemp;

}


void DSP_Triad::ApplyTransform(C3dMatrix mInMat)
{
C3dMatrix mTemp;
C3dVector vTempA;


vTempA = mInMat*vAxisPts[0];
vAxisPts[0] = vTempA;

vTempA = mInMat*vAxisPts[1];
vAxisPts[1] = vTempA;

vTempA = mInMat*vAxisPts[2];
vAxisPts[2] = vTempA;

vTempA = mInMat*vAxisPts[3];
vAxisPts[3] = vTempA;

}

void DSP_Triad::Trans(double dX,double dY,double dZ)
{
C3dMatrix mInt;
C3dMatrix mTemp;
C3dVector vTemp;
mTemp.MakeUnit();
mTemp.Translate (dX/dSclFact,dY/dSclFact,dZ/dSclFact);
vTemp = mTemp*vAxisPts[0];
vAxisPts[0] = vTemp;
vTemp = mTemp*vAxisPts[1];
vAxisPts[1] = vTemp;
vTemp = mTemp*vAxisPts[2];
vAxisPts[2] = vTemp;
vTemp = mTemp*vAxisPts[3];
vAxisPts[3] = vTemp;

}


void DSP_Triad::Scl(double dSfactInc)
{
dSclFact = dSclFact + dSfactInc;
if (dSclFact < 0) 
   {dSclFact = 0.001;}
else if (dSclFact > 50000) 
  {dSclFact = 50000;}

}

double DSP_Triad::GetScl()
{
return (dSclFact);
}


C3dMatrix DSP_Triad::RetrieveMat()
{
C3dMatrix mTr;
C3dMatrix mTp;
C3dMatrix mSc;
C3dMatrix mRot;
C3dVector vTr;
//move points to origin;
vTr.x = 0-vAxisPts[0].x;
vTr.y = 0-vAxisPts[0].y;
vTr.z = 0-vAxisPts[0].z;
mTr.MakeUnit();
mTr.Translate(vTr.x,vTr.y,vTr.z);
ApplyTransform(mTr);
mOrientMat.MakeUnit();
mOrientMat.Translate(-vTr.x,-vTr.y,-vTr.z);
mOrientMat.m_00 = vAxisPts[1].x;
mOrientMat.m_10 = vAxisPts[1].y;
mOrientMat.m_20 = vAxisPts[1].z;

mOrientMat.m_01 = vAxisPts[2].x;
mOrientMat.m_11 = vAxisPts[2].y;
mOrientMat.m_21 = vAxisPts[2].z;

mOrientMat.m_02 = vAxisPts[3].x;
mOrientMat.m_12 = vAxisPts[3].y;
mOrientMat.m_22 = vAxisPts[3].z;

ReSet();
ApplyTransform(mOrientMat);
mOrientMat.Scale(dSclFact,dSclFact,dSclFact);

return (mOrientMat);
}

void DSP_Triad::PushMat(C3dMatrix mT)
{
	C3dVector vS;
	double dS;
	double dS2;
	vS.x = mT.m_00;
	vS.y = mT.m_10;
	vS.z = mT.m_20;
	dS = vS.Mag();
	vS.x = mT.m_01;
	vS.y = mT.m_11;
	vS.z = mT.m_21;
	dS2 = vS.Mag();

	//dSclFact = mT.m_00;
	dSclFact = dS;
	mT.Scale(1 / dSclFact, 1 / dSclFact, 1 / dSclFact);

	vAxisPts[0].x = mT.m_30;
	vAxisPts[0].y = mT.m_31;
	vAxisPts[0].z = mT.m_32;

	vAxisPts[1].x= mT.m_00;
	vAxisPts[1].y= mT.m_10;
	vAxisPts[1].z= mT.m_20;
	vAxisPts[1] += vAxisPts[0];

	vAxisPts[2].x = mT.m_01;
	vAxisPts[2].y = mT.m_11;
	vAxisPts[2].z = mT.m_21;
	vAxisPts[2] += vAxisPts[0];

	vAxisPts[3].x = mT.m_02;
	vAxisPts[3].y = mT.m_12;
	vAxisPts[3].z = mT.m_22;
	vAxisPts[3] += vAxisPts[0];

}


Mat::Mat()
{
v=NULL;
m=0;
n=0;
}

Mat::Mat(const Mat &b)
{
int i;
m=b.m;
n=b.n;
v = new double[m*n];
for (i=0;i<m*n;i++)
{
  v[i]=b.v[i];
}
}

Mat::Mat(int r,int c)
{
int i;
v= new double[r*c];
m=r;
n=c;
for(i=0;i<m*n;i++)
{
  v[i]=0;
}
}

void Mat::Create(int r,int c)
{
int i;
v= new double[r*c];
m=r;
n=c;
for(i=0;i<m*n;i++)
{
  v[i]=0;
}
}

Mat::~Mat()
{
if (v!=NULL)
{
  delete [] v;
  v=NULL;
  m=0;
  n=0;
}
}

void Mat::clear()
{
if (v!=NULL)
{
  delete [] v;
  v=NULL;
  m=0;
  n=0;
}
}

void Mat::MakeUpperTri()
{
int i,j;
for(i=2;i<n+1;i++)
{
  for(j=1;j<i;j++)
  {
    *mn(i,j)=0; 
  }
}
}

BOOL Mat::isSym()
{
int i,j;
BOOL brc=TRUE;
for(i=2;i<n+1;i++)
{
  for(j=1;j<i;j++)
  {
    if (*mn(i,j) != *mn(j,i))
	{
      brc=FALSE;
	}
  }
}
return (brc);
}

void Mat::MakeZero(){
int i;
for (i=0;i<m*n;i++)
{
  v[i]=0;
}
}

void Mat::MakeUnit()
{
int i;
if (m==n)
{
  for(i=1;i<m+1;i++)
  {
    *mn(i,i)=1;
  }
}
}

void Mat::Transpose()
{
int i;
int j;
int iN=0;


if ((m>0) && (n>0))
{
  double *Temp = new double[m*n];
  for(j=1;j<n+1;j++)
  {
    for(i=1;i<m+1;i++)
    {
      Temp[iN]=*mn(i,j);
	  iN++;
    }
  }
delete [] v;
v=Temp;
Temp=NULL;
iN=m;m=n;n=iN;
}
}

int Mat::Invert()
{
int irc=-1;
int i,j,k;
double con;
if (m==n)
{
for (k=1;k<m+1;k++)
{
  con = *mn(k, k);
  *mn(k, k) = 1;
  for(j=1;j<m+1;j++)
  {
    *mn(k, j) /= con;
  }
  for(i=1;i<m+1;i++)
  {
    if (i!=k)
	{
      con = *mn(i, k);
      *mn(i, k) = 0;
      for(j=1;j<m+1;j++)
	  {
        *mn(i, j) = *mn(i, j) - *mn(k, j) * con;
      }
    }
  }
}
}
return (irc);
}

Mat Mat::InvertJac(double &det)
{
Mat invjac(m,n);
if (m==1)
{
  det =1;
  *invjac.mn(1,1)=det/(*mn(1,1));
}
else if (m==2)
{
  det =*mn(1,1)**mn(2,2)-*mn(1,2)**mn(2,1);
  *invjac.mn(1,1)=*mn(2,2)/det;
  *invjac.mn(2,2)=*mn(1,1)/det;
  *invjac.mn(1,2)=-*mn(1,2)/det;
  *invjac.mn(2,1)=-*mn(2,1)/det;
}
else if (m==3)
{
  det = *mn(1, 1) * (*mn(2, 2) * *mn(3, 3) - *mn(2, 3) * *mn(3, 2));
  det = det - *mn(1, 2) * (*mn(2, 1) * *mn(3, 3) - *mn(2, 3) * *mn(3, 1));
  det = det + *mn(1, 3) * (*mn(2, 1) * *mn(3, 2) - *mn(2, 2) * *mn(3, 1));
  *invjac.mn(1,1) = (*mn(2, 2) * *mn(3, 3) - *mn(2, 3) * *mn(3, 2)) / det;
  *invjac.mn(2,1) = -(*mn(2, 1) * *mn(3, 3) - *mn(2, 3) * *mn(3, 1)) / det;
  *invjac.mn(3,1) = (*mn(2, 1) * *mn(3, 2) - *mn(2, 2) * *mn(3, 1)) / det;
  *invjac.mn(1,2) = -(*mn(1, 2) * *mn(3, 3) - *mn(1, 3) * *mn(3, 2)) / det;
  *invjac.mn(2,2) = (*mn(1, 1) * *mn(3, 3) - *mn(1, 3) * *mn(3, 1)) / det;
  *invjac.mn(3,2) = -(*mn(1, 1) * *mn(3, 2) - *mn(1, 2) * *mn(3, 1)) / det;
  *invjac.mn(1,3) = (*mn(1, 2) * *mn(2, 3) - *mn(1, 3) * *mn(2, 2)) / det;
  *invjac.mn(2,3) = -(*mn(1, 1) * *mn(2, 3) - *mn(1, 3) * *mn(2, 1)) / det;
  *invjac.mn(3,3) = (*mn(1, 1) * *mn(2, 2) - *mn(1, 2) * *mn(2, 1)) / det;
}
return (invjac);


}


double Mat::GetV(int r,int c)
{
  
	if ((r <= m) && (c <= n))
      return(v[(r-1)*n+c-1]);
}


double* Mat::mn(int r,int c)
{
double* drc=NULL;
int i;

if ((r*c<=m*n) && (r>0) && (c>0))
{
  i=(r-1)*n+c-1;
  drc=&v[i];
}
return(drc);
}


double* Mat::mn2(int r,int c)
{
double* drc=NULL;
int i;
if (r*c<=m*n) 
{
  i=r*n+c;
  drc=&v[i];
}
return(drc);
}



void Mat::diag()
{
FILE* pFile;
int i;
int j;
pFile = fopen("C:/SCRATCH/MIN3/MAT_DIAG_MIN3.txt","w");

fprintf(pFile,"%s\n","MATRIX");
fprintf(pFile,"%s%i%s%i\n","M",m,"N",n);

for (i=0;i<m;i++)
{
  for (j=0;j<n;j++)
  {
  fprintf(pFile,"%g,",*mn(i+1,j+1));
  }
fprintf(pFile,"\n");
}
fclose(pFile);
}



Mat& Mat::operator += (const Mat& r)
{
int i;
if ((m==r.m) && (n==r.n))
{
  for (i=0;i<m*n;i++)
  {
    v[i]+=r.v[i];
  }
}
return *this;
}

Mat Mat::operator * (Mat& r)
{
Mat rc(m,r.n);
int i,j,k;
double sum;
if ((n==r.m))
{

for (i = 1;i<m+1;i++)
{
  for(j = 1;j<r.n+1;j++)
  {
    sum = 0;
    for (k = 1;k<n+1; k++)
    {
     sum = sum + *mn(i, k) * r.GetV(k, j);
    }
    *rc.mn(i, j) = sum;
  }
}
}
return(rc);
}


Mat& Mat::operator -= (const Mat& r)
{
int i;
if ((m==r.m) && (n==r.n))
{
  for (i=0;i<m*n;i++)
  {
    v[i]-=r.v[i];
  }
}
return *this;
}

Mat& Mat::operator = (const Mat& r)
{
int i;
m=r.m;
n=r.n;
if (v!=NULL)
{
delete[] v;
}
v = new double[m*n];
for (i=0;i<m*n;i++)
{
  v[i]=r.v[i];
}
return *this;
}



Mat& Mat::operator *= (const double r)
{
int i;
for (i=0;i<m*n;i++)
{
  v[i]*=r;
}
return *this;
}

double Mat::Det()
{
double determ;
if (n==1)
{
  determ = 1;
}
else if (n==2)
{
  determ = *mn(1, 1) * *mn(2, 2) - *mn(1, 2) * *mn(2, 1);
}
else if (n==3)
{
  determ = *mn(1, 1) * (*mn(2, 2) * *mn(3, 3) - *mn(3, 2) * *mn(2, 3));
  determ = determ - *mn(1, 2) * (*mn(2, 1) * *mn(3, 3) - *mn(3, 1) * *mn(2, 3));
  determ = determ + *mn(1, 3) * (*mn(2, 1) * *mn(3, 2) - *mn(3, 1) * *mn(2, 2));
}
else
{
  determ=Det2();
}

return(determ);
}

double Mat::Det2()
{
Mat Matrix(*this);
int k, k1, i, j;
double save;
double deter;
int Norder = Matrix.n;

BOOL check;
deter = 1;

for (k=1;k<Norder+1;k++)
{
 if (*Matrix.mn(k, k) == 0)
 {
  j = k;
  do
  {
   check = TRUE;
   if (*Matrix.mn(k, j) == 0)
   {
    if (j == Norder)
	{
     deter = 0;
     goto fend;
    }
    check = FALSE;
    j++;
   }
   if (*Matrix.mn(k, j) != 0)
   {
    for (i=k;i<Norder+1;i++)
	{
     save = *Matrix.mn(i, j);
     *Matrix.mn(i, j) = *Matrix.mn(i, k);
     *Matrix.mn(i, k) = save;
    }
    deter = -deter;
   }
  }
  while (check == FALSE);
 }


 deter = deter * *Matrix.mn(k, k);
 if (k - Norder < 0)
 {
  k1 = k + 1;
  for (i = k1;i<Norder+1;i++)
  {
   for (j = k1;j<Norder+1;j++)
   {
    *Matrix.mn(i, j) = *Matrix.mn(i, j) - (*Matrix.mn(i, k) * *Matrix.mn(k, j) / *Matrix.mn(k, k));
   }
  }
 }
}

fend:;
Matrix.clear();
return(deter);
}

//*******************************************************
//Cholesky decomposition
//Pre:is positive definate symmetic matrix
//Post: matrix L, such that that this = L.Transpose*L     
//*******************************************************
Mat Mat::Cholesky()
{
double V,AJJ;
int i,j,k;
Mat L;
L=*this;
for (j=1;j<n+1;j++)
{
  V=0.0;
  for (k=1;k<j;k++)
  {
    V=V+*L.mn(k,j)**L.mn(k,j);
  }
  AJJ = *L.mn(j,j)-V;
  if (AJJ<=0)
  {	  
    goto fend;
  }
  AJJ=pow(AJJ,0.5);
  *L.mn(j,j) = AJJ;
  if (j<n)
  {
    for (i=j+1;i<n+1;i++)
	{
       V=0.0;
       for (k=1;k<j;k++) 
	   {
         V=V+*L.mn(k,i)**L.mn(k,j);
       }
       *L.mn(j,i)=*L.mn(j,i)-V;
    }
    V=1/AJJ;
    for (k=j+1;k<n+1;k++)
	{
       *L.mn(j,k)=V**L.mn(j,k);
    }
  }
}
fend:;
return (L);
}

