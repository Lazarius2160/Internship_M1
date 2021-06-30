import os
import unittest
import logging
import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *
from slicer.util import VTKObservationMixin

#
# myFirstModule
#

class myFirstModule(ScriptedLoadableModule):
  """Uses ScriptedLoadableModule base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def __init__(self, parent):
    ScriptedLoadableModule.__init__(self, parent)
    self.parent.title = "myFirstModule"  # TODO: make this more human readable by adding spaces
    self.parent.categories = ["Examples"]  # TODO: set categories (folders where the module shows up in the module selector)
    self.parent.dependencies = []  # TODO: add here list of module names that this module requires
    self.parent.contributors = ["John Doe (AnyWare Corp.)"]  # TODO: replace with "Firstname Lastname (Organization)"
    # TODO: update with short description of the module and a link to online module documentation
    self.parent.helpText = """
This is an example of scripted loadable module bundled in an extension.
See more information in <a href="https://github.com/organization/projectname#myFirstModule">module documentation</a>.
"""
    # TODO: replace with organization, grant and thanks
    self.parent.acknowledgementText = """
This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc., Andras Lasso, PerkLab,
and Steve Pieper, Isomics, Inc. and was partially funded by NIH grant 3P41RR013218-12S1.
"""



class myFirstModuleWidget(ScriptedLoadableModuleWidget, VTKObservationMixin):
  """Uses ScriptedLoadableModuleWidget base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def __init__(self, parent=None):
    """
    Called when the user opens the module the first time and the widget is initialized.
    """
    ScriptedLoadableModuleWidget.__init__(self, parent)
    VTKObservationMixin.__init__(self)  # needed for parameter node observation
    self.logic = None
    self._parameterNode = None
    self._updatingGUIFromParameterNode = False

  def setup(self):
    """
    Called when the user opens the module the first time and the widget is initialized.
    """
    ScriptedLoadableModuleWidget.setup(self)

    # Load widget from .ui file (created by Qt Designer).
    # Additional widgets can be instantiated manually and added to self.layout.
    uiWidget = slicer.util.loadUI(self.resourcePath('UI/myFirstModule.ui'))
    self.layout.addWidget(uiWidget)
    self.ui = slicer.util.childWidgetVariables(uiWidget)

    # Set scene in MRML widgets. Make sure that in Qt designer the top-level qMRMLWidget's
    # "mrmlSceneChanged(vtkMRMLScene*)" signal in is connected to each MRML widget's.
    # "setMRMLScene(vtkMRMLScene*)" slot.
    uiWidget.setMRMLScene(slicer.mrmlScene)
    self.setupQuadBufferMode()

  def setupQuadBufferMode(self):
    # layout name is used to create and identify the underlying view node and  should be set to a value that is not used in any of the layouts owned by the layout manager
    layoutName = "QuadBuffered window"
    layoutLabel = "QB"
    layoutColor = [0.5, 0.5, 1.0]
    # ownerNode manages this view instead of the layout manager (it can be any node in the scene)
    self.viewOwnerNode = slicer.mrmlScene.AddNewNodeByClass("vtkMRMLScriptedModuleNode")

    # Create MRML node
    self.viewLogic = slicer.vtkMRMLViewLogic()
    self.viewLogic.SetMRMLScene(slicer.mrmlScene)
    self.viewNode = self.viewLogic.AddViewNode(layoutName)
    self.viewNode.SetLayoutLabel(layoutLabel)
    self.viewNode.SetLayoutColor(layoutColor)
    self.viewNode.SetAndObserveParentLayoutNodeID(self.viewOwnerNode.GetID())

    # Create widget
    self.viewWidget = slicer.qMRMLThreeDWidget()
    self.viewWidget.setMRMLScene(slicer.mrmlScene)
    self.viewWidget.setMRMLViewNode(self.viewNode)
    


    self.ui.EnableQuadBufferButton.connect('clicked(bool)', self.showQuadBufferWidget)


  def showQuadBufferWidget(self):
    self.viewWidget.show()

