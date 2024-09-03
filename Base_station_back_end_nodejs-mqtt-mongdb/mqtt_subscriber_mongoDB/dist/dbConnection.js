"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.mongoConn = void 0;
const mongoose_1 = __importDefault(require("mongoose"));
// const url = "mongodb://127.0.0.1/BaseStation";
// const url = "mongodb+srv://shohaniu8:PUzWtWh43jm63ael@test-mongodb-1.dfh2ki0.mongodb.net/?retryWrites=true&w=majority&appName=test-mongodb-1";
const url = "mongodb+srv://r-fine:m0ng0ap$10t@apsiot.xq0fdv2.mongodb.net";
// export function mongoConn(){
//     mongoose.connect(url)
//     console.log("Connected to MongoDB")
// }
function mongoConn() {
    mongoose_1.default.connect(url, {}).then(() => {
        console.log("Database Connected");
    }).catch((err) => console.log(err));
}
exports.mongoConn = mongoConn;
//# sourceMappingURL=dbConnection.js.map