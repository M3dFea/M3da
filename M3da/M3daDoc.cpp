
// M3daDoc.cpp : implementation of the CM3daDoc class
//

#include "stdafx.h"
#include "M3da.h"
#include "M3daDoc.h"
#include "GLOBAL_VARS.h"
#include <iostream>
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//The data base class
DBase *cDBase;
zMnu* pMnu;

// CM3daDoc

IMPLEMENT_DYNCREATE(CM3daDoc, CDocument)

BEGIN_MESSAGE_MAP(CM3daDoc, CDocument)
  ON_COMMAND(ID_VIEW_DISPLAYALL, &CM3daDoc::OnViewDisplayall)
  ON_COMMAND(ID_EDIT_DES, &CM3daDoc::OnEditDes)
  ON_COMMAND(ID_EDIT_INFORMATION, &CM3daDoc::OnEditInformation)
  ON_COMMAND(ID_EDIT_KEYIN, &CM3daDoc::OnEditKeyin)
  ON_COMMAND(ID_EDIT_PICK, &CM3daDoc::OnEditPick)
  ON_COMMAND(ID_EDIT_BETWEEN, &CM3daDoc::OnEditBetween)
  ON_COMMAND(ID_EDIT_TRANSLATEDFROM, &CM3daDoc::OnEditTranslatedfrom)
  ON_COMMAND(ID_EDIT_FILTERNONE, &CM3daDoc::OnEditFilternone)
  ON_COMMAND(ID_EDIT_CANCEL, &CM3daDoc::OnEditCancel)
  ON_COMMAND(ID_EDIT_DONE, &CM3daDoc::OnEditDone)
  ON_COMMAND(ID_GROUP_ADDTOGROUP, &CM3daDoc::OnGroupAddtogroup)
  ON_COMMAND(ID_GROUP_REMOVEFROMGROUP, &CM3daDoc::OnGroupRemovefromgroup)
  ON_COMMAND(ID_GROUP_ADDGROUP, &CM3daDoc::OnGroupAddgroup)
  ON_COMMAND(ID_GROUP_REMOVEGROUP, &CM3daDoc::OnGroupRemovegroup)
  ON_COMMAND(ID_GROUP_SETCURRENT, &CM3daDoc::OnGroupSetcurrent)
  ON_COMMAND(ID_GROUP_LISTGROUPS, &CM3daDoc::OnGroupListgroups)
  ON_COMMAND(ID_IMPORT_UNV, &CM3daDoc::OnImportUnv)
  ON_COMMAND(ID_IMPORT_DAT, &CM3daDoc::OnImportDat)
  ON_COMMAND(ID_IMPORT_IGES, &CM3daDoc::OnImportIges)
  ON_COMMAND(ID_VIEW_NODESOFF, &CM3daDoc::OnViewNodesoff)
  ON_COMMAND(ID_CREATE_POINT, &CM3daDoc::OnCreatePoint)
//  ON_COMMAND(ID_LINE_LINE, &CM3daDoc::OnLineLine)
  ON_COMMAND(ID_LINE_LINEX, &CM3daDoc::OnLineLinex)
  ON_COMMAND(ID_LINE_LINEY, &CM3daDoc::OnLineLiney)
  ON_COMMAND(ID_LINE_LINEZ, &CM3daDoc::OnLineLinez)
  ON_COMMAND(ID_CREATE_CIRCLE, &CM3daDoc::OnCreateCircle)
  ON_COMMAND(ID_CREATE_CURVE, &CM3daDoc::OnCreateCurve)
  ON_COMMAND(ID_SURFACE_LOFT, &CM3daDoc::OnSurfaceLoft)
  ON_COMMAND(ID_SURFACE_EXTRUDE, &CM3daDoc::OnSurfaceExtrude)
  ON_COMMAND(ID_SURFACE_REVOLVE, &CM3daDoc::OnSurfaceRevolve)
  ON_COMMAND(ID_CREATE_NODE, &CM3daDoc::OnCreateNode)
  ON_COMMAND(ID_CREATE_ELEMENT, &CM3daDoc::OnCreateElement)
  ON_COMMAND(ID_ELEMENTTYPE_TRI, &CM3daDoc::OnElementtypeTri)
  ON_COMMAND(ID_ELEMENTTYPE_QUAD, &CM3daDoc::OnElementtypeQuad)
  ON_COMMAND(ID_ELEMENTTYPE_BRICK, &CM3daDoc::OnElementtypeBrick)
  ON_COMMAND(ID_ELEMENTTYPE_WEDGE, &CM3daDoc::OnElementtypeWedge)
  ON_COMMAND(ID_ELEMENTTYPE_TET, &CM3daDoc::OnElementtypeTet)
  ON_COMMAND(ID_CREATE_COPYNODES, &CM3daDoc::OnCreateCopynodes)
  ON_COMMAND(ID_CREATE_NODEMOVETO, &CM3daDoc::OnCreateNodemoveto)
  ON_COMMAND(ID_CREATE_NODESBETWEEN, &CM3daDoc::OnCreateNodesbetween)
  ON_COMMAND(ID_CREATE_NODESONCURVE, &CM3daDoc::OnCreateNodesoncurve)
  ON_COMMAND(ID_VIEW_SELECTALL, &CM3daDoc::OnViewSelectall)
  ON_COMMAND(ID_TOOLS_MOVE, &CM3daDoc::OnToolsMove)
  ON_COMMAND(ID_TOOLS_COPY, &CM3daDoc::OnToolsCopy)
  ON_COMMAND(ID_TOOLS_WPMODE, &CM3daDoc::OnToolsWpmode)
  ON_COMMAND(ID_TOOLS_WPALIGN, &CM3daDoc::OnToolsWpalign)
  ON_COMMAND(ID_TOOLS_WPGLOBAL, &CM3daDoc::OnToolsWpglobal)
  ON_COMMAND(ID_VIEW_CONTROLPOINT, &CM3daDoc::OnViewControlpoint)
  ON_COMMAND(ID_TOOLS_COLOUR, &CM3daDoc::OnToolsColour)
  ON_COMMAND(ID_TOOLS_SETCURRENTMESH, &CM3daDoc::OnToolsSetcurrentmesh)
  ON_COMMAND(ID_EXPORT_CURRENTMESHTO, &CM3daDoc::OnExportCurrentmeshto)
  ON_COMMAND(ID_GROUP_CREATEGROUP, &CM3daDoc::OnGroupCreategroup)
  ON_COMMAND(ID_TOOLS_DELETE, &CM3daDoc::OnToolsDelete)
  ON_COMMAND(ID_CREATE_FITTEDCURVE, &CM3daDoc::OnCreateFittedcurve)
  ON_COMMAND(ID_EDIT_ONSCREENLOCATION, &CM3daDoc::OnEditOnscreenlocation)
  ON_COMMAND(ID_EDIT_REPEATLASTCOMMAND, &CM3daDoc::OnEditRepeatlastcommand)
  ON_COMMAND(ID_EDIT_IITERSECTION, &CM3daDoc::OnEditIitersection)
  ON_COMMAND(ID_EDIT_PROJECT, &CM3daDoc::OnEditProject)
  ON_COMMAND(ID_CREATE_FILLET, &CM3daDoc::OnCreateFillet)
  ON_COMMAND(ID_CREATE_OFFSET, &CM3daDoc::OnCreateOffset)
  ON_COMMAND(ID_LINE_LINEANGLE, &CM3daDoc::OnLineLineangle)
  ON_COMMAND(ID_CREATE_MAKECORNER, &CM3daDoc::OnCreateMakecorner)
  ON_COMMAND(ID_CREATE_RECTANGLE, &CM3daDoc::OnCreateRectangle)
  ON_COMMAND(ID_SURFACE_PROJECTCURVE, &CM3daDoc::OnSurfaceProjectcurve)
  ON_COMMAND(ID_SURFACE_TRIMSURFACE, &CM3daDoc::OnSurfaceTrimsurface)
  ON_COMMAND(ID_SURFACE_PLANAR, &CM3daDoc::OnSurfacePlanar)
  ON_COMMAND(ID_SURFACE_INTERNALTRIMLOOP, &CM3daDoc::OnSurfaceInternaltrimloop)
  ON_COMMAND(ID_CREATE_COORDSYS, &CM3daDoc::OnCreateCoordsys)
  ON_COMMAND(ID_GROUP_ELEMENTSBYPID, &CM3daDoc::OnGroupElementsbypid)
  ON_COMMAND(ID_GROUP_ELEMENTSBYCOLOUR, &CM3daDoc::OnGroupElementsbycolour)
  ON_COMMAND(ID_SELECTION_ELEMENTSBYPID, &CM3daDoc::OnSelectionElementsbypid)
  ON_COMMAND(ID_SELECTION_ELEMENTSBYCOLOUR, &CM3daDoc::OnSelectionElementsbycolour)
  ON_COMMAND(ID_SELECTION_NODESBYCOLOUR, &CM3daDoc::OnSelectionNodesbycolour)
  ON_COMMAND(ID_SELECTION_SELECTALL, &CM3daDoc::OnSelectionSelectall)
  ON_COMMAND(ID_SELECTION_RELATEDTO, &CM3daDoc::OnSelectionRelatedto)
  ON_COMMAND(ID_SELECTION_ELEMENTSBYTYPE, &CM3daDoc::OnSelectionElementsbytype)
  ON_COMMAND(ID_CREATE_COORDSYSLINE, &CM3daDoc::OnCreateCoordsysline)
  ON_COMMAND(ID_SELECTION_ELAT, &CM3daDoc::OnSelectionElat)
  ON_COMMAND(ID_TOOLS_LISTPROPERTY, &CM3daDoc::OnToolsListproperty)
  ON_COMMAND(ID_TOOLS_MEASURE, &CM3daDoc::OnToolsMeasure)
  ON_COMMAND(ID_ELEMENTMODIFIY_PID, &CM3daDoc::OnElementmodifiyPid)
  ON_COMMAND(ID_NODEMODIFY_OUTPUTCOORDSYS, &CM3daDoc::OnNodemodifyOutputcoordsys)
  ON_COMMAND(ID_EDIT_RELATEDTO, &CM3daDoc::OnEditRelatedto)
  ON_COMMAND(ID_EDIT_LABEL, &CM3daDoc::OnEditLabel)
  ON_COMMAND(ID_SELECTION_ELEMENTSBYMATERIAL, &CM3daDoc::OnSelectionElementsbymaterial)
  ON_COMMAND(ID_MESH_MAPPEDSURFACEMESH, &CM3daDoc::OnMeshMappedsurfacemesh)
  ON_COMMAND(ID_MESH_MAPPEDTRIMESH, &CM3daDoc::OnMeshMappedtrimesh)
  ON_COMMAND(ID_CHECKS_COINCIDENTNODES, &CM3daDoc::OnChecksCoincidentnodes)
  ON_COMMAND(ID_MESH_SWEEPELEMENTS, &CM3daDoc::OnMeshSweepelements)
  ON_COMMAND(ID_VIEW_SHADEDEDGES, &CM3daDoc::OnViewShadededges)
