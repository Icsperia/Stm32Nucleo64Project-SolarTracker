This repository provides the essential Verilog and SystemVerilog source code required to synthesize a robust digital spirit level on a field-programmable gate array (FPGA). The system's architecture is strictly modular, cleanly separating physical hardware connections, serial communication layers, core algorithmic processing, and human-readable output translation.  

File Structure and Module Hierarchy
The project directory is built upon a top-level wrapper that coordinates several specialized sub-modules:

    DE10_LITE_Golden_Top.v: This standard Verilog file acts as the top-level structural entity for the entire hardware design. In the context of DE10-Lite FPGA development, the Golden Top module defines all physical input, output, and bidirectional pin assignments. It functions as the central hub where clock signals are routed and all subsequent logical modules are instantiated and wired together.  

    two_way_spirit_level.sv: Developed in SystemVerilog, this file houses the core computational logic of the application. It ingests raw spatial data and calculates the device's exact inclination across two distinct axes (typically X and Y), generating the fundamental mathematical behavior necessary for a dual-axis spirit level system.  

    spi_phy.sv: This SystemVerilog module is engineered to implement the physical layer of the Serial Peripheral Interface (SPI) protocol. It handles the stringent timing, clock generation (SCLK), and data sequencing (MOSI/MISO) required to communicate with the board's embedded accelerometer. This module acts as the crucial bridge for gathering the raw spatial and gravitational metrics needed by the central logic engine.  

    seg.sv: This SystemVerilog module serves as the peripheral display driver. It continuously receives the processed tilt and orientation values from the core logic and translates them into the precise multiplexing signaling patterns required to illuminate external 7-segment displays. This provides the user with an immediate, visual representation of the measured angles.  

System Architecture and Data Flow

    Hardware Interfacing: The design utilizes the physical layer SPI module to establish a high-speed data link with the sensor hardware, actively sampling raw multi-axis acceleration vectors.  

    Data Processing: Once acquired, the raw sensor signals are piped directly into the two-way spirit level module, which filters and mathematically maps the data to geometric planes.  

    Data Visualization: The finalized tilt metrics are routed through the segment driver, converting raw binary calculations into human-readable numeric or graphical outputs on the physical hardware displays.  

    Top-Level Integration: All internal processes, state machines, and I/O assignments are synchronized by the board's primary clock and mapped to the physical silicon via the Golden Top wrapper, ensuring a stable, synthesis-ready design.
