const isDev = import.meta.env.DEV;

export const CONFIG = {
  isDev,
  interval: !isDev ? 150 : 2000,
};
