/* 
 * Question Description:
 * (Question 33 in <Coding Intervies>) Please implement a function that gets the minimal number of coins 
 * with values v1, v2, …, vn, to make change for an amount of money with value t. There are an infinite 
 * number of coins for each value vi. For example, the minimum number of coins to make change for 15 out 
 * of a set of coins with values 1, 3, 9, 10 is 3. We can choose two coins with value 3 and a coin with 
 * value 9. The number of coins for other choices should be greater than 3
*/

#include <vector>
#include <stdio.h>

using namespace std;

int GetMinCount(int total, const vector<int>& coins)
{
    vector<int> counts(total + 1);
    counts[0] = 0;

    const int MAX = 0x7FFFFFFF;
    int length = coins.size();

    for (int i = 1; i <= total; ++i)
    {
        int count = MAX;
        for (int j = 0; j < length; ++j)
        {
            if (i - coins[j] >= 0 && count > counts[i - coins[j]])
                count = counts[i - coins[j]];
        }

        if (count < MAX)
            counts[i] = count + 1;
        else
            counts[i] = MAX;
    }

    return counts[total];
}

// ============================ test code ============================
static void Test(char* testName, int total, const vector<int>& coins, int expected)
{
    printf("%s begins: ", testName);

    if (GetMinCount(total, coins) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

static void Test1()
{
    int coins[] = { 1, 5, 10, 20, 25 };
    int total = 40;
    int expected = 2;

    Test("test1", total, vector<int>(coins, coins + sizeof(coins) / sizeof(int)), expected);
}

static void Test2()
{
    int coins[] = { 1, 3, 9, 10 };
    int total = 15;
    int expected = 3;

    Test("test2", total, vector<int>(coins, coins + sizeof(coins) / sizeof(int)), expected);
}

static void Test3()
{
    int coins[] = { 1, 2, 5, 21, 25 };
    int total = 63;
    int expected = 3;

    Test("test3", total, vector<int>(coins, coins + sizeof(coins) / sizeof(int)), expected);
}

// Impossible to make changes
static void Test4()
{
    int coins[] = { 2, 4, 8, 16 };
    int total = 63;
    int expected = 0x7FFFFFFF;

    Test("test4", total, vector<int>(coins, coins + sizeof(coins) / sizeof(int)), expected);
}

// Total value is in the array for coins
static void Test5()
{
    int coins[] = { 1, 3, 9, 10 };
    int total = 9;
    int expected = 1;

    Test("test5", total, vector<int>(coins, coins + sizeof(coins) / sizeof(int)), expected);
}

void main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
}
