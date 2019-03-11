#ifndef WIDGETGL_H
#define WIDGETGL_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLTexture>

#include <QElapsedTimer>
#include <QList>

//-----------------------------------------------------------------------------

class WidgetGL : public QOpenGLWidget
{
   Q_OBJECT

public:
   explicit WidgetGL(QWidget *parent = nullptr);

private:
   QElapsedTimer elapsedTimer;

   int heigth;
   int width;

   int fpsCounter;
   int fpsPerSecond;

   QOpenGLFunctions_2_0 *func = nullptr;

   //--------------

   QOpenGLTexture *tex01;
   QOpenGLTexture *tex02;

   GLuint listTex01;
   GLuint listTex02;

   float rot = 0.0f;

protected:
   void initializeGL();
   void resizeGL(int width, int height);
   void paintGL();

signals:
   void signalFpsPerSecond(int fps);
   void signalResize(int width, int height);

};

//-----------------------------------------------------------------------------

#endif // WIDGETGL_H
