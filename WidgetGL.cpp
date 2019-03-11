#include "WidgetGL.h"

#include <QThread>

//-----------------------------------------------------------------------------

WidgetGL::WidgetGL(QWidget *parent) : QOpenGLWidget(parent),
   heigth(0),
   width(0),
   fpsCounter(0),
   fpsPerSecond(0),
   func(nullptr)
{

}

//-----------------------------------------------------------------------------

void WidgetGL::initializeGL()
{
   func = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_2_0>();

   //----------------------------------
   // Inicialização do OPENGL

   func->glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
   func->glShadeModel(GL_SMOOTH);
   func->glEnable(GL_DEPTH_TEST);
   func->glEnable(GL_BLEND);
   func->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   func->glEnable(GL_ALPHA_TEST);
   func->glAlphaFunc(GL_GEQUAL, static_cast<GLclampf>(0.1));

   //----------------------------------
   // Filtro Antialias

   func->glEnable(GL_LINE_SMOOTH);
   func->glEnable(GL_BLEND);
   func->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   func->glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

   //----------------------------------
   // Define Light's

   GLfloat lightAmbient[]  = {  1.00f,  1.00f,  1.00f,  1.00f };
   GLfloat lightDiffuse[]  = {  1.00f,  1.00f,  1.00f,  1.00f };
   GLfloat lightPosition[] = { -0.40f,  0.40f, -2.00f,  1.00f };

   func->glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);   // Setup The Ambient Light
   func->glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);   // Setup The Diffuse Light
   func->glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);  // Position The Light

   func->glDisable(GL_LIGHT0);
   func->glDisable(GL_LIGHTING);

   //----------------------------------
   // Counter FPS

   elapsedTimer.start();

   //----------------------------------
   // Load Textures ManPress_001

   tex01 = new QOpenGLTexture(QPixmap(":/images/ManPress_001.png").toImage().mirrored());
   tex01->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
   tex01->setMagnificationFilter(QOpenGLTexture::Linear);

   listTex01 = func->glGenLists(1);
   func->glNewList(listTex01, GL_COMPILE);
   {
      func->glEnable(GL_TEXTURE_2D);
      {
         tex01->bind();
         func->glBegin(GL_QUADS);
         {
            func->glTexCoord2i(0, 0); func->glVertex2f(-tex01->width()/2, -tex01->height()/2);
            func->glTexCoord2i(1, 0); func->glVertex2f( tex01->width()/2, -tex01->height()/2);
            func->glTexCoord2i(1, 1); func->glVertex2f( tex01->width()/2,  tex01->height()/2);
            func->glTexCoord2i(0, 1); func->glVertex2f(-tex01->width()/2,  tex01->height()/2);
         }
         func->glEnd();
      }
      func->glDisable(GL_TEXTURE_2D);
   }
   func->glEndList();

   //----------------------------------
   // Load Textures ManPress_002

   tex02 = new QOpenGLTexture(QPixmap(":/images/ManPress_002.png").toImage().mirrored());
   tex02->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
   tex02->setMagnificationFilter(QOpenGLTexture::Linear);

   listTex02 = func->glGenLists(1);
   func->glNewList(listTex02, GL_COMPILE);
   {
      func->glEnable(GL_TEXTURE_2D);
      {
         tex02->bind();
         func->glBegin(GL_QUADS);
         {
            func->glTexCoord2i(0, 0); func->glVertex2f(-tex02->width()/2, -tex02->height()/2);
            func->glTexCoord2i(1, 0); func->glVertex2f( tex02->width()/2, -tex02->height()/2);
            func->glTexCoord2i(1, 1); func->glVertex2f( tex02->width()/2,  tex02->height()/2);
            func->glTexCoord2i(0, 1); func->glVertex2f(-tex02->width()/2,  tex02->height()/2);
         }
         func->glEnd();
      }
      func->glDisable(GL_TEXTURE_2D);
   }
   func->glEndList();

}

//-----------------------------------------------------------------------------

void WidgetGL::resizeGL(int width, int height)
{
   this->width  = width;
   this->heigth = height;

   //----------------------------------
   // Projeção 2D
	  	  
   func->glViewport(0, 0, width, heigth);
   func->glMatrixMode(GL_PROJECTION);
   func->glLoadIdentity();

   func->glOrtho(0, width, 0, heigth, -20, +20);
   func->glMatrixMode(GL_MODELVIEW);
   func->glLoadIdentity();	  

   //----------------------------------

   emit signalResize(width, height);
}

//-----------------------------------------------------------------------------

void WidgetGL::paintGL()
{
   func->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   func->glLoadIdentity();

   //----------------------------------
   // Draw Texture 01

   func->glPushMatrix();
   {
      func->glTranslatef(150, 150, 0);
      func->glCallList(listTex01);
   }
   func->glPopMatrix();

   //----------------------------------
   // Draw Texture 02

   rot += 0.20f;

   func->glPushMatrix();
   {
      func->glTranslatef(150, 150, 1);
      func->glRotatef(-rot, 0.0, 0.0, 1.0);
      func->glCallList(listTex02);
   }
   func->glPopMatrix();

   //----------------------------------
   // Draw Square

   func->glPushMatrix();
   {
      func->glTranslatef(450, 150, 1);

      func->glBegin(GL_QUADS);
      {
         func->glColor3ub(255, 0, 0);
         func->glVertex3f(-50.0,  50.0, 1.0);

         func->glColor3ub(0, 255, 0);
         func->glVertex3f( 50.0,  50.0, 1.0);

         func->glColor3ub(0, 0, 255);
         func->glVertex3f( 50.0, -50.0, 1.0);

         func->glColor3ub(255, 0, 0);
         func->glVertex3f(-50.0, -50.0, 1.0);
      }
      func->glEnd();

      func->glColor3ub(255, 255, 255);
   }
   func->glPopMatrix();

   //----------------------------------
   // Counter FPS

   fpsCounter++;
   if ( elapsedTimer.elapsed() > 1000 )
   {
      elapsedTimer.restart();
      fpsPerSecond = fpsCounter;

      signalFpsPerSecond(fpsPerSecond);
      fpsCounter = 0;
   }

   //----------------------------------

   QThread::msleep(10);

   update();
}

//-----------------------------------------------------------------------------
