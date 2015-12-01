//
// Created by haoruitao on 15-11-27.
//

#include "forth.h"

void program(){
    HashTablePtr H = Initialize(5);
    int identity;
    char name[NameSize];
    printf("***********************************\n"
           "*Welcome to User Management system*\n"
           "***********************************\n"
           "* Please press any key to continue*\n"
           "***********************************\n\n\n");
    getchar();

    identity = IdentityCheck();

    Read(H);

    while(identity != 3) {
        switch (identity) {
            case 1:
                Manager(H);
                break;
            case 2:
                getchar();
                printf("Input your name:\n");
                scanf("%[^\n]", name);
                if(Find(name,NameSize,H) != NULL) {
                    User(Find(name,NameSize,H),H);
                }else{
                    printf("Can't find!!!\n");
                }
                break;
            default:
                printf("Invalid identity!!!\n");
                break;
        }
        identity = IdentityCheck();
    }
    Destroy(H);
}

int IdentityCheck(){
    int identity;

    printf("***********************************\n"
           "*   Please choice your identity   *\n"
           "*          1 is manager           *\n"
           "*          2 is user              *\n"
           "*          3 to end               *\n"
           "***********************************\n");
    printf("your identity:\n");
    if(!scanf("%d",&identity)){
        printf("input error!!!\n");
        exit(1);
    }

    return identity;
}

int Manager(HashTablePtr H){
    int choice;
    printf("***********************************\n"
           "*        Enter your choice        *\n"
           "*        1 to insert a user       *\n"
           "*        2 to delete a user       *\n"
           "*        3 to print Userlist      *\n"
           "*        4 to end                 *\n"
           "***********************************\n");
    printf("your choice:\n");
    if(!scanf("%d",&choice)){
        printf("input error!!!\n");
        exit(1);
    }

    while(choice != 4) {
        switch (choice) {
            case 1:
                Read(H);
                InsertUser(H);
                Write(H);
                break;
            case 2:
                Read(H);
                DeleteUser(H);
                Write(H);
                break;
            case 3:
                Read(H);
                printHash(H);
                break;
            default:
                printf("Invalid choice!!!\n");
                break;
        }
        printf("***********************************\n"
               "*        Enter your choice        *\n"
               "*        1 to insert a user       *\n"
               "*        2 to delete a user       *\n"
               "*        3 to print Userlist      *\n"
               "*        4 to end                 *\n"
               "***********************************\n");
        printf("your choice:\n");
        if(!scanf("%d",&choice)){
            printf("input error!!!\n");
            exit(1);
        }
    }
}

