#include <cs50.h>
#include <stdio.h>
#include <string.h>

int getFirst2Digits(long input)
{
    while (input >= 100)
    {
        input /= 10;
    }
    return input;
}

bool isValidLength(int length)
{
    return (length == 13 || length == 15 || length == 16);
}

int calculateChecksum(const char* cardNumber, int length)
{
    int sum = 0;

    // Process every second digit from the right
    for (int i = length - 2; i >= 0; i -= 2)
    {
        int digit = (cardNumber[i] - '0') * 2;
        sum += digit / 10 + digit % 10;
    }

    // Add the remaining digits
    for (int i = length - 1; i >= 0; i -= 2)
    {
        sum += cardNumber[i] - '0';
    }

    return sum;
}

int main(void)
{
    long cardNumber = get_long("Number: ");
    char cardStr[256];
    sprintf(cardStr, "%ld", cardNumber);
    int length = strlen(cardStr);

    if (!isValidLength(length) || calculateChecksum(cardStr, length) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    int firstTwoDigits = getFirst2Digits(cardNumber);

    if ((firstTwoDigits == 34 || firstTwoDigits == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if (firstTwoDigits >= 51 && firstTwoDigits <= 55 && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (firstTwoDigits / 10 == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
