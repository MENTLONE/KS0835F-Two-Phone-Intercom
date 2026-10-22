# Bill of Materials

## A. Proven two-phone prototype

| Item | Quantity | Notes |
|---|---:|---|
| Arduino UNO R4 Minima | 1 | Main prototype controller |
| Gadget Reboot KS0835F SLIC breakout board | 2 | One per phone; [source and schematic](https://github.com/GadgetReboot/KS0835F_Phone_SLIC) |
| Corded analog telephone | 2 | One per SLIC board |
| Breadboard / prototyping board | 1 | For low-voltage control and power distribution where suitable |
| Jumper wires | Assortment | F/R, RM, SHK, ground |
| Telephone cable, jack, and terminations | As required | Match the phone and chosen connection method |
| Regulated SLIC supply | 1 | Match voltage and current requirements from the SLIC documentation |
| USB data cable | 1 | Uploads sketch and powers Arduino |
| Enclosure / strain relief | Optional, recommended | For safer finished installation |

Exact connectors, cable lengths, and power-supply selection depend on your build. Consult the [upstream SLIC project](https://github.com/GadgetReboot/KS0835F_Phone_SLIC) and verify board requirements before applying power.

## B. Preliminary 10-house plan — NOT BUILD-VALIDATED

Assumption: ten extension phones total, retaining the two existing phones and SLIC boards. Initial goal: one active call at a time.

| Item | Planning quantity | Notes |
|---|---:|---|
| Arduino Mega 2560 Rev3 or other selected controller | 1 | Candidate only; needs enough I/O and correctly designed control logic |
| KS0835F SLIC boards | 10 total (8 additional) | Verify power, ringing, and board limitations before purchase |
| Corded analog telephones | 10 total (8 additional) | Phone compatibility and dialing method need definition |
| Analog audio switching matrix | 1 engineered system | Must route selected caller/recipient audio; topology not selected yet |
| Matrix control/driver hardware | To be designed | Depends on audio switch technology |
| Ringing and line power subsystem | 1 engineered system | Design around all line interfaces and expected ringing load |
| Regulated power distribution | 1 engineered system | Size only after confirming real SLIC requirements and measuring/estimating load |
| Cable drops, jacks, terminal blocks | 10 house connections plus exchange wiring | Depends on home-run vs shared-trunk layout and cable lengths |
| Line protection and isolation | To be engineered | Requirements depend on selected topology, cable length, and environment |
| Enclosure and mounting hardware | 1 set | Central exchange cabinet |
| Test equipment and spare connectors | As needed | Multimeter, insulated test leads, spare wire/connectors |

### Do not purchase the ten-line parts from this estimate alone

The multi-house system is still a design concept. Do not assume a ten-line design automatically needs 45 relays, and do not size the power supply by multiplying the prototype supply. First design and review the audio matrix, call architecture, line supply/ringing, protection/isolation, and wiring plan.
