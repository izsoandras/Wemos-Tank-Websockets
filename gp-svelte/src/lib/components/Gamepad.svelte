<script lang="ts">
  let xPosition = $state<number>(0);
  let yPosition = $state<number>(0);
  const joystickSize = 60;
  const containerSize = 200;
  const maxDistance = (containerSize - joystickSize) / 2;

  function handleMouseDown(event, axis) {
    const moveJoystick = (e) => {
      const rect = e.target.getBoundingClientRect();
      const centerX = rect.left + rect.width / 2;
      const centerY = rect.top + rect.height / 2;

      if (axis === "x") {
        xPosition = Math.max(
          -maxDistance,
          Math.min(maxDistance, e.clientX - centerX)
        );
      } else {
        yPosition = Math.max(
          -maxDistance,
          Math.min(maxDistance, e.clientY - centerY)
        );
      }
    };

    const stopDrag = () => {
      window.removeEventListener("mousemove", moveJoystick);
      window.removeEventListener("mouseup", stopDrag);
      xPosition = 0;
      yPosition = 0;
    };

    window.addEventListener("mousemove", moveJoystick);
    window.addEventListener("mouseup", stopDrag);
  }

  function handleTouchStart(event, axis) {
    event.preventDefault();

    const moveJoystick = (e) => {
      const touch = e.touches[0];
      const rect = e.target.getBoundingClientRect();
      const centerX = rect.left + rect.width / 2;
      const centerY = rect.top + rect.height / 2;

      if (axis === "x") {
        xPosition = Math.max(
          -maxDistance,
          Math.min(maxDistance, touch.clientX - centerX)
        );
      } else {
        yPosition = Math.max(
          -maxDistance,
          Math.min(maxDistance, touch.clientY - centerY)
        );
      }
    };

    const stopDrag = () => {
      window.removeEventListener("touchmove", moveJoystick);
      window.removeEventListener("touchend", stopDrag);
      xPosition = 0;
      yPosition = 0;
    };

    window.addEventListener("touchmove", moveJoystick, { passive: false });
    window.addEventListener("touchend", stopDrag);
  }
</script>

<div class="flex space-x-8">
  <!-- svelte-ignore a11y_no_static_element_interactions -->
  <div
    class="relative bg-gray-300 rounded-full cursor-pointer"
    style="width: {containerSize}px; height: {containerSize}px;"
    onmousedown={(e) => handleMouseDown(e, "x")}
    ontouchstart={(e) => handleTouchStart(e, "x")}
  >
    <div
      class="absolute bg-blue-500 rounded-full transition-transform duration-50"
      style="width: {joystickSize}px; height: {joystickSize}px; top: 50%; left: 50%; transform: translate(calc(-50% + {xPosition}px), -50%);"
    ></div>
  </div>
  <!-- svelte-ignore a11y_no_static_element_interactions -->
  <div
    class="relative bg-gray-300 rounded-full cursor-pointer"
    style="width: {containerSize}px; height: {containerSize}px;"
    onmousedown={(e) => handleMouseDown(e, "y")}
    ontouchstart={(e) => handleTouchStart(e, "y")}
  >
    <div
      class="absolute bg-green-500 rounded-full transition-transform duration-50"
      style="width: {joystickSize}px; height: {joystickSize}px; top: 50%; left: 50%; transform: translate(-50%, calc(-50% + {yPosition}px));"
    ></div>
  </div>
</div>
<div class="mt-8 text-center">
  <p>X-axis: {xPosition.toFixed(2)}</p>
  <p>Y-axis: {yPosition.toFixed(2)}</p>
</div>
