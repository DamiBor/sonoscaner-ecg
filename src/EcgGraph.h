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

    /**
     * @brief Redifinition to the key press event handling to handle Play/Pause inputs
     * @param event Key pressed event to handle
     */
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

public slots:
    /**
     * @brief Slot to call to update the graph with a new point
     */
    void updateGraph();

private:
    unsigned int _startIndex; /*! Index of the first point of the ECG data vector to draw on the graph. */
    unsigned int _pointNb; /*! Number of ECG point currently displayed on the graph. */
    unsigned int _maxPointNb; /*! Max number of point to display on the graph */
    int _dataMin, _dataMax; /*! Min and max values in teh ECG data vector. */

    QTimer _timer; /*! Timer to trig graph update at the requested frequency. */
};