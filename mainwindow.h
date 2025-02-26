#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSvgRenderer>
#include <QPen> // Add this line

class DrawingScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void exitApp();
    void undoAction();
    void redoAction();
    void clearDrawing();
    void enableLineDrawing();
    void enableCircleDrawing();

private:
    Ui::MainWindow *ui;
    DrawingScene *scene;
    QUndoStack *undoStack;
    QPen pen; // Add this line
};

#endif // MAINWINDOW_H