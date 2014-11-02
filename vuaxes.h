#ifndef VUAXES_H
#define VUAXES_H

#include <QQuickItem>

class VUMeter;

class VUAxes : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(float yMin READ yMin NOTIFY yAxisScalingChanged)
    Q_PROPERTY(float yMax READ yMax NOTIFY yAxisScalingChanged)
    Q_PROPERTY(float tickSpacing READ tickSpacing NOTIFY yAxisScalingChanged)
    Q_PROPERTY(int maxTicks READ maxTicks WRITE setMaxTicks NOTIFY maxTicksChanged)

public:
    explicit VUAxes(QQuickItem *parent = 0);

    QColor color() const;
    float yMin() const { return m_min; }
    float yMax() const { return m_max; }

    float tickSpacing() const { return m_tickSpacing; }
    int maxTicks() const { return m_maxTicks; }

protected:
    void itemChange(ItemChange change, const ItemChangeData& data);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    float niceNum(float range, bool round);
    float yval(float y) const;

signals:
    void colorChanged(QColor arg);
    void yAxisScalingChanged(float min, float max, float tickSpacing);
    void scrollingViewChanged(bool arg);

public slots:
    void setColor(QColor arg);
    void setMaxTicks(int arg);
    void updateNiceScale();

private:
    QList<VUMeter*> m_meters;
    float m_min, m_max;
    QColor m_color;
    float m_tickSpacing;
    int m_maxTicks;
    int m_numPoints;
    bool m_scrollingView;
};

#endif // VUAXES_H
