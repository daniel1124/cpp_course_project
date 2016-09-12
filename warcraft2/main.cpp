#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Warrior{
	int id; // warrior's id number
	int camp; // 0:red, 1:blue
	int prof; // 0:"dragon", 1:"ninja", 2:"iceman", 3:"lion", 4:"wolf"
 	int health; // 0 < health <= 100
	
	public:
	const static string campName[2];
	const static string profName[5];
	static int units[2]; // total health units
	static int sysHealth[5]; // health units for each profession
	static int warriorCts[2][5]; // count warrior number for each camp and profession
	static int time; 
	
	Warrior(int newCamp, int newProf, int newHealth);
	int getId();
	int getCamp();
	int getProf();
	int getHealth();
};

Warrior::Warrior(int newCamp, int newProf, int newHealth){
	if (units[newCamp] >= newHealth ){		
		id = time + 1;
		camp = newCamp;
		prof = newProf;
		health = newHealth;	
		
		units[camp] -= health;
		warriorCts[camp][prof] += 1;
		
		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",time,campName[camp].c_str(),
			profName[prof].c_str(),id,health, warriorCts[camp][prof], profName[prof].c_str(), campName[camp].c_str());
		//000 red iceman 1 born with strength 5,1 iceman in red headquarter
	}
	else cout<< "Not enough units!" << endl;
}

int Warrior::getId(){
	return id;
}
int Warrior::getCamp(){
	return camp;
}
int Warrior::getHealth(){
	return health;
}
int Warrior::getProf(){
	return prof;
}


const string Warrior::campName[2] = {"red","blue"};
const string Warrior::profName[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Warrior::units[2]; // total health units
int Warrior::sysHealth[5];
int Warrior::warriorCts[2][5]; // count the warrior number for each camp and profession
int Warrior::time = 0; 
void buildArmy();
int buildAlter(int & i, int camp, const int (&buildOrder)[5]);

int main()
{
	int caseNum;
	char temp[100];
	gets(temp);
	caseNum = atoi(temp);
	
	int caseUnits[caseNum];
	int caseSysHealth[caseNum][5];
	
	
	for (int i=0;i<caseNum;i++){
		if(gets(temp)) caseUnits[i] = atoi(temp);	
		if(gets(temp)) sscanf(temp,"%d %d %d %d %d", caseSysHealth[i], caseSysHealth[i]+1, caseSysHealth[i]+2, 
			caseSysHealth[i]+3, caseSysHealth[i]+4);	
	}

	for(int i=0;i<caseNum;i++){
		Warrior::units[0] = Warrior::units[1] = caseUnits[i];
		for(int j=0;j<5;j++){
			Warrior::sysHealth[j] = caseSysHealth[i][j];	
		}		
		cout << "Case:" << i+1 << endl;
		buildArmy();
		Warrior::time = 0;
		for(int j =0;j<5;j++){
			
			Warrior::warriorCts[0][j] = Warrior::warriorCts[1][j] = 0;
		}
		
	}
	
	return 0;
}



void buildArmy(){
	// red 2:iceman, 3:lion, 4:wolf, 1:ninja, 0:dragon
	// blue 3:lion, 0:dragon, 1:ninja, 2:iceman, 4:wolf
	int buildOrder[2][5] = {{2,3,4,1,0}, {3,0,1,2,4}};	
	int buildCheck[2] = {1,1};
	int i[2] = {0,0};
	while(buildCheck[0] == 1 | buildCheck[1] == 1){							
			for (int camp=0; camp<2; camp++){
				if(buildCheck[camp] == 1){
					int prof = buildOrder[camp][ i[camp] % 5 ];
					if(Warrior::units[camp] >= Warrior::sysHealth[prof]){
						Warrior man1(camp, prof, Warrior::sysHealth[prof]);
						i[camp] ++;
					}						
					else buildCheck[camp] = buildAlter(i[camp], camp, buildOrder[camp]);	
				}				
			}
			Warrior::time += 1;			
		
	}
}

int buildAlter(int & i, int camp, const int (&buildOrder)[5]){
	for(int j = (i%5)+1; j < (i%5)+5; j++){
		int k = j % 5;		
		int prof = buildOrder[k];
		if(Warrior::units[camp] >= Warrior::sysHealth[prof]){
			Warrior man1(camp, prof, Warrior::sysHealth[prof]);
			i = k + 1;
			return 1;
		}		
	}
	//003 red headquarter stops making warriors
	printf("%03d %s headquarter stops making warriors\n", Warrior::time, Warrior::campName[camp].c_str());
	return 0;
}
