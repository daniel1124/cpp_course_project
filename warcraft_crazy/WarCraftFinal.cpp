#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;
class Warrior;
class Weapon;

const int NumWarrTypes = 5;
const int NumWeaponTypes = 3;

class City{
	protected:
		int camp; // 0:red, 1:blue, -1:unsided
		int units;	
		int arrival[2]; // 1st item for red, 2nd for blue, store the id, 0 if nobody
		int winCt[2]; // red blue
		int dadie;
	public:
		const static string campName[2]; // 0:red, 1:blue
		static int numCities;
		static int hour;
		static int token[2];
		int getCamp() const {return camp;};
		void setCamp(int newCamp){camp = newCamp;}
		int getUnits() const {return units;};
		void addUnits(int inc) {units+=inc;}
		void setUnits(int u){units = u;}
		City(int newUnits, int newCamp = -1):camp(newCamp),units(newUnits){
			arrival[0] = arrival[1] = 0;
			winCt[0] = winCt[1] = 0;
		}
		const int * getArrival() const {return arrival;}
		void setArrival(int camp, int id){ arrival[camp] = id;}
		void setWinCt(int camp, int x){winCt[camp] = x;}
		void addWinCt(int camp, int x){winCt[camp]+= x;}
		void setDoubleArrowDie(int val){dadie=val;}
		int getDoubleArrowDie(){return dadie;}
		const int * getWinCt() const {return winCt;}
		virtual ~City(){}
		virtual void buildArmy(int hr){}
		virtual Warrior ** getArmy() {cout << "ha"<<endl;}
		virtual int getTotWarrNum() const {}
		virtual void setEnimy2(int){}
		virtual int getEnimy2(){}
};

class Headquarter: public City{
	private:
		int warriorCts[NumWarrTypes];
		// 1st item for self, 2nd for 1st enimy, 3rd for 2nd enimy
		int totWarrNum;
		int curBuildNum; // current building number in the building process 
		int enimy2; // the second enimy's id
	public:	Warrior * army[1000];		
	public:
		friend class Warrior;
		const static int buildOrder[2][NumWarrTypes];
		int getTotWarrNum() const{return totWarrNum;}
		void setEnimy2(int id){enimy2 = id;}
		int getEnimy2(){return enimy2;}
		Headquarter(int, int);
//		~Headquarter();
		void buildArmy(int);
		Warrior ** getArmy() {return army;}
};
Headquarter::Headquarter(int newUnits, int newCamp):City(newUnits,newCamp){
	if(newCamp == -1) cout << "Headquarter can't be unsided!" << endl;
	totWarrNum = 0;
	curBuildNum = 0;
	enimy2 = 0; 
	arrival[0] = arrival[1] = arrival[2] = 0;
	for(int i=0; i<NumWarrTypes; i++) warriorCts[i]=0;
}
//Headquarter::~Headquarter () {
//	for(int i = 0; i < totWarrNum; i ++ ) delete army[i];
//}

//class Cities{
//	private:
//		int numCities;
//		City * p[100];
//	public:
//		Cities(int nC, int newUnits){
//			numCities = nC;
//			//p = new City*[numCities+2];
//			p[0] = new Headquarter(newUnits,0);
//			p[numCities+1] = new Headquarter(newUnits,1);
//			for(int i=1; i<=numCities; i++) p[i] = new City(0); 
//		}
//		City * operator[](int i){
//			return p[i];
//		}
//		int getNumCities() const{return numCities;}
//};

class Warrior{
	protected:
		int id; // warrior's id number
		const Headquarter * head;
//		const Cities * myWorld;
		int curCity; // which city or headquarter it is currently located at 0~N+1
		int reach; // 1: reach the animy headquarter, 0 otherwise
		int health;
		int prof;
		int death; // 1: dead, 0: alive
		int run; // 1: ran, 0: didn't run
		int force;
		int numWeapons; // number of weapons the warrior has
		Weapon * myWeapon[NumWeaponTypes];
		int weaponStat[NumWeaponTypes]; // sword, bomb, arrow; 0: no such weapon, 1,2,3 ith weapon is such weapon
	public:
		const static string profName[NumWarrTypes];
		const static string weaponName[NumWeaponTypes];
		static int sysHealth[NumWarrTypes]; // Initial health units for each profession	
		static int sysWarrForce[NumWarrTypes]; // Initial force for each profession
		static int lionLoyaltyDe;
		Warrior(const Headquarter * , int , int);	
		virtual ~Warrior(){}
		bool isDead(){return death==1;}
		bool isReach(){return reach ==1;}
		void kill(){death =1;health=0;}
		bool isRun(){return run==1;}
		int getId() const {return id;}
		int getCamp() const {return head->camp;}
		int getHealth() const {return health;}
		int getCurCity() const {return curCity;}
		virtual void setHealth(int incre) { health += incre;}
		const int * getWeapStat() const {return weaponStat;}
		void setWeapStat(int index, int val){weaponStat[index] = val;}
		Weapon ** getWeapon() { return myWeapon;}
		int getProf() const {return prof;}
		int getForce() const {return force;}
		virtual void attack(Warrior & man){}
		virtual void hurted(int force){}
		virtual void fightback(Warrior & man){}
		virtual void afterFight(Warrior & man){}
		virtual void setPreHealth(int val){}
		virtual int getLoyalty() const{}
		virtual int getPreBatHealth(){}
		virtual void disert(){}
		virtual int walk(){ // return 0:didn't walk, 1: walked
			if(reach == 0 and !isRun() and !isDead() ){
				if(head->camp == 0){
					curCity ++;
						
					if(curCity == City::numCities+1) reach = 1;
				}	
				else{
					curCity --;
					if(curCity == 0) reach = 1;
				}
//				printf("%s %d*****%d*****\n",Warrior::profName[prof].c_str(),id,isDead());
				return 1;
			}
			else return 0;
		}
		static Warrior * makeWarrior(Headquarter *, int, int);
		
};
Warrior::Warrior(const Headquarter * newHead, int newProf, int time){				
//		id = time + 1;		
	
		prof = newProf;			
		head = newHead;
		id = head->getTotWarrNum()+1;
		if(head->camp==0) curCity = 0;
		else curCity = City::numCities + 1;
		reach = 0;
		health = sysHealth[prof];
		death = 0;
		run = 0;
		force = sysWarrForce[prof];
		for(int i=0;i<NumWeaponTypes;i++) weaponStat[i] = 0;
		printf("%03d:00 %s %s %d born\n",time,Headquarter::campName[head->camp].c_str(),profName[prof].c_str(),id);
//		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
//		time,Headquarter::campName[head->camp].c_str(),profName[prof].c_str(),id,health, 
//		head->warriorCts[prof], profName[prof].c_str(),Headquarter::campName[head->camp].c_str());	
		
}