int User(UserNodePtr User,HashTablePtr H){
	int choice;
    int id;
    char name[NameSize];
    LinkNodePtr MFriend,TFriend;
    printf("***********************************\n"
           "*      Enter your choice          *\n"
           "*      1 to view yourself         *\n"
           "*      2 to add a friend          *\n"
           "*      3 to delete a friend       *\n"
           "*      4 to follow somebody       *\n"
           "*      5 to cancel follow         *\n"
           "*      6 to find mutual friend    *\n"
           "*      7 to find twice friend     *\n"
           "*      8 to view somebody         *\n"
           "*      9 to end                   *\n"
           "***********************************\n");
    printf("your choice:\n");
    if(!scanf("%d",&choice)){
        printf("input error!!!\n");
        exit(1);
    }

    while(choice != 9){
        switch(choice){
            case 1:
                printUser(User,H);
                break;
            case 2:
                printf("***********************************\n"
                       "*      Enter your choice          *\n"
                       "*      1 by id                    *\n"
                       "*      2 by name                  *\n"
                       "***********************************\n");
                printf("your choice:\n");
                if(!scanf("%d",&choice)){
                    printf("input error!!!\n");
                    choice = 0;
                }
                switch(choice){
                    case 1:
                        printf("input your friend's id:\n");
                        scanf("%d",&id);
                        if(FindId(id,H) != NULL) {
                            InsertFriends(User->Name, FindId(id, H)->Name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    case 2:
                        printf("input your firend's name:\n");
                        getchar();
                        scanf("%[^\n]",name);
                        if(Find(name,NameSize,H) != NULL) {
                            InsertFriends(User->Name, name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    default:
                        printf("Invalid choice!!!\n");
                        break;
                }
                break;
            case 3:
                printf("***********************************\n"
                       "*      Enter your choice          *\n"
                       "*      1 by id                    *\n"
                       "*      2 by name                  *\n"
                       "***********************************\n");
                printf("your choice:\n");
                if(!scanf("%d",&choice)){
                    printf("input error!!!\n");
                    choice = 0;
                }
                switch(choice){
                    case 1:
                        printf("input your friend's id:\n");
                        scanf("%d",&id);
                        if(FindId(id,H) != NULL) {
                            DeleteFriends(User->Name, FindId(id, H)->Name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    case 2:
                        printf("input your firend's name:\n");
                        getchar();
                        scanf("%[^\n]",name);
                        if(Find(name,NameSize,H) != NULL) {
                            DeleteFriends(User->Name, name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    default:
                        printf("Invalid choice!!!\n");
                        break;
                }
                break;
            case 4:
                printf("***********************************\n"
                       "*      Enter your choice          *\n"
                       "*      1 by id                    *\n"
                       "*      2 by name                  *\n"
                       "***********************************\n");
                printf("your choice:\n");
                if(!scanf("%d",&choice)){
                    printf("input error!!!\n");
                    choice = 0;
                }
                switch(choice){
                    case 1:
                        printf("input your follow's id:\n");
                        scanf("%d",&id);
                        if(FindId(id,H) != NULL) {
                            InsertFollows(User->Name, FindId(id, H)->Name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    case 2:
                        printf("input your follow's name:\n");
                        getchar();
                        scanf("%[^\n]",name);
                        if(Find(name,NameSize,H) != NULL) {
                            InsertFollows(User->Name, name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    default:
                        printf("Invalid choice!!!\n");
                        break;
                }
                break;
            case 5:
                printf("***********************************\n"
                       "*      Enter your choice          *\n"
                       "*      1 by id                    *\n"
                       "*      2 by name                  *\n"
                       "***********************************\n");
                printf("your choice:\n");
                if(!scanf("%d",&choice)){
                    printf("input error!!!\n");
                    choice = 0;
                }
                switch(choice){
                    case 1:
                        printf("input your follow's id:\n");
                        scanf("%d",&id);
                        if(FindId(id,H) != NULL) {
                            DeleteFollows(User->Name, FindId(id, H)->Name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    case 2:
                        printf("input your follow's name:\n");
                        getchar();
                        scanf("%[^\n]",name);
                        if(Find(name,NameSize,H) != NULL) {
                            DeleteFollows(User->Name, name, NameSize, H);
                        }else{
                            printf("Can't find!!!\n");
                        }
                        Write(H);
                        break;
                    default:
                        printf("Invalid choice!!!\n");
                        break;
                }
                break;
            case 6:
                printf("input a name:\n");
                getchar();
                scanf("%[^\n]",name);
                if(Find(name,NameSize,H) != NULL){
                    MFriend = Intersection(User->Name,name,NameSize,H);
                    printList(MFriend,H);
                }else{
                    printf("Can't find!!!\n");
                }
                break;
            case 7:
                printf("input a name:\n");
                getchar();
                scanf("%[^\n]",name);
                if(Find(name,NameSize,H) != NULL){
                    TFriend = Twice(User->Name,name,NameSize,H);
                    printList(TFriend,H);
                }else{
                    printf("Can't find!!!\n");
                }
                break;
            case 8:
                printf("***********************************\n"
                       "*    Please input your choice     *\n"
                       "*          1  friends             *\n"
                       "*          2  follows             *\n"
                       "*          3  fans                *\n"
                       "***********************************\n");
                printf("your choice:\n");
                scanf("%d",&choice);
                switch (choice){
                    case 1:
                        printFriend(User,H);
                        break;
                    case 2:
                        printFollow(User,H);
                        break;
                    case 3:
                        printFan(User,H);
                        break;
                }
                break;
            default:
                printf("Invalid choice!!!\n");
                break;
        }
        printf("***********************************\n"
               "*      Enter your choice          *\n"
               "*      1 to view yourself         *\n"
               "*      2 to add a friend          *\n"
               "*      3 to delete a friend       *\n"
               "*      4 to follow somebody       *\n"
               "*      5 to cancel follow         *\n"
               "*      6 to find mutual           *\n"
               "*      7 to find twice            *\n"
               "*      8 to view somebody         *\n"
               "*      9 to end                   *\n"
               "***********************************\n");
        printf("your choice:\n");
        if(!scanf("%d",&choice)){
            printf("input error!!!\n");
            exit(1);
        }
    }
}
