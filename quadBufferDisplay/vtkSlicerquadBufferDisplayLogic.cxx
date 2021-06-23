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

// quadBufferDisplay Logic includes
#include "vtkSlicerquadBufferDisplayLogic.h"

// MRML includes
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkIntArray.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>

// STD includes
#include <cassert>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerquadBufferDisplayLogic);

//----------------------------------------------------------------------------
vtkSlicerquadBufferDisplayLogic::vtkSlicerquadBufferDisplayLogic()
{
	//M default ou creer direct new layout + widget stereo?
}

//----------------------------------------------------------------------------
vtkSlicerquadBufferDisplayLogic::~vtkSlicerquadBufferDisplayLogic()
{
	//M cf au dessus
}

//----------------------------------------------------------------------------
void vtkSlicerquadBufferDisplayLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//---------------------------------------------------------------------------
/* M Doit savoir si doit avoir ca en internal ou si juste setMRMLScene suffit
void vtkSlicerquadBufferDisplayLogic::SetMRMLSceneInternal(vtkMRMLScene* newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}*/

//-----------------------------------------------------------------------------
void vtkSlicerquadBufferDisplayLogic::RegisterNodes()
{
    vtkMRMLScene* scene = this->GetMRMLScene();
    if (!scene)
    {
        vtkErrorMacro("vtkSlicerViewControllersLogic::RegisterNodes failed: invalid scene");
        return;
}

//---------------------------------------------------------------------------
void vtkSlicerquadBufferDisplayLogic::UpdateFromMRMLScene()
{
  // M ou comme j'ai fait sur mon main
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
/* M Soit fait facon donnee par view controller soit avec extension wizad mais plus long? 
void vtkSlicerquadBufferDisplayLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
}*/
vtkMRMLViewNode* vtkSlicerViewControllersLogic::GetDefaultThreeDViewNode()
{
    vtkMRMLScene* scene = this->GetMRMLScene();
    if (!scene)
    {
        vtkErrorMacro("vtkSlicerViewControllersLogic::GetDefaultThreeDViewNode failed: invalid scene");
        return nullptr;
    }
    vtkMRMLNode* defaultNode = scene->GetDefaultNodeByClass("vtkMRMLViewNode");
    if (!defaultNode)
    {
        defaultNode = scene->CreateNodeByClass("vtkMRMLViewNode");
        scene->AddDefaultNode(defaultNode);
        defaultNode->Delete(); // scene owns it now
    }
    return vtkMRMLViewNode::SafeDownCast(defaultNode);
}

//---------------------------------------------------------------------------
/* M Pareil que au dessus, garde juste le view node de la 3d?
void vtkSlicerquadBufferDisplayLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}*/
void vtkSlicerViewControllersLogic::ResetAllViewNodesToDefault()
{
    vtkMRMLScene* scene = this->GetMRMLScene();
    if (!scene)
    {
        vtkErrorMacro("vtkSlicerViewControllersLogic::ResetAllViewNodesToDefault failed: invalid scene");
        return;
    }
    scene->StartState(vtkMRMLScene::BatchProcessState);
    //vtkMRMLSliceNode* defaultSliceViewNode = GetDefaultSliceViewNode();
    //std::vector< vtkMRMLNode* > viewNodes;
    //scene->GetNodesByClass("vtkMRMLSliceNode", viewNodes);
    //for (std::vector< vtkMRMLNode* >::iterator it = viewNodes.begin(); it != viewNodes.end(); ++it)
    //{
    //    vtkMRMLSliceNode* sliceNode = vtkMRMLSliceNode::SafeDownCast(*it);
    //    if (!sliceNode)
    //    {
    //        continue;
    //    }
    //    sliceNode->Reset(defaultSliceViewNode);
    //    sliceNode->SetOrientationToDefault();
    //}
    //viewNodes.clear();
    vtkMRMLViewNode* defaultThreeDViewNode = GetDefaultThreeDViewNode();
    scene->GetNodesByClass("vtkMRMLViewNode", viewNodes);
    for (std::vector< vtkMRMLNode* >::iterator it = viewNodes.begin(); it != viewNodes.end(); ++it)
    {
        (*it)->Reset(defaultThreeDViewNode);
    }
    viewNodes.clear();
    /*vtkmrmlplotviewnode* defaultplotviewnode = getdefaultplotviewnode();
    scene->getnodesbyclass("vtkmrmlplotviewnode", viewnodes);
    for (std::vector< vtkmrmlnode* >::iterator it = viewnodes.begin(); it != viewnodes.end(); ++it)
    {
        (*it)->reset(defaultplotviewnode);
    }*/
    scene->EndState(vtkMRMLScene::BatchProcessState);
}

