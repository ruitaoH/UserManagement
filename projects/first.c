//
// Created by haoruitao on 15-11-22.
//

#include "first.h"

/*Hash()函数*/
unsigned int Hash(char *name,int tablesize){
    unsigned int hash = 5381;
    while(*name){
        hash += (hash << 5) + (*name++);
    }

    return (hash & 0x7FFFFFFF) % tablesize;
}

/*下一个素数*/
int NextPrime(int n){
    int i;
    if(n % 2 == 0)
        n++;
    for(;;n += 2){
        for(i = 3;i * i <= n;i++){
            if(n % i ==0)
                break;
        }
        if(i * i > n)
            return n;
    }
}

/*初始化链表*/
HashTablePtr Initialize(int TableSize){
    HashTablePtr  H;
    int i;

    H = malloc(sizeof(HashTable));
    if(H == NULL){
        printf("Out of space!!!\n");
        exit(1);
    }

    H->TabelSize = NextPrime(TableSize);
    H->TheUser = malloc(sizeof(UserNodePtr) * H->TabelSize);

    for(i = 0;i < H->TabelSize;i++){
        H->TheUser[i] = malloc(sizeof(UserNode));
        H->TheUser[i]->nextPtr = NULL;
    }

    return H;
}


/*插入*/
void Insert(int id,char name[],int namesize,HashTablePtr H){
    UserNodePtr temp,newUser;

    temp = Find(name,namesize,H);
    if(temp == NULL){
        newUser = malloc(sizeof(UserNode));

        newUser->ID = id;
        strcpy(newUser->Name,name);

        /*初始化用户的Friends链表*/
        newUser->Friends = malloc(sizeof(LinkNode));
        if(newUser->Friends == NULL){
            printf("Out of space!!!\n");
            exit(1);
        }
        newUser->Friends->nextPtr = NULL;

        /*初始化用户的Follows链表*/
        newUser->Follows = malloc(sizeof(LinkNode));
        if(newUser->Follows == NULL){
            printf("Out of space!!!\n");
            exit(1);
        }
        newUser->Follows->nextPtr = NULL;

        /*初始化用户的Fans链表*/
        newUser->Fans = malloc(sizeof(LinkNode));
        if(newUser->Fans == NULL){
            printf("Out of space!!!\n");
            exit(1);
        }
        newUser->Fans->nextPtr = NULL;

        temp = H->TheUser[Hash(name,H->TabelSize)];
        while(temp->nextPtr != NULL)
            temp = temp->nextPtr;
        temp->nextPtr = newUser;
        newUser->nextPtr = NULL;
    }else{
        printf("the name had been inserted\n");
    }
}

/*查找name*/
UserNodePtr Find(char name[],int namesize,HashTablePtr H){
    UserNodePtr temp;

    temp = H->TheUser[Hash(name,H->TabelSize)]->nextPtr;
    while(temp != NULL && strcmp(temp->Name,name) != 0)
        temp = temp->nextPtr;

    return temp;
}

/*查找id*/
UserNodePtr FindId(int id,HashTablePtr H){
    UserNodePtr temp;
    int i;

    for(i = 0;i < H->TabelSize;i++){
        temp = H->TheUser[i]->nextPtr;

        while(temp != NULL && temp->ID != id)
            temp = temp->nextPtr;

        if(temp != NULL)
            break;
    }

    return temp;
}

/*删除*/
void Delete(char name[],int namesize,HashTablePtr H){
    UserNodePtr temp,tempPre;
    int i,max = FindMaxId(H);
    LinkNodePtr Follow,Friend,Fan;
    UserNodePtr tempUser;

    if(Find(name,namesize,H) != NULL) {
        i = Find(name,namesize,H)->ID;

        tempPre = H->TheUser[Hash(name, H->TabelSize)];
        temp = tempPre->nextPtr;
        while (temp != NULL && strcmp(temp->Name, name) != 0) {
            tempPre = temp;
            temp = temp->nextPtr;
        }

        tempPre->nextPtr = temp->nextPtr;

        DeleteFollow(temp->ID,H);
        DeleteFriend(temp->ID,H);
        DeleteFan(temp->ID,H);

        free(temp);
    }else{
        printf("Can't find\n");
    }
}

