#include <iostream>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

template <typename T>
vector<T> mergeSort(vector<T> input)
{
    vector<T> returnVec = input;
    if (input.size() > 2)
    {
        //splits the vectors in half
        int half = input.size()/2;
        vector<T> returnVecA;
        vector<T> returnVecB;

        for (int a = 0; a <= half; a++)
        {
            returnVecA.push_back(input[a]);
        }
        for (int a = half + 1; a <= input.size(); a++)
        {
            returnVecB.push_back(input[a]);
        }

        //recursive call
        returnVecA = mergeSort(returnVecA);
        returnVecB = mergeSort(returnVecB);

        //reconstruction
        returnVec = {};
        int aPos = 0;
        int bPos = 0;
        while (returnVecA.size() + returnVecB.size() < returnVec.size())
        {
            //if both exist and a is less than b
            if (returnVecA.size() > aPos && returnVecB.size() > bPos && returnVecA[aPos] < returnVecB[bPos])
            {
                returnVec.push_back(returnVecA[aPos]);
                aPos += 1;
            } else
            {
                //if both exist and b is less then a
                if (returnVecA.size() > aPos && returnVecB.size() > bPos && returnVecA[aPos] >= returnVecB[bPos])
                {
                    returnVec.push_back(returnVecB[bPos]);
                    bPos += 1;
                } else //if b does not exist
                {
                    if(returnVecA.size() > aPos && returnVecB.size() <= bPos)
                    {
                        returnVec.push_back(returnVecA[aPos]);
                        aPos += 1;
                    } else //if a does not exist
                    {
                        if (returnVecA.size() <= aPos && returnVecB.size() > bPos)
                        {
                            returnVec.push_back(returnVecB[bPos]);
                            bPos += 1;
                        }
                    }
                }
            }
        }

    } else
    {
        //reached the end of the splitting
        if (returnVec.size() == 2)
        {
            //shuffles the numbers around
            T hold = returnVec[0];
            if (returnVec[1]>returnVec[0])
            {
                returnVec[0] = returnVec[1];
                returnVec[1] = hold;
            }
        }
        return returnVec;
    }
    //returns the end product
    return returnVec;
}


//tests
//JR's
TEST(JR_MergeSort_Tests, WorksOne)
{
    vector<int> s;
    s.push_back(5);
    vector<int> t = {5};
    ASSERT_EQ(mergeSort(s),t);
}

TEST(JR_MergeSort_Tests, WorksThree)
{
    vector<int> s;
    s.push_back(5);
    s.push_back(4);
    s.push_back(3);
    vector<int> t = {3,4,5};
    ASSERT_EQ(mergeSort(s),t);
}

TEST(JR_MergeSort_Tests, WorksHundred)
{
    vector<int> s;
    vector<int> t;
    for (int i = 49; i >= 0; i--)
    {
        s.push_back(-i);
    }
    for (int i = 0; i < 50; i++)
    {
        s.push_back(i);
    }
    for (int i = 0; i < 50; i++)
    {
        s.push_back(i);
        s.push_back(-i);
    }
    ASSERT_EQ(mergeSort(s),t);
}

TEST(JR_MergeSort_Tests, IsEmptyWorks)
{
    vector<int> s;
    vector<int> t = {};
    ASSERT_EQ(mergeSort(s),t);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();

    return res;
}
