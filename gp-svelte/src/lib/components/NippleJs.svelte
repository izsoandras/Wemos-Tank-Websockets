<script lang="ts">
  import nipplejs from "nipplejs";
  import { onMount } from "svelte";

  type Props = {
    vector: { x: number; y: number };
  } & Pick<nipplejs.JoystickManagerOptions, "lockX" | "lockY" | "position">;

  let { vector = $bindable(), lockX, lockY, position }: Props = $props();
  let joystickDiv = $state<HTMLElement | null>(null);

  let hasInstance = $state(false);

  onMount(() => {
    const joystick = nipplejs.create({
      zone: joystickDiv as HTMLElement,
      mode: "semi",
      color: "red",
      restJoystick: true,
      size: 100,
      catchDistance: 30,
      shape: "square",
      lockX,
      lockY,
    });
    joystick.on("move", (_, data) => {
      vector = data.vector;
    });
    joystick.on("end", () => {
      vector = { x: 0, y: 0 };
    });
    joystick.on("start", () => {
      if (!hasInstance) {
        hasInstance = true;
      }
    });
  });
</script>

{#if !hasInstance}
  <div class="absolute">Tap and drag anywhere to start</div>
{/if}

<div class="select-none size-full" bind:this={joystickDiv}></div>
