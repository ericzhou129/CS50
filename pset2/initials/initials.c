#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(void)
{ 
    //get name from user
    string name = get_string();
    
    // if the first index is a letter the print letter as upper case
    if(isalpha(name[0]))
    {
        printf( "%c", toupper(name[0]));
    }
    
    // while the string has not terminated
    int i = 0;
    while (name[i] != '\0')
    {
        // for any character that is not very first index of string, whose previous index is a space, whose next index is a char
        // and whose current index is a char
        if( i > 0 && name[i-1] == ' ' && isalpha(name[i+1]) && isalpha(name[i]))
        {
            // print the letter in upper case
            printf("%c", toupper(name[i]));
        }
        i++;
    }
    
    printf("\n");
}



