#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void exitApp();
    void undoAction();
    void redoAction();
    void clearDrawing();

private:
    Ui::MainWindow *ui;
    DrawingScene *scene;  // No need to delete manually
};

#endif // MAINWINDOW_H