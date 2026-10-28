#include <stdio.h>

int getValidDays()
{
    int fest_days;

    printf("Enter number of festival days (1-7): ");
    scanf("%d", &fest_days);

    while (fest_days > 7 || fest_days < 1)
    {
        printf("Invalid! Re-Enter number of festival days (1-7): ");
        scanf("%d", &fest_days);
    }

    return fest_days;
}

float calculateDailySales(int dayNumber)
{
    int i, order_num;
    float order_amount, total = 0.0, highest = 0.0;

    printf("\n--- Day %d ---\n", dayNumber);
    printf("Enter number of orders: ");
    scanf("%d", &order_num);

    while (order_num < 1)
    {
        printf("Invalid! Re-Enter number of orders: ");
        scanf("%d", &order_num);
    }

    for (i = 0; i < order_num; i++)
    {
        printf("Enter amount of order %d: Rs. ", i + 1);
        scanf("%f", &order_amount);

        while (order_amount <= 0)
        {
            printf("Invalid! Re-Enter amount of order %d: Rs. ", i + 1);
            scanf("%f", &order_amount);
        }

        total = total + order_amount;

        if (order_amount > highest)
        {
            highest = order_amount;
        }
    }

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", total / order_num);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i;
    float highest = dailySales[0];
    int highest_index = 0;

    for (i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > highest)
        {
            highest = dailySales[i];
            highest_index = i;
        }
    }

    return highest_index + 1;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, stars;

    printf("\n--- Daily Sales Bar Chart (1 * = Rs. 100) ---\n");
    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);

        printf("Day %d: ", i + 1);

        for (j = 0; j < stars; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

int main()
{
    float dailySales[7];
    float festivalTotal = 0;
    int days, i, bestDay;

    days = getValidDays();

    for (i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    bestDay = findHighestSalesDay(dailySales, days);

    printf("\n=== Festival Summary ===\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", bestDay);

    displayBarChart(dailySales, days);

    return 0;
}