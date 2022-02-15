

const { exec } = require('child_process');




//copio html a mainpas





const command = "cd src/  && g++ parser.cpp -o myprog && ./myprog"

exec(command, (error, stdout, stderr) => {
    if (error) {
        console.error(`exec error: ${error}`);
        return;
    }

    if(stdout.length != 0){
        console.log( stdout);
    }else{
        exec("cd test/ && node code.js",(err,jsout,jserr)=>{
            if (err) {
                console.log(`error: ${err.message}`);
                return;
            }
            console.log(`${jsout}`);
        })
    }

});



