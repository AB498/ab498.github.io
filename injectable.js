window.capturedLogs = [];
window.printedLogs = [];

window.originalConsoleLog = console.log;
window._special_debug = function (line, col, arg) {
    val = arg;
    if (typeof val == 'object')
        val = JSON.parse(JSON.stringify(val))
    capturedLogs.push([line, col, val]);
    return arg;
};
window._special_console_log = function (line, col, ...args) {
    val = args.length == 1 ? args[0] : args;
    if (typeof val == 'object')
        val = JSON.parse(JSON.stringify(val))
    capturedLogs.push([line, col, val]);
    printedLogs.push([line, col, val]);
    // console.log(...args);
};
