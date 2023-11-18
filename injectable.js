window.capturedLogs = [];
window.printedLogs = [];

window.originalConsoleLog = console.log;
window._special_debug = function (line, col, arg) {
    capturedLogs.push([line, col, arg]);
    return arg;
};
window._special_console_log = function (line, col, ...args) {
    capturedLogs.push([line, col, args.length == 1 ? args[0] : args]);
    printedLogs.push([line, col, args.length == 1 ? args[0] : args]);
    // console.log(...args);
};
