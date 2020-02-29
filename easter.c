//find if the year is easter//
//Steve //
//z5310206//

#include <stdio.h>

int main(void){

    int z;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int g = 0;
    int h = 0;
    int i = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    int p = 0;    
    
    printf("Enter year: ");
    scanf("%d", &z);
    
    a = z % 19;
    b = z / 100;
    c = z % 100;
    d = b / 4;
    e = b % 4;
    f = (b + 8) / 25;
    g = (b - f + 1) / 3;
    h = (19 * a + b - d - g + 15) % 30;
    i = c / 4;
    k = c % 4;
    l = (32 + 2 * e + 2 * i - h - k) % 7;
    m = (a + 11 * h + 22 * l) / 451;
    p = (h + l - 7 * m + 114) % 31;
    
    int EasterMonth;
    int EasterDate;
    
    EasterMonth = (h + l - 7 * m + 114) / 31;
    EasterDate = p + 1;
    
    if (EasterMonth == 3) {
        printf("Easter is March %d in %d.\n", EasterDate, z);
    }
    else {
        printf("Easter is April %d in %d.\n", EasterDate, z);
    }
    
    return(0);
}


