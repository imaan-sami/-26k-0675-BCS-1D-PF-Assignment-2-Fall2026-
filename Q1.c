#include <stdio.h>
int main()
{
    int row,col;

    printf("Enter number of rows: ");
    scanf("%d", &row);
    
    printf("Enter number of seats per row: ");
    scanf("%d", &col);

    int seating_plan[row][col];
    int i,j;

    for (i=0;i<row;i++){
        for (j=0;j<col;j++){

            printf("Is seat R%d seat no. %d occupied? (0 - No, 1 - Yes) : ",i,j);
            scanf("%d",&seating_plan[i][j]);

        }
    }

    int total_free_seats=0;
    int free_seats_per_row[row]={};

    for (i=0;i<row;i++){
        for (j=0;j<col;j++){

            if(seating_plan[i][j]==0)
            {
                total_free_seats++;
                free_seats_per_row[i]=free_seats_per_row[i]+1;
                
            }
        }
    }
    
    printf("\t");

    for (j=0;j<col;j++)
    {
        printf(" %d ",j);
    }
    printf("\n");

    for (i=0;i<row;i++)
    {   printf("R%d\t",i);
        for (j=0;j<col;j++)
        {
            if (seating_plan[i][j]==0)
            {
                printf(" _ ");

            }
            else
            {   
                printf(" X ");

            }
        }
        printf("\n");
    }

    printf("Total free: %d\n",total_free_seats);
    
    printf("Free seats per row: ");

    for (i=0;i<row;i++)
    {
        printf(" %d ",free_seats_per_row[i]);    
    }

    int k;
    printf("Enter the number of people who wants to sit together: ");
    scanf("%d",&k);

    




    return 0;
}