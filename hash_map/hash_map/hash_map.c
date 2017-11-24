//
//  hash_map.c
//  hash_map
//
//  Created by rong on 2017/11/5.
//  Copyright © 2017年 zcr. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_map.h"

#define HASH_ARRAY_MAX 256

#define  my_malloc malloc
#define  my_free free
struct hash_node{
    char key[64];
    void* value;
    struct hash_node* next;//指向下一个hash节点的指针
};
struct hash_map{
    struct hash_node* hash_array[HASH_ARRAY_MAX];
};

#pragma mark - hash_node
static struct hash_node* hash_node_create(char* key,void* value){
    struct hash_node* node = (struct hash_node*)my_malloc(sizeof(struct hash_node));
    memset(node, 0, sizeof(struct hash_node));
    strcpy(node->key, key);
    node->value = value;
    return node;
}

static void hash_node_free(struct hash_node* node){
    my_free(node);
}

#pragma mark - hash_map
//hash算法
unsigned int SDBMHash(char *str)
{
    unsigned int hash = 0;
    
    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    
    return (hash & 0x7FFFFFFF);
}
//根据key进行哈希运算，然后模运算获取key值
static int key_gethashvalue(char *key){
    //哈希
    int hash = SDBMHash(key);
    //模运算
    int keyhash = hash%HASH_ARRAY_MAX;
    return keyhash;
//    return 0;
}

struct hash_map* hash_map_create(void){
    struct hash_map *map = (struct hash_map *)my_malloc(sizeof(struct hash_map));
    memset(map, 0, sizeof(struct hash_map));
    return map;
}



void hash_map_add_front(struct hash_map* map,const char* key ,void* value){
    int v = key_gethashvalue((char*)key);
    //将新的节点加入到map中
    struct hash_node* newNode = hash_node_create((char*)key, value);
    newNode->next = map->hash_array[v];//将新建的node指向原来的头节点
    map->hash_array[v]=newNode;//头节点指针指向新的指针
    return;
}

void hash_map_add_tail(struct hash_map* map,const char* key, void* value){
    struct hash_node* newNode = hash_node_create((char*)key, value);
    
    int v = key_gethashvalue((char*)key);
    struct hash_node* head = map->hash_array[v];
    if (head == NULL) {
        map->hash_array[v]=newNode;
    }else{
        while (head->next) {
            head = head->next;
        }
        head->next = newNode;
    }
    head = NULL;
    return;
    
}

void hash_map_remove(struct hash_map* map,const char* key){
    int v = key_gethashvalue((char*)key);
    struct hash_node** walk = &(map->hash_array[v]);
    //单链表的删除操作！！！
    while (*walk) {
        if (strcmp((*walk)->key, (char*)key)==0) {//名字相同
            struct hash_node *node_remove = *walk;
            *walk = node_remove->next;
            node_remove->next = NULL;
            hash_node_free(node_remove);
        }else{
            walk = &((*walk)->next);
        }
    }
}

void* hash_map_find(struct hash_map* map,const char* key){
    int v = key_gethashvalue((char*)key);
    struct hash_node* walk= map->hash_array[v];
    while (walk) {
        if (strcmp(walk->key, key)) {
            return walk->value;
        }
        walk = walk->next;
    }
    return  NULL;
}

void hash_map_remove_object_for_key(struct hash_map* map,char* key){
    int v = key_gethashvalue(key);
    struct hash_node** walk = &(map->hash_array[v]);
    while (*walk) {
        if (strcmp((*walk)->key, (const char*)key)==0) {
            //删除节点
            struct hash_node *tmpnode = *walk;
            *walk = tmpnode->next;
            tmpnode->next = NULL;
            hash_node_free(tmpnode);
        }else{
            walk = &((*walk)->next);
        }

    }
}

void hash_map_clear(struct hash_map* map){
    //释放所有节点
    for (int i = 0 ; i<HASH_ARRAY_MAX; i++) {
        struct hash_node* head = map->hash_array[i];
        while (head) {
            struct hash_node* node =head;
            head = node->next;
            node->next = NULL;//删除链表节点的时候直接释放这块内存不可以吗，为什么还要指向空呢？
            hash_node_free(node);
        }
    }
    memset(map, 0, sizeof(struct hash_map));
}

void hash_map_print(struct hash_map* map){
    for (int i =0; i<HASH_ARRAY_MAX; i++) {
        struct hash_node* head = map->hash_array[i];
        while (head) {
            struct hash_node* node = head;
            printf("node key=%s value=%s \n",node->key,(char*)node->value);
            head = node->next;
        }
    }
}



