<script lang="ts">
  import Joy from "./Joy.svelte";

  let x1 = $state(0);
  let y1 = $state(0);

  let x2 = $state(0);
  let y2 = $state(0);

  const radius = 80;
</script>

GAMEPAD
<div>
  <Joy oneAxis="x" {radius} x_coordinate={x1} y_coordinate={y1} />
  <Joy oneAxis="y" {radius} x_coordinate={x2} y_coordinate={y2} />
</div>

<style lang="postcss">
  div {
    @apply flex flex-row;
  }
</style>
