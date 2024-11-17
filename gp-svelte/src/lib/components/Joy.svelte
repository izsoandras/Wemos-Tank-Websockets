<script lang="ts">
  interface Props {
    showValues?: boolean;
    outputCoord: { x: number; y: number };
    oneAxis?: "x" | "y";
    radius?: number;
    parentWidth?: number;
  }
  let {
    showValues,
    outputCoord = $bindable(),
    radius = 100,
    oneAxis,
    parentWidth,
  }: Props = $props();

  let parent = $state<HTMLDivElement | null>(null);

  let canvas = $state<HTMLCanvasElement | undefined>(undefined);
  let canvasCtx = $derived(canvas?.getContext("2d"));

  /**
   * Canvas container size
   */
  let container = $derived({
    width: parentWidth ?? screen.width,
    height: radius * 4.5,
  });

  /**
   * Inner center
   */
  let origin = $derived({
    x: container.width / 2,
    y: container.height / 2,
  });

  /**
   * Position inside canvas, normalized
   */
  let coord = $state({ x: 0, y: 0 });

  /**
   * Is painting?
   */
  let paint = $state(false);
  let speed = $state(0);
  let angle = $state(0);

  $effect(() => {
    resize();
  });

  function resize() {
    if (!canvas) return;

    canvas.width = container.width;
    canvas.height = container.height;
    drawJoystick(container.width / 2, container.height / 2);
  }

  function drawJoystick(x: number, y: number) {
    if (!canvas || !canvasCtx) return;
    canvasCtx.clearRect(0, 0, canvas.width, canvas.height);
    canvasCtx.beginPath();
    canvasCtx.arc(x, y, radius, 0, Math.PI * 2, true);
    canvasCtx.fillStyle = "#444";
    canvasCtx.fill();
    canvasCtx.strokeStyle = "#fff";
    canvasCtx.lineWidth = 8;
    canvasCtx.stroke();
  }

  /**
   * Sets current position in `coord`
   * @param event
   */
  function getPosition(event: MouseEvent | TouchEvent) {
    if (!canvas) return;

    let mouse_x, mouse_y;

    if (event instanceof MouseEvent) {
      mouse_x = event.clientX;
      mouse_y = event.clientY;
    } else {
      mouse_x = event.touches[0].clientX;
      mouse_y = event.touches[0].clientY;
    }

    coord.x = mouse_x - canvas.offsetLeft;
    coord.y = mouse_y - canvas.offsetTop;

    if (oneAxis === "x") {
      coord.x = origin.x;
    }

    if (oneAxis === "y") {
      coord.y = origin.y;
    }

    return { x: coord.x, y: coord.y };
  }

  function isInCircle() {
    const current_radius = Math.sqrt(
      Math.pow(coord.x - origin.x, 2) + Math.pow(coord.y - origin.y, 2)
    );
    return radius >= current_radius;
  }

  function startDrawing(event: MouseEvent | TouchEvent) {
    paint = true;
    getPosition(event);

    if (isInCircle()) {
      drawJoystick(coord.x * 10, coord.y);
      Draw(event);
    }
  }

  function stopDrawing() {
    paint = false;
    drawJoystick(container.width / 2, container.height / 2);
    outputCoord = { x: 0, y: 0 };

    speed = 0;
    angle = 0;
  }

  function Draw(event: MouseEvent | TouchEvent) {
    if (paint) {
      let x, y;
      const angleRad = Math.atan2(coord.y - origin.y, coord.x - origin.x);

      const angleInDegrees =
        Math.sign(angleRad) == -1
          ? Math.round((-angleRad * 180) / Math.PI)
          : Math.round(360 - (angleRad * 180) / Math.PI);

      if (isInCircle()) {
        x = coord.x;
        y = coord.y;
        drawJoystick(coord.x, coord.y);
      } else {
        x = radius * Math.cos(angleRad) + origin.x;
        y = radius * Math.sin(angleRad) + origin.y;
        drawJoystick(x, y);
      }

      getPosition(event);

      speed = Math.round(
        (100 *
          Math.sqrt(Math.pow(x - origin.x, 2) + Math.pow(y - origin.y, 2))) /
          radius
      );

      outputCoord = {
        x: Math.round(x - origin.x),
        y: Math.round(y - origin.y),
      };

      angle = angleInDegrees;
    }
  }
</script>

<svelte:window onresize={() => resize()} />

<div class="joystick-container" bind:this={parent}>
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
    font-size: 16px;
    margin-bottom: 20px;

    @apply select-none;
  }

  canvas {
    touch-action: none;
    background-image: radial-gradient(circle, #f08080, #fff);
    @apply border-2 bg-slate-100;
  }
</style>
