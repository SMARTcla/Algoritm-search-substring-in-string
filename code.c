#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
void first_step(int d[], char substring[])
{
    int tmp = 1;
    int size = strlen(substring);
    for (int i = size - 2; i > -1; i--)
    {
        d[i] = tmp;
        for (int j = size - 2; j > i; j--)
        {
            if (substring[i] == substring[j])
            {
                d[i] = d[j];
                break;
            }
        }
        tmp++;
    }
}
int second_step(int d[], char substring[], char string[])
{
    int size = strlen(substring), tmp = 0;
    d[size - 1] = size;
    for (int i = size - 2; i > -1; i--)
    {
        if (substring[size - 1] == substring[i])
        {
            d[size - 1] = d[i];
            break;
        }
    }
    int size_string = strlen(string), temp = 0, t = 0;
    for (int i = size - 1; i < size_string; tmp++)
    {
        int tp = i;
        for (int j = size - 1; j >= 0; j--)
        {
            if (string[tp] == substring[j])
            {
                t++;
            }
            if (string[tp] != substring[j])
            {
                for (int k = size - 1; k >= 0; k--)
                {
                    if (string[tp] == substring[k])
                    {
                        i += d[k];
                        temp = 1;
                        break;
                    }
                }
                if (temp == 0)
                    i += size;
                temp = 0;
                break;
            }
            tp--;
        }
        if (t == size)
            return i - size + 1;
        else
            t = 0;
    }
    return 0;
}
int main()
{
    struct timeval tvalBefore, tvalAfter;
    char string[1000000];
    FILE *file = NULL;
    file = fopen("in.txt", "r");
    if (!file)
    {
        printf("Open ERR!\n");
    }
    for (int i = 0; i < 1000000; i++)
    {
        fscanf(file, "%c", &string[i]);
    }
    fclose(file);
    file = NULL;
    char substring[20];
    file = fopen("substring.txt", "r");
    if (!file)
    {
        printf("Open ERR!\n");
    }
    for (int i = 0; i < 20; i++)
    {
        fscanf(file, "%c", &substring[i]);
    }
    fclose(file);
    int d[100], answer = 1;
    gettimeofday(&tvalBefore, NULL);
    first_step(d, substring);
    answer = second_step(d, substring, string);
    gettimeofday(&tvalAfter, NULL);
    printf("\nTime in microseconds: %ld microseconds\n", ((tvalAfter.tv_sec - tvalBefore.tv_sec) * 1000000L + tvalAfter.tv_usec) - tvalBefore.tv_usec);
    printf("Shift = %d", answer);
    return 0;
}
