<script lang="ts">
  import type { GamepadButton } from "../constants";
  import { buttonStore } from "../stores/buttons";
  import ButtonBase from "./ButtonBase.svelte";

  type Props = GamepadButton;

  let { label, icon, favouredColor, customOnClick, isFlashing }: Props =
    $props();

  const activeColor = favouredColor ?? "#2563eb";
  let active = $state(false);

  function handleClick() {
    active = !active;
    buttonStore.set(label, active);
  }
</script>

<ButtonBase
  {active}
  {activeColor}
  {handleClick}
  {label}
  {icon}
  blinking={isFlashing}
/>
