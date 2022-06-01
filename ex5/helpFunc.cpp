#include <stdio.h>
#include <string.h>

char upCase(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}
//compare strings and returns 1 (true) if they are equal, otherwise 0 (false)
int compareStr(char* sentences , char* word, int lenWord) {
    for (int i=0; i<lenWord; i++) {
        //Compares each letter and does not distinguish between lowercase and uppercase letters
        if (upCase(sentences[i]) != upCase(word[i])) {
            return 0;
        }
    }
    return 1;//1 = true 
}