debugcount = 0;

document.body.insertAdjacentElement(
  "beforeend",
  new DOMParser().parseFromString(
    `<div
        class="debugcol items-stretch h-1/2 h-8 w-full dark:text-zinc-50 text-zinc-950/75 bg-zinc-50 dark:bg-zinc-950/75 flex flex-col overflow-auto whitespace-pre-wrap transition-all bottom-0 fixed z-50 backdrop-filter backdrop-blur-sm">
        <div class="flex h-8 w-full shrink-0 justify-center items-center font-bold bg-zinc-50 dark:bg-zinc-950/75 p-1 sticky top-0 z-10">
            <div class="debugtitle grow rounded hover:bg-gray-500  bg-zinc-200 dark:bg-zinc-900/75 flex justify-center items-center "
             onclick="document.querySelector('.debugcol').classList.toggle('h-8');"
            > LOGS </div>
            <div class="flex self-end"
            onclick="document.querySelector('#debug-settings').classList.toggle('hidden');"
            > &#9776;</div>
        </div>
        <div  id="debug-settings" class="flex flex-col hidden  p-2 bg-zinc-50 dark:bg-zinc-950/75">
          <div class="flex p-0 m-0">
            <div class="">
              Auto Open
            </div>
            <input type='checkbox' id='debug-auto-open'
            onchange="window.localStorage.setItem('debug-auto-open', this.checked)"
            ></input>
          </div>
        </div>
        <div class="debug flex flex-col overflow-auto grow">
            <div class="grow"></div>
        </div>
    </div>`,
    "text/html"
  ).body.firstChild
);
let originalLog = window.console.log;

