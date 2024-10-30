<script lang="ts">
  import type { GamepadButton } from "../constants";

  type Props = GamepadButton;

  let { label, icon, favouredColor, isPush }: Props = $props();

  const activeColor = favouredColor ?? "#2563eb";
  let active = $state(false);
  let ButtonIcon = icon;

  function handleClick() {
    if (isPush) {
      active = true;
      setTimeout(() => {
        active = false;
      }, 500);
      return;
    }

    active = !active;
  }
</script>

<button
  style="--activeColor:{activeColor};"
  class:active
  class:inactive={!active}
  onclick={handleClick}
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
