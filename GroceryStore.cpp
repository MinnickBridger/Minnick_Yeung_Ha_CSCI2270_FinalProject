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
    }else if(words == "Other"){
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
        //cout<<"First Time being added to index "<<hashTable[index]->title<<endl;
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
    //cout<<"Being added in tree: "<<node->title<<" Parent: "<<node->parent->title<<endl;
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
    cout<<"Item: "<<node->title<<", Isle: "<<node->isle<<", Category: "<<node->category<<", Quantity: "<<node->quantity<<endl;
    if(node->rightChild!=NULL){
        printStoreInventory(node->rightChild);
    }

}
void GroceryStore::printStoreInventory(){
    for(int i = 0; i<=6;i++){
        printStoreInventory(hashTable[i]);
    }
}
GroceryNode *GroceryStore::search(GroceryNode *node, string titles){
    while(node!=NULL){
        if(node->title>titles){
            node = node->leftChild;
        }else if(node->title<titles){
            node = node->rightChild;
        }else{
            return node;
        }
    }
}
void GroceryStore::findItem(string title, string category){
    int index = hashSum(category);
    GroceryNode *tmp = search(hashTable[index], title);
    if(tmp!=NULL && tmp->title == title){
        cout<<"Item: "<<tmp->title<<", Isle: "<<tmp->isle<<", Category: "<<tmp->category<<", Quantity: "<<tmp->quantity<<endl;
    }
    else{
        cout<<"Item not found, make sure it is the correct category"<<endl;
    }
}
GroceryNode* GroceryStore::treeMinimum(GroceryNode *node){
    //node = node->rightChild;
    while(node->leftChild!=NULL){
        node = node->leftChild;
    }
    return node;
}
void GroceryStore::deleteItem(string title, string category){
    int index = hashSum(category);
    GroceryNode *node;
    GroceryNode *root = hashTable[index];
    node = search(hashTable[index], title);
    if(node!=NULL){
    if(node != root){
        if(node->leftChild == NULL && node->rightChild == NULL){
            //No Child
            if(node->parent->leftChild==node){
                node->parent->leftChild = NULL;
            }else{
                node->parent->rightChild = NULL;
            }
        }else if(node->leftChild != NULL && node->rightChild != NULL){
            //Two Children
            GroceryNode *minn;
            minn = treeMinimum(node->rightChild);
            if(minn == node->rightChild){
                node->parent->leftChild = minn;
                minn->parent = node->parent;
                node->leftChild->parent = minn;
                minn->leftChild = node->leftChild;
            }else{
                minn->parent->leftChild = minn->rightChild;
                minn->rightChild->parent = minn->parent;
                minn->parent = node->parent;
                node->parent->leftChild = minn;
                minn->leftChild = node->leftChild;
                minn->rightChild = node->rightChild;
                node->rightChild->parent = minn;
                node->leftChild->parent = minn;

            }

        }else{
            //One Child
            if(node->leftChild==NULL){
                GroceryNode *x = node->rightChild;
                if(node->parent->leftChild == node){
                    node->parent->leftChild = x;
                }else{
                    node->parent->rightChild = x;
                }

                x->parent = node->parent;
            }else if(node->rightChild == NULL){
                 GroceryNode *x = node->leftChild;
                if(node->parent->leftChild == node){
                    node->parent->leftChild = x;
                }else{
                    node->parent->rightChild = x;
                }

                x->parent = node->parent;
            }
        }
    delete node;
    }else{
        //THIS ELSE IF FOR DELETING THE ROOT
        cout<<"inside of else"<<endl;
        GroceryNode *walker = root->rightChild;
        GroceryNode *temp = walker->leftChild;
        while(temp != NULL){
            walker = temp;
            temp = temp->leftChild;
        }
        if(walker->parent == root){
            if(walker->rightChild != NULL){
                walker->parent->rightChild = walker->rightChild;
                walker->rightChild->parent = walker->parent;
            }else {
                walker->parent->rightChild = NULL;
                walker->parent = NULL; }
        }else {
            if(walker->rightChild != NULL){
            walker->parent->leftChild = walker->rightChild;
            walker->rightChild->parent = walker->parent;
            }else {
                walker->parent->leftChild = NULL;
                walker->parent = NULL;
            }
        }
        walker->leftChild = root->leftChild; walker->rightChild=root->rightChild;
        if(walker->leftChild != NULL){
           walker->leftChild->parent = walker;
        }
        if(walker->rightChild != NULL){
           walker->rightChild->parent = walker;
        }
        delete root;
        //root = walker;

    }
    //delete node;
    }else{
        cout << "Movie not found." << endl;
    }
}
void GroceryStore::removeQuantity(string title, string category){
    int index = hashSum(category);
    GroceryNode *foundMovie = search(hashTable[index], title);
    if(foundMovie!=NULL){
        if(foundMovie->quantity==0){
            cout << "Item out of stock." << endl;
        }else{
            foundMovie->quantity-=1;
            cout << "Item has been removed." << endl;
            cout << "item Info:" << endl;
            cout << "===========" << endl;
            cout << "Isle:" << foundMovie->isle << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout<< "Category:" << foundMovie->category << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
            if(foundMovie->quantity == 0){
                deleteItem(title, category);
            }
        }
    }else{
        cout << "Item not found." << endl;
    }
}
