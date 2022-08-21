#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * list = (List*) malloc (sizeof(List));
  list -> head = NULL;
  list -> tail = NULL;
  list -> current = NULL;
  return list;
}

void * firstList(List * list) {
  if (!list->head) return NULL;
  list->current = list->head;
  return (list->head->data);
  //return NULL;
}

void * nextList(List * list) {
  if (!list->current) return NULL;
  if (!list->current->next) return NULL;
  list->current = list->current->next;
  return (list->current->data);
}

void * lastList(List * list) {
  list->current = list->tail;
  return (list->current->data);
}

void * prevList(List * list) {
  if (!list->current) return NULL;
  if (!list->current->prev) return NULL; 
  list->current = list->current->prev;
  return (list->current->data);
}

void pushFront(List * list, void * data) {
  Node * new = createNode(data); // creacion nodo
  new->next = list->head; //el puntero next apunta al head
  if (list->head) //si existe head, el anterior a esa será el new
    list->head->prev = new;
  list->head = new;
  list->tail = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * current = list->current;

  
  if (current == list->head){
    current->next->prev = NULL;
    list->head = current->next;
  }else{
    if (current == list->tail){
      current->prev->next = NULL;
      list->tail = current->prev;
    }else{
      current->prev->next = current->next->prev;
      current->next->prev = current->prev->next;
    }
    free(current);
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}