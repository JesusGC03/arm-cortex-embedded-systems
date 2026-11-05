# ARM Cortex-M3 (NXP LPC1768) Embedded Firmware & Peripherals

<div align="center">

![MCU](https://img.shields.io/badge/MCU-NXP_LPC1768-00599C?style=for-the-badge&logo=nxp&logoColor=white)
![Core](https://img.shields.io/badge/Core-ARM_Cortex--M3-0091BD?style=for-the-badge&logo=arm&logoColor=white)
![IDE](https://img.shields.io/badge/Toolchain-Keil_µVision-002B49?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C_%26_ARM_Assembly-A8B9CC?style=for-the-badge&logo=c&logoColor=black)

</div>

Low-level firmware development, peripheral interfacing, and bare-metal programming on the **NXP LPC1768** microcontroller (ARM Cortex-M3 core, 32-bit RISC up to 100 MHz).

Developed as part of the **Digital Electronic Systems (SED)** engineering curriculum at **Escuela Politécnica Superior (Universidad de Alcalá)**.

---

## 🎯 Key Engineering Competencies Demonstrated

* **Direct Register Manipulation (Bare-Metal):** Configuration of hardware peripherals without high-level abstraction layers by directly programming Memory-Mapped I/O registers (`LPC_PINCON`, `LPC_GPIO`, `LPC_SC`, `LPC_TIM`).
* **Interrupt Handling & NVIC:** Setup and prioritization of hardware interrupt service routines (ISRs) via the ARM Nested Vectored Interrupt Controller.
* **Real-Time Periodic Scheduling:** Configuration of the ARM Cortex SysTick core timer for predictable, periodic task execution.
* **Hardware Timers & Counters:** Prescaler calculation, Match Register (`MR0`) configuration, and timer interrupt generation.
* **Assembly & Memory Architecture:** Stack frame management (`SP`, `LR`), register allocation, and memory addressing modes on ARMv7-M.

---

## 📁 Repository Structure

```text
arm-cortex-embedded-systems/
├── 01-assembly-fundamentals/
│   ├── addressing_modes.s       # Direct, indirect and offset addressing modes on ARM
│   └── stack_operations.s       # Stack pointer manipulation (PUSH/POP) and call stack
├── 02-gpio-logic-analysis/
│   ├── gpio_ports.c             # Fast GPIO control (FIODIR, FIOCLR, FIOSET)
│   └── logic_analyzer.c         # Digital signal generation verified via logic analyzer
├── 03-external-interrupts/
│   └── eint_interrupts.c        # External interrupts (EINT0, EINT1) via NVIC and pinmux
├── 04-systick-timer/
│   └── systick_interrupt.c      # ARM Cortex-M SysTick timer for periodic polling & debouncing
└── 05-hardware-timers/
    └── timer_match_interrupt.c  # 32-bit Hardware Timer1 with prescaler and match registers
```

---

## 🔬 Hardware & Peripheral Breakdown

### 1. Low-Level Assembly (`01-assembly-fundamentals`)
- Exploration of ARMv7-M Thumb-2 instruction set.
- Initialization of Vector Table and Stack Pointer (`STACK_TOP = 0x10000200`).
- Demonstration of memory addressing modes: immediate, register indirect with pre/post-indexed offsets.

### 2. General Purpose Input/Output (`02-gpio-logic-analysis`)
- Pin Multiplexing configuration via `PINSEL` registers to designate pins as GPIO.
- Pull-up / pull-down resistor configuration using `PINMODE`.
- High-speed direct pin toggling using Fast GPIO registers (`LPC_GPIO0->FIODIR`, `FIOSET`, `FIOCLR`).
- Signal inspection and timing verification using Segger J-Link / logic analyzer.

### 3. External Interrupts & NVIC (`03-external-interrupts`)
- Multiplexing pins `P2.10` and `P2.11` to trigger hardware interrupt lines `EINT0` and `EINT1`.
- Edge sensitivity and polarity setup in the External Interrupt Flag (`EXTINT`) and Mode registers.
- Vectoring and enabling IRQs in the Nested Vectored Interrupt Controller (`NVIC_EnableIRQ`).

### 4. Core SysTick Timer (`04-systick-timer`)
- 24-bit down-counter configuration (`SysTick->LOAD`, `SysTick->VAL`, `SysTick->CTRL`).
- Periodic interrupt generation for non-blocking state machines and button debounce logic.
- Interrupt priority tuning via `NVIC_SetPriority(SysTick_IRQn, priority)`.

### 5. 32-Bit Hardware Timers (`05-hardware-timers`)
- Peripheral power management through System Control (`LPC_SC->PCONP`).
- Peripheral Clock divider selection (`PCLKSEL0`) to drive `Timer 1` at $CCLK / 2$.
- Prescaler (`PR`) and Match Register (`MR0`) math for exact frequency generation and automated timer resets via `MCR`.

---

## 🛠️ Toolchain & Setup

1. **IDE:** [Keil µVision 5](https://www.keil.com/) (MDK-ARM).
2. **Device Family Pack:** NXP LPC1700 Series Device Support (`LPC17xx_DFP`).
3. **Debugger / Programmer:** Keil ULINK / Segger J-Link / CMSIS-DAP over SWD (Serial Wire Debug).
4. **Target Board:** LandTiger / MCB1700 or custom LPC1768 development board.

---

## 👤 Author

**Jesús Gay Canelada**  
Telematics Engineering Student @ Universidad de Alcalá (UAH)  
- LinkedIn: [linkedin.com/in/jesus-gay](https://www.linkedin.com/in/jesus-gay)  
- GitHub: [@JesusGC03](https://github.com/JesusGC03)  
- Email: [jgaycanelada@gmail.com](mailto:jgaycanelada@gmail.com)
