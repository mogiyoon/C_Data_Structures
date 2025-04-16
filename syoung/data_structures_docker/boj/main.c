#include <stdio.h>
//1개 또는 3개 가져가기 -> 마지막 돌 가져가는 사람이 승(SK, CY)
int main(){
    int n;
    scanf("%d", &n);
    int dp[n+1];
    dp[0] = 1;
    for(int i=1; i<n+1; i++){
        if(i>1 && i<3)
            dp[i] = dp[i-1];
        else
            dp[i] = (dp[i-1]<dp[i-3] ? dp[i-1] : dp[i-3])+1;
    }
    if(dp[n]%2==0){
        printf("%d", dp[n]);
        printf("CY");
    }else{
        printf("%d", dp[n]);
        printf("SK");
    }
        
    return 0;
}