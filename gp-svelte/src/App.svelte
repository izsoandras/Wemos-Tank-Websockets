<script lang="ts">
  import "./app.css";

  import ButtonPanel from "./lib/components/ButtonPanel.svelte";
  import Gamepad from "./lib/components/Gamepad.svelte";
  import Joy from "./lib/components/Joy.svelte";

  import { customWsStore } from "./lib/stores/ws";
  import { controllerStore } from "./lib/stores/controller";

  $inspect($customWsStore).with(console.debug);
</script>

<div
  class="h-svh min-h-svh w-svw overflow-y-clip overflow-x-clip p-2 flex flex-col justify-between"
>
  <nav>
    <ButtonPanel />
  </nav>

  {#if $controllerStore === "joy"}
    <Joy />
  {/if}
  {#if $controllerStore === "gamepad"}
    <Gamepad />
  {/if}
</div>
