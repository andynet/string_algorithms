#include <string.h>

int bmh(char *pattern, char *text) {
    int match = 0;
    static int j = -1;
    j++;
    for (; j < strlen(text); j++) {
        for (int i = 0; i < strlen(pattern); i++) {
            if (pattern[i] == text[j + match]) {
                match++;
            } else {
                match = 0;
                break;
            }
            if (match == strlen(pattern)) {
                return j;
            }
        }
    }
    return -1;
}

//int main(void) {
//    int m = bmh("AB", "BBBBAB");
//    return 0;
//}

