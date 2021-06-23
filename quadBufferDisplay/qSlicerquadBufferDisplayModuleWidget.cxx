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

// Qt includes
#include <QDebug>

// Slicer includes
#include "qSlicerquadBufferDisplayModuleWidget.h"
#include "ui_qSlicerquadBufferDisplayModuleWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerquadBufferDisplayModuleWidgetPrivate: 
    public Ui_qSlicerquadBufferDisplayModuleWidget
{
  Q_DECLARE_PUBLIC(qSlicerquadBufferDisplayModuleWidget);
  protected:
    // M need ce pointeur?? voir autre classes :
      qSlicerquadBufferDisplayModuleWidget* const q_ptr;
  public:
  // M besoin de eux 2??
    qSlicerquadBufferDisplayModuleWidgetPrivate(qSlicerquadBufferDisplayModuleWidgetPrivate& obj);
    virtual ~qSlicerquadBufferDisplayModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerquadBufferDisplayModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerquadBufferDisplayModuleWidgetPrivate::qSlicerquadBufferDisplayModuleWidgetPrivate(qSlicerquadBufferDisplayModuleWidget& object)
    : q_ptr(&object)
{
}

//-----------------------------------------------------------------------------
// qSlicerquadBufferDisplayModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerquadBufferDisplayModuleWidget::qSlicerquadBufferDisplayModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerquadBufferDisplayModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerquadBufferDisplayModuleWidget::~qSlicerquadBufferDisplayModuleWidget()
{
}
//marine, voir si defaut ou pas le destructeur

//-----------------------------------------------------------------------------
// M create a new controller (on and off quad buff), create new layout?
void
qSlicerViewControllersModuleWidgetPrivate::createController(vtkMRMLNode* n, qSlicerLayoutManager* layoutManager)
{
    Q_Q(qSlicerViewControllersModuleWidget);

    if (this->ControllerMap.find(n) != this->ControllerMap.end())
    {
        qDebug() << "qSlicerViewControllersModuleWidgetPrivate::createController - Node already added to module";
        return;
    }

    vtkMRMLViewNode* vn = vtkMRMLViewNode::SafeDownCast(n);
    if (vn)
    {
        // ThreeDViewController needs to now the ThreeDView
        qMRMLThreeDWidget* viewWidget = dynamic_cast<qMRMLThreeDWidget*>(layoutManager->viewWidget(vn));
        if (viewWidget)
        {
            qMRMLThreeDViewControllerWidget* widget =
                new qMRMLThreeDViewControllerWidget(this->ThreeDViewControllersCollapsibleButton);
            widget->setLayoutBehavior(qMRMLViewControllerBar::Panel);
            widget->setMRMLScene(q->mrmlScene());
            widget->setThreeDView(viewWidget->threeDView());
            // qMRMLThreeDViewControllerWidget needs to know the ViewLogic(s)
            widget->setViewLogic(viewWidget->threeDController()->viewLogic());
            // add the widget to the display
            this->ThreeDViewControllersLayout->addWidget(widget);
            barWidget = widget;
        }
    }
    // cache the widget. we'll clean this up on the NodeRemovedEvent
    this->ControllerMap[n] = barWidget;
}

//-----------------------------------------------------------------------------
void
qSlicerViewControllersModuleWidgetPrivate::removeController(vtkMRMLNode* n)
{
    // find the widget for the SliceNode
    ControllerMapType::iterator cit = this->ControllerMap.find(n);
    if (cit == this->ControllerMap.end())
    {
        qDebug() << "qSlicerViewControllersModuleWidgetPrivate::removeController - Node has no Controller managed by this module.";
        return;
    }

    // unpack the widget
    vtkMRMLViewNode* vn = vtkMRMLViewNode::SafeDownCast(n);
    if (vn)
    {
        ThreeDViewControllersLayout->removeWidget((*cit).second);
    }
    // delete the widget
    delete (*cit).second;

    // remove entry from the map
    this->ControllerMap.erase(cit);
}

//-----------------------------------------------------------------------------
void qSlicerquadBufferDisplayModuleWidget::setup()
{
  Q_D(qSlicerquadBufferDisplayModuleWidget);
  d->setupUi(this);
  // qui est la superclasse? 
  this->Superclass::setup();
  // creer le bouton pour activer quad buff, cad que active = ouvrir le widget en quad buff
//  d->CopyAction = new QAction(this);
//  d->CopyAction->setIcon(QIcon(":Icons/Medium/SlicerEditCopy.png"));
//  d->CopyAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
//  d->CopyAction->setShortcuts(QKeySequence::Copy);
//  d->CopyAction->setToolTip(tr("Copy"));
//   !!! un truc dans ce bail la
}

//----------------------------------------------------------------------------
// M how to set and link my scene, faire comme dans le CLI plus simple ou le view controllers??
void qSlicerViewControllersModuleWidget::setMRMLScene(vtkMRMLScene* newScene)
{
    Q_D(qSlicerViewControllersModuleWidget);

    vtkMRMLScene* oldScene = this->mrmlScene();

    this->Superclass::setMRMLScene(newScene);

    qSlicerApplication* app = qSlicerApplication::application();
    if (!app)
    {
        return;
    }
    qSlicerLayoutManager* layoutManager = app->layoutManager();
    if (!layoutManager)
    {
        return;
    }

    // Search the scene for the available view nodes and create a
    // Controller and connect it up
    std::vector<vtkMRMLNode*> sliceNodes;
    newScene->GetNodesByClass("vtkMRMLSliceNode", sliceNodes);
    for (std::vector< vtkMRMLNode* >::iterator sliceNodeIt = sliceNodes.begin(); sliceNodeIt != sliceNodes.end(); ++sliceNodeIt)
    {
        vtkMRMLSliceNode* snode = vtkMRMLSliceNode::SafeDownCast(*sliceNodeIt);
        if (snode)
        {
            d->createController(snode, layoutManager);
        }
    }

    std::vector<vtkMRMLNode*> threeDNodes;
    newScene->GetNodesByClass("vtkMRMLViewNode", threeDNodes);
    for (std::vector< vtkMRMLNode* >::iterator threeDNodeIt = threeDNodes.begin(); threeDNodeIt != threeDNodes.end(); ++threeDNodeIt)
    {
        vtkMRMLViewNode* vnode = vtkMRMLViewNode::SafeDownCast(*threeDNodeIt);
        if (vnode)
        {
            d->createController(vnode, layoutManager);
        }
    }

    std::vector<vtkMRMLNode*> plotNodes;
    newScene->GetNodesByClass("vtkMRMLPlotViewNode", plotNodes);
    for (std::vector< vtkMRMLNode* >::iterator plotNodeIt = plotNodes.begin(); plotNodeIt != plotNodes.end(); ++plotNodeIt)
    {
        vtkMRMLPlotViewNode* pnode = vtkMRMLPlotViewNode::SafeDownCast(*plotNodeIt);
        if (pnode)
        {
            d->createController(pnode, layoutManager);
        }
    }

    // Need to listen for any new slice or view nodes being added
    this->qvtkReconnect(oldScene, newScene, vtkMRMLScene::NodeAddedEvent,
        this, SLOT(onNodeAddedEvent(vtkObject*, vtkObject*)));

    // Need to listen for any slice or view nodes being removed
    this->qvtkReconnect(oldScene, newScene, vtkMRMLScene::NodeRemovedEvent,
        this, SLOT(onNodeRemovedEvent(vtkObject*, vtkObject*)));

    // Listen to changes in the Layout so we only show controllers for
    // the visible nodes
    QObject::connect(layoutManager, SIGNAL(layoutChanged(int)), this,
        SLOT(onLayoutChanged(int)));

}
