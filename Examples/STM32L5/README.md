CMSIS-Zone Example for STM32L552
================================

This examples demonstrates the usage of CMSIS-Zone for configuring the
TrustZone configuration for ST's STM32L5 Blinky example.

The CMSIS-Zone project and configuration is stored in Zone folder. See below for
a quick step guide how to open and inspect the configuration.

The adopted MDK project is stored in MDK folder. See further below for a quick step
guide how to open and debug the demo on an STM32L552E-EVAL board.


CMSIS-Zone Configuration
------------------------

The Zone configuration can be loaded in CMSIS-Zone by perfoming the following steps:

1. Start CMSIS-Zone utility (i.e. eclipse.exe)
2. Import project
   - File > Import > Existing Projects into Workspace
   - Select root directory: Examples/STM32L5/Zone
   - Projects: STM32L5
3. Open STM32L5.azone from Project Explorer
4. Click the Generate button in the Zone Editor tool bar
   All FreeMarker templates from ftl folder (\*.ftl) are generated into ftl_gen folder:
   - dump_fzone.txt contains a textual dump of all zone project information.
   - mem_layout.h contains defines for memory region start addresses and sizes.
   - partition_gen.h contains the generated parts for the partition header file.
   - scatter_\*.sct contains scatter file templates.
   - SystemIsolation_Config.c.ftl contains the TrustTone configurations obtained from the project settings.
   
The example zone configuration shows a minimal resource partitioning needed for
TrustZone devices, i.e. blinky_s and blinky_ns zones.

The memory is devided into
individual section for secure and non-secure CODE and DATA, respectively. Additionally
a small flash region is reserved for the non-secure callable veneer table (i.e. secure
gateways). This information is used by the mem_layout.h, the scatter_\*.sct, the SAU setup
in partition_gen.h and the MPC setup in SystemIsolation_Config.c templates.

Some peripherals are assigned to either the secure or the non-secure zone to demonstrate
generation of PPC setup in SystemIsolation_Config.c and interrupt config in partition.h
templates.


MDK Example Project
-------------------

The demo project can be loaded in uVision, built and debugged by perfoming the
following steps:

1. Navigate to Examples\STM32L5\MDK
2. Opeb blinky.uvmpw to open the uVision multi-project workspace.
3. Optional: Update the generated files by executing the copy_gen.bat script.
4. Run the batch build in MDK.
   Both projects, blinky_s and blinky_ns needs to be compiled in order.
5. Assure blinky_s is the active project.
6. Connect the STM32L552E-EVAL using a Micro-USB cable at CN22.
7. Assure that ST-Link Debugger is selected and the ST-Link/V2-1 is used.
8. Launch a debug session and watch the serial console output.


fred-r's tweaks to play around with Handlebars
----------------------------------------------

The intention here is to generate the C code with handlebars (https://handlebarsjs.com/) as the templating engine instead of freemarker.

This is restricted to the STM32L5 example.
In this example, two new folders named 
* 'handlebars' : hosting the templates
* 'handlebars_gen' : hosting the generated code  

are added in the STM32L5 project (CMSIS-Zone\Examples\STM32L5\Zone).  
We do not manage the blinky_s and blinky_ns subfolders.  
We focus on the application project level.

We also add a directory named 'tools' where we put a minimal codegen tool written in JavaScript.

### Handlebars in a nutshell

Handlebars uses a template and an input object to generate the text we want (C code in our case).   
A Handlebars template is just some text that contains Handlebars expressions.  
Once you have a template (basically a string, in our case coming from a template file), the next step is to compile that string into a Handlebars template function.   
You can then render the template by passing a data object (also known as a context) into that function.

Example:
* our codegen template stored in mem_layout_template.h is loaded in *handlebars_template_string*  
* our data (platform and user settings) stored in STM32L5.azone.json is loaded in *data_object*

Handlebars invokation looks like :
```
template_function = handlebars.compile(handlebars_template_string)
generated_code = template_function(data_object)
```


### Settings

For the time being, we do not pay attention to the rzone.  
We will convert STM32L5.fzone from XML to JSON format because handlebars requires a Javascript Object as input object and JSON is supported natively by JavaScript (but XML could do the job as well).

Also: as the developer needs to get oriented in the fields, I think JSON is far more convenient than XML.


To do this conversion, we use an online tool: https://jsonformatter.org/xml-to-json

Let's store the result in STM32L5.fzone.json

### Invoking the codegen

The idea is to work from: CMSIS-Zone\Examples\STM32L5\Zone  

Please refer to : CMSIS-Zone\Examples\STM32L5\Zone\tools\README.md  
for installing all required packages.

The templates are in the folder: *handlebars*  
The generated code will be storedin the folder: *handlebars_gen* 

The codegen is invoked this way:  

```
node ./tools/mini_codegen --template ./handlebars/mem_layout_template.h --data ./STM32L5.fzone.json --output ./handlebars_gen/mem_layout.h
```

FIXME: At the moment, you need to invoke this command individually for each supported template.
