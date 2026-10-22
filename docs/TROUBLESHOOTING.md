# Troubleshooting

## Serial output is unreadable or absent
- Set Serial Monitor to **9600 baud**.
- Confirm board selection is **Arduino UNO R4 Minima** and choose the correct COM port.
- Press reset once after opening the monitor if needed.

## SHK never changes
- Verify the board's SHK label and Arduino pin mapping: A uses D4; B uses D7.
- Confirm Arduino and SLIC grounds share a reference.
- Power down, inspect solder joints and header connections, then test one board at a time.
- Use the serial readings to verify actual logic levels; do not rely on assumed levels.

The tested setup used `INPUT_PULLUP`: LOW = on-hook, HIGH = off-hook. This may not hold for a modified board or different design.

## The other phone does not ring
- Check F/R and RM control connections.
- Confirm only one handset is off-hook to start a call.
- Read the serial log to see which board the sketch is trying to ring.
- Power off before changing wiring. Never probe exposed ringing terminals while powered.
- A short successful ring does not establish that the supply supports repeated or prolonged ringing.

## Ringing stops, but audio is missing or one-way
- Power off and verify AOUT A → AIN B and AOUT B → AIN A.
- Confirm the exact pin labels on both boards.
- Check the upstream SLIC schematic for required audio coupling components.
- Test directions separately and note which direction fails.
- Confirm both phones are off-hook during the conversation test.

## It does not return to idle
- Observe A SHK and B SHK in Serial Monitor.
- Put both phones fully on-hook and wait longer than the debounce interval.
- Check that the ringing control outputs are LOW after termination.
- If unresolved, save the serial log and inspect SHK wiring and solder joints.

## When opening an issue
Include Arduino board, SLIC revision, telephone model, supply model and rating, wiring changes, serial log, and the exact test that failed.