class Weapon{
	private:
		int type; // 0:sword, 1:bomb, 2:arrow
	protected:
		int exist; // 1: still usable, 0: destroyed or not usable	
		int force;
		Warrior * myOwner; // pointing to the owner
	public:
		int getType() const{return type;}
		int getForce() const{return force;}
		void changeOwner(Warrior * newOwner){myOwner = newOwner;}
		Weapon(Warrior * newOwner, int newType, int newForce):
			myOwner(newOwner),type(newType),force(newForce){exist = 1;}
		static Weapon * makeWeapon(Warrior *, int);
		static int arrowForce;
		virtual void use(Warrior & man){}
		virtual int getNumLeft(){}
		virtual void redForce(){}
		virtual void setExist(){}
};

class Sword: public Weapon{
	public:
		void use(Warrior & man){
			man.hurted(myOwner->getForce() + force);
			man.fightback(*myOwner);
			myOwner->afterFight(man);
			redForce();	
		}
		Sword(Warrior * newOwner):Weapon(newOwner, 0, int(newOwner->getForce()*0.2)){}
		void redForce(){
			force = int(force*0.8);
			if (force <= 0){
				exist = 0; 	
				myOwner->setWeapStat(0,0);
			} 		
		}
};

class Bomb: public Weapon{
	public:
		Bomb(Warrior * newOwner):Weapon(newOwner, 1, 100000000){}
		void use(Warrior & man){			
			man.kill();
			myOwner->kill();
			exist = 0;
			myOwner->setWeapStat(1,0);
		}
};

class Arrow: public Weapon{
	private:
		int numLeft; // number of arrows left. 0~3
	public:
		Arrow(Warrior * newOwner):Weapon(newOwner, 2, arrowForce){numLeft=3;}
		int getNumLeft(){return numLeft;}
		void use(Warrior & man){
			man.setHealth(-force);
			if(man.getHealth()<=0){
				man.kill();
				man.setPreHealth(0);
			}
			else man.setPreHealth(man.getHealth());
			numLeft --;
			if(numLeft <= 0) {
				exist = 0;
				myOwner->setWeapStat(2,0);
			}		
		}
};

Weapon * Weapon::makeWeapon(Warrior * newOwner, int newType){
	if(newType == 0) return new Sword(newOwner);
	if(newType == 1) return new Bomb(newOwner);
	if(newType == 2) return new Arrow(newOwner);
}

class Dragon: public Warrior{
	private:
		float morale;
	public:
		Dragon(const Headquarter * newHead, int time): Warrior(newHead, 0, time){
			morale = 1.0 * head->getUnits() / health; 
			myWeapon[id%3] = Weapon::makeWeapon(this, id % 3);
			weaponStat[id % 3]++;
			numWeapons = 1;
			if(id%3 ==0 and myWeapon[id%3]->getForce()==0 ){
				weaponStat[0] = 0;
				numWeapons = 0;	
			}
			// It has a arrow,and it's morale is 23.34
			printf("Its morale is %.2f\n", morale);
		}
		~Dragon(){} // modify
		float getMorale() const { return morale;}
		Weapon ** getWeapon() { return myWeapon;}
		
		void attack(Warrior & man){
			if (weaponStat[0]) myWeapon[0]->use(man);
			else{
				man.hurted(force);
				man.fightback(*this);
				afterFight(man);
			} 
		}
		
		void afterFight(Warrior & man){
//		003:40 blue dragon 2 yelled in city 4
			if(health>0){
				if(man.isDead()) morale += 0.2;
				else morale -= 0.2;
				if(morale > 0.8) 
					printf("%03d:40 %s %s %d yelled in city %d\n", City::hour,City::campName[getCamp()].c_str(),
						Warrior::profName[prof].c_str(),id,curCity);
			}
		}
		
