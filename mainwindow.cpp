#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingscene.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QUndoStack>
#include <QSvgGenerator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new DrawingScene(this)), undoStack(new QUndoStack(this)), pen(Qt::black) { // Initialize pen
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
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "JSON Files (*.json);;SVG Files (*.svg);;Image Files (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        if (fileName.endsWith(".json", Qt::CaseInsensitive)) {
            // Load JSON file
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::warning(this, "Open File", "Failed to open file.");
                return;
            }
            QByteArray data = file.readAll();
            file.close();

            QJsonDocument doc = QJsonDocument::fromJson(data);
            if (doc.isNull()) {
                QMessageBox::warning(this, "Open File", "Invalid JSON file.");
                return;
            }

            scene->clear();
            undoStack->clear();

            QJsonArray shapesArray = doc.array();
            for (const QJsonValue &value : shapesArray) {
                QJsonObject shapeObj = value.toObject();
                QString type = shapeObj["type"].toString();
                if (type == "line") {
                    QLineF line(QPointF(shapeObj["x1"].toDouble(), shapeObj["y1"].toDouble()),
                                QPointF(shapeObj["x2"].toDouble(), shapeObj["y2"].toDouble()));
                    scene->addLine(line, pen);
                } else if (type == "circle") {
                    QRectF rect(QPointF(shapeObj["x"].toDouble(), shapeObj["y"].toDouble()),
                                QSizeF(shapeObj["width"].toDouble(), shapeObj["height"].toDouble()));
                    scene->addEllipse(rect, pen);
                }
            }
            QMessageBox::information(this, "Open File", "File Opened: " + fileName);
        } else if (fileName.endsWith(".svg", Qt::CaseInsensitive)) {
            // Load SVG file
            QGraphicsSvgItem *svgItem = new QGraphicsSvgItem(fileName);
            if (svgItem->renderer()->isValid()) {
                scene->clear();
                undoStack->clear();
                scene->addItem(svgItem);
                QMessageBox::information(this, "Open File", "File Opened: " + fileName);
            } else {
                delete svgItem;
                QMessageBox::warning(this, "Open File", "Invalid SVG file.");
            }
        } else if (fileName.endsWith(".png", Qt::CaseInsensitive) || fileName.endsWith(".jpg", Qt::CaseInsensitive) || fileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
            // Load PNG or JPG file
            QImage image(fileName);
            if (image.isNull()) {
                QMessageBox::warning(this, "Open File", "Invalid image file.");
                return;
            }

            scene->clear();
            undoStack->clear();

            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            scene->addItem(pixmapItem);
            QMessageBox::information(this, "Open File", "File Opened: " + fileName);
        } else {
            QMessageBox::warning(this, "Open File", "Unsupported file format.");
        }
    }
}

void MainWindow::saveFile() {
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