/*销毁链表*/
void Destroy(HashTablePtr H){
    UserNodePtr  temp,user;
    int i;

    for(i = 0;i < H->TabelSize;i++) {
        user = H->TheUser[i]->nextPtr;
        while(user != NULL){
            temp = user;
            user = user->nextPtr;
            free(temp);
        }
    }
    free(H->TheUser);
    free(H);
}

/*清空链表*/
void MakeEmpty(HashTablePtr H){
    UserNodePtr temp,user;
    int i;

    for(i = 0;i < H->TabelSize;i++){
        user = H->TheUser[i];
        while(user != NULL){
            temp = user;
            user = user->nextPtr;
            free(temp);
        }
    }
    free(H->TheUser);

    H = Initialize(H->TabelSize);
}

/*改名*/
void Change(char name[],int namesize,HashTablePtr H){
    UserNodePtr  temp;
    char newname[namesize];

    temp = Find(name,namesize,H);

    if(temp == NULL){
        printf("Can't find\n");
    }else{
        printf("Please input newname:\n");
        getchar();
        scanf("%[^\n]",newname);

        strcpy(temp->Name,newname);
    }
}

/*查找最后一个前一个*/
LinkNodePtr FindLastPre(LinkNodePtr L){
    LinkNodePtr P;

    P = L;
    while(P->nextPtr != NULL)
        P = P->nextPtr;

    return P;
}

int GetLinkId(LinkNodePtr L){
    return L->ID;
}

void SetLinkId(int id,LinkNodePtr L){
    L->ID = id;
}

LinkNodePtr GetLinkNext(LinkNodePtr L){
    return L->nextPtr;
}

void SetLinkNext(LinkNodePtr newPtr,LinkNodePtr L){
    L->nextPtr = newPtr;
}

int GetUserId(UserNodePtr U){
    return U->ID;
}

void SetUserId(int id,UserNodePtr U){
    U->ID = id;
}

char* GetUserName(UserNodePtr U){
    return U->Name;
}

void SetUserName(char name[],int namesize,UserNodePtr U){
    strcpy(U->Name,name);
}

LinkNodePtr GetUserFriend(UserNodePtr U){
    return U->Friends;
}

LinkNodePtr GetUserFollow(UserNodePtr U){
    return U->Follows;
}

LinkNodePtr GetUserFan(UserNodePtr U){
    return U->Fans;
}

UserNodePtr GetUserNext(UserNodePtr U){
    return U->nextPtr;
}

void SetUserNext(UserNodePtr newPtr,UserNodePtr U){
    U->nextPtr = newPtr;
}

int FindMaxId(HashTablePtr H){
    UserNodePtr temp;
    int i,max = 0;

    for(i = 0;i < H->TabelSize;i++){
        for(temp = H->TheUser[i]->nextPtr;temp != NULL;temp = temp->nextPtr){
            max = temp->ID > max ? temp->ID : max;
        }
    }

    return max;
}

void printHash(HashTablePtr H){
    UserNodePtr Users;
    LinkNodePtr Follows,Friends,Fans;
    cJSON *objArr,*root,*arrayFri,*arrayFol,*arrayFan;
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

    printf("\n%s\n",c);

    cJSON_Delete(objArr);
}

