<script lang="ts">
  import { angularVelocityStore, speedStore } from "../stores/controller";
  import Joy from "./Joy.svelte";

  let x = $state<number>(0);
  let y = $state<number>(0);

  $inspect(x);

  $effect(() => {
    speedStore.set((y / 100) * -1);
  });

  $effect(() => {
    angularVelocityStore.set(x / 100);
  });
</script>

JOY
<Joy showValues x_coordinate={x} y_coordinate={y} />
