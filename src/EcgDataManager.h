#pragma once

#include <string>
#include <vector>


/**
 * @brief This class manage the ECG data read from files on disk
 * @details This class allows to read ECG data as signed integer values from multiple files.
 * All values are stored in a vector.
 * The class is able to read all files in a given directory which name fit the format "ecg-X.txt", X being the numerical ID allowing to read data in the right order.
 */
class EcgDataManager
{
public:
    /**
     * @brief Read ecg data from a file and store it into the vector _ecgData.
     * @details All lines are expected to contain one numerical value between -32768 and 32767 (range for a short). Non numerical line are ignored. Values are inserted in the vector in reading order.
     * @param fileName Name of the file to read, with full path
     */
    static void readFromFile(std::string fileName);

    /**
     * @brief Read ecg data from all data files in given directory and store it into the vector _ecgData.
     * @details Call readFromFile on each file in given directory which name match the format "ecg-X.txt", X being the numerical ID allowing to read data in the right order.
     * The function will process from ecg-0.txt to ecg-n.txt.
     * @param directoryPath The full path of the directory to load data from.
     */
    static void readFromDirectory(std::string directoryPath);

    static std::vector<short> _ecgData; /*! Vector containing all ECG values in chronological ordered  */
    
};