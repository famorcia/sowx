/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

/*------------------------------------------------------------
 *  This is an example from the Inventor Mentor,
 *  chapter 16, example 3.
 *
 *  This example builds a render area in a window supplied by
 *  the application and a Material Editor in its own window.
 *  It attaches the editor to the material of an object.
 *-----------------------------------------------------------*/

#include <Inventor/SoDB.h>         
#include <Inventor/Xt/SoXt.h>         
#include <Inventor/Xt/SoXtMaterialEditor.h>
#include <Inventor/Xt/SoXtRenderArea.h>  
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>

int
main(int , char **argv)
{
   // Initialize Inventor and Xt
   Widget myWindow = SoXt::init(argv[0]);
   
   // Build the render area in the applications main window
   SoXtRenderArea *myRenderArea = new SoXtRenderArea(myWindow);
   myRenderArea->setSize(SbVec2s(200, 200));
   
   // Build the material editor in its own window
   SoXtMaterialEditor *myEditor = new SoXtMaterialEditor;
   
   // Create a scene graph
   SoSeparator *root = new SoSeparator;
   SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
   SoMaterial *myMaterial = new SoMaterial;
   
   root->ref();
   myCamera->position.setValue(0.212482, -0.881014, 2.5);
   myCamera->heightAngle = M_PI/4;
   root->addChild(myCamera);
   root->addChild(new SoDirectionalLight);
   root->addChild(myMaterial);

   // Read the geometry from a file and add to the scene
   SoInput myInput;
   SoInput::addDirectoryFirst("/home/fmorciano/CLionProjects/ivexamples/data");
   if (!myInput.openFile("dogDish.iv"))
      exit (1);
   SoSeparator *geomObject = SoDB::readAll(&myInput);
   if (geomObject == NULL)
      exit (1);
   root->addChild(geomObject);
   
   // Set the scene graph 
   myRenderArea->setSceneGraph(root);
   
   // Attach material editor to the material
   myEditor->attach(myMaterial);
   
   // Show the application window and the material editor
   myRenderArea->setTitle("Attach Editor");
   myRenderArea->show();
   SoXt::show(myWindow);
   myEditor->show();

   // Loop forever
   SoXt::mainLoop();

   // FIXME: deallocate resources. 20000412 mortene.

   return 0;
}
