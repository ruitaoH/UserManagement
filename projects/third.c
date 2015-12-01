//
// Created by haoruitao on 15-11-24.
//

#include "third.h"

void Write(HashTablePtr H){
    UserNodePtr Users;
    LinkNodePtr Follows,Friends,Fans;
    cJSON *objArr,*root,*arrayFri,*arrayFol,*arrayFan;
    FILE *file;
    int i,max = FindMaxId(H);
    char *c;

    objArr = cJSON_CreateArray();

    for(i = 1;i <= max;i++){
        root = cJSON_CreateObject();
        arrayFol = cJSON_CreateArray();
        arrayFri = cJSON_CreateArray();
        arrayFan = cJSON_CreateArray();

        if((Users = FindId(i,H)) != NULL){

            Follows = GetLinkNext(GetUserFollow(Users));
            Friends = GetLinkNext(GetUserFriend(Users));
            Fans = GetLinkNext(GetUserFan(Users));

            cJSON_AddNumberToObject(root, "id", GetUserId(Users));
            cJSON_AddStringToObject(root, "name", GetUserName(Users));

            while (Follows != NULL) {
                cJSON_AddNumberToObject(arrayFol, "folid", GetLinkId(Follows));

                Follows = GetLinkNext(Follows);
            }
            cJSON_AddItemToObject(root,"Followings",arrayFol);

            while (Friends != NULL) {
                cJSON_AddNumberToObject(arrayFri, "friid", GetLinkId(Friends));

                Friends = GetLinkNext(Friends);
            }
            cJSON_AddItemToObject(root,"Friends",arrayFri);

            while(Fans != NULL){
                cJSON_AddNumberToObject(arrayFan, "fanid", GetLinkId(Fans));

                Fans = GetLinkNext(Fans);
            }
            cJSON_AddItemToObject(root,"Fans",arrayFan);

            cJSON_AddItemToArray(objArr,root);
        }
    }
    c = cJSON_Print(objArr);

    cJSON_Delete(objArr);

    if((file = fopen("/home/haoruitao/projects/users.txt","w")) == NULL){
        printf("Can't open\n");
    }else {
        fprintf(file,"%s",c);
        fclose(file);
    }
}

void Read(HashTablePtr H){
    MakeEmpty(H);
    cJSON *objArr,*root,*arrayFol,*arrayFri;
    cJSON *UserId,*UserName,*FolId,*FriId;
    FILE *file;
    int i = 0,size;
    char *fol,*fri;

    if((file = fopen("/home/haoruitao/projects/users.txt","r")) == NULL){
        printf("Can't open\n");
        return ;
    }else{
        while(!feof(file)){
            fgetc(file);
            i++;
        }
        fclose(file);
    }
    char c[i];
    i = 0;
    if((file = fopen("/home/haoruitao/projects/users.txt","r")) == NULL){
        printf("Can't open\n");
        return ;
    }else{
        while(!feof(file)){
            c[i] = fgetc(file);
            i++;
        }
    }
    c[i - 1] = '\0';
    if(c[0] != '\0') {
        objArr = cJSON_Parse(c);
        size = cJSON_GetArraySize(objArr);

        for (i = 0; i < size; i++) {
            root = cJSON_GetArrayItem(objArr, i);

            if (root) {
                UserId = cJSON_GetObjectItem(root, "id");
                UserName = cJSON_GetObjectItem(root, "name");
                Insert(UserId->valueint, UserName->valuestring, NameSize, H);
            }
        }
        for (i = 0; i < size; i++) {
            root = cJSON_GetArrayItem(objArr, i);

            if (root) {
                UserName = cJSON_GetObjectItem(root, "name");
                //解析arrayFol
                fol = cJSON_Print(cJSON_GetObjectItem(root, "Followings"));
                arrayFol = cJSON_Parse(fol);
                FolId = arrayFol->child;
                while (FolId != NULL) {
                    InsertFollows(UserName->valuestring, GetUserName(FindId(FolId->valueint, H)), NameSize, H);

                    FolId = FolId->next;
                }

                //解析arrayFri
                fri = cJSON_Print(cJSON_GetObjectItem(root, "Friends"));
                arrayFri = cJSON_Parse(fri);
                FriId = arrayFri->child;
                while (FriId != NULL) {
                    InsertFriends(UserName->valuestring, GetUserName(FindId(FriId->valueint, H)), NameSize, H);

                    FriId = FriId->next;
                }
            }
        }
        cJSON_Delete(objArr);
    }
}

