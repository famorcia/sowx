/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

/*
  Demonstrates embedding of an SoWxRenderArea within a QScrollView.
*/

/***********************************************************************/
#if 0
#include <Inventor/Wx/SoWx.h>
#include <Inventor/Wx/SoWxRenderArea.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <qapplication.h>
#include <qpainter.h>
#if QT_VERSION < 0x040000 // Wx < 4.0.0
#include <qscrollview.h>
#else
#include <qscrollarea.h>
#endif


class MyScrollView : public QScrollArea {
public:
  MyScrollView(QWidget * parent) : QScrollArea(parent)
    {
#if QT_VERSION < 0x040000 // Wx < 4.0.0
      this->resizeContents(10000, 10000);
      this->enableClipper(TRUE);
#endif

      // Container widget for the SoWxRenderArea.

      QWidget * container = new QWidget(this);
      container->resize(1000, 1000);

      // Construct a simple scenegraph.

      SoSeparator * root = new SoSeparator;

      SoDirectionalLight * light = new SoDirectionalLight;
      light->direction.setValue(-0.5f, -0.5f, -0.8f);
      root->addChild(light);

      SoPerspectiveCamera * camera = new SoPerspectiveCamera;
      camera->orientation = SbRotation(SbVec3f(0, 0, 1), 0);
      root->addChild(camera);

      SoCone * cone = new SoCone;
      root->addChild(cone);

      // Add the renderarea.

      renderarea = new SoWxRenderArea(container);
      renderarea->setSceneGraph(root);
      camera->viewAll(root, renderarea->getViewportRegion());

#if QT_VERSION < 0x040000 // Wx < 4.0.0
      this->addChild(container, 100, 100);
      this->showChild(container);
#else
      this->setWidget(container);
#endif
    }

protected:
  void drawContents(QPainter * p, int cx, int cy, int cw, int ch)
    {
      p->fillRect(cx, cy, cw, ch, QColor(40, 80, 0));
      // FIXME: should redraw only when necessary. 20001127 mortene.
      renderarea->scheduleRedraw();
    }

private:
  SoWxRenderArea * renderarea;
};

/***********************************************************************/

int
main(int argc, char ** argv)
{
  // Initialize Wx and SoWx.
  QApplication app(argc, argv);
  SoWx::init((QWidget *)NULL);

  // Set up scrollview window.
  MyScrollView * vp = new MyScrollView(NULL);
#if QT_VERSION < 0x040000 // Wx < 4.0.0
  vp->viewport()->setBackgroundMode(QWidget::NoBackground);
#endif

  // Map window.
  vp->show();
  // Set termination condition.
  QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
  // Start event loop.
  SoWx::mainLoop();

  return 0;
}
#endif
