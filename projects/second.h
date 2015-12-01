//
// Created by haoruitao on 15-11-24.
//

#ifndef TASK3_SECOND_H
#define TASK3_SECOND_H

#include "first.h"

void InsertUser(HashTablePtr H);
void DeleteUser(HashTablePtr H);

/*集合 交集*/
LinkNodePtr Intersection(char name1[],char name2[],int namesize,HashTablePtr H);

LinkNodePtr Twice(char name1[],char name2[],int namesize,HashTablePtr H);

#endif //TASK3_SECOND_H
