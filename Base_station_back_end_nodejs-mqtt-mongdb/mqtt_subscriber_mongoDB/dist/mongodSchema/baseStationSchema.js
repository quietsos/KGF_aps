"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.baseStationDataSchema = void 0;
const mongoose_1 = __importDefault(require("mongoose"));
// const baseStationSchema = new mongoose.Schema({
//     sensorMac : {type : String},
//     currentCM : {type : Number},
//     batteryLevel : {type : Number},
//     signalStrength : {type: Number}
// });
const baseStationSchema = new mongoose_1.default.Schema({
    NodeID: { type: Number },
    PayloadID: { type: Number },
    Accelerometer: { type: String },
    // ay : {type: Number},
    // az : {type: Number},
    Gyroscope: { type: String },
    // gy : {type: Number},
    // gz : {type: Number},
    Temperature: { type: Number },
    Current_Time: { type: String }
});
exports.baseStationDataSchema = mongoose_1.default.model('baseStation', baseStationSchema, 'baseStation');
//# sourceMappingURL=baseStationSchema.js.map