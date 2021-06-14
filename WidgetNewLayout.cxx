/*Create a new 3D widget outside the current layout to display in stereo mode,
Needs to have :
- a surface supporting stereo mode
- a new widget of qMRMLThreeDWidget type to be suppored by 3DSlicer
- a render window set up for stereo mode
- a new MRML node connected to the actual MRML Scene
- a new layout to add to the layout manager
*/

// Qt includes
#include <QSurfaceFormat>

// MRML includes
#include <vtkMRMLScene.h> //marine, include pour les nodes et la scene
#include <vtkMRMLViewNode.h> //marine, include pour les nodes et la scene
// #include "vtkMRMLLayoutLogic.h" marine, so far pas eu besoin

// MRMLWidgets includes
#include <qMRMLThreeDWidget.h> //marine, accede à la renderwindow depuis threedview car herite de ctkVTKRenderView qui herite de ctkVTKAbstractView 
// #include <qMRMLThreeDViewControllerWidget.h> marine, so far pas eu besoin
// 
// MRMLLogic includes
#include <vtkMRMLViewLogic.h> //marine, include pour les nodes et la scene

// Slicer includes
#include <QVTKOpenGLStereoWidget.h> //marine, on utilise cet version car derniere en date et normalement fonctionne
#include <QVTKOpenGLNativeWidget.h>
// #include "qSlicerApplication.h"  marine, so far pas eu besoin
// #include "qSlicerLayoutManager.h"  marine, so far pas eu besoin

// VTK includes
#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

/*
* Verifie les versions vtk ? si oui voir le render no ui file dans vtk examples
* !! pense plutot lever une exception si pas vtk 9 car marche pas en 8?
#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif
*/
// Marine, de ce que j'ai capte grace a mes test avec vtk 9.0 vtk890 = vtk 9 




int main(int argc, char** argv)
{
	//marine, LAYOUT
	string layoutName("Test3DView");
	string layoutLabel("QB");
	float layoutColor[3] = { 0.0, 0.0, 1.0 };

	// marine, ownerNode manages this view instead of the layout manager(it can be any node in the scene)
	vtkNew<vtkMRMLScene> viewOwnerNode;
	viewOwnerNode->AddNewNodeByClass("vtkMRMLQuadBufferModuleNode");

	//marine, Create MRML NODE
	vtkNew<vtkMRMLViewLogic> viewLogic;
	viewLogic->setMRMLScene(q->mrmlScene()); //marine, pk q dans le module view controller??

	vtkNew<vtkMRMLViewNode> viewNode;
	viewNode.viewLogic->AddViewNode(layoutName); //marine , structure de ce truc??
	viewNode->SetLayoutLabel(layoutLabel);  //marine,trouve ses fonctions dans son heritage
	viewNode->SetLayoutColor(layoutColor);
	viewNode->SetAndObserveParentLayoutNodeID(viewOwnerNode.GetID()); //marine, structure?
	viewNode->SetStereoType(1); // on active le mode stereo dans le noeud, ne sait pas si ca sert



	//WIDGET
	// pour palier au manque de : QVTKOpenGLStereoWidget,  on créer un widget slicer classique et on lui ajoute la render window
	qMRMLThreeDWidget viewWidget;
	viewWidget->setQuadBufferStereoSupportEnabled(1);
	viewWidget->SetMRMLScene(q->mrmlScene()); //marine, voir pk cette structure
	viewWidget->SetMRMLViewNode(viewNode);
	
	//!!!!!!!!!!! doit mettre la surface dans le widget
	// marine, SURFACE
	// marine, oblige de modifier la surface pour afficher en stereo
	QSurfaceFormat format;
	format.setStereo(true);
	viewWidget.setFormat(format);
	
	//marine, RENDER WINDOW ?
	renderWindow = viewWiget.threeDView().renderWindow();
	renderWindow->SetStereoType(1);
	renderWindow->SetStereoCapableWindow(1);
	renderWindow->SetStereoRender(1);
	viewWidget.setRenderWindow(renderWindow);  // PAS TESTER AVEC
	//widget.resize(600, 600);
	viewWidget.renderWindow()->StereoUpdate();
	renderWindow->Render();


	viewWidget.show();

	return EXIT_SUCCESS;
}
