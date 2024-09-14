#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define WINDOWS 1

void clrscr() {
  #ifdef WINDOWS
  system("cls");
  #endif
  #ifdef LINUX
  system("clear");
  #endif
}

void insert_stock();
void display_stock();
void search_stock_name();
void search_stock_symbol();
void delete_stock_symbol();
void delete_stock_name();
void sort_stock_cprice();
void sort_stock_52wkshigh();
void sort_stock_52wkslow();

struct stock
{
  char symbol[6];
  char stockname[25];
  long int currentmcap;
  float currentprice;
  float wk52low;
  float wk52high;
  int perchange;
};

typedef struct stock stk;

stk s;

void main()
{
    int ch;
    clrscr();
    for( ; ; )
    {
        clrscr();
        printf("<<<----------------------------------------------------------------------------------->>>\n");
        printf("        <<-------------WELCOME TO STOCK MARKET DATA BASE---------------->>\n");
        printf("<<<------------------------------------------------------------------------------------>>>\n\n\n");
        printf("<<----------------------------AVAILABLE FUNCTIONALITIES--------------------------------->>\n");
        printf("                            1-INSERT THE STOCK\n");
        printf("                            2-DISPLAY THE STOCK\n");
        printf("                            3-SEARCH THE STOCK BY NAME\n");
        printf("                            4-SEARCH THE STOCK BY SYMBOL\n");
        printf("                            5-DELETE THE STOCK BY NAME\n");
        printf("                            6-SEARCH THE STOCK BY SYMBOL\n");
        printf("                            7-SORT THE STOCK BY CURRENT PRICE\n");
        printf("                            8-SORT THE STOCK BY 52 WEEKS HIGH\n");
        printf("                            9-SORT THE STOCK BY 52 WEEKS LOW\n");
        printf("                            10-EXIT\n");
        printf("<<----------------------------------------------------------------------------------------\n");
        printf("                              ENTER THE CHOICE    :  ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
             clrscr();
             insert_stock(); 
             break;
            case 2:
             clrscr(); 
             display_stock(); 
             break;
            case 3:
             clrscr();
             search_stock_name();
              break;
            case 4:
             clrscr();
             search_stock_symbol();
              break;
            case 5: 
              clrscr(); 
              delete_stock_name(); 
              break;
            case 6: 
              clrscr(); 
              delete_stock_symbol(); 
              break;
            case 7: 
                clrscr(); 
                sort_stock_cprice(); 
                break;
            case 8: 
                clrscr(); 
                sort_stock_52wkshigh(); 
                break;
            case 9: 
                clrscr(); 
                sort_stock_52wkslow(); 
                break;
            case 10: 
                 clrscr(); 
                 printf("Exiting\n"); 
                 exit(0);
            default : 
                 clrscr(); 
                 printf("Enter valid choice\n"); 
                 break;
        }
        printf("Enter any key to continue...");
        getch();
    }
}
        
void insert_stock()
{
    FILE *fp=NULL;
    fp = fopen("stk.txt","ab+");
    if(fp==NULL)
    {
        printf("Could not pen a file!!\n"); return;
    }
    printf("------------------>>PREVIOUS DATA<<--------------------\n");
    display_stock();
    printf("-------------------------------------------------------\n");
    printf("                  ENTER NEW STOCK DETAILS              \n");

    printf("Enter Stock name        :  "); 
    scanf("%s",s.stockname);        
    fflush(stdin);

    printf("Enter Stock symbol      :  "); 
    scanf("%s",s.symbol);          
    fflush(stdin);

    printf("Enter Current m cap     :  "); 
    scanf("%ld",&s.currentmcap);    
    fflush(stdin);

    printf("Enter Current price     :  "); 
    scanf("%f",&s.currentprice);    
    fflush(stdin);

    printf("Enter 52 weeks high     :  "); 
    scanf("%f",&s.wk52high);        
    fflush(stdin);

    printf("Enter 52 weeks low      :  "); 
    scanf("%f",&s.wk52low);         
    fflush(stdin);

    printf("Enter Percentage change :  "); 
    scanf("%d",&s.perchange);       
    fflush(stdin);

    fwrite(&s,sizeof(s),1,fp);
    printf("---------STOCK DETAILS INSERTED SUCCESSFULLY------------\n");
    fclose(fp);

    printf("------------>>UPDATED STOCK MARKET BASE<<------------\n");
    display_stock();
}

