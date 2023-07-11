const rootIdentifier = "root";
const allProxies = [];

function recursizeProxify(
  obj,
  isRoot = true,
  rootObj,
  key,
  parent,
  handlerInc
) {
  if (!rootObj) rootObj = obj;

  // if (Array.isArray(obj)) {
  //   let obj2 = {};
  //   obj.forEach((item, index) => {
  //     obj2[index] = item;
  //   });
  //   obj = obj2;
  //
  // }
  let handler = {
    _isArray: Array.isArray(obj),
    _isJSONReactive: true,
    get(target, prop) {
      if (prop == "[[handler]]") {
        return handler;
      }
      if (prop == "length" && Array.isArray(target)) {
        // allProxies.forEach((p) => {
        //   p.proxy["[[handler]]"]._activeGet = false;
        // });
        // handler._root._activeGet = true;
        return target.length;
      }

      handler._root._currentAccessedPath?.push(prop);
      allProxies.forEach((p) => {
        p.proxy["[[handler]]"]._activeGet = false;
      });
      handler._root._activeGet = true;
      if (Object.keys(target).includes(prop)) {
        handler._root._currentAccessedPathArr = [
          ...this._path,
          target instanceof Array ? parseInt(prop) : prop,
        ];
      }
      return target[prop];
    },
    set(target, prop, value) {
      let oldVal = target[prop];

      this._callCallbacks(
        [...this._path, prop].join("."),
        oldVal,
        value,
        target,
        prop
      );
      if (typeof value == "object") {
        value = value;
      }
      target[prop] = recursizeProxify(
        value,
        false,
        rootObj,
        prop,
        target,
        handler
      );
      return true;
    },
    _startRecording() {
      handler._root._currentAccessedPath = [rootIdentifier];
      handler._root._recording = true;
    },
    _stopRecording() {
      handler._root._recording = false;
      return handler._root._currentAccessedPathArr;
    },
    _callCallbacks(pathStr, oldVal, newVal, target, prop) {
      for (let key in handler._root._callbacks) {
        let matchPath = pathStr.slice(0, key.length);
        if (matchPath == key) {
          let oldV = fastObjCopy(
            getValueByPath(matchPath.split("."), this._root._obj)
          );
          target[prop] = newVal;
          let newV = fastObjCopy(
            getValueByPath(matchPath.split("."), this._root._obj)
          );

          handler._root._callbacks[matchPath].forEach((cb) => {
            cb(oldV, newV, pathStr, prop, newVal);
          });
        }
        target[prop] = oldVal;
      }
    },
  };

  if (isRoot) {
    handler._root = handler;
    handler._parent = null;
    handler._isRoot = true;
    handler._path = [rootIdentifier];

    handler._callbacks = {};
    handler._obj = obj;
  } else {
    handler._root = handlerInc._root;
    handler._parent = handlerInc;
    handler._path = [
      ...handlerInc._path,
      parent instanceof Array ? parseInt(key) : key,
    ];
    handler._callbacks = {};
    handler._obj = obj;
  }

  let result = null;

  if (obj && typeof obj == "object") {
    try {
      for (let key in obj) {
        if (typeof obj[key] == "object") {
          obj[key] = recursizeProxify(
            obj[key],
            false,
            rootObj,
            key,
            obj,
            handler
          );
        }
      }
      result = new Proxy(obj, handler);
    } catch (e) {
      result = obj;
    }
  } else {
    result = obj;
  }

  handler._obj = result;
  return result;
}

function findPath(access_func) {
  let path = null;
  let pxRoot = null;
  let robj = typeof access_func == "function" ? access_func() : access_func;

  if (robj && robj["[[handler]]"] && robj["[[handler]]"]._isJSONReactive) {
    path = robj["[[handler]]"]._path;
    pxRoot = robj;
    return path;
  } else {
    pxRoot = allProxies.find((p) => p.proxy["[[handler]]"]._activeGet)?.proxy;
    // if (!pxRoot) pxRoot = robj[Object.keys(robj)[0]];
  }
  path = pxRoot["[[handler]]"]._stopRecording();

  for (let i = 0; i < path.length; i++) {
    if (getValueByPath(path.slice(0, i), pxRoot) instanceof Array) {
      path[i] = parseInt(path[i]);
    }
  }

  return path;
}

function formatPath(path) {
  let res = "";
  for (let i = 0; i < path.length; i++) {
    if (typeof path[i] == "number") {
      res += `[${path[i]}]`;
    } else {
      res += i == 0 ? path[i] : `.${path[i]}`;
    }
  }
  return res;
}

