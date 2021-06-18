# executable = pong

# cxx = g++
# cxx_include_libs = -lsfml-graphics -lsfml-window -lsfml-system
# src_dir = src
# build_dir = build#

# srcs ?= $(wildcard src/*.cpp)
# objs ?= $(srcs:%=$(build_dir)/%.o)

# mkdir_p = mkdir -p

# pong: $(build_dir)/$(executable)
# 	@echo "building"


# $(build_dir)/$(executable): $(objs)
# 	@$(cxx)


# clean:
# 	@rm -r $(build_dir)/*