		void hurted(int force){
			health -= force;
			if (health <= 0){
				kill();
//				001:40 red lion 2 was killed in city 1
				printf("%03d:40 %s %s %d was killed in city %d\n",City::hour,City::campName[getCamp()].c_str(),
					Warrior::profName[prof].c_str(),id,curCity);
			}
		
		}
		void fightback(Warrior & man){
			if(death==0){
				int backForce = force/2;
				if(weaponStat[0]){
					backForce += myWeapon[0]->getForce(); 
					myWeapon[0]->redForce();
				} 
				printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
					City::hour,City::campName[head->getCamp()].c_str(),Warrior::profName[prof].c_str(),id,City::campName[man.getCamp()].c_str(),
					Warrior::profName[man.getProf()].c_str(),man.getId(),curCity);
				man.hurted(backForce);
			
			}
		}
		
};
class Ninja: public Warrior{
	private:
	public:
		Ninja(const Headquarter * newHead, int time): Warrior(newHead, 1, time){
			myWeapon[id%3] = Weapon::makeWeapon(this, id % 3);
			myWeapon[(id+1)%3] = Weapon::makeWeapon(this, (id+1) % 3);
			numWeapons = 2;
			weaponStat[id % 3] ++;
			weaponStat[(id+1) % 3] ++;
			if((id%3 ==0 and myWeapon[id%3]->getForce()==0) or 
				((id+1)%3 ==0 and myWeapon[(id+1)%3]->getForce()==0) ){
				weaponStat[0] = 0;
				numWeapons --;	
			}
			// It has a bomb and a arrow
//			printf("It has a %s and a %s\n",weaponName[id % 3].c_str(),weaponName[(id+1) % 3].c_str());
		}
		~Ninja(){} //modify
		Weapon ** getWeapon() { return myWeapon;}
		void attack(Warrior & man){
			if (weaponStat[0]) myWeapon[0]->use(man);
			else{
				man.hurted(force);
				man.fightback(*this);
			} 
		}
		void hurted(int force){
			health -= force;
			if (health <= 0){
				kill();
				printf("%03d:40 %s %s %d was killed in city %d\n",City::hour,City::campName[getCamp()].c_str(),
					Warrior::profName[prof].c_str(),id,curCity);
			} 
		}
		void fightback(Warrior & man){}
		
};
class Iceman: public Warrior{
	private:
		int step;
		void stepfun(){
			step++;
			if(step == 2){
				step = 0;
				force += 20;
				if (health > 9) health -= 9;
				else health = 1;
			}
		}
	public:
		Iceman(const Headquarter * newHead, int time): Warrior(newHead, 2, time){
			myWeapon[id%3] = Weapon::makeWeapon(this, id % 3);
			numWeapons = 1;
			weaponStat[id % 3]++;
			if(id%3 ==0 and myWeapon[id%3]->getForce()==0 ){
				weaponStat[0] = 0;
				numWeapons = 0;	
			}
			step = 0;
			// It has a sword
//			printf("It has a %s\n", weaponName[myWeapon[id%3]->getType()].c_str());
		}
		~Iceman(){} // modify
		Weapon ** getWeapon() { return myWeapon;}
		
