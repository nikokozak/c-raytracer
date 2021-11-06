ROOT_DIR=$(shell pwd)/../..
UTILS=$(ROOT_DIR)/utils

clock: clock.c $(ROOT_DIR)/tuple.c $(ROOT_DIR)/canvas.c  $(ROOT_DIR)/color.c $(ROOT_DIR)/matrix.c $(ROOT_DIR)/transform.c $(UTILS)/utils.c
	gcc $^ -I$(UTILS) -I$(ROOT_DIR) -o clock

