// Get the full URL of the current page
var currentURL = window.location.href;

// Parse the URL to extract query parameters
var urlParams = new URLSearchParams(window.location.search);

// Get the values of the "source" and "clickid" parameters
var sourceParam = urlParams.get("source");
var clickIdParam = urlParams.get("clickid");

// Do something with the captured parameters
console.log("Source: " + sourceParam);
console.log("Click ID: " + clickIdParam);

// other parameters
var firstnameURLParam = urlParams.get("firstname");
var lastnameURLParam = urlParams.get("lastname");
var postcodeURLParam = urlParams.get("postcode");
var emailURLParam = urlParams.get("email");
var phoneURLParam = urlParams.get("phone");

$("#first-name").val(firstnameURLParam);
$("#last-name").val(lastnameURLParam);
$("#postcode").val(postcodeURLParam);
$("#email").val(emailURLParam);
$("#phn-number").val(phoneURLParam);

$(".btn_show_form").click(function (e) {
  showForm(e);
});

function showForm(e) {
  if (e) {
    e.preventDefault();
    e.stopPropagation();
  }
  setTimeout(() => {
    if ($(".absolute-form").hasClass("d-none"))
      $(".absolute-form").removeClass("d-none");
  }, 0);
}
const specifiedElement = document
  .querySelector(".absolute-form")
  .querySelector(".wrapper");
// I'm using "click" but it works with any event
document.addEventListener("click", (event) => {
  const isClickInside = specifiedElement.contains(event.target);

  if (!isClickInside) {
    if (!$(".absolute-form").hasClass("d-none"))
      $(".absolute-form").addClass("d-none");
    // The click was OUTSIDE the specifiedElement, do something
  }
});

//accordion
$(document).ready(function () {
  //toggle the component with   ass accordion_body
  $(".accordion_head").click(function () {
    if ($(".accordion_head").css("background-color", "")) {
      $(".accordion_body").is(":visible");
      $(".accordion_body").slideUp(300);
      $(".plusminus").text("+");
    }
    if ($(this).next(".accordion_body").is(":visible")) {
      $(this).next(".accordion_body").slideUp(300);
      $(this).children(".plusminus").text("+");
    } else {
      $(".accordion_head").css("background-color", "");
      $(this).next(".accordion_body").slideDown(300);
      $(this).children(".plusminus").text("-");
    }
  });
});
// testimonial
var swiper = new Swiper(".slider-content", {
  slidesPerView: 3,
  spaceBetween: 25,
  loop: true,
  centeredSlides: true,
  grabCursor: true,
  pagination: {
    el: ".swiper-pagination",
    clickable: true,
    dynamicBullets: true,
  },
  navigation: {
    nextEl: ".swiper-button-next",
    prevEl: ".swiper-button-prev",
  },

  breakpoints: {
    0: {
      slidesPerView: 1,
    },
    520: {
      slidesPerView: 2,
    },
    950: {
      slidesPerView: 3,
    },
  },
});
// form

var form_1 = document.querySelector(".form_1");
var form_2 = document.querySelector(".form_2");
var form_3 = document.querySelector(".form_3");

var form_1_btns = document.querySelector(".form_1_btns");
var form_2_btns = document.querySelector(".form_2_btns");
var form_3_btns = document.querySelector(".form_3_btns");

var form_1_next_btn = document.querySelector(".form_1_btns .btn_next");

var form_2_next_btn = document.querySelector(".form_2_btns .btn_next");

var form_1_progessbar = document.querySelector(".form_1_progessbar");
var form_2_progessbar = document.querySelector(".form_2_progessbar");
var form_3_progessbar = document.querySelector(".form_3_progessbar");

var btn_done = document.querySelector(".btn_done");
var modal_wrapper = document.querySelector(".modal_wrapper");
var shadow = document.querySelector(".shadow");

var form_1_data = {};
var form_2_data = {};
var form_3_data = {};

const error = document.querySelector(".error");
let errorRemoval;
function showError(msg, title) {
  const error = document.querySelector(".error");
  error.style.animation = "";
  setTimeout(() => {
    error.style.animation = "shake 0.5s linear 1";
  }, 0);
  error.querySelector(".error-text").innerHTML = msg;
  error.querySelector(".error-text-title").innerHTML = title || "Error!";
  error.classList.remove("d-none");
}
function removeError() {
  error.classList.add("d-none");
}