function findRelativePath(access_func, root) {
  let dataPath = findPath(access_func);
  let rootPath = findPath(root);

  let res = [];
  for (let i = 0; i < dataPath.length; i++) {
    if (dataPath[i] != rootPath[i]) {
      res.push(dataPath[i]);
    }
  }
  return res;
}
function resolveFullPath(path, relativeRoot) {
  let relativeRootPath = findPath(relativeRoot);

  return relativeRootPath.concat(path);
}
function parsePath(path) {
  let res = [];
  let current = "";
  for (let i = 0; i < path.length; i++) {
    if (path[i] == ".") {
      if (current) res.push(current);
      current = "";
    } else if (path[i] == "[") {
      res.push(current);
      current = "";
      let j = i + 1;
      while (path[j] != "]") {
        current += path[j];
        j++;
      }
      res.push(parseInt(current));
      current = "";
      i = j;
    } else {
      current += path[i];
    }
  }
  if (current) res.push(current);

  return res;
}

function getValueByPath(path, proxy) {
  let obj = proxy;
  for (let i = 0; i < path.length; i++) {
    if (path[i] == rootIdentifier) continue;
    obj = obj[path[i]];
  }
  return obj;
}

function setValueByPath(
  path,
  value,
  proxy,
  silent = false,
  cleanAssign = true
) {
  let obj = proxy;
  let callbacksStash = proxy["[[handler]]"]._callbacks;
  if (silent) {
    proxy["[[handler]]"]._callbacks = {};
  }
  for (let i = 0; i < path.length - 1; i++) {
    if (path[i] == rootIdentifier) continue;
    obj = obj[path[i]];
  }

  if (cleanAssign) {
    // if (typeof obj == "object") {
    //   for (let key in obj) {
    //     if (key == path[path.length - 1]) continue;
    //     delete obj[key];
    //   }
    // }
  }

  let res = null;
  if (path[path.length - 1] == rootIdentifier) {
    if (typeof value != "object")
      throw new Error("Root object must be an object");
    Object.assign(obj, value);
    res = obj;
  } else {
    obj[path[path.length - 1]] = recursizeProxify(
      value,
      false,
      proxy["[[handler]]"]._root._obj,
      path[path.length - 1],
      obj,
      proxy["[[handler]]"]
    );
    res = obj[path[path.length - 1]];
  }
  if (silent) {
    proxy["[[handler]]"]._callbacks = callbacksStash;
  }

  return res;
}

function fastObjCopy(obj) {
  return JSON.parse(JSON.stringify(obj));
}
function watch(access_func, callback) {
  // if (
  //   typeof access_func != "function" &&
  //   !access_func["[[handler]]"] &&
  //   !access_func["[[handler]]"]._isJSONReactive
  // )
  //   throw new Error("access_func must be a function or a json-reactive object");

  let path = null;
  let pxRoot = null;
  let robj = typeof access_func == "function" ? access_func() : access_func;

  if (robj && robj["[[handler]]"] && robj["[[handler]]"]._isJSONReactive) {
    path = robj["[[handler]]"]._path;
    pxRoot = robj["[[handler]]"]._root._obj;
  } else {
    path = findPath(access_func);

    pxRoot = allProxies.find((p) => p.proxy["[[handler]]"]._activeGet)?.proxy;
    if (!pxRoot) pxRoot = robj[Object.keys(robj)[0]];
  }

  let pathStr = path.map((x) => x.toString()).join(".");

  if (!pxRoot["[[handler]]"]._callbacks[pathStr]) {
    pxRoot["[[handler]]"]._callbacks[pathStr] = [];
  }
  pxRoot["[[handler]]"]._callbacks[pathStr].push(callback);

  return pathStr;
}

function unwatch(access_func, callback) {
  let path = null;
  let pxRoot = null;
  let robj = typeof access_func == "function" ? access_func() : access_func;

  if (robj && robj["[[handler]]"] && robj["[[handler]]"]._isJSONReactive) {
    path = robj["[[handler]]"]._path;
    pxRoot = robj["[[handler]]"]._root._obj;
  } else {
    path = findPath(access_func);

    pxRoot = allProxies.find((p) => p.proxy["[[handler]]"]._activeGet)?.proxy;
    if (!pxRoot) pxRoot = robj[Object.keys(robj)[0]];
  }

  let pathStr = path.map((x) => x.toString()).join(".");
  if (pxRoot["[[handler]]"]._callbacks[pathStr]) {
    let index = pxRoot["[[handler]]"]._callbacks[pathStr].indexOf(callback);
    if (index != -1) {
      pxRoot["[[handler]]"]._callbacks[pathStr].splice(index, 1);
    }
  }
}

function create(data) {
  let px = recursizeProxify(data);
  px["[[handler]]"]._activeGet = true;
  allProxies.push({ proxy: px });
  return px;
}

const data = {
  appname: "root",
  children: [
    {
      appname: "app",
      el: {},
      children: [],
      data: { list: [32, 4, 34, 5, 4, 5, 423] },
    },
    { appname: "app2", el: {}, children: [], data: {} },
  ],
  el: {},
  data: {},
};
let proxy = create(data);

// const data2 = {
//   deep: [2, 3],
// };

