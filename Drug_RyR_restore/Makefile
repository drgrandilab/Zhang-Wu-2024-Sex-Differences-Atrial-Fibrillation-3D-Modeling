# Makefile
# Haibo Ni <haibo.ni02@gmail.com> // 15:53:54, Thu, 23-January-2020, By Haibo
CXX=icpc
# CXX=mpiicpc

CXXFLAGS = -O3 -qopenmp -std=c++11 -g -lz #  -no-prec-div,-static, -fp-model fast=2  -xHost  #-parallel-source-info=2  -Fast-math -DCPU   -xSSE3 
#CXXFLAGS = -Ilib -O3 -qopenmp -std=c++11 -g -lz #-parallel-source-info=2
LDFLAGS=-lz# -L~/intel/zlib/lib/

# INC=$(lib_cell) $(lib)
INC_PARAMS=-Ilib -Ilib_cell
# CXX = g++
srcs = $(wildcard lib_cell/*.cpp lib/*.cpp)
# 	   $(wildcard lib/*.cpp) 
BUILD_DIR=build

objs := $(srcs:%=$(BUILD_DIR)/%.o)
deps := $(objs:.o=.d)


pace_2: pace_2.cpp $(objs)  
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $^ -o $@

# Atria_3D_OMP_2D_2d: Atria_3D_OMP_2D_2d.cpp $(objs)  
Atria_2D_MPI_Ghost: Atria_2D_MPI_Ghost.cpp $(objs)  
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $^ -o $@ $(LDFLAGS)

ONE_D_MPI_Ghost: ONE_D_MPI_Ghost.cpp $(objs)  
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $^ -o $@ $(LDFLAGS)
# %.o: %.cpp
# 	$(CXX) $(INC_PARAMS)   $(CXXFLAGS)  -MMD -MP -c $< -o $@ 
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(INC_PARAMS)   $(CXXFLAGS)  -MMD -MP -c $< -o $@ 


Atria_2D_MPI_Ghost_for_0DCell: Atria_2D_MPI_Ghost_for_0DCell.cpp $(objs)  
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $^ -o $@ $(LDFLAGS)


.PHONY: clean

# $(RM) is rm -f by default
clean:
	$(RM) $(objs) $(deps) pace

-include $(deps)
MKDIR_P ?= mkdir -p