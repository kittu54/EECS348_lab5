#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MONTHS 12

void readSales(float sales[], const char *filename);
void printSalesReport(const float sales[]);
void printSalesSummary(const float sales[]);
void printSixMonthMovingAverage(const float sales[]);
void printSalesHighToLow(const float sales[]);
int compare(const void *a, const void *b);

int main() {
    char filename[100];
    printf("Enter the filename containing the sales data: ");
    scanf("%s", filename);

    float sales[MONTHS];
    readSales(sales, filename);
    printf("Monthly sales report for 2022:\n");
    printSalesReport(sales);
    printSalesSummary(sales);
    printSixMonthMovingAverage(sales);
    printSalesHighToLow(sales);
    return 0;
}

void readSales(float sales[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        exit(1); // Exiting the program if the file cannot be opened
    }
    for (int i = 0; i < MONTHS; i++) {
        fscanf(file, "%f", &sales[i]);
    }
    fclose(file);
}

void printSalesReport(const float sales[]) {
    const char *months[MONTHS] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    printf("Month\t\tSales\n");
    for (int i = 0; i < MONTHS; i++) {
        printf("%-9s\t$%.2f\n", months[i], sales[i]);
    }
    printf("\n");
}

void printSalesSummary(const float sales[]) {
    float min = sales[0], max = sales[0], sum = sales[0];
    int minMonth = 0, maxMonth = 0;
    for (int i = 1; i < MONTHS; i++) {
        if (sales[i] < min) {
            min = sales[i];
            minMonth = i;
        }
        if (sales[i] > max) {
            max = sales[i];
            maxMonth = i;
        }
        sum += sales[i];
    }
    const char *months[MONTHS] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    printf("Sales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", min, months[minMonth]);
    printf("Maximum sales: $%.2f (%s)\n", max, months[maxMonth]);
    printf("Average sales: $%.2f\n\n", sum / MONTHS);
}

void printSixMonthMovingAverage(const float sales[]) {
    printf("Six-Month Moving Average Report:\n");
    for (int i = 0; i <= MONTHS - 6; i++) {
        float sum = 0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        printf("%s - %s $%.2f\n", "January", "June", sum / 6);
    }
    printf("\n");
}

void printSalesHighToLow(const float sales[]) {
    float salesCopy[MONTHS];
    memcpy(salesCopy, sales, sizeof(salesCopy));
    qsort(salesCopy, MONTHS, sizeof(float), compare);
    
    printf("Sales Report (Highest to Lowest):\nMonth\t\tSales\n");
    for (int i = 0; i < MONTHS; i++) {
        for (int j = 0; j < MONTHS; j++) {
            if (salesCopy[i] == sales[j]) {
                printf("%-9s\t$%.2f\n", "December", salesCopy[i]);
                break;
            }
        }
    }
}

int compare(const void *a, const void *b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa < fb) - (fa > fb);
}
