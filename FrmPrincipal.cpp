#include "FrmPrincipal.h"
#include "ui_FrmPrincipal.h"

//-----------------------------------------------------------------------------

FrmPrincipal::FrmPrincipal(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::FrmPrincipal)
{
   ui->setupUi(this);

   connect(ui->widgetGL, &WidgetGL::signalFpsPerSecond,
           this, &FrmPrincipal::slotFpsPerSecond);

   connect(ui->widgetGL, &WidgetGL::signalResize,
           this, &FrmPrincipal::slotResize);

}

//-----------------------------------------------------------------------------

FrmPrincipal::~FrmPrincipal()
{
   delete ui;
}

//-----------------------------------------------------------------------------

void FrmPrincipal::slotFpsPerSecond(int fps)
{
   QString text;
   text = text.sprintf("FPS: %d", fps);
   ui->lbFps->setText(text);
}

//-----------------------------------------------------------------------------

void FrmPrincipal::slotResize(int width, int height)
{
   QString text;
   text = text.sprintf("Size [width: %d, height: %d]", width, height);
   ui->lbSize->setText(text);
}

//-----------------------------------------------------------------------------
