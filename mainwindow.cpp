#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new DrawingScene(this))
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
}

MainWindow::~MainWindow()
{
    delete ui; // No need to delete scene
}

// Menu Actions
void MainWindow::newFile()
{
    scene->clear();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Images (*.png *.xpm *.jpg);;All Files (*)");
    if (!fileName.isEmpty()) {
        QMessageBox::information(this, "Open File", "File Opened: " + fileName);
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "PNG Files (*.png);;JPEG Files (*.jpg);;All Files (*)");
    if (!fileName.isEmpty()) {
        QMessageBox::information(this, "Save File", "File Saved: " + fileName);
    }
}

void MainWindow::exitApp()
{
    close();
}

void MainWindow::undoAction()
{
    // Placeholder for actual undo functionality
    QMessageBox::information(this, "Undo", "Undo action triggered!");
}

void MainWindow::redoAction()
{
    // Placeholder for actual redo functionality
    QMessageBox::information(this, "Redo", "Redo action triggered!");
}

void MainWindow::clearDrawing()
{
    scene->clear();
}