//  ON_COMMAND(ID_VIEW_LINE, &CM3daDoc::OnViewLine)
ON_COMMAND(ID_VISABILITY_NODEON, &CM3daDoc::OnVisabilityNodeon)
ON_COMMAND(ID_VISABILITY_ELEMENTON, &CM3daDoc::OnVisabilityElementon)
ON_COMMAND(ID_VIEW_NODESASK, &CM3daDoc::OnViewNodesask)
ON_COMMAND(ID_VISABILITY_SURFACESON, &CM3daDoc::OnVisabilitySurfaceson)
ON_COMMAND(ID_VISABILITY_CURVESON, &CM3daDoc::OnVisabilityCurveson)
ON_COMMAND(ID_VISABILITY_ALLVISABLE, &CM3daDoc::OnVisabilityAllvisable)
ON_COMMAND(ID_VIEW_LABELENTITIES, &CM3daDoc::OnViewLabelentities)
ON_COMMAND(ID_QWANTA_IMPORTCATALOGUE, &CM3daDoc::OnQwantaImportcatalogue)
ON_COMMAND(ID_QWANTA_IMPORTSECTIONTABLE, &CM3daDoc::OnQwantaImportsectiontable)
ON_COMMAND(ID_QWANTA_IMPORTWAVEGUIDE, &CM3daDoc::OnQwantaImportwaveguide)
ON_COMMAND(ID_QWANTA_1D, &CM3daDoc::OnQwanta1d)
ON_COMMAND(ID_QWANTA_MESHDENSITYTOGGLE, &CM3daDoc::OnQwantaMeshdensitytoggle)
ON_COMMAND(ID_QWANTA_GENERATEMESH, &CM3daDoc::OnQwantaGeneratemesh)
ON_COMMAND(ID_CATALOGUEDISPLAY_DISPLAYCATALUGUE, &CM3daDoc::OnCataloguedisplayDisplaycatalugue)
ON_COMMAND(ID_CATALOGUEDISPLAY_DISPLAYNEXT, &CM3daDoc::OnCataloguedisplayDisplaynext)
ON_COMMAND(ID_CATALOGUEDISPLAY_DISPLAYPREVIOUS, &CM3daDoc::OnCataloguedisplayDisplayprevious)
ON_COMMAND(ID_VISABILITY_ASSEMBLIES, &CM3daDoc::OnVisabilityAssemblies)
ON_COMMAND(ID_QWANTA_BUILDAMDEXPORT, &CM3daDoc::OnQwantaBuildamdexport)
ON_COMMAND(ID_GROUP_DELETEALLGROUPS, &CM3daDoc::OnGroupDeleteallgroups)
//ON_COMMAND(ID_FILE_SAVE, &CM3daDoc::OnFileSave)
//ON_COMMAND(ID_FILE_NEW, &CM3daDoc::OnFileNew)
//ON_COMMAND(ID_FILE_SAVE_AS, &CM3daDoc::OnFileSaveAs)
//ON_COMMAND(ID_FILE_OPEN, &CM3daDoc::OnFileOpen)
ON_COMMAND(ID_VIEW_WHITE, &CM3daDoc::OnViewWhite)
ON_COMMAND(ID_TOOLS_ALIGN, &CM3daDoc::OnToolsAlign)
ON_COMMAND(ID_TOOLS_WPSIZE, &CM3daDoc::OnToolsWpsize)
ON_COMMAND(ID_TOOLS_ROTATEBYANGLES, &CM3daDoc::OnToolsRotatebyangles)
ON_COMMAND(ID_TOOLS_ROTATEABOUT, &CM3daDoc::OnToolsRotateabout)
ON_COMMAND(ID_TOOLS_COPYROTATE, &CM3daDoc::OnToolsCopyrotate)
ON_COMMAND(ID_TOOLS_SCALE, &CM3daDoc::OnToolsScale)
ON_COMMAND(ID_TOOLS_REFLECT, &CM3daDoc::OnToolsReflect)
ON_COMMAND(ID_FILE_INSERTCATALOGUEPART, &CM3daDoc::OnFileInsertcataloguepart)
ON_COMMAND(ID_LINE_LINE, &CM3daDoc::OnLineLine)
ON_COMMAND(ID_TOOLS_LISTALLPROPERTIES, &CM3daDoc::OnToolsListallproperties)
ON_COMMAND(ID_EXPORT_CURRENTMESTTONAS, &CM3daDoc::OnExportCurrentmesttonas)
ON_COMMAND(ID_NODEMODIFY_DEFINITIONCOORDSYS, &CM3daDoc::OnNodemodifyDefinitioncoordsys)
ON_COMMAND(ID_ELEMENTTYPE_RIGID, &CM3daDoc::OnElementtypeRigid)
ON_COMMAND(ID_LIST_ALLMATERIALS, &CM3daDoc::OnListAllmaterials)
ON_COMMAND(ID_LIST_ALLPROPERTIES, &CM3daDoc::OnListAllproperties)
ON_COMMAND(ID_LIST_MATERIAL, &CM3daDoc::OnListMaterial)
ON_COMMAND(ID_LIST_PROPERTY, &CM3daDoc::OnListProperty)
ON_COMMAND(ID_VIEW_DISPLAYSHELLTHICKNESS, &CM3daDoc::OnViewDisplayshellthickness)
ON_COMMAND(ID_VIEW_DISPLAYELEMENTOFFSETS, &CM3daDoc::OnViewDisplayelementoffsets)
ON_COMMAND(ID_ELEMENTTYPE_BEAM, &CM3daDoc::OnElementtypeBeam)
ON_COMMAND(ID_ELEMENTMODIFIY_BEAMOFFSET, &CM3daDoc::OnElementmodifiyBeamoffset)
ON_COMMAND(ID_ELEMENTMODIFIY_BEAMUPVECTORS, &CM3daDoc::OnElementmodifiyBeamupvectors)
ON_COMMAND(ID_PROPERTY_BEAM, &CM3daDoc::OnPropertyBeam)
ON_COMMAND(ID_PROPERTY_BEAMBAR, &CM3daDoc::OnPropertyBeambar)
ON_COMMAND(ID_PROPERTY_BEAMTUBE, &CM3daDoc::OnPropertyBeamtube)
ON_COMMAND(ID_PROPERTY_BEAMBOX, &CM3daDoc::OnPropertyBeambox)
ON_COMMAND(ID_PROPERTY_SHELL, &CM3daDoc::OnPropertyShell)
ON_COMMAND(ID_ELEMENTMODIFIY_SHELLOFFSET, &CM3daDoc::OnElementmodifiyShelloffset)
ON_COMMAND(ID_MATERIAL_ISENTROPIC, &CM3daDoc::OnMaterialIsentropic)
ON_COMMAND(ID_PROPERTYMODIFY_CHANGEMATERIAL, &CM3daDoc::OnPropertymodifyChangematerial)
ON_COMMAND(ID_EXPORT_GROUPSTOTXT, &CM3daDoc::OnExportGroupstotxt)
ON_COMMAND(ID_QWANTA_MERGEBOUNDARIES, &CM3daDoc::OnQwantaMergeboundaries)
ON_COMMAND(ID_CHECKS_MERGENODES, &CM3daDoc::OnChecksMergenodes)
ON_COMMAND(ID_MESH_BUILDASSEMBLYMESH, &CM3daDoc::OnMeshBuildassemblymesh)
ON_COMMAND(ID_SURFACE_SWEEP, &CM3daDoc::OnSurfaceSweep)
ON_COMMAND(ID_SOLVER_SOLVE, &CM3daDoc::OnSolverSolve)
ON_COMMAND(ID_SOLVER_CREATERESTRAINT, &CM3daDoc::OnSolverCreaterestraint)
ON_COMMAND(ID_SOLVER_CREATEFORCE, &CM3daDoc::OnSolverCreateforce)
ON_COMMAND(ID_SURFACESON_SURFACECURVES, &CM3daDoc::OnSurfacesonSurfacecurves)
ON_COMMAND(ID_SURFACES_SURFACESON, &CM3daDoc::OnSurfacesSurfaceson)
ON_COMMAND(ID_VISABILITY_POINTSON, &CM3daDoc::OnVisabilityPointson)
ON_COMMAND(ID_CIRCLE_CIRCLECENRERADIUS, &CM3daDoc::OnCircleCirclecenreradius)
ON_COMMAND(ID_CIRCLE_CIRCLE3POINTS, &CM3daDoc::OnCircleCircle3points)
ON_COMMAND(ID_CIRCLE_ARC3POINT, &CM3daDoc::OnCircleArc3point)
ON_COMMAND(ID_SELECTION_SURFACESBYCOLOUR, &CM3daDoc::OnSelectionSurfacesbycolour)
ON_COMMAND(ID_SELECTION_CURVESBYCOLOUR, &CM3daDoc::OnSelectionCurvesbycolour)
ON_COMMAND(ID_SELECTION_POINTSBYCOLOUR, &CM3daDoc::OnSelectionPointsbycolour)
ON_COMMAND(ID_WORKPLAIN_WPALIGNTOCURVE, &CM3daDoc::OnWorkplainWpaligntocurve)
ON_COMMAND(ID_WORKPLAIN_WPALIGNTOSURFACE, &CM3daDoc::OnWorkplainWpaligntosurface)
ON_COMMAND(ID_WORKPLAIN_WPCENTRE, &CM3daDoc::OnWorkplainWpcentre)
ON_COMMAND(ID_ELEMENTTYPE_SCELLCFD, &CM3daDoc::OnElementtypeScellcfd)
ON_COMMAND(ID_ANALYSIS_SOLVEIMCOMPFLUIDS, &CM3daDoc::OnAnalysisSolveimcompfluids)
ON_COMMAND(ID_IMPORT_OP2, &CM3daDoc::OnImportOp2)
ON_COMMAND(ID_POST_LISTRESSET, &CM3daDoc::OnPostListresset)
ON_COMMAND(ID_POST_SELECTRESULTS, &CM3daDoc::OnPostSelectresults)
ON_COMMAND(ID_POST_LISTSELECTEDRESSET, &CM3daDoc::OnPostListselectedresset)
ON_COMMAND(ID_POST_CONTOURRAWDATA, &CM3daDoc::OnPostContourrawdata)
ON_COMMAND(ID_POST_SELECTVARIABLE, &CM3daDoc::OnPostSelectvariable)
ON_COMMAND(ID_POST_TOGRESULTSLABELS, &CM3daDoc::OnPostTogresultslabels)
ON_COMMAND(ID_POST_DEFORMEDDISPLAY, &CM3daDoc::OnPostDeformeddisplay)
ON_COMMAND(ID_POST_SELECTDEFORMEDRESULTS, &CM3daDoc::OnPostSelectdeformedresults)
ON_COMMAND(ID_PROPERTY_SOLID, &CM3daDoc::OnPropertySolid)
ON_COMMAND(ID_OPTIONS_DEFORMATIONSCALE, &CM3daDoc::OnOptionsDeformationscale)
ON_COMMAND(ID_PROPERTY_2DPLAINSTRESS, &CM3daDoc::OnProperty2dplainstress)
ON_COMMAND(ID_ELEMENTTYPE_ROD, &CM3daDoc::OnElementtypeRod)
ON_COMMAND(ID_PROPERTY_ROD, &CM3daDoc::OnPropertyRod)
ON_COMMAND(ID_VIEW_DISPLAYELEMENTCOORDSYS, &CM3daDoc::OnViewDisplayelementcoordsys)
ON_COMMAND(ID_ANALYSIS_CREATEMOMENT, &CM3daDoc::OnAnalysisCreatemoment)
ON_COMMAND(ID_ANALYSIS_CREATEPRESSURE, &CM3daDoc::OnAnalysisCreatepressure)
ON_COMMAND(ID_VISABILITY_BOUNDARYCONDITIONS, &CM3daDoc::OnVisabilityBoundaryconditions)
ON_COMMAND(ID_POST_EXPORTRESULTSTOTEXTFILE, &CM3daDoc::OnPostExportresultstotextfile)
ON_COMMAND(ID_NODEMODIFY_LABEL, &CM3daDoc::OnNodemodifyLabel)
ON_COMMAND(ID_ELEMENTMODIFIY_LABELBYINC, &CM3daDoc::OnElementmodifiyLabelbyinc)
ON_COMMAND(ID_NODEMODIFY_LABELBYSTART, &CM3daDoc::OnNodemodifyLabelbystart)
ON_COMMAND(ID_ELEMENTMODIFIY_LABELBYSTART, &CM3daDoc::OnElementmodifiyLabelbystart)
ON_COMMAND(ID_MESH_FREETRIMESH, &CM3daDoc::OnMeshFreetrimesh)
ON_COMMAND(ID_POST_LISTELEMENTRESULT, &CM3daDoc::OnPostListelementresult)
ON_COMMAND(ID_VIEW_GFRADIENTFILLEDBACKGROUND, &CM3daDoc::OnViewGfradientfilledbackground)
ON_COMMAND(ID_EXPORT_EXPORTTOTEXT, &CM3daDoc::OnExportExporttotext)
ON_COMMAND(ID_ELEMENTMODIFIY_REVERSE, &CM3daDoc::OnElementmodifiyReverse)
ON_COMMAND(ID_MESHQND, &CM3daDoc::OnMeshqnd)
ON_COMMAND(ID_IMPORT_TXTTOGROUPS, &CM3daDoc::OnImportTxttogroups)
ON_COMMAND(ID_VIEW_DISPLAYMATERIALDURECTION, &CM3daDoc::OnViewDisplaymaterialdurection)
ON_COMMAND(ID_OPTIONS_SETCOLOURBAR, &CM3daDoc::OnOptionsSetcolourbar)
ON_COMMAND(ID_VISABILITY_COORDSON, &CM3daDoc::OnVisabilityCoordson)
ON_COMMAND(ID_GROUP_NEXTGROUP, &CM3daDoc::OnGroupNextgroup)
ON_COMMAND(ID_GROUP_PREVIOUSGRPUP, &CM3daDoc::OnGroupPreviousgrpup)
ON_COMMAND(ID_GROUP_ELEMENTSBYTYPE, &CM3daDoc::OnGroupElementsbytype)
ON_COMMAND(ID_GROUP_NODEBYCOLOUR, &CM3daDoc::OnGroupNodebycolour)
ON_COMMAND(ID_GROUP_NODEBUOUTPUTSYS, &CM3daDoc::OnGroupNodebuoutputsys)
ON_COMMAND(ID_GROUP_NODEBYDEFINITIONSYSTEM, &CM3daDoc::OnGroupNodebydefinitionsystem)
ON_COMMAND(ID_GROUP_ELEMENTSBYMID, &CM3daDoc::OnGroupElementsbymid)
ON_COMMAND(ID_POST_DELETEALLRESULTSSETS, &CM3daDoc::OnPostDeleteallresultssets)
ON_COMMAND(ID_OPTIONS_REVERSECOLOURBAR, &CM3daDoc::OnOptionsReversecolourbar)
ON_COMMAND(ID_SELECTION_INVERTSELECTION, &CM3daDoc::OnSelectionInvertselection)
ON_COMMAND(ID_QWANTA_DEBUG, &CM3daDoc::OnQwantaDebug)
ON_COMMAND(ID_CURVEMODIFY_WEIGHTLARGE, &CM3daDoc::OnCurvemodifyWeightlarge)
ON_COMMAND(ID_CURVEMODIFY_WEIGHTMEDIUM, &CM3daDoc::OnCurvemodifyWeightmedium)
ON_COMMAND(ID_CURVEMODIFY_WEIGHTTHIN, &CM3daDoc::OnCurvemodifyWeightthin)
ON_COMMAND(ID_CURVEMODIFY_DASH, &CM3daDoc::OnCurvemodifyDash)
ON_COMMAND(ID_CURVEMODIFY_DOT, &CM3daDoc::OnCurvemodifyDot)
ON_COMMAND(ID_CURVEMODIFY_SOLID, &CM3daDoc::OnCurvemodifySolid)
ON_COMMAND(ID_CURVEMODIFY_CENTRE, &CM3daDoc::OnCurvemodifyCentre)
ON_COMMAND(ID_POINTMODIFY_CTRLPOINTWEIGHT, &CM3daDoc::OnPointmodifyCtrlpointweight)
ON_COMMAND(ID_IMPORT_SYMBOLSTABLE, &CM3daDoc::OnImportSymbolstable)
ON_COMMAND(ID_CIRCLE_CIRCLECENTREPOINT, &CM3daDoc::OnCircleCirclecentrepoint)
ON_COMMAND(ID_TOOLS_REFLECT2D, &CM3daDoc::OnToolsReflect2d)
ON_COMMAND(ID_TOOLS_COPYROTATE2D, &CM3daDoc::OnToolsCopyrotate2d)
ON_COMMAND(ID_TOOLS_MOVETO, &CM3daDoc::OnToolsMoveto)
ON_COMMAND(ID_TOOLS_COPYTO, &CM3daDoc::OnToolsCopyto)
ON_COMMAND(ID_SURFACE_UN, &CM3daDoc::OnSurfaceUn)
ON_COMMAND(ID_MESH_TETFROMSHELLBOUNDARY, &CM3daDoc::OnMeshTetfromshellboundary)
ON_COMMAND(ID_CHECKS_FREEFACEDSP, &CM3daDoc::OnChecksFreefacedsp)
ON_COMMAND(ID_MESH_SHELLCOATSOLIDELEMENTS, &CM3daDoc::OnMeshShellcoatsolidelements)
ON_COMMAND(ID_CHECKS_FREEEDGEDISPLAY, &CM3daDoc::OnChecksFreeedgedisplay)
ON_COMMAND(ID_MESH_QUADTOTRI, &CM3daDoc::OnMeshQuadtotri)
ON_COMMAND(ID_CHECKS_SHELLNORMALCONSISTANCY, &CM3daDoc::OnChecksShellnormalconsistancy)
ON_COMMAND(ID_ANALYSIS_LOADSETS, &CM3daDoc::OnAnalysisLoadsets)
ON_COMMAND(ID_LOADSBC_BCSETS, &CM3daDoc::OnLoadsbcBcsets)
ON_COMMAND(ID_LOADSBC_TEMPERATURESETS, &CM3daDoc::OnLoadsbcTemperaturesets)
ON_COMMAND(ID_LOADSBC_CREATESTRUCTURALTEMP, &CM3daDoc::OnLoadsbcCreatestructuraltemp)
ON_COMMAND(ID_LOADSBC_CREATETHERMALNETTFLUXLOAD, &CM3daDoc::OnLoadsbcCreatethermalnettfluxload)
ON_COMMAND(ID_LOADSBC_CREATETHERMALTEMPBC, &CM3daDoc::OnLoadsbcCreatethermaltempbc)
ON_COMMAND(ID_SOLUTION_LISTSOLUTIONSEQUENCES, &CM3daDoc::OnSolutionListsolutionsequences)
ON_COMMAND(ID_SOLUTION_CREATESOLUTIONSEQUENCE, &CM3daDoc::OnSolutionCreatesolutionsequence)
ON_COMMAND(ID_SOLUTION_CREATE, &CM3daDoc::OnSolutionCreate)
ON_COMMAND(ID_LOADSBC_LISTLOADSETS, &CM3daDoc::OnLoadsbcListloadsets)
ON_COMMAND(ID_LOADSBC_LISTBOUNDARYSETS, &CM3daDoc::OnLoadsbcListboundarysets)
ON_COMMAND(ID_LOADSBC_LISTTEMPERATURESETS, &CM3daDoc::OnLoadsbcListtemperaturesets)
ON_COMMAND(ID_LOADSBC_CREATEACCELERATIONBODYLOAD, &CM3daDoc::OnLoadsbcCreateaccelerationbodyload)
ON_COMMAND(ID_ELEMENTTYPE_TRANSLATIONALSPRING, &CM3daDoc::OnElementtypeTranslationalspring)
ON_COMMAND(ID_ELEMENTTYPE_ROTATIONALSPRING, &CM3daDoc::OnElementtypeRotationalspring)
ON_COMMAND(ID_ELEMENTMODIFIY_SPRINGCOORDSYSTEM, &CM3daDoc::OnElementmodifiySpringcoordsystem)
ON_UPDATE_COMMAND_UI(ID_INDC_LC, &CM3daDoc::OnUpdateLC)
ON_UPDATE_COMMAND_UI(ID_INDC_BC, &CM3daDoc::OnUpdateBC)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_TS, &CM3daDoc::OnUpdateTC)
ON_COMMAND(ID_PROPERTY_ROTATIONALSPRING, &CM3daDoc::OnPropertyRotationalspring)
ON_COMMAND(ID_PROPERTY_TRANSLATIONALSPRING, &CM3daDoc::OnPropertyTranslationalspring)
ON_COMMAND(ID_CHECKS_NEGATIVEVOLUMEELEMENTS, &CM3daDoc::OnChecksNegativevolumeelements)
ON_COMMAND(ID_CHECKS_CHECKSHELLELEMENTASPECTRATION, &CM3daDoc::OnChecksCheckshellelementaspectration)
ON_COMMAND(ID_CHECKS_CHECKTETCOLLAPSE, &CM3daDoc::OnChecksChecktetcollapse)
ON_COMMAND(ID_ELEMENTTYPE_MASS, &CM3daDoc::OnElementtypeMass)
ON_COMMAND(ID_PROPERTY_LUMPEDMASS, &CM3daDoc::OnPropertyLumpedmass)
ON_COMMAND(ID_VISABILITY_WORKPLANE, &CM3daDoc::OnVisabilityWorkplane)
ON_COMMAND(ID_TOOLS_MEASUREANGLE, &CM3daDoc::OnToolsMeasureangle)
ON_COMMAND(ID_LOADSBC_CREATEROTATIONALBODYLOAD, &CM3daDoc::OnLoadsbcCreaterotationalbodyload)
ON_COMMAND(ID_IMPORT_LOADBMP, &CM3daDoc::OnImportLoadbmp)
ON_COMMAND(ID_TOOLS_ELEMENTMASSSUMMATION, &CM3daDoc::OnToolsElementmasssummation)
ON_COMMAND(ID_ELEMENTMODIFIY_SHELLMATCORRDSYSTEM, &CM3daDoc::OnElementmodifiyShellmatcorrdsystem)
ON_COMMAND(ID_CHECKS_COINCIDENTELEMENTS, &CM3daDoc::OnChecksCoincidentelements)
ON_COMMAND(ID_NODEMODIFY_CHANGEXORDINATE, &CM3daDoc::OnNodemodifyChangexordinate)
ON_COMMAND(ID_NODEMODIFY_CHANGEYORDINATE, &CM3daDoc::OnNodemodifyChangeyordinate)
ON_COMMAND(ID_NODEMODIFY_CHANGEZORDINATE, &CM3daDoc::OnNodemodifyChangezordinate)
ON_COMMAND(ID_PROPERTYMODIFY_EDITPROPERTYVALUES, &CM3daDoc::OnPropertymodifyEditpropertyvalues)
ON_COMMAND(ID_PROPERTY_EDITMATERIALVALUES, &CM3daDoc::OnPropertyEditmaterialvalues)
ON_COMMAND(ID_PROPERTY_BEAM_BASIC, &CM3daDoc::OnPropertyBeamBasic)
ON_COMMAND(ID_VIEW_SURFACEDIRECTIONMARKERS, &CM3daDoc::OnViewSurfacedirectionmarkers)
ON_COMMAND(ID_POST_LISTNODALRESULTS, &CM3daDoc::OnPostListnodalresults)
ON_COMMAND(ID_CURVEMODIFY_INSERTKNOT, &CM3daDoc::OnCurvemodifyInsertknot)
ON_COMMAND(ID_POST_ANIMATE, &CM3daDoc::OnPostAnimate)
ON_COMMAND(ID_POST_ANIMATENEG, &CM3daDoc::OnPostAnimateneg)
ON_COMMAND(ID_POST_FRAMEDELAY, &CM3daDoc::OnPostFramedelay)
ON_COMMAND(ID_POST_ANIMATIONFRAMES, &CM3daDoc::OnPostAnimationframes)
ON_COMMAND(ID_ELEMENTMODIFIY_BEAMENDARELEASE, &CM3daDoc::OnElementmodifiyBeamendarelease)
ON_COMMAND(ID_ELEMENTMODIFIY_BEAMENDBRELEASE, &CM3daDoc::OnElementmodifiyBeamendbrelease)
ON_COMMAND(ID_OPTIONS_DEFORMATIONOFFSET, &CM3daDoc::OnOptionsDeformationoffset)
ON_COMMAND(ID_POST_LISTRESULTSVECTORS, &CM3daDoc::OnPostListresultsvectors)
ON_COMMAND(ID_TOOLS_EDITOBJECT, &CM3daDoc::OnToolsEditobject)
ON_COMMAND(ID_OPTIONS_VECTORSCALE, &CM3daDoc::OnOptionsVectorscale)
ON_COMMAND(ID_POST_SELECTVECTORRESULTS, &CM3daDoc::OnPostSelectvectorresults)
ON_COMMAND(ID_POST_CLEARRESULTSVECTORS, &CM3daDoc::OnPostClearresultsvectors)
ON_COMMAND(ID_MESH_ADVANCINGFRONTSURFACEMESHTRI, &CM3daDoc::OnMeshAdvancingfrontsurfacemeshtri)
ON_COMMAND(ID_LINE_MULTILINE, &CM3daDoc::OnLineMultiline)
ON_COMMAND(ID_CHECKS_2DSECTIONPROPERTIESAIXXIYYETC, &CM3daDoc::OnChecks2dsectionpropertiesaixxiyyetc)
ON_COMMAND(ID_MESHMANAGEMENT_LISTALLMESHES, &CM3daDoc::OnMeshmanagementListallmeshes)
ON_COMMAND(ID_MESHMANAGEMENT_CREATENEWMESH, &CM3daDoc::OnMeshmanagementCreatenewmesh)
ON_COMMAND(ID_MESHMANAGEMENT_SETACTIVEMESH, &CM3daDoc::OnMeshmanagementSetactivemesh)
ON_COMMAND(ID_MESHMANAGEMENT_TOGGLEMESHVISABILITY, &CM3daDoc::OnMeshmanagementTogglemeshvisability)
ON_COMMAND(ID_MESHMANAGEMENT_DELETEMESH, &CM3daDoc::OnMeshmanagementDeletemesh)
ON_COMMAND(ID_VIEW_HIDEENTITIES, &CM3daDoc::OnViewHideentities)
ON_COMMAND(ID_VIEW_SHOWALLHIDDEN, &CM3daDoc::OnViewShowallhidden)
ON_COMMAND(ID_POST_LISTRESPONSEDATA, &CM3daDoc::OnPostListresponsedata)
ON_COMMAND(ID_MESH_MESHSIZEONSURFACE, &CM3daDoc::OnMeshMeshsizeonsurface)
ON_COMMAND(ID_PARTMODIFY_EXTRACT, &CM3daDoc::OnPartmodifyExtract)
ON_COMMAND(ID_CHECKS_TETCIRCUMSPHERE, &CM3daDoc::OnChecksTetcircumsphere)
ON_COMMAND(ID_FEMTOOLS_MESHSIZEONCURVES, &CM3daDoc::OnFemtoolsMeshsizeoncurves)
//ON_COMMAND(ID_EDIT_REDO, &CM3daDoc::OnEditRedo)
//ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CM3daDoc::OnUpdateEditRedo)
//ON_COMMAND(ID_FILE_OPEN, &CM3daDoc::OnFileOpen)
ON_COMMAND(ID_CURVETOOLS_TEXT, &CM3daDoc::OnCurvetoolsText)
ON_COMMAND(ID_PROPERTY_PCOMP, &CM3daDoc::OnPropertyPcomp)
ON_COMMAND(ID_MATERIAL_ORTHOTROPIC, &CM3daDoc::OnMaterialOrthotropic)
ON_COMMAND(ID_PROPERTY_DISPLAYLAMINATESTACK, &CM3daDoc::OnPropertyDisplaylaminatestack)
ON_COMMAND(ID_PROPERTY_PBUSH, &CM3daDoc::OnPropertyPbush)
ON_COMMAND(ID_MANIPULATION_DIVIDEINTO, &CM3daDoc::OnManipulationDivideinto)
ON_COMMAND(ID_MANIPULATION_ENVELOPEMAXIMUM, &CM3daDoc::OnManipulationEnvelopemaximum)
ON_COMMAND(ID_MANIPULATION_ENVELOPEMINIMUM, &CM3daDoc::OnManipulationEnvelopeminimum)
ON_COMMAND(ID_MANIPULATION_SCALE, &CM3daDoc::OnManipulationScale)
ON_COMMAND(ID_EDIT_TOGGLEON, &CM3daDoc::OnEditToggleon)
ON_COMMAND(ID_PROPERTY_BEAM_T2, &CM3daDoc::OnPropertyBeamT2)
ON_COMMAND(ID_PROPERTY_BEAM_CHAN2, &CM3daDoc::OnPropertyBeamChan2)
ON_COMMAND(ID_PROPERTY_BEAM_I2, &CM3daDoc::OnPropertyBeamI2)
ON_COMMAND(ID_PROPERTY_BEAM_L, &CM3daDoc::OnPropertyBeamL)
ON_COMMAND(ID_ELEMENTMODIFIY_BEAMOFFSETINBEAMY, &CM3daDoc::OnElementmodifiyBeamoffsetinbeamy)
ON_COMMAND(ID_ELEMENTMODIFIY_BEAMOFFSETINBEAMZ, &CM3daDoc::OnElementmodifiyBeamoffsetinbeamz)
ON_COMMAND(ID_TOOLS_PLANET, &CM3daDoc::OnToolsPlanet)
ON_COMMAND(ID_FEMTOOLS_SWEEPNODESTOSHELLS, &CM3daDoc::OnFemtoolsSweepnodestoshells)
ON_COMMAND(ID_FEMTOOLS_SWEEPNODESTOBEAMS, &CM3daDoc::OnFemtoolsSweepnodestobeams)
ON_COMMAND(ID_POST_LISTRESPONSEDATAALLVARS, &CM3daDoc::OnPostListresponsedataallvars)
ON_COMMAND(ID_POST_LABELRESPONSEENTITIES, &CM3daDoc::OnPostLabelresponseentities)
ON_COMMAND(ID_POST_GRAPHRESPONSEDATA, &CM3daDoc::OnPostGraphresponsedata)
//ON_COMMAND(ID_FEMTOOLS_SWEEPNODESTOBEAMS33361, &CM3daDoc::OnFemtoolsSweepnodestobeams33361)
//ON_COMMAND(ID_FEMTOOLS_SWEEPNODESTOSHELLS33362, &CM3daDoc::OnFemtoolsSweepnodestoshells33362)
ON_COMMAND(ID_FEMTOOLS_SWEEPNODESTOBEAMS33361, &CM3daDoc::OnFemtoolsSweepnodestobeams33361)
ON_COMMAND(ID_FEMTOOLS_SWEEPNODESTOSHELLS33362, &CM3daDoc::OnFemtoolsSweepnodestoshells33362)
ON_COMMAND(ID_VIEW_HIGHLIGHTLIMIT, &CM3daDoc::OnViewHighlightlimit)
ON_COMMAND(ID_SELECTION_RBECENTRENODES, &CM3daDoc::OnSelectionRbecentrenodes)
ON_COMMAND(ID_CHECKS_COUNTF, &CM3daDoc::OnChecksCountf)
ON_COMMAND(ID_CURVEMODIFY_SPLITATPOINT, &CM3daDoc::OnCurvemodifySplitatpoint)
ON_COMMAND(ID_ELEMENTMODIFIY_INTERSECTTRIELEMENTS, &CM3daDoc::OnElementmodifiyIntersecttrielements)
ON_COMMAND(ID_NODEMODIFY_EQUIVALENCELAB, &CM3daDoc::OnNodemodifyEquivalencelab)
ON_COMMAND(ID_ELEMENTMODIFIY_COLOURBYPID, &CM3daDoc::OnElementmodifiyColourbypid)
ON_COMMAND(ID_EXPORT_INCLUDEFILE, &CM3daDoc::OnExportIncludefile)
ON_COMMAND(ID_GROUP_GROUPFROMINCLUDEFILE, &CM3daDoc::OnGroupGroupfromincludefile)
ON_COMMAND(ID_MESHMANAGEMENT_SETINCLUDEFILENO, &CM3daDoc::OnMeshmanagementSetincludefileno)
ON_COMMAND(ID_ELEMENTMODIFIY_COLOURBYINCLUDEFILE, &CM3daDoc::OnElementmodifiyColourbyincludefile)
ON_COMMAND(ID_CURVETOOLS_ORTHOSNAP, &CM3daDoc::OnCurvetoolsOrthosnap)
ON_COMMAND(ID_CURVEMODIFY_TRIM, &CM3daDoc::OnCurvemodifyTrim)
ON_COMMAND(ID_LIST_GAPSBETWEENLABELS, &CM3daDoc::OnListGapsbetweenlabels)
ON_COMMAND(ID_LIST_GAPSBETWEENMATSANDPROPSLABELS, &CM3daDoc::OnListGapsbetweenmatsandpropslabels)
ON_COMMAND(ID_ELEMENTMODIFIY_INSERTSPRINGONRIGID, &CM3daDoc::OnElementmodifiyInsertspringonrigid)
ON_COMMAND(ID_FEMTOOLS_SWEEPEDGESOUTWARD, &CM3daDoc::OnFemtoolsSweepedgesoutward)
ON_COMMAND(ID_OBJECTSIZE_POINT, &CM3daDoc::OnObjectsizePoint)
ON_COMMAND(ID_OBJECTSIZE_NODE, &CM3daDoc::OnObjectsizeNode)
ON_COMMAND(ID_OBJECTSIZE_LUMPMASS, &CM3daDoc::OnObjectsizeLumpmass)
ON_COMMAND(ID_OBJECTSIZE_ELEMENTEDGE, &CM3daDoc::OnObjectsizeElementedge)
ON_COMMAND(ID_OBJECTSIZE_ELEMENTFREEEDGE, &CM3daDoc::OnObjectsizeElementfreeedge)
ON_COMMAND(ID_OBJECTSIZE_ELEMENTFREEFACE, &CM3daDoc::OnObjectsizeElementfreeface)
ON_COMMAND(ID_OBJECTSIZE_WORKPLANELINES, &CM3daDoc::OnObjectsizeWorkplanelines)
ON_COMMAND(ID_OBJECTSIZE_BEAMS, &CM3daDoc::OnObjectsizeBeams)
ON_COMMAND(ID_OBJECTSIZE_TEXT, &CM3daDoc::OnObjectsizeText)
ON_COMMAND(ID_EXPORT_EXPORTVIEWMATRIX, &CM3daDoc::OnExportExportviewmatrix)
ON_COMMAND(ID_IMPORT_IMPORTVIEWMATRIX, &CM3daDoc::OnImportImportviewmatrix)
ON_COMMAND(ID_CURVETOOLS_LINETHROUPTANDTANGENTTOCIRCLE, &CM3daDoc::OnCurvetoolsLinethrouptandtangenttocircle)
ON_COMMAND(ID_CURVETOOLS_LINETANGENTTO2CIRCLES, &CM3daDoc::OnCurvetoolsLinetangentto2circles)
ON_COMMAND(ID_CURVETOOLS_POINTSONCIRCLE, &CM3daDoc::OnCurvetoolsPointsoncircle)
ON_COMMAND(ID_EDIT_POLARTRANSLATEDFROM, &CM3daDoc::OnEditPolartranslatedfrom)
ON_COMMAND(ID_VIEW_TOGGLECONTROLPOINTVISABILITY, &CM3daDoc::OnViewTogglecontrolpointvisability)
ON_COMMAND(ID_EXPORT_EXPORTDXF, &CM3daDoc::OnExportExportdxf)
ON_COMMAND(ID_CURVEMODIFY_LAYERNUMBER, &CM3daDoc::OnCurvemodifyLayernumber)
ON_COMMAND(ID_SELECTION_SELECTCURVE, &CM3daDoc::OnSelectionSelectcurve)
ON_COMMAND(ID_VIEW_TOGGLEONCIRCLESTARTMARKERS, &CM3daDoc::OnViewToggleoncirclestartmarkers)
ON_COMMAND(ID_TOOLS_INSERTBITMAPBACKGROUND, &CM3daDoc::OnToolsInsertbitmapbackground)
ON_COMMAND(ID_VIEW_TOGGLEON, &CM3daDoc::OnViewToggleon)
ON_COMMAND(ID_QFILTER_NODES, &CM3daDoc::OnQfilterNodes)
ON_COMMAND(ID_QFILTER_ELEMENTS, &CM3daDoc::OnQfilterElements)
ON_COMMAND(ID_QFILTER_POINTS, &CM3daDoc::OnQfilterPoints)
ON_COMMAND(ID_QFILTER_CURVES, &CM3daDoc::OnQfilterCurves)
ON_COMMAND(ID_QFILTER_SURFACE, &CM3daDoc::OnQfilterSurface)
ON_COMMAND(ID_QFILTER_ALL, &CM3daDoc::OnQfilterAll)
ON_COMMAND(ID_DIMENSIONTOOLS_DIMSIZE, &CM3daDoc::OnDimensiontoolsDimsize)
ON_COMMAND(ID_DIMENSIONTOOLS_ALIGNEDDIM, &CM3daDoc::OnDimensiontoolsAligneddim)
ON_COMMAND(ID_DIMENSIONTOOLS_LINEARDIM, &CM3daDoc::OnDimensiontoolsLineardim)
ON_COMMAND(ID_DIMENSIONTOOLS_HORIZONTALDIM, &CM3daDoc::OnDimensiontoolsHorizontaldim)
ON_COMMAND(ID_DIMENSIONTOOLS_VERTICALDIM, &CM3daDoc::OnDimensiontoolsVerticaldim)
ON_COMMAND(ID_DIMENSIONTOOLS_LEADERTEXT, &CM3daDoc::OnDimensiontoolsLeadertext)
ON_COMMAND(ID_DIMENSIONTOOLS_RADIUSDIM, &CM3daDoc::OnDimensiontoolsRadiusdim)
ON_COMMAND(ID_DIMENSIONTOOLS_DIAMETERDIM, &CM3daDoc::OnDimensiontoolsDiameterdim)
ON_COMMAND(ID_DIMENSIONTOOLS_ANGULARDIMBY3POINTS, &CM3daDoc::OnDimensiontoolsAngulardimby3points)
ON_COMMAND(ID_DIMENSIONTOOLS_DRAGDIM, &CM3daDoc::OnDimensiontoolsDragdim)
ON_COMMAND(ID_DIMENSIONTOOLS_CIRCLECENTREMARKER, &CM3daDoc::OnDimensiontoolsCirclecentremarker)
ON_COMMAND(ID_ELEMENTTYPE_BUSH, &CM3daDoc::OnElementtypeBush)
ON_COMMAND(ID_EDIT_GLOBALPREFERENCES, &CM3daDoc::OnEditGlobalpreferences)
ON_COMMAND(ID_LOADSBC_CREATETEMPD, &CM3daDoc::OnLoadsbcCreatetempd)
ON_COMMAND(ID_LOADSBC_CREATEGRAV, &CM3daDoc::OnLoadsbcCreategrav)
ON_COMMAND(ID_EXPORT_CURRENT_STL, &CM3daDoc::OnExportCurrentStl)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CM3daDoc, CDocument)
	DISP_FUNCTION_ID(CM3daDoc, "GetNo", dispidGetNo, GetNo, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CM3daDoc, "APIGetModel", dispidAPIGetModel, APIGetModel, VT_DISPATCH, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "DeleteSelectedWG", dispidDeleteSelectedWG, API_DeleteSelectedWG, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "DesAll", dispidDesAll, API_DesAll, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "ReDraw", dispidReDraw, API_ReDraw, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "GenMesh", dispidGenMesh, API_GenMesh, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "ImportCat", dispidImportCat, API_ImportCat, VT_EMPTY, VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "Tog1d2d", dispidTogOn1d2d, API_On1d2d, VT_I2, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "ImportWG", dispidImportWG, API_ImportWG, VT_I2, VTS_BSTR VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "GetDBNoObjs", dispidGetDBNoObjs, API_GetDBNoObjs, VT_I4, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "GetName", dispidGetName, API_GetName, VT_BSTR, VTS_I4)
  DISP_FUNCTION_ID(CM3daDoc, "ImpSecT", dispidImpSecT, API_ImpSecT, VT_EMPTY, VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "SelectWG", dispidSelectWG, API_SelectWG, VT_EMPTY, VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "InvertSel", dispidInvertSel, API_InvertSel, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "AddPoint", dispidAddPoint, API_AddPoint, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8 VTS_I4)
  DISP_FUNCTION_ID(CM3daDoc, "AddLine", dispidAddLine, API_AddLine, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4)
  DISP_PROPERTY_EX_ID(CM3daDoc, "ElLen", dispidElLen, API_GetElLen, API_SetElLen, VT_R8)
  DISP_PROPERTY_EX_ID(CM3daDoc, "IMode", dispidIMode, API_GetIMode, API_SetIMode, VT_I2)
  DISP_PROPERTY_EX_ID(CM3daDoc, "NoElementsH", dispidNoElemenrsH, API_GetNoElementsH, API_SetNoElementsH, VT_I2)
  DISP_PROPERTY_EX_ID(CM3daDoc, "NoElementsW", dispidNoElemenrsV, API_GetNoElementsW, API_SetNoElementsW, VT_I2)
  DISP_FUNCTION_ID(CM3daDoc, "ImportWG2", dispidImportWG2, API_ImportWG2, VT_I2, VTS_BSTR VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "BuildAssem", dispidBuildAssem, API_BuildAssem, VT_I2, VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "DisplayAll", dispidDisplayAll, API_DisplayAll, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CM3daDoc, "ExportUNV", dispidExportUNV, API_ExportUNV, VT_I2, VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "SelectAllWGs", dispidSelectAllWGs, API_SelectAllWGs, VT_EMPTY, VTS_NONE)
  DISP_PROPERTY_EX_ID(CM3daDoc, "ElDeg", dispidElDeg, GetElDeg, SetElDeg, VT_R8)
  DISP_FUNCTION_ID(CM3daDoc, "ExportNAS", dispidExportNAS, API_ExportNAS, VT_I2, VTS_BSTR)
  DISP_FUNCTION_ID(CM3daDoc, "MergeNodes", dispidMergeNodes, API_MergeNodes, VT_EMPTY, VTS_R8)
  DISP_FUNCTION_ID(CM3daDoc, "ExportGroups", dispidExportGroups, API_ExportGroups, VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()

// Note: we add support for IID_IM3da to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {D0A70CB8-1A81-462F-9171-84EFAB11DD21}
static const IID IID_IM3da =
{ 0xD0A70CB8, 0x1A81, 0x462F, { 0x91, 0x71, 0x84, 0xEF, 0xAB, 0x11, 0xDD, 0x21 } };

BEGIN_INTERFACE_MAP(CM3daDoc, CDocument)
	INTERFACE_PART(CM3daDoc, IID_IM3da, Dispatch)
END_INTERFACE_MAP()


// CM3daDoc construction/destruction

CM3daDoc::CM3daDoc()
{
	// TODO: add one-time construction code here
cDBase=NULL;
EnableAutomation();
AfxOleLockApp();
InitDoc();
}

CM3daDoc::~CM3daDoc()
{
	AfxOleUnlockApp();
  delete(cDBase);
}

BOOL CM3daDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	if (bOnFirst == FALSE)
	{
		InitDoc();
	}
	else
	{
		bOnFirst = FALSE;
	}
	ReSet();
	CheckPoint();
	return TRUE;

}




