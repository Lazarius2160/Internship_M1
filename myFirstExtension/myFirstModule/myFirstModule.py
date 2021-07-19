import os
import unittest
import logging
import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *
from slicer.util import VTKObservationMixin


"""
brief : This module allows user to display in QuadBuffer (QB) Stereo mode in Slicer 4.13 using VTK 9.

Scripted module which, when one clicks on "Enable QuadBuffer" button, opens a new 3D view (outside the actual layout), to display in QuadBuffer stereo mode.
This module requires Slicer to be build from source using a QVTKOpenGLStereoWidget and not a QVTKOpenGLNativeWidget, as this widget does not support rendering
in QuadBuffer mode.

If the widget by default is ...StereoWidget, there may be no need to create a new view, we did so for testing; as for now, Slicer cannot use stereo widget by default.

Beware : QuadBuffer (QB) = Crystal eyes, theses mean the same stereo mode. This mode requires special hardware (such as the zSpace's graphic configuration, AMD Radeon Pro + 
120Hz screen).
"""


#________________________________________________________________________________________________


class mySecondModule(ScriptedLoadableModule):
  """Uses ScriptedLoadableModule base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def __init__(self, parent):
    ScriptedLoadableModule.__init__(self, parent)
    self.parent.title = "mySecondModule"  
    self.parent.categories = ["zSpace"]  
    self.parent.dependencies = []  
    self.parent.contributors = ["Marine CAMBA - CENIR Paris Brain Institute, Sara FERNANDEZ VIDAL - CENIR Paris Brain Institute, Sinan HALIYO - ISIR Sorbonne Université"]  
    self.parent.helpText = """
This module allows user to display in QuadBuffer Stereo mode in Slicer 4.13 using VTK 9"""
    self.parent.acknowledgementText = """
This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc., Andras Lasso, PerkLab,
and Steve Pieper, Isomics, Inc. and was partially funded by NIH grant 3P41RR013218-12S1.
"""


#________________________________________________________________________________________________


class mySecondModuleWidget(ScriptedLoadableModuleWidget):    


  def __init__(self, parent=None):
    """
    Called when the user opens the module the first time and the widget is initialized.
    """
    ScriptedLoadableModuleWidget.__init__(self, parent)
    self.logic = None
    self._parameterNode = None
    self._updatingGUIFromParameterNode = False

  def setup(self):

    ScriptedLoadableModuleWidget.setup(self)

    # Load widget from .ui file (created by Qt Designer).
    # Additional widgets can be instantiated manually and added to self.layout.
    uiWidget = slicer.util.loadUI(self.resourcePath('UI/mySecondModule.ui'))
    self.layout.addWidget(uiWidget)
    self.ui = slicer.util.childWidgetVariables(uiWidget)
    
    # The scene needs to be attached to the widget as Slicer is event-driven
    uiWidget.setMRMLScene(slicer.mrmlScene)
    self.setupQuadBufferMode()


#________________________________________________________________________________________________


  def setupQuadBufferMode(self):

    # Create a new layout to get another 3D view
    layoutName = "QuadBuffered window"
    layoutLabel = "QB"
    layoutColor = [0.5, 0.5, 1.0]

    # This node will manage the view instead of the layout node, so this view can mode freely and have it's own parameters.
    self.viewOwnerNode = slicer.mrmlScene.AddNewNodeByClass("vtkMRMLScriptedModuleNode")

    # Create the node and connect it to the scene/layout/owner node
    self.viewLogic = slicer.vtkMRMLViewLogic()
    self.viewLogic.SetMRMLScene(slicer.mrmlScene)
    self.viewNode = self.viewLogic.AddViewNode(layoutName)
    self.viewNode.SetLayoutLabel(layoutLabel)
    self.viewNode.SetLayoutColor(layoutColor)
    self.viewNode.SetAndObserveParentLayoutNodeID(self.viewOwnerNode.GetID())    

    # Create a new threeDWidget
    self.viewWidget = slicer.qMRMLThreeDWidget() 

    ## The surface needs to be stereo enabled to render the object in QB mode, if disabled, the window will accept stereo but won't render correctly
    #self.format = qt.QSurfaceFormat().setStereo(True)
    #self.viewWidget.setFormat(format) 

    ## Not only the widget and its surface must be stereo enabled, we also need to state which stereo we want and that the render window is capable of render in QB mode.
    self.renderWindowQuadBuffer = self.viewWidget.threeDView().renderWindow()
    #self.renderWindowQuadBuffer.SetStereoCapableWindow(1)  #Needs the window to be created in stereo capable mode
    #self.renderWindowQuadBuffer.SetStereoRender(1)  #Turned ON enables stereo rendering
    #self.renderWindowQuadBuffer.SetStereoType(2) #1=crystaleyes, 2=red blue, works on VTK but seems to be uneffective by itself on Slicer, may need to use line 106

    """If this turns to 3=quadbuffer, activate QB just as if one clicked on the button on the view controller
    (means QB is activated AND the correct mode is selected on the view controller)
    May not be needed if the renderWindowQuadBuffer does the work by itself line 101, to test out when Slicer accepts StereoWidget"""
    #self.viewNode.SetStereoType(3) 

    # Connect everything to the widget, make it a bit bigger than by default
    self.viewWidget.setMRMLScene(slicer.mrmlScene)
    self.viewWidget.setMRMLViewNode(self.viewNode)
    self.viewWidget.resize(800, 800)

    # Connects the methods of view the widget to the button, so whenever someone opens the widget and closes it using the classical cross, the widget can be re-opened
    self.ui.EnableQuadBufferButton.connect('clicked(bool)', self.showQuadBufferWidget)


  def showQuadBufferWidget(self):
    
    # Open the new widget when the button is clicked
    self.viewWidget.show()

    # Testings, print all data related to the render window and the node
    print("Render window")
    print(self.renderWindowQuadBuffer)
    #If "Stereo Capable Window Requested: Yes" that the widget by default is StereoWidget, also need to have "Stereo render: Yes" to know that QB works properly
    print("View node")
    print(self.viewNode)
  



