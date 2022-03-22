# Intership Master 1
Development of an HMI for the planning of deep brain stimulation: 
Creating a 3D slicer module to use it onto a zSpace device.  

## How to navigate through this repo:
Cmake : cmake files for building Slicer using QVTKOpenGLWidget (VTK 8) by default (rather than Native).  
**myFirstExtension** : plugin to make QuadBuffer option work on Slicer if we can enable QVTKOpenGLStereoWidget by default  
**quadBufferDisplay** : include files for creating a loadable module to add the quad buffer widget to 3DSlicer, miss the CMake file, not finished because switched to scripted module.  
**vtkQuadBufferRenderWindow** : CMake + cxx file, app based on Cylinder example from [vtk example](https://kitware.github.io/vtk-examples/site/Cxx/GeometricObjects/CylinderExample/) to make a window render in quadbuffer mode using VTK and Qt only. Works in VTK 9 but can be switched to VTK 8.2 easily.  
**vtkQuadBufferWidget** : Cmake + cxx file, use a widget (stereo) and render window, based on RenderWindowNoUiFile from [vtk example](https://kitware.github.io/vtk-examples/site/Cxx/Qt/RenderWindowNoUiFile/) to create a widget which renders in quadbuffer mode. Use VTK 9, can use VTK 8.2 but beware of the type of the widget.  
Tangible interface: Slicer plugin + arduino code to make the 3D view move based on the orientation of an IMU connected to an Arduino Uno.
Project_NA_MIC... : first draft of my [project web page for NA MIC Week](https://github.com/NA-MIC/ProjectWeek/tree/master/PW35_2021_Virtual/Projects/VRDisplayPluginForPyDBSUsingZspace).

