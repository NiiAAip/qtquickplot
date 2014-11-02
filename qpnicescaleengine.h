#ifndef QPNICESCALEENGINE_H
#define QPNICESCALEENGINE_H

#include "qpscaleengine.h"

class QPNiceScaleEngine : public QPScaleEngine
{
    Q_OBJECT
public:
    explicit QPNiceScaleEngine(QQuickItem *parent = 0);

protected:
    void calculateMinMax(qreal &min, qreal &max);

};

#endif // QPNICESCALEENGINE_H
