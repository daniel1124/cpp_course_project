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

const int NumWarrTypes = 5;

class Headquarter{
	int camp; // 0:red, 1:blue
	int totWarrNum;
	int warriorCts[NumWarrTypes];
	int units;
	int curBuildNum; // current building number in the building process 
	Warrior * army[1000];
	
	public:
	friend class Warrior;
	const static string campName[2]; // 0:red, 1:blue
	const static int buildOrder[2][NumWarrTypes];
	Headquarter(int, int);
	~Headquarter();
	int getCamp();
	int getUnits();
	int buildArmy(int);
};

class Warrior{
	int id; // warrior's id number
	const Headquarter * head;
	int prof; // 0:"dragon", 1:"ninja", 2:"iceman", 3:"lion", 4:"wolf"
	
	public:
	const static string profName[NumWarrTypes];
	static int sysHealth[NumWarrTypes]; // health units for each profession
	
	Warrior(const Headquarter * , int , int);
	int getId();
	int getCamp();
	int getProf();
	int getHealth();
};

Warrior::Warrior(const Headquarter * newHead, int newProf, int time){
	if (newHead->units >= sysHealth[newProf] ){		
		id = time + 1;		
		prof = newProf;			
		head = newHead;
		
		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",time,Headquarter::campName[head->camp].c_str(),
			profName[prof].c_str(),id,sysHealth[prof], head->warriorCts[prof], profName[prof].c_str(), Headquarter::campName[head->camp].c_str());
		//000 red iceman 1 born with strength 5,1 iceman in red headquarter
	}
	else cout<< "Not enough units!" << endl;
}

int Warrior::getId(){
	return id;
}
int Warrior::getCamp(){
	return head->camp;
}
int Warrior::getHealth(){
	return sysHealth[prof];
}
int Warrior::getProf(){
	return prof;
}

Headquarter::Headquarter(int newCamp, int newUnits){
	camp = newCamp;
	units = newUnits;
	totWarrNum = 0;
	curBuildNum = 0;
	for(int i=0; i<NumWarrTypes; i++) warriorCts[i]=0;
}

Headquarter::~Headquarter () {
	for( int i = 0; i < totWarrNum; i ++ )
		delete army[i];
}

int Headquarter::getCamp(){
	return camp;
}

int Headquarter::getUnits(){
	return units;
}

int buildArmy(int time){

}




const string Headquarter::campName[2] = {"red","blue"};
const int Headquarter::buildOrder[2][NumWarrTypes] = {{2,3,4,1,0}, {3,0,1,2,4}};	
const string Warrior::profName[NumWarrTypes] = {"dragon", "ninja", "iceman", "lion", "wolf"};
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


int Headquarter::buildArmy(int time){
	int prof = buildOrder[camp][curBuildNum];		
	for(int j = 0; j < NumWarrTypes; j++){
		int k = (curBuildNum + j) % NumWarrTypes;
		prof = buildOrder[camp][k];
		if(units >= Warrior::sysHealth[prof]){
			totWarrNum ++;
			warriorCts[prof] ++;
			army[totWarrNum] = new Warrior(this, prof, time);
			units -= Warrior::sysHealth[prof];
			curBuildNum = (k + 1) % NumWarrTypes;
			return 1;
		}			
	}
	printf("%03d %s headquarter stops making warriors\n", time, campName[camp].c_str());
	return 0;
}

