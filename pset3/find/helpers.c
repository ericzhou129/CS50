/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a bninary search algorithm
    
    // set left to the value of index 0
    int L = 0;
    // set right to the value of index n-1
    int R = n-1;
    
    // while true (loop)
    while (true)
    {
        // find middle by (right + left)/2
        int M = (R+L)/2;
        int value_M = values[M];
        
        // if value == middle
        if (value == value_M)
        {
            return true;
        }

        // if value is smaller than middle
        else if (value < value_M)
        {
            R = M - 1; 
        }

        // if value is bigger than middle
        else if (value > value_M)
        {
            L = M + 1;
        }

        // if left > right or right < left
        if (L > R || R < L)
        {
            return false;
        }
   
    }
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int i = 0;
    int max = 0;
    int j= 0;
    // find the max value within array
    for(i=0; i<n; i++)
    {
        if(max < values[i])
        {
            max = values[i];
        }
    }
    
    // Step 1: store the count of each number within array
    // make an count array of n values
    int count[max+1];
    
    for(i=0; i<=max; i++)
    {
        count[i] = 0;
    }

    // // error check
    // printf("count[max]");
    // for(i=0; i<=max; i++)
    // {
    //     printf("%i", count[i]);
    // }
    // printf("\n");

    
    // cycle through acount array, add 1 to the index for every number matched
    for (i = 0; i < n; i++)
    {
        j = values[i];
        count[j] = count[j] + 1;
        // printf("%i \n", count[j]);
    }
    
    // // error check
    // printf("step 1 count[]: ");
    // for(i=0; i<=max; i++)
    // {
    //     printf("%i", count[i]);
    // }
    // printf("\n");
    // printf("%i \n", count[max-1]);


    // Step 2: Modify count array to store sum of previous counts
    // for each array[i] value, if index i > than 0 and smaller than n, add the value of array[i-1] to array [i] value. 
    for(i=1; i<=max; i++)
    {
        count[i] = count[i-1] + count[i];
    }
    
    // // error check
    // printf("step 2 count[]: ");
    // for(i=0; i<=max; i++)
    // {
    //     printf("%i", count[i]);
    // }
    // printf("\n");

    // Step 3: Output each number in sequence and decrease its count by 1
    // int output_array[n];
    
    // // error check
    // printf("values[]");
    // for(i=0; i<n; i++)
    // {
    //     printf("%i", values[i]);
    // }
    // printf("\n");

    // // error check
    // printf("count[]");
    // for(i=0; i<=max; i++)
    // {
    //     printf("%i", count[i]);
    // }
    // printf("\n");

    int output[n];
    
    // printf("initial output[]");
    // for(i=0; i<=max; i++)
    // {
    // printf("%i", output[i]);
    // }
    // printf("\n");

    
    for(i=0; i<n; i++)
    {
        // while the index value is greater than the index before it
        // printf("count[i]: %i \n", count[i]);
        // printf("count[i-1]: %i \n", count[i-1]);
        int v = values[i];
        int c = count[v];
        output[c-1] = values[i];
        
        // output[count[values[i]]-1] = values[i];
        count[values[i]] --; 
        
        // while(count[i] > count[i-1])
        // {
        //     if(values[i] == 0)
        //     {
        //         // store in haystack array global variable
        //         values[i] = i;
        //         // decrease count of index by 1
        //         count[i] = count[i] - 1;
        //     }   
        // }
        // eprintf("output value: %i \n", output[count[values[i]]-1]);
    }

    // // error check
    // printf("output[]: ");
    // for(i=0; i<n; i++)
    // {
    //     printf("%i", output[i]);
    // }
    // printf("\n");


    // copy to values[]
    for(i=0; i<n; i++)
    {
        values[i] = output[i];
    }
    
    // // error check
    // for(i=0; i<n; i++)
    // {
    //     printf("%i", values[i]);
    // }
    
    // printf("\n");
    
    return;
}
