#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define YESOPTION "YES"
#define NOOPTION "NO"
#define ABSOPTION "Abstention"

enum Vote { YES, NO, ABS, UNDEFINED = -1 };

#define USER_COUNT 4 
// USER_COUNT: Shows the number of people we have identified.
#define UNDIFENED_USER_INDEX -1
// The information of our users is registered in the index and it ensures that a user other than these users cannot log in when they want to log in to the system. 
// We showed the unregistered user with -1 because the index starts from 0.
// It shows that the user logged into the system is not defined to the system.
// int votesCountYES = 0, votesCountNO = 0, votesCountAbs = 0;
// The purpose of this function is to increase the votes cast. It increases the "yes" or "no" option according to the selection made.
void castVote(int);
// This function shows all the votes cast to the users.
void votesCount(void);
void changePassword(void);
void changeVote(void);
int countVote(enum Vote vote);


struct User {
    char username[15];
    char password[15];
    enum Vote vote;
    // We set the voting right of the user with the bool type. It gets "true" if it has voting rights, "false" otherwise.
    bool voteRight;
};

// struct User users[USER_COUNT];
struct User* users;

void createInitialUsers() {
    users = malloc(sizeof(struct User) * USER_COUNT);

    struct User firstUser;
    strcpy(firstUser.username, "20201701018");
    strcpy(firstUser.password, "123");
    firstUser.vote = UNDEFINED;
    firstUser.voteRight = true;
    users[0] = firstUser;

    struct User secondUser;
    strcpy(secondUser.username, "20201701055");
    strcpy(secondUser.password, "123");
    secondUser.vote = UNDEFINED;
    secondUser.voteRight = true;
    users[1] = secondUser;

    struct User thirdUser;
    strcpy(thirdUser.username, "20201701062");
    strcpy(thirdUser.password, "123");
    thirdUser.vote = UNDEFINED;
    thirdUser.voteRight = true;
    users[2] = thirdUser;

    struct User fourthUser;
    strcpy(fourthUser.username, "20201701003");
    strcpy(fourthUser.password, "123");
    fourthUser.vote = UNDEFINED;
    fourthUser.voteRight = true;
    users[3] = fourthUser;
}

void populateUserFromFile() {
    FILE* data;
    if ((data = fopen("users.bin", "rb")) == NULL) {
        printf("Populating initial users\n");
        createInitialUsers();
    }
    else {
        users = malloc(sizeof(struct User) * USER_COUNT);
        fread(users, sizeof(struct User), USER_COUNT, data);
    }
}

void saveUsersToFile() {
    FILE* data;
    if ((data = fopen("users.bin", "wb")) != NULL) {

        fwrite(users, sizeof(struct User), USER_COUNT, data);
        fclose(data);
    }
    else {
        printf("Error opening file\n");
    }
}

int main() {

    populateUserFromFile();

    int mainMenuChoice;
    // With do-while, we run the code and get input from the user. Then the loop continues until the condition in the while is satisfied.
    do {
        printf("\n\n ###### Welcome to Voting 2022 #####");
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
            // Each index is assigned a user. We also used the "for" loop to call them. 
            // Here we check the input we received earlier. 
            // If the entered value matches one of the users in the directory we assigned, the login is successful (we used the "strcmp" function to do this comparison).
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
                // With do-while, if the user logs in successfully, it will show the user options to vote, see the voting status.
                do {

                    printf("\n\n 1. Cast the Vote");
                    printf("\n 2. Find Vote Count");
                    printf("\n 3. Change the Password");
                    printf("\n 4. Change your Vote");
                    printf("\n 0. Sign Out");
                    printf("\n Please enter your choice : ");
                    scanf("%d", &choice);
                    switch (choice) {
                    case 1:
                        // The purpose of this function is to increase the votes cast. It increases the "yes" or "no" option according to the selection made.
                        // The purpose of using the if statement is to check "if" the user has voting rights. 
                        // If there is a right to vote and the person votes, the right to vote becomes "false".
                        // When it becomes "false", user cannot use vote.
                        if (users[loggedUserIndex].voteRight) {
                            users[loggedUserIndex].voteRight = false;
                            castVote(loggedUserIndex);
                        }
                        else {
                            printf("\nYou cannot vote again!");
                        }
                        break;
                    case 2:
                        votesCount();
                        break;
                    case 3: {
                        char newPassword[15];
                        printf("\n Please enter the new password: ");
                        scanf("%s", newPassword);
                        strcpy(users[loggedUserIndex].password, newPassword);
                        printf("\n ##Your password successfuly changed.##");
                    }
                          break;
                    case 4:
                        if (users[loggedUserIndex].voteRight) {
                            printf("\n## First you have to vote! ##");
                        }
                        else {
                            castVote(loggedUserIndex);
                        }
                        break;
                    default: {
                        choice = 0;
                        printf("\n ## User signed out. ##");
                    }
                    }
                } while (choice != 0);
            }
            else {
                printf("\n## Login failed! ##");
            }
        }
              break;
        default: {
            mainMenuChoice = 0;
            printf("\nBye!!!");
        }
               break;
        }
        // It allows the other user to log in to the system when the logged in user leaves the system. In this way, the cycle continues.    
    } while (mainMenuChoice != 0);

    saveUsersToFile();
    return 0;
}

void castVote(int loggedUserIndex) {
    int choice;
    printf("\n\n ### Please choose your Candidate ####\n\n");
    printf("\n 1. %s", YESOPTION);
    printf("\n 2. %s", NOOPTION);
    printf("\n 3. %s", ABSOPTION);
    printf("\nInput your choice (1, 2 or 3) : ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        users[loggedUserIndex].vote = YES;
        printf("\n ## Thanks for vote !! ##");
        break;
    case 2:
        users[loggedUserIndex].vote = NO;
        printf("\n ## Thanks for vote !! ##");
        break;
    case 3:
        users[loggedUserIndex].vote = ABS;
        printf("\n ## Thanks for vote !! ##");
        break;
    default:
        printf("\n ## Error: Wrong Choice !! Please retry ##");
    }

    int votesCountYES = countVote(YES);
    int votesCountNO = countVote(NO);
    int votesCountAbs = countVote(ABS);


    int enoughVoteCount = (USER_COUNT / 2);
    // When the majority of votes is achieved in the voting, it determines the voting result.
    if (votesCountYES > enoughVoteCount || votesCountYES == enoughVoteCount && votesCountAbs == votesCountNO) {
        votesCount();
        printf(" \n\n ## 'YES' WON BY %d VOTES. ## \n", votesCountYES);
    }
    else if (votesCountNO > enoughVoteCount || votesCountNO == enoughVoteCount && votesCountAbs == votesCountYES) {
        votesCount();
        printf(" \n\n ## 'NO' WON BY %d VOTES. ## \n", votesCountNO);
    }
    else if (votesCountAbs > votesCountYES && votesCountAbs > votesCountNO && votesCountAbs == enoughVoteCount) {
        printf(" \n\n ## THERE IS NO WINNER. ## \n");
        votesCount();
    }
}

int countVote(enum Vote vote) {
    int countOfVotes = 0;
    for (int userIndex = 0; userIndex < USER_COUNT; userIndex++) {
        struct User aUser = users[userIndex];
        if (aUser.vote == vote) {
            countOfVotes++;
        }
    }
    return countOfVotes;
}

void votesCount() {
    printf("\n\n ##### Voting Statics ####");
    printf("\n YES - %d ", countVote(YES));
    printf("\n NO - %d ", countVote(NO));
    printf("\n ABS - %d ", countVote(ABS));
}
