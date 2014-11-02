#include "vuaxes.h"
#include "vumeter.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

VUAxes::VUAxes(QQuickItem *parent) :
    QQuickItem(parent),
    m_min(std::numeric_limits<float>::infinity()),
    m_max(-std::numeric_limits<float>::infinity()),
    m_color(QColor(0, 0, 0, 64)),
    m_tickSpacing(0),
    m_maxTicks(10),
    m_numPoints(100),
    m_scrollingView(true)
{
    setFlag(QQuickItem::ItemHasContents);
}

void VUAxes::setColor(QColor arg)
{
    if (m_color != arg) {
        m_color = arg;
        emit colorChanged(arg);
        update();
    }
}

void VUAxes::setMaxTicks(int arg)
{
    if (m_maxTicks != arg) {
        m_maxTicks = arg;
        updateNiceScale();
        emit maxTicksChanged(arg);
    }
}

void VUAxes::setScrollingView(bool arg)
{
    if (m_scrollingView != arg) {
        m_scrollingView = arg;
        emit scrollingViewChanged(arg);
    }
}

QColor VUAxes::color() const
{
    return m_color;
}

void VUAxes::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    if (change == ItemChildAddedChange) {
        if (VUMeter *obj = qobject_cast<VUMeter*>(data.item)) {
            obj->property("anchors").value<QObject*>()->setProperty("fill", QVariant::fromValue<QObject*>(this));
            obj->setNumPoints(m_numPoints);
            connect(obj, &VUMeter::yBoundsChanged, this, &VUAxes::updateNiceScale);
            m_meters << obj;
        }
    }

    QQuickItem::itemChange(change, data);
}

QSGNode *VUAxes::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    QSGFlatColorMaterial *material = 0;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINES);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        material = new QSGFlatColorMaterial;
        material->setColor(m_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
        node->markDirty(QSGNode::DirtyMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        material = static_cast<QSGFlatColorMaterial*>(node->material());
        if (material->color() != m_color) {
            material->setColor(m_color);
            node->markDirty(QSGNode::DirtyMaterial);
        }
    }

    const QRectF bounds = boundingRect();
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    vertices[0].set(bounds.left(), bounds.top());
    vertices[1].set(bounds.left(), bounds.bottom());

    float yzero = yval(0);
    vertices[2].set(bounds.left(), yzero);
    vertices[3].set(bounds.right(), yzero);

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}

float VUAxes::niceNum(float range, bool round)
{
    float exponent = std::floor(std::log10(range));     /** exponent of range */
    float fraction = range / std::pow(10, exponent);    /** fractional part of range */
    float niceFraction;                                 /** nice, rounded fraction */

    if (round) {
        if (fraction < 1.5)
            niceFraction = 1;
        else if (fraction < 3)
            niceFraction = 2;
        else if (fraction < 7)
            niceFraction = 5;
        else
            niceFraction = 10;
    } else {
        if (fraction <= 1)
            niceFraction = 1;
        else if (fraction <= 2)
            niceFraction = 2;
        else if (fraction <= 5)
            niceFraction = 5;
        else
            niceFraction = 10;
    }

    return niceFraction * std::pow(10, exponent);
}

void VUAxes::updateNiceScale()
{
    float realMin = std::numeric_limits<float>::infinity();
    float realMax = -std::numeric_limits<float>::infinity();
    for (VUMeter *meter : m_meters) {
        realMin = std::min(meter->yMin(), realMin);
        realMax = std::max(meter->yMax(), realMax);
    }

    float range = niceNum(realMax - realMin, false);
    bool changed = false;

    float newSpacing;
    if ((newSpacing = niceNum(range / (m_maxTicks - 1), true)) != m_tickSpacing) {
        changed = true;
        m_tickSpacing = newSpacing;
    }
    float newMin;
    if ((newMin = std::floor(realMin / m_tickSpacing) * m_tickSpacing) != m_min) {
        changed = true;
        m_min = newMin;
    }
    float newMax;
    if ((newMax = std::ceil(realMax / m_tickSpacing) * m_tickSpacing) != m_max) {
        changed = true;
        m_max = newMax;
    }

    if (changed) {
        update();
        emit yAxisScalingChanged(m_min, m_max, m_tickSpacing);
    }
}

float VUAxes::yval(float y) const
{
    return (y - m_min) / (m_min - m_max) * boundingRect().height() + boundingRect().height();
}

