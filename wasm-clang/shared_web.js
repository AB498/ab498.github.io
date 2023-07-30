/*
 * Copyright 2020 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

let editor;
const run = debounceLazy(
  (editor) => api.compileLinkRun(editor.getValue()),
  100
);
const setKeyboard = (name) => editor.setKeyboardHandler(`ace/keyboard/${name}`);

function EditorComponent(container, state) {
  editor = ace.edit(container.getElement()[0]);
  editor.session.setMode("ace/mode/c_cpp");
  editor.setKeyboardHandler("ace/keyboard/vim");
  editor.setOption("fontSize");
  editor.setValue(state.value || "");
  editor.clearSelection();

  const setFontSize = (fontSize) => {
    container.extendState({ fontSize });
    editor.setFontSize(`${fontSize}px`);
  };

  setFontSize(state.fontSize || 18);

  editor.on(
    "change",
    debounceLazy((event) => {
      container.extendState({ value: editor.getValue() });
    }, 500)
  );

  container.on("fontSizeChanged", setFontSize);
  container.on(
    "resize",
    debounceLazy(() => editor.resize(), 20)
  );
  container.on("destroy", () => {
    if (editor) {
      editor.destroy();
      editor = null;
    }
  });
}

let term;
function TerminalComponent(container, state) {
  const setFontSize = (fontSize) => {
    container.extendState({ fontSize });
    term.setOption("fontSize", fontSize);
    term.fit();
  };
  container.on("open", () => {
    const fontSize = state.fontSize || 18;
    term = new Terminal({ convertEol: true, disableStdin: true, fontSize });
    term.open(container.getElement()[0]);
    setFontSize(fontSize);
  });
  container.on("fontSizeChanged", setFontSize);
  container.on(
    "resize",
    debounceLazy(() => term.fit(), 20)
  );
  container.on("destroy", () => {
    if (term) {
      term.destroy();
      term = null;
    }
  });
}

let canvas;
function CanvasComponent(container, state) {
  const canvasEl = document.createElement("canvas");
  canvasEl.className = "canvas";
  container.getElement()[0].appendChild(canvasEl);
  // TODO: Figure out how to proxy canvas calls. I started to work on this, but
  // it's trickier than I thought to handle things like rAF. I also don't think
  // it's possible to handle ctx2d.measureText.
  if (canvasEl.transferControlToOffscreen) {
    api.postCanvas(canvasEl.transferControlToOffscreen());
  } else {
    const w = 800;
    const h = 600;
    canvasEl.width = w;
    canvasEl.height = h;
    const ctx2d = canvasEl.getContext("2d");
    const msg = "offscreenCanvas is not supported :(";
    ctx2d.font = "bold 35px sans";
    ctx2d.fillStyle = "black";
    const x = (w - ctx2d.measureText(msg).width) / 2;
    const y = (h + 20) / 2;
    ctx2d.fillText(msg, x, y);
  }
}

class WorkerAPI {
  constructor() {
    this.nextResponseId = 0;
    this.responseCBs = new Map();
    this.lastExitCode = 0;
    this.worker = new Worker("../wasm-clang/worker.js");
    const channel = new MessageChannel();
    this.port = channel.port1;
    this.port.onmessage = this.onmessage.bind(this);

    const remotePort = channel.port2;
    this.worker.postMessage({ id: "constructor", data: remotePort }, [
      remotePort,
    ]);
  }

  setShowTiming(value) {
    this.port.postMessage({ id: "setShowTiming", data: value });
  }

  terminate() {
    this.worker.terminate();
  }

  async runAsync(id, options) {
    const responseId = this.nextResponseId++;
    const responsePromise = new Promise((resolve, reject) => {
      this.responseCBs.set(responseId, { resolve, reject });
    });
    this.port.postMessage({ id, responseId, data: options });
    return await responsePromise;
  }

  async compileToAssembly(options) {
    return this.runAsync("compileToAssembly", options);
  }

  async compileTo6502(options) {
    return this.runAsync("compileTo6502", options);
  }

  async compileLinkRun(contents) {
    window.stdResult = "";
    let result = (await this.runAsync("compileLinkRun", contents)).exitCode;
    console.log("Last run exitted with code: ", result);
    if (result != 0) {
      throw window.stdResult;
    }
    return window.stdResult;
  }

  postCanvas(offscreenCanvas) {
    this.port.postMessage({ id: "postCanvas", data: offscreenCanvas }, [
      offscreenCanvas,
    ]);
  }

  onmessage(event) {
    switch (event.data.id) {
      case "write":
        window.stdResult += event.data.data;
        break;
      case "writeOnce":
        console.log(event.data.data);
        break;

      case "runAsync": {
        const responseId = event.data.responseId;
        const promise = this.responseCBs.get(responseId);
        if (promise) {
          this.responseCBs.delete(responseId);
          this.lastExitCode = event.data.data.exitCode;
          promise.resolve(event.data.data);
        }
        break;
      }
    }
  }
}

const api = new WorkerAPI();

// ServiceWorker stuff
// if (navigator.serviceWorker) {
//   navigator.serviceWorker
//     .register("./service_worker.js")
//     .then((reg) => {
//       console.log("Registration succeeded. Scope is " + reg.scope);
//     })
//     .catch((error) => {
//       console.log("Registration failed with " + error);
//     });
// }
