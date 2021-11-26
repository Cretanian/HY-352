/*#include "Hogwarts.h"


template<typename... Args>
bool and_function(bool a, bool b, Args... args) { return a && b && (...&&args); }

template<typename... Args2>
bool or_function(bool a, bool b, Args2... args) { return a || b || (...||args); }

bool not_function(bool a) {return !a;}

int get_hp(std::string player_on_turn) {
	if (player_on_turn.compare("defender-"))
		return defender->GET_health();
	else if (player_on_turn.compare("attacker-"))
		return attacker->GET_health();
	assert(false);
}

std::string get_house(std::string player_on_turn) {
	if (player_on_turn.compare("defender-"))
		return defender->GET_house();
	else if (player_on_turn.compare("attacker-"))
		return attacker->GET_house();
	assert(false);
}

std::string get_name(std::string player_on_turn) {
	if (player_on_turn.compare("defender-"))
		return defender->GET_fullname();
	else if (player_on_turn.compare("attacker-"))
		return attacker->GET_fullname();
	assert(false);
}

Wizard& Damage(Wizard& wiz) {
	wiz.deal_damage = true;
	wiz.heal_damage = false;
	return wiz;
}
Wizard& Heal(Wizard& wiz) {
	wiz.deal_damage = false;
	wiz.heal_damage = true;
	return wiz;
}

ForActionsList forActionsList;

#define GET_HP(x) get_hp(STRINGFY(x))
#define GET_HOUSE(x) get_house(STRINGFY(x))
#define GET_NAME(x) get_name(STRINGFY(x))
#define HEAL Heal
#define DAMAGE Damage


#define DEFENDER (*defender)-
#define ATTACKER (*attacker)-
#define _ ++;

#define AND and_function
#define OR or_function
#define NOT not_function

#define DO ){
//
#define FOR forActionsList.tempNode = ForActions(); forActionsList.tempNode.to_end =
#define ROUNDS ; forActionsList = [](Wizard* wiz


BEGIN_GAME
CREATE WIZARD{
	NAME: "name",
	HOUSE : "house",
	HP : 100
}

CREATE WIZARDS[
	WIZARD{ NAME: "name1", HOUSE : "house", HP : 2 },
		WIZARD{ NAME: "name2", HOUSE : "house", HP : 3 }
]

CREATE SPELL{
	NAME: "AGAYASSSPELL",
	ACTION : START


	END
	}

CREATE SPELLS[
	SPELL{
		NAME: "AGAYASSSPELL",
		ACTION : START

		END
	},
	SPELL{
		NAME: "AGAYASSSPELL",
		ACTION : START
		END
	}
]


MR "name1" LEARN[
	SPELL_NAME(WinguardiumLeviosa)
		SPELL_NAME(ConfundusCharm)
		SPELL_NAME(Stupefy)
		SPELL_NAME(Obliviate)
]

		MRS "name2" LEARN[
			SPELL_NAME(WinguardiumLeviosa)
				SPELL_NAME(ConfundusCharm)
				SPELL_NAME(Stupefy)
				SPELL_NAME(Obliviate)
		]

		DUEL


	
		assert(WizList.list.back().GET_house() == "house");

			forActionsList.tempNode = ForActions(); forActionsList.tempNode.to_end = 5
				; forActionsList = [](Wizard* wiz) { std::cout << "IT FUCKING WORKS" << std::endl; };


			forActionsList.tempNode = ForActions();

			Wizard* a;
			Wizard sd;
			a = &sd;
			forActionsList.list.front().forfun(a);
			bool x = false;
			(*a)---- - x;
			std::cout << sd.GET_has_wand()<< std::endl;
			(*a)_
				std::cout << sd.GET_has_wand() << std::endl;
			system("pause");
			Heal(*a) - 5;

			

			CREATE SPELL{
NAME: "Sectumsempra",
ACTION : START
		 FOR 5 ROUNDS DO
		 DAMAGE DEFENDER 8
		 END
		 END
			}
			;
END_GAME

*/

