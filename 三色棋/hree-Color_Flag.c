/*
三色棋
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLUE 'b'
#define WHITE 'w'
#define RED 'r'
#define SWAP(x, y) { char temp; \
temp = color[x]; \
color[x] = color[y]; \
color[y] = temp; }
int main() {
    char color[] = {'r', 'w', 'b', 'w', 'w',
        'b', 'r', 'b', 'w', 'r', '\0'};
    int wFlag = 0;
    int bFlag = 0;
    int rFlag = strlen(color) - 1;
    int i;
    for(i = 0; i < strlen(color); i++)
        printf("%c ", color[i]);
    printf("\n");
    while(wFlag <= rFlag) {
        if(color[wFlag] == WHITE)
            wFlag++;
        else if(color[wFlag] == BLUE) {
            SWAP(bFlag, wFlag);
            bFlag++; wFlag++;
        }
        else {
            while(wFlag < rFlag && color[rFlag] == RED)
                rFlag--;
            SWAP(rFlag, wFlag);
            rFlag--;
        }
    }
    for(i = 0; i < strlen(color); i++)
        printf("%c ", color[i]);
    printf("\n");
    return 0;
}