void display_stock()
{
    FILE *fp=NULL;
    fp = fopen("stk.txt","rb");
    if(fp == NULL)
    {
        printf("Could not open file!!\n"); return;
    }
    printf("\n\t\t>>STOCK MARKET DETAILS OF THE YEAR<<\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\tSYMBOL          STOCK NAME                    CURRENT M CAP         CURRENT PRICE          52 WEEKS HIGH           52 WEEKS LOW            PERCENTAGE CHANGE\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    while(fread(&s,sizeof(s),1,fp)==1)
     {  printf("\t%-8s%-16s%-30ld%-21f%-23f%-24f%-24d\n",s.symbol,s.stockname,s.currentmcap,s.currentprice,s.wk52high,s.wk52low,s.perchange); }
  
    fclose(fp);
}

void search_stock_name()
{
  int flag=0;
  char name0[25];
  FILE *fp=NULL;
  fp = fopen("stk.txt","rb");
  if(fp==NULL)
  {
    printf("Could not open the file\n"); 
    return;
  }

  display_stock();
  printf("Enter the Name    : "); 
  scanf("%s",name0); 
  fflush(stdin);

  while((fread(&s,sizeof(s),1,fp)>0)&&(flag==0))
  {
    if(strcmp(s.stockname,name0)==0)
    {
        flag=1;
        printf("SEARCH SUCCESSFUL!!\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
        printf("SYMBOL  STOCK NAME\t\tCURRENT M CAP\tCURRENT PRICE\t52 WEEKS HIGH\t52 WEEKS LOW\tPERCENTAGE CHANGE\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
     {  printf("\t%-8s%-16s%-30ld%-21f%-23f%-24f%-24d\n",s.symbol,s.stockname,s.currentmcap,s.currentprice,s.wk52high,s.wk52low,s.perchange); }
    }
  }
  if(flag==0)
  { 
    printf("STOCK NAME NOT FOUND/INVALID STOCKSYMBOL!!");  
  }

  fclose(fp);
}

void search_stock_symbol()
{
  int flag=0;
  char symbl[6];
  FILE *fp=NULL;
  fp = fopen("stk.txt","rb");
  if(fp==NULL)
  {
    printf("Could not open the file\n"); 
    return;
  }

  display_stock();
  printf("Enter the Symbol    : "); 
  scanf("%s",symbl); 
  fflush(stdin);

  while((fread(&s,sizeof(s),1,fp)>0)&&(flag==0))
  {
    if(strcmp(s.symbol,symbl)==0)
    {
        flag=1;
        printf("SEARCH SUCCESSFUL!!\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
        printf("SYMBOL  STOCK NAME\t\tCURRENT M CAP\tCURRENT PRICE\t52 WEEKS HIGH\t52 WEEKS LOW\tPERCENTAGE CHANGE\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
     {  printf("\t%-8s%-16s%-30ld%-21f%-23f%-24f%-24d\n",s.symbol,s.stockname,s.currentmcap,s.currentprice,s.wk52high,s.wk52low,s.perchange); }
    }
  }
  if(flag==0)
  { 
    printf("STOCK SYMBOL NOT FOUND/INVALID STOCKSYMBOL!!");  
  }

  fclose(fp);
}

void delete_stock_symbol()
{
  int flag=0;
  char symbl[6];
  FILE *fp=NULL,*ft=NULL;

  fp = fopen("stk.txt","rb");
  if(fp==NULL)
  {
    printf("Could not open the file\n"); 
    return;
  }

  display_stock();
  printf("Enter the Symbol    : "); 
  scanf("%s",symbl); 
  fflush(stdin);

  ft = fopen("stk1.txt","ab+");
  while((fread(&s,sizeof(s),1,fp)==1))
  {
    if(strcmp(s.symbol,symbl)==0)
    { 
      printf("DELETING %s STOCK!!",s.stockname); 
      flag=1; 
    }
    if(strcmp(s.symbol,symbl)!=0)
    {
       fwrite(&s,sizeof(s),1,ft); 
    }
  }
  if(flag==0)
  { 
    printf("STOCK SYMBOL NOT FOUND/INVALID STOCKSYMBOL!!");  
   }
  fclose(fp);
  fclose(ft);
  remove("stk.txt");
  rename("stk1.txt","stk.txt");
  printf("                    UPDATED STOCK DATA BASE\n");

  display_stock();
}

void delete_stock_name()
{
  int flag=0;
  char name0[25];
  FILE *fp=NULL,*ft=NULL;

  fp = fopen("stk.txt","rb");
  if(fp==NULL)
  {
    printf("Could not open the file\n"); 
    return;
  }
  display_stock();
  printf("Enter the Name    : "); 
  scanf("%s",name0); 
  fflush(stdin);

  ft = fopen("stk2.txt","ab+");
  while((fread(&s,sizeof(s),1,fp)==1))
  {
    if(strcmp(s.stockname,name0)==0)
    { 
      printf("DELETING %s STOCK!!",s.stockname); 
      flag=1; 
    }
    if(strcmp(s.stockname,name0)!=0)
    {
       fwrite(&s,sizeof(s),1,ft); 
    }
  }
  if(flag==0)
  { 
    printf("STOCK NAME NOT FOUND/INVALID STOCKSYMBOL!!");  
   }
  fclose(fp);
  fclose(ft);
  remove("stk.txt");
  rename("stk2.txt","stk.txt");
  printf("                    UPDATED STOCK DATA BASE\n");

  display_stock();
}


void sort_stock_cprice()
{
    stk a[50],temp;
    int i,j,k=0;
    FILE *fp=NULL;
    fp = fopen("stk.txt","rb");
    if(fp == NULL)
    {  
      printf("Could not open the file!!\n"); 
      return; 
    }
    i=0;
    while(fread(&a[i],sizeof(a[i]),1,fp)==1)
    {
     i++;k++;
    }

    for(i=0 ; i<k ; i++)
    {
        for(j=0 ; j<k-1-i ; j++)
        {
            if(a[j+1].currentprice > a[j].currentprice)
            {
                temp = a[j];
                a[j] =  a[j+1];
                a[j+1] = temp;
            }
        }
    }

    printf("                 << STOCK MARKET DETAILS SORTED ACCORDING TO CURRENT PRICE >>\n");
    printf("SYMBOL  STOCK NAME\t\tCURRENT M CAP\tCURRENT PRICE\t52 WEEKS HIGH\t52 WEEKS LOW\tPERCENTAGE CHANGE\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for(i=0 ; i<k ; i++)
    {  
      printf("%s\t%s\t\t%ld\t%f\t%f\t%f\t%d\n",a[i].symbol,a[i].stockname,a[i].currentmcap,a[i].currentprice,a[i].wk52high,a[i].wk52low,a[i].perchange);  
    }

    fclose(fp);
}

void sort_stock_52wkshigh()
{
    stk a[50],temp;
    int i,j,k=0;
    FILE *fp=NULL;
    fp = fopen("stk.txt","rb");
    if(fp == NULL)
    {  
      printf("Could not open the file!!\n"); 
      return; 
    }
    i=0;
    while(fread(&a[i],sizeof(a[i]),1,fp)==1)
    {
     i++;k++;
    }

    for(i=0 ; i<k ; i++)
    {
        for(j=0 ; j<k-1-i ; j++)
        {
            if(a[j+1].wk52high > a[j].wk52high)
            {
                temp = a[j];
                a[j] =  a[j+1];
                a[j+1] = temp;
            }
        }
    }

    printf("                 << STOCK MARKET DETAILS SORTED ACCORDING TO 52 WEEKS HIGH >>\n");
    printf("SYMBOL  STOCK NAME\t\tCURRENT M CAP\tCURRENT PRICE\t52 WEEKS HIGH\t52 WEEKS LOW\tPERCENTAGE CHANGE\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for(i=0 ; i<k ; i++)
    {  
      printf("%s\t%s\t\t%ld\t%f\t%f\t%f\t%d\n",a[i].symbol,a[i].stockname,a[i].currentmcap,a[i].currentprice,a[i].wk52high,a[i].wk52low,a[i].perchange);  
    }

    fclose(fp);
}

void sort_stock_52wkslow()
{
    stk a[50],temp;
    int i,j,k=0;
    FILE *fp=NULL;
    fp = fopen("stk.txt","rb");
    if(fp == NULL)
    {  
      printf("Could not open the file!!\n"); 
      return; 
    }
    i=0;
    while(fread(&a[i],sizeof(a[i]),1,fp)==1)
    {
     i++;k++;
    }

    for(i=0 ; i<k ; i++)
    {
        for(j=0 ; j<k-1-i ; j++)
        {
            if(a[j+1].wk52low < a[j].wk52low)
            {
                temp = a[j];
                a[j] =  a[j+1];
                a[j+1] = temp;
            }
        }
    }

    printf("                 << STOCK MARKET DETAILS SORTED ACCORDING TO 52 WEEKS LOW >>\n");
    printf("SYMBOL  STOCK NAME\t\tCURRENT M CAP\tCURRENT PRICE\t52 WEEKS HIGH\t52 WEEKS LOW\tPERCENTAGE CHANGE\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for(i=0 ; i<k ; i++)
    {  
      printf("%s\t%s\t\t%ld\t%f\t%f\t%f\t%d\n",a[i].symbol,a[i].stockname,a[i].currentmcap,a[i].currentprice,a[i].wk52high,a[i].wk52low,a[i].perchange);  
    }

    fclose(fp);
}



