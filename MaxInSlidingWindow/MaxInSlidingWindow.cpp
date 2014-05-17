/* 
 * Question Description:
 * (Question 93 in <Coding Intervies>) Given an array of numbers and a sliding window size, 
 * how do you get the maximum numbers in all sliding windows?
*/

#include <stdio.h>
#include <vector>
#include <deque>

using namespace std;

vector<int> maxInWindows(const vector<int>& numbers, unsigned int windowSize)
{
    vector<int> maxInSlidingWindows;
    if(numbers.size() >= windowSize && windowSize >= 1)
    {
        deque<int> indices;

        for(unsigned int i = 0; i < windowSize; ++i)
        {
            while(!indices.empty() && numbers[i] >= numbers[indices.back()])
                indices.pop_back();

            indices.push_back(i);
        }

        for(unsigned int i = windowSize; i < numbers.size(); ++i)
        {
            maxInSlidingWindows.push_back(numbers[indices.front()]);

            while(!indices.empty() && numbers[i] >= numbers[indices.back()])
                indices.pop_back();
            if(!indices.empty() && indices.front() <= (int)(i - windowSize))
                indices.pop_front();

            indices.push_back(i);
        }
        maxInSlidingWindows.push_back(numbers[indices.front()]);
    }

    return maxInSlidingWindows;
}

// ==================== Test Code ====================
void Test(char* testName, const vector<int>& numbers, unsigned int windowSize, const vector<int>& expected)
{
    if(testName != NULL)
        printf("%s begins: ", testName);

    vector<int> result = maxInWindows(numbers, windowSize);

    vector<int>::const_iterator iterResult = result.begin();
    vector<int>::const_iterator iterExpected = expected.begin();
    while(iterResult < result.end() && iterExpected < expected.end())
    {
        if(*iterResult != *iterExpected)
            break;

        ++iterResult;
        ++iterExpected;
    }

    if(iterResult == result.end() && iterExpected == expected.end())
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

void Test1()
{
    int numbers[] = {2, 3, 4, 2, 6, 2, 5, 1};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    int expected[] = {4, 4, 6, 6, 6, 5};
    vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

    unsigned int windowSize = 3;

    Test("Test1", vecNumbers, windowSize, vecExpected);
}

void Test2()
{
    int numbers[] = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    int expected[] = {3, 3, 5, 5, 6, 7};
    vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

    unsigned int windowSize = 3;

    Test("Test2", vecNumbers, windowSize, vecExpected);
}

// increasingly sorted
void Test3()
{
    int numbers[] = {1, 3, 5, 7, 9, 11, 13, 15};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    int expected[] = {7, 9, 11, 13, 15};
    vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

    unsigned int windowSize = 4;

    Test("Test3", vecNumbers, windowSize, vecExpected);
}

// decreasingly sorted
void Test4()
{
    int numbers[] = {16, 14, 12, 10, 8, 6, 4};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    int expected[] = {16, 14, 12};
    vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

    unsigned int windowSize = 5;

    Test("Test4", vecNumbers, windowSize, vecExpected);
}

// size of sliding windows is 1
void Test5()
{
    int numbers[] = {10, 14, 12, 11};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    int expected[] = {10, 14, 12, 11};
    vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

    unsigned int windowSize = 1;

    Test("Test5", vecNumbers, windowSize, vecExpected);
}

// size of sliding windows is same as the array length
void Test6()
{
    int numbers[] = {10, 14, 12, 11};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    int expected[] = {14};
    vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

    unsigned int windowSize = 4;

    Test("Test6", vecNumbers, windowSize, vecExpected);
}

// size of sliding windows is 0
void Test7()
{
    int numbers[] = {10, 14, 12, 11};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    vector<int> vecExpected;

    unsigned int windowSize = 0;

    Test("Test7", vecNumbers, windowSize, vecExpected);
}

// size of sliding windows is greater than the array length
void Test8()
{
    int numbers[] = {10, 14, 12, 11};
    vector<int> vecNumbers(numbers, numbers + sizeof(numbers) / sizeof(int));

    vector<int> vecExpected;

    unsigned int windowSize = 5;

    Test("Test8", vecNumbers, windowSize, vecExpected);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();

	return 0;
}

