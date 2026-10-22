# Safety Notes

**Read before wiring or powering the telephone-line circuitry.** Ringing voltage may be hazardous even though the control electronics are low voltage.

- Do not touch exposed telephone-line terminals while the system is powered.
- Power down the SLIC supply and disconnect Arduino USB before changing line, audio, or control wires.
- Keep the circuit dry and away from conductive surfaces. Enclose the circuit and use strain relief for a finished installation.
- Do not connect this prototype to the public telephone network or an existing building telephone network.
- Arduino GPIO pins are logic signals only. Never use them to power telephone ringers, relay coils, or other loads directly.
- Do not assume a small USB breadboard supply has enough current for multiple SLIC boards or repeated/prolonged ringing. Check ratings and actual loads.
- Use the original [KS0835F SLIC schematic](https://github.com/GadgetReboot/KS0835F_Phone_SLIC) for board-specific pins and support components.
- A multi-house system needs a reviewed design for line power, ringing, fault/overcurrent protection, line isolation, cabling, and enclosure safety. Obtain qualified review before permanent installation.

This is an experimental hobby build, not a certified residential or commercial telephone distribution system.
