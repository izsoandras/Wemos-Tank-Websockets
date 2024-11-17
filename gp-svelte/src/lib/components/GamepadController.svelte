<script lang="ts">
  import { onMount } from "svelte";
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import nipplejs from "nipplejs";

  let vertical = $state({ x: 0, y: 0 });
  let horizontal = $state({ x: 0, y: 0 });

  /*
    v  =  (R + L) / 2
    w =  (R - L) / (2*d)
  */
  const d = 1.5;

  let v = $derived({
    v: Math.round(((vertical.y - horizontal.x) / 2) * 1000) / 1000,
    w: Math.round(((vertical.y + horizontal.x) / (2 * d)) * 1000) / 1000,
  });

  $effect(() => {
    speedStore.set(v.v);
  });

  $effect(() => {
    angularVelocityStore.set(v.w);
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
    <span>velocity: {v.v}</span>
    <span>circular: {v.w}</span>
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
