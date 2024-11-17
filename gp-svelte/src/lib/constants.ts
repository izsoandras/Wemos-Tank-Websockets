import type { Component } from "svelte";
import TriangleAlert from "./components/icons/triangle-alert.svelte";
import AudioLines from "./components/icons/audio-lines.svelte";
import ArrowLeft from "./components/icons/arrow-left.svelte";
import ArrowRight from "./components/icons/arrow-right.svelte";
import Joystick from "./components/icons/joystick.svelte";
import LowBeam from "./components/icons/low-beam.svelte";
import HighBeam from "./components/icons/high-beam.svelte";
import { controllerStore } from "./stores/controller";
import Auto from "./components/icons/auto.svelte";

type RGB = `rgb(${number}, ${number}, ${number})`;
type RGBA = `rgba(${number}, ${number}, ${number}, ${number})`;
type HEX = `#${string}`;

type Color = RGB | RGBA | HEX;

export type ButtonTypes =
  | "LowBeam"
  | "HighBeam"
  | "AutoLights"
  | "Horn"
  | "Emergency"
  | "LeftSignal"
  | "RightSignal"
  | "AutoSignal";

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
  green: "#008000",
} as const satisfies Record<string, Color>;

export const buttonMappings: GamepadButton[] = [
  {
    label: "LowBeam",
    gpio: 0,
    icon: LowBeam,
    favouredColor: colors.green,
  },
  {
    label: "HighBeam",
    gpio: 1,
    icon: HighBeam,
    favouredColor: colors.darkBlue,
  },
  {
    label: "AutoLights",
    gpio: 2,
    icon: Auto,
  },
  {
    label: "Horn",
    gpio: 3,
    icon: AudioLines,
  },
  {
    label: "Emergency",
    gpio: 4,
    icon: TriangleAlert,
    favouredColor: colors.red,
  },
  {
    label: "LeftSignal",
    gpio: 5,
    icon: ArrowLeft,
    favouredColor: colors.yellow,
  },
  {
    label: "RightSignal",
    gpio: 6,
    icon: ArrowRight,
    favouredColor: colors.yellow,
  },
  {
    label: "AutoSignal",
    gpio: 7,
    icon: Auto,
    favouredColor: colors.yellow,
  },
];
