//#include "stdafx.h"
#define D3DVAL(val) ((float)(val))
typedef float D3DVALUE, *LPD3DVALUE;

typedef D3DVALUE D3DRMMATRIX4D[4][4];
#define DEFAULT_ALLOC 2

typedef struct OglMat
{
float fMat[16];  
} OglMat;

// COMMENTED OUT IN VS2017 AS GET TYPE REDEFINITION????????

//typedef struct _D3DVECTOR {
//    union {
//        D3DVALUE x;
//        D3DVALUE dvX;
//    };
//    union {
//        D3DVALUE y;
//        D3DVALUE dvY;
//    };
//    union {
//        D3DVALUE z;
//        D3DVALUE dvZ;
//    };
//} D3DVECTOR, *LPD3DVECTOR;
//
//typedef struct _D3DMATRIX {
//    D3DVALUE        _11, _12, _13, _14;
//    D3DVALUE        _21, _22, _23, _24;
//    D3DVALUE        _31, _32, _33, _34;
//    D3DVALUE        _41, _42, _43, _44;
//} D3DMATRIX, *LPD3DMATRIX;

class Mat;
class C3dMatrix;
class C3dVector

{
public:
  double x,y,z;
  C3dVector();
  ~C3dVector();
  //C3dVector(const D3DVECTOR& r);
  C3dVector(double x, double y, double z);
  virtual void Serialize(CArchive& ar,int iV);
  void Set(double x, double y, double z);
  BOOL operator == (const C3dVector r);
  C3dVector operator = (const C3dVector r);
  C3dVector operator = (const C3dVector* r);
  C3dVector operator = (const double r);
  C3dVector operator + (const C3dVector b);
  C3dVector operator - (const C3dVector b);
  C3dVector& operator += (const C3dVector& r);
  //friend C3dVector operator - (const C3dVector& a, const C3dVector& b);
  C3dVector& operator -= (const C3dVector& r);
  //C3dVector operator * (const C3dVector& a, const C3dVector& b);
  C3dVector& operator *= (const C3dVector& r);
  C3dVector operator * (const double s);
  C3dVector& operator *= (const double s);
  C3dVector& operator /= (const double s);
  C3dVector operator - ();
  double Ang(const C3dVector& r);
  double AngSigned(C3dVector r, C3dVector vN);
  double Dot(const C3dVector& a);
  double Mag();
  C3dVector Cross(C3dVector vIn);
  BOOL Normalize();
  BOOL Coincident(const C3dVector& r);
  C3dVector GenerateUp();
  C3dMatrix GetTMat();
  void Rotate(C3dVector vA1,C3dVector vA2,double dAng);
  void Translate (C3dVector vIn);
  BOOL IsNull();
  double Dist(C3dVector inPt);
  C3dVector& TGet();
  void SetToScr(C3dMatrix* pModMat,C3dMatrix* pScrTran);
};

//Class C3dVector written for 2d parametric mesh generation
class C2dVector

{// 2d Vector 
public:
	double x, y;
	C2dVector();
	~C2dVector();
	C2dVector(double x, double y);
	C2dVector operator = (const C2dVector r);
	C2dVector operator = (const C2dVector* r);
	C2dVector operator = (const double r);
	BOOL operator == (const C2dVector r);
	C2dVector operator + (const C2dVector b);
	C2dVector operator - (const C2dVector b);
	C2dVector& operator += (const C2dVector& r);
	C2dVector& operator -= (const C2dVector& r);
	C2dVector& operator *= (const double s);
	double Cross(C2dVector vIn);
	double Dot(C2dVector vIn);
	void Clamp(double dMin, double dMax);
	double Dist(C2dVector inV);
	BOOL Normalize();
	double Mag();
};

class C4dVector

{
public:
	double xw,yw,zw,w;
  C4dVector();
  ~C4dVector();
  C4dVector(double dx, double dy, double dz, double dw);
  C4dVector operator = (const C4dVector r);
  C4dVector operator = (const double r);
  C4dVector operator + (const C4dVector b);
  C4dVector operator * (const double s);
  virtual void Serialize(CArchive& ar,int iV);
  void Translate(C3dVector vS);
  C3dVector GetPoint();
  double GetWght();
  void Transform(C3dMatrix TMat);
  void Clear();
};









