# Intership Master 1
Development of an HMI for the planning of deep brain stimulation.
Creating a 3D slicer module to use it onto a zSpace device.  

### How to navigate through this repo:
Errors : just a mess, do not open  
vtkQuadBufferRenderWindow : used the Cylinder example from [vtk example](https://kitware.github.io/vtk-examples/site/Cxx/GeometricObjects/CylinderExample/) to make a window render in quadbuffer mode
vtkQuadBufferWidget : used the RenderWindowNoUiFile from [vtk example](https://kitware.github.io/vtk-examples/site/Cxx/Qt/RenderWindowNoUiFile/) to create a widget which renders in quadbuffer mode
quadBufferDisplay : adding the widget to 3DSlicer  
WidgetNewLayout.cxx : currently trying to create a 3D view outside the layout on slicer and having it display in quadbuffer mode
