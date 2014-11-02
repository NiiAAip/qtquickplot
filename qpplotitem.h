#ifndef QPPLOTITEM_H
#define QPPLOTITEM_H

#include <QQuickItem>

class QPScaleEngine;

class QPPlotItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF coordinateBounds READ coordinateBounds NOTIFY coordinateBoundsChanged)
    Q_PROPERTY(QPScaleEngine* xScaleEngine READ xScaleEngine WRITE setXScaleEngine NOTIFY xScaleEngineChanged)
    Q_PROPERTY(QPScaleEngine* yScaleEngine READ yScaleEngine WRITE setYScaleEngine NOTIFY yScaleEngineChanged)

public:
    explicit QPPlotItem(QQuickItem *parent = 0);
    ~QPPlotItem();

    virtual QRectF coordinateBounds() const;

    QPScaleEngine* xScaleEngine() const;
    QPScaleEngine* yScaleEngine() const;

signals:
    void coordinateBoundsChanged(QRectF arg);
    void xScaleEngineChanged(QPScaleEngine* arg);
    void yScaleEngineChanged(QPScaleEngine *arg);

public slots:
    void setXScaleEngine(QPScaleEngine* arg);
    void setYScaleEngine(QPScaleEngine* arg);

protected:
    QPointF map(const QPointF &p);
    QPointF map(qreal x, qreal y);

private:
    QPScaleEngine *m_xScaleEngine, *m_yScaleEngine;
};

#endif // QPPLOTITEM_H
