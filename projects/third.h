//
// Created by haoruitao on 15-11-24.
//

#ifndef TASK3_THIRD_H
#define TASK3_THIRD_H

#include "second.h"

void Write(HashTablePtr H);
void Read(HashTablePtr H);

/*添加删除好友 添加删除关注*/
void InsertFriends(char name1[],char name2[],int namesize,HashTablePtr H);
void DeleteFriends(char name1[],char name2[],int namesize,HashTablePtr H);
void InsertFollows(char name1[],char name2[],int namesize,HashTablePtr H);
void DeleteFollows(char name1[],char name2[],int namesize,HashTablePtr H);

#endif //TASK3_THIRD_H
