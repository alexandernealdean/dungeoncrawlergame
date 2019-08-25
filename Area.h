#include <string>
#include <iostream>
#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

using namespace std;

class Area{
  public:
		uLList<Item*> items;

    void setDescription (string desc){
    	description = desc;
    }
		void setGoal(bool g){
			goal = g;		
		}
		void setID(bool id){
			instadeath = id;		
		}
    string getDescription(){
    	return description;
    }
    bool getID(){
    	return instadeath;
    }
		bool getGoal(){
			return goal;
		}
		void displayArea(){
			cout<<description<<endl;		
		}
		void search(){
			nodeType<Item*>* temp;
      temp = items.getFirst();
			//cout<<temp<<endl;
			if(temp == NULL){
				cout<<"No items are in this room."<<endl;
			}
			else{
				cout<<"The following items are in this room:"<<endl;
				while(temp != NULL){
					cout<<"\t"<<temp->info->getName()<<endl;
					temp = temp->link;
				}
			}
		}
    
  private:
    string description;
		bool instadeath;
		bool goal;
		
};
