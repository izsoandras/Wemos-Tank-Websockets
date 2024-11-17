<script lang="ts">
  import JoyStickIcon from "./icons/joystick.svelte";
  import GamepadIcon from "./icons/gamepad.svelte";
  import ButtonBase from "./ButtonBase.svelte";
  import type { Component } from "svelte";
  import { controllerStore } from "../stores/controller";
  import type { InputDeviceType } from "../stores/controller";

  type ConfigProps = {
    label: string;
    icon: Component;
  };

  const input: Record<InputDeviceType, ConfigProps> = {
    joypad: {
      label: "Joypad",
      icon: JoyStickIcon,
    },
    gamepad: {
      label: "Gamepad",
      icon: GamepadIcon,
    },
  };

  let value = $derived($controllerStore);
  let config = $derived(input[value]);

  function handleClick() {
    controllerStore.toggle();
  }
</script>

<ButtonBase
  active={false}
  label={config.label}
  icon={config.icon}
  {handleClick}
/>
