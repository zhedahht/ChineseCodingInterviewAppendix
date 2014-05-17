/* 
 * Question Description:
 * (Question 69 in <Coding Intervies>) How do you find the median from a stream of numbers? 
 * The median of a set of numbers is the middle one when they are arranged in order. If the 
 * count of numbers is even, the median is defined as the average value of the two numbers in the middle. 
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

template<typename T> class DynamicArray
{
public:
    void Insert(T num)
    {
        if(((minHeap.size() + maxHeap.size()) & 1) == 0)
        {
            if(maxHeap.size() > 0 && num < maxHeap[0])
            {
                maxHeap.push_back(num);
                push_heap(maxHeap.begin(), maxHeap.end(), less<T>());

                num = maxHeap[0];

                pop_heap(maxHeap.begin(), maxHeap.end(), less<T>());
                maxHeap.pop_back();
            }

            minHeap.push_back(num);
            push_heap(minHeap.begin(), minHeap.end(), greater<T>());
        }
        else
        {
            if(minHeap.size() > 0 && minHeap[0] < num)
            {
                minHeap.push_back(num);
                push_heap(minHeap.begin(), minHeap.end(), greater<T>());

                num = minHeap[0];

                pop_heap(minHeap.begin(), minHeap.end(), greater<T>());
                minHeap.pop_back();
            }

            maxHeap.push_back(num);
            push_heap(maxHeap.begin(), maxHeap.end(), less<T>());
        }
    }

    T GetMedian()
    { 
        int size = minHeap.size() + maxHeap.size();
        if(size == 0)
            throw exception("No numbers are available");

        T median = 0;
        if((size & 1) == 1)
            median = minHeap[0];
        else
            median = (minHeap[0] + maxHeap[0]) / 2;

        return median;
    }

private:
    vector<T> minHeap;
    vector<T> maxHeap;
};

// ==================== Test Code ====================
void Test(char* testName, DynamicArray<double>& numbers, double expected)
{
    if(testName != NULL)
        printf("%s begins: ", testName);

    if(abs(numbers.GetMedian() - expected) < 0.0000001)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
    DynamicArray<double> numbers;

    printf("Test1 begins: ");
    try
    {
        numbers.GetMedian();
        printf("FAILED.\n");
    }
    catch(exception e)
    {
        printf("Passed.\n");
    }

    numbers.Insert(5);
    Test("Test2", numbers, 5);

    numbers.Insert(2);
    Test("Test3", numbers, 3.5);

    numbers.Insert(3);
    Test("Test4", numbers, 3);

    numbers.Insert(4);
    Test("Test6", numbers, 3.5);

    numbers.Insert(1);
    Test("Test5", numbers, 3);

    numbers.Insert(6);
    Test("Test7", numbers, 3.5);

    numbers.Insert(7);
    Test("Test8", numbers, 4);

    numbers.Insert(0);
    Test("Test9", numbers, 3.5);

    numbers.Insert(8);
    Test("Test10", numbers, 4);

	return 0;
}

