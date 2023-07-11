let xData = {
  lastXPX: null,
  lastPath: null,
  arrayPaths: [],
};

watcherCount = 0;
watcherUUID = () => watcherCount++;

class XJSON {
  static xProxy = () => ({
    _isXJSON: true,
    get(target, prop) {
      if (prop == "[[handler]]") return this;
      if (typeof prop == "symbol") return target[prop];
      if (prop == "length")
        if (Array.isArray(target)) {
          return target.length;
        } else {
          return Object.keys(target).length;
        }
      if (typeof target[prop] == "undefined") {
        return undefined;
      }
      if (!target[prop]["[[handler]]"]) {
        xData.lastPath = [
          ...this._path,
          Array.isArray(target) ? parseInt(prop) : prop,
        ];
      } else {
        xData.lastPath = target[prop]["[[handler]]"]._path;
      }
      return target[prop];
    },
    set(target, prop, value) {
      let oldVal = copyObj(target[prop]);
      if (prop == "length") {
        if (Array.isArray(target)) {
          target.length = value;
          return true;
        } else {
          return false;
        }
      }
      let px = XJSON.create(this._px, value, false, prop);
      for (let key in this._root["[[handler]]"]._callbacks) {
        let callbackPath = this._root["[[handler]]"]._callbacks[key];
        if (key == XJSON.stringifyPath(px._path).slice(0, key.length)) {
          let wholeVal = copyObj(
            XJSON.get(this._root["[[handler]]"]._px, XJSON.parsePath(key))
          );
          target[prop] = value;
          let wholeValNew = XJSON.get(
            this._root["[[handler]]"]._px,
            XJSON.parsePath(key)
          );
          for (let callbackName in callbackPath) {
            callbackPath[callbackName].forEach((callback) => {
              callback[1](wholeVal, wholeValNew, key, prop, value);
            });
          }
          target[prop] = oldVal;
        }
      }
      target[prop] = px._px;

      return true;
    },
  });
  static stringifyPath(path) {
    let str = "";
    let absolute = path[0] == "";

    for (let i = absolute ? 1 : 0; i < path.length; i++) {
      if (typeof path[i] == "number") {
        str += `[${path[i]}]`;
      } else {
        str += `.${path[i]}`;
      }
    }

    return str;
  }
  static parsePath(pathStr) {
    let parsedPath = [];
    let gathered = "";
    for (let i = 0; i < pathStr.length; i++) {
      let c = pathStr[i];
      if (c == ".") {
        parsedPath.push(gathered);
        gathered = "";
      } else if (c == "[") {
        parsedPath.push(gathered);
        gathered = "";
        let num = "";
        while (pathStr[++i] != "]") {
          num += pathStr[i];
        }
        parsedPath.push(parseInt(num));
      } else {
        gathered += c;
      }
    }
    if (gathered) parsedPath.push(gathered);

    return parsedPath;
  }