void printFriend(UserNodePtr U,HashTablePtr H){
    printf("\n%s's friends:\n",U->Name);

    LinkNodePtr Friend;
    LinkNodePtr Friends,Follows,Fans;
    UserNodePtr temp;
    cJSON *objArr,*root,*arrayFri,*arrayFol,*arrayFan;
    char *c;

    objArr = cJSON_CreateArray();

    Friend = U->Friends->nextPtr;
    while(Friend != NULL){
        root = cJSON_CreateObject();
        arrayFol = cJSON_CreateArray();
        arrayFri = cJSON_CreateArray();
        arrayFan = cJSON_CreateArray();

        if((temp = FindId(Friend->ID,H)) != NULL){
            Follows = GetLinkNext(GetUserFollow(temp));
            Friends = GetLinkNext(GetUserFriend(temp));
            Fans = GetLinkNext(GetUserFan(temp));

            cJSON_AddNumberToObject(root, "id", GetUserId(temp));
            cJSON_AddStringToObject(root, "name", GetUserName(temp));

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

        Friend = Friend->nextPtr;
    }
    c = cJSON_Print(objArr);

    printf("\n%s\n",c);

    cJSON_Delete(objArr);
}

void printFollow(UserNodePtr U,HashTablePtr H){
    printf("\n%s's follows:\n",U->Name);

    LinkNodePtr Follow;
    LinkNodePtr Friend;
    LinkNodePtr Friends,Follows,Fans;
    UserNodePtr temp;
    cJSON *objArr,*root,*arrayFri,*arrayFol,*arrayFan;
    char *c;

    objArr = cJSON_CreateArray();

    Follow = U->Follows->nextPtr;
    while(Follow != NULL){
        root = cJSON_CreateObject();
        arrayFol = cJSON_CreateArray();
        arrayFri = cJSON_CreateArray();
        arrayFan = cJSON_CreateArray();

        if((temp = FindId(Follow->ID,H)) != NULL){
            Follows = GetLinkNext(GetUserFollow(temp));
            Friends = GetLinkNext(GetUserFriend(temp));
            Fans = GetLinkNext(GetUserFan(temp));

            cJSON_AddNumberToObject(root, "id", GetUserId(temp));
            cJSON_AddStringToObject(root, "name", GetUserName(temp));

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

        Follow = Follow->nextPtr;
    }
    c = cJSON_Print(objArr);

    printf("\n%s\n",c);

    cJSON_Delete(objArr);
}

void printFan(UserNodePtr U,HashTablePtr H) {
    printf("\n%s's fans:\n",U->Name);

    LinkNodePtr Fan;
    LinkNodePtr Friends,Follows,Fans;
    UserNodePtr temp;
    cJSON *objArr,*root,*arrayFri,*arrayFol,*arrayFan;
    char *c;

    objArr = cJSON_CreateArray();

    Fan = U->Fans->nextPtr;
    while(Fan != NULL){
        root = cJSON_CreateObject();
        arrayFol = cJSON_CreateArray();
        arrayFri = cJSON_CreateArray();
        arrayFan = cJSON_CreateArray();

        if((temp = FindId(Fan->ID,H)) != NULL){
            Follows = GetLinkNext(GetUserFollow(temp));
            Friends = GetLinkNext(GetUserFriend(temp));
            Fans = GetLinkNext(GetUserFan(temp));

            cJSON_AddNumberToObject(root, "id", GetUserId(temp));
            cJSON_AddStringToObject(root, "name", GetUserName(temp));

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

        Fan = Fan->nextPtr;
    }
    c = cJSON_Print(objArr);

    printf("\n%s\n",c);

    cJSON_Delete(objArr);
}

void printUser(UserNodePtr U,HashTablePtr H){
    printf("%s:\n",U->Name);

    LinkNodePtr Friends,Follows,Fans;
    cJSON *root,*arrayFri,*arrayFol,*arrayFan;
    char *c;

    root = cJSON_CreateObject();
    arrayFol = cJSON_CreateArray();
    arrayFri = cJSON_CreateArray();
    arrayFan = cJSON_CreateArray();

    Follows = GetLinkNext(GetUserFollow(U));
    Friends = GetLinkNext(GetUserFriend(U));
    Fans = GetLinkNext(GetUserFan(U));

    cJSON_AddNumberToObject(root, "id", GetUserId(U));
    cJSON_AddStringToObject(root, "name", GetUserName(U));

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

    c = cJSON_Print(root);

    printf("\n%s\n",c);

    cJSON_Delete(root);
}

void printList(LinkNodePtr L,HashTablePtr H){
    LinkNodePtr Link;
    LinkNodePtr Friends,Follows,Fans;
    UserNodePtr temp;
    cJSON *objArr,*root,*arrayFri,*arrayFol,*arrayFan;
    char *c;

    objArr = cJSON_CreateArray();

    Link = L->nextPtr;
    while(Link != NULL) {
        root = cJSON_CreateObject();
        arrayFol = cJSON_CreateArray();
        arrayFri = cJSON_CreateArray();
        arrayFan = cJSON_CreateArray();

        if ((temp = FindId(Link->ID, H)) != NULL) {
            Follows = GetLinkNext(GetUserFollow(temp));
            Friends = GetLinkNext(GetUserFriend(temp));
            Fans = GetLinkNext(GetUserFan(temp));

            cJSON_AddNumberToObject(root, "id", GetUserId(temp));
            cJSON_AddStringToObject(root, "name", GetUserName(temp));

            while (Follows != NULL) {
                cJSON_AddNumberToObject(arrayFol, "folid", GetLinkId(Follows));

                Follows = GetLinkNext(Follows);
            }
            cJSON_AddItemToObject(root, "Followings", arrayFol);

            while (Friends != NULL) {
                cJSON_AddNumberToObject(arrayFri, "friid", GetLinkId(Friends));

                Friends = GetLinkNext(Friends);
            }
            cJSON_AddItemToObject(root, "Friends", arrayFri);

            while (Fans != NULL) {
                cJSON_AddNumberToObject(arrayFan, "fanid", GetLinkId(Fans));

                Fans = GetLinkNext(Fans);
            }
            cJSON_AddItemToObject(root, "Fans", arrayFan);

            cJSON_AddItemToArray(objArr, root);
        }
        Link = Link->nextPtr;
    }
    c = cJSON_Print(objArr);

    printf("\n%s\n",c);

    cJSON_Delete(objArr);
}

/*删除所有有id好友的的人的好友列表中的id好友*/
void DeleteFriend(int id,HashTablePtr H){
    UserNodePtr User;
    LinkNodePtr FriendPre,Friend;
    int i,max = FindMaxId(H);

    for(i = 1;i <= max;i++){
        if((User = FindId(i,H)) != NULL){
            FriendPre = User->Friends;
            Friend = FriendPre->nextPtr;
            while(Friend != NULL && Friend->ID != id) {
                FriendPre = Friend;
                Friend = Friend->nextPtr;
            }
            if(Friend != NULL) {
                FriendPre->nextPtr = Friend->nextPtr;
                free(Friend);
            }
        }
    }
}

/*删除所有关注id的人的关注列表中的id关注*/
void DeleteFollow(int id,HashTablePtr H){
    UserNodePtr User;
    LinkNodePtr FollowPre,Follow;
    int i,max = FindMaxId(H);

    for(i = 1;i <= max;i++){
        if((User = FindId(i,H)) != NULL){
            FollowPre = User->Follows;
            Follow = FollowPre->nextPtr;
            while(Follow != NULL && Follow->ID != id){
                FollowPre = Follow;
                Follow = Follow->nextPtr;
            }
            if(Follow != NULL){
                FollowPre->nextPtr = Follow->nextPtr;
                free(Follow);
            }
        }
    }
}

/*删除所有有id粉丝的人的粉丝列表中的id粉丝*/
void DeleteFan(int id,HashTablePtr H){
    UserNodePtr User;
    LinkNodePtr FanPre,Fan;
    int i,max = FindMaxId(H);

    for(i = 1;i <= max;i++){
        if((User = FindId(i,H)) != NULL){
            FanPre = User->Fans;
            Fan = FanPre->nextPtr;
            while(Fan != NULL && Fan->ID != id){
                FanPre = Fan;
                Fan = Fan->nextPtr;
            }
            if(Fan != NULL){
                FanPre->nextPtr = Fan->nextPtr;
                free(Fan);
            }
        }
    }
}