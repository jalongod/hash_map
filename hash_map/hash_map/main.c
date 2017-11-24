//
//  main.c
//  hash_map
/*
 NSDictionary的原理和实现
 NSDictionary的原理：哈希链表
 */
//  Created by rong on 2017/11/5.
//  Copyright © 2017年 zcr. All rights reserved.
//

#include <stdio.h>
#include "hash_map.h"


int main(int argc, const char * argv[]) {
    struct hash_map* map = hash_map_create();
    hash_map_add_front(map, "name", "zhangchengrong");
    hash_map_add_front(map, "bid", "com.jalon.test");
    hash_map_print(map);
    
    
//    hash_map_add_tail(map, "bid", "com.jalon.test");
//    hash_map_add_tail(map, "name", "zhangchengrong");
//    hash_map_print(map);
//
//    //删除key
//    hash_map_remove_object_for_key(map, "bid");
//    hash_map_print(map);
    
    //清空hash表
//    hash_map_clear(map);
//    hash_map_print(map);
    
  
    
    return 0;
}
