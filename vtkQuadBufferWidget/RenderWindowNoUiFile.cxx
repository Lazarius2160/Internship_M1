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
  QSurfaceFormat format;
  format.setStereo(true);   
  //marine, ou en une ligne : QSurfaceFormat::setDefaultFormat(QVTKOpenGLStereoWidget::defaultFormat(1));
  // marine, test sans stereo widget mais marche pas:  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat(1));

  QVTKOpenGLStereoWidget widget;
  //QVTKOpenGLNativeWidget widget;
  widget.setFormat(format);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

#if VTK890
  //marine, need to set the stereo type before creating the render window
  renderWindow->SetStereoType(1);
  renderWindow->SetStereoCapableWindow(1);
  renderWindow->SetStereoRender(1);
  widget.setRenderWindow(renderWindow); 
#else 
  renderWindow->SetStereoType(1);
  renderWindow->SetStereoCapableWindow(1);
  renderWindow->SetStereoRender(1);
  widget.SetRenderWindow(renderWindow);
#endif

  widget.resize(600, 600);

  vtkNew<vtkSphereSource> sphereSource;

  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(sphereActor);
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());



#if VTK890
  widget.renderWindow()->AddRenderer(renderer);
  widget.renderWindow()->SetWindowName(widget.renderWindow()->GetStereoTypeAsString()); // Marine, get viens du vtkrenderwindow
  widget.renderWindow()->StereoUpdate();
  //cout << "Type de render : " << widget.renderWindow()->GetStereoTypeAsString() << endl;
  //cout << "VTK version 9" << endl;
  renderWindow->Render();
  
#else
  widget.GetRenderWindow()->AddRenderer(renderer);
  widget.GetRenderWindow()->SetWindowName(widget.GetRenderWindow()->GetStereoTypeAsString());
  widget.GetRenderWindow()->StereoUpdate();
  //cout << "Type de render : " << widget.GetRenderWindow()->GetStereoTypeAsString() << endl;
  //cout << "vtk autre version" << endl;
  renderWindow->Render();

#endif

  widget.show();
  app.exec();

  return EXIT_SUCCESS;
}
