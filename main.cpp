#include <iostream>
#include <GroceryStore.h>

using namespace std;

int main()
{

    GroceryStore gs;
    int n = 0;
    string line;
    string word;
    string category;
    int quantity;
    int isle;
    string title;
    ifstream inFile;
    inFile.open("finalGrocery.txt");
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
                    counter++;
                }else if(counter == 2){
                    category = word;
                    counter++;
                }else if(counter == 3){
                    quantity = atoi(word.c_str());
                }
                //cout<<word<<endl;
            }
            counter = 0;
            gs.addItemToHash(isle, title, category, quantity);
        }
    }else{
        cout<<"Didnt open"<<endl;
    }
    while(n!=6){
        cout << "======Main Menu======" << endl;
        cout << "1. Find an item" << endl;
        cout << "2. Print items in a category" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Delete an item" << endl;
        cout << "5. Count the items" << endl;
        cout << "6. Quit" << endl;
        int choice;
        cin>>choice;
        if(choice == 1){
            string itemName;
            cout << "Enter item name: " << endl;
            cin.ignore();
            getline(cin,itemName);
            //gs.findItem(itemName);
        }else if(choice == 2){

        }else if(choice == 3){
            string word;
            cout<<"Enter a category: "<<endl;
            cin.ignore();
            getline(cin,word);
            gs.printItemsInCategory(word);
        }else if(choice == 6){
            cout << "Goodbye!" << endl;
            n = 6;
        }else if(choice == 4){
            string deleteNode;
            cout << "Enter item: " << endl;
            cin.ignore();
            getline(cin, deleteNode);
            //gs.deleteItem(deleteNode);


        }else if(choice == 5){
            //cout<<"Tree contains: "<<gs.countItems()<<" items."<< endl;
        }

    }
    return 0;
}
