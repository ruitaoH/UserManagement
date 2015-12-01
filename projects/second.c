//
// Created by haoruitao on 15-11-24.
//

#include "second.h"

/*交集*/
LinkNodePtr Intersection(char name1[],char name2[],int namesize,HashTablePtr H){
    UserNodePtr user1,user2;
    LinkNodePtr friend1,friend2;
    LinkNodePtr follow1,follow2;
    LinkNodePtr fan1,fan2;
    LinkNodePtr temp,newCell;
    LinkNodePtr iList;

    iList = malloc(sizeof(LinkNode));
    if(iList == NULL){
        printf("Out of space!!!\n");
        exit(1);
    }
    SetLinkNext(NULL,iList);

    user1 = Find(name1,namesize,H);
    user2 = Find(name2,namesize,H);
    if(user1 == NULL || user2 == NULL){
        printf("Can't find\n");
        return NULL;
    }

    int choice;
    printf("***********************************\n"
           "*    Please input your choice     *\n"
           "*          1  friends             *\n"
           "*          2  follows             *\n"
           "*          3  fans                *\n"
           "***********************************\n");
    printf("your choice:\n");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            friend1 = GetLinkNext(GetUserFriend(user1));
            friend2 = GetLinkNext(GetUserFriend(user2));
            if(friend1 == NULL || friend2 == NULL){
                printf("%s or %s didn't have friends\n",name1,name2);
                return iList;
            }

            for(;friend1 != NULL;friend1 = GetLinkNext(friend1)){
                for(friend2 = GetLinkNext(GetUserFriend(user2));friend2 != NULL;friend2 = GetLinkNext(friend2)){
                    if(GetLinkId(friend1) == GetLinkId(friend2)){
                        newCell = malloc(sizeof(LinkNode));
                        if(newCell == NULL){
                            printf("Out of space!!!\n");
                            exit(1);
                        }
                        *newCell = *friend1;

                        temp = FindLastPre(iList);
                        SetLinkNext(newCell,temp);
                        SetLinkNext(NULL,newCell);
                        break;
                    }
                }
            }
            break;
        case 2:
            follow1 = GetLinkNext(GetUserFollow(user1));
            follow2 = GetLinkNext(GetUserFollow(user2));
            if(follow1 == NULL || follow2 == NULL){
                printf("%s or %s didn't have follows\n",name1,name2);
                return iList;
            }

            for(;follow1 != NULL;follow1 = GetLinkNext(follow1)){
                for(follow2 = GetLinkNext(GetUserFollow(user2));follow2 != NULL;follow2 = GetLinkNext(follow2)){
                    if(GetLinkId(follow1) == GetLinkId(follow2)){
                        newCell = malloc(sizeof(LinkNode));
                        if(newCell == NULL){
                            printf("Out of space!!!\n");
                            exit(1);
                        }
                        *newCell = *follow1;

                        temp = FindLastPre(iList);
                        SetLinkNext(newCell,temp);
                        SetLinkNext(NULL,newCell);
                        break;
                    }
                }
            }
            break;
        case 3:
            fan1 = GetLinkNext(GetUserFan(user1));
            fan2 = GetLinkNext(GetUserFan(user2));
            if(fan1 == NULL || fan2 == NULL){
                printf("%s or %s didn't have fans\n",name1,name2);
                return iList;
            }

            for(;fan1 != NULL;fan1 = GetLinkNext(fan1)){
                for(fan2 = GetLinkNext(GetUserFan(user2));fan2 != NULL;fan2 = GetLinkNext(fan2)){
                    if(GetLinkId(fan1) == GetLinkId(fan2)){
                        newCell = malloc(sizeof(LinkNode));
                        if(newCell == NULL){
                            printf("Out of space!!!\n");
                            exit(1);
                        }
                        *newCell = *fan1;

                        temp = FindLastPre(iList);
                        SetLinkNext(newCell,temp);
                        SetLinkNext(NULL,newCell);
                        break;
                    }
                }
            }
            break;
    }

    return iList;
}

