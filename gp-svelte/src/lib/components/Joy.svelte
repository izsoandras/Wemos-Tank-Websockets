<script lang="ts">
  import { onMount } from "svelte";
  import { angularVelocityStore, speedStore } from "../stores/controller";

  let canvas = $state<HTMLCanvasElement | undefined>(undefined);
  let ctx = $derived(canvas?.getContext("2d"));
  let width = $state<number>(window.innerWidth);
  let radius = 100;
  let height = $state<number>(radius * 4.5);
  // svelte-ignore state_referenced_locally
  let x_orig = $state<number>(width / 2);
  // svelte-ignore state_referenced_locally
  let y_orig = $state<number>(height / 2);
  let coord = { x: 0, y: 0 };
  let paint = false;
  let x_coordinate = $state(0);
  let y_coordinate = $state(0);
  let speed = $state(0);
  let angle = $state(0);

  onMount(() => {
    resize();
  });

  function resize() {
    if (!canvas) return;
    width = window.innerWidth;
    height = radius * 4.5;
    canvas.width = width;
    canvas.height = height;
    x_orig = width / 2;
    y_orig = height / 2;
    drawJoystick(width / 2, height / 2);
  }

  function drawJoystick(x: number, y: number) {
    if (!canvas || !ctx) return;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.beginPath();
    ctx.arc(x, y, radius, 0, Math.PI * 2, true);
    ctx.fillStyle = "#F08080";
    ctx.fill();
    ctx.strokeStyle = "#F6ABAB";
    ctx.lineWidth = 8;
    ctx.stroke();
  }

  function getPosition(event) {
    if (!canvas) return;
    const mouse_x = event.clientX || event.touches[0].clientX;
    const mouse_y = event.clientY || event.touches[0].clientY;
    coord.x = mouse_x - canvas.offsetLeft;
    coord.y = mouse_y - canvas.offsetTop;
  }

  function is_it_in_the_circle() {
    const current_radius = Math.sqrt(
      Math.pow(coord.x - x_orig, 2) + Math.pow(coord.y - y_orig, 2)
    );
    return radius >= current_radius;
  }

  function startDrawing(event) {
    paint = true;
    getPosition(event);
    if (is_it_in_the_circle()) {
      drawJoystick(coord.x, coord.y);
      Draw(event);
    }
  }

  function stopDrawing() {
    paint = false;
    drawJoystick(width / 2, height / 2);
    x_coordinate = 0;
    y_coordinate = 0;

    speedStore.reset();
    angularVelocityStore.reset();

    speed = 0;
    angle = 0;
  }

  function Draw(event) {
    if (paint) {
      let angle_in_degrees, x, y;
      const angleRad = Math.atan2(coord.y - y_orig, coord.x - x_orig);

      if (Math.sign(angleRad) == -1) {
        angle_in_degrees = Math.round((-angleRad * 180) / Math.PI);
      } else {
        angle_in_degrees = Math.round(360 - (angleRad * 180) / Math.PI);
      }

      if (is_it_in_the_circle()) {
        drawJoystick(coord.x, coord.y);
        x = coord.x;
        y = coord.y;
      } else {
        x = radius * Math.cos(angleRad) + x_orig;
        y = radius * Math.sin(angleRad) + y_orig;
        drawJoystick(x, y);
      }

      getPosition(event);

      speed = Math.round(
        (100 * Math.sqrt(Math.pow(x - x_orig, 2) + Math.pow(y - y_orig, 2))) /
          radius
      );

      x_coordinate = Math.round(x - x_orig);
      y_coordinate = Math.round(y - y_orig);

      speedStore.set((y_coordinate / 100) * -1);
      angularVelocityStore.set(x_coordinate / 100);

      angle = angle_in_degrees;

      // Uncomment the following line if you want to implement the send function
      // send(x_coordinate, y_coordinate, speed, angle);
    }
  }
</script>

<svelte:window onresize={() => resize()} />

<div class="joystick-container">
  <p class="coordinates">
    X: <span>{x_coordinate}</span> Y: <span>{y_coordinate}</span> Speed:
    <span>{speed}</span>% Angle: <span>{angle}</span>
  </p>
  <canvas
    bind:this={canvas}
    onmousedown={startDrawing}
    onmouseup={stopDrawing}
    onmousemove={Draw}
    ontouchstart={startDrawing}
    ontouchend={stopDrawing}
    ontouchcancel={stopDrawing}
    ontouchmove={Draw}
  ></canvas>
</div>

<style lang="postcss">
  .joystick-container {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100%;
    width: 100%;
  }

  .coordinates {
    font-family: Arial, sans-serif;
    font-size: 16px;
    margin-bottom: 20px;
    @apply select-none;
  }

  canvas {
    touch-action: none;
  }
</style>