template <class T>
class Vec 
{
public:
T* v;
int n; //Cols
Vec();
Vec(int c);
~Vec();
Vec(const Vec<T> &b);
void clear();
void Zero();
T* nn(int c);
void Size(int in);
void diag();
void ReOrder(int iSt);

Vec<T>& operator = (const Vec<T>& r);
Vec<T>& operator += (const Vec<T>& r);
Vec<T>& operator -= (const Vec<T>& r);

Vec<T> operator * (Mat& r);
T& elem(const int i); 
T  elem(const int i) const; 

T& operator()(const int i)  
    { return elem(i); } 

T  operator()(const int i) const 
    { return elem(i); } 

T& operator[](const int i)  
    { return elem(i); } 

T  operator[](const int i) const 
    { return elem(i); } 
void DeleteAll()
{clear();}
};



template <class T>
Vec<T> Vec<T>::operator * (Mat& r)
{
Vec rc(r.m);
int i,j;
double sum;
if ((r.n==n))
{

for (i = 1;i<r.m+1;i++)
{
  sum=0;
  for(j = 1;j<r.n+1;j++)
  {
    sum = sum + *r.mn(i, j) * *nn(j);
  }
  *rc.nn(i) = sum;
}
}
return(rc);
}

template <class T>
Vec<T>::Vec()
{
v=NULL;
n=0;
}

template <class T>
Vec<T>::Vec(const Vec<T> &b)
{
int i;
n=b.n;
v = new T[n];
for (i=0;i<n;i++)
{
  v[i]=b.v[i];
}
}

template <class T>
void Vec<T>::Size(int in)
{

if (v!=NULL)
{
  delete [] v;
  v=NULL;
  n=0;

}
n=in;
v= new T[in];
}

template <class T>
Vec<T>::Vec(int c)
{
int i;
v= new T[c];
n=c;
for(i=0;i<n;i++)
{
  v[i]=0;
}
}

//template <>
//Vec<C4dVector>::Vec(int c)
//{
//int i;
//v= new C4dVector[c];
//n=c;
//for(i=0;i<n;i++)
//{
//  v[i].Clear();
//}
//}

template <class T>
Vec<T>::~Vec()
{
if (v!=NULL)
{
  delete [] v;
  v=NULL;
  n=0;
}
}


template <class T>
void Vec<T>::clear()
{
if (v!=NULL)
{
  delete [] v;
  v=NULL;
  n=0;
}
}


template <class T>
void Vec<T>::Zero()
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (v != NULL)
		  v[i] = 0;
	}
}

template <class T>
void Vec<T>::ReOrder(int iSt)
{
	int i;
	int a, b;

	Vec<T> copy(n);
	for (i = 0; i < n; i++)
	{
		copy.v[i] = v[i];
	}
	int iCnt = 0;
	for (i = iSt; i < n; i++)
	{
		v[iCnt] = copy.v[i];
		iCnt++;
	}
	for (i = 0; i < iSt; i++)
	{
		v[iCnt] =  copy.v[i];
		iCnt++;
	}
}

template <class T>
T* Vec<T>::nn(int c)
{
T* drc=NULL;
if ((c>0)&&(c<=n))
{
  drc=&v[c-1];
}
return(drc);
}

template <class T>
T& Vec<T>::elem(const int i)
{
  return v[i];
}

template <class T>
T Vec<T>::elem(const int i) const
{
  return v[i];
}

template <class T>
Vec<T>& Vec<T>::operator = (const Vec<T>& r)
{
int i;
n=r.n;
if (v!=NULL)
{
delete[] v;
}
v = new T[n];
for (i=0;i<n;i++)
{
  v[i]=r.v[i];
}
return *this;
}

template <class T>
void Vec<T>::diag()
{
FILE* pFile;
int j;
pFile = fopen("C:/SCRATCH/MIN3/VEC_DIAG.txt","w");

fprintf(pFile,"%s\n","VECTOR");
fprintf(pFile,"%s%i\n","N",n);

for (j=0;j<n;j++)
{
  fprintf(pFile,"%g",*nn(j+1));
  fprintf(pFile,"\n","");
}
fclose(pFile);
}



template <class T>
Vec<T>& Vec<T>::operator += (const Vec<T>& r)
{
int i;
if (n==r.n)
{
  for (i=0;i<n;i++)
  {
    v[i]+=r.v[i];
  }
}
return *this;
}

