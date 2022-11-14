#include <stdio.h>

int binsearch(int x, int v[], int n){
    int low, high, mid;
    low = 0;
    high = n - 1 ;
    while (low <= high && x != v[(mid = (low + high) / 2)] ) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1 ;
    }
    if (x != v[mid])
        return -1; /* совпадения нет */
    else
        return mid;/* совпадение есть */
}

int main(){

    return 0;
}
