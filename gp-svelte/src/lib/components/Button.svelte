<script lang="ts">
  import { CONFIG } from "../config";
  import type { GamepadButton } from "../constants";
  import { buttonStore } from "../stores/buttons";
  import ButtonBase from "./ButtonBase.svelte";

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

<ButtonBase {active} {activeColor} {handleClick} {label} {icon} />
