<script lang="ts">
  import { onMount } from "svelte";
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import nipplejs from "nipplejs";

  let joyRightValue = $state({ x: 0, y: 0 });
  let joyLeftValue = $state({ x: 0, y: 0 });

  /*
    v  =  (R + L) / 2
    w =  (R - L) / (2*d)
  */
  const d = 1.5;

  let v = $derived({
    v: Math.round(((joyRightValue.y + joyLeftValue.y) / 2) * 1000) / 1000,
    w: Math.round(((joyRightValue.y - joyLeftValue.y) / (2 * d)) * 1000) / 1000,
  });

  $effect(() => {
    speedStore.set(v.v);
  });

  $effect(() => {
    angularVelocityStore.set(v.w);
  });

  let left = $state<HTMLElement | null>(null);
  let right = $state<HTMLElement | null>(null);

  const size = 100;

  onMount(() => {
    const joystickL = nipplejs.create({
      zone: left as HTMLElement,
      mode: "static",
      position: { left: "20%", top: "50%" },
      color: "green",
      lockY: true,
      size,
    });
    joystickL.on("move", (_, data) => {
      joyLeftValue = data.vector;
    });

    joystickL.on("end", () => {
      joyLeftValue = { x: 0, y: 0 };
    });

    const joystickR = nipplejs.create({
      zone: right as HTMLElement,
      mode: "static",
      position: { left: "80%", top: "50%" },
      color: "red",
      lockY: true,
      size,
    });
    joystickR.on("move", (_, data) => {
      joyRightValue = data.vector;
    });

    joystickR.on("end", () => {
      joyRightValue = { x: 0, y: 0 };
    });
  });
</script>

<div class="gamepad-container relative">
  <div class="absolute top-2 left-2">
    <span>velocity: {v.v.toFixed(3)}</span>
    <span>circular: {v.w.toFixed(3)}</span>
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
