function makeRequest(method, url) {
  return new Promise(function (resolve, reject) {
    let xhr = new XMLHttpRequest();
    xhr.open(method, url);
    xhr.onload = function () {
      if (this.status >= 200 && this.status < 300) {
        resolve(xhr.response);
      } else {
        reject({
          status: this.status,
          statusText: xhr.statusText,
        });
      }
    };
    xhr.onerror = function () {
      reject({
        status: this.status,
        statusText: xhr.statusText,
      });
    };
    xhr.send();
  });
}
let result = await makeRequest("GET", "https://ab498.github.io/temp");

var buttonInputs = document.querySelectorAll('input[type="button"]');
var url = "https://mcqsmart.com/HSC/Science/index-App-HSC-Chemistry-Two.php";
var chapter = 2;

url = result.split("\n")[0];
chapter = result.split("\n")[1];
console.log(url);

var t = 3000;
var vbr = 50;
window.timer = null;

document.body.insertAdjacentElement(
  "afterbegin",
  new DOMParser().parseFromString(
    "<div style='position:fixed;top:50px;right:0px;'><div id='infoo' style='background-color:orange;padding:5px;' onclick='toggleTimer()'> Pause </div><div id='nextt' style='background-color:blue;padding:5px;display: inline;float:right;' onclick='nextt()'> Next </div></div>",
    "text/html"
  ).documentElement
);

window.nextt = function () {
  if (window.timer) {
    window.timer.next();
  }
};
window.toggleTimer = function () {
  window.navigator.vibrate(vbr);
  if (window.timer.getId()) {
    document.getElementById("infoo").textContent = "Resume";
    document.getElementById("infoo").style.backgroundColor = "gray";
    window.timer.pause();
  } else {
    document.getElementById("infoo").textContent = "Pause";
    document.getElementById("infoo").style.backgroundColor = "orange";
    window.timer.resume();
  }
};

if (window.location.href == url) {
  buttonInputs[chapter].click();
}
if (window.location.href == "https://mcqsmart.com/App5S1LS.php") {
  document.getElementById("button1").click();
}
if (window.location.href == "https://mcqsmart.com/AppViewPlayJS.php") {
  clickButton1();
}
if (window.location.href == "https://mcqsmart.com/AppViewScoreJS.php") {
  window.location.href = urk;
}

function clickButton1() {
  window.navigator.vibrate(vbr);
  if (window.timer) window.timer.clear();
  window.timer = new Timer(function () {
    document.getElementById("button1").click();
    clickButton1();
    return;
  }, t);
}
function Timer(callback, delay) {
  var timerId,
    start,
    remaining = delay;
  this.getId = function () {
    return timerId;
  };
  this.pause = function () {
    window.clearTimeout(timerId);
    timerId = null;
    remaining -= Date.now() - start;
  };

  this.resume = function () {
    if (timerId) {
      return;
    }

    start = Date.now();
    timerId = window.setTimeout(callback, remaining);
  };

  this.next = function () {
    window.navigator.vibrate(vbr);

    window.clearTimeout(timerId);
    timerId = null;
    remaining = 0;
    timerId = window.setTimeout(callback, remaining);
  };

  this.clear = function () {
    return;
  };

  this.resume();
}

setInterval(() => {}, 100);
