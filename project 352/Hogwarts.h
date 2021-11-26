#include <iostream>
#include <functional>
#include <cassert>
#include <list>
#include <string>
#include <sstream>

int Round = 1;
double extra_dmg, reduce_dmg;

class toequip {
public:
	bool equip;

	toequip(bool x) {
		equip = x;
	}

	toequip operator --() {
		return *this;
	}

	toequip operator -() {
		return *this;
	}
};

toequip x(true);
toequip unequip_wand(false);

class ForActions {
public:
	int to_end;
	int begun;
	std::function<void()> forfun;
	std::function<void()>* pointerToFun;
	ForActions() {
	}

	ForActions(int a, std::function<void()> fun) {
		to_end = a;
		begun = Round;
		forfun = fun;
		pointerToFun = &forfun;
	}

	bool operator ==(ForActions a) const {
		return (a.pointerToFun == this->pointerToFun);
	}

};

class AfterActions {
public:
	int to_execute;
	int begun;
	std::function<void()> afterfun;
	std::function<void()>* pointerToFun;

	AfterActions() {}

	AfterActions(int a, std::function<void()> fun) {
		to_execute = a;
		begun = Round;
		afterfun = fun;
		pointerToFun = &afterfun;
	}

	bool operator ==(AfterActions a) const {
		return (a.pointerToFun == this->pointerToFun);
	}

};

class ForAndAfterActionsList {
public:
	ForActions tempNode;
	AfterActions afterTempNode;
	bool forloop;

	std::list<ForActions> for_list;
	std::list<AfterActions> after_list;

	ForAndAfterActionsList operator = (std::function<void()> fun) {
		if (forloop) {
			tempNode.forfun = fun;
			for_list.push_back(tempNode);
			return *this;
		}
		else if (!forloop) {
			afterTempNode.afterfun = fun;
			after_list.push_back(afterTempNode);
			return *this;
		}
	}

};

class Wizards_Spell_List {
public:
	std::list<std::string> list;

	Wizards_Spell_List operator[] (std::string strTok) {
		//to_tokenize = "";
		std::stringstream stream(strTok);
		std::string temp;

		while (getline(stream, temp, ',')) {
			if(temp != "") 
				this->list.push_back(temp);
		}	
		return *this;
	}

	Wizards_Spell_List operator =(Wizards_Spell_List foreign_list) {
		list.splice(list.end(), foreign_list.list);
		return *this;
	}
};

class Wizard {
protected:
	std::string fullname = "";
	std::string house = "";
	int health_points = -1;
	bool has_wand = true;
public:
	bool deal_damage = false;
	bool heal_damage = false;
	int max_hp = -1;
	ForAndAfterActionsList forAndAfterActionsList;

	Wizard() {}

	Wizard(std::string name, std::string house, int hp) {
		this->fullname = name;
		this->house = house;
		this->health_points = hp;
		this->max_hp = hp;
	}

	void SET_fullname(std::string name)
	{
		assert(name.empty());
		fullname = name;
	}

	void SET_house(std::string house_name)
	{
		assert(house_name.empty());
		house = house_name;
	}

	void SET_health(int new_hp)
	{
		health_points = new_hp;
	}

	std::string GET_fullname() {
		assert(!fullname.empty());
		return fullname;
	}

	std::string GET_house() {
		assert(!house.empty());
		return house;
	}

	int GET_health() {
		assert(health_points <= max_hp);
		return health_points;
	}

	bool GET_has_wand() {
		return has_wand;
	}
	void SET_has_wand() {
		has_wand = true;
	}

	Wizards_Spell_List my_spells;

	void operator=(Wizards_Spell_List foreign_list) {

	}

	

	Wizard operator -- (int) {
		has_wand = true;
		return *this;
	}

	Wizard operator -(toequip a) {
		has_wand = a.equip;
		return *this;
	}

	

