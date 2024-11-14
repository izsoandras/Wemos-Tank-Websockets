import { writable } from "svelte/store";
import type { ButtonTypes } from "../constants";

const defaults = {
  AutoSignal: false,
  AutoLights: false,
  HighBeam: false,
  LowBeam: false,
  Horn: false,
  Joystick: false,
  LeftSignal: false,
  RightSignal: false,
} as Record<ButtonTypes, boolean>;

function createButtonsStore() {
  const { set, subscribe, update } =
    writable<Record<ButtonTypes, boolean>>(defaults);

  const setButton = (button: ButtonTypes, value?: boolean) => {
    update((v) => {
      let obj = {
        ...v,
        [button]: value,
      };
      return obj;
    });
  };

  return {
    subscribe,
    set: setButton,
    reset: () => set(defaults),
  };
}

export const buttonStore = createButtonsStore();
