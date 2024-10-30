import Lightbulb from "./components/icons/lightbulb.svelte";
import TriangleAlert from "./components/icons/triangle-alert.svelte";
import AudioLines from "./components/icons/audio-lines.svelte";
import ArrowLeft from "./components/icons/arrow-left.svelte";
import ArrowRight from "./components/icons/arrow-right.svelte";
import Power from "./components/icons/power.svelte";
import Gamepad from "./components/icons/gamepad.svelte";
import Flame from "./components/icons/flame.svelte";
import type { Component } from "svelte";
import Joystick from "./components/icons/joystick.svelte";

type RGB = `rgb(${number}, ${number}, ${number})`;
type RGBA = `rgba(${number}, ${number}, ${number}, ${number})`;
type HEX = `#${string}`;

type Color = RGB | RGBA | HEX;

export interface GamepadButton {
  label: string;
  gpio: string;
  icon: Component;
  favouredColor?: Color;
  isPush?: boolean;
}

const colors = {
  red: "#dc2626",
  yellow: "#f59e0b",
  darkBlue: "#1e3a8a",
} as const satisfies Record<string, Color>;

export const buttonMappings: GamepadButton[] = [
  {
    label: "Lights",
    gpio: "a",
    icon: Lightbulb,
    favouredColor: colors.darkBlue,
  },
  {
    label: "Hazard",
    gpio: "a",
    icon: TriangleAlert,
  },
  {
    label: "Horn",
    gpio: "a",
    icon: AudioLines,
    isPush: true,
  },

  {
    label: "Power",
    gpio: "a",
    icon: Power,
    favouredColor: colors.red,
  },
  {
    label: "Flame",
    gpio: "a",
    icon: Flame,
  },
  {
    label: "Joystick",
    gpio: "a",
    icon: Joystick,
  },
  {
    label: "LeftL",
    gpio: "a",
    icon: ArrowLeft,
    favouredColor: colors.yellow,
  },
  {
    label: "RightL",
    gpio: "a",
    icon: ArrowRight,
    favouredColor: colors.yellow,
  },
];
