/*
* Question Description:
* (Question 12 in <Coding Intervies>) How do you check whether a string stands for a number or not?
* Numbers include positive and negative integers and floats. For example, strings "+100.", "5e2", "-.123", "3.1416", and "-1E-16"
* stand for numbers, but "12e", "1a3.14", "1.2.3", "+-5", and "12e+5.4" do not.
*/

#include <stdio.h>

bool scanDigits(char** string);
bool isExponential(char** string);

bool isNumeric(char* string)
{
   if (string == NULL)
      return false;

   if (*string == '+' || *string == '-')
      ++string;
   if (*string == '\0')
      return false;

   bool numeric = true;

   bool hasDigits = scanDigits(&string);
   if (*string != '\0')
   {
      // for floats
      if (*string == '.')
      {
         ++string;
         if (*string == 'e' || *string == 'E')
            return false;
         if (!hasDigits && *string == '\0')
            return false;

         scanDigits(&string);

         if (*string == 'e' || *string == 'E')
            numeric = isExponential(&string);
      }
      // for integers
      else if (*string == 'e' || *string == 'E')
         numeric = isExponential(&string);
      else
         numeric = false;
   }

   return numeric && *string == '\0';
}

bool scanDigits(char** string)
{
   char* pBefore = *string;

   while (**string != '\0' && **string >= '0' && **string <= '9')
      ++(*string);

   // return true when there are some digits in string
   return *string > pBefore;
}

bool isExponential(char** string)
{
   if (**string != 'e' && **string != 'E')
      return false;

   ++(*string);
   if (**string == '+' || **string == '-')
      ++(*string);

   if (**string == '\0')
      return false;

   scanDigits(string);
   return (**string == '\0') ? true : false;
}

// ==================== Test Code ====================

void Test(char* testName, char* string, bool expected)
{
   if (testName != NULL)
      printf("%s begins: ", testName);

   if (isNumeric(string) == expected)
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
   Test("Test10", "179.", true);

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
