#include <pgmspace.h>
char index_html[] PROGMEM = R"=====(<!DOCTYPE html>

<head>
    <meta charset="utf-8">
    <title>Tiger Tank (V1.1)</title>
    <meta name="viewport" content="width=device-width, user-scalable=no">

    <style>
        *,
        *:before,
        *:after {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }

         :root {
            --dur: 0.3s;
            --dur2: 0.15s;
            font-size: 16px;
        }

        body {
            background-color: #50594d;
        }

        form {
            display: flex;
            font-size: 1vh;
            justify-content: space-between;
            align-items: center;
            margin: 2em auto 0 auto;
            width: 23em;
        }

        .levers {
            padding-top: 5vh;
        }
        /* form label {
            background-color: #f00;
            background-image: radial-gradient(0.3em 0.25em at 50% 25%, rgb(255, 255, 255) 25%, rgba(255, 255, 255, 0)), radial-gradient(0.25em 0.25em at 30% 75%, rgba(255, 255, 255, 0.5), rgba(255, 255, 255, 0)), radial-gradient(0.3em 0.3em at 60% 80%, rgba(255, 255, 255, 0.5), rgba(255, 255, 255, 0)), radial-gradient(100% 100%, rgba(255, 255, 255, 0) 30%, rgba(255, 255, 255, 0.3) 40%, rgba(0, 0, 0, 0.5) 50%);
            border-radius: 50%;
            box-shadow: 0 0 0.75em #f00, 0 0.5em 0.75em rgba(0, 0, 0, 0.3);
            display: inline-block;
            transition: all var(--dur2) var(--dur2) linear;
            width: 1.5em;
            height: 1.5em;
        }
         */

        form label:first-of-type {
            background-color: #050;
            box-shadow: 0 0.5em 0.75em rgba(0, 0, 0, 0.3);
            order: -1;
        }

        label span {
            display: inline-block;
            overflow: hidden;
            width: 0;
        }
        /* Lever */

        .lever {
            background-image: radial-gradient(1em 1.5em at 50% 50%, rgb(204, 204, 204) 25%, rgb(170, 170, 170) 49%, rgba(170, 170, 170, 0) 50%), radial-gradient(0.65em 1em at 50% 53%, rgb(68, 68, 68), rgba(68, 68, 68, 0)), radial-gradient(0.75em 0.75em at 55% 45%, rgb(255, 255, 255), rgba(255, 255, 255, 0)), radial-gradient(0.5em 0.4em at 43% 56%, rgba(255, 255, 255, 0.5), rgba(255, 255, 255, 0)), radial-gradient(0.5em 0.4em at 55% 57%, rgba(255, 255, 255, 0.6), rgba(255, 255, 255, 0)), radial-gradient(0.5em 0.4em at 50% 60%, rgba(255, 255, 255, 0.6), rgba(255, 255, 255, 0)), radial-gradient(100% 100% at 50% 50%, rgb(238, 238, 238), rgb(170, 170, 170) 10%, rgb(0, 0, 0) 18%, rgb(0, 0, 0) 21%, rgb(153, 153, 153) 21.5%, rgb(153, 153, 153) 24%, rgba(153, 153, 153, 0) 24.5%, rgba(221, 221, 221, 0) 30%, rgb(221, 221, 221) 30.5%, rgb(221, 221, 221) 33%, rgb(68, 68, 68) 33.5%, rgb(68, 68, 68) 35%, rgba(68, 68, 68, 0) 35.5%, rgba(221, 221, 221, 0) 41%, rgb(221, 221, 221) 41.5%, rgb(238, 238, 238) 45%, rgb(68, 68, 85) 45.5%, rgb(68, 68, 85) 49%, rgba(68, 68, 85, 0) 50%), radial-gradient(2em 2em at 35% 20%, rgb(255, 255, 255), rgba(255, 255, 255, 0) 2em), radial-gradient(2em 2em at 65% 80%, rgb(255, 255, 255), rgba(255, 255, 255, 0) 2em), radial-gradient(2em 2em at 80% 35%, rgb(255, 255, 255), rgba(255, 255, 255, 0) 2em), radial-gradient(2em 2em at 20% 65%, rgb(255, 255, 255), rgba(255, 255, 255, 0) 2em), radial-gradient(100% 100% at center, rgb(170, 170, 170) 49%, rgba(170, 170, 170, 0) 50%);
            background-position: 0.5em 0, 0.5em 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0;
            border-radius: 50%;
            box-shadow: 0 2em 2em rgba(0, 0, 0, 0.3);
            cursor: pointer;
            font-size: 1em;
            display: block;
            outline: 0;
            position: relative;
            width: 12em;
            height: 12em;
            -webkit-appearance: none;
            -moz-appearance: none;
            appearance: none;
            transition: background-position var(--dur) linear;
        }

        .lever:before,
        .lever:after {
            content: "";
            display: block;
            position: absolute;
            top: 50%;
            left: 50%;
        }

        .lever:before {
            animation: leverAOff var(--dur) linear forwards;
            background: radial-gradient(35% 25% at 50% 25%, rgb(136, 136, 153) 20%, rgba(136, 136, 153, 0)), radial-gradient(1em 0.75em at 32% 75%, rgb(102, 102, 102), rgba(102, 102, 102, 0)), radial-gradient(1em 0.75em at 65% 78%, rgb(102, 102, 102), rgba(102, 102, 102, 0)), radial-gradient(100% 100% at center, rgb(68, 68, 68) 49.5%, rgba(68, 68, 68, 0) 50%);
            box-shadow: -2em 4em 2em rgba(0, 0, 0, 0.3), -2em 5em 4em rgba(0, 0, 0, 0.2), -2em 7em 4em rgba(0, 0, 0, 0.2), -2em 9em 4em rgba(0, 0, 0, 0.2), -2em 11em 4em rgba(0, 0, 0, 0.2);
            border-radius: 50%;
            width: 4em;
            height: 4em;
            transform: translate(100%, -50%);
            z-index: 1;
        }

        .lever:checked {
            background-position: -0.5em 0, -0.5em 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0, 0 0;
        }

        .lever:checked:before {
            animation: leverAOn var(--dur) linear forwards;
        }

        .lever:after {
            animation: leverBOff var(--dur) linear forwards;
            background-color: #333;
            border-radius: 15em;
            box-shadow: 0 0 1em #667 inset;
            width: 7.5em;
            height: 4em;
            transform: translate(0.5em, -50%);
        }

        .lever:checked:after {
            animation: leverBOn var(--dur) linear forwards;
        }

        .lever:checked+label {
            background-color: #0d0;
            box-shadow: 0 0 0.75em #0f0, 0 0.5em 0.75em rgba(0, 0, 0, 0.3);
        }

        .lever:checked+label+label {
            background-color: #500;
            box-shadow: 0 0.5em 0.75em rgba(0, 0, 0, 0.3);
        }
        /* To stop animations from running on load */

        .pristine:before,
        .pristine:after {
            animation: none;
        }

        @keyframes leverAOn {
            from {
                box-shadow: -2em 4em 2em rgba(0, 0, 0, 0.3), -2em 5em 4em rgba(0, 0, 0, 0.2), -2em 7em 4em rgba(0, 0, 0, 0.2), -2em 9em 4em rgba(0, 0, 0, 0.2), -2em 11em 4em rgba(0, 0, 0, 0.2);
                transform: translate(100%, -50%);
            }
            50% {
                box-shadow: 0 6em 2em rgba(0, 0, 0, 0.3), 0 5em 4em rgba(0, 0, 0, 0.2), 0 7em 4em rgba(0, 0, 0, 0.2), 0 9em 4em rgba(0, 0, 0, 0.2), 0 11em 4em rgba(0, 0, 0, 0.2);
            }
            to {
                box-shadow: 2em 4em 2em rgba(0, 0, 0, 0.3), 2em 5em 4em rgba(0, 0, 0, 0.2), 2em 7em 4em rgba(0, 0, 0, 0.2), 2em 9em 4em rgba(0, 0, 0, 0.2), 2em 11em 4em rgba(0, 0, 0, 0.2);
                transform: translate(-200%, -50%);
            }
        }

        @keyframes leverAOff {
            from {
                box-shadow: 2em 4em 2em rgba(0, 0, 0, 0.3), 2em 5em 4em rgba(0, 0, 0, 0.2), 2em 7em 4em rgba(0, 0, 0, 0.2), 2em 9em 4em rgba(0, 0, 0, 0.2), 2em 11em 4em rgba(0, 0, 0, 0.2);
                transform: translate(-200%, -50%);
            }
            50% {
                box-shadow: 0 6em 2em rgba(0, 0, 0, 0.3), 0 5em 4em rgba(0, 0, 0, 0.2), 0 7em 4em rgba(0, 0, 0, 0.2), 0 9em 4em rgba(0, 0, 0, 0.2), 0 11em 4em rgba(0, 0, 0, 0.2);
            }
            to {
                box-shadow: -2em 4em 2em rgba(0, 0, 0, 0.3), -2em 5em 4em rgba(0, 0, 0, 0.2), -2em 7em 4em rgba(0, 0, 0, 0.2), -2em 9em 4em rgba(0, 0, 0, 0.2), -2em 11em 4em rgba(0, 0, 0, 0.2);
                transform: translate(100%, -50%);
            }
        }

        @keyframes leverBOn {
            from {
                width: 7.5em;
                transform: translate(0.5em, -50%);
            }
            50% {
                width: 4em;
                transform: translate(-50%, -50%);
            }
            to {
                width: 7.5em;
                transform: translate(-8em, -50%);
            }
        }

        @keyframes leverBOff {
            from {
                width: 7.5em;
                transform: translate(-8em, -50%);
            }
            50% {
                width: 4em;
                transform: translate(-50%, -50%);
            }
            to {
                width: 7.5em;
                transform: translate(0.5em, -50%);
            }
        }

        canvas {
            display: inline-block;
            color: #59594D;
            background-color: #59594D;
            text-shadow: 0 0 2px rgba(0, 0, 0, .3);
            box-shadow: inset 0 0 2px 0 rgba(255, 255, 255, 0.24), inset 0 0 3px 0 rgba(0, 0, 0, 1), inset 0 0 3px 5px rgba(0, 0, 1, .05), 2px 2px 4px 0 rgba(1, 1, 1, 1);
            border-radius: 54px;
            position: relative;
        }
    </style>
