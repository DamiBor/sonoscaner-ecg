#include "EcgDataManager.h"
#include "EcgGraph.h"

#include <iostream>
#include <vector>
#include <string>

#include <qtwidgets/qapplication.h>
#include <qtwidgets/qlabel.h>

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
    

    QLabel loadedData(QString("Loaded ECG data with ")+QString::number(EcgDataManager::_ecgData.size())+QString(" points"), nullptr, Qt::Dialog);
    loadedData.resize(200,60);
    loadedData.show();

    EcgGraph theGraph(nullptr);
    theGraph.resize(500, 500);
    theGraph.show();

    return a.exec();
}