		void attack(Warrior & man){
	//		printf("****before attack preh:%d****\n",man.getPreBatHealth());
			if (weaponStat[0]) myWeapon[0]->use(man);
			else{
				man.hurted(force);
				man.fightback(*this);
			} 
		}
		void hurted(int force){
			health -= force;
			if (health <= 0){
				kill();
				printf("%03d:40 %s %s %d was killed in city %d\n",City::hour,City::campName[getCamp()].c_str(),
					Warrior::profName[prof].c_str(),id,curCity);
			} 
		}
		void fightback(Warrior & man){
			if(death==0){
				int backForce = force/2;
				if(weaponStat[0]){
					backForce += myWeapon[0]->getForce(); 
					myWeapon[0]->redForce();
				} 
				printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
					City::hour,City::campName[head->getCamp()].c_str(),Warrior::profName[prof].c_str(),id,City::campName[man.getCamp()].c_str(),
					Warrior::profName[man.getProf()].c_str(),man.getId(),curCity);
				man.hurted(backForce);
			}
		}
		
		int walk(){
			int i = Warrior::walk();
			if(i==1) stepfun();
			return i;
		}
		
};
class Lion: public Warrior{
	private:
		int loyalty;
		int preBatHealth;
	public:
		Lion(const Headquarter * newHead, int hour): Warrior(newHead, 3, hour){
			loyalty = head->getUnits();
			preBatHealth = health;
			numWeapons = 0;
			run = 0;
			// It's loyalty is 24
			printf("Its loyalty is %d\n", loyalty);
		}
		~Lion(){} // modify
		void disert(){run = 1;}
		int getLoyalty() const { return loyalty;}
		void attack(Warrior & man){	
				man.hurted(force);
				man.fightback(*this);
		}
		void hurted(int force){		
			health -= force;
			if (health <= 0){
				kill();
				printf("%03d:40 %s %s %d was killed in city %d\n",City::hour,City::campName[getCamp()].c_str(),
					Warrior::profName[prof].c_str(),id,curCity);
			}
			else preBatHealth = health;
		}
		void fightback(Warrior & man){
			if(death==0){
				printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
					City::hour,City::campName[head->getCamp()].c_str(),Warrior::profName[prof].c_str(),id,City::campName[man.getCamp()].c_str(),
					Warrior::profName[man.getProf()].c_str(),man.getId(),curCity);
				man.hurted(force/2);
			}
		}
		void afterFight(Warrior & man){
			if (!isDead()){
				if(!man.isDead()) {
					loyalty -= lionLoyaltyDe;
				}
			//	if (reach == 0 and loyalty <= 0) disert(); 
			}
			else if(!man.isDead()){
				man.setHealth(preBatHealth);
			}
		}
		void setPreHealth(int val){preBatHealth = val;}
		int getPreBatHealth(){return preBatHealth;}
		void setHealth(int incre) { health += incre; preBatHealth = health;}
};
class Wolf: public Warrior{
	public:
		Wolf(const Headquarter * newHead, int hour): Warrior(newHead, 4, hour){
			numWeapons = 0;
		}
		~Wolf(){} // modify
		Weapon ** getWeapon() { return myWeapon;}
		void attack(Warrior & man){	
			if(weaponStat[0]) myWeapon[0]->use(man);
			else{
				man.hurted(force);
				man.fightback(*this);
				afterFight(man);
			}
		}
		void hurted(int force){			
			health -= force;
			if (health <= 0){
				kill();
				printf("%03d:40 %s %s %d was killed in city %d\n",City::hour,City::campName[getCamp()].c_str(),
					Warrior::profName[prof].c_str(),id,curCity);
			} 
		}
		void fightback(Warrior & man){
			if(death==0){
				int backForce = force/2;
				if(weaponStat[0]){
					backForce += myWeapon[0]->getForce(); 
					myWeapon[0]->redForce();
				}
				printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
					City::hour,City::campName[head->getCamp()].c_str(),Warrior::profName[prof].c_str(),id,City::campName[man.getCamp()].c_str(),
					Warrior::profName[man.getProf()].c_str(),man.getId(),curCity);
				man.hurted(backForce);
			}
		}
		void afterFight(Warrior & man){
			if (man.isDead() ){
				for(int i=0;i<NumWeaponTypes;i++){
					if (weaponStat[i] < man.getWeapStat()[i]) {
						myWeapon[i] = man.getWeapon()[i];
						numWeapons ++;
						weaponStat[i]++;
						myWeapon[i]->changeOwner(this);
					}
				}
			}
		}
};

Warrior * Warrior::makeWarrior(Headquarter * newHead, int newProf, int hour){
	if(newProf == 0) return new Dragon(newHead,hour);
	if(newProf == 1) return new Ninja(newHead,hour);
	if(newProf == 2) return new Iceman(newHead,hour);
	if(newProf == 3) return new Lion(newHead,hour);
	if(newProf == 4) return new Wolf(newHead,hour);
}

void Headquarter::buildArmy(int hour){
	int prof = buildOrder[camp][curBuildNum];		
	if(units >= Warrior::sysHealth[prof]){	
		units -= Warrior::sysHealth[prof];
		warriorCts[prof] ++;	
		army[totWarrNum] = Warrior::makeWarrior(this, prof, hour);
		setArrival(camp,army[totWarrNum]->getId());
		totWarrNum ++;			
		curBuildNum = (curBuildNum + 1) % NumWarrTypes;		
	}			
	//printf("%03d %s headquarter stops making warriors\n", hour, campName[camp].c_str());
}

const string City::campName[2] = {"red","blue"};
int City::numCities;
const int Headquarter::buildOrder[2][NumWarrTypes] = {{2,3,4,1,0}, {3,0,1,2,4}};	
const string Warrior::profName[NumWarrTypes] = {"dragon", "ninja", "iceman", "lion", "wolf"};
const string Warrior::weaponName[NumWeaponTypes] = {"sword", "bomb", "arrow"};
int Warrior::sysHealth[NumWarrTypes];
int Warrior::sysWarrForce[NumWarrTypes];
int Weapon::arrowForce; 
int Warrior::lionLoyaltyDe;
int City::token[2] = {0,0};
int City::hour;

void mainBuildArmy(City * world[], int hr){
// wait if not enough units
	world[0]->buildArmy(hr);
	world[City::numCities+1]->buildArmy(hr);
}

void mainLionRun(City * world[], int hr){
//	000:05 blue lion 1 ran away 
// run if loyalty <= 0; don't run if reach enimy's headquater
	int id[2];
	City *p[2];
	p[0] = world[0];
	p[1] = world[City::numCities+1];
	Warrior* man;
	for(int i=0;i<=City::numCities+1;i++){
		id[0] = world[i]->getArrival()[0]; // the recent born warrior's id 
		id[1] = world[i]->getArrival()[1];
		if(i==0) id[1]= 0;
		if(i==City::numCities+1) id[0]=0;
		for(int k=0;k<2;k++){
			if(id[k] != 0 ){
				man = p[k]->getArmy()[id[k]-1];
				if(man->getProf() == 3){ // it's a lion
//					printf("*****%s %s %d loyalty %d****\n",City::campName[man->getCamp()].c_str(),
//								Warrior::profName[man->getProf()].c_str(),id[k],man->getLoyalty());
					if(!man->isDead() ){
						if(man->getLoyalty() <= 0){
							man->disert();
							world[i]->setArrival(k,0);
							printf("%03d:05 %s %s %d ran away\n",hr,City::campName[man->getCamp()].c_str(),
								Warrior::profName[man->getProf()].c_str(),id[k]);
						}
					}
				}		
			} 	
		}
	}
}

