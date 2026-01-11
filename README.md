### Building the wasm module
```bash
clang \
	-target wasm32 -O3 -fno-builtin \
	-c src/mod.c -o mod.o

wasm-ld --no-entry --allow-undefined \
	--export=frame_buffer \
	--export=frameSize \
	--export=frameWidth \
	--export=frameHeight \
	--export=update \
	mod.o -o static/mod.wasm
```
or
```bash
./build.sh
```

### Running it
A server is required for js functions like `fetch` and `WebAssembly.instantiateStreaming` to work.
You can use whatever you like to locally host the contents of the "static" directory or if have go, you can use the one provided
```bash
go run server.go
```