// CM3daDoc serialization

void CM3daDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
    cDBase->Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
    cDBase->Serialize(ar);
    cDBase->Dsp_All();
	}

}

//Added to implement undo and redo
//This will delete all content i the database I think
void CM3daDoc::DeleteContents2()
{
	//delete(cDBase);
	//cDBase = new DBase(10);
	if (cDBase != NULL)
	{
	  cDBase->DeleteAll();
	  cDBase->InvalidateOGL();
	}
	
	//if (bOnFirst == FALSE)
		//InitDoc();
	//else
		//bOnFirst = FALSE;
}


// CM3daDoc diagnostics

#ifdef _DEBUG
void CM3daDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CM3daDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CM3daDoc commands
void CM3daDoc::InitDoc()
{
	CView* pV;
	//cDBase->SetView(pCViewIn);
	if (cDBase != NULL)
	{
		pV = cDBase->pTheView;
		delete(cDBase);
		iDrawMode = 4;
		cDBase = new DBase(10);
		CRect C;
		if (pV != NULL)  //Re-Uses existing View
		{
			pV->GetClientRect(&C);
			SetView(pV);
			SetScreenMat(C);
		}
	}
	else
	{
		iDrawMode = 4;
		cDBase = new DBase(10);
	}
	cDBase->S_Count = 0;
	cDBase->DspFlags = (cDBase->DspFlags ^ DSP_GRAD);
	pMnu = new zMnu();
	pMnu->Init(cDBase, -1);
	sLastcmd = "";
}

