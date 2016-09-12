#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
/*
* Changes from HW4:
* Created a new class Headquarter
* Move  camp, warriorCts[5], units, campName[2]   from Warrior to Headquarter
* Add buildorder
* Headquarter and Warrior point to each other
* Move time to outside of the class
*/
using namespace std;
class Warrior;
class Dragon; 
class Ninja; 
class Iceman; 
class Lion; 
class Wolf;

const int NumWarrTypes = 5;
const int NumWeaponTypes = 3;

class Headquarter{
	private:
		int camp; // 0:red, 1:blue
		int warriorCts[NumWarrTypes];
		int totWarrNum;
		int units;
		int curBuildNum; // current building number in the building process 
		Dragon * dragonArmy[1000];
		Ninja * ninjaArmy[1000];
		Iceman * icemanArmy[1000];
		Lion * lionArmy[1000];
		Wolf * wolfArmy[1000];
		 
	public:
		friend class Warrior;
		const static string campName[2]; // 0:red, 1:blue
		const static int buildOrder[2][NumWarrTypes];
		Headquarter(int, int);
		~Headquarter();
		int getCamp() const {return camp;};
		int getUnits() const {return units;};
		int buildArmy(int);
};

Headquarter::Headquarter(int newCamp, int newUnits){
	camp = newCamp;
	units = newUnits;
	totWarrNum = 0;
	curBuildNum = 0;
	for(int i=0; i<NumWarrTypes; i++) warriorCts[i]=0;
	
}



class Warrior{
	private:
		int prof; // 0:"dragon", 1:"ninja", 2:"iceman", 3:"lion", 4:"wolf"
	protected:
		int id; // warrior's id number
		const Headquarter * head;
		int health;
	public:
		const static string profName[NumWarrTypes];
		const static string weaponName[NumWeaponTypes];
		static int sysHealth[NumWarrTypes]; // health units for each profession	
		Warrior(const Headquarter * , int , int);		
		int getId() const {return id;}
		int getCamp() const {return head->camp;}
		int getHealth() const {return sysHealth[prof];}
		int getProf() const {return prof;}
};

Warrior::Warrior(const Headquarter * newHead, int newProf, int time){				
		id = time + 1;		
		prof = newProf;			
		head = newHead;
		health = sysHealth[prof];
		
		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
		time,Headquarter::campName[head->camp].c_str(),profName[prof].c_str(),id,health, 
		head->warriorCts[prof], profName[prof].c_str(),Headquarter::campName[head->camp].c_str());	

}

class Dragon: public Warrior{
	private:
		float morale;
		int weapon; // 0: sword, 1: bomb, 2, arrow;
	public:
		Dragon(const Headquarter * newHead, int time): Warrior(newHead, 0, time){
			morale = 1.0 * head->getUnits() / health; 
			weapon = id % 3;
			// It has a arrow,and it's morale is 23.34
			printf("It has a %s,and it's morale is %.2f\n", weaponName[weapon].c_str(), morale);
		}
		float getMorale() const { return morale;}
		int getWeapon() const { return weapon;}
};
class Ninja: public Warrior{
	private:
		int weapon[2]; // 2 weapons
	public:
		Ninja(const Headquarter * newHead, int time): Warrior(newHead, 1, time){
			weapon[0] = id % 3;
			weapon[1] = (id+1) % 3;
			// It has a bomb and a arrow
			printf("It has a %s and a %s\n",weaponName[weapon[0]].c_str(),weaponName[weapon[1]].c_str());
		}
		const int * getWeapon() const {
			int * wp = new int[2];
			memcpy(wp, weapon,sizeof(int)*2);
			return wp;
		}
};
class Iceman: public Warrior{
	private:
		int weapon; 
	public:
		Iceman(const Headquarter * newHead, int time): Warrior(newHead, 2, time){
			weapon = id % 3;
			// It has a sword
			printf("It has a %s\n", weaponName[weapon].c_str());
		}
		int getWeapon() const { return weapon;}
};
class Lion: public Warrior{
	private:
		int loyalty;
	public:
		Lion(const Headquarter * newHead, int time): Warrior(newHead, 3, time){
			loyalty = head->getUnits();
			// It's loyalty is 24
			printf("It's loyalty is %d\n", loyalty);
		}
		int getLoyalty() const { return loyalty;}
};
class Wolf: public Warrior{
	public:
		Wolf(const Headquarter * newHead, int time): Warrior(newHead, 4, time){}
};

Headquarter::~Headquarter () {
	for( int i = 0; i < warriorCts[0]; i ++ ) delete dragonArmy[i];
	for( int i = 0; i < warriorCts[1]; i ++ ) delete ninjaArmy[i];
	for( int i = 0; i < warriorCts[2]; i ++ ) delete icemanArmy[i];
	for( int i = 0; i < warriorCts[3]; i ++ ) delete lionArmy[i];
	for( int i = 0; i < warriorCts[4]; i ++ ) delete wolfArmy[i];
}


int Headquarter::buildArmy(int time){
	int prof = buildOrder[camp][curBuildNum];		
	for(int j = 0; j < NumWarrTypes; j++){
		int k = (curBuildNum + j) % NumWarrTypes;
		prof = buildOrder[camp][k];
		if(units >= Warrior::sysHealth[prof]){	
			units -= Warrior::sysHealth[prof];
			warriorCts[prof] ++;	
			if (prof == 0) dragonArmy[warriorCts[prof] -1] = new Dragon(this, time);
			if (prof == 1) ninjaArmy[warriorCts[prof] -1] = new Ninja(this, time);
			if (prof == 2) icemanArmy[warriorCts[prof] -1] = new Iceman(this, time);
			if (prof == 3) lionArmy[warriorCts[prof] -1] = new Lion(this, time);
			if (prof == 4) wolfArmy[warriorCts[prof] -1] = new Wolf(this, time);			
			totWarrNum ++;			
			curBuildNum = (k + 1) % NumWarrTypes;
			return 1;
		}			
	}
	printf("%03d %s headquarter stops making warriors\n", time, campName[camp].c_str());
	return 0;
}

const string Headquarter::campName[2] = {"red","blue"};
const int Headquarter::buildOrder[2][NumWarrTypes] = {{2,3,4,1,0}, {3,0,1,2,4}};	
const string Warrior::profName[NumWarrTypes] = {"dragon", "ninja", "iceman", "lion", "wolf"};
const string Warrior::weaponName[NumWeaponTypes] = {"sword", "bomb", "arrow"};
int Warrior::sysHealth[NumWarrTypes];

int main(){
	int TotCaseNo;
	scanf("%d",&TotCaseNo);
	int caseUnits;
	int time = 0;
	
	for(int i=0;i<TotCaseNo;i++){
		scanf("%d",&caseUnits);
		Headquarter red(0,caseUnits), blue(1,caseUnits);
		for(int j=0; j<NumWarrTypes; j++){
			scanf("%d",&Warrior::sysHealth[j]);
		}
		cout << "Case:" << i+1 << endl;
		
		int check[2] = {1,1};
		while(check[0] || check[1]){		
			if(check[0]) check[0] = red.buildArmy(time);
			if(check[1]) check[1] = blue.buildArmy(time);
			time++;
		}
		
		time = 0;
	}
	
	return 0;
}





