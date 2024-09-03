import mongoose from 'mongoose';


// const url = "mongodb://127.0.0.1/BaseStation";
// const url = "mongodb+srv://shohaniu8:PUzWtWh43jm63ael@test-mongodb-1.dfh2ki0.mongodb.net/?retryWrites=true&w=majority&appName=test-mongodb-1";
const url = "mongodb+srv://r-fine:m0ng0ap$10t@apsiot.xq0fdv2.mongodb.net";


// export function mongoConn(){
//     mongoose.connect(url)

//     console.log("Connected to MongoDB")
    
// }


export function mongoConn() {

    mongoose.connect(url, {
    }).then(() => {
        console.log("Database Connected");
    }).catch((err) => console.log(err));

}


