# Dom's KBD67 Rev2 Layout

This layout was created for the KBD67 Rev2 (KBD65 v2 PCB) in a TOFU65 case.
This means there is no blocker, for a total of 68 Keys.

## Notes

There's emphasis on one-handed actions in this layout, as I often find myself with a mouse in one hand, typing quick commands with the other.
There's a MO(1) at the bottom right of the layout, as well as when holding Capslock on the left. Some actions are repeated on the funtion layer on either the left or right side, so they can be executed with one hand.

Since the RGB backlight bleeds through the plate a little bit, I've used some colors to identify modes. Default layer, function layer, media layer, Capslock active, and Reset/Flashing colors can all be set individually.


## Features / Macros
- Double-tap ESC for Lock Screen (Win+L)
- Double-tap single quote (') for double quote (")
- Left Shift when held, ( when tapped
- Right Shift when held, ) when tapped
- Braces and brackets swapped. Unmodified = {}, Shift = []
- Tap for Capslock, hold for Layer
- Phrases
- WinOpen: Open Programs (WinKey, Send_string, Enter)
- Single button copy paste
- Super Alt Tab
- Copy, New tab, Enter Command

## Customizations

I've separated any values that I believe will be different for everyone into the `customizations.h` file. In this file you can specify your phrases, programs for WinOpen, and set default RGB values.

## Activating Macros and Features

| Activation             | Type      | Action                                    |
|------------------------|-----------|-------------------------------------------|
| Double-Tap `'`         | Tap Dance | Outputs `"`                               |
| Double-Tap `ESC`       | Tap Dance | Locks Screen                              |
| Single-Tap Left Shift  | Quantum   | Outputs `(`                               |
| Single-Tap Right Shift | Quantum   | Outputs `)`                               |
| MO(1) + d              | Macro     | Sends `Phrase1`, taps Tab                 |
| MO(1) + Shift + d      | Macro     | Sends `Phrase2`, taps Tab                 |
| MO(1) + Ctrl + d       | Macro     | Sends `Phrase3`, taps Enter               |
| MO(1) + n              | Macro     | Taps WinKey, Sends `WinOpen1`, taps Enter |