<script lang="ts">
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import Joy from "./Joy.svelte";

  let outputCoord = $state({ x: 0, y: 0 });

  $effect(() => {
    speedStore.set((outputCoord.y / 100) * -1);
  });

  $effect(() => {
    angularVelocityStore.set(outputCoord.x / 100);
  });
</script>

<Joy showValues bind:outputCoord />
