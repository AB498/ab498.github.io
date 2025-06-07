(function (global, factory) {
    typeof exports === 'object' && typeof module !== 'undefined' ? factory(exports, require('react')) :
    typeof define === 'function' && define.amd ? define(['exports', 'react'], factory) :
    (global = typeof globalThis !== 'undefined' ? globalThis : global || self, factory(global.Valtio = {}, global.React));
})(this, (function (exports, react) { 'use strict';

    /* eslint @typescript-eslint/no-explicit-any: off */
    // symbols
    const TRACK_MEMO_SYMBOL = Symbol();
    const GET_ORIGINAL_SYMBOL = Symbol();
    // properties
    const AFFECTED_PROPERTY = 'a';
    const IS_TARGET_COPIED_PROPERTY = 'f';
    const PROXY_PROPERTY = 'p';
    const PROXY_CACHE_PROPERTY = 'c';
    const TARGET_CACHE_PROPERTY = 't';
    const HAS_KEY_PROPERTY = 'h';
    const ALL_OWN_KEYS_PROPERTY = 'w';
    const HAS_OWN_KEY_PROPERTY = 'o';
    const KEYS_PROPERTY = 'k';
    // function to create a new bare proxy
    let newProxy$1 = (target, handler) => new Proxy(target, handler);
    // get object prototype
    const getProto = Object.getPrototypeOf;
    const objectsToTrack = new WeakMap();
    // check if obj is a plain object or an array
    const isObjectToTrack = (obj) => obj &&
        (objectsToTrack.has(obj)
            ? objectsToTrack.get(obj)
            : getProto(obj) === Object.prototype || getProto(obj) === Array.prototype);
    // check if it is object
    const isObject$2 = (x) => typeof x === 'object' && x !== null;
    // Properties that are both non-configurable and non-writable will break
    // the proxy get trap when we try to return a recursive/child compare proxy
    // from them. We can avoid this by making a copy of the target object with
    // all descriptors marked as configurable, see `copyTargetObject`.
    // See: https://github.com/dai-shi/proxy-compare/pull/8
    const needsToCopyTargetObject = (obj) => Object.values(Object.getOwnPropertyDescriptors(obj)).some((descriptor) => !descriptor.configurable && !descriptor.writable);
    // Make a copy with all descriptors marked as configurable.
    const copyTargetObject = (obj) => {
        if (Array.isArray(obj)) {
            // Arrays need a special way to copy
            return Array.from(obj);
        }
        // For non-array objects, we create a new object keeping the prototype
        // with changing all configurable options (otherwise, proxies will complain)
        const descriptors = Object.getOwnPropertyDescriptors(obj);
        Object.values(descriptors).forEach((desc) => {
            desc.configurable = true;
        });
        return Object.create(getProto(obj), descriptors);
    };
    const createProxyHandler = (origObj, isTargetCopied) => {
        const state = {
            [IS_TARGET_COPIED_PROPERTY]: isTargetCopied,
        };
        let trackObject = false; // for trackMemo
        const recordUsage = (type, key) => {
            if (!trackObject) {
                let used = state[AFFECTED_PROPERTY].get(origObj);
                if (!used) {
                    used = {};
                    state[AFFECTED_PROPERTY].set(origObj, used);
                }
                if (type === ALL_OWN_KEYS_PROPERTY) {
                    used[ALL_OWN_KEYS_PROPERTY] = true;
                }
                else {
                    let set = used[type];
                    if (!set) {
                        set = new Set();
                        used[type] = set;
                    }
                    set.add(key);
                }
            }
        };
        const recordObjectAsUsed = () => {
            trackObject = true;
            state[AFFECTED_PROPERTY].delete(origObj);
        };
        const handler = {
            get(target, key) {
                if (key === GET_ORIGINAL_SYMBOL) {
                    return origObj;
                }
                recordUsage(KEYS_PROPERTY, key);
                return createProxy(Reflect.get(target, key), state[AFFECTED_PROPERTY], state[PROXY_CACHE_PROPERTY], state[TARGET_CACHE_PROPERTY]);
            },
            has(target, key) {
                if (key === TRACK_MEMO_SYMBOL) {
                    recordObjectAsUsed();
                    return true;
                }
                recordUsage(HAS_KEY_PROPERTY, key);
                return Reflect.has(target, key);
            },
            getOwnPropertyDescriptor(target, key) {
                recordUsage(HAS_OWN_KEY_PROPERTY, key);
                return Reflect.getOwnPropertyDescriptor(target, key);
            },
            ownKeys(target) {
                recordUsage(ALL_OWN_KEYS_PROPERTY);
                return Reflect.ownKeys(target);
            },
        };
        if (isTargetCopied) {
            handler.set = handler.deleteProperty = () => false;
        }
        return [handler, state];
    };
    const getOriginalObject = (obj) => 
    // unwrap proxy
    obj[GET_ORIGINAL_SYMBOL] ||
        // otherwise
        obj;
    /**
     * Create a proxy.
     *
     * This function will create a proxy at top level and proxy nested objects as you access them,
     * in order to keep track of which properties were accessed via get/has proxy handlers:
     *
     * NOTE: Printing of WeakMap is hard to inspect and not very readable
     * for this purpose you can use the `affectedToPathList` helper.
     *
     * @param {object} obj - Object that will be wrapped on the proxy.
     * @param {WeakMap<object, unknown>} affected -
     * WeakMap that will hold the tracking of which properties in the proxied object were accessed.
     * @param {WeakMap<object, unknown>} [proxyCache] -
     * WeakMap that will help keep referential identity for proxies.
     * @returns {Proxy<object>} - Object wrapped in a proxy.
     *
     * @example
     * import { createProxy } from 'proxy-compare';
     *
     * const original = { a: "1", c: "2", d: { e: "3" } };
     * const affected = new WeakMap();
     * const proxy = createProxy(original, affected);
     *
     * proxy.a // Will mark as used and track its value.
     * // This will update the affected WeakMap with original as key
     * // and a Set with "a"
     *
     * proxy.d // Will mark "d" as accessed to track and proxy itself ({ e: "3" }).
     * // This will update the affected WeakMap with original as key
     * // and a Set with "d"
     */
    const createProxy = (obj, affected, proxyCache, targetCache) => {
        if (!isObjectToTrack(obj))
            return obj;
        let targetAndCopied = targetCache && targetCache.get(obj);
        if (!targetAndCopied) {
            const target = getOriginalObject(obj);
            if (needsToCopyTargetObject(target)) {
                targetAndCopied = [target, copyTargetObject(target)];
            }
            else {
                targetAndCopied = [target];
            }
            targetCache === null || targetCache === void 0 ? void 0 : targetCache.set(obj, targetAndCopied);
        }
        const [target, copiedTarget] = targetAndCopied;
        let handlerAndState = proxyCache && proxyCache.get(target);
        if (!handlerAndState ||
            handlerAndState[1][IS_TARGET_COPIED_PROPERTY] !== !!copiedTarget) {
            handlerAndState = createProxyHandler(target, !!copiedTarget);
            handlerAndState[1][PROXY_PROPERTY] = newProxy$1(copiedTarget || target, handlerAndState[0]);
            if (proxyCache) {
                proxyCache.set(target, handlerAndState);
            }
        }
        handlerAndState[1][AFFECTED_PROPERTY] = affected;
        handlerAndState[1][PROXY_CACHE_PROPERTY] = proxyCache;
        handlerAndState[1][TARGET_CACHE_PROPERTY] = targetCache;
        return handlerAndState[1][PROXY_PROPERTY];
    };
    const isAllOwnKeysChanged = (prevObj, nextObj) => {
        const prevKeys = Reflect.ownKeys(prevObj);
        const nextKeys = Reflect.ownKeys(nextObj);
        return (prevKeys.length !== nextKeys.length ||
            prevKeys.some((k, i) => k !== nextKeys[i]));
    };
    /**
     * Compare changes on objects.
     *
     * This will compare the affected properties on tracked objects inside the proxy
     * to check if there were any changes made to it,
     * by default if no property was accessed on the proxy it will attempt to do a
     * reference equality check for the objects provided (Object.is(a, b)). If you access a property
     * on the proxy, then isChanged will only compare the affected properties.
     *
     * @param {object} prevObj - The previous object to compare.
     * @param {object} nextObj - Object to compare with the previous one.
     * @param {WeakMap<object, unknown>} affected -
     * WeakMap that holds the tracking of which properties in the proxied object were accessed.
     * @param {WeakMap<object, unknown>} [cache] -
     * WeakMap that holds a cache of the comparisons for better performance with repetitive comparisons,
     * and to avoid infinite loop with circular structures.
     * @returns {boolean} - Boolean indicating if the affected property on the object has changed.
     *
     * @example
     * import { createProxy, isChanged } from 'proxy-compare';
     *
     * const obj = { a: "1", c: "2", d: { e: "3" } };
     * const affected = new WeakMap();
     *
     * const proxy = createProxy(obj, affected);
     *
     * proxy.a
     *
     * isChanged(obj, { a: "1" }, affected) // false
     *
     * proxy.a = "2"
     *
     * isChanged(obj, { a: "1" }, affected) // true
     */
    const isChanged = (prevObj, nextObj, affected, cache, // for object with cycles
    isEqual = Object.is) => {
        if (isEqual(prevObj, nextObj)) {
            return false;
        }
        if (!isObject$2(prevObj) || !isObject$2(nextObj))
            return true;
        const used = affected.get(getOriginalObject(prevObj));
        if (!used)
            return true;
        if (cache) {
            const hit = cache.get(prevObj);
            if (hit === nextObj) {
                return false;
            }
            // for object with cycles
            cache.set(prevObj, nextObj);
        }
        let changed = null;
        for (const key of used[HAS_KEY_PROPERTY] || []) {
            changed = Reflect.has(prevObj, key) !== Reflect.has(nextObj, key);
            if (changed)
                return changed;
        }
        if (used[ALL_OWN_KEYS_PROPERTY] === true) {
            changed = isAllOwnKeysChanged(prevObj, nextObj);
            if (changed)
                return changed;
        }
        else {
            for (const key of used[HAS_OWN_KEY_PROPERTY] || []) {
                const hasPrev = !!Reflect.getOwnPropertyDescriptor(prevObj, key);
                const hasNext = !!Reflect.getOwnPropertyDescriptor(nextObj, key);
                changed = hasPrev !== hasNext;
                if (changed)
                    return changed;
            }
        }
        for (const key of used[KEYS_PROPERTY] || []) {
            changed = isChanged(prevObj[key], nextObj[key], affected, cache, isEqual);
            if (changed)
                return changed;
        }
        if (changed === null)
            throw new Error('invalid used');
        return changed;
    };
    /**
     * Unwrap proxy to get the original object.
     *
     * Used to retrieve the original object used to create the proxy instance with `createProxy`.
     *
     * @param {Proxy<object>} obj -  The proxy wrapper of the originial object.
     * @returns {object | null} - Return either the unwrapped object if exists.
     *
     * @example
     * import { createProxy, getUntracked } from 'proxy-compare';
     *
     * const original = { a: "1", c: "2", d: { e: "3" } };
     * const affected = new WeakMap();
     *
     * const proxy = createProxy(original, affected);
     * const originalFromProxy = getUntracked(proxy)
     *
     * Object.is(original, originalFromProxy) // true
     * isChanged(original, originalFromProxy, affected) // false
     */
    const getUntracked = (obj) => {
        if (isObjectToTrack(obj)) {
            return obj[GET_ORIGINAL_SYMBOL] || null;
        }
        return null;
    };
    /**
     * Mark object to be tracked.
     *
     * This function marks an object that will be passed into `createProxy`
     * as marked to track or not. By default only Array and Object are marked to track,
     * so this is useful for example to mark a class instance to track or to mark a object
     * to be untracked when creating your proxy.
     *
     * @param obj - Object to mark as tracked or not.
     * @param mark - Boolean indicating whether you want to track this object or not.
     * @returns - No return.
     *
     * @example
     * import { createProxy, markToTrack, isChanged } from 'proxy-compare';
     *
     * const nested = { e: "3" }
     *
     * markToTrack(nested, false)
     *
     * const original = { a: "1", c: "2", d: nested };
     * const affected = new WeakMap();
     *
     * const proxy = createProxy(original, affected);
     *
     * proxy.d.e
     *
     * isChanged(original, { d: { e: "3" } }, affected) // true
     */
    const markToTrack = (obj, mark = true) => {
        objectsToTrack.set(obj, mark);
    };
    /**
     * Convert `affected` to path list
     *
     * `affected` is a weak map which is not printable.
     * This function is can convert it to printable path list.
     * It's for debugging purpose.
     *
     * @param obj - An object that is used with `createProxy`.
     * @param affected - A weak map that is used with `createProxy`.
     * @param onlyWithValues - An optional boolean to exclude object getters.
     * @returns - An array of paths.
     */
    const affectedToPathList = (obj, affected, onlyWithValues) => {
        const list = [];
        const seen = new WeakSet();
        const walk = (x, path) => {
            var _a, _b, _c;
            if (seen.has(x)) {
                // for object with cycles
                return;
            }
            if (isObject$2(x)) {
                seen.add(x);
            }
            const used = isObject$2(x) && affected.get(getOriginalObject(x));
            if (used) {
                (_a = used[HAS_KEY_PROPERTY]) === null || _a === void 0 ? void 0 : _a.forEach((key) => {
                    const segment = `:has(${String(key)})`;
                    list.push(path ? [...path, segment] : [segment]);
                });
                if (used[ALL_OWN_KEYS_PROPERTY] === true) {
                    const segment = ':ownKeys';
                    list.push(path ? [...path, segment] : [segment]);
                }
                else {
                    (_b = used[HAS_OWN_KEY_PROPERTY]) === null || _b === void 0 ? void 0 : _b.forEach((key) => {
                        const segment = `:hasOwn(${String(key)})`;
                        list.push(path ? [...path, segment] : [segment]);
                    });
                }
                (_c = used[KEYS_PROPERTY]) === null || _c === void 0 ? void 0 : _c.forEach((key) => {
                    if ('value' in (Object.getOwnPropertyDescriptor(x, key) || {})) {
                        walk(x[key], path ? [...path, key] : [key]);
                    }
                });
            }
            else if (path) {
                list.push(path);
            }
        };
        walk(obj);
        return list;
    };

    const isObject$1 = (x) => typeof x === "object" && x !== null;
    const canProxyDefault = (x) => isObject$1(x) && !refSet.has(x) && (Array.isArray(x) || !(Symbol.iterator in x)) && !(x instanceof WeakMap) && !(x instanceof WeakSet) && !(x instanceof Error) && !(x instanceof Number) && !(x instanceof Date) && !(x instanceof String) && !(x instanceof RegExp) && !(x instanceof ArrayBuffer) && !(x instanceof Promise);
    const createSnapshotDefault = (target, version) => {
      const cache = snapCache$2.get(target);
      if ((cache == null ? void 0 : cache[0]) === version) {
        return cache[1];
      }
      const snap = Array.isArray(target) ? [] : Object.create(Object.getPrototypeOf(target));
      markToTrack(snap, true);
      snapCache$2.set(target, [version, snap]);
      Reflect.ownKeys(target).forEach((key) => {
        if (Object.getOwnPropertyDescriptor(snap, key)) {
          return;
        }
        const value = Reflect.get(target, key);
        const { enumerable } = Reflect.getOwnPropertyDescriptor(
          target,
          key
        );
        const desc = {
          value,
          enumerable,
          // This is intentional to avoid copying with proxy-compare.
          // It's still non-writable, so it avoids assigning a value.
          configurable: true
        };
        if (refSet.has(value)) {
          markToTrack(value, false);
        } else if (proxyStateMap$2.has(value)) {
          const [target2, ensureVersion] = proxyStateMap$2.get(
            value
          );
          desc.value = createSnapshotDefault(target2, ensureVersion());
        }
        Object.defineProperty(snap, key, desc);
      });
      return Object.preventExtensions(snap);
    };
    const createHandlerDefault = (isInitializing, addPropListener, removePropListener, notifyUpdate) => ({
      deleteProperty(target, prop) {
        const prevValue = Reflect.get(target, prop);
        removePropListener(prop);
        const deleted = Reflect.deleteProperty(target, prop);
        if (deleted) {
          notifyUpdate(["delete", [prop], prevValue]);
        }
        return deleted;
      },
      set(target, prop, value, receiver) {
        const hasPrevValue = !isInitializing() && Reflect.has(target, prop);
        const prevValue = Reflect.get(target, prop, receiver);
        if (hasPrevValue && (objectIs(prevValue, value) || proxyCache.has(value) && objectIs(prevValue, proxyCache.get(value)))) {
          return true;
        }
        removePropListener(prop);
        if (isObject$1(value)) {
          value = getUntracked(value) || value;
        }
        const nextValue = !proxyStateMap$2.has(value) && canProxy(value) ? proxy(value) : value;
        addPropListener(prop, nextValue);
        Reflect.set(target, prop, nextValue, receiver);
        notifyUpdate(["set", [prop], value, prevValue]);
        return true;
      }
    });
    const proxyStateMap$2 = /* @__PURE__ */ new WeakMap();
    const refSet = /* @__PURE__ */ new WeakSet();
    const snapCache$2 = /* @__PURE__ */ new WeakMap();
    const versionHolder = [1, 1];
    const proxyCache = /* @__PURE__ */ new WeakMap();
    let objectIs = Object.is;
    let newProxy = (target, handler) => new Proxy(target, handler);
    let canProxy = canProxyDefault;
    let createSnapshot = createSnapshotDefault;
    let createHandler = createHandlerDefault;
    function proxy(baseObject = {}) {
      if (!isObject$1(baseObject)) {
        throw new Error("object required");
      }
      const found = proxyCache.get(baseObject);
      if (found) {
        return found;
      }
      let version = versionHolder[0];
      const listeners = /* @__PURE__ */ new Set();
      const notifyUpdate = (op, nextVersion = ++versionHolder[0]) => {
        if (version !== nextVersion) {
          version = nextVersion;
          listeners.forEach((listener) => listener(op, nextVersion));
        }
      };
      let checkVersion = versionHolder[1];
      const ensureVersion = (nextCheckVersion = ++versionHolder[1]) => {
        if (checkVersion !== nextCheckVersion && !listeners.size) {
          checkVersion = nextCheckVersion;
          propProxyStates.forEach(([propProxyState]) => {
            const propVersion = propProxyState[1](nextCheckVersion);
            if (propVersion > version) {
              version = propVersion;
            }
          });
        }
        return version;
      };
      const createPropListener = (prop) => (op, nextVersion) => {
        const newOp = [...op];
        newOp[1] = [prop, ...newOp[1]];
        notifyUpdate(newOp, nextVersion);
      };
      const propProxyStates = /* @__PURE__ */ new Map();
      const addPropListener = (prop, propValue) => {
        const propProxyState = !refSet.has(propValue) && proxyStateMap$2.get(propValue);
        if (propProxyState) {
          if (typeof process !== "undefined" && process.env ? process.env.NODE_ENV : propProxyStates.has(prop)) {
            throw new Error("prop listener already exists");
          }
          if (listeners.size) {
            const remove = propProxyState[2](createPropListener(prop));
            propProxyStates.set(prop, [propProxyState, remove]);
          } else {
            propProxyStates.set(prop, [propProxyState]);
          }
        }
      };
      const removePropListener = (prop) => {
        var _a;
        const entry = propProxyStates.get(prop);
        if (entry) {
          propProxyStates.delete(prop);
          (_a = entry[1]) == null ? void 0 : _a.call(entry);
        }
      };
      const addListener = (listener) => {
        listeners.add(listener);
        if (listeners.size === 1) {
          propProxyStates.forEach(([propProxyState, prevRemove], prop) => {
            if (typeof process !== "undefined" && process.env ? process.env.NODE_ENV : prevRemove) {
              throw new Error("remove already exists");
            }
            const remove = propProxyState[2](createPropListener(prop));
            propProxyStates.set(prop, [propProxyState, remove]);
          });
        }
        const removeListener = () => {
          listeners.delete(listener);
          if (listeners.size === 0) {
            propProxyStates.forEach(([propProxyState, remove], prop) => {
              if (remove) {
                remove();
                propProxyStates.set(prop, [propProxyState]);
              }
            });
          }
        };
        return removeListener;
      };
      let initializing = true;
      const handler = createHandler(
        () => initializing,
        addPropListener,
        removePropListener,
        notifyUpdate
      );
      const proxyObject = newProxy(baseObject, handler);
      proxyCache.set(baseObject, proxyObject);
      const proxyState = [baseObject, ensureVersion, addListener];
      proxyStateMap$2.set(proxyObject, proxyState);
      Reflect.ownKeys(baseObject).forEach((key) => {
        const desc = Object.getOwnPropertyDescriptor(
          baseObject,
          key
        );
        if ("value" in desc && desc.writable) {
          proxyObject[key] = baseObject[key];
        }
      });
      initializing = false;
      return proxyObject;
    }
    function getVersion(proxyObject) {
      const proxyState = proxyStateMap$2.get(proxyObject);
      return proxyState == null ? void 0 : proxyState[1]();
    }
    function subscribe(proxyObject, callback, notifyInSync) {
      const proxyState = proxyStateMap$2.get(proxyObject);
      if (typeof process !== "undefined" && process.env ? process.env.NODE_ENV : !proxyState) {
        console.warn("Please use proxy object");
      }
      let promise;
      const ops = [];
      const addListener = proxyState[2];
      let isListenerActive = false;
      const listener = (op) => {
        ops.push(op);
        if (notifyInSync) {
          callback(ops.splice(0));
          return;
        }
        if (!promise) {
          promise = Promise.resolve().then(() => {
            promise = void 0;
            if (isListenerActive) {
              callback(ops.splice(0));
            }
          });
        }
      };
      const removeListener = addListener(listener);
      isListenerActive = true;
      return () => {
        isListenerActive = false;
        removeListener();
      };
    }
    function snapshot(proxyObject) {
      const proxyState = proxyStateMap$2.get(proxyObject);
      if (typeof process !== "undefined" && process.env ? process.env.NODE_ENV : !proxyState) {
        console.warn("Please use proxy object");
      }
      const [target, ensureVersion] = proxyState;
      return createSnapshot(target, ensureVersion());
    }
    function ref(obj) {
      refSet.add(obj);
      return obj;
    }
    function unstable_getInternalStates() {
      return {
        proxyStateMap: proxyStateMap$2,
        refSet,
        snapCache: snapCache$2,
        versionHolder,
        proxyCache
      };
    }
    function unstable_replaceInternalFunction(name, fn) {
      switch (name) {
        case "objectIs":
          objectIs = fn(objectIs);
          break;
        case "newProxy":
          newProxy = fn(newProxy);
          break;
        case "canProxy":
          canProxy = fn(canProxy);
          break;
        case "createSnapshot":
          createSnapshot = fn(createSnapshot);
          break;
        case "createHandler":
          createHandler = fn(createHandler);
          break;
        default:
          throw new Error("unknown function");
      }
    }

    const useAffectedDebugValue = (state, affected) => {
      const pathList = react.useRef(void 0);
      react.useEffect(() => {
        pathList.current = affectedToPathList(state, affected);
      });
      react.useDebugValue(pathList.current);
    };
    const condUseAffectedDebugValue = useAffectedDebugValue;
    const targetCache = /* @__PURE__ */ new WeakMap();
    function useSnapshot(proxyObject, options) {
      const notifyInSync = options == null ? void 0 : options.sync;
      const affected = react.useMemo(
        () => proxyObject && /* @__PURE__ */ new WeakMap(),
        [proxyObject]
      );
      const lastSnapshot = react.useRef(void 0);
      let inRender = true;
      const currSnapshot = react.useSyncExternalStore(
        react.useCallback(
          (callback) => {
            const unsub = subscribe(proxyObject, callback, notifyInSync);
            callback();
            return unsub;
          },
          [proxyObject, notifyInSync]
        ),
        () => {
          const nextSnapshot = snapshot(proxyObject);
          try {
            if (!inRender && lastSnapshot.current && !isChanged(
              lastSnapshot.current,
              nextSnapshot,
              affected,
              /* @__PURE__ */ new WeakMap()
            )) {
              return lastSnapshot.current;
            }
          } catch (e) {
          }
          return nextSnapshot;
        },
        () => snapshot(proxyObject)
      );
      inRender = false;
      react.useLayoutEffect(() => {
        lastSnapshot.current = currSnapshot;
      });
      if (typeof process !== "undefined" && process.env ? process.env.NODE_ENV : true) {
        condUseAffectedDebugValue(currSnapshot, affected);
      }
      const proxyCache = react.useMemo(() => /* @__PURE__ */ new WeakMap(), []);
      return createProxy(currSnapshot, affected, proxyCache, targetCache);
    }

    function subscribeKey(proxyObject, key, callback, notifyInSync) {
      let prevValue = proxyObject[key];
      return subscribe(
        proxyObject,
        () => {
          const nextValue = proxyObject[key];
          if (!Object.is(prevValue, nextValue)) {
            callback(prevValue = nextValue);
          }
        },
        notifyInSync
      );
    }

    let currentCleanups;
    function watch(callback, options) {
      let alive = true;
      const cleanups = /* @__PURE__ */ new Set();
      const subscriptions = /* @__PURE__ */ new Map();
      const cleanup = () => {
        if (alive) {
          alive = false;
          cleanups.forEach((clean) => clean());
          cleanups.clear();
          subscriptions.forEach((unsubscribe) => unsubscribe());
          subscriptions.clear();
        }
      };
      const revalidate = async () => {
        if (!alive) {
          return;
        }
        cleanups.forEach((clean) => clean());
        cleanups.clear();
        const proxiesToSubscribe = /* @__PURE__ */ new Set();
        const parent = currentCleanups;
        currentCleanups = cleanups;
        try {
          const promiseOrPossibleCleanup = callback((proxyObject) => {
            proxiesToSubscribe.add(proxyObject);
            if (alive && !subscriptions.has(proxyObject)) {
              const unsubscribe = subscribe(proxyObject, revalidate, options == null ? void 0 : options.sync);
              subscriptions.set(proxyObject, unsubscribe);
            }
            return proxyObject;
          });
          const couldBeCleanup = promiseOrPossibleCleanup && promiseOrPossibleCleanup instanceof Promise ? await promiseOrPossibleCleanup : promiseOrPossibleCleanup;
          if (couldBeCleanup) {
            if (alive) {
              cleanups.add(couldBeCleanup);
            } else {
              cleanup();
            }
          }
        } finally {
          currentCleanups = parent;
        }
        subscriptions.forEach((unsubscribe, proxyObject) => {
          if (!proxiesToSubscribe.has(proxyObject)) {
            subscriptions.delete(proxyObject);
            unsubscribe();
          }
        });
      };
      if (currentCleanups) {
        currentCleanups.add(cleanup);
      }
      revalidate();
      return cleanup;
    }

    const DEVTOOLS = Symbol();
    function devtools(proxyObject, options) {
      const { enabled, name = "", ...rest } = options || {};
      let extension;
      try {
        extension = (enabled != null ? enabled : typeof process !== "undefined" && process.env ? process.env.NODE_ENV : true) && window.__REDUX_DEVTOOLS_EXTENSION__;
      } catch (e) {
      }
      if (!extension) {
        if (typeof process !== "undefined" && process.env ? process.env.NODE_ENV : enabled) {
          console.warn("[Warning] Please install/enable Redux devtools extension");
        }
        return;
      }
      let isTimeTraveling = false;
      const devtools2 = extension.connect({ name, ...rest });
      const unsub1 = subscribe(proxyObject, (ops) => {
        const action = ops.filter(([_, path]) => path[0] !== DEVTOOLS).map(([op, path]) => `${op}:${path.map(String).join(".")}`).join(", ");
        if (!action) {
          return;
        }
        if (isTimeTraveling) {
          isTimeTraveling = false;
        } else {
          const snapWithoutDevtools = Object.assign({}, snapshot(proxyObject));
          delete snapWithoutDevtools[DEVTOOLS];
          devtools2.send(
            {
              type: action,
              updatedAt: (/* @__PURE__ */ new Date()).toLocaleString()
            },
            snapWithoutDevtools
          );
        }
      });
      const unsub2 = devtools2.subscribe((message) => {
        var _a, _b, _c, _d, _e, _f;
        if (message.type === "ACTION" && message.payload) {
          try {
            Object.assign(proxyObject, JSON.parse(message.payload));
          } catch (e) {
            console.error(
              "please dispatch a serializable value that JSON.parse() and proxy() support\n",
              e
            );
          }
        }
        if (message.type === "DISPATCH" && message.state) {
          if (((_a = message.payload) == null ? void 0 : _a.type) === "JUMP_TO_ACTION" || ((_b = message.payload) == null ? void 0 : _b.type) === "JUMP_TO_STATE") {
            isTimeTraveling = true;
            const state = JSON.parse(message.state);
            Object.assign(proxyObject, state);
          }
          proxyObject[DEVTOOLS] = message;
        } else if (message.type === "DISPATCH" && ((_c = message.payload) == null ? void 0 : _c.type) === "COMMIT") {
          devtools2.init(snapshot(proxyObject));
        } else if (message.type === "DISPATCH" && ((_d = message.payload) == null ? void 0 : _d.type) === "IMPORT_STATE") {
          const actions = (_e = message.payload.nextLiftedState) == null ? void 0 : _e.actionsById;
          const computedStates = ((_f = message.payload.nextLiftedState) == null ? void 0 : _f.computedStates) || [];
          isTimeTraveling = true;
          computedStates.forEach(({ state }, index) => {
            const action = actions[index] || "No action found";
            Object.assign(proxyObject, state);
            if (index === 0) {
              devtools2.init(snapshot(proxyObject));
            } else {
              devtools2.send(action, snapshot(proxyObject));
            }
          });
        }
      });
      devtools2.init(snapshot(proxyObject));
      return () => {
        unsub1();
        unsub2 == null ? void 0 : unsub2();
      };
    }

    const { proxyStateMap: proxyStateMap$1, snapCache: snapCache$1 } = unstable_getInternalStates();
    const isProxy$1 = (x) => proxyStateMap$1.has(x);
    const isProxyMap = (obj) => {
      return Symbol.toStringTag in obj && obj[Symbol.toStringTag] === "Map" && proxyStateMap$1.has(obj);
    };
    function proxyMap(entries) {
      const initialData = [];
      let initialIndex = 0;
      const indexMap = /* @__PURE__ */ new Map();
      const snapMapCache = /* @__PURE__ */ new WeakMap();
      const registerSnapMap = () => {
        const cache = snapCache$1.get(vObject);
        const latestSnap = cache == null ? void 0 : cache[1];
        if (latestSnap && !snapMapCache.has(latestSnap)) {
          const clonedMap = new Map(indexMap);
          snapMapCache.set(latestSnap, clonedMap);
        }
      };
      const getMapForThis = (x) => snapMapCache.get(x) || indexMap;
      if (entries) {
        if (typeof entries[Symbol.iterator] !== "function") {
          throw new TypeError(
            "proxyMap:\n	initial state must be iterable\n		tip: structure should be [[key, value]]"
          );
        }
        for (const [key, value] of entries) {
          indexMap.set(key, initialIndex);
          initialData[initialIndex++] = value;
        }
      }
      const vObject = {
        data: initialData,
        index: initialIndex,
        epoch: 0,
        get size() {
          if (!isProxy$1(this)) {
            registerSnapMap();
          }
          const map = getMapForThis(this);
          return map.size;
        },
        get(key) {
          const map = getMapForThis(this);
          const index = map.get(key);
          if (index === void 0) {
            this.epoch;
            return void 0;
          }
          return this.data[index];
        },
        has(key) {
          const map = getMapForThis(this);
          this.epoch;
          return map.has(key);
        },
        set(key, value) {
          if (!isProxy$1(this)) {
            throw new Error("Cannot perform mutations on a snapshot");
          }
          const index = indexMap.get(key);
          if (index === void 0) {
            indexMap.set(key, this.index);
            this.data[this.index++] = value;
          } else {
            this.data[index] = value;
          }
          this.epoch++;
          return this;
        },
        delete(key) {
          if (!isProxy$1(this)) {
            throw new Error("Cannot perform mutations on a snapshot");
          }
          const index = indexMap.get(key);
          if (index === void 0) {
            return false;
          }
          delete this.data[index];
          indexMap.delete(key);
          this.epoch++;
          return true;
        },
        clear() {
          if (!isProxy$1(this)) {
            throw new Error("Cannot perform mutations on a snapshot");
          }
          this.data.length = 0;
          this.index = 0;
          this.epoch++;
          indexMap.clear();
        },
        forEach(cb) {
          this.epoch;
          const map = getMapForThis(this);
          map.forEach((index, key) => {
            cb(this.data[index], key, this);
          });
        },
        *entries() {
          this.epoch;
          const map = getMapForThis(this);
          for (const [key, index] of map) {
            yield [key, this.data[index]];
          }
        },
        *keys() {
          this.epoch;
          const map = getMapForThis(this);
          for (const key of map.keys()) {
            yield key;
          }
        },
        *values() {
          this.epoch;
          const map = getMapForThis(this);
          for (const index of map.values()) {
            yield this.data[index];
          }
        },
        [Symbol.iterator]() {
          return this.entries();
        },
        get [Symbol.toStringTag]() {
          return "Map";
        },
        toJSON() {
          return new Map(this.entries());
        }
      };
      const proxiedObject = proxy(vObject);
      Object.defineProperties(proxiedObject, {
        size: { enumerable: false },
        index: { enumerable: false },
        epoch: { enumerable: false },
        data: { enumerable: false },
        toJSON: { enumerable: false }
      });
      Object.seal(proxiedObject);
      return proxiedObject;
    }

    const { proxyStateMap, snapCache } = unstable_getInternalStates();
    const maybeProxify = (x) => typeof x === "object" ? proxy({ x }).x : x;
    const isProxy = (x) => proxyStateMap.has(x);
    const isProxySet = (obj) => {
      return Symbol.toStringTag in obj && obj[Symbol.toStringTag] === "Set" && proxyStateMap.has(obj);
    };
    function proxySet(initialValues) {
      const initialData = [];
      const indexMap = /* @__PURE__ */ new Map();
      let initialIndex = 0;
      const snapMapCache = /* @__PURE__ */ new WeakMap();
      const registerSnapMap = () => {
        const cache = snapCache.get(vObject);
        const latestSnap = cache == null ? void 0 : cache[1];
        if (latestSnap && !snapMapCache.has(latestSnap)) {
          const clonedMap = new Map(indexMap);
          snapMapCache.set(latestSnap, clonedMap);
        }
      };
      const getMapForThis = (x) => snapMapCache.get(x) || indexMap;
      if (initialValues) {
        if (typeof initialValues[Symbol.iterator] !== "function") {
          throw new TypeError("not iterable");
        }
        for (const value of initialValues) {
          if (!indexMap.has(value)) {
            const v = maybeProxify(value);
            indexMap.set(v, initialIndex);
            initialData[initialIndex++] = v;
          }
        }
      }
      const vObject = {
        data: initialData,
        index: initialIndex,
        epoch: 0,
        get size() {
          if (!isProxy(this)) {
            registerSnapMap();
          }
          return indexMap.size;
        },
        has(value) {
          const map = getMapForThis(this);
          const v = maybeProxify(value);
          this.epoch;
          return map.has(v);
        },
        add(value) {
          if (!isProxy(this)) {
            throw new Error("Cannot perform mutations on a snapshot");
          }
          const v = maybeProxify(value);
          if (!indexMap.has(v)) {
            indexMap.set(v, this.index);
            this.data[this.index++] = v;
            this.epoch++;
          }
          return this;
        },
        delete(value) {
          if (!isProxy(this)) {
            throw new Error("Cannot perform mutations on a snapshot");
          }
          const v = maybeProxify(value);
          const index = indexMap.get(v);
          if (index === void 0) {
            return false;
          }
          delete this.data[index];
          indexMap.delete(v);
          this.epoch++;
          return true;
        },
        clear() {
          if (!isProxy(this)) {
            throw new Error("Cannot perform mutations on a snapshot");
          }
          this.data.length = 0;
          this.index = 0;
          this.epoch++;
          indexMap.clear();
        },
        forEach(cb) {
          this.epoch;
          const map = getMapForThis(this);
          map.forEach((index) => {
            cb(this.data[index], this.data[index], this);
          });
        },
        *values() {
          this.epoch;
          const map = getMapForThis(this);
          for (const index of map.values()) {
            yield this.data[index];
          }
        },
        keys() {
          this.epoch;
          return this.values();
        },
        *entries() {
          this.epoch;
          const map = getMapForThis(this);
          for (const index of map.values()) {
            const value = this.data[index];
            yield [value, value];
          }
        },
        toJSON() {
          return new Set(this.values());
        },
        [Symbol.iterator]() {
          return this.values();
        },
        get [Symbol.toStringTag]() {
          return "Set";
        },
        intersection(other) {
          this.epoch;
          const otherSet = proxySet(other);
          const resultSet = proxySet();
          for (const value of this.values()) {
            if (otherSet.has(value)) {
              resultSet.add(value);
            }
          }
          return proxySet(resultSet);
        },
        union(other) {
          this.epoch;
          const resultSet = proxySet();
          const otherSet = proxySet(other);
          for (const value of this.values()) {
            resultSet.add(value);
          }
          for (const value of otherSet) {
            resultSet.add(value);
          }
          return proxySet(resultSet);
        },
        difference(other) {
          this.epoch;
          const resultSet = proxySet();
          const otherSet = proxySet(other);
          for (const value of this.values()) {
            if (!otherSet.has(value)) {
              resultSet.add(value);
            }
          }
          return proxySet(resultSet);
        },
        symmetricDifference(other) {
          this.epoch;
          const resultSet = proxySet();
          const otherSet = proxySet(other);
          for (const value of this.values()) {
            if (!otherSet.has(value)) {
              resultSet.add(value);
            }
          }
          for (const value of otherSet.values()) {
            if (!this.has(value)) {
              resultSet.add(value);
            }
          }
          return proxySet(resultSet);
        },
        isSubsetOf(other) {
          this.epoch;
          const otherSet = proxySet(other);
          return this.size <= other.size && [...this.values()].every((value) => otherSet.has(value));
        },
        isSupersetOf(other) {
          this.epoch;
          const otherSet = proxySet(other);
          return this.size >= other.size && [...otherSet].every((value) => this.has(value));
        },
        isDisjointFrom(other) {
          this.epoch;
          const otherSet = proxySet(other);
          return [...this.values()].every((value) => !otherSet.has(value));
        }
      };
      const proxiedObject = proxy(vObject);
      Object.defineProperties(proxiedObject, {
        size: { enumerable: false },
        data: { enumerable: false },
        index: { enumerable: false },
        epoch: { enumerable: false },
        toJSON: { enumerable: false }
      });
      Object.seal(proxiedObject);
      return proxiedObject;
    }

    const isObject = (x) => typeof x === "object" && x !== null;
    let defaultRefSet;
    const getDefaultRefSet = () => {
      if (!defaultRefSet) {
        defaultRefSet = unstable_getInternalStates().refSet;
      }
      return defaultRefSet;
    };
    function deepClone(obj, getRefSet = getDefaultRefSet) {
      if (!isObject(obj) || getRefSet().has(obj)) {
        return obj;
      }
      if (isProxySet(obj)) {
        return proxySet([...obj]);
      }
      if (isProxyMap(obj)) {
        return proxyMap([
          ...obj.entries()
        ]);
      }
      const baseObject = Array.isArray(obj) ? [] : Object.create(Object.getPrototypeOf(obj));
      Reflect.ownKeys(obj).forEach((key) => {
        baseObject[key] = deepClone(obj[key], getRefSet);
      });
      return baseObject;
    }

    const DUMMY_SYMBOL = Symbol();
    function useProxy(proxy, options) {
      const snapshot = useSnapshot(proxy, options);
      snapshot[DUMMY_SYMBOL];
      let isRendering = true;
      react.useLayoutEffect(() => {
        isRendering = false;
      });
      return new Proxy(proxy, {
        get(target, prop) {
          return isRendering ? snapshot[prop] : target[prop];
        }
      });
    }

    exports.deepClone = deepClone;
    exports.devtools = devtools;
    exports.getVersion = getVersion;
    exports.proxy = proxy;
    exports.proxyMap = proxyMap;
    exports.proxySet = proxySet;
    exports.ref = ref;
    exports.snapshot = snapshot;
    exports.subscribe = subscribe;
    exports.subscribeKey = subscribeKey;
    exports.unstable_getInternalStates = unstable_getInternalStates;
    exports.unstable_replaceInternalFunction = unstable_replaceInternalFunction;
    exports.useProxy = useProxy;
    exports.useSnapshot = useSnapshot;
    exports.watch = watch;

}));
