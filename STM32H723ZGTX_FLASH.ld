/*
******************************************************************************
**
**  File        : LinkerScript.ld
**
**  Author      : STM32CubeIDE
**
**  Abstract    : Linker script for STM32H7 series
**                1024Kbytes FLASH and 560Kbytes RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is, without any warranty
**                of any kind.
**
*****************************************************************************
** @attention
**
** Copyright (c) 2022 STMicroelectronics.
** All rights reserved.
**
** This software is licensed under terms that can be found in the LICENSE file
** in the root directory of this software component.
** If no LICENSE file comes with this software, it is provided AS-IS.
**
****************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM_D1) + LENGTH(RAM_D1);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x20000 ; /* required amount of heap  */
_Min_Stack_Size = 0x3000 ; /* required amount of stack */

/* Specify the memory areas
 * EEPROM emulation in the last 128KB sector of flash (1MB for VG part)
 * DMA buffers for LwIP in first 64K of D1_RAM (needed for SDMMC1 access)
 */

MEMORY
{
  FLASH (rx)        : ORIGIN = 0x08000000, LENGTH = 1024K - 128K
  EEPROM_EMUL (xrw) : ORIGIN = 0x080E0000, LENGTH = 128K
  DTCMRAM (xrw)     : ORIGIN = 0x20000000, LENGTH = 128K
  RAM_D1_DMA (xrw)  : ORIGIN = 0x24000000, LENGTH = 64K
  RAM_D1 (xrw)      : ORIGIN = 0x24010000, LENGTH = 320K - LENGTH(RAM_D1_DMA)
  RAM_D2 (xrw)      : ORIGIN = 0x30000000, LENGTH = 32K
  RAM_D3 (xrw)      : ORIGIN = 0x38000000, LENGTH = 16K
  ITCMRAM (xrw)     : ORIGIN = 0x00000000, LENGTH = 64K
}

_EEPROM_Emul_Start = ORIGIN(EEPROM_EMUL);

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM_D1 AT> FLASH

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM_D1

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM_D1

  /* 64KB section at the beginning of D1 RAM (AXI SRAM), being used
   * for DMA buffers as we need fixed addresses for MPU configuration
   */
  .dma_buffers (NOLOAD) : {

    /* 16KB for LwIP Rx Pool */
    . = ABSOLUTE(0x24000000);
    *(.Rx_PoolSection)

    /* 32KB for LwIP Tx Heap */
    . = ABSOLUTE(0x24004000);
    *(.Tx_HeapSection)

    /* 1KB for LwIP DMA Descriptors */
    . = ABSOLUTE(0x2400C000);
    *(.RxDecripSection)
    . = ABSOLUTE(0x2400C200);
    *(.TxDecripSection)

    /* 15KB currently unused from 0x2400C400 */

  } >RAM_D1_DMA AT> FLASH

  /*
   * Define another data section in DTCM RAM.
   * First use is for boot flags (DFU, USB-Serial passthru).
   */
  .dtcmdata (NOLOAD) :
  {
    . = ALIGN(4);
  } >DTCMRAM

_siitcmram = LOADADDR(.itcmram);
  /* ITCMRAM section */
  .itcmram :
  {
    . = ALIGN(4);
    _sitcmram = .; /* define a global symbols at itcmram start */
    *(.itcmram)
    *(.itcmram*)
    . = ALIGN(4);
    _eitcmram = .; /* define a global symbols at itcmram end */
  } >ITCMRAM AT> FLASH

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
