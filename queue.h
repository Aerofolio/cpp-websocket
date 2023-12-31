#pragma once
#include <stdlib.h>
#include <string.h>
#include <iostream>

struct nodeValue{
    char *name, *content, *date;
};

struct node {
    struct nodeValue * value;
	struct node * next;
};

struct queue {
    int size;
    node *first, *last;
};

nodeValue * createNodeValue(char *name, char *content, char *date){
    nodeValue * newNode = (nodeValue *) malloc(sizeof(nodeValue));

    newNode->name = (char *) malloc(strlen(name));
    strcpy(newNode->name, name);

    newNode->content = (char *) malloc(strlen(content));
    strcpy(newNode->content, content);

    newNode->date = (char *) malloc(strlen(date));
    strcpy(newNode->date, date);

    return newNode;
}

void add(queue * q, nodeValue * val){
    if(q != NULL){
        node * newNode = (node *) malloc(sizeof(node));
        newNode->next = NULL;
        newNode->value = val;

        q->size = q->size + 1;

        if(q->first == NULL){
            q->first = newNode;
            q->last = newNode;
        }else{
            q->last->next = newNode;
            q->last = newNode;
        }
    }
}

queue * initQueue(){
    queue * q = (queue *) malloc(sizeof(queue));
    q->size = 0;
    q->first = NULL;
    q->last = NULL;

    return q;
}

bool empty(queue * q){
    if(q->first == NULL) return true;
    return false;
}

void printNodeValue(nodeValue * n){
    if(n != NULL){
        std::cout << "\tNome: " << n->name << std::endl;
        std::cout << "\tArquivo: " << n->content << std::endl;
        std::cout << "\tData: " << n->date << std::endl;
    }
}

std::string getQueueString(queue * q){
    if(q != NULL){
        std::string queueString;
        node * searchNode = q->first;
        int position = 1;

        if(empty(q)){
            return "Fila Vazia!";
        }else{
            while (searchNode != NULL)
            {
                queueString += "Posição " + std::to_string(position) + "\n\n";
                position++;
                queueString += "\tNome: " + std::string(searchNode->value->name) + "\n";
                queueString += "\tArquivo: " + std::string(searchNode->value->content) + "\n";
                queueString += "\tData: " + std::string(searchNode->value->date) + "\n";

                if(searchNode->next != NULL){
                    queueString += "\n";
                }

                searchNode = searchNode->next;
            }

            return queueString;
        }
    }else{
        return "Fila Vazia!";
    }
}

nodeValue * remove(queue * q){
    if(q != NULL && !empty(q)){
        node * nodeToBeRemoved = q->first;
        nodeValue * valueRemoved = nodeToBeRemoved->value;
        q->first = nodeToBeRemoved->next;

        if(q->first == NULL)
            q->last = NULL;

        free(nodeToBeRemoved);
        return valueRemoved;
    }

    return NULL;
}

void clearQueue(queue * q){
    node * searchNode = q->first;
    nodeValue * valueAux;
    while (searchNode != NULL)
    {
        searchNode = searchNode->next;
        valueAux = remove(q);
        free(valueAux);
    }
}