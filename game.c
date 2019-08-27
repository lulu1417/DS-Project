#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#define MAX_LENGTH 4
clock_t start,finish;

char *check(char data[MAX_LENGTH], char answer[MAX_LENGTH]) {
    static char clue[12];
    char temp_A[5],temp_B[5];
    int i;
    int A = 0;
    int ans_appear_times[10] = {0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0};
    int data_appear_times[10] = {0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0};
    //calculate A
    for(i=0; i<MAX_LENGTH; i++) {
        if(data[i] == answer[i]) {
            A++;
        }
        else {
            ans_appear_times[answer[i]-'0']++;
            data_appear_times[data[i]-'0']++;
        }
    }
  // calculate B
    int B = 0;
    for(i=0; i<10; i++) {
        if(data_appear_times[i] >= ans_appear_times[i]) {
            B += ans_appear_times[i];
        }
        else {
            B += data_appear_times[i];
        }
    }
    if(A==MAX_LENGTH && B==0)	{
  	    return "Answer Correct!!";
    }
    sprintf(temp_A,"%d",A);
    sprintf(temp_B,"%d",B);
    strcat(temp_A,"A");
    strcat(temp_B,"B");
    strcat(temp_A,temp_B);
    strcpy(clue,temp_A);

    return clue;
}
char *guess(char *clue){

    static char data[MAX_LENGTH]; //'data' is the number that you guess
    int i;
    char str[MAX_LENGTH];
    scanf("%s",str);
    for(i=0; i<MAX_LENGTH; i++) {
        data[i] = str[i];
    }
    //delete the above code and change it into your own program
    return data;
}

int main() {

    char ans[MAX_LENGTH];
    char get_back[MAX_LENGTH]="0A0B";   //initial input to guess function
    srand(time(NULL));
    struct timeval tval_before, tval_after, tval_result;
	printf("\n***********星爆猜數字************\n\n");
	printf("規則：猜四位數字，數字包含0~9（可重複） \n數字與位置正確為A，數字正確但位置不正確則為B。\n\nEx.正解為1341，猜1354則回傳2A1B\n\n");
	printf("請輸入四位數字:\n");
    int i=0;
    for(i=0; i<MAX_LENGTH; i++) {
        ans[i] = rand()%10+'0';
    }

    //time start
    i=1;
    gettimeofday(&tval_before, NULL);
    while(1){
        //get_back means the result of your guess
  	    strcpy(get_back,check(guess(get_back), ans));
        printf("[%d] %s\n\n",i,get_back);
        // your guess is right!!! Congratulation !!!
        if(strcmp(get_back,"Answer Correct!!")==0)
             break;
  	    gettimeofday(&tval_after, NULL);
  	    long t = (tval_after.tv_sec*1e6 + tval_after.tv_usec) - (tval_before.tv_sec*1e6 + tval_before.tv_usec);
  	    // convert to what we can read
        const int n = snprintf(NULL, 0, "%lu", t);
        assert(n > 0);
        char buf[n+1];
        int c = snprintf(buf, n+1, "%lu", t);
        assert(buf[n] == '\0');
        assert(c == n);
        //print time
        /*int length = strlen(buf);
        if(length>6) {
            for(int i=0; i<length-6;i++){
                printf("%c",buf[i]);
            }
            printf(",");
            for(int i=length-6; i<length;i++) {
                printf("%c",buf[i]);
            }
            printf("\n");
        }*/
        i++;
    }
    return 0;
}
