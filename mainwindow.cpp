#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingscene.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QUndoStack>
#include <QSvgGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new DrawingScene(this)), undoStack(new QUndoStack(this)) {
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitApp);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undoAction);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redoAction);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::clearDrawing);
    connect(ui->actionLine, &QAction::triggered, this, &MainWindow::enableLineDrawing);
    connect(ui->actionCircle, &QAction::triggered, this, &MainWindow::enableCircleDrawing);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::newFile() {
    scene->clear();
    undoStack->clear();
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "JSON Files (*.json);;SVG Files (*.svg)");
    if (!fileName.isEmpty()) {
        QMessageBox::information(this, "Open File", "File Opened: " + fileName);
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save File", "", "PNG Files (*.png);;JPEG Files (*.jpg);;SVG Files (*.svg);;All Files (*)");

    if (!fileName.isEmpty()) {
        if (fileName.endsWith(".svg", Qt::CaseInsensitive)) {
            // Save as SVG
            QSvgGenerator generator;
            generator.setFileName(fileName);
            generator.setSize(scene->sceneRect().size().toSize());
            generator.setViewBox(scene->sceneRect());

            QPainter painter(&generator);
            scene->render(&painter);
            QMessageBox::information(this, "Save File", "File Saved: " + fileName);
        }
        else {
            // Save as PNG or JPG
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
}

void MainWindow::exitApp() {
    close();
}

void MainWindow::undoAction() {
    undoStack->undo();
}

void MainWindow::redoAction() {
    undoStack->redo();
}

void MainWindow::clearDrawing() {
    scene->clear();
    undoStack->clear();
}

void MainWindow::enableLineDrawing() {
    scene->setDrawingMode(DrawingScene::DrawingMode::Line);
}

void MainWindow::enableCircleDrawing() {
    scene->setDrawingMode(DrawingScene::DrawingMode::Circle);
}