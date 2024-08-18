#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    int words = 1, letters = 0, sentences = 0;

    // Calculate words, letters, sentences
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];

        if (c == '.' || c == '?' || c == '!')
        {
            sentences++;
        }

        if (c == ' ')
        {
            words++;
        }

        if (isalpha(c))
        {
            letters++;
        }
    }

    // Rounding will cause a lot of error, so make sure to round only at last, therefore indexFloat
    // and indexRounded
    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;

    float indexFloat = 0.0588 * L - 0.296 * S - 15.8;
    int indexRounded = round(indexFloat);

    if (indexRounded > 16)
    {
        printf("Grade 16+");
    }
    else if (indexRounded < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %d", indexRounded);
    }

    printf("\n");
}