template <class T>
Vec<T>& Vec<T>::operator -= (const Vec<T>& r)
{
int i;
if (n==r.n)
{
  for (i=0;i<n;i++)
  {
    v[i]-=r.v[i];
  }
}
return *this;
}
//
//

template <class T>
class Matrix 
{
public:
T* v;
int m; //Cols
int n; //Cols
Matrix();
Matrix(int im,int in);
void Size(int im,int in);
~Matrix();
void diag();
T* mn(int r,int c);
T& elem(const int i,const int j);  // returns an error message if the index is out of range
T  elem(const int i,const int j) const; 
T& operator()(const int i,const int j)  //!< calls elem(i,j)   
    { return elem(i,j); } 
T  operator()(const int i,const int j) const //!< calls elem(i,j)
    { return elem(i,j); } 
Matrix<T>& operator = (const Matrix<T>& r);
void Matrix<T>::Mult (Matrix<T>& r,Matrix<T>& rc);
void DeleteAll();
void Invert();
//Vec(const Vec<T> &b);
//void clear();
//T* nn(int c);
//void diag();
//Vec<T>& operator = (const Vec<T>& r);
//Vec<T>& operator += (const Vec<T>& r);
//Vec<T>& operator -= (const Vec<T>& r);
//Vec<T> operator * (Mat& r);
};