void mainWalk(City * world[], int hr, int * T){
//	000:10 red iceman 1 marched to city 1 with 20 elements and force 30
// 001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
	Warrior* man;
	City *p[2];
	p[0] = world[0];
	p[1] = world[City::numCities +1];
	for(int k=0;k<2;k++)
		for(int i=0;i<p[k]->getTotWarrNum();i++){
			man = p[k]->getArmy()[i];
			if(man->walk()) {
				world[ man->getCurCity() - int(pow(-1,k)) ]->setArrival(k,0); 
				if(! man->isReach())
					world[ man->getCurCity() ]->setArrival(k,man->getId());
				else
					if(world[man->getCurCity()]->getArrival()[k] != 0){
						*T = 0;
						world[ man->getCurCity() ]->setEnimy2(man->getId());					
					}
					else
						world[ man->getCurCity() ]->setArrival(k,man->getId());
			}
		}		
	int camp,id;

	for(int i=0;i<=City::numCities+1;i++){
		if(i==0 or i==City::numCities+1){
			if(i==0) camp =0; else camp =1;
			id = world[i]->getEnimy2();
			if(id){
				man = p[1-camp]->getArmy()[id-1];
				printf("%03d:10 %s %s %d reached %s headquarter with %d elements and force %d\n",
					hr,City::campName[man->getCamp()].c_str(),Warrior::profName[man->getProf()].c_str(),
					man->getId(),City::campName[camp].c_str(),man->getHealth(),man->getForce());
				printf("%03d:10 %s headquarter was taken\n",hr,City::campName[camp].c_str());
			}
			else{
				id = world[i]->getArrival()[1-camp];
				if(id and City::token[camp]==0){
					City::token[camp]=1;
					man = p[1-camp]->getArmy()[id-1];
					printf("%03d:10 %s %s %d reached %s headquarter with %d elements and force %d\n",
						hr,City::campName[man->getCamp()].c_str(),Warrior::profName[man->getProf()].c_str(),
						man->getId(),City::campName[camp].c_str(),man->getHealth(),man->getForce());
				}
			} 
		}
		else{
			for(int k=0;k<2;k++){
				id = world[i]->getArrival()[k];
				if(id){
					man = p[k]->getArmy()[id-1];
					printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n",
						hr,City::campName[man->getCamp()].c_str(),Warrior::profName[man->getProf()].c_str(),
						man->getId(),man->getCurCity(),man->getHealth(),man->getForce());
				}
			}
		}
	}
}
void mainCityUpdate(City * world[], int hr){
	for(int i=1;i<=City::numCities;i++) world[i]->addUnits(10);
}
void mainTakeUnits(City * world[], int hr){
	int inc;
	Warrior * man;
	for(int i=1;i<=City::numCities;i++){
		const int* id = world[i]->getArrival();
		if(id[0] and !id[1]){
			inc = world[i]->getUnits();
			man = world[0]->getArmy()[id[0]-1];
			world[0]->addUnits(inc);
			world[i]->setUnits(0);	
//			001:30 blue dragon 2 earned 10 elements for his headquarter
			printf("%03d:30 red %s %d earned %d elements for his headquarter\n",
					hr,Warrior::profName[man->getProf()].c_str(),
					man->getId(),inc);
		}
		if(id[1] and !id[0]){
			inc = world[i]->getUnits();
			man = world[City::numCities+1]->getArmy()[id[1]-1];
			world[City::numCities+1]->addUnits(inc);
			world[i]->setUnits(0);	
			printf("%03d:30 blue %s %d earned %d elements for his headquarter\n",
					hr,Warrior::profName[man->getProf()].c_str(),
					man->getId(),inc);
		}
	}
}
void mainArrow(City * world[], int hr){
	Warrior * man;
	Warrior * other;
	City *p[2];
	p[0] = world[0];
	p[1] = world[City::numCities +1];
	for(int i=1;i<=City::numCities;i++){
		const int* id = world[i]->getArrival();
		for(int camp=0; camp<2;camp++){
			if( !(i==1 and camp==1) and !(i==City::numCities and camp==0) ){
				if(id[camp]){
					man = p[camp]->getArmy()[id[camp]-1];
					if(man->getWeapStat()[2] == 1){
						int otherId = world[i+int(pow(-1,camp))]->getArrival()[1-camp];
						if(otherId){
							other = p[1-camp]->getArmy()[otherId-1];
							man->getWeapon()[2]->use(*other);
	//						000:35 blue dragon 1 shot and killed red lion 4
							if(other->getHealth() <=0 )  	
								printf("%03d:35 %s %s %d shot and killed %s %s %d\n",
									hr,City::campName[man->getCamp()].c_str(),Warrior::profName[man->getProf()].c_str(),
									man->getId(),City::campName[other->getCamp()].c_str(),Warrior::profName[other->getProf()].c_str(),
									other->getId());
							else
								printf("%03d:35 %s %s %d shot\n",hr,City::campName[man->getCamp()].c_str(),
									Warrior::profName[man->getProf()].c_str(),man->getId());
						} 
					}
				}
			}
		}
	}
	for(int i=1;i<=City::numCities;i++){
		const int* id = world[i]->getArrival();
		if(id[0] and id[1]){
			man = p[0]->getArmy()[id[0]-1];
			other = p[1]->getArmy()[id[1]-1];
			if(man->isDead() and other->isDead()) world[i]->setDoubleArrowDie(1);
		}
	}
}

