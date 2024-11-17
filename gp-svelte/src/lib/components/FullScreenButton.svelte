<script>
  import ButtonBase from "./ButtonBase.svelte";
  import Maximize from "./icons/maximize.svelte";

  function handleClick() {
    if (!document.fullscreenElement) {
      document.documentElement.requestFullscreen();
      active = true;
    } else if (document.exitFullscreen) {
      document.exitFullscreen();
      active = false;
    }
  }

  let active = $state(!!document.fullscreenElement);
  const label = "Fullscreen";
  const activeColor = "#5E239D";
</script>

<ButtonBase {active} {activeColor} {label} {handleClick} icon={Maximize} />
