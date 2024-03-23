
// M3daDoc.h : interface of the CM3daDoc class
//


#pragma once
#include "Mnu.h"

class CM3daDoc : public CDocument, public CUndo
{
protected: // create from serialization only
	CM3daDoc();
	DECLARE_DYNCREATE(CM3daDoc)

// Attributes
public:
//

BOOL bUndo = TRUE;
BOOL bFinalChkPt = FALSE;
BOOL bOnFirst=TRUE;
CView* pCView;
CDC* D_ClientDC;
CPen *Pen;
CPen *OldPen;
int iFirst;
CString sLastcmd;
void SetPen(CDC* pDC,int R,int G,int B);
void RestorePen(CDC* pDC);
double GetWPSize();
C3dMatrix GetWPmat();
		//graphics mapping to screen
		//inverse screen mapping
    //
int iDrawMode;
void SetView (CView* pCViewIn);
void InitDoc();
void SetScreenMat(CRect rRect);
void Draw(C3dMatrix pM,CDC* pCView,int iMode);
void DragUpdate(CPoint m_PointNew);
BOOL isBlackDisp();
void SetToScr2(C3dMatrix pM);
void DrawDrag(CDC* pDC,CPoint P1,CPoint P2);
BOOL isDragging();
void SetLineStart(CPoint pS);
void SetLineEnd(CPoint pE);
void LineDrag(CDC* pDC, CPoint P1, CPoint P2);
void SelectBox(CPoint P1,CPoint P2);
void InitOGL(CDC* pDC);
void InvalidateOGL();
double GetHeight();
void DoMsg(int MsgType,CPoint PT1,CPoint PT2,CString InFu);
BOOL isMenuNULL();
void DspAll();
void DspSel();
void DspCat();
void DspNext();
void DspPrev();
void SetDrawType(int iType);
int  GetDrawType();
C3dVector GetViewPt();
C3dVector GetMeshCentre();
int GetMeshYExt();
void UpTree();
void Dsp_Group(); 
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents2();
// Implementation
public:
	virtual ~CM3daDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
  afx_msg void OnUpdateLC(CCmdUI *pCmdUI);  //ADDED BY ME 
  afx_msg void OnUpdateBC(CCmdUI *pCmdUI);  //ADDED BY ME 
  afx_msg void OnUpdateTC(CCmdUI *pCmdUI);  //ADDED BY ME 
  afx_msg void OnViewDisplayall();
  afx_msg void OnEditDes();
  afx_msg void OnEditInformation();
  afx_msg void OnEditKeyin();
  afx_msg void OnEditPick();
  afx_msg void OnEditBetween();
  afx_msg void OnEditTranslatedfrom();
  afx_msg void OnEditFilternone();
  afx_msg void OnEditCancel();
  afx_msg void OnEditDone();
  afx_msg void OnGroupAddtogroup();
  afx_msg void OnGroupRemovefromgroup();
  afx_msg void OnGroupAddgroup();
  afx_msg void OnGroupRemovegroup();
  afx_msg void OnGroupSetcurrent();
  afx_msg void OnGroupListgroups();
  afx_msg void OnImportUnv();
  afx_msg void OnImportDat();
  afx_msg void OnImportIges();
  afx_msg void OnImportLoadbmp();
  afx_msg void OnViewNodesoff();
  afx_msg void OnCreatePoint();
//  afx_msg void OnLineLine();
  afx_msg void OnLineLinex();
  afx_msg void OnLineLiney();
  afx_msg void OnLineLinez();
  afx_msg void OnCreateCircle();
  afx_msg void OnCreateCurve();
  afx_msg void OnSurfaceLoft();
  afx_msg void OnSurfaceExtrude();
  afx_msg void OnSurfaceRevolve();
  afx_msg void OnCreateNode();
  afx_msg void OnCreateElement();
  afx_msg void OnElementtypeTri();
  afx_msg void OnElementtypeQuad();
  afx_msg void OnElementtypeBrick();
  afx_msg void OnElementtypeWedge();
  afx_msg void OnElementtypeTet();
  afx_msg void OnCreateCopynodes();
  afx_msg void OnCreateNodemoveto();
  afx_msg void OnCreateNodesbetween();
  afx_msg void OnCreateNodesoncurve();
  afx_msg void OnViewSelectall();
  afx_msg void OnToolsMove();
  afx_msg void OnToolsCopy();
  afx_msg void OnToolsWpmode();
  afx_msg void OnToolsWpalign();
  afx_msg void OnToolsWpglobal();
  afx_msg void OnViewControlpoint();
protected:
	void GetNo(void);

