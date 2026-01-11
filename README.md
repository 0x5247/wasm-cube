### Building the wasm module
```bash
./build.sh
```

### Running it
A server is required for js functions like `fetch` and `WebAssembly.instantiateStreaming` to work.
You can use whatever you like to locally host the contents of the "static" directory or if have go, you can use the one provided
```bash
go run server.go
```
