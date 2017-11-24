//
//  hash_map.h
//  hash_map
/**
 NSDictionary的c语言实现
 **/
//  Created by rong on 2017/11/5.
//  Copyright © 2017年 zcr. All rights reserved.
//

#ifndef hash_map_h
#define hash_map_h

#include <stdio.h>


//哈希链表
struct hash_map;

//创建
struct hash_map* hash_map_create(void);

//删除map对象
void hash_map_clear(struct hash_map* map);

//先序添加数据
//key  value
void hash_map_add_front(struct hash_map* map,const char* key ,void* value);

//后续添加数据
void hash_map_add_tail(struct hash_map* map,const char* key, void* value);

//先序删除数据
void hash_map_remove(struct hash_map* map,const char* key);

//获取hashmap中指定key对应的值
void* hash_map_find(struct hash_map* map,const char* key);

//打印hashmap
void hash_map_print(struct hash_map* map);

#endif /* hash_map_h */