void CM3daDoc::SetView (CView* pCViewIn)
{
cDBase->SetView(pCViewIn);
}



void CM3daDoc::SetScreenMat(CRect rRect)
{
cDBase->SetScreenMat(rRect);
}


void CM3daDoc::UpTree() 
{
	// TODO: Add your command handler code here
	if (cDBase!=NULL)
	{
	  cDBase->UpTree();
	  outtext1("Up Tree");
	}
}

void CM3daDoc::SetPen(CDC* pDC,int R,int G,int B)
{
  Pen = new CPen(PS_SOLID,1,RGB(R,G,B));
  OldPen = pDC->SelectObject(Pen);
}


void CM3daDoc::RestorePen(CDC* pDC)
{    
  pDC->SelectObject(OldPen);
  Pen->DeleteObject();
  Pen->~CPen();
  delete Pen;
  Pen = NULL;
}

void CM3daDoc::InvalidateOGL()
{
if (cDBase!=NULL)
{
  cDBase->InvalidateOGL();
}
}

void CM3daDoc::InitOGL(CDC* pDC)
{
//cDBase->InvalidateOGL();
cDBase->InitOGL(pDC);
}

void CM3daDoc::SetToScr2(C3dMatrix pM)
{
cDBase->SetToScr2(pM);
}

void CM3daDoc::Draw(C3dMatrix pM,CDC* pCView,int iMode)
{
D_ClientDC = pCView;
cDBase->Draw(pM,pCView,iMode);
}

void CM3daDoc::DragUpdate(CPoint m_PointNew)
{
	cDBase->DragUpdate(m_PointNew);
}


BOOL CM3daDoc::isBlackDisp()
{
	return (cDBase->isBlackDisp());
}

double CM3daDoc::GetHeight()
{
return(cDBase->dHeight);
}
void CM3daDoc::DrawDrag(CDC* pCView,CPoint P1,CPoint P2)
{
cDBase->DrawDrag(pCView,P1,P2);
}

BOOL CM3daDoc::isDragging()
{
	if (cDBase != NULL)
		return(cDBase->bIsDrag);
	else
		return(FALSE);
}

void CM3daDoc::SetLineStart(CPoint pS)
{
	if (cDBase != NULL)
		cDBase->SetLineStart(pS);
}

void CM3daDoc::SetLineEnd(CPoint pE)
{
	if (cDBase != NULL)
		cDBase->SetLineEnd(pE);
}

void CM3daDoc::LineDrag(CDC* pCView, CPoint P1, CPoint P2)
{
	if (cDBase != NULL)
		cDBase->LineDrag(pCView, P1, P2);
}

void CM3daDoc::SelectBox(CPoint P1,CPoint P2)
{
cDBase->S_Box(P1,P2);
}

void SendMsg(CString AAA)
{
CString Msg;
Msg=AAA;
CPoint N(0,0);
int iExit;
iExit = pMnu->DoMenu(Msg,N);

}

BOOL CM3daDoc::isMenuNULL()
{
return(pMnu->isNULL());
}

void CM3daDoc::DspAll()
{
  outtext1("Display All.");
  cDBase->Dsp_All();
}

void CM3daDoc::DspSel()
{
  outtext1("Display Selected.");
  cDBase->Dsp_Selected();
}

double CM3daDoc::GetWPSize()
{
return (cDBase->WPSize);
}

C3dMatrix CM3daDoc::GetWPmat()
{
  C3dMatrix mT;
  mT = cDBase->GetWPmat();
  return(mT);
}


void CM3daDoc::DspCat()
{
  cDBase->Dsp_Cat();
}

void CM3daDoc::DspNext()
{
  cDBase->Dsp_Next();
}

void CM3daDoc::DspPrev()
{
  cDBase->Dsp_Prev();
}

void CM3daDoc::SetDrawType(int iType)
{
cDBase->SetDrawType(iType);
}

int CM3daDoc::GetDrawType()
{
return(cDBase->GetDrawType());
}

void CM3daDoc::DoMsg(int MsgType,CPoint PT1,CPoint PT2,CString InFu)
{

//cDBase->SetView(pCView,m_ScrMat,m_ModelMap);
if (cDBase->bPICK==TRUE)
{
  cDBase->DoMsg(MsgType, PT1, PT2);
}
if (MsgType == 1)
{
  pMnu->DoMenu(InFu,PT1);

}
}

//ADDED BY ME
void CM3daDoc::OnUpdateLC(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString strPage;
    int iLC=-1;
    int ind;
    if (cDBase->pCurrentMesh!=NULL)
    {
       ind=cDBase->pCurrentMesh->iCurLC;
       if (ind!=-1)
         iLC=cDBase->pCurrentMesh->GetLCID(ind);
    }
    strPage.Format(_T("LC: %d"), iLC); 
    pCmdUI->SetText(strPage); 
}

void CM3daDoc::OnUpdateBC(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString strPage;
    int iBC=-1;
    int ind;
    if (cDBase->pCurrentMesh!=NULL)
    {
       ind=cDBase->pCurrentMesh->iCurBC;
       if (ind!=-1)
         iBC=cDBase->pCurrentMesh->GetBCID(ind);
    }
    strPage.Format(_T("BC: %d"), iBC); 
    pCmdUI->SetText(strPage); 
}

void CM3daDoc::OnUpdateTC(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString strPage;
    int iTC=-1;
    int ind;
    if (cDBase->pCurrentMesh!=NULL)
    {
       ind=cDBase->pCurrentMesh->iCurTSet;
       if (ind!=-1)
         iTC=cDBase->pCurrentMesh->GetTSETID(ind);
    }
    strPage.Format(_T("TS: %d"), iTC); 
    pCmdUI->SetText(strPage); 
}


void CM3daDoc::OnViewDisplayall()
{
  // TODO: Add your command handler code here
  outtext1("Display All.");
  cDBase->Dsp_All();
}


void CM3daDoc::OnEditDes()
{
  // TODO: Add your command handler code here
  cDBase->S_Des();
  //outtextMSG2("DES");
  outtext1("Deselect All.");
}

void CM3daDoc::OnEditInformation()
{
  cDBase->Info();	
}

void CM3daDoc::OnEditKeyin()
{
  // TODO: Add your command handler code here
  outtextMSG2("KEY");
}

void CM3daDoc::OnEditPick()
{
  // TODO: Add your command handler code here
  outtextMSG2("PICK");
}

void CM3daDoc::OnEditBetween()
{
  // TODO: Add your command handler code here
  outtextMSG2("BET");
}

void CM3daDoc::OnEditTranslatedfrom()
{
  // TODO: Add your command handler code here
  outtextMSG2("TRAN");	
}

void CM3daDoc::OnEditFilternone()
{

  cDBase->SetFilter();
}

void CM3daDoc::OnEditCancel()
{
  // TODO: Add your command handler code here
  outtextMSG2("C");
}

void CM3daDoc::OnEditDone()
{
  // TODO: Add your command handler code here
  outtextMSG2("D");
}


void CM3daDoc::Dsp_Group() 
{
	// TODO: Add your command handler code here
outtext1("Displaying Current Group.");
cDBase->Dsp_Group(); 	
}

C3dVector CM3daDoc::GetViewPt()
{ 

outtext1("Setting View Point");
return(cDBase->GetVPt());
}

C3dVector CM3daDoc::GetMeshCentre()
{ 
return(cDBase->GetMeshCentre());
}

int CM3daDoc::GetMeshYExt()
{ 
return(cDBase->GetMeshYExt());
}

void CM3daDoc::OnGroupAddtogroup()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
   outtextMSG2("GPADD");
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnGroupRemovefromgroup()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("GPREM");
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnGroupAddgroup()
{
  // TODO: Add your command handler code here	
  int iGp=cDBase->GetGroupID();
}

void CM3daDoc::OnGroupRemovegroup()
{
  // TODO: Add your command handler code here
  int iGp=cDBase->GetGroupID();
}


