@ECHO OFF
XCopy /Y ..\Zone\handlebars_gen\SystemIsolation_config.c blinky_s
XCopy /Y ..\Zone\handlebars_gen\partition_gen.h blinky_s\RTE\Device\STM32L552ZETxQ
XCopy /Y ..\Zone\handlebars_gen\mem_layout.h .\
XCopy /Y ..\Zone\handlebars_gen\scatter_s.sct blinky_s\RTE\Device\STM32L552ZETxQ
XCopy /Y ..\Zone\handlebars_gen\scatter_ns.sct blinky_ns\RTE\Device\STM32L552ZETxQ
XCopy /Y ..\Zone\handlebars_gen\scatter_s.sct blinky_s\blinky_s.sct
XCopy /Y ..\Zone\handlebars_gen\scatter_ns.sct blinky_ns\blinky_ns.sct


