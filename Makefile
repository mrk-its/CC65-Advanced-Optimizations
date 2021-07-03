SUBDIRS := 01-start 03-smallest-unsigned-data-types 04-get-rid-of-C-stack 05-replace-array-of-structs 06-get-rid-of-enums ./08-get-rid-of-parameter-passing ./09-replace-calculations-and-switches-with-lookup-tables 11-improve-array-access 12-inline-functions
CL65_OPTIMIZATION_FLAGS=-Osir -Cl

all:	$(SUBDIRS)
	@echo " llvm-mos:" `cd ../llvm-mos; git rev-parse HEAD)`
	@echo " llvm-mos-sdk:" `cd ../llvm-mos-sdk; git rev-parse HEAD)`


$(SUBDIRS):
	@$(MAKE) --no-print-director -C $@ -f ../Makefile run_sim CLANG_FLAGS="-O2"

clean:
	find -name '*.sim' -delete
	find -name '*.xex' -delete

clang:
	../../llvm-mos/build/bin/clang --config ../../llvm-mos-sdk/build/atari/800xl.cfg game.c -Wno-main-return-type -Wno-switch -I../utils/clang  -Wl,--oformat,elf -o a.out.elf
	llvm-objcopy --output-target binary --strip-unneeded a.out.elf a.out

game.sim: game.c
	../../llvm-mos/build/bin/clang ${CLANG_FLAGS} --config ../../llvm-mos-sdk/build/sim.cfg game.c -Wno-main-return-type -Wno-switch -I../utils/sim -o game.sim

game.xex: game.c
	cl65 -I../utils/cc65/ ${CL65_OPTIMIZATION_FLAGS} -t atari -Ln game.lbl --listing game.lst --add-source -o game.xex game.c

game-clang.xex: game.c
	../../llvm-mos/build/bin/clang ${CLANG_FLAGS} --config ../../llvm-mos-sdk/build/atari/800xl.cfg game.c -Wno-main-return-type -Wno-switch -I../utils/clang -o game-clang.xex

run_sim: game.sim game-clang.xex game.xex
	@echo -n " "; basename `pwd`
	@echo " cc65:" $$((`cat ref.txt | grep cc65 | cut -d : -f 2` * 24223))
	@echo " "`../../llvm-mos-sdk/build/bin/sim game.sim`
	@echo " "

.PHONY: all $(SUBDIRS)
