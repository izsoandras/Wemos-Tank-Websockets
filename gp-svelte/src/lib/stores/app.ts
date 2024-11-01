import { get, writable } from "svelte/store";
import type { ButtonTypes } from "../constants";
import { buttonMappings } from "../constants";
import { buttonStore } from "./buttons";
import { CONFIG } from "../config";

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
  let intervalRunning: boolean = false;
  let intervalId: number | undefined = undefined;

  const { subscribe } = writable({}, (set) => {
    const uri = import.meta.env.VITE_WS_SERVER as string;
    const soc = new WebSocket(uri);
    soc.addEventListener("open", () => {
      set({ message: "<client>: Connection Open" });
      _startSendInterval();
    });

    soc.addEventListener("message", (event) => {
      const data = JSON.parse(event.data);
      set(data);
    });

    socket = soc;

    return () => {
      _stopSendInterval();
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
  };

  const _startSendInterval = () => {
    if (!intervalRunning) {
      intervalRunning = true;
      intervalId = setInterval(() => {
        if (socket && socket.readyState == WebSocket.OPEN) {
          sendMessage();
        }
      }, CONFIG.interval);
    }
  };

  const _stopSendInterval = () => {
    intervalRunning = false;
    clearInterval(intervalId);
  };

  return {
    subscribe,
    sendMessage,
  };
}

export const customWsStore = createWsStore();
