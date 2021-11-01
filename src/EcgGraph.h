#pragma once

#include <qtwidgets/qwidget.h>
#include <qtcore/qtimer.h>

/**
 * @brief A Widget drawing an ECG graph from a list of points
 * 
 */
class EcgGraph : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Ecg Graph object
     * @param parent Parent widget of the graph
     */
    explicit EcgGraph(QWidget *parent=0);

    /**
     * @brief Define the painting of the graph
     * @param event Event trigerring the painting
     */
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public slots:
    /**
     * @brief Slot to call to update the graph with a new point
     */
    void updateGraph();

    /**
     * @brief Play or pause the timer that update the graph.
     */
    void playPause();

    /**
     * @brief Change the size of the average window used to compute displayed values.
     * @param windowSize New average window size, in number of values.
     */
    void changeAverageWindow(int windowSize);

    /**
     * @brief Change the scrolling speed of the graph
     * @param speed Update frequency in Hz
     */
    void changeScrollingSpeed(int speed);

private:
    /**
     * @brief Get the average value of ECG vlaue at given index, following the current average window.
     * @details The returned value is the average of all value around given index in current window.
     * Ex : average window is 3, index is 10, returned value is the average of value at 9, 10 and 11.
     * @param index Index fo the value to average
     * @return qreal Average value to display on graph
     */
    qreal getAverageECGValue(int index);

    unsigned int _startIndex; /*! Index of the first point of the ECG data vector to draw on the graph. */
    unsigned int _pointNb; /*! Number of ECG point currently displayed on the graph. */
    unsigned int _maxPointNb; /*! Max number of point to display on the graph */
    int _dataMin, _dataMax; /*! Min and max values in teh ECG data vector. */

    int _avgWindowSize; /*! Size of the average window used to compute displayed values, in number of values. */

    QTimer _timer; /*! Timer to trig graph update at the requested frequency. */
    int _scrollingSpeed; /*! Scrolling speed of the graph (speed of the insertion of points in the graph), corresponding to the timer interval, in ms. */
};