	enum 
	{
    dispidExportGroups = 29L,
    dispidMergeNodes = 28L,
    dispidExportNAS = 27L,
    dispidElDeg = 26,
	dispidSelectAllWGs = 25L,
    dispidExportUNV = 24L,
    dispidDisplayAll = 23L,
    dispidBuildAssem = 22L,
    dispidImportWG2 = 21L,
    dispidNoElemenrsV = 20,
    dispidNoElemenrsH = 19,
    dispidIMode = 18,
    dispidElLen = 17,
    dispidAddLine = 16L,
    dispidAddPoint = 15L,
    dispidInvertSel = 14L,
    dispidSelectWG = 13L,
    dispidImpSecT = 12L,
    dispidGetName = 11L,
    dispidGetDBNoObjs = 10L,
    dispidImportWG = 9L,
    dispidTogOn1d2d = 8L,
    dispidImportCat = 7L,
    dispidGenMesh = 6L,
    dispidReDraw = 5L,
    dispidDesAll = 4L,
    dispidDeleteSelectedWG = 3L,
    dispidAPIGetModel = 2L,
		dispidGetNo = 1L
	};
public:
	afx_msg void OnToolsColour();
	afx_msg void OnToolsSetcurrentmesh();
	afx_msg void OnExportCurrentmeshto();
	afx_msg void OnGroupCreategroup();
	afx_msg void OnToolsDelete();
protected:
	IDispatch* APIGetModel(void);
public:
  afx_msg void OnCreateFittedcurve();
  afx_msg void OnEditOnscreenlocation();
  afx_msg void OnEditRepeatlastcommand();
  afx_msg void OnEditIitersection();
  afx_msg void OnEditProject();
  afx_msg void OnCreateFillet();
  afx_msg void OnCreateOffset();
  afx_msg void OnLineLineangle();
  afx_msg void OnCreateMakecorner();
  afx_msg void OnCreateRectangle();
  afx_msg void OnSurfaceProjectcurve();
  afx_msg void OnSurfaceTrimsurface();
  afx_msg void OnSurfacePlanar();
  afx_msg void OnSurfaceInternaltrimloop();
  afx_msg void OnCreateCoordsys();
  afx_msg void OnGroupElementsbypid();
  afx_msg void OnGroupElementsbycolour();
  afx_msg void OnSelectionElementsbypid();
  afx_msg void OnSelectionElementsbycolour();
  afx_msg void OnSelectionNodesbycolour();
  afx_msg void OnSelectionSelectall();
  afx_msg void OnSelectionRelatedto();
  afx_msg void OnSelectionElementsbytype();
  afx_msg void OnCreateCoordsysline();
  afx_msg void OnSelectionElat();
  afx_msg void OnToolsListproperty();
  afx_msg void OnToolsMeasure();
  afx_msg void OnElementmodifiyPid();
  afx_msg void OnNodemodifyOutputcoordsys();
  afx_msg void OnEditRelatedto();
  afx_msg void OnEditLabel();
  afx_msg void OnSelectionElementsbymaterial();
  afx_msg void OnMeshMappedsurfacemesh();
  afx_msg void OnMeshMappedtrimesh();
  afx_msg void OnChecksCoincidentnodes();
  afx_msg void OnMeshSweepelements();
  afx_msg void OnViewShadededges();
//  afx_msg void OnViewLine();
  afx_msg void OnVisabilityNodeon();
  afx_msg void OnVisabilityElementon();
  afx_msg void OnViewNodesask();
  afx_msg void OnVisabilitySurfaceson();
  afx_msg void OnVisabilityCurveson();
  afx_msg void OnVisabilityAllvisable();
  afx_msg void OnViewLabelentities();
  afx_msg void OnQwantaImportcatalogue();
  afx_msg void OnQwantaImportsectiontable();
  afx_msg void OnQwantaImportwaveguide();
  afx_msg void OnQwanta1d();
  afx_msg void OnQwantaMeshdensitytoggle();
  afx_msg void OnQwantaGeneratemesh();
  afx_msg void OnCataloguedisplayDisplaycatalugue();
  afx_msg void OnCataloguedisplayDisplaynext();
  afx_msg void OnCataloguedisplayDisplayprevious();
protected:
  void API_DeleteSelectedWG(void);
  void API_DesAll(void);
  void API_ReDraw(void);
  void API_GenMesh(void);
  void API_ImportCat(LPCTSTR FileName);
  SHORT API_On1d2d(void);
public:
  afx_msg void OnVisabilityAssemblies();
  afx_msg void OnQwantaBuildamdexport();
  afx_msg void OnGroupDeleteallgroups();
protected:
  SHORT API_ImportWG(LPCTSTR sFName,LPCTSTR WGName);
  LONG API_GetDBNoObjs(void);
  BSTR API_GetName(LONG Index);
  void API_ImpSecT(LPCTSTR sFName);
  void API_SelectWG(LPCTSTR inName);
  void API_InvertSel(void);
  void API_AddPoint(DOUBLE x, DOUBLE y, DOUBLE z, LONG Lab);
  void API_AddLine(DOUBLE x1, DOUBLE y1, DOUBLE z1, DOUBLE x2, DOUBLE y2, DOUBLE z2, LONG Lab);
  DOUBLE API_GetElLen(void);
  void API_SetElLen(DOUBLE newVal);
  SHORT API_GetIMode(void);
  void API_SetIMode(SHORT newVal);
  SHORT API_GetNoElementsH(void);
  void API_SetNoElementsH(SHORT newVal);
  SHORT API_GetNoElementsW(void);
  void API_SetNoElementsW(SHORT newVal);
  SHORT API_ImportWG2(LPCTSTR sFName, LPCTSTR sName);
  SHORT API_BuildAssem(LPCTSTR sModName);
  void API_DisplayAll(void);
public:
  afx_msg void OnViewWhite();
protected:
  SHORT API_ExportUNV(LPCTSTR sFName);
  void API_SelectAllWGs(void);
public:
  afx_msg void OnToolsAlign();
  afx_msg void OnToolsWpsize();
  afx_msg void OnToolsRotatebyangles();
  afx_msg void OnToolsRotateabout();
  afx_msg void OnToolsCopyrotate();
  afx_msg void OnToolsScale();
  afx_msg void OnToolsReflect();
  afx_msg void OnFileInsertcataloguepart();
  afx_msg void OnLineLine();
protected:
	DOUBLE GetElDeg(void);
	void SetElDeg(DOUBLE newVal);
public:
  afx_msg void OnToolsListallproperties();
  afx_msg void OnExportCurrentmesttonas();
  afx_msg void OnNodemodifyDefinitioncoordsys();
  afx_msg void OnElementtypeRigid();
  afx_msg void OnListAllmaterials();
  afx_msg void OnListAllproperties();
  afx_msg void OnListMaterial();
  afx_msg void OnListProperty();
  afx_msg void OnViewDisplayshellthickness();
  afx_msg void OnViewDisplayelementoffsets();
  afx_msg void OnElementtypeBeam();
  afx_msg void OnElementmodifiyBeamoffset();
  afx_msg void OnElementmodifiyBeamupvectors();
  afx_msg void OnPropertyBeam();
  afx_msg void OnPropertyBeambar();
  afx_msg void OnPropertyBeamtube();
  afx_msg void OnPropertyBeambox();
  afx_msg void OnPropertyShell();
  afx_msg void OnElementmodifiyShelloffset();
  afx_msg void OnMaterialIsentropic();
  afx_msg void OnPropertymodifyChangematerial();
protected:
  SHORT API_ExportNAS(LPCTSTR inName);
public:
  afx_msg void OnExportGroupstotxt();
protected:
  void API_MergeNodes(DOUBLE dTol);
public:
  afx_msg void OnQwantaMergeboundaries();
protected:
  void API_ExportGroups(LPCTSTR sFName);
public:
  afx_msg void OnChecksMergenodes();
  afx_msg void OnMeshBuildassemblymesh();
  afx_msg void OnSurfaceSweep();
  afx_msg void OnSolverSolve();
  afx_msg void OnSolverCreaterestraint();
  afx_msg void OnSolverCreateforce();
  afx_msg void OnSurfacesonSurfacecurves();
  afx_msg void OnSurfacesSurfaceson();
  afx_msg void OnVisabilityPointson();
  afx_msg void OnCircleCirclecenreradius();
  afx_msg void OnCircleCircle3points();
  afx_msg void OnCircleArc3point();
  afx_msg void OnSelectionSurfacesbycolour();
  afx_msg void OnSelectionCurvesbycolour();
  afx_msg void OnSelectionPointsbycolour();
  afx_msg void OnWorkplainWpaligntocurve();
  afx_msg void OnWorkplainWpaligntosurface();
  afx_msg void OnWorkplainWpcentre();
  afx_msg void OnElementtypeScellcfd();
  afx_msg void OnAnalysisSolveimcompfluids();
  afx_msg void OnImportOp2();
  afx_msg void OnPostListresset();
  afx_msg void OnPostSelectresults();
  afx_msg void OnPostListselectedresset();
  afx_msg void OnPostContourrawdata();
  afx_msg void OnPostSelectvariable();
  afx_msg void OnPostTogresultslabels();
  afx_msg void OnPostDeformeddisplay();
  afx_msg void OnPostSelectdeformedresults();
  afx_msg void OnPropertySolid();
  afx_msg void OnOptionsDeformationscale();
  afx_msg void OnProperty2dplainstress();
  afx_msg void OnElementtypeRod();
  afx_msg void OnPropertyRod();
  afx_msg void OnViewDisplayelementcoordsys();
  afx_msg void OnAnalysisCreatemoment();
  afx_msg void OnAnalysisCreatepressure();
  afx_msg void OnVisabilityBoundaryconditions();
  afx_msg void OnPostExportresultstotextfile();
  afx_msg void OnNodemodifyLabel();
  afx_msg void OnElementmodifiyLabelbyinc();
  afx_msg void OnNodemodifyLabelbystart();
  afx_msg void OnElementmodifiyLabelbystart();
  afx_msg void OnMeshFreetrimesh();
  afx_msg void OnPostListelementresult();
  afx_msg void OnViewGfradientfilledbackground();
  afx_msg void OnExportExporttotext();
  afx_msg void OnElementmodifiyReverse();
  afx_msg void OnMeshqnd();
  afx_msg void OnImportTxttogroups();
  afx_msg void OnViewDisplaymaterialdurection();
  afx_msg void OnOptionsSetcolourbar();
  afx_msg void OnVisabilityCoordson();
  afx_msg void OnGroupNextgroup();
  afx_msg void OnGroupPreviousgrpup();
  afx_msg void OnGroupElementsbytype();
  afx_msg void OnGroupNodebycolour();
  afx_msg void OnGroupNodebuoutputsys();
  afx_msg void OnGroupNodebydefinitionsystem();
  afx_msg void OnGroupElementsbymid();
  afx_msg void OnPostDeleteallresultssets();
  afx_msg void OnOptionsReversecolourbar();
  afx_msg void OnSelectionInvertselection();
  afx_msg void OnQwantaDebug();
  afx_msg void OnCurvemodifyWeightlarge();
  afx_msg void OnCurvemodifyWeightmedium();
  afx_msg void OnCurvemodifyWeightthin();
  afx_msg void OnCurvemodifyDash();
  afx_msg void OnCurvemodifyDot();
  afx_msg void OnCurvemodifySolid();
  afx_msg void OnCurvemodifyCentre();
  afx_msg void OnPointmodifyCtrlpointweight();
  afx_msg void OnImportSymbolstable();
  afx_msg void OnCircleCirclecentrepoint();
  afx_msg void OnToolsReflect2d();
  afx_msg void OnToolsCopyrotate2d();
  afx_msg void OnToolsMoveto();
  afx_msg void OnToolsCopyto();
  afx_msg void OnSurfaceUn();
  afx_msg void OnMeshTetfromshellboundary();
  afx_msg void OnChecksFreefacedsp();
  afx_msg void OnMeshShellcoatsolidelements();
  afx_msg void OnChecksFreeedgedisplay();
  afx_msg void OnMeshQuadtotri();
  afx_msg void OnChecksShellnormalconsistancy();
  afx_msg void OnAnalysisLoadsets();
  afx_msg void OnLoadsbcBcsets();
  afx_msg void OnLoadsbcTemperaturesets();
  afx_msg void OnLoadsbcCreatestructuraltemp();
  afx_msg void OnLoadsbcCreatethermalnettfluxload();
  afx_msg void OnLoadsbcCreatethermaltempbc();
  afx_msg void OnSolutionListsolutionsequences();
  afx_msg void OnSolutionCreatesolutionsequence();
  afx_msg void OnSolutionCreate();
  afx_msg void OnLoadsbcListloadsets();
  afx_msg void OnLoadsbcListboundarysets();
  afx_msg void OnLoadsbcListtemperaturesets();
  afx_msg void OnLoadsbcCreateaccelerationbodyload();
  afx_msg void OnElementtypeTranslationalspring();
  afx_msg void OnElementtypeRotationalspring();
  afx_msg void OnElementmodifiySpringcoordsystem();
  afx_msg void OnPropertyRotationalspring();
  afx_msg void OnPropertyTranslationalspring();
  afx_msg void OnChecksNegativevolumeelements();
  afx_msg void OnChecksCheckshellelementaspectration();
  afx_msg void OnChecksChecktetcollapse();
  afx_msg void OnElementtypeMass();
  afx_msg void OnPropertyLumpedmass();
  afx_msg void OnVisabilityWorkplane();
  afx_msg void OnToolsMeasureangle();
  afx_msg void OnLoadsbcCreaterotationalbodyload();

