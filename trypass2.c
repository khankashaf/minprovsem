#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
int locctr,initial_address,program_length,o,operand,i;
char opcode[20],label[20],op[20],otp[20],start[10];
//void pass2()
int main()
{
    FILE *p1,*p2,*p3,*p4;
    p1=fopen("inputpass2.txt","r");
    p2=fopen("length.txt","r");
    p3=fopen("optab.txt","r");
    p4=fopen("symtab.txt","r");
    fscanf(p1,"%s%s%s",label,opcode,op);
if(strcmp(opcode,"START")==0)
{
   // printf("hello");
    strcpy(start,op);
    fscanf(p2,"%d",&program_length);
  //  printf("%d",program_length);
}
//printf("hello");
    printf("H^%s^00%s^%d\nT^00%s",label,start,program_length,start);
    fscanf(p1,"%s%s%s",label,opcode,op);
    //fscanf(p1,"%d%s%s%s",locctr,label,opcode,op);
    printf("hello");
}
