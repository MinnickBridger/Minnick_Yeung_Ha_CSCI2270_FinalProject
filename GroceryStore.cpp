#include "GroceryStore.h"
#include <iostream>
using namespace std;

GroceryStore::GroceryStore()
{
    //ctor
    //root = NULL;
    for(int x = 0; x<10; x++){
        hashTable[x] = NULL;
    }
}

GroceryStore::~GroceryStore()
{
    //dtor
}
int GroceryStore::hashSum(string words){
    if(words == "Dairy"){
        return 0;
    }else if(words == "Produce"){
        return 1;
    }else if(words == "Meat"){
        return 2;
    }else if(words == "Grains"){
        return 3;
    }else if(words == "Condiment"){
        return 4;
    }else{
        return 5;
    }
}
void GroceryStore::addItemToHash(int isle, string title, string category, int quantity){
    int index = hashSum(category);
    if(hashTable[index] == NULL){
        GroceryNode *hashElement = new GroceryNode;
        hashElement->title = title;
        hashElement->isle = isle;
        hashElement->category = category;
        hashElement->quantity = quantity;
        hashElement->leftChild = NULL;
        hashElement->rightChild = NULL;
        hashElement->parent = NULL;
        hashTable[index] = hashElement;
    }
    else{
        addItem(hashTable[index],isle, title, category, quantity);
    }

}
void GroceryStore::addItem(GroceryNode *root, int isle, string title, string category, int quantity){
    GroceryNode *tmp = root;
    GroceryNode *parent = NULL;
    GroceryNode *node = new GroceryNode(isle, title, category, quantity);
    node->leftChild = NULL;
    node->rightChild = NULL;
    //node->parent = NULL;
    while(tmp!=NULL){
        parent = tmp;
        if(node->title<tmp->title){
            tmp = tmp->leftChild;
        }else{
            tmp = tmp->rightChild;
        }
    }
    if(parent==NULL){
        root = node;
    }else if(node->title < parent->title){
        parent->leftChild = node;
        node->parent = parent;
    }else{
        parent->rightChild = node;
        node->parent = parent;
    }
}
void GroceryStore::printItemsInCategory(string category){
    GroceryNode *tmp;
    int index = hashSum(category);
    tmp = hashTable[index];
    if(tmp!=NULL){
       printStoreInventory(tmp);
    }
    else{
        cout<<"No items in "<<category<<endl;
    }

}
void GroceryStore::printStoreInventory(GroceryNode *node){
    if(node->leftChild!=NULL){
        printStoreInventory(node->leftChild);
    }
    cout<<"Item: "<<node->title<<" "<<node->quantity<<endl;
    if(node->rightChild!=NULL){
        printStoreInventory(node->rightChild);
    }

}
