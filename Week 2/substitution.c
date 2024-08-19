#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int used[26] = {0};
char arr[26];

/**
 * Checks if a given key is valid for substitution.
 * 
 * A valid key is a string consisting of alphabetic characters only, with no repeating characters.
 * 
 * @param key The key to be checked.
 * @return true if the key is valid, false otherwise.
 */
bool checkKey(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        char c = tolower(key[i]);

        // First check is valid or not
        if (isalpha(c) == 0)
        {
            printf("Is not alpha\n");
            return false;
        }

        // Then check if did repeat or not
        if (!isalpha(arr[i]) && used[c - 'a' - 1] == 0)
        {
            used[c - 'a' - 1] = 1;
            arr[i] = c;
        }
        else
        {
            printf("Already used %c %d %c %d\n", c, c - 'a' - 1, arr[i], used[c - 'a' - 1]);
            return false;
        }
    }

    return true;
}

/**
 * Encrypts a given plaintext string using a substitution cipher.
 * 
 * This function takes a string as input, iterates over each character, and replaces
 * alphabetic characters with their corresponding substitution values. Non-alphabetic
 * characters are left unchanged. The function modifies the input string in-place and
 * returns the encrypted string.
 * 
 * @param plaintext The input string to be encrypted.
 * @return The encrypted string.
 */
string cipher(string plaintext)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        bool uppercase = isupper(plaintext[i]);
        char c = tolower(plaintext[i]);
        int alpha = isalpha(c); // check if is symbol, lowercase or uppercase

        if (alpha == 0)
            continue; // symbol no replace

        plaintext[i] = arr[c - 'a'];

        if (uppercase)
            plaintext[i] = toupper(plaintext[i]);
    }

    // Encrypted but directly modified the parameter
    return plaintext;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) == 26 && checkKey(key))
    {
        string plaintext = get_string("plaintext: ");
        string ciphertext = cipher(plaintext);

        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        return 1;
    }
}
