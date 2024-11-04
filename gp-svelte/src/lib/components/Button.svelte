<script lang="ts">
  import { CONFIG } from "../config";
  import type { GamepadButton } from "../constants";
  import { buttonStore } from "../stores/buttons";

  type Props = GamepadButton;

  let { label, icon, favouredColor, isPush, customOnClick }: Props = $props();

  const activeColor = favouredColor ?? "#2563eb";
  let active = $state(false);
  let ButtonIcon = icon;

  let intervalId = $state<number | undefined>(undefined);

  function handleClick() {
    if (isPush) {
      if (intervalId) {
        clearTimeout(intervalId);
      }

      active = true;
      intervalId = setTimeout(() => {
        active = false;
      }, CONFIG.interval * 0.75);
      return;
    }

    active = !active;
    buttonStore.set(label, active);
  }
</script>

<button
  style="--activeColor:{activeColor};"
  class:active
  class:inactive={!active}
  onclick={customOnClick ?? handleClick}
>
  <ButtonIcon />
  <span>{label}</span>
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
