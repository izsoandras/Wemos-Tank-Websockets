<script lang="ts">
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import Joy from "./Joy.svelte";

  let vertical = $state({ x: 0, y: 0 });
  let horizontal = $state({ x: 0, y: 0 });

  const radius = 100;

  $effect(() => {
    speedStore.set((vertical.y / 100) * -1);
  });

  $effect(() => {
    angularVelocityStore.set(horizontal.x / 100);
  });
</script>

<div>
  <Joy oneAxis="x" {radius} bind:outputCoord={vertical} />
  <Joy oneAxis="y" {radius} bind:outputCoord={horizontal} />
</div>

<style lang="postcss">
  div {
    @apply flex flex-row;
  }
</style>
