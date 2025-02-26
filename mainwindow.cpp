#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingscene.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QUndoStack>
#include <QUndoCommand>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new DrawingScene(this)) // Initialize scene
    , undoStack(new QUndoStack(this))
{
    ui->setupUi(this);

    // Set up the graphics scene in the QGraphicsView
    ui->graphicsView->setScene(scene);

    // Connect menu actions to functions
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitApp);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undoAction);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redoAction);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::clearDrawing);
    connect(ui->actionLine, &QAction::triggered, this, &MainWindow::enableLineDrawing);
}

MainWindow::~MainWindow()
{
    delete ui; // No need to delete scene
}

// Menu Actions
void MainWindow::newFile()
{
    scene->clear();
    undoStack->clear(); // Clear the undo stack
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Images (*.png *.xpm *.jpg);;All Files (*)");
    if (!fileName.isEmpty()) {
        // Load the image into the scene
        QPixmap pixmap(fileName);
        scene->clear();
        scene->addPixmap(pixmap);
        undoStack->clear(); // Clear the undo stack
        QMessageBox::information(this, "Open File", "File Opened: " + fileName);
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "PNG Files (*.png);;JPEG Files (*.jpg);;All Files (*)");
    if (!fileName.isEmpty()) {
        QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
        image.fill(Qt::transparent);

        QPainter painter(&image);
        scene->render(&painter);

        if (image.save(fileName)) {
            QMessageBox::information(this, "Save File", "File Saved: " + fileName);
        } else {
            QMessageBox::warning(this, "Save File", "Failed to save file.");
        }
    }
}

void MainWindow::exitApp()
{
    close();
}

void MainWindow::undoAction()
{
    undoStack->undo();
}

void MainWindow::redoAction()
{
    undoStack->redo();
}

void MainWindow::clearDrawing()
{
    scene->clear();
    undoStack->clear(); // Clear the undo stack
}

void MainWindow::enableLineDrawing()
{
    // Set the drawing mode to line
    currentDrawingMode = DrawingMode::Line;
}