void mainBomb(City * world[], int hr){
	Warrior * man;
	Warrior * other;
	City *p[2];
	int init;
	int decision[2]={0,0}; // 1: use 0: not use
	p[0] = world[0];
	p[1] = world[City::numCities +1];
	for(int i=1;i<=City::numCities;i++){
		init = int(world[i]->getCamp()== 1 or (world[i]->getCamp()== -1 and i%2==0));
		const int* id = world[i]->getArrival();
		int manTotForce=0;
		int otherTotForce=0;
		if(id[0] and id[1]){
			man = p[init]->getArmy()[id[init]-1];
			other = p[1-init]->getArmy()[id[1-init]-1];
			if(!other->isDead()  and !man->isDead()){
				if(man->getWeapStat()[0] ==1){
					manTotForce = man->getWeapon()[0]->getForce() + man->getForce();
				}
				else manTotForce = man->getForce();
				if(other->getProf() == 1) otherTotForce =0;
				else{
					if(other->getWeapStat()[0] ==1) 
						otherTotForce = other->getWeapon()[0]->getForce() + other->getForce()/2;
					else otherTotForce = other->getForce()/2;
				}
				if(man->getWeapStat()[1]==1){
					if(manTotForce < other->getHealth() and otherTotForce >= man->getHealth()){
						decision[init]=1;
					}
				}
				if(other->getWeapStat()[1]==1){
					if(manTotForce >= other->getHealth() ) decision[1-init] =1;
				}
				for(int k=0;k<2;k++){
					if(decision[k]){
						man = p[k]->getArmy()[id[k]-1];
						other = p[1-k]->getArmy()[id[1-k]-1];
						man->getWeapon()[1]-> use(*other);	
//						000:38 blue dragon 1 used a bomb and killed red lion 7
						printf("%03d:38 %s %s %d used a bomb and killed %s %s %d\n",
							hr,City::campName[man->getCamp()].c_str(),Warrior::profName[man->getProf()].c_str(),
							man->getId(),City::campName[other->getCamp()].c_str(),Warrior::profName[other->getProf()].c_str(),
							other->getId());
					}
				}
				decision[0] = decision[1] =0;
			}
		}
	}
}
void mainFight(City * world[], int hr){
//	000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
//	001:40 blue dragon 2 fought back against red lion 2 in city 1
//  001:40 red lion 2 was killed in city 1
//  003:40 blue dragon 2 yelled in city 4
//  001:40 blue dragon 2 earned 10 elements for his headquarter
//  004:40 blue flag raised in city 4
	Warrior * man;
	Warrior * other;
	int liveAttack;
	City *p[2];
	p[0] = world[0];
	p[1] = world[City::numCities +1];
	int inc;
	for(int i=1;i<=City::numCities;i++){
		liveAttack = 0;
		int init = int(world[i]->getCamp()== 1 or (world[i]->getCamp()== -1 and i%2==0));
		const int* id = world[i]->getArrival();
		if(id[0] and id[1]){
			man = p[init]->getArmy()[id[init]-1];
			other = p[1-init]->getArmy()[id[1-init]-1];
			if(!man->isDead()){
				if(!other->isDead()){
					liveAttack = 1;
					printf("%03d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
						hr,City::campName[man->getCamp()].c_str(),Warrior::profName[man->getProf()].c_str(),
						man->getId(),City::campName[other->getCamp()].c_str(),Warrior::profName[other->getProf()].c_str(),
						other->getId(),i,man->getHealth(),man->getForce());
					man->attack(*other);
				}
				else if(man->getProf() == 0 or man->getProf() == 4) man->afterFight(*other);
			}
			else if(!other->isDead() and other->getProf() == 4) other->afterFight(*man); 
			
			if(man->getProf() == 3) {
				man->afterFight(*other);	
			}
			if(other->getProf() == 3){
				other->afterFight(*man);	
			} 
			
			man = p[0]->getArmy()[id[0]-1];
			other = p[1]->getArmy()[id[1]-1];
			if(!man->isDead() and other->isDead()){
				inc = world[i]->getUnits();
				printf("%03d:40 %s %s %d earned %d elements for his headquarter\n",
						hr,City::campName[man->getCamp()].c_str(),Warrior::profName[man->getProf()].c_str(),
						man->getId(),inc);
				if(world[i]->getWinCt()[1] == 1) world[i]->setWinCt(1,0);
				world[i]->addWinCt(0,1);
//				printf("********up:winCt red:%d blue:%d********\n",world[i]->getWinCt()[0],world[i]->getWinCt()[1]);
				if(world[i]->getWinCt()[0] == 2){
					world[i]->setWinCt(1,0);
					world[i]->setCamp(0);
//					world[i]->addWinCt(0,1);
					printf("%03d:40 %s flag raised in city %d\n",City::hour,City::campName[0].c_str(),i);
				}
				if(world[i]->getWinCt()[0] > 2){
					world[i]->setWinCt(0,2);
				}
			}
			else if(!other->isDead() and man->isDead()){
				inc = world[i]->getUnits();
				printf("%03d:40 %s %s %d earned %d elements for his headquarter\n",
					hr,City::campName[other->getCamp()].c_str(),Warrior::profName[other->getProf()].c_str(),
					other->getId(),inc);
				if(world[i]->getWinCt()[0] == 1) world[i]->setWinCt(0,0);
				world[i]->addWinCt(1,1);
//				printf("********down:winCt red:%d blue:%d********\n",world[i]->getWinCt()[0],world[i]->getWinCt()[1]);
				if(world[i]->getWinCt()[1] == 2){
					world[i]->setWinCt(0,0);
					world[i]->setCamp(1);
//					world[i]->addWinCt(1,1);
//					004:40 blue flag raised in city 4
					printf("%03d:40 %s flag raised in city %d\n",City::hour,City::campName[1].c_str(),i);
				}
				if(world[i]->getWinCt()[1] > 2){
					world[i]->setWinCt(1,2);
				}
			}
			else if(!other->isDead() and !man->isDead()){
				if(world[i]->getWinCt()[0] == 1) world[i]->setWinCt(0,0);
				if(world[i]->getWinCt()[1] == 1) world[i]->setWinCt(1,0);	
			}
			else{
				if(liveAttack == 1 ){
					if(world[i]->getWinCt()[0] == 1) world[i]->setWinCt(0,0);
					if(world[i]->getWinCt()[1] == 1) world[i]->setWinCt(1,0);
//					world[i]->setDoubleArrowDie(0);
				}
			}
		}
	}

}

