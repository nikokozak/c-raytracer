ROOT_DIR=$(shell pwd)/../..
UTILS=$(ROOT_DIR)/utils

projectile: projectile.c $(ROOT_DIR)/tuple.c $(UTILS)/utils.c
	gcc $^ -I$(UTILS) -I$(ROOT_DIR) -o projectile

