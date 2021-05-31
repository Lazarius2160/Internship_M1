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

#include <QSurfaceFormat>
#include <QVTKOpenGLStereoWidget.h>

int main(int argc, char** argv)
{
  // Needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat format;
  format.setStereo(true); 

  QApplication app(argc, argv);

  QVTKOpenGLStereoWidget widget;

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

#if VTK890
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
  widget.renderWindow()->SetWindowName(widget.renderWindow()->GetStereoTypeAsString());
  widget.renderWindow()->StereoUpdate();
  cout << "Type de render : " << widget.renderWindow()->GetStereoTypeAsString() << endl;
  cout << "VTK version 8.9" << endl;
  renderWindow->Render();
  
#else
  widget.GetRenderWindow()->AddRenderer(renderer);
  widget.GetRenderWindow()->SetWindowName(widget.GetRenderWindow()->GetStereoTypeAsString());
  widget.GetRenderWindow()->StereoUpdate();
  cout << "Type de render : " << widget.GetRenderWindow()->GetStereoTypeAsString() << endl;
  cout << "vtk autre version" << endl;
  renderWindow->Render();

#endif

  widget.show();

  app.exec();

  return EXIT_SUCCESS;
}