template <class T>
void Matrix<T>::diag()
{
FILE* pFile;
CFileDialog FDia(FALSE,"txt", "*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
pFile = fopen(sPath,"w");

int j;
int i;
fprintf(pFile,"%s\n","MAT");
fprintf(pFile,"%s%i%s%i\n","M",m,"n",n);

for (i=0;i<m;i++)
{
  for (j=0;j<n;j++)
  {
    fprintf(pFile,"%8s",f4(elem(i,j)));  
  }
  fprintf(pFile,"\n","");
}
fclose(pFile);
}



template <class T>
Matrix<T>::~Matrix()
{

if (v!=NULL)
{
  delete [] v;
  v=NULL;
  n=0;
  m=0;
}
}

template <class T>
void Matrix<T>::DeleteAll()
{
if (v!=NULL)
{
  delete [] v;
  v=NULL;
  n=0;
  m=0;
}
}



template <class T>
Matrix<T>::Matrix()
{
v=NULL;
n=0;
m=0;
}


template <class T>
Matrix<T>::Matrix(int im,int in)
{
m=im;
n=in;
v= new T[m*n];
}


template <class T>
void Matrix<T>::Size(int im,int in)
{

if (v!=NULL)
{
  delete [] v;
  v=NULL;
  n=0;
  m=0;
}
m=im;
n=in;
v= new T[m*n];
}

template <class T>
T* Matrix<T>::mn(int r,int c)
{
T* drc=NULL;
int i;
if (r*c<=m*n) 
{
  i=(r)*n+c;
  drc=&v[i];
}
return(drc);
}

template <class T>
T& Matrix<T>::elem(const int i,const int j)
{
  return v[i*n+j];
}

template <class T>
T Matrix<T>::elem(const int i,const int j) const
{
  return v[i*n+j];
}

template <class T>
void Matrix<T>::Invert()
{
int irc=-1;
int i,j,k;
double con;
if (m==n)
{
for (k=0;k<m;k++)
{
  con = elem(k, k);
  *mn(k, k) = 1;
  for(j=0;j<m;j++)
  {
    elem(k, j) /= con;
  }
  for(i=0;i<m;i++)
  {
    if (i!=k)
	{
      con = elem(i, k);
      elem(i, k) = 0;
      for(j=0;j<m;j++)
	    {
        elem(i, j) = elem(i, j) - elem(k, j) * con;
      }
    }
  }
}
}
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& r)
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

template <class T>
void Matrix<T>::Mult (Matrix<T>& r,Matrix<T>& rc)
{
rc.Size(m,r.n);
int i,j,k;
T sum;
if ((n==r.m))
{

for (i = 0;i<m;i++)
{
  for(j = 0;j<r.n;j++)
  {
    sum = 0;
    for (k = 0;k<n; k++)
    {
     sum = sum + elem(i, k) * r.elem(k, j);
    }
    rc.elem(i, j) = sum;
  }
}
}
}

class Mat 
{
public:
double* v;
int m; //Rows
int n; //Cols
Mat();
Mat(int r,int c);
void Create(int r,int c);
~Mat();
Mat(const Mat &b);
void clear();
//inline
double* mn(int r,int c);
double* mn2(int r,int c);
void diag();
void MakeUnit();
void MakeZero();
Mat& operator += (const Mat& r);
Mat& operator -= (const Mat& r);
Mat& operator = (const Mat& r);
Mat& operator *= (const double r);
Mat operator * (Mat& r);
double GetV(int r,int c);
void Transpose();
void MakeUpperTri();
BOOL isSym();
int Invert();
Mat InvertJac(double &det);
double Det();
double Det2();
Mat Cholesky();
};

class C3dObject : public CObject
{
public:
	DECLARE_DYNAMIC(C3dObject);
    C3dObject();
    ~C3dObject();
	HRESULT GetResult() {return m_hr;}
protected:
	HRESULT m_hr; // result of last system call

};






//**************************************






 
class C3dMatrix {
public:
    //DECLARE_DYNAMIC(C3dMatrix);
    C3dMatrix();
    virtual ~C3dMatrix();
    C3dMatrix(const C3dMatrix& r);
    C3dMatrix(
        double v00, double v01, double v02, double v03,
        double v10, double v11, double v12, double v13,
        double v20, double v21, double v22, double v23,
        double v30, double v31, double v32, double v33
    );
    virtual void Serialize(CArchive& ar, int iV);
    C3dMatrix& operator=(const C3dMatrix& r);
    C3dMatrix operator+(const C3dMatrix& b);
    C3dMatrix& operator+=(const C3dMatrix& r);
    C3dMatrix operator*(const C3dMatrix& b);
    C3dMatrix& operator*=(const C3dMatrix& r);
    C3dVector operator*(const C3dVector& v);
    void Rotate(double rx, double ry, double rz);
    void Translate(double dx, double dy, double dz);
    void Translate2(double dx, double dy, double dz);
    void Scale(double sx, double sy, double sz);
    void Scale(double s) { Scale(s, s, s); }
    void MakeUnit();
    void SetColVec(int iC, C3dVector inV);
    C3dVector GetColVec(int iC);
    C3dVector GetUpVec();
    //void Initialize(D3DRMMATRIX4D& rlm);
    C3dVector Mult(C3dVector vInVect);
    C3dVector MultBack(C3dVector vInVect);
    OglMat GetOglMat();
    void Transpose();
    double det();
    C3dMatrix Inv();
    C3dMatrix CalcTran(C3dVector vIn);
    C3dMatrix CalcTranVUP(C3dVector vDir, C3dVector vUp);
    double GetZRot(C3dMatrix mUp);
    void ReverseZ();
    void ClearTranslations();
    // elements
    double m_00, m_01, m_02, m_03;
    double m_10, m_11, m_12, m_13;
    double m_20, m_21, m_22, m_23;
    double m_30, m_31, m_32, m_33;
};

void Circumsphere(C3dVector* v0, C3dVector* v1, C3dVector*  v2, C3dVector*  v3, C3dVector*  center, double* radius);
double TetVolume(C3dVector* v0, C3dVector* v1, C3dVector*  v2, C3dVector*  v3);

class DSP_Triad 
{
public:
     C3dVector vAxisPts[4];
     C3dVector vEyePt;
	 C3dMatrix mOrientMat;
     double ds;
	 double dSclFact;
     void Create(double WPS);
	 void ReSet();
     void SetTopView();
     void SetLeftView();
     void SetFrontView();
     void SetBottomView();
     void SetVIEW(C3dMatrix mT);
     void SetBackView();
     void SetRightView();
     void ReSet2();
     void Draw(CDC* pDC,C3dMatrix pMod,C3dMatrix pScrTran);
     void SetEye(double x,double y ,double z);
     void Rot(float fAx,float fAy,float fAz);
     void Trans(double dX,double dY,double dZ);
	   void ApplyTransform(C3dMatrix mInMat);
	   void Scl(double dSfactInc);
	   double GetScl();
	   C3dMatrix RetrieveMat();
	   void PushMat(C3dMatrix mT);
};



