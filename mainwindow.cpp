#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this)) // Initialize the scene
{
    ui->setupUi(this);
    
    // Set up the graphics scene in the QGraphicsView
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}