	Wizard operator-(int num) {
		assert(deal_damage != heal_damage);
		if (deal_damage) {
			extra_dmg = num * extra_dmg;
			reduce_dmg = num * reduce_dmg;
			SET_health(GET_health() - (num - (int)(reduce_dmg - extra_dmg)));
		}
		else {
			if (GET_health() + num >= max_hp) {
				SET_health(max_hp);
				return *this;
			}				
			SET_health(GET_health() + num);
		}
		return *this;
	}

	Wizard operator ++(int) {
		has_wand = false;
		return *this;
	}

};

Wizard* attacker = new Wizard();
Wizard* defender = new Wizard();

Wizard& Damage(Wizard& wiz) {
	wiz.deal_damage = true;
	wiz.heal_damage = false;
	if (attacker->GET_house() == "Slytherin") {
		extra_dmg = 0.15;
		if (defender->GET_house() == "Gryffindor") {
			reduce_dmg = 0.3;
			extra_dmg = 0.2;
		}
		else if (defender->GET_house() == "Hufflepuff") {
			reduce_dmg = 0.07;
		}
	}
	else if (attacker->GET_house() == "Hufflepuff") {
		extra_dmg = 0.07;
		if (defender->GET_house() == "Hufflepuff") {
			reduce_dmg = 0.07;
		}
		else if (defender->GET_house() == "Gryffindor") {
			reduce_dmg = 0.2;
		}
	}
	else if (attacker->GET_house() == "Gryffindor") {
		if (defender->GET_house() == "Hufflepuff") {
			reduce_dmg = 0.07;
		}
		else if (defender->GET_house() == "Gryffindor") {
			reduce_dmg = 0.2;
		}
	}
	else if (attacker->GET_house() == "Ravenclaw") {
		if (Round % 3 == 0) {
			extra_dmg = 0.07;
		}
	}
	return wiz;
}

Wizard& Heal(Wizard& wiz) {
	wiz.deal_damage = false;
	wiz.heal_damage = true;
	return wiz;
}

class Spell {
public:
	std::string name;
	std::function<void()> spell_function;
	Spell(std::string name, std::function<void()> pell_function) {
		this->name = name;
		this->spell_function = pell_function;
	}
};

class spells_list {
public:
	std::list<Spell> list;
	spells_list operator=(const Spell spell) {
		list.push_back(spell);
		return *this;
	}

	void operator [](const spells_list spellist) {}

	Spell* getSpell(std::string name) {
		std::list<Spell>::iterator it;
		for (it = this->list.begin(); it != this->list.end(); it++) {
			if (it->name == name)
				return &(*it);
		}
		assert(false);
	}
};

class wizards_list {
public:
	std::list<Wizard> list;
	wizards_list operator=(const Wizard wiz) {
		list.push_back(wiz);
		return *this;
	}

	void operator [](const wizards_list wizards_list) {}

	Wizard* getWizard(std::string name) {
		std::list<Wizard>::iterator it;
		for (it = this->list.begin(); it != this->list.end(); it++) {
			if (it->GET_fullname() == name)
				return &(*it);
		}
		assert(false);
	}
};

template<typename... Args>
bool and_function(bool a, bool b, Args... args) { return a && b && (... && args); }

template<typename... Args2>
bool or_function(bool a, bool b, Args2... args) { return a || b || (... || args); }

bool not_function(bool a) {
	return !a;
}

int get_hp(std::string player_on_turn) {
	if (player_on_turn == "(*defender)-")
		return defender->GET_health();
	else if (player_on_turn == "(*attacker)-")
		return attacker->GET_health();
	assert(false);
}

bool has_wand(std::string player_on_turn) {
	if (player_on_turn == "(*defender)-")
		return defender->GET_has_wand();
	else if (player_on_turn == "(*attacker)-")
		return attacker->GET_has_wand();
	assert(false);
}

std::string get_house(std::string player_on_turn) {
	if (player_on_turn == "(*defender)-")
		return defender->GET_house();
	else if (player_on_turn == "(*attacker)-")
		return attacker->GET_house();
	assert(false);
}

std::string get_name(std::string player_on_turn) {
	if (player_on_turn == "(*defender)-")
		return defender->GET_fullname();
	else if (player_on_turn == "(*attacker)-")
		return attacker->GET_fullname();
	assert(false);
}

