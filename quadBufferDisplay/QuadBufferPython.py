import os
import unittest
import logging
import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *
from slicer.util import VTKObservationMixin

#
# QuadBufferPython
#

class QuadBufferPython(ScriptedLoadableModule):

  def __init__(self, parent):
    ScriptedLoadableModule.__init__(self, parent)
    self.parent.title = "Quad Buffer Python"  # TODO: make this more human readable by adding spaces
    self.parent.categories = ["Examples"]  # TODO: set categories (folders where the module shows up in the module selector)
    self.parent.contributors = ["Marine CAMBA (Institut du Cerveau et de la Moelle Epinière - Paris, ISIR Sorbonne Université - Paris), Sara FERNANDEZ VIDAL (Institut du Cerveau et de la Moelle Epinière - Paris)"]  # TODO: replace with "Firstname Lastname (Organization)"
    # TODO: update with short description of the module and a link to online module documentation
    self.parent.helpText = """
This is an example of scripted loadable module bundled in an extension."""
    # TODO: replace with organization, grant and thanks
    self.parent.acknowledgementText = """
This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc., Andras Lasso, PerkLab,
and Steve Pieper, Isomics, Inc. and was partially funded by NIH grant 3P41RR013218-12S1.
"""


#
# QuadBufferPythonWidget
#

class QuadBufferPythonWidget(ScriptedLoadableModuleWidget, VTKObservationMixin):
  """Uses ScriptedLoadableModuleWidget base class  """

  """____________define class attributes______________"""
  # ownerNode manages this view instead of the layout manager (it can be any node in the scene)
  viewOwnerNode = slicer.mrmlScene.AddNewNodeByClass("vtkMRMLScriptedModuleNode")
  viewLogic = slicer.vtkMRMLViewLogic()
  viewNode = viewLogic.AddViewNode("QuadBuffered window")
  viewWidget = slicer.qMRMLThreeDWidget()

  def __init__(self, parent=None):
    """
    Called when the user opens the module the first time and the widget is initialized.
    """
    ScriptedLoadableModuleWidget.__init__(self, parent)
    VTKObservationMixin.__init__(self)  # needed for parameter node observation > Mais en utilise pas!!!
    self.logic = None
    self._parameterNode = None
    self._updatingGUIFromParameterNode = False

  def setup(self):
    """
    Called when the user opens the module the first time and the widget is initialized.
    """
    ScriptedLoadableModuleWidget.setup(self)

    """___________________________________________________________________________________"""
    """_________________________LOAD WIDGET WITH QT DESIGNER______________________________"""
    # Load widget from .ui file (created by Qt Designer).
    # This widget correspond to the left pannel of Slicer. Not to the Stereo Widget created to render QuadBuffer stereo mode.
    # Additional widgets can be instantiated manually and added to self.layout. 
    uiWidget = slicer.util.loadUI(self.resourcePath('UI/QuadBufferPython.ui'))
    self.layout.addWidget(uiWidget)
    self.ui = slicer.util.childWidgetVariables(uiWidget)

    # Set scene in MRML widgets. Make sure that in Qt designer the top-level qMRMLWidget's
    # "mrmlSceneChanged(vtkMRMLScene*)" signal in is connected to each MRML widget's.
    # "setMRMLScene(vtkMRMLScene*)" slot.
    # Marine, on lie le bouton du widget à la scene MAIS APRES lui on le lie a quoi/qui? avec connect?
    uiWidget.setMRMLScene(slicer.mrmlScene)


    # Connections

    # These connections ensure that we update parameter node when scene is closed
    self.addObserver(slicer.mrmlScene, slicer.mrmlScene.StartCloseEvent, self.onSceneStartClose)
    self.addObserver(slicer.mrmlScene, slicer.mrmlScene.EndCloseEvent, self.onSceneEndClose)

    # These connections ensure that whenever user changes some settings on the GUI, that is saved in the MRML scene
    # (in the selected parameter node).
    self.ui.inputSelector.connect("currentNodeChanged(vtkMRMLNode*)", self.updateParameterNodeFromGUI)
    self.ui.outputSelector.connect("currentNodeChanged(vtkMRMLNode*)", self.updateParameterNodeFromGUI)
    self.ui.imageThresholdSliderWidget.connect("valueChanged(double)", self.updateParameterNodeFromGUI)
    self.ui.invertOutputCheckBox.connect("toggled(bool)", self.updateParameterNodeFromGUI)
    self.ui.invertedOutputSelector.connect("currentNodeChanged(vtkMRMLNode*)", self.updateParameterNodeFromGUI)

    #_______________Appelle methode pour setup le layout___________________________
    self.setupQuadBuffer()

    # Buttons
    # Clicking on the button in the UI activate the enableQuadBufferMode method
    # Needed here or done in the .ui file : pense que dans le UI c'est le lien entre les boutons
    # eux meme alors que connect lien bouton avec methode (pas besoin de ce truc de scene du coup?)

    self.ui.EnableQuadBufferButton.connect('clicked(bool)', self.enableQuadBufferMode)

    # Make sure parameter node is initialized (needed for module reload)
    self.initializeParameterNode()






"""______________pas de parameter node donc doit remplacer par les valeurs que l'on veut____________"""

  def cleanup(self):
    """
    Called when the application closes and the module widget is destroyed.
    """
    self.removeObservers()  
    
  def onSceneStartClose(self, caller, event):
    """
    Called just before the scene is closed.
    """
    # Parameter node will be reset, do not use it anymore
    self.setParameterNode(None)

  def onSceneEndClose(self, caller, event):
    """
    Called just after the scene is closed.
    """
    # If this module is shown while the scene is closed then recreate a new parameter node immediately
    if self.parent.isEntered:
      self.initializeParameterNode()

"""_____________________Process de creation du layout + add widget info___________________"""
  def setupQuadBuffer(self):
    """ pour l'instnt essaye juste afficher le widget 3d en dehors du layout classique avec le
    callback ici"""
    # layoutName = "QuadBuffered window">> put directly inside viewNode 
    layoutLabel = "QB"
    layoutColor = [0.0, 0.0, 1.0]
    # Create MRML node
    self.viewLogic.SetMRMLScene(slicer.mrmlScene)
    self.viewNode.SetLayoutLabel(layoutLabel)
    self.viewNode.SetLayoutColor(layoutColor)
    self.viewNode.SetAndObserveParentLayoutNodeID(self.viewOwnerNode.GetID())

    # Create widget
    self.viewWidget.setMRMLScene(slicer.mrmlScene)
    self.viewWidget.setMRMLViewNode(self.viewNode)

""" ____________________Callback de uand on a cliqué sur le bouton________________________"""
  def enableQuadBufferMode(self):
    """
    Show the widget when user clicks "EnableQuadBufferButton" button.
    Works like a callback method.
    """
    """ pour l'instnt essaye juste afficher le widget 3d en dehors du layout classique avec le
    callback ici"""
    self.viewWidget.show()

