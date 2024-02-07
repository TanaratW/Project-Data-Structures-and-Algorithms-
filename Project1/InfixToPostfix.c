#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct nd {
    char c;
    struct nd* next;
} node;

node* top = NULL;

void push(char x) {
    node* n = malloc(sizeof(node));
    n->next = top;
    top = n;
    n->c = x;
}

char pop() {
    char p;
    node* n;
    n = top;
    top = top->next;
    p = n->c;
    free(n);
    return p;
}

char stacktop() {
    if (top == NULL) {
        return '\0';
    } else {
        return top->c;
    }
}

// check ลำดับความสำคัญ
int checkOperator(char operator) {

    if (operator == '^')
        return 3;
    else if (operator == '*' || operator == '/')
        return 2;
    else if (operator == '+' || operator == '-')
        return 1;
    else
        return 0;
}

void InfixToPostfixWithSteps(char* infix, int size) {
    char stack[size],output[size];
    int nst = 0, nout = 0;

    // ทำให้ข้อมูลใน array ของ stack, output เป็น NULL ทุก index
    for(int i = 0; i <= size; i++){
        stack[i] = '\0';
        output[i] = '\0';
    }
    
    printf("----------------------------------------------------------------------------------\n");
    printf("%-5s%-10s%-15s%-5s%-11s%10s%25s\n", "|","Step", "|    Symbol", "|","Stack", "|    Output", "|");
    printf("----------------------------------------------------------------------------------\n");

    for(int i = 0; i <= size; i++){

        if(isalnum(infix[i])){          //  ตรวจว่าตัวที่รับเข้ามานั้น ใช่ Operand รึป่าว
            output[nout++] = infix[i];

        }else if (infix[i] == '('){     // ตรวจ (
            push(infix[i]);
            stack[nst++] = infix[i];

        }else if (infix[i] == ')'){     // ตรวจ )
            while(stacktop() != '('){
                output[nout++] = pop();
                stack[nst--] = '\0';
            }
            pop(); // เอา ( ออก
            stack[nst--] = '\0';
            stack[nst] = '\0';
        }else{                          // ตรวจ Operator  
            if(stacktop() == '\0' || stacktop() == '('){ 
                push(infix[i]);
                stack[nst++] = infix[i];
            }else {
                while((checkOperator(infix[i]) <= checkOperator(stacktop())) && stacktop() != '\0'){
                    output[nout++] = pop();
                    stack[nst--] = '\0';
                }
                push(infix[i]);
                stack[nst++] = infix[i];
            }
        }
        printf("%-6s%-9d%-7s%-8c%-5s%-11s%-5s%-30s%s\n", "|", i + 1, "|", infix[i], "|", stack, "|", output, "|");
    }

    // เป็นการแสดงผลลัพธ์บรรทัดสุดท้าย
    int finalcheck = 0;
    while(stacktop() != '\0'){
        output[nout++] = pop();
        finalcheck++;
    } 

    if(finalcheck > 0){
        printf("%-6s%-9d%-7s%-8s%-7s%-9s%-5s%-30s%s\n", "|",  size + 2, "|", "", "|", "", "|", output, "|");
    }
    printf("----------------------------------------------------------------------------------\n");
    printf("|   RESULT: %-69s", output);
    printf("%s\n", "|");
    printf("----------------------------------------------------------------------------------");
}

int main() {
    char forcls[10];
    printf("\n\n          [ENG23 2031 Data Structres and Algorithim]\n\n");
    printf("              Welcome to our project [Group 15]\n\n");
    printf("     This project can help you convert Infix to Postfix ");
    printf("\n\n--------------------------- Develops --------------------------------");
    printf("\n\nB6505295 Poramet Withaisong\n\nB6507022 Padungsit Supromin\n\nB6509644 Tanarat Witantiwong\n\nB6525279 Martin Panchengsri");
    printf("\n\n--------------------------- Present ----------------------------------");
    printf("\n\nDr. Supaporn Bunrit");
    printf("\n\n----------------------------------------------------------------------");
    printf("\n\n             [ Please Enter to continue .... ]");
    fflush(stdin);
    scanf("%[^\n]%c", &forcls);
    system("cls");
    getchar();

    char c;
    int size = -1;
    printf("\n\n                                  [Start ... ]");
    printf("\n\n----------------------- PROGRAM CONVERT INFIX TO POSTFIX -------------------------\n\n");
    printf("Please enter your Infix:");
    printf("\n\nInfix: ");

    do{
        scanf("%c",&c);
        if(c != '\n'){
            push(c);
            size++;
        }
    }while(c != '\n');

    char Infix[size];
    for(int i = size; i >= 0; i--){
        Infix[i] = pop();
    }

    InfixToPostfixWithSteps(Infix, size);

    // Example
    //Infix : a+b*(c^d-e)^(f+g*h)-i ---> Postfix : abcd^e-fgh*+^*+i- (ref. geeksforgeeks)
    //Infix : ((H*((((A+((B+C)*D))*F)*G)*E))+J) ---> Postfix : HABC+D*+F*G*E**J+
    //Infix : (2-3+4)*(5+6*7) ---> Postfix : 23-4+567*+*
    return 0;
}