/*name1是本人 name2是好友 返回name2好友列表中name1所没有的*/
LinkNodePtr  Twice(char name1[],char name2[],int namesize,HashTablePtr H){
    UserNodePtr user1, user2;
    LinkNodePtr friend1, friend2;
    LinkNodePtr follow1, follow2;
    LinkNodePtr fan1, fan2;
    LinkNodePtr temp, newCell;
    LinkNodePtr dList;

    dList = malloc(sizeof(LinkNode));
    if (dList == NULL) {
        printf("Out of space!!!\n");
        exit(1);
    }
    SetLinkNext(NULL, dList);

    user1 = Find(name1, namesize, H);
    user2 = Find(name2, namesize, H);
    if (user1 == NULL || user2 == NULL) {
        printf("Can't find\n");
        return NULL;
    }

    int choice;
    printf("***********************************\n"
           "*    Please input your choice     *\n"
           "*          1  friends             *\n"
           "*          2  follows             *\n"
           "*          3  fans                *\n"
           "***********************************\n");
    printf("your choice:\n");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            friend1 = GetLinkNext(GetUserFriend(user1));
            friend2 = GetLinkNext(GetUserFriend(user2));
            if (friend1 == NULL || friend2 == NULL) {
                printf("%s or %s didn't have friends\n", name1, name2);
                return dList;
            }

            for (friend2 = GetLinkNext(GetUserFriend(user2)); friend2 != NULL; friend2 = GetLinkNext(friend2)) {
                for (friend1 = GetLinkNext(GetUserFriend(user1)); friend1 != NULL; friend1 = GetLinkNext(friend1)) {
                    if (GetLinkId(friend2) == GetLinkId(friend1))
                        break;
                }
                if (friend1 == NULL) {
                    newCell = malloc(sizeof(LinkNode));
                    if (newCell == NULL) {
                        printf("Out of space!!!\n");
                        exit(1);
                    }
                    *newCell = *friend2;

                    temp = FindLastPre(dList);
                    SetLinkNext(newCell, temp);
                    SetLinkNext(NULL, newCell);
                }
            }
            break;
        case 2:
            follow1 = GetLinkNext(GetUserFollow(user1));
            follow2 = GetLinkNext(GetUserFollow(user2));
            if (follow1 == NULL || follow2 == NULL) {
                printf("%s or %s didn't have friends\n", name1, name2);
                return dList;
            }

            for (follow2 = GetLinkNext(GetUserFollow(user2)); follow2 != NULL; follow2 = GetLinkNext(follow2)) {
                for (follow1 = GetLinkNext(GetUserFollow(user1)); follow1 != NULL; follow1 = GetLinkNext(follow1)) {
                    if (GetLinkId(follow2) == GetLinkId(follow1))
                        break;
                }
                if (follow1 == NULL) {
                    newCell = malloc(sizeof(LinkNode));
                    if (newCell == NULL) {
                        printf("Out of space!!!\n");
                        exit(1);
                    }
                    *newCell = *follow2;

                    temp = FindLastPre(dList);
                    SetLinkNext(newCell, temp);
                    SetLinkNext(NULL, newCell);
                }
            }
            break;
        case 3:
            fan1 = GetLinkNext(GetUserFan(user1));
            fan2 = GetLinkNext(GetUserFan(user2));
            if (fan1 == NULL || fan2 == NULL) {
                printf("%s or %s didn't have friends\n", name1, name2);
                return dList;
            }

            for (fan2 = GetLinkNext(GetUserFan(user2)); fan2 != NULL; fan2 = GetLinkNext(fan2)) {
                for (fan1 = GetLinkNext(GetUserFan(user1)); fan1 != NULL; fan1 = GetLinkNext(fan1)) {
                    if (GetLinkId(fan2) == GetLinkId(fan1))
                        break;
                }
                if (fan1 == NULL) {
                    newCell = malloc(sizeof(LinkNode));
                    if (newCell == NULL) {
                        printf("Out of space!!!\n");
                        exit(1);
                    }
                    *newCell = *fan2;

                    temp = FindLastPre(dList);
                    SetLinkNext(newCell, temp);
                    SetLinkNext(NULL, newCell);
                }
            }
            break;
    }

    return dList;
}

void InsertUser(HashTablePtr H){
    getchar();
    char name[NameSize];
    int id = FindMaxId(H) + 1;

    printf("***********************************\n"
           "*    Please input your name       *\n"
           "***********************************\n");
    scanf("%[^\n]",name);

    Insert(id,name,NameSize,H);
}

void DeleteUser(HashTablePtr H){
    getchar();
    char name[NameSize];

    printf("***********************************\n"
           "*    Please input the name        *\n"
           "*   which you want to delete      *\n"
           "***********************************\n");
    scanf("%[^\n]",name);

    Delete(name,NameSize,H);
}
