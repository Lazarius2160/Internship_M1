// Create a render window inside a QWidget 
// !! dif widget.renderWindow and the object renderwindow


#include <QApplication>

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
#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif
*/

// Marine, de ce que j'ai capte grace a mes test avec vtk 9.0 vtk890 = vtk 9 

#include <QSurfaceFormat>
#include <QVTKOpenGLStereoWidget.h> //marine, on utilise cet version car derniere en date et normalement fonctionne
#include <QVTKOpenGLNativeWidget.h>
#include <vtkMRMLScene.h> //marine, include pour les nodes et la scene
#include <vtkMRMLViewLogic.h> //marine, include pour les nodes et la scene
#include <vtkMRMLViewNode.h> //marine, include pour les nodes et la scene


int main(int argc, char** argv)
{

  //marine, test creer un widget en stereo hors du layout
  
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

  //marine, pas besoin de app?? QApplication app(argc, argv);
  

  // marine, WIDGET
  // marine, By default setstereo is OFF so quadbuffering is not possible https://doc.qt.io/qt-5/qsurfaceformat.html, voir dans QVTKOpenGLWindow.h ouis qsurfqceformat
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLStereoWidget::defaultFormat(1));
  //marine, pas eu besoin lors des test : widget.setFormat(format);
  
  
  QVTKOpenGLStereoWidget widget;
  // marine, du moment que le widget est creer avec e type stereo, si fait une render window en stereo avnt apres pendnat etc affichera correctement en stereo, et sans stereo (mais moche) si le demande pas
  /*marine, oblige de definir un widget aui accepte la stereo, si pas possible prendre un widget de ce type alors fait :
  * qMRMLThreeDWidget::setQuadBufferStereoSupportEnabled ??? OU
  * qMRMLThreeDViewControllerWidget::setQuadBufferStereoSupportEnabled ??? OU/ET
  * qMRMLThreeDViewControllerWidget::setStereoType
  */

  //marine, RENDER WINDOW ??????????????????????????????????????????
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  //marine, need to set the stereo type before creating the render window
  renderWindow->SetStereoType(1);
  renderWindow->SetStereoCapableWindow(1);
  renderWindow->SetStereoRender(1);
  widget.setRenderWindow(renderWindow); 
  widget.resize(600, 600);
  widget.renderWindow()->StereoUpdate();
  renderWindow->Render();  
  //?????????????????????




  widget.show();

  //marine, pas besoin de app : app.exec();

  return EXIT_SUCCESS;
}
