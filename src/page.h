const char page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta
      name="viewport"
      content="width=device-width, initial-scale=1.0, user-scalable=no"
    />

    <link rel="shortcut icon" href="data:" type="image/x-icon" />
    <title>RC</title>

    <style>
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
        background-color: #303030;
        color: beige;
        font-family: monospace;
        font-weight: 900;
        user-select: none;
        outline: none;
      }

      html,
      body {
        height: 100%;
      }

      body {
        display: flex;
        align-items: center;
        justify-content: space-evenly;
      }

      body > div {
        width: 30%;
      }

      body > div > input {
        width: 100%;
      }


    </style>
  </head>

  <body>
    <div id="steerdiv">
      <input type="range" id="steer" min="0" max="2" value="1" />
    </div>

    <div id="throtdiv">
      <input type="range" id="throt" min="0" max="20" value="10" />
    </div>

    <script>
      const socket = new WebSocket("ws://" + location.hostname + ":81");

      socket.onopen = () => {
        const steer = document.getElementById("steer");
        const throttle = document.getElementById("throt");

        const data = new Uint8Array(1);

        throttle.oninput = steer.oninput = () => {
          data[0] = (+throttle.value) * 10 + (+steer.value);
          socket.send(data);
        };
      };

      //   socket.onclose = () => {
      //     document.body.innerHTML =
      //       '<h1 align="center" style="margin-top: 50%">Connection Lost!!</h1>';
      //   };
    </script>
  </body>
</html>
)rawliteral";