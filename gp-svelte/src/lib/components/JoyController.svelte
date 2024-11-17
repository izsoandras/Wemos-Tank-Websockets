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
    angularVelocityStore.set(v.x);
  });
</script>

<p class="coordinates">
  X: <span>{v.x}</span> Y:
  <span>{v.y}</span>
</p>

<div class="flex flex-row relative size-full">
  <NippleJs bind:vector={outputCoord} />
</div>
