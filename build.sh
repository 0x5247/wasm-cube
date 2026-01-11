#!/usr/bin/env bash

clang -std=c99 \
	-Wall -Wextra -Werror -Werror=declaration-after-statement -pedantic-errors \
	-target wasm32 -O3 -fno-builtin \
	-c src/mod.c -o mod.o && \

wasm-ld --no-entry --allow-undefined \
	--export=frame_buffer \
	--export=frameSize \
	--export=frameWidth \
	--export=frameHeight \
	--export=update \
	mod.o -o static/mod.wasm && \

rm mod.o
