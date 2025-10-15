# Microcontroller-Based-Washing-Machine-Simulation-using-PicsimLab
A washing machine simulation built using PicsimLab and PIC microcontroller, demonstrating embedded system design and control logic. The project replicates real washing machine functions like program selection, water level control, start/stop operations, and safety alerts — all within a virtual simulation environment.



The main objective is to **design and simulate a washing machine control system** that:
- Responds to user inputs (buttons and switches)
- Controls various washing cycles
- Displays system states on a simulated CLCD
- Implements safety features (door open detection, buzzer alert)
- Demonstrates automation logic in a virtual embedded environment

---

## ⚙️ Features Implemented

### 🟢 1. Power ON Screen
- Displays “Press Key5 to Power ON Washing Machine”  
- Waits for user input (SW5) to start

### 🔵 2. Washing Program Selection
- Multiple washing modes:  
  `Daily, Heavy, Delicates, Whites, Stain Wash, Eco Cottons, Woolens, Bed Sheets, Rinse+Dry, Dry Only, Wash Only, Aqua Store`
- Navigation using SW4; long press to select

### 🌊 3. Water Level Selection
- Options: `Auto, Low, Medium, High, Max`
- Scroll and select using SW4

### ▶️ 4. Start / Stop Control
- Start machine (SW5)
- Stop or go back to previous menu (SW6)

### 🔁 5. Function Display
- Shows the ongoing function (`Wash`, `Rinse`, `Spin`)
- Displays remaining time on CLCD
- Door status monitored via SW1 with buzzer alerts

### ✅ 6. Completion Screen
- Displays `"Program Completed. Remove Clothes"` once finished