void useless() {
	assert(false);
}

void display_wizards(wizards_list WizList) {
	std::list<Wizard>::iterator it;
	std::cout << "----------------------------" << std::endl;
	for (it = WizList.list.begin(); it != WizList.list.end(); it++) {
		std::cout << it->GET_fullname() << std::endl;
	}
	std::cout << "----------------------------" << std::endl;
}

void display_my_spells(Wizard* wiz) {
	std::list<std::string>::iterator it;
	std::list<std::string> wizards_spell_list;
	wizards_spell_list = (*wiz).my_spells.list;
	std::cout << "----------------------------" << std::endl;
	for (it = wizards_spell_list.begin(); it != wizards_spell_list.end(); it++) {
		std::cout << (*it) << std::endl;
	}
	std::cout << "----------------------------" << std::endl;
}

void display_wizard_stats(Wizard* wiz) {
	std::cout << "############################" << std::endl;
	std::cout << "Name: " << wiz->GET_fullname() << std::endl;
	std::cout << "HP: " << wiz->GET_health() << std::endl;
	if (wiz->GET_has_wand())
		std::cout << "Wand equipped" << std::endl;
	else
		std::cout << "Wand not equipped" << std::endl;
	std::cout << "############################" << std::endl << std::endl << std::endl;
}

void display_round() {
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Round " << Round << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void add_hp(Wizard* wiz) {
	double heal = 0.05;
	int new_hp = wiz->GET_health() + (int)(heal * wiz->max_hp);
	if (new_hp >= wiz->max_hp) {
		wiz->SET_health(wiz->max_hp);
	}
	else {
		wiz->SET_health(new_hp);
	}
}

void do_spell(std::string spell_name, Wizard* wiz, spells_list* SpellList) {
	bool found = (std::find(wiz->my_spells.list.begin(), wiz->my_spells.list.end(), spell_name) != wiz->my_spells.list.end());
	if (found) {
		Spell *tmp = SpellList->getSpell(spell_name);
		tmp->spell_function();		
	}
}

void execute_for_effects() {
	std::list<ForActions>::iterator it;

	if ((*attacker).forAndAfterActionsList.for_list.empty())
		return;

	for (it = (*attacker).forAndAfterActionsList.for_list.begin(); it != attacker->forAndAfterActionsList.for_list.end(); it++) {
		(*it).forfun();
		if (--(*it).to_end == 0) {
			(*attacker).forAndAfterActionsList.for_list.remove((*it));

			if ((*attacker).forAndAfterActionsList.for_list.size() == 0)
				return;
		}
	}	
}

void execute_after_effects() {
	std::list<AfterActions>::iterator it;

	if ((*attacker).forAndAfterActionsList.after_list.empty())
		return;

	for (it = (*attacker).forAndAfterActionsList.after_list.begin(); it != (*attacker).forAndAfterActionsList.after_list.end(); it++) {		
		if (--(*it).to_execute == 0) {
			(*it).afterfun();
			(*attacker).forAndAfterActionsList.after_list.remove((*it));

			if ((*attacker).forAndAfterActionsList.after_list.size() == 0)
				return;
		}
	}
}

