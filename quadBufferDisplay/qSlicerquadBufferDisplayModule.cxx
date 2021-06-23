/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// Marine, include de base dans Slicer Loadable Module
// quadBufferDisplay Logic includes
#include <vtkSlicerquadBufferDisplayLogic.h>

// quadBufferDisplay includes
#include "qSlicerquadBufferDisplayModule.h"
#include "qSlicerquadBufferDisplayModuleWidget.h"

//Marine, mes includes pour le quadbuffer
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>    //Marine, ainsi on utilise renderwindow et pas le widget
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <array>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerquadBufferDisplayModulePrivate
{
public:
  // M du coup non comme c'est rpive ?
	qSlicerquadBufferDisplayModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerquadBufferDisplayModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerquadBufferDisplayModulePrivate::qSlicerquadBufferDisplayModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerquadBufferDisplayModule methods

//-----------------------------------------------------------------------------
qSlicerquadBufferDisplayModule::qSlicerquadBufferDisplayModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerquadBufferDisplayModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerquadBufferDisplayModule::~qSlicerquadBufferDisplayModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerquadBufferDisplayModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerquadBufferDisplayModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerquadBufferDisplayModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerquadBufferDisplayModule::icon() const
{
  return QIcon(":/Icons/quadBufferDisplay.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerquadBufferDisplayModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerquadBufferDisplayModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerquadBufferDisplayModule::setup()
{
  this->Superclass::setup(); 
  // en fonction de la superclass doit changer ca (stereo widget??)
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerquadBufferDisplayModule
::createWidgetRepresentation()
{
  return new qSlicerquadBufferDisplayModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerquadBufferDisplayModule::createLogic()
{
  return vtkSlicerquadBufferDisplayLogic::New();
}
