#include "drawingscene.h"
#include <QGraphicsSceneMouseEvent>

DrawingScene::DrawingScene(QObject *parent)
    : QGraphicsScene(parent), drawing(false), currentLine(nullptr)
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
        currentLine = nullptr;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}