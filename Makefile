# install rule from https://gist.github.com/groyoh/a3d8ec21d6c98ec0182ee704c75e6c99 *chef's kiss*
SHELL=/bin/zsh

.PHONY: test install clean

CMOCKA_DIR=$(shell pwd)/cmocka-1.1.0
CMOCKA_BUILD_DIR=$(CMOCKA_DIR)/build
CMOCKA_OUT_DIR=$(CMOCKA_BUILD_DIR)/output
TEST_DIR=$(shell pwd)/tests
UTILS_DIR=$(shell pwd)/utils

TEST_FILES := $(wildcard *_test.c)
UTIL_FILES := $(wildcard $(UTILS_DIR)/*.c)
SOURCE_FILES := $(shell find . -maxdepth 1 -name "*.c" -not -name "*_test.c")

all: test

test: $(basename $(TEST_FILES))

%_test: %_test.c %.c $(UTIL_FILES) $(SOURCE_FILES)

	gcc $^ -L./lib -I./ -I./include -I./utils -lcmocka -std=c99 -o $(TEST_DIR)/$@

install:

	curl https://cmocka.org/files/1.1/cmocka-1.1.0.tar.xz -o cmocka.tar
	tar xf cmocka.tar
	rm cmocka.tar
	mkdir -p $(CMOCKA_OUT_DIR)
	cd $(CMOCKA_BUILD_DIR) && \
	 cmake -DWITH_STATIC_LIB=1 -DCMAKE_INSTALL_PREFIX=$(CMOCKA_OUT_DIR) .. && \
	 make && \
	 make install
	mkdir -p lib include $(TEST_DIR)
	cp $(CMOCKA_OUT_DIR)/lib/libcmocka.a lib
	cp $(CMOCKA_OUT_DIR)/include/*.h include
	rm -R $(CMOCKA_DIR)

clean:

	emulate sh -c 'rm -f *.o $(TEST_DIR)/*' 2> /dev/null