void duel(wizards_list* WizList, spells_list* SpellList) {
	std::string tmp_wizard_name1 = "";
	std::string tmp_wizard_name2 = "";
	std::string selected_spell = "";

	Wizard* tmp;
	std::cout << "----------------------------------------";
	std::cout << "HARRY POTTER THE GAME";
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Player1 select wizard:" << std::endl;
	display_wizards(*WizList);
	std::getline(std::cin, tmp_wizard_name1);
	std::cout << std::endl;
	display_wizards(*WizList);
	std::getline(std::cin, tmp_wizard_name2);
	std::cout << std::endl;
	
	if (tmp_wizard_name1 == tmp_wizard_name2) {
		attacker = WizList->getWizard(tmp_wizard_name1);
		*defender = *attacker;
	}
	else {
		attacker = WizList->getWizard(tmp_wizard_name1);
		defender = WizList->getWizard(tmp_wizard_name2);
	}

	Wizard* player1 = attacker;
	Wizard* player2 = defender;
	while (player1->GET_health() > 0 && player2->GET_health() > 0) {
		if (Round % 2 == 0) {
			if (player1->GET_house() == "Ravenclaw") {
				add_hp(player1);
			}

			if (player2->GET_house() == "Ravenclaw") {
				add_hp(player2);
			}
		}

		display_round();
		if (player1->GET_has_wand()) {
			std::cout << tmp_wizard_name1 << "(Player1) select spell:" << std::endl;
			display_my_spells(player1);
			std::cin >> selected_spell;
			std::cout << std::endl;

			do_spell(selected_spell, player1, SpellList);

			display_wizard_stats(player1);
			display_wizard_stats(player2);
		}else{
			std::cout << tmp_wizard_name1 << "(Player1) has not a wand so he/she can't cast a spell." << std::endl << std::endl;
		}

		if (player2->GET_health() < 0) {
			std::cout << "WINNER!!! " << player1->GET_fullname() << std::endl << std::endl;
			break;
		}

		execute_for_effects();
		execute_after_effects();
		tmp = attacker;
		attacker = defender;
		defender = tmp;


		if (player2->GET_has_wand()) {
			std::cout << tmp_wizard_name2 << "(Player2) select spell:" << std::endl;
			display_my_spells(player2);
			std::cin >> selected_spell;
			std::cout << std::endl;

			do_spell(selected_spell, player2, SpellList);

			display_wizard_stats(player1);
			display_wizard_stats(player2);

		}else{
			std::cout << tmp_wizard_name2 << "(Player2) has not a wand so he/she can't cast a spell." << std::endl << std::endl;
		}
		if (player1->GET_health() < 0) {
			std::cout << "WINNER!!! " << player2->GET_fullname() << std::endl << std::endl;
			break;
		}
		execute_for_effects();
		execute_after_effects();

		tmp = attacker;
		attacker = defender;
		defender = tmp;
		Round++;
	}
	system("pause");
}

#define BEGIN_GAME int main() {wizards_list WizList; spells_list SpellList; Wizards_Spell_List temp;
#define END_GAME }

#define CREATE ;
#define WIZARD  WizList = Wizard
#define WIZARDS WizList
#define NAME  false ? "impossible_name" 
#define HOUSE  false ? "impossible_house"
#define HP false ? -1

#define SPELL SpellList = Spell
#define SPELLS SpellList
#define	ACTION false ?  useless
#define START [](){ 
#define END ;}

#define MR ;temp.list.clear();WizList.getWizard(
#define MRS ;temp.list.clear();WizList.getWizard(
#define LEARN )->my_spells = temp

#define STRINGFY(x) #x
#define comma ","
#define SPELL_NAME comma STRINGFY

#define AND and_function
#define OR or_function
#define NOT not_function

#define GET_HP(x) get_hp(STRINGFY(x))
#define GET_HOUSE(x) get_house(STRINGFY(x))
#define GET_NAME(x)  get_name(STRINGFY(x))
#define HAS_WAND(x) has_wand(STRINGFY(x))

#define HEAL ;Heal
#define DAMAGE ;Damage
#define _ unequip_wand;

#define EQUIP ;

#define DEFENDER (*defender)-
#define ATTACKER (*attacker)-

#define IF if (
#define DO ){
#define ELSE ;}else{
#define ELSE_IF ;}else if (

#define FOR ; (*attacker).forAndAfterActionsList.forloop = true; (*attacker).forAndAfterActionsList.tempNode = ForActions(); (*attacker).forAndAfterActionsList.tempNode.to_end = 
#define ROUNDS ; (*attacker).forAndAfterActionsList = [](
#define AFTER ;	(*attacker).forAndAfterActionsList.forloop = false; (*attacker).forAndAfterActionsList.afterTempNode = AfterActions(); (*attacker).forAndAfterActionsList.afterTempNode.to_execute =


#define SHOW ;std::cout <<

#define DUEL ;duel(&WizList, &SpellList); 