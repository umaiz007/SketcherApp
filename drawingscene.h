#ifndef DRAWINGSCENE_H
#define DRAWINGSCENE_H

#include <QGraphicsScene>
#include <QPen>
#include <QUndoStack>
#include <QGraphicsItem>

class DrawingScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit DrawingScene(QObject *parent = nullptr);

    enum class DrawingMode {
        None,
        Line,
        Circle
    };

    void setDrawingMode(DrawingMode mode);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool drawing;
    QPointF startPoint;
    QGraphicsItem *currentShape;
    QPen pen;
    QUndoStack *undoStack;
    DrawingMode currentMode = DrawingMode::None;
};

#endif // DRAWINGSCENE_H