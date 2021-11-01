#include "EcgDataManager.h"
#include "EcgGraph.h"

#include <iostream>
#include <vector>
#include <string>

#include <qtwidgets/qapplication.h>
#include <qtwidgets/qlabel.h>
#include <qtwidgets/qspinbox.h>
#include <qtwidgets/qpushbutton.h>
#include <qtwidgets/QHBoxLayout>
#include <qtwidgets/QVBoxLayout>

int main( int argc, char **argv )
{
    // Handle command line option for ECG data path
    std::string datapath;
    for(int i = 0 ; i<argc ; i++)
    {
        if(strcmp(argv[i], "-data") == 0)
        {
            if(i+1 < argc)
            {
                datapath = argv[i+1];
                break;
            }
        }
    }

    if(datapath == "")
    {
        std::cout << "Use -data to specify ECG data path." << std::endl;
        return 0;
    }

    QApplication a( argc, argv );
    QLabel loadingLabel("Loading data, please wait...", nullptr, Qt::Dialog);
    loadingLabel.resize(200,60);
    loadingLabel.show();

    std::cout << "Loading ECG data in directory " << datapath << std::endl;
    EcgDataManager::readFromDirectory(datapath);
    
    loadingLabel.hide();

    // We define the window and its layout here, but it's a bit ugly
    QWidget mainWindow;
    mainWindow.resize(500, 500);
    QVBoxLayout layout(&mainWindow);

    // Button bar
    QHBoxLayout buttonBar;
    layout.addLayout(&buttonBar);
    
    QPushButton playPause("Play/Pause");
    buttonBar.addWidget(&playPause);

    QLabel averageLabel("Average window size: ");
    buttonBar.addWidget(&averageLabel);

    QSpinBox averageWindow;
    averageWindow.setMinimum(1);
    averageWindow.setValue(1);
    averageWindow.setSingleStep(2);
    buttonBar.addWidget(&averageWindow);
    
    // ECG graph
    EcgGraph theGraph;
    layout.addWidget(&theGraph);
    QObject::connect(&playPause,SIGNAL(pressed()),&theGraph,SLOT(playPause()));
    QObject::connect(&averageWindow,SIGNAL(valueChanged(int)),&theGraph,SLOT(changeAverageWindow(int)));

    mainWindow.show();

    return a.exec();
}