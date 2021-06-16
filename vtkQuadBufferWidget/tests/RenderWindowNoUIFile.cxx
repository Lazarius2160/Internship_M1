// Create a render window inside a QWidget 
// TESTED TO CREATE 2 DIFFERENT WIDGETS, ONE IN STEREO WITH A STEREO SURFACE AND ONE NATIVE WITH A NATIVE DEFAULT FORMAT TO SEE IF CHANGING THE FORMAT JUST BEFORE SHOWING THE
// WIDGET HAD AN IMPACT. SEE THE TESTS ON THE GRID IN ONE NOTE

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

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif
// Marine, de ce que j'ai capte grace a mes test avec vtk 9.0 vtk890 = vtk 9 

#include <QSurfaceFormat>
#include <QVTKOpenGLStereoWidget.h> //marine, on utilise cet version car derniere en date et normalement fonctionne
#include <QVTKOpenGLNativeWidget.h>

int main(int argc, char** argv)
{

  QApplication app(argc, argv);
  
  //Marine, doit avoir le surface format pret pour la stereo donc utilise :
    
  //marine, ou en une ligne : 
  // si met (0) lors active pas le mode stereo de base doit le reactiver apres
  //QSurfaceFormat::setDefaultFormat(QVTKOpenGLStereoWidget::defaultFormat(1));  
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat(1));

  QVTKOpenGLStereoWidget widget;
  QVTKOpenGLNativeWidget widgetNative; // ne supporte pas le stereo de base!
  
  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindowNative;

#if VTK890
  //marine, need to set the stereo type before creating the render window
  renderWindow->SetStereoType(1);
  renderWindow->SetStereoCapableWindow(1);
  renderWindow->SetStereoRender(1);
  renderWindowNative->SetStereoType(1);
  renderWindowNative->SetStereoCapableWindow(1);
  renderWindowNative->SetStereoRender(1);
  widget.setRenderWindow(renderWindow);
  widgetNative.setRenderWindow(renderWindowNative);
#else 
  renderWindow->SetStereoType(1);
  renderWindow->SetStereoCapableWindow(1);
  renderWindow->SetStereoRender(1);
  widget.SetRenderWindow(renderWindow);
#endif

  widget.resize(600, 600);
  widgetNative.resize(600, 600);

  vtkNew<vtkSphereSource> sphereSource;

  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("LimeGreen").GetData());

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(sphereActor);
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
  //-------------------------------
  vtkNew<vtkSphereSource> sphereSource2;

  vtkNew<vtkPolyDataMapper> sphereMapper2;
  sphereMapper2->SetInputConnection(sphereSource2->GetOutputPort());

  vtkNew<vtkActor> sphereActor2;
  sphereActor2->SetMapper(sphereMapper2);
  sphereActor2->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

  vtkNew<vtkRenderer> renderer2;
  renderer2->AddActor(sphereActor2);
  renderer2->SetBackground(colors->GetColor3d("SteelBlue").GetData());


#if VTK890
  widget.renderWindow()->AddRenderer(renderer);
  widget.renderWindow()->SetWindowName(widget.renderWindow()->GetStereoTypeAsString()); // Marine, get viens du vtkrenderwindow
  widget.renderWindow()->StereoUpdate();

  widgetNative.renderWindow()->AddRenderer(renderer2);
  widgetNative.renderWindow()->SetWindowName(widgetNative.renderWindow()->GetStereoTypeAsString()); // Marine, get viens du vtkrenderwindow
  widgetNative.renderWindow()->StereoUpdate();
  //cout << "Type de render : " << widget.renderWindow()->GetStereoTypeAsString() << endl;
  //cout << "VTK version 9" << endl;
  renderWindow->Render();
  renderWindowNative->Render();
  
#else
  widget.GetRenderWindow()->AddRenderer(renderer);
  widget.GetRenderWindow()->SetWindowName(widget.GetRenderWindow()->GetStereoTypeAsString());
  widget.GetRenderWindow()->StereoUpdate();
  //cout << "Type de render : " << widget.GetRenderWindow()->GetStereoTypeAsString() << endl;
  //cout << "vtk autre version" << endl;
  renderWindow->Render();

#endif

  /*QSurfaceFormat format;
  format.setStereo(true);
  widget.setFormat(format);*/

  widgetNative.show();
  widget.show();

  app.exec();

  return EXIT_SUCCESS;
}
