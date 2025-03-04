#include "tokenizer.h"
#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize the linked list
List* init_history(){
    List *list = (List *)malloc(sizeof(List));
    if (!list) return NULL;
    list->root = NULL;
    list->count = 0;  //Start ID count at 0
    return list;
}

//Add a new history item
void add_history(List *list, char *str){
    if (!list || !str) return;

    Item *new_item = (Item *)malloc(sizeof(Item));
    if (!new_item) return;

    new_item->str = strdup(str);
    new_item->next = NULL;
    
    //Assign ID using the global counter
    new_item->id = ++list->count;  //Ensure ID increments correctly

    //Append to end of the list
    if (list->root){
        Item *current = list->root;
        while (current->next){
            current = current->next;
        }
        current->next = new_item;
    } else {
        list->root = new_item;
    }
}

//Retrieve a history item by ID
char *get_history(List *list, int id){
    if (!list) return NULL;
    Item *current = list->root;
    while (current){
        if (current->id == id){
            return current->str;
        }
        current = current->next;
    }
    return NULL;
}

//Print the history list
void print_history(List *list){
  if (!list) return;
  Item *current = list->root;
  while (current){
    printf("%d: %s\n", current->id, current->str);
    current = current->next;
  }
}

//Free the history list
void free_history(List *list){
  if (!list) return;
  Item *current = list->root;
  while (current){
    Item *next = current->next;
    free(current->str);
    free(current);
    current = next;
  }
  free(list);
}
