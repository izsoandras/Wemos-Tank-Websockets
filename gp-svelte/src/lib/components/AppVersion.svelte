<script lang="ts">
  import { customWsStore } from "../stores/ws";

  const version = APP_VERSION;

  const connected = $derived(
    $customWsStore.connected ? "connected" : "offline"
  );
</script>

<div class="absolute bottom-0 right-0 p-1">
  <span>{connected}</span>
  <span>v{version}</span>
</div>
