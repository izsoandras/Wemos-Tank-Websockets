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

export type ButtonTypes =
  | "Lights"
  | "Hazard"
  | "Horn"
  | "Power"
  | "Flame"
  | "Joystick"
  | "LeftSignal"
  | "RightSignal";

export interface GamepadButton {
  label: ButtonTypes;
  gpio: number;
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
    gpio: 0,
    icon: Lightbulb,
    favouredColor: colors.darkBlue,
  },
  {
    label: "Hazard",
    gpio: 1,
    icon: TriangleAlert,
  },
  {
    label: "Horn",
    gpio: 2,
    icon: AudioLines,
    isPush: true,
  },

  {
    label: "Power",
    gpio: 3,
    icon: Power,
    favouredColor: colors.red,
  },
  {
    label: "Flame",
    gpio: 4,
    icon: Flame,
  },
  {
    label: "Joystick",
    gpio: 5,
    icon: Joystick,
  },
  {
    label: "LeftSignal",
    gpio: 6,
    icon: ArrowLeft,
    favouredColor: colors.yellow,
  },
  {
    label: "RightSignal",
    gpio: 7,
    icon: ArrowRight,
    favouredColor: colors.yellow,
  },
];
