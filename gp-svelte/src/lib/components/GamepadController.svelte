<script lang="ts">
  import { onMount } from "svelte";
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import nipplejs from "nipplejs";

  let vertical = $state({ x: 0, y: 0 });
  let horizontal = $state({ x: 0, y: 0 });

  let v = $derived({
    x: Math.round(horizontal.x * 100),
    y: Math.round(vertical.y * 100),
  });

  $effect(() => {
    speedStore.set(v.y);
  });

  $effect(() => {
    angularVelocityStore.set(v.x);
  });

  let left = $state<HTMLElement | null>(null);
  let right = $state<HTMLElement | null>(null);

  onMount(() => {
    const joystickL = nipplejs.create({
      zone: left as HTMLElement,
      mode: "static",
      position: { left: "20%", top: "50%" },
      color: "green",
      lockX: true,
      size: 100,
    });
    joystickL.on("move", (_, data) => {
      horizontal = data.vector;
    });

    joystickL.on("end", () => {
      horizontal = { x: 0, y: 0 };
    });

    const joystickR = nipplejs.create({
      zone: right as HTMLElement,
      mode: "static",
      position: { left: "80%", top: "50%" },
      color: "red",
      lockY: true,
      size: 100,
    });
    joystickR.on("move", (_, data) => {
      vertical = data.vector;
    });

    joystickR.on("end", () => {
      vertical = { x: 0, y: 0 };
    });
  });
</script>

<div class="gamepad-container relative">
  <div class="absolute top-2 left-2">
    <span>X: {v.x}</span>
    <span>Y: {v.y}</span>
  </div>
  <div class="relative size-full">
    <div bind:this={left}></div>
    <div bind:this={right}></div>
  </div>
</div>

<style lang="postcss">
  .gamepad-container {
    @apply size-full;
  }
</style>