form_1_next_btn.addEventListener("click", function () {
  removeError();
  $(form_1.querySelector("form"))
    .serializeArray()
    .map(function (x) {
      form_1_data[x.name] = x.value;
    });
  var data = $("input[name=issue]:checked")
    .map(function (err, el) {
      return $(el).val();
    })
    .get();
  form_1_data["issue"] = data.join(", ");
  console.log(form_1_data);
  if (!form_1_data["issue"]) {
    showError("Please select an issue");
    return;
  }

  form_1.style.display = "none";
  form_2.style.display = "block";

  form_1_btns.style.display = "none";
  form_2_btns.style.display = "flex";

  form_1_progessbar.querySelector(
    "p"
  ).innerHTML = `<i class="fa-solid fa-check"></i>`;
  form_2_progessbar.classList.add("active");
});

form_2_next_btn.addEventListener("click", function () {
  removeError();
  let form2errors = getErrorsForm2();
  if (form2errors) {
    showError(form2errors, "Sorry!");
    return;
  }

  $(form_2.querySelector("form"))
    .serializeArray()
    .map(function (x) {
      form_2_data[x.name] = x.value;
    });
  form_2.style.display = "none";
  form_3.style.display = "block";

  form_3_btns.style.display = "flex";
  form_2_btns.style.display = "none";

  form_3_progessbar.classList.add("active");

  $(".step_1_2_info").addClass("d-none");
  form_2_progessbar.querySelector(
    "p"
  ).innerHTML = `<i class="fa-solid fa-check"></i>`;
});

let inputWraps = document.querySelectorAll(".input_wrap");

inputWraps.forEach((inputWrap) => {
  let input = inputWrap.querySelector(".input_select");

  input.addEventListener("click", function () {
    if (input.checked) {
      inputWrap.classList.add("checked");
    } else {
      inputWrap.classList.remove("checked");
    }
  });
});
$(form_3)
  .find("input[type='checkbox']")
  .change(function () {
    removeError();
    $(form_3.querySelector("form"))
      .serializeArray()
      .map(function (x) {
        form_3_data[x.name] = x.value;
      });
    $(form_3)
      .find("input[type='checkbox']")
      .each(function () {
        var checkboxName = $(this).attr("name");
        var isChecked = $(this).is(":checked");
        form_3_data[checkboxName] = isChecked;
      });
    if (!form_3_data["tickbox"]) {
      showError("Please read and confirm checkbox");
      return;
    }
  });
let checkboxes = document.querySelectorAll('input[type="radio"][name="issue"]');
checkboxes.forEach((checkbox) => {
  checkbox.addEventListener("change", (event) => {
    if (event.target.checked) {
      checkboxes.forEach((cb) => {
        if (cb !== event.target) {
          cb.checked = false;
          cb.parentElement.classList.remove("checked");
        }
      });
    }
  });
});

function getErrorsForm2() {
  $(form_2.querySelector("form"))
    .serializeArray()
    .map(function (x) {
      form_2_data[x.name] = x.value;
    });
  console.log("form_2_data", form_2_data);
  // console.log(form_2_data["switch-one"]);
  if (form_2_data["switch-one"] == "no") {
    return "Unfortunately you are unable to make a claim if you do not live in a council or housing association property";
  }
  if (form_2_data["switch-two"] == "yes") {
    return "Unfortunately you are unable to make a claim if the issues in the property have been fixed";
  }
  if (form_2_data["switch-three"] == "Under 6 months") {
    return "Unfortunately we are unable to help with a claim if the issues have only been reported to the landlord in the last 4 months.";
  }
  return false;
}
let checkboxes_2 = $(".form_2").find('input[type="radio"]');
checkboxes_2.on("change", () => {
  removeError();
  let form2errors = getErrorsForm2();
  if (form2errors) {
    showError(form2errors, "Sorry!");
    return;
  }
});

