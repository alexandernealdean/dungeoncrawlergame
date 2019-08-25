#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

//**INCLUDE ANY NEW CLASS FILES HERE**//
#include "IFDParser.h"
#include "LinkData.h"

using namespace std;

template <class AreaType>
struct areaNode
{
	AreaType info;
	areaNode<AreaType> *u;
	areaNode<AreaType> *d;
	areaNode<AreaType> *l;
	areaNode<AreaType> *r;
};

template <class AreaType>
class Map{
	private:
		vector<areaNode<AreaType>*> areasVec;
		vector<Item*> itemsVec;
		int areacnt;
		
		//Here is the instance of IFDParser
	  IFDParser parser;

		//Some additional class attributes here
    vector<LinkData*> linkVec;
		string nextToken;

		bool ifderr;		

	public:
		Map(){  
			//**PUT CODE HERE**//
      ifderr = false;
			parser.tokenIt();
			
			//::COUT OF ALL THE TOKENS::
			//parser.printTokens();
			//::::::::::::::::::::::::::

			nextToken = parser.getNext();
			
			if(nextToken == "<game>"){
				//cout<<"::Found <game>::"<<endl;
				parser.eatToken();
				nextToken = parser.getNext();
				while(nextToken != "</game>"){  //consider what happens when run out of tokens && not error state  
					if(nextToken == "<area>"){
						//cout<<"::Found <area>::"<<endl;
						parser.eatToken();
						nextToken = parser.getNext();					
						makeArea();					
					}
					else if(nextToken == "<links>"){
						//cout<<"::Found <links>::"<<endl;
						parser.eatToken();
						nextToken = parser.getNext();
						makeLinks();
					}
					else if(nextToken == "<item>"){
					  //cout<<"::Found <item>::"<<endl;
						parser.eatToken();
						nextToken = parser.getNext();
						makeItem();
					}
					else{
						cout<<"Parse Error Location 1"<<endl;
						ifderr = true;
						break;
					}				
					parser.eatToken();
					nextToken = parser.getNext();	
				}// while !</game>

				if(ifderr){
						cout<<" :: ERROR :: IF Document Formatting Error"<<endl;
						cout<<"Game Loading Failed"<<endl;
						cout<<"General Area of Parsing Failure:"<<endl;
						cout<<"-------------------------------------"<<endl;
						cout<<nextToken<<endl;
						parser.eatToken();
						nextToken = parser.getNext();
						cout<<nextToken<<endl;
						parser.eatToken();
						nextToken = parser.getNext();
						cout<<nextToken<<endl;
						parser.eatToken();
						nextToken = parser.getNext();
						cout<<nextToken<<endl;
						cout<<"-------------------------------------"<<endl;
						return;
					}	
				//cout<<"::Found </game>::"<<endl;				
			}
			else{
				cout<<" :: ERROR :: No \"<game>\" tag found."<<endl;
				cout<<"Game Loading Failed"<<endl;
			}

			//link up areas
			linkLinks();

			//put in the items
			insertItems();
		}//constructor

		//**FEEL FREE TO ADD ADDITIONAL METHODS HERE**//
    void makeArea(){
			//cout<<"::In makeArea::"<<endl;

			int id;
			int goal;
			string xstr;
      
      AreaType* tempRmPtr = new AreaType;
			areaNode<AreaType>* tempNodePtr = new areaNode<AreaType>;
      tempNodePtr->info = *tempRmPtr;
			
			while(nextToken != "</area>"){
	
				if(nextToken == "<desc>"){
					parser.eatToken();
					nextToken = parser.getNext();
							
					tempNodePtr->info.setDescription(nextToken);
				}
				else if(nextToken == "<feats>"){
					parser.eatToken();
					nextToken = parser.getNext();
							
					istringstream ss(nextToken);
          getline(ss, xstr, ',');
          tempNodePtr->info.setID(atoi(xstr.c_str()));

          getline(ss, xstr, ',');
					tempNodePtr->info.setGoal(atoi(xstr.c_str()));
				}
				else if(nextToken == "</desc>" || nextToken == "</feats>"){
				  //do nothing
				}
				else{
					cout<<"Parse Error Location 2"<<endl;
					ifderr = true;
					break;
				}
			
				parser.eatToken();
				nextToken = parser.getNext();
			}//while !</area>
					
			//add area to vector
			areasVec.push_back(tempNodePtr);					
	
			//cout<<"::Finished </areas>"<<endl;
			//cout<<"::Number of Areas Found : " <<areasVec.size()<<" ::"<<endl;
		} //end makeArea()

