#include<stdio.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
# define max 10

struct Expenses{
    char category[100];
    float expense;
};
// structure banaya hai expenses karke because har ek expense me 2 trh ka data store hoga uska naam aur paise kharch kitna hua hai

void printbar(FILE *fp, float expense);
// function definition for creating bargraph

void printbar(FILE *fp, float expense){
    int i, bars;
    bars = (int)(expense/500);
    for(i=0;i<bars;i++){
        fprintf(fp, "🟩");
    }
    fprintf(fp, "(%.2f)\n", expense);
}

int main(){
    setlocale(LC_ALL, "");      // to enable UTF-8 characters

    struct Expenses exp[max];
    float budget;
    float total=0;
    int i, n;

    printf("=============================== MONTHLY EXPENSE TRACKER ===================================\n\n");
    printf("Enter your monthly budget: ");
    scanf("%f", &budget);

    while (getchar() != '\n');

    printf("\nEnter the number of categories of your expenses: ");
    scanf("%d",&n);
    getchar();
    for(i=0; i<n; i++){

        printf("\nEnter the category and amount: \n");
        scanf("\n%[^\n] %f", exp[i].category, &exp[i].expense);

        while(getchar() != '\n');
        total += exp[i].expense;
    }
    printf("\n----------------------------------- MONTHLY EXPENSE REPORT --------------------------------------\n\n");
    for(i=0;i<n;i++){
        printf("\n\t%s : %.2f\n",exp[i].category, exp[i].expense);
    }

    printf("\n-----------------------------------------------------------------\n");
    printf("\nTotal Expense: %.2f", total);
    printf("\nMonthly Income: %.2f", budget);

    if(budget>total){
        wprintf(L"\u2705");
        printf(" \nYou did a SAVING of %.2f this month!\n", budget-total);
    }
    if(budget<total){
        wprintf(L"\u274C");
        printf(" \nYou did OVERSPENDING of %.2f this month!\n", total-budget);
    }
    if(budget==total){
        wprintf(L"\u2696");
        printf(" \nEXACTLY UNDER BUDGET! No saving this month!\n");
    }


    // File management

    FILE *fp;
    fp = fopen("expenses.txt", "a");
    if(fp == NULL){
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "\n============================== MONTHLY EXPENSE TRACKER =============================\n\n");
    for(i=0;i<n;i++){
        fprintf(fp, "\n\t%s : %.2f\n",exp[i].category, exp[i].expense);
    }
    fprintf(fp, "\n------------------------------------------------------------------------------");
    fprintf(fp, "\nTotal Expense: %.2f", total);
    fprintf(fp, "\nMonthly Income: %.2f", budget);
    fprintf(fp, "\n------------------------------------------------------------------------------");

     if(budget>total){
        // fwprintf(fp, L"\u2705");
        fprintf(fp, "\n ✅You did a SAVING of %.2f this month!", budget-total);
    }
    if(budget<total){
        // fwprintf(fp, L"\u274C");
        fprintf(fp, "\n❌ You did OVERSPENDING of %.2f this month!", total-budget);
    }
    if(budget==total){
        // fwprintf(fp, L"\u2696");
        fprintf(fp, "\n⚖️ EXACTLY UNDER BUDGET! No saving this month!");
    }

    // Print expense Graph
    fprintf(fp, "\n ==================================== MONTHLY EXPENSE GRAPH ==================================\n");
    for(i=0; i<n; i++){
        fprintf(fp, "%s\t" ,exp[i].category);
        printbar(fp, exp[i].expense);
    }
    
    fclose(fp);
    printf("Report saved in expenses.txt \n");
    return 0;
}

