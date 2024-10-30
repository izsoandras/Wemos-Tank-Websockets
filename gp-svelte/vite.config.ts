import { defineConfig } from "vite";
import { svelte } from "@sveltejs/vite-plugin-svelte";
import { visualizer } from "rollup-plugin-visualizer";

// https://vite.dev/config/
export default defineConfig({
  plugins: [
    svelte(),
    visualizer({
      emitFile: true,
      filename: "stats.html",
    }),
  ],
  build: {
    rollupOptions: {
      output: {
        manualChunks: {
          svelte: ["svelte"],
        },
      },
    },
  },
});
