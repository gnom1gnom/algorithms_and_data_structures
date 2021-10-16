/*
 * Cracking the coding interview, edition 6
 * Problem 1.1
 * Write an algorithm to determine whether a string has unique characters or not
 * Can we do it without using additional data structures?
 */

#include <iostream>
#include <cstring>
#include <bitset>

using namespace std;

/*
 * Function hasUniqueChars1
 * Args - std::string
 * Output:: True if string has all characters which are unique
 *          False if string has at least one repeated char.
 * Assumption:: ASCII chars, 256 chars.
 */
bool hasUniqueChars1(std::string str)
{
    bool charcount[127]{0};
    for (std::string::size_type i = 0; i < str.size(); i++)
    {
        int8_t letterCode = str[i];
        // std::cout << str[i] << " is " << unsigned(letterCode) << std::endl;
        if (!charcount[letterCode])
            charcount[letterCode]++;
        else
            return false;
    }
    return true;
}

/*
 * Function hasUniqueChars2
 * Args - std::string
 * Output:: True if string has all characters which are unique
 *          False if string has at least one repeated char.
 * Assumption:: string only contains (a..z), 26 chars.
 */

bool hasUniqueChars2(std::string str)
{
    bool charcount[26]{0};
    for (std::string::size_type i = 0; i < str.size(); i++)
    {
        int8_t letterCode = str[i];
        // std::cout << str[i] << " is " << unsigned(letterCode) << std::endl;
        // a =97
        if (!charcount[letterCode - 97])
            charcount[letterCode - 97]++;
        else
            return false;
    }
    return true;
}

/*
 * Function hasUniqueChars1
 * Args - std::string
 * Output:: True if string has all characters which are unique
 *          False if string has at least one repeated char.
 * Assumption:: ASCII chars, 256 chars.
 */
bool hasUniqueChars3(std::string str)
{
    int len = str.length();
    int check[8]; // represents 256 bits.
    std::memset(check, 0, sizeof check);
    int idx, v, shift;

    for (int i = 0; i < len; ++i)
    {
        v = (int)str[i];
        idx = v / 32;   // identify which int bucket will represent this char
        shift = v % 32; // identify which bit in above int will represent the char
        if (check[idx] & (1 << shift))
        {
            return false;
        }
        check[idx] |= (1 << shift);
    }
    return true;
}

/*
 * Function hasUniqueChars2
 * Args - std::string
 * Output:: True if string has all characters which are unique
 *          False if string has at least one repeated char.
 * Assumption:: string only contains (a..z), 26 chars.
 */

bool hasUniqueChars4(std::string str)
{
    int check = 0;
    int len = str.length();
    cout << std::endl;
    for (int i = 0; i < len; ++i)
    {
        cout << str[i] << std::endl
             << "zyxwvutsrqponmlkjihgfedcba" << std::endl;
        int letterCode = (int)(str[i] - 'a');

        bitset<26> b_check(check);
        cout << b_check << std::endl;

        // przesuwamy w 00000000000000000000000001 jedynkę o tyle miejsc jaki jest asci cod litery
        bitset<26> b_shift = 1 << letterCode;
        cout << b_shift << std::endl;

        bitset<26> b_and = check & (1 << letterCode);
        cout << b_and << std::endl;

        // robimy bitowy AND - jak 1 się powtórzą na którymś miejscu wyjdzie liczba różna od 00000000000000000000000000
        if (check & (1 << letterCode))
        {
            return false;
        }
        // dopisujemy literę do checka, czyli insertujemy bit na odpowiadającej mu pozycji
        check |= (1 << letterCode);
    }
    return true;
}

int main()
{
    std::string word1("copyrightable");
    std::string word2("Dermatoglyphics!");
    std::string word3("abiogenesis");
    std::string word4("Centrobaric!");

    // a word with unique chars (a-z)
    std::cout << "Does " << word1 << " has unique chars :" << hasUniqueChars2(word1) << std::endl;

    // a word with unique ASCII chars
    std::cout << "Does " << word2 << " has unique chars :" << hasUniqueChars1(word2) << std::endl;

    // a word with repeated chars (a-z)
    std::cout << "Does " << word3 << " has unique chars :" << hasUniqueChars2(word3) << std::endl;

    // a word with repeated AsCII chars
    std::cout << "Does " << word4 << " has unique chars :" << hasUniqueChars1(word4) << std::endl;
    return 0;
}
