#acceptable buildTypes: Release/Debug/Profile

# STOP CHANGING THIS AND COMMITTING IT
# If you want to change the build type then
# either run export buildType=Debug
# or run buildType=Debug make
buildType ?= Release
CC ?= $(which clang-5.0)
CXX ?= $(which clang++-5.0)

ifeq ($(buildType),Debug)
	buildDir=build_debug
else
	buildDir=build
endif

ifeq ($(buildType), RelWithDebInfo)
	cmakeBuildType=$(buildType)
	conanBuildType=$(buildType)
else
	cmakeBuildType=$(buildType)
	conanBuildType=$(buildType)
endif

# get the current make file path and directory
# see http://stackoverflow.com/questions/18136918/how-to-get-current-relative-directory-of-your-makefile#18137056

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkfile_path)))

PROTO_FILES = $(wildcard proto/**)

.PHONY: all clean cleanup_cache cleanup_conan clean_all cleanlogs conan_update test

all: install

build: cmake $(PROTO_FILES)
	$(MAKE) --no-print-directory -C $(buildDir)

clean:
	$(MAKE) --no-print-directory -C $(buildDir) clean

cleanup_cache:
	rm -f $(buildDir)/CMakeCache.txt

cleanup_conan:
	rm -rf $(buildDir)/conan*

clean_all: clean cleanup_cache cleanup_conan

cleanlogs:
	(cd logs; rm -rf *.txt *.vraw *.?log *.log *.idx html/*.html)

cmake: conan CMakeLists.txt
	cd $(buildDir) && PYENV_VERSION=conan-pkg cmake -DCMAKE_INSTALL_PREFIX=$(current_dir) ..

conan_update: conanfile.txt
	cd $(buildDir) && PYENV_VERSION=conan-pkg timeout 30 conan info --update ..

conan: conanfile.txt
	cd $(buildDir) && PYENV_VERSION=conan-pkg conan install --build=missing -s build_type=$(conanBuildType) ..

docs: cmake
	$(MAKE) --no-print-directory -C $(buildDir) docs

install: build
	$(MAKE) --no-print-directory -C $(buildDir) install
