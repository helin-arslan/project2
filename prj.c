#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define YESOPTION "YES"
#define NOOPTION "NO"
#define USER_COUNT 4 
// USER_COUNT: Shows the number of people we have identified.

#define UNDIFENED_USER_INDEX -1
// The information of our users is registered in the index and it ensures that a user other than these users cannot log in when they want to log in to the system. 
// We showed the unregistered user with -1 because the index starts from 0.
// It shows that the user logged into the system is not defined to the system.

int votesCountYES = 0, votesCountNO = 0;

void castVote(void);
// The purpose of this function is to increase the votes cast. It increases the "yes" or "no" option according to the selection made.

void votesCount(void);   
 // This function shows all the votes cast to the users.

struct User {
    char username[15];
    char password[15];
    bool voteRight;
    // We set the voting right of the user with the bool type. It gets "true" if it has voting rights, "false" otherwise.
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
                        printf("\n 0. Sign Out");
                        printf("\n Please enter your choice : ");
                        scanf("%d", &choice);
                        switch (choice) {
                            case 1: 
                                // The purpose of using the if statement is to check "if" the user has voting rights. 
                                // If there is a right to vote and the person votes, the right to vote becomes "false".
                                // When it becomes "false", user cannot use vote.
                                if (users[loggedUserIndex].voteRight) {
                                    castVote();
                                    users[loggedUserIndex].voteRight = false; 

                                    int enoughVoteCount = (USER_COUNT / 2);
                                    // When the majority of votes is achieved in the voting, it determines the voting result.
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
    // It allows the other user to log in to the system when the logged in user leaves the system. In this way, the cycle continues.    
    } while (mainMenuChoice != 0);
    return 0;
}

void castVote() {
    // The purpose of this function is to increase the votes cast. It increases the "yes" or "no" option according to the selection made.

    int choice;
    printf("\n\n ### Please choose your Candidate ####\n\n");
    printf("\n 1. %s", YESOPTION);
    printf("\n 2. %s", NOOPTION);
    printf("\nInput your choice (1 or 2) : ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: 
        // Here we increment the votesCountYES and votesCountNO that we defined above.
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
    // This function shows all the votes cast to the users.
    printf("\n\n ##### Voting Statics ####");
    printf("\n %s - %d ", YESOPTION, votesCountYES);
    printf("\n %s - %d ", NOOPTION, votesCountNO);
}
