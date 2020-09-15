#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

string luhn(long cc_num);
bool checksum(long cc_num);
int leftmost_digits(long num, int n);
int card_length(long num);

int main(void)
{
    // get and validate user input
    long card = get_long("Enter a Credit Card Number: ");
    // check card validity according to formula
    string validity = luhn(card);
    // print type of card if valid
    printf("%s", validity);

    return 0;
}

// check validty of card using luhns algorithm
// returns type of card or INVALID
string luhn(long cc_num)
{
    // default value is invalid
    string validity = "INVALID\n";
    // do checksum on card number
    bool check = checksum(cc_num);
    if (!check) 
    {
        return validity;
    } 
    // determine card type
    // get two leftmost digits and card length
    int leftmost = leftmost_digits(cc_num, 2);
    int card_len = card_length(cc_num);

    if (leftmost == 34 || leftmost == 37)
    {
        // AMEX uses length 15
        if (card_len == 15) 
        {
            validity = "AMEX\n";
        }
    }
    else if (leftmost > 50 && leftmost < 56)
    {
        // MC uses 16
        if (card_len == 16)
        {
            validity = "MASTERCARD\n";
        }
    }
    else if (leftmost >= 40 && leftmost <= 49)
    {   
        // VISA uses 13 or 16
        if (card_len == 13 || card_len == 16)
        {
            validity = "VISA\n";
        }
    }
    
    return validity;
}

// test cc numbers checksum for luhns
bool checksum(long cc_num) 
{
    bool result = false;
    int digit = 1;
    int sum = 0;
    int num;
   
    while (cc_num != 0)
    {
        num = cc_num % 10;
        if (digit % 2 == 0)
        {
            // multiply by 2 and add digits of num to sum
            num *= 2;
            do 
            {
                sum += num % 10;
                num /= 10;
            }
            while (num != 0);
        }
        else 
        {
            // digit is odd just add num to sum
            sum += num;
        }
        digit++;
        cc_num /= 10;
    }

    // check total modulo 10
    if (sum > 0 && sum % 10 == 0) 
    {
        result = true;
    }

    return result;
}

// given a long of unknown length, get the leftmost n digits
// had to use a SO solution for this math
// https://stackoverflow.com/a/15551989
int leftmost_digits(long num, int n)
{
    int log10 = (log(num) / log(10)) + 1;
    long divisor = pow(10, log10 - n);
    int res = num / divisor;

    return res;
}

// return length of a long
int card_length(long num)
{
    int count = 0;
    while (num != 0) 
    {
        num /= 10;    
        count++;
    }

    return count;
}
