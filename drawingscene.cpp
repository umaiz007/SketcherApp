#include "drawingscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QUndoStack>
#include <QUndoCommand>

class DrawLineCommand : public QUndoCommand
{
public:
    DrawLineCommand(QGraphicsLineItem *line, QGraphicsScene *scene, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), line(line), scene(scene) {}

    void undo() override {
        scene->removeItem(line);
    }

    void redo() override {
        scene->addItem(line);
    }

private:
    QGraphicsLineItem *line;
    QGraphicsScene *scene;
};

DrawingScene::DrawingScene(QObject *parent)
    : QGraphicsScene(parent), drawing(false), currentLine(nullptr), undoStack(new QUndoStack(this))
{
    pen.setColor(Qt::red);
    pen.setWidth(2);
}

void DrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        startPoint = event->scenePos();
        currentLine = addLine(QLineF(startPoint, startPoint), pen);
    }
    QGraphicsScene::mousePressEvent(event);
}

void DrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawing && currentLine) {
        QLineF newLine(startPoint, event->scenePos());
        currentLine->setLine(newLine);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void DrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        if (currentLine) {
            undoStack->push(new DrawLineCommand(currentLine, this));
            currentLine = nullptr;
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}