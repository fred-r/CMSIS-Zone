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
const version = "0.0.2"

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