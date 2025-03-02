<script lang="ts">
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import NippleJs from "./NippleJs.svelte";

  let outputCoord = $state({ x: 0, y: 0 });

  let v = $derived({
    x: Math.round(outputCoord.x * 1000) / 1000,
    y: Math.round(outputCoord.y * 1000) / 1000,
  });

  $effect(() => {
    speedStore.set(v.y);
  });

  $effect(() => {
    angularVelocityStore.set(v.x * -1);
  });
</script>

<div class="relative">
  <p class="coordinates">
    X: <span>{v.x.toFixed(3)}</span> Y:
    <span>{v.y.toFixed(3)}</span>
  </p>
</div>

<div class="flex flex-row relative size-full">
  <div class="size-full">
    <NippleJs bind:vector={outputCoord} />
  </div>
</div>

<style lang="postcss">
  .coordinates {
    position: absolute;
    top: 0;
    right: 0;
    z-index: 50;
    background-color: rgba(255, 255, 255, 0.5);
    padding: 0.5rem;
  }
</style>
