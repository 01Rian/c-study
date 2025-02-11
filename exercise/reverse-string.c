#include <stdio.h>

char* reverse_string(char* str)
{
    if (!str) return NULL;

    char* end = str;
    while (*end) end++;
    end--; 

    char* start = str;

    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;

        start++;
        end--;
    }

    return str;
}

int main()
{
    char str[] = "Hello, World!";
    printf("Original: %s\n", str);
    printf("Reversed: %s\n", reverse_string(str));
    return 0;
}