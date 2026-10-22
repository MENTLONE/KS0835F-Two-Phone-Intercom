# Ten-House Exchange Roadmap

**Status: proposed only.** The verified build in this repository is the two-phone prototype. A ten-house system has not yet been assembled or validated.

## Goal

A private wired exchange for ten house extensions. For the first multi-line prototype, start with one active conversation at a time:

1. A caller goes off-hook.
2. The caller chooses an extension (dial interface not yet implemented).
3. The destination line rings.
4. Answering stops the ringing and connects bidirectional audio.
5. When either party hangs up, the audio path is disconnected and the exchange returns to idle.

The current sketch starts ringing the opposite phone based on which handset is lifted. It does **not** implement extension dialing, destination selection, busy tones, or multiple independent calls.

## Candidate controller: Arduino Mega 2560 Rev3

The Mega is a reasonable candidate for line-status and control tasks because it has more GPIO than the UNO. If each KS0835F line uses F/R, RM, and SHK, ten lines nominally use 30 digital control pins before adding keypad, indicators, and matrix control. Confirm exact electrical requirements and I/O plans first.

A Mega does not replace:
- An analog audio crosspoint or switching matrix
- A designed telephone-line/ringing power system
- Line isolation and protection
- Tested firmware for ten-line call arbitration

## Engineering milestones

1. Confirm exact specifications and limitations of all SLIC boards.
2. Choose an audio switching topology and document its signal path.
3. Decide whether the first version supports only one call at a time.
4. Engineer line power and ringing, including isolation and protection.
5. Choose a cabling topology: home runs to a central exchange or a shared trunk.
6. Implement and independently test hook detection on each line.
7. Add extension selection, busy/invalid extension behavior, and call-state transitions.
8. Add audio path setup/teardown and robust recovery on caller or recipient hang-up.
9. Verify one line at a time before connecting the full bank of phones.
10. Publish measured tests and update the documents only after validation.

## Audio switching count is not yet fixed

There are 45 unique extension pairs among ten houses (10 × 9 / 2). This does **not** imply that the correct design requires 45 relays: actual quantity depends on the selected matrix topology, isolation, and supported simultaneous calls. Select and review the architecture before buying matrix parts.

## Status checklist

- [x] Two-phone hook detection and ringing demonstrated
- [x] Two-way audio conversation demonstrated on the prototype
- [x] Automatic return to idle observed
- [ ] Select the ten-line audio matrix architecture
- [ ] Design and verify line supply, ringing, and protection
- [ ] Prototype three lines
- [ ] Implement extension dialing and busy handling
- [ ] Expand to ten lines and publish validated test results
