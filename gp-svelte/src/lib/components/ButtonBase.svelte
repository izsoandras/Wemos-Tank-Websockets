<script lang="ts">
  import type { Component } from "svelte";

  interface Props {
    activeColor?: string;
    active: boolean;
    handleClick: () => void;
    label: string;
    icon: Component;
    blinking?: boolean;
  }

  let {
    active,
    activeColor = "#555",
    handleClick,
    label,
    icon,
    blinking,
  }: Props = $props();

  const ButtonIcon = $derived(icon);
</script>

<button
  style="--activeColor:{activeColor};"
  class:active
  class:inactive={!active}
  onclick={handleClick}
  class:blinking={active && blinking}
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

  .blinking {
    animation: blink 1s infinite;
  }

  .inactive {
    @apply bg-gray-900;
  }

  @keyframes blink {
    0% {
      background-color: #000;
    }
    50% {
      background-color: var(--activeColor);
    }
    100% {
      background-color: #000;
    }
  }
</style>
