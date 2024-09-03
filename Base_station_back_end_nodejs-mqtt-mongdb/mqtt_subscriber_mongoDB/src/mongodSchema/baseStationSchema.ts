import mongoose from "mongoose";

// const baseStationSchema = new mongoose.Schema({
//     sensorMac : {type : String},
//     currentCM : {type : Number},
//     batteryLevel : {type : Number},
//     signalStrength : {type: Number}
// });


const baseStationSchema = new mongoose.Schema({
    NodeID : {type : Number},
    PayloadID : {type : Number},
    Accelerometer : {type : String},
    // ay : {type: Number},
    // az : {type: Number},
    Gyroscope : {type: String},
    // gy : {type: Number},
    // gz : {type: Number},
    Temperature : {type: Number},
    Current_Time : { type : String}
});


export const baseStationDataSchema = mongoose.model('baseStation', baseStationSchema, 'baseStation');