void CM3daDoc::OnGroupSetcurrent()
{

  int iGp=cDBase->GetGroupID();
}


void CM3daDoc::OnGroupListgroups()
{
  // TODO: Add your command handler code here
  outtextMSG2("GPLIST");
}

void CM3daDoc::OnImportUnv()
{
  // TODO: Add your command handler code here
	outtext1("IMPORT UNIVERSAL FILE");
    FILE* pFile;
	//TODO: Add your command handler code here
	CFileDialog FDia( TRUE,"unv", "*.unv",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	FDia.DoModal();	
	CString sPath = FDia.GetPathName();
    CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		pFile = fopen(sPath,"r");
		if (pFile!=NULL)
		  {
		  cDBase->S_Import(pFile,sFile,1);
		  } 
	fclose(pFile);
	}
}




void CM3daDoc::OnImportDat()
{
  // TODO: Add your command handler code here
  outtext1("IMPORT BDF FILE");
	//TODO: Add your command handler code here
	CFileDialog FDia( TRUE,"NASTRAN", "*.DAT;*.NAS;*.NID;*.D;*.BLK;*.BDF",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	FDia.DoModal();	
	CString sPath = FDia.GetPathName();

    CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		//pFile = fopen(sPath,"r");
		//if (pFile!=NULL)
		//  {
		  cDBase->S_Import(NULL,sPath,3);
		//  } 
	//fclose(pFile);
	}
}

void CM3daDoc::OnImportIges()
{
  // TODO: Add your command handler code here
  outtext1("IMPORT IGES FILE");
FILE* pFile;
//TODO: Add your command handler code here
CFileDialog FDia( TRUE,"IGS", "*.IGS",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"r");
  if (pFile!=NULL)
  {
	cDBase->S_ImportIges(pFile,sFile);
  } 
  fclose(pFile);
}	
}

void CM3daDoc::OnImportLoadbmp()
{
    // TODO: Add your command handler code here
    outtext1("IMPORT BMP FILE");
    //TODO: Add your command handler code here
    CFileDialog FDia(TRUE, "BMP", "*.BMP", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
    FDia.DoModal();
    CString sPath = FDia.GetPathName();
    CString sFile = FDia.GetFileName();
    if (sFile != "")
    {
       if (cDBase->S_loadBMP(sPath, sFile))
	      cDBase->insBackGround();
    }
}

void CM3daDoc::OnViewNodesoff()
{
	cDBase->SetFastView();
}

void CM3daDoc::OnCreatePoint()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("PTCR");
  sLastcmd="PTCR";

}
else
{
  outtext1("Finish Current Operation.");
}

}

//void CM3daDoc::OnLineLine()
//{
//  // TODO: Add your command handler code here
//  CFilterDialog Dlg;
//	Dlg.DoModal();
//
// SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
// outtextMSG2("LN");
// sLastcmd="LN";
//}


void CM3daDoc::OnLineLinex()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("LNX");
  sLastcmd="LNX";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnLineLiney()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("LNY");
  sLastcmd="LNY";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnLineLinez()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("LNZ");
  sLastcmd="LNZ";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnCreateCircle()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CIRCR2");
  sLastcmd="CIRCR2";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsWpsize()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  outtextMSG2("WPSIZE");
  sLastcmd="WPSIZE";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnCreateCurve()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CVCR");
  sLastcmd="CVCR";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnSurfaceLoft()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("SURCR");
    sLastcmd="SURCR";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSurfaceExtrude()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SUREX");
  sLastcmd="SUREX";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSurfaceRevolve()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SURRV");
  sLastcmd="SURRV";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsCopyrotate()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("COPYROT");
  sLastcmd="COPYROT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnCreateNode()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDCR");
  sLastcmd="NDCR";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnCreateElement()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELCR");
  sLastcmd="ELCR";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnElementtypeTri()
{
  // TODO: Add your command handler code here
SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
outtextMSG2("ELTYPE");
outtextMSG2("TRI");
}

void CM3daDoc::OnElementtypeQuad()
{
// TODO: Add your command handler code here
SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
outtextMSG2("ELTYPE");
outtextMSG2("QUAD");
}

void CM3daDoc::OnElementtypeBrick()
{
// TODO: Add your command handler code here
SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
outtextMSG2("ELTYPE");
outtextMSG2("BRICK");
}




void CM3daDoc::OnElementtypeWedge()
{
// TODO: Add your command handler code here
SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
outtextMSG2("ELTYPE");
outtextMSG2("WEDGE");
}


void CM3daDoc::OnElementtypeTet()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELTYPE");
  outtextMSG2("TET");
}

void CM3daDoc::OnElementtypeRigid()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELTYPE");
  outtextMSG2("RIGID");
}

void CM3daDoc::OnCreateCopynodes()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDCO"); 
  sLastcmd="NDCO";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnFileInsertcataloguepart()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("INSCAT"); 
  sLastcmd="INSCAT";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnToolsScale()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SCALE"); 
  sLastcmd="SCALE";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnCreateNodemoveto()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDMOVE");
  sLastcmd="NDMOVE";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnCreateNodesbetween()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDBET");
  sLastcmd="NDBET";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnCreateNodesoncurve()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDONCV");
  sLastcmd="NDONCV";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnViewSelectall()
{
  // TODO: Add your command handler code here
  cDBase->S_All(-1);
  outtext1("Invert Selection");
}



void CM3daDoc::OnToolsMove()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("MOVE");
  sLastcmd="MOVE";
}
else
{
  outtext1("Finish Current Operation.");
}

  
}

void CM3daDoc::OnToolsReflect()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("REFLECT");
  sLastcmd="REFLECT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsCopy()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("COPY");	
  sLastcmd="COPY";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnToolsWpmode()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("WPMODE");	
  sLastcmd="WPMODE";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsWpalign()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("WPALIGN");	
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsWpglobal()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("WPGLOB");
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnViewControlpoint()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("CVPTON");
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::GetNo(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: Add your dispatch handler code here
}

void CM3daDoc::OnToolsColour()
{
	// TODO: Add your command handler code here

//if (iCol!=-1)
//  cDBase->Colour(iCol);
if (pMnu->isNULL())
{
  int iCol=cDBase->GetColourID();
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("COL");
  outtextMSG2("D");
  char S1[22];
  sprintf_s(S1,"%i",iCol);
  outtextMSG2(S1);
  sLastcmd="COL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsSetcurrentmesh()
{
	// TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  cDBase->SetCurMesh();
}

void CM3daDoc::OnExportCurrentmesttonas()
{
cDBase->ExporttoNAS(-1);
}

void CM3daDoc::OnExportCurrentmeshto()
{
	// TODO: Add your command handler code here
outtext1("EXPORTING UNIVERSAL FILE");
FILE* pFile;
CFileDialog FDia(FALSE,"unv", "*.unv",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"w");
  if (pFile!=NULL)
  {
	cDBase->ExportMesh(pFile);
	fclose(pFile);
  } 
}
}

void CM3daDoc::OnViewShadededges()
{
	// TODO: Add your command handler code here

  cDBase->DspFlags=(cDBase->DspFlags ^ DSP_SHADED_EDGES);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnViewDisplayelementcoordsys()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags=(cDBase->DspFlags ^ DSP_ELSYS);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnGroupCreategroup()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPCR");
  sLastcmd="GPCR";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnEditRepeatlastcommand()
{
  // TODO: Add your command handler code here
if (pMnu->isNULL())
{
  outtextMSG2(sLastcmd);
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnEditOnscreenlocation()
{
  // TODO: Add your command handler code here
  outtextMSG2("ONSCR");
}

void CM3daDoc::OnCreateFittedcurve()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CVFIT");
  sLastcmd="CVFIT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnLineLineangle()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("LNANG");
  sLastcmd="LNANG";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnCreateFillet()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("FIL");
  sLastcmd="FIL";

}

void CM3daDoc::OnCreateOffset()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("OFFSET");
  sLastcmd="OFFSET";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnCreateMakecorner()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
   SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CORNER");
  sLastcmd="CORNER";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSurfaceProjectcurve()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CVONSUR");
  sLastcmd="CVONSUR";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSurfaceTrimsurface()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SURTRIM");
  sLastcmd="SURTRIM";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnCreateRectangle()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("RECT");
  sLastcmd="RECT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnGroupElementsbypid()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPBYPID");
  sLastcmd="GPBYPID";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnGroupElementsbycolour()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPBYCOL");
  sLastcmd="GPBYCOL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionElementsbypid()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELBYPID");
  sLastcmd="SELBYPID";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionElementsbycolour()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELBYCOL");
  sLastcmd="SELBYCOL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionNodesbycolour()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELNODESBYCOL");
  sLastcmd="SELNODESBYCOL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSurfacePlanar()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SURBOUND");
  sLastcmd="SURBOUND";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionSelectall()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELALL");
  outtextMSG2("-1");
  sLastcmd="SELALL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnCreateCoordsys()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("COORDCR");
  sLastcmd="COORDCR";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnSurfaceInternaltrimloop()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SURTRIMLOOP");
  sLastcmd="SURTRIMLOOP";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSelectionElementsbytype()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELBYTYPE");
  sLastcmd="SELBYTYPE";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSelectionElementsbymaterial()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELBYMID");
  sLastcmd="SELBYMID";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnEditRelatedto()
{
  // TODO: Add your command handler code here
  outtextMSG2("RELTO");
  int iGp=cDBase->GetItemType();
  //cDBase->SetCurrentGP(iGp);
  char sStr[10];
  itoa (iGp,sStr,10);
  if (iGp!=-1)
  {
     outtextMSG2(sStr);
  }
}

void CM3daDoc::OnCreateCoordsysline()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("COLINE");
  sLastcmd="COLINE";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionElat()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("ELAT");
  sLastcmd="ELAT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsListproperty()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("PRLIST");
  sLastcmd="PRLIST";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionRelatedto()
{
  // TODO: Add your command handler code here
  outtextMSG2("RELTO");
}

void CM3daDoc::OnEditLabel()
{
  // TODO: Add your command handler code here
  outtextMSG2("LAB");
  int iSelLabType = cDBase->GetItemType();
  char sStr[10];
  itoa(iSelLabType, sStr, 10);
  //_itoa_s(iSelLabType, sStr, sizeof(sStr), 10);
  outtextMSG2(sStr);
}


void CM3daDoc::OnElementmodifiyPid()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELMOPID");
  sLastcmd="ELMOPID";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnChecksCoincidentnodes()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("CNODES");
    sLastcmd="CNODES";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnNodemodifyOutputcoordsys()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDMOOSYS");
  sLastcmd="NDMOOSYS";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnMeshSweepelements()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELSWEEP");
  sLastcmd="ELSWEEP";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsMeasure()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("LMEAS");
  sLastcmd="LMEAS";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsAlign()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ALIGN");
  sLastcmd="ALIGN";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnMeshMappedsurfacemesh()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("MMESHQ");
  sLastcmd="MMESHQ";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnMeshMappedtrimesh()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("MMESHT");
  sLastcmd="MMESHT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsRotateabout()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
	outtextMSG2("ROTABOUT");
  sLastcmd="ROTABOUT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnToolsRotatebyangles()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ROTANG");
  sLastcmd="ROTANG";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnEditIitersection()
{
  // TODO: Add your command handler code here
  outtextMSG2("INT");
}


void CM3daDoc::OnEditProject()
{
  // TODO: Add your command handler code here
  outtextMSG2("PROJ");

}

void CM3daDoc::OnToolsDelete()
{
	// TODO: Add your command handler code here
	DeleteObjs();
}

void CM3daDoc::DeleteObjs()
{
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DEL");
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


IDispatch* CM3daDoc::APIGetModel(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: Add your dispatch handler code here

	return cDBase->GetIDispatch(FALSE);;
}








































































//void CM3daDoc::OnViewLine()
//{
//	// TODO: Add your command handler code here
//}

void CM3daDoc::OnVisabilityNodeon()
{
	// TODO: Add your command handler code here
	cDBase->DspFlags = (cDBase->DspFlags ^ DSP_NODES);
	cDBase->InvalidateOGL();
    cDBase->ReDraw();
}

void CM3daDoc::OnVisabilityElementon()
{
	// TODO: Add your command handler code here
	cDBase->DspFlags = (cDBase->DspFlags ^ DSP_ELEMENTS);
	cDBase->InvalidateOGL();
    cDBase->ReDraw();
}

void CM3daDoc::OnViewNodesask()
{
	// TODO: Add your command handler code here
	cDBase->DspFlags = (cDBase->DspFlags ^ DSP_NODES_ASK);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnVisabilitySurfaceson()
{
	// TODO: Add your command handler code here
	cDBase->DspFlags = (cDBase->DspFlags ^ DSP_SURFACES);
	cDBase->InvalidateOGL();
    cDBase->ReDraw();
}


void CM3daDoc::OnVisabilityCurveson()
{
	// TODO: Add your command handler code here
	cDBase->DspFlags = (cDBase->DspFlags ^ DSP_CURVES);
	cDBase->InvalidateOGL();
    cDBase->ReDraw();
}

void CM3daDoc::OnVisabilityAllvisable()
{
	// TODO: Add your command handler code here
	cDBase->DspFlags = DSP_ALL;
	cDBase->InvalidateOGL();
    cDBase->ReDraw();
}

void CM3daDoc::OnViewLabelentities()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
	outtextMSG2("LABENT");
    sLastcmd="LABENT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnQwantaImportcatalogue()
{
// TODO: Add your command handler code here

FILE* pFile;
//TODO: Add your command handler code here
CFileDialog FDia( TRUE,"cat", "*.cat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"r");
  if (pFile!=NULL)
  {
	cDBase->S_ImportCat(pFile,sFile);
  } 
  fclose(pFile);
}
}

void CM3daDoc::OnQwantaImportsectiontable()
{
// TODO: Add your command handler code here
outtext1("IMPORT SEC TABLE");
FILE* pFile;
//TODO: Add your command handler code here
CFileDialog FDia( TRUE,"sec", "*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"r");
  if (pFile!=NULL)
  {
	cDBase->LoadSecT(pFile);
  } 
  fclose(pFile);
  cDBase->LoadProps(sPath);
}
}

void CM3daDoc::OnQwantaImportwaveguide()
{
// TODO: Add your command handler code here
outtext1("IMPORT WAVEGUIDE REPORT");
FILE* pFile;
int iErr=0;
	//TODO: Add your command handler code here
CFileDialog FDia( TRUE,"txt", "*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"r");
  if (pFile!=NULL)
  {
    iErr=cDBase->S_ImportWG(pFile,sFile);
  } 
fclose(pFile);
}
if (iErr==3)
{
  int irc = AfxMessageBox("WG GENERATION FAILED",MB_OK,0);	
}
}

void CM3daDoc::OnQwanta1d()
{
	// TODO: Add your command handler code here
  if (cDBase->gDim==2)
  {
	  cDBase->gDim=1;
	  outtext1("Beam Mesh Enabled");
  }
  else
  {
	  cDBase->gDim=2;
	  outtext1("Shell Mesh Enabled");
  }
}


void CM3daDoc::OnQwantaMeshdensitytoggle()
{
  // TODO: Add your command handler code here
  cDBase->TogMeshD();
}


void CM3daDoc::OnQwantaGeneratemesh()
{
  // TODO: Add your command handler code here
  outtext1("MESHING WAVEGUIDES");
  cDBase->UserCalc();	
  //API_SelectAllWGs();
  //API_ExportUNV("C:\TEST\Fredy.unv");
}


void CM3daDoc::OnCataloguedisplayDisplaycatalugue()
{
  // TODO: Add your command handler code here
    cDBase->Dsp_Cat();
}

void CM3daDoc::OnCataloguedisplayDisplaynext()
{
  // TODO: Add your command handler code here
    cDBase->Dsp_Next();
}

void CM3daDoc::OnCataloguedisplayDisplayprevious()
{
  // TODO: Add your command handler code here
    cDBase->Dsp_Prev();
}

void CM3daDoc::API_DeleteSelectedWG(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  // TODO: Add your dispatch handler code here
cDBase->DeleteObj();
}

void CM3daDoc::API_DesAll(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  // TODO: Add your dispatch handler code here
  cDBase->S_Des();
}



void CM3daDoc::API_ReDraw(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  // TODO: Add your dispatch handler code here
  cDBase->ReDraw();
}

void CM3daDoc::API_GenMesh(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  // TODO: Add your dispatch handler code here
  outtext1("MESHING WAVEGUIDES");
  cDBase->UserCalc();	
}



void CM3daDoc::API_ImportCat(LPCTSTR FileName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: Add your dispatch handler code here
outtext1("IMPORT CATALOGUE FILE");
FILE* pFile;

pFile = fopen(FileName,"r");
if (pFile!=NULL)
{
	cDBase->S_ImportCat(pFile,FileName);
	fclose(pFile);
} 
}

SHORT CM3daDoc::API_On1d2d(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
short brc = 0;
	// TODO: Add your dispatch handler code here
if (cDBase!=NULL)
{
    if (cDBase->gDim==2)
    {
	    cDBase->gDim=1;
	    outtext1("Beam Mesh Enabled");
	    brc=1;
    }
    else
    {
      outtext1("Shell Mesh Enabled");
	    cDBase->gDim=2;
	    brc=0;
    }
}
return brc;
}

void CM3daDoc::OnVisabilityAssemblies()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_ASSEM);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnQwantaBuildamdexport()
{
outtext1("Starting final model generation");
cDBase->BuildAssembly("");
outtext1("Finished final model generation");
}

void CM3daDoc::OnGroupDeleteallgroups()
{
  // TODO: Add your command handler code here
  int iResult;
  iResult=MessageBox(NULL,"Warning this will permanently delete all groups", NULL, MB_OKCANCEL | MB_ICONWARNING);
  if (iResult==1)
    cDBase->DelAll_Group();
}

SHORT CM3daDoc::API_ImportWG(LPCTSTR sFName,LPCTSTR WGName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  int iRC=0;
  outtext1("IMPORT WAVEGUIDE REPORT");
  FILE* pFile;
  pFile = fopen(sFName,"r");
  if (pFile!=NULL)
  {
    iRC=cDBase->S_ImportWG(pFile,WGName);
    fclose(pFile);
  }
  else
  {
    iRC=1;
  }
  return iRC;
}

LONG CM3daDoc::API_GetDBNoObjs(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  return (cDBase->DB_ObjectCount-1);
}

BSTR CM3daDoc::API_GetName(LONG Index)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  CString strResult;
  strResult=cDBase->GetObjName(Index);
  return strResult.AllocSysString();
}

