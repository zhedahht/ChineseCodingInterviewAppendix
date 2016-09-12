/*
* Question Description:
* (Question 12 in <Coding Intervies>) How do you check whether a string stands for a number or not?
* Numbers include positive and negative integers and floats. For example, strings "+100.", "5e2", "-.123", "3.1416", and "-1E-16"
* stand for numbers, but "12e", "1a3.14", "1.2.3", "+-5", and "12e+5.4" do not.
*/

#include <stdio.h>

bool scanUnsignedInteger(const char** str);
bool scanInteger(const char** str);

// the form of exponent is like A[.[B]][e|EC] or .B[e|EC]
// where A and C is an integer with or without sign, and B is an unsigned integer
bool isNumeric(const char* str)
{
    if (str == NULL)
        return false;

    bool numeric = scanInteger(&str);

    // for floats
    // you can have no integer part such as .123 means 0.123
    // in the meanwhile, you can have no decimal part such as 233. means 233.0
    // what's more, 233.666 is OK also.
    if (*str == '.') {
        ++str;
        numeric = scanUnsignedInteger(&str) || numeric;
    }

    // for exponent
    if (*str == 'e' || *str == 'E') {
        ++str;
        numeric = scanInteger(&str) && numeric;
    }

    return numeric && *str == '\0';
}

bool scanUnsignedInteger(const char** str)
{
    const char* pBefore = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9')
        ++(*str);

    // return true when there are some digits in str
    return *str > pBefore;
}

// an integer's form is like [+|-]B, where B is an unsigned integer
bool scanInteger(const char** str)
{
    if (**str == '+' || **str == '-')
        ++(*str);
    return scanUnsignedInteger(str);
}

// ==================== Test Code ====================

void Test(const char* testName, const char* str, bool expected)
{
    if (testName != NULL)
        printf("%s begins: ", testName);

    if (isNumeric(str) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}


int main(int argc, char* argv[])
{
    Test("Test1", "100", true);
    Test("Test2", "123.45e+6", true);
    Test("Test3", "+500", true);
    Test("Test4", "5e2", true);
    Test("Test5", "3.1416", true);
    Test("Test6", "600.", true);
    Test("Test7", "-.123", true);
    Test("Test8", "-1E-16", true);
    Test("Test9", "1.79769313486232E+308", true);

    printf("\n\n");

    Test("Test10", "12e", false);
    Test("Test11", "1a3.14", false);
    Test("Test12", "1+23", false);
    Test("Test13", "1.2.3", false);
    Test("Test14", "+-5", false);
    Test("Test15", "12e+5.4", false);
    Test("Test16", ".", false);
    Test("Test17", ".e1", false);
    Test("Test18", "+.", false);

    return 0;
}
