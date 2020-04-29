target_file=moving_walkways

source=limak.cpp walkway.cpp utils.cpp

ifeq ($(TEST), on)
  source += main_ut.cpp
else
  source += main.cpp
endif

headers=limak.hpp walkway.hpp

obj_dir=./obj/

object_files=$(addprefix $(obj_dir),$(addsuffix .o,$(basename $(notdir $(source)))))

VPATH=./src/

DEBUG_MODE ?= off

.PHONY: all clean

CC=c++

CPP_FLAGS=-std=c++14

ifeq ($(DEBUG_MODE), on)
  CPP_FLAGS += -g -O0
endif

all: $(target_file)

$(target_file): $(object_files)
	$(CC) $(CPP_FLAGS) $^ -o $@

$(obj_dir)%.o : %.cpp $(headers) $(obj_dir)
	$(CC) $(CPP_FLAGS) -o $@ $< -c

$(obj_dir): 
	mkdir -p $(obj_dir)

clean:
	rm -rf $(obj_dir)

cleanall: clean
	rm -rf $(target_file)
