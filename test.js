try {
    throw new Error('foo');
} catch (e) {
    console.log(e.message);
    console.log(e.stack);

    const errorStack = `
        ReferenceError: d is not defined\n
        at eval (eval at runCurrentFile (http://127.0.0.1:3000/hotcode/js.html:159:34), <anonymous>:8:2)\n
        at eval (<anonymous>)\n
        at runCurrentFile (http://127.0.0.1:3000/hotcode/js.html:614:34)\n
        at http://127.0.0.1:3000/hotcode/js.html:540:13"
    `;
    errorLogs = {};
    errorLogs.stack = errorStack;
    const [lineno, colno] = errorLogs.stack.match(/<anonymous>.*?(\d+:\d+)\)\n/)[1].split(':').map(Number);
    console.log('Line:', lineno);
    console.log('Column:', colno);
}
_special_loop_counter = 0; while (1) if (_special_loop_counter++ > 10) { throw new Error("Loop iteration limit exceeded"); break; } else {

}