void mainAfter(City * world[], int hr){
	Warrior * man;
	Warrior * other;
	City *p[2];
	p[0] = world[0];
	p[1] = world[City::numCities +1];
	for(int i=1;i<=City::numCities;i++){
		const int* id = world[i]->getArrival();
		if(id[0] and id[1]){
			man = p[0]->getArmy()[id[0]-1];
			other = p[1]->getArmy()[id[1]-1];
			if(!man->isDead() and other->isDead()){
				if(p[0]->getUnits() >= 8 ){
					man->setHealth(8);
					p[0]->addUnits(-8);
				}
			}
		}
	}
	for(int i=City::numCities;i>=1;i--){
		const int* id = world[i]->getArrival();
		if(id[0] and id[1]){
			man = p[0]->getArmy()[id[0]-1];
			other = p[1]->getArmy()[id[1]-1];
			if(!other->isDead() and man->isDead()){
				if(p[1]->getUnits() >= 8 ){
					other->setHealth(8);
					p[1]->addUnits(-8);
				}
			}
		}
	}
//	001:40 blue dragon 2 earned 10 elements for his headquarter
	int inc;
	for(int i=1;i<=City::numCities;i++){
		const int* id = world[i]->getArrival();
		if(id[0] and id[1]){
			man = p[0]->getArmy()[id[0]-1];
			other = p[1]->getArmy()[id[1]-1];
			if(!man->isDead() and other->isDead()){
				inc = world[i]->getUnits();
				p[0]->addUnits(inc);
				world[i]->setUnits(0);	
			}
			else if(!other->isDead() and man->isDead()){
				inc = world[i]->getUnits();
				p[1]->addUnits(inc);
				world[i]->setUnits(0);
			}
		}
		if(id[0]){
			man = p[0]->getArmy()[id[0]-1];
			if(man->isDead()) world[i]->setArrival(0,0);
		}
		if(id[1]){
			man = p[1]->getArmy()[id[1]-1];
			if(man->isDead()) world[i]->setArrival(1,0);
		}
	}
}

void mainReportUnits(City * world[], int hr){
//	000:50 100 elements in red headquarter 
	printf("%03d:50 %d elements in red headquarter\n", City::hour, world[0]->getUnits());
	printf("%03d:50 %d elements in blue headquarter\n", City::hour, world[City::numCities+1]->getUnits());
}

