#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controlador.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit  MainWindow(Controlador& controlador, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btMoviento_clicked();

    void on_btMoviento_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_btZoomMas_clicked();

    void on_btZoomMenos_clicked();

    void on_btCamaraDia_clicked();

    void on_btCamaraTermica_clicked();

private:
    Ui::MainWindow *ui;
    Controlador& controlador;

};
#endif // MAINWINDOW_H
