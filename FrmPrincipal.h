#ifndef FRMPRINCIPAL_H
#define FRMPRINCIPAL_H

#include <QMainWindow>

//-----------------------------------------------------------------------------

namespace Ui {
class FrmPrincipal;
}

class FrmPrincipal : public QMainWindow
{
   Q_OBJECT

public:
   explicit FrmPrincipal(QWidget *parent = nullptr);
   ~FrmPrincipal();

private:
   Ui::FrmPrincipal *ui;

private slots:
   void slotFpsPerSecond(int fps);
   void slotResize(int width, int height);

};

//-----------------------------------------------------------------------------

#endif // FRMPRINCIPAL_H
