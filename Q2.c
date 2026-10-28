#include <stdio.h>


int sum_proper_divisor(int num) {
    int i, sum = 0; 
    
    for (i = 1; i <= num / 2; i++) {
       
        if (num % i == 0) { 
            sum = sum + i;
        }
    }
    return sum;
}

int main() {
    int n, i, sum1, sum2; 
    int pairs_count = 0;

    printf("Enter number: ");
    scanf("%d", &n);

  
    while (n < 2) {
        printf("Invalid input. Enter number greater than or equal to 2: ");
        scanf("%d", &n);
    }

    printf("Amicable pairs:\n");

   
    for (i = 1; i <= n; i++) {
        sum1 = sum_proper_divisor(i);
        sum2 = sum_proper_divisor(sum1);

     
        if (i == sum2 && sum1 <= n) {
            
           
            if (i < sum1) { 
                printf("(%d, %d)\n", i, sum1);
                pairs_count++; 
            }
        }
    }

    
    if (pairs_count > 0) {
        printf("\nTotal amicable pairs found: %d\n", pairs_count);
    } else {
        printf("\nNo amicable pairs found up to %d.\n", n);
    }

    return 0;
}
