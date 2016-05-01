/*
Final Project
Authors: Bridger, Eric, Syrus
CSCI 2270
*/
#include <iostream>
#include "GroceryStore.h"
#include <string>

using namespace std;

int main(int argc, char*argv[])
{
    cout<<"Welcome to grocery store item inventory!"<<endl;
    cout<<"To see the list of item categories, please press 6"<<endl;
    cout<<" "<<endl;
    GroceryStore gs;
    int n = 0;
    string line;
    string word;
    string category;
    int quantity;
    int isle;
    string cartTitle;
    string cartCategory;
    float price;
    string title;
    ifstream inFile(argv[1]);
    //ifstream inFile;
    //inFile.open("finalGrocery.txt");
    int counter = 0;
    if(inFile.good()){
        while(getline(inFile,line)){
            stringstream ss(line);
            while(getline(ss, word, ',')){
                if(counter == 0){
                    isle = atoi(word.c_str());
                    counter++;
                }else if(counter == 1){
                    title = word;

                    //cout<<word<<endl;
                    counter++;
                }else if(counter == 2){
                    category = word;
                    counter++;
                }else if(counter == 3){
                    quantity = atoi(word.c_str());
                    counter++;
                }else if(counter == 4){
                    price = std::stof(word.c_str());
                }
                //cout<<word<<endl;
            }
            counter = 0;
            gs.addItemToHash(isle, title, category, quantity, price);
        }
    }else{
        cout<<"Didnt open"<<endl;
    }
    inFile.close();
    string choice;
    while(n!=11){
        cout << "======Main Menu======" << endl;
        cout << "1. Find an item" << endl;
        cout << "2. Print items in a category" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Remove one item from the inventory" << endl;
        cout << "5. Count the items" << endl;
        cout << "6. List the categories"<<endl;
        cout << "7. Remove all of the available inventory of an item"<<endl;
        cout << "8. Add item to Cart" << endl;
        cout << "9. Print Cart Contents"<<endl;
        cout <<"10. Clear Cart"<<endl;
        cout <<"11. Quit"<<endl;
        cin>>choice;
        if(choice == "1"){
            string itemName;
            cout << "Enter item name: " << endl;
            cin.ignore();
            getline(cin, itemName);
            string itemCategory;
            cout << "Enter the item category: " << endl;
            getline(cin, itemCategory);
            gs.findItem(itemName, itemCategory);
        }else if(choice == "3"){
            gs.printStoreInventory();

        }else if(choice == "2"){
            string word;
            cout<<"Enter a category: "<<endl;
            cin.ignore();
            getline(cin,word);
            gs.printItemsInCategory(word);
        }else if(choice == "11"){
            cout << "Goodbye!" << endl;
            n = 11;
        }else if(choice == "4"){
            string deleteNode;
            cout << "Enter item: " << endl;
            cin.ignore();
            getline(cin, deleteNode);
            string cat;
            cout<<"Enter the item category: "<<endl;
            getline(cin, cat);
            gs.removeQuantity(deleteNode, cat);


        }else if(choice == "5"){
            //cout<<"Tree contains: "<<gs.countItems()<<" items."<< endl;
        }else if(choice == "6"){
            cout<<"Item categories: Produce, Meat, Condiment, Grains, Dairy and other."<<endl;
        }else if(choice == "7"){
            string deleteNode;
            cout << "Enter item: " << endl;
            cin.ignore();
            getline(cin, deleteNode);
            string cat;
            cout<<"Enter the item category: "<<endl;
            getline(cin, cat);
            gs.deleteItem(deleteNode, cat);

        }else if(choice == "8"){
            cout<<"Enter Item you would like to add to your cart:"<<endl;
            cin.ignore();
            getline(cin, cartTitle);
            cout<<"What category is it in?:"<<endl;
            cout<<"Reminder: Item categories: Produce, Meat, Condiment, Grains, Dairy and other."<<endl;

            getline(cin,cartCategory);
            gs.addToCart(cartTitle,cartCategory);
        }else if(choice == "9"){
            gs.viewCart();
        }
        else if(choice == "10"){
            gs.clearCart();
        }
        else{
            cout<<"Please enter the number to one of the options below"<<endl;
        }

    }
    return 0;
}
