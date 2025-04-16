#include <stdio.h>

int main(){
    int sum=0;
    int x[4];
    for(int i=0;i<4;i++){
        scanf("%d",&x[i]);
    }

    for(int i=0;i<4;i++){
        sum += x[i];
    }

    printf("%d\n",sum/60);
    printf("%d",sum%60);

    return 0;

}