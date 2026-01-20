#ifndef EASY_ESP_CONNECT_UI_H
#define EASY_ESP_CONNECT_UI_H

#include <Arduino.h>

constexpr char index_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang='en'>
<head>
<meta charset='UTF-8'>
<meta http-equiv='X-UA-Compatible' content='IE=edge'>
<meta name='viewport' content='width=device-width, initial-scale=1.0'>
<title>EasyESP Connect</title>
</head>
<script>
function loadNetworks() {
  fetch("/scan")
    .then(response => response.json())
    .then(data => {

      if (data.status !== "done") {
        setTimeout(loadNetworks, 1000);
        return;
      }

      const select = document.getElementById("ssidSelect");
      select.innerHTML = '<option value="">Select WiFi network</option>';

      data.networks.forEach(ssid => {
        const option = document.createElement("option");
        option.value = ssid;
        option.textContent = ssid;
        select.appendChild(option);
      });
    })
    .catch(err => {
      console.log("Scan error", err);
    });
}

window.onload = loadNetworks();
</script>
<script>
document.addEventListener("DOMContentLoaded", () => {
  document.querySelector(".wifi-image").focus();
});
</script>
<body>
<div class='container'>
  <div class='title'>
    <h2 id="title-block">%TITLE%</h2>
  </div>

  <div class='wifi-image'>
    <img src='data:image/png;base64,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' alt=''>
  </div>

  <div class='info-div'>
    <p class='info-para'>
      Please provide the Wi-Fi name (SSID) and password to connect to the internet.
    </p>
  </div>

  <div class='access-token'>
    <h3>Access Token</h3>
    <p>%TOKEN%</p> <!-- 1xTARS1HA26AP2 -->
  </div>

  <!-- FORM WITH DYNAMIC SSID LIST -->
  <form action='/' method='post' onsubmit='return validateForm()'>

    <select class="ssid-select" id="ssidSelect">
    <option value="">Select Wi-Fi Network</option>
    </select>
    <input
      type="text"
      name="ssid"
      id="ssidInput"
      class="ssid-field"
      placeholder="Or enter SSID manually"
      required
    >

    <input type='password' name='password' class='password-field' required placeholder='Password'>
    <button type='submit' class='connect-button'>Connect</button>
  </form>

  <div class='footer'>
    Designed and developed by <a href='http://anvesh-padamata.in'>Anvesh</a>
  </div>
</div>
</body>
<script>
document.addEventListener("DOMContentLoaded", function () {
  const select = document.getElementById("ssidSelect");
  const input  = document.getElementById("ssidInput");

  if (!select || !input) {
    console.log("SSID elements not found");
    return;
  }

  select.addEventListener("change", function () {
    input.value = this.value;
    //input.focus();   // nice UX
  });
});
</script>
<script>
function validateForm() {
  const ssid_v = document.getElementById("ssidInput").value.trim();
  const pwd_v  = document.querySelector(".password-field").value;

  if (ssid_v.length < 1) {
    alert("Please select or enter a Wi-Fi network");
    return false;
  }
  if (pwd_v.length < 8) {
    alert("Password must be at least 8 characters");
    return false;
  }
  return true;
}
</script>

<style>
body{display: flex;justify-content: center;}
.container {display: flex;flex-direction: column;align-items: center;background: linear-gradient(180deg, %THEME_COLOUR% 0%, #FFFFFF 100%);min-width: 320px;width: 600px;height: 860px;border-radius: 32px;margin: 20px;padding: 20px 0px;box-shadow: 0px 4px 32px rgba(0, 0, 0, 0.25);}
h2{font-size: 20px;font-family: sans-serif;font-style: bold;font-weight: 600;color: #313131;}
.wifi-image img{width: 180px;}
.info-div{margin-top: 20px;display: flex;justify-content: center;align-items: center;width: 260px; height: 90px;background-color: whitesmoke;border-radius: 12px;}
.info-para{width: 80%;font-family: monospace;font-style: normal;font-weight: 500;font-size: 12px;line-height: 18px;color: #595959dd;}
.access-token{margin-top: 38px;display: flex;flex-direction: column;align-items: center;}
.access-token h3{margin: 0;font-family: sans-serif;font-style: normal;font-weight: 500;font-size: 14px;line-height: 21px;color: #595959;}
.access-token p{margin:8px;font-family: monospace;font-style: normal;font-weight: 600;font-size: 16px;line-height: 24px;color:#313131;}
form{margin-top: 6px;display: flex;flex-direction: column;align-items: center;}
.ssid-field, .password-field{font-family: monospace;font-size: 16px; font-weight: 600;color: #313131;width: 240px;height:36px;padding-left: 20px;margin-top: 24px;border-radius: 8px;border: 0;}
.connect-button{margin: 26px;width: 140px;height: 40px;border-radius: 22px;border: 0;background: #ADD7D2;box-shadow: 0px 4px 12px rgba(0, 0, 0, 0.25);font-family: sans-serif;font-style: normal;font-weight: 600;font-size: 16px;color: rgba(0, 0, 0, 0.7);line-height: 24px;}
.footer{font-family: monospace;font-size: 10px;margin-top: 40px;font-weight: 600;align-self: center;text-align: center;color: #313131;}
.ssid-select {font-family: monospace;font-weight: 600;color: #313131;width: 240px;height: 36px;padding-left: 16px;margin-top: 24px;
  border-radius: 8px;
  border: 0;
  background-color: white;
  appearance: none;
  -webkit-appearance: none;
  -moz-appearance: none;

  background-image: url("data:image/svg+xml;utf8,\
  <svg xmlns='http://www.w3.org/2000/svg' width='12' height='8'>\
  <path d='M1 1l5 5 5-5' stroke='%23313131' stroke-width='2' fill='none'/>\
  </svg>");
  background-repeat: no-repeat;
  background-position: right 12px center;
}
</style>
</html>
)rawliteral";

constexpr char success_html[] PROGMEM = R"rawliteral(
  <!doctype html>
  <html lang='en'>
  <head>
      <meta charset='UTF-8'>
      <meta http-equiv='X-UA-Compatible' content='IE=edge'>
      <meta name='viewport' content='width=device-width, initial-scale=1.0'>
      <title>Credentials Saved</title>
  </head>
  <body>
      <div class='info-div'>
          <p class='info-para'> Wi-Fi credentials are saved. Device will restart in 5 seconds. </p>
      </div>
  </body>
  <style>
      body {
          display: flex;
          justify-content: center;
      }
      .info-div {
          margin-top: 20px;
          display: flex;
          justify-content: center;
          align-items: center;
          width: 260px;
          height: 90px;
          background-color: whitesmoke;
          border-radius: 12px;
      }
      .info-para {
          width: 80%;
          font-style: normal;
          font-family: monospace;
          font-weight: 500;
          font-size: 16px;
          line-height: 18px;
          color: #595959dd;
      }
  </style>
  </html>
)rawliteral";


#endif