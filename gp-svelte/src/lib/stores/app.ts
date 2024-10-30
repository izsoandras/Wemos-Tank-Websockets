import { readable, writable } from "svelte/store";

interface AppState {
  connected: boolean;
  error: boolean;
}

export const socketStore = readable({}, (set) => {
  const uri = import.meta.env.VITE_WS_SERVER as string;
  const socket = new WebSocket(uri);

  socket.addEventListener("open", (event) => {
    set({ message: "<client>: Connection Open" });
  });

  socket.addEventListener("message", (event) => {
    const data = JSON.parse(event.data);
    set(data);
  });

  return () => {
    socket.close();
  };
});
