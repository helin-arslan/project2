#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define YESOPTION "YES"
#define NOOPTION "NO"
#define USER_COUNT 4

#define UNDIFENED_USER_INDEX -1

int votesCountYES = 0, votesCountNO = 0;

void castVote(void);
void votesCount(void);

struct User {
    char username[15];
    char password[15];
    bool voteRight;
};

int main() {
    struct User users[USER_COUNT];

    struct User firstUser;
    strcpy(firstUser.username, "20201701018");
    strcpy(firstUser.password, "123");
    firstUser.voteRight = true;
    users[0] = firstUser;

    struct User secondUser;
    strcpy(secondUser.username, "20201701055");
    strcpy(secondUser.password, "123");
    secondUser.voteRight = true;
    users[1] = secondUser;

    struct User thirdUser;
    strcpy(thirdUser.username, "20201701062");
    strcpy(thirdUser.password, "123");
    thirdUser.voteRight = true;
    users[2] = thirdUser;

    struct User fourthUser;
    strcpy(fourthUser.username, "20201701003");
    strcpy(fourthUser.password, "123");
    fourthUser.voteRight = true;
    users[3] = fourthUser;

    // for (int i = 0; i < USER_COUNT; i++) {
    //     struct User aUser = users[i];
    //     printf("Username %s \n", aUser.username);
    // }

    int mainMenuChoice;
    do {
        // printf("\n\n ###### Welcome to Voting 2022 #####");
        printf("\n\n 1. Sing In");
        printf("\n 0. Exit");
        printf("\n Please enter your choice : ");
        scanf("%d", &mainMenuChoice);
        switch (mainMenuChoice) {
            case 1: {
                char readUsername[15];
                printf("Enter your username: ");
                scanf("%s", readUsername);

                char readPassword[15];
                printf("Enter your password: ");
                scanf("%s", readPassword);

                int loggedUserIndex = UNDIFENED_USER_INDEX;
                for (int userIndex = 0; userIndex < USER_COUNT; userIndex++) {
                    struct User aUser = users[userIndex];
                    if (strcmp(readUsername, aUser.username) == 0 && strcmp(readPassword, aUser.password) == 0) {
                        loggedUserIndex = userIndex;
                        break;
                    }
                }

                if (loggedUserIndex != UNDIFENED_USER_INDEX) {
                    printf("Login success");
                    printf("\n\n ###### Welcome to Voting 2022 #####");
                    int choice;
                    do {
                        printf("\n\n 1. Cast the Vote");
                        printf("\n 2. Find Vote Count");
                        printf("\n 0. Sign Out");
                        printf("\n Please enter your choice : ");
                        scanf("%d", &choice);
                        switch (choice) {
                            case 1: 
                                if (users[loggedUserIndex].voteRight) {
                                    castVote();
                                    users[loggedUserIndex].voteRight = false;

                                    int enoughVoteCount = (USER_COUNT / 2);
                                    if (votesCountYES > enoughVoteCount || votesCountNO > enoughVoteCount) {
                                        votesCount();
                                        printf("\nResult has been decided!");
                                    }else if (votesCountYES == votesCountNO){
                                        votesCount();
                                        printf("\nThe votecount is equal.");
                                    }
                                } else {
                                    printf("\nYou cannot vote again!");
                                }
                            break;
                            case 2:
                                votesCount(); 
                            break;
                            default: {
                                choice = 0;
                                printf("\nUser signed out.");
                            }
                        }
                    } while (choice != 0 );
                } else {
                    printf("\nLogin failed!");
                }
            }
            break;
            default: {
                mainMenuChoice = 0;
                printf("\nBye!!!");
            }    
            break;
        }
    } while (mainMenuChoice != 0);
    return 0;
}

void castVote() {
    int choice;
    printf("\n\n ### Please choose your Candidate ####\n\n");
    printf("\n 1. %s", YESOPTION);
    printf("\n 2. %s", NOOPTION);
    printf("\nInput your choice (1 or 2) : ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: 
            votesCountYES++;
            printf("\n thanks for vote !!");
        break;
        case 2:
            votesCountNO++;
            printf("\n Thanks for vote !!");
        break;
        default: 
            printf("\n Error: Wrong Choice !! Please retry");
    }
}

void votesCount() {
    printf("\n\n ##### Voting Statics ####");
    printf("\n %s - %d ", YESOPTION, votesCountYES);
    printf("\n %s - %d ", NOOPTION, votesCountNO);
}