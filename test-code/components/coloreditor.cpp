#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotationXYZ.h>

#include <Inventor/Wx/SoWx.h>
#include <Inventor/Wx/SoWxColorEditor.h>
#include <Inventor/Wx/nodes/SoGuiColorEditor.h>
#include <Inventor/Wx/viewers/SoWxExaminerViewer.h>

static SoMaterial * material;

#define WANT_INTEGRATED 0

SoSeparator *
makescene(void)
{
  SoSeparator * root = new SoSeparator;
  root->addChild(material = new SoMaterial);
  root->addChild(new SoCube);
  return root;
}

int
main(int argc, char ** argv)
{
  wxWindow* w = SoWx::init(argc, argv, "SoWxColorEditor");
  SoWxExaminerViewer * viewer = new SoWxExaminerViewer(w);
  SoSeparator * root;
  viewer->setSceneGraph(root = makescene());
  viewer->show();

#if WANT_INTEGRATED
  // we want ColorEditor in scene
  SoSeparator * editorscene = new SoSeparator;
  SoTranslation * trans = new SoTranslation;
  trans->translation.setValue(SbVec3f(2.0f, 0.0f, 0.0f));
  SoRotationXYZ * rot = new SoRotationXYZ;
  SoMaterial * mat = new SoMaterial;
  mat->diffuseColor.setValue(0.8, 0.8, 0.8);
  rot->axis = SoRotationXYZ::Y;
  rot->angle = 0.5;
  editorscene->addChild(trans);
  editorscene->addChild(rot);
  editorscene->addChild(mat);
  SoGuiColorEditor * inscene = new SoGuiColorEditor;
  inscene->wysiwyg.setValue(TRUE);
  inscene->color.connectFrom(&(material->diffuseColor));
  inscene->color.getValue(); // update field
  material->diffuseColor.connectFrom(&(inscene->color));
  editorscene->addChild(inscene);
  root->insertChild(editorscene, 0);
#else
  SoWxColorEditor * editor = new SoWxColorEditor;
  editor->attach(&(material->diffuseColor));
  editor->show();
#endif

  SoWx::show(w);
  SoWx::mainLoop();
  return 0;
}

