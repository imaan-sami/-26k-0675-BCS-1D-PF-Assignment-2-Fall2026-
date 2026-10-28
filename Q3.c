#include <stdio.h>


void input(int sensor_count, int hours, int reading[sensor_count][hours]) {
    int i, j;

    for (i = 0; i < sensor_count; i++) {
        for (j = 0; j < hours; j++) {
            printf("Enter reading of sensor %d at hour %d : ", i + 1, j + 1);
            scanf("%d", &reading[i][j]);
        }
    }
}

double sensor_analysis(int sensor_no, int hours, int row[]) {
    int j;
    int total = 0;
    int max = row[0];
    int min = row[0];
    int critical = 0;
    int warning = 0;
    int streak = 0;
    int longest = 0;
    double average;

    for (j = 0; j < hours; j++) {
        total = total + row[j];

        if (row[j] > max) {
            max = row[j];
        }

        if (row[j] < min) {
            min = row[j];
        }

        if (row[j] >= 40) {
            critical++;
        }

        if (row[j] >= 35 && row[j] <= 39) {
            warning++;
        }

        if (row[j] >= 35) {
            streak++;
            if (streak > longest) {
                longest = streak;
            }
        }
        else {
            streak = 0;
        }
    }

    average = (double)total / hours;

    printf("\n--- Report of Sensor %d ---\n", sensor_no);
    printf("Total = %d\n", total);
    printf("Average = %.2f\n", average);
    printf("Highest = %d\n", max);
    printf("Lowest = %d\n", min);
    printf("Critical readings = %d\n", critical);
    printf("Warning readings = %d\n", warning);
    printf("Longest streak = %d hours\n", longest);

    return average;
}

int highest_average(int sensor_count, double avg[]) {
    int i;
    int best = 0;

    for (i = 1; i < sensor_count; i++) {
        if (avg[i] > avg[best]) {
            best = i;
        }
    }

    return best + 1;
}

int main() {
    int sensor_count, hours;
    int i, best;

    printf("Enter sensor number : ");
    scanf("%d", &sensor_count);

    printf("How many hours do you want to record the temperature reading : ");
    scanf("%d", &hours);

    int reading[sensor_count][hours];
    double avg[sensor_count];

    input(sensor_count, hours, reading);

    for (i = 0; i < sensor_count; i++) {
        avg[i] = sensor_analysis(i + 1, hours, reading[i]);
    }

    best = highest_average(sensor_count, avg);

    printf("\n=== Final Report ===\n");
    printf("Sensor %d has the highest average = %.2f\n", best, avg[best - 1]);

    return 0;
}