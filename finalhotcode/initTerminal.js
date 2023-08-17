window.initTerminal = async () => {
  window.processCommand = (command) => {
    if (command.trim() == "clear") {
      window.term.clear();
    } else if (command == "help") {
    } else if (command == "run") {
    } else if (command == "compile") {
    } else if (command == "exit") {
    } else {
      window.term.write("\nNot found: " + command);
    }
    window.term.write("\n\x1B[1;3;31m >> \x1B[0m");
    window.terminal_history.push(command);
  };
  window.current_command = "";
  window.terminal_history = [];

  window.term = new window.Terminal({ convertEol: true, fontSize: 12 });
  window.fitAddon = new FitAddon.FitAddon();
  window.term.loadAddon(window.fitAddon);
  window.term.onData((data) => {
    if (data.charCodeAt(0) == 13) {
      window.processCommand(window.current_command);
      window.current_command = "";
      return;
    } else if (data.charCodeAt(0) == 127) {
      window.current_command = window.current_command.slice(0, -1);
      window.term.write("\b \b");
      return;
    } else if (data.charCodeAt(0) == 27) {
      window.term.write(Array(window.current_command.length).join("\b \b"));
      window.current_command =
        window.terminal_history[window.terminal_history.length - 1];
      window.terminal_history.pop();
      window.term.write(window.current_command);
      return;
    }
    console.log(window.current_command);
    window.current_command += data;
    window.term.write(data);
  });
  window.term.open(document.querySelector(".terminal"));
  window.term.write("Welcome to \x1B[1;3;31mHotCode - C++\x1B[0m");
  window.term.write("\n\x1B[1;3;31m >> \x1B[0m");
  window.fitAddon.fit();
};
