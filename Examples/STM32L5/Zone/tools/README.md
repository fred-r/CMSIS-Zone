# Basic handlebars codegen tool

## Requirements

Install node.js available on https://nodejs.org/en/

Requires also:
* handlebars, 
* handlebars-helpers,
* yargs

So from: CMSIS-Zone\Examples\STM32L5\Zone\tools

```
npm install handlebars
npm install yargs
npm install handlebars-helpers
```

## Usage
Calling the tool from : CMSIS-Zone\Examples\STM32L5\Zone  

```
node ./tools/mini_codegen --template ./handlebars/mem_layout_template.h --data ./STM32L5.azone.json --output ./handlebars_gen/mem_layout.h
```

