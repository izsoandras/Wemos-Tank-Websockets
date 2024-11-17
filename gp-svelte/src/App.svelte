<script lang="ts">
  import "./app.css";

  import ButtonsPanel from "./lib/components/ButtonsPanel.svelte";
  import GamepadController from "./lib/components/GamepadController.svelte";
  import JoyController from "./lib/components/JoyController.svelte";

  import { customWsStore } from "./lib/stores/ws";
  import { controllerStore } from "./lib/stores/controller";

  $inspect($customWsStore).with(console.debug);
</script>

<div
  class="h-svh min-h-svh w-svw overflow-y-clip overflow-x-clip p-2 flex flex-col justify-between"
>
  <nav>
    <ButtonsPanel />
  </nav>

  {#if $controllerStore === "joypad"}
    <JoyController />
  {/if}
  {#if $controllerStore === "gamepad"}
    <GamepadController />
  {/if}
</div>
