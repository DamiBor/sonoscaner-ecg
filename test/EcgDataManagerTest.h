#pragma once

#include <EcgDataManager.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class EcgDataManagerUnitTest : public ::testing::Test
{
protected:
    /**
     * @brief Default constructor used by GoogleTest to construct a EcgDataManagerUnitTest instance for each test case. 
     */
    EcgDataManagerUnitTest() {}

    /**
     * @brief Destroys EcgDataManagerUnitTest objects.
     */
    virtual ~EcgDataManagerUnitTest() {}

    /**
     * @brief SetUp is executed each time a test case is run
     */
    virtual void SetUp() {}

    /**
     * @brief TearDown is executed each time a test case is finished, whatever the result.
     */
    virtual void TearDown() {}
};

/**
 * @brief Test for EcgDataManager::readFromDirectory function
 * @details What is tested : 
 * - data in file that are not named ecg-x.txt are ignored
 * - non numeric value in ecg file are ignored
 * - value are ordered by file ID, then in the same order as they are in the file
 */
TEST_F(EcgDataManagerUnitTest, readFromDirectory)
{
    // call readFromDirectory with test data directory
    EcgDataManager::readFromDirectory("./data");

    // Check data content after read
    std::vector<short> expectedData = {110, -1014, -1436, 178, 1264, -3000, 354, 3678, 3366, 879, -8956, 8451, 865, 822};
    EXPECT_EQ(expectedData, EcgDataManager::_ecgData);
}