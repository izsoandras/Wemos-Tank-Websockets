<script lang="ts">
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import Joy from "./Joy.svelte";

  let vertical = $state({ x: 0, y: 0 });
  let horizontal = $state({ x: 0, y: 0 });

  const radius = 50;

  $effect(() => {
    speedStore.set(((vertical.y * (100 / radius)) / 100) * -1);
  });

  $effect(() => {
    angularVelocityStore.set((horizontal.x * (100 / radius)) / 100);
  });

  let parent = $state<HTMLDivElement | null>(null);
  const pads = 2;
  let width = $state(0);

  $effect(() => {
    window.innerWidth;
    if (parent) {
      width = parent.offsetWidth / pads;
    }
  });

  $inspect(parent?.offsetWidth);
</script>

<span>X: {horizontal.x}</span>
<span>Y: {vertical.y * -1}</span>

<div class="gamepad-container" bind:this={parent}>
  {#if parent}
    <Joy parentWidth={width} oneAxis="x" {radius} bind:outputCoord={vertical} />
    <Joy
      parentWidth={width}
      oneAxis="y"
      {radius}
      bind:outputCoord={horizontal}
    />
  {/if}
</div>

<style lang="postcss">
  .gamepad-container {
    @apply flex flex-row w-full;
  }
</style>
