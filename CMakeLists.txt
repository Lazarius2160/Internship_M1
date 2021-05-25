cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(renderWindowCrystal)
# Marine, pas besoin de plus de pkg car déjà tt dans le renderwindow.h pas de nouveaux .h ou include
# Change tt les noms de cylindres en renderWindowCrystal
find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkFiltersSources
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  QUIET
)

if (NOT VTK_FOUND)
  message("Skipping renderWindowCrystal: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(renderWindowCrystal MACOSX_BUNDLE renderWindowCrystal.cxx )
  target_link_libraries(renderWindowCrystal PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(renderWindowCrystal MACOSX_BUNDLE renderWindowCrystal.cxx )
  target_link_libraries(renderWindowCrystal PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS renderWindowCrystal
    MODULES ${VTK_LIBRARIES}
    )
endif ()