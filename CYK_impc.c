#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkNTR(char ch){
    char big[] = {'S','A','B','C','D','E','F','G','H'};
    for(int i=0; i<strlen(big); i++){
        if(ch==big[i])
            return true;
    }
    return false;
}

bool checkTR(char ch){
    char small[] = {'a','b','c','d','e'};
    for(int i=0; i<strlen(small); i++){
        if(ch==small[i])
            return true;
    }
    return false;
}

bool checkPR(char ch[]){
    if(strlen(ch)==1){
        if(checkTR(ch[0])){
            return true;
        }
    } else if(strlen(ch)==2){
        if(checkNTR(ch[0]) && checkNTR(ch[1])){
           return true;
        }
    }
    return false;
}

bool checkEle(char El[], char ch){
    for(int i=0; i<strlen(El); i++){
        if(ch==El[i]){
            return true;
        }
    }
    return false;
}

int main(){
    // Predefinidos
    int n_pr = 4;
    char ntr[] = {'S', 'A', 'B'};
    int ntr_cnt[] = {2, 1, 1};
    char pr[4][3] = {"AB", "e", "a", "b"};

    printf("Producción predefinida:\n");
    printf("S --> AB\nS --> e\nA --> a\nB --> b\n");

    fflush(stdin);
    int n = 0;
    printf("\n\nInput String: ");
    char s1[10];
    fgets(s1, sizeof(s1), stdin);
    s1[strcspn(s1, "\n")] = '\0';
    fflush(stdin);
    n = strlen(s1);
    char st[n];
    strcpy(st, s1);
    char tb[n][n][10]; // Table

    if(n == 0){
        printf("Empty String!\n");
        return -1;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 10; k++)
                tb[i][j][k] = '\0';
        }
    }

    for(int i = 0; i < n; i++){
        int pr_cnt = 0;
        int k2 = 0;
        for(int i2 = 0; i2 < 3; i2++){
            for(int j2 = 0; j2 < ntr_cnt[i2]; j2++) {
                pr_cnt += (i2 + j2);
                if(checkTR(pr[pr_cnt][0]) && pr[pr_cnt][0] == st[i]){
                    tb[i][i][k2] = ntr[i2];
                    k2 += 1;
                }
            }
        }
    }

    for(int l = 1; l <= (n - 1); l++){
        for(int i = 0, j = 0; i <= (n - l - 1); i++){
            j = i + l;

            for(int k = i; k <= (j - 1); k++){
                int pr_cnt = 0;
                int k2 = 0;

                for(int i2 = 0; i2 < 3; i2++){
                    for(int j2 = 0; j2 < ntr_cnt[i2]; j2++) {
                        pr_cnt += (i2 + j2);
                        if(checkNTR(pr[pr_cnt][0])){
                            if(checkEle(tb[i][k], pr[pr_cnt][0]) && checkEle(tb[k+1][j], pr[pr_cnt][1])){
                                tb[i][j][k2] = ntr[i2];
                                k2 += 1;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("\n\n\nTable:\n\n");

    for(int i = 0; i < n; i++){
        printf("|");
        for(int j = 0; j < n; j++){
            printf("%s |", tb[i][j]);
        }
        printf("\n");
    }

    if(checkEle(tb[0][n-1], 'S')){
        printf("\n\nThis String is Accepted!\n\n");
    } else{
        printf("\n\nThis String is Rejected!\n\n");
    }

    return 0;
}