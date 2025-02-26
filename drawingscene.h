#ifndef DRAWINGSCENE_H
#define DRAWINGSCENE_H

#include <QGraphicsScene>
#include <QPen>
#include <QUndoStack>
#include <QGraphicsLineItem>

class DrawingScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DrawingScene(QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool drawing;
    QPointF startPoint;
    QGraphicsLineItem *currentLine;
    QPen pen;
    QUndoStack *undoStack;
};

#endif // DRAWINGSCENE_H