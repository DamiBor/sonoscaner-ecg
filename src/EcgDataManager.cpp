#include "EcgDataManager.h"
#include <fstream>
#include <iostream>
#include <qtcore/qdir.h>
#include <qtcore/qcollator.h>

std::vector<short> EcgDataManager::_ecgData;

void EcgDataManager::readFromFile(std::string fileName)
{
    std::cout << "EcgDataManager::readFromFile : reading file : " << fileName << std::endl;

    std::ifstream fs(fileName, std::ifstream::in);
    if(!fs.bad())
    {
        std::string readVal;
        while(std::getline(fs, readVal))
        {
            // There is no standard function to convert from string to short directly, so we have to cast from it to short. An improvement here could be to check for short boundaries to detect any invalid value.
            short value = 0;
            try
            {
                value = static_cast<short>(stoi(readVal));                
            }
            catch(std::invalid_argument& e)
            {
                std::cout << "Could not convert line to numeric value :" << readVal << std::endl;
                continue;
            }
            _ecgData.push_back(value);
        }
    }
    else
    {
        std::cout << "EcgDataManager::readFromFile : cannot open file : " << fileName << std::endl;
    }

    fs.close();
}

void EcgDataManager::readFromDirectory(std::string directoryPath)
{
    QDir ecgDir(directoryPath.c_str());
    if(ecgDir.exists())
    {
        // Get all file entries in given directory that match the ecg file name pattern. (possible improvement here : replace * with the regexp for "any number of digits" to be sure to get only correct files)
        QStringList ecgNameFilter;
        ecgNameFilter << "ecg-*.txt";
        QStringList ecgFileList = ecgDir.entryList(ecgNameFilter, QDir::Files);

        // Sort the file list with a numeric mode so they are correctly sorted by ID
        QCollator ecgFileSorter;
        ecgFileSorter.setNumericMode(true);
        std::sort(ecgFileList.begin(), ecgFileList.end(),ecgFileSorter);

        for(QStringList::const_iterator it = ecgFileList.constBegin() ; it != ecgFileList.constEnd() ; ++it)
        {
            EcgDataManager::readFromFile(directoryPath + "\\" + (*it).toStdString());
        }
    }
    else
    {
        std::cout << "EcgDataManager::readFromDirectory : given directory does not exist : " << directoryPath << std::endl;
    }
}