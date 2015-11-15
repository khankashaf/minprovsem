#include<stdio.h>
#include<conio.h>
#include<string.h>
void pass1();
void chkopcode();
int locctr,sa,program_length,o,op1;
char opcode[20],label[20],op[20],otp[20];
void pass1()
{

    FILE *f1,*f2,*f4;
     f1=fopen("input.txt","r");
    f2=fopen("symtab.txt","w");
    fscanf(f1,"%s%s%d",label,opcode,&op1);
    if(strcmp(opcode,"START")==0)
    {
        sa=op1;
        locctr=sa;
        printf("%s\t%d\t%d\t\n",label,opcode,op1);
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
    chkopcode();
    fscanf(f1,"%s%s",label,opcode);
    }
    if(strcmp(opcode,"END")==0)
    {
        program_length=locctr-sa;
    }
    f4=fopen("length.txt","w");
    fprintf(f4,"%d",program_length);
    fclose(f1);
    fclose(f2);
}
void chkopcode()
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
        op1=atoi(op);
        locctr=locctr+(3*op1);
    }
    else if(strcmp(opcode,"BYTE")==0)
    {
        if(op[0]=='X')
            locctr=locctr+1;
        else
        {
            program_length=strlen(op)-2;
            locctr=locctr+program_length;}
        }
        else if(strcmp(opcode,"RESB")==0)
                {
                    op1=atoi(op);
                    locctr=locctr+op;
                }
}
int main()
{
    pass1();
    printf("length of program=%d",program_length);
    getch();
}
