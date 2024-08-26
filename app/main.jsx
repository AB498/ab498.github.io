window.uuid = () => {
    return "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx".replace(/[xy]/g, function (c) {
        var r = (Math.random() * 16) | 0,
            v = c == "x" ? r : (r & 0x3) | 0x8;
        return v.toString(16);
    });
}

let transform = window.sucrase ? (code) => window.sucrase.transform(code, { transforms: ['jsx'] }).code : (code) => window.Babel.transform(code, { presets: ['react'] }).code;

async function addFile(src) {
    if (src.slice(-3) == ".js") {
        return eval(await (await fetch(src + '?t=' + new Date().getTime() + '&nocache=' + new Date().getTime() + Math.random())).text())
    }
    if (src.slice(-3) == ".css") {
        document.write(`<link rel="stylesheet" href="${src}">`)
    }

    if (src.slice(-4) == ".jsx") {
        return eval(transform(await (await fetch(src + '?t=' + new Date().getTime() + '&nocache=' + new Date().getTime() + Math.random())).text()))
    }

    return null



}



let loadstart = new Date();
document.body.style.margin = "0";
document.querySelector("#loader").style.width = 0;
document.querySelector("#lastloader").style.width = window.localStorage["lastLoaderProgress"] || "0px";

let loaderInterval = setInterval(() => {
    let inc = (window.innerWidth - parseFloat(document.querySelector("#loader").style.width)) / 100;
    document.querySelector("#loader").style.width =
        parseFloat(document.querySelector("#loader").style.width) + inc + "px";
    // document.querySelector("#loader").textContent = inc;
}, 10);

function loaded() {
    clearInterval(loaderInterval);
    window.localStorage["lastLoaderProgress"] = parseFloat(document.querySelector("#loader").style.width);
    console.log("loaded in", parseInt(new Date() - loadstart), "ms");
}

async function loadOnce() {

    await addFile("assets/js/tailwind.js");
    await addFile("assets/js/utils.js");

    await addFile("assets/js/react.development.js");
    await addFile("assets/js/react-dom.development.js");
    await addFile("assets/js/react-router-dom.min.js");


    await addFile("assets/js/pocketbase.umd.min.js");
    console.log(window.PocketBase)

}

(async () => {

    await loadOnce();


    const { useState, useMemo, useEffect, createContext, useContext, useRef } = window.React; // eslint-disable-line no-unused-vars
    const { HashRouter, Route, Switch, useHistory, useLocation } = window.ReactRouterDOM; // eslint-disable-line no-unused-vars



    function useAsync(asyncFn) { // eslint-disable-line no-unused-vars
        let [data, setData] = useState(null);
        let [error, setError] = useState(null);
        useEffect(() => {
            asyncFn().then(setData).catch(setError);
        }, []);
        (error && console.log('useAsync Error', error?.data ? error.data : error));
        return [data, setData, error?.data ? error.data : error];
    }
    function useForceUpdate() {
        let [, set] = useState(0);
        return () => set((i) => i + 1);
    }
    window.lastCodes = window.lastCodes || {};
    let DynamicComponent = (props) => {
        let { path } = props || {};
        let Comp = useRef(window.lastCodes[path]);

        let forceUpdate = useForceUpdate();
        useEffect(() => {
            // console.log(path, 'mounted')

            let mounted = true;
            let componentPoll = async () => {
                if (!mounted) return;
                Comp.current = await addFile("components" + path + ".jsx");
                if (Comp.current.toString() != window.lastCodes[path]?.toString()) {
                    console.log(path, 'changed', Comp.current.toString()?.length, window.lastCodes[path]?.length)

                    forceUpdate();
                }
                window.lastCodes[path] = Comp.current;
                await new Promise((resolve) => setTimeout(resolve, 2000));
                componentPoll();
            }
            componentPoll();
            return () => {
                mounted = false;



            }
        }, []);


        return Comp.current ? <Comp.current {...props} /> : '[NULL/LOADING]';


    }

    let React = window.React;
    window.ReactDOM.createRoot(document.querySelector("#root") || document.body.appendChild(Object.assign(document.createElement("div"), { id: "root" }))).render(
        <DynamicComponent path="/auth"
            homePage={<DynamicComponent path="/home"
                studentPage={<DynamicComponent path="/student"
                    dashboardPage={<DynamicComponent path="/student/dashboard" />}
                    academicPage={<DynamicComponent path="/student/academic" />}
                    resultPage={<DynamicComponent path="/student/result" />}
                    financePage={<DynamicComponent path="/student/finance" />}
                />}
                teacherPage={<DynamicComponent path="/teacher" />} />}
        />
    );

    window.lastCode = await (await fetch("main.jsx")).text();;
    let intv = setInterval(async () => {
        let mainJSX = await (await fetch("main.jsx")).text();
        if (window.lastCode != null && window.lastCode != mainJSX) {
            console.log('main.jsx loaded');
            clearInterval(intv);
            eval(transform(mainJSX));
        }
        window.lastCode = mainJSX;
    }, 2000);




    loaded();

})();
