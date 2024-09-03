"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.esp32DataSchema = void 0;
const mongoose_1 = __importDefault(require("mongoose"));
const esp32Schema = new mongoose_1.default.Schema({
    sensorMac: { type: String },
    currentCM: { type: Number },
    batteryLevel: { type: Number },
    signalStrength: { type: Number }
});
exports.esp32DataSchema = mongoose_1.default.model('esp32', esp32Schema, 'esp32');
//# sourceMappingURL=esp32Schema.js.map