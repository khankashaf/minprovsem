#include<stdio.h>
#include<conio.h>
#include<string.h>
void pass1();
void opcodetally();
int locctr,initial_address,program_length,o,operand;
char opcode[20],label[20],op[20],otp[20];
void pass1()
{

    FILE *f1,*f2,*f4;
     f1=fopen("input.txt","r");
    f2=fopen("symtab.txt","w");
    printf("LOCATION\tLABEL\tOPERAND\tOPCODE");
    fscanf(f1,"%s%s%d",label,opcode,&operand);
    if(strcmp(opcode,"START")==0)
    {
        initial_address=operand;
        locctr=initial_address;
        printf("%s\t%s\t%d\t\n",label,opcode,operand);
    }
    else
    locctr=0;
    fscanf(f1,"%s%s",label,opcode);
    while(!feof(f1))
    {
    fscanf(f1,"%s",op);
    printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,op);
    if(strcmp(label,"-")!=0)
    {
        fprintf(f2,"\n%d\t%s\n",locctr,label);

    }
    opcodetally();
    fscanf(f1,"%s%s",label,opcode);
    }
    if(strcmp(opcode,"END")==0)
    {
        program_length=locctr-initial_address;
    }
    f4=fopen("length.txt","w");
    fprintf(f4,"%d",program_length);
    fclose(f1);
    fclose(f2);
}
void opcodetally()
{
    FILE *f3;
     f3=fopen("optab.txt","r");
    fscanf(f3,"%s%d",otp,&o);
    while(!feof(f3))
    {
        if(strcmp(opcode,otp)==0)
        {
            locctr=locctr+3;
            break;
        }
        fscanf(f3,"%s%d",otp,&o);
    }
    fclose(f3);
    if(strcmp(opcode,"WORD")==0)
    {
        locctr=locctr+3;
    }
    else if(strcmp(opcode,"RESW")==0)
    {
        operand=atoi(op);
        locctr=locctr+(3*operand);
    }
    else if(strcmp(opcode,"BYTE")==0)
    {
        if(op[0]=='X')
            locctr=locctr+1;
        else
        {
            operand=strlen(op)-2;
            locctr=locctr+operand;}
        }
        else if(strcmp(opcode,"RESB")==0)
                {
                    operand=atoi(op);
                    locctr=locctr+operand;
                }
}
int main()
{
    pass1();
    printf("length of program=%d",program_length);
    getch();
}
