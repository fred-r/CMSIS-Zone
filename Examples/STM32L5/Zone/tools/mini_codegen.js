/******************** (C) COPYRIGHT 2021 fred-r ******************************
* File    mini_codegen.js
* Author  fred-r
* This tool uses handlebars.js to generate some C code.
******************************************************************************
*
* Copyright (c) 2021 fred-r. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* Neither the name of fred-r nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

/* ----------------------------------------------------------------------
 * This is some crappy code to invoke handlebars written by a C developer
 * We will not use object-oriented programming.
 * ---------------------------------------------------------------------- */
const version = "0.0.3"

/* ------- */
/* MODULES */
/* ------- */
const yargs = require('yargs');
const { hideBin } = require("yargs/helpers");

/* ------- */
/* GLOBALS */
/* ------- */
let argv;  /* command line arguments */

let codegen_template;  /* codegen template file (C code instrumented with Handlebars expressions) */
let fzone_data;        /* application configuration declared in the fzone file */
let generated_file;    /* codegen output file */

let fs = require("fs"); /* files operations */

let handlebars = require("handlebars"); /* the handlebars engine */
/* some standard handlebars helpers we may use */
let helpers = require('handlebars-helpers')({
  handlebars: handlebars
});

/* ------------------ */
/* HANDLEBARS HELPERS */
/* ------------------ */
let my_global_counter;    /* a global value that gets updated by handlebar */

/**
 * Initializes the global counter and returns it.
 * @param  {integer} value The value to be set in the global counter
 * @return nothing
 */
 handlebars.registerHelper("init_global", function(value) {
    my_global_counter = value;
 });

/**
 * Updates the global counter and returns it.
 * @param  {integer} inc The value to be added to the global counter
 * @return nothing
 */
 handlebars.registerHelper("increment_global", function(inc) {
    my_global_counter += inc;
 });

 /**
 * Returns the global counter.
 * @return nothing
 */
  handlebars.registerHelper("get_global", function(options) {
    return my_global_counter;
  });

/**
 * Parse the command line arguments.
 * @param  {string} hex_str1 First element to add in hexadecimal format
 * @param  {string} hex_str2 Second element to add in hexadecimal format
 * @return the sum of the two arguments as a string (result in hexadecimal format)
 */
handlebars.registerHelper("hex_add", function (hex_str1, hex_str2) {
    if ( (hex_str1 && typeof hex_str1 === "string") &&
         (hex_str2 && typeof hex_str2 === "string") ) {
            var arg1 = parseInt(hex_str1, 16);
            var arg2 = parseInt(hex_str2, 16);
            var res = arg1 + arg2;
            return (res.toString(16).toUpperCase())
    }
    return "hex_add error";
  });


/**
 * Converts a string into an integer .
 * @param  {string} str The string to be converted (integer in decimal format)
 * @return the integer value
 */
handlebars.registerHelper("str2int", function(str) {
        return parseInt(str,10);
});

/**
 * Formats an integer in hexadecimal format
 * @param  {integer} value The value to be displayed in hexadecimal format
 * @return the integer value
 */
 handlebars.registerHelper("show_hex", function(value) {
    return (value.toString(16).toUpperCase());
 });

/**
 * Stores a value in a variable.
 * @param  {string} varName name of the variable
 * @param  {string} varValue value of the variable
 * @param  {???} options options-object
 * @return nothing
 */
  handlebars.registerHelper("setVar", function(varName, varValue, options) {
    options.data.root[varName] = varValue;
  });

/**
 * retrieves the value from variable.
 * @param  {string} varName name of the variable
 * @param  {???} options options-object
 * @return value stored in the variable
 */
 handlebars.registerHelper("getVar", function(varName, options) {
    return(options.data.root[varName]);
 });

/**
 * Addition.
 * @param  {integer} a First element to add
 * @param  {integer} b Second element to add
 * @return the sum of the two arguments as an integer
 */
 handlebars.registerHelper("add", function (a, b) {
    return (a+b);
 });

/**
 * Substraction.
 * @param  {integer} a First element
 * @param  {integer} b Second element
 * @return a - b as an integer
 */
 handlebars.registerHelper("sub", function (a, b) {
    return (a-b);
 });

/**
 * Multiplication.
 * @param  {integer} a First element
 * @param  {integer} b Second element
 * @return the multiplication of the two arguments as an integer
 */
 handlebars.registerHelper("mult", function (a, b) {
    return (a*b);
 });

/**
 * Division.
 * @param  {integer} a First element
 * @param  {integer} b Second element
 * @return the division of the two arguments as an integer
 */
 handlebars.registerHelper("div", function (a, b) {
  return (a/b);
});

/**
 * Returns the power P of the input value
 * @param  {integer} value The value
 * @param  {integer} power The power
 * @return math.pow(value,power)
 */
 handlebars.registerHelper("power", function(value, power) {
    return Math.pow(value, power);
 });


/**
 * Repeats block n times and pass the counter as a aprameter to the template function.
 * @param  {integer} n repeat the block n times
 * @param  {string} block the block to be repeated (pattern)
 * @return the generated text where block is interpreted n times, each time with the current counter value as a parameter
 */
handlebars.registerHelper('block_loop', function(n, block) {
    var output_text = '';
    for(var i = 0; i < n; ++i)
        output_text += block.fn(i);
    return output_text;
});


/**
 * Check if a value is in the given range.
 * @param  {integer} val value to be checked
 * @param  {integer} min range.min
 * * @param  {integer} max range.max
 * @return true if in the range, false otherwise
 */
 handlebars.registerHelper("is_in_range", function (val, min, max) {
    if ( (val >= min) && (val <= max) ) {
        return true;
    } else {
        return false;
    }
  });



/**
 * Converts val as 32-bit unsigned integer to 8 digits hexadecimal number.
 * @param  {integer} val The value to be printed as 0x........
 * @return string formatted as 0x........
 */
function hex32(val) {
  var hex = val.toString(16).toUpperCase();
  hex = hex.padStart(8, "0")
  return "0x"+hex;
}

/**
 * Computes a 32-bit register value from an array of bits.
 * @param  {integer} idx The value of the first index in the array of bits
 * @param  {array} array The array of bits (at least 32 bits long after idx)
 * @return the value stored in the register
 */
 handlebars.registerHelper("compute_reg_value", function(idx, array) {
  let value = 0;
  for(var i = 0; i < 32; i++) {
    value = value + (parseInt(array[idx + i],10) * Math.pow(2, i));
  }
  return(hex32(value));
});

/**
 * String replacement
 * @param  {string} find Pattern to be replaced
 * @param  {string} replace Pattern to be inserted
 * @param  {???} options options-object
 * @return the result string (replacement performed)
 */
handlebars.registerHelper('replace', function( find, replace, options) {
  var string = options.fn(this);
  return string.replace( find, replace );
});

/* ------- */
/* HELPERS */
/* ------- */

/**
 * Do the code generation
 * @return nothing
 */
function invokeCodegen() {
    /* Load the codege template into a string */
    try {
        handlebars_template_string = fs.readFileSync(codegen_template).toString();
      } catch (error) {
        console.log("[ERROR] " + error);
      }

    /* Load the configuration data into a javascript object */
    try {
        dictionary = fs.readFileSync(fzone_data).toString();
      } catch (error) {
        console.log("[ERROR] " + error);
      }
    data_object = JSON.parse(dictionary);

    /* Generate the template function by processing the template string*/
    template_function = handlebars.compile(handlebars_template_string)

    /* Generate the code by taking into account the data object */
    generated_code = template_function(data_object)

    /* Generate the output file */
    try {
        fs.writeFileSync(generated_file, generated_code);
        console.log("[INFO] Code generation completed successfully in: " + generated_file)
    } catch (error) {
        console.log("[ERROR] " + error);
    }
}

/**
 * Initializes the global variables from the command line arguments
 * @return nothing
 */
function setGlobals() {
    /* codegen template */
    if (argv.template) {
        if (fs.existsSync(argv.template)) {
            codegen_template = argv.template;
            console.log("[INFO]: codegen template is " + codegen_template);
        } else {
            console.log("[ERROR]: template file not found");
            process.exit();
        }
    }
    else {
        console.log("[ERROR]: need a codegen template as 1st input parameter.");
        process.exit();
    }

    /* fzone settings  */
    if (argv.template) {
        if (fs.existsSync(argv.data)) {
            fzone_data = argv.data;
            console.log("[INFO]: configuration settings taken from " + fzone_data);
        } else {
            console.log("[ERROR]: data file not found");
            process.exit();
        }
    }
    else {
        console.log("[ERROR]: need a data as 2nd input parameter.");
        process.exit();
    }

    /* codegen template */
    if (argv.output) {
        generated_file = argv.output;
        console.log("[INFO]: generating code in " + generated_file);
    }
    else {
        console.log("[ERROR]: need an output file name as 3rd input parameter.");
        process.exit();
    }
}

/**
 * Parse the command line arguments.
 * @param  {string} template The codegen template file to be processed.
 * @param  {string} data The fzone.json file containing the data to be used with the codegen template.
 * @param  {string} output The resulting C file.
 * @return nothing
 */
function commandLineHandler() {
    argv = yargs(hideBin(process.argv))
      .option("template", { type: "string" })
      .option("data", { type: "string" })
      .option("output", { type: "string" }).argv;
  }


/* ----------- */
/* ENTRY POINT */
/* ----------- */

/**
 * Entry point of this crappy application.
 * @return nothing
 */
function main() {
    console.log("[INFO] mini_codegen - START OF PROCESSING (version: " + version+ ")");
    commandLineHandler();
    setGlobals();
    invokeCodegen();
    console.log("[INFO] mini_codegen - END OF PROCESSING");
}

/* Let's get started ... */
main();