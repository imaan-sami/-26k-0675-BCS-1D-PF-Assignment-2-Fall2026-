#include <stdio.h>
#include <string.h>

void displayMenu()
{
    printf("\n===== University Library =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    printf("Enter name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    printf("Membership type (1 = Student, 2 = Faculty): ");
    scanf("%d", memberType);

    while (*memberType != 1 && *memberType != 2)
    {
        printf("Invalid! Enter 1 for Student or 2 for Faculty: ");
        scanf("%d", memberType);
    }

    printf("Registration successful!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    int i;

    printf("\n%-10s %-30s %-10s\n", "Book ID", "Title", "Available");
    for (i = 0; i < totalBooks; i++)
    {
        printf("%-10d %-30s %-10d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    int id, days, i, index = -1;
    int allowedDays = (memberType == 1) ? 14 : 30;

    if (*borrowedCount >= 3)
    {
        printf("Limit reached! You can borrow only 3 books at a time.\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &id);

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            index = i;
        }
    }

    if (index == -1)
    {
        printf("Invalid book ID.\n");
        return;
    }

    if (availableCopies[index] <= 0)
    {
        printf("Sorry, no copies of \"%s\" are available.\n", bookTitles[index]);
        return;
    }

    printf("Enter number of days you want to keep the book: ");
    scanf("%d", &days);

    while (days <= 0)
    {
        printf("Invalid! Days must be positive. Re-enter: ");
        scanf("%d", &days);
    }

    if (days > allowedDays)
    {
        printf("Note: Allowed period is %d days. Fine applies after that.\n", allowedDays);
    }

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;

    printf("You borrowed \"%s\".\n", bookTitles[index]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id, days, i, borrowedIndex = -1, bookIndex = -1;
    int allowedDays = (memberType == 1) ? 14 : 30;
    int finePerDay = (memberType == 1) ? 20 : 10;
    float fine = 0.0, payable = 0.0;
    char code[20];

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            borrowedIndex = i;
        }
    }

    if (borrowedIndex == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0.0;
    }

    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &days);

    while (days <= 0)
    {
        printf("Invalid! Days must be positive. Re-enter: ");
        scanf("%d", &days);
    }

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            bookIndex = i;
        }
    }
    availableCopies[bookIndex]++;

    for (i = borrowedIndex; i < *borrowedCount - 1; i++)
    {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;

    if (days > allowedDays)
    {
        fine = (days - allowedDays) * finePerDay;
        *totalFine += fine;
        payable = fine;

        printf("Late return! Fine: Rs. %.2f\n", fine);

        printf("Enter membership code: ");
        scanf("%19s", code);

        if (strcmp(code, "LIB2026") == 0)
        {
            payable = fine * 0.5;
            printf("Correct code! 50%% waiver applied.\n");
        }
        else
        {
            printf("Wrong code. No waiver.\n");
        }

        printf("Fine payable for this return: Rs. %.2f\n", payable);
    }
    else
    {
        printf("Book returned on time. No fine.\n");
    }

    return payable;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver)
{
    int i;

    printf("\n--- Member Record ---\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);
    printf("Membership type: %s\n", (memberType == 1) ? "Student" : "Faculty");

    printf("Borrowed books: ");
    if (borrowedCount == 0)
    {
        printf("None");
    }
    for (i = 0; i < borrowedCount; i++)
    {
        printf("%d ", borrowedBookIDs[i]);
    }
    printf("\n");

    printf("Total fine (before waiver): Rs. %.2f\n", totalFine);
    printf("Final fine payable (after waiver): Rs. %.2f\n", fineAfterWaiver);
}

int main()
{
    int bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {
        "C Programming",
        "Data Structures",
        "Database Systems",
        "Operating Systems",
        "Computer Networks"};
    int availableCopies[5] = {3, 2, 1, 2, 1};
    int totalBooks = 5;

    char name[50] = "";
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[3];
    int borrowedCount = 0;
    float totalFine = 0.0, fineAfterWaiver = 0.0;
    int registered = 0;
    int choice;

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (registered)
            {
                printf("A member is already registered.\n");
            }
            else
            {
                registerMember(name, &studentID, &memberType);
                registered = 1;
            }
            break;

        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
            break;

        case 3:
            if (!registered)
            {
                printf("Please register first (option 1).\n");
            }
            else
            {
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                           borrowedBookIDs, &borrowedCount, memberType);
            }
            break;

        case 4:
            if (!registered)
            {
                printf("Please register first (option 1).\n");
            }
            else
            {
                fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
            }
            break;

        case 5:
            if (!registered)
            {
                printf("Please register first (option 1).\n");
            }
            else
            {
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
            }
            break;

        case 6:
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
