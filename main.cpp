#include <QApplication>
#include <QStyleFactory>
#include <QSurfaceFormat>

#include "FrmPrincipal.h"

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
   QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
   QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QApplication a(argc, argv);

   //----------------------------------
   // Define default theme

   a.setStyle(QStyleFactory::create("Fusion"));

   //----------------------------------
   // Define OpenGL settings

   QSurfaceFormat format;
   format.setDepthBufferSize(24);
   format.setStencilBufferSize(8);

   // OpenGL 2.1 (2006)
   format.setVersion(2, 1);
   format.setProfile(QSurfaceFormat::CoreProfile);

   format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
   format.setSwapInterval(1);

   QSurfaceFormat::setDefaultFormat(format);

   //----------------------------------

   FrmPrincipal w;
   w.show();

   //----------------------------------

   return a.exec();
}

//-----------------------------------------------------------------------------
