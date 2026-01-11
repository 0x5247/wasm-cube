const runWasm = (wasmModule) => {
	const exports = wasmModule.instance.exports;

	const memory = exports.memory;

	canvas.width = exports.frameWidth();
	canvas.height = exports.frameHeight();

	const ctx = canvas.getContext("2d", { willReadFrequently: false });

	const frame = new ImageData(
		new Uint8ClampedArray(memory.buffer, exports.frame_buffer.valueOf(), exports.frameSize()),
		canvas.width,
		canvas.height
	);

	const step = () => {
		exports.update();

		ctx.putImageData(frame, 0, 0);
		requestAnimationFrame(step);
	};

	step();
};

const wasmBrowserInstantiate = async (wasmModuleUrl, importObject) => {
	let response = undefined;

	if (!importObject) {
		importObject = {
			env: {
				abort: () => console.log("Abort!")
			}
		};
	}

	if (WebAssembly.instantiateStreaming) {
		response = await WebAssembly.instantiateStreaming(
			fetch(wasmModuleUrl),
			importObject
		);
	} else {
		const fetchAndInstantiateTask = async () => {
			const wasmArrayBuffer = await fetch(wasmModuleUrl).then(response =>
				response.arrayBuffer()
			);
			return WebAssembly.instantiate(wasmArrayBuffer, importObject);
		};
		response = await fetchAndInstantiateTask();
	}

	return response;
};

wasmBrowserInstantiate("/mod.wasm", {
	env: {
		abort: () => console.log("Abort!"),
		sin: (v) => Math.sin(v),
		cos: (v) => Math.cos(v),
	},
}).then(runWasm);
