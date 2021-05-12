# stage_m1
Code pour le stage à l'ICM / ISIR, developpement d'une IHM pour la stimulation cérébrale profonde.

### Liens a ajouter one note:  
https://discourse.slicer.org/t/slicer-4-10-summary-highlights-and-changelog/4610
https://www.techiedelight.com/clone-specific-tag-with-git/#:~:text=git%20clone,-You%20can%20also&text=It%20has%20%E2%80%93branch%20option%2C%20which,.&text=If%20you%20only%20need%20the,branches%20in%20the%20cloned%20repository.


### Errors
## When launching Pv
Generic Warning: In C:\pv\pv\VTK\Rendering\OpenGL2\vtkOpenGLState.cxx, line 234
Error in cache state for GL_DRAW_BUFFER got 1027 expected1029

Generic Warning: In C:\pv\pv\VTK\Rendering\OpenGL2\vtkOpenGLState.cxx, line 274
at stack loc
 at vtksys::SystemInformation::RunMemoryCheck
 at vtksys::SystemInformation::GetProgramStack
 at vtkOpenGLState::CheckState
 at vtkOpenGLState::vtkglGetBooleanv
 at vtkOpenGLState::GLState::GLState
 at vtkOpenGLRenderWindow::BlitDisplayFramebuffer
 at QVTKRenderWindowAdapter::QVTKRenderWindowAdapter
 at QVTKRenderWindowAdapter::blit
 at QVTKRenderWindowAdapter::blitRightEye
 at QVTKOpenGLWindow::paintGL
 at QPaintDeviceWindowPrivate::paint
 at QPaintDeviceWindow::exposeEvent
 at QWindow::event
 at QVTKOpenGLWindow::event
 at QApplicationPrivate::notify_helper
 at QApplication::notify
 at QCoreApplication::notifyInternal2
 at QGuiApplicationPrivate::processExposeEvent
 at QWindowSystemInterface::sendWindowSystemEvents
 at QWindowSystemInterface::flushWindowSystemEvents
 at QWindowSystemInterface::flushWindowSystemEvents
 at QWindowSystemInterface::flushWindowSystemEvents
 at QWindowSystemInterface::flushWindowSystemEvents
 at CallWindowProcW
 at CallWindowProcW
 at glPushClientAttrib
 at CallWindowProcW
 at DispatchMessageW
 at IsWindowVisible
 at KiUserCallbackDispatcher
 at NtUserDispatchMessage
 at DispatchMessageW
 at QEventDispatcherWin32::processEvents
 at qt_plugin_query_metadata
 at QEventLoop::exec
 at QCoreApplication::exec
 at QCoreApplication::exec
 at QCoreApplication::exec
 at QCoreApplication::exec
 at BaseThreadInitThunk
 at RtlUserThreadStart

## When openning a zspace view (try to relaunch laptop completly)
Generic Warning: In C:\pv\pv\VTK\Rendering\OpenGL2\vtkOpenGLState.cxx, line 234
Error in cache state for GL_DRAW_BUFFER got 1029 expected1027



