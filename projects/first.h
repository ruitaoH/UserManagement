//
// Created by haoruitao on 15-11-22.
//

#ifndef TASK3_FIRST_H
#define TASK3_FIRST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./cJSON/cJSON.h"

#define NameSize 30

struct LinkNode{
    int ID;
    struct LinkNode *nextPtr;
};

typedef struct LinkNode LinkNode;
typedef LinkNode *LinkNodePtr;

struct UserNode{
    int ID;
    char Name[NameSize];
    LinkNodePtr Friends;
    LinkNodePtr Follows;
    LinkNodePtr Fans;
    struct UserNode *nextPtr;
};

typedef struct UserNode UserNode;
typedef UserNode *UserNodePtr;

struct HashTable{
    int TabelSize;
    UserNodePtr *TheUser;
};

typedef struct HashTable HashTable;
typedef HashTable *HashTablePtr;

unsigned int Hash(char *name,int tablesize);
int NextPrime(int n);

/*散列表基本操作*/
HashTablePtr Initialize(int TableSize);
void Insert(int id,char name[],int namesize,HashTablePtr H);
void Destroy(HashTablePtr H);
void Delete(char name[],int namesize,HashTablePtr H);
void Change(char name[],int namesize,HashTablePtr H);
UserNodePtr Find(char name[],int namesize,HashTablePtr H);
UserNodePtr FindId(int id,HashTablePtr H);
LinkNodePtr FindLastPre(LinkNodePtr L);
void MakeEmpty(HashTablePtr H);

/*Get Set*/
int GetLinkId(LinkNodePtr L);
void SetLinkId(int id,LinkNodePtr L);

LinkNodePtr GetLinkNext(LinkNodePtr L);
void SetLinkNext(LinkNodePtr newPtr,LinkNodePtr L);

int GetUserId(UserNodePtr U);
void SetUserId(int id,UserNodePtr U);

char* GetUserName(UserNodePtr U);
void SetUserName(char name[],int namesize,UserNodePtr U);

UserNodePtr GetUserNext(UserNodePtr U);
void SetUserNext(UserNodePtr newPtr,UserNodePtr U);

LinkNodePtr GetUserFriend(UserNodePtr U);
LinkNodePtr GetUserFollow(UserNodePtr U);
LinkNodePtr GetUserFan(UserNodePtr U);

int FindMaxId(HashTablePtr H);

void DeleteFriend(int id,HashTablePtr H);
void DeleteFollow(int id,HashTablePtr H);
void DeleteFan(int id,HashTablePtr H);

void printHash(HashTablePtr H);
void printFriend(UserNodePtr U,HashTablePtr H);
void printFollow(UserNodePtr U,HashTablePtr H);
void printFan(UserNodePtr U,HashTablePtr H);
void printUser(UserNodePtr U,HashTablePtr H);
void printList(LinkNodePtr L,HashTablePtr H);

#endif //TASK3_FIRST_H
