<script lang="ts">
  import "./app.css";

  import ButtonPanel from "./lib/components/ButtonPanel.svelte";
  import Joypad from "./lib/components/Joypad.svelte";

  import { customWsStore } from "./lib/stores/app";

  let uiMode = $state<"joy" | "gamepad">("joy");

  $inspect($customWsStore);

  function sendMessage() {
    customWsStore.sendMessage();
  }
</script>

<div
  class="h-svh min-h-svh w-svw overflow-y-clip p-2 flex flex-col justify-between"
>
  <nav>
    <ButtonPanel />
  </nav>
  <button
    class="bg-black p-1 text-white rounded-lg"
    onclick={() => sendMessage()}>Send</button
  >
  {#if uiMode === "joy"}
    <Joypad />
  {/if}
  {#if uiMode === "gamepad"}
    <p>gamepad</p>
  {/if}
</div>
