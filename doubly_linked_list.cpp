//=================================================================
// Implementation for DLL module.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

LLNode* create_llnode(void* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;
  
    return newNode; 
}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

int getSize(DLinkedList* dLinkedList){
    return dLinkedList->size;
}

LLNode* getHead(DLinkedList* dLinkedList){
    return dLinkedList->head;
}

LLNode* getTail(DLinkedList* dLinkedList){
    return dLinkedList->tail;
}

LLNode* getNext(LLNode* node){
    return node->next;
}

LLNode* getPrev(LLNode* node){
    return node->prev;
}

void* getData(LLNode* node){
    return node->data;
}

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL");
    return;
  }

  LLNode* newNode = create_llnode(data);
  newNode->prev = prev_node;
  newNode->next = prev_node->next;
  prev_node->next = newNode;
  dLinkedList->size++;

  if(newNode->next != NULL) {
    newNode->next->prev = newNode;
  }else{
    dLinkedList->tail = newNode;
  }
  return;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (next_node == NULL) {
    printf("the given next node cannot be NULL");
    return;
  }
  
  LLNode* newNode = create_llnode(data);
 
  newNode->prev = next_node->prev;
  newNode->next = next_node;
  next_node->prev = newNode;
  dLinkedList->size++; 

  //check if next_node is head of DLL

  if(newNode->prev != NULL) {
    newNode->prev->next = newNode;
  } else {
    dLinkedList->head = newNode;
  }
  return;
}

void insertHead(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertBefore(dLinkedList, dLinkedList->head, data);
  }
}

void insertTail(DLinkedList* dLinkedList, void* data){
    
    if(dLinkedList->tail == NULL){
    LLNode* newNode = create_llnode(data);
    
    //dLinkedList->tail->next = newNode;
    //dLinkedList->tail = newNode;
    //dLinkedList->size++;

    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertAfter(dLinkedList, dLinkedList->tail, data);
  }
}

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){

  //head reference to point to head node pointer
  LLNode* headRef = dLinkedList->head;

  if (headRef == NULL || Node == NULL) 
    return;
  if(headRef == Node) {
    dLinkedList->head = Node->next;
    // second node prev pointer to null

    //have to check if the next node exists
    if (Node->next){
      Node->next->prev = NULL;
    } else {
      dLinkedList->tail = NULL;
    }
  } else if (Node == dLinkedList->tail) {
    dLinkedList->tail = Node->prev;
    Node->prev->next = NULL;
  } else {
    Node->next->prev = Node->prev;
    Node->prev->next = Node->next;
  }
    
  free(Node->data);
  free(Node);
  dLinkedList->size--;
  return;
}

void destroyList(DLinkedList* dLinkedList){

  LLNode* headRef = dLinkedList->head;
  LLNode* nullNode = NULL;
  while(headRef != NULL) {
    nullNode = (headRef)->next;
    free(headRef->data);
    free(headRef);
    headRef = nullNode;
  }

  free(dLinkedList);
  return;

}

void reverse(DLinkedList* dLinkedList)
{
  LLNode* headRef = dLinkedList->head;
  LLNode* temp = NULL;
  LLNode* curr = headRef;

  if(dLinkedList->size == 1 || dLinkedList->size == 0) {
    return;
  }

  while (curr != NULL) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;   
  }

  //reset head and tail pointers
  if (temp != NULL) {
    dLinkedList->tail = temp->prev;
  }
}     