void CM3daDoc::API_ImpSecT(LPCTSTR sFName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  FILE* pFile = fopen(sFName,"r");
  if (pFile!=NULL)
  {
	cDBase->LoadSecT(pFile);
  } 
  fclose(pFile);
  cDBase->LoadProps(sFName);
}

void CM3daDoc::API_SelectWG(LPCTSTR inName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->SelWGName(inName);
}

void CM3daDoc::API_InvertSel(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->S_All(-1);	
}

void CM3daDoc::API_AddPoint(DOUBLE x, DOUBLE y, DOUBLE z, LONG Lab)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->AddPt2(x,y,z,Lab);
}

void CM3daDoc::API_AddLine(DOUBLE x1, DOUBLE y1, DOUBLE z1, DOUBLE x2, DOUBLE y2, DOUBLE z2, LONG Lab)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->AddLN2(x1,y1,z1,x2,y2,z2,Lab);
}

DOUBLE CM3daDoc::API_GetElLen(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  // TODO: Add your dispatch handler code here
  return (cDBase->gdSize);
}

void CM3daDoc::API_SetElLen(DOUBLE newVal)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  if (newVal>0)
  {
    cDBase->gdSize=newVal;
  }
}

SHORT CM3daDoc::API_GetIMode(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  // TODO: Add your dispatch handler code here

  return (cDBase->iSMode);
}

void CM3daDoc::API_SetIMode(SHORT newVal)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->iSMode=newVal;
}

SHORT CM3daDoc::API_GetNoElementsH(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  return cDBase->iSH;
}

void CM3daDoc::API_SetNoElementsH(SHORT newVal)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->iSH=newVal;
}

SHORT CM3daDoc::API_GetNoElementsW(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  // TODO: Add your dispatch handler code here
  return cDBase->iSW;
}

void CM3daDoc::API_SetNoElementsW(SHORT newVal)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->iSW=newVal;
}

SHORT CM3daDoc::API_ImportWG2(LPCTSTR sFName, LPCTSTR sName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  int iRC=0;
  outtext1("IMPORT WAVEGUIDE REPORT");
  FILE* pFile;
  pFile = fopen(sFName,"r");
  if (pFile!=NULL)
  {
    iRC=cDBase->S_ImportWG(pFile,sName);
    fclose(pFile);
  }
  else
  {
    iRC=1;
  }
  return iRC;
}


SHORT CM3daDoc::API_BuildAssem(LPCTSTR sModName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  outtext1("Starting final model generation");
  cDBase->BuildAssembly(sModName);
  outtext1("Finished final model generation");
  return 0;
}

void CM3daDoc::API_DisplayAll(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());

  outtext1("Display All.");
  cDBase->Dsp_All();
}

void CM3daDoc::OnViewWhite()
{
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_BLACK);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

SHORT CM3daDoc::API_ExportUNV(LPCTSTR sFName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  SHORT bRet;
  CString ff = sFName;
  FILE* pFile;
  // TODO: Add your dispatch handler code here
  outtext1("EXPORTING UNIVERSAL FILE");
  outtext1(sFName);
  pFile = fopen(sFName,"w");
  if (pFile!=NULL)
  { 
	cDBase->ExportMesh(pFile);
    outtext1("Export of Universal File Finished");
	fclose(pFile);
    bRet=0;
  } 
  else
  {
    outtext1("Export of Universal File Failed");
    bRet=1;
  }
  return (bRet);
}

void CM3daDoc::API_SelectAllWGs(void)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->SelAllWGs();
}
















void CM3daDoc::OnLineLine()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("LN");
  sLastcmd="LN";
}
else
{
  outtext1("Finish Current Operation.");
}

}

DOUBLE CM3daDoc::GetElDeg(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: Add your dispatch handler code here
    
	return (cDBase->gdASize);
}

void CM3daDoc::SetElDeg(DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: Add your property handler code here
    cDBase->gdASize=newVal;
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
}

void CM3daDoc::OnToolsListallproperties()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  	outtextMSG2("PRLISTALL");
    sLastcmd="PRLISTALL";
}
else
{
  outtext1("Finish Current Operation.");
}
}



void CM3daDoc::OnNodemodifyDefinitioncoordsys()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDMORSYS");
  sLastcmd="NDMORSYS";
}
else
{
  outtext1("Finish Current Operation.");
}
}



void CM3daDoc::OnListAllmaterials()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("MATLISTALL");
  sLastcmd="MATLISTALL";
}
else
{
  outtext1("Finish Current Operation.");
}

}


void CM3daDoc::OnListAllproperties()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("PRLISTALL");
  sLastcmd="PRLISTALL";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnListMaterial()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    outtextMSG2("MATLIST");
    sLastcmd="MATLIST";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}

void CM3daDoc::OnListProperty()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("PRLIST");
  sLastcmd="PRLIST";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnViewDisplayshellthickness()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_THK);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnViewDisplayelementoffsets()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_OFF);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnElementtypeBeam()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtext1("BEAM TYPE 21 SET");
  outtextMSG2("ELTYPE");
  outtextMSG2("BEAM");
}

void CM3daDoc::OnElementtypeRod()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELTYPE");
  outtextMSG2("ROD");
}

void CM3daDoc::OnElementmodifiyBeamoffset()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("BOFF");
  sLastcmd="BOFF";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnElementmodifiyBeamupvectors()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("BUPVEC");
  sLastcmd="BUPVEC";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnPropertySolid()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //outtextMSG2("PRSOLID");
  //sLastcmd="PRSOLID";
  int iNLab = cDBase->PropsT->NextID();
  cDBase->CreatePrSolid("Solid Property", iNLab, -1);
  cDBase->EditProp(iNLab);
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnPropertyBeam()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //outtextMSG2("PRBROD");
  //sLastcmd="PRBROD";
  int iNLab = cDBase->PropsT->NextID();
  cDBase->CreatePrRod("ROD Beam Property", iNLab, -1, 0.015);
  cDBase->EditProp(iNLab);
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnPropertyRod()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //outtextMSG2("PRROD");
  //sLastcmd="PRROD";
  int iNLab = cDBase->PropsT->NextID();
  cDBase->CreatePRod("Rod Element", iNLab, -1, 0.0000785398, 4.90874e-10 + 4.90874e-10);
  cDBase->EditProp(iNLab);
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnPropertyBeambar()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //outtextMSG2("PRBBAR");
  //sLastcmd="PRBBAR";
  int iNLab = cDBase->PropsT->NextID();
  cDBase->CreatePrBar("BAR Beam Property", iNLab, -1, 0.010, 0.015);
  cDBase->EditProp(iNLab);
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnPropertyBeamtube()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("PRBTUBE");
  sLastcmd="PRBTUBE";
  int iNLab = cDBase->PropsT->NextID();
  cDBase->CreatePrTube("TUBE Beam Property", iNLab, -1, 0.015, 0.01);
  cDBase->EditProp(iNLab);

}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnPropertyBeambox()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //outtextMSG2("PRBBOX");
  //sLastcmd="PRBBOX";
  int iNLab = cDBase->PropsT->NextID();
  cDBase->CreatePrBox("BOX Beam Property", iNLab, -1, 0.01, 0.015, 0.005, 0.0025);
  cDBase->EditProp(iNLab);
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnPropertyShell()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //outtextMSG2("PRSHELL");
  //sLastcmd="PRSHELL";
  int iNLab = cDBase->PropsT->NextID();
  cDBase->CreatePrShell("NAME", iNLab, -1, 1, 0);
  cDBase->EditProp(iNLab);
  
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnElementmodifiyShelloffset()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SOFF");
  sLastcmd="SOFF";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnMaterialIsentropic()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //outtextMSG2("MMAT1");
  //sLastcmd="MMAT1";
  int iNLab = cDBase->MatT->NextID();
  cDBase->CreateMat1("Al Material", iNLab, 70.0e9, 0.33, 2750.0, 23.0e-6, 150.0);
  cDBase->EditMat(iNLab,FALSE);

}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnPropertymodifyChangematerial()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("PRCMAT");
  sLastcmd="PRCMAT";
}
else
{
  outtext1("Finish Current Operation.");
}
}

SHORT CM3daDoc::API_ExportNAS(LPCTSTR inName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  SHORT bRet;
  CString ff = inName;
  FILE* pFile;
  // TODO: Add your dispatch handler code here
  outtext1("EXPORTING NASTRAN DECK FILE");
  outtext1(inName);
  pFile = fopen(inName,"w");
  if (pFile!=NULL)
  {
    
	cDBase->ExportMeshNAS(pFile,-1);
	fclose(pFile);
    outtext1("Export of Nastran deck Finished");
    bRet=0;
  } 
  else
  {
    outtext1("Export of Nastran deck Failed");
    bRet=1;
  }
  return (bRet);
  // TODO: Add your dispatch handler code here

}

void CM3daDoc::OnExportGroupstotxt()
{
  // TODO: Add your command handler code here
outtext1("Exporting groups to file");
FILE* pFile;
CFileDialog FDia(FALSE,"txt", "*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"w");
  if (pFile!=NULL)
  {
	cDBase->ExportPermGroupsTXT(pFile);
	fclose(pFile);
  } 
}
}

void CM3daDoc::API_MergeNodes(DOUBLE dTol)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
  cDBase->CNodesMerge(dTol);
  // TODO: Add your dispatch handler code here
}

void CM3daDoc::OnQwantaMergeboundaries()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("QWNODES");
  sLastcmd="QWNODES";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::API_ExportGroups(LPCTSTR sFName)
{
  AFX_MANAGE_STATE(AfxGetAppModuleState());
CString sFile;
sFile=sFName;
FILE* pFile;
outtext1("Exporting groups to file");
if (sFile != "")
{
  pFile = fopen(sFile,"w");
  if (pFile!=NULL)
  {
	cDBase->ExportPermGroupsTXT(pFile);
	fclose(pFile);
  } 
}
  // TODO: Add your dispatch handler code here
}

void CM3daDoc::OnChecksMergenodes()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("MERNODES");
  sLastcmd="MERNODES";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnMeshBuildassemblymesh()
{
// TODO: Add your command handler code here
outtext1("Starting to build assembly mesh");
cDBase->BuildAssembly("");
outtext1("Finished final model generation");
}

void CM3daDoc::OnSurfaceSweep()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("SURSWEEP");
  sLastcmd="SURSWEEP";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSolverSolve()
{
  // TODO: Add your command handler code here
  outtextMSG2("SOLVE");
}

void CM3daDoc::OnSolverCreaterestraint()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("RCR");
  sLastcmd="RCR";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSolverCreateforce()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("FCR");
  sLastcmd="FCR";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSurfacesonSurfacecurves()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_SURC);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnSurfacesSurfaceson()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_SURFACES);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnVisabilityPointson()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_POINTS);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnCircleCirclecenreradius()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CIRCR2");
  sLastcmd="CIRCR2";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnCircleCircle3points()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CIR3PT");
  sLastcmd="CIR3PT";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnCircleArc3point()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ARC3PT");
  sLastcmd="ARC3PT";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionSurfacesbycolour()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELSURFCOL");
  sLastcmd="SELSURFCOL";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSelectionCurvesbycolour()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELCURCOL");
  sLastcmd="SELCURCOL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnSelectionPointsbycolour()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELPTSCOL");
  sLastcmd="SELPTSCOL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnWorkplainWpaligntocurve()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("WPONCV");
  sLastcmd="WPONCV";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnWorkplainWpaligntosurface()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("WPONSURF");
  sLastcmd="WPONSURF";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnWorkplainWpcentre()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("WPCENT");
  sLastcmd="WPCENT";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnElementtypeScellcfd()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELTYPE");
  outtextMSG2("SCELL");

}

void CM3daDoc::OnAnalysisSolveimcompfluids()
{
  // TODO: Add your command handler code here
  outtext1("SOLVING INCOMPRESSIBLE FLUIDS");
  cDBase->SolveIncompFluids();
}

void CM3daDoc::OnImportOp2()
{
  // TODO: Add your command handler code here
  outtext1("IMPORT OP2 RESULTS FILE");
  outtext1("DATA BLOCKS:-");
  FILE* pFile;
	//TODO: Add your command handler code here
	CFileDialog FDia( TRUE,"op2", "*.op2",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	FDia.DoModal();	
	CString sPath = FDia.GetPathName();
  CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		pFile = fopen(sPath,"rb");
		if (pFile!=NULL)
		  {
		  cDBase->S_ImportOp2(pFile,sFile,1);
		  fclose(pFile);
		  } 
	}
}

void CM3daDoc::OnPostListresset()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  outtextMSG2("RESSETLIST");
  sLastcmd="RESSETLIST";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnPostSelectresults()
{
  // TODO: Add your command handler code here
  //outtextMSG2("RESSEL");
  sLastcmd="RESSEL";
  //cDBase->InvalidateOGL();
  //cDBase->ReDraw();
  cDBase->ResSelect();
}

void CM3daDoc::OnPostListselectedresset()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  outtextMSG2("RESSETFULLLIST");
  sLastcmd="RESSETFULLLIST";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnPostContourrawdata()
{
  // TODO: Add your command handler code here
  if (cDBase->DspFlags & DSP_LINE == 1)
    cDBase->DspFlags=(cDBase->DspFlags ^ DSP_LINE);
  cDBase->DspFlags=(cDBase->DspFlags ^ DSP_CONT);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnPostSelectvariable()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  outtextMSG2("RESSELVAR");
  sLastcmd="RESSELVAR";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnPostTogresultslabels()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_RESLAB);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();

}

void CM3daDoc::OnPostDeformeddisplay()
{
  // TODO: Add your command handler code here
  
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_RESDEF);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
  

}

void CM3daDoc::OnPostSelectdeformedresults()
{
  // TODO: Add your command handler code here
  cDBase->ResSelectDef();
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}



void CM3daDoc::OnOptionsDeformationscale()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  outtextMSG2("RESSETDEFSCL");
  sLastcmd="RESSETDEFSCL";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnProperty2dplainstress()
{
  // TODO: Add your command handler code here


if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("PRSHELL");
  sLastcmd="PRSHELL";
}
else
{
  outtext1("Finish Current Operation.");
}

}







void CM3daDoc::OnAnalysisCreatemoment()
{

  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("MCR");
  sLastcmd="MCR";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnAnalysisCreatepressure()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("PCR");
  sLastcmd="PCR";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnVisabilityBoundaryconditions()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_BC);
	cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnPostExportresultstotextfile()
{
// TODO: Add your command handler code here
outtext1("Exporting results to file");
FILE* pFile;
CFileDialog FDia(FALSE,"txt", "*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"w");
  if (pFile!=NULL)
  {
	cDBase->ExportRes(pFile);
	fclose(pFile);
  } 
}
}

void CM3daDoc::OnNodemodifyLabel()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDMOLAB");
  sLastcmd="NDMOLAB";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnElementmodifiyLabelbyinc()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELMOLAB");
  sLastcmd="ELMOLAB";
}
else
{
  outtext1("Finish Current Operation.");
}

}

void CM3daDoc::OnNodemodifyLabelbystart()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("NDMOLAB2");
  sLastcmd="NDMOLAB2";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnElementmodifiyLabelbystart()
{
  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELMOLAB2");
  sLastcmd="ELMOLAB2";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnMeshFreetrimesh()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("FMESHT");
    sLastcmd="FMESHT";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnPostListelementresult()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("RESLISTEL");
    sLastcmd="RESLISTEL";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnViewGfradientfilledbackground()
{
	// TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_GRAD);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}

void CM3daDoc::OnExportExporttotext()
{
	// TODO: Add your command handler code here
// TODO: Add your command handler code here
outtext1("EXPORTING TO TEXT");
FILE* pFile;
CFileDialog FDia(FALSE,"dat", "*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"w");
  if (pFile!=NULL)
  {
	cDBase->ExportToText(pFile);
	fclose(pFile);
  } 
}
}


void CM3daDoc::OnElementmodifiyReverse()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
	SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("ELREV");
    sLastcmd="ELREV";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnMeshqnd()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
	SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("MESHQND");
    sLastcmd="MESHQND";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnImportTxttogroups()
{

  outtext1("IMPORT GROUPS TXT FILE");
  FILE* pFile;
	//TODO: Add your command handler code here
  CFileDialog FDia( TRUE,"txt", "*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
  FDia.DoModal();	
  CString sPath = FDia.GetPathName();
  CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
	  pFile = fopen(sPath,"r");
	  if (pFile!=NULL)
	  {
		cDBase->S_ImportGroups(pFile);
	  } 
	fclose(pFile);
	}
}


void CM3daDoc::OnViewDisplaymaterialdurection()
{
	// TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_MATL);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}


void CM3daDoc::OnOptionsSetcolourbar()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("RESSETCOLBAR");
  sLastcmd="RESSETCOLBAR";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnVisabilityCoordson()
{
	// TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_COORD);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}


void CM3daDoc::OnGroupNextgroup()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
	outtextMSG2("GPNEXT");
    sLastcmd="GPNEXT";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnGroupPreviousgrpup()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
	outtextMSG2("GPPREV");
    sLastcmd="GPPREV";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnGroupElementsbytype()
{
	// TODO: Add your command handler code here
	  // TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPBYTYPE");
  sLastcmd="GPBYTYPE";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnGroupNodebycolour()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPNDBYCOL");
  sLastcmd="GPNDBYCOL";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnGroupNodebuoutputsys()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPNDBYOSYS");
  sLastcmd="GPNDBYOSYS";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnGroupNodebydefinitionsystem()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPNDBYDSYS");
  sLastcmd="GPNDBYDSYS";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnGroupElementsbymid()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("GPBYMID");
  sLastcmd="GPBYMID";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnPostDeleteallresultssets()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("RESDEL");
  sLastcmd="RESDEL";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnOptionsReversecolourbar()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("RESREVCOLBAR");
  sLastcmd="RESREVCOLBAR";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnSelectionInvertselection()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  outtextMSG2("SELINV");
  sLastcmd="SELINV";
}
else
{
  outtext1("Finish Current Operation.");
}
}


void CM3daDoc::OnQwantaDebug()
{
	// TODO: Add your command handler code here
  API_ImportCat("F:\\b\\WR51_2D_4x6_mid.cat");
  API_ImpSecT ("F:\\b\\CAT\\DB_SES10.txt");
  API_ImportWG ("F:\\b\\DP0943638_00_01_002_8932E.txt", "NULL");
  API_GenMesh();
}

void CM3daDoc::OnCurvemodifyWeightlarge()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CVMOLWL");
  sLastcmd="CVMOLWL";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnCurvemodifyWeightmedium()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CVMOLWM");
  sLastcmd="CVMOLWM";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnCurvemodifyWeightthin()
{
	// TODO: Add your command handler code here

if (pMnu->isNULL())
{
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("CVMOLWT");
  sLastcmd="CVMOLWT";
}
else
{
  outtext1("Finish Current Operation.");
}
}

void CM3daDoc::OnCurvemodifyDash()
{
	// TODO: Add your command handler code here

	if (pMnu->isNULL())
	{
	SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("CVMODASH");
    sLastcmd="CVMODASH";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnCurvemodifyDot()
{
	// TODO: Add your command handler code here

	if (pMnu->isNULL())
	{
	SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("CVMODOT");
    sLastcmd="CVMODOT";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnCurvemodifySolid()
{
	// TODO: Add your command handler code here

	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("CVMOSOL");
      sLastcmd="CVMOSOL";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnCurvemodifyCentre()
{
	// TODO: Add your command handler code here

	if (pMnu->isNULL())
	{
      SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("CVMOCTR");
      sLastcmd="CVMOCTR";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnPointmodifyCtrlpointweight()
{
	// TODO: Add your command handler code here

	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("CVMOW");
      sLastcmd="CVMOW";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnImportSymbolstable()
{
// TODO: Add your command handler code here
outtext1("IMPORT SYMBOLS TABLE");
FILE* pFile;
//TODO: Add your command handler code here
CFileDialog FDia( TRUE,"symbols", "*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
FDia.DoModal();	
CString sPath = FDia.GetPathName();
CString sFile = FDia.GetFileName();
if (sFile != "")
{
  pFile = fopen(sPath,"r");
  if (pFile!=NULL)
  {
	cDBase->LoadSymbols(pFile);
  } 
  fclose(pFile);
}
}

void CM3daDoc::OnCircleCirclecentrepoint()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("CIRCPT");
      sLastcmd="CIRCPT";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnToolsReflect2d()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("REFLECT2D");
      sLastcmd="REFLECT2D";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}



void CM3daDoc::OnToolsCopyrotate2d()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("COPYROT2D");
      sLastcmd="COPYROT2D";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnToolsMoveto()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("MOVETO");
      sLastcmd="MOVETO";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnToolsCopyto()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("COPYTO");
      sLastcmd="COPYTO";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnSurfaceUn()
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("SURFUNTRIM");
      sLastcmd="SURFUNTRIM";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnMeshTetfromshellboundary()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
    //outtext1("Not Available Yet!");
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("MMESHTET");
    sLastcmd="MMESHTET";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnChecksFreefacedsp()
{
	if (pMnu->isNULL())
	{
      outtextMSG2("FFACE");
      sLastcmd="FFACE";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnMeshShellcoatsolidelements()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("MSHELL");
      sLastcmd="MSHELL";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnChecksFreeedgedisplay()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
      outtextMSG2("FEDGE");
      sLastcmd="FEDGE";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnMeshQuadtotri()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("MQUADTOTRI");
      sLastcmd="MQUADTOTRI";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnChecksShellnormalconsistancy()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("SNORM");
      sLastcmd="SNORM";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnAnalysisLoadsets()
{
	// TODO: Add your command handler code here
	cDBase->AnalysisLoadsets();
}

void CM3daDoc::OnLoadsbcBcsets()
{
	// TODO: Add your command handler code here
	cDBase->AnalysisBCsets();
}

void CM3daDoc::OnLoadsbcTemperaturesets()
{
	// TODO: Add your command handler code here
	cDBase->AnalysisTEMPsets();
}

void CM3daDoc::OnLoadsbcCreatestructuraltemp()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("TCR");
      sLastcmd="TCR";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnLoadsbcCreatethermalnettfluxload()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("FLUXCR");
      sLastcmd="FLUXCR";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnLoadsbcCreatethermaltempbc()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
      outtextMSG2("TBCR");
      sLastcmd="TBCR";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnSolutionListsolutionsequences()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
	{
    outtextMSG2("SOLLIST");
    sLastcmd="SOLLIST";
	}
	else
	{
    outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnSolutionCreatesolutionsequence()
{
  // TODO: Add your command handler code here
  cDBase->AnalysisSolution();
  //if (pMnu->isNULL())
	//{
	//  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  //  outtextMSG2("SOLCR");
  //  sLastcmd="SOLCR";
	//}
	//else
	//{
  //    outtext1("Finish Current Operation.");
	//}
}

void CM3daDoc::OnSolutionCreate()
{
  // TODO: Add your command handler code here
  cDBase->AnalysisLoadStep();

 // if (pMnu->isNULL())
	//{
	//  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
 //   outtextMSG2("STEPCR");
 //   sLastcmd="STEPCR";
	//}
	//else
	//{
 //     outtext1("Finish Current Operation.");
	//}
}

void CM3daDoc::OnLoadsbcListloadsets()
{
  if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("LSETLIST");
    sLastcmd="LSETLIST";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnLoadsbcListboundarysets()
{
  if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("BSETLIST");
    sLastcmd="BSETLIST";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnLoadsbcListtemperaturesets()
{
  if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("TSETLIST");
    sLastcmd="TSETLIST";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnLoadsbcCreateaccelerationbodyload()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("ACR");
    sLastcmd="ACR";
	}
	else
	{
      outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnElementtypeTranslationalspring()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELTYPE");
  outtextMSG2("TSPRING");
}

void CM3daDoc::OnElementtypeRotationalspring()
{
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELTYPE");
  outtextMSG2("RSPRING");
}

void CM3daDoc::OnElementmodifiySpringcoordsystem()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("SPGMOSYS");
    sLastcmd="SPGMOSYS";
	}
	else
	{
    outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnPropertyRotationalspring()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    //outtextMSG2("PRSPGR");
    //sLastcmd="PRSPGR";
	  int iNLab = cDBase->PropsT->NextID();
	  cDBase->CreatePrSpringR("Rotational Spring", iNLab, 1.0e5, 1.0e5, 1.0e5, 1000);
	  cDBase->EditProp(iNLab);
	}
	else
	{
    outtext1("Finish Current Operation.");
	}
}

void CM3daDoc::OnPropertyTranslationalspring()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
	{
	  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    //outtextMSG2("PRSPGT");
    //sLastcmd="PRSPGT";
	  int iNLab = cDBase->PropsT->NextID();
	  cDBase->CreatePrSpringT("Translational Spring", iNLab, 1.0e7, 1.0e7, 1.0e7, 1000);
	  cDBase->EditProp(iNLab);
	}
	else
	{
    outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnChecksNegativevolumeelements()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("CHKJAC");
    sLastcmd = "CHKJAC";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnChecksCheckshellelementaspectration()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("CHKSHELLASP");
    sLastcmd = "CHKSHELLASP";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnChecksChecktetcollapse()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("CHKTETCOL");
    sLastcmd = "CHKTETCOL";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnElementtypeMass()
{
  // TODO: Add your command handler code here
  // TODO: Add your command handler code here
  SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
  outtextMSG2("ELTYPE");
  outtextMSG2("SCALAR");
}


void CM3daDoc::OnPropertyLumpedmass()
{
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    //outtextMSG2("PRMASS");
    //sLastcmd = "PRMASS";
	int iNLab = cDBase->PropsT->NextID();
	cDBase->CreatePrLumpedMass("Lumped Mass Property", iNLab, 0.1);
	cDBase->EditProp(iNLab);
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnVisabilityWorkplane()
{
  // TODO: Add your command handler code here
  cDBase->DspFlags = (cDBase->DspFlags ^ DSP_WP);
  cDBase->InvalidateOGL();
  cDBase->ReDraw();
}


void CM3daDoc::OnToolsMeasureangle()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    outtextMSG2("AMEAS");
    sLastcmd = "AMEAS";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnLoadsbcCreaterotationalbodyload()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    outtextMSG2("RACR");
    sLastcmd = "RACR";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}





void CM3daDoc::OnToolsElementmasssummation()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    outtextMSG2("ELMASS");
    sLastcmd = "ELMASS";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnElementmodifiyShellmatcorrdsystem()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    outtextMSG2("ELMOSHELLMCYS");
    sLastcmd = "ELMOSHELLMCYS";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnChecksCoincidentelements()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    outtextMSG2("CELM");
    sLastcmd = "CELM";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnNodemodifyChangexordinate()
{
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("NODEX");
    sLastcmd = "NODEX";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnNodemodifyChangeyordinate()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("NODEY");
    sLastcmd = "NODEY";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnNodemodifyChangezordinate()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("NODEZ");
    sLastcmd = "NODEZ";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnPropertymodifyEditpropertyvalues()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("PREDIT");
    sLastcmd = "PREDIT";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnPropertyEditmaterialvalues()
{
  // TODO: Add your command handler code here
  if (pMnu->isNULL())
  {
    SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
    outtextMSG2("MATEDIT");
    sLastcmd = "MATEDIT";
  }
  else
  {
    outtext1("Finish Current Operation.");
  }
}


void CM3daDoc::OnPropertyBeamBasic()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		//outtextMSG2("PRBAR2");
		//sLastcmd = "PRBAR2";
		int iNLab = cDBase->PropsT->NextID();
		cDBase->CreatePRBar2("Bar Property", iNLab, -1, 0.0000785398, 4.90874e-10, 4.90874e-10, 4.90874e-10+ 4.90874e-10);
		cDBase->EditProp(iNLab);
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnViewSurfacedirectionmarkers()
{
	// TODO: Add your command handler code here
	cDBase->DspFlags = (cDBase->DspFlags ^ DSP_SURFU);
	cDBase->InvalidateOGL();
	cDBase->ReDraw();
}


void CM3daDoc::OnPostListnodalresults()
{
	if (pMnu->isNULL())
	{
		outtextMSG2("RESLISTND");
		sLastcmd = "RESLISTND";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnCurvemodifyInsertknot()
{
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("KNOTINS");
		sLastcmd = "KNOTINS";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostAnimate()
{
	// TODO: Add your command handler code here
	cDBase->Animate();
}


void CM3daDoc::OnPostAnimateneg()
{
	// TODO: Add your command handler code here
	cDBase->AnimatePosNeg();
}


void CM3daDoc::OnPostFramedelay()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("RESDELAY");
		sLastcmd = "RESDELAY";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostAnimationframes()
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("RESFRAMES");
		sLastcmd = "RESFRAMES";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyBeamendarelease()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("BDOFA");
		sLastcmd = "BDOFA";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyBeamendbrelease()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("BDOFB");
		sLastcmd = "BDOFB";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnOptionsDeformationoffset()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("RESDISPOFF");
		sLastcmd = "RESDISPOFF";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostListresultsvectors()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("RESVECLIST");
		sLastcmd = "RESVECLIST";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnToolsEditobject()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("OEDIT");
		sLastcmd = "OEDIT";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnOptionsVectorscale()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("RESSETVECSCL");
		sLastcmd = "RESSETVECSCL";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostSelectvectorresults()
{
	// TODO: Add your command handler code here
	cDBase->ResSelectVec();
	cDBase->InvalidateOGL();
	cDBase->ReDraw();
}


void CM3daDoc::OnPostClearresultsvectors()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("RESVECDEL");
		sLastcmd = "RESVECDEL";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshAdvancingfrontsurfacemeshtri()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("MMESHAF");
		sLastcmd = "MMESHAF";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnLineMultiline()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("LNC");
		sLastcmd = "LNC";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnChecks2dsectionpropertiesaixxiyyetc()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("CHK2D");
		sLastcmd = "CHK2D";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshmanagementListallmeshes()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("MSHLIST");
		sLastcmd = "MSHLIST";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshmanagementCreatenewmesh()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("MSHCR");
		sLastcmd = "MSHCR";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshmanagementSetactivemesh()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("MSHACT");
		sLastcmd = "MSHACT";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshmanagementTogglemeshvisability()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("MSHVIS");
		sLastcmd = "MSHVIS";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshmanagementDeletemesh()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("MSHDEL");
		sLastcmd = "MSHDEL";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnViewHideentities()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("HIDE");
		sLastcmd = "HIDE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnViewShowallhidden()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("SHOWALL");
		sLastcmd = "SHOWALL";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostListresponsedata()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("RESLSTRESP");
		sLastcmd = "RESLSTRESP";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshMeshsizeonsurface()
{
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("MMESHSZ");
		sLastcmd = "MMESHSZ";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPartmodifyExtract()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("EXTRACT");
		sLastcmd = "EXTRACT";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnChecksTetcircumsphere()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("CHKCIRCUMSPH");
		sLastcmd = "CHKCIRCUMSPH";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnFemtoolsMeshsizeoncurves()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint();bFinalChkPt=FALSE;
		outtextMSG2("MMESHBZ");
		sLastcmd = "MMESHBZ";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


//void CM3daDoc::OnEditRedo()
//{
//	// TODO: Add your command handler code here
//
//}


//void CM3daDoc::OnUpdateEditRedo(CCmdUI *pCmdUI)
//{
//	// TODO: Add your command update UI handler code here
//}





BOOL CM3daDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!__super::OnOpenDocument(lpszPathName))
		return FALSE;
	ReSet();
	CheckPoint();
	// TODO:  Add your specialized creation code here

	return TRUE;
}


void CM3daDoc::OnCurvetoolsText()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("TEXTCR");
		sLastcmd = "TEXTCR";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPropertyPcomp()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		//outtextMSG2("PRPCOMP");
		//sLastcmd = "PRPCOMP";
		int iNLab = cDBase->PropsT->NextID();
		CString sLay[50];
		sLay[0] = "1,1,0";
		cDBase->CreatePrPCOMP("NAME", iNLab, 0.0, 1, sLay);
		cDBase->EditProp(iNLab);
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMaterialOrthotropic()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		//outtextMSG2("MMAT8");
		//sLastcmd = "MMAT8";
		int iNLab = cDBase->MatT->NextID();
		cDBase->CreateMat8("NASTRAN MAT8 Property", iNLab, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0);
		cDBase->EditMat(iNLab, FALSE);
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPropertyDisplaylaminatestack()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DSPLAM");
		sLastcmd = "DSPLAM";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPropertyPbush()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		//outtextMSG2("PRBUSH");
		//sLastcmd="PRBUSH";
		int iNLab = cDBase->PropsT->NextID();
		cDBase->CreatePrBUSH("NASTRAN PBUSH Property", iNLab, 1.0e7, 1.0e7, 1.0e7, 1.0e4, 1.0e4, 1.0e4);
		cDBase->EditProp(iNLab);

	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnManipulationDivideinto()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		//SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("RESDIVINTO");
		sLastcmd = "RESDIVINTO";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnManipulationEnvelopemaximum()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		//SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("RESENVMAX");
		sLastcmd = "RESENVMAX";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnManipulationEnvelopeminimum()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		//SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("RESENVMIN");
		sLastcmd = "RESENVMIN";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnManipulationScale()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		//SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("RESSCALE");
		sLastcmd = "RESSCALE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnEditToggleon()
{
	// TODO: Add your command handler code here
	if (bUndo)
	{
		bUndo = FALSE;
		ReSet();
		SetUndoLevels(0);
	}
	else
	{
		bUndo = TRUE;
		ReSet();
		SetUndoLevels(4);
		CheckPoint();
	}
}


void CM3daDoc::OnPropertyBeamT2()
{
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		//outtextMSG2("PRBBAR");
		//sLastcmd="PRBBAR";
		int iNLab = cDBase->PropsT->NextID();
		cDBase->CreatePrT2("T2 Beam Property", iNLab, -1, 1.0, 2.0,0.5,0.2);
		cDBase->EditProp(iNLab);
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPropertyBeamChan2()
{
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		//outtextMSG2("PRBBAR");
		//sLastcmd="PRBBAR";
		int iNLab = cDBase->PropsT->NextID();
		cDBase->CreatePrCHAN2("CHAN2 Beam Property", iNLab, -1, 2, 1, 0.5, 0.2);
		cDBase->EditProp(iNLab);
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPropertyBeamI2()
{
	if (pMnu->isNULL())
	{
		// TODO: Add your command handler code here
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		//outtextMSG2("PRBBAR");
		//sLastcmd="PRBBAR";
		int iNLab = cDBase->PropsT->NextID();
		cDBase->CreatePrI2("I2 Beam Property", iNLab, -1, 0.6, 0.4, 0.2, 0.1, 0.05, 0.05);
		cDBase->EditProp(iNLab);
	}
	else
	{
	outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPropertyBeamL()
{
	if (pMnu->isNULL())
	{
		// TODO: Add your command handler code here
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		int iNLab = cDBase->PropsT->NextID();
		cDBase->CreatePrL("L Beam Property", iNLab, -1, 0.07, 0.07, 0.008, 0.008);
		cDBase->EditProp(iNLab);
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyBeamoffsetinbeamy()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("BOFFY");
		sLastcmd = "BOFFY";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyBeamoffsetinbeamz()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("BOFFZ");
		sLastcmd = "BOFFZ";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnToolsPlanet()
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	outtext1("IMPORT EARTH BMP FILE");
	//TODO: Add your command handler code here
	CFileDialog FDia(TRUE, "BMP", "*.BMP", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		if (cDBase->S_loadBMP(sPath, sFile))
			cDBase->insPlanet();
	}
}


void CM3daDoc::OnFemtoolsSweepnodestoshells()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("ELSWEEPNDS");
		sLastcmd = "ELSWEEPNDS";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnFemtoolsSweepnodestobeams()
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("ELSWEEPNDB");
		sLastcmd = "ELSWEEPNDB";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostListresponsedataallvars()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("RESLSTRESPFULL");
		sLastcmd = "RESLSTRESPFULL";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostLabelresponseentities()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("RESLABRESP");
		sLastcmd = "RESLABRESP";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnPostGraphresponsedata()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("RESGRAPHRESP");
		sLastcmd = "RESGRAPHRESP";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}





void CM3daDoc::OnFemtoolsSweepnodestobeams33361()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("ELSWEEPNDB");
		sLastcmd = "ELSWEEPNDB";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnFemtoolsSweepnodestoshells33362()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("ELSWEEPNDS");
		sLastcmd = "ELSWEEPNDS";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnViewHighlightlimit()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("HLIMIT");
		sLastcmd = "HLIMIT";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnSelectionRbecentrenodes()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("SELRBENODE");
		sLastcmd = "SELRBENODE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnChecksCountf()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("CHKCOUNT");
		sLastcmd = "CHKCOUNT";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnCurvemodifySplitatpoint()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("CVSPLIT");
		sLastcmd = "CVSPLIT";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyIntersecttrielements()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("MESHINT");
		sLastcmd = "MESHINT";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnNodemodifyEquivalencelab()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("NDEQLAB");
		sLastcmd = "NDEQLAB";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyColourbypid()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("COLPID");
		sLastcmd = "COLPID";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnExportIncludefile()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		//SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("EXPINC");
		sLastcmd = "EXPINC";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnGroupGroupfromincludefile()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("GPBYINC");
		sLastcmd = "GPBYINC";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnMeshmanagementSetincludefileno()
{
	// TODO: Add your command handler code here 
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("MODINCNO");
		sLastcmd = "MODINCNO";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyColourbyincludefile()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("COLINC");
		sLastcmd = "COLINC";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnCurvetoolsOrthosnap()
{
	// TODO: Add your command handler code here

		if (gORTHO == FALSE)
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


void CM3daDoc::OnCurvemodifyTrim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("TRIM");
		sLastcmd = "TRIM";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnListGapsbetweenlabels()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("LABGAP");
		sLastcmd = "LABGAP";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnListGapsbetweenmatsandpropslabels()
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("LABGAPMP");
		sLastcmd = "LABGAPMP";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementmodifiyInsertspringonrigid()
{
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("ELINSSPG");
		sLastcmd = "ELINSSPG";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnFemtoolsSweepedgesoutward()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("ELSWEEPB");
		sLastcmd = "ELSWEEPB";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizePoint()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("PTSIZE");
		sLastcmd = "PTSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeNode()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("NDSIZE");
		sLastcmd = "NDSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeLumpmass()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("LMSIZE");
		sLastcmd = "LMSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeElementedge()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("ELSIZE");
		sLastcmd = "ELSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeElementfreeedge()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("EDSIZE");
		sLastcmd = "EDSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeElementfreeface()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("FCSIZE");
		sLastcmd = "FCSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeWorkplanelines()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("WPLSIZE");
		sLastcmd = "WPLSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeBeams()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("BMSIZE");
		sLastcmd = "BMSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnObjectsizeText()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("TXTSIZE");
		sLastcmd = "TXTSIZE";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnExportExportviewmatrix()
{
	// TODO: Add your command handler code here
	outtext1("EXPORTING CURRENT VIEW MATRIX");
	FILE* pFile;
	CFileDialog FDia(FALSE, "MTX", "*.MTX", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		pFile = fopen(sPath, "w");
		if (pFile != NULL)
		{
			cDBase->ExportViewMat(pFile);
			fclose(pFile);
		}
	}
}


void CM3daDoc::OnImportImportviewmatrix()
{
	// TODO: Add your command handler code here
	outtext1("IMPORT VIEW MATRIX");
	FILE* pFile;
	//TODO: Add your command handler code here
	CFileDialog FDia(TRUE, "VIEW MATRIX", "*.MTX", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		pFile = fopen(sPath, "r");
		if (pFile != NULL)
		{
			cDBase->ImportViewMat(pFile);
		}
		fclose(pFile);
	}
}


void CM3daDoc::OnCurvetoolsLinethrouptandtangenttocircle()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("LNTANCIR");
		sLastcmd = "LNTANCIR";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnCurvetoolsLinetangentto2circles()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("LNTAN2CIR");
		sLastcmd = "LNTAN2CIR";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnCurvetoolsPointsoncircle()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("PTSONCIR");
		sLastcmd = "PTSONCIR";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnEditPolartranslatedfrom()
{
	// TODO: Add your command handler code here
	outtextMSG2("PTRAN");
}


void CM3daDoc::OnViewTogglecontrolpointvisability()
{
	// TODO: Add your command handler code here
	if (gDSP_CPTS == FALSE)
	{
		gDSP_CPTS = TRUE;
		outtext1("All Control Points ON.");
	}
	else
	{
		gDSP_CPTS = FALSE;
		outtext1("All Control Points OFF.");
	}
	cDBase->InvalidateOGL();
	cDBase->ReDraw();
}


void CM3daDoc::OnExportExportdxf()
{
	// TODO: Add your command handler code here
	outtext1("EXPORTING 2D DXF FILE");
	FILE* pFile;
	CFileDialog FDia(FALSE, "dxf", "*.dxf", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		pFile = fopen(sPath, "w");
		if (pFile != NULL)
		{
			cDBase->ExportDXF(pFile);
			fclose(pFile);
		}
	}
}


void CM3daDoc::OnCurvemodifyLayernumber()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("MODLAYNO");
		sLastcmd = "MODLAYNO";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnSelectionSelectcurve()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("SELCURLAY");
		sLastcmd = "SELCURLAY";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnViewToggleoncirclestartmarkers()
{
	// TODO: Add your command handler code here
	if (gDSP_CIRS == FALSE)
	{
		gDSP_CIRS = TRUE;
		outtext1("Circle Start Markers ON.");
	}
	else
	{
		gDSP_CIRS = FALSE;
		outtext1("Circle Start Markers OFF.");
	}
	cDBase->InvalidateOGL();
	cDBase->ReDraw();

}


void CM3daDoc::OnToolsInsertbitmapbackground()
{
	// TODO: Add your command handler code here
	outtext1("IMPORT BMP BACKGROUND FILE");
	//TODO: Add your command handler code here
	CFileDialog FDia(TRUE, "BMP", "*.BMP", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		if (cDBase->S_loadBMP(sPath, sFile))
			cDBase->insBackGround();
	}
	
}


void CM3daDoc::OnViewToggleon()
{
	// TODO: Add your command handler code here
	if (gDSP_BACK == FALSE)
	{
		gDSP_BACK = TRUE;
		outtext1("Background is ON.");
	}
	else
	{
		gDSP_BACK = FALSE;
		outtext1("Background is OFF.");
	}
	cDBase->InvalidateOGL();
	cDBase->ReDraw();
}


void CM3daDoc::OnQfilterNodes()
{
	// TODO: Add your command handler code here
	cDBase->QFilterNode();
}


void CM3daDoc::OnQfilterElements()
{
	// TODO: Add your command handler code here
	cDBase->QFilterElement();
}


void CM3daDoc::OnQfilterPoints()
{
	// TODO: Add your command handler code here
	cDBase->QFilterPoint();
}


void CM3daDoc::OnQfilterCurves()
{
	// TODO: Add your command handler code here
	cDBase->QFilterCurve();
}


void CM3daDoc::OnQfilterSurface()
{
	// TODO: Add your command handler code here
	cDBase->QFilterSurface();
}


void CM3daDoc::OnQfilterAll()
{
	// TODO: Add your command handler code here
	cDBase->QFilterAll();
}


void CM3daDoc::OnDimensiontoolsDimsize()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		outtextMSG2("DIMSCL");
		sLastcmd = "DIMSCL";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsAligneddim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMA");
		sLastcmd = "DIMA";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsLineardim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMHV");
		sLastcmd = "DIMHV";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsHorizontaldim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMH");
		sLastcmd = "DIMH";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsVerticaldim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMV");
		sLastcmd = "DIMV";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsLeadertext()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIML");
		sLastcmd = "DIML";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsRadiusdim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMR");
		sLastcmd = "DIMR";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsDiameterdim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMD");
		sLastcmd = "DIMD";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsAngulardimby3points()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMANG");
		sLastcmd = "DIMANG";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsDragdim()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMDRAG");
		sLastcmd = "DIMDRAG";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnDimensiontoolsCirclecentremarker()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("DIMCL");
		sLastcmd = "DIMCL";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnElementtypeBush()
{
	// TODO: Add your command handler code here
	outtextMSG2("ELTYPE");
	outtextMSG2("BUSH");
}


void CM3daDoc::OnEditGlobalpreferences()
{
	// TODO: Add your command handler code here
	cDBase->EditGlobals();
}


void CM3daDoc::OnLoadsbcCreatetempd()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("TEMPD");
		sLastcmd = "TEMPD";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnLoadsbcCreategrav()
{
	// TODO: Add your command handler code here
	if (pMnu->isNULL())
	{
		SetModifiedFlag(); CheckPoint(); bFinalChkPt = FALSE;
		outtextMSG2("GRAV");
		sLastcmd = "GRAV";
	}
	else
	{
		outtext1("Finish Current Operation.");
	}
}


void CM3daDoc::OnExportCurrentStl()
{
	// TODO: Add your command handler code here
	outtext1("EXPORTING TO STL");
	FILE* pFile;
	CFileDialog FDia(FALSE, "stl", "*.stl", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "")
	{
		pFile = fopen(sPath, "w");
		if (pFile != NULL)
		{
			cDBase->ExportMesh2STL(sPath);
		}
	}
}
