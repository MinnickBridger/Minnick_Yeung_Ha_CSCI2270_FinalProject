#ifndef GROCERYSTORE_H
#define GROCERYSTORE_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <cstdlib>

struct GroceryNode{
    int isle;
    std::string title;
    std::string category;
    int quantity;
    GroceryNode *parent;
    GroceryNode *leftChild;
    GroceryNode *rightChild;
    //GroceryNode *root;

    GroceryNode(){};

    GroceryNode(int in_isle, std::string in_title, std::string in_category, int in_quantity)
    {
        isle = in_isle;
        title = in_title;
        category = in_category;
        quantity = in_quantity;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }

};
class GroceryStore
{
    public:
        GroceryStore();
        ~GroceryStore();
        void printStoreInventory();
        void printItemsInCategory(std::string title);
        int countItems();
        void deleteItem(std::string title);
        void addItem(GroceryNode *root, int isle, std::string title, std::string category, int quantity);
        void addItemToHash(int isle, std::string title, std::string category, int quantity);
        void findItem(std::string title, std::string category);
    protected:
    private:
        void DeleteAll(GroceryNode * node); //use this for the post-order traversal deletion of the tree
        void printStoreInventory(GroceryNode * node);
        void countItems(GroceryNode *node, int *c);
        GroceryNode* search(GroceryNode *tmp, std::string title);
        GroceryNode* treeMinimum(GroceryNode *node);
        //GroceryNode *root;
        int hashSum(std::string x);
		int tableSize = 6;
		GroceryNode* hashTable[6];
};

#endif // GROCERYSTORE_H