/*name1是本人 name2是要添加好友的名字*/
void InsertFriends(char name1[],char name2[],int namesize,HashTablePtr H){
    LinkNodePtr check;
    UserNodePtr User1,User2;
    LinkNodePtr  temp,newFriend;

    User1 = Find(name1,namesize,H);
    User2 = Find(name2,namesize,H);
    if(User1 == NULL || User2 == NULL) {
        printf("Can't find\n");
        return;
    }

    check = GetLinkNext(GetUserFriend(User1));
    while(check != NULL){
        if(GetLinkId(check) == GetUserId(User2))
            break;

        check = GetLinkNext(check);
    }

    if(check == NULL) {
        newFriend = malloc(sizeof(LinkNode));
        if (newFriend == NULL) {
            printf("Out of space!!!\n");
            exit(1);
        }
        SetLinkId(GetUserId(User2),newFriend);

        temp = FindLastPre(GetUserFriend(User1));
        SetLinkNext(newFriend,temp);
        SetLinkNext(NULL,newFriend);
    }else{
        printf("%s had been insert\n",GetUserName(User2));
    }
}

/*name1是本人 name2是要删除的好友的名字*/
void DeleteFriends(char name1[],char name2[],int namesize,HashTablePtr H){
    UserNodePtr User1,User2;
    LinkNodePtr temp,tempPre;

    User1 = Find(name1,namesize,H);
    User2 = Find(name2,namesize,H);
    if(User1 == NULL || User2 == NULL){
        printf("Can't find\n");
        return ;
    }

    temp = GetUserFriend(User1);
    while(GetLinkNext(temp) != NULL && GetLinkId(GetLinkNext(temp)) != GetUserId(User2))
        temp = GetLinkNext(temp);
    if(GetLinkNext(temp) == NULL){
        printf("%s didn't have a friend named %s\n",name1,name2);
    }else{
        tempPre = temp;
        temp = GetLinkNext(temp);
        SetLinkNext(GetLinkNext(temp),tempPre);
        free(temp);
    }
}

/*name1是本人 name2是要添加关注的对象*/
void InsertFollows(char name1[],char name2[],int namesize,HashTablePtr H){
    LinkNodePtr check;
    UserNodePtr User1,User2;
    LinkNodePtr temp,newFollow;
    LinkNodePtr newFan;

    User1 = Find(name1,namesize,H);
    User2 = Find(name2,namesize,H);
    if(User1 == NULL || User2 == NULL){
        printf("Can't find\n");
        return ;
    }

    check = GetLinkNext(GetUserFollow(User1));
    while(check != NULL){
        if(GetLinkId(check) == GetUserId(User2))
            break;

        check = GetLinkNext(check);
    }

    if(check == NULL) {
        /*在name1用户中添加关注name2*/
        newFollow = malloc(sizeof(LinkNode));
        if (newFollow == NULL) {
            printf("Out of space!!!\n");
            exit(1);
        }
        SetLinkId(GetUserId(User2),newFollow);

        temp = FindLastPre(GetUserFollow(User1));
        SetLinkNext(newFollow,temp);
        SetLinkNext(NULL,newFollow);

        /*在name2用户中添加粉丝name1*/
        newFan = malloc(sizeof(LinkNode));
        if (newFan == NULL) {
            printf("Out of space!!1\n");
            exit(1);
        }
        SetLinkId(GetUserId(User1),newFan);

        temp = FindLastPre(GetUserFan(User2));
        SetLinkNext(newFan,temp);
        SetLinkNext(NULL,newFan);
    }else{
        printf("%s had been followed\n",GetUserName(User2));
    }
}

/*name1是本人 name2是要删除关注的对象*/
void DeleteFollows(char name1[],char name2[],int namesize,HashTablePtr H){
    UserNodePtr User1,User2;
    LinkNodePtr temp,tempPre;

    User1 = Find(name1,namesize,H);
    User2 = Find(name2,namesize,H);
    if(User1 == NULL || User2 == NULL){
        printf("Can't find\n");
        exit(1);
    }

    /*在name1中删除所关注的name2*/
    temp = GetUserFollow(User1);
    while(GetLinkNext(temp) != NULL && GetLinkId(GetLinkNext(temp)) != GetUserId(User2))
        temp = GetLinkNext(temp);

    if(GetLinkNext(temp) == NULL){
        printf("%s didn't have a follow named %s\n",name1,name2);
    }else{
        tempPre = temp;
        temp = GetLinkNext(temp);
        SetLinkNext(GetLinkNext(temp),tempPre);
        free(temp);
    }

    /*在name2中删除粉丝name1*/
    temp = GetUserFan(User2);
    while(GetLinkNext(temp) != NULL && GetLinkId(GetLinkNext(temp)) != GetUserId(User1))
        temp = GetLinkNext(temp);

    if(GetLinkNext(temp) == NULL){
        printf("%s didn't have a fan named %s\n",name2,name1);
    }else{
        tempPre = temp;
        temp = GetLinkNext(temp);
        SetLinkNext(GetLinkNext(temp),tempPre);
        free(temp);
    }
}