function uuidv4() {
  return "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx".replace(/[xy]/g, function (c) {
    let r = (Math.random() * 16) | 0,
      v = c == "x" ? r : (r & 0x3) | 0x8;
    return v.toString(16);
  });
}
function escapeHTML(str) {
  var p = document.createElement("p");
  p.appendChild(document.createTextNode(str));
  return p.innerHTML;
}
window.debug = (...args) => {
  originalLog(...args);

  const hours = new Date().getHours();
  let time =
    (hours % 12 || 12) +
    ":" +
    new Date().getMinutes() +
    ":" +
    new Date().getSeconds() +
    "." +
    new Date().getMilliseconds() +
    " " +
    (hours >= 12 ? "PM" : "AM");
  if (args[0] instanceof HTMLElement) {
    debug(escapeHTML(args[0].outerHTML));
    return;
  }
  if (typeof args[0] == "object") {
    let jsv = new DOMParser()
      .parseFromString(
        `<div class="m-1 border-2 border-green-600/50 rounded-md p-1 flex flex-col bg-zinc-50 dark:bg-zinc-950/75 pt-1 font-mono whitespace-pre-wrap"><div class="time bg-zinc-50 dark:bg-zinc-950/75 rounded-md p-1 text-xs">${time}</div></div>`,
        "text/html"
      )
      .documentElement.querySelector("body").firstChild;
    let jsv2 = new DOMParser()
      .parseFromString(`<div class="w-full h-full"></div>`, "text/html")
      .documentElement.querySelector("body").firstChild;
    document.querySelector(".debug").insertAdjacentElement("afterbegin", jsv);
    jsv.appendChild(jsv2);
    new JsonViewer({
      container: jsv2,
      data: JSON.stringify(args[0]),
      theme: "dark",
      expand: false,
    });
  } else {
    let argsString = args
      .map((e) => f(e))
      .join(" ")
      .replace(
        /[\u001b\u009b][[()#;?]*(?:[0-9]{1,4}(?:;[0-9]{0,4})*)?[0-9A-ORZcf-nqry=><]/g,
        ""
      );
    let jsv = new DOMParser()
      .parseFromString(
        `<div class="m-1 border-2 border-green-600/50 rounded-md p-1 flex flex-col bg-zinc-50 dark:bg-zinc-950/75 pt-1 font-mono whitespace-pre-wrap"><div class="time bg-zinc-50 dark:bg-zinc-950/75 rounded-md p-1 text-xs">${time}</div><div>${argsString}</div></div>`,
        "text/html"
      )
      .documentElement.querySelector("body").firstChild;
    document.querySelector(".debug").insertAdjacentElement("afterbegin", jsv);
  }
  debugcount++;
  document.querySelector(".debugtitle").textContent = `LOGS (${debugcount})`;
  if (window.localStorage.getItem("debug-auto-open") == "true")
    document.querySelector(".debugcol").classList.remove("h-8");
};
window.error = (...args) => {
  console.error(...args);

  const hours = new Date().getHours();
  let time =
    (hours % 12 || 12) +
    ":" +
    new Date().getMinutes() +
    ":" +
    new Date().getSeconds() +
    "." +
    new Date().getMilliseconds() +
    " " +
    (hours >= 12 ? "PM" : "AM");
  if (args[0] instanceof HTMLElement) {
    debug(escapeHTML(args[0].outerHTML));
    return;
  }
  if (typeof args[0] == "object") {
    let jsv = new DOMParser()
      .parseFromString(
        `<div class="m-1 border-2 border-green-600/50 rounded-md p-1 flex flex-col bg-red-500 rounded-md p-1 text-xs">${time}</div></div>`,
        "text/html"
      )
      .documentElement.querySelector("body").firstChild;
    let jsv2 = new DOMParser()
      .parseFromString(`<div class="w-full h-full"></div>`, "text/html")
      .documentElement.querySelector("body").firstChild;
    document.querySelector(".debug").insertAdjacentElement("afterbegin", jsv);
    jsv.appendChild(jsv2);
    new JsonViewer({
      container: jsv2,
      data: JSON.stringify(args[0]),
      theme: "dark",
      expand: false,
    });
  } else {
    let argsString = args
      .map((e) => f(e))
      .join(" ")
      .replace(
        /[\u001b\u009b][[()#;?]*(?:[0-9]{1,4}(?:;[0-9]{0,4})*)?[0-9A-ORZcf-nqry=><]/g,
        ""
      );
    let jsv = new DOMParser()
      .parseFromString(
        `<div class="m-1 border-2 border-green-600/50 rounded-md p-1 flex flex-col bg-red-800 pt-1 font-mono whitespace-pre-wrap"><div class="time bg-zinc-50 dark:bg-zinc-950/75 rounded-md p-1 text-xs">${time}</div><div>${argsString}</div></div>`,
        "text/html"
      )
      .documentElement.querySelector("body").firstChild;
    document.querySelector(".debug").insertAdjacentElement("afterbegin", jsv);
  }
  debugcount++;
  document.querySelector(".debugtitle").textContent = `LOGS (${debugcount})`;
  if (window.localStorage.getItem("debug-auto-open") == "true")
    document.querySelector(".debugcol").classList.remove("h-8");
};
window.onerror = (event, source, lineno, colno, error) => {
  let msg = `${event}
${source.replace(window.location.origin, "")}:${lineno}:${colno}`;
  window.error(msg);
  return false; // true if you want to consume event
};

window.console.log = (...args) => {
  debug(...args);
};

function getRect(el, parent) {
  let boundingRect = el.getBoundingClientRect();
  let parentRect = parent
    ? parent.getBoundingClientRect()
    : { left: 0, top: 0 };
  let paranetScrolls = parent
    ? { left: parent.scrollLeft, top: parent.scrollTop }
    : { left: 0, top: 0 };
  return {
    left: boundingRect.left - parentRect.left + paranetScrolls.left,
    top: boundingRect.top - parentRect.top + paranetScrolls.top,
    width: boundingRect.width,
    height: boundingRect.height,
  };
}

function tryStringify(obj) {
  if (typeof obj == "string") return obj;
  if (typeof obj == "number") return obj;
  if (typeof obj == "boolean") return obj;

  try {
    return JSON.stringify(obj);
  } catch (e) {
    return escapeHTML(obj);
  }
}
function f(o) {
  return escapeHTML(tryStringify(o));
}
let overlayEls = [];
function overlayAppError(el, e) {
  el.style.position = "relative";
  let overlayEl = document.createElement("div");
  overlayEls.push(overlayEl);
  overlayEl.addAttribute("data-debug-overlay", uuidv4());
  overlayEl.style.position = "absolute";
  overlayEl.style.border = "6px solid red";
  overlayEl.style.top = "0px";
  overlayEl.style.left = "0px";
  overlayEl.style.width = "100%";
  overlayEl.style.height = "100%";
  overlayEl.textContent = e?.message;
  overlayEl.style.fontSize = "20px";
  overlayEl.style.color = "white";
  overlayEl.style.backgroundColor = "#222222aa";
  overlayEl.style.display = "flex";
  overlayEl.style.justifyContent = "center";
  overlayEl.style.alignItems = "center";
  overlayEl.style.backdropFilter = "blur(2px)";
  el.insertAdjacentElement("afterbegin", overlayEl);

  let closeBtn = document.createElement("button");
  closeBtn.textContent = "Close";
  closeBtn.style.position = "absolute";
  closeBtn.style.top = "0px";
  closeBtn.style.right = "0px";
  closeBtn.style.fontSize = "14px";
  overlayEl.appendChild(closeBtn);

  closeBtn.addEventListener("click", () => {
    overlayEl.parentNode.removeChild(overlayEl);
  });

  let titleEl = document.createElement("div");
  titleEl.textContent = "Error in app: " + app.appname + "";
  titleEl.style.position = "absolute";
  titleEl.style.top = "0px";
  titleEl.style.left = "0px";
  titleEl.style.fontSize = "14px";
  overlayEl.appendChild(titleEl);
}

function releaseOverlayAppError(el) {
  let overlayEl = el.querySelector("[data-debug-overlay]");
  if (overlayEl) {
    overlayEl.parentNode.removeChild(overlayEl);
  }
  overlayEls = overlayEls.filter((e) => e != overlayEl);
}

function randColor() {
  return "#" + Math.floor(Math.random() * 16777215).toString(16);
}
ondebug = [];
debugEl = (el, s) => {
  if (!el || !el.style) return;
  let tempEl = {
    border: el.style.border,
    backgroundColor: el.style.backgroundColor,
    textContent: el.textContent,
    boxShadow: el.style.boxShadow,
  };
  el.style.border = "4px dotted black";
  el.style.backgroundColor = "rgba(0, 255, 0, 0.1)";
  el.style.boxShadow = "0 0 7px 7px white";

  // el.textContent = s + '\n' + el.textContent;
  el.setAttribute("data-debug", uuidv4());
  // overlayAppError(el, s);
  ondebug.push({ tmp: tempEl, el: el, id: el.attributes["data-debug"] });
};
releaseEl = (el) => {
  if (!el || !el.style) return;

  let tmp = ondebug.find((e) => e.id == el.attributes["data-debug"]);
  if (tmp) {
    el.style.border = tmp.tmp.border;
    el.style.backgroundColor = tmp.tmp.backgroundColor;
    el.style.boxShadow = tmp.tmp.boxShadow;
    // el.textContent = tmp.tmp.textContent;
    el.removeAttribute("data-debug");
    ondebug = ondebug.filter((e) => e.id != el.attributes["data-debug"]);
  }
};

circularReplacer = () => {
  const seen = new WeakSet();
  return (key, value) => {
    if (typeof value === "object" && value !== null) {
      if (seen.has(value)) {
        return;
      }
      seen.add(value);
    }
    return value;
  };
};

function tryParseJSON(jsonString) {
  try {
    var o = JSON.parse(jsonString);
    if (o && typeof o === "object") {
      return o;
    }
  } catch (e) {}

  return false;
}

function tryStringifyJSON(jsonString) {
  try {
    var o = JSON.stringify(jsonString, circularReplacer());

    return o;
  } catch (e) {}
}

function findMatches(str) {
  let matches = [];
  let regex = /{{\s*(.*?)\s*}}/g;
  let match;
  while ((match = regex.exec(str))) {
    matches.push(match[1]);
  }
  return matches;
}
function findImmediateTextNodes(el) {
  let textNodes = [];
  for (let node of el.childNodes) {
    if (node.nodeType === 3) {
      textNodes.push(node);
    }
  }
  return textNodes;
}

const toString = Object.prototype.toString;
function isString(val) {
  return typeof val === "string";
}
function isNumber(val) {
  return typeof val === "number";
}
function isBoolean(val) {
  return typeof val === "boolean";
}
function isUndefined(val) {
  return typeof val === "undefined";
}
function isArray(val) {
  return toString.call(val) === "[object Array]";
}
function isObject(val) {
  return toString.call(val) === "[object Object]";
}
function isNull(val) {
  return toString.call(val) === "[object Null]";
}
function JsonViewer(options) {
  const defaults = {
    theme: "light",
    container: null,
    data: "{}",
    expand: false,
  };
  this.options = Object.assign(defaults, options);
  if (isNull(options.container)) {
    throw new Error("Container: dom element is required");
  }
  this.render();
}
JsonViewer.prototype.renderRight = function (theme, right, val) {
  if (isNumber(val)) {
    right.setAttribute("class", theme + "rightNumber");
  } else if (isBoolean(val)) {
    right.setAttribute("class", theme + "rightBoolean");
  } else if (val === "null") {
    right.setAttribute("class", theme + "rightNull");
  } else {
    right.setAttribute("class", theme + "rightString");
  }
  right.innerText = val;
};
JsonViewer.prototype.renderChildren = function (
  theme,
  key,
  val,
  right,
  indent,
  left
) {
  let self = this;
  let folder = this.createElement("span");
  let rotate90 = this.options.expand ? "rotate90" : "";
  let addHeight = this.options.expand ? "add-height" : "";
  folder.setAttribute("class", theme + "folder " + rotate90);
  folder.onclick = function (e) {
    let nextSibling = e.target.parentNode.nextSibling;
    self.toggleItem(nextSibling, e.target);
  };
  let len = 0;
  let isObj = false;
  if (isObject(val)) {
    len = Object.keys(val).length;
    isObj = true;
  } else {
    len = val?.length;
  }
  left.innerHTML = isObj
    ? key + "&nbsp;&nbsp{" + len + "}"
    : key + "&nbsp;&nbsp[" + len + "]";
  left.prepend(folder);
  right.setAttribute("class", theme + "rightObj " + addHeight);

  self.parse(val, right, indent + 0, theme);
};

JsonViewer.prototype.parse = function (dataObj, parent, indent, theme) {
  const self = this;
  this.forEach(dataObj, function (val, key) {
    const { left, right } = self.createItem(
      indent,
      theme,
      parent,
      key,
      typeof val !== "object"
    );
    if (typeof val !== "object") {
      self.renderRight(theme, right, val);
    } else {
      self.renderChildren(theme, key, val, right, indent, left);
    }
  });
};

JsonViewer.prototype.createItem = function (
  indent,
  theme,
  parent,
  key,
  basicType
) {
  let self = this;
  let current = this.createElement("div");
  let left = this.createElement("div");
  let right = this.createElement("div");
  let wrap = this.createElement("div");

  current.style.marginLeft = indent * 2 + "px";
  left.innerHTML = `${key}<span class="jv-${theme}-symbol">&nbsp;:&nbsp;</span>`;
  if (basicType) {
    current.appendChild(wrap);
    wrap.appendChild(left);
    wrap.appendChild(right);
    parent.appendChild(current);
    current.setAttribute("class", theme + "current");
    wrap.setAttribute("class", "jv-wrap");
    left.setAttribute("class", theme + "left");
  } else {
    current.appendChild(left);
    current.appendChild(right);
    parent.appendChild(current);
    current.setAttribute("class", theme + "current");
    left.setAttribute("class", theme + "left jv-folder");
    left.onclick = function (e) {
      let nextSibling = e.target.nextSibling;
      self.toggleItem(nextSibling, e.target.querySelector("span"));
    };
  }

  return {
    left,
    right,
    current,
  };
};

JsonViewer.prototype.render = function () {
  let data = this.options.data;
  let theme = "jv-" + this.options.theme + "-";
  let indent = 0;
  let parent = this.options.container;
  let key = "object";
  let dataObj;

  parent.setAttribute("class", theme + "con");
  try {
    dataObj = JSON.parse(data);
  } catch (error) {
    throw new Error("It is not a json format");
  }
  if (isArray(dataObj)) {
    key = "array";
  }
  const { left, right } = this.createItem(indent, theme, parent, key);
  this.renderChildren(theme, key, dataObj, right, indent, left);
};

JsonViewer.prototype.toggleItem = function (ele, target) {
  ele?.classList?.toggle("add-height");
  target?.classList?.toggle("rotate90");
};

JsonViewer.prototype.createElement = function (type) {
  return document.createElement(type);
};

JsonViewer.prototype.forEach = function (obj, fn) {
  if (isUndefined(obj) || isNull(obj)) {
    return;
  }
  if (typeof obj === "object" && isArray(obj)) {
    for (let i = 0, l = obj.length; i < l; i++) {
      fn.call(null, obj[i], i, obj);
    }
  } else {
    for (let key in obj) {
      if (obj.hasOwnProperty(key)) {
        fn.call(null, obj[key] ?? "null", key, obj);
      }
    }
  }
};

window.JsonViewer = JsonViewer;
