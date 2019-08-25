#include <string>
#include <iostream>

using namespace std;

class Item{
  public:
    void setName (string n){
    	name = n;
    }
		void setDesc(string desc){
			description = desc;		
		}
		void setSR(int rm){
			startRoom = rm;		
		}
		string getName(){
    	return name;
    }
    string getDesc(){
    	return description;
    }
    int getSR(){
			return startRoom;
		}
		void displayName(){
			cout<<name<<endl;		
		}
		void displayDesc(){
			cout<<description<<endl;		
		}

		friend ostream& operator<<(ostream&, Item&);
    
  private:
		string name;
    string description;
		int startRoom;
};

ostream& operator<<(ostream& osObject, Item& item)
{
	osObject<<"Name: "<<item.getName()<<endl;
	osObject<<"Desc: "<<item.getDesc()<<endl;
	osObject<<"StrtRm: "<<item.getSR()<<endl;
   return osObject;
}
