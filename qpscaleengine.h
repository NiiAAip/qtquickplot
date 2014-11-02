#ifndef QPSCALEENGINE_H
#define QPSCALEENGINE_H

#include <QQuickItem>

class QPPlotItem;

class QPScaleEngine : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal min READ min NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max NOTIFY maxChanged)
    Q_PROPERTY(QQmlListProperty<QPPlotItem> plotItems READ plotItemList)
    Q_PROPERTY(Qt::Axis axis READ axis WRITE axis NOTIFY axisChanged)

public:
    explicit QPScaleEngine(QQuickItem *parent = 0);

    qreal min() const;
    qreal max() const;

    QList<QPPlotItem*> plotItems() const;

    Qt::Axis axis() const;

    Q_INVOKABLE qreal map(qreal val, const QRectF &rect);
    Q_INVOKABLE qreal map(qreal val, QQuickItem *item);

signals:
    void minChanged(qreal arg);
    void maxChanged(qreal arg);
    void axisChanged(Qt::Axis arg);

public slots:
    void addPlotItem(QPPlotItem* item);
    void removePlotItem(QPPlotItem* item);
    void clearPlotItems();

    void updateScale();
    void axis(Qt::Axis arg);

protected:
    virtual void calculateMinMax(qreal &min, qreal &max);

private:
    QQmlListProperty<QPPlotItem> plotItemList();

    qreal m_min, m_max;
    QList<QPPlotItem*> m_plotItems;
    Qt::Axis m_axis;
};

#endif // QPSCALEENGINE_H