		void makeLinks(){
			//cout<<"::In makeLinks::"<<endl;

			string xstr;
			int u, d, l, r;
			while(nextToken != "</links>"){
				if(nextToken == "<linkset>"){
					parser.eatToken();
			  	nextToken = parser.getNext();

					LinkData* tempLDPtr = new LinkData;
					
					istringstream ss(nextToken);
        	getline(ss, xstr, ',');
        	u = atoi(xstr.c_str());
        	getline(ss, xstr, ',');
        	d = atoi(xstr.c_str());
					getline(ss, xstr, ',');
        	l = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					r = atoi(xstr.c_str());

					tempLDPtr->setDigits(u, d, l, r);
          linkVec.push_back(tempLDPtr); 
   
				}
				else if(nextToken == "</linkset>"){
					//do nothing
				}
				else{
					cout<<"Parse Error Location 3"<<endl;
					ifderr = true;
					break;
				}
				parser.eatToken();
			  nextToken = parser.getNext();
			}//while !</links>
		}//makeLinks()

		void makeItem(){
			//cout<<"::In makeItem::"<<endl;
			Item* itmptr;
			itmptr = new Item;

			while(nextToken != "</item>"){
				//cout<<nextToken<<endl;
				if(nextToken == "<name>"){
					parser.eatToken();
			  	nextToken = parser.getNext();
					itmptr->setName(nextToken);
				}
				else if(nextToken == "<desc>"){
					parser.eatToken();
			  	nextToken = parser.getNext();
					itmptr->setDesc(nextToken);
				}
				else if(nextToken == "<star>"){
					parser.eatToken();
			  	nextToken = parser.getNext();
					itmptr->setSR(atoi(nextToken.c_str()));
				}
				else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</use>" || nextToken == "</edible>"){
					//do nothing
				}
				else{
					cout<<"Parse Error Location 4"<<endl;
					ifderr = true;
					break;
				}

				parser.eatToken();
			  nextToken = parser.getNext();
			}//while !</item>

		  itemsVec.push_back(itmptr);	
		} //makeItem()

		void linkLinks(){
			for(int i=0; i<linkVec.size(); i++){
					areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0))-1];
					areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1))-1];
					areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2))-1];
					areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3))-1];		
			}
		}

		void insertItems(){
			//clear any items from Areas
			for(int i=0; i<areasVec.size(); i++){
				areasVec[i]->info.items.initializeList();
			}
			//add items to appropriate start Areas
			for(int i=0; i<itemsVec.size(); i++){
				areasVec[(itemsVec[i]->getSR())-1]->info.items.insertLast(itemsVec[i]);
			}
		}

		areaNode<AreaType>* getStart(){
			return areasVec[0];  //returns a pointer to the first area listed
		}

		void print(){
			cout<<"******************************************************************"<<endl;
			cout<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
			cout<<"******************************************************************"<<endl;
			for(int i=0; i<areasVec.size(); i++){
				cout<<"This is area: "<<i+1<<endl;
				cout<<areasVec[i]->info.getDescription()<<endl;
				if(areasVec[i]->info.getID() == 1){
					cout<<"Area is INSTADEATH."<<endl;
				}
				if(areasVec[i]->info.getGoal() == 1){
					cout<<"Area is GOAL."<<endl;
				}
				cout<<"Connections:"<<endl;
				cout<<"\t u: Area #"<<reverseLookUp(areasVec[i]->u)<<endl;
				cout<<"\t d: Area #"<<reverseLookUp(areasVec[i]->d)<<endl;
				cout<<"\t l: Area #"<<reverseLookUp(areasVec[i]->l)<<endl;
				cout<<"\t r: Area #"<<reverseLookUp(areasVec[i]->r)<<endl; 
			}
		}

		int reverseLookUp(areaNode<AreaType>* addy){
      int num = 0;
			for(int i=0; i<areasVec.size(); i++){
				if(areasVec[i] == addy){
					num = i+1;		
            }	
			}
         return num;
		}

		void resetItems(){
			for(int i=0; i<areasVec.size(); i++){
				areasVec[i]->info.items.destroyList();		
			}
			//replace items to original areas lists
			for(int j=0; j<itemsVec.size(); j++){
				areasVec[(itemsVec[j]->getSR())-1]->info.items.insertLast(itemsVec[j]);
			}			
			//areasVec[strm-1]->info.items.insertLast(itmptr);
			//itemsVec.push_back(itmptr);
		}
};