  static get(obj, path) {
    let pathArr = path;
    let currentObj = obj;
    if (path[0] == "" && path.length > 1) pathArr = path.slice(1);
    for (let i = 0; i < pathArr.length; i++) {
      currentObj = currentObj[pathArr[i]];
    }
    return currentObj;
  }
  static set(obj, path, val) {
    let pathArr = path;
    let currentObj = obj;
    if (path[0] == "" && path.length > 1) pathArr = path.slice(1);
    for (let i = 0; i < pathArr.length; i++) {
      if (i == pathArr.length - 1) currentObj[pathArr[i]] = val;
      currentObj = currentObj[pathArr[i]];
    }
    return currentObj;
  }
  static isObject(obj) {
    return typeof obj == "object" && obj !== null;
  }
  static create(parent, obj, root, nodeName) {
    let xpx = this.xProxy();
    xpx._isRoot = root;
    xpx._obj = obj;
    if (typeof obj == "object") xpx._px = new Proxy(obj, xpx);
    else xpx._px = obj;

    if (xpx._isRoot) {
      xpx._callbacks = {};
      xpx._root = xpx._px;
      xpx._path = [nodeName];
    } else {
      if (Array.isArray(parent["[[handler]]"]._obj)) {
        nodeName = parseInt(nodeName);
      }
      xpx._root = parent["[[handler]]"]._px["[[handler]]"]._root;
      xpx._path = [...parent["[[handler]]"]._px["[[handler]]"]._path, nodeName];
    }

    // if (Array.isArray(obj))
    //   xData.arrayPaths.push({ path: xpx._path, obj: root });

    // console.log(xpx);
    for (let key in xpx._px) {
      if (typeof xpx._px[key] == "object") {
        xpx._px[key] = xpx._px[key];
      }
    }
    return xpx;
  }
  static getPath(access_func) {
    return access_func()["[[handler]]"]?._path || xData.lastPath;
  }
  static watch(obj, path, callback, name) {
    let id = watcherUUID();
    if (!obj["[[handler]]"]._root["[[handler]]"]._callbacks[path]) {
      obj["[[handler]]"]._root["[[handler]]"]._callbacks[path] = {};
    }
    if (!obj["[[handler]]"]._root["[[handler]]"]._callbacks[path][name]) {
      obj["[[handler]]"]._root["[[handler]]"]._callbacks[path][name] = [];
    }
    obj["[[handler]]"]._root["[[handler]]"]._callbacks[path][name].push([
      id,
      callback,
    ]);
    return id;
  }
  static unwatch(obj, path, name, id) {
    try {
      if (name)
        delete obj["[[handler]]"]._root["[[handler]]"]._callbacks[path][name];
      else delete obj["[[handler]]"]._root["[[handler]]"]._callbacks[path];
    } catch (e) {
      console.log(e);
    }

    return obj["[[handler]]"]._root["[[handler]]"]._callbacks[path];
  }
  static getWatchers(obj, path) {
    return obj["[[handler]]"]._root["[[handler]]"]._callbacks[path];
  }
}
function copyObj(obj) {
  if (typeof obj == "object") {
    let newObj = {};
    for (let key in obj) {
      newObj[key] = copyObj(obj[key]);
    }
    return new Proxy(newObj, XJSON.xProxy());
  } else {
    return obj;
  }
}
// let obj = XJSON.create(
//   {},
//   { hello: "world", deep: { deep1: [23, 25] } },
//   true,
//   ""
// )._px;

// XJSON.watch(
//   obj,
//   //   ".deep.deep1",
//   XJSON.stringifyPath(XJSON.getPath(() => obj.deep.deep1)),
//   (oldVal, newVal) => {
//     console.log(oldVal.length, newVal);
//   },
//   "test"
// );
// console.log(XJSON.parsePath("hello"));
// obj.deep.deep1.push(235);

// let rootData = XJSON.create(
//   {},
//   {
//     ["i"]: 0,
//   },
//   true,
//   ""
// )._px;

// console.log(XJSON.get(rootData, XJSON.parsePath("i")));

window.XJSON = XJSON;

///////////////////////
autoDOMData = {};

