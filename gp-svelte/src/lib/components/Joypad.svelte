<script lang="ts">
  type Event = TouchEvent & {
    currentTarget: EventTarget & HTMLDivElement;
  };

  let position = $state({ x: 0, y: 0 });
  let active = $state(false);

  const handleMove = (event: Event) => {
    const touch = event.touches[0];
    const ref = event.target as Element;

    if (ref) {
      const rect = ref.getBoundingClientRect();
      const centerX = rect.left + rect.width / 2;
      const centerY = rect.top + rect.height / 2;

      let x = (touch.clientX - centerX) / (rect.width / 2);
      let y = (touch.clientY - centerY) / (rect.height / 2);

      x = Math.max(-1, Math.min(1, x));
      y = Math.max(-1, Math.min(1, y));

      position = { x, y };
    }
  };

  const handleStart = (_event: Event) => {
    active = true;
  };

  const handleEnd = (_event: Event) => {
    active = false;
    position = { x: 0, y: 0 };
  };

  const size = 128;
</script>

<div class="container">
  <!-- svelte-ignore a11y_no_static_element_interactions -->
  <div
    class="joystick"
    ontouchstart={handleStart}
    ontouchmove={handleMove}
    ontouchend={handleEnd}
  >
    <div
      class="knob"
      style="transform: translate(calc(50% + {position.x *
        size}px - 2rem), calc(50% + {position.y * size}px - 2rem));"
    ></div>
  </div>
  <div class="position-info">
    <p>Joystick Position</p>
    <p>X: {position.x.toFixed(2)}</p>
    <p>Y: {position.y.toFixed(2)}</p>
  </div>
</div>

<style>
  .container {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
  }
  .joystick {
    position: relative;
    width: 4rem;
    height: 4rem;
    background-color: #e2e8f0;
    border-radius: 50%;
    box-shadow: inset 0 0 10px rgba(0, 0, 0, 0.1);
    cursor: pointer;
  }
  .knob {
    position: absolute;
    width: 4rem;
    height: 4rem;
    background-color: #3b82f6;
    border-radius: 50%;
    box-shadow: 0 0 5px rgba(0, 0, 0, 0.2);
    transition: transform 75ms ease-out;
  }
  .position-info {
    margin-top: 2rem;
    text-align: center;
  }
  .position-info p {
    font-size: 1.25rem;
    font-weight: 600;
  }
</style>
