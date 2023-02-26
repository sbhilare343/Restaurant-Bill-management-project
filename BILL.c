#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

struct items
{
    char item[30];
    int qty;
    float price;
} typedef items;
struct order
{
    char name[30];
    int num; // number of items
    items itm[50];
};

// functions to generate bills

// function will generate bill header with date and name
void generateBillHeader(char name[50])
{
    //  time_t tm;
    //  time(&tm);

    printf("\n\n");
    printf("\t  KAMAT RESTAURANT");
    printf("\n\t----------------");
    // printf("\nDate/time:%s", ctime(&tm));
    printf("\nDate:%s",__DATE__);
    printf("\nInvoice to: %s", name);
    printf("\n");
    printf("------------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------");
    printf("\n\n");
}

// function will generate bill body and take item,qty and price as a input
void generateBillBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

// function will generate footer and will take total as an arguement
void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float nettotal = total - dis;
    float cgst = 0.09 * nettotal;
    float grandtotal = nettotal + (cgst + cgst);
    printf("-------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t-------------");
    printf("\nNet Total\t\t\t%.2f", nettotal);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n----------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandtotal);
    printf("\n----------------------------------------\n");
}

int main()
{
float total;
int ch,n;
struct order ord;
struct order ords;

char saveBill='y';
FILE *fpw;
FILE *fpr;

while(1)
{
    // dashboard
    printf("\n===========KAMAT RESTAURANT===========");
    printf("\nPlease Select a Option:\t");
    printf("\n1.Generate Bill\n2.Search Bill\n3.Exit\n");
    scanf("%d", &ch);
    printf("\nYou have chosen %d.\n", ch);
    switch (ch)
    {
    case 1:
        printf("Please enter name of customer:\n");
        scanf("%s",&ord.name);
        // scanf("%s", &ord.name);
        // printf("%s\n",ord.name);

        printf("Please enter number of items:\n");
        scanf("%d",&n);
        ord.num=n;
        //16:00
        for (int i = 0; i < n; i++)
        {
            printf("Please enter your item %d:\n",i+1);
            scanf("%s",&ord.itm[i].item);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;

            printf("Please enter your item quantity:\n");
            scanf("%d",&ord.itm[i].qty);
            
            printf("Please enter the unit price:\n");
            scanf("%f",&ord.itm[i].price);
            total+=(ord.itm[i].qty * ord.itm[i].price);
        }
        
        generateBillHeader(ord.name);
        for (int i = 0; i <ord.num ; i++)
        {
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }

        generateBillFooter(total);

        printf("\nDo you want to save the file(y/n):\n");
        scanf("%s",&saveBill);
        if (saveBill == 'y')
        {
            fpw=fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct order),1,fpw);
            if (fwrite!=0)
            {
                printf("\nSuccessfully Saved.\n");
            }
            else
            {
                printf("\nError Saving.\n");
            }
            fclose(fpw);
        }
        
        break;
    
    case 2:
        fpr=fopen("RestaurantBill.dat","r");
        printf("\n*******Your previous invoices*********\n");
        while (fread(&ord,sizeof(struct order),1,fpr))
        {
            generateBillHeader(ord.name);
            for (int i = 0; i < ord.num; i++)
            {
                generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                total+=ord.itm[i].qty*ord.itm[i].price;

            }
           generateBillFooter(total); 
        }
        fclose(fpr);
        break;

    case 3:
        exit(0);
        break;
    }
}
}