# Automatic inline-water-pressure-booster-esp32
Automatic inline water pressure booster system using ESP32 and YF-S201 flow sensor for domestic appliances, featuring demand-based activation, dry-run protection, and energy-efficient operation.

**Year:** 2025  
**Status:** R&D / Field-Tested Domestic System  
**Platform:** ESP32 DevKit V1  
**Operation:** Fully Offline (No Wi-Fi, No Cloud)

---

## Overview

This project implements an **automatic inline water pressure booster system** designed to compensate for **low municipal water pressure** in single-storey residential installations.

The system ensures reliable water delivery to **washing machines, geysers, and dishwashers** by intelligently detecting water demand and activating a low-power inline booster pump only when required.

The design prioritizes **pump safety, pressure stability, energy efficiency, and cost effectiveness**.

---

## Problem Statement

In many residential areas, municipal water pressure is insufficient to reliably operate modern domestic appliances.  
Commercial booster systems are often:
- Expensive
- Overpowered
- Energy inefficient
- Always-on, causing unnecessary wear

This project addresses these issues using **flow-based demand detection** and intelligent control logic.

---

## System Architecture

### Operating Principle

1. Appliance opens its inlet valve  
2. Water flow is detected by a **YF-S201 flow sensor**  
3. Controller waits **2 seconds** to confirm sustained demand  
4. Inline booster pump is energized via relay  
5. Pump runs only while water flow exists  
6. Pump shuts down immediately when flow stops  

This ensures **zero dry-run risk** and **no pressure surge**.

---

## Key Features

- Flow-based demand detection using YF-S201
- 2-second delayed pump activation to avoid false triggering
- Immediate pump shutdown on flow cessation
- Dry-run prevention by design
- Relay-isolated pump control
- Fully offline operation
- Extremely low power consumption
- Compact and retrofit-friendly design

---

## Control Logic Summary

| Event | Action |
|-----|-------|
| Flow detected | Start 2-second confirmation timer |
| Flow sustained after 2 seconds | Turn ON booster pump |
| Flow stops | Immediately turn OFF pump |
| No flow | Pump remains OFF |

This logic eliminates unnecessary starts and improves pump life.

---

## Hardware Used

### Controller
- ESP32 DevKit V1

### Sensor
- YF-S201 Hall-effect water flow sensor

### Actuation
- Relay module (opto-isolated recommended)
- 40 W inline booster pump

### Power
- Low-voltage DC supply for controller
- Mains AC isolated through relay

---

## Performance Results

- Achieved stable operating pressure for domestic appliances
- Reliable appliance operation under low municipal pressure
- Negligible impact on electricity consumption
- Approx. **5% of the cost** of commercial booster systems
- Silent and maintenance-friendly operation

---

## Safety Considerations

⚠ **IMPORTANT**

- Use proper electrical isolation for relay and pump
- Ensure correct grounding
- Do not exceed pump rated duty cycle
- Install non-return valve where required
- Follow local electrical and plumbing safety standards

The author assumes no liability for improper use.

---

## Project Status

- ✔ Designed and implemented  
- ✔ Field tested in residential environment  
- ✔ Stable long-term operation  
- ⚠ Experimental / non-certified system  

---

## Future Improvements

- Pressure sensor feedback for closed-loop control
- Adjustable delay and flow thresholds
- Soft-start motor control
- Compact enclosure design
- Reusable control module

---

## License

This project is licensed under the **Apache License 2.0**.  
See the `LICENSE` file for details.

---

## Author

**MD Hashim**  
Mechanical Engineer | Embedded Systems | Automation & Control
