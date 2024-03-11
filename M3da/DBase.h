
#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "resource.h"
#include "G_Object.h"

//Note the version number has to be negative
//so we can maintain compatability with older files
const int VERSION_NO=-74;
const int MAX_GPS = 1000;
const int MAX_TEMPGRP = 10000;

const int MAX_SIZE = 10000000;


class DBase : public CCmdTarget
{
DECLARE_DYNAMIC(DBase)

public:
//Include Nastran files try out 15/04/2023
    int iFileNo = 0;
    CString sFiles[200];
    int GetFileByNo(CString sF);
    void ExporttoNAS(int iFileNo);
    void ModIncludeNo(int iF);
    void ModLayerNo(int iF);
    void Ortho();
    void LabGaps(int iGap);
HGLRC		hrc;
//Dynamic draging object 
BOOL bIsDrag;
G_Object* pDragObj = nullptr;
void DragUpdate(CPoint inPt);
double WPSize;
double gdSize;
double gdASize;
//int iSelLabType;
C3dVector vLS; //Line Start
C3dVector vLE; //Line End
void SetLineStart(CPoint pS);
void SetLineEnd(CPoint pE);
int ResFrameDelay; // frame delay in msec
int NoResFrame; // No of frames for animation
//WORLD BITMAP TEST
BMP* pWorldBMP;
//****************************28/09/2016 SYMBOLS TABLE****************************
int iHLimit = -1;
int iPtLabCnt;
int iTxtLabCnt;
int iCVLabCnt;
int iSFLabCnt;
int iPartLabCnt;
DBase();
DBase(double WPS);
virtual ~DBase();
void DeleteAll();
int DspFlags;
BOOL bPICK;
int iVER;
void ClearSymTable();
void AddSymbol(Symbol* pSym);
//Symbol* GetSymbol(int iLab);
void LoadSymbols(FILE* pFile);
//14/07/2020
//Load the symbols table from SymTable.h stored internally
void LoadSymbolsInternal();
void SymTableCalcMetrics();
void AddText(C3dVector vN, C3dVector vDir, C3dVector vInPt, CString inText,double dH);
//debug only
void displaySymTable();
//****************************     End 28/09/2016    ****************************
BOOL bRevColBar;
double dMFullScl;
void CalcMScl();
double dPixelSize;
void ResSelect();
void ResSelectVec();
void ResSelectDef();
//******************      MESH MANAGEMNT   ****************************
void MeshListALl();
void CreateNewMesh(CString sName);
void SetActiveMesh(int ID);
void TogVisableMesh(int ID);
void DeleteMesh(int ID);
//*********************************************************************
void SetCurLC(int iSet);
void SetCurBC(int iSet);
void SetCurTSET(int iSet);
void ListLC();
void ListBC();
void ListTSET();
void DeleteLC(int iSet);
void DeleteBC(int iSet);
void DeleteTSET(int iSet);
void AnalysisLoadsets();
void AnalysisBCsets();
void AnalysisTEMPsets();
void CreateLC(int ID, CString sTit);
void CreateBC(int ID, CString sTit);
void CreateTSET(int ID, CString sTit);

void AnalysisSolution();
void AnalysisLoadStep();
void SetActStep(int iD);
void SetActSol(int iD);

//*********************************

void PrintTime(CString cS);
virtual void OnFinalRelease();
void DELAY(int iDelay); //iDelay in seconds
void HLimit(int iHlim); //Highlight limit
void ResListRespData(int iEnt);
void ResGraphRespData(int iEnt);
void LabelRespItems();
void ResListRespDataFull(int iEnt);
void ResDelay(int iDelay); //Animation frame Delay in mseconds
void ResFrames(int iNoF); //Animation frame Delay in mseconds
void SetScreenMat(CRect rRect);
void ReCalcScreenMat();
void SetView(CView* pCViewCurrent);
//final screen transform

int GetMaxPtLabCnt();
int GetMaxTxtLabCnt(); int GetMaxCVLabCnt();
int GetMaxSFLabCnt();
C3dMatrix pScrMat;
C3dMatrix pScrInvMat;
C3dMatrix pModelMat;
int dWidth,dHeight;
OglMat mOGLmat;

int iOGLInit;
int iCurElemType;
int iEdges;
BOOL bDispAll;

PropTable* PropsT;
MatTable* MatT;
void LabGapsMP(int iGap);

G_Object* DB_Obj[MAX_SIZE];       //all 
G_Object* TmpOGL[MAX_TEMPGRP];
int TmpOGLCnt;
int DB_ObjectCount;
Filter FILTER;
void SetFilter();
void QFilterNode();
void QFilterElement();
void QFilterPoint();
void QFilterCurve();
void QFilterSurface();
void QFilterAll();
int GetGroupID();
int GetColourID();
int GetItemType();
G_Object* S_Buff[MAX_SIZE];        //selector array
int S_BuffAdd(G_Object* cAddObj); //0 removed 1 added
void S_BuffAdd2(CDC* pDC,G_Object* cAddObj);
void S_BuffAdd3(G_Object* cAddObj);
BOOL S_IsIn(G_Object* cAddObj);
void S_Save(ObjList* oList);
void S_Res();
G_Object* Dsp_List[MAX_SIZE];     //display list
int DB_DrawState;               //draw method
int iDspLstCount;
int iFastView;
BOOL bNoList;               //no in display list
void Serialize(CArchive& ar);
void Dsp_All();
void Dsp_ShowAll();
void Dsp_Hide();
void Info();
void ReDraw();
void ReGen();
void Dsp_Selected();
void Dsp_Cat();
void Dsp_Next();
void Dsp_Prev();
void Dsp_Add(G_Object* pDspObject);
void Dsp_Rem(G_Object* gIn);
int iOGLList;
int iOGL_Start;
int iOGL_NoOff;
ObjList* OTemp;
ObjList* OTemp2;
Part* pCurrentPart;      //pointer to current part
ME_Object* pCurrentMesh;      //pointer to current mesh
void SetCurMesh();
void Dsp_CurMesh();
int iMeshCnt;

void InsertCat(C3dVector p1);
//*****************************
// Results
//*****************************
void ListResSets();
void ListVecSets();
void DelResSets();
void ListResSet();
void ResSetDivInTo(CString sSeq, double dS);
void ResSetScale(CString sSeq, double dS);
void ResSetEnvMax(CString sSeq[], int iNo);
void ResSetEnvMin(CString sSeq[], int iNo);
void SetCurrentResSet(int iRS, int iRV, int iOPT);
void DeleteResVec();
void SetCurrentResVec(int iRS, int iRV, int iD);
void SetCurrentResSetDef(int iRS,int iRV);
void SetDefScale(double dS);
void SetVecScale(double dS);
void SetColourBar(double dMin,double dMax);
void RevColourBar();
//*****************************
// GROUPS
//*****************************
ObjGp* Groups[MAX_GPS];
int iNoGPs;
int iCurGp;
int AddGp(CString inTit);
void ListGp();
void Dsp_Group();
void DelAll_Group();
void Del_Group(int iThisGp);
void AddToGroup();
void ChkNegJac();
void ChkShellAspect(ObjList* Nodes, double dT, BOOL bList);
void ChkTetCollapse(ObjList* Nodes, double dT, BOOL bList);
void AddToGroupbyPID(int PID);
void ColourByPID(int PID);
void ColourByINC(int PID);
void AddToGroupbyMID(int PID);
void RelatedTo(int iType);
BOOL IsOnScr(G_Object* pThis);
void CreateCoordLine();
void NoOfElementOnANode(int iNo);
void SelbyPID(int PID);
void SelbyMID(int inMID);
void SelbyCOL(int PID);
void SelbyTYPE(int PID);
void SelNodesbyCOL(int PID);
void SetResDispOff(Node* pN);
void SelSurfsbyCOL (int iCol);
void SelPtsbyCOL(int iCOl);
void SelCursbyCOL(int iCOl);
void SelCursbyLAY(int iLAY);
void AddToGroupbyCol(int PID);
void GPByInclude(int iFile);
void AddToGroupbyNDCol(int PID);
void AddToGroupbyNDOSYS(int PID);
void AddToGroupbyNDDSYS(int PID);
void AddToGroupbyType(int PID);
void RemFromGroup();
void Dsp_RemGP(G_Object* gIn);
void SaveGps(CArchive& ar);
void SetCurrentGP(int iGP);
void GPAddGP(int iGP);
void GPRemGP(int iGP);
void NextGp();
void PrevGp();
void TestSYS();
G_Object* GetObj(int iType,int iLab);
G_Object* LabSel(int iType,int iLab1,int iLab2);
//*********************************************************************
//              SOLUTION    SET     MANAGEMENT
//*********************************************************************
void ListSolutions();
void AddSolutions(CString sT,int iSol,double dT);
void AddStep(CString sT,int iLC,int iBC,int iTC,BOOL bRS);
BOOL isValidLCid(int iLC);
BOOL isValidBCid(int iLC);
BOOL isValidTCid(int iLC);
BOOL isActiveSolSet();
//*********************************************************************

//*****************************
// MESH CATALOG
//*****************************
PartsCat* MeshCat;
//*****************************
CRect		mCView_Rect;
int iWP;
void WPMode();
void CreateWP(double dWPSize);
ME_Object* CreateMesh(CString inName);
void Colour(int iCol);
void CountItems();
void LabEnt();
void ElemntMoPID(int iPID);
void ElementReverse();
void TetCircumSphere();
void ShellMoCSys(int iSys);
void SelRBENode(ObjList* Items);
void SpringMoCSys(int iSys);
void NodeMoOSys(int iSys);
void NodeMoLab(int iN);
void ElementMoLab(int iN);
void NodeMoLab2(int iN);
void ElementMoLab2(int iN);
void NodeMoRSys(int iSys);
void FindNode(C3dVector vP);
void AddNode(C3dVector InPt, int iLab,int i2,int i3, int iC,int iDef,int iOut);
void AddCoordSys(C3dVector p1,C3dVector p2,C3dVector p3,int Lab,int Typ,int iRID);
CvPt_Object* AddPt(C3dVector InPt, int iLab,BOOL bRedraw);
void AddPt2(double x,double y,double z, int iLab);
void AddDragLN(C3dVector v1);
void AddDragDIMA(C3dVector v1,C3dVector v2);
void AddDragDIMANG(C3dVector vVert, C3dVector v1, C3dVector v2);
void AddDragDIMH(C3dVector v1, C3dVector v2);
void AddDragDIMV(C3dVector v1, C3dVector v2);
void AddDragDIML(CString sText,C3dVector v1);
void AddDragDIMR(NCircle* pC, C3dVector v1);
void AddCirCL(NCircle* pC);
void AddDragDIMD(NCircle* pC, C3dVector v1);
void AddDimForDrag(DIM* pD);
NLine* AddLN(C3dVector v1,C3dVector v2, int ilab,BOOL bRedraw);
NLine* AddLNfromDrag(C3dVector v2);
DIM* AddDIMfromDrag(C3dVector v3);
NLine* AddLNbyXYZ(double x1,double y1, double z1, double x2, double y2, double z2,int iCol);
void AddRect(C3dVector v1,C3dVector v2, int ilab);
Line_Object* AddLN2(double x1,double y1,double z1,double x2,double y2,double z2, int ilab);
BOOL ChainCurves(ObjList* Curves);
BOOL ChainPath(ObjList* Curves);
BOOL ChainReverse(ObjList* Curves);
BOOL isClockWise(ObjList* Curves);                           
BOOL ChainNormal(ObjList* Curves,C3dVector &vN);             //This fails
BOOL ChainNormal2(NSurf* pS,ObjList* Curves,C3dVector &vN);  //This fails
BOOL ChainRef(ObjList* Curves,C3dVector &vR,C3dVector &vC);
BOOL Extents(ObjList* Curves,C3dMatrix TMat,C3dVector vO
             ,double &dXMax,double &dYMax
             ,double &dXMin,double &dYMin);
void AddSolidSection();
void AddSurfBound();
void CurveModLWT(int iW);
void CurveModType(int iW);
void AddSurfBoundIGES(G_Object* pS,ObjList* pCur);
void AddSurfBoundIGES2(G_Object* pS, ObjList* pCur);
void AddSurfBoundTrimLoopIGES(G_Object* pS,ObjList* pCur);
NCircle* AddCirCentPt(C3dVector vNorm,C3dVector vCent,C3dVector vR);
NLine* AddCirTanPt(C3dVector vNorm, C3dVector vPt, CPoint PNear1);
NLine* AddLinTan2Cir(CPoint PNear1, CPoint PNear2);
NCircle* AddCirCR(C3dVector vNorm,C3dVector vCent,double dR,int ilab);
void AddDragCIR(C3dVector vN, C3dVector v1);
void TrimLn();
//Fileet two LINES in 3d
NCircle* Fillet(NLine* L1,NLine* L2,double dR,C3dVector PNear1,C3dVector PNear2);
//Fileet two Curves in 3d iterate for intersections
NCircle* FilletIter(NLine* L1, NLine* L2, double dR, C3dVector PNear1, C3dVector PNear2);
NCircle* Fillet2(double dR,CPoint PNear1,CPoint PNear2);
NCircle* Circ3Pts(C3dVector p1,C3dVector p2,C3dVector p3);
NCircle* Arc3Pts(C3dVector p1,C3dVector p2,C3dVector p3);
void Corner(NLine* L1,NLine* L2,C3dVector PNear1,C3dVector PNear2);
void Corner2(CPoint PNear1,CPoint PNear2);
void Trim(CPoint PNear1, CPoint PNear2);
C3dVector LnInt(Line_Object* L1, G_Object* L2);
BOOL LnIntByPoints(C3dVector p11, C3dVector p12, C3dVector p21, C3dVector p22, C3dVector &pInt);

C3dVector LnInt2(Line_Object* L1,G_Object* L2);
C3dVector NLnInt(NCurve* L1,NCurve* L2,C3dVector* pNear);
C3dVector NLnInt2(NCurve* L1, NCurve* L2, C3dVector* pNear);
C3dVector NLnInt3(NCurve* L1, NCurve* L2, C3dVector* pNear);
BOOL IsIntersection(C3dVector C1S, C3dVector C1E, C3dVector C2S, C3dVector C2E);
int TentativeInt(NCurve* C1, NCurve* C2, C3dVector vInts[10],double uInts[10]);
int FindNearest(int iNo,double uInts[10], double u);
void ModNodeX(ObjList* Nodes, double dX);
void ModNodeY(ObjList* Nodes, double dX);
void ModNodeZ(ObjList* Nodes, double dX);
void CpNodes(ObjList* Nodes,C3dVector vTrVect,int iNoOfTimes);
void BetNodes(ObjList* Nodes,ObjList* Nodes2,int iNoOfTimes);
void ElsBetNodes(ObjList* Nodes,ObjList* Nodes2,int iNoOfTimes);
void IntersectEls(ObjList* Els1);
void ListAllProps();
void ListAllMats();
E_Object* AddEl(int iPos, BOOL AddDsp); 
E_Object* InsSpringEl(int iPos, BOOL AddDsp);
int  AddEl2(int pVnode[100], int iLab,int iCol,int iType,int iPID,int iMat, int iNoNodes,int A,int B,int C);
void AddContPolyW(double dWght, double deg);
void AddCurveFit(int p);
void AddSurfE(C3dVector vTr);
NSurf* AddPlainSurf(C3dVector vC,C3dVector vN,C3dVector vR, int ilab,BOOL bRedraw);
NSurf* AddPlainSurf2(C3dMatrix TMat,double XMax,double YMax,double XMin,double YMin,BOOL bRedraw);
C3dMatrix GetNodalSys(Node* pN);
void AddFluxQ(ObjList* Nodes,double T);
void AddTemperatureBC(ObjList* Nodes,double T);
void AddAccel(ObjList* Elements,C3dVector vA);
void AddRotAccel(ObjList* Elements, double dw, C3dVector vAP1, C3dVector vAP2);
void AddTemperature(ObjList* Nodes,double T);
void AddTEMPD(double T);
void AddGrav(double dScl, C3dVector Vec);
void AddForce(ObjList* Nodes,C3dVector F);
void AddMoment(ObjList* Nodes,C3dVector F);
void AddPressure(ObjList* Nodes,C3dVector F);
void ShellSolids(ObjList* Els,int iCol);
E_Object* GetElRelEdge(ObjList* pFrom, Node* N1, Node* N2);
void ShellNormConsistancy(ObjList* Els);
void QuadToTri(ObjList* Els);
void ElMass(ObjList* Els);
ObjList* is2D(ObjList* Els, double &dxMin, double &dyMin, double &dxMax, double &dyMax);
void SectionProps(ObjList* Els);
void FreeFaceDsp(ObjList* Els);
void FreeEdgeDsp(ObjList* Els);
eEdgeList* FindEdges(ObjList* Els);
//**************** Advancing Front 2D Surface Mesher ****************
double DistPtSeg(cSeg* pSeg, C2dVector pt);
double DistPtSeg2d(cSeg* pSeg, C2dVector pt, double dSX, double dSY);
double CirCircle(cSeg* pSeg, C2dVector pt, C2dVector &pC);
//Scaled parametric version
double CirCircle2d(cSeg* pSeg, C2dVector pt, C2dVector &pC, double dSX, double dSY);
void TestCircleCir();
BOOL CheckInt(ObjList* pSegs, cSeg* bS, c2dParPt* vPt);
double ProximityChk(ObjList* pSegs,c2dParPt* vPt);
double ProximityChk2d(ObjList* pSegs, c2dParPt* vPt, double dSX, double dSY);
void GetCandiatesSeg(cSeg* pNot, cLinkedList* pFrom, C2dVector vC, double dCD, ObjList* pRes);
void GetCandiatesNodes(cSeg* pNot, ObjList* pFrom, C2dVector vC, double dCD, ObjList* pRes);
//Scaled to real stretched 2d coordinates
void GetCandiatesSeg2d(cSeg* pNot, cLinkedList* pFrom, C2dVector vC, double dCD, ObjList* pRes, double dSX, double dSY);
void GetCandiatesNodes2d(cSeg* pNot, ObjList* pFrom, C2dVector vC, double dCD, ObjList* pRes, double dSX, double dSY);

void CreateBSegs(ObjList* pP, cLinkedList* pS, double dS, NSurf* pSf);
void GenPts(NSurf* pS, ObjList* Pts);
BOOL UpdateFront(NSurf* pSf, int &iNodeLab, int &iSegLab, BOOL isNewNd,cSeg* pBaseSeg, ObjList* Pts, cLinkedList* Segs, c2dParPt* pbFNd, C2dVector pTmp,ObjList* pEls);
eFaceList* GenTesselation(ObjList* pN, ObjList* pE);
void Smooth(ObjList* pN, ObjList* pE);
BOOL NodeInTri(C2dVector t1, C2dVector t2, C2dVector t3, C2dVector pt);
BOOL isSegIn(ObjList* pSegs, c2dParPt* pS1, c2dParPt* pS2);
BOOL isNodeInCircle(ObjList* pN, int iExclude,double dRad, C2dVector Cpt);
BOOL isNodeInCircle2d(ObjList* pN, int iExclude, double dRad, C2dVector Cpt, double dSX, double dSY);
void MeshBeamSize(ObjList* pCurves, double dS);
void MeshBeams(ObjList* pCurves);
void MeshSurfSize(ObjList* pSurfs, double dS);
//****************  2d Advancing Front Auto Mesher ******************
void MeshSurfAF(ObjList* pSurfs, double dSz);
//***************************************************************************
//                     EXPERIMENTAL QMORPH
// Cpnvert tri mesh to quads
// Advancing Front Quadrilateral Meshing Using Triangle Transformations
// Steven J. Owen1,2, Matthew L. Staten2, Scott A. Canann1,2 and Sunil Saigal1
//***************************************************************************
void QMorph(ObjList* Els);
//****************   Advancing Front 3d TET Mesher   ****************
void MeshTET(ObjList* Els,double G);
void AdvancingTet(cLinkedList* fEls, cLinkedList* fNodes,double dG);
E_Object3* GetFace(ObjList* pAdjFaces,Node* N1,Node* N2,Node* N3);
E_Object34* GetTETRelFace(E_Object3* pF);
double GetTargetElSize(cLinkedList* fEls);
E_Object3* DoesTETPenetrateBoundary(ObjList* pCandidateFaces,E_Object34* pTET,E_Object3* notThisFace);
BOOL IsBaseIntersect(C3dVector vIntPt, C3dVector vFN1, C3dVector vFN2, C3dVector vFN3, double dTol);
BOOL DoesTETPenetrateFace(E_Object34* pTET,E_Object3* pFace,double dTol);
int LineIntPlane(C3dVector p0,C3dVector p1,E_Object3* pFace, C3dVector& vRes,double& dR);
BOOL LineIntTRI(C3dVector p0,C3dVector p1,E_Object3* pFace, C3dVector& vRes,double& dS,double& dT,double dTol);
BOOL IsValidTET(ObjList* pCandidateFaces,E_Object34* eTET, double dCD,E_Object3* pBaseF);
BOOL isNodeInTET(ObjList* pChkNodes,E_Object34* eTET);
BOOL IsValidTET2(ObjList* pCandidateFaces,ObjList* pChkNodes,E_Object34* eTET, double dCD,E_Object3* pBaseF);
void CreateTET(E_Object34* eTET,E_Object3* pE,Node* nNode);
double MinInternalAngTET(E_Object34* eTET);
BOOL NodeNotInTET(E_Object34* eTET,ObjList* pCandidateNodes);
double TETFaceInternalAng(C3dVector vN0,C3dVector vN1,C3dVector vN2,C3dVector vN3);
double dot2D(C3dVector u,C3dVector v);
double perp2D(C3dVector u,C3dVector v);
int intersect2DUV_2Segments(C2dVector S1a, C2dVector S1b, C2dVector S2a, C2dVector S2b, C2dVector* I0, C2dVector* I1);
int intersect2D_2Segments(C3dVector S1a, C3dVector S1b,C3dVector S2a, C3dVector S2b,C3dVector* I0, C3dVector* I1);
double sign (C3dVector p1, C3dVector p2, C3dVector p3);
BOOL PointIn2dTriangle(C3dVector vt1,C3dVector vt2,C3dVector vt3,C3dVector vPt);
E_Object3* DoesFaceOverLap(E_Object3* pF1,ObjList* pCandidateFaces,double dTol);
BOOL CommitTET(cLinkedList* fEls,ObjList* pCandidateFaces,E_Object34* eTET);
void DeleteTET(cLinkedList* fEls, cLinkedList* fNodes,ObjList* pCandidateFaces,E_Object34* eTET);
E_Object3* CreateFace(Node* N1,Node* N2,Node* N3);
void RemoveFace(cLinkedList* fEls,ObjList* pCandidateFaces,E_Object3* pFF);
void RemoveFaces(cLinkedList* fEls,ObjList* pAdjFaces,E_Object3* pE);
Node* GetOtherNode(E_Object3* pFrom,E_Object3* pFace);
Node* GetBestNode(ObjList* pFrom,E_Object3* pFace);
E_Object3* GetAdjFace(ObjList* pFrom,Node* N1,Node* N2,Node* N3,E_Object3* pExclude);
double AngleBetweenFaces(E_Object3* pFace1,E_Object3* pFace2);
void GetAdjFaces(ObjList* pFrom,E_Object3* pFace, ObjList* pRes,double* dAngO,E_Object3*& pNode);
void GetCandiates(cLinkedList* pFrom,C3dVector vC, double dCD, ObjList* pRes);
void ZeroRemeshFlg(cLinkedList* pFrom);
void GetCandiateFaces(E_Object3* pBF,ObjList* pFrom,C3dVector vC, double dCD, ObjList* pRes);
void GetCandiatesNode(E_Object3* pFace,ObjList* pFrom,C3dVector vC, double dCD, ObjList* pRes);
void RESLISTEL(ObjList* Els);
void RESLISTND(ObjList* Nds);
void AddRestraint(ObjList* Nodes,C3dVector TDofSet,C3dVector RDofSet);
void CoincidentNodes(ObjList* Nodes,ObjList* CNodes,double dTol);
void CoincidentElements(ObjList* Chkls);
void AddSurfR(C3dVector vB, C3dVector vD,double dAng);
void Draw(C3dMatrix pM,CDC* pDC,int iDrawmode);
BOOL isBlackDisp();
void AddObj(G_Object* gIn);
void RemTempGraphics(G_Object* gIn);
void AddTempGraphics(G_Object* gIn);
void RemObj(G_Object* gIn);
void RemObjNoDel(G_Object* gIn);
void DrawDrag(CDC* pDC,CPoint p1,CPoint p2);
void LineDrag(CDC* pDC, CPoint p1, CPoint p2);
void DBase::GenAnimationW(int iDspFlgs,int iNoFrames);
void DBase::GenAnimationS(int iDspFlgs, int iNoFrames);
void DBase::GenAnimationFrameW(int iDspFlgs, int iFrameNo, double dF);
void DBase::GenAnimationFrameS(int iDspFlgs, int iFrameNo, double dF);
void OglDraw(int iDspFlgs);
void OglDrawW(int iDspFlgs);
void Cycle();
void Animate();
void AnimatePosNeg();
void SetToScr();
void SetToScr2(C3dMatrix pM);
void SetWPMode(int iMode);
void SetWPSize(double dSize);
C3dMatrix GetWPmat();
C3dVector WPtoGlobal(C3dVector InPt);
C3dVector WPtoGlobal2(C3dVector InPt);
C3dVector GlobaltoWP(C3dVector InPt);
C3dVector GlobaltoWP2(C3dVector InPt);
C3dVector GlobaltoWP3(C3dVector InPt);
C3dVector CylToCart(C3dVector InPt);
C3dVector CartToCyl(C3dVector InPt);
//Drawing Pen Attributes
CClientDC* ClientDC;
CView* pTheView;
CDC* pDCont;
CPen *Pen;
CPen *OldPen;
void SetPen(CDC* pDC,int iCol);
void RestorePen(CDC* pDC);
CClientDC* OGLClientDC;
void InitOGL(CDC* pDC);
float m_fRadius;
void InvalidateOGL();
void SetDrawType(int iType); //0 GUI LiNE; 1 OGL SHADE
int GetDrawType();
void SetFastView(); 
int GetFastView();
//***************************************************
// Element Creation Mode
//***************************************************
void SetCurEType(int iEType);
int GetCurEType();
C3dVector GetVPt();
C3dVector GetMeshCentre();
int GetMeshYExt();
//***************************************************
// Set buffer for incomming points 
//***************************************************
int DB_ActiveBuff;
int DB_ActiveBuffSet(int iWhichBuff);
// 1 send msgs pts to selector
// 2 send msgs pts to Pt & selector auquisition buffer

//***************************************************
// selector buffer management
//***************************************************
int S_Count;
G_Object* S_Single(CPoint InPT);
void S_Box(CPoint UL, CPoint LR);
void S_Des();
void S_All(int iT);
void S_Invert();
//***************************************************
// Pt buffer management
//***************************************************

C3dVector DB_PtBuff[500];
int DB_BuffCount;
void DB_AddPtBuff(C3dVector InPT);
void DB_Dellast();
void DB_ClearBuff();
C3dVector DB_GetBuffbyInd(int iInd);
C3dVector DB_GetBuff();
C3dVector DB_PopBuff();
int DB_NoInBuff();

//***************************************************
// Process Message
//***************************************************
void DoMsg(int MsgType, CPoint PT1, CPoint PT2);
void S_Import(FILE* pFile, CString inName,int iT);
void S_ImportGroups(FILE* pFile);
void Readdb(FILE* pFile,int Vals[],int &iCnt,int &iKey,int &iRec,CString &sTit,CString &sSubTit,double &dFreq);
void AddOEFRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOEFResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOAG1Res(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOQMRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOUGRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOES1Res(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOES1ResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOSTRRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOSTRResF(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dF);
void AddOESNRes(int Vals[],int iCnt,CString sTitle,CString sSubTitle,CString inName);
void AddOESResR(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName);
void AddOSTRResR(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName,double dFreq);
void AddOSTRFCPXRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName, double dFreq);
void AddONRGRes(int Vals[], int iCnt, CString sTitle, CString sSubTitle, CString inName);
void S_ImportOp2(FILE* pFile, CString inName,int iT);
G_Object* GetBasicIGESType(int iD,IgesD (&DirEnt)[100000],IgesP* PDat);
void S_ImportIges(FILE* pFile, CString inName);
void S_ImportCat(FILE* pFile, CString inName);
int S_ImportWG(FILE* pFile, CString inName);
//******************BITMAP FOR EARTH TEXTURE MAP EXAMPLR*************************
GLuint S_loadBMP(CString sFile, CString inName);
//*******************************************************************************
ME_Object* ImportUNV(FILE* pFile,CString inName);
ME_Object* ImportNAS(FILE* pFile,CString inName,BOOL ReLab);
void ImportNASTRAN_SOL(CString inName, ME_Object* pME);
void ImportNASTRANFirstPass(CString inName, ME_Object* pME,NEList* PIDs,NEList* MATs);
void ImportNASTRANGRID(CString inName, ME_Object* pME);
void ImportNASTRANELEM(CString inName, ME_Object* pME,NEList* PIDs);
ME_Object* ImportNASTRAN(CString inName);
ME_Object* ImportNASTRAN2(CString inName,BOOL ReLab);
BOOL isSupportedNAS(CString sKwrd);
BOOL isSupportedNASCYS(CString sKwrd);
BOOL isSupportedNASGRID(CString sKwrd);
BOOL isSupportedNASELEM(CString sKwrd);
void UserCalc();
void UserCalc2();
void TestTrans();
void ExportMesh(FILE* pFile2);
void ExportDXF(FILE* pFile2);
void ExportRes(FILE* pFile2);
void ExportMeshNAS(FILE* pFile2,int iFile); //iFile is include file no or -1 all
void ExportToText(FILE* pFile2);
void ExportViewMat(FILE* pFile2);
void ImportViewMat(FILE* pFile);
void ExportCMesh(FILE* pFile2);
void ExportGroupsTXT(FILE* pFile2);
void ExportPermGroupsTXT(FILE* pFile2);
int gDim;
void UpTree();
void FlipZ();
void FlipY();
//****************************OGL******************************** 
int iF;
CDC*   m_pDC;
CPalette     m_cPalette;
CPalette    *m_pOldPalette;
BOOL bSetupPixelFormat();
void CreateRGBPalette();
unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
SecTable* pSecs;
int iSMode;
int iSH;
int iSW;
void LoadSecT(FILE* pFileA);
void LoadProps(CString sFile);
void DeleteObj();
void TogMeshD();
CString GetObjName(int index);
void SelWGName(CString inName);
void SelAllWGs();
void NodesOnCurve(NCurve* pC, int iNo, cLinkedList* pN);
void GenNodesOnCurve(int iNo, cLinkedList* pN);
void GenPointsOnCircle(int iNo);
void GenNodesOnCircle(NCircle* pCir,int iNo, cLinkedList* pN);
void GenPoinsOnCir(NCircle* pCir, int iNo);
void Test2();
void TestMPM2();
void TestFL();     //Test Face list display
void insPlanet();
void insBackGround();
void Dsp_CtrlPts();
void Move(ObjList* Nodes,C3dVector vTrVect);
void Align(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3,
                          C3dVector p4,C3dVector p5,C3dVector p6);
void Reflect(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3);
void Reflect2(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3);
void Reflect2d(ObjList* Objs,C3dVector p1,C3dVector p2,C3dVector p3);
void RotateAngs(ObjList* Objs,C3dVector pCent,C3dVector pRot);
void RotateAbout(ObjList* Objs,C3dVector p1,C3dVector p2,double dAng);
void RotateAbout2(G_Object* Obj,C3dVector p1,C3dVector p2,double dAng);
void Scale2(G_Object* Obj,C3dVector p1,double dScale);
void Scale(ObjList* Objs,C3dVector p1,double dScale);
void CopyRot(ObjList* Objs,C3dVector p1,C3dVector p2,double dAng,int iNoOff);

void Solve();
void CV_ModifW(double dW);
void AddSurf();
void AddSurfSweep(ObjList* pC,ObjList* pP);
C3dMatrix CalcTranSsswep(C3dMatrix TMat,C3dVector vDir);
//Extract Surface / Curves / Points From PART obj
void Extract(ObjList* pPObjs);
void SweepSurf(NCurve* pC,NCurve* pP,C3dMatrix TMatB,C3dVector vCO,C3dMatrix& TMat);
void MoveObjs(ObjList* Items,C3dVector tVec);
void MoveObj(G_Object* Item,C3dVector tVec);
void Copy(ObjList* Items,C3dVector tVec,int iNoOff);
void BeamUpVecs(ObjList* Items,C3dVector tVec);
void BeamOffsets(ObjList* Items, C3dVector tVec);
void BeamOffsetY(ObjList* Items, double dy);
void BeamOffsetZ(ObjList* Items, double dz);
void SetDOFStringA(ObjList* Items, CString sDOF);
void SetDOFStringB(ObjList* Items, CString sDOF);
void ShellOffsets(ObjList* Items,double dOff);
void ElSweep(ObjList* Items,C3dVector tVec,int iNoOff);
void NDSweepToShell(ObjList* Items, C3dVector tVec, int iNoOff);
void NDSweepToBeam(ObjList* Items, C3dVector tVec, int iNoOff);
void ViewLam(int iP);
//******************************************************************
//                  Drap Demo 22/062020 BlowsR
//******************************************************************
C3dVector GetNodalNormal(Node* pN, ObjList* ELS);
C3dVector GetNodalNormal2(Node* pN, ObjList* ELS);
double DirCheck(C3dVector vN, ObjList* ELS);
void CalcAngles(cLinkedList* NDF);
double CalcAngle(BOOL bL, Node* pN,ObjList* NDF);
void GenFronts(cLinkedList* NDF,int iDir);
BOOL MoveFront(c2dFront* pMF);
void ChkIntersects(cLinkedList* NDF);
void GenBEamElements(cLinkedList* NDF, int iCOl);
void GenElements(cLinkedList* NDF);
void GenElements2(BOOL bL,ObjList* NF1, ObjList* NF2);
void CreatTestPCOMPS();
void ElSweepB(ObjList* Items,double dDist, int iNo);   //*** MAIN ***
//******************************************************************
void OffSet(G_Object* pOff,C3dVector vDir,double Dist);
void MapMesh(double dU, double dV);
void MapMeshTri(double dU, double dV);
void FreeMeshTri(double dS);
void FreeMeshTriSurf(double dS,NSurf* pS);
C3dVector Intersect(BOOL &bErr, CPoint nPt);
C3dVector ClosestTo(C3dVector vPt);
void KnotModify(NCurve* pC,CString sKnot);
void KnotInsertion(NCurve* pC, C3dVector vPt);
void CurveDivide(NCurve* pC, NCurve* &pC1, NCurve* &pC2, C3dVector vPt);
void CurveSplit(NCurve* pC, C3dVector vPt);
G_Object*  AddRHDCyl(C3dVector vNorm,C3dVector vCent,C3dVector vRef,double dR,int ilab,BOOL bRedraw);
C3dVector PickPointToGlobal(CPoint Pt);
//***************************************************************************
//Gets a point picked on the work plane 
//Noye as the Z ordinate is lost some
//work hass to be done to get it back
//Superceeds PickPointToGlobal
//09/04/2020
//***************************************************************************
C3dVector PickPointToGlobal2(CPoint Pt);
void ListMat(int MID,BOOL bPID); 
void EditMat(int MID, BOOL bPID);
void EditProp(int PID);
void ListProp(int PID);
void EditObject();
void EditGlobals();
void lMeasure(C3dVector v1,C3dVector v2);
void AMeasure(C3dVector v1, C3dVector v2, C3dVector v3);
void CurvesToSurface(ObjList* OL1,ObjList* OL2);
Shell* AddShell514(Part* pP, int iDE, IgesP* PDat, BOOL bOrient);
void CleanFromDB(Part* pP);
BOOL TrimLoop508(int iS,IgesP* PDat, int iLOOP, ObjList* Curves, ObjList* ParaCurves,BOOL bOut);
BOOL EndChecks(ObjList* Curves, ObjList* ParaCurves);
BOOL CurvesToSurface508(int iS, IgesP* PDat, ObjList* Curves, ObjList* ParaCurves, Vec<int> bOrient);
int FindCurveInU(ObjList* Curves, NSurf* pSurf);  //Return index of curve that varies in V on surface
int FindCurveInV(ObjList* Curves, NSurf* pSurf);  //Return index of curve that varies in V on surface
NCurveOnSurf* GetIsoCurve(NSurf* pSurf, NCurve* pSC,int iIso,BOOL EndChk);
NCurveOnSurf* CreateTrimLine(NSurf* pSurf, NCurve* pSC, C3dVector v1, C3dVector v2);
void SurfaceTrim(ObjList* OL1,ObjList* OL2);
void SurfUnTrim();
void SurfaceTrimLoop(ObjList* Sur,ObjList* Curves2);
void BuildAssembly(CString sModName);
void BuildGroupsFromCurrentFEM();
NSurf* BSurfIges(IgesD DE,CString PLine);
NCurve* BCurveIges(IgesD DE,CString PLine);
NCurve* SplineCurveIges(IgesD DE,CString PLine);
NSurf* RevSurfIges(G_Object* pAxis,G_Object* pGen,double dS,double dE);
C3dVector CalcBeamUpVec(E_Object2* EB,int iONID,C3dVector vU);
void SetBeamOffs(E_Object2B* EB,C3dVector vOffA,C3dVector vOffB);
void CreatePrRod(CString sT,int iPID,int iMID,double dR);
void CreatePRBar2(CString sT, int iPID, int iMID, double dA, double dI1, double dI2, double dJ);
void CreatePRod(CString sT,int iPID,int iMID,double dA,double dJ);
void CreatePrTube(CString sT,int iPID,int iMID,double dR,double dr);
void CreatePrBar(CString sT,int iPID,int iMID,double dW,double dH);
void CreatePrBox(CString sT,int iPID,int iMID,double dW,double dH,double dWT,double dHT);
void CreatePrL(CString sT, int iPID, int iMID, double dW, double dH, double dWT, double dHT);
void CreatePrT2(CString sT, int iPID, int iMID, double dW, double dH, double dWT, double dHT);
void CreatePrCHAN2(CString sT, int iPID, int iMID, double dW, double dH, double dWT, double dHT);
void CreatePrI2(CString sT, int iPID, int iMID, double d1, double d2, double d3, double d4, double d5, double d6);
void CreatePrShell(CString sT,int iPID,int iMID,double dT,double dNSM);
void CreatePrPCOMP(CString sT, int iPID, double dNSM, int iNoLay, CString sLay[]);
void CreatePrSpringT(CString sT,int iPID,double dkx,double dky,double dkz,double dkt);
void CreatePrBUSH(CString sT, int iPID, double dk1, double dk2, double dk3, double dk4, double dk5, double dk6);
void CreatePrSpringR(CString sT,int iPID,double dkx,double dky,double dkz,double dkt);
void CreatePrLumpedMass(CString sT, int iPID, double dM);
void CreatePrSolid(CString sT,int iPID,int iMID);
void CreateMat1(CString sT,int iMID,double dE,double dV,double dDen,double dAlpha,double dkt);
void CreateMat8(CString sInTit,
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
                double dk);
void ModifyPrMat(int iPID,int iMID1,int iMID2);
void CNodesMerge(double dTol);
void GetClosestNodes(ObjList* pSource, C3dVector pTrg, ObjList* pRes, double dTol);
void CNodesMerge2(ObjList* Nodes,double dTol,BOOL UpLab,BOOL bDel);
void EqLab(ObjList* Nodes, double dTol, BOOL UpLab, BOOL bDel);
void DoDeformedDisp();
void SolveIncompFluids();
void SolveStress();
void  SolveCFD();
void  SolveCFD2();
void  PlotSol(ObjList* pVec,Matrix<double> &UVP,double dx,double dy);
void  PlotData(ObjList* pVec,Matrix<double> &UVP,double dx,double dy);
void  PlotSol2(ObjList* pVec,Matrix<double> &U,Matrix<double> &V,double dx,double dy);
void  PlotData2(ObjList* pVec,Matrix<double> &U,Matrix <double> &V,double dx,double dy);
void CycleFrames();
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	LONG GetNo(void);

	enum 
	{
        dispidReDrawWindow = 3L,
        dispidAddNode = 2L,
        dispidGetNo = 1L
	};
public:
  afx_msg void OnEditProject();
//  afx_msg void OnMaterialIsentropic();
//  afx_msg void OnSurfaceSweep();
protected:
    void API_AddNode(DOUBLE X, DOUBLE Y, DOUBLE Z, LONG ID, LONG COL);
    void ReDrawWindow();
};



