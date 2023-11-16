var capturedLogs = [];
var printedLogs = [];

var originalConsoleLog = console.log;
_special_debug = function (line, col, arg) {
    capturedLogs.push([line, col, arg]);
    return arg;
};
_special_console_log = function (line, col, ...args) {
    capturedLogs.push([line, col, args.length == 1 ? args[0] : args]);
    printedLogs.push([line, col, args.join(' ')]);
    // console.log(...args);
};