#include "Hogwarts.h"

BEGIN_GAME

CREATE WIZARD{
	NAME: "Harry Potter" ,
	HOUSE : "Gryffindor" ,
	HP : 120
}

CREATE WIZARD{
	NAME: "Draco Malfoy" ,
	HOUSE : "Slytherin" ,
	HP : 100
}

CREATE WIZARDS[
	WIZARD{
		NAME: "Hermione Granger" ,
		HOUSE : "Gryffindor" ,
		HP : 120
	},
	WIZARD{
			NAME: "Luna Lovegood" ,
			HOUSE : "Ravenclaw" ,
			HP : 85
	}
];


CREATE SPELL{
	NAME: "Anapneo" ,
	ACTION : START
		IF GET_HP(ATTACKER) < 30 DO
			HEAL ATTACKER 25
		ELSE
			HEAL ATTACKER 15
		END
	END
	}

		CREATE SPELL{
			NAME: "Levicorpus" ,
			ACTION : START
				EQUIP ATTACKER ---x
				DAMAGE DEFENDER 20
			END
	}


		CREATE SPELLS[
			SPELL{
				NAME: "hehe" ,
				ACTION : START
					IF GET_HP(DEFENDER) > 100 DO
						DAMAGE DEFENDER 25
					ELSE
						DAMAGE DEFENDER 1
					END
				END
			},
				SPELL{
					NAME: "Expulso" ,
					ACTION : START
						SHOW GET_HOUSE(DEFENDER) << GET_NAME(DEFENDER) << HAS_WAND(DEFENDER) << std::endl;
					END
			},
				SPELL{
					NAME: "HighNoon" ,
					ACTION : START
						IF OR(GET_HP(DEFENDER) > 30 , GET_HP(DEFENDER) < 70) DO
							DAMAGE DEFENDER 250
						END
					END
			},
				SPELL{
					NAME: "fortest" ,
					ACTION : START
						FOR 5 ROUNDS DO
							IF AND(GET_HP(DEFENDER) > 10 , GET_HP(DEFENDER) < 80) DO
								DAMAGE DEFENDER 20
							END
						END
					END
			},
				SPELL{
					NAME: "s" ,
					ACTION : START
						
							 SHOW GET_HP(ATTACKER)
					END
			},
				SPELL{
					NAME: "A_F_test" ,
					ACTION : START
						AFTER 2 ROUNDS DO
							EQUIP DEFENDER _
						END

						FOR 5 ROUNDS DO
							IF OR(GET_HP(DEFENDER) > 10 , GET_HP(DEFENDER) < 80) DO
								DAMAGE DEFENDER 20
							END
						END

					END
			}

		]

		MR "Harry Potter" LEARN[
			SPELL_NAME(s)
				SPELL_NAME(Anapneo)
				SPELL_NAME(Expulso)
				SPELL_NAME(fortest)
				SPELL_NAME(aftertest)

		]

				MRS "Hermione Granger" LEARN[
					SPELL_NAME(Anapneo)
						SPELL_NAME(Levicorpus)
						SPELL_NAME(hehe)
						SPELL_NAME(Expulso)
						SPELL_NAME(HighNoon)
						SPELL_NAME(fortest)
						SPELL_NAME(aftertest)
				]

				MRS "Draco Malfoy" LEARN[
					SPELL_NAME(hehe)
						SPELL_NAME(Anapneo)
						SPELL_NAME(HighNoon)
						SPELL_NAME(A_F_test)
						SPELL_NAME(aftertest)
				]

						MRS "Luna Lovegood" LEARN[
							SPELL_NAME(Levicorpus)
								SPELL_NAME(hehe)
								SPELL_NAME(Expulso)
								SPELL_NAME(A_F_test)
								SPELL_NAME(aftertest)
						]



DUEL

		END_GAME

