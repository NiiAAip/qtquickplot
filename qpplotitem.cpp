#include "qpplotitem.h"
#include "qpscaleengine.h"

QPPlotItem::QPPlotItem(QQuickItem *parent) :
    QQuickItem(parent), m_xScaleEngine(0), m_yScaleEngine(0)
{
}

QPPlotItem::~QPPlotItem()
{
}

QRectF QPPlotItem::coordinateBounds() const
{
    return QRectF();
}

QPScaleEngine *QPPlotItem::yScaleEngine() const
{
    return m_yScaleEngine;
}

QPScaleEngine *QPPlotItem::xScaleEngine() const
{
    return m_xScaleEngine;
}

void QPPlotItem::setYScaleEngine(QPScaleEngine *arg)
{
    if (m_yScaleEngine == arg)
        return;

    m_yScaleEngine = arg;
    emit yScaleEngineChanged(arg);
}

void QPPlotItem::setXScaleEngine(QPScaleEngine *arg)
{
    if (m_xScaleEngine == arg)
        return;

    m_xScaleEngine = arg;
    emit xScaleEngineChanged(arg);
}

QPointF QPPlotItem::map(const QPointF &p)
{
    return map(p.x(), p.y());
}

QPointF QPPlotItem::map(qreal x, qreal y)
{
    return QPointF(xScaleEngine()->map(x, boundingRect()),
                   yScaleEngine()->map(y, boundingRect()));
}
