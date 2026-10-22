# KS0835F Two-Phone Intercom

A DIY private analog telephone intercom built with two Gadget Reboot KS0835F SLIC breakout boards, two corded analog telephones, and an Arduino UNO R4 Minima.

**SLIC PCB source, schematic, and board details:** [Gadget Reboot KS0835F Phone SLIC](https://github.com/GadgetReboot/KS0835F_Phone_SLIC)

## Status
The two-phone prototype has been assembled and tested. A mock conversation was completed between both handsets, and hanging up returned the controller to idle automatically. The 10-house network is a future design concept only; it has not been built or validated.

## Hardware used
- 1 × Arduino UNO R4 Minima
- 2 × [KS0835F SLIC breakout boards](https://github.com/GadgetReboot/KS0835F_Phone_SLIC)
- 2 × analog corded telephones
- Breadboard/jumper wires, telephone cable/connectors, and suitable regulated low-voltage SLIC supply
- USB data cable for Arduino

## Repo layout
- `firmware/KS0835F_TwoPhone_Intercom/KS0835F_TwoPhone_Intercom.ino` — two-phone prototype sketch
- `docs/BUILD_GUIDE.md` — step-by-step assembly and testing
- `docs/BOM.md` — parts list and preliminary 10-house plan
- `docs/SAFETY.md` — line-voltage and wiring precautions
- `docs/TROUBLESHOOTING.md` — common issues
- `docs/TEN_HOUSE_ROADMAP.md` — future ten-house design notes

## Quick start
1. Read [Safety](docs/SAFETY.md) before wiring.
2. Follow the [Build Guide](docs/BUILD_GUIDE.md).
3. Open the `.ino` file in Arduino IDE and select **Arduino UNO R4 Minima**.
4. Upload and open Serial Monitor at **9600 baud**.
5. Test hook detection, ringing in both directions, conversation audio, and automatic return to idle.

## Tested prototype pin map
| Signal | Phone/SLIC A | Phone/SLIC B |
|---|---:|---:|
| F/R | D2 | D5 |
| RM | D3 | D6 |
| SHK | D4 | D7 |

SHK used `INPUT_PULLUP`. In the author's setup, LOW indicated on-hook and HIGH indicated off-hook. Verify this on your own board/phone combination.

## Audio wiring
With power disconnected: AOUT A → AIN B and AOUT B → AIN A. Confirm required coupling components in the [upstream KS0835F schematic](https://github.com/GadgetReboot/KS0835F_Phone_SLIC).

## Important limitations
- This code is for the proven two-phone UNO R4 prototype, not a ten-line PBX.
- Arduino GPIO must not directly power phone ringers or relay coils.
- Do not assume the prototype breadboard supply will support ten lines or prolonged ringing.
- Never connect this experimental circuit to a public telephone network or building telephone wiring.
- The ten-house plan still needs engineering for audio switching, ringing and line power, isolation/protection, and multi-call behavior.

## License
Software and documentation are covered by the MIT License in this repository. The upstream SLIC board files remain subject to the terms in the [Gadget Reboot repository](https://github.com/GadgetReboot/KS0835F_Phone_SLIC).