  afx_msg void OnToolsElementmasssummation();
  afx_msg void OnElementmodifiyShellmatcorrdsystem();
  afx_msg void OnChecksCoincidentelements();
  afx_msg void OnNodemodifyChangexordinate();
  afx_msg void OnNodemodifyChangeyordinate();
  afx_msg void OnNodemodifyChangezordinate();
  afx_msg void OnPropertymodifyEditpropertyvalues();
  afx_msg void OnPropertyEditmaterialvalues();
  afx_msg void OnPropertyBeamBasic();
  afx_msg void OnViewSurfacedirectionmarkers();
  afx_msg void OnPostListnodalresults();
  afx_msg void OnCurvemodifyInsertknot();
  afx_msg void OnPostAnimate();
  afx_msg void OnPostAnimateneg();
  afx_msg void OnPostFramedelay();
  afx_msg void OnPostAnimationframes();
  afx_msg void OnElementmodifiyBeamendarelease();
  afx_msg void OnElementmodifiyBeamendbrelease();
  afx_msg void OnOptionsDeformationoffset();
  afx_msg void OnPostListresultsvectors();
  afx_msg void OnToolsEditobject();
  afx_msg void OnOptionsVectorscale();
  afx_msg void OnPostSelectvectorresults();
  afx_msg void OnPostClearresultsvectors();
  afx_msg void OnMeshAdvancingfrontsurfacemeshtri();
  afx_msg void OnLineMultiline();
  afx_msg void OnChecks2dsectionpropertiesaixxiyyetc();
  afx_msg void OnMeshmanagementListallmeshes();
  afx_msg void OnMeshmanagementCreatenewmesh();
  afx_msg void OnMeshmanagementSetactivemesh();
  afx_msg void OnMeshmanagementTogglemeshvisability();
  afx_msg void OnMeshmanagementDeletemesh();
  afx_msg void OnViewHideentities();
  afx_msg void OnViewShowallhidden();
  afx_msg void OnPostListresponsedata();
  afx_msg void OnMeshMeshsizeonsurface();
  afx_msg void OnPartmodifyExtract();
  afx_msg void OnChecksTetcircumsphere();
  afx_msg void OnFemtoolsMeshsizeoncurves();
//  afx_msg void OnEditRedo();
//  afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
//  afx_msg void OnFileOpen();
  virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
  afx_msg void OnCurvetoolsText();
  afx_msg void OnPropertyPcomp();
  afx_msg void OnMaterialOrthotropic();
  afx_msg void OnPropertyDisplaylaminatestack();
  afx_msg void OnPropertyPbush();
  afx_msg void OnManipulationDivideinto();
  afx_msg void OnManipulationEnvelopemaximum();
  afx_msg void OnManipulationEnvelopeminimum();
  afx_msg void OnManipulationScale();
  afx_msg void OnEditToggleon();
  afx_msg void OnPropertyBeamT2();
  afx_msg void OnPropertyBeamChan2();
  afx_msg void OnPropertyBeamI2();
  afx_msg void OnPropertyBeamL();
  afx_msg void OnElementmodifiyBeamoffsetinbeamy();
  afx_msg void OnElementmodifiyBeamoffsetinbeamz();
  afx_msg void OnToolsPlanet();
  afx_msg void OnFemtoolsSweepnodestoshells();
  afx_msg void OnFemtoolsSweepnodestobeams();
  afx_msg void OnPostListresponsedataallvars();
  afx_msg void OnPostLabelresponseentities();
  afx_msg void OnPostGraphresponsedata();

