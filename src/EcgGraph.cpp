#include "EcgGraph.h"
#include "EcgDataManager.h"

#include <qtgui/qpainter.h>
#include <qtgui/qpainterpath.h>
#include <qtgui/qevent.h>

#include <iostream>

EcgGraph::EcgGraph(QWidget *parent) : QWidget(parent), _startIndex(0), _pointNb(0), _maxPointNb(3000), _avgWindowSize(1)
{
    EcgDataManager::computeMinMax(_dataMin, _dataMax);
    
    connect(&_timer,SIGNAL(timeout()),this,SLOT(updateGraph()));
    _timer.start(2);
}

qreal EcgGraph::getAverageECGValue(int index)
{
    // Define range of value to consider
    int beginIndex = std::max(index - ((_avgWindowSize-1)/2), 0);
    int endIndex = std::min(index + ((_avgWindowSize-1)/2), static_cast<int>(EcgDataManager::_ecgData.size())-1);

    int sum = 0;
    for(int i=beginIndex; i<=endIndex ; ++i)
    {
        sum += EcgDataManager::_ecgData.at(i);
    }

    qreal average = static_cast<qreal>(sum) / static_cast<qreal>((endIndex-beginIndex+1));
    return average;
}

void EcgGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen(Qt::black, 0.5, Qt::SolidLine, Qt::RoundCap));

    if(_pointNb > 0)
    {
        // Define graph parameter following current size fo the widget and data content
        qreal xInterval = static_cast<float>(this->width()) / static_cast<float>(_maxPointNb - 1);
        qreal zeroYPos = this->height()/2.0f;
        qreal yInterval = (this->height()/2.0f) / std::max(std::abs(_dataMin), std::abs(_dataMax));

        QPainterPath path;
        qreal currentValue = getAverageECGValue(_startIndex);
        qreal xPos = 0;
        qreal yPos = zeroYPos + (currentValue * yInterval);
        path.moveTo(xPos,yPos);

        for(int i = _startIndex + 1 ; i<_startIndex + _pointNb - 1 ; ++i)
        {
            currentValue = getAverageECGValue(i);
            xPos += xInterval;
            yPos = zeroYPos + (currentValue * yInterval);
            path.lineTo(xPos,yPos);
        }

        painter.drawPath(path);
    }

    QWidget::paintEvent(event);
    painter.end();
}

void EcgGraph::playPause()
{
    if(_timer.isActive())
    {
        _timer.stop();
    }
    else
    {
        _timer.start(2);
    }
}

void EcgGraph::changeAverageWindow(int windowSize)
{
    _avgWindowSize = windowSize;
    this->update();
}

void EcgGraph::updateGraph()
{
    // If we don't yet display the max number of point, increment only the number of displayed point. Else increment the first index to display.
    if(_pointNb < _maxPointNb)
    {
        _pointNb++;
    }
    else if(_startIndex + _pointNb < EcgDataManager::_ecgData.size())
    {
        _startIndex++;
    }
    
    this->update();
}