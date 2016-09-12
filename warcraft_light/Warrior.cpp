class Warrior{
	int id; // warrior's id number
	int camp; // 0:red, 1:blue
	int prof; // 0:"dragon", 1:"ninja", 2:"iceman", 3:"lion", 4:"wolf"
 	int health; // 0 < health <= 100
	
	Public:
	const static string campName[2];
	const static string profName[5];
	static int units[2]; // total health units
	static int sysHealth[5]; // health units for each profession
	static int warriorCts[2][5]; // count warrior number for each camp and profession
	static int time; 
	
	Warrior(int newCamp, int newProf, int newHealth);
	~Warrior();
	int getid();
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
		
		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter",time,campName[camp].c_str(),
			profName[prof].c_str(),id,health, warriorCts[camp][prof], profName[prof].c_str(), campName[camp].c_str());
		//000 red iceman 1 born with strength 5,1 iceman in red headquarter
	}
	else cout<< "Not enough units!" << endl;
}

Warrior::~Warrior(){
	delete Warrior;
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


