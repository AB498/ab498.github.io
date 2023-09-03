window.setDarkMode = (isDark, updateUI) => {
  if (updateUI) {
    if (
      document
        .querySelector(".tailwind-dark-toggle-main")
        .classList.contains("opacity-0")
    )
      document
        .querySelector(".tailwind-dark-toggle-main")
        .classList.remove("opacity-0");
    if (isDark) document.querySelector("#switchhelper").classList.add("grow");
    else document.querySelector("#switchhelper").classList.remove("grow");
  }
  // update html element
  if (isDark) {
    document.documentElement.classList.add("dark");
    localStorage.theme = "dark";
  } else {
    document.documentElement.classList.remove("dark");
    localStorage.theme = "light";
  }
};
window.setDarkMode(localStorage.getItem("theme") === "dark");

window.poll = (func, callback) => {
  let res = func();
  if (!res) {
    setTimeout(() => {
      window.poll(func, callback);
    }, 100);
    return;
  }
  callback();
};

poll(
  () => window.document.querySelector(".tailwind-dark-toggle"),
  () => {
    document.querySelector(".tailwind-dark-toggle").insertAdjacentElement(
      "beforeend",
      new DOMParser()
        .parseFromString(
          `
       <div class="transition-all duration-300 tailwind-dark-toggle-main flex flex-col items-center justify-center opacity-0">
          <input
            type="checkbox"
            class="hidden"
            id="dark-toggle"
            onchange="window.setDarkMode(localStorage.theme != 'dark', true)"
          />
          <label for="dark-toggle">
            <div
              class="flex h-6 w-10 cursor-pointer items-center rounded-full bg-gray-200 dark:bg-gray-700 ring-2 dark:ring-slate-500 border-violet-400 text-zinc-950 dark:text-zinc-50"
            >
              <div
                id="switchhelper"
                class="transition-all duration-200 ease-in-out"
                :ref="
                  (el) => {
                    // window.localStorage.getItem('theme') == 'dark'
                    //   ? el.classList.add('grow')
                    //   : null;
                  }
                "
              ></div>
              <div
                class="toggle-circle flex h-6 w-6 items-center justify-center rounded-full bg-zinc-50 dark:bg-blue-950 border-2 border-blue-400 p-1"
              >
                <svg
                  role="img"
                  class="dark:hidden dark:invert"
                  width="20"
                  viewBox="0 0 24 24"
                  xmlns="http://www.w3.org/2000/svg"
                  aria-labelledby="color-scheme-light"
                >
                  <path
                    d="M12 18c-3.309 0-6-2.691-6-6s2.691-6 6-6 6 2.691 6 6-2.691 6-6 6zm0-10c-2.206 0-4 1.794-4 4s1.794 4 4 4 4-1.794 4-4-1.794-4-4-4zm0-4a1 1 0 0 1-1-1V1a1 1 0 0 1 2 0v2a1 1 0 0 1-1 1zm0 20a1 1 0 0 1-1-1v-2a1 1 0 1 1 2 0v2a1 1 0 0 1-1 1zM5.64 6.64a.997.997 0 0 1-.707-.293l-1.42-1.42a.999.999 0 1 1 1.414-1.414l1.42 1.42A.999.999 0 0 1 5.64 6.64zm14.139 14.139a.997.997 0 0 1-.707-.293l-1.42-1.42a.999.999 0 1 1 1.414-1.414l1.42 1.42a.999.999 0 0 1-.707 1.707zM3 13H1a1 1 0 1 1 0-2h2a1 1 0 0 1 0 2zm20 0h-2a1 1 0 1 1 0-2h2a1 1 0 1 1 0 2zM4.22 20.779a.999.999 0 0 1-.707-1.707l1.42-1.42a.999.999 0 1 1 1.414 1.414l-1.42 1.42a.993.993 0 0 1-.707.293zM18.359 6.64a.999.999 0 0 1-.707-1.707l1.42-1.42a.999.999 0 1 1 1.414 1.414l-1.42 1.42a.997.997 0 0 1-.707.293z"
                  ></path>
                </svg>
                <svg
                  role="img"
                  class="hidden dark:block dark:invert"
                  width="20"
                  viewBox="0 0 24 24"
                  xmlns="http://www.w3.org/2000/svg"
                  aria-labelledby="color-scheme-dark"
                >
                  <path
                    d="M12.048 21.963c-.308 0-.618-.015-.93-.043-2.66-.246-5.064-1.513-6.771-3.567s-2.512-4.651-2.266-7.311a10.004 10.004 0 0 1 9.038-9.038 1 1 0 0 1 .896 1.589 6.008 6.008 0 0 0 1.258 8.392c2.078 1.536 5.055 1.536 7.133 0a1 1 0 0 1 1.591.896 9.951 9.951 0 0 1-9.949 9.082zM9.315 4.438a8.006 8.006 0 0 0-5.244 6.787 7.954 7.954 0 0 0 1.813 5.849 7.95 7.95 0 0 0 5.417 2.854 7.95 7.95 0 0 0 8.266-5.243 8.01 8.01 0 0 1-2.729.476 7.946 7.946 0 0 1-4.755-1.565C9.174 11.443 8.145 7.68 9.315 4.438z"
                  ></path>
                </svg>
              </div>
            </div>
          </label>
        </div>`,
          "text/html"
        )
        .documentElement.querySelector("body").firstChild
    );
    window.setDarkMode(localStorage.getItem("theme") === "dark", true);
  }
);
