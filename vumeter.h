#ifndef VUMETER_H
#define VUMETER_H

#include <QQuickItem>
#include <boost/circular_buffer.hpp>
#include <set>

#include "qpplotitem.h"

class VUMeter : public QPPlotItem
{
    Q_OBJECT
    Q_PROPERTY(int numPoints READ numPoints WRITE setNumPoints NOTIFY numPointsChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(float lastValue READ lastValue)

public:
    explicit VUMeter(QQuickItem *parent = 0);

    int numPoints() const;
    QColor color() const;

    QRectF coordinateBounds() const;

    float yMin() const { return m_orderedData.empty() ? 0 : *m_orderedData.begin(); }
    float yMax() const { return m_orderedData.empty() ? 0 : *m_orderedData.rbegin(); }

    float lastValue() const { return m_data.empty() ? 0 : m_data.back(); }

public slots:
    void newDataArrived(const QVector<float>& data);
    void appendDataPoint(qreal v);
    void setNumPoints(int arg);
    void setColor(const QColor& arg);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

signals:
    void numPointsChanged(int arg);
    void colorChanged(QColor arg);

private:
    int m_numPoints, m_numVertices;
    boost::circular_buffer<float> m_data;
    std::multiset<float> m_orderedData;
    QColor m_color;
};

#endif // VUMETER_H
