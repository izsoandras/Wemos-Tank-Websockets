# Web ui

Use npm or bun.

## Install packages

`npm i / bun i`

## Start devserver

`npm run dev / bun run dev`

## Start dummy Websocket server

`node server.js / bun run ws-server`

## How to deploy?

```sh
# with nodejs
npm i
npm run build

# with bun
bun i
bun run build
```

and then copy the content of the `/dist` folder whereever you want. The most simpliest config should be enough to serve the `index.html` and the client will load the files under the `/assets` folder.
