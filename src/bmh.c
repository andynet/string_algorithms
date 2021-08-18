#include <string.h>
#include <stdlib.h>

int *precompute_lambda(char *pattern){
    size_t m = strlen(pattern);
    int *lambda = (int *)calloc(256, (sizeof *lambda));
    for (size_t i = 0; i < m; i++){
        lambda[(uint)pattern[i]] = i;
    }
    return lambda;
}

int bmh(char *pattern, char *text) {
    int *lambda = precompute_lambda(pattern);
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);
    static int j = -1;
    j++;
    while (j <= n - m){
        int i = m - 1;
        while (i >= 0 && pattern[i] == text[j+i]){
            i--;
        }
        if (i < 0){
            return j + i + 1;
        }
        j = j + m - lambda[(uint)text[j+m]];
    }
    return -1;
}

