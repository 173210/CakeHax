ENTRY(_start)
SECTIONS
{
    .text.spider : { *(.text.spider) }
    .rodata.spider : { *(.rodata.spider) }
    .text.mset : { *(.text.mset) }
    .text.start : { *(.text.start) }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
}