</head>

<body onload="start()">
    <!-- <div class="voltage" id="vbat_min_div" style="display: none">VMin: <input id="vbat_min" type="number" min="0.1" max="5.0" step="0.05" value="4.0" style="width: 50px" />
    </div> -->

    <div class="levers">
        <form>
            <input type="checkbox" id="Button0" onchange="Button1Change(this)" class="lever pristine" role="switch">
            <label for="lever"><span>On</span></label>
            <label for="lever"><span>Off</span></label>
        </form>

        <form>
            <input type="checkbox" id="Button0" onchange="Button2Change(this)" class="lever pristine" role="switch">
            <label for="lever"><span>On</span></label>
            <label for="lever"><span>Off</span></label>
        </form>
        <form>
            <input type="checkbox" id="Button0" onchange="Button3Change(this)" class="lever pristine" role="switch">
            <label for="lever"><span>On</span></label>
            <label for="lever"><span>Off</span></label>
        </form>
        <form>
            <input type="checkbox" id="Button0" onchange="Button4Change(this)" class="lever pristine" role="switch">
            <label for="lever"><span>On</span></label>
            <label for="lever"><span>Off</span></label>
        </form>
        <form>
            <input type="checkbox" id="Button0" onchange="Button5Change(this)" class="lever pristine" role="switch">
            <label for="lever"><span>On</span></label>
            <label for="lever"><span>Off</span></label>
        </form>
        <form>
            <input type="checkbox" id="Button0" onchange="Button6Change(this)" class="lever pristine" role="switch">
            <label for="lever"><span>On</span></label>
            <label for="lever"><span>Off</span></label>
        </form>

    </div>

    <div class="voltage" id="vbat" style="display: none">0 V</div>


    <!-- <div id=textdiv style="position:absolute;top:0px;left:0px;"></div> -->
    <canvas id="Canvas_left" style="border:1px solid #d3d3d3;position:absolute; top:10%; left:5%; z-index:0">
	Your browser does not support the HTML5 canvas tag.</canvas>
    <canvas id="Canvas_right" style="border:1px solid #d3d3d3;position:absolute; top:10%; left:55%; z-index:0">
	Your browser does not support the HTML5 canvas tag.</canvas>
    <canvas id="Canvas_stickl" style="position:absolute; top:10%; left:5%; z-index:1">
	Your browser does not support the HTML5 canvas tag.</canvas>
    <canvas id="Canvas_stickr" style="position:absolute; top:10%; left:55%; z-index:1">
	Your browser does not support the HTML5 canvas tag.</canvas>




    <script>
        var elements = document.querySelectorAll(".lever");

        elements.forEach(el => el.addEventListener("change", event => {
            event.target.classList.remove("pristine");
            let ac = "aria-checked";

            event.target.setAttribute(ac, event.target.getAttribute(ac) == "true" ? "false" : "true");
        }));
    </script>

    <script>
        var touches = [];
        var w = 0;
        var wsconnect = 0;
        var h = 0;
        var end = 0;
        var ctx_left;
        var ctx_right;
        var ctx_stickl;
        var ctx_stickr;
        var buttons = [0, 0, 0, 0];
        var ppm = [0, 0, 0, 0, 0, 1100, 1100, 1100];
        var oldppm = [0, 0, 0, 0, 0, 0, 0, 0];
        var pwmtargets = [0, 0, 0, 0, 0];
        var getInterval;
        var aliveInterval;
        var visible = 0;
        var decaymode = 0;

        //var connection = new WebSocket('ws://' + window.location.host + ':81', ['arduino']);
        var connection = new WebSocket('ws://' + window.location.hostname + ':81', ['arduino']);

        connection.onopen = function() { //open
            console.log("Websocket Open");
            wsconnect = 1;
            window.requestAnimationFrame(update);
            draw_stick(ctx_stickl, ctx_stickl.canvas.width / 2, ctx_stickl.canvas.height / 2, 0, 1);
            draw_stick(ctx_stickr, ctx_stickr.canvas.width / 2, ctx_stickr.canvas.height / 2, 2, 3);
            aliveInterval = setInterval(sendalive, 150);
        };

        connection.onerror = function(error) { //error
            console.log('WebSocket Error ' + error);
            wsconnect = 0;
            draw_stick(ctx_stickl, ctx_stickl.canvas.width / 2, ctx_stickl.canvas.height / 2, 0, 1);
            draw_stick(ctx_stickr, ctx_stickr.canvas.width / 2, ctx_stickr.canvas.height / 2, 2, 3);
            clearInterval(getInterval);
        };

        connection.onmessage = function(e) { //Daten empfangen
            console.log("indata: " + e.data);
        }

        connection.onclose = function(e) {
            console.log("Websocket close");
            wsconnect = 0;
            draw_stick(ctx_stickl, ctx_stickl.canvas.width / 2, ctx_stickl.canvas.height / 2, 0, 1);
            draw_stick(ctx_stickr, ctx_stickr.canvas.width / 2, ctx_stickr.canvas.height / 2, 2, 3);
            clearInterval(getInterval);
        }

        function getCursorPosition(canvas, event) {
            var rect = canvas.getBoundingClientRect();
            var x = (2.0 * (event.clientX - rect.left) / canvas.width) - 1.0;
            var y = (2.0 * (event.clientY - rect.top) / canvas.height) - 1.0;
            console.log("x: " + x + " y: " + y);
            return {
                mx: x,
                my: y
            }
        }

        function start() {
            var c_left = document.getElementById("Canvas_left");
            ctx_left = c_left.getContext("2d");

            var c_right = document.getElementById("Canvas_right");
            ctx_right = c_right.getContext("2d");

            var c_stickl = document.getElementById("Canvas_stickl");
            ctx_stickl = c_stickl.getContext("2d");

            var c_stickr = document.getElementById("Canvas_stickr");
            ctx_stickr = c_stickr.getContext("2d");

            update();

            draw_stick(ctx_stickl, c_stickl.width / 2, c_stickl.height / 2, 0, 1);
            draw_stick(ctx_stickr, c_stickr.width / 2, c_stickr.height / 2, 2, 3);

            window.addEventListener("optimizedResize", function() {
                resize();
            });
            window.addEventListener("orientationchange", function() {
                window.setTimeout(resize, 300)
            });
            c_stickl.addEventListener('touchend', function() {
                console.log("endl");
                draw_stick(ctx_stickl, c_stickl.width / 2, c_stickl.height / 2, 0, 1);
            });
            c_stickl.addEventListener('touchmove', function(event) {
                event.preventDefault();
                touches = event.touches;
                window.requestAnimationFrame(update);
            });



            c_stickl.addEventListener('click', function(event) {
                console.log('stickl_clicked_at');
                console.log(event);
                var coords = getCursorPosition(this, event);
                ppm[1] = 0;
                ppm[2] = coords.my;
                sendtankdata();
            });


            c_stickr.addEventListener('click', function(event) {
                console.log('stickr_clicked_at');
                console.log(event);
                var coords = getCursorPosition(this, event);
                ppm[1] = coords.mx;
                ppm[2] = 0;
                sendtankdata();
            });


            c_stickl.addEventListener('touchstart', function(event) {
                console.log('startl');
            });
            c_stickr.addEventListener('touchend', function() {
                console.log("endr");
                end = 1;
                draw_stick(ctx_stickr, c_stickr.width / 2, c_stickr.height / 2, 2, 3);
            });
            c_stickr.addEventListener('touchmove', function(event) {
                event.preventDefault();
                touches = event.touches;
                window.requestAnimationFrame(update);
            });
            c_stickr.addEventListener('touchstart', function(event) {
                console.log('startr');
                end = 0;
            });
        };

        function getVBat() {
            if (wsconnect) {
                console.log("get");
                connection.send("get");
            }
        }

        function Button1Change(checkbox) {
            if (checkbox.checked == true) ppm[4] = ppm[4] | 0x01;
            else ppm[4] = ppm[4] & (~0x01);
            window.requestAnimationFrame(update);
            console.log("Button1: " + ppm[4]);
        }

        function Button2Change(checkbox) {
            if (checkbox.checked == true) ppm[4] = ppm[4] | 0x02;
            else
                ppm[4] = ppm[4] & (~0x02);
            window.requestAnimationFrame(update);
            console.log("Button2: " + ppm[4]);
        }

        function Button3Change(checkbox) {
            if (checkbox.checked == true) ppm[4] = ppm[4] | 0x04;
            else ppm[4] = ppm[4] & (~0x04);
            window.requestAnimationFrame(update);
            console.log("Button3: " + ppm[4]);
        }

        function Button4Change(checkbox) {
            if (checkbox.checked == true) ppm[4] = ppm[4] | 0x08;
            else ppm[4] = ppm[4] & (~0x08);
            window.requestAnimationFrame(update);
            console.log("Button4: " + ppm[4]);
        }

        function Button5Change(checkbox) {
            if (checkbox.checked == true) ppm[4] = ppm[4] | 0x10;
            else ppm[4] = ppm[4] & (~0x10);
            window.requestAnimationFrame(update);
            console.log("Button5: " + ppm[4]);
        }

        function Button6Change(checkbox) {
            if (checkbox.checked == true) ppm[4] = ppm[4] | 0x20;
            else ppm[4] = ppm[4] & (~0x20);
            window.requestAnimationFrame(update);
            console.log("Button6: " + ppm[4]);
        }

        function Button7Change(checkbox) {
            if (checkbox.checked == true) {
                ppm[4] = ppm[4] | 0x40;
                decaymode = 1;
            } else {
                ppm[4] = ppm[4] & (~0x40);
                decaymode = 0;
            }
            window.requestAnimationFrame(update);
            console.log("Button7: " + ppm[4]);
        }

        function resize() {
            ctx_left.canvas.height = window.innerHeight - (window.innerHeight / 10 * 2);
            ctx_left.canvas.width = (window.innerWidth - (window.innerWidth / 10 * 2)) / 2;

            ctx_right.canvas.height = window.innerHeight - (window.innerHeight / 10 * 2);
            ctx_right.canvas.width = (window.innerWidth - (window.innerWidth / 10 * 2)) / 2;

            ctx_stickl.canvas.height = ctx_left.canvas.height;
            ctx_stickl.canvas.width = ctx_left.canvas.width;

            ctx_stickr.canvas.height = ctx_right.canvas.height;
            ctx_stickr.canvas.width = ctx_right.canvas.width;

            draw_stick(ctx_stickl, ctx_stickl.canvas.width / 2, ctx_stickl.canvas.height / 2);
            draw_stick(ctx_stickr, ctx_stickr.canvas.width / 2, ctx_stickr.canvas.height / 2);

        }

        function draw_stick(context, x, y, ppm0, ppm1) {
            context.clearRect(0, 0, context.canvas.width, context.canvas.height);

            context.beginPath();
            context.arc(x, y, window.innerWidth / 100 * 2, 0, 2 * Math.PI);
            if (wsconnect)
                context.fillStyle = 'green';
            else
                context.fillStyle = 'red';
            context.fill();
            context.lineWidth = 5;
            context.strokeStyle = '#003300';
            context.stroke();
            ppm[ppm0] = parseFloat((2.0 * x / context.canvas.width) - 1.0);
            ppm[ppm1] = parseFloat((2.0 * y / context.canvas.height) - 1.0);
        }

        function update() {
            var nw = window.innerWidth;
            var nh = window.innerHeight;
            if ((w != nw) || (h != nh)) {
                w = nw;
                h = nh;
                resize();
            }

            var i, len = touches.length;
            var left = 0;
            var right = 0;
            for (i = 0; i < len; i++) {
                var touch = touches[i];
                var px = touch.pageX - touch.target.offsetLeft;
                var py = touch.pageY - touch.target.offsetTop;
                console.log(touch.target.id);
                if (touch.target.id == "Canvas_stickl" && !left) {
                    if (px > ctx_stickl.canvas.width)
                        px = ctx_stickl.canvas.width;
                    if (py < 0)
                        py = 0;
                    if (px < 0)
                        px = 0;
                    if (py > ctx_stickl.canvas.height)
                        py = ctx_stickl.canvas.height;
                    draw_stick(ctx_stickl, px, py, 0, 1);
                    left = 1;
                }
                if (touch.target.id == "Canvas_stickr" && !right && !end) {
                    if (px > ctx_stickr.canvas.width)
                        px = ctx_stickr.canvas.width;
                    if (py < 0)
                        py = 0;
                    if (px < 0)
                        px = 0;
                    if (py > ctx_stickr.canvas.height)
                        py = ctx_stickr.canvas.height;
                    draw_stick(ctx_stickr, px, py, 2, 3);
                    right = 1;
                }
            }

            sendtankdata();
        }

        function sendalive() {
            sendtankdata();
            return;
        }

        function sendtankdata() {
            //So we know the ppm order: LX, LY, RX, RY
            //the ppm range needs to be transformed to (it already is :) )[-1,1]
            var LY;
            var RX;
            if (ppm[4] & 0x01) {
                LY = ppm[2];
                RX = ppm[3]; //ppm[1];
            } else {
                LY = ppm[0];
                RX = ppm[1]; //ppm[1];
            }
            var axis_fwrev = LY * Math.abs(LY) * 1.0 + LY * Math.abs(LY) * 0.5 * Math.abs(RX);
            var axis_leftright = Math.abs(RX) * RX;
            var mul = 255;
            var left_reverse = mul * Math.max(0, Math.min(1.0, axis_leftright - axis_fwrev));
            var left_forward = mul * Math.max(0, Math.min(1.0, -(axis_leftright - axis_fwrev)));
            var right_reverse = mul * Math.max(0, Math.min(1.0, axis_leftright + axis_fwrev));
            var right_forward = mul * Math.max(0, Math.min(1.0, -(axis_leftright + axis_fwrev)));
            var l_pwm = Math.max(left_forward, left_reverse);
            var r_pwm = Math.max(right_forward, right_reverse);
            if (decaymode == 1) {
                if (left_reverse > 0) {
                    left_forward = 255 - left_reverse;
                    left_reverse = 255;
                } else if (left_forward > 0) {
                    left_reverse = 255 - left_forward;
                    left_forward = 255;
                }
                if (right_reverse > 0) {
                    right_forward = 255 - right_reverse;
                    right_reverse = 255;
                } else if (right_forward > 0) {
                    right_reverse = 255 - right_forward;
                    right_forward = 255;
                }
            }

            //console.log('ppm '+ppm);
            //console.log('LY '+LY);
            //console.log('RX '+RX);
            //console.log('axis_fwrev '+axis_fwrev);
            //console.log('axis_leftright '+axis_leftright);
            //console.log('left_reverse '+left_reverse);
            //console.log('left_forward '+left_forward);
            //console.log('right_reverse '+right_reverse);
            //console.log('right_forward '+right_forward);
            //console.log('buttons '+ppm[4]);
            var sendframe = new Uint8Array(5);
            sendframe[0] = left_reverse;
            sendframe[1] = left_forward;
            sendframe[2] = right_reverse;
            sendframe[3] = right_forward;
            sendframe[4] = ppm[4];
            if (wsconnect) connection.send(sendframe);
            //var newtext = "";
            //newtext = "ppm: ";
            //for (var i = 0; i<8; i++){
            //	newtext += i+":"+ppm[i].toFixed(3)+ " ";
            //}
            // var newtext = "Lpwm= " + l_pwm.toFixed(1) + " Rpwm= " + r_pwm.toFixed(1);
            // newtext += "<br/>";
            // newtext += ' RX=' + RX.toFixed(3) + ' LY=' + LY.toFixed(3) + " FW=" + axis_fwrev.toFixed(3) + " LR=" + axis_leftright.toFixed(3);
            // document.getElementById("textdiv").innerHTML = newtext
        }
    </script>


</body>

</html>
	)=====";
