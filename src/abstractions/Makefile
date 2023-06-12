# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=0

psvn2c_core.c:
	@cp ../../psvn/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp ../../psvn/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp ../../psvn/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@echo "**** Constructing $@ ..."
	@../../psvn/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

# %.succ: %.c ../global/succ.c
# 	@echo "**** Constructing $@ ..."
# 	@$(CC) $(OPT) ../global/succ.c -include $< -o $@
# 	@rm -f $*.c

%.dist: %.c ../../psvn/global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../psvn/global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c ../../psvn/global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../psvn/global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c ../../psvn/global/generator.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../psvn/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) ../../psvn/abstractor.cpp ../../psvn/psvn.cpp -o $@

%.pdb: abstractor
	@echo "**** Running abstractor on ${psvn_file} with $*.txt ..."
	@echo Aqui abstractor ${psvn_file} `basename $*` < $*.txt
	@./abstractor ${psvn_file} `basename $*` < $*.txt > /dev/null
	@make `basename $*`.distSummary
	@echo "**** Constructing PDB `basename $*`.pdb ..."
	@./`basename $*`.distSummary `basename $*`.pdb > /dev/null
	@rm -f `basename $*`.distSummary
	@mv `basename $*`.pdb $*.pdb
	@mv `basename $*`.abst $*.abst
	@mv `basename $*`.psvn $*.psvn

%.dist_pdb: %.c ../global/dist_pdb.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/dist_pdb.cpp -include $< -o $@
	@rm -f $*.c

.PHONY: clean all
clean:
	rm -fr *.succ *.dist *.distSummary *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~

all:
	make hanoi/4-12/hanoi4-12_group_1.pdb psvn_file=hanoi/4-12/hanoi4-12.psvn
	make hanoi/4-12/hanoi4-12_group_2.pdb psvn_file=hanoi/4-12/hanoi4-12.psvn
	make hanoi/4-14/hanoi4-14_group_1.pdb psvn_file=hanoi/4-14/hanoi4-14.psvn
	make hanoi/4-14/hanoi4-14_group_2.pdb psvn_file=hanoi/4-14/hanoi4-14.psvn
	make hanoi/4-18/hanoi4-18_group_1.pdb psvn_file=hanoi/4-18/hanoi4-18.psvn
	make hanoi/4-18/hanoi4-18_group_2.pdb psvn_file=hanoi/4-18/hanoi4-18.psvn
	
	make n-puzzle/15-puzzle/15-puzzle_group_1.pdb psvn_file=n-puzzle/15-puzzle/15-puzzle.psvn
	make n-puzzle/15-puzzle/15-puzzle_group_2.pdb psvn_file=n-puzzle/15-puzzle/15-puzzle.psvn
	make n-puzzle/15-puzzle/15-puzzle_group_3.pdb psvn_file=n-puzzle/15-puzzle/15-puzzle.psvn
	make n-puzzle/24-puzzle/24-puzzle_group_1.pdb psvn_file=n-puzzle/24-puzzle/24-puzzle.psvn
	make n-puzzle/24-puzzle/24-puzzle_group_2.pdb psvn_file=n-puzzle/24-puzzle/24-puzzle.psvn
	make n-puzzle/24-puzzle/24-puzzle_group_3.pdb psvn_file=n-puzzle/24-puzzle/24-puzzle.psvn
	make n-puzzle/24-puzzle/24-puzzle_group_4.pdb psvn_file=n-puzzle/24-puzzle/24-puzzle.psvn

	make rubik/3x3/rubik_corner_1.pdb psvn_file=rubik/3x3/rubik3.psvn
	make rubik/3x3/rubik_corner_2.pdb psvn_file=rubik/3x3/rubik3.psvn
	make rubik/3x3/rubik_corner_3.pdb psvn_file=rubik/3x3/rubik3.psvn
	make rubik/3x3/rubik_corner_4.pdb psvn_file=rubik/3x3/rubik3.psvn
	make rubik/3x3/rubik_edge_1.pdb psvn_file=rubik/3x3/rubik3.psvn
	make rubik/3x3/rubik_edge_2.pdb psvn_file=rubik/3x3/rubik3.psvn
	make rubik/3x3/rubik_edge_3.pdb psvn_file=rubik/3x3/rubik3.psvn
	make rubik/3x3/rubik_edge_4.pdb psvn_file=rubik/3x3/rubik3.psvn

	make topSpin/12-4/topspin_12_4_group_1.pdb psvn_file=topSpin/12-4/topspin_12_4.psvn
	make topSpin/12-4/topspin_12_4_group_2.pdb psvn_file=topSpin/12-4/topspin_12_4.psvn
	make topSpin/14-4/topspin_14_4_group_2.pdb psvn_file=topSpin/14-4/topspin_14_4.psvn
	make topSpin/14-4/topspin_14_4_group_1.pdb psvn_file=topSpin/14-4/topspin_14_4.psvn
	make topSpin/14-4/topspin_14_4_group_2.pdb psvn_file=topSpin/14-4/topspin_14_4.psvn
	make topSpin/17-4/topspin_17_4_group_1.pdb psvn_file=topSpin/17-4/topspin_17_4.psvn
	make topSpin/17-4/topspin_17_4_group_2.pdb psvn_file=topSpin/17-4/topspin_17_4.psvn
	make topSpin/17-4/topspin_17_4_group_3.pdb psvn_file=topSpin/17-4/topspin_17_4.psvn

	@rm -f abstractor
	