class AutoDOM {
  static attach(selector, obj) {}
  static create(selector, obj) {
    let rootData = XJSON.create({}, obj, true, "")._px;
    obj = rootData;
    // rootData.items[0] = { show: true };
    // rootData.deep.deep1[0] = 100;
    let element = document.querySelector(selector);
    if (!element) return;
    // for (let key in attrMap) {
    //     debug(JSON.stringify(XJSON.get(rootData, XJSON.parsePath(attrMap[key]))));
    // }
    let attrMap = Object.fromEntries(
      Object.entries(rootData).map(([key, val]) => [
        key,
        XJSON.stringifyPath(XJSON.getPath(() => rootData[key])),
      ])
    );

    fire(element, rootData, element, { attrMap }, rootData, true, element);
    return rootData;
  }
}
function fire(el, data, template, watchinfo = {}, dataroot, attach, ignoreEl) {
  if (ignoreEl == el) {
    let chs = [...el.children];
    for (let child of chs) {
      fire(child, data, child, watchinfo, dataroot, attach);
    }
    return;
  }
  if (el?.attributes["e-app"]) {
    AutoDOM.create("#" + el.attributes["e-app"].value, { ...data });
    // fire(el, data, el, watchinfo, dataroot, true);

    return;
  }
  try {
    let _elTemp = el.cloneNode(true);
    if (!el.attributes["e-data-id"]) el.setAttribute("e-data-id", uuidv4());
    if (el.attributes["e-if"]) {
      let ifData = XJSON.get(
        rootData,
        XJSON.parsePath(el.attributes["e-if"].value)
      );
      if (!ifData) {
        el.style.display = "none";
        el.remove();
        return;
      }
      el.removeAttribute("e-if");
    }
    if (el.attributes["e-for"]) {
      // for (item, index) in list
      let forItemIndex = el.attributes["e-for"].value.split("in")[0].trim();
      let forItem = forItemIndex.replace(/\(|\)/g, "").split(",")[0]?.trim();
      let forIndex = forItemIndex.replace(/\(|\)/g, "").split(",")[1]?.trim();
      let forList = el.attributes["e-for"].value.split(" in ")[1].trim();
      let forListData = data[forList];
      // debug("e-for", forListData);

      el.removeAttribute("e-for");
      let renderedEls = [];
      // for (let renderedEl of renderedEls) {
      //     renderedEl.remove();
      // }
      // renderedEls = []

      for (let i = 0; i < forListData.length; i++) {
        let item = forListData[i];
        let renderedEl = renderedEls[i];
        if (!renderedEl) {
          renderedEl = el.cloneNode(true);
          renderedEls.push(renderedEl);
          el.insertAdjacentElement("beforebegin", renderedEl);
        }
        let itemData = {
          ...data,
          [forIndex]: i,
          [forItem]: item,
        };
        if (!dataroot._tmp) dataroot._tmp = {};
        let uid = uuidv4();
        dataroot._tmp[uid] = i;
        let uid2 = uuidv4();
        dataroot._tmp[uid2] = item;
        // debug("uid", XJSON.stringifyPath(XJSON.getPath(() => dataroot._tmp[uid])));
        attrMapNew = {};
        attrMapNew[forIndex] = XJSON.stringifyPath(
          XJSON.getPath(() => dataroot._tmp[uid])
        );
        attrMapNew[forItem] = XJSON.stringifyPath(
          XJSON.getPath(() => dataroot._tmp[uid2])
        );

        fire(
          renderedEl,
          itemData,
          renderedEl,
          { renderedEls, attrMap: { ...watchinfo.attrMap, ...attrMapNew } },
          dataroot,
          attach
        );
      }
      el.style.display = "none";
      // el.remove();
      // debug(XJSON.getPath(() => ['items'].length))
      if (attach) {
        XJSON.watch(dataroot, ".items", (old, val, p, k, v) => {
          XJSON.unwatch(dataroot, ".items");
          // for (let renderedEl of renderedEls) {
          //     renderedEl.remove();
          // }
          // renderedEls = []
          // debug("old", old?.length, "val", val.length);
          if (old?.length != val.length) {
            el.style.display = "block";
            el.setAttribute("e-for", _elTemp.attributes["e-for"].value);

            fire(el, data, el, watchinfo, dataroot, true);
          }
        });
      }
      return;
    }

    let textNodes = findImmediateTextNodes(el);
    let textNodesT = findImmediateTextNodes(template);
    for (let i = 0; i < textNodesT.length; i++) {
      let textNode = textNodes[i];
      let textNodeT = textNodesT[i];

      let matchesSqBrackets = findMatchesSqBrackets(textNodeT.textContent);
      let toReplace = textNodeT.textContent;
      for (let match of matchesSqBrackets) {
        if (match.trim()[0] == '"') continue;
        if (/^\d+$/.test(match.trim())) continue;
        let key = match.trim();
        let val = XJSON.get(dataroot, [
          ...XJSON.parsePath(watchinfo.attrMap[XJSON.parsePath(match)[0]]),
          ...XJSON.parsePath(match).slice(1),
        ]);
        toReplace = toReplace.replace(
          new RegExp("\\[\\s*" + escapeRegex(key) + "\\s*\\]", "g"),
          "[" + val + "]"
        );
      }

      let matches = findMatches(toReplace);
      let id = el.attributes["e-data-id"].value;
      for (let match of matches) {
        let key = match.trim();
        let pth = watchinfo.attrMap[XJSON.parsePath(match)[0]];
        let val = XJSON.get(dataroot, [
          ...XJSON.parsePath(watchinfo.attrMap[XJSON.parsePath(match)[0]]),
          ...XJSON.parsePath(match).slice(1),
        ]);
        // debug('val', val)
        if (pth) {
          // debug("wc ", Object.keys(XJSON.getWatchers(dataroot, pth) || []).length);
          // XJSON.unwatch(dataroot, pth, id);
          if (attach) {
            XJSON.watch(
              dataroot,
              pth,
              (old, val) => {
                // debug(pth, val);
                reseAttrs(el, _elTemp);
                // debug("matches", match, el.textContent.trim());
                // XJSON.unwatch(dataroot, pth, id);
                // debug('removed ' + JSON.stringify(id in Object.keys(XJSON.getWatchers(dataroot, pth))));
                fire(el, data, el, watchinfo, dataroot, false);
              },
              id
            );
          }
        }
        toReplace = toReplace.replace(
          new RegExp("{{\\s*" + escapeRegex(key) + "\\s*}}", "g"),
          JSON.stringify(val)
        );
      }
      textNode.textContent = toReplace;
    }

    let attrs = [...el.attributes];
    for (let attr of attrs) {
      if (attr.name == "@click") continue;
      let matches = findMatches(attr.value);
      let id = el.attributes["e-data-id"].value;
      for (let match of matches) {
        let key = match.trim();
        let pth = watchinfo.attrMap[XJSON.parsePath(match)[0]];

        let val = XJSON.get(dataroot, [
          ...XJSON.parsePath(watchinfo.attrMap[XJSON.parsePath(match)[0]]),
          ...XJSON.parsePath(match).slice(1),
        ]);
        if (pth) {
          // debug("wc ", Object.keys(XJSON.getWatchers(dataroot, pth) || []).length);
          // XJSON.unwatch(dataroot, pth, id);
          if (attach) {
            XJSON.watch(
              dataroot,
              pth,
              (old, val) => {
                reseAttrs(el, _elTemp);
                // debug(val);
                // XJSON.unwatch(dataroot, pth, id);
                // debug('removed ' + JSON.stringify(id in Object.keys(XJSON.getWatchers(dataroot, pth))));
                fire(el, data, el, watchinfo, dataroot, false);
              },
              id
            );
          }
        }
        if (attr.name == "e-checked") {
          if (val) el.setAttribute("checked", "checked");
          else el.removeAttribute("checked");
          if (val ^ el.checked) el.click();
          el.onchange = (e) => {
            console.log("." + e.target.checked);
            // debug(
            //   XJSON.set(
            //     dataroot,
            //     [
            //       ...XJSON.parsePath(
            //         watchinfo.attrMap[XJSON.parsePath(match)[0]]
            //       ),
            //       ...XJSON.parsePath(match).slice(1),
            //     ],
            //     e.target.checked
            //   )
            // );
          };
          continue;
        }
        attr.value = attr.value.replace(
          new RegExp("{{\\s*" + escapeRegex(key) + "\\s*}}", "g"),
          val
        );
      }
    }

    if (el.attributes["@click"]) {
      let key = el.attributes["@click"].value.trim();
      let pth = watchinfo.attrMap[XJSON.parsePath(key)[0]];
      let matches = findMatches(key);
      // debug("indef", watchinfo.attrMap[matches[0]], watchinfo.attrMap);
      let val = XJSON.get(dataroot, [
        ...XJSON.parsePath(watchinfo.attrMap[matches[0]]),
        ...XJSON.parsePath(key).slice(1),
      ]);
      el.onclick = () => val(dataroot);
    }

    let chs = [...el.children];
    for (let child of chs) {
      fire(child, data, child, watchinfo, dataroot, attach);
    }
  } catch (e) {
    console.error(e);
  }
}
function escapeRegex(string) {
  return string.replace(/[-\/\\^$*+?.()|[\]{}]/g, "\\$&");
}

function reseAttrs(el, _elTemp) {
  let textNodes = findImmediateTextNodes(el);
  let textNodesT = findImmediateTextNodes(_elTemp);
  for (let i = 0; i < textNodesT.length; i++) {
    let textNode = textNodes[i];
    let textNodeT = textNodesT[i];
    textNode.textContent = textNodeT.textContent;
  }
}
function findMatchesSqBrackets(string) {
  let matches = [];
  let match;
  let regex = /\[([^\]]*)\]/g;
  while ((match = regex.exec(string)) != null) {
    matches.push(match[1]);
  }
  return matches;
}

window.AutoDOM = AutoDOM;
