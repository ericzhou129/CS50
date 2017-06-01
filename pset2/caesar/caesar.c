#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // use atoi to convert the key from string to integer
        int k = atoi(argv[1]);
        
        // get plaintext from the user
        printf("plaintext: ");
        string p = get_string();
        
        printf("ciphertext: ");
        for (int i=0; i < strlen(p); i++)
        {
            // if the character is a letter
            if (isalpha(p[i]))
            {
                // if character is uppercase
                if (isupper(p[i]))
                {
                    // shift to alphebetical index
                    char a = p[i] - 65;
                    // use modulus to apply wrap around to plain text character p and convert to ascii
                    a = (a + k) % 26 + 65;
                    printf("%c", a);
                    
                }
                
                // if letter is lowercase
                if (islower(p[i]))
                {
                    
                    // shift to alphebetical index
                    char a = p[i] - 97;
                    // use modulus to apply wrap around to plain text character p and convert to ascii
                    a = (a + k) % 26 + 97;
                    printf("%c", a);
                }
            }
            
            // if the character is punctuation or number
            else 
            {
                // print the character as is
                printf("%c", p[i]);
            }
        }
        printf("\n");
    
    return 0;
    }
    
    // if user does not put in the key as first input or argc != 2
    else
    {
        // print message and return 1
        printf("please input the key");
        return 1;
    }
}