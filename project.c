/*
It is a project to build a query processing engine for Ad-Hoc OLAP queries.
In our project, the program will parse the input list of parameters to the
Phi operator and use several structs to store these parameters. And then,
generate the output. By compiling the output, we can achieve the result.

Use gcc to run the project.c
gcc -c project.c
gcc -o project project.o

Compile the output.pgc
ecpg -I /Library/PostgreSQL/9.4/include output.pgc
gcc -c -I /Library/PostgreSQL/9.4/include output.c
gcc -L /Library/PostgreSQL/9.4/lib -lecpg -o output output.o
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct
{
    char cust[10];
    char prod[10];
} sale[100];

struct
{
    char attribute[100];
} attribute[100];
int num_attribute;
//save the output attribute

struct
{
    char group[100];
}group[100];
int num_group;
//save group by

struct
{
    char condition[100];
}condition[100];
int num_condition;
//such that

struct
{
    char having[100];
}having[100];
int num_having;
//having

int num_group_variables;
//number of grouping variables

int i,j,k,t,p;

int main(){
    printf("input the number of output attribute:\n");
    scanf("%d",&num_attribute);
    printf("input the output attribute:\n");
    for (int i=0;i<num_attribute;i++)
        scanf("%s",attribute[i].attribute);
    //input output attribute

    printf("input the number of grouping variables:\n");
    scanf("%d",&num_group_variables);
    //input number of grouping variables

    printf("input the number of grouping:\n");
    scanf("%d",&num_group);
    if (num_group!=0)
        printf("input the grouping\n");
    for (int i=0;i<num_group;i++)
        scanf("%s",group[i].group);
    //input group by

    printf("input the number of condition:\n");
    scanf("%d",&num_condition);
    if (num_condition!=0)
        printf("input the condition:\n");
    for (int i=0;i<num_condition;i++)
        scanf("%s",condition[i].condition);
    //input such that

    printf("input the number of having:\n");
    scanf("%d",&num_having);
    if (num_having!=0)
        printf("input the having\n");
    for (int i=0;i<num_having;i++)
        scanf("%s",having[i].having);
    //------------------------------------------------------------------------
    //input

    printf("#include<stdio.h>\n");
    printf("#include<string.h>\n");
    printf("#include<string.h>\n");
    //header file

    printf("EXEC SQL BEGIN DECLARE SECTION;\n");
    printf("\n");

    printf("struct{\n");
    printf("    char *cust;\n");
    printf("    char *prod;\n");
    printf("    short dd;\n");
    printf("    short mm;\n");
    printf("    short yy;\n");
    printf("    char *state;\n");
    printf("    long quant;\n");
    printf("} sale_rec;");
    printf("\n");
    printf("\n");
    //struct to save data of database

    printf("struct{\n");
    printf("    char cust[10];\n");
    printf("    char prod[10];\n");
    printf("    short dd[100];\n");
    printf("    short mindd[100];\n");
    printf("    short maxdd[100];\n");
    printf("    short d;\n");
    printf("    short mm[100];\n");
    printf("    short minmm[100];\n");
    printf("    short maxmm[100];\n");
    printf("    short m;\n");
    printf("    short yy[100];\n");
    printf("    short minyy[100];\n");
    printf("    short maxyy[100];\n");
    printf("    short y;\n");
    printf("    char state[100][10];\n");
    printf("    char minstate[100][10];\n");
    printf("    char maxstate[100][10];\n");
    printf("    char st[10];\n");
    printf("    long quant;\n");
    printf("    int avg[10];\n");
    printf("    int sum[10];\n");
    printf("    int count[10];\n");
    printf("    int min[10];\n");
    printf("    int max[10];\n");
    printf("} sale[100];");
    printf("\n");
    printf("\n");
    //struct to save answer

    printf("EXEC SQL END DECLARE SECTION;\n");
    printf("EXEC SQL INCLUDE sqlca;\n");
    printf("\n");

    printf("int main(int argc, char* argv[])\n{\n");

    printf("int i,k,p;\n");

    if (num_attribute==0)
    {
        printf("    printf(\"NULL\\n\");\n");
        printf("return 0;\n");
        printf("}\n");
        return 0;
    }
    //no output attribute

    for (i=0;i<num_attribute;i++)
    {
        p=0;
        if (strcmp(attribute[i].attribute,"cust")==0)
            p=1;
        else if (strcmp(attribute[i].attribute,"prod")==0)
            p=1;
        else if (strcmp(attribute[i].attribute,"state")==0)
            p=1;
        else if (strcmp(attribute[i].attribute,"day")==0)
            p=1;
        else if (strcmp(attribute[i].attribute,"month")==0)
            p=1;
        else if (strcmp(attribute[i].attribute,"year")==0)
            p=1;
        else if (strcmp(attribute[i].attribute,"quant")==0)
            p=1;
        for (j=0;j<strlen(attribute[i].attribute);j++)
        {
            if (attribute[i].attribute[j]=='[')
                p=1;
        }
        if (p==0)
        {
            printf("    printf(\"ERROR\\n\");\n");
            printf("return 0;\n");
            printf("}\n");
            return 0;
        }
    }
    //output has ERROR

    printf("EXEC SQL CONNECT TO postgres@localhost:5432 USER postgres;\n");
    printf("EXEC SQL WHENEVER sqlerror sqlprint;\n");
    printf("EXEC SQL DECLARE mycursor CURSOR FOR SELECT * FROM sales;\n");
    printf("EXEC SQL SET TRANSACTION read only;\n");
    printf("\n");
    //connect to database
    //------------------------------------------------------------------------

if (num_group_variables!=0)
//judge that if the grouping by exist
{
    //if it has grouping by
    for (i=0;i<=num_group_variables;i++)
    //compute all the grouping variables(from 0 to num_group_variables)
    {
        printf("EXEC SQL OPEN mycursor;\n");
        printf("EXEC SQL FETCH FROM mycursor INTO :sale_rec;\n");
        //fitch fist data from database

        printf("k=0;\n");
        printf("while (sqlca.sqlcode == 0)\n");
        printf("{\n");
        printf("    p=0;\n");
        printf("    for (i=1;i<=k;i++)\n");
        printf("    {\n");
        printf("        if (");

        for (j=0;j<num_group;j++)
        {
            if (strcmp(group[j].group,"cust")==0)
                printf("strcmp(sale[i].cust,sale_rec.cust)==0 ");
            else if (strcmp(group[j].group,"prod")==0)
                printf("strcmp(sale[i].prod,sale_rec.prod)==0 ");
            else if (strcmp(group[j].group,"state")==0)
                printf("strcmp(sale[i].st,sale_rec.state)==0 ");
            else if (strcmp(group[j].group,"year")==0)
                printf("sale[i].y==sale_rec.yy ");
            else if (strcmp(group[j].group,"month")==0)
                printf("sale[i].m==sale_rec.mm ");
            else if (strcmp(group[j].group,"day")==0)
                printf("sale[i].d==sale_rec.dd ");
            else if (strcmp(group[j].group,"quant")==0)
                printf("sale[i].quant==sale_rec.quant ");
            if (j!=num_group-1)
                printf(" && ");
        }
        //get the group by content
        //judge that if the combination of group by is exist

        printf(")\n");
        printf("        {\n");
        printf("            p=1;\n");

        p=0;
        for (j=0;j<num_condition;j++)
            if (condition[j].condition[0]==i+48)
                p=1;
        //judge that if that such that is exist
        if (p!=0)
        {
            printf("            if (");
            t=0;
            for (j=0;j<num_condition;j++)
                if (condition[j].condition[0]==i+48)
                {
                    if (t>0)
                        printf(" && ");
                    for (k=2;k<strlen(condition[j].condition);k++)
                        printf("%c",condition[j].condition[k]);
                }
        printf(")\n");
        }
        //get the such that content

        printf("            {\n");
        printf("                strcpy(sale[i].state[%d],sale_rec.state);\n",i);
        printf("                sale[i].yy[%d]=sale_rec.yy;\n",i);
        printf("                sale[i].mm[%d]=sale_rec.mm;\n",i);
        printf("                sale[i].dd[%d]=sale_rec.dd;\n",i);
        printf("                if  (sale[i].min[%d]==0)\n",i);
        printf("                {\n");
        printf("                    sale[i].min[%d]=sale_rec.quant;\n",i);
        printf("                    sale[i].mindd[%d]=sale_rec.dd;\n",i);
        printf("                    sale[i].minmm[%d]=sale_rec.mm;\n",i);
        printf("                    sale[i].minyy[%d]=sale_rec.yy;\n",i);
        printf("                    strcpy(sale[i].minstate[%d],sale_rec.state);\n",i);
        printf("                }\n");
        printf("                if (sale[i].min[%d]>sale_rec.quant)\n",i);
        printf("                {\n");
        printf("                      sale[i].min[%d]=sale_rec.quant;\n",i);
        printf("                      sale[i].mindd[%d]=sale_rec.dd;\n",i);
        printf("                      sale[i].minmm[%d]=sale_rec.mm;\n",i);
        printf("                      sale[i].minyy[%d]=sale_rec.yy;\n",i);
        printf("                      strcpy(sale[i].minstate[%d],sale_rec.state);\n",i);
        printf("                }\n");
        printf("                if (sale[i].max[%d]<sale_rec.quant)\n",i);
        printf("                {\n");
        printf("                      sale[i].max[%d]=sale_rec.quant;\n",i);
        printf("                      sale[i].maxdd[%d]=sale_rec.dd;\n",i);
        printf("                      sale[i].maxmm[%d]=sale_rec.mm;\n",i);
        printf("                      sale[i].maxyy[%d]=sale_rec.yy;\n",i);
        printf("                      strcpy(sale[i].maxstate[%d],sale_rec.state);\n",i);
        printf("                }\n");
        printf("                sale[i].sum[%d]+=sale_rec.quant;\n",i);
        printf("                sale[i].count[%d]++;\n",i);
        printf("            }\n");
        printf("        }\n");
        printf("    }\n");
        //if the combination is exist then update struct(sale)

        printf("    if (p==0)\n");
        printf("    {\n");
        printf("        k++;\n");
        printf("        strcpy(sale[k].cust,sale_rec.cust);\n");
        printf("        strcpy(sale[k].prod,sale_rec.prod);\n");
        printf("        strcpy(sale[k].state[%d],sale_rec.state);\n",i);
        printf("        strcpy(sale[k].st,sale_rec.state);\n");
        printf("        sale[k].yy[%d]=sale_rec.yy;\n",i);
        printf("        sale[k].mm[%d]=sale_rec.mm;\n",i);
        printf("        sale[k].dd[%d]=sale_rec.dd;\n",i);
        printf("        sale[k].y=sale_rec.yy;\n");
        printf("        sale[k].m=sale_rec.mm;\n");
        printf("        sale[k].d=sale_rec.dd;\n");
        printf("        sale[k].quant=sale_rec.quant;\n");
        p=0;
        for (j=0;j<num_condition;j++)
            if (condition[j].condition[0]==i+48)
                p=1;
        if (p!=0)
        {
            printf("        if (");
            t=0;
            for (j=0;j<num_condition;j++)
                if (condition[j].condition[0]==i+48)
                {
                    if (t>0)
                        printf(" && ");
                    for (k=2;k<strlen(condition[j].condition);k++)
                        printf("%c",condition[j].condition[k]);
                }
        printf(")\n");
        }
        //get such that content

        printf("        {\n");
        printf("            sale[k].min[%d]=sale_rec.quant;\n",i);
        printf("            sale[i].mindd[%d]=sale_rec.dd;\n",i);
        printf("            sale[i].minmm[%d]=sale_rec.mm;\n",i);
        printf("            sale[i].minyy[%d]=sale_rec.yy;\n",i);
        printf("            strcpy(sale[i].minstate[%d],sale_rec.state);\n",i);
        printf("            sale[k].max[%d]=sale_rec.quant;\n",i);
        printf("            sale[i].maxdd[%d]=sale_rec.dd;\n",i);
        printf("            sale[i].maxmm[%d]=sale_rec.mm;\n",i);
        printf("            sale[i].maxyy[%d]=sale_rec.yy;\n",i);
        printf("            strcpy(sale[i].maxstate[%d],sale_rec.state);\n",i);
        printf("            sale[k].sum[%d]+=sale_rec.quant;\n",i);
        printf("            sale[k].count[%d]++;\n",i);
        printf("        }\n");
        printf("    }\n");
        //if the combination is not exist then add new lane into struct(sale)

        printf("    EXEC SQL FETCH FROM mycursor INTO :sale_rec;\n");
        printf("}\n");

        printf("for (i=1;i<=k;i++)\n");
        printf("    if (sale[i].count[%d]!=0)\n",i);
        printf("        sale[i].avg[%d]=sale[i].sum[%d]/sale[i].count[%d];\n",i,i,i);
        //compute average

        printf("EXEC SQL CLOSE mycursor;\n");
        printf("\n");
    }
    printf("printf(\"");
    for (i=0;i<num_attribute;i++)
    {
        if (strcmp(attribute[i].attribute,"cust")==0 || strcmp(attribute[i].attribute,"prod")==0)
        printf("   ");
        printf("%s ",attribute[i].attribute);
    }
    printf("\\n");
    printf("\");\n");
    //output title

    printf("for (i=1;i<=k;i++)\n");
    if (num_having!=0)
    {
        printf("    if (");//sale[i].sum[1]>2*sale[i].sum[2] || sale[i].avg[1]>sale[i].avg[3];
        for (i=0;i<num_having;i++)
            printf("%s ",having[i].having);
        printf(")\n");
    }
    //deal with having

    printf("        printf(\"");
    for (j=0;j<num_attribute;j++)
    {
        if (strcmp(attribute[j].attribute,"cust")==0)
        {
            printf("%%");
            printf("%lds",strlen(attribute[j].attribute)+3);
        }
        else if (strcmp(attribute[j].attribute,"prod")==0)
        {
            printf("%%");
            printf("%lds",strlen(attribute[j].attribute)+3);
        }
        else if (strcmp(attribute[j].attribute,"state")==0)
        {
            printf("%%");
            printf("%lds",strlen(attribute[j].attribute));
        }
        else if (attribute[j].attribute[0]=='s' && attribute[j].attribute[1]=='t')
        {
            printf("%%");
            printf("%lds",strlen(attribute[j].attribute));
        }
        else
        {
            printf("%%");
            printf("%ldd",strlen(attribute[j].attribute));
        }
        if (j!=num_attribute-1)
            printf(" ");
    }

    printf("\\n\",");
    for (j=0;j<num_attribute;j++)
    {
        printf("sale[i].");
        if (strcmp(attribute[j].attribute,"month")==0)
            printf("m");
        else if (strcmp(attribute[j].attribute,"year")==0)
            printf("y");
        else if (strcmp(attribute[j].attribute,"day")==0)
            printf("d");
        else printf("%s",attribute[j].attribute);
        if (j!=num_attribute-1)
            printf(",");
    }
    printf(");\n");
    //output

    printf("\n");
    printf("return 0;\n");
    printf("}\n");
}
else if (num_group_variables==0)
//it doesn't have goup by
{
    printf("EXEC SQL OPEN mycursor;\n");
    printf("EXEC SQL FETCH FROM mycursor INTO :sale_rec;\n");
    printf("printf(\"");
    for (i=0;i<num_attribute;i++)
    {
        if (strcmp(attribute[i].attribute,"cust")==0 || (strcmp(attribute[i].attribute,"prod")==0))
            printf("   ");
        printf("%s ",attribute[i].attribute);
    }
    printf("\\n");
    printf("\");\n");
    //output title

    printf("while (sqlca.sqlcode == 0)\n");
    printf("{\n");
    if (num_having!=0)
    {
        printf("    if (");
        for (j=0;j<num_having;j++)
            printf("%s ",having[j].having);
        printf(")\n");
    }
    printf("        printf(\"");
    for (i=0;i<num_attribute;i++)
    {
        if (strcmp(attribute[i].attribute,"cust")==0)
            printf("%%7s ");
        else if (strcmp(attribute[i].attribute,"prod")==0)
            printf("%%7s ");
        else if (strcmp(attribute[i].attribute,"month")==0)
            printf("%%5d ");
        else if (strcmp(attribute[i].attribute,"day")==0)
            printf("%%3d ");
        else if (strcmp(attribute[i].attribute,"year")==0)
            printf("%%4d ");
        else if (strcmp(attribute[i].attribute,"state")==0)
            printf("%%5s ");
        else if (strcmp(attribute[i].attribute,"quant")==0)
            printf("%%5ld ");
    }
    printf("\\n\",");
    for (i=0;i<num_attribute;i++)
    {
        if (strcmp(attribute[i].attribute,"cust")==0)
            printf("sale_rec.cust");
        else if (strcmp(attribute[i].attribute,"prod")==0)
            printf("sale_rec.prod");
        else if (strcmp(attribute[i].attribute,"month")==0)
            printf("sale_rec.mm");
        else if (strcmp(attribute[i].attribute,"day")==0)
            printf("sale_rec.dd");
        else if (strcmp(attribute[i].attribute,"year")==0)
            printf("sale_rec.yy");
        else if (strcmp(attribute[i].attribute,"state")==0)
            printf("sale_rec.state");
        else if (strcmp(attribute[i].attribute,"quant")==0)
            printf("sale_rec.quant");
        if (i!=num_attribute-1)
            printf(",");
    }
    //output

    printf(");\n");
    printf("    EXEC SQL FETCH FROM mycursor INTO :sale_rec;\n");
    printf("}\n");
    printf("EXEC SQL CLOSE mycursor;\n");
    printf("return 0;\n");
    printf("}\n");
}

    return 0;
}
