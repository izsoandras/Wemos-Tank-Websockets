<script lang="ts">
  import Button from "./Button.svelte";
  import { buttonMappings } from "../constants";
  import InputDeviceButton from "./InputDeviceButton.svelte";
  import FullScreenButton from "./FullScreenButton.svelte";
</script>

<div class="flex h-full w-full flex-col justify-between">
  <div class="relative">
    <div class="buttonGrid">
      {#each buttonMappings.sort((a, b) => a.gpio - b.gpio) as buttonProps}
        <Button {...buttonProps} />
      {/each}
      <InputDeviceButton />
      <FullScreenButton />
    </div>
  </div>
</div>

<style lang="postcss">
  .buttonGrid {
    @apply grid gap-2 grid-cols-4 md:grid-cols-5 lg:grid-cols-6 xl:grid-cols-8;
  }
</style>
