import { readable, writable } from "svelte/store";
import type { ButtonTypes } from "../constants";
import { buttonMappings } from "../constants";

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
  console.log(message);
  return new Uint8Array([0, 0, 0]);
}

const defaultValue: Message = {
  speed: true,
  angularVelocity: true,
  buttons: {
    LeftSignal: false,
    RightSignal: false,
    Flame: false,
    Hazard: false,
    Horn: false,
    Joystick: false,
    Lights: false,
    Power: false,
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

  const sendMessage = (data: Message) => {
    if (!socket) return;

    const message = mapAppMessageToWebsocketMessage(data);

    socket.send(message);
    console.log("data sent");
  };

  return {
    subscribe,
    sendMessage,
  };
}

export const customWsStore = createWsStore();
