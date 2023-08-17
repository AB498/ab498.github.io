window.initLayout = async () => {
  var config = {
    content: [
      {
        type: "row",
        content: [
          {
            type: "component",
            componentName: "editorComponent",
          },
          {
            type: "column",
            content: [
              {
                type: "component",
                componentName: "terminalComponent",
              },
              {
                type: "component",
                componentName: "testComponent",
                componentState: { label: "C" },
              },
            ],
          },
        ],
      },
    ],
  };
  window.myLayout = new GoldenLayout(config, $("#layoutContainer"));
  window.myLayout.registerComponent(
    "testComponent",
    function (container, componentState) {
      container.getElement().html("<h2>" + componentState.label + "</h2>");
    }
  );
  window.myLayout.registerComponent(
    "editorComponent",
    function (container, componentState) {
      container.getElement().append(document.querySelector(".editor"));
    }
  );
  window.myLayout.registerComponent(
    "terminalComponent",
    function (container, componentState) {
      container.getElement().append(document.querySelector(".terminal"));
    }
  );
  window.myLayout.init();

  window.myLayout.on("initialised", () => {
    window.myLayout.root.contentItems[0]
      .getItemsByType("component")
      .forEach((component) => {
        if (component.componentName == "editorComponent")
          component.container.on("resize", () => {
            window.editor.layout();
          });
        if (component.componentName == "terminalComponent")
          component.container.on("resize", () => {
            window.fitAddon.fit();
          });
      });
  });
};