// let proxy2 = create(data2);
// //
// let p2 = proxy.hello;

//
//

// watchJSON(
//   () => proxy.hello.world,
//   (o, n, p, k, v) => {
//
//   }
// );

// proxy.hello.world = 24;
// setValByPath(
//   findPath(() => proxy.hello.world),
//   34,
//   false
// );

//

// proxy.hello.world[0] = 24;
function hyperscript(nodeName, attrs, ...children) {
  const $el = window.document.createElement(nodeName);

  for (let key in attrs) {
    if (Object.prototype.hasOwnProperty.call(attrs, key)) {
      if (key in $el) {
        // Set property if key is a property name
        $el[key] = attrs[key];
      } else {
        // Set attribute otherwise
        $el.setAttribute(key, attrs[key]);
      }
    }
  }

  children.forEach((child) => {
    if (typeof child === "string") {
      $el.appendChild(window.document.createTextNode(child));
    } else {
      $el.appendChild(child);
    }
  });
  return $el;
}

function updatescript($el, attrs, ...children) {
  $el.innerHTML = "";
  children.forEach((child) => {
    if (typeof child === "string") {
      $el.appendChild(window.document.createTextNode(child));
    } else {
      $el.appendChild(child);
    }
  });

  for (let key in attrs) {
    if (Object.prototype.hasOwnProperty.call(attrs, key)) {
      if (key in $el) {
        // Set property if key is a property name
        $el[key] = attrs[key];
      } else {
        // Set attribute otherwise
        $el.setAttribute(key, attrs[key]);
      }
    }
  }

  return $el;
}

renderApp = () => {
  window.app = extreme.create({});
  window.app.data = {};
  window.app.els = {};

  watch(window.app.els, (o, n, p, k, v) => {
    // let eldata = extreme.getValueByPath(p.split("."), window.app);
    //
    // for (let key in eldata.props) {
    //   eldata.el[key] = window.app.data[eldata.props[key]] || "Undefined";
    // }
  });
  watch(window.app.data, (o, n, p, k, v) => {
    for (let key in window.app.els[k]?.props) {
      let targVal = window.app.els[k].props[key].template.replace(
        window.app.els[k].props[key].variable,
        v || "Undefined"
      );
      window.app.els[k].el[key] = targVal;
    }
    // window.app.els[k].el.textContent = window.app.data[k];
  });
  // Recursive function to traverse the DOM
  function traverseDOM(node) {
    if (node.nodeType === Node.ELEMENT_NODE) {
      // Check if the element's immediate text content contains {{}} notation
      if (
        node.childNodes.length === 1 &&
        node.firstChild.nodeType === Node.TEXT_NODE
      ) {
        const textContent = node.firstChild.textContent.trim();
        let matc = /\{\{.*?\}\}/.exec(textContent);
        matc = matc?.[0];
        if (matc) {
          window.app.data.debug = matc;

          window.app.els[matc.slice(2, -2).trim()] = {
            el: node,
            props: {
              textContent: {
                template: textContent,
                variable: matc,
              },
            },
          };
        }
      }
      const classString = /\[.*?\]/.exec(node.classList.value)?.[0];
      if (classString) {
        window.app.els[classString.slice(1, -1).trim()] = {
          el: node,
          props: {
            classList: {
              template: node.classList.value,
              variable: classString,
            },
          },
        };
      }
      const e_for = node.getAttribute("e-for");
      if (e_for) {
        //for item in items
        window.app.data.list = [13, 2, 432, 54, 32, 5];
        let [item, in_, items] = e_for.split(" ");
        [item, in_, items] = [item, in_, window.app.data[items]];

        window.app.data.debug = [item, in_, items];

        for (let item in items) {
          let newEl = node.cloneNode(true);
          newEl.removeAttribute("e-for");
          newEl.innerHTML = item;
          node.parentNode.insertBefore(newEl, node);
        }
      }
    }
    // Continue traversing child nodes
    node = node.firstChild;
    while (node) {
      traverseDOM(node);
      node = node.nextSibling;
    }
  }

  // Start traversing from the document body
  traverseDOM(document.body);
  return window.app;
};
function uuidv4() {
  return "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx".replace(/[xy]/g, function (c) {
    let r = (Math.random() * 16) | 0,
      v = c == "x" ? r : (r & 0x3) | 0x8;
    return v.toString(16);
  });
}
if (typeof module != "undefined")
  module.exports = {
    create,
    watch,
    getValueByPath,
    setValueByPath,
    renderApp,
    findPath,
    findRelativePath,
    formatPath,
    parsePath,
    resolveFullPath,
    unwatch,
  };
else {
  window.extreme = {
    create,
    watch,
    getValueByPath,
    setValueByPath,
    renderApp,
    findPath,
    findRelativePath,
    formatPath,
    parsePath,
    resolveFullPath,
    unwatch,
  };
}
