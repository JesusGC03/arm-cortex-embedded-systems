# ARM Cortex-M3 (NXP LPC1768) Embedded Firmware & Peripherals

<div align="center">

![MCU](https://img.shields.io/badge/MCU-NXP_LPC1768-00599C?style=for-the-badge&logo=nxp&logoColor=white)
![Core](https://img.shields.io/badge/Core-ARM_Cortex--M3-0091BD?style=for-the-badge&logo=arm&logoColor=white)
![IDE](https://img.shields.io/badge/Toolchain-Keil_µVision-002B49?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C_%26_ARM_Assembly-A8B9CC?style=for-the-badge&logo=c&logoColor=black)

</div>

Bare-metal firmware development, peripheral interfacing, and low-level driver programming on the **NXP LPC1768** microcontroller (ARM Cortex-M3 core, 32-bit RISC architecture up to 100 MHz).

Developed as part of the **Digital Electronic Systems (SED)** engineering curriculum at **Escuela Politécnica Superior (Universidad de Alcalá)**.

---

## 🎯 Engineering Highlights & Implemented Features

* **Direct Register Manipulation (Bare-Metal):** Configuration of Memory-Mapped I/O registers (`LPC_PINCON`, `LPC_GPIO`, `LPC_SC`, `LPC_TIM`) without third-party abstraction layers.
* **NVIC Interrupt Vectoring & Priority Grouping:** Dual external interrupt service routines (`EINT0` and `EINT1`) with programmable edge polarity, interrupt pending flags, and priority arbitration via the Nested Vectored Interrupt Controller.
* **Real-Time Periodic Scheduling (SysTick):** Interrupt-driven digital clock and stopwatch maintaining seconds and minutes, integrated with hardware external reset routines.
* **Hardware Timers & PWM/Match Logic:** 32-bit Timer1 prescaler math, Match Register (`MR0`) threshold interrupts, and automated counter reset logic.
* **Fast GPIO & Pin Multiplexing:** Bidirectional bitwise LED sequencers, pull-up/pull-down resistor control (`PINMODE`), and J-Link debug routines.

---

## 📁 Repository Structure

```text
arm-cortex-embedded-systems/
├── 01-assembly-fundamentals/
│   ├── addressing_modes.s       # Direct, register-indirect, and pre/post-indexed addressing
│   └── memory_and_stack.s       # Stack pointer manipulation, memory blocks, and register initialization
├── 02-gpio-and-pinmux/
│   ├── gpio_sequencer.c         # Fast GPIO bitwise shifter and bidirectional LED sequencer
│   ├── jlink_gpio_debug.c       # Pin multiplexing (PINSEL/PINMODE) and Segger J-Link debugging
│   ├── delay.c                  # Calibrated busy-wait millisecond delay driver
│   └── delay.h                  # Delay function prototypes
├── 03-external-interrupts-nvic/
│   └── eint_priority_handlers.c # Dual EINT0/EINT1 with edge triggers, NVIC priority, and GPIO handshake
├── 04-systick-timer/
│   └── systick_digital_clock.c  # Core SysTick periodic timer maintaining digital clock with EINT0 reset
└── 05-hardware-timers/
    └── timer_match_interrupt.c  # 32-bit Timer1 prescaler, Match Register 0, and interrupt routines
```

---

## 🔬 Hardware & Peripheral Architecture

### 1. Low-Level Assembly (`01-assembly-fundamentals`)
- Execution on ARMv7-M Thumb-2 instruction set.
- Vector Table initialization and Stack Pointer setup (`STACK_TOP = 0x10000200`).
- Demonstration of load/store multiple (`LDM`/`STM`) and stack frame mechanics (`PUSH`/`POP`).

### 2. General Purpose Input/Output & Pinmux (`02-gpio-and-pinmux`)
- Pin Function Select (`PINSEL0` to `PINSEL7`) to assign physical pins to GPIO or dedicated hardware controllers.
- Pin Mode configuration (`PINMODE`) for tri-state, pull-up, and pull-down configurations.
- Bidirectional circular bit-shifting on port `P0.[0..3]` with register-level port masking (`FIODIR`, `FIOCLR`, `FIOPIN`).
- Hardware verification with Segger J-Link logic probes.

### 3. Nested Vectored Interrupt Controller & EINT (`03-external-interrupts-nvic`)
- Hardware pin mapping: `P2.10` $\rightarrow$ `EINT0` and `P2.11` $\rightarrow$ `EINT1`.
- Edge detection logic via `EXTMODE` and polarity selection via `EXTPOLAR` (e.g., falling edge on `EINT1`, rising edge on `EINT0`).
- Priority arbitration using `NVIC_SetPriorityGrouping(4)` and sub-priority assignment (`NVIC_SetPriority`).
- Interrupt flag acknowledgment and clearing in `EXTINT` and pending IRQs in `NVIC_ClearPendingIRQ`.

### 4. SysTick Core Timer (`04-systick-timer`)
- 24-bit core system timer configured at 100 MHz clock frequency (`SysTick->LOAD`, `SysTick->CTRL = 0x7`).
- Implemented real-time clock tracking `segundos` and `minutos` non-blocking state machine.
- Asynchronous reset capability tied to external push-button interrupt (`EINT0_IRQHandler`).

### 5. 32-Bit Hardware Timers (`05-hardware-timers`)
- Peripheral power control via System Control register (`LPC_SC->PCONP`).
- Peripheral Clock selection (`PCLKSEL0`) to clock Timer1 at $CCLK / 2$.
- Prescaler (`PR`) and Match Register (`MR0`) calculations for accurate frequency synthesis and interrupt generation via Match Control Register (`MCR`).

---

## 🛠️ Toolchain & Development Environment

1. **IDE:** [Keil µVision 5](https://www.keil.com/) (MDK-ARM).
2. **Device Family Pack:** NXP LPC1700 Series Device Support (`LPC17xx_DFP`).
3. **Hardware / Simulator:** NXP LPC1768 board (Cortex-M3) / Keil µVision Simulator & Segger J-Link over SWD.

---

## 👤 Author

**Jesús Gay Canelada**  
Telematics Engineering Student @ Universidad de Alcalá (UAH)  
- LinkedIn: [linkedin.com/in/jesus-gay](https://www.linkedin.com/in/jesus-gay)  
- GitHub: [@JesusGC03](https://github.com/JesusGC03)  
- Email: [jgaycanelada@gmail.com](mailto:jgaycanelada@gmail.com)
