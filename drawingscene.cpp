#include "drawingscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QUndoStack>
#include <QUndoCommand>

class DrawShapeCommand : public QUndoCommand {
public:
    DrawShapeCommand(QGraphicsItem *shape, QGraphicsScene *scene, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), shape(shape), scene(scene) {}

    void undo() override {
        scene->removeItem(shape);
    }

    void redo() override {
        scene->addItem(shape);
    }

private:
    QGraphicsItem *shape;
    QGraphicsScene *scene;
};

DrawingScene::DrawingScene(QObject *parent)
    : QGraphicsScene(parent), drawing(false), currentShape(nullptr), undoStack(new QUndoStack(this)) {
    pen.setColor(Qt::red);
    pen.setWidth(2);
}

void DrawingScene::setDrawingMode(DrawingMode mode) {
    currentMode = mode;
}

void DrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        startPoint = event->scenePos();
        
        if (currentMode == DrawingMode::Line) {
            currentShape = addLine(QLineF(startPoint, startPoint), pen);
        } else if (currentMode == DrawingMode::Circle) {
            currentShape = addEllipse(startPoint.x(), startPoint.y(), 1, 1, pen);
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void DrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (drawing && currentShape) {
        if (currentMode == DrawingMode::Line) {
            QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(currentShape);
            if (line) {
                line->setLine(QLineF(startPoint, event->scenePos()));
            }
        } else if (currentMode == DrawingMode::Circle) {
            QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem *>(currentShape);
            if (ellipse) {
                QRectF rect(startPoint, event->scenePos());
                ellipse->setRect(rect.normalized());
            }
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void DrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        if (currentShape) {
            undoStack->push(new DrawShapeCommand(currentShape, this));
            currentShape = nullptr;
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}