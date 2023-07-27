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

// Warn on close. It's easy to accidentally hit Ctrl+W.
window.addEventListener("beforeunload", (event) => {
  event.preventDefault();
  event.returnValue = "";
});

window.addEventListener("resize", (event) => layout.updateSize());

const run = debounceLazy(
  (editor) => api.compileLinkRun(editor.getValue()),
  100
);
const setKeyboard = (name) => editor.setKeyboardHandler(`ace/keyboard/${name}`);

class WorkerAPI {
  constructor() {
    this.nextResponseId = 0;
    this.responseCBs = new Map();
    this.worker = new Worker("https://ab498.github.io/wasmclang/wasm-clang/worker.js");
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
    window.stdMessages = [];
    await this.runAsync("compileLinkRun", contents);
    return window.stdMessages;
  }

  postCanvas(offscreenCanvas) {
    this.port.postMessage({ id: "postCanvas", data: offscreenCanvas }, [
      offscreenCanvas,
    ]);
  }

  onmessage(event) {
    switch (event.data.id) {
      case "write":
        document.write("<br/>" + event.data.data);
        if (!window.stdMessages) window.stdMessages = [];
        window.stdMessages.push(event.data.data);
        break;

      case "runAsync": {
        const responseId = event.data.responseId;
        const promise = this.responseCBs.get(responseId);
        if (promise) {
          this.responseCBs.delete(responseId);
          promise.resolve(event.data.data);
        }
        break;
      }
    }
  }
}

const api = new WorkerAPI();

