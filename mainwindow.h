#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>

class DrawingScene; // Forward declaration

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
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

private:
    Ui::MainWindow *ui;
    DrawingScene *scene; // Add this line
    QUndoStack *undoStack;
    enum class DrawingMode {
        None,
        Line
    };
    DrawingMode currentDrawingMode = DrawingMode::None;
};

#endif // MAINWINDOW_H