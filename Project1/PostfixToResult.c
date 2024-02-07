#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX_SIZE 100

typedef struct nd {
    char Data[MAX_SIZE];
    struct nd* next;
} node;
node* top = NULL;

void push(char x[]) {
    node* n = (node*)malloc(sizeof(node));
    n->next = top;
    top = n;
    strcpy(n->Data, x);
}

char* pop() {
    char* pop = (char*)malloc(MAX_SIZE * sizeof(char));

    node* n;
    n = top;
    top = top->next;

    strcpy(pop, n->Data);
    free(n);
    return pop;
}

char* stacktop() {
    char* checktop = (char*)malloc(MAX_SIZE * sizeof(char));

    if (top == NULL) {
        return NULL;
    } else {
        strcpy(checktop, top->Data);
        return checktop;
    }
}

void printStackOfAlpha() {
    node *current = top;
    char stack[MAX_SIZE][MAX_SIZE];
    char display[MAX_SIZE];

    for(int i = 0; i < MAX_SIZE; i++){
        display[i] = '\0';
    }

    int index = 0;
    while(current != NULL){
        strcpy(stack[index],current->Data);
        current = current->next;
        index++;
    }
    printf("%3s", "");
    for(int i = index - 1; i >= 0; i--){
        strcat(display,stack[i]);
    }
    printf("%-51s", display);
}


void printStackOfDigit() {
    node *current = top;
    char stack[MAX_SIZE][MAX_SIZE];
    char display[MAX_SIZE];

    for(int i = 0; i < MAX_SIZE; i++){
        display[i] = '\0';
    }

    int index = 0;
    while(current != NULL){
        strcpy(stack[index],current->Data);
        current = current->next;
        index++;
    }
    printf("%3s", "");
    for(int i = index - 1; i >= 0; i--){

        if(i == 0){
            strcat(display,stack[i]);

        } else {
            strcat(display,stack[i]);
            strcat(display, ", ");
        }
    }
    printf("%-51s", display);
}

int isOperator(char sym) {
    return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^');
}

void PostfixToResultWithStep(char Postfix[], int size){

    char open[2] = { '(', '\0' }, end[2] = { ')', '\0' };
    char chuaKhrao[2];
    int value;

    printf("----------------------------------------------------------------------------------\n");
    printf("%-10s%-15s%-3s%-53s%s\n", "|  Step ", "|   Symbol ", "|","  Stack ", "|");
    printf("----------------------------------------------------------------------------------\n");

    for(int i = 0; i < size; i++){
        char operand1[MAX_SIZE] = {'\0'}, operand2[MAX_SIZE] = {'\0'}, ex[MAX_SIZE] = {'\0'};
        chuaKhrao[0] = Postfix[i];
        chuaKhrao[1] = '\0';
        if(isalpha(Postfix[0])){
            if(isalpha(chuaKhrao[0])){
                push(chuaKhrao);
            } else if(isOperator(chuaKhrao[0])){
                strcpy(operand2, pop());
                strcpy(operand1, pop());
                strcat(ex,open);
                strcat(ex,operand1);
                strcat(ex,chuaKhrao);
                strcat(ex,operand2);
                strcat(ex,end);
                push(ex);   
            } else {
                printf("Invalid Input!!!\n");
                exit(0);
            }

            printf("%-4s%-6d%-6s%-9c%-2s","|", i + 1, "|", Postfix[i] , "|");
            printStackOfAlpha();
            printf("%s", "|");
            printf("\n");


        } else if(isdigit(Postfix[0])) {
            if(isdigit(chuaKhrao[0])){
                push(chuaKhrao);
            } else if(isOperator(chuaKhrao[0])){
                strcpy(operand2, pop());
                strcpy(operand1, pop());

                switch(chuaKhrao[0]){
                    case '+':

                        value = atoi(operand1) + atoi(operand2);
                        break;

                    case '-':

                        value = atoi(operand1) - atoi(operand2);
                        break;

                    case '*':

                        value = atoi(operand1) * atoi(operand2);
                        break;

                    case '/':

                        value = atoi(operand1) / atoi(operand2);
                        break;

                    case '^':

                        value = pow(atoi(operand1),atoi(operand2));
                        break;
                    
                    default:
                        break;
                }

                itoa(value, ex, 10);
                push(ex);

            } else {
                printf("Invalid Input!!!\n");
                exit(0);
            }

            printf("%-4s%-6d%-6s%-9c%-2s","|", i + 1, "|", Postfix[i] , "|");
            printStackOfDigit();
            printf("%s", "|");
            printf("\n");

        }
    }

    printf("----------------------------------------------------------------------------------\n");
    char * t = stacktop();
    if(t != NULL){
        printf("| RESULT: %-71s", t);
        printf("%s\n", "|");
    } else {
        printf("| RESULT: ");
        printf("%71s\n", "|");
    }
    printf("----------------------------------------------------------------------------------\n");
}

int main() {

    char forcls[10];
    printf("\n\n          [ENG23 2031 Data Structres and Algorithim]\n\n");
    printf("              Welcome to our project [Group 15]\n\n");
    printf("     This project can help you convert Postfix to Result ");
    printf("\n\n--------------------------- Develops --------------------------------");
    printf("\n\nB6505295 Poramet Withaisong\n\nB6507022 Padungsit Supromin\n\nB6509644 Tanarat Witantiwong\n\nB6525279 Martin Panchengsri");
    printf("\n\n--------------------------- Present ----------------------------------");
    printf("\n\nDr. Supaporn Bunrit");
    printf("\n\n----------------------------------------------------------------------");
    printf("\n\n             [ Please Enter to continue .... ]");
    fflush(stdin);
    scanf("%[^\n]%*c", &forcls);
    system("cls");
    getchar();

    printf("\n\n                                  [Start ... ]");
    printf("\n\n----------------------- PROGRAM CONVERT POSTFIX TO RESULT ------------------------\n\n");

    char Postfix[MAX_SIZE];
    printf("Please Enter your Postfix: \n\n");
    printf("Postfix: ");
    fgets(Postfix,sizeof(Postfix),stdin);
    int size = strlen(Postfix) - 1;

    PostfixToResultWithStep(Postfix,size);
    
    // Example
    //Infix : a+b*(c^d-e)^(f+g*h)-i ---> Postfix : abcd^e-fgh*+^*+i- (ref. geeksforgeeks)
    //Infix : ((H*((((A+((B+C)*D))*F)*G)*E))+J) ---> Postfix : HABC+D*+F*G*E**J+
    //Infix : (2-3+4)*(5+6*7) ---> Postfix : 23-4+567*+* --> Result : 141

    return 0;
}
