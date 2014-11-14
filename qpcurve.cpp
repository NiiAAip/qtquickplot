#include "qpcurve.h"

#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

QPCurve::QPCurve(QQuickItem *parent) :
    QPPlotItem(parent)
{
    setFlag(QQuickItem::ItemHasContents);
}

QPCurve::DataVector QPCurve::data() const
{
    return m_data;
}

QRectF QPCurve::coordinateBounds() const
{
    return m_bounds;
}

QColor QPCurve::color() const
{
    return m_color;
}

void QPCurve::setColor(const QColor &arg)
{
    if (m_color == arg)
        return;

    m_color = arg;
    emit colorChanged(arg);
    update();
}

void QPCurve::setData(const QVector<float> &data)
{
    m_data.clear();

    if (data.isEmpty()) {
        return;
    }

    m_data.resize(data.size());

    float ymin =  std::numeric_limits<float>::infinity();
    float ymax = -std::numeric_limits<float>::infinity();

    for (int i = 0; i < data.size(); ++i) {
        m_data[i] = QPointF(i, data[i]);
        if (data[i] < ymin) {
            ymin = data[i];
        }
        if (data[i] > ymax) {
            ymax = data[i];
        }
    }

    float xmin = 0;
    float xmax = data.size() - 1;

    m_bounds.setCoords(xmin, ymax, xmax, ymin);

    emit coordinateBoundsChanged(coordinateBounds());
    update();
}

void QPCurve::setData(const DataVector &data)
{
    m_data = data;

    if (data.isEmpty()) {
        return;
    }

    float ymin =  std::numeric_limits<float>::infinity();
    float ymax = -std::numeric_limits<float>::infinity();
    float xmin =  std::numeric_limits<float>::infinity();
    float xmax = -std::numeric_limits<float>::infinity();

    for (int i = 0; i < data.size(); ++i) {
        if (data[i].x() < xmin) {
            xmin = data[i].x();
        }
        if (data[i].x() > xmax) {
            xmax = data[i].x();
        }
        if (data[i].y() < ymin) {
            ymin = data[i].y();
        }
        if (data[i].y() > ymax) {
            ymax = data[i].y();
        }
    }

    m_bounds.setCoords(xmin, ymax, xmax, ymin);

    emit coordinateBoundsChanged(coordinateBounds());
    update();
}

QSGNode *QPCurve::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    QSGFlatColorMaterial *material = 0;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_data.size());
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINE_STRIP);
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
        geometry->allocate(m_data.size());
        material = static_cast<QSGFlatColorMaterial*>(node->material());
        if (material->color() != m_color) {
            material->setColor(m_color);
            node->markDirty(QSGNode::DirtyMaterial);
        }
    }

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    for (int i = 0; i < m_data.size(); ++i) {
        QPointF p = map(m_data[i]);
        vertices[i].set(p.x(), p.y());
    }

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
