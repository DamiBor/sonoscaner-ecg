#include "EcgDataManager.h"

#include <iostream>
#include <vector>
#include <string>

#include <qtwidgets/qapplication.h>
#include <qtwidgets/qpushbutton.h>

int main( int argc, char **argv )
{
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

    std::cout << "Loading ECG data in directory " << datapath << std::endl;
    EcgDataManager::readFromDirectory(datapath);
    
    QApplication a( argc, argv );

    QPushButton hello( QString::number(EcgDataManager::_ecgData.size()), 0 );
    hello.resize( 100, 30 );

    //a.setMainWidget( &hello );
    hello.show();
    return a.exec();
}