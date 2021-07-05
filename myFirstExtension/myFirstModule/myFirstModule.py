import os
import unittest
import logging
import vtk, qt, ctk, slicer
from PythonQt5 import QtGui
from vtk.qt5.QVTKOpenGLWidget import QVTKOpenGLWidget
from slicer.ScriptedLoadableModule import *
from slicer.util import VTKObservationMixin

#
# mySecondModule
#

class mySecondModule(ScriptedLoadableModule):
  """Uses ScriptedLoadableModule base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def __init__(self, parent):
    ScriptedLoadableModule.__init__(self, parent)
    self.parent.title = "mySecondModule"  
    self.parent.categories = ["Test"]  
    self.parent.dependencies = []  
    self.parent.contributors = ["Marine CAMBA - CENIR Paris Brain Institute, Sara FERNANDEZ VIDAL - CENIR Paris Brain Institute"]  
    self.parent.helpText = """
This module allows user to display in QuadBuffer Stereo mode in Slicer 4.13 using VTK 9"""
    self.parent.acknowledgementText = """
This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc., Andras Lasso, PerkLab,
and Steve Pieper, Isomics, Inc. and was partially funded by NIH grant 3P41RR013218-12S1.
"""

#
# mySecondModuleWidget
#

class mySecondModuleWidget(ScriptedLoadableModuleWidget):    
  """Uses ScriptedLoadableModuleWidget base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def __init__(self, parent=None):
    """
    Called when the user opens the module the first time and the widget is initialized.
    """
    ScriptedLoadableModuleWidget.__init__(self, parent)
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
    uiWidget = slicer.util.loadUI(self.resourcePath('UI/mySecondModule.ui'))
    self.layout.addWidget(uiWidget)
    self.ui = slicer.util.childWidgetVariables(uiWidget)

    # Set scene in MRML widgets. Make sure that in Qt designer the top-level qMRMLWidget's
    # "mrmlSceneChanged(vtkMRMLScene*)" signal in is connected to each MRML widget's.
    uiWidget.setMRMLScene(slicer.mrmlScene)
    self.setupQuadBufferMode()

  def setupQuadBufferMode(self):

    layoutName = "QuadBuffered window"
    layoutLabel = "QB"
    layoutColor = [0.5, 0.5, 1.0]
    # ownerNode manages this view instead of the layout manager (it can be any node in the scene)
    self.viewOwnerNode = slicer.mrmlScene.AddNewNodeByClass("vtkMRMLScriptedModuleNode")

    self.viewLogic = slicer.vtkMRMLViewLogic()
    self.viewLogic.SetMRMLScene(slicer.mrmlScene)
    self.viewNode = self.viewLogic.AddViewNode(layoutName)
    self.viewNode.SetLayoutLabel(layoutLabel)
    self.viewNode.SetLayoutColor(layoutColor)
    self.viewNode.SetAndObserveParentLayoutNodeID(self.viewOwnerNode.GetID())    

    self.stereoWidget = QVTKOpenGLWidget()
    self.viewWidget = slicer.qMRMLThreeDWidget(self.stereoWidget) 
    # self.viewWidget.setFormat(self.setStrereo(True)) #passe au format stereo, voit si bonne forme pour le code
    self.viewWidget.setQuadBufferStereoSupportEnabled(1)

    self.renderWindowQuadBuffer = self.viewWidget.threeDView().renderWindow()
    self.renderWindowQuadBuffer.SetStereoCapableWindow(1)  #on off if the window is created in stereo capable mode, needs to be stereowidget
    #self.renderWindowQuadBuffer.SetStereoType(2) #1=crystaleyes, 2=red blue  >> seul ne se passe rien doit ajouter autre chose
    self.renderWindowQuadBuffer.SetStereoRender(1)  #on off for stereo rendering

    self.viewNode.SetStereoType(3) #active le mode stereo sur l'image + dans le menu déroulant, cad comme si clique moi sur le bouton, 3=quadbuffer
    self.viewWidget.setMRMLScene(slicer.mrmlScene)
    self.viewWidget.setMRMLViewNode(self.viewNode)
    self.viewWidget.resize(800, 800)

    
    #Modify render window
    # comme on créer la fenetre a partir de view widget surement pas besoin de ces 3 lignes :
    #self.viewWidget.setRenderWindow(self.renderWindowQuadBuffer)
    #self.renderWindowQuadBuffer.Render()
    
    self.ui.EnableQuadBufferButton.connect('clicked(bool)', self.showQuadBufferWidget)


  def showQuadBufferWidget(self):
    # self.renderWindowQuadBuffer.StereoUpdate() ici ou dans la fonction precedente fait crash l'appli
    self.viewWidget.show()
    # tests
    print(self.viewNode.GetStereoType()) #Not available as string only int
    print(self.renderWindowQuadBuffer.GetStereoTypeAsString())
  