  afx_msg void OnFemtoolsSweepnodestobeams33361();
  afx_msg void OnFemtoolsSweepnodestoshells33362();
  afx_msg void OnViewHighlightlimit();
  afx_msg void OnSelectionRbecentrenodes();
  afx_msg void OnChecksCountf();
  afx_msg void OnCurvemodifySplitatpoint();
  afx_msg void OnElementmodifiyIntersecttrielements();
  afx_msg void OnNodemodifyEquivalencelab();
  afx_msg void OnElementmodifiyColourbypid();
  afx_msg void OnExportIncludefile();
  afx_msg void OnGroupGroupfromincludefile();
  afx_msg void OnMeshmanagementSetincludefileno();
  afx_msg void OnElementmodifiyColourbyincludefile();
  afx_msg void OnCurvetoolsOrthosnap();
  afx_msg void OnCurvemodifyTrim();
  afx_msg void OnListGapsbetweenlabels();
  afx_msg void OnListGapsbetweenmatsandpropslabels();
  afx_msg void OnElementmodifiyInsertspringonrigid();
  afx_msg void OnFemtoolsSweepedgesoutward();
  afx_msg void OnObjectsizePoint();
  afx_msg void OnObjectsizeNode();
  afx_msg void OnObjectsizeLumpmass();
  afx_msg void OnObjectsizeElementedge();
  afx_msg void OnObjectsizeElementfreeedge();
  afx_msg void OnObjectsizeElementfreeface();
  afx_msg void OnObjectsizeWorkplanelines();
  afx_msg void OnObjectsizeBeams();
  afx_msg void OnObjectsizeText();
  afx_msg void OnExportExportviewmatrix();
  afx_msg void OnImportImportviewmatrix();
  afx_msg void OnCurvetoolsLinethrouptandtangenttocircle();
  afx_msg void OnCurvetoolsLinetangentto2circles();
  afx_msg void OnCurvetoolsPointsoncircle();
  afx_msg void OnEditPolartranslatedfrom();
  void DeleteObjs();
  afx_msg void OnViewTogglecontrolpointvisability();
  afx_msg void OnExportExportdxf();
  afx_msg void OnCurvemodifyLayernumber();
  afx_msg void OnSelectionSelectcurve();
  afx_msg void OnViewToggleoncirclestartmarkers();
  afx_msg void OnToolsInsertbitmapbackground();
  afx_msg void OnViewToggleon();
  afx_msg void OnQfilterNodes();
  afx_msg void OnQfilterElements();
  afx_msg void OnQfilterPoints();
  afx_msg void OnQfilterCurves();
  afx_msg void OnQfilterSurface();
  afx_msg void OnQfilterAll();
  afx_msg void OnDimensiontoolsDimsize();
  afx_msg void OnDimensiontoolsAligneddim();
  afx_msg void OnDimensiontoolsLineardim();
  afx_msg void OnDimensiontoolsHorizontaldim();
  afx_msg void OnDimensiontoolsVerticaldim();
  afx_msg void OnDimensiontoolsLeadertext();
  afx_msg void OnDimensiontoolsRadiusdim();
  afx_msg void OnDimensiontoolsDiameterdim();
  afx_msg void OnDimensiontoolsAngulardimby3points();
  afx_msg void OnDimensiontoolsDragdim();
  afx_msg void OnDimensiontoolsCirclecentremarker();
  afx_msg void OnElementtypeBush();
  afx_msg void OnEditGlobalpreferences();
  afx_msg void OnLoadsbcCreatetempd();
  afx_msg void OnLoadsbcCreategrav();
  afx_msg void OnExportCurrentStl();
  afx_msg void OnImportStltotrimesh();
};


