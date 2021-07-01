# Intership Master 1
Official : Development of an HMI for the planning of deep brain stimulation.  
Reality : Creating a 3D slicer module to use it onto a zSpace device.  

## How to navigate through this repo:
Cmake : cmake files for building Slicer using QVTKOpenGLWidget (VTK 8) by default (rather than Native).  
Errors : just a mess, do not open.    
Screenshots : images for my internship report. 

**myFirstExtension** : a whole Slicer extension (with my module inside) where I changed only the .py file (scripted module) to show a 3D outside the actual layout, and a .ui file to show my widget. I now added the parameters/methods for the quadBuffer displays to change the type of the view to quadbuffer.  
**quadBufferDisplay** : include files for creating a loadable module to add the quad buffer widget to 3DSlicer, miss the CMake file, not finished because switched to scripted module.  
**vtkQuadBufferRenderWindow** : CMake + cxx file, very small app (no widget only render window), based on Cylinder example from [vtk example](https://kitware.github.io/vtk-examples/site/Cxx/GeometricObjects/CylinderExample/) to make a window render in quadbuffer mode using VTK and Qt only. Works in VTK 9 but can be switched to VTK 8.2 easily.  
**vtkQuadBufferWidget** : 
- Cmake + cxx file, use a widget (stereo) and render windo, based on RenderWindowNoUiFile from [vtk example](https://kitware.github.io/vtk-examples/site/Cxx/Qt/RenderWindowNoUiFile/) to create a widget which renders in quadbuffer mode. Use VTK 9, can use VTK 8.2 but beware of the type of the widget.  
- test is a cxx file used to test different widgets, render window and surface. It displays 2 widgets.  

CLI python.py: used to test out python command line into Slicer's python interactor.  
Project_NA_MIC... : first draft of my project web page for NA MIC Week.
WidgetNewLayout.cxx : **draft**, a mix of Slicer programming to create a 3D view outside the layout and having it display in quadbuffer mode using my previous VTK code.
