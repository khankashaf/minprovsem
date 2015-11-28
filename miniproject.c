#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
void pass1();
void opcodetally();
int locctr,initial_address,program_length,operand,lno,o;
char opcode[20],label[20],op[20],otp[20],progname[10];
void pass1()
{

    FILE *f1,*f2,*f4,*f5;
     f1=fopen("input.txt","r");
    f2=fopen("symtab.txt","w");
    f5=fopen("inputpass2.txt","w");
    printf("LOCATION LABEL\tOPCODE\tOPERAND\n");
    printf("______________________________________\n");
    fscanf(f1,"%s%s%x",label,opcode,&operand);
    if(strcmp(opcode,"START")==0)
    {
        initial_address=operand;
        locctr=initial_address;
        fprintf(f5,"-\t%s\t%s\t%x\t\n",label,opcode,operand);

    }

    else

    {
        locctr=0;
         fscanf(f1,"%s%s",label,opcode);
    }
         printf("%x %s\t%s\t%x\t\n",locctr,label,opcode,operand);
    fscanf(f1,"%s%s",label,opcode);
    while(!feof(f1))
    {
    fscanf(f1,"%s",op);
    fprintf(f5,"\n%04x\t%s\t%s\t%s\n",locctr,label,opcode,op);
    printf("\n%04x\t%s\t%s\t%s\n",locctr,label,opcode,op);

    if(strcmp(label,"-")!=0)
    {
        fprintf(f2,"\n%x\t%s\n",locctr,label);
        lno=lno+1;
    }
    opcodetally();
    fscanf(f1,"%s%s",label,opcode);
    }
    if(strcmp(opcode,"END")==0)
    {
        program_length=locctr-initial_address;
    }
    fclose(f1);
    fclose(f2);
    fclose(f5);
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
void pass2()
{
    int count=0,i=0,j=0,t,top,ar[50], n=0,m;
     int x;
    char val[10],loctr[10],xy[10],record[200],address[20],labal[10],opt[10],ot[10],lock[10],tric[10];
    FILE *p1,*p3,*p4,*p5;
    p1=fopen("inputpass2.txt","r");

    p3=fopen("optab.txt","r");
    p4=fopen("symtab.txt","r");
    p5=fopen("output.txt","w");
    fscanf(p1,"%s%s%s%s",val,label,opcode,op);
if(strcmp(opcode,"START")==0)
{

    fprintf(p5,"H^%s^00%s^%06x\n",label,op,program_length);
   // printf("H^%s^00%s^%06x\n",label,op,program_length);
}
    fscanf(p1,"%s%s%s%s",loctr,label,opcode,op);

   while(strcmp(opcode,"END")!=0)
    {
        memset(val,'\0',sizeof(val));
        strcpy(address,loctr);

        if(strcmp(opcode,"WORD")==0)
                {

                    t=strlen(op);

                    x=atoi(op);
                    itoa(x,xy,16);
                    top=strlen(xy);
                    j=0;
                    for(i=0;i<(6-top);i++)
                    {
                        val[j]='0';
                        j++;
                    }
                    val[j]='\0';
                    strcat(val,xy);
                    strcat(record,"^");
                    strcat(record,val);
                    count+=(strlen(val))/2;
                    printf("\n%s\t%s\t%s\t%s\t%s",loctr,label,opcode,op,val);
                }
            else if(strcmp(opcode,"BYTE")==0)
                    {
                        n=0;
                        m=0;
                        t=strlen(op);
                        t=t-3;
                        strcat(record,"^");
                        if(op[0]=='C')
                            {
                               printf("\n%s\t%s\t%s\t%s\t",loctr,label,opcode,op);
                                for(n=2,m=0;n<(t+2);m++,n++)
                                {
                                    ar[m]=op[n];
                                   itoa(ar[m],val,16);
                                    strcat(record,val);
                                   printf("%s",val);

                                }

                               printf("\n");
                                count+=m;
                            }
                     else if(op[0]=='X')
                        {
                            i=0;
                                j=0;
                                for(i=2;i<t+2;i++)
                                {
                                    val[j]=op[i];
                                    j++;
                                }
                                val[j]='\0';
                                strcat(record,val);
                                count+=(strlen(val))/2;
                                printf("\n%s\t%s\t%s\t%s\t%s",loctr,label,opcode,op,val);
                        }

                    }
                    else if(strcmp(opcode,"RESB")==0||strcmp(opcode,"RESW")==0)
                         {

                             printf("\n%s\t%s\t%s\t%s\n",loctr,label,opcode,op);
                        }
        else
         {
             fscanf(p3,"%s%s",opt,ot);
         while(strcmp(opt,opcode)!=0)
            {
                fscanf(p3,"%s%s",opt,ot);

            }

                 count=count+3;
                 strcat(record,"^");
                 strcat(record,ot);
                 rewind(p3);

                 if(strcmp(op,"-")!=0)
                 {
                     fscanf(p4,"%s%s",lock,labal);
                     while(strcmp(op,labal)!=0)

                             fscanf(p4,"%s%s",lock,labal);
                             strcat(record,lock);
                             strcpy(tric,lock);




                    }
                     rewind(p4);
                    printf("\n%s\t%s\t%s\t%s\t%s%s\n",loctr,label,opcode,op,ot,tric);

                      if(strcmp(op,"-")==0)
                         {

                             strcat(record,"^");

                             strcat(record,"0000");
                             count+=3;
                         }
         }

              fscanf(p1,"%s%s%s%s",loctr,label,opcode,op);

                }
                fprintf(p5,"T^00%s^%x%s\n",address,count,record);
            //  printf("\nT^00%s^%x%s",address,count,record);
             fprintf(p5,"E^00%x\n",initial_address);
               // printf("\nE^00%x\n",initial_address);
                fclose(p1);
                fclose(p3);
                fclose(p4);
                fclose(p5);


}
int main()
{
    pass1();
    printf("length of program=%x\n",program_length);
    printf("_____________/////////////////////////////////___________________");
    printf("\n________________________________________________________________");
    pass2();
    getch();
}
