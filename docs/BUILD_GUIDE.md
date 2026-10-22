# Build Guide — Two-Phone Prototype

This guide describes the author's reported working prototype. Board revisions and telephone models can differ, so verify all signals against the labels and the upstream schematic.

**SLIC board source and schematic:** [Gadget Reboot — KS0835F Phone SLIC](https://github.com/GadgetReboot/KS0835F_Phone_SLIC)

## Parts
See [BOM.md](BOM.md). The core build uses one Arduino UNO R4 Minima, two KS0835F SLIC breakout boards, two corded analog telephones, wiring, and an appropriate regulated low-voltage supply.

## 1. Power down first
Disconnect the SLIC power supply and Arduino USB before changing any wiring. Telephone ringing circuits can generate hazardous voltage. Read [SAFETY.md](SAFETY.md).

## 2. Control wiring

Use the **signal labels** on the boards, not assumed header pin positions.

| SLIC signal | Board A → Arduino | Board B → Arduino |
|---|---|---|
| F/R | D2 | D5 |
| RM | D3 | D6 |
| SHK | D4 | D7 |
| GND | Common GND | Common GND |

The two SLIC boards and Arduino must share a signal-ground reference for the logic inputs/outputs. Power the Arduino by USB as in the tested setup. Do not connect an external +5 V rail to the Arduino 5V pin while USB-powered unless the power arrangement has been deliberately designed and verified.

The prototype's external breadboard module powered the SLIC boards. Check its voltage/current rating and the breakout requirements; do not assume the same supply is suitable for a larger network.

## 3. Telephone-line and audio wiring

Connect each telephone to its own SLIC board using the board's documented line terminals. The original prototype used a telephone jack for each phone; verify the pair and pinout for your jack and phone.

With power disconnected, cross-connect the audio:
- Board A **AOUT** → Board B **AIN**
- Board B **AOUT** → Board A **AIN**

Use the upstream [KS0835F schematic](https://github.com/GadgetReboot/KS0835F_Phone_SLIC) to verify any coupling capacitors or other parts required for your exact breakout revision.

## 4. Upload the sketch

1. Install Arduino IDE.
2. Open `firmware/KS0835F_TwoPhone_Intercom/KS0835F_TwoPhone_Intercom.ino`.
3. Connect an Arduino UNO R4 Minima using USB.
4. Select **Arduino UNO R4 Minima** under Tools → Board.
5. Choose the correct COM port.
6. Upload.
7. Open Serial Monitor at **9600 baud**.

## 5. Test in stages

1. **Idle:** Leave both handsets on-hook. The serial output should report each SHK as LOW and state IDLE once readings stabilize.
2. **Hook detection:** Pick up Phone A, confirm A SHK becomes HIGH, then hang up and confirm it returns LOW. Repeat for Phone B.
3. **A calls B:** Pick up A. Verify B rings and that ringing stops when B is picked up.
4. **B calls A:** Hang up both phones, then repeat starting from B.
5. **Two-way audio:** With both handsets picked up in the tested configuration, verify that both people can hear and speak to one another.
6. **Release:** Hang up and confirm both SHK signals return to on-hook and the controller returns to IDLE without resetting.

On the author's setup, SHK uses `INPUT_PULLUP`: LOW = on-hook, HIGH = off-hook. This should be verified on every new assembly.

## Troubleshooting

See [TROUBLESHOOTING.md](TROUBLESHOOTING.md). Change one thing at a time and power down before rewiring.
