/* QuadBuffer using a render window (not qvtkstereowidget!) add a render window interactor
Only in VTK, later in Slicer
Use the examples in VTK examples cxx hello world with a cylinder
*/


#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>    //Marine, ainsi on utilise renderwindow et pas le widget
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkOpenGLRenderWindow.h> //Marine, a voir si besoin de ces fonctions

#include <array>

int main(int, char* [])
{
    vtkNew<vtkNamedColors> colors;

    // Set the background color.
    std::array<unsigned char, 4> bkg{ {26, 51, 102, 255} };
    colors->SetColor("BkgColor", bkg.data());

    // This creates a polygonal cylinder model with eight circumferential facets
    // (i.e, in practice an octagonal prism).
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes are
    // defined.
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it around the X and Y axes.
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(
        colors->GetColor4d("Tomato").GetData());
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    // The renderer generates the image
    // which is then displayed on the render window.
    // It can be thought of as a scene to which the actor is added
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(cylinderActor);
    renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    // Zoom in a little by accessing the camera and invoking its "Zoom" method.
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.5);

    // The render window is the actual GUI window
    // that appears on the computer screen
    vtkNew<vtkRenderWindow> renderWindow;    
    renderWindow->SetStereoType(1);    //Marine, c'est cette fonction qu'il fqut utiliser elle est dans vtkRenderWindow.cxx et non celle ci SetStereoTypeToCrystalEyes aui est dans le header
    renderWindow->SetStereoCapableWindow(1);     //Marine, 1 = crystal eyes
    renderWindow->SetStereoRender(1);     //Marine,  1 = crystal eyes
    renderWindow->SetSize(300, 300);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName(renderWindow->GetStereoTypeAsString());
    renderWindow->StereoUpdate(); // Marine, besoin d'une update? Si oui où?

    //Marine, pour savoir quel type de stereo on utilise
    cout << "Type de render : " << renderWindow->GetStereoTypeAsString()<< endl;

    // The render window interactor captures mouse events
    // and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // This starts the event loop and as a side effect causes an initial render.
     
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}