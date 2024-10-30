<script>
  import Button from "./Button.svelte";
  import { buttonMappings } from "../constants";
</script>

<div class="flex h-full w-full flex-col justify-between">
  <div class="relative">
    <div class="grid grid-cols-4 gap-2">
      {#each buttonMappings as buttonProps}
        <Button {...buttonProps} />
      {/each}
    </div>
  </div>
</div>
