import { readable, writable } from "svelte/store";

interface AppState {
  connected: boolean;
  error: boolean;
}

type WebsocketMessage = {
  message: string;
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

  const sendMessage = (data: WebsocketMessage) => {
    if (!socket) return;

    socket.send(JSON.stringify(data));
    console.log("data sent");
  };

  return {
    subscribe,
    sendMessage,
  };
}

export const customWsStore = createWsStore();