void mainReportWeapon(City * world[], int hr){
//000:55 blue wolf 2 has arrow(2),bomb,sword(23)
//000:55 blue wolf 4 has no weapon
//000:55 blue wolf 5 has sword(20)
	Warrior * man;
	City *p[2];
	p[0] = world[0];
	p[1] = world[City::numCities +1];
	for(int i=1;i<=City::numCities+1;i++){
		int id = world[i]->getArrival()[0];
		if(id){
			man = p[0]->getArmy()[id-1];
			printf("%03d:55 red %s %d has ", City::hour,Warrior::profName[man->getProf()].c_str(),man->getId());
			if(man->getWeapStat()[2] ==1 ) printf("arrow(%d)",man->getWeapon()[2]->getNumLeft());
			if(man->getWeapStat()[2] ==1 and man->getWeapStat()[1] ==1) printf(",");
			if(man->getWeapStat()[1] ==1 ) printf("bomb");
			if((man->getWeapStat()[2] ==1 and man->getWeapStat()[0] ==1)
				or (man->getWeapStat()[1] ==1 and man->getWeapStat()[0] ==1) ) printf(",");
			if(man->getWeapStat()[0] ==1 ) printf("sword(%d)",man->getWeapon()[0]->getForce());
			if(man->getWeapStat()[2] ==0 and man->getWeapStat()[1] ==0 and man->getWeapStat()[0] ==0 )
				printf("no weapon");
			printf("\n");
		}
	}
	for(int i=0;i<=City::numCities;i++){
		int id = world[i]->getArrival()[1];
		if(id){
			man = p[1]->getArmy()[id-1];
			printf("%03d:55 blue %s %d has ", City::hour,Warrior::profName[man->getProf()].c_str(),man->getId());
			if(man->getWeapStat()[2] ==1 ) printf("arrow(%d)",man->getWeapon()[2]->getNumLeft());
			if(man->getWeapStat()[2] ==1 and man->getWeapStat()[1] ==1) printf(",");
			if(man->getWeapStat()[1] ==1 ) printf("bomb");
			if((man->getWeapStat()[2] ==1 and man->getWeapStat()[0] ==1)
				or (man->getWeapStat()[1] ==1 and man->getWeapStat()[0] ==1) ) printf(",");
			if(man->getWeapStat()[0] ==1 ) printf("sword(%d)",man->getWeapon()[0]->getForce());
			if(man->getWeapStat()[2] ==0 and man->getWeapStat()[1] ==0 and man->getWeapStat()[0] ==0 )
				printf("no weapon");
			printf("\n");
		}
	}
}

int main(){
	int TotCaseNo;
//	freopen("inputcase.txt","r",stdin);
//	freopen("outputcase.txt","w",stdout);
	cin >> TotCaseNo;
//	cout << TotCaseNo << endl;
	int caseUnits,caseMin;
	City::hour = 0;
	for(int i=0;i<TotCaseNo;i++){
		cin >> caseUnits >> City::numCities >> Weapon::arrowForce
			>> Warrior::lionLoyaltyDe >> caseMin;
//		cout << caseUnits << " "<< City::numCities << " "<< Weapon::arrowForce <<" "
//			 << Warrior::lionLoyaltyDe << " "<< caseMin <<endl;
//		scanf("%d",&caseUnits);
//		scanf("%d",&caseNumCities);
//		scanf("%d",&Weapon::arrowForce);
//		scanf("%d",&Warrior::lionLoyaltyDe);
//		scanf("%d",&caseMin);
//		Cities world(caseNumCities,caseUnits);
		City * world[100];
		world[0] = new Headquarter(caseUnits,0);
		world[City::numCities+1] = new Headquarter(caseUnits,1);
		for(int j=1;j<=City::numCities;j++) world[j] = new City(0);
//		for(int j=0; j<=2; j++) cout<<world[i]->getCamp()<<"mark"<<endl;
		for(int j=0; j<NumWarrTypes; j++){
			cin >> Warrior::sysHealth[j];
//			cout << Warrior::sysHealth[j]<< " " ;
//			scanf("%d",&Warrior::sysHealth[j]);
		}
//		cout << endl;
		for(int j=0; j<NumWarrTypes; j++){
			cin >> Warrior::sysWarrForce[j];
//			cout << Warrior::sysWarrForce[j]<<" ";
//			scanf("%d",&Warrior::sysWarrForce[j]);
		}
//		cout << endl;
		cout << "Case " << i+1 <<":"<< endl;
		
		while(City::hour*60 <= caseMin) {
			mainBuildArmy(world,City::hour);
			if(City::hour*60 + 5 > caseMin) break;
			mainLionRun(world,City::hour);
			if(City::hour*60 + 10 > caseMin) break;
			mainWalk(world,City::hour,&caseMin);
			if(City::hour*60 + 20 > caseMin) break;
			mainCityUpdate(world,City::hour);
			if(City::hour*60 + 30 > caseMin) break;
			mainTakeUnits(world,City::hour);
			if(City::hour*60 + 35 > caseMin) break;
			mainArrow(world,City::hour);
			if(City::hour*60 + 38 > caseMin) break;
			mainBomb(world,City::hour);
			if(City::hour*60 + 40 > caseMin) break;
			mainFight(world,City::hour);
			mainAfter(world,City::hour);
			if(City::hour*60 + 50 > caseMin) break;
			mainReportUnits(world,City::hour);
			if(City::hour*60 + 55 > caseMin) break;
			mainReportWeapon(world,City::hour);
			City::hour++;
		}
		City::hour = 0;
		City::token[0] = City::token[1] = 0;
	}
	
	return 0;
}

//	// 000:38 blue dragon 1 used a bomb and killed red lion 7
//			printf("%03d:%d %s %s %d used a bomb and killed %s %s %d",
//				hour,minute,City::campName[myOwner->getCamp()],Warrior::profName[myOwner->getProf()],
//				myOwner->getId(),City::campName[man.getCamp()],Warrior::profName[man->getProf()],man.getId());
//


