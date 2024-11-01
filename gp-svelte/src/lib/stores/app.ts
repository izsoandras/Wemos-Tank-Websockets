import { get, writable } from "svelte/store";
import type { ButtonTypes } from "../constants";
import { buttonMappings } from "../constants";
import { buttonStore } from "./buttons";

interface AppState {
  connected: boolean;
  error: boolean;
}

type Message = {
  speed: any;
  angularVelocity: any;
  buttons: Record<ButtonTypes, boolean>;
};

type WebsocketMessage = Uint8Array;

function mapAppMessageToWebsocketMessage(message: Message): WebsocketMessage {
  const { buttons } = message;

  const buttonByte = Object.entries(buttons)
    .sort((a, b) => {
      const buttonA = buttonMappings.find((e) => e.label === a[0]);
      const buttonB = buttonMappings.find((e) => e.label === b[0]);

      return (buttonB?.gpio as number) - (buttonA?.gpio as number);
    })
    .map(([type, value]) => {
      const button = buttonMappings.find((e) => e.label === type);
      if (!button) throw Error("asd");
      const gpio = button?.gpio;

      return Number(value) << gpio;
    })
    .reduce((acc, curr) => {
      return acc | curr;
    }, 0);

  console.log(buttonByte.toString(2).padStart(8, "0"));

  return new Uint8Array([0, 0, buttonByte]);
}

const defaultValue: Message = {
  speed: true,
  angularVelocity: true,
  buttons: {
    Lights: true,
    Hazard: false,
    Horn: false,
    Power: true,
    Flame: false,
    Joystick: true,
    LeftSignal: false,
    RightSignal: false,
  },
};

export function createWsStore() {
  let socket: WebSocket | null = null;

  const { set, subscribe, update } = writable({}, (set) => {
    const uri = import.meta.env.VITE_WS_SERVER as string;
    const soc = new WebSocket(uri);
    soc.addEventListener("open", (event) => {
      set({ message: "<client>: Connection Open" });
    });

    soc.addEventListener("message", (event) => {
      const data = JSON.parse(event.data);
      set(data);
    });

    socket = soc;

    return () => {
      soc.close();
    };
  });

  const sendMessage = () => {
    if (!socket) return;

    const buttonStoreValues = get(buttonStore);

    const message = mapAppMessageToWebsocketMessage({
      ...defaultValue,
      buttons: buttonStoreValues,
    });

    socket.send(message);
    console.log("data sent");
  };

  return {
    subscribe,
    sendMessage,
  };
}

export const customWsStore = createWsStore();
