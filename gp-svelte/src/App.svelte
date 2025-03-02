<script lang="ts">
  import "./app.css";

  import ButtonsPanel from "./lib/components/ButtonsPanel.svelte";
  import GamepadController from "./lib/components/GamepadController.svelte";
  import JoyController from "./lib/components/JoyController.svelte";

  import { customWsStore } from "./lib/stores/ws";
  import { controllerStore } from "./lib/stores/controller";
  import AppVersion from "./lib/components/AppVersion.svelte";
</script>

<AppVersion />

<div
  class="h-svh min-h-svh w-svw overflow-y-clip overflow-x-clip p-2 flex flex-col justify-between"
>
  <nav>
    <ButtonsPanel />
  </nav>
  <div class="absolute bottom-0 left-0 z-50">
    {JSON.stringify($customWsStore)}
  </div>

  {#if $controllerStore === "joypad"}
    <JoyController />
  {/if}
  {#if $controllerStore === "gamepad"}
    <GamepadController />
  {/if}
</div>
