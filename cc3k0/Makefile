CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = cc3k
OBJECTS = main.o game.o entity.o character.o player.o enemy.o item.o potion.o human.o dwarf.o elf.o orc.o werewolf.o vampire.o goblin.o troll.o phoenix.o merchant.o dragon.o treasure.o itemvisitor.o attackvisitor.o random.o coorddiff.o compass.o barrier.o playerstatus.o basestatus.o potiondecorator.o tempPotion.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