function isValidPhoneLive(phoneNumber) {
  form_3_btns.classList.add("loading");
  form_3_btns.querySelector(".btn_done").disabled = true;
  if (phoneNumber.slice(0, 3) == "+44") {
    phoneNumber = phoneNumber.replace("+44", "0");
  }
  return new Promise((resolve, reject) => {
    $.ajax({
      type: "get",
      url: "apiphone.php?phone=" + phoneNumber,
      async: false,
      success: function (result) {
        try {
          console.log(JSON.parse(result));
          resolve(JSON.parse(result));
        } catch (e) {
          console.error("Failed to reach API", e);
          resolve({ error: "Failed to reach API" });
        }
      },
      error: function (error) {
        console.log(error);
        resolve(false);
      },
    });
  });
}
function isValidPostcode(postcode) {
  const ukPostcodeRegex =
    /^(([Gg][Ii][Rr]\s0[Aa]{2})|((([A-Za-z][0-9]{1,2})|(([A-Za-z][A-Ha-hJ-Yj-y][0-9]{1,2})|(([A-Za-z][0-9][A-Za-z])|([A-Za-z][A-Ha-hJ-Yj-y][0-9][A-Za-z]?))))\s?[0-9][A-Za-z]{2}))$/;
  return ukPostcodeRegex.test(postcode);
}
async function submitForm() {
  removeError();

  $(form_3.querySelector("form"))
    .serializeArray()
    .map(function (x) {
      form_3_data[x.name] = x.value;
    });
  $(form_3)
    .find("input[type='checkbox']")
    .each(function () {
      var checkboxName = $(this).attr("name");
      var isChecked = $(this).is(":checked");
      form_3_data[checkboxName] = isChecked;
    });
  console.log(form_3_data);
  const fields = {
    "first-name": "First name",
    "last-name": "Last name",
    email: "Email",
    "phone-number": "Phone number",
  };
  for (const [field, fieldName] of Object.entries(fields)) {
    if (!form_3_data[field]) {
      showError(fieldName + " is empty");
      return;
    }
  }
  if (!isValidPhone(form_3_data["phone-number"])) {
    showError("Invalid phone number");
    return;
  }
  if (!isValidEmail(form_3_data["email"])) {
    showError("Invalid email");
    return;
  }
  if (!isValidPostcode(form_3_data["postcode"])) {
    showError("Invalid email");
    return;
  }
  if (!form_3_data["tickbox"]) {
    showError("Please read and confirm checkbox");
    return;
  }
  try {
    let validPhone = await isValidPhoneLive(form_3_data["phone-number"]);
    if (!validPhone?.error || validPhone?.status != "Valid") {
      showError(validPhone?.error || "Please enter a valid phone number");
      return;
    }
    let [errors, response] = await postData();
    console.log(response);
    if (response.status == "Error") {
      showError(response.errors[0]);
      return;
    } else {
      const formWrap = document.querySelector(".form_wrap");
      const submittedDiv = document.querySelector(".submitteddiv");
      const progressBar = document.querySelector(".header");
      const btnWrap = document.querySelector(".btns_wrap");
      const formtxtp = document.querySelector(".form_txtp");
      formtxtp.style.display = "none";
      progressBar.style.display = "none";
      btnWrap.style.display = "none";
      formWrap.style.display = "none";
      submittedDiv.style.display = "block";
      document.querySelector(".thanks_txt").textContent = document
        .querySelector(".thanks_txt")
        .textContent.replace("$Name", form_3_data["first-name"]);
    }
  } catch (e) {
    showError("Request to API failed!");
    console.log(e);
  } finally {
    form_3_btns.classList.remove("loading");
    form_3_btns.querySelector(".btn_done").disabled = false;
  }
}
// function isValidPhone(input) {
//   const numericRegexWithPlus = /^\+?\d{10}$/;
//   return numericRegexWithPlus.test(input);
// }
function isValidPhone(phoneNumber) {
  // Regular expression to match UK phone number with +44 country code
  // const ukPhoneRegex = /^\+44\s?(\d\s?){9,13}\d$/;
  const ukPhoneRegex =
    /^(((\+44\s?\d{4}|\(?0\d{4}\)?)\s?\d{3}\s?\d{3})|((\+44\s?\d{3}|\(?0\d{3}\)?)\s?\d{3}\s?\d{4})|((\+44\s?\d{2}|\(?0\d{2}\)?)\s?\d{4}\s?\d{4}))(\s?\#(\d{4}|\d{3}))?$/;

  // Test the phone number against the regex and return the result (true if valid, false otherwise)
  return ukPhoneRegex.test(phoneNumber);
}

function isValidEmail(email) {
  let regex = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
  if (email.match(regex)) return true;
  return false;
}
function postData() {
  return new Promise((resolve, reject) => {
    const requestData = {
      key: "42c4ea91c662a693e6479788c105bf6f",
      lead: {
        campid: "HOUSING-DISREPAIR",
        sid: "1",
        email: form_3_data["email"],
        firstname: form_3_data["first-name"],
        lastname: form_3_data["last-name"],
        phone1: form_3_data["phone-number"],
        postcode: form_3_data["postcode"],
        main_issues: form_1_data["issue"],
        council_or_ha: form_2_data["switch-one"],
        confirm_landlord_not_rectified:
          form_2_data["switch-two"] == "yes" ? "no" : "yes",
        "6months": form_2_data["switch-three"],
        source: sourceParam || "",
        c1: clickIdParam || "",
      },
    };

    console.log("requestData", requestData);
    $.ajax({
      type: "post",
      url: "api.php",
      data: JSON.stringify(requestData),
      contentType: "application/json",
      success: function (response) {
        // Handle the response from the API
        resolve([null, JSON.parse(response)]);
      },
      error: function (xhr, status, error) {
        // Handle any errors that occur during the request
        console.log("xhr", xhr);
        console.log("status", status);
        console.log("error", error);
        reject(error);
      },
    });
    // Data to be sent in the POST request

    // jQuery AJAX POST request
  });
}
