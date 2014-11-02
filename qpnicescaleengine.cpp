#include "qpnicescaleengine.h"
#include "qpplotitem.h"

#include <QtDebug>

QPNiceScaleEngine::QPNiceScaleEngine(QQuickItem *parent) :
    QPScaleEngine(parent)
{
}

void QPNiceScaleEngine::calculateMinMax(qreal &min, qreal &max)
{
    min = std::numeric_limits<qreal>::infinity();
    max = -std::numeric_limits<qreal>::infinity();

    foreach (QPPlotItem *plotItem, plotItems()) {
        QRectF coordinateBounds = plotItem->coordinateBounds();
        if (axis() == Qt::YAxis) {
            if (coordinateBounds.top() > max) {
                max = coordinateBounds.top();
            }
            if (coordinateBounds.bottom() < min) {
                min = coordinateBounds.bottom();
            }
        } else if (axis() == Qt::XAxis) {
            if (coordinateBounds.left() < min) {
                min = coordinateBounds.left();
            }
            if (coordinateBounds.right() > max) {
                max = coordinateBounds.right();
            }
        }
    }
}
