<script lang="ts">
  import nipplejs from "nipplejs";
  import { onMount } from "svelte";

  type Props = {
    vector: { x: number; y: number };
  } & Pick<nipplejs.JoystickManagerOptions, "lockX" | "lockY" | "position">;

  let { vector = $bindable(), lockX, lockY, position }: Props = $props();
  let joystickDiv = $state<HTMLElement | null>(null);

  onMount(() => {
    const joystick = nipplejs.create({
      zone: joystickDiv as HTMLElement,
      mode: "static",
      color: "red",
      restJoystick: true,
      size: 150,
      position: { left: "50%", top: "50%" },
      lockX,
      lockY,
    });
    joystick.on("move", (_, data) => {
      vector = data.vector;
    });
    joystick.on("end", () => {
      vector = { x: 0, y: 0 };
    });
  });
</script>

<div class="select-none" bind:this={joystickDiv}></div>
