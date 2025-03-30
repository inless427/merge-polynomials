#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct polynomial
{
    int coef;
    int exp;
    struct polynomial *link;
}polynomial;

polynomial *head=NULL;
polynomial *current=NULL;
polynomial *last=NULL;


//print each polynomial
void printPolynomaial(polynomial *a){
    if(a==NULL){
        printf("invaild polynomials");
    }
    head=a;
    current=head;
    while (current->link!=NULL)
    {
        printf("%dx^%d+",current->coef,current->exp);
        current=current->link;
        
    }   
    printf("%dx^%d\n",current->coef,current->exp);
    last=current;
    head=NULL;
    current=NULL;
}

//search a term with given exponent
polynomial *search(int exp,polynomial *plb){
    while(plb!=NULL){
    if(plb->exp==exp){
        return plb;                                                                     //if found , return  the founded address of specified term
    }
    else{
        plb=plb->link;                                                                 //if not search next term
    }
}
return NULL;                                                                            //after examining all the terms but not found,return NULL
}

//check if the polynomial is empty
bool isEmpty(){
    return head == NULL;                                                               //if the polynomial is empty then return 1
}


//buble-sort every term of polynominal
polynomial *sort(polynomial *c){
    polynomial *temp=(polynomial*)malloc(sizeof(polynomial));
    int length=0;
    current=c;
    while(current!=NULL){
        length++;
        current=current->link;
    }
    int temp_exp=0;
    int temp_coef=0;
    for(int i=0;i<length;i++){
        current=c;
        for(int j=0;i+j<length;j++){
           if(current->link!=NULL)
         {  
            if (current->exp>current->link->exp)
            {
                //switch exponents
                temp_exp=current->link->exp;
                current->link->exp=current->exp;
                current->exp=temp_exp;

                //switch coefficients
                temp_coef=current->link->coef;
                current->link->coef=current->coef;
                current->coef=temp_coef;
            }
        }
        current=current->link;
    }
    }
    return c;
}


//merge polynomials
polynomial *merge(polynomial *a,polynomial *b){
    polynomial *temp_b=(polynomial*)malloc(sizeof(polynomial));
    while(a!=NULL&&last!=NULL){
        temp_b=search(a->exp,b);
        if(temp_b==NULL){                                                                     //if there is no such exponent in b,then link this term to last       
            last->link=a;
            last=last->link;
        }
        if(temp_b!=NULL){                                                                    //if found such exponent in b,merge the terms
            temp_b->coef+=a->coef;
        }
        a=a->link;
    }
    return b;
}

//pass parameters to create a new term
void insertTerm(polynomial *a) 
{   
    int coef,exp,i;
    printf("Please input how many terms:\n");
    scanf("%d",&i);
    while (i!=0)
    {
    printf("Please input coef:\n");
    scanf("%d",&coef);
    printf("Please input exponent:\n");
    scanf("%d",&exp);
    polynomial *newterm=(polynomial*)malloc(sizeof(polynomial));
    newterm->exp=exp;
    newterm->coef=coef;
    if (isEmpty()){                                                                         //if the polynomial is empty then create first term
        a->exp=exp;
        a->coef=coef;
        a->link=NULL;
        head=a;
        current=head;
    }
    else{
        current->link=newterm;                                                              //else link newterm to the polynomial
        current=current->link;
        current->link=NULL;
    }
    i--;
    }
    
}

int main(){
    polynomial *a=(polynomial*)malloc(sizeof(polynomial));
    polynomial *b=(polynomial*)malloc(sizeof(polynomial));
    polynomial *c=(polynomial*)malloc(sizeof(polynomial));
    insertTerm(a);
    printf("polynomial a is:\n");
    printPolynomaial(a);
    insertTerm(b);
    printf("polynomial b is:\n");
    printPolynomaial(b);
    c=merge(a,b);
    sort(c);
    printf("The polynomial after merging a and b is:\n");
    printPolynomaial(c);
    a=NULL;
    b=NULL;
    c=NULL;
    head=NULL;
    current=NULL;
    last=NULL;
    free(a);
    free(b);
    free(c);
    free(head);
    free(current);
    free(last);
    return 0;
}
