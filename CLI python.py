layoutName = "Test3DView"  
layoutLabel = "T3"  
layoutColor = [1.0, 1.0, 0.0]  
viewOwnerNode = slicer.mrmlScene.AddNewNodeByClass("vtkMRMLScriptedModuleNode")  
viewLogic = slicer.vtkMRMLViewLogic() 
viewLogic.SetMRMLScene(slicer.mrmlScene)  
viewNode = viewLogic.AddViewNode(layoutName) 
viewNode.SetLayoutLabel(layoutLabel) 
viewNode.SetLayoutColor(layoutColor) 
viewNode.SetAndObserveParentLayoutNodeID(viewOwnerNode.GetID()) 
format=qt.QSurfaceFormat()
format.setOptions(qt.QSurfaceFormat().StereoBuffers) 
format.setStereo(True)
qt.QSurfaceFormat.setDefaultFormat(format)

viewWidget = slicer.qMRMLThreeDWidget() # test avec stereowidget
viewWidget.setQuadBufferStereoSupportEnabled(1)
viewWidget.setMRMLScene(slicer.mrmlScene)
viewWidget.setMRMLViewNode(viewNode) 

renderWin=viewWidget.threeDView().renderWindow(); 
renderWin.SetStereoType(1); 
renderWin.SetStereoCapableWindow(1); 
renderWin.SetStereoRender(1); 
renderWin.StereoUpdate(); 
renderWin.Render(); 

viewWidget.show(); 

