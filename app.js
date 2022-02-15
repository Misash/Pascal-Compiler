

const { exec } = require('child_process');
const express = require("express");
const bodyParser = require("body-parser");
const ejs = require("ejs");
const fs = require('fs');
const { diffieHellman } = require('crypto');


const app = express();

app.set('view engine', 'ejs');

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static("public"));



let pascalCode = ""
let shell = ""


app.get("/", (req, res) => {


    res.render("home", { pascalCode: pascalCode, shell: shell })
})

app.post("/compile", (req, res) => {

    pascalCode = req.body.code

    writeToFile()
    compileParser()
    
    console.log("redirect")
    res.redirect("/")
})




app.listen(3000, function () {
    console.log("Server started on port 3000");
});



function writeToFile() {

    fs.writeFile('./test/main.pas', pascalCode, err => {
        if (err) {
            console.error(err)
            return
        }
    })
}


function compileParser() {
    const command = "cd src/  && g++ parser.cpp -o myprog && ./myprog"
    exec(command, (error, stdout, stderr) => {

        if (error) {
            shell = "error"
            console.error(`exec error: ${error}`);
            return;
        }

        if (stdout.length != 0) {
            shell = stdout
            console.log(stdout);
        } else {
            exec("cd test/ && node code.js", (err, jsout, jserr) => {
                if (err) {
                    shell = err.message
                    console.log(`error: ${err.message}`);
                    return;
                }
                shell = jsout
                console.log(`${jsout}`);
            })
        }

    });

}
