<script lang="ts">
  import type { Component } from "svelte";

  interface Props {
    activeColor?: string;
    active: boolean;
    handleClick: () => void;
    label: string;
    icon: Component;
  }

  let {
    active,
    activeColor = "#555",
    handleClick,
    label,
    icon,
  }: Props = $props();

  const ButtonIcon = $derived(icon);
</script>

<button
  style="--activeColor:{activeColor};"
  class:active
  class:inactive={!active}
  onclick={handleClick}
>
  <ButtonIcon />
  <span class="text-xs">{label}</span>
</button>

<style lang="postcss">
  button {
    @apply aspect-square flex flex-col items-center justify-center gap-1 rounded-md text-white transition-colors;
    filter: drop-shadow(0px 0px 2px #000);
  }

  .active {
    background-color: var(--activeColor);
  }

  .inactive {
    @apply bg-gray-900;
  }
</style>
