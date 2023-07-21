debugcount = 0;

document.body.insertAdjacentElement(
  "beforeend",
  new DOMParser().parseFromString(
    `<div
        class="debugcol h-1/2 h-8 dark:text-zinc-50 text-zinc-950/75 bg-zinc-50 dark:bg-zinc-950/75 flex flex-col overflow-auto whitespace-pre-wrap transition-all bottom-0 fixed w-screen z-50 backdrop-filter backdrop-blur-sm">
        <script src="https://cdn.tailwindcss.com"></script>
        <div onclick="document.querySelector('.debugcol').classList.toggle('h-8');"
            class="h-8 shrink-0 justify-center items-center flex flex-col  font-bold bg-zinc-50 dark:bg-zinc-950/75 p-1 sticky top-0 z-10">
            <div class="debugtitle rounded hover:bg-gray-500  bg-zinc-200 dark:bg-zinc-900/75 flex justify-center items-center w-full"> LOGS </div>
        </div>
        <div class="debug flex flex-col overflow-auto">
            <div class="grow"></div>
        </div>
    </div>`,
  ).body.firstChild
);
        // <script src="https://cdn.tailwindcss.com"></script>

document.body.appendChild(
  new DOMParser().parseFromString(
    <script src="https://cdn.tailwindcss.com"></script>
  )
);

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
const debug = (...args) => {
  console.log(...args);

  let time = new Date().toLocaleTimeString();
  if (typeof args[0] == "object") {
    let jsv = new DOMParser()
      .parseFromString(
        `<div class="m-1 border-2 border-green-600/50 rounded-md p-1 flex flex-col bg-zinc-50 dark:bg-zinc-950/75 pt-1 first-letter:font-mono whitespace-pre-wrap"><div class="time bg-zinc-50 dark:bg-zinc-950/75 rounded-md p-1 text-xs">${time}</div></div>`,
        "text/html"
      )
      .documentElement.querySelector("body").firstChild;
    let jsv2 = new DOMParser()
      .parseFromString(`<div class="w-full h-full"></div>`, "text/html")
      .documentElement.querySelector("body").firstChild;
    console.log(jsv2);
    document.querySelector(".debug").appendChild(jsv);
    jsv.appendChild(jsv2);
    new JsonViewer({
      container: jsv2,
      data: JSON.stringify(args[0]),
      theme: "dark",
      expand: false,
    });
  } else {
    let argsString = args.map((e) => f(e)).join(" ");
    let jsv = new DOMParser().parseFromString(
      `<div class="m-1 border-2 border-green-600/50 rounded-md p-1 flex flex-col bg-zinc-50 dark:bg-zinc-950/75 pt-1 first-letter:font-mono whitespace-pre-wrap"><div class="time bg-zinc-50 dark:bg-zinc-950/75 rounded-md p-1 text-xs">${time}</div><div>${argsString}</div></div>`,
      "text/html"
    ).documentElement;
    document.querySelector(".debug").appendChild(jsv);
  }
  debugcount++;
  document.querySelector(".debugtitle").textContent = `LOGS (${debugcount})`;
};
error = (s) => {
  document.querySelector(".debug").innerHTML +=
    '\n<div class="bg-red-500 font-mono border-b-2  whitespace-pre-wrap">' +
    f(s) +
    "</div>";
  document.querySelector(".debug").classList.remove("bg-sky-500/75");
  document.querySelector(".debug").classList.add("bg-red-500/75");
};
// window.onerror = function (msg, url, linenumber) {
//   document.querySelector(".debug").innerHTML +=
//     '\n<div class="bg-red-500 font-mono border-b-2  whitespace-pre-wrap">' +
//     f(msg) +
//     "\nURL: " +
//     url +
//     "\nLine Number: " +
//     linenumber +
//     "</div>";
//   document.querySelector(".debug").classList.remove("bg-sky-500/75");
//   document.querySelector(".debug").classList.add("bg-red-500/75");
//   return true;
// };
window.onerror = function (msg, url, lineNo, columnNo, error) {
  var string = msg.toLowerCase();
  var substring = "script error";
  if (string.indexOf(substring) > -1) {
    debug("Script Error: See Browser Console for Detail");
  } else {
    var message = [
      "Message: " + msg,
      "URL: " + url,
      "Line: " + lineNo,
      "Column: " + columnNo,
      "Error object: " + JSON.stringify(error),
    ].join(" - ");

    debug(message);
  }
  